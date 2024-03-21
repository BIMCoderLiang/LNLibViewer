// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_jsoncpp_fwd_h
#define vtk_jsoncpp_fwd_h

/* Use the jsoncpp library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkjsoncpp 0

#if VTK_MODULE_USE_EXTERNAL_vtkjsoncpp
# include <json/>
#else
# include <vtkjsoncpp/json/json-forwards.h>
#endif

#endif
