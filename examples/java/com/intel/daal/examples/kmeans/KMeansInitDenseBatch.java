/* file: KMeansInitDenseBatch.java */
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
 //  Content:
 //     Java example of dense K-Means clustering with different initialization
 //      methods in the batch processing mode
 ////////////////////////////////////////////////////////////////////////////////
 */

/**
 * <a name="DAAL-EXAMPLE-JAVA-KMEANSINITDENSEBATCH">
 * @example KMeansInitDenseBatch.java
 */

package com.intel.daal.examples.kmeans;

import com.intel.daal.algorithms.kmeans.*;
import com.intel.daal.algorithms.kmeans.init.*;
import com.intel.daal.data_management.data.NumericTable;
import com.intel.daal.data_management.data_source.DataSource;
import com.intel.daal.data_management.data_source.FileDataSource;
import com.intel.daal.examples.utils.Service;
import com.intel.daal.services.DaalContext;
import java.nio.DoubleBuffer;
import java.nio.IntBuffer;

class KMeansInitDenseBatch {
    /* Input data set parameters */
    private static final String dataset       = "../data/batch/kmeans_init_dense.csv";
    private static final int    nClusters     = 20;

    /* K-Means algorithm parameters */
    private static final int maxIterations = 1000;
    private static final double accuracyThreshold = 0.01;

    private static DaalContext context = new DaalContext();

    private static double getSingleDouble(NumericTable nt) {
        DoubleBuffer result = DoubleBuffer.allocate(1);
        result = nt.getBlockOfRows(0, 1, result);
        return result.get(0);
    }

    private static int getSingleInt(NumericTable nt) {
        IntBuffer result = IntBuffer.allocate(1);
        result = nt.getBlockOfRows(0, 1, result);
        return result.get(0);
    }

    private static void runKmeans(NumericTable input, InitMethod method, final String methodName, double oversamplingFactor) {
        /* Calculate initial clusters for K-Means clustering */
        InitBatch init = new InitBatch(context, Float.class, method, nClusters);
        init.input.set(InitInputId.data, input);
        if (oversamplingFactor > 0)
            init.parameter.setOversamplingFactor(oversamplingFactor);
        System.out.print("K-means init parameters: method = " + methodName);
        if (method == InitMethod.parallelPlusDense)
            System.out.print(", oversamplingFactor = " + init.parameter.getOversamplingFactor() +
                ", nRounds = " + init.parameter.getNRounds());
        System.out.println("");

        InitResult initResult = init.compute();
        NumericTable inputCentroids = initResult.get(InitResultId.centroids);

        /* Create an algorithm for K-Means clustering */
        Batch algorithm = new Batch(context, Float.class, Method.lloydDense, nClusters, maxIterations);

        /* Set an input object for the algorithm */
        algorithm.input.set(InputId.data, input);
        algorithm.input.set(InputId.inputCentroids, inputCentroids);
        algorithm.parameter.setAccuracyThreshold(accuracyThreshold);

        /* Clusterize the data */
        Result result = algorithm.compute();

        final double goalFunc = getSingleDouble(result.get(ResultId.objectiveFunction));
        final int nIterations = getSingleInt(result.get(ResultId.nIterations));

        /* Print the results */
        System.out.println("K-means algorithm results: Objective function = " + goalFunc*1e-6 +
            "*1e+6, number of iterations = " + nIterations);
    }

    public static void main(String[] args) throws java.io.FileNotFoundException, java.io.IOException {
        /* Retrieve the input data */
        FileDataSource dataSource = new FileDataSource(context, dataset,
                DataSource.DictionaryCreationFlag.DoDictionaryFromContext,
                DataSource.NumericTableAllocationFlag.DoAllocateNumericTable);
        dataSource.loadDataBlock();
        NumericTable input = dataSource.getNumericTable();

        runKmeans(input, InitMethod.deterministicDense, "deterministicDense", 0.); /* oversamplingFactor doesn't mater */
        runKmeans(input, InitMethod.randomDense, "randomDense", 0.); /* oversamplingFactor doesn't mater */
        runKmeans(input, InitMethod.plusPlusDense, "plusPlusDense", 0.); /* oversamplingFactor doesn't mater */
        runKmeans(input, InitMethod.parallelPlusDense, "plusPlusDense", 0.5);
        runKmeans(input, InitMethod.parallelPlusDense, "plusPlusDense", 2.0);
        context.dispose();
    }
}
