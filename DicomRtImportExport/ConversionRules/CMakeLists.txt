project(vtkSlicer${MODULE_NAME}ConversionRules)

set(KIT ${PROJECT_NAME})

set(${KIT}_EXPORT_DIRECTIVE "VTK_SLICER_${MODULE_NAME_UPPER}_CONVERSIONRULES_EXPORT")

set(${KIT}_INCLUDE_DIRECTORIES
  ${SlicerRtCommon_INCLUDE_DIRS}
  ${vtkSegmentationCore_INCLUDE_DIRS}
  )

set(${KIT}_SRCS
  vtkPlanarContourToClosedSurfaceConversionRule.cxx
  vtkPlanarContourToClosedSurfaceConversionRule.h
  vtkPlanarContourToRibbonModelConversionRule.cxx
  vtkPlanarContourToRibbonModelConversionRule.h
  vtkRibbonModelToBinaryLabelmapConversionRule.cxx
  vtkRibbonModelToBinaryLabelmapConversionRule.h
  vtkClosedSurfaceToFractionalLabelmapConversionRule.cxx
  vtkClosedSurfaceToFractionalLabelmapConversionRule.h
  vtkFractionalLabelmapToClosedSurfaceConversionRule.cxx
  vtkFractionalLabelmapToClosedSurfaceConversionRule.h
  )

set(${KIT}_TARGET_LIBRARIES
  vtkSlicerRtCommon
  vtkSegmentationCore
  vtkSlicerSegmentationsModuleMRMLDisplayableManager
  )

SET (${KIT}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${SlicerRtCommon_INCLUDE_DIRS} CACHE INTERNAL "" FORCE)

#-----------------------------------------------------------------------------
SlicerMacroBuildModuleLogic(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  )