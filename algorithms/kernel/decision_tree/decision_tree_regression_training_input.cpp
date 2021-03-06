/* file: decision_tree_regression_training_input.cpp */
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
//  Implementation of Decision tree algorithm classes.
//--
*/

#include "algorithms/decision_tree/decision_tree_regression_training_types.h"
#include "serialization_utils.h"
#include "daal_strings.h"

namespace daal
{
namespace algorithms
{
namespace decision_tree
{
namespace regression
{
namespace training
{
namespace interface1
{

using namespace daal::data_management;
using namespace daal::services;

Input::Input() : algorithms::regression::training::Input(lastInputId + 1) {}
Input::Input(const Input &other) : algorithms::regression::training::Input(other) {}

NumericTablePtr Input::get(decision_tree::regression::training::InputId id) const
{
    return algorithms::regression::training::Input::get(algorithms::regression::training::InputId(id));
}

void Input::set(decision_tree::regression::training::InputId id, const data_management::NumericTablePtr & value)
{
    algorithms::regression::training::Input::set(algorithms::regression::training::InputId(id), value);
}

size_t Input::getNumberOfFeatures() const
{
    const NumericTablePtr dataTable = get(data);
    return dataTable ? dataTable->getNumberOfColumns() : 0;
}

size_t Input::getNumberOfDependentVariables() const
{
    const NumericTablePtr dependentVariablesTable = get(dependentVariables);
    return dependentVariablesTable ? dependentVariablesTable->getNumberOfColumns() : 0;
}

services::Status Input::check(const daal::algorithms::Parameter * parameter, int method) const
{
    services::Status s;
    DAAL_CHECK_STATUS(s, algorithms::regression::training::Input::check(parameter, method));
    return checkImpl(parameter);
}

services::Status Input::checkImpl(const daal::algorithms::Parameter * parameter) const
{
    DAAL_CHECK_EX(getNumberOfDependentVariables() == 1, ErrorIncorrectNumberOfColumns, ArgumentName, dependentVariableStr());

    services::Status s;
    const decision_tree::regression::Parameter * const par = static_cast<const decision_tree::regression::Parameter *>(parameter);
    if (par->pruning == decision_tree::reducedErrorPruning)
    {
        const NumericTablePtr dataForPruningTable = get(dataForPruning);
        DAAL_CHECK_STATUS(s, checkNumericTable(dataForPruningTable.get(), dataForPruningStr(), 0, 0, this->getNumberOfFeatures()));
        const int unexpectedLabelsLayouts = (int)NumericTableIface::upperPackedSymmetricMatrix
                                            | (int)NumericTableIface::lowerPackedSymmetricMatrix
                                            | (int)NumericTableIface::upperPackedTriangularMatrix
                                            | (int)NumericTableIface::lowerPackedTriangularMatrix;
        DAAL_CHECK_STATUS(s, checkNumericTable(get(dependentVariablesForPruning).get(), dependentVariablesForPruningStr(), unexpectedLabelsLayouts,
                          0, 1, dataForPruningTable->getNumberOfRows()));
    }
    else
    {
        DAAL_CHECK_EX(get(dataForPruning).get() == nullptr, ErrorIncorrectOptionalInput, ArgumentName, dataForPruningStr());
        DAAL_CHECK_EX(get(dependentVariablesForPruning).get() == nullptr, ErrorIncorrectOptionalInput, ArgumentName,
                      dependentVariablesForPruningStr());
    }

    return s;
}

} // namespace interface1

using interface1::Input;

} // namespace training
} // namespace regression
} // namespace decision_tree
} // namespace algorithms
} // namespace daal
