/* file: parameter.cpp */
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

/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>/* Header for class com_intel_daal_algorithms_brownboost_Batch */

#include "daal.h"
#include "brownboost/JParameter.h"

using namespace daal;
using namespace daal::algorithms;

JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_brownboost_Parameter_cSetAccuracyThreshold
(JNIEnv *env, jobject thisObj, jlong parAddr, jdouble acc)
{
    (*(brownboost::Parameter *)parAddr).accuracyThreshold = acc;
}

JNIEXPORT jdouble JNICALL Java_com_intel_daal_algorithms_brownboost_Parameter_cGetAccuracyThreshold
(JNIEnv *env, jobject thisObj, jlong parAddr)
{
    return(jdouble)(*(brownboost::Parameter *)parAddr).accuracyThreshold;
}

JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_brownboost_Parameter_cSetnewtonRaphsonAccuracyThreshold
(JNIEnv *env, jobject thisObj, jlong parAddr, jdouble acc)
{
    (*(brownboost::Parameter *)parAddr).newtonRaphsonAccuracyThreshold = acc;
}

JNIEXPORT jdouble JNICALL Java_com_intel_daal_algorithms_brownboost_Parameter_cGetnewtonRaphsonAccuracyThreshold
(JNIEnv *env, jobject thisObj, jlong parAddr)
{
    return(jdouble)(*(brownboost::Parameter *)parAddr).newtonRaphsonAccuracyThreshold;
}

JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_brownboost_Parameter_cSetThr
(JNIEnv *env, jobject thisObj, jlong parAddr, jdouble acc)
{
    (*(brownboost::Parameter *)parAddr).degenerateCasesThreshold = acc;
}

JNIEXPORT jdouble JNICALL Java_com_intel_daal_algorithms_brownboost_Parameter_cGetThr
(JNIEnv *env, jobject thisObj, jlong parAddr)
{
    return(jdouble)(*(brownboost::Parameter *)parAddr).degenerateCasesThreshold;
}

JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_brownboost_Parameter_cSetMaxIterations
(JNIEnv *env, jobject thisObj, jlong parAddr, jlong nIter)
{
    (*(brownboost::Parameter *)parAddr).maxIterations = nIter;
}

JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_brownboost_Parameter_cGetMaxIterations
(JNIEnv *env, jobject thisObj, jlong parAddr)
{
    return(jlong)(*(brownboost::Parameter *)parAddr).maxIterations;
}

JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_brownboost_Parameter_cSetnewtonRaphsonMaxIterations
(JNIEnv *env, jobject thisObj, jlong parAddr, jlong nIter)
{
    (*(brownboost::Parameter *)parAddr).newtonRaphsonMaxIterations = nIter;
}

JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_brownboost_Parameter_cGetnewtonRaphsonMaxIterations
(JNIEnv *env, jobject thisObj, jlong parAddr)
{
    return(jlong)(*(brownboost::Parameter *)parAddr).newtonRaphsonMaxIterations;
}
