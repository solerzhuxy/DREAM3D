/* ============================================================================
 * Copyright (c) 2010, Michael A. Jackson (BlueQuartz Software)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of Michael A. Jackson nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 //
 //  This code was written under United States Air Force Contract number
 //                           FA8650-07-D-5800
 //
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#ifndef _M3CEntireVolume_H_
#define _M3CEntireVolume_H_

#include <string>

#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/DREAM3DSetGetMacros.h"
#include "DREAM3DLib/Common/IDataArray.h"
#include "DREAM3DLib/Common/AbstractFilter.h"
#include "DREAM3DLib/Common/SurfaceMeshStructs.h"
#include "DREAM3DLib/Common/AbstractFilter.h"


/**
 * @class MMCSurfaceMeshingFilter MMCSurfaceMeshingFilter.h DREAM3DLic/SurfaceMeshingFilters/MMCSurfaceMeshingFilter.h
 * @brief This filter was contributed by Dr. Sukbin Lee of Carnegi-Mellon University and uses a "MultiMaterial Marching
 * Cubes" algorithm originally proposed by Wu & Sullivan.
 * Multiple material marching cubes algorithm, Ziji Wu1, John M. Sullivan Jr2, International Journal for Numerical Methods in Engineering
 * Special Issue: Trends in Unstructured Mesh Generation, Volume 58, Issue 2, pages 189–207, 14 September 2003
 * @author
 * @date
 * @version 1.0
 */
class DREAM3DLib_EXPORT M3CEntireVolume : public AbstractFilter
{
  public:
    DREAM3D_SHARED_POINTERS(M3CEntireVolume)
    DREAM3D_STATIC_NEW_MACRO(M3CEntireVolume)
    DREAM3D_TYPE_MACRO_SUPER(M3CEntireVolume, AbstractFilter)

    virtual ~M3CEntireVolume();

    //------ Created Surface Mesh Cell Data
    DREAM3D_INSTANCE_STRING_PROPERTY(SurfaceMeshEdgesArrayName)
    DREAM3D_INSTANCE_STRING_PROPERTY(SurfaceMeshInternalEdgesArrayName)
    DREAM3D_INSTANCE_STRING_PROPERTY(SurfaceMeshNodeTypeArrayName)

    //------ Required Cell Data
    DREAM3D_INSTANCE_STRING_PROPERTY(GrainIdsArrayName)

    //--------- Input Parameters
    DREAM3D_INSTANCE_PROPERTY(bool, AddSurfaceLayer)

    /**
    * @brief This returns the group that the filter belonds to. You can select
    * a different group if you want. The string returned here will be displayed
    * in the GUI for the filter
    */
    virtual const std::string getGroupName() { return DREAM3D::FilterGroups::SurfaceMeshingFilters; }

    /**
    * @brief This returns a string that is displayed in the GUI. It should be readable
    * and understandable by humans.
    */
    virtual const std::string getHumanLabel() { return "M3C Surface Mesh (Volume at a time)"; }

    /**
    * @brief This method will instantiate all the end user settable options/parameters
    * for this filter
    */
    virtual void setupFilterParameters();

    /**
    * @brief This method will write the options to a file
    * @param writer The writer that is used to write the options to a file
    */
    virtual void writeFilterParameters(AbstractFilterParametersWriter* writer);

     /**
    * @brief Reimplemented from @see AbstractFilter class
    */
    virtual void execute();

    /**
    * @brief This function runs some sanity checks on the DataContainer and inputs
    * in an attempt to ensure the filter can process the inputs.
    */
    virtual void preflight();

  protected:
    M3CEntireVolume();

    /**
    * @brief Checks for the appropriate parameter values and availability of
    * arrays in the data container
    * @param preflight
    * @param voxels The number of voxels
    * @param fields The number of fields
    * @param ensembles The number of ensembles
    */
    void dataCheck(bool preflight, size_t voxels, size_t fields, size_t ensembles);

 virtual int createMesh(size_t* dims, float* res, size_t* fileDim);

    /**
     * @brief initialize_micro_from_grainIds
     * @param dims
     * @param res
     * @param fileDims
     * @param grainIds
     * @param points
     * @param voxelCoords
     * @return
     */
    virtual int initialize_micro_from_grainIds(size_t dims[3], float res[3], size_t fileDims[3],
                                       int32_t* grainIds,
                                       DataArray<int32_t>::Pointer points,
                                       VoxelCoord* point);

    /**
     * @brief get_neighbor_list
     * @param n
     * @param ns
     * @param nsp
     * @param xDim
     * @param yDim
     * @param zDim
     */
    virtual void get_neighbor_list(Neighbor* n, int ns, int nsp, int xDim, int yDim, int zDim);

    virtual void initialize_nodes (VoxelCoord* p,
                           Node* v,
                           int ns, float dx, float dy, float dz);
    virtual void initialize_squares (Neighbor* neighbors, Face* sq, int ns, int nsp);
    virtual int  get_number_fEdges (Face* sq, DataArray<int32_t>::Pointer points, Neighbor* n, int ns);
    virtual void get_nodes_fEdges (Face* sq,
                           DataArray<int32_t>::Pointer points,
                           Neighbor* neighbors,
                           Node* v,
                           Segment* e,
                           int ns,
                           int nsp,
                           int xDim);
    virtual int  get_square_index (int tns[4]);
    virtual int  treat_anomaly (int tnst[4], DataArray<int32_t>::Pointer points, Neighbor* n1, int sqid);
    virtual void get_nodes (int cst, int ord, int nidx[2], int *nid, int nsp1, int xDim1);
    virtual void get_spins (DataArray<int32_t>::Pointer points, int cst, int ord, int pID[2], int *pSpin, int nsp1, int xDim1);
    virtual int  get_number_triangles (DataArray<int32_t>::Pointer points,
                               Face* sq,
                               Node* v,
                               Segment* e,
                               int ns,
                               int nsp,
                               int xDim);
    virtual int  get_number_case0_triangles (int *afe, Node* v, Segment* e1, int nfedge);
    virtual int  get_number_case2_triangles (int *afe, Node* v1, Segment* fedge, int nfedge, int *afc, int nfctr);
    virtual int  get_number_caseM_triangles (int *afe, Node* v, Segment* e1, int nfedge, int *afc, int nfctr);
    virtual int  get_triangles (VoxelCoord* p,
                        Triangle* t,
                        Face* sq,
                        Node* v,
                        Segment* e,
                        Neighbor* neighbors,
                        int ns,
                        int nsp,
                        int xDim);
    virtual void get_case0_triangles (Triangle* t1, int *afe, Node* v1, Segment* e1,
                              int nfedge, int tin, int *tout, double tcrd1[3], double tcrd2[3], int mcid);
    virtual void get_case2_triangles (Triangle* triangles1, int *afe, Node* v1, Segment* fedge,
                              int nfedge, int *afc, int nfctr, int tin, int *tout, double tcrd1[3], double tcrd2[3], int mcid);
    virtual void get_caseM_triangles (Triangle* triangles1, int *afe, Node* v1, Segment* fedge,
                              int nfedge, int *afc, int nfctr, int tin, int *tout, int ccn, double tcrd1[3], double tcrd2[3], int mcid);
    virtual void find_edgePlace(double tvcrd1[3], double tvcrd2[3], double tvcrd3[3], int tw[3],
                        double xh, double xl, double yh, double yl, double zh, double zl);
    virtual int get_number_unique_inner_edges(Triangle* triangles, int nT);
    virtual void get_unique_inner_edges(Triangle* t, ISegment* ie, int nT, int nfedge);
    virtual void update_triangle_sides_with_fedge(Triangle* t,
                                          Segment* e,
                                          Face* sq,
                                          int nT,
                                          int xDim,
                                          int nsp);
    virtual void arrange_spins (DataArray<int32_t>::Pointer points,
                        VoxelCoord* pCoord,
                        Triangle* triangles,
                        Node* v,
                        int numT, int xDim, int nsp);
    virtual void update_node_edge_kind(Node* v, Segment* fe, ISegment* ie, Triangle* t, int nT, int nfedge);
    virtual int assign_new_nodeID (Node* v, DataArray<int32_t>::Pointer node_ids, int ns);
    virtual void generate_update_nodes_edges_array(DataArray<int32_t>::Pointer new_ids_for_nodes,
                                            DataArray<int8_t>::Pointer nodeKindPtr,
                                            StructArray<Node>::Pointer shortNodes,
                                            StructArray<Node>::Pointer vertices,
                                            StructArray<Triangle>::Pointer triangles,
                                            StructArray<Segment>::Pointer faceEdges,
                                            StructArray<ISegment>::Pointer internalEdges);

    virtual void resetMaxGrainIdToZero( DataArray<int32_t>::Pointer new_ids_for_nodes,
                                                                 DataArray<int8_t>::Pointer nodeKindPtr,
                                                                StructArray<Node>::Pointer shortNodes,
                                                                StructArray<Node>::Pointer vertices,
                                                                StructArray<Triangle>::Pointer triangles,
                                                                StructArray<Segment>::Pointer faceEdges,
                                                                StructArray<ISegment>::Pointer internalEdges,
                                                                int maxGrainId);

  private:
    int32_t* m_GrainIds;
    int8_t* m_SurfaceMeshNodeType;

    int EdgeTable2D[20][8];
    int NSTable2D[20][8];

    M3CEntireVolume(const M3CEntireVolume&); // Copy Constructor Not Implemented
    void operator=(const M3CEntireVolume&); // Operator '=' Not Implemented
};

#endif /* _M3CEntireVolume_H_ */
