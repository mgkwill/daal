/* file: batch_normalization_layer_backward_impl.i */
/*******************************************************************************
* Copyright 2014-2017 Intel Corporation
* All Rights Reserved.
*
* If this  software was obtained  under the  Intel Simplified  Software License,
* the following terms apply:
*
* The source code,  information  and material  ("Material") contained  herein is
* owned by Intel Corporation or its  suppliers or licensors,  and  title to such
* Material remains with Intel  Corporation or its  suppliers or  licensors.  The
* Material  contains  proprietary  information  of  Intel or  its suppliers  and
* licensors.  The Material is protected by  worldwide copyright  laws and treaty
* provisions.  No part  of  the  Material   may  be  used,  copied,  reproduced,
* modified, published,  uploaded, posted, transmitted,  distributed or disclosed
* in any way without Intel's prior express written permission.  No license under
* any patent,  copyright or other  intellectual property rights  in the Material
* is granted to  or  conferred  upon  you,  either   expressly,  by implication,
* inducement,  estoppel  or  otherwise.  Any  license   under such  intellectual
* property rights must be express and approved by Intel in writing.
*
* Unless otherwise agreed by Intel in writing,  you may not remove or alter this
* notice or  any  other  notice   embedded  in  Materials  by  Intel  or Intel's
* suppliers or licensors in any way.
*
*
* If this  software  was obtained  under the  Apache License,  Version  2.0 (the
* "License"), the following terms apply:
*
* You may  not use this  file except  in compliance  with  the License.  You may
* obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*
* Unless  required  by   applicable  law  or  agreed  to  in  writing,  software
* distributed under the License  is distributed  on an  "AS IS"  BASIS,  WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
* See the   License  for the   specific  language   governing   permissions  and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Implementation of backward batch normalization layer
//--
*/

#ifndef __BATCH_NORMALIZATION_LAYER_BACKWARD_IMPL_I__
#define __BATCH_NORMALIZATION_LAYER_BACKWARD_IMPL_I__

#include "service_math.h"
#include "threading.h"

using namespace daal::services;

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace batch_normalization
{
namespace backward
{
namespace internal
{

/* pre-defined adjustable sizes */
#define _MIN_THREAD_SIZE_    16384
#define _MAX_BLOCK_KJ_SIZE_  1048576
#define _MIN_BLOCK_KJ_SIZE_  1024
#define _DEF_BLOCKS_MUL_     2

/* Common structure with arrays and variables */
template<typename algorithmFPType, Method method, CpuType cpu>
struct common_batchnorm_data_t
{
    /**************** Constructor **************************************************/
    common_batchnorm_data_t( const Tensor &inputGradientTensor,
                             const batch_normalization::Parameter &parameter ):
        _propagate_gradient(parameter.propagateGradient)
    {
        const services::Collection<size_t> &dims = inputGradientTensor.getDimensions();

        const size_t _dimension = parameter.dimension;
        _dimensionSize  = dims[_dimension];
        _dimension0Size = dims[0];
        _nDims          = dims.size();

        _offsetBefore   = (_dimension == 0 ? 1 : inputGradientTensor.getSize(0, _dimension));
        _offsetAfter    = (_dimension == _nDims - 1 ? 1 : inputGradientTensor.getSize(_dimension + 1, _nDims - _dimension - 1));
    }

    Status init( Tensor &gradientTensor,
                 const Tensor &weightsTensor,
                 const Tensor &stDevTensor,
                 const Tensor &inputGradientTensor,
                 const Tensor &dataTensor,
                 const Tensor &meanTensor,
                 Tensor &weightsDerTensor,
                 Tensor &biasesDerTensor)
    {
        _weights = _weightsBlock.set(const_cast<Tensor&>(weightsTensor), 0, 0, 0, _dimensionSize);
        DAAL_CHECK_BLOCK_STATUS(_weightsBlock);

        _stDev = _stDevBlock.set(const_cast<Tensor &>(stDevTensor), 0, 0, 0, _dimensionSize);
        DAAL_CHECK_BLOCK_STATUS(_stDevBlock);

        _inputGradient = _inputGradientBlock.set(const_cast<Tensor &>(inputGradientTensor), 0, 0, 0, _dimension0Size);
        DAAL_CHECK_BLOCK_STATUS(_inputGradientBlock);

        _data = _dataBlock.set(const_cast<Tensor &>(dataTensor), 0, 0, 0, _dimension0Size);
        DAAL_CHECK_BLOCK_STATUS(_dataBlock);

        _mean = _meanBlock.set(const_cast<Tensor &>(meanTensor), 0, 0, 0, _dimensionSize);
        DAAL_CHECK_BLOCK_STATUS(_meanBlock);

        _weightsDer = _weightsDerBlock.set(weightsDerTensor, 0, 0, 0, _dimensionSize);
        DAAL_CHECK_BLOCK_STATUS(_weightsDerBlock);

        _biasesDer = _biasesDerBlock.set(biasesDerTensor, 0, 0, 0, _dimensionSize);
        DAAL_CHECK_BLOCK_STATUS(_biasesDerBlock);

        _invStDev = _invStDevPtr.reset(_dimensionSize);
        DAAL_CHECK_MALLOC(_invStDev);

        if(_propagate_gradient)
        {
            _gradient = _gradientBlock.set(gradientTensor, 0, 0, 0, _dimension0Size);
            DAAL_CHECK_BLOCK_STATUS(_gradientBlock);

            _invStDevByWeights = _invStDevByWeightsPtr.reset(_dimensionSize);
            _biasesDerMultiplier = _biasesDerMultiplierPtr.reset(_dimensionSize);
            _weightsDerMultiplier = _weightsDerMultiplierPtr.reset(_dimensionSize);
            DAAL_CHECK_MALLOC(_invStDevByWeights && _biasesDerMultiplier && _weightsDerMultiplier);
        }

        PRAGMA_IVDEP
        PRAGMA_VECTOR_ALWAYS
        for (size_t k = 0; k < _dimensionSize; k++)
        {
            _weightsDer[k]  = (algorithmFPType)0.0;
            _biasesDer[k]   = (algorithmFPType)0.0;
        }

        return Status();
    }

    /*******************************************************************************/

    /****************** Calculate weight and bias derivatives ***********************/
    void compute_weights_biases(size_t i_index, size_t kbeg, size_t kend)
    {
        for(size_t k = kbeg; k < kend; k++)
        {
            size_t idx_ik = ( i_index * _dimensionSize + k ) * _offsetAfter;

            algorithmFPType biasesDerSum  = 0.0;
            algorithmFPType weightsDerSum = 0.0;

            algorithmFPType m = _mean[k];
            algorithmFPType s = _invStDev[k];

            PRAGMA_IVDEP
            PRAGMA_VECTOR_ALWAYS
            for ( size_t j = 0; j < _offsetAfter; j++ )
            {
                algorithmFPType g = _inputGradient[ idx_ik + j ];
                algorithmFPType d = _data[ idx_ik + j ];

                biasesDerSum   += g;
                weightsDerSum  += g * (d - m) * s;
            }

            _biasesDer[k]  += biasesDerSum;
            _weightsDer[k] += weightsDerSum;
        }

        return;
    }
    /*******************************************************************************/

    /****************** Calculate output gradients *********************************/
    void compute_gradients(size_t i_index, size_t kbeg, size_t kend)
    {
        for(size_t k = kbeg; k < kend; k++)
        {
            size_t idx_ik = ( i_index * _dimensionSize + k ) * _offsetAfter;

            algorithmFPType iw = _invStDevByWeights[k];
            algorithmFPType bm = _biasesDerMultiplier[k];
            algorithmFPType wm = _weightsDerMultiplier[k];
            algorithmFPType m  = _mean[k];

            PRAGMA_IVDEP
            PRAGMA_VECTOR_ALWAYS
            for ( size_t j = 0; j < _offsetAfter; j++ )
            {
                algorithmFPType g = _inputGradient[ idx_ik + j ];
                algorithmFPType d = _data[ idx_ik + j ];

                _gradient[ idx_ik + j ] =  iw * ( g - bm - wm * ( d - m ) );
            }
        }

        return;
    }
    /*******************************************************************************/

    ReadSubtensor<algorithmFPType, cpu> _weightsBlock;
    ReadSubtensor<algorithmFPType, cpu> _stDevBlock;
    ReadSubtensor<algorithmFPType, cpu> _inputGradientBlock;
    ReadSubtensor<algorithmFPType, cpu> _dataBlock;
    ReadSubtensor<algorithmFPType, cpu> _meanBlock;
    WriteOnlySubtensor<algorithmFPType, cpu> _weightsDerBlock;
    WriteOnlySubtensor<algorithmFPType, cpu> _biasesDerBlock;
    WriteOnlySubtensor<algorithmFPType, cpu> _gradientBlock;

    const algorithmFPType *_weights;
    const algorithmFPType *_stDev;
    const algorithmFPType *_inputGradient;
    const algorithmFPType *_data;
    const algorithmFPType *_mean;
    algorithmFPType *_gradient;
    algorithmFPType *_weightsDer;
    algorithmFPType *_biasesDer;

    TArray<algorithmFPType, cpu> _invStDevPtr;
    algorithmFPType *_invStDev;

    TArray<algorithmFPType, cpu> _invStDevByWeightsPtr;
    TArray<algorithmFPType, cpu> _biasesDerMultiplierPtr;
    TArray<algorithmFPType, cpu> _weightsDerMultiplierPtr;

    algorithmFPType *_invStDevByWeights;
    algorithmFPType *_biasesDerMultiplier;
    algorithmFPType *_weightsDerMultiplier;

    const int _propagate_gradient;
    size_t _dimension0Size;
    size_t _dimensionSize;
    size_t _nDims;
    size_t _offsetBefore;
    size_t _offsetAfter;
};

/* "Smart" block splitter */
/* computes block size (including last block) and number of blocks */
static inline void split_blocks(  int threadnum,
                                  size_t k_size,
                                  size_t j_size,
                                  int *pblocknum_k,
                                  int *pblocksize_k,
                                  int *pblocksize_last_k )
{
    /* Set initial number of blocks by */
    /* k = _DEF_BLOCKS_MUL_ * number_of_threads */
    /* _DEF_BLOCKS_MUL_ > 1 : number of blocks greater than threads */
    int _blocknum_k  = _DEF_BLOCKS_MUL_ * threadnum;
    int _blocksize_k;
    int _blocksize_last_k;

    /* If initial number of blocks greater than k-size, */
    /* set number of blocks = k-size */
    if(_blocknum_k > k_size)
    {
        _blocknum_k = k_size;
    }

    /* block size = k-size / number_of_blocks  */
    _blocksize_k = k_size / _blocknum_k;

    /* If block size is too big */
    if( (_blocksize_k * j_size) > _MAX_BLOCK_KJ_SIZE_ )
    {
        _blocksize_k = _MAX_BLOCK_KJ_SIZE_ / j_size;

        if(_blocksize_k < 1)
        {
            _blocksize_k = 1;
        }

        _blocknum_k  = k_size / _blocksize_k;
    }
    /* If block size is too small */
    else if( (_blocksize_k * j_size) < _MIN_BLOCK_KJ_SIZE_ )
    {
        _blocksize_k = _MIN_BLOCK_KJ_SIZE_ / j_size;
        _blocknum_k  = k_size / _blocksize_k;

        if(_blocknum_k < 1)
        {
            _blocknum_k = 1;
            _blocksize_k = k_size;
        }
    }

    /* Last block size is generally bigger */
    _blocksize_last_k = _blocksize_k + (k_size - _blocknum_k * _blocksize_k);

    *pblocknum_k       = _blocknum_k;
    *pblocksize_k      = _blocksize_k;
    *pblocksize_last_k = _blocksize_last_k;

    return;
}

template<typename algorithmFPType, Method method, CpuType cpu>
services::Status BatchNormalizationKernel<algorithmFPType, method, cpu>::compute(
    Tensor &gradientTensor,
    const Tensor &weightsTensor,
    const Tensor &stDevTensor,
    const Tensor &inputGradientTensor,
    const Tensor &dataTensor,
    const Tensor &meanTensor,
    Tensor &weightsDerTensor,
    Tensor &biasesDerTensor,
    const batch_normalization::Parameter &parameter )
{
    common_batchnorm_data_t<algorithmFPType, method, cpu> _cd(inputGradientTensor , parameter);

    Status s;
    DAAL_CHECK_STATUS(s, _cd.init(gradientTensor,
                                  weightsTensor,
                                  stDevTensor,
                                  inputGradientTensor,
                                  dataTensor,
                                  meanTensor,
                                  weightsDerTensor,
                                  biasesDerTensor));

    size_t ij  = _cd._offsetBefore * _cd._offsetAfter;
    size_t ikj = ij  * _cd._dimensionSize;

    int threadnum        = services::Environment::getInstance()->getNumberOfThreads();
    int do_threading     = ( ikj > _MIN_THREAD_SIZE_ ) && ( threadnum > 1 );

    int blocknum_k       = 1;
    int blocksize_k      = _cd._dimensionSize;
    int blocksize_last_k = blocksize_k;
    int blocknum_ik      = _cd._offsetBefore;

    /* Split target dimension by blocks for threaded branches only */
    if( do_threading )
    {
        split_blocks( threadnum,
                      _cd._dimensionSize,
                      _cd._offsetAfter,
                      &blocknum_k,
                      &blocksize_k,
                      &blocksize_last_k );

        /* Each 'i' from _offsetBefore is treated as separate block in threading */
        blocknum_ik = _cd._offsetBefore * blocknum_k;
    }

    PRAGMA_NOVECTOR
    for (size_t k = 0; k < _cd._dimensionSize; k++)
    {
        _cd._invStDev[k] = algorithmFPType(1.0) / _cd._stDev[k];
    }

    /* Calculate weight and bias derivatives */
    if( do_threading )
    {
        daal::threader_for( blocknum_k, blocknum_k, [ & ](int block_k)
        {
            size_t kbeg  = block_k * blocksize_k;
            size_t kend  = kbeg + ((block_k == blocknum_k - 1) ? blocksize_last_k : blocksize_k);

            for (size_t i = 0; i < _cd._offsetBefore; i++)
            {
                _cd.compute_weights_biases( i, kbeg, kend );
            }
        } );
    }
    else
    {
        for (size_t i = 0; i < _cd._offsetBefore; i++)
        {
            _cd.compute_weights_biases( i, 0, _cd._dimensionSize );
        }
    }

    /* Calculate output gradients */
    if(_cd._propagate_gradient)
    {
        algorithmFPType invM  = 1.0 / (algorithmFPType)ij;
        algorithmFPType invM1 = 1.0 / (algorithmFPType)(ij - 1);

        PRAGMA_IVDEP
        PRAGMA_VECTOR_ALWAYS
        for ( size_t k = 0; k < _cd._dimensionSize; k++ )
        {
            _cd._invStDevByWeights[k]    = _cd._weights[k] * _cd._invStDev[k];
            _cd._biasesDerMultiplier[k]  = invM * _cd._biasesDer[k];
            _cd._weightsDerMultiplier[k] = invM1 * _cd._invStDev[k] * _cd._weightsDer[k];
        }

        if( do_threading ) /* threaded branch */
        {
            daal::threader_for( blocknum_ik, blocknum_ik, [ & ]( int block_ik )
            {
                int block_i = block_ik / blocknum_k;
                int block_k = block_ik % blocknum_k;

                size_t kbeg  = block_k * blocksize_k;
                size_t kend  = kbeg + (( block_k == (blocknum_k - 1) ) ? blocksize_last_k : blocksize_k);

                _cd.compute_gradients( (size_t)block_i, kbeg, kend);
            } ); /* daal::threader_for */
        }
        else /* sequential branch */
        {
            for (size_t i = 0; i < _cd._offsetBefore; i++)
            {
                _cd.compute_gradients( i, 0, _cd._dimensionSize );
            }
        }
    }

    return s;
}

} // namespace internal
} // namespace backward
} // namespace batch_normalization
} // namespace layers
} // namespace neural_networks
} // namespace algorithms
} // namespace daal

#endif
