// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_expat_h
#define vtk_expat_h

/* Use the expat library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkexpat 0

#if VTK_MODULE_USE_EXTERNAL_vtkexpat
# include <expat.h>
#else
/* #undef XML_STATIC */
# include <vtkexpat/lib/expat.h>
#endif

#endif
