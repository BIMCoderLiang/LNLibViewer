// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
// .NAME vtkTypeInt32Array - dynamic, self-adjusting array of vtkTypeInt32
// .SECTION Description
// vtkTypeInt32Array is an array of values of type vtkTypeInt32.  It
// provides methods for insertion and retrieval of values and will
// automatically resize itself to hold new data.
//
// This array should be preferred for data of type Int32 as this
// array will use the correct underlying datatype based on the desired number of bits
// and the current platform.  The superclass of this type will change depending on the
// machine and compiler in use so that the data contained always uses the proper type.

#ifndef vtkTypeInt32Array_h
#define vtkTypeInt32Array_h

#include "vtkCommonCoreModule.h" // For export macro
#include "vtkType.h" // For native type selections.

#if VTK_TYPE_INT32 == VTK_INT
# include "vtkIntArray.h"
# define vtkTypeArrayBase vtkIntArray
#endif


VTK_ABI_NAMESPACE_BEGIN

class VTKCOMMONCORE_EXPORT vtkTypeInt32Array : public vtkTypeArrayBase
{
public:
  static vtkTypeInt32Array* New();
  vtkTypeMacro(vtkTypeInt32Array,vtkTypeArrayBase);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  // Description:
  // A faster alternative to SafeDownCast for downcasting vtkAbstractArrays.
  static vtkTypeInt32Array* FastDownCast(vtkAbstractArray *source)
  {
    return static_cast<vtkTypeInt32Array*>(Superclass::FastDownCast(source));
  }

protected:
  vtkTypeInt32Array();
  ~vtkTypeInt32Array() override;

private:
  vtkTypeInt32Array(const vtkTypeInt32Array&) = delete;
  void operator=(const vtkTypeInt32Array&) = delete;
};

// Define vtkArrayDownCast implementation:
vtkArrayDownCast_FastCastMacro(vtkTypeInt32Array);

VTK_ABI_NAMESPACE_END

#undef vtkTypeArrayBase

#endif
/* VTK-HeaderTest-Exclude: INCLUDES */
