/*
 * Author:
 * 2024/03/21 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 *
 * Use of this source code is governed by a GPL-3.0 license that can be found in
 * the LICENSE file.
 */

#include "curve.h"
#include "surface.h"
#include "XYZW.h"
#include "arrow.h"
#include "point.h"
#include "mesh.h"
#include "customIteractorStyle.h"

#include <vtkNew.h>
#include <vtkAxesActor.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkLight.h>
#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2)
using namespace LNLib;

int main(int, char* [])
{
	std::vector<LN_NurbsSurface> surfaces;
	{
	
		int degreeU = 3;
		int degreeV = 3;
		std::vector<double> kvU = { 0,0,0,0,0.4,0.6,1,1,1,1 };
		std::vector<double> kvV = { 0,0,0,0,0.4,0.6,1,1,1,1 };
		std::vector<std::vector<XYZW>> controlPoints(6, std::vector<XYZW>(6));

		controlPoints[0][0] = XYZW(0, 0, 0, 1);
		controlPoints[0][1] = XYZW(6.666666, 0, 4, 1);
		controlPoints[0][2] = XYZW(16.666666, 0, 22, 1);
		controlPoints[0][3] = XYZW(33.333333, 0, 22, 1);
		controlPoints[0][4] = XYZW(43.333333, 0, 4, 1);
		controlPoints[0][5] = XYZW(50, 0, 0, 1);

		controlPoints[1][0] = XYZW(0, 6.666667, 0, 1);
		controlPoints[1][1] = XYZW(6.6666667, 6.666667, 9.950068, 1);
		controlPoints[1][2] = XYZW(16.6666666, 6.666667, 9.65541838, 1);
		controlPoints[1][3] = XYZW(33.3333333, 6.666667, 47.21371742, 1);
		controlPoints[1][4] = XYZW(43.3333333, 6.666667, -11.56982167, 1);
		controlPoints[1][5] = XYZW(50, 6.6666667, 0, 1);

		controlPoints[2][0] = XYZW(0, 16.666666, 0, 1);
		controlPoints[2][1] = XYZW(6.6666667, 16.666666, -7.9001371, 1);
		controlPoints[2][2] = XYZW(16.6666666, 16.666666, 46.6891632, 1);
		controlPoints[2][3] = XYZW(33.3333333, 16.666667, -28.4274348, 1);
		controlPoints[2][4] = XYZW(43.3333333, 16.666667, 35.1396433, 1);
		controlPoints[2][5] = XYZW(50, 16.6666667, 0, 1);

		controlPoints[3][0] = XYZW(0, 33.3333333, 0, 1);
		controlPoints[3][1] = XYZW(6.6666667, 33.3333333, 29.2877911, 1);
		controlPoints[3][2] = XYZW(16.6666666, 33.3333333, -30.4644718, 1);
		controlPoints[3][3] = XYZW(33.3333333, 33.3333333, 129.1582990, 1);
		controlPoints[3][4] = XYZW(43.3333333, 33.3333333, -62.1717142, 1);
		controlPoints[3][5] = XYZW(50, 33.333333, 0, 1);

		controlPoints[4][0] = XYZW(0, 43.333333, 0, 1);
		controlPoints[4][1] = XYZW(6.6666667, 43.333333, -10.384636, 1);
		controlPoints[4][2] = XYZW(16.6666666, 43.333333, 59.21371742, 1);
		controlPoints[4][3] = XYZW(33.3333333, 43.333333, -37.7272976, 1);
		controlPoints[4][4] = XYZW(43.3333333, 43.333333, 45.1599451, 1);
		controlPoints[4][5] = XYZW(50, 43.333333, 0, 1);

		controlPoints[5][0] = XYZW(0, 50, 0, 1);
		controlPoints[5][1] = XYZW(6.6666667, 50, 0, 1);
		controlPoints[5][2] = XYZW(16.6666666, 50, 0, 1);
		controlPoints[5][3] = XYZW(33.3333333, 50, 0, 1);
		controlPoints[5][4] = XYZW(43.3333333, 50, 0, 1);
		controlPoints[5][5] = XYZW(50, 50, 0, 1);

		LNLib::LN_NurbsSurface surface;
		surface.DegreeU = degreeU;
		surface.DegreeV = degreeV;
		surface.KnotVectorU = kvU;
		surface.KnotVectorV = kvV;
		surface.ControlPoints = controlPoints;

		surfaces.emplace_back(surface);
	}
	
	std::vector<LN_NurbsCurve> curves;
	{
		LNLib::XYZ center = LNLib::XYZ(0, 0, 0);
		LNLib::XYZ xAxis = LNLib::XYZ(1, 0, 0);
		LNLib::XYZ yAxis = LNLib::XYZ(0, 1, 0);
		double radius = 100;
		LNLib::LN_NurbsCurve curve;
		auto x = LNLib::Constants::Pi;
		bool createArc = LNLib::NurbsCurve::CreateArc(center, xAxis, yAxis, 0, 2 * LNLib::Constants::Pi, radius, radius, curve);
		curves.emplace_back(curve);
	}

	std::vector<XYZ> points = {
	
		XYZ(0,0,0),
		XYZ(100,0,0),
		XYZ(200,0,0),
		XYZ(300,0,0)
	
	};

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->SetWindowName("LNLibViewer - BIMCoder Liang (bim.frankliang@foxmail.com)");
	renderWindow->FullScreenOn();
	renderWindow->BordersOn();

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	DisplayCurves(renderer, curves);
	DisplaySurfaces(renderer, surfaces);
	DisplayArrow(renderer, XYZ(0, 0, 0), XYZ(1, 1, 1), 100);
	DisplayPoints(renderer, points);
	/*DisplayMesh(renderer, mesh);*/

	vtkNew<vtkLight> light;
	light->SetLightTypeToSceneLight();
	light->SetPosition(1000, 1000, 1000);
	light->SetFocalPoint(0, 0, 0);
	light->SetIntensity(1.5);
	light->SetColor(1.0, 1.0, 1.0);
	renderer->AddLight(light);

	renderer->SetUseShadows(false);
	renderer->SetTwoSidedLighting(true);
	renderer->SetAmbient(0.2, 0.2, 0.2);

	vtkNew<vtkAxesActor> axesActor;
	vtkNew<vtkTransform>  userTrans;
	userTrans->Update();
	axesActor->SetUserTransform(userTrans);
	axesActor->AxisLabelsOn();
	axesActor->SetTotalLength(100, 100, 100);
	renderer->AddActor(axesActor);

	renderer->GradientBackgroundOn();
	renderer->SetBackground(0, 0, 0);
	renderer->SetBackground2(0.9, 0.9, 0.9);

	vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
	renderWindowInteractor->SetRenderWindow(renderWindow);

	vtkNew<customIteractorStyle> style;
	style->SetFixedAxesActor(axesActor);
	renderWindowInteractor->SetInteractorStyle(style);
	renderWindow->AddRenderer(renderer);

	renderer->ResetCamera();
	renderWindow->Render();
	renderWindowInteractor->Start();

    return 0;
}
