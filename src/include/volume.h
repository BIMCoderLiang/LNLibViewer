/*
 * Author:
 * 2026/05/27 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 *
 * Use of this source code is governed by a GPL-3.0 license that can be found in
 * the LICENSE file.
 */

#include "NurbsVolume.h"
#include <vtkRenderer.h>
#include <vector>

using namespace LNLib;

void DisplayVolumes(vtkSmartPointer<vtkRenderer> renderer, const std::vector<LN_NurbsVolume>& volumes, double r, double g, double b);