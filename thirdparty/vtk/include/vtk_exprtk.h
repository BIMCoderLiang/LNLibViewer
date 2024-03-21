// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_exprtk_h
#define vtk_exprtk_h

/* Use the exprtk library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_VTK_exprtk 0

#if VTK_MODULE_USE_EXTERNAL_VTK_exprtk
# include <exprtk.hpp>
#else
# include <vtkexprtk/exprtk.hpp>
#endif

#endif
