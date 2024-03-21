// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_netcdf_h
#define vtk_netcdf_h

/* Use the netcdf library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtknetcdf 0

#if VTK_MODULE_USE_EXTERNAL_vtknetcdf
# include <netcdf.h>
#else
# include <vtknetcdf/include/netcdf.h>
#endif

#endif
