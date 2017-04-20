/* file: smoothrelu_layer_forward_types.h */
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
//  Implementation of the forward smooth relu layer types.
//--
*/

#ifndef __SMOOTHRELU_LAYER_FORWARD_TYPES_H__
#define __SMOOTHRELU_LAYER_FORWARD_TYPES_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "data_management/data/homogen_tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer_forward_types.h"
#include "algorithms/neural_networks/layers/smoothrelu/smoothrelu_layer_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace smoothrelu
{
/**
 * @defgroup smoothrelu_layers_forward Forward Smooth Rectifier Linear Unit (SmoothReLU) Layer
 * \copydoc daal::algorithms::neural_networks::layers::smoothrelu::forward
 * @ingroup smoothrelu_layers
 * @{
 */
/**
 * \brief Contains classes for the forward smooth relu layer
 */
namespace forward
{
/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__SMOOTHRELU__FORWARD__INPUT"></a>
 * \brief %Input objects for the forward smooth relu layer
 */
class DAAL_EXPORT Input : public layers::forward::Input
{
public:
    /** Default constructor */
    Input();

    /**
     * Returns an input object for the forward smooth relu layer
     */
    using layers::forward::Input::get;

    /**
     * Sets an input object for the forward smooth relu layer
     */
    using layers::forward::Input::set;

    /**
     * Returns dimensions of weights tensor
     * \return Dimensions of weights tensor
     */
    virtual const services::Collection<size_t> getWeightsSizes(const layers::Parameter *parameter) const DAAL_C11_OVERRIDE;

    /**
     * Returns dimensions of biases tensor
     * \return Dimensions of biases tensor
     */
    virtual const services::Collection<size_t> getBiasesSizes(const layers::Parameter *parameter) const DAAL_C11_OVERRIDE;

    virtual ~Input() {}
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__SMOOTHRELU__FORWARD__RESULT"></a>
 * \brief Provides methods to access the result obtained with the compute() method
 *        of the forward smooth relu layer
 */
class DAAL_EXPORT Result : public layers::forward::Result
{
public:
    DECLARE_SERIALIZABLE();
    /** Default Constructor */
    Result();
    virtual ~Result() {};

    /**
     * Returns the result of the forward smooth relu layer
     */
    using layers::forward::Result::get;

    /**
     * Sets the result of the forward smooth relu layer
     */
    using layers::forward::Result::set;

    /**
     * Returns the result of the forward smooth relu layer
     * \param[in] id    Identifier of the result
     * \return          Result that corresponds to the given identifier
     */
    services::SharedPtr<data_management::Tensor> get(LayerDataId id) const;

    /**
     * Sets the result of the forward smooth relu layer
     * \param[in] id      Identifier of the result
     * \param[in] value   Result
     */
    void set(LayerDataId id, const services::SharedPtr<data_management::Tensor> &value);

    /**
     * Checks the result of the forward smooth relu layer
     * \param[in] input   %Input object for the layer
     * \param[in] par     %Parameter of the layer
     * \param[in] method  Computation method
     */
    void check(const daal::algorithms::Input *input, const daal::algorithms::Parameter *par, int method) const DAAL_C11_OVERRIDE;

    /**
     * Allocates memory to store the result of the forward smooth relu layer
     * \param[in] input Pointer to an object containing the input data
     * \param[in] parameter %Parameter of the forward smooth relu layer
     * \param[in] method Computation method for the layer
     */
    template <typename algorithmFPType>
    DAAL_EXPORT void allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, const int method);

    /**
     * Sets the result that is used in backward smooth relu layer
     * \param[in] input     Pointer to an object containing the input data
     */
    virtual void setResultForBackward(const daal::algorithms::Input *input) DAAL_C11_OVERRIDE;

    /**
     * Returns dimensions of value tensor
     * \return Dimensions of value tensor
     */
    virtual const services::Collection<size_t> getValueSize(const services::Collection<size_t> &inputSize,
                                                            const daal::algorithms::Parameter *par, const int method) const DAAL_C11_OVERRIDE;

protected:
    /** \private */
    template<typename Archive, bool onDeserialize>
    void serialImpl(Archive *arch)
    {
        daal::algorithms::Result::serialImpl<Archive, onDeserialize>(arch);
    }

    void serializeImpl(data_management::InputDataArchive  *arch) DAAL_C11_OVERRIDE
    {serialImpl<data_management::InputDataArchive, false>(arch);}

    void deserializeImpl(data_management::OutputDataArchive *arch) DAAL_C11_OVERRIDE
    {serialImpl<data_management::OutputDataArchive, true>(arch);}
};
} // namespace interface1
using interface1::Input;
using interface1::Result;
} // namespace forward
/** @} */
} // namespace smoothrelu
} // namespace layers
} // namespace neural_networks
} // namespace algorithm
} // namespace daal
#endif
