/* file: train_distributedstep1.cpp */
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
#include <jni.h>
/* Header for class com_intel_daal_algorithms_multinomial_naive_bayes_training_TrainingDistributedStep1Local */

#include "daal.h"
#include "multinomial_naive_bayes/training/JTrainingDistributedStep1Local.h"

#include "common_helpers.h"

USING_COMMON_NAMESPACES();
using namespace daal::algorithms::multinomial_naive_bayes::training;

/*
 * Class:     com_intel_daal_algorithms_multinomial_naive_bayes_training_TrainingDistributedStep1Local
 * Method:    cInit
 * Signature: (IIJ)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_multinomial_1naive_1bayes_training_TrainingDistributedStep1Local_cInit
(JNIEnv *env, jobject thisObj, jint prec, jint method, jlong nClasses)
{
    return jniDistributed<step1Local, multinomial_naive_bayes::training::Method, Distributed, defaultDense, fastCSR>::newObj(prec, method, nClasses);
}

/*
 * Class:     com_intel_daal_algorithms_multinomial_naive_bayes_training_TrainingDistributedStep1Local
 * Method:    cInitParameter
 * Signature: (JIII)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_multinomial_1naive_1bayes_training_TrainingDistributedStep1Local_cInitParameter
(JNIEnv *env, jobject thisObj, jlong algAddr, jint prec, jint method)
{
    return jniDistributed<step1Local, multinomial_naive_bayes::training::Method, Distributed, defaultDense, fastCSR>::
        getParameter(prec, method, algAddr);
}

/*
 * Class:     com_intel_daal_algorithms_multinomial_naive_bayes_training_TrainingDistributedStep1Local
 * Method:    cGetResult
 * Signature: (JII)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_multinomial_1naive_1bayes_training_TrainingDistributedStep1Local_cGetResult
(JNIEnv *env, jobject thisObj, jlong algAddr, jint prec, jint method)
{
    return jniDistributed<step1Local, multinomial_naive_bayes::training::Method, Distributed, defaultDense, fastCSR>::
        getResult(prec, method, algAddr);
}

JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_multinomial_1naive_1bayes_training_TrainingDistributedStep1Local_cSetResult
(JNIEnv *env, jobject thisObj, jlong algAddr, jint prec, jint method, jlong cObj)
{
    jniDistributed<step1Local, multinomial_naive_bayes::training::Method, Distributed, defaultDense, fastCSR>::
        setResult<multinomial_naive_bayes::training::Result>(prec, method, algAddr, cObj);
}

/*
 * Class:     com_intel_daal_algorithms_multinomial_naive_bayes_training_TrainingDistributedStep1Local
 * Method:    cGetPartialResult
 * Signature: (JII)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_multinomial_1naive_1bayes_training_TrainingDistributedStep1Local_cGetPartialResult
(JNIEnv *env, jobject thisObj, jlong algAddr, jint prec, jint method)
{
    return jniDistributed<step1Local, multinomial_naive_bayes::training::Method, Distributed, defaultDense, fastCSR>::
        getPartialResult(prec, method, algAddr);
}

JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_multinomial_1naive_1bayes_training_TrainingDistributedStep1Local_cSetPartialResult
(JNIEnv *env, jobject thisObj, jlong algAddr, jint prec, jint method, jlong cObj)
{
    jniDistributed<step1Local, multinomial_naive_bayes::training::Method, Distributed, defaultDense, fastCSR>::
        setPartialResult<multinomial_naive_bayes::training::PartialResult>(prec, method, algAddr, cObj);
}

/*
 * Class:     com_intel_daal_algorithms_multinomial_naive_bayes_training_TrainingDistributedStep1Local
 * Method:    cClone
 * Signature: (JII)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_multinomial_1naive_1bayes_training_TrainingDistributedStep1Local_cClone
(JNIEnv *env, jobject thisObj, jlong algAddr, jint prec, jint method)
{
    return jniDistributed<step1Local, multinomial_naive_bayes::training::Method, Distributed, defaultDense, fastCSR>::
        getClone(prec, method, algAddr);
}
