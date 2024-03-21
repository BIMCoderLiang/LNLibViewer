// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_fast_float_h
#define vtk_fast_float_h

/* Use the fast_float library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkfast_float 0

#if VTK_MODULE_USE_EXTERNAL_vtkfast_float
# include <fast_float/fast_float.h>
#else
# include <vtkfast_float/vtkfast_float/fast_float.h>
#endif

#endif
