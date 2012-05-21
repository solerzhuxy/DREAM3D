/* ============================================================================
 * Copyright (c) 2011 Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2011 Dr. Michael A. Groeber (US Air Force Research Laboratories)
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
 *                           FA8650-07-D-5800
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include <limits>
#include <vector>
#include <sstream>
#include "ReadH5Ebsd.h"


#include "EbsdLib/H5EbsdVolumeInfo.h"
#include "EbsdLib/H5EbsdVolumeReader.h"
#include "EbsdLib/TSL/AngDirectoryPatterns.h"
#include "EbsdLib/TSL/AngFields.h"
#include "EbsdLib/TSL/H5AngVolumeReader.h"
#include "EbsdLib/HKL/H5CtfVolumeReader.h"
#include "EbsdLib/HKL/CtfFields.h"

#include "DREAM3DLib/Common/Constants.h"
#include "DREAM3DLib/Common/DREAM3DMath.h"
#include "DREAM3DLib/Common/DREAM3DRandom.h"

#include "DREAM3DLib/GenericFilters/DetermineGoodVoxels.h"


#define ERROR_TXT_OUT 1
#define ERROR_TXT_OUT1 1

const static float m_pi = M_PI;



#define NEW_SHARED_ARRAY(var, type, size)\
  boost::shared_array<type> var##Array(new type[size]);\
  type* var = var##Array.get();

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ReadH5Ebsd::ReadH5Ebsd() :
AbstractFilter(),
m_CellEulerAnglesArrayName(DREAM3D::CellData::EulerAngles),
m_CellPhasesArrayName(DREAM3D::CellData::Phases),
m_GoodVoxelsArrayName(DREAM3D::CellData::GoodVoxels),
m_CrystalStructuresArrayName(DREAM3D::EnsembleData::CrystalStructures),
m_H5EbsdFile(""),
m_RefFrameZDir(Ebsd::UnknownRefFrameZDirection),
m_ZStartIndex(0),
m_ZEndIndex(0),
m_Manufacturer(Ebsd::UnknownManufacturer),
m_CellPhases(NULL),
m_GoodVoxels(NULL),
m_CellEulerAngles(NULL)
{
 // Seed = MXA::getMilliSeconds();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ReadH5Ebsd::~ReadH5Ebsd()
{
}

// -----------------------------------------------------------------------------
void ReadH5Ebsd::writeFilterOptions(AbstractFilterOptionsWriter* writer)
{

  writer->writeValue("H5EbsdFile", getH5EbsdFile() );
  writer->writeValue("ZStartIndex", getZStartIndex() );
  writer->writeValue("ZEndIndex", getZEndIndex() );
  int numQFilters = getQualityMetricFilters().size();
  writer->writeValue("NumQualityFilters",  numQFilters);
  std::stringstream ss;
  for(size_t i = 0; i < getQualityMetricFilters().size(); i++)
  {
	ss << "QualityMetricFilter-" << i;
	writer->writeValue(ss.str(), m_QualityMetricFilters[i].get());
	ss.str("");
  }
  int numPhaseType = m_PhaseTypes->GetNumberOfTuples();
  writer->writeValue("NumPhaseTypes", numPhaseType);
  for(int i = 0; i < numPhaseType; ++i)
  {
    ss << "PhaseType-" << i;
    writer->writeValue(ss.str(), m_PhaseTypes->GetValue(i));
    ss.str("");
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int ReadH5Ebsd::initDataContainerDimsRes(int64_t dims[3], DataContainer* m)
{
  int err = 0;
  /* Sanity check what we are trying to load to make sure it can fit in our address space.
   * Note that this does not guarantee the user has enough left, just that the
   * size of the volume can fit in the address space of the program
   */
#if   (CMP_SIZEOF_SSIZE_T==4)
  int64_t max = std::numeric_limits<size_t>::max();
#else
  int64_t max = std::numeric_limits<int64_t>::max();
#endif
  if(dims[0] * dims[1] * dims[2] > max)
  {
    err = -1;
    std::stringstream s;
    s << "The total number of elements '" << (dims[0] * dims[1] * dims[2]) << "' is greater than this program can hold. Try the 64 bit version.";
    setErrorCondition(err);
    setErrorMessage(s.str());
    return err;
  }

  if(dims[0] > max || dims[1] > max || dims[2] > max)
  {
    err = -1;
    std::stringstream s;
    s << "One of the dimensions is greater than the max index for this sysem. Try the 64 bit version.";
    s << " dim[0]=" << dims[0] << "  dim[1]=" << dims[1] << "  dim[2]=" << dims[2];
    setErrorCondition(err);
    setErrorMessage(s.str());
    return err;
  }
  return err;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ReadH5Ebsd::dataCheck(bool preflight, size_t voxels, size_t fields, size_t ensembles)
{
  setErrorCondition(0);
  std::stringstream ss;
  DataContainer* m = getDataContainer();

  if (m_H5EbsdFile.empty() == true && m_Manufacturer == Ebsd::UnknownManufacturer)
  {
    ss << getHumanLabel() << ": Either the H5Ebsd file must exist or the Manufacturer must be set";
    setErrorCondition(-1);
    setErrorMessage(ss.str());
  }
  else if (m_H5EbsdFile.empty() == false)
  {
    H5EbsdVolumeInfo::Pointer reader = H5EbsdVolumeInfo::New();
    reader->setFileName(m_H5EbsdFile);
    int err = reader->readVolumeInfo();
    if (err < 0)
    {
      ss << getHumanLabel() << ": Error reading VolumeInfo from H5Ebsd File";
      setErrorCondition(-1);
      setErrorMessage(ss.str());
      return;
    }

    std::string manufacturer = reader->getManufacturer();
    if(manufacturer.compare(Ebsd::Ang::Manufacturer) == 0)
    {
      m_Manufacturer = Ebsd::TSL;
    }
    else if(manufacturer.compare(Ebsd::Ctf::Manufacturer) == 0)
    {
      m_Manufacturer = Ebsd::HKL;
    }
    else
    {
      ss << getHumanLabel() << ": Original Data source could not be determined. It should be TSL or HKL";
      setErrorCondition(-1);
      setErrorMessage(ss.str());
      return;
    }
  }

  H5EbsdVolumeReader::Pointer reader;
  std::vector<std::string> names;

  if (m_Manufacturer == Ebsd::TSL)
  {
    AngFields fields;
    reader = H5AngVolumeReader::New();
	names = fields.getFilterFields<std::vector<std::string> >();
  }
  else if (m_Manufacturer == Ebsd::HKL)
  {
    CtfFields fields;
    reader = H5CtfVolumeReader::New();
    names = fields.getFilterFields<std::vector<std::string> >();
  }
  else
  {
    ss << getHumanLabel() << ": Original Data source could not be determined. It should be TSL or HKL";
    setErrorCondition(-1);
    setErrorMessage(ss.str());
    return;
  }

  for (size_t i = 0; i < names.size(); ++i)
  {
    if (reader->getPointerType(names[i]) == Ebsd::Int32)
    {
      Int32ArrayType::Pointer array = Int32ArrayType::CreateArray(voxels, names[i]);
      m->addCellData(names[i], array);
    }
    else if (reader->getPointerType(names[i]) == Ebsd::Float)
    {
      FloatArrayType::Pointer array = FloatArrayType::CreateArray(voxels, names[i]);
      m->addCellData(names[i], array);
    }
  }

  CREATE_NON_PREREQ_DATA(m, DREAM3D, CellData, GoodVoxels, ss, bool, BoolArrayType, false, voxels, 1);
  CREATE_NON_PREREQ_DATA(m, DREAM3D, CellData, CellEulerAngles, ss, float, FloatArrayType, 0, voxels, 3);
  CREATE_NON_PREREQ_DATA(m, DREAM3D, CellData, CellPhases, ss, int32_t, Int32ArrayType, 0, voxels, 1);

  typedef DataArray<unsigned int> XTalStructArrayType;
  CREATE_NON_PREREQ_DATA(m, DREAM3D, EnsembleData, CrystalStructures, ss, unsigned int, XTalStructArrayType, Ebsd::CrystalStructure::UnknownCrystalStructure, ensembles, 1);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ReadH5Ebsd::preflight()
{
  dataCheck(true, 1, 1, 1);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ReadH5Ebsd::execute()
{
  std::stringstream ss;
  DataContainer* m = getDataContainer();
  if(NULL == m)
  {
    setErrorCondition(-1);
    ss << getNameOfClass() << " DataContainer was NULL";
    setErrorMessage(ss.str());
    return;
  }
  int err = 0;
  setErrorCondition(err);
  std::string manufacturer;
  // Get the Size and Resolution of the Volume
  {
    H5EbsdVolumeInfo::Pointer volumeInfoReader = H5EbsdVolumeInfo::New();
    volumeInfoReader->setFileName(m_H5EbsdFile);
    err = volumeInfoReader->readVolumeInfo();
    setErrorCondition(err);
    int64_t dims[3];
    float res[3];
    volumeInfoReader->getDimsAndResolution(dims[0], dims[1], dims[2], res[0], res[1], res[2]);
    /* Sanity check what we are trying to load to make sure it can fit in our address space.
     * Note that this does not guarantee the user has enough left, just that the
     * size of the volume can fit in the address space of the program
     */
#if   (CMP_SIZEOF_SSIZE_T==4)
    int64_t max = std::numeric_limits<size_t>::max();
#else
    int64_t max = std::numeric_limits<int64_t>::max();
#endif
    if(dims[0] * dims[1] * dims[2] > max)
    {
      err = -1;
      std::stringstream s;
      s << "The total number of elements '" << (dims[0] * dims[1] * dims[2]) << "' is greater than this program can hold. Try the 64 bit version.";
      setErrorCondition(err);
      setErrorMessage(s.str());
      return;
    }

    if(dims[0] > max || dims[1] > max || dims[2] > max)
    {
      err = -1;
      std::stringstream s;
      s << "One of the dimensions is greater than the max index for this sysem. Try the 64 bit version.";
      s << " dim[0]=" << dims[0] << "  dim[1]=" << dims[1] << "  dim[2]=" << dims[2];
      setErrorCondition(err);
      setErrorMessage(s.str());
      return;
    }
    /* ************ End Sanity Check *************************** */
    size_t dcDims[3] =
    { dims[0], dims[1], dims[2] };
    m->setDimensions(dcDims);
    m->setResolution(res);
    //Now Calculate our "subvolume" of slices, ie, those start and end values that the user selected from the GUI
    dcDims[2] = m_ZEndIndex - m_ZStartIndex + 1;
    m->setDimensions(dcDims);
    manufacturer = volumeInfoReader->getManufacturer();
    volumeInfoReader = H5EbsdVolumeInfo::NullPointer();
  }
  H5EbsdVolumeReader::Pointer ebsdReader;
  if(manufacturer.compare(Ebsd::Ang::Manufacturer) == 0)
  {
    ebsdReader = H5AngVolumeReader::New();
    if(NULL == ebsdReader)
    {
      setErrorCondition(-1);
      setErrorMessage("Could not Create H5AngVolumeReader object.");
      return;
    }
    H5AngVolumeReader* angReader = dynamic_cast<H5AngVolumeReader*>(ebsdReader.get());
    err = loadInfo<H5AngVolumeReader, AngPhase>(angReader);
    if(err < 0)
    {
      setErrorCondition(-1);
      setErrorMessage("Could not read information about the Ebsd Volume.");
      return;
    }
  }
  else if(manufacturer.compare(Ebsd::Ctf::Manufacturer) == 0)
  {
    ebsdReader = H5CtfVolumeReader::New();
    if(NULL == ebsdReader)
    {
      setErrorCondition(-1);
      setErrorMessage("Could not Create H5CtfVolumeReader object.");
      return;
    }
    H5CtfVolumeReader* ctfReader = dynamic_cast<H5CtfVolumeReader*>(ebsdReader.get());
    err = loadInfo<H5CtfVolumeReader, CtfPhase>(ctfReader);
    if(err < 0)
    {
      setErrorCondition(-1);
      setErrorMessage("Could not read information about the Ebsd Volume.");
      return;
    }
  }
  else
  {
    setErrorCondition(-1);
    std::string msg("Could not determine or match a supported manufacturer from the data file.");
    msg = msg.append("Supported manufacturer codes are: ").append(Ebsd::Ctf::Manufacturer);
    msg = msg.append(" and ").append(Ebsd::Ang::Manufacturer);
    setErrorMessage(msg);
    return;
  }

  // This will create the arrays with the correct sizes
//  dataCheck(false, m->getTotalPoints(), m->getNumFieldTuples(), m->getNumEnsembleTuples());
  if(getErrorCondition() < 0)
  {
    return;
  }

  // Initialize all the arrays with some default values
  int64_t totalPoints = m->getTotalPoints();
  ss.str("");
  ss << getHumanLabel() << " - Initializing " << totalPoints << " voxels";
  notify(ss.str(), 0, Observable::UpdateProgressMessage);

  ss.str("");
  ss << getHumanLabel() << " - Reading Ebsd Data from file";
  notify(ss.str(), 0, Observable::UpdateProgressMessage);
  ebsdReader->setSliceStart(m_ZStartIndex);
  ebsdReader->setSliceEnd(m_ZEndIndex);
  err = ebsdReader->loadData(m->getXPoints(), m->getYPoints(), m->getZPoints(), m_RefFrameZDir);
  if(err < 0)
  {
    setErrorCondition(err);
    setErrorMessage("Error Loading Data from Ebsd Data file.");
    return;
  }

  float* f1 = NULL;
  float* f2 = NULL;
  float* f3 = NULL;
  int* phasePtr = NULL;


  if(manufacturer.compare(Ebsd::Ang::Manufacturer) == 0)
  {
    f1 = reinterpret_cast<float*>(ebsdReader->getPointerByName(Ebsd::Ang::Phi1));
    f2 = reinterpret_cast<float*>(ebsdReader->getPointerByName(Ebsd::Ang::Phi));
    f3 = reinterpret_cast<float*>(ebsdReader->getPointerByName(Ebsd::Ang::Phi2));
    FloatArrayType::Pointer fArray = FloatArrayType::CreateArray(totalPoints * 3, DREAM3D::CellData::EulerAngles);
    float* cellEulerAngles = fArray->GetPointer(0);

    for (int64_t i = 0; i < totalPoints; i++)
    {
      cellEulerAngles[3 * i] = f1[i] ;
      cellEulerAngles[3 * i + 1] = f2[i];
      cellEulerAngles[3 * i + 2] = f3[i];
    }
    m->addCellData(DREAM3D::CellData::EulerAngles, fArray);

    f1 = reinterpret_cast<float*>(ebsdReader->getPointerByName(Ebsd::Ang::ImageQuality));
    fArray = FloatArrayType::CreateArray(totalPoints, Ebsd::Ang::ImageQuality);
    ::memcpy(fArray->GetPointer(0), f1, sizeof(float) * totalPoints);
    m->addCellData(Ebsd::Ang::ImageQuality, fArray);

    f1 = reinterpret_cast<float*>(ebsdReader->getPointerByName(Ebsd::Ang::ConfidenceIndex));
    fArray = FloatArrayType::CreateArray(totalPoints, Ebsd::Ang::ConfidenceIndex);
    ::memcpy(fArray->GetPointer(0), f1, sizeof(float) * totalPoints);
    m->addCellData(Ebsd::Ang::ConfidenceIndex, fArray);

    phasePtr = reinterpret_cast<int*>(ebsdReader->getPointerByName(Ebsd::Ang::PhaseData));
    Int32ArrayType::Pointer iArray = Int32ArrayType::CreateArray(totalPoints, Ebsd::Ang::PhaseData);
    ::memcpy(iArray->GetPointer(0), phasePtr, sizeof(int32_t) * totalPoints);
    m->addCellData(DREAM3D::CellData::Phases, iArray);

    f1 = reinterpret_cast<float*>(ebsdReader->getPointerByName(Ebsd::Ang::SEMSignal));
    fArray = FloatArrayType::CreateArray(totalPoints, Ebsd::Ang::SEMSignal);
    ::memcpy(fArray->GetPointer(0), f1, sizeof(float) * totalPoints);
    m->addCellData(Ebsd::Ang::SEMSignal, fArray);

    f1 = reinterpret_cast<float*>(ebsdReader->getPointerByName(Ebsd::Ang::Fit));
    fArray = FloatArrayType::CreateArray(totalPoints, Ebsd::Ang::Fit);
    ::memcpy(fArray->GetPointer(0), f1, sizeof(float) * totalPoints);
    m->addCellData(Ebsd::Ang::Fit, fArray);
  }
  else if(manufacturer.compare(Ebsd::Ctf::Manufacturer) == 0)
  {
  //  radianconversion = M_PI / 180.0;
    f1 = reinterpret_cast<float*>(ebsdReader->getPointerByName(Ebsd::Ctf::Euler1));
    f2 = reinterpret_cast<float*>(ebsdReader->getPointerByName(Ebsd::Ctf::Euler2));
    f3 = reinterpret_cast<float*>(ebsdReader->getPointerByName(Ebsd::Ctf::Euler3));
    FloatArrayType::Pointer fArray = FloatArrayType::CreateArray(totalPoints * 3, DREAM3D::CellData::EulerAngles);
    float* cellEulerAngles = fArray->GetPointer(0);

    for (int64_t i = 0; i < totalPoints; i++)
    {
      cellEulerAngles[3 * i] = f1[i] ;
      cellEulerAngles[3 * i + 1] = f2[i];
      cellEulerAngles[3 * i + 2] = f3[i];
    }
    m->addCellData(DREAM3D::CellData::EulerAngles, fArray);

    phasePtr = reinterpret_cast<int*>(ebsdReader->getPointerByName(Ebsd::Ctf::Phase));
    Int32ArrayType::Pointer iArray = Int32ArrayType::CreateArray(totalPoints, Ebsd::Ctf::Phase);
    ::memcpy(iArray->GetPointer(0), phasePtr, sizeof(int32_t) * totalPoints);
    m->addCellData(DREAM3D::CellData::Phases, iArray);

    phasePtr = reinterpret_cast<int*>(ebsdReader->getPointerByName(Ebsd::Ctf::Bands));
    iArray = Int32ArrayType::CreateArray(totalPoints, Ebsd::Ctf::Bands);
    ::memcpy(iArray->GetPointer(0), phasePtr, sizeof(int32_t) * totalPoints);
    m->addCellData(Ebsd::Ctf::Bands, iArray);

    phasePtr = reinterpret_cast<int*>(ebsdReader->getPointerByName(Ebsd::Ctf::Error));
    iArray = Int32ArrayType::CreateArray(totalPoints, Ebsd::Ctf::Error);
    ::memcpy(iArray->GetPointer(0), phasePtr, sizeof(int32_t) * totalPoints);
    m->addCellData(Ebsd::Ctf::Error, iArray);

    f1 = reinterpret_cast<float*>(ebsdReader->getPointerByName(Ebsd::Ctf::MAD));
    fArray = FloatArrayType::CreateArray(totalPoints, Ebsd::Ctf::MAD);
    ::memcpy(fArray->GetPointer(0), f1, sizeof(float) * totalPoints);
    m->addCellData(Ebsd::Ctf::MAD, fArray);

    phasePtr = reinterpret_cast<int*>(ebsdReader->getPointerByName(Ebsd::Ctf::BC));
	iArray = Int32ArrayType::CreateArray(totalPoints, Ebsd::Ctf::BC);
    ::memcpy(iArray->GetPointer(0), phasePtr, sizeof(int32_t) * totalPoints);
	m->addCellData(Ebsd::Ctf::BC, iArray);

	phasePtr = reinterpret_cast<int*>(ebsdReader->getPointerByName(Ebsd::Ctf::BS));
	iArray = Int32ArrayType::CreateArray(totalPoints, Ebsd::Ctf::BS);
    ::memcpy(iArray->GetPointer(0), phasePtr, sizeof(int32_t) * totalPoints);
	m->addCellData(Ebsd::Ctf::BS, iArray);
  }
  else
  {
    std::string msg("Could not determine or match a supported manufacturer from the data file.");
    msg = msg.append("Supported manufacturer codes are: ").append(Ebsd::Ctf::Manufacturer);
    msg = msg.append(" and ").append(Ebsd::Ang::Manufacturer);
    setErrorMessage(msg);
    return;
  }

  CREATE_NON_PREREQ_DATA(m, DREAM3D, CellData, GoodVoxels, ss, bool, BoolArrayType, false, totalPoints, 1);

  // Run the filter to determine the good Voxels
  DetermineGoodVoxels::Pointer filter = DetermineGoodVoxels::New();
  filter->setQualityMetricFilters(m_QualityMetricFilters);
  filter->setObservers(getObservers());
  filter->setMessagePrefix(getMessagePrefix());
  filter->setEbsdVolumeReader(ebsdReader);
  filter->setDataContainer(m);
  filter->execute();
  err = filter->getErrorCondition();
  if(err < 0)
  {
    setErrorCondition(err);
    setErrorMessage("Error Filtering Ebsd Data.");
    return;
  }
  filter = DetermineGoodVoxels::NullPointer(); // Clean up some memory

  // If there is an error set this to something negative and also set a message
  ss.str("");
  ss << getHumanLabel() << " Completed";
  notify(ss.str(), 0, Observable::UpdateProgressMessage);
}
