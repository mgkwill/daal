/* file: RatingsPartialResult.java */
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

/**
 * @ingroup implicit_als_prediction
 * @{
 */
package com.intel.daal.algorithms.implicit_als.prediction.ratings;

import com.intel.daal.algorithms.Precision;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__IMPLICIT_ALS__PREDICTION__RATINGS__RATINGSPARTIALRESULT"></a>
 * @brief Provides methods to access partial results obtained with the compute() method
 *        of the implicit ALS algorithm in the rating prediction stage
 */
public final class RatingsPartialResult extends com.intel.daal.algorithms.PartialResult {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    /**
     * Constructs a partial result of the implicit ALS ratings prediction algorithm and attaches it to the context
     * @param context Context to manage the memory in the native part of the partial result object
     */
    public RatingsPartialResult(DaalContext context) {
        super(context);
        this.cObject = cNewPartialResult();
    }

    /** @private */
    public RatingsPartialResult(DaalContext context, long cObject) {
        super(context, cObject);
    }

    /**
     * Returns a partial result of the implicit ALS ratings prediction algorithm
     * @param id    Identifier of the partial result
     * @return      Value that corresponds to the given identifier
     */
    public RatingsResult get(RatingsPartialResultId id) {
        if (id != RatingsPartialResultId.finalResult) {
            throw new IllegalArgumentException("RatingsPartialResultId unsupported");
        }

        return new RatingsResult(getContext(), cGetResult(getCObject(), id.getValue()));
    }

    /**
     * Sets a partial result of the implicit ALS ratings prediction algorithm
     * @param id    Identifier of the partial result
     * @param value New partial result object
     */
    public void set(RatingsPartialResultId id, RatingsResult value) {
        if (id != RatingsPartialResultId.finalResult) {
            throw new IllegalArgumentException("RatingsPartialResultId unsupported");
        }
        cSetResult(getCObject(), id.getValue(), value.getCObject());
    }

    private native long cNewPartialResult();

    private native long cGetResult(long presAddr, int id);
    private native void cSetResult(long presAddr, int id, long resAddr);
}
/** @} */
