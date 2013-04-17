/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Kevin Wang, Radiation Medicine Program, 
  University Health Network and was supported by Cancer Care Ontario (CCO)'s ACRU program 
  with funds provided by the Ontario Ministry of Health and Long-Term Care
  and Ontario Consortium for Adaptive Interventions in Radiation Oncology (OCAIRO).

==============================================================================*/

#ifndef __qSlicerContourMorphologyModuleWidget_h
#define __qSlicerContourMorphologyModuleWidget_h

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerContourMorphologyModuleExport.h"

class qSlicerContourMorphologyModuleWidgetPrivate;
class vtkMRMLNode;

/// \ingroup Slicer_QtModules_ExtensionTemplate
class Q_SLICER_QTMODULES_CONTOURMORPHOLOGY_EXPORT qSlicerContourMorphologyModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT
  QVTK_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerContourMorphologyModuleWidget(QWidget *parent=0);
  virtual ~qSlicerContourMorphologyModuleWidget();

  virtual void enter();

public slots:
  /// Set the current MRML scene to the widget
  virtual void setMRMLScene(vtkMRMLScene*);

  /// Process loaded scene
  void onSceneImportedEvent();

  /// Set current parameter node
  void setContourMorphologyNode(vtkMRMLNode*);

  /// Update widget GUI from parameter node
  void updateWidgetFromMRML();

protected slots:

  ///
  void setContourANode(vtkMRMLNode* node);

  ///
  void setContourBNode(vtkMRMLNode* node);

  ///
  void setReferenceVolumeNode(vtkMRMLNode* node);

  ///
  void setOutputContourNode(vtkMRMLNode* node);

  ///
  void radioButtonExpandClicked();

  ///
  void radioButtonShrinkClicked();

  ///
  void radioButtonUnionClicked();

  ///
  void radioButtonIntersectClicked();

  ///
  void radioButtonSubtractClicked();

  ///
  void doubleSpinBoxXSizeChanged(double value);

  ///
  void doubleSpinBoxYSizeChanged(double value);

  ///
  void doubleSpinBoxZSizeChanged(double value);

  ///
  void applyClicked();

  ///
  void onLogicModified();

protected:
  QScopedPointer<qSlicerContourMorphologyModuleWidgetPrivate> d_ptr;
  
  ///
  virtual void setup();

  // Generates a new isodose level name
  void onEnter();

  ///
  void updateButtonsState();

private:
  Q_DECLARE_PRIVATE(qSlicerContourMorphologyModuleWidget);
  Q_DISABLE_COPY(qSlicerContourMorphologyModuleWidget);
};

#endif
