// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_doubleconversion_h
#define vtk_doubleconversion_h

/* Use the doubleconversion library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkdoubleconversion 0

#if VTK_MODULE_USE_EXTERNAL_vtkdoubleconversion
# define VTK_DOUBLECONVERSION_HEADER(header) <header>
#else
# define VTK_DOUBLECONVERSION_HEADER(header) <vtkdoubleconversion/double-conversion/header>
#endif

#endif
