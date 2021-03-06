/* file: CompressionMethod.java */
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
 * @ingroup data_compression
 * @{
 */
package com.intel.daal.data_management.compression;

/**
 * <a name="DAAL-CLASS-DATA_MANAGEMENT__COMPRESSION__COMPRESSIONMETHOD"></a>
 * @brief Compression and decompression methods
 */
public final class CompressionMethod {
    private int _value;

    /**
     * Constructs the compression method object using the provided value
     * @param value     Value corresponding to the compression method object
     */
    public CompressionMethod(int value) {
        _value = value;
    }

    /**
     * Returns the value corresponding to the compression method object
     * @return Value corresponding to the compression method object
     */
    public int getValue() {
        return _value;
    }

    private static final int Zlib  = 0;
    private static final int Lzo   = 1;
    private static final int Rle   = 2;
    private static final int Bzip2 = 3;

    public static final CompressionMethod zlib  = new CompressionMethod(Zlib);  /*!< DEFLATE compression method with ZLIB block header
                                                                                     or simple GZIP block header */
    public static final CompressionMethod lzo   = new CompressionMethod(
            Lzo);                                                               /*!< LZO1X compatible compression method */
    public static final CompressionMethod rle   = new CompressionMethod(Rle);   /*!< Run-Length Encoding method */
    public static final CompressionMethod bzip2 = new CompressionMethod(Bzip2); /*!< BZIP2 compression method */
}
/** @} */
