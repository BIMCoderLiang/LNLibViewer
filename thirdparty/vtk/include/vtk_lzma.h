// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_lzma_h
#define vtk_lzma_h

#define LZMA_BUILT_AS_DYNAMIC_LIB 1
#if !LZMA_BUILT_AS_DYNAMIC_LIB
#define LZMA_API_STATIC
#endif

/* Use the lzma library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtklzma 0

#if VTK_MODULE_USE_EXTERNAL_vtklzma
# include <lzma.h>
#else
# include <vtklzma/src/liblzma/api/lzma.h>
#endif

#endif
