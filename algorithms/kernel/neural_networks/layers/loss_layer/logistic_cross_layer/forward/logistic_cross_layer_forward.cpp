/* file: logistic_cross_layer_forward.cpp */
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
//  Implementation of logistic cross calculation algorithm and types methods.
//--
*/

#include "logistic_cross_layer_types.h"
#include "logistic_cross_layer_forward_types.h"
#include "serialization_utils.h"

using namespace daal::data_management;
using namespace daal::services;

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace loss
{
namespace logistic_cross
{
namespace forward
{
namespace interface1
{
__DAAL_REGISTER_SERIALIZATION_CLASS(Result, SERIALIZATION_NEURAL_NETWORKS_LAYERS_LOSS_LOGISTIC_CROSS_FORWARD_RESULT_ID);
/** Default constructor */
Input::Input() : loss::forward::Input() {};

/**
 * Returns dimensions of weights tensor
 * \return Dimensions of weights tensor
 */
const Collection<size_t> Input::getWeightsSizes(const layers::Parameter *parameter) const
{
    return Collection<size_t>();
}

/**
 * Returns dimensions of biases tensor
 * \return Dimensions of biases tensor
 */
const Collection<size_t> Input::getBiasesSizes(const layers::Parameter *parameter) const
{
    return Collection<size_t>();
}

/**
 * Checks an input object for the layer algorithm
 * \param[in] par     %Parameter of algorithm
 * \param[in] method  Computation method of the algorithm
 */
void Input::check(const daal::algorithms::Parameter *par, int method) const
{
    if(Argument::size() != 5) { this->_errors->add(ErrorIncorrectNumberOfInputNumericTables); return; }

    TensorPtr dataTensor = get(layers::forward::data);
    TensorPtr groundTruthTensor = get(layers::loss::forward::groundTruth);

    if (!checkTensor(dataTensor.get(), this->_errors.get(), dataStr())) { return; }
    const Collection<size_t> &inputDims = dataTensor->getDimensions();

    if (!checkTensor(groundTruthTensor.get(), this->_errors.get(), groundTruthStr())) { return; }
    const Collection<size_t> &gtDims = groundTruthTensor->getDimensions();

    DAAL_CHECK_EX(dataTensor->getSize() == groundTruthTensor->getSize(), ErrorIncorrectSizeOfDimensionInTensor, ParameterName, groundTruthStr());
    DAAL_CHECK_EX(gtDims.size() == 1 || gtDims.size() == inputDims.size() , ErrorIncorrectNumberOfDimensionsInTensor, ParameterName, dataStr());
    DAAL_CHECK_EX(gtDims[0] == inputDims[0] , ErrorIncorrectSizeOfDimensionInTensor, ParameterName, dataStr());
}

    /** Default constructor */
Result::Result() : loss::forward::Result() {};

/**
 * Returns the result of the forward logistic cross-entropy layer
 * \param[in] id    Identifier of the result
 * \return          Result that corresponds to the given identifier
 */
SharedPtr<Tensor> Result::get(LayerDataId id) const
{
    LayerDataPtr layerData = layers::LayerData::cast<SerializationIface>(Argument::get(layers::forward::resultForBackward));
    return Tensor::cast<SerializationIface>((*layerData)[id]);
}

/**
 * Sets the result of the forward logistic cross-entropy layer
 * \param[in] id      Identifier of the result
 * \param[in] value   Result
 */
void Result::set(LayerDataId id, const SharedPtr<Tensor> &value)
{
    LayerDataPtr layerData = layers::LayerData::cast<SerializationIface>(Argument::get(layers::forward::resultForBackward));
    (*layerData)[id] = value;
}

/**
 * Checks the result of the forward logistic cross-entropy layer
 * \param[in] input   %Input object for the layer
 * \param[in] par     %Parameter of the layer
 * \param[in] method  Computation method
 */
void Result::check(const daal::algorithms::Input *input, const daal::algorithms::Parameter *par, int method) const
{
    const Input *in = static_cast<const Input * >(input);
    layers::forward::Result::check(input, par, method);
    if(this->_errors->size() != 0) { return; }

    Collection<size_t> valueDim(1);
    valueDim[0] = 1;
    if (!checkTensor(get(layers::forward::value).get(), this->_errors.get(), valueStr(), &valueDim)) { return; }
    if (!checkTensor(get(auxData).get(), this->_errors.get(), auxDataStr(), &(in->get(layers::forward::data)->getDimensions()))) { return; }
    const layers::Parameter *parameter = static_cast<const layers::Parameter * >(par);
    if(!parameter->predictionStage)
    {
        if (!checkTensor(get(auxGroundTruth).get(), this->_errors.get(), auxGroundTruthStr(), &(in->get(loss::forward::groundTruth)->getDimensions()))) { return; }
    }
}

/**
 * Returns dimensions of value tensor
 * \return Dimensions of value tensor
 */
const Collection<size_t> Result::getValueSize(const Collection<size_t> &inputSize,
        const daal::algorithms::Parameter *par, const int method) const
{
    return inputSize;
}

/**
 * Sets the result that is used in backward abs layer
 * \param[in] input     Pointer to an object containing the input data
 */
void Result::setResultForBackward(const daal::algorithms::Input *input)
{
    const loss::logistic_cross::forward::Input *in = static_cast<const loss::logistic_cross::forward::Input * >(input);
    set(auxData, in->get(layers::forward::data));
    set(auxGroundTruth, in->get(loss::forward::groundTruth));
}
}// namespace interface1
}// namespace forward
}// namespace logistic_cross
}// namespace loss
}// namespace layers
}// namespace neural_networks
}// namespace algorithms
}// namespace daal
