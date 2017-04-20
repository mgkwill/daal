/* file: RidgeRegNormEqDistr.java */
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

/*
 //  Content:
 //     Java example of ridge regression in the distributed processing mode.
 //
 //     The program trains the ridge regression model on a training
 //     data set with the normal equations method and computes regression for
 //     the test data.
 ////////////////////////////////////////////////////////////////////////////////
 */

/**
 * <a name="DAAL-EXAMPLE-JAVA-RIDGEREGRESSIONNORMEQDISTRIBUTED">
 * @example RidgeRegNormEqDistr.java
 */

package com.intel.daal.examples.ridge_regression;

import com.intel.daal.algorithms.ridge_regression.Model;
import com.intel.daal.algorithms.ridge_regression.prediction.*;
import com.intel.daal.algorithms.ridge_regression.training.*;
import com.intel.daal.data_management.data.NumericTable;
import com.intel.daal.data_management.data.HomogenNumericTable;
import com.intel.daal.data_management.data.MergedNumericTable;
import com.intel.daal.data_management.data_source.DataSource;
import com.intel.daal.data_management.data_source.FileDataSource;
import com.intel.daal.examples.utils.Service;
import com.intel.daal.services.DaalContext;

class RidgeRegNormEqDistr {
    /* Input data set parameters */
    private static final String[] trainDatasetFileNames = {
            "../data/distributed/linear_regression_train_1.csv", "../data/distributed/linear_regression_train_2.csv",
            "../data/distributed/linear_regression_train_3.csv", "../data/distributed/linear_regression_train_4.csv" };

    private static final String testDatasetFileName = "../data/distributed/linear_regression_test.csv";

    private static final int nFeatures            = 10;  /* Number of features in training and testing data sets */
    private static final int nDependentVariables  = 2;   /* Number of dependent variables that correspond to each observation */
    private static final int nNodes               = 4;

    static Model        model;
    static NumericTable results;
    static NumericTable testDependentVariables;

    private static DaalContext context = new DaalContext();

    public static void main(String[] args) throws java.io.FileNotFoundException, java.io.IOException {

        trainModel();

        testModel();

        printResults();

        context.dispose();
    }

    private static void trainModel() {

        /* Build partial ridge regression models on local nodes */
        PartialResult[] pres = new PartialResult[nNodes];

        for (int node = 0; node < nNodes; node++) {
            /* Initialize FileDataSource to retrieve the input data from a .csv file */
            FileDataSource trainDataSource = new FileDataSource(context, trainDatasetFileNames[node],
                    DataSource.DictionaryCreationFlag.DoDictionaryFromContext,
                    DataSource.NumericTableAllocationFlag.NotAllocateNumericTable);

            /* Create Numeric Tables for training data and labels */
            NumericTable trainData = new HomogenNumericTable(context, Double.class, nFeatures, 0, NumericTable.AllocationFlag.NotAllocate);
            NumericTable trainDependentVariables = new HomogenNumericTable(context, Double.class, nDependentVariables, 0,
                                                                           NumericTable.AllocationFlag.NotAllocate);
            MergedNumericTable mergedData = new MergedNumericTable(context);
            mergedData.addNumericTable(trainData);
            mergedData.addNumericTable(trainDependentVariables);

            /* Retrieve the data from an input file */
            trainDataSource.loadDataBlock(mergedData);

            /* Create an algorithm object to train the ridge regression model with the normal equations method */
            TrainingDistributedStep1Local ridgeRegressionTraining = new TrainingDistributedStep1Local(context,
                    Double.class, TrainingMethod.normEqDense);

            /* Set the input data */
            ridgeRegressionTraining.input.set(TrainingInputId.data, trainData);
            ridgeRegressionTraining.input.set(TrainingInputId.dependentVariable, trainDependentVariables);

            /* Build a partial ridge regression model */
            pres[node] = ridgeRegressionTraining.compute();
        }

        /* Build the final ridge regression model on the master node*/
        /* Create an algorithm object to train the ridge regression model with the normal equations method */
        TrainingDistributedStep2Master ridgeRegressionTraining = new TrainingDistributedStep2Master(context,
                Double.class, TrainingMethod.normEqDense);

        /* Set partial ridge regression models built on local nodes */
        for (int node = 0; node < nNodes; node++) {
            ridgeRegressionTraining.input.add(MasterInputId.partialModels, pres[node]);
        }

        /* Build and retrieve the final ridge regression model */
        ridgeRegressionTraining.compute();

        TrainingResult trainingResult = ridgeRegressionTraining.finalizeCompute();

        model = trainingResult.get(TrainingResultId.model);
    }

    private static void testModel() {
        /* Initialize FileDataSource to retrieve the input data from a .csv file */
        FileDataSource testDataSource = new FileDataSource(context, testDatasetFileName,
                DataSource.DictionaryCreationFlag.DoDictionaryFromContext,
                DataSource.NumericTableAllocationFlag.NotAllocateNumericTable);

        /* Create Numeric Tables for testing data and labels */
        NumericTable testData = new HomogenNumericTable(context, Double.class, nFeatures, 0, NumericTable.AllocationFlag.NotAllocate);
        testDependentVariables = new HomogenNumericTable(context, Double.class, nDependentVariables, 0, NumericTable.AllocationFlag.NotAllocate);
        MergedNumericTable mergedData = new MergedNumericTable(context);
        mergedData.addNumericTable(testData);
        mergedData.addNumericTable(testDependentVariables);

        /* Retrieve the data from an input file */
        testDataSource.loadDataBlock(mergedData);

        /* Create algorithm objects to predict values of ridge regression with the default method */
        PredictionBatch ridgeRegressionPredict = new PredictionBatch(context, Double.class,
                PredictionMethod.defaultDense);

        /* Provide the input data */
        ridgeRegressionPredict.input.set(PredictionInputId.data, testData);
        ridgeRegressionPredict.input.set(PredictionInputId.model, model);

        /* Compute and retrieve the prediction results */
        PredictionResult predictionResult = ridgeRegressionPredict.compute();

        results = predictionResult.get(PredictionResultId.prediction);
    }

    private static void printResults() {
        NumericTable beta = model.getBeta();
        NumericTable expected = testDependentVariables;
        Service.printNumericTable("Coefficients: ", beta);
        Service.printNumericTable("First 10 rows of results (obtained): ", results, 10);
        Service.printNumericTable("First 10 rows of results (expected): ", expected, 10);
    }
}
