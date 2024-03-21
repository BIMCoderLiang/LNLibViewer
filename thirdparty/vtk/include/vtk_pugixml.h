// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_pugixml_h
#define vtk_pugixml_h

/* Use the pugixml library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkpugixml 0

#if VTK_MODULE_USE_EXTERNAL_vtkpugixml
# include <pugixml.hpp>
#else
# include <vtkpugixml/src/pugixml.hpp>
#endif

#endif
