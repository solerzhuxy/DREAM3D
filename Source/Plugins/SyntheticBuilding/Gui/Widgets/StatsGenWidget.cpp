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

#include "StatsGenWidget.h"

// Needed for AxisAngle_t and Crystal Symmetry constants
#include "EbsdLib/EbsdConstants.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
StatsGenWidget::StatsGenWidget(QWidget* parent)
: QWidget(parent)
, m_PhaseType(PhaseType::Type::Primary)
, m_CrystalStructure(Ebsd::CrystalStructure::Cubic_High)
, m_PhaseIndex(0)
, m_PhaseFraction(1.0)
, m_TotalPhaseFraction(1.0)
, m_DataHasBeenGenerated(false)
, m_BulkLoadFailure(false)
, m_TabTitle("Unknown Phase")
, m_PhaseName("Unknown Phase")
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
StatsGenWidget::~StatsGenWidget() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void StatsGenWidget::extractStatsData(AttributeMatrix::Pointer attrMat, int index)
{
  Q_ASSERT(false);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString StatsGenWidget::getComboString()
{
  return QString("StatsGenWidget - THIS IS BAD. YOU SHOULD NOT BE SEEING THIS.");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int StatsGenWidget::gatherStatsData(AttributeMatrix::Pointer attrMat, bool preflight)
{
  return -1;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void StatsGenWidget::generateDefaultData()
{
}

//// -----------------------------------------------------------------------------
////
//// -----------------------------------------------------------------------------
// void StatsGenWidget::dataWasEdited()
//{
//  Q_ASSERT(false);
//}
