/* ============================================================================
* Copyright (c) 2009-2015 BlueQuartz Software, LLC
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


#ifndef _FindRelativeMotionBetweenSlices_H_
#define _FindRelativeMotionBetweenSlices_H_

#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/AbstractFilter.h"
#include "DREAM3DLib/Common/DREAM3DSetGetMacros.h"

/**
 * @brief The FindRelativeMotionBetweenSlices class. See [Filter documentation](@ref findrelativemotionbetweenslices) for details.
 */
class FindRelativeMotionBetweenSlices : public AbstractFilter
{
    Q_OBJECT /* Need this for Qt's signals and slots mechanism to work */
  public:
    DREAM3D_SHARED_POINTERS(FindRelativeMotionBetweenSlices)
    DREAM3D_STATIC_NEW_MACRO(FindRelativeMotionBetweenSlices)
    DREAM3D_TYPE_MACRO_SUPER(FindRelativeMotionBetweenSlices, AbstractFilter)

    virtual ~FindRelativeMotionBetweenSlices();

    DREAM3D_FILTER_PARAMETER(DataArrayPath, SelectedArrayPath)
    Q_PROPERTY(DataArrayPath SelectedArrayPath READ getSelectedArrayPath WRITE setSelectedArrayPath)

    DREAM3D_FILTER_PARAMETER(unsigned int, Plane)
    Q_PROPERTY(unsigned int Plane READ getPlane WRITE setPlane)

    DREAM3D_FILTER_PARAMETER(int, PSize1)
    Q_PROPERTY(int PSize1 READ getPSize1 WRITE setPSize1)

    DREAM3D_FILTER_PARAMETER(int, PSize2)
    Q_PROPERTY(int PSize2 READ getPSize2 WRITE setPSize2)

    DREAM3D_FILTER_PARAMETER(int, SSize1)
    Q_PROPERTY(int SSize1 READ getSSize1 WRITE setSSize1)

    DREAM3D_FILTER_PARAMETER(int, SSize2)
    Q_PROPERTY(int SSize2 READ getSSize2 WRITE setSSize2)

    DREAM3D_FILTER_PARAMETER(int, SliceStep)
    Q_PROPERTY(int SliceStep READ getSliceStep WRITE setSliceStep)

    DREAM3D_FILTER_PARAMETER(QString, MotionDirectionArrayName)
    Q_PROPERTY(QString MotionDirectionArrayName READ getMotionDirectionArrayName WRITE setMotionDirectionArrayName)

    virtual const QString getCompiledLibraryName();
    virtual AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters);
    virtual const QString getGroupName();
    virtual const QString getSubGroupName();
    virtual const QString getHumanLabel();

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
    void updateFilterParameters(AbstractFilter* filter);
    void parametersChanged();
    void preflightAboutToExecute();
    void preflightExecuted();

  protected:
    FindRelativeMotionBetweenSlices();

  private:
    DEFINE_REQUIRED_IDATAARRAY_VARIABLE(InData)

    DEFINE_CREATED_DATAARRAY_VARIABLE(float, MotionDirection)

    void dataCheck();

    FindRelativeMotionBetweenSlices(const FindRelativeMotionBetweenSlices&); // Copy Constructor Not Implemented
    void operator=(const FindRelativeMotionBetweenSlices&); // Operator '=' Not Implemented
};

#endif /* FindRelativeMotionBetweenSlices_H_ */
