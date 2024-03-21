// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_loguru_h
#define vtk_loguru_h

/* Use the loguru library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkloguru 0

#if VTK_MODULE_USE_EXTERNAL_vtkloguru
# include <loguru.hpp>
#else
#include <vtkloguru/loguru.hpp>
#endif

#endif
