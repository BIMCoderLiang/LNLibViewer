// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
/**
 * @class   vtkAbstractPolyDataReader
 * @brief   Superclass for algorithms that read
 * models from a file.
 *
 * This class allows to use a single base class to manage AbstractPolyData
 * reader classes in a uniform manner without needing to know the actual
 * type of the reader.
 * i.e. makes it possible to create maps to associate filename extension
 * and vtkAbstractPolyDataReader object.
 *
 * @sa
 * vtkOBJReader vtkPLYReader vtkSTLReader
 */

#ifndef vtkAbstractPolyDataReader_h
#define vtkAbstractPolyDataReader_h

#include "vtkIOCoreModule.h" // For export macro
#include "vtkPolyDataAlgorithm.h"

VTK_ABI_NAMESPACE_BEGIN
class VTKIOCORE_EXPORT vtkAbstractPolyDataReader : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkAbstractPolyDataReader, vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  ///@{
  /**
   * Specify file name of AbstractPolyData file (obj / ply / stl).
   */
  vtkSetFilePathMacro(FileName);
  vtkGetFilePathMacro(FileName);
  ///@}

protected:
  vtkAbstractPolyDataReader();
  ~vtkAbstractPolyDataReader() override;

  char* FileName;

private:
  vtkAbstractPolyDataReader(const vtkAbstractPolyDataReader&) = delete;
  void operator=(const vtkAbstractPolyDataReader&) = delete;
};

VTK_ABI_NAMESPACE_END
#endif
