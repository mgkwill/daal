/* file: logitboost_training_types.h */
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
//  Implementation of LogitBoost training algorithm interface.
//--
*/

#ifndef __LOGIT_BOOST_TRAINING_TYPES_H__
#define __LOGIT_BOOST_TRAINING_TYPES_H__

#include "algorithms/algorithm.h"
#include "algorithms/classifier/classifier_training_types.h"
#include "algorithms/boosting/logitboost_model.h"

namespace daal
{
namespace algorithms
{
/**
 * @defgroup logitboost Logitboost Classifier
 * \copydoc daal::algorithms::logitboost
 * @ingroup boosting
 */
namespace logitboost
{
/**
 * @defgroup logitboost_training Training
 * \copydoc daal::algorithms::logitboost::training
 * @ingroup logitboost
 * @{
 */
/**
 * \brief Contains classes for LogitBoost models training
 */
namespace training
{
/**
 * <a name="DAAL-ENUM-ALGORITHMS__LOGITBOOST__TRAINING__METHOD"></a>
 * Available methods for LogitBoost model training
 */
enum Method
{
    friedman = 0,       /*!< Default method proposed by Friedman et al. */
    defaultDense = 0    /*!< Default training method */
};

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__LOGITBOOST__TRAINING__RESULT"></a>
 * \brief Provides methods to access final results obtained with the compute() method
 *        of the LogitBoost training algorithm in the batch processing mode
 */
class DAAL_EXPORT Result : public classifier::training::Result
{
public:
    DECLARE_SERIALIZABLE_CAST(Result);

    virtual ~Result() {}

    /**
     * Returns the model trained with the LogitBoost algorithm
     * \param[in] id    Identifier of the result, \ref classifier::training::ResultId
     * \return          Model trained with the LogitBoost algorithm
     */
    daal::algorithms::logitboost::ModelPtr get(classifier::training::ResultId id) const;

    /**
     * Allocates memory to store final results of the LogitBoost training algorithm
     * \param[in] input         %Input of the LogitBoost training algorithm
     * \param[in] parameter     Parameters of the algorithm
     * \param[in] method        LogitBoost computation method
     */
    template <typename algorithmFPType>
    DAAL_EXPORT services::Status allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, const int method);

protected:
    /** \private */
    template<typename Archive, bool onDeserialize>
    services::Status serialImpl(Archive *arch)
    {
        return daal::algorithms::Result::serialImpl<Archive, onDeserialize>(arch);
    }
};
typedef services::SharedPtr<Result> ResultPtr;
} // namespace interface1
using interface1::Result;
using interface1::ResultPtr;

} // namespace daal::algorithms::logitboost::training
/** @} */
}
}
} // namespace daal
#endif // __LOGIT_BOOST_TRAINING_TYPES_H__
