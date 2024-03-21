// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-FileCopyrightText: Copyright (c) Kitware, Inc.
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_cgns_h
#define vtk_cgns_h

/* Use the cgns library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_VTK_cgns 0

/**
 * When including an CGNS header in VTK code, use the following form:
 *
 *   // .clang-format off
 *   #include VTK_CGNS(cgnslib.h)
 *   // .clang-format on
 *
 * Note, the clang-format sentinels are needed to avoid incorrect formatting.
 */
#if VTK_MODULE_USE_EXTERNAL_VTK_cgns
# define VTK_CGNS(x) <x>
#else
# define VTK_CGNS(x) <vtkcgns/src/x>
#endif

#endif
