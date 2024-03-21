// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtkOptions_h
#define vtkOptions_h

/* Whether vtkIdType is a 64-bit integer type (or a 32-bit integer type).  */
#define VTK_USE_64BIT_IDS

/* Whether MTime should use a 64-bit integer type on 32 bit builds.  */
#define VTK_USE_64BIT_TIMESTAMPS

/* Whether VTK_FUTURE_CONST should be defined as const or nothing.  */
#define VTK_USE_FUTURE_CONST 0

/* Whether vtkTypeBool should be defined as int or bool.  */
#define VTK_USE_FUTURE_BOOL 0

#endif
