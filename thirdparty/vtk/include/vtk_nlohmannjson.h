// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_nlohmannjson_h
#define vtk_nlohmannjson_h

/* Use the nlohmannjson library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtknlohmannjson 0

#if VTK_MODULE_USE_EXTERNAL_vtknlohmannjson
# define VTK_NLOHMANN_JSON(x) <nlohmann/x>
#else
# define nlohmann vtknlohmann
# define VTK_NLOHMANN_JSON(x) <vtknlohmannjson/include/vtknlohmann/x>
#endif

#endif
