// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-FileCopyrightText: Copyright (c) Kitware, Inc.
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_lz4_h
#define vtk_lz4_h

/* Use the lz4 library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtklz4 0

#if VTK_MODULE_USE_EXTERNAL_vtklz4
# include <lz4.h>
#else
# include <vtklz4/lib/lz4.h>
#endif

#endif
