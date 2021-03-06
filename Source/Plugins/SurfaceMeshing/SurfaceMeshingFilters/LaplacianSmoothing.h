/* ============================================================================
* Copyright (c) 2009-2016 BlueQuartz Software, LLC
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
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
* contributors may be used to endorse or promote products derived from this software
* without specific prior written permission.
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
*
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#pragma once

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/Filtering/AbstractFilter.h"
#include "SIMPLib/SIMPLib.h"

#include "SurfaceMeshing/SurfaceMeshingFilters/SurfaceMeshFilter.h"

#define OUTPUT_DEBUG_VTK_FILES 1

#include "SurfaceMeshing/SurfaceMeshingDLLExport.h"

/**
 * @brief The LaplacianSmoothing class. See [Filter documentation](@ref laplaciansmoothing) for details.
 */
class SurfaceMeshing_EXPORT LaplacianSmoothing : public SurfaceMeshFilter
{
  Q_OBJECT
    PYB11_CREATE_BINDINGS(LaplacianSmoothing SUPERCLASS SurfaceMeshFilter)
    PYB11_PROPERTY(DataArrayPath SurfaceDataContainerName READ getSurfaceDataContainerName WRITE setSurfaceDataContainerName)
    PYB11_PROPERTY(DataArrayPath SurfaceMeshNodeTypeArrayPath READ getSurfaceMeshNodeTypeArrayPath WRITE setSurfaceMeshNodeTypeArrayPath)
    PYB11_PROPERTY(DataArrayPath SurfaceMeshFaceLabelsArrayPath READ getSurfaceMeshFaceLabelsArrayPath WRITE setSurfaceMeshFaceLabelsArrayPath)
    PYB11_PROPERTY(int IterationSteps READ getIterationSteps WRITE setIterationSteps)
    PYB11_PROPERTY(float Lambda READ getLambda WRITE setLambda)
    PYB11_PROPERTY(float SurfacePointLambda READ getSurfacePointLambda WRITE setSurfacePointLambda)
    PYB11_PROPERTY(float TripleLineLambda READ getTripleLineLambda WRITE setTripleLineLambda)
    PYB11_PROPERTY(float QuadPointLambda READ getQuadPointLambda WRITE setQuadPointLambda)
    PYB11_PROPERTY(float SurfaceTripleLineLambda READ getSurfaceTripleLineLambda WRITE setSurfaceTripleLineLambda)
    PYB11_PROPERTY(float SurfaceQuadPointLambda READ getSurfaceQuadPointLambda WRITE setSurfaceQuadPointLambda)
    PYB11_PROPERTY(bool UseTaubinSmoothing READ getUseTaubinSmoothing WRITE setUseTaubinSmoothing)
    PYB11_PROPERTY(float MuFactor READ getMuFactor WRITE setMuFactor)
public:
  SIMPL_SHARED_POINTERS(LaplacianSmoothing)
  SIMPL_FILTER_NEW_MACRO(LaplacianSmoothing)
   SIMPL_TYPE_MACRO_SUPER_OVERRIDE(LaplacianSmoothing, SurfaceMeshFilter)

   ~LaplacianSmoothing() override;

   SIMPL_FILTER_PARAMETER(DataArrayPath, SurfaceDataContainerName)
   Q_PROPERTY(DataArrayPath SurfaceDataContainerName READ getSurfaceDataContainerName WRITE setSurfaceDataContainerName)

   SIMPL_FILTER_PARAMETER(DataArrayPath, SurfaceMeshNodeTypeArrayPath)
   Q_PROPERTY(DataArrayPath SurfaceMeshNodeTypeArrayPath READ getSurfaceMeshNodeTypeArrayPath WRITE setSurfaceMeshNodeTypeArrayPath)

   SIMPL_FILTER_PARAMETER(DataArrayPath, SurfaceMeshFaceLabelsArrayPath)
   Q_PROPERTY(DataArrayPath SurfaceMeshFaceLabelsArrayPath READ getSurfaceMeshFaceLabelsArrayPath WRITE setSurfaceMeshFaceLabelsArrayPath)

   SIMPL_FILTER_PARAMETER(int, IterationSteps)
   Q_PROPERTY(int IterationSteps READ getIterationSteps WRITE setIterationSteps)

   SIMPL_FILTER_PARAMETER(float, Lambda)
   Q_PROPERTY(float Lambda READ getLambda WRITE setLambda)

   SIMPL_FILTER_PARAMETER(float, SurfacePointLambda)
   Q_PROPERTY(float SurfacePointLambda READ getSurfacePointLambda WRITE setSurfacePointLambda)

   SIMPL_FILTER_PARAMETER(float, TripleLineLambda)
   Q_PROPERTY(float TripleLineLambda READ getTripleLineLambda WRITE setTripleLineLambda)

   SIMPL_FILTER_PARAMETER(float, QuadPointLambda)
   Q_PROPERTY(float QuadPointLambda READ getQuadPointLambda WRITE setQuadPointLambda)

   SIMPL_FILTER_PARAMETER(float, SurfaceTripleLineLambda)
   Q_PROPERTY(float SurfaceTripleLineLambda READ getSurfaceTripleLineLambda WRITE setSurfaceTripleLineLambda)

   SIMPL_FILTER_PARAMETER(float, SurfaceQuadPointLambda)
   Q_PROPERTY(float SurfaceQuadPointLambda READ getSurfaceQuadPointLambda WRITE setSurfaceQuadPointLambda)

   SIMPL_FILTER_PARAMETER(bool, UseTaubinSmoothing)
   Q_PROPERTY(bool UseTaubinSmoothing READ getUseTaubinSmoothing WRITE setUseTaubinSmoothing)

   SIMPL_FILTER_PARAMETER(float, MuFactor)
   Q_PROPERTY(float MuFactor READ getMuFactor WRITE setMuFactor)

   /* This class is designed to be subclassed so that thoes subclasses can add
    * more functionality such as constrained surface nodes or Triple Lines. We use
    * this array to assign each vertex a specific Lambda value. Subclasses can set
    * this array then simply call the 'smooth' protected method to actually run the
    * smoothing iterations
    */
   SIMPL_VIRTUAL_INSTANCE_PROPERTY(DataArray<float>::Pointer, LambdaArray)

   /**
    * @brief getCompiledLibraryName Reimplemented from @see AbstractFilter class
    */
   const QString getCompiledLibraryName() const override;

   /**
    * @brief getBrandingString Returns the branding string for the filter, which is a tag
    * used to denote the filter's association with specific plugins
    * @return Branding string
    */
   const QString getBrandingString() const override;

   /**
    * @brief getFilterVersion Returns a version string for this filter. Default
    * value is an empty string.
    * @return
    */
   const QString getFilterVersion() const override;

   /**
    * @brief newFilterInstance Reimplemented from @see AbstractFilter class
    */
   AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters) const override;

   /**
    * @brief getGroupName Reimplemented from @see AbstractFilter class
    */
   const QString getGroupName() const override;

   /**
    * @brief getSubGroupName Reimplemented from @see AbstractFilter class
    */
   const QString getSubGroupName() const override;

   /**
    * @brief getUuid Return the unique identifier for this filter.
    * @return A QUuid object.
    */
   const QUuid getUuid() override;

   /**
    * @brief getHumanLabel Reimplemented from @see AbstractFilter class
    */
   const QString getHumanLabel() const override;

   /**
    * @brief setupFilterParameters Reimplemented from @see AbstractFilter class
    */
   void setupFilterParameters() override;

   /**
    * @brief readFilterParameters Reimplemented from @see AbstractFilter class
    */
   void readFilterParameters(AbstractFilterParametersReader* reader, int index) override;

   /**
    * @brief execute Reimplemented from @see AbstractFilter class
    */
   void execute() override;

   /**
    * @brief preflight Reimplemented from @see AbstractFilter class
    */
   void preflight() override;

 protected:
   LaplacianSmoothing();
   /**
    * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
    */
   void dataCheck();

   /**
    * @brief Initializes all the private instance variables.
    */
   void initialize();

   /**
    * @brief generateLambdaArray Generates the Lambda array that will be use during the smoothing
    * @return Integer error code
    */
   virtual int32_t generateLambdaArray();

   /**
    * @brief edgeBasedSmoothing Version of the smoothing algorithm uses Edge->Vertex connectivity information for its algorithm
    * @return Integer error code
    */
   virtual int32_t edgeBasedSmoothing();

 private:
   DEFINE_DATAARRAY_VARIABLE(int8_t, SurfaceMeshNodeType)
   DEFINE_DATAARRAY_VARIABLE(int32_t, SurfaceMeshFaceLabels)

 public:
   LaplacianSmoothing(const LaplacianSmoothing&) = delete;            // Copy Constructor Not Implemented
   LaplacianSmoothing(LaplacianSmoothing&&) = delete;                 // Move Constructor Not Implemented
   LaplacianSmoothing& operator=(const LaplacianSmoothing&) = delete; // Copy Assignment Not Implemented
   LaplacianSmoothing& operator=(LaplacianSmoothing&&) = delete;      // Move assignment Not Implemented
};

