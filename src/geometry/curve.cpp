/*
 * Author:
 * 2024/03/21 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 *
 * Use of this source code is governed by a GPL-3.0 license that can be found in
 * the LICENSE file.
 */

#include "curve.h"
#include "XYZ.h"
#include "XYZW.h"
#include "LNObject.h"
#include "Constants.h"
#include "NurbsCurve.h"

#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAutoInit.h>

#include <random>
VTK_MODULE_INIT(vtkRenderingOpenGL2)

void DisplayCurves(vtkSmartPointer<vtkRenderer> renderer, const std::vector<LN_NurbsCurve>& curves)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(50, 250);
	for (int i = 0; i < curves.size(); i++)
	{
		LNLib::LN_NurbsCurve curve = curves[i];

		std::vector<LNLib::XYZ> tessellation = LNLib::NurbsCurve::Tessellate(curve);
		int size = tessellation.size();

		vtkNew<vtkPolyData> geometry;
		vtkNew<vtkPoints> points;
		vtkNew<vtkCellArray> polys;
		polys->InsertNextCell(size);
		for (int i = 0; i < size; i++)
		{
			LNLib::XYZ t = tessellation[i];
			points->InsertPoint(i, t.GetX(), t.GetY(), t.GetZ());
			polys->InsertCellPoint(i);
		}

		geometry->SetPoints(points);
		geometry->SetLines(polys);

		vtkNew<vtkPolyDataMapper> geometryMapper;
		geometryMapper->SetInputData(geometry);
		geometryMapper->ScalarVisibilityOff();
		vtkNew<vtkActor> geometryActor;

		double r = distrib(gen) / 255.0;
		double g = distrib(gen) / 255.0;
		double b = distrib(gen) / 255.0;

		geometryActor->GetProperty()->SetColor(r, g, b);
		geometryActor->GetProperty()->SetLineWidth(3);
		geometryActor->SetMapper(geometryMapper);

		renderer->AddActor(geometryActor);
	}
}
