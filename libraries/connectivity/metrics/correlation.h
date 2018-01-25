//=============================================================================================================
/**
* @file     correlation.h
* @author   Lorenz Esch <Lorenz.Esch@tu-ilmenau.de>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     January, 2018
*
* @section  LICENSE
*
* Copyright (C) 2018, Lorenz Esch and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of MNE-CPP authors nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief     Correlation class declaration.
*
*/

#ifndef CORRELATION_H
#define CORRELATION_H


//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "connectivity_global.h"

#include "abstractmetric.h"


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QSharedPointer>


//*************************************************************************************************************
//=============================================================================================================
// Eigen INCLUDES
//=============================================================================================================

#include <Eigen/Core>


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================

namespace MNELIB {
    class MNEEpochDataList;
}


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE CONNECTIVITYLIB
//=============================================================================================================

namespace CONNECTIVITYLIB {


//*************************************************************************************************************
//=============================================================================================================
// CONNECTIVITYLIB FORWARD DECLARATIONS
//=============================================================================================================

class Network;


//=============================================================================================================
/**
* This class computes the correlation metric.
*
* @brief This class computes the correlation metric.
*/
class CONNECTIVITYSHARED_EXPORT Correlation : public AbstractMetric
{    

public:
    typedef QSharedPointer<Correlation> SPtr;            /**< Shared pointer type for Correlation. */
    typedef QSharedPointer<const Correlation> ConstSPtr; /**< Const shared pointer type for Correlation. */

    //=========================================================================================================
    /**
    * Constructs a Correlation object.
    */
    explicit Correlation();

    //=========================================================================================================
    /**
    * Calculates the correlation coefficient between the rows of the data matrix.
    *
    * @param[in] epochDataList  The data in form of epochs.
    * @param[in] matVert        The vertices of each network node.
    *
    * @return                   The connectivity information in form of a network structure.
    */
    static Network correlationCoeff(const MNELIB::MNEEpochDataList& epochDataList, const Eigen::MatrixX3f& matVert);

protected:
    //=========================================================================================================
    /**
    * Calculates the actual correlation coefficient between two data vectors.
    *
    * @param[in] vecFirst    The first input data row.
    * @param[in] vecSecond   The second input data row.
    *
    * @return               The correlation coefficient.
    */
    static double calcCorrelationCoeff(const Eigen::RowVectorXd &vecFirst, const Eigen::RowVectorXd &vecSecond);
};


//*************************************************************************************************************
//=============================================================================================================
// INLINE DEFINITIONS
//=============================================================================================================


} // namespace CONNECTIVITYLIB

#endif // CORRELATION_H
