/* file: pooling3d_layer_backward_types.h */
/*******************************************************************************
* Copyright 2014-2017 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Implementation of backward 3D pooling layer.
//--
*/

#ifndef __POOLING3D_LAYER_BACKWARD_TYPES_H__
#define __POOLING3D_LAYER_BACKWARD_TYPES_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "data_management/data/homogen_tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer_backward_types.h"
#include "algorithms/neural_networks/layers/pooling3d/pooling3d_layer_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace pooling3d
{
/**
 * @defgroup pooling3d_backward Backward Three-dimensional Pooling Layer
 * \copydoc daal::algorithms::neural_networks::layers::pooling3d::backward
 * @ingroup pooling3d
 * @{
 */
/**
 * \brief Contains classes for backward three-dimensional (3D) pooling layer
 */
namespace backward
{

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__POOLING3D__BACKWARD__INPUT"></a>
 * \brief %Input objects for the backward 3D pooling layer
 */
class DAAL_EXPORT Input : public layers::backward::Input
{
public:
    /** Default constructor */
    Input();

    virtual ~Input() {}

    /**
     * Return the collection with gradient size
     * \return The collection with gradient size
     */
    virtual services::Collection<size_t> getGradientSize() const;

protected:
    virtual data_management::NumericTablePtr getAuxInputDimensions() const = 0;

    virtual services::Collection<size_t> getInputGradientSize(const pooling3d::Parameter *parameter) const;

    size_t computeInputDimension(size_t maskDim, size_t kernelSize, size_t padding, size_t stride) const;
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__POOLING3D__BACKWARD__RESULT"></a>
 * \brief Provides methods to access the result obtained with the compute() method
 *        of the backward 3D pooling layer
 */
class DAAL_EXPORT Result : public layers::backward::Result
{
public:
    /** Default constructor */
    Result();
    virtual ~Result() {}

    /**
     * Allocates memory to store the result of the backward 3D pooling layer
     * \param[in] input Pointer to an object containing the input data
     * \param[in] method Computation method for the layer
     * \param[in] parameter %Parameter of the backward 3D pooling layer
     */
    template <typename algorithmFPType>
    DAAL_EXPORT void allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, const int method);

    /**
     * Checks the result of the backward 3D pooling layer
     * \param[in] input %Input object for the layer
     * \param[in] parameter %Parameter of the layer
     * \param[in] method Computation method
     */
    void check(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, int method) const DAAL_C11_OVERRIDE;
};

} // namespace interface1
using interface1::Input;
using interface1::Result;
} // namespace backward
/** @} */
} // namespace pooling3d
} // namespace layers
} // namespace neural_networks
} // namespace algorithm
} // namespace daal

#endif
