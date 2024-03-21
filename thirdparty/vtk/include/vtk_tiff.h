// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_tiff_h
#define vtk_tiff_h

/* Use the tiff library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtktiff 0

#if VTK_MODULE_USE_EXTERNAL_vtktiff
# include <tiffio.h>
#else
# include <vtktiff/libtiff/tiffio.h>
#endif

#endif
