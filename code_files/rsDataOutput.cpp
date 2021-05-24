#define _USE_MATH_DEFINES
#include <cmath> 
#include "rsDataOutput.h"
/// The same;


void rsDataOutput::DataOutputName(const char* dataOutputNameInput)
{
	dataOutputName = dataOutputNameInput;
}

/** \brief CorticalDataOutput;
 *
 * \param double boundaryRadius;
 * \param double baseRadius;
 * \param vector<int> corticalCellNumDB;
 * \param double totalHeight;
 * \param vector<double> corticalAddRadiusDB;
 * \param vector<double> objectVerticalDB;
 * \param map<int, vector<double> > circleSegmentLengthDB;
 * \param map<int, vector< vector<double> > > objectHeightDB;
 * \param vector<double> vacuoleVerticalDB;
 * \param map<int, vector<double> > vacuoleParallelDB;
 * \param map<int, vector< vector<double> > > vacuoleHeightDB;
 *
 */

void rsDataOutput::CorticalDataOutputCalculate
(double baseRadius,
	double totalHeight,
	rsSourceCorticalDB* RsSourceCorticalDB)


{
	vector<int>::iterator itVecNum;
	vector<double>::iterator itVecAddRadius;

	corticalInnermostCellDiameter = RsSourceCorticalDB->corticalCellAddRadiusMin;
	/// if coritcalAddRadius is calculated from cortex radius,
	/// redifne the corticalInnermostCellDiameter;

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
	rootSegment1cmRatio = 10000 / totalHeight; // Jagdeep 5-14-2020 This ratio represents the ratio of simualted segment by 1 cm long segment.
	/// The ratio of volume accupied by air;
	//airSpaceRatio = 0.95;

	/// sectionVolume = the volume without epidermis;

	ofstream fout("individual_cortical_cell_volume.txt", ios::app); // Jagdeep 1-24-2021

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
		fout << "CCFN " << i << " no_of_cells " << corticalperRingCellNum << " Totallength " << totalHeight << endl;;
		fout << "CCFN " << i << " cortexTheoreticalVolume " << cortexTheoreticalVolume << " Totallength " << totalHeight << endl;
		fout << "CCFN " << i << " sectionVolume " << sectionVolume << " Totallength " << totalHeight << endl;;
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
				corticalTotalCellVolume += RsSourceCorticalDB->objectVerticalDB[iRingNum] * // it is cell radius - refer to objectVerticalDB function in RsSourceCorticalDB.cpp line 304.
					RsSourceCorticalDB->circleSegmentLengthDB[iRingNum][i] *
					RsSourceCorticalDB->objectHeightDB[iRingNum][i][sliceTempNum] * 8; // jgdp 1-24-2021 this was multiplied by eight https://www.google.com/search?q=8xyz+volume+of+ellipsoid&source=lmns&bih=903&biw=1920&rlz=1C1CHBF_enUS893US893&hl=en&sa=X&ved=2ahUKEwjXjdm2hbbuAhXNneAKHfZNB3kQ_AUoAHoECAEQAA
																					  // also refer to ObjectHeightAndZPositionDB function in RsSourceCorticalDB.cpp line 415.
/////major change - I am trrating cortical cells as cylinders - Jie Wu treated them as cuboids.         
				corticalTotalCellVolume_each_ring = M_PI * RsSourceCorticalDB->objectVerticalDB[iRingNum] *
					RsSourceCorticalDB->objectVerticalDB[iRingNum] *
					(RsSourceCorticalDB->objectHeightDB[iRingNum][i][sliceTempNum] * 2);

				//fout << "RingNum" << iRingNum <<"Objectvertical --" << RsSourceCorticalDB->objectVerticalDB[iRingNum] << endl;
				//fout << "RingNum" << iRingNum << "circle segment length --" << RsSourceCorticalDB->circleSegmentLengthDB[iRingNum][i] << endl;
				//fout << "RingNum" << iRingNum << "objectHeightDB --" << RsSourceCorticalDB->objectHeightDB[iRingNum][i][sliceTempNum] << endl;
				//fout << "RingNum" << iRingNum << "  corticalTotalCellVolume --" << RsSourceCorticalDB->objectVerticalDB[iRingNum] * RsSourceCorticalDB->circleSegmentLengthDB[iRingNum][i] * RsSourceCorticalDB->objectHeightDB[iRingNum][i][sliceTempNum] * 8 << endl;
			}
		}
		fout << "CCFN " << iRingNum + 1 << " corticalTotalCellVolume_each_ring " << corticalTotalCellVolume_each_ring << " Totallength " << totalHeight << endl;
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
		fout << "CCFN " << iRingNum + 1 << " corticalPureCellVolume_each_ring " << corticalPureCellVolume_each_ring << " Totallength " << totalHeight << endl;

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
		fout << "CCFN " << iRingNum + 1 << " corticalVacuoleVolume_each_ring " << corticalVacuoleVolume_each_ring << " Totallength " << totalHeight << endl;

	}
	/// for 1 cm root segment, we need to mutiply rootSegment1cmRatio;
	corticalVacuoleVolume = corticalVacuoleVolume; //* airSpaceRatio * rootSegment1cmRatio;

	/******************************************************************************************
	calculating plasma memembrane volume by adding 0.01 to a, b, and, c radius to pure cell volume
	**********************************************************************************************///// 1-27-2021 - JGDP
	double PM_thick = 0.01;
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
				corticalPureCell_plus_PM_Volume += (RsSourceCorticalDB->pureCellVerticalDB[iRingNum] + 0.01) *
					(RsSourceCorticalDB->pureCellParallelDB[iRingNum][i] + 0.01) *
					(RsSourceCorticalDB->pureCellHeightDB[iRingNum][i][sliceTempNum] + 0.01) * 8;

				corticalPureCell_plus_PM_Volume_each_ring = M_PI * (RsSourceCorticalDB->pureCellVerticalDB[iRingNum] + 0.01) *
					(RsSourceCorticalDB->pureCellVerticalDB[iRingNum] + 0.01) *
					(RsSourceCorticalDB->pureCellHeightDB[iRingNum][i][sliceTempNum] + 0.01) * 2;
			}

		}
		fout << "CCFN " << iRingNum + 1 << " corticalPureCell_plus_PM_Volume_each_ring " << corticalPureCell_plus_PM_Volume_each_ring << " Totallength " << totalHeight << endl;

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


void rsDataOutput::RcaDataOutputCalculate(rsRcaDB* RsRcaDB)
{

	//    ofstream fout( dataOutputName, ios::app);
	//   fout << endl;
	//   fout << "RCA: " << endl;
	//   fout << endl;
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
	//    ofstream fout( dataOutputName, ios::app);
	//   fout << endl;
	//   fout << "PathLength: " << endl;
	//   fout << endl;
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

	//   nitrogenPerCorticalVolume = nitrogenTotal / corticalTotalCellVolume;

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

	//   phosphorusPerCorticalVolume = phosphorusTotal / corticalTotalCellVolume;

	   /*************
		 Mitochondria;
	   **************/
	   /// Mitochondria number in 1 cm root segment of cortical cell;
	   // 170 per 1000 ¦Ìm3 of cytoplasm (Maize, Stele, 200 ¦Ìm from the root apex);
	mitoNumTotal = corticalCytoplasmVolume * 170 / 1000;

}

void rsDataOutput::AllDataOutput(double baseRadius,
	double totalHeight) // Jagdeep

{  /// Output filename;
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

	string prefix = steleRadiusName + blankSpace + steleRadiusString + blankSpace
		+ ringNumName + blankSpace + ringNumString + blankSpace
		+ corticalInnermostCellDiameterName + blankSpace + corticalInnermostCellDiameterString + blankSpace
		+ rca2CortexRatioName + blankSpace + rca2CortexRatioString + blankSpace
		+ gapCytoTonoName + blankSpace + gapCytoTonoString + blankSpace
		+ gapCellWallName + blankSpace + gapCellWallString + blankSpace
		+ TotalHeightName + blankSpace + TotalHeightString + blankSpace;






	/// output Name;
 //   string outputTxtName;
 //   string suffix = ".txt";
 //   outputTxtName = prefix + suffix;
 //    const char* outputTxtNameFinal = outputTxtName.c_str();
	ofstream fout("AllOutputName.txt", ios::app);

	cout << prefix << endl;

	/// Cortical;
	fout << prefix << "cortexThickness(um) " << cortexThickness << endl;
	fout << prefix << "corticalTotalCellNum " << corticalTotalCellNum << endl;
	//   fout << prefix << "sectionVolume(um3) " << sectionVolume << endl;
	//   fout << prefix << "cortexTheoreticalVolume (um3) " << cortexTheoreticalVolume << endl;
	fout << prefix << "cortex2SectionRatio " << cortex2SectionRatio << endl;

	//   fout << prefix << "corticalTotalCellVolume(um3) " << corticalTotalCellVolume << endl;
	fout << prefix << "corticalCellWallVolume(um3) " << corticalCellWallVolume << endl;
	fout << prefix << "corticalCytoplasmVolume(um3) " << corticalCytoplasmVolume << endl;
	fout << prefix << "corticalVacuoleVolume(um3) " << corticalVacuoleVolume << endl;
	//   fout << prefix << "cytoplasm2SectionRatio " << cytoplasm2SectionRatio << endl;
	//   fout << prefix << "vacuole2SectionRatio " << vacuole2SectionRatio << endl;
	fout << prefix << "cellWall2CellRatio " << cellWall2CellRatio << endl;
	fout << prefix << "cytoplasm2CellRatio " << cytoplasm2CellRatio << endl;
	fout << prefix << "vacuole2CellRatio " << vacuole2CellRatio << endl;

	/// RCA;
 //   fout << prefix << "rcaRealVolume(um) " << rcaRealVolume  <<endl;
	fout << prefix << "rca2CortexExactRatio " << rca2CortexExactRatio << endl;

	/// Path volume;
	fout << prefix << "apoplastVolume(um3) " << apoplastVolume << endl;
	fout << prefix << "symplastVolume(um3) " << symplastVolume << endl;

	/// Path length;
	// Apoplast;
	fout << prefix << "apoplastTotal(um) " << apoplastPathLengthTotal << endl;
	fout << prefix << "apoplastAverage(um) " << apoplastPathLengthAverage << endl;
	fout << prefix << "apoplastShortest(um) " << apoplastPathLengthShortest << endl;
	fout << prefix << "apoplastLongest(um) " << apoplastPathLengthLongest << endl;
	// Symplast;
	fout << prefix << "symplastTotal(um) " << symplastPathLengthTotal << endl;
	fout << prefix << "symplastAverage(um) " << symplastPathLengthAverage << endl;
	fout << prefix << "symplastShortest(um) " << symplastPathLengthShortest << endl;
	fout << prefix << "symplastLongest(um) " << symplastPathLengthLongest << endl;

	/// Nutrient And Mitochondria;
	fout << prefix << "nitrogenTotal(pmol) " << nitrogenTotal << endl;
	fout << prefix << "nitrogenSolubleTotal(pmol) " << nitrogenSolubleTotal << endl;
	fout << prefix << "nitrateTotal(pmol) " << nitrateTotal << endl;
	fout << prefix << "ammoniumTotal(pmol) " << ammoniumTotal << endl;
	fout << prefix << "aminoAcidTotal(pmol) " << aminoAcidTotal << endl;

	fout << prefix << "phosphorusTotal(pmol) " << phosphorusTotal << endl;
	fout << prefix << "PiTotal(pmol) " << PiTotal << endl;

	fout << prefix << "nitrogenPerCorticalVolume(mol m-3) " << nitrogenPerCorticalVolume << endl;
	fout << prefix << "phosphorusPerCorticalVolume(mol m-3) " << phosphorusPerCorticalVolume << endl;
	fout << prefix << "mitoNumTotal " << mitoNumTotal << endl;

}
