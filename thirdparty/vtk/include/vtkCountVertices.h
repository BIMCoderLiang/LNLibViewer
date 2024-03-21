// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause

/**
 * @class   vtkCountVertices
 * @brief   Add a cell data array containing the number of
 * vertices per cell.
 *
 *
 * This filter adds a cell data array containing the number of vertices per
 * cell.
 */

#ifndef vtkCountVertices_h
#define vtkCountVertices_h

#include "vtkFiltersGeneralModule.h" // For export macro
#include "vtkPassInputTypeAlgorithm.h"

VTK_ABI_NAMESPACE_BEGIN
class VTKFILTERSGENERAL_EXPORT vtkCountVertices : public vtkPassInputTypeAlgorithm
{
public:
  static vtkCountVertices* New();
  vtkTypeMacro(vtkCountVertices, vtkPassInputTypeAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  ///@{
  /**
   * The name of the new output array containing the vertex counts.
   */
  vtkSetStringMacro(OutputArrayName);
  vtkGetStringMacro(OutputArrayName);
  ///@}

protected:
  vtkCountVertices();
  ~vtkCountVertices() override;

  int RequestData(vtkInformation* request, vtkInformationVector** inInfoVec,
    vtkInformationVector* outInfoVec) override;

  int FillOutputPortInformation(int port, vtkInformation* info) override;
  int FillInputPortInformation(int port, vtkInformation* info) override;

  char* OutputArrayName;

private:
  vtkCountVertices(const vtkCountVertices&) = delete;
  void operator=(const vtkCountVertices&) = delete;
};

VTK_ABI_NAMESPACE_END
#endif // vtkCountVertices_h
