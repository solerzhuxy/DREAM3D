/* ============================================================================
 * Copyright (c) 2012 Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2012 Dr. Michael A. Groeber (US Air Force Research Laboratories)
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
 * Neither the name of Michael A. Groeber, Michael A. Jackson, the US Air Force,
 * BlueQuartz Software nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written
 * permission.
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
 *  This code was written under United States Air Force Contract number
 *                           FA8650-10-D-5210
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#ifndef _GenericExample_H_
#define _GenericExample_H_

#include <QtCore/QString>

#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/DREAM3DSetGetMacros.h"
#include "DREAM3DLib/DataArrays/IDataArray.h"
#include "DREAM3DLib/Common/AbstractFilter.h"


/**
 * @class GenericExample GenericExample.h ExamplePlugin/Code/ExamplePluginFilters/GenericExample.h
 * @brief
 * @author
 * @date
 * @version 1.0
 */
class DREAM3DLib_EXPORT GenericExample : public AbstractFilter
{
    Q_OBJECT /* Need this for Qt's signals and slots mechanism to work */
  public:
    DREAM3D_SHARED_POINTERS(GenericExample)
    DREAM3D_STATIC_NEW_MACRO(GenericExample)
    DREAM3D_TYPE_MACRO_SUPER(GenericExample, AbstractFilter)

    virtual ~GenericExample();

    DREAM3D_INSTANCE_STRING_PROPERTY(DataContainerName)
    DREAM3D_INSTANCE_STRING_PROPERTY(CellAttributeMatrixName)


    /* Place your input parameters here. You can use some of the DREAM3D Macros if you want to */
    DREAM3D_INSTANCE_STRING_PROPERTY(StlFilePrefix)
    Q_PROPERTY(QString StlFilePrefix READ getStlFilePrefix WRITE setStlFilePrefix NOTIFY parametersChanged)
    DREAM3D_INSTANCE_PROPERTY(int, MaxIterations)
    Q_PROPERTY(int MaxIterations READ getMaxIterations WRITE setMaxIterations NOTIFY parametersChanged)
    DREAM3D_INSTANCE_PROPERTY(double, MisorientationTolerance)
    DREAM3D_INSTANCE_STRING_PROPERTY(InputFile)
    Q_PROPERTY(QString InputFile READ getInputFile WRITE setInputFile NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(InputPath)
    Q_PROPERTY(QString InputPath READ getInputPath WRITE setInputPath NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(OutputFile)
    Q_PROPERTY(QString OutputFile READ getOutputFile WRITE setOutputFile NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(OutputPath)
    Q_PROPERTY(QString OutputPath READ getOutputPath WRITE setOutputPath NOTIFY parametersChanged)
    DREAM3D_INSTANCE_PROPERTY(bool, WriteAlignmentShifts)
    Q_PROPERTY(bool WriteAlignmentShifts READ getWriteAlignmentShifts WRITE setWriteAlignmentShifts NOTIFY parametersChanged)
    DREAM3D_INSTANCE_PROPERTY(int, ConversionType)

    DREAM3D_INSTANCE_PROPERTY(IntVec3_t, Dimensions)
    Q_PROPERTY(IntVec3_t Dimensions READ getDimensions WRITE setDimensions NOTIFY parametersChanged)
    DREAM3D_INSTANCE_PROPERTY(FloatVec3_t, Origin)
    Q_PROPERTY(FloatVec3_t Origin READ getOrigin WRITE setOrigin NOTIFY parametersChanged)

    DREAM3D_INSTANCE_PROPERTY(QVector<AxisAngleInput_t>, AxisAngleInputs)

    DREAM3D_INSTANCE_PROPERTY(QVector<QString>, StrVector)

    DREAM3D_INSTANCE_PROPERTY(QVector<int8_t>, Int8Array)
    DREAM3D_INSTANCE_PROPERTY(QVector<int16_t>, Int16Array)
    DREAM3D_INSTANCE_PROPERTY(QVector<int32_t>, Int32Array)
    DREAM3D_INSTANCE_PROPERTY(QVector<int64_t>, Int64Array)
    DREAM3D_INSTANCE_PROPERTY(QVector<uint8_t>, UInt8Array)
    DREAM3D_INSTANCE_PROPERTY(QVector<uint16_t>, UInt16Array)
    DREAM3D_INSTANCE_PROPERTY(QVector<uint32_t>, UInt32Array)
    DREAM3D_INSTANCE_PROPERTY(QVector<uint64_t>, UInt64Array)
    DREAM3D_INSTANCE_PROPERTY(QVector<float>, FloatArray)
    DREAM3D_INSTANCE_PROPERTY(QVector<double>, DoubleArray)

    DREAM3D_INSTANCE_PROPERTY(int8_t, Int8Value)
    DREAM3D_INSTANCE_PROPERTY(int16_t, Int16Value)
    DREAM3D_INSTANCE_PROPERTY(int32_t, Int32Value)
    DREAM3D_INSTANCE_PROPERTY(int64_t, Int64Value)
    DREAM3D_INSTANCE_PROPERTY(uint8_t, UInt8Value)
    DREAM3D_INSTANCE_PROPERTY(uint16_t, UInt16Value)
    DREAM3D_INSTANCE_PROPERTY(uint32_t, UInt32Value)
    DREAM3D_INSTANCE_PROPERTY(uint64_t, UInt64Value)
    DREAM3D_INSTANCE_PROPERTY(float, FloatValue)
    DREAM3D_INSTANCE_PROPERTY(double, DoubleValue)


    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedVolumeVertexArrayName)
    Q_PROPERTY(QString SelectedVolumeVertexArrayName READ getSelectedVolumeVertexArrayName WRITE setSelectedVolumeVertexArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedVolumeEdgeArrayName)
    Q_PROPERTY(QString SelectedVolumeEdgeArrayName READ getSelectedVolumeEdgeArrayName WRITE setSelectedVolumeEdgeArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedVolumeFaceArrayName)
    Q_PROPERTY(QString SelectedVolumeFaceArrayName READ getSelectedVolumeFaceArrayName WRITE setSelectedVolumeFaceArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedVolumeCellArrayName)
    Q_PROPERTY(QString SelectedVolumeCellArrayName READ getSelectedVolumeCellArrayName WRITE setSelectedVolumeCellArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedVolumeFeatureArrayName)
    Q_PROPERTY(QString SelectedVolumeFeatureArrayName READ getSelectedVolumeFeatureArrayName WRITE setSelectedVolumeFeatureArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedVolumeEnsembleArrayName)
    Q_PROPERTY(QString SelectedVolumeEnsembleArrayName READ getSelectedVolumeEnsembleArrayName WRITE setSelectedVolumeEnsembleArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedSurfaceVertexArrayName)
    Q_PROPERTY(QString SelectedSurfaceVertexArrayName READ getSelectedSurfaceVertexArrayName WRITE setSelectedSurfaceVertexArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedSurfaceEdgeArrayName)
    Q_PROPERTY(QString SelectedSurfaceEdgeArrayName READ getSelectedSurfaceEdgeArrayName WRITE setSelectedSurfaceEdgeArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedSurfaceFaceArrayName)
    Q_PROPERTY(QString SelectedSurfaceFaceArrayName READ getSelectedSurfaceFaceArrayName WRITE setSelectedSurfaceFaceArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedSurfaceFeatureArrayName)
    Q_PROPERTY(QString SelectedSurfaceFeatureArrayName READ getSelectedSurfaceFeatureArrayName WRITE setSelectedSurfaceFeatureArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedSurfaceEnsembleArrayName)
    Q_PROPERTY(QString SelectedSurfaceEnsembleArrayName READ getSelectedSurfaceEnsembleArrayName WRITE setSelectedSurfaceEnsembleArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedEdgeVertexArrayName)
    Q_PROPERTY(QString SelectedEdgeVertexArrayName READ getSelectedEdgeVertexArrayName WRITE setSelectedEdgeVertexArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedEdgeEdgeArrayName)
    Q_PROPERTY(QString SelectedEdgeEdgeArrayName READ getSelectedEdgeEdgeArrayName WRITE setSelectedEdgeEdgeArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedEdgeFeatureArrayName)
    Q_PROPERTY(QString SelectedEdgeFeatureArrayName READ getSelectedEdgeFeatureArrayName WRITE setSelectedEdgeFeatureArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedEdgeEnsembleArrayName)
    Q_PROPERTY(QString SelectedEdgeEnsembleArrayName READ getSelectedEdgeEnsembleArrayName WRITE setSelectedEdgeEnsembleArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedVertexVertexArrayName)
    Q_PROPERTY(QString SelectedVertexVertexArrayName READ getSelectedVertexVertexArrayName WRITE setSelectedVertexVertexArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedVertexFeatureArrayName)
    Q_PROPERTY(QString SelectedVertexFeatureArrayName READ getSelectedVertexFeatureArrayName WRITE setSelectedVertexFeatureArrayName NOTIFY parametersChanged)
    DREAM3D_INSTANCE_STRING_PROPERTY(SelectedVertexEnsembleArrayName)
    Q_PROPERTY(QString SelectedVertexEnsembleArrayName READ getSelectedVertexEnsembleArrayName WRITE setSelectedVertexEnsembleArrayName NOTIFY parametersChanged)


    /**
    * @brief This returns the group that the filter belonds to. You can select
    * a different group if you want. The string returned here will be displayed
    * in the GUI for the filter
    */
    virtual const QString getGroupName() { return DREAM3D::FilterGroups::TestFilters; }

    /**
    * @brief This returns a string that is displayed in the GUI. It should be readable
    * and understandable by humans.
    */
    virtual const QString getHumanLabel() { return "GenericExample"; }

    /**
    * @brief This returns a string that is displayed in the GUI and helps to sort the filters into
    * a subgroup. It should be readable and understandable by humans.
    */
    virtual const QString getSubGroupName() { return "Misc"; }

    /**
    * @brief This method will instantiate all the end user settable options/parameters
    * for this filter
    */
    virtual void setupFilterParameters();

    /**
    * @brief This method will write the options to a file
    * @param writer The writer that is used to write the options to a file
    */
    virtual int writeFilterParameters(AbstractFilterParametersWriter* writer, int index);

    /**
    * @brief This method will read the options from a file
    * @param reader The reader that is used to read the options from a file
    */
    virtual void readFilterParameters(AbstractFilterParametersReader* reader, int index);

    /**
     * @brief Reimplemented from @see AbstractFilter class
     */
    virtual void execute();

    /**
    * @brief This function runs some sanity checks on the DataContainer and inputs
    * in an attempt to ensure the filter can process the inputs.
    */
    virtual void preflight();

  signals:
    void parametersChanged();
    void preflightAboutToExecute();
    void preflightExecuted();

  protected:
    GenericExample();

    /**
    * @brief Checks for the appropriate parameter values and availability of
    * arrays in the data container
    * @param preflight
    * @param voxels The number of voxels
    * @param features The number of features
    * @param ensembles The number of ensembles
    */
    void dataCheck();

    // This is just here for testing purpose.
    void dataCheck2();

  private:
    DEFINE_PTR_WEAKPTR_DATAARRAY(int32_t, FeatureIds)
    DEFINE_PTR_WEAKPTR_DATAARRAY(float, CellPatternQuality)
    DEFINE_PTR_WEAKPTR_DATAARRAY(float, CellEulerAngles)
    DEFINE_PTR_WEAKPTR_DATAARRAY(bool, GoodVoxels)

    GenericExample(const GenericExample&); // Copy Constructor Not Implemented
    void operator=(const GenericExample&); // Operator '=' Not Implemented
};

#endif /* _GenericExample_H_ */

