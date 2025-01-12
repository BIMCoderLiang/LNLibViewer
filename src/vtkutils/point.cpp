/*
 * Author:
 * 2025/01/12 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 *
 * Use of this source code is governed by a GPL-3.0 license that can be found in
 * the LICENSE file.
 */

#include "point.h"
#include <vtkActor.h>
#include <vtkNew.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>

void DisplayPoints(vtkSmartPointer<vtkRenderer> renderer, std::vector<XYZ> points)
{
	for (int i = 0; i < points.size(); i++)
	{
		XYZ point = points[i];
		vtkNew<vtkSphereSource> source;
		source->SetRadius(2);
		source->SetCenter(point.GetX(), point.GetY(), point.GetZ());
		source->SetPhiResolution(10);

		vtkNew<vtkPolyDataMapper> mapper;
		mapper->SetInputConnection(source->GetOutputPort());
		vtkNew<vtkActor> actor;
		actor->SetMapper(mapper);

		renderer->AddActor(actor);
	}
}

