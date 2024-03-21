// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
/**
 * @class   vtkFilteringInformationKeyManager
 * @brief   Manages key types in vtkFiltering.
 *
 * vtkFilteringInformationKeyManager is included in the header of any
 * subclass of vtkInformationKey defined in the vtkFiltering library.
 * It makes sure that the table of keys is created before and
 * destroyed after it is used.
 */

#ifndef vtkFilteringInformationKeyManager_h
#define vtkFilteringInformationKeyManager_h

#include "vtkCommonExecutionModelModule.h" // For export macro
#include "vtkSystemIncludes.h"

#include "vtkDebugLeaksManager.h" // DebugLeaks exists longer than info keys.

VTK_ABI_NAMESPACE_BEGIN
class vtkInformationKey;

class VTKCOMMONEXECUTIONMODEL_EXPORT vtkFilteringInformationKeyManager
{
public:
  vtkFilteringInformationKeyManager();
  ~vtkFilteringInformationKeyManager();

  /**
   * Called by constructors of vtkInformationKey subclasses defined in
   * vtkFiltering to register themselves with the manager.  The
   * instances will be deleted when vtkFiltering is unloaded on
   * program exit.
   */
  static void Register(vtkInformationKey* key);

private:
  // Unimplemented
  vtkFilteringInformationKeyManager(const vtkFilteringInformationKeyManager&) = delete;
  vtkFilteringInformationKeyManager& operator=(const vtkFilteringInformationKeyManager&) = delete;

  static void ClassInitialize();
  static void ClassFinalize();
};

// This instance will show up in any translation unit that uses key
// types defined in vtkFiltering or that has a singleton.  It will
// make sure vtkFilteringInformationKeyManager's vector of keys is
// initialized before and destroyed after it is used.
static vtkFilteringInformationKeyManager vtkFilteringInformationKeyManagerInstance;

VTK_ABI_NAMESPACE_END
#endif
// VTK-HeaderTest-Exclude: vtkFilteringInformationKeyManager.h
