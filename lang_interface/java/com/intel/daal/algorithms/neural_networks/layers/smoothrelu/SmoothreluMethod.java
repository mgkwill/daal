/* file: SmoothreluMethod.java */
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
 * @ingroup smoothrelu_layers
 * @{
 */
package com.intel.daal.algorithms.neural_networks.layers.smoothrelu;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__SMOOTHRELU__SMOOTHRELUMETHOD"></a>
 * @brief Available methods for smoothrelu layer
 */
public final class SmoothreluMethod {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    private int _value;

    public SmoothreluMethod(int value) {
        _value = value;
    }

    /**
     * Returns the value of the method identifier
     * @return Value of the method identifier
     */
    public int getValue() {
        return _value;
    }

    private static final int DefaultMethodValue = 0;

    public static final SmoothreluMethod defaultDense = new SmoothreluMethod(DefaultMethodValue); /*!< Default method */
}
/** @} */
