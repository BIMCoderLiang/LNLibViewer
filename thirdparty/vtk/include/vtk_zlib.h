// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_zlib_h
#define vtk_zlib_h

/* Use the zlib library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkzlib 0

#if VTK_MODULE_USE_EXTERNAL_vtkzlib
# include <zlib.h>
#else
# include <vtkzlib/zlib.h>
#endif

#endif
