// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtkVersionMacros_h
#define vtkVersionMacros_h

/* Note: this file is deliberately both valid C and valid C++. */

#define VTK_MAJOR_VERSION 9
#define VTK_MINOR_VERSION 3
#define VTK_BUILD_VERSION 0
#define VTK_VERSION "9.3.0"

#define VTK_SOURCE_VERSION "vtk version " VTK_VERSION

#define VTK_VERSION_CHECK(major, minor, build)                                                     \
  (10000000000ULL * major + 100000000ULL * minor + build)
#define VTK_VERSION_NUMBER                                                                         \
  VTK_VERSION_CHECK(VTK_MAJOR_VERSION, VTK_MINOR_VERSION, VTK_BUILD_VERSION)

#endif
