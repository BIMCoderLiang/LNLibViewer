/*
 * Author:
 * 2024/03/21 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 * 微信公众号：BIMCoder梁老师
 *
 * Use of this source code is governed by a GPL-3.0 license that can be found in
 * the LICENSE file.
 */

#include "customIteractorStyle.h"
#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);

void customIteractorStyle::OnMouseWheelForward()
{
    ScaleAxes(m_ScaleFator[0]);
    vtkInteractorStyleTrackballCamera::OnMouseWheelForward();
}

void customIteractorStyle::OnMouseWheelBackward()
{
    ScaleAxes(m_ScaleFator[1]);
    vtkInteractorStyleTrackballCamera::OnMouseWheelBackward();
}

void customIteractorStyle::SetFixedAxesActor(vtkAxesActor* actor)
{
    if (this->m_axesActor != actor)
    {
        this->m_axesActor = actor;
    }
}

customIteractorStyle::customIteractorStyle()
{
    m_axesActor = nullptr;

    double wheelFactor = 0;
    wheelFactor = this->MotionFactor * (-0.2) * this->MouseWheelMotionFactor;
    m_ScaleFator[0] = pow(1.1, wheelFactor); // forward wheel
    wheelFactor = this->MotionFactor * 0.2 * this->MouseWheelMotionFactor;
    m_ScaleFator[1] = pow(1.1, wheelFactor); // back wheel
}

customIteractorStyle::~customIteractorStyle()
{
    m_axesActor = nullptr;
}

void customIteractorStyle::ScaleAxes(double factor)
{
    if (m_axesActor == nullptr)
    {
        return;
    }
    vtkNew<vtkTransform> scaleTrans;
    scaleTrans->Scale(factor, factor, factor);
    scaleTrans->Update();


    vtkNew<vtkTransform> trans;
    trans->Concatenate(m_axesActor->GetUserTransform());
    trans->Concatenate(scaleTrans);
    trans->Update();
    m_axesActor->SetUserTransform(trans);
}