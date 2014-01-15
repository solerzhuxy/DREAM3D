/*
 * Your License or Copyright Information can go here
 */

#include "GenericFilter.h"
#include "DREAM3DLib/HDF5/H5FilterParametersConstants.h"

#define StlFilePrefixDefaultValue "StlFilePrefixDefaultValue"
#define MaxIterationsDefaultValue 92
#define MisorientationToleranceDefaultValue 21
#define InputFileDefaultValue "InputFileDefaultValue.html"
#define InputPathDefaultValue "InputPathDefaultValue.html"
#define OutputFileDefaultValue "OutputFileDefaultValue.html"
#define OutputPathDefaultValue "OutputPathDefaultValue.html"
#define WriteAlignmentShiftsDefaultValue false
#define ConversionTypeDefaultValue 78
#define SelectedCellArrayNameDefaultValue "SelectedCellArrayNameDefaultValue"
#define SelectedFeatureArrayNameDefaultValue "SelectedFeatureArrayNameDefaultValue"
#define SelectedEnsembleArrayNameDefaultValue "SelectedEnsembleArrayNameDefaultValue"
#define SurfaceMeshPointArrayNameDefaultValue "SurfaceMeshPointArrayNameDefaultValue"
#define SurfaceMeshFaceArrayNameDefaultValue "SurfaceMeshFaceArrayNameDefaultValue"
#define SurfaceMeshEdgeArrayNameDefaultValue "SurfaceMeshEdgeArrayNameDefaultValue"
#define SolidMeshPointArrayNameDefaultValue "SolidMeshPointArrayNameDefaultValue"
#define SolidMeshFaceArrayNameDefaultValue "SolidMeshFaceArrayNameDefaultValue"
#define SolidMeshEdgeArrayNameDefaultValue "SolidMeshEdgeArrayNameDefaultValue"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
GenericFilter::GenericFilter() :
  AbstractFilter(),
  m_StlFilePrefix(""),
  m_MaxIterations(25),
  m_MisorientationTolerance(5.0),
  m_InputFile(""),
  m_InputPath(""),
  m_OutputFile(""),
  m_OutputPath(""),
  m_WriteAlignmentShifts(false),
  m_ConversionType(0),
{
  m_Dimensions.x = 0;
  m_Dimensions.y = 0;
  m_Dimensions.z = 0;

  m_Origin.x = 0.0;
  m_Origin.y = 0.0;
  m_Origin.z = 0.0;

  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
GenericFilter::~GenericFilter()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenericFilter::setupFilterParameters()
{
  QVector<FilterParameter::Pointer> options;
  /* Place all your option initialization code here */
  /* For String input use this code */
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("STL Output Prefix");
    option->setPropertyName("StlFilePrefix");
    option->setWidgetType(FilterParameterWidgetType::StringWidget);
    option->setValueType("string");
    options.push_back(option);
  }
  /*  For an Integer use this code*/
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Max Iterations");
    option->setPropertyName("MaxIterations");
    option->setWidgetType(FilterParameterWidgetType::IntWidget);
    option->setValueType("int");
    options.push_back(option);
  }
  /*  For a Floating point value use this code*/
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Misorientation Tolerance");
    option->setPropertyName("MisorientationTolerance");
    option->setWidgetType(FilterParameterWidgetType::DoubleWidget);
    option->setValueType("float");
    option->setCastableValueType("double");
    options.push_back(option);
  }
  /*   For an input file use this code*/
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Input File");
    option->setPropertyName("InputFile");
    option->setWidgetType(FilterParameterWidgetType::InputFileWidget);
    option->setValueType("string");
    options.push_back(option);
  }
  /*   For an input path use this code*/
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Input Path");
    option->setPropertyName("InputPath");
    option->setWidgetType(FilterParameterWidgetType::InputPathWidget);
    option->setValueType("string");
    options.push_back(option);
  }

  /*   For an output file use this code*/
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Output File");
    option->setPropertyName("OutputFile");
    option->setWidgetType(FilterParameterWidgetType::OutputFileWidget);
    option->setValueType("string");
    options.push_back(option);
  }
  /*   For an output path use this code*/
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Output Path");
    option->setPropertyName("OutputPath");
    option->setWidgetType(FilterParameterWidgetType::OutputPathWidget);
    option->setValueType("string");
    options.push_back(option);
  }
  /*   For a simple true/false boolean use this code*/
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Write Alignment Shift File");
    option->setPropertyName("WriteAlignmentShifts");
    option->setWidgetType(FilterParameterWidgetType::BooleanWidget);
    option->setValueType("bool");
    options.push_back(option);
  }
  /*   For presenting a set of choices to the user use this code*/
  {
    ChoiceFilterParameter::Pointer option = ChoiceFilterParameter::New();
    option->setHumanLabel("Conversion Type");
    option->setPropertyName("ConversionType");
    option->setWidgetType(FilterParameterWidgetType::ChoiceWidget);
    option->setValueType("unsigned int");
    QVector<QString> choices;
    choices.push_back("Degrees To Radians");
    choices.push_back("Radians To Degrees");
    option->setChoices(choices);
    options.push_back(option);
  }


  /* Display a group of 3 text boxes to collect 3 integer values */
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Dimensions");
    option->setPropertyName("Dimensions");
    option->setWidgetType(FilterParameterWidgetType::IntVec3Widget);
    option->setValueType("IntVec3Widget_t");
    option->setUnits("XYZ");
    options.push_back(option);
  }
  /* Display a group of 3 text boxes to collect 3 float values */
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Origin");
    option->setPropertyName("Origin");
    option->setWidgetType(FilterParameterWidgetType::FloatVec3Widget);
    option->setValueType("FloatVec3Widget_t");
    option->setUnits("XYZ");
    options.push_back(option);
  }


  /* To Display a Combobox with a list of current Voxel Cell Arrays in it */
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Voxel Cell Array Name");
    option->setPropertyName("SelectedVoxelCellArrayName");
    option->setWidgetType(FilterParameterWidgetType::VoxelCellArrayNameSelectionWidget);
    option->setValueType("string");
    option->setUnits("");
    options.push_back(option);
  }
  /* To Display a Combobox with a list of current Voxel Feature Arrays in it */
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Voxel Feature Array Name");
    option->setPropertyName("SelectedVoxelFeatureArrayName");
    option->setWidgetType(FilterParameterWidgetType::VoxelFeatureArrayNameSelectionWidget);
    option->setValueType("string");
    option->setUnits("");
    options.push_back(option);
  }
  /* To Display a Combobox with a list of current Voxel Ensemble Arrays in it */
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Voxel Ensemble Array Name");
    option->setPropertyName("SelectedVoxelEnsembleArrayName");
    option->setWidgetType(FilterParameterWidgetType::VoxelEnsembleArrayNameSelectionWidget);
    option->setValueType("string");
    option->setUnits("");
    options.push_back(option);
  }

  /* To Display a Combobox with a list of current SurfaceMesh Point Arrays in it */
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("SurfaceMesh Point Array Name");
    option->setPropertyName("SelectedSurfaceMeshPointArrayName");
    option->setWidgetType(FilterParameterWidgetType::SurfaceMeshVertexArrayNameSelectionWidget);
    option->setValueType("string");
    option->setUnits("");
    options.push_back(option);
  }
  /* To Display a Combobox with a list of current SurfaceMesh Face Arrays in it */
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("SurfaceMesh Face Array Name");
    option->setPropertyName("SelectedSurfaceMeshFaceArrayName");
    option->setWidgetType(FilterParameterWidgetType::SurfaceMeshFaceArrayNameSelectionWidget);
    option->setValueType("string");
    option->setUnits("");
    options.push_back(option);
  }
  /* To Display a Combobox with a list of current SurfaceMesh Edge Arrays in it */
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("SurfaceMesh Edge Array Name");
    option->setPropertyName("SelectedSurfaceMeshEdgeArrayName");
    option->setWidgetType(FilterParameterWidgetType::SurfaceMeshEdgeArrayNameSelectionWidget);
    option->setValueType("string");
    option->setUnits("");
    options.push_back(option);
  }

  /* To Display a Combobox with a list of current SolidMesh Point Arrays in it */
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("SolidMesh Point Array Name");
    option->setPropertyName("SelectedSolidMeshPointArrayName");
    option->setWidgetType(FilterParameterWidgetType::SolidMeshVertexArrayNameSelectionWidget);
    option->setValueType("string");
    option->setUnits("");
    options.push_back(option);
  }
  /* To Display a Combobox with a list of current SolidMesh Face Arrays in it */
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("SolidMesh Face Array Name");
    option->setPropertyName("SelectedSolidMeshFaceArrayName");
    option->setWidgetType(FilterParameterWidgetType::SolidMeshFaceArrayNameSelectionWidget);
    option->setValueType("string");
    option->setUnits("");
    options.push_back(option);
  }
  /* To Display a Combobox with a list of current SolidMesh Edge Arrays in it */
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("SolidMesh Edge Array Name");
    option->setPropertyName("SelectedSolidMeshEdgeArrayName");
    option->setWidgetType(FilterParameterWidgetType::SolidMeshEdgeArrayNameSelectionWidget);
    option->setValueType("string");
    option->setUnits("");
    options.push_back(option);
  }

  /* Display the AxisAngleWidget to collect Axis-Angle pairs from the user */
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Crystal Rotations");
    option->setPropertyName("AxisAngleRotations");
    option->setWidgetType(FilterParameterWidgetType::AxisAngleWidget);
    options.push_back(option);
  }
  /* To select arrays */
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Arrays to Delete");
    option->setPropertyName("ArraysToDelete");
    option->setWidgetType(FilterParameterWidgetType::ArraySelectionWidget);
    options.push_back(option);
  }

  setFilterParameters(options);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenericFilter::readFilterParameters(AbstractFilterParametersReader* reader, int index)
{
  reader->openFilterGroup(this, index);

  setStlFilePrefix( reader->readValue("StlFilePrefix", getStlFilePrefix()) );
  setMaxIterations( reader->readValue("MaxIterations", getMaxIterations()) );
  setMisorientationTolerance( reader->readValue("MisorientationTolerance", getMisorientationTolerance()) );
  setInputFile( reader->readValue("InputFile", getInputFile()) );
  setInputPath( reader->readValue("InputPath", getInputPath()) );
  setOutputFile( reader->readString("OutputFile", getOutputFile()) );
  setOutputPath( reader->readValue("OutputPath", getOutputPath()) );
  setWriteAlignmentShifts( reader->readValue("WriteAlignmentShifts", getWriteAlignmentShifts()) );
  setConversionType( reader->readValue("ConversionType", getConversionType()) );
  setDimensions( reader->readValue("Dimensions", getDimensions()) );
  setOrigin( reader->readValue("Origin", getOrigin()) );
  setTestAxisAngleRotations( reader->readValue("TestAxisAngleRotations", getTestAxisAngleRotations()) );

  setSelectedVoxelCellArrayName( reader->readValue("SelectedVoxelCellArrayName", getSelectedVoxelCellArrayName()) );
  setSelectedVoxelFeatureArrayName( reader->readValue("SelectedFeatureArrayName", getSelectedVoxelFeatureArrayName()) );
  setSelectedVoxelEnsembleArrayName( reader->readValue("SelectedEnsembleArrayName", getSelectedVoxelEnsembleArrayName()) );
  setSelectedSurfaceMeshPointArrayName( reader->readValue("SelectedSurfaceMeshPointArrayName", getSelectedSurfaceMeshPointArrayName()) );
  setSelectedSurfaceMeshFaceArrayName( reader->readValue("SelectedSurfaceMeshFaceArrayName", getSelectedSurfaceMeshFaceArrayName()) );
  setSelectedSurfaceMeshEdgeArrayName( reader->readValue("SelectedSurfaceMeshEdgeArrayName", getSelectedSurfaceMeshEdgeArrayName()) );
  setSelectedSolidMeshPointArrayName( reader->readValue("SelectedSolidMeshPointArrayName", getSelectedSolidMeshPointArrayName()) );
  setSelectedSolidMeshFaceArrayName( reader->readValue("SelectedSolidMeshFaceArrayName", getSelectedSolidMeshFaceArrayName()) );
  setSelectedSolidMeshEdgeArrayName( reader->readValue("SelectedSolidMeshEdgeArrayName", getSelectedSolidMeshEdgeArrayName()) );


  setStrVector( reader->readValue("StrVector", getStrVector() ) );
  reader->closeFilterGroup();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int GenericFilter::writeFilterParameters(AbstractFilterParametersWriter* writer, int index)
{
  writer->openFilterGroup(this, index);
  /* Place code that will write the inputs values into a file. reference the
   AbstractFilterParametersWriter class for the proper API to use. */
  writer->writeValue("StlFilePrefix", getStlFilePrefix());
  writer->writeValue("MaxIterations", getMaxIterations());
  writer->writeValue("MisorientationTolerance", getMisorientationTolerance());
  writer->writeValue("InputFile", getInputFile());
  writer->writeValue("InputPath", getInputPath());
  writer->writeValue("OutputFile", getOutputFile());
  writer->writeValue("OutputPath", getOutputPath());
  writer->writeValue("WriteAlignmentShifts", getWriteAlignmentShifts());
  writer->writeValue("ConversionType", getConversionType());
  writer->writeValue("Dimensions", getDimensions());
  writer->writeValue("Origin", getOrigin());
  writer->writeValue("TestAxisAngleRotations", getTestAxisAngleRotations());

  writer->writeValue("SelectedVoxelCellArrayName", getSelectedVoxelCellArrayName());
  writer->writeValue("SelectedFeatureArrayName", getSelectedVoxelFeatureArrayName());
  writer->writeValue("SelectedEnsembleArrayName", getSelectedVoxelEnsembleArrayName());
  writer->writeValue("SelectedSurfaceMeshPointArrayName", getSelectedSurfaceMeshPointArrayName());
  writer->writeValue("SelectedSurfaceMeshFaceArrayName", getSelectedSurfaceMeshFaceArrayName());
  writer->writeValue("SelectedSurfaceMeshEdgeArrayName", getSelectedSurfaceMeshEdgeArrayName());
  writer->writeValue("SelectedSolidMeshPointArrayName", getSelectedSolidMeshPointArrayName());
  writer->writeValue("SelectedSolidMeshFaceArrayName", getSelectedSolidMeshFaceArrayName());
  writer->writeValue("SelectedSolidMeshEdgeArrayName", getSelectedSolidMeshEdgeArrayName());

  writer->writeValue("StrVector", getStrVector());

  writer->closeFilterGroup();
  return ++index;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenericFilter::dataCheck()
{
  setErrorCondition(0);

  /* Example code for preflighting looking for a valid string for the output file
   * but not necessarily the fact that the file exists: Example code to make sure
   * we have something in a string before proceeding.*/
  /*
  if (m_OutputFile.empty() == true)
  {
    ss << "The output file must be set before executing this filter.";
    PipelineMessage em(getNameOfClass(), "There was an error", -666);
    addErrorMessage(em);
    setErrorCondition(-1);
  }
  */


}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenericFilter::preflight()
{
  /* Place code here that sanity checks input arrays and input values. Look at some
  * of the other DREAM3DLib/Filters/.cpp files for sample codes */
  dataCheck();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenericFilter::execute()
{
  int err = 0;
  setErrorCondition(err);
  VoxelDataContainer* m = getVoxelDataContainer();
  if(NULL == m)
  {
    setErrorCondition(-999);
    notifyErrorMessage(getHumanLabel(), "The DataContainer Object was NULL", getErrorCondition());
    return;
  }
  setErrorCondition(0);

  /* Place all your code to execute your filter here. */

  /* Let the GUI know we are done with this filter */
  notifyStatusMessage(getHumanLabel(), "Complete");
}
