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
 *                           FA8650-07-D-5800
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "VertexDataContainerReader.h"


#include "H5Support/QH5Utilities.h"
#include "H5Support/QH5Lite.h"

#include "DREAM3DLib/HDF5/VTKH5Constants.h"
#include "DREAM3DLib/HDF5/H5DataArrayReader.h"
#include "DREAM3DLib/DataArrays/StatsDataArray.h"
#include "DREAM3DLib/DataContainers/VertexDataContainer.h"
#include "DREAM3DLib/DataContainers/VertexArray.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
VertexDataContainerReader::VertexDataContainerReader() :
  IOSupport(),
  m_ReadVertexData(true),
  m_ReadVertexFeatureData(true),
  m_ReadVertexEnsembleData(true),
  m_ReadAllVertexArrays(false),
  m_ReadAllVertexFeatureArrays(false),
  m_ReadAllVertexEnsembleArrays(false)
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
VertexDataContainerReader::~VertexDataContainerReader()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void VertexDataContainerReader::dataCheck(bool preflight, size_t voxels, size_t features, size_t ensembles)
{
  setErrorCondition(0);

  // We are NOT going to check for NULL DataContainer because we are this far and the checks
  // have already happened. WHich is why this method is protected or private.
  VertexDataContainer* dc = VertexDataContainer::SafePointerDownCast(getDataContainer());

  if(NULL == dc)
  {
    setErrorCondition(-383);
    addErrorMessage(getHumanLabel(), "Vertex DataContainer is NULL", getErrorCondition());
    return;
  }
  if(getHdfGroupId() < 0)
  {
    setErrorCondition(-150);
    addErrorMessage(getHumanLabel(), "The HDF5 file id was < 0. This means this value was not set correctly from the calling object.", getErrorCondition());
  }
  else if (preflight == true)
  {
    if(m_VertexArraysToRead.size() == 0 && m_ReadAllVertexArrays != true) { m_ReadVertexData = false; }
    if(m_VertexFeatureArraysToRead.size() == 0 && m_ReadAllVertexFeatureArrays != true) { m_ReadVertexFeatureData = false; }
    if(m_VertexEnsembleArraysToRead.size() == 0 && m_ReadAllVertexEnsembleArrays != true) { m_ReadVertexEnsembleData = false; }

    if(m_ReadVertexData == true) { dc->clearVertexData(); }
    if(m_ReadVertexFeatureData == true) { dc->clearVertexFeatureData(); }
    if(m_ReadVertexEnsembleData == true) { dc->clearVertexEnsembleData(); }

    int err = gatherData(preflight);
    if (err < 0)
    {

    }
  }
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void VertexDataContainerReader::preflight()
{
  /* Place code here that sanity checks input arrays and input values. Look at some
  * of the other DREAM3DLib/Filters/.cpp files for sample codes */
  dataCheck(true, 1, 1, 1);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void VertexDataContainerReader::execute()
{
  int err = 0;
  // We are NOT going to check for NULL DataContainer because we are this far and the checks
  // have already happened. WHich is why this method is protected or private.
  VertexDataContainer* dc = VertexDataContainer::SafePointerDownCast(getDataContainer());
  if(NULL == dc)
  {
    setErrorCondition(-999);
    notifyErrorMessage("The DataContainer Object was NULL", -999);
    return;
  }

  setErrorCondition(err);

  if(m_VertexArraysToRead.size() == 0 && m_ReadAllVertexArrays != true) { m_ReadVertexData = false; }
  if(m_VertexFeatureArraysToRead.size() == 0 && m_ReadAllVertexFeatureArrays != true) { m_ReadVertexFeatureData = false; }
  if(m_VertexEnsembleArraysToRead.size() == 0 && m_ReadAllVertexEnsembleArrays != true) { m_ReadVertexEnsembleData = false; }

  if(m_ReadVertexData == true) { dc->clearVertexData(); }
  if(m_ReadVertexFeatureData == true) { dc->clearVertexFeatureData(); }
  if(m_ReadVertexEnsembleData == true) { dc->clearVertexEnsembleData(); }

  err = gatherData(false);
  setErrorCondition(err);

  /* Let the GUI know we are done with this filter */
  notifyStatusMessage("Complete");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void VertexDataContainerReader::setReadAllArrays()
{
  m_ReadAllVertexArrays = true;
  m_ReadAllVertexFeatureArrays = true;
  m_ReadAllVertexEnsembleArrays = true;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int VertexDataContainerReader::gatherData(bool preflight)
{


  if(getHdfGroupId() < 0)
  {
    QString ss = QObject::tr(": Error opening input file");
    setErrorCondition(-150);
    addErrorMessage(getHumanLabel(), ss, getErrorCondition());
    return -1;
  }

  hid_t dcGid = H5Gopen(getHdfGroupId(), getDataContainer()->getName().toLatin1().data(), H5P_DEFAULT );
  if (dcGid < 0)
  {
    QString ss = QObject::tr("Error opening Group %1").arg(DREAM3D::Defaults::VertexDataContainerName);
    setErrorCondition(-61);
    addErrorMessage(getHumanLabel(), ss, getErrorCondition());
    return -61;
  }

  int err = 0;

  readMeshData(dcGid, preflight);

  if(m_ReadVertexData == true)
  {
    QVector<QString> readNames;
    QSet<QString> vertexArraysToRead = getVertexArraysToRead();
    err |= readGroupsData(dcGid, H5_VERTEX_DATA_GROUP_NAME, preflight, readNames, vertexArraysToRead, m_ReadAllVertexArrays);
    if(err < 0)
    {
      err |= H5Gclose(dcGid);
      setErrorCondition(err);
      return -1;
    }
  }

  if(m_ReadVertexFeatureData == true)
  {
    QVector<QString> readNames;
    QSet<QString> vertexFeatureArraysToRead = getVertexFeatureArraysToRead();
    err |= readGroupsData(dcGid, H5_VERTEX_FIELD_DATA_GROUP_NAME, preflight, readNames, vertexFeatureArraysToRead, m_ReadAllVertexFeatureArrays);
    if(err < 0)
    {
      err |= H5Gclose(dcGid);
      setErrorCondition(err);
      return -1;
    }
  }

  if(m_ReadVertexEnsembleData == true)
  {
    QVector<QString> readNames;
    QSet<QString> vertexEnsembleArraysToRead = getVertexEnsembleArraysToRead();
    err |= readGroupsData(dcGid, H5_VERTEX_ENSEMBLE_DATA_GROUP_NAME, preflight, readNames, vertexEnsembleArraysToRead, m_ReadAllVertexEnsembleArrays);
    if(err < 0)
    {
      err |= H5Gclose(dcGid);
      setErrorCondition(err);
      return -1;
    }
  }

  // Now finally close the group
  err |= H5Gclose(dcGid); // Close the Data Container Group

  return err;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int VertexDataContainerReader::readMeshData(hid_t dcGid, bool preflight)
{
  // We are NOT going to check for NULL DataContainer because we are this far and the checks
  // have already happened. WHich is why this method is protected or private.
  VertexDataContainer* dc = VertexDataContainer::SafePointerDownCast(getDataContainer());

  int err = 0;
  QVector<hsize_t> dims;
  H5T_class_t type_class;
  size_t type_size;
  if (true == preflight)
  {
    err = QH5Lite::getDatasetInfo(dcGid, DREAM3D::HDF5::VerticesName, dims, type_class, type_size);
    if (err >= 0)
    {
      VertexArray::Pointer vertices = VertexArray::CreateArray(1, DREAM3D::VertexData::SurfaceMeshNodes);
      dc->setVertices(vertices);
    }
  }
  else
  {
    err = QH5Lite::getDatasetInfo(dcGid, DREAM3D::HDF5::VerticesName, dims, type_class, type_size);
    if (err >= 0)
    {
      // Allocate the Vertex_t structures
      VertexArray::Pointer verticesPtr = VertexArray::CreateArray(dims[0], DREAM3D::VertexData::SurfaceMeshNodes);
      // We need this to properly use QH5Lite because the data is stored as int32_t in 5 columns
      float* data = reinterpret_cast<float*>(verticesPtr->getPointer(0));
      // Read the data from the file
      err = QH5Lite::readPointerDataset(dcGid, DREAM3D::HDF5::VerticesName, data);
      if (err < 0)
      {
        setErrorCondition(err);
        notifyErrorMessage("Error Reading Vertex List from DREAM3D file", getErrorCondition());
        return err;
      }
      dc->setVertices(verticesPtr);
    }
  }
  return 1;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int VertexDataContainerReader::readGroupsData(hid_t dcGid, const QString& groupName, bool preflight,
                                              QVector<QString>& namesRead,
                                              QSet<QString>& namesToRead,
                                              bool readAllCurrentArrays)
{
  // We are NOT going to check for NULL DataContainer because we are this far and the checks
  // have already happened. WHich is why this method is protected or private.
  VertexDataContainer* dc = VertexDataContainer::SafePointerDownCast(getDataContainer());

  int err = 0;
  //Read the Cell Data
  hid_t gid = H5Gopen(dcGid, groupName.toLatin1().data(), H5P_DEFAULT);
  if(gid < 0)
  {
    return -154;
  }

  NameListType names;
  QH5Utilities::getGroupObjects(gid, H5Utilities::H5Support_DATASET | H5Utilities::H5Support_ANY, names);
  //  qDebug() << "Number of Items in " << groupName << " Group: " << names.size() << "\n";
  QString classType;
  for (NameListType::iterator iter = names.begin(); iter != names.end(); ++iter)
  {
    QSet<QString>::iterator contains = namesToRead.find(*iter);
    if (contains == namesToRead.end() && false == preflight && readAllCurrentArrays == false) { continue; } // Do not read this item if it is NOT in the set of arrays to read
    namesRead.push_back(*iter);
    classType.clear();
    QH5Lite::readStringAttribute(gid, *iter, DREAM3D::HDF5::ObjectType, classType);
    //   qDebug() << groupName << " Array: " << *iter << " with C++ ClassType of " << classType << "\n";
    IDataArray::Pointer dPtr = IDataArray::NullPointer();

    if(classType.startsWith("DataArray") == true)
    {
      dPtr = H5DataArrayReader::readIDataArray(gid, *iter, preflight);
    }
    else if(classType.compare("StringDataArray") == 0)
    {
      dPtr = H5DataArrayReader::readStringDataArray(gid, *iter, preflight);
    }
    else if(classType.compare("vector") == 0)
    {

    }
    else if(classType.compare("NeighborList<T>") == 0)
    {
      dPtr = H5DataArrayReader::readNeighborListData(gid, *iter, preflight);
    }
    else if ( (*iter).compare(DREAM3D::EnsembleData::Statistics) == 0)
    {
      StatsDataArray::Pointer statsData = StatsDataArray::New();
      statsData->SetName(DREAM3D::EnsembleData::Statistics);
      statsData->readH5Data(gid);
      dPtr = statsData;
    }

    if (NULL != dPtr.get())
    {
      if(groupName.compare(H5_VERTEX_DATA_GROUP_NAME) == 0)
      {
        dc->addVertexData(dPtr->GetName(), dPtr);
      }
      else if(groupName.compare(H5_VERTEX_FIELD_DATA_GROUP_NAME) == 0)
      {
        dc->addVertexFeatureData(dPtr->GetName(), dPtr);
      }
      else if(groupName.compare(H5_VERTEX_ENSEMBLE_DATA_GROUP_NAME) == 0)
      {
        dc->addVertexEnsembleData(dPtr->GetName(), dPtr);
      }
    }

  }
  H5Gclose(gid); // Close the Cell Group
  return err;
}
