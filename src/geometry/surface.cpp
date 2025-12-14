/*
 * Author:
 * 2024/03/21 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 *
 * Use of this source code is governed by a GPL-3.0 license that can be found in
 * the LICENSE file.
 */

#include "surface.h"
#include "mesh.h"
#include "LNObject.h"
#include "NurbsSurface.h"
#include <vtkRenderer.h>

using namespace LNLib;

void DisplaySurfaces(vtkSmartPointer<vtkRenderer> renderer, const std::vector<LN_NurbsSurface>& surfaces)
{
	for (int i = 0; i < surfaces.size(); i++)
	{
		LNLib::LN_NurbsSurface surface = surfaces[i];

		LNLib::LN_Mesh mesh = NurbsSurface::Triangulate(surface, 200,200,false);
		DisplayMesh(renderer,mesh);
	}
}
