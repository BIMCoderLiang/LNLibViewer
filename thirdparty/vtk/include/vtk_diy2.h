// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_diy2_h
#define vtk_diy2_h

/* Use the diy2 library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkdiy2 0

/* enable/disable DIY MPI */
#define DIY_NO_MPI

#if VTK_MODULE_USE_EXTERNAL_vtkdiy2
#  define VTK_DIY2(header) <header>
#else
#  define VTK_DIY2(header) <vtkdiy2/include/header>
#  define diy vtkdiy2 // mangle namespace diy
#endif

#endif
