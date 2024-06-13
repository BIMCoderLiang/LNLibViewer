#include "surface.h"
/*
 * Author:
 * 2024/03/21 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 * 微信公众号：BIMCoder梁老师
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

#include "customIteractorStyle.h"

#include <vtkNew.h>
#include <vtkAssembly.h>
#include <vtkAssemblyPath.h>
#include <vtkAxesActor.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkFollower.h>
#include <vtkTriangle.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolygon.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkVectorText.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
using namespace LNLib;

namespace {
	//----------------------------------------------------------------------------
	class vtkPositionCallback : public vtkCallbackCommand
	{
	public:
		static vtkPositionCallback* New()
		{
			return new vtkPositionCallback;
		}

		void Execute(vtkObject* vtkNotUsed(caller), unsigned long vtkNotUsed(event),
			void* vtkNotUsed(callData))
		{
			this->Axes->InitPathTraversal();
			vtkAssemblyPath* path = 0;
			int count = 0;
			vtkFollower* followers[3] = { this->XLabel, this->YLabel, this->ZLabel };
			int followerId = 0;
			while ((path = this->Axes->GetNextPath()) != NULL)
			{
				if (count++ > 2)
				{
					vtkProp3D* prop3D =
						static_cast<vtkProp3D*>(path->GetLastNode()->GetViewProp());
					if (prop3D)
					{
						prop3D->PokeMatrix(path->GetLastNode()->GetMatrix());
						followers[followerId]->SetPosition(prop3D->GetCenter());
						followerId++;
						prop3D->PokeMatrix(NULL);
					}
				}
			}
		}

		vtkPositionCallback() : XLabel(0), YLabel(0), ZLabel(0), Axes(0)
		{
		}

		vtkFollower* XLabel;
		vtkFollower* YLabel;
		vtkFollower* ZLabel;
		vtkAssembly* Axes;
	};

} // namespace

void Test_TessllateSurface()
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

	LN_NurbsSurface surface;
	surface.DegreeU = degreeU;
	surface.DegreeV = degreeV;
	surface.KnotVectorU = kvU;
	surface.KnotVectorV = kvV;
	surface.ControlPoints = controlPoints;

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
	double r = 255.0 / 255.0;
	double g = 0.0 / 255.0;
	double b = 0.0 / 255.0;
	actor->GetProperty()->SetColor(r, g, b);

	// Visualize
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	vtkSmartPointer<vtkRenderWindow> renderWindow =	vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->SetWindowName("Tessellate Surface");
	
	vtkNew<vtkAxesActor> axesActor;
	vtkNew<vtkTransform>  userTrans;
	userTrans->Update();
	axesActor->SetUserTransform(userTrans);
	axesActor->AxisLabelsOn();
	axesActor->SetTotalLength(100, 100, 100);

	renderer->AddActor(axesActor);
	renderer->SetBackground(0, 0, 0);

	vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
	renderWindowInteractor->SetRenderWindow(renderWindow);

	vtkNew<customIteractorStyle> style;
	style->SetFixedAxesActor(axesActor);
	renderWindowInteractor->SetInteractorStyle(style);

	renderWindow->AddRenderer(renderer);

	renderer->ResetCamera();
	renderWindow->Render();
	renderWindowInteractor->Start();

}
