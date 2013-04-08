/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Csaba Pinter, PerkLab, Queen's University
  and was supported through the Applied Cancer Research Unit program of Cancer Care
  Ontario with funds provided by the Ontario Ministry of Health and Long-Term Care

==============================================================================*/

#ifndef __qMRMLScenePatientHierarchyModel_h
#define __qMRMLScenePatientHierarchyModel_h

// SlicerRt includes
#include "qSlicerPatientHierarchyModuleWidgetsExport.h"

// MRMLWidgets includes
#include "qMRMLSceneHierarchyModel.h"

class qMRMLScenePatientHierarchyModelPrivate;

/// \ingroup Slicer_QtModules_PatientHierarchy
class Q_SLICER_MODULE_PATIENTHIERARCHY_WIDGETS_EXPORT qMRMLScenePatientHierarchyModel : public qMRMLSceneHierarchyModel
{
  Q_OBJECT

  /// Control in which column vtkMRMLNode::NodeType are displayed (Qt::DecorationRole).
  /// A value of -1 hides it. Hidden by default (value of -1).
  Q_PROPERTY (int nodeTypeColumn READ nodeTypeColumn WRITE setNodeTypeColumn)

public:
  typedef qMRMLSceneHierarchyModel Superclass;
  qMRMLScenePatientHierarchyModel(QObject *parent=0);
  virtual ~qMRMLScenePatientHierarchyModel();

  /// Retrieve parent of a node
  virtual vtkMRMLNode* parentNode(vtkMRMLNode* node)const;

  /// Fast function that only check the type of the node to know if it can be a child.
  virtual bool canBeAChild(vtkMRMLNode* node)const;

  /// Fast function that only check the type of the node to know if it can be a parent.
  virtual bool canBeAParent(vtkMRMLNode* node)const;

  /// If newParent == 0, set the node into the vtkMRMLScene
  //virtual bool reparent(vtkMRMLNode* node, vtkMRMLNode* newParent);

  //virtual int nodeIndex(vtkMRMLNode* node)const;

  int nodeTypeColumn()const;
  void setNodeTypeColumn(int column);

signals:
  /// Signal invoked when a node is added to the scene
  void nodeAdded();

protected:
  /// Overridden function for performing additional steps when a node is added
  virtual void onMRMLSceneNodeAdded(vtkMRMLScene* scene, vtkMRMLNode* node);

  /// Get the largest column ID
  virtual int maxColumnId()const;

  /// Overridden function to handle tree view item display from node data
  virtual void updateItemDataFromNode(QStandardItem* item, vtkMRMLNode* node, int column);

  /// Overridden function to handle node update from tree view item
  virtual void updateNodeFromItemData(vtkMRMLNode* node, QStandardItem* item);

private:
  Q_DECLARE_PRIVATE(qMRMLScenePatientHierarchyModel);
  Q_DISABLE_COPY(qMRMLScenePatientHierarchyModel);
};

#endif