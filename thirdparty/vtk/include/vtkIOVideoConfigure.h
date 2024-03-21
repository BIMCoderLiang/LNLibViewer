// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtkIOVideoConfigure_h
#define vtkIOVideoConfigure_h

// If defined, `vtkMP4Writer.h` is available.
/* #undef VTK_USE_VIDEO_FOR_WINDOWS_CAPTURE */

#ifdef VTK_USE_VIDEO_FOR_WINDOWS_CAPTURE
// The old name for the define.
#define VTK_USE_VFW_CAPTURE
#endif

#endif
