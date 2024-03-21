// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_verdict_h
#define vtk_verdict_h

/* Use the verdict library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_VTK_verdict 0

#if VTK_MODULE_USE_EXTERNAL_VTK_verdict
# include <verdict.h>
#else
# include <vtkverdict/verdict.h>
#endif

#endif
