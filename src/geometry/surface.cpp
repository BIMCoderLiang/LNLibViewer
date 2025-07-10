/*
 * Author:
 * 2024/03/21 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 *
 * Use of this source code is governed by a GPL-3.0 license that can be found in
 * the LICENSE file.
 */

#include "surface.h"
#include "XYZ.h"
#include "XYZW.h"
#include "LNObject.h"
#include "Constants.h"
#include "NurbsSurface.h"

#include <vtkTriangle.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolygon.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>

#include <random>
using namespace LNLib;

void DisplaySurfaces(vtkSmartPointer<vtkRenderer> renderer, const std::vector<LN_NurbsSurface>& surfaces)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(50, 250);

	for (int i = 0; i < surfaces.size(); i++)
	{
		LNLib::LN_NurbsSurface surface = surfaces[i];

		LNLib::LN_Mesh mesh = NurbsSurface::Triangulate(surface);
		std::vector<std::vector<int>> faces = mesh.Faces;
		std::vector<XYZ> vertices = mesh.Vertices;

		// Setup three points
		vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
		for (int i = 0; i < vertices.size(); i++)
		{
			points->InsertNextPoint(vertices[i][0], vertices[i][1], vertices[i][2]);
		}

		// Add the polygon to a list of polygons
		vtkSmartPointer<vtkCellArray> triangles = vtkSmartPointer<vtkCellArray>::New();
		for (int i = 0; i < faces.size(); i++)
		{
			// Create the triangle
			vtkSmartPointer<vtkTriangle> triangle = vtkSmartPointer<vtkTriangle>::New();

			triangle->GetPointIds()->SetId(0, faces[i][0]);
			triangle->GetPointIds()->SetId(1, faces[i][1]);
			triangle->GetPointIds()->SetId(2, faces[i][2]);

			triangles->InsertNextCell(triangle);
		}

		// Create a PolyData
		vtkSmartPointer<vtkPolyData> polygonPolyData = vtkSmartPointer<vtkPolyData>::New();
		polygonPolyData->SetPoints(points);
		polygonPolyData->SetPolys(triangles);

		// Create a mapper and actor
		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputData(polygonPolyData);

		vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);
		double r = distrib(gen) / 255.0;
		double g = distrib(gen) / 255.0;
		double b = distrib(gen) / 255.0;
		actor->GetProperty()->SetColor(r, g, b);

		renderer->AddActor(actor);
	}
}
