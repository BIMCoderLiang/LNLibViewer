// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
/**
 * @class   vtkCompositePolyDataMapper
 * @brief   a class that renders hierarchical polygonal data
 *
 * This class uses a set of vtkPolyDataMappers to render input data
 * which may be hierarchical. The input to this mapper may be
 * either vtkPolyData or a vtkCompositeDataSet built from
 * polydata. If something other than vtkPolyData is encountered,
 * an error message will be produced.
 * @sa
 * vtkPolyDataMapper
 */

#ifndef vtkCompositePolyDataMapper_h
#define vtkCompositePolyDataMapper_h

#include "vtkPolyDataMapper.h"

#include "vtkDeprecation.h"         // for VTK_DEPRECATED_IN_9_3_0
#include "vtkRenderingCoreModule.h" // for export macro
#include "vtkStateStorage.h"        // for ivar

#include <array>  // for ColorResult. Remove when double* GetBlockColor gets removed.
#include <memory> // for unique_ptr
#include <vector> // for return

VTK_ABI_NAMESPACE_BEGIN
class vtkActor;
class vtkCompositePolyDataMapperDelegator;
class vtkCompositeDataDisplayAttributes;
class vtkCompositeDataSet;
class vtkDataObjectTreeIterator;
class vtkInformation;
class vtkPolyData;
class vtkRenderer;

class VTKRENDERINGCORE_EXPORT vtkCompositePolyDataMapper : public vtkPolyDataMapper
{
public:
  static vtkCompositePolyDataMapper* New();
  vtkTypeMacro(vtkCompositePolyDataMapper, vtkPolyDataMapper);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Standard method for rendering a mapper. This method will be
   * called by the actor.
   */
  void Render(vtkRenderer* renderer, vtkActor* actor) override;

  ///@{
  /**
   * Standard vtkProp method to get 3D bounds of a 3D prop
   */
  double* GetBounds() VTK_SIZEHINT(6) override;
  void GetBounds(double bounds[6]) override { this->Superclass::GetBounds(bounds); }
  ///@}

  /**
   * Make a shallow copy of this mapper.
   */
  void ShallowCopy(vtkAbstractMapper* mapper) override;

  /**
   * Release the underlying resources associated with this mapper
   */
  void ReleaseGraphicsResources(vtkWindow*) override;

  ///@{
  /**
   * Some introspection on the type of data the mapper will render
   * used by props to determine if they should invoke the mapper
   * on a specific rendering pass.
   */
  bool HasOpaqueGeometry() override;
  bool HasTranslucentPolygonalGeometry() override;
  ///@}

  ///@{
  /**
   * Set/get the composite data set attributes.
   */
  void SetCompositeDataDisplayAttributes(vtkCompositeDataDisplayAttributes* attributes);
  vtkCompositeDataDisplayAttributes* GetCompositeDataDisplayAttributes();
  ///@}

  ///@{
  /**
   * Set/get the visibility for a block given its flat index.
   */
  void SetBlockVisibility(unsigned int index, bool visible);
  bool GetBlockVisibility(unsigned int index);
  void RemoveBlockVisibility(unsigned int index);
  void RemoveBlockVisibilities();
  ///@}

  ///@{
  /**
   * Set/get the color for a block given its flat index.
   */
  void SetBlockColor(unsigned int index, const double color[3]);
  void SetBlockColor(unsigned int index, double r, double g, double b)
  {
    double color[3] = { r, g, b };
    this->SetBlockColor(index, color);
  }
  VTK_DEPRECATED_IN_9_3_0("Use void GetBlockColor(unsigned int index, double color[3])")
  double* GetBlockColor(unsigned int index);
  void GetBlockColor(unsigned int index, double color[3]);
  void RemoveBlockColor(unsigned int index);
  void RemoveBlockColors();
  ///@}

  ///@{
  /**
   * Set/get the opacity for a block given its flat index.
   */
  void SetBlockOpacity(unsigned int index, double opacity);
  double GetBlockOpacity(unsigned int index);
  void RemoveBlockOpacity(unsigned int index);
  void RemoveBlockOpacities();
  ///@}

  ///@{
  /**
   * @see vtkMapper::SetScalarMode
   */
  void SetBlockScalarMode(unsigned int index, int value);
  int GetBlockScalarMode(unsigned int index);
  void RemoveBlockScalarMode(unsigned int index);
  void RemoveBlockScalarModes();
  ///@}

  ///@{
  /**
   * @see vtkMapper::SetArrayAccessMode
   */
  void SetBlockArrayAccessMode(unsigned int index, int value);
  int GetBlockArrayAccessMode(unsigned int index);
  void RemoveBlockArrayAccessMode(unsigned int index);
  void RemoveBlockArrayAccessModes();
  ///@}

  ///@{
  /**
   * @see vtkMapper::SetArrayComponent
   */
  void SetBlockArrayComponent(unsigned int index, int value);
  int GetBlockArrayComponent(unsigned int index);
  void RemoveBlockArrayComponent(unsigned int index);
  void RemoveBlockArrayComponents();
  ///@}

  ///@{
  /**
   * @see vtkMapper::SetArrayId
   */
  void SetBlockArrayId(unsigned int index, int value);
  int GetBlockArrayId(unsigned int index);
  void RemoveBlockArrayId(unsigned int index);
  void RemoveBlockArrayIds();
  ///@}

  ///@{
  /**
   * @see vtkMapper::SetArrayName
   */
  void SetBlockArrayName(unsigned int index, const std::string& value);
  std::string GetBlockArrayName(unsigned int index);
  void RemoveBlockArrayName(unsigned int index);
  void RemoveBlockArrayNames();
  ///@}

  ///@{
  /**
   * @see vtkMapper::SetFieldDataTupleId
   */
  void SetBlockFieldDataTupleId(unsigned int index, vtkIdType value);
  vtkIdType GetBlockFieldDataTupleId(unsigned int index);
  void RemoveBlockFieldDataTupleId(unsigned int index);
  void RemoveBlockFieldDataTupleIds();
  ///@}

  ///@{
  /**
   * If the current 'color by' array is missing on some datasets, color these
   * dataset by the LookupTable's NaN color, if the lookup table supports it.
   * Default is false.
   *
   */
  vtkSetMacro(ColorMissingArraysWithNanColor, bool);
  vtkGetMacro(ColorMissingArraysWithNanColor, bool);
  vtkBooleanMacro(ColorMissingArraysWithNanColor, bool);
  ///@}

  ///@{
  /**
   * Call SetInputArrayToProcess on helpers.
   */
  using vtkAlgorithm::SetInputArrayToProcess;
  void SetInputArrayToProcess(
    int idx, int port, int connection, int fieldAssociation, const char* name) override;
  void SetInputArrayToProcess(
    int idx, int port, int connection, int fieldAssociation, int fieldAttributeType) override;
  void SetInputArrayToProcess(int idx, vtkInformation* info) override;
  ///@}

  /**
   * Accessor to the ordered list of PolyData that we last drew.
   */
  std::vector<vtkPolyData*> GetRenderedList();

  /**
   * allows a mapper to update a selections color buffers
   * Called from a prop which in turn is called from the selector
   */
  void ProcessSelectorPixelBuffers(
    vtkHardwareSelector* sel, std::vector<unsigned int>& pixeloffsets, vtkProp* prop) override;

  /**
   * A convenience method for enabling/disabling  the VBO's shift+scale transform.
   */
  void SetVBOShiftScaleMethod(int method) override;

  /**
   * Pause updates of shift-scale parameters based on camera position.
   *
   * This override passes the information to all instances in \a Helpers .
   */
  void SetPauseShiftScale(bool pauseShiftScale) override;

  /**
   * Overridden to include vtkCompositeDataDisplayAttributes' mtime.
   */
  vtkMTimeType GetMTime() override;

  ///@{
  /**
   * By default, this class uses the dataset's point and cell ids during
   * rendering. However, one can override those by specifying cell and point
   * data arrays to use instead. Currently, only vtkIdType array is supported.
   * Set to NULL string (default) to use the point ids instead.
   */
  vtkSetStringMacro(PointIdArrayName);
  vtkGetStringMacro(PointIdArrayName);
  vtkSetStringMacro(CellIdArrayName);
  vtkGetStringMacro(CellIdArrayName);
  ///@}

  ///@{
  /**
   * If this class should override the process id using a data-array,
   * set this variable to the name of the array to use. It must be a
   * point-array.
   */
  vtkSetStringMacro(ProcessIdArrayName);
  vtkGetStringMacro(ProcessIdArrayName);
  ///@}

  ///@{
  /**
   * Generally, this class can render the composite id when iterating
   * over composite datasets. However in some cases (as in AMR), the rendered
   * structure may not correspond to the input data, in which case we need
   * to provide a cell array that can be used to render in the composite id in
   * selection passes. Set to NULL (default) to not override the composite id
   * color set by vtkCompositePainter if any.
   * The array *MUST* be a cell array and of type vtkUnsignedIntArray.
   */
  vtkSetStringMacro(CompositeIdArrayName);
  vtkGetStringMacro(CompositeIdArrayName);
  ///@}

protected:
  vtkCompositePolyDataMapper();
  ~vtkCompositePolyDataMapper() override;

  MapperHashType InsertPolyData(vtkPolyData* polydata, const unsigned int& flatIndex);

  /**
   * We need to override this method because the standard streaming
   * demand driven pipeline is not what we want - we are expecting
   * hierarchical data as input
   */
  vtkExecutive* CreateDefaultExecutive() override;

  /**
   * Need to define the type of data handled by this mapper.
   */
  int FillInputPortInformation(int port, vtkInformation* info) override;

  /**
   * This is the build method for creating the delegator.
   * A delegator has definitions for a single batch element
   * and methods to insert, get, clear a whole batch.
   * The delegator also provides the underlying mapper through
   * delegator->GetDelegate()
   */
  virtual vtkCompositePolyDataMapperDelegator* CreateADelegator();

  /**
   * Invoked just before all delegators render their datasets. You may
   * access the built delegators this way to do custom initialization
   * that is specific to the domain of your custom delegator.
   */
  virtual void PreRender(const std::vector<vtkSmartPointer<vtkCompositePolyDataMapperDelegator>>&,
    vtkRenderer*, vtkActor*)
  {
  }

  /**
   * Invoked just after all delegators render their datasets. You may
   * access the built delegators this way to performa a finalize action.
   */
  virtual void PostRender(const std::vector<vtkSmartPointer<vtkCompositePolyDataMapperDelegator>>&,
    vtkRenderer*, vtkActor*)
  {
  }

  /**
   * Creates an empty polydata mapper and asks the mapper to hash the polydata.
   */
  vtkPolyDataMapper::MapperHashType GenerateHash(vtkPolyData* polydata) override;

  /**
   * Initialize an iterator for the composite dataset.
   */
  virtual vtkDataObjectTreeIterator* MakeAnIterator(vtkCompositeDataSet* dataset);

  /**
   * Need to loop over the hierarchy to compute bounds
   */
  void ComputeBounds() override;

  bool RecursiveHasTranslucentGeometry(vtkDataObject* dobj, unsigned int& flat_index);

  void BuildRenderValues(
    vtkRenderer* renderer, vtkActor* actor, vtkDataObject* dobj, unsigned int& flat_index);

  /**
   * A prototype of the object factory override mapper.
   * This prototype is reused to hash multiple polydata instead
   * of creating a new mapper every single time a hash needs to be computed.
   */
  vtkNew<vtkPolyDataMapper> PrototypeMapper;

  /**
   * Composite data set attributes.
   */
  vtkSmartPointer<vtkCompositeDataDisplayAttributes> CompositeAttributes;

  /**
   * If the current 'color by' array is missing on some datasets, color these
   * dataset by the LookupTable's NaN color, if the lookup table supports it.
   */
  bool ColorMissingArraysWithNanColor = false;

  /**
   * Time stamp for computation of bounds.
   */
  vtkTimeStamp BoundsMTime;

  // additional picking indirection
  char* PointIdArrayName = nullptr;
  char* CellIdArrayName = nullptr;
  char* ProcessIdArrayName = nullptr;
  char* CompositeIdArrayName = nullptr;

  vtkStateStorage TranslucentState;
  bool HasTranslucentGeometry = false;
  vtkStateStorage RenderValuesState;
  vtkStateStorage TempState;
  vtkTimeStamp DelegatorMTime;

private:
  vtkCompositePolyDataMapper(const vtkCompositePolyDataMapper&) = delete;
  void operator=(const vtkCompositePolyDataMapper&) = delete;

  std::array<double, 3> ColorResult = {};

  class vtkInternals;
  std::unique_ptr<vtkInternals> Internals;
};

VTK_ABI_NAMESPACE_END
#endif
