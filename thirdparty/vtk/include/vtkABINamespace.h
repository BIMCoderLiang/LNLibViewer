// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtkABINamespace_h
#define vtkABINamespace_h

#ifndef VTK_NO_ABI_NAMESPACE
#if defined(__cplusplus)
#define VTK_ABI_NAMESPACE_BEGIN 
#define VTK_ABI_NAMESPACE_END 
#else
#define VTK_ABI_NAMESPACE_BEGIN
#define VTK_ABI_NAMESPACE_END
#endif
#endif // VTK_NO_ABI_NAMESPACE

#endif // vtkABINamespace_h
