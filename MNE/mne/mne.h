//=============================================================================================================
/**
* @file     mne.h
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hämäläinen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     July, 2012
*
* @section  LICENSE
*
* Copyright (C) 2012, Christoph Dinh and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of the Massachusetts General Hospital nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MASSACHUSETTS GENERAL HOSPITAL BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    Contains the MNE class declaration, which provides static wrapper functions to stay consistent with
*           mne matlab toolbox
*
*/

#ifndef MNE_H
#define MNE_H

//*************************************************************************************************************
//=============================================================================================================
// MNE INCLUDES
//=============================================================================================================

#include "mne_global.h"

#include "mne_forwardsolution.h"
#include "mne_hemisphere.h"
#include "mne_sourcespace.h"


//*************************************************************************************************************
//=============================================================================================================
// FIFF INCLUDES
//=============================================================================================================

#include "../fiff/fiff_constants.h"


//*************************************************************************************************************
//=============================================================================================================
// Qt INCLUDES
//=============================================================================================================

#include <QMap>


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE MNELIB
//=============================================================================================================

namespace MNELIB
{

//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

//using namespace SOURCELAB;
using namespace FIFFLIB;


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================


//=============================================================================================================
/**
* DECLARE MNE WRAPPER CLASS
* @brief The MNE class provides wrapper functions to stay consistent with mne matlab toolbox.
*/

class MNESHARED_EXPORT MNE
{

public:

    //=========================================================================================================
    /**
    * dtor
    */
    virtual ~MNE()
    { }


    //=========================================================================================================
    /**
    * mne_block_diag - decoding part
    *
    * ### MNE toolbox root function ###
    *
    * Wrapper for the MNEForwardSolution::extract_block_diag static function
    */
    //    static inline MatrixXf extract_block_diag(MatrixXf& A, qint32 n);



    //=========================================================================================================
    /**
    * mne_get_current_comp
    *
    * ### MNE toolbox root function ###
    *
    * Wrapper for the FiffInfo get_current_comp member function
    *
    * Get the current compensation in effect in the data
    *
    * @param[in] info   Fiff measurement info
    *
    * @return the current compensation
    */
    static inline qint32 get_current_comp(FiffInfo* info)
    {
        return info->get_current_comp();
    }


    //=========================================================================================================
    /**
    * mne_block_diag - encoding part
    *
    * ### MNE toolbox root function ###
    *
    * Wrapper for the MNEForwardSolution::make_block_diag static function
    *
    * Make a sparse block diagonal matrix
    *
    * Returns a sparse block diagonal, diagonalized from the elements in "A". "A" is ma x na, comprising
    * bdn=(na/"n") blocks of submatrices. Each submatrix is ma x "n", and these submatrices are placed down
    * the diagonal of the matrix.
    *
    * @param[in, out] A Matrix which should be diagonlized
    * @param[in, out] n Columns of the submatrices
    *
    * @return A sparse block diagonal, diagonalized from the elements in "A".
    */
    static inline SparseMatrix<float> make_block_diag(MatrixXf& A, qint32 n)
    {
        return MNEForwardSolution::make_block_diag(A, n);

    }



//    %
//    % [comp] = mne_make_compensator(info,from,to,exclude_comp_chs)
//    %
//    % info              - measurement info as returned by the fif reading routines
//    % from              - compensation in the input data
//    % to                - desired compensation in the output
//    % exclude_comp_chs  - exclude compensation channels from the output (optional)
//    %

//    %
//    % Create a compensation matrix to bring the data from one compensation
//    % state to another
//    %
//    function [comp] =
//    mne_make_compensator(info,from,to,exclude_comp_chs)


    //=========================================================================================================
    /**
    * ToDo make this part of FiffInfo
    * mne_make_compensator
    *
    * ### MNE toolbox root function ###
    *
    * Create a compensation matrix to bring the data from one compensation state to another
    *
    * @param[in] info               measurement info as returned by the fif reading routines
    * @param[in] from               compensation in the input data
    * @param[in] to                 desired compensation in the output
    * @param[out] comp              Compensation Matrix
    * @param[in] exclude_comp_chs   exclude compensation channels from the output (optional)
    *
    * @return true if succeeded, false otherwise
    */
    static bool make_compensator(FiffInfo* info, fiff_int_t from, fiff_int_t to, FiffCtfComp& ctf_comp, bool exclude_comp_chs = false)
    {
        return info->make_compensator(from, to, ctf_comp, exclude_comp_chs);
    }


    //ToDo FiffChInfoList Class
    //=========================================================================================================
    /**
    * mne_set_current_comp
    *
    * ### MNE toolbox root function ###
    *
    * Wrapper for the FiffInfo::set_current_comp static function
    * Consider taking the member function of a FiffInfo set_current_comp(fiff_int_t value),
    * when compensation should be applied to the channels of FiffInfo
    *
    * Set the current compensation value in the channel info structures
    *
    * @param[in] chs    fiff channel info list
    * @param[in] value  compensation value
    *
    * @return the current compensation
    */
    static QList<FiffChInfo> set_current_comp(QList<FiffChInfo>& chs, fiff_int_t value)
    {
        return FiffInfo::set_current_comp(chs, value);
    }


    //=========================================================================================================
    /**
    * make_projector
    *
    * ### MNE toolbox root function ###
    *
    * Wrapper for the FiffInfo::make_projector static function
    * There exists also a member function which should be preferred:
    * make_projector(MatrixXf& proj, MatrixXf& U = defaultUMatrix)
    *
    * Make an SSP operator
    *
    * @param[in] projs      A set of projection vectors
    * @param[in] ch_names   A cell array of channel names
    * @param[out] proj      The projection operator to apply to the data
    * @param[in] bads       Bad channels to exclude
    * @param[out] U         The orthogonal basis of the projection vectors (optional)
    *
    * @return nproj - How many items in the projector
    */
    inline static fiff_int_t make_projector(QList<FiffProj*>& projs, QStringList& ch_names, MatrixXf& proj, QStringList& bads = defaultQStringList, MatrixXf& U = defaultMatrixXf)
    {
        return FiffInfo::make_projector(projs, ch_names, proj, bads, U);
    }


    //=========================================================================================================
    /**
    * mne_make_projector_info
    *
    * ### MNE toolbox root function ###
    *
    * Wrapper for the FiffInfo make_projector_info(MatrixXf& proj) member function
    *
    * Make a SSP operator using the meas info
    *
    * @param[in] info       Fiff measurement info
    * @param[out] proj      The projection operator to apply to the data
    *
    * @return nproj - How many items in the projector
    */
    static inline qint32 make_projector_info(FiffInfo* info, MatrixXf& proj)
    {
        return info->make_projector_info(proj);
    }


    //=========================================================================================================
    /**
    * mne_find_source_space_hemi
    *
    * ### MNE toolbox root function ###
    *
    * Wrapper for the MNESourceSpace::find_source_space_hemi static function
    *
    * Returns the hemisphere id (FIFFV_MNE_SURF_LEFT_HEMI or FIFFV_MNE_SURF_RIGHT_HEMI) for a source space.
    *
    * @param[in] p_pHemisphere the hemisphere to investigate
    *
    * @return the deduced hemisphere id
    */
    inline static qint32 find_source_space_hemi(MNEHemisphere* p_pHemisphere)
    {
        return MNESourceSpace::find_source_space_hemi(p_pHemisphere);
    }


    //=========================================================================================================
    /**
    * mne_patch_info
    *
    * ### MNE toolbox root function ###
    *
    * Wrapper for the MNESourceSpace::patch_info static function
    *
    * @param [in] nearest   The nearest vector of the source space.
    * @param [out] pinfo    The requested patch information.
    *
    * @return true if succeeded, false otherwise
    */
    static bool patch_info(VectorXi& nearest, QList<VectorXi>& pinfo)
    {
        return MNESourceSpace::patch_info(nearest, pinfo);
    }


// ToDo Eventlist Class??
    //=========================================================================================================
    /**
    * mne_read_events
    *
    * ### MNE toolbox root function ###
    *
    * Read an event list from a fif file
    *
    * @param [in] p_sFileName   The name of the file
    * @param [out] eventlist    The read eventlist m x 3; with m events; colum: 1 - position in samples, 3 - eventcode
    *
    * @return true if succeeded, false otherwise
    */
    static bool read_events(QString& p_sFileName, MatrixXi& eventlist);


    //=========================================================================================================
    /**
    * mne_read_forward_solution
    *
    * ### MNE toolbox root function ###
    *
    * Wrapper for the MNEForwardSolution::read_forward_solution static function
    *
    * Reads a forward solution from a fif file
    *
    * @param [in] p_sFile       The name of the file
    * @param [out] fwd A forward solution from a fif file
    * @param [in] force_fixed   Force fixed source orientation mode? (optional)
    * @param [in] surf_ori      Use surface based source coordinate system? (optional)
    * @param [in] include       Include these channels (optional)
    * @param [in] exclude       Exclude these channels (optional)
    *
    * @return true if succeeded, false otherwise
    */
    static inline bool read_forward_solution(QString& p_sFile, MNEForwardSolution*& fwd, bool force_fixed = false, bool surf_ori = false, QStringList& include = defaultQStringList, QStringList& exclude = defaultQStringList)
    {
        return MNEForwardSolution::read_forward_solution(p_sFile, fwd, force_fixed, surf_ori, include, exclude);
    }

    //=========================================================================================================
    /**
    * mne_read_forward_solution
    *
    * ### MNE toolbox root function ###
    *
    * Wrapper for the MNESourceSpace::read_source_spaces static function
    *
    * Reads source spaces from a fif file
    *
    * @param [in] p_pFile   The open fiff file
    * @param [in] add_geom  Add geometry information to the source spaces
    * @param [in] p_pTree   Search for the source spaces here
    *
    * @param [out] p_pSourceSpace     The read source spaces
    *
    * @return true if succeeded, false otherwise
    */
    static bool read_source_spaces(FiffFile*& p_pFile, bool add_geom, FiffDirTree*& p_pTree, MNESourceSpace*& p_pSourceSpace)
    {
        return MNESourceSpace::read_source_spaces(p_pFile, add_geom, p_pTree, p_pSourceSpace);
    }

    //=========================================================================================================
    /**
    * mne_transform_source_space_to
    *
    * ### MNE toolbox root function ###
    *
    * Wrapper for the MNESourceSpace transform_source_space_to member function
    *
    * Transforms source space data to the desired coordinate system
    *
    * @param [in, out] p_pMNESourceSpace the source space which is should be transformed
    * @param [in] dest destination check code
    * @param [in] trans transformation information
    */
    static inline void transform_source_space_to(MNESourceSpace* p_pMNESourceSpace, fiff_int_t dest, FiffCoordTrans* trans)
    {
        return p_pMNESourceSpace->transform_source_space_to(dest, trans);
    }

    //=========================================================================================================
    /**
    * mne_transpose_named_matrix
    *
    * ### MNE toolbox root function ###
    *
    * Wrapper for the MNEForwardSolution::transpose_named_matrix static function
    *
    * Transpose a named matrix (FiffNamedMatrix)
    *
    * @param[in, out] mat FiffNamedMatrix which shoul be transposed.
    *
    */
    static inline void transpose_named_matrix(FiffNamedMatrix*& mat)
    {
        return MNEForwardSolution::transpose_named_matrix(mat);
    }

private:



};


} // NAMESPACE

#endif // MNE_H
