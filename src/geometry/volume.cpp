/*
 * Author:
 * 2026/05/27 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 *
 * Use of this source code is governed by a GPL-3.0 license that can be found in
 * the LICENSE file.
 */

#include "volume.h"
#include "LNObject.h"
#include "NurbsVolume.h"
#include "curve.h"
#include "UVW.h"
#include <vtkRenderer.h>

using namespace LNLib;

void DisplayVolumes(vtkSmartPointer<vtkRenderer> renderer, const std::vector<LN_NurbsVolume>& volumes)
{
	
	for (int i = 0; i < volumes.size(); i++)
	{
		std::vector<LN_NurbsCurve> curves;

		LNLib::LN_NurbsVolume volume = volumes[i];
		std::vector<double> kvU = volume.KnotVectorU;
		std::vector<double> kvV = volume.KnotVectorV;
		std::vector<double> kvW = volume.KnotVectorW;

		double kvUmin = kvU[0];
		double kvUmax = kvU[kvU.size() - 1];
		double kvVmin = kvV[0];
		double kvVmax = kvV[kvV.size() - 1];
		double kvWmin = kvW[0];
		double kvWmax = kvW[kvW.size() - 1];

		for (int i = 0; i < kvU.size(); i++)
		{
			double currentU = kvU[i];
			for (int j = 0; j < kvV.size(); j++)
			{
				double currentV = kvV[j];
				LN_NurbsCurve curve = NurbsVolume::GetIsoCurve(volume, LNLib::UVW(currentU, currentV, -1));
				curves.emplace_back(curve);
			}
		}

		for (int i = 0; i < kvV.size(); i++)
		{
			double currentV = kvV[i];
			for (int j = 0; j < kvW.size(); j++)
			{
				double currentW = kvW[j];
				LN_NurbsCurve curve = NurbsVolume::GetIsoCurve(volume, LNLib::UVW(-1, currentV, currentW));
				curves.emplace_back(curve);
			}
		}

		for (int i = 0; i < kvU.size(); i++)
		{
			double currentU = kvU[i];
			for (int j = 0; j < kvW.size(); j++)
			{
				double currentW = kvW[j];
				LN_NurbsCurve curve = NurbsVolume::GetIsoCurve(volume, LNLib::UVW(currentU, -1, currentW));
				curves.emplace_back(curve);
			}
		}

		DisplayCurves(renderer, curves);
	}
}
