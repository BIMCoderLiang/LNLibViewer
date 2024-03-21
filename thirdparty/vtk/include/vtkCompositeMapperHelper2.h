// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause

#ifndef vtkCompositeMapperHelper2_h
#define vtkCompositeMapperHelper2_h

#include "vtkColor.h"                  // class uses vtkColor
#include "vtkDeprecation.h"            // For VTK_DEPRECATED_IN_9_3_0
#include "vtkRenderingOpenGL2Module.h" // for export macro
#include "vtk_glew.h"                  // for OpenGL enums
// clang-format off
// Must be included after vtk_glew.h for GL_ES_VERSION_3_0
#ifndef GL_ES_VERSION_3_0
#include "vtkOpenGLPolyDataMapper.h"
#define vtkOpenGLPolyDataMapperImplementation vtkOpenGLPolyDataMapper
#else
#include "vtkOpenGLES30PolyDataMapper.h"
#define vtkOpenGLPolyDataMapperImplementation vtkOpenGLES30PolyDataMapper
#endif
// clang-format on

VTK_ABI_NAMESPACE_BEGIN
class vtkPolyData;
class vtkCompositePolyDataMapper2;

// this class encapsulates values tied to a
// polydata

class VTK_DEPRECATED_IN_9_3_0(
  "Please use vtkCompositePolyDataMapper instead") vtkCompositeMapperHelperData
{
public:
  vtkPolyData* Data;
  unsigned int FlatIndex;
  double Opacity;
  bool IsOpaque;
  bool Visibility;
  bool Pickability;
  bool OverridesColor;
  vtkColor3d AmbientColor;
  vtkColor3d DiffuseColor;
  vtkColor3d SelectionColor;
  double SelectionOpacity;

  bool Marked;

  unsigned int StartVertex;
  unsigned int NextVertex;

  // point line poly strip edge stripedge
  unsigned int StartIndex[vtkOpenGLPolyDataMapper::PrimitiveEnd];
  unsigned int NextIndex[vtkOpenGLPolyDataMapper::PrimitiveEnd];

  // stores the mapping from vtk cells to gl_PrimitiveId
  vtkNew<vtkOpenGLCellToVTKCellMap> CellCellMap;
};

//===================================================================
/// Helper class for vtkCompositePolyDataMapper2 that is a subclass of vtkOpenGLPolyDataMapper
class VTK_DEPRECATED_IN_9_3_0("Please use vtkCompositePolyDataMapper instead")
  VTKRENDERINGOPENGL2_EXPORT vtkCompositeMapperHelper2
  : public vtkOpenGLPolyDataMapperImplementation
{
public:
  static vtkCompositeMapperHelper2* New();
  vtkTypeMacro(vtkCompositeMapperHelper2, vtkOpenGLPolyDataMapperImplementation);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  void SetParent(vtkCompositePolyDataMapper2* p) { this->Parent = p; }

  vtkCompositeMapperHelperData* AddData(vtkPolyData* pd, unsigned int flatIndex);

  /**
   * Implemented by sub classes. Actual rendering is done here.
   */
  void RenderPiece(vtkRenderer* ren, vtkActor* act) override;

  ///@{
  /// keep track of what data is being used as the multiblock
  /// can change
  void ClearMark();
  void RemoveUnused();
  bool GetMarked() { return this->Marked; }
  void SetMarked(bool v) { this->Marked = v; }
  ///@}

  /**
   * Accessor to the ordered list of PolyData that we last drew.
   */
  std::vector<vtkPolyData*> GetRenderedList() const;

  /**
   * allows a mapper to update a selections color buffers
   * Called from a prop which in turn is called from the selector
   */
  void ProcessSelectorPixelBuffers(
    vtkHardwareSelector* sel, std::vector<unsigned int>& pixeloffsets, vtkProp* prop) override;

  virtual void ProcessCompositePixelBuffers(vtkHardwareSelector* sel, vtkProp* prop,
    vtkCompositeMapperHelperData* hdata, std::vector<unsigned int>& mypixels);

protected:
  vtkCompositePolyDataMapper2* Parent;
  std::map<vtkPolyData*, vtkCompositeMapperHelperData*> Data;

  bool Marked;

  /// handle updating shift scale based on pose changes
  void UpdateCameraShiftScale(vtkRenderer* ren, vtkActor* actor) override;

  vtkCompositeMapperHelper2() { this->Parent = nullptr; };
  ~vtkCompositeMapperHelper2() override;

  void DrawIBO(vtkRenderer* ren, vtkActor* actor, int primType, vtkOpenGLHelper& CellBO,
    GLenum mode, int pointSize);

  virtual void SetShaderValues(
    vtkShaderProgram* prog, vtkCompositeMapperHelperData* hdata, size_t primOffset);

  /**
   * Make sure appropriate shaders are defined, compiled and bound.  This method
   * orchistrates the process, much of the work is done in other methods
   */
  void UpdateShaders(vtkOpenGLHelper& cellBO, vtkRenderer* ren, vtkActor* act) override;

  /**
   * Perform string replacements on the shader templates, called from
   * ReplaceShaderValues
   */
  void ReplaceShaderColor(
    std::map<vtkShader::Type, vtkShader*> shaders, vtkRenderer* ren, vtkActor* act) override;

  /**
   * Does the VBO/IBO need to be rebuilt
   */
  bool GetNeedToRebuildBufferObjects(vtkRenderer* ren, vtkActor* act) override;

  /**
   * Build the VBO/IBO, called by UpdateBufferObjects
   */
  void BuildBufferObjects(vtkRenderer* ren, vtkActor* act) override;
  virtual void AppendOneBufferObject(vtkRenderer* ren, vtkActor* act,
    vtkCompositeMapperHelperData* hdata, vtkIdType& flat_index, std::vector<unsigned char>& colors,
    std::vector<float>& norms);

  /**
   * Build the selection IBOs, called by UpdateBufferObjects
   */
  void BuildSelectionIBO(
    vtkPolyData* poly, std::vector<unsigned int> (&indices)[4], vtkIdType offset) override;

  /**
   * Returns if we can use texture maps for scalar coloring. Note this doesn't
   * say we "will" use scalar coloring. It says, if we do use scalar coloring,
   * we will use a texture. Always off for this mapper.
   */
  int CanUseTextureMapForColoring(vtkDataObject*) override;

  std::vector<unsigned int> VertexOffsets;

  // vert line poly strip edge stripedge
  std::vector<unsigned int> IndexArray[PrimitiveEnd];

  void RenderPieceDraw(vtkRenderer* ren, vtkActor* act) override;

  bool PrimIDUsed;
  bool OverideColorUsed;

  vtkHardwareSelector* CurrentSelector;

  /// used by the hardware selector
  std::vector<std::vector<unsigned int>> PickPixels;

  std::map<vtkAbstractArray*, vtkDataArray*> ColorArrayMap;

private:
  vtkCompositeMapperHelper2(const vtkCompositeMapperHelper2&) = delete;
  void operator=(const vtkCompositeMapperHelper2&) = delete;
};

VTK_ABI_NAMESPACE_END
#endif
