/*
 * Author:
 * 2025/07/10 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 *
 * Use of this source code is governed by a GPL-3.0 license that can be found in
 * the LICENSE file.
 */

#include "mesh.h"
#include "LNObject.h"
#include "Constants.h"

#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkProperty.h>
#include <vtkTriangleFilter.h>

#include <random>
using namespace LNLib;

vtkSmartPointer<vtkPolyData> ConvertToPolyData(const LN_Mesh& mesh) {
    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();

    for (const auto& vertex : mesh.Vertices) {
        points->InsertNextPoint(vertex.X(), vertex.Y(), vertex.Z());
    }
    polyData->SetPoints(points);

    for (const auto& face : mesh.Faces) {
        vtkSmartPointer<vtkIdList> idList = vtkSmartPointer<vtkIdList>::New();
        for (int id : face) {
            idList->InsertNextId(id);
        }
        cells->InsertNextCell(idList);
    }
    polyData->SetPolys(cells);

    if (!mesh.Normals.empty() && !mesh.NormalIndices.empty() &&
        mesh.NormalIndices.size() == mesh.Vertices.size()) {

        vtkSmartPointer<vtkDoubleArray> normals = vtkSmartPointer<vtkDoubleArray>::New();
        normals->SetNumberOfComponents(3);
        normals->SetName("Normals");

        for (size_t i = 0; i < mesh.Vertices.size(); ++i) {
            int normalIdx = mesh.NormalIndices[i];
            if (normalIdx >= 0 && normalIdx < mesh.Normals.size()) {
                const XYZ& normal = mesh.Normals[normalIdx];
                double n[3] = { normal.X(), normal.Y(), normal.Z() };
                normals->InsertNextTuple(n);
            }
            else {
                double n[3] = { 0.0, 0.0, 1.0 };
                normals->InsertNextTuple(n);
            }
        }
        polyData->GetPointData()->SetNormals(normals);
    }

    if (!mesh.UVs.empty() && !mesh.UVIndices.empty() &&
        mesh.UVIndices.size() == mesh.Vertices.size()) {

        vtkSmartPointer<vtkDoubleArray> texCoords = vtkSmartPointer<vtkDoubleArray>::New();
        texCoords->SetNumberOfComponents(2);
        texCoords->SetName("TextureCoordinates");

        for (size_t i = 0; i < mesh.Vertices.size(); ++i) {
            int uvIdx = mesh.UVIndices[i];
            if (uvIdx >= 0 && uvIdx < mesh.UVs.size()) {
                const UV& uv = mesh.UVs[uvIdx];
                double uvVal[2] = { uv.U(), uv.V() };
                texCoords->InsertNextTuple(uvVal);
            }
            else {
                double uvVal[2] = { 0.0, 0.0 };
                texCoords->InsertNextTuple(uvVal);
            }
        }
        polyData->GetPointData()->SetTCoords(texCoords);
    }

    vtkSmartPointer<vtkTriangleFilter> triangleFilter = vtkSmartPointer<vtkTriangleFilter>::New();
    triangleFilter->SetInputData(polyData);
    triangleFilter->Update();

    return triangleFilter->GetOutput();
}

void DisplayMesh(vtkSmartPointer<vtkRenderer> renderer, const LNLib::LN_Mesh& mesh)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(50, 250);

    // Create a PolyData
    vtkSmartPointer<vtkPolyData> polygonPolyData = ConvertToPolyData(mesh);

    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polygonPolyData);
    mapper->SetScalarVisibility(false);

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    double r = distrib(gen) / 255.0;
    double g = distrib(gen) / 255.0;
    double b = distrib(gen) / 255.0;
    actor->GetProperty()->SetColor(r, g, b);
    mapper->SetScalarVisibility(false);
    renderer->AddActor(actor);
}
