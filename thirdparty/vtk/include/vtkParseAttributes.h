// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause

#ifndef vtkParseAttributes_h
#define vtkParseAttributes_h

/**
 * This header defines attribute specifiers for use by the wrappers.
 * They are stored in a 32-bit unsigned int (see vtkParseData.h).
 */

#define VTK_PARSE_NEWINSTANCE 0x00000001 /* [[vtk::newinstance]] */
#define VTK_PARSE_ZEROCOPY 0x00000002    /* [[vtk::zerocopy]] */
#define VTK_PARSE_FILEPATH 0x00000004    /* [[vtk::filepath]] */
#define VTK_PARSE_WRAPEXCLUDE 0x00000010 /* [[vtk::wrapexclude]] */
#define VTK_PARSE_DEPRECATED 0x00000020  /* [[vtk::deprecated()]] */

#endif
/* VTK-HeaderTest-Exclude: vtkParseAttributes.h */
