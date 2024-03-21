// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_ioss_h
#define vtk_ioss_h

/* Use the ioss library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkioss 0

#if VTK_MODULE_USE_EXTERNAL_vtkioss
# define VTK_IOSS(x) <x>
#else
# define VTK_IOSS(x) <vtkioss/x>
#endif

#endif
