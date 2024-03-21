// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_eigen_h
#define vtk_eigen_h

// VTK should only be using MPL2 Eigen code.
#ifndef EIGEN_MPL2_ONLY
#define EIGEN_MPL2_ONLY
#endif

/* Use the eigen library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkeigen 0

#if VTK_MODULE_USE_EXTERNAL_vtkeigen
# define VTK_EIGEN(x) <Eigen/x>
#else
# define VTK_EIGEN(x) <vtkeigen/eigen/x>
#endif

#endif
