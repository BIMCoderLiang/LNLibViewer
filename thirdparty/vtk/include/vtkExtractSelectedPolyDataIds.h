// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
/**
 * @class   vtkExtractSelectedPolyDataIds
 * @brief   extract a list of cells from a polydata
 *
 * vtkExtractSelectedPolyDataIds extracts all cells in vtkSelection from a
 * vtkPolyData.
 *
 * @sa
 * vtkSelection
 *
 * @deprecated vtkExtractSelectedPolyDataIds is deprecated in VTK 9.2 and will be removed.
 * Use `vtkExtractSelection` instead of `vtkExtractSelectedPolyDataIds`.
 *
 * Example using vtkExtractSelectedPolyDataIds:
 *
 * vtkNew<vtkExtractSelectedPolyDataIds> selFilter;
 * selFilter->SetInputConnection(0, sphereSource->GetOutputPort());
 * selFilter->SetInputConnection(1, selectionSource->GetOutputPort());
 *
 * Example using vtkExtractSelection:
 *
 * vtkNew<vtkExtractSelection> selFilter;
 * selFilter->SetInputConnection(0, sphereSource->GetOutputPort());
 * selFilter->SetInputConnection(1, selectionSource->GetOutputPort());
 *
 * convert selFilter's output from vtkUnstructuredGrid to vtkPolydata
 */

#ifndef vtkExtractSelectedPolyDataIds_h
#define vtkExtractSelectedPolyDataIds_h

#include "vtkDeprecation.h"             // For VTK_DEPRECATED_IN_9_2_0
#include "vtkFiltersExtractionModule.h" // For export macro
#include "vtkPolyDataAlgorithm.h"

VTK_ABI_NAMESPACE_BEGIN
class vtkSelection;

class VTK_DEPRECATED_IN_9_2_0("Use vtkExtractSelection instead of vtkExtractSelectedPolyDataIds.")
  VTKFILTERSEXTRACTION_EXPORT vtkExtractSelectedPolyDataIds : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkExtractSelectedPolyDataIds, vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;
  static vtkExtractSelectedPolyDataIds* New();

protected:
  vtkExtractSelectedPolyDataIds();
  ~vtkExtractSelectedPolyDataIds() override;

  int FillInputPortInformation(int port, vtkInformation* info) override;

  // Usual data generation method
  int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

private:
  vtkExtractSelectedPolyDataIds(const vtkExtractSelectedPolyDataIds&) = delete;
  void operator=(const vtkExtractSelectedPolyDataIds&) = delete;
};

VTK_ABI_NAMESPACE_END
#endif

// VTK-HeaderTest-Exclude: vtkExtractSelectedPolyDataIds.h
