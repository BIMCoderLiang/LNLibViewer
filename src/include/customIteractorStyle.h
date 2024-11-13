/*
 * Author:
 * 2024/06/13 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 *
 * Use of this source code is governed by a GPL-3.0 license that can be found in
 * the LICENSE file.
 */

 //customIteractorStyle.h
#include <iostream>
#include <vtkSmartPointer.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTransform.h>
#include <vtkAxesActor.h>

class customIteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
    static customIteractorStyle* New() { return new customIteractorStyle(); }
    void SetFixedAxesActor(vtkAxesActor* actor);

protected:
    customIteractorStyle();
    ~customIteractorStyle() override;
    void ScaleAxes(double factor);

    double m_ScaleFator[2];
    vtkAxesActor* m_axesActor;
};