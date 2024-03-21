// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtkOBJImporterInternals_h
#define vtkOBJImporterInternals_h

#include "vtkIOImportModule.h" // For export macro
#include "vtkPolyDataAlgorithm.h"
#include <map>    // for std::map
#include <string> // for std::string
#include <vector> // for std::vector

VTK_ABI_NAMESPACE_BEGIN
class vtkActor;

struct VTKIOIMPORT_EXPORT vtkOBJImportedMaterial
{
  std::string name;
  std::string texture_filename;
  double amb[3];
  double diff[3];
  double spec[3];
  double map_Kd_scale[3];
  double map_Kd_offset[3];
  int illum;
  double reflect;
  double refract;
  double trans;
  double specularPower;
  double glossy;
  double refract_index;
  const char* GetClassName() { return "vtkOBJImportedMaterial"; }
  vtkOBJImportedMaterial();
};

VTKIOIMPORT_EXPORT
void obj_set_material_defaults(vtkOBJImportedMaterial* mtl);

struct vtkOBJImportedPolyDataWithMaterial;

class VTKIOIMPORT_EXPORT vtkOBJPolyDataProcessor : public vtkPolyDataAlgorithm
{
public:
  static vtkOBJPolyDataProcessor* New();
  vtkTypeMacro(vtkOBJPolyDataProcessor, vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  // Description:
  // Specify file name of Wavefront .obj file.
  void SetFileName(const char* arg)
  {
    if (arg == nullptr)
    {
      return;
    }
    if (this->FileName == arg)
    {
      return;
    }
    FileName = std::string(arg);
  }
  void SetMTLfileName(const char* arg)
  {
    if (arg == nullptr)
    {
      return;
    }
    if (this->MTLFileName == arg)
    {
      return;
    }
    MTLFileName = std::string(arg);
    this->DefaultMTLFileName = false;
  }
  void SetTexturePath(const char* arg)
  {
    TexturePath = std::string(arg);
    if (TexturePath.empty())
      return;
#if defined(_WIN32)
    const char sep = '\\';
#else
    const char sep = '/';
#endif
    if (TexturePath.at(TexturePath.size() - 1) != sep)
      TexturePath += sep;
  }
  const std::string& GetTexturePath() const { return TexturePath; }

  const std::string& GetFileName() const { return FileName; }

  const std::string& GetMTLFileName() const { return MTLFileName; }

  vtkSetMacro(VertexScale, double);
  vtkGetMacro(VertexScale, double);
  vtkGetMacro(SuccessParsingFiles, int);

  virtual vtkPolyData* GetOutput(int idx);

  int GetNumberOfOutputs();

  vtkOBJImportedMaterial* GetMaterial(int k);

  std::string GetTextureFilename(int idx); // return string by index

  double VertexScale; // scale vertices by this during import

  std::vector<vtkOBJImportedMaterial*> parsedMTLs;
  std::map<std::string, vtkOBJImportedMaterial*> mtlName_to_mtlData;

  // our internal parsing/storage
  std::vector<vtkOBJImportedPolyDataWithMaterial*> poly_list;

  // what gets returned to client code via GetOutput()
  std::vector<vtkSmartPointer<vtkPolyData>> outVector_of_vtkPolyData;

  std::vector<vtkSmartPointer<vtkActor>> actor_list;
  /////////////////////

  std::vector<vtkOBJImportedMaterial*> ParseOBJandMTL(std::string filename, int& result_code);

  void ReadVertices(bool gotFirstUseMaterialTag, char* pLine, float xyz, int lineNr, double v_scale,
    bool everything_ok, vtkPoints* points, bool use_scale);

protected:
  vtkOBJPolyDataProcessor();
  ~vtkOBJPolyDataProcessor() override;
  int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override
    /*override*/;

  vtkSetMacro(SuccessParsingFiles, int);

  std::string FileName;    // filename (.obj) being read
  std::string MTLFileName; // associated .mtl to *.obj, typically it is *.obj.mtl
  bool DefaultMTLFileName; // tells whether default of *.obj.mtl to be used
  std::string TexturePath;
  int SuccessParsingFiles;

private:
  vtkOBJPolyDataProcessor(const vtkOBJPolyDataProcessor&) = delete;
  void operator=(const vtkOBJPolyDataProcessor&) = delete;
};

class vtkRenderWindow;
class vtkRenderer;
VTKIOIMPORT_EXPORT
void bindTexturedPolydataToRenderWindow(
  vtkRenderWindow* renderWindow, vtkRenderer* renderer, vtkOBJPolyDataProcessor* reader);

VTK_ABI_NAMESPACE_END
#endif
