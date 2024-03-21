// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_gl2ps_h
#define vtk_gl2ps_h

/* Use the gl2ps library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkgl2ps 0

#if VTK_MODULE_USE_EXTERNAL_vtkgl2ps
# include <gl2ps.h>
#else
# include <vtkgl2ps/gl2ps.h>
#endif

#endif
