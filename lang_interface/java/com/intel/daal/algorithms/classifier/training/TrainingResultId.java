/* file: TrainingResultId.java */
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

/**
 * @ingroup training
 * @{
 */
package com.intel.daal.algorithms.classifier.training;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__CLASSIFIER__TRAINING__TRAININGRESULTID"></a>
 * @brief Available identifiers of results of the classifier model training algorithm
 */
public final class TrainingResultId {
    private int _value;

    public TrainingResultId(int value) {
        _value = value;
    }

    public int getValue() {
        return _value;
    }

    private static final int Model = 0;

    /** Trained model */
    public static final TrainingResultId model = new TrainingResultId(Model);
}
/** @} */
