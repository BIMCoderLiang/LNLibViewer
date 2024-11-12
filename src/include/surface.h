/*
 * Author:
 * 2024/03/21 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 *
 * Use of this source code is governed by a GPL-3.0 license that can be found in
 * the LICENSE file.
 */

#include "LNObject.h"
#include <vtkRenderer.h>
#include <vector>

using namespace LNLib;

void DisplaySurfaces(vtkSmartPointer<vtkRenderer> renderer, const std::vector<LN_NurbsSurface>& surfaces);