/*
 * Author:
 * 2025/01/05 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 *
 * Use of this source code is governed by a GPL-3.0 license that can be found in
 * the LICENSE file.
 */

#include "arrow.h"
#include <vtkActor.h>
#include <vtkArrowSource.h>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkVertex.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkGlyph3D.h>

void DisplayArrow(vtkSmartPointer<vtkRenderer> renderer, XYZ origin, XYZ direction, double length)
{
	// make origin.
	vtkNew<vtkPoints> points;
	points->InsertNextPoint(origin.GetX(), origin.GetY(), origin.GetZ());
	vtkNew<vtkVertex> vertex;
	vertex->GetPointIds()->SetNumberOfIds(points->GetNumberOfPoints());
	for (int i = 0; i < points->GetNumberOfPoints(); i++)
	{
		vertex->GetPointIds()->SetId(i, i);
	}
	vtkNew<vtkCellArray> vertices;
	vertices->InsertNextCell(vertex);

	// make direction.
	vtkNew<vtkDoubleArray> dir;
	dir->SetNumberOfComponents(3);
	dir->InsertNextTuple3(direction.GetX(), direction.GetY(), direction.GetZ());

	// make length.
	vtkNew<vtkDoubleArray> scalars;
	scalars->SetNumberOfComponents(1);
	scalars->InsertNextTuple1(length);

	vtkNew<vtkPolyData> polyData;
	polyData->SetPoints(points);
	polyData->SetVerts(vertices);
	polyData->GetPointData()->SetNormals(dir);
	polyData->GetPointData()->SetScalars(scalars);

	// Create an arrow.
	vtkNew<vtkArrowSource> arrowSource;
	arrowSource->Update();

	// Create a mapper and actor
	vtkNew<vtkPolyDataMapper> mapper;
	vtkNew<vtkGlyph3D> glyph;
	glyph->SetInputData(polyData);
	glyph->SetSourceData(arrowSource->GetOutput());
	glyph->SetVectorModeToUseNormal();
	glyph->Update();
	mapper->SetInputData(glyph->GetOutput());
	vtkNew<vtkActor> actor;
	actor->SetMapper(mapper);

	renderer->AddActor(actor);
}

