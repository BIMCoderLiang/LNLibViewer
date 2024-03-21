// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_libtheora_h
#define vtk_libtheora_h

/* Use the theora library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtktheora 0

#if VTK_MODULE_USE_EXTERNAL_vtktheora
# include <theora/theora.h>
# include <theora/theoradec.h>
# include <theora/theoraenc.h>
#else
# include <vtktheora/include/theora/theora.h>
# include <vtktheora/include/theora/theoradec.h>
# include <vtktheora/include/theora/theoraenc.h>
#endif

#endif
