/* file: PcaCorDenseStep2Reducer.java */
/*******************************************************************************
* Copyright 2017 Intel Corporation
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

package DAAL;

import java.io.*;

import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.*;
import org.apache.hadoop.fs.FileSystem;

import com.intel.daal.data_management.data.HomogenNumericTable;
import com.intel.daal.algorithms.pca.*;
import com.intel.daal.algorithms.PartialResult;
import com.intel.daal.data_management.data.*;
import com.intel.daal.services.*;

public class PcaCorDenseStep2Reducer extends Reducer<IntWritable, WriteableData, IntWritable, WriteableData> {

    @Override
    public void reduce(IntWritable key, Iterable<WriteableData> values, Context context)
                  throws IOException, InterruptedException {

        DaalContext daalContext = new DaalContext();

        /* Create an algorithm to compute PCA decomposition using the correlation method on the master node */
        DistributedStep2Master pcaMaster = new DistributedStep2Master(daalContext, Double.class, Method.correlationDense);

        for (WriteableData value : values) {
            PartialResult pr = (PartialResult)value.getObject(daalContext);
            pcaMaster.input.add( MasterInputId.partialResults, pr );
        }

        /* Compute PCA decomposition on the master node */
        pcaMaster.compute();

        /* Finalize computations and retrieve the results */
        Result res = pcaMaster.finalizeCompute();

        HomogenNumericTable eigenValues  = (HomogenNumericTable)res.get(ResultId.eigenValues );
        HomogenNumericTable eigenVectors = (HomogenNumericTable)res.get(ResultId.eigenVectors);

        context.write(new IntWritable(0), new WriteableData( eigenValues  ) );
        context.write(new IntWritable(1), new WriteableData( eigenVectors ) );

        daalContext.dispose();
    }
}
