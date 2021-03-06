/* file: regression_training_types.h */
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
//  Implementation of the regression algorithm interface
//--
*/

#ifndef __REGRESSION_TRAINING_TYPES_H__
#define __REGRESSION_TRAINING_TYPES_H__

#include "data_management/data/numeric_table.h"
#include "algorithms/algorithm_types.h"
#include "algorithms/regression/regression_model.h"

namespace daal
{
namespace algorithms
{
namespace regression
{
/**
 * @defgroup base_regression_training Training
 * \copydoc daal::algorithms::regression::training
 * @ingroup base_regression
 * @{
 */
/**
 * \brief Contains a class for regression model-based training
 */
namespace training
{
/**
 * <a name="DAAL-ENUM-ALGORITHMS__REGRESSION__TRAINING__INPUTID"></a>
 * \brief Available identifiers of input objects for regression model-based training
 */
enum InputId
{
    data,               /*!< %Input data table */
    dependentVariables,   /*!< Values of the dependent variable for the input data */
    lastInputId = dependentVariables
};

/**
 * <a name="DAAL-ENUM-ALGORITHMS__REGRESSION__TRAINING__RESULTID"></a>
 * \brief Available identifiers of the result of regression model-based training
 */
enum ResultId
{
    model,                /*!< Regression model */
    lastResultId = model
};

/**
 * \brief Contains version 1.0 of the Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__REGRESSION__TRAINING__INPUT"></a>
 * \brief %Input objects for the regression model-based training
 */
class DAAL_EXPORT Input : public daal::algorithms::Input
{
public:
    /**
     * Constructs input objects for the regression training algorithm
     * \param[in] nElements Number of input objects
     */
    Input(size_t nElements);
    Input(const Input& other);

    virtual ~Input() {}

    /**
     * Returns an input object for the regression model-based training
     * \param[in] id    Identifier of the input object
     * \return          %Input object that corresponds to the given identifier
     */
    data_management::NumericTablePtr get(InputId id) const;

    /**
     * Sets an input object for linear regression model-based training
     * \param[in] id      Identifier of the input object
     * \param[in] value   Input numeric table
     */
    void set(InputId id, const data_management::NumericTablePtr &value);

    /**
     * Checks an input object for the linear regression algorithm
     * \param[in] par     Algorithm parameter
     * \param[in] method  Computation method
     *
     * \return Status of computations
     */
    services::Status check(const daal::algorithms::Parameter *par, int method) const DAAL_C11_OVERRIDE;
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__REGRESSION__TRAINING__PARTIALRESULT"></a>
 * \brief Provides methods to access a partial result obtained with the compute() method of
 *        the regression model-based training in the online processing mode
 */
class DAAL_EXPORT PartialResult : public daal::algorithms::PartialResult
{
    DECLARE_SERIALIZABLE_IMPL();
public:
    DAAL_CAST_OPERATOR(PartialResult);

    /**
     * Constructs the partial results of the regression training algorithm
     * \param[in] nElements Number of partial results
     */
    PartialResult(size_t nElements = 0);
protected:
    /** \private */
    template<typename Archive, bool onDeserialize>
    services::Status serialImpl(Archive *arch)
    {
        return daal::algorithms::PartialResult::serialImpl<Archive, onDeserialize>(arch);
    }
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__REGRESSION__TRAINING__RESULT"></a>
 * \brief Provides methods to access the result obtained with the compute() method
 *        of the regression model-based training
 */
class DAAL_EXPORT Result : public daal::algorithms::Result
{
    DECLARE_SERIALIZABLE_IMPL();
public:
    DAAL_CAST_OPERATOR(Result);

    /**
     * Constructs the results of the regression training algorithm
     * \param[in] nElements Number of results
     */
    Result(size_t nElements = 0);

    /**
     * Returns the result of the regression model-based training
     * \param[in] id    Identifier of the result
     * \return          Result that corresponds to the given identifier
     */
    regression::ModelPtr get(ResultId id) const;

    /**
     * Sets the result of the regression model-based training
     * \param[in] id      Identifier of the result
     * \param[in] value   Result
     */
    void set(ResultId id, const regression::ModelPtr &value);

    /**
     * Checks the result of the regression model-based training
     * \param[in] input   %Input object for the algorithm
     * \param[in] par     %Parameter of the algorithm
     * \param[in] method  Computation method
     *
     * \return Status of computations
     */
    services::Status check(const daal::algorithms::Input *input, const daal::algorithms::Parameter *par, int method) const DAAL_C11_OVERRIDE;

protected:
    /** \private */
    template<typename Archive, bool onDeserialize>
    services::Status serialImpl(Archive *arch)
    {
        return daal::algorithms::Result::serialImpl<Archive, onDeserialize>(arch);
    }
};
typedef services::SharedPtr<Result> ResultPtr;
typedef services::SharedPtr<const Result> ResultConstPtr;
typedef services::SharedPtr<PartialResult> PartialResultPtr;
typedef services::SharedPtr<const PartialResult> PartialResultConstPtr;
}
using interface1::Input;
using interface1::Result;
using interface1::ResultPtr;
using interface1::ResultConstPtr;
using interface1::PartialResult;
using interface1::PartialResultPtr;
using interface1::PartialResultConstPtr;
}
/** @} */
}
}
}
#endif
