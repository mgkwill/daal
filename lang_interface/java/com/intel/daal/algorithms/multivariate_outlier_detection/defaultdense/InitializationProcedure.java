/* file: InitializationProcedure.java */
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
 * @ingroup multivariate_outlier_detection
 * @{
 */
package com.intel.daal.algorithms.multivariate_outlier_detection.defaultdense;

import java.nio.DoubleBuffer;
import com.intel.daal.data_management.data.NumericTable;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__MULTIVARIATE_OUTLIER_DETECTION__DEFAULTDENSE__INITIALIZATIONPROCEDURE"></a>
 * @brief Class that specifies the default method for setting initial parameters of multivariate outlier detection algorithm
 */
public class InitializationProcedure extends InitializationProcedureIface {

    /**
     * Constructs the default initialization procedure
     * @param context   Context to manage the algorithm
     */
    public InitializationProcedure(DaalContext context) {
        super(context);
        this.cInitIface = cNewJavaInitializationProcedure();
        this.cObject = this.cInitIface;
    }

    /**
     * Sets initial parameters of multivariate outlier detection algorithm
     * @param data        %Input data table of size n x p
     * @param location    Vector of mean estimates of size 1 x p
     * @param scatter     Measure of spread, the variance-covariance matrix of size p x p
     * @param threshold   Limit that defines the outlier region, the array of size 1 x 1 containing a non-negative number
     */
    @Override
    public void initialize(NumericTable data, NumericTable location, NumericTable scatter, NumericTable threshold) {
        long nDataRows    = data.getNumberOfRows();
        long nDataColumns = data.getNumberOfColumns();
        int iNDataColumns = (int) nDataColumns;
        int iNDataRows    = (int) nDataRows;

        DoubleBuffer locationBuffer  = DoubleBuffer.allocate(iNDataColumns);
        DoubleBuffer scatterBuffer   = DoubleBuffer.allocate(iNDataColumns * iNDataColumns);
        DoubleBuffer thresholdBuffer = DoubleBuffer.allocate(1);

        locationBuffer  = location.getBlockOfRows(0, 1, locationBuffer);
        scatterBuffer   = scatter.getBlockOfRows(0, nDataColumns, scatterBuffer);
        thresholdBuffer = threshold.getBlockOfRows(0, 1, thresholdBuffer);

        thresholdBuffer.put(0, 3.0);
        for (int i = 0; i < iNDataColumns; i++) {
            locationBuffer.put(i, 0.0);

            for (int j = 0; j < iNDataColumns; j++) {
                if(i == j) {
                    scatterBuffer.put(i * iNDataColumns + j, 1.0);
                } else {
                    scatterBuffer.put(i * iNDataColumns + j, 0.0);
                }
            }
        }

        location.releaseBlockOfRows(0, 1, locationBuffer);
        scatter.releaseBlockOfRows(0, nDataColumns, scatterBuffer);
        threshold.releaseBlockOfRows(0, 1, thresholdBuffer);
    }

    /**
    * Releases memory allocated for the native iface object
    */
    @Override
    public void dispose() {
        if(this.cInitIface != 0) {
            cInitIfaceDispose(this.cInitIface);
            this.cInitIface = 0;
        }
    }

    protected long cInitIface;

    private native long cNewJavaInitializationProcedure();
    private native void cInitIfaceDispose(long cInitIface);
}
/** @} */
