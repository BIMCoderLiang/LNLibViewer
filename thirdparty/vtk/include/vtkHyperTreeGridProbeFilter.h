// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
/**
 * @class   vtkHyperTreeGridProbeFilter
 * @brief   Probe a vtkHyperTreeGrid
 *
 * Heavily modeled after the vtkProbeFilter, this class
 *  is meant to be used to probe vtkHyperTreeGrid objects.
 *
 */

#ifndef vtkHyperTreeGridProbeFilter_h
#define vtkHyperTreeGridProbeFilter_h

#include "vtkDataSetAlgorithm.h"
#include "vtkFiltersCoreModule.h" //For export Macro
#include "vtkNew.h"               //For init in header
#include "vtkSmartPointer.h"      //For members

VTK_ABI_NAMESPACE_BEGIN
class vtkCharArray;
class vtkIdList;
class vtkIdTypeArray;
class vtkDataSet;
class vtkHyperTreeGrid;
class vtkHyperTreeGridLocator;

class VTKFILTERSCORE_EXPORT vtkHyperTreeGridProbeFilter : public vtkDataSetAlgorithm
{
public:
  vtkTypeMacro(vtkHyperTreeGridProbeFilter, vtkDataSetAlgorithm);

  void PrintSelf(ostream& os, vtkIndent indent) override;

  static vtkHyperTreeGridProbeFilter* New();

  ///@{
  /**
   * Specify the data set that will be probed at the input points.
   * The Input gives the geometry (the points and cells) for the output,
   * while the Source is probed (interpolated) to generate the scalars,
   * vectors, etc. for the output points based on the point locations.
   */
  void SetSourceData(vtkHyperTreeGrid* source);
  vtkHyperTreeGrid* GetSource();
  ///@}

  /**
   * Specify the data set that will be probed at the input points.
   * The Input gives the geometry (the points and cells) for the output,
   * while the Source is probed (interpolated) to generate the scalars,
   * vectors, etc. for the output points based on the point locations.
   */
  void SetSourceConnection(vtkAlgorithmOutput* algOutput);

  ///@{
  /**
   * Set and get the locator object
   */
  virtual vtkHyperTreeGridLocator* GetLocator();
  virtual void SetLocator(vtkHyperTreeGridLocator*);
  ///@}

  ///@{
  /**
   * Shallow copy the input cell data arrays to the output.
   * Off by default.
   */
  vtkSetMacro(PassCellArrays, bool);
  vtkBooleanMacro(PassCellArrays, bool);
  vtkGetMacro(PassCellArrays, bool);
  ///@}
  ///@{
  /**
   * Shallow copy the input point data arrays to the output
   * Off by default.
   */
  vtkSetMacro(PassPointArrays, bool);
  vtkBooleanMacro(PassPointArrays, bool);
  vtkGetMacro(PassPointArrays, bool);
  ///@}

  ///@{
  /**
   * Set whether to pass the field-data arrays from the Input i.e. the input
   * providing the geometry to the output. On by default.
   */
  vtkSetMacro(PassFieldArrays, bool);
  vtkBooleanMacro(PassFieldArrays, bool);
  vtkGetMacro(PassFieldArrays, bool);
  ///@}

  ///@{
  /**
   * Returns the name of the char array added to the output with values 1 for
   * valid points and 0 for invalid points.
   * Set to "vtkValidPointMask" by default.
   */
  vtkSetMacro(ValidPointMaskArrayName, std::string);
  vtkGetMacro(ValidPointMaskArrayName, std::string);
  ///@}

  ///@{
  /**
   * Get the list of point ids in the output that contain attribute data
   * from the source.
   */
  vtkIdTypeArray* GetValidPoints();
  ///@}

  ///@{
  /**
   * Get/Set tolerance used when finding points in the HTG source.
   * Overridden when ComputeTolerance == true.
   *
   * Default is 0.0
   */
  vtkSetMacro(Tolerance, double);
  vtkGetMacro(Tolerance, double);
  ///@}

  ///@{
  /**
   * Get/Set whether or not to compute the tolerance automatically for
   * when finding points in the HTG source. If false use the tolerance
   * from SetTolerance .
   *
   * Default is true
   */
  vtkSetMacro(ComputeTolerance, bool);
  vtkGetMacro(ComputeTolerance, bool);
  ///@}

protected:
  ///@{
  /**
   * Construction methods
   */
  vtkHyperTreeGridProbeFilter();
  ~vtkHyperTreeGridProbeFilter() override;
  ///@}

  ///@{
  /**
   * Methods for processing requests
   */
  int RequestInformation(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;
  int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;
  int RequestUpdateExtent(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;
  ///@}

  ///@{
  /**
   * Input port should have 2 inputs: input (a dataset) and a source (an HTG).
   * Output should be same as input
   */
  int FillInputPortInformation(int, vtkInformation*) override;
  ///@}

  ///@{
  /**
   * Helper method for initializing the output and local arrays for all processes
   */
  bool Initialize(vtkDataSet* input, vtkHyperTreeGrid* source, vtkDataSet* output);

  /**
   * Helper method for passing data from input to output
   */
  bool PassAttributeData(vtkDataSet* input, vtkDataSet* output);

  /**
   * Helper method for performing the probing
   */
  bool DoProbing(
    vtkDataSet* input, vtkHyperTreeGrid* source, vtkDataSet* output, vtkIdList* localPointIds);

  /**
   * Helper method for reducing the data after probing
   */
  bool Reduce(vtkHyperTreeGrid* source, vtkDataSet* output, vtkIdList* localPointIds);

  /**
   * Helper method for filling arrays with default values
   */
  void FillDefaultArray(vtkAbstractArray* aa) const;

  /**
   * Helper method for dealing with arrays coming from remote locations during the reduce operation
   */
  void DealWithRemote(vtkIdList* remotePointIds, vtkDataSet* remoteOutput, vtkHyperTreeGrid* source,
    vtkDataSet* totOutput);
  ///@}

  vtkSmartPointer<vtkHyperTreeGridLocator> Locator;

  bool PassCellArrays = false;
  bool PassPointArrays = false;
  bool PassFieldArrays = true;
  double Tolerance = 0.0;
  bool ComputeTolerance = true;

  std::string ValidPointMaskArrayName = "vtkValidPointMask";
  vtkNew<vtkIdTypeArray> ValidPoints;
  vtkSmartPointer<vtkCharArray> MaskPoints;

private:
  vtkHyperTreeGridProbeFilter(const vtkHyperTreeGridProbeFilter&) = delete;
  void operator=(const vtkHyperTreeGridProbeFilter&) = delete;

}; // vtkHyperTreeGridProbeFilter

VTK_ABI_NAMESPACE_END
#endif // vtkHyperTreeGridProbeFilter_h
