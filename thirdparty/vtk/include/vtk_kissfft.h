// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_kissfft_h
#define vtk_kissfft_h

/* Use the kissfft library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkkissfft 0

#if VTK_MODULE_USE_EXTERNAL_vtkkissfft
# define VTK_KISSFFT_HEADER(header) <header>
#else
# define VTK_KISSFFT_HEADER(header) <vtkkissfft/header>
#endif

#endif
