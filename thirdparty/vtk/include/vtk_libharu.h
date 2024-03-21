// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_libharu_h
#define vtk_libharu_h

/* Use the libharu library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtklibharu 0

#define HPDF_DLL

#if VTK_MODULE_USE_EXTERNAL_vtklibharu
# include <hpdf.h>
#else
# include <vtklibharu/include/hpdf.h>
#endif

#endif // #ifndef vtk_libharu_h
