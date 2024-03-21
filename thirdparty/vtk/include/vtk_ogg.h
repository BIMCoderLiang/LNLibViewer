// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_ogg_h
#define vtk_ogg_h

/* Use the ogg library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkogg 0

#if VTK_MODULE_USE_EXTERNAL_vtkogg
# include <ogg/ogg.h>
#else
# include <vtkogg/include/ogg/ogg.h>
#endif

#endif
