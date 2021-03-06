/* file: SetNumberOfThreads.java */
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
 //     Java example of setting the maximum number of threads
 ////////////////////////////////////////////////////////////////////////////////
 */

/**
 * <a name="DAAL-EXAMPLE-JAVA-SETNUMBEROFTHREADS">
 * @example SetNumberOfThreads.java
 */

package com.intel.daal.examples.set_number_of_threads;

import com.intel.daal.algorithms.kmeans.Batch;
import com.intel.daal.algorithms.kmeans.InputId;
import com.intel.daal.algorithms.kmeans.Method;
import com.intel.daal.algorithms.kmeans.init.InitBatch;
import com.intel.daal.algorithms.kmeans.init.InitInputId;
import com.intel.daal.algorithms.kmeans.init.InitMethod;
import com.intel.daal.algorithms.kmeans.init.InitResult;
import com.intel.daal.algorithms.kmeans.init.InitResultId;
import com.intel.daal.data_management.data.NumericTable;
import com.intel.daal.data_management.data_source.DataSource;
import com.intel.daal.data_management.data_source.FileDataSource;
import com.intel.daal.services.DaalContext;
import com.intel.daal.services.Environment;

class SetNumberOfThreads {
    /* Input data set parameters */
    private static final String dataset       = "../data/batch/kmeans_dense.csv";
    private static final int    nClusters     = 20;

    /* K-Means algorithm parameters */
    private static final int maxIterations = 5;
    private static final int nThreads = 2;
    private static  int nThreadsInit;
    private static  int nThreadsNew;

    private static DaalContext context = new DaalContext();

    public static void main(String[] args) throws java.io.FileNotFoundException, java.io.IOException {

        /* Get the number of threads that is used by the library by default */
        nThreadsInit = Environment.getNumberOfThreads();

        /* Set the maximum number of threads to be used by the library */
        Environment.setNumberOfThreads(nThreads);

        /* Get the number of threads that is used by the library after changing */
        nThreadsNew = Environment.getNumberOfThreads();

        /* Retrieve the input data */
        FileDataSource dataSource = new FileDataSource(context, dataset,
                                                       DataSource.DictionaryCreationFlag.DoDictionaryFromContext,
                                                       DataSource.NumericTableAllocationFlag.DoAllocateNumericTable);
        dataSource.loadDataBlock();
        NumericTable input = dataSource.getNumericTable();

        /* Calculate initial clusters for K-Means clustering */
        InitBatch init = new InitBatch(context, Float.class, InitMethod.randomDense, nClusters);
        init.input.set(InitInputId.data, input);
        InitResult initResult = init.compute();
        NumericTable inputCentroids = initResult.get(InitResultId.centroids);

        /* Create an algorithm for K-Means clustering */
        Batch algorithm = new Batch(context, Float.class, Method.lloydDense, nClusters, maxIterations);

        /* Set an input object for the algorithm */
        algorithm.input.set(InputId.data, input);
        algorithm.input.set(InputId.inputCentroids, inputCentroids);

        /* Clusterize the data */
        algorithm.compute();

        System.out.println("Initial number of threads:        " + nThreadsInit);
        System.out.println("Number of threads to set:         " + nThreads);
        System.out.println("Number of threads after setting:  " + nThreadsNew);

        context.dispose();
    }
}
