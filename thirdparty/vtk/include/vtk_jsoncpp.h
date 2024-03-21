// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_jsoncpp_h
#define vtk_jsoncpp_h

/* Use the jsoncpp library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkjsoncpp 0

#define VTK_JSONCPP_SHARED 1

#if VTK_MODULE_USE_EXTERNAL_vtkjsoncpp
# if !defined(JSON_DLL) && defined(_WIN32) && VTK_JSONCPP_SHARED
#  define JSON_DLL
# endif
# include <json/json.h>
#else
// Needed for Windows declspec import logic
# if !defined(JSON_DLL) && defined(_WIN32) && VTK_JSONCPP_SHARED
#  define JSON_DLL
# endif
# include <vtkjsoncpp/json/json.h>
#endif

#endif
