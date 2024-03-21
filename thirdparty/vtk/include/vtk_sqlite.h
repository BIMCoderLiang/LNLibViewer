// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtk_sqlite_h
#define vtk_sqlite_h

/* Use the sqlite library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtksqlite 0

#if VTK_MODULE_USE_EXTERNAL_vtksqlite
# include <sqlite3.h>
#else
# include <vtksqlite/sqlite3.h>
#endif

#endif
