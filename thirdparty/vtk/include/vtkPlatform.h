// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtkPlatform_h
#define vtkPlatform_h

/* Whether we require large files support.  */
/* #undef VTK_REQUIRE_LARGE_FILE_SUPPORT */

/* The maximum length of a file name in bytes including the
 * terminating null.
 */
#if defined(PATH_MAX) // Usually defined on Windows
# define VTK_MAXPATH PATH_MAX
#elif defined(MAXPATHLEN)  // Usually defined on linux
# define VTK_MAXPATH MAXPATHLEN
#else
# define VTK_MAXPATH 32767 // Possible with Windows "extended paths"
#endif

#endif
