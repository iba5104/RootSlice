#define _USE_MATH_DEFINES
#include <cmath>
#include <regex>
#include "rsDataOutput.h"
/// The same;


void rsDataOutput::DataOutputName(const char* dataOutputNameInput)
{
	dataOutputName = dataOutputNameInput;
}

/** \brief CorticalDataOutput;
 *
 * \param rsSourceCorticalDB RsSourceCorticalDB;
 *
 */
void rsDataOutput::CorticalDataOutputCalculate (rsSourceCorticalDB* RsSourceCorticalDB)
{
	vector<int>::iterator itVecNum;
	vector<double>::iterator itVecAddRadius;

	corticalInnermostCellDiameter = RsSourceCorticalDB->corticalCellAddRadiusMin;

	if (corticalInnermostCellDiameter == 0)
	{
		corticalInnermostCellDiameter = RsSourceCorticalDB->corticalInnermostCellDiameterCalculate;
		corticalInnermostCellDiameter = double(int((corticalInnermostCellDiameter + 0.05) * 10)) / 10;
	}

	gapCellWall = RsSourceCorticalDB->gapCellWall;
	gapCytoTono = RsSourceCorticalDB->gapCytoTono;

	steleRadius = baseRadius;
	cortexThickness = RsSourceCorticalDB->boundaryRadius - baseRadius;
	cortexHeight = totalHeight;

	/// for volume calculation of 1 cm root segment, we need to mutiply 450 / 10000;
	// Jagdeep 5-14-2020 This ratio represents the ratio of simualted segment by 1 cm long segment.
	rootSegment1cmRatio = 10000 / totalHeight;
	
	/// The ratio of volume accupied by air;
	//airSpaceRatio = 0.95;
	/// sectionVolume = the volume without epidermis;

	ofstream fout(getFolderName() + "individual_cortical_cell_volume.csv", ios::app);

	sectionVolume = M_PI * RsSourceCorticalDB->boundaryRadius * RsSourceCorticalDB->boundaryRadius * totalHeight;
	//*rootSegment1cmRatio;

	cortexTheoreticalVolume =
		M_PI * (RsSourceCorticalDB->boundaryRadius * RsSourceCorticalDB->boundaryRadius - baseRadius * baseRadius)
		* totalHeight; //*rootSegment1cmRatio;

	cortex2SectionRatio = cortexTheoreticalVolume / sectionVolume;
	int i;

	/// corticalTotalCellNum;
	corticalTotalCellNum = 0;
	double corticalperRingCellNum = 0;
	for (itVecNum = RsSourceCorticalDB->corticalCellNumDB.begin(), i = 1;
		itVecNum != RsSourceCorticalDB->corticalCellNumDB.end();
		itVecNum++, i++)
	{
		corticalTotalCellNum += *itVecNum;
		corticalperRingCellNum = *itVecNum;
		corticalRingNum = i;
		fout << "CCFN,Number of Cells,Cortex Theoretical Volume,Section Volume,Total Length" << endl;
		fout << i << "," << corticalperRingCellNum << "," << cortexTheoreticalVolume << "," << sectionVolume << "," << totalHeight << endl;
	}

	/*******************************************************************************
	corticalTotalCellVolume;
	********************************************************************************/
	map<int, vector< vector<double> > >::iterator itMap;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator           itVec1;
	/// declare int;
	int iRingNum;
	int sliceTempNum;

	corticalTotalCellVolume = 0;
	double corticalTotalCellVolume_each_ring = 0;

	fout << endl << endl << "CCFN,Total Cell Volume,Pure Cell Volume,Vacuole Volume,Pure Cell plus PM Volume" << endl;
	vector<string> lines;

	for (iRingNum = 0, itMap = RsSourceCorticalDB->objectHeightDB.begin();
		itMap != RsSourceCorticalDB->objectHeightDB.end();
		iRingNum++, itMap++)
	{
		for (i = 0, itVec2 = (*itMap).second.begin(); itVec2 != (*itMap).second.end(); i++, itVec2++)
		{
			for (sliceTempNum = 0, itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				sliceTempNum++, itVec1++)
			{
				// Volume of cuboid
				corticalTotalCellVolume += RsSourceCorticalDB->objectVerticalDB[iRingNum] *
					RsSourceCorticalDB->circleSegmentLengthDB[iRingNum][i] *
					RsSourceCorticalDB->objectHeightDB[iRingNum][i][sliceTempNum] * 8;

				/////Volume of cylinder
				corticalTotalCellVolume_each_ring = M_PI * RsSourceCorticalDB->objectVerticalDB[iRingNum] *
					RsSourceCorticalDB->objectVerticalDB[iRingNum] *
					RsSourceCorticalDB->objectHeightDB[iRingNum][i][sliceTempNum];
			}
		}
		string line = to_string(iRingNum + 1) + "," + to_string(corticalTotalCellVolume_each_ring);
		lines.push_back(line);
		//fout << "CCFN," << iRingNum + 1 << ",corticalTotalCellVolume_each_ring," << corticalTotalCellVolume_each_ring << ",Totallength," << totalHeight << endl;
	}

	/// for 1 cm root segment, we need to mutiply rootSegment1cmRatio;
	corticalTotalCellVolume = corticalTotalCellVolume; //*airSpaceRatio; //* rootSegment1cmRatio;


	/*******************************************************************************
	corticalPureCellVolume;
	********************************************************************************/
	corticalPureCellVolume = 0;
	double corticalPureCellVolume_each_ring = 0;
	for (iRingNum = 0, itMap = RsSourceCorticalDB->objectHeightDB.begin();
		itMap != RsSourceCorticalDB->objectHeightDB.end();
		iRingNum++, itMap++)
	{
		for (i = 0, itVec2 = (*itMap).second.begin(); itVec2 != (*itMap).second.end(); i++, itVec2++)
		{
			for (sliceTempNum = 0, itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				sliceTempNum++, itVec1++)
			{
				corticalPureCellVolume += RsSourceCorticalDB->pureCellVerticalDB[iRingNum] *
					RsSourceCorticalDB->pureCellParallelDB[iRingNum][i] *
					RsSourceCorticalDB->pureCellHeightDB[iRingNum][i][sliceTempNum] * 8;

				/////major change - I am trrating cortical cells as cylinders - Jie Wu treated them as cuboids.
				corticalPureCellVolume_each_ring = M_PI * RsSourceCorticalDB->pureCellVerticalDB[iRingNum] * // 1-27-2021 JGDP
					RsSourceCorticalDB->pureCellVerticalDB[iRingNum] *
					RsSourceCorticalDB->pureCellHeightDB[iRingNum][i][sliceTempNum] * 2;
			}

		}
		lines[iRingNum] = lines[iRingNum] + "," + to_string(corticalPureCellVolume_each_ring);
	}

	/******************
	corticalVacuoleVolume;
	******************/
	corticalVacuoleVolume = 0;
	double corticalVacuoleVolume_each_ring = 0;
	for (iRingNum = 0, itMap = RsSourceCorticalDB->vacuoleHeightDB.begin();
		itMap != RsSourceCorticalDB->vacuoleHeightDB.end();
		iRingNum++, itMap++)
	{
		for (i = 0, itVec2 = (*itMap).second.begin(); itVec2 != (*itMap).second.end(); i++, itVec2++)
		{
			for (sliceTempNum = 0, itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				sliceTempNum++, itVec1++)
			{
				corticalVacuoleVolume += RsSourceCorticalDB->vacuoleVerticalDB[iRingNum] *
					RsSourceCorticalDB->vacuoleParallelDB[iRingNum][i] *
					RsSourceCorticalDB->vacuoleHeightDB[iRingNum][i][sliceTempNum] * 8;

				corticalVacuoleVolume_each_ring = M_PI * RsSourceCorticalDB->vacuoleVerticalDB[iRingNum] * // 1-28-2021 JGDP
					RsSourceCorticalDB->vacuoleVerticalDB[iRingNum] *
					RsSourceCorticalDB->vacuoleHeightDB[iRingNum][i][sliceTempNum] * 2;
			}
		}
		lines[iRingNum] = lines[iRingNum] + "," + to_string(corticalVacuoleVolume_each_ring);
	}
	/// for 1 cm root segment, we need to mutiply rootSegment1cmRatio;
	corticalVacuoleVolume = corticalVacuoleVolume; //* airSpaceRatio * rootSegment1cmRatio;

	/******************************************************************************************
	calculating plasma memembrane volume by adding 0.01 to a, b, and, c radius to pure cell volume
	**********************************************************************************************///// 1-27-2021 - JGDP
	double PM_thick = RsSourceCorticalDB->plasmaMembraneThickness;
	double corticalPureCell_plus_PM_Volume = 0;
	double corticalPureCell_plus_PM_Volume_each_ring = 0;

	for (iRingNum = 0, itMap = RsSourceCorticalDB->objectHeightDB.begin();
		itMap != RsSourceCorticalDB->objectHeightDB.end();
		iRingNum++, itMap++)
	{
		for (i = 0, itVec2 = (*itMap).second.begin(); itVec2 != (*itMap).second.end(); i++, itVec2++)
		{
			for (sliceTempNum = 0, itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				sliceTempNum++, itVec1++)
			{
				corticalPureCell_plus_PM_Volume += (RsSourceCorticalDB->pureCellVerticalDB[iRingNum] + PM_thick) *
					(RsSourceCorticalDB->pureCellParallelDB[iRingNum][i] + PM_thick) *
					(RsSourceCorticalDB->pureCellHeightDB[iRingNum][i][sliceTempNum] + PM_thick) * 8;

				corticalPureCell_plus_PM_Volume_each_ring = M_PI * (RsSourceCorticalDB->pureCellVerticalDB[iRingNum] + PM_thick) *
					(RsSourceCorticalDB->pureCellVerticalDB[iRingNum] + PM_thick) *
					(RsSourceCorticalDB->pureCellHeightDB[iRingNum][i][sliceTempNum] + PM_thick) * 2;
			}
		}
		lines[iRingNum] = lines[iRingNum] + "," + to_string(corticalPureCell_plus_PM_Volume_each_ring);
		fout << lines[iRingNum] << endl;
	}


	/// for 1 cm root segment, we need to mutiply rootSegment1cmRatio;
	corticalPureCellVolume = corticalPureCellVolume;// * airSpaceRatio; //* rootSegment1cmRatio;

	/*******************************************************************************
	corticalCellWallVolume;
	********************************************************************************/
	corticalCellWallVolume = corticalTotalCellVolume - corticalPureCellVolume;

	/********************
	corticalCytoplasmVolume;
	********************/
	corticalCytoplasmVolume = corticalPureCellVolume - corticalVacuoleVolume;

	/***************************
	cytoplasm and vacuole ratio;
	***************************/
	cytoplasm2SectionRatio = corticalCytoplasmVolume / sectionVolume;
	vacuole2SectionRatio = corticalVacuoleVolume / sectionVolume;

	cellWall2CellRatio = corticalCellWallVolume / corticalTotalCellVolume;
	cytoplasm2CellRatio = corticalCytoplasmVolume / corticalTotalCellVolume;
	vacuole2CellRatio = corticalVacuoleVolume / corticalTotalCellVolume;

	/***************************
	PathVolume;
	***************************/
	/// apoplastVolume;
	apoplastVolume = corticalCellWallVolume;
	/// symplastVolume;
	symplastVolume = corticalCytoplasmVolume;

}

void rsDataOutput::DermisDataOutputCalculate(rsSourceDermisDB* RsSourceDermisDB)
{
	vector<int>::iterator itVecNum;
	vector<double>::iterator itVecAddRadius;

	/// for volume calculation of 1 cm root segment, we need to mutiply 450 / 10000;
	// Jagdeep 5-14-2020 This ratio represents the ratio of simualted segment by 1 cm long segment.
	// rootSegment1cmRatio = 10000 / totalHeight;

	/// The ratio of volume accupied by air;
	//airSpaceRatio = 0.95;
	/// sectionVolume = the volume without epidermis;

	ofstream fout(getFolderName() + "individual_"+ RsSourceDermisDB->cellType +"_cell_volume.csv", ios::app);

	double sectionVolume = M_PI * RsSourceDermisDB->circleRadiusDB.back() * RsSourceDermisDB->circleRadiusDB.back() * totalHeight;
	//*rootSegment1cmRatio;

	double theoreticalVolume =
		M_PI * (RsSourceDermisDB->circleRadiusDB.back() * RsSourceDermisDB->circleRadiusDB.back() - baseRadius * baseRadius)
		* totalHeight; //*rootSegment1cmRatio;

	double sectionRatio = theoreticalVolume / sectionVolume;
	int i;

	/// corticalTotalCellNum;
	double totalCellNum = 0;
	double perRingCellNum = 0;
	for (itVecNum = RsSourceDermisDB->DermisCellNumDB.begin(), i = 1;
		itVecNum != RsSourceDermisDB->DermisCellNumDB.end();
		itVecNum++, i++)
	{
		totalCellNum += *itVecNum;
		perRingCellNum = *itVecNum;
		//ringNum = i;
		fout << "Ring Num,Number of Cells,Cortex Theoretical Volume,Section Volume,Total Length" << endl;
		fout << i << "," << perRingCellNum << "," << theoreticalVolume << "," << sectionVolume << "," << totalHeight << endl;
	}

	/*******************************************************************************
	TotalCellVolume;
	********************************************************************************/
	map<int, vector< vector<double> > >::iterator itMap;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator           itVec1;
	/// declare int;
	int iRingNum;
	int sliceTempNum;

	double totalCellVolume = 0;
	double totalCellVolume_each_ring = 0;

	fout << endl << endl << "Ring Num,Total Cell Volume,Pure Cell Volume,Vacuole Volume,Pure Cell plus PM Volume" << endl;
	vector<string> lines;

	for (iRingNum = 0, itMap = RsSourceDermisDB->objectHeightDB.begin();
		itMap != RsSourceDermisDB->objectHeightDB.end();
		iRingNum++, itMap++)
	{
		for (i = 0, itVec2 = (*itMap).second.begin(); itVec2 != (*itMap).second.end(); i++, itVec2++)
		{
			for (sliceTempNum = 0, itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				sliceTempNum++, itVec1++)
			{
				// Volume of cuboid
				totalCellVolume += RsSourceDermisDB->objectVerticalDB[iRingNum] *
					RsSourceDermisDB->circleSegmentLengthDB[iRingNum][i] *
					RsSourceDermisDB->objectHeightDB[iRingNum][i][sliceTempNum] * 8;

				/////Volume of cylinder
				totalCellVolume_each_ring = M_PI * RsSourceDermisDB->objectVerticalDB[iRingNum] *
					RsSourceDermisDB->objectVerticalDB[iRingNum] *
					RsSourceDermisDB->objectHeightDB[iRingNum][i][sliceTempNum];
			}
		}
		string line = to_string(iRingNum + 1) + "," + to_string(totalCellVolume_each_ring);
		lines.push_back(line);
	}

	/// for 1 cm root segment, we need to mutiply rootSegment1cmRatio;
	//corticalTotalCellVolume = corticalTotalCellVolume; //*airSpaceRatio; //* rootSegment1cmRatio;


	/*******************************************************************************
	PureCellVolume;
	********************************************************************************/
	double pureCellVolume = 0;
	double pureCellVolume_each_ring = 0;
	for (iRingNum = 0, itMap = RsSourceDermisDB->objectHeightDB.begin();
		itMap != RsSourceDermisDB->objectHeightDB.end();
		iRingNum++, itMap++)
	{
		for (i = 0, itVec2 = (*itMap).second.begin(); itVec2 != (*itMap).second.end(); i++, itVec2++)
		{
			for (sliceTempNum = 0, itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				sliceTempNum++, itVec1++)
			{
				pureCellVolume += RsSourceDermisDB->pureCellVerticalDB[iRingNum] *
					RsSourceDermisDB->pureCellParallelDB[iRingNum][i] *
					RsSourceDermisDB->pureCellHeightDB[iRingNum][i][sliceTempNum] * 8;

				/////major change - I am trrating cortical cells as cylinders - Jie Wu treated them as cuboids.
				pureCellVolume_each_ring = M_PI * RsSourceDermisDB->pureCellVerticalDB[iRingNum] * // 1-27-2021 JGDP
					RsSourceDermisDB->pureCellVerticalDB[iRingNum] *
					RsSourceDermisDB->pureCellHeightDB[iRingNum][i][sliceTempNum] * 2;
			}

		}
		lines[iRingNum] = lines[iRingNum] + "," + to_string(pureCellVolume_each_ring);
	}

	/******************
	VacuoleVolume;
	******************/
	double vacuoleVolume = 0;
	double vacuoleVolume_each_ring = 0;
	for (iRingNum = 0, itMap = RsSourceDermisDB->vacuoleHeightDB.begin();
		itMap != RsSourceDermisDB->vacuoleHeightDB.end();
		iRingNum++, itMap++)
	{
		for (i = 0, itVec2 = (*itMap).second.begin(); itVec2 != (*itMap).second.end(); i++, itVec2++)
		{
			for (sliceTempNum = 0, itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				sliceTempNum++, itVec1++)
			{
				vacuoleVolume += RsSourceDermisDB->vacuoleVerticalDB[iRingNum] *
					RsSourceDermisDB->vacuoleParallelDB[iRingNum][i] *
					RsSourceDermisDB->vacuoleHeightDB[iRingNum][i][sliceTempNum] * 8;

				vacuoleVolume_each_ring = M_PI * RsSourceDermisDB->vacuoleVerticalDB[iRingNum] * // 1-28-2021 JGDP
					RsSourceDermisDB->vacuoleVerticalDB[iRingNum] *
					RsSourceDermisDB->vacuoleHeightDB[iRingNum][i][sliceTempNum] * 2;
			}
		}
		lines[iRingNum] = lines[iRingNum] + "," + to_string(vacuoleVolume_each_ring);
	}
	
	/******************************************************************************************
	calculating plasma memembrane volume
	*******************************************************************************************/
	double PM_thick = RsSourceDermisDB->plasmaMembraneThickness;
	double pureCell_plus_PM_Volume = 0;
	double pureCell_plus_PM_Volume_each_ring = 0;

	for (iRingNum = 0, itMap = RsSourceDermisDB->objectHeightDB.begin();
		itMap != RsSourceDermisDB->objectHeightDB.end();
		iRingNum++, itMap++)
	{
		for (i = 0, itVec2 = (*itMap).second.begin(); itVec2 != (*itMap).second.end(); i++, itVec2++)
		{
			for (sliceTempNum = 0, itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				sliceTempNum++, itVec1++)
			{
				pureCell_plus_PM_Volume += (RsSourceDermisDB->pureCellVerticalDB[iRingNum] + PM_thick) *
					(RsSourceDermisDB->pureCellParallelDB[iRingNum][i] + PM_thick) *
					(RsSourceDermisDB->pureCellHeightDB[iRingNum][i][sliceTempNum] + PM_thick) * 8;

				pureCell_plus_PM_Volume_each_ring = M_PI * (RsSourceDermisDB->pureCellVerticalDB[iRingNum] + PM_thick) *
					(RsSourceDermisDB->pureCellVerticalDB[iRingNum] + PM_thick) *
					(RsSourceDermisDB->pureCellHeightDB[iRingNum][i][sliceTempNum] + PM_thick) * 2;
			}
		}
		lines[iRingNum] = lines[iRingNum] + "," + to_string(pureCell_plus_PM_Volume_each_ring);
		fout << lines[iRingNum] << endl;
	}

	/*******************************************************************************
	cellWallVolume;
	********************************************************************************/
	double cellWallVolume = totalCellVolume - pureCellVolume;

	/********************
	cytoplasmVolume;
	********************/
	double cytoplasmVolume = pureCellVolume - vacuoleVolume;

	/***************************
	cytoplasm and vacuole ratio;
	***************************/
	double cytoplasm2SectionRatio = cytoplasmVolume / sectionVolume;
	double vacuole2SectionRatio = vacuoleVolume / sectionVolume;

	double cellWall2CellRatio = cellWallVolume / totalCellVolume;
	double cytoplasm2CellRatio = cytoplasmVolume / totalCellVolume;
	double vacuole2CellRatio = vacuoleVolume / totalCellVolume;

	/***************************
	PathVolume;
	***************************/
	/// apoplastVolume;
	double apoplastVolume = cellWallVolume;
	/// symplastVolume;
	double symplastVolume = cytoplasmVolume;

}

void rsDataOutput::PXDataOutputCalculate(rsPXCoreDB* RsPXCoreDB) {
	vector<int>::iterator itVecNum;
	vector<double>::iterator itVecAddRadius;

	ofstream fout(getFolderName() + "individual_protoxylem_cell_volume.csv", ios::app);

	double sectionVolume = M_PI * pow(RsPXCoreDB->circleRadius, 2.0) * totalHeight;

	double theoreticalVolume = M_PI * (pow(RsPXCoreDB->circleRadius, 2.0) - pow(baseRadius, 2.0)) * totalHeight;

	double sectionRatio = theoreticalVolume / sectionVolume;
	int i;

	/*******************************************************************************
	TotalCellVolume;
	********************************************************************************/
	map<int, vector<double> > ::iterator itMap;
	vector<double>::iterator           itVec;
	/// declare int;
	int iRingNum;
	int sliceTempNum;

	double totalCellVolume = 0;
	double totalCellVolume_each_ring = 0;

	fout << endl << endl << "Ring Num,Total Cell Volume,Pure Cell Volume,Vacuole Volume,Pure Cell plus PM Volume" << endl;
	vector<string> lines;

	for (iRingNum = 0, itMap = RsPXCoreDB->pxSmallCenterRingObjectHeightDB.begin();
		itMap != RsPXCoreDB->pxSmallCenterRingObjectHeightDB.end();
		iRingNum++, itMap++)
	{
		for (sliceTempNum = 0, itVec = (*itMap).second.begin(); itVec != (*itMap).second.end(); sliceTempNum++, itVec++)
		{
			/////Volume of cylinder
			totalCellVolume_each_ring = M_PI * RsPXCoreDB->pxSmallVerticalRadiusDB[iRingNum] *
				RsPXCoreDB->pxSmallVerticalRadiusDB[iRingNum] *
				RsPXCoreDB->pxSmallCenterRingObjectHeightDB[iRingNum][sliceTempNum];
		}
		string line = to_string(iRingNum + 1) + "," + to_string(totalCellVolume_each_ring);
		lines.push_back(line);
		fout << lines[iRingNum] << endl;
	}

	/*******************************************************************************
	PureCellVolume;
	********************************************************************************/

	/******************
	VacuoleVolume;
	******************/


	/******************************************************************************************
	calculating plasma memembrane volume
	*******************************************************************************************/
	double PM_thick = RsPXCoreDB->plasmaMembraneThickness;
	double pureCell_plus_PM_Volume = 0;
	double pureCell_plus_PM_Volume_each_ring = 0;

	/*******************************************************************************
	cellWallVolume;
	********************************************************************************/
	//double cellWallVolume = totalCellVolume - pureCellVolume;

	/********************
	cytoplasmVolume;
	********************/
	//double cytoplasmVolume = pureCellVolume - vacuoleVolume;

	/***************************
	cytoplasm and vacuole ratio;
	***************************/
	//double cytoplasm2SectionRatio = cytoplasmVolume / sectionVolume;
	//double vacuole2SectionRatio = vacuoleVolume / sectionVolume;

	//double cellWall2CellRatio = cellWallVolume / totalCellVolume;
	//double cytoplasm2CellRatio = cytoplasmVolume / totalCellVolume;
	//double vacuole2CellRatio = vacuoleVolume / totalCellVolume;

}
void rsDataOutput::MXDataOutputCalculate(rsMXCoreDB* RsMXCoreDB) {

}
void rsDataOutput::MXBoundaryDataOutputCalculate(rsMXBoundaryOutDB* RSMXBoundaryOutDB) {

}
void rsDataOutput::SteleDataOutputCalculate(rsSteleInnerDB* RsSteleInnerDB) {

}
void rsDataOutput::PXBoundaryDataOutputCalculate(rsPXBoundaryDB* RsPXBoundaryDB) {

	vector<int>::iterator itVecNum;
	vector<double>::iterator itVecAddRadius;

	ofstream fout(getFolderName() + "individual_protoxylem_boundary_cell_volume.csv", ios::app);

	double sectionVolume = M_PI * pow(RsPXBoundaryDB->circleRadius, 2.0) * totalHeight;

	double theoreticalVolume = M_PI * (pow(RsPXBoundaryDB->circleRadius, 2.0) - pow(baseRadius, 2.0)) * totalHeight;

	double sectionRatio = theoreticalVolume / sectionVolume;
	int i;

	/*******************************************************************************
	TotalCellVolume;
	********************************************************************************/
	map<int, vector<double> > ::iterator itMap;
	vector<double>::iterator           itVec;
	/// declare int;
	int iRingNum;
	int sliceTempNum;

	double totalCellVolume = 0;
	double totalCellVolume_each_ring = 0;

	fout << endl << endl << "Ring Num,Total Cell Volume,Pure Cell Volume,Vacuole Volume,Pure Cell plus PM Volume" << endl;
	vector<string> lines;

	for (iRingNum = 0, itMap = RsPXBoundaryDB->pxSmallCenterRingObjectHeightDB.begin();
		itMap != RsPXBoundaryDB->pxSmallCenterRingObjectHeightDB.end();
		iRingNum++, itMap++)
	{
		for (sliceTempNum = 0, itVec = (*itMap).second.begin(); itVec != (*itMap).second.end(); sliceTempNum++, itVec++)
		{
			/////Volume of cylinder
			totalCellVolume_each_ring = M_PI * RsPXBoundaryDB->pxSmallVerticalRadiusDB[iRingNum] *
				RsPXBoundaryDB->pxSmallVerticalRadiusDB[iRingNum] *
				RsPXBoundaryDB->pxSmallCenterRingObjectHeightDB[iRingNum][sliceTempNum];
		}
		string line = to_string(iRingNum + 1) + "," + to_string(totalCellVolume_each_ring);
		lines.push_back(line);
		fout << lines[iRingNum] << endl;
	}
}
void rsDataOutput::PhloemDataOutputCalculate(rsPhloemDB* RsPhloemDB) {

}


void rsDataOutput::RcaDataOutputCalculate(rsRcaDB* RsRcaDB)
{
	rca2CortexExactRatio = RsRcaDB->rca2CortexExactRatio;
	rcaRatioInput = RsRcaDB->rcaRatio;
	rcaRealVolume = RsRcaDB->rcaRealVolume;
}

void rsDataOutput::NonRcaDataOutput()
{
	rca2CortexExactRatio = 0;
	rcaRatioInput = 0;
	rcaRealVolume = 0;
}

void rsDataOutput::PathLengthDataOutputCalculate(rsEpiCortexEndoWaterPathDB* RsEpiCortexEndoWaterPathDB)
{
	apoplastPathLengthTotal = RsEpiCortexEndoWaterPathDB->apoplastPathLengthTotal;
	apoplastPathLengthAverage = RsEpiCortexEndoWaterPathDB->apoplastPathLengthAverage;
	apoplastPathLengthShortest = RsEpiCortexEndoWaterPathDB->apoplastPathLengthShortest;
	apoplastPathLengthLongest = RsEpiCortexEndoWaterPathDB->apoplastPathLengthLongest;

	symplastPathLengthTotal = RsEpiCortexEndoWaterPathDB->symplastPathLengthTotal;
	symplastPathLengthAverage = RsEpiCortexEndoWaterPathDB->symplastPathLengthAverage;
	symplastPathLengthShortest = RsEpiCortexEndoWaterPathDB->symplastPathLengthShortest;
	symplastPathLengthLongest = RsEpiCortexEndoWaterPathDB->symplastPathLengthLongest;
}

void rsDataOutput::NutrientAndMitochondriaCalculate()
{  /*************
	 Nitrogen;
   **************/
   /// Nitrogen in 1 cm root segment of cortical cell;
/// Nitrate:
//  Cytosol Nitrate Concentration:
//  3.1 mol m-3 (Maize, root epidermal cells, 1-2cm from the root tip, 10 mol m-3 nitrate, double-barrelled nitrate-selective microelectrodes)
//  Vacuolar Nitrate Concentration:
//  69.6 mol m-3 (Barley, root cortical cells, 1-2cm from the root tip, 10 mol m-3 nitrate, double-barrelled nitrate-selective microelectrodes)
/// Ammonium:
//  Cytosol Ammonium Concentration:
//  10 mol m-3 (Maize, mature regions, NMR)
//  Vacuolar Ammonium Concentration:
//  15 mol m-3 (Maize, mature regions, NMR)
/// Amino Acid:
//  Cytosol Amino Acid concentration:
//  274 mol m-3 (Barley, leaves, after 9h of illumination)
//  Vacuolar Amino Acid concentration:
//  1.73 mol m-3 (Barley, leaves, after 9h of illumination)
//  Soluble Nitrogen = ( total cytoplasmic Nitrate + Ammonium + Amino acid)
//                   + (total vacuolar Nitrate + Ammonium + Amino acid)
//  Soluble Nitrogen fraction = 4% (from figure)
//  Total N = Soluble N / 4%


	double nitrogenSolubleTotalCytoplasm;
	double nitrogenSolubleTotalVacuole;

	double nitrateTotalCytoplasm;
	double nitrateTotalVacuole;

	double ammoniumTotalCytoplasm;
	double ammoniumTotalVacuole;

	double aminoAcidTotalCytoplasm;
	double aminoAcidTotalVacuole;

	/// Nitrogen concentration;
	// Nitrate;
	double vacuolarNitrate = 1;
	double cytoplasmicNitrate = 1;
	// Ammonium;
	double vacuolarAmmonium = 1;
	double cytoplasmicAmmonium = 1;
	// Amino acid;
	double vacuolarAminoAcid = 1;
	double cytoplasmicAminoAcid = 274;

	/// unit pmol;
	nitrateTotalCytoplasm = corticalCytoplasmVolume * cytoplasmicNitrate / 1000000000;
	nitrateTotalVacuole = corticalVacuoleVolume * vacuolarNitrate / 1000000000;
	ammoniumTotalCytoplasm = corticalCytoplasmVolume * cytoplasmicAmmonium / 1000000000;
	ammoniumTotalVacuole = corticalVacuoleVolume * vacuolarAmmonium / 1000000000;
	aminoAcidTotalCytoplasm = corticalCytoplasmVolume * cytoplasmicAminoAcid / 1000000000;
	aminoAcidTotalVacuole = corticalVacuoleVolume * vacuolarAminoAcid / 1000000000;


	nitrogenSolubleTotalCytoplasm = nitrateTotalCytoplasm + ammoniumTotalCytoplasm + aminoAcidTotalCytoplasm;
	nitrogenSolubleTotalVacuole = nitrateTotalVacuole + ammoniumTotalVacuole + aminoAcidTotalVacuole;


	/// for output;
	// pmol;
	nitrateTotal = (nitrateTotalCytoplasm + nitrateTotalVacuole);
	ammoniumTotal = (ammoniumTotalCytoplasm + ammoniumTotalVacuole);
	aminoAcidTotal = (aminoAcidTotalCytoplasm + aminoAcidTotalVacuole);
	nitrogenSolubleTotal = (nitrogenSolubleTotalCytoplasm + nitrogenSolubleTotalVacuole);
	nitrogenTotal = nitrogenSolubleTotal / 0.04;

	nitrogenPerCorticalVolume = nitrogenTotal / corticalTotalCellVolume;

	   /*************
		 Phosphorus;
	   **************/
	   /// Phosphorus in 1 cm root segment of cortical cell;
	///  Inorganic Phosphate(Pi)£º
	//   Cytoplasm Pi concentration: 6.5 mol m-3;
	//   Vacuolar Pi concentration: 6.7 mol m-3;
	///  Pi fraction:
	//   37%(mean)
	///  Total Phosphorus
	//   = ( total cytoplasmic Pi + total vacuolar Pi) / 37%

	   /// Pi concentration;
	double vacuolarPi = 1;
	double cytoplasmicPi = 1;


	double inorganicPhosphateTotalCytoplasm;
	double inorganicPhosphateTotalVacuole;

	/// unit pmol
	inorganicPhosphateTotalCytoplasm = corticalCytoplasmVolume * cytoplasmicPi / 1000000000;
	inorganicPhosphateTotalVacuole = corticalVacuoleVolume * vacuolarPi / 1000000000;

	/// for output;
	PiTotal = inorganicPhosphateTotalCytoplasm + inorganicPhosphateTotalVacuole;
	phosphorusTotal = PiTotal / 0.37;

	phosphorusPerCorticalVolume = phosphorusTotal / corticalTotalCellVolume;

	   /*************
		 Mitochondria;
	   **************/
	   /// Mitochondria number in 1 cm root segment of cortical cell;
	   // 170 per 1000 ¦Ìm3 of cytoplasm (Maize, Stele, 200 ¦Ìm from the root apex);
	mitoNumTotal = corticalCytoplasmVolume * 170 / 1000;
}

void rsDataOutput::AllDataOutput(double baseRadius, double totalHeight)
{
	cout << "totalHeight --- line 335 " << totalHeight << endl;
	cout << "Ringnum " << corticalRingNum << endl;
	/// steleRadius to string;
	string steleRadiusName = "SteleR(um)";
	stringstream steleRadiusSS;
	string steleRadiusString;
	steleRadiusSS << baseRadius;
	steleRadiusSS >> steleRadiusString;

	/// corticalRingNum to string;
	string ringNumName = "RingNum";
	stringstream ringNumSS;
	string ringNumString;
	ringNumSS << corticalRingNum;
	ringNumSS >> ringNumString;

	/// CorticalInnestCellDiameter to string;
	string corticalInnermostCellDiameterName = "MinCellD(um)";
	stringstream corticalInnermostCellDiameterSS;
	string corticalInnermostCellDiameterString;
	corticalInnermostCellDiameterSS << corticalInnermostCellDiameter;
	corticalInnermostCellDiameterSS >> corticalInnermostCellDiameterString;

	/// rca2CortexRatio to string;
	string rca2CortexRatioName = "RcaRatio";
	stringstream rca2CortexRatioSS;
	string rca2CortexRatioString;
	rca2CortexRatioSS << rcaRatioInput;
	rca2CortexRatioSS >> rca2CortexRatioString;

	/// gapCytoTono to string;
	string gapCytoTonoName = "GapCT(um)";
	stringstream gapCytoTonoSS;
	string gapCytoTonoString;
	gapCytoTonoSS << gapCytoTono;
	gapCytoTonoSS >> gapCytoTonoString;

	/// gapCellWall to string;
	string gapCellWallName = "GapCW(um)";
	stringstream gapCellWallSS;
	string gapCellWallString;
	gapCellWallSS << gapCellWall;
	gapCellWallSS >> gapCellWallString;

	/// totalheight to string ** Jagdeep 12-2-2020
	cout << "totalHeight --- " << totalHeight << endl;
	string TotalHeightName = "TotalHeight";
	stringstream TotalHeightSS;
	string TotalHeightString;
	TotalHeightSS << totalHeight;
	TotalHeightSS >> TotalHeightString;

	string blankSpace = " ";
	string comma = ",";

	string prefix = steleRadiusName + comma + steleRadiusString + comma
		+ ringNumName + comma + ringNumString + comma
		+ corticalInnermostCellDiameterName + comma + corticalInnermostCellDiameterString + comma
		+ rca2CortexRatioName + comma + rca2CortexRatioString + comma
		+ gapCytoTonoName + comma + gapCytoTonoString + comma
		+ gapCellWallName + comma + gapCellWallString + comma
		+ TotalHeightName + comma + TotalHeightString + comma;

	ofstream fout(getFolderName() + "AllOutputName.csv", ios::app);

	cout << prefix << endl;

	/// Cortical;
	fout << prefix << "cortexThickness(um)," << cortexThickness << endl;
	fout << prefix << "corticalTotalCellNum," << corticalTotalCellNum << endl;
	fout << prefix << "cortex2SectionRatio," << cortex2SectionRatio << endl;

	fout << prefix << "corticalCellWallVolume(um3)," << corticalCellWallVolume << endl;
	fout << prefix << "corticalCytoplasmVolume(um3)," << corticalCytoplasmVolume << endl;
	fout << prefix << "corticalVacuoleVolume(um3)," << corticalVacuoleVolume << endl;

	fout << prefix << "cellWall2CellRatio," << cellWall2CellRatio << endl;
	fout << prefix << "cytoplasm2CellRatio," << cytoplasm2CellRatio << endl;
	fout << prefix << "vacuole2CellRatio," << vacuole2CellRatio << endl;

	/// RCA;
	fout << prefix << "rca2CortexExactRatio," << rca2CortexExactRatio << endl;

	/// Path volume;
	fout << prefix << "apoplastVolume(um3)," << apoplastVolume << endl;
	fout << prefix << "symplastVolume(um3)," << symplastVolume << endl;

	/// Path length;
	// Apoplast;
	fout << prefix << "apoplastTotal(um)," << apoplastPathLengthTotal << endl;
	fout << prefix << "apoplastAverage(um)," << apoplastPathLengthAverage << endl;
	fout << prefix << "apoplastShortest(um)," << apoplastPathLengthShortest << endl;
	fout << prefix << "apoplastLongest(um)," << apoplastPathLengthLongest << endl;
	// Symplast;
	fout << prefix << "symplastTotal(um)," << symplastPathLengthTotal << endl;
	fout << prefix << "symplastAverage(um)," << symplastPathLengthAverage << endl;
	fout << prefix << "symplastShortest(um)," << symplastPathLengthShortest << endl;
	fout << prefix << "symplastLongest(um)," << symplastPathLengthLongest << endl;

	/// Nutrient And Mitochondria;
	fout << prefix << "nitrogenTotal(pmol)," << nitrogenTotal << endl;
	fout << prefix << "nitrogenSolubleTotal(pmol)," << nitrogenSolubleTotal << endl;
	fout << prefix << "nitrateTotal(pmol)," << nitrateTotal << endl;
	fout << prefix << "ammoniumTotal(pmol)," << ammoniumTotal << endl;
	fout << prefix << "aminoAcidTotal(pmol)," << aminoAcidTotal << endl;

	fout << prefix << "phosphorusTotal(pmol)," << phosphorusTotal << endl;
	fout << prefix << "PiTotal(pmol)," << PiTotal << endl;

	fout << prefix << "nitrogenPerCorticalVolume(mol m-3)," << nitrogenPerCorticalVolume << endl;
	fout << prefix << "phosphorusPerCorticalVolume(mol m-3)," << phosphorusPerCorticalVolume << endl;
	fout << prefix << "mitoNumTotal," << mitoNumTotal << endl;
}
