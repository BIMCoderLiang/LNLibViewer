// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_utf8_h
#define vtk_utf8_h

/* Use the utf8cpp library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkutf8 0

#if VTK_MODULE_USE_EXTERNAL_vtkutf8
# include <utf8.h>
#else
# include <vtkutf8/utf8.h>
namespace utf8 = vtk_utf8;
#endif

#endif
