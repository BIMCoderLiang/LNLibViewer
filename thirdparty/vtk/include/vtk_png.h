// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_png_h
#define vtk_png_h

/* Use the png library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkpng 0

#if VTK_MODULE_USE_EXTERNAL_vtkpng
# include <png.h>
#else
# include <vtkpng/png.h>
#endif

#endif
