/*
 * Author:
 * 2024/03/21 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 * 微信公众号：BIMCoder梁老师
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
VTK_MODULE_INIT(vtkRenderingOpenGL2)

void Test_TessllateCurve()
{
	LNLib::XYZ center = LNLib::XYZ(0, 0, 0);
	LNLib::XYZ xAxis = LNLib::XYZ(1, 0, 0);
	LNLib::XYZ yAxis = LNLib::XYZ(0, 1, 0);
	double radius = 100;
	LNLib::LN_NurbsCurve curve;
	auto x = LNLib::Constants::Pi;
	bool createArc = LNLib::NurbsCurve::CreateArc(center, xAxis, yAxis, 0, 2 * LNLib::Constants::Pi, radius, radius, curve);
	std::vector<LNLib::XYZ> tessellation = LNLib::NurbsCurve::Tessellate(curve);
	int size = tessellation.size();

	vtkNew<vtkPolyData> geometry;
	vtkNew<vtkPoints> points;
	vtkNew<vtkCellArray> polys;
	polys->InsertNextCell(size);
	for (int i = 0; i < size; i++)
	{
		LNLib::XYZ t = tessellation[i];
		points->InsertPoint(i,t.GetX(),t.GetY(),t.GetZ());
		polys->InsertCellPoint(i);
	}

	geometry->SetPoints(points);
	geometry->SetLines(polys);

	vtkNew<vtkPolyDataMapper> geometryMapper;
	geometryMapper->SetInputData(geometry);
	geometryMapper->ScalarVisibilityOff();
	vtkNew<vtkActor> geometryActor;

	double r = 255.0 / 255.0;
	double g = 0.0 / 255.0;
	double b = 0.0 / 255.0;

	geometryActor->GetProperty()->SetColor(r, g, b);
	geometryActor->GetProperty()->SetLineWidth(3);
	geometryActor->SetMapper(geometryMapper);

	vtkNew<vtkRenderer> renderer;
	renderer->AddActor(geometryActor);
	renderer->ResetCamera();
	renderer->SetBackground(0, 0, 0);

	vtkNew<vtkRenderWindow> renWin;
	renWin->SetWindowName("Tessellate Curve");
	renWin->AddRenderer(renderer);
	renWin->SetSize(500, 500);

	vtkNew<vtkRenderWindowInteractor> iren;
	iren->SetRenderWindow(renWin);
	renWin->Render();
	iren->Start();
}
