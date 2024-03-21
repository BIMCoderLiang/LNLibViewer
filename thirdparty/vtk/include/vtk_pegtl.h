// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_pegtl_h
#define vtk_pegtl_h

/* Use the pegtl library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkpegtl 0

#if VTK_MODULE_USE_EXTERNAL_vtkpegtl
# define VTK_PEGTL(x) <tao/x>
#else
# include <vtkpegtl/include/tao/pegtl.hpp>
# define VTK_PEGTL(x) <vtkpegtl/include/tao/x>
#endif

#include VTK_PEGTL(pegtl.hpp)

#endif
