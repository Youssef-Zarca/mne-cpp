//=============================================================================================================
/**
* @file     realtimemultisamplearraymodel.h
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     May, 2014
*
* @section  LICENSE
*
* Copyright (C) 2014, Christoph Dinh and Matti Hamalainen. All rights reserved.
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
* @brief    Declaration of the RealTimeMultiSampleArrayModel Class.
*
*/

#ifndef REALTIMEMULTISAMPLEARRAYMODEL_H
#define REALTIMEMULTISAMPLEARRAYMODEL_H


//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include <xMeas/realtimesamplearraychinfo.h>
#include <fiff/fiff_types.h>
#include <fiff/fiff_info.h>

#include <utils/filterTools/filterdata.h>
#include <utils/mnemath.h>


//*************************************************************************************************************
//=============================================================================================================
// Qt INCLUDES
//=============================================================================================================

#include <QAbstractTableModel>

#include <QtConcurrent/QtConcurrent>
#include <QFuture>


//*************************************************************************************************************
//=============================================================================================================
// Eigen INCLUDES
//=============================================================================================================

#include <Eigen/Core>
#include <Eigen/SparseCore>


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE XDISPLIB
//=============================================================================================================

namespace XDISPLIB
{


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace XMEASLIB;
using namespace FIFFLIB;
using namespace Eigen;
using namespace UTILSLIB;


//*************************************************************************************************************
//=============================================================================================================
// DEFINE TYPEDEFS
//=============================================================================================================

typedef QPair<const double*,qint32> RowVectorPair;
typedef Matrix<double,Dynamic,Dynamic,RowMajor> MatrixXdR;

//=============================================================================================================
/**
* DECLARE CLASS RealTimeMultiSampleArrayModel
*
* @brief The RealTimeMultiSampleArrayModel class implements the data access model for a real-time multi sample array data stream
*/
class RealTimeMultiSampleArrayModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    //=========================================================================================================
    /**
    * Constructs an real-time multi sample array table model for the given parent.
    *
    * @param[in] parent     parent of the table model
    */
    RealTimeMultiSampleArrayModel(QObject *parent = 0);

    //=========================================================================================================
    /**
    * Returns the number of rows under the given parent. When the parent is valid it means that rowCount is returning the number of children of parent.
    *
    * @param[in] parent     not used
    *
    * @return number of rows
    */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const ;

    //=========================================================================================================
    /**
    * Returns the number of columns for the children of the given parent.
    *
    * @param[in] parent     not used
    *
    * @return number of columns
    */
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    //=========================================================================================================
    /**
    * Returns the data stored under the given role for the item referred to by the index.
    *
    * @param[in] index      determines item location
    * @param[in] role       role to return
    *
    * @return accessed data
    */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    //=========================================================================================================
    /**
    * Returns the data for the given role and section in the header with the specified orientation.
    *
    * @param[in] section        For horizontal headers, the section number corresponds to the column number. Similarly, for vertical headers, the section number corresponds to the row number.
    * @param[in] orientation    Qt::Horizontal or Qt::Vertical
    * @param[in] role           role to show
    *
    * @return accessed eader data
    */
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    //=========================================================================================================
    /** ToDo: Obsolete
    * Sets corresponding channel information
    *
    * @param [in] chInfo        The corresponding channel information list
    */
    void setChannelInfo(QList<RealTimeSampleArrayChInfo> &chInfo);

    //=========================================================================================================
    /**
    * Sets corresponding fiff information
    *
    * @param [in] p_pFiffInfo   The corresponding fiff information
    */
    void setFiffInfo(FIFFLIB::FiffInfo::SPtr& p_pFiffInfo);

    //=========================================================================================================
    /**
    * Sets the sampling information and calculates the resulting downsampling factor between actual sps and desired sps
    *
    * @param[in] sps        Samples per second of incomming data
    * @param[in] T          Time window length to display
    */
    void setSamplingInfo(float sps, int T);

    //=========================================================================================================
    /**
    * Adds multiple time points (QVector) for a channel set (VectorXd)
    *
    * @param[in] data       data to add (Time points of channel samples)
    */
    void addData(const QList<MatrixXd> &data);

    //=========================================================================================================
    /**
    * Returns the kind of a given channel number
    *
    * @param[in] row    row number which correspodns to a given channel
    *
    * @return kind of given channel number
    */
    fiff_int_t getKind(qint32 row) const;

    //=========================================================================================================
    /**
    * Returns the unit of a given channel number
    *
    * @param[in] row    row number which correspodns to a given channel
    *
    * @return unit of given channel number
    */
    fiff_int_t getUnit(qint32 row) const;

    //=========================================================================================================
    /**
    * Returns the coil type of a given channel number
    *
    * @param[in] row    row number which correspodns to a given channel
    *
    * @return coil type of given channel number
    */
    fiff_int_t getCoil(qint32 row) const;

    //=========================================================================================================
    /**
    * Returns the maximal number of samples of the downsampled data to display
    *
    * @return the maximal number of samples
    */
    inline qint32 getMaxSamples() const;

    //=========================================================================================================
    /**
    * Returns the current sample index which represents the index which the next incoming data will be stored at in the data
    *
    * @return the current sample index
    */
    inline qint32 getCurrentSampleIndex() const;

    //=========================================================================================================
    /**
    * Returns the first value of the last complete data display block
    *
    * @param[in] row    row for which the first value is to be returned
    *
    * @return the first value of the last complete data display block
    */
    inline double getLastBlockFirstValue(int row) const;

    //=========================================================================================================
    /**
    * Returns a map which conatins the channel idx and its corresponding selection status
    *
    * @return the channel idx to selection status
    */
    inline const QMap<qint32,qint32>& getIdxSelMap() const;

    //=========================================================================================================
    /**
    * Selects the given list of channel indeces and unselect all other channels
    *
    * @param[in] selection      channel index list to select
    */
    void selectRows(const QList<qint32> &selection);

    //=========================================================================================================
    /**
    * Hides the given list of channel
    *
    * @param[in] selection      channel index list to select
    */
    void hideRows(const QList<qint32> &selection);

    //=========================================================================================================
    /**
    * Resets the current selection (selects all channels)
    */
    void resetSelection();

    //=========================================================================================================
    /**
    * Returns the number of vertical lines (one per second)
    *
    * @return number of vertical lines
    */
    inline qint32 numVLines() const;

    //=========================================================================================================
    /**
    * Toggle freeze for all channels when a channel is double clicked
    *
    * @param [in] index     of the channel which has been double clicked
    */
    void toggleFreeze(const QModelIndex &index);

    //=========================================================================================================
    /**
    * Returns current freezing status
    *
    * @return the current freezing status
    */
    inline bool isFreezed() const;

    //=========================================================================================================
    /**
    * Returns current scaling
    *
    * @return the current scaling
    */
    inline const QMap< qint32,float >& getScaling() const;

    //=========================================================================================================
    /**
    * Set scaling channel scaling
    *
    * @param[in] p_qMapChScaling    Map of scaling factors
    */
    void setScaling(const QMap< qint32,float >& p_qMapChScaling);

    //=========================================================================================================
    /**
    * Update the SSP projection
    */
    void updateProjection();

    //=========================================================================================================
    /**
    * Filter parameters changed
    *
    * @param[in] filterData    list of the currently active filter
    */
    void filterChanged(QList<FilterData> filterData);

    //=========================================================================================================
    /**
    * Sets the type of channel which are to be filtered
    *
    * @param[in] channelType    the channel type which is to be filtered (EEG, MEG, All)
    */
    void setFilterChannelType(QString channelType);

    //=========================================================================================================
    /**
    * Create list of channels which are to be filtered based on channel names
    *
    * @param[in] channelNames    the channel names which are to be filtered
    */
    void createFilterChannelList(QStringList channelNames);

signals:
    //=========================================================================================================
    /**
    * Emmited when new selcetion was made
    *
    * @param [in] selection     list of all selected channels
    */
    void newSelection(QList<qint32> selection);

    //=========================================================================================================
    /**
    * Emmited when the window size/max number of samples changed
    *
    * @param [in] windowSize     number of samples in the window
    */
    void windowSizeChanged(int windowSize);

private:
    //=========================================================================================================
    /**
    * Inits this model
    */
    void init();

    //=========================================================================================================
    /**
    * Clears the model
    */
    void clearModel();

    //=========================================================================================================
    /**
    * Calculates the filtered version of the raw input data
    *
    * @param [in] data          data which is to be filtered
    * @param [in] dataIndex     current position in the global data matrix
    */
    void filterChannelsConcurrently(const MatrixXd &data, int dataIndex);

    //=========================================================================================================
    /**
    * Calculates the filtered version of the channels in m_matDataRaw
    */
    void filterChannelsConcurrently();

    bool    m_bProjActivated;       /**< Proj activated */
    bool    m_bIsFreezed;           /**< Display is freezed */
    float   m_fSps;                 /**< Sampling rate */
    qint32  m_iT;                   /**< Time window */
    qint32  m_iDownsampling;        /**< Down sampling factor */
    qint32  m_iMaxSamples;          /**< Max samples per window */
    qint32  m_iCurrentSample;       /**< Current sample which holds the current position in the data matrix */
    qint32  m_iCurrentSampleFreeze; /**< Current sample which holds the current position in the data matrix when freezing tool is active */
    qint32  m_iMaxFilterLength;     /**< Max order of the current filters */
    qint32  m_iCurrentBlockSize;    /**< Current block size */

    QString m_sFilterChannelType;   /**< Kind of channel which is to be filtered */

    FiffInfo::SPtr          m_pFiffInfo;                        /**< Fiff info */

    RowVectorXi             m_vecBadIdcs;                       /**< Idcs of bad channels */
    VectorXd                m_vecLastBlockFirstValuesFiltered;  /**< The first value of the last complete filtered data display block */
    VectorXd                m_vecLastBlockFirstValuesRaw;       /**< The first value of the last complete raw data display block */

    MatrixXd                m_matProj;                          /**< SSP projector */
    SparseMatrix<double>    m_matSparseProj;                    /**< Sparse SSP projector */

    MatrixXdR               m_matDataRaw;
    MatrixXdR               m_matDataFiltered;
    MatrixXdR               m_matDataRawFreeze;
    MatrixXdR               m_matDataFilteredFreeze;
    MatrixXd                m_matOverlapBack;                   /**< Last overlap block for the back */

    QMap< qint32,float>                 m_qMapChScaling;        /**< Sensor selection widget. */
    QList<FilterData>                   m_filterData;           /**< List of currently active filters. */
    QList<RealTimeSampleArrayChInfo>    m_qListChInfo;          /**< Channel info list. ToDo: Obsolete*/
    QStringList                         m_filterChannelList;    /**< List of channels which are to be filtered.*/
    QStringList                         m_visibleChannelList;   /**< List of currently visible channels in the view.*/
    QMap<qint32,qint32>                 m_qMapIdxRowSelection;  /**< Selection mapping.*/
};


//*************************************************************************************************************
//=============================================================================================================
// INLINE DEFINITIONS
//=============================================================================================================

inline qint32 RealTimeMultiSampleArrayModel::getMaxSamples() const
{
    return m_iMaxSamples;
}


//*************************************************************************************************************

inline qint32 RealTimeMultiSampleArrayModel::getCurrentSampleIndex() const
{
    if(m_bIsFreezed)
        return m_iCurrentSampleFreeze;

    return m_iCurrentSample;
}


//*************************************************************************************************************

inline double RealTimeMultiSampleArrayModel::getLastBlockFirstValue(int row) const
{
    if(row>m_vecLastBlockFirstValuesFiltered.rows() || row>m_vecLastBlockFirstValuesRaw.rows())
        return 0;

    if(!m_filterData.isEmpty())
        return m_vecLastBlockFirstValuesFiltered[row];

    return m_vecLastBlockFirstValuesRaw[row];
}


//*************************************************************************************************************

inline const QMap<qint32,qint32>& RealTimeMultiSampleArrayModel::getIdxSelMap() const
{
    return m_qMapIdxRowSelection;
}


//*************************************************************************************************************

inline qint32 RealTimeMultiSampleArrayModel::numVLines() const
{
    return (m_iT - 1);
}


//*************************************************************************************************************

inline bool RealTimeMultiSampleArrayModel::isFreezed() const
{
    return m_bIsFreezed;
}


//*************************************************************************************************************

inline const QMap< qint32,float >& RealTimeMultiSampleArrayModel::getScaling() const
{
    return m_qMapChScaling;
}


} // NAMESPACE

#ifndef metatype_rowvectorpair
#define metatype_rowvectorpair
Q_DECLARE_METATYPE(XDISPLIB::RowVectorPair);
#endif

#endif // REALTIMEMULTISAMPLEARRAYMODEL_H
