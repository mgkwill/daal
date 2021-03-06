/* file: batch_result.cpp */
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

#include <jni.h>/* Header for class com_intel_daal_algorithms_cosdistance_Result */

#include "daal.h"
#include "cosdistance/JResult.h"
#include "cosdistance/JResultId.h"
#include "cosdistance/JMethod.h"

#include "common_helpers.h"

USING_COMMON_NAMESPACES();
using namespace daal::algorithms::cosine_distance;

#define DefaultMethodValue com_intel_daal_algorithms_cosdistance_Method_DefaultMethodValue
#define DefaultResultId com_intel_daal_algorithms_cosdistance_ResultId_DefaultResultId

JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_cosdistance_Result_cNewResult
(JNIEnv *env, jobject thisObj)
{
    return jniArgument<cosine_distance::Result>::newObj();
}

/*
 * Class:     com_intel_daal_algorithms_cosdistance_Result
 * Method:    cGetResultTable
 * Signature:(J)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_cosdistance_Result_cGetResultTable
(JNIEnv *env, jobject thisObj, jlong resAddr, jint id)
{
    return jniArgument<cosine_distance::Result>::get<cosine_distance::ResultId, NumericTable>(resAddr, id);
}

JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_cosdistance_Result_cSetResultTable
(JNIEnv *env, jobject thisObj, jlong resAddr, jint id, jlong ntAddr)
{
    jniArgument<cosine_distance::Result>::set<cosine_distance::ResultId, NumericTable>(resAddr, id, ntAddr);
}
