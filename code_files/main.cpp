#include "tinyxml.h"
#include "viStringTokenizer.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include "rsDynamicDataOutput.h"
#include "rsSteleInnerVisual.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	TiXmlDocument doc("CorticalData.xml");
	doc.LoadFile();
	TiXmlElement* main = doc.FirstChildElement("Main");
	string filePrefix = main->Attribute("name");
	//TiXmlElement* plantNum = doc.FirstChildElement("Main")
	//	->FirstChildElement("Plant")
	//	->FirstChildElement("PlantNum");
	//map<int, double> corticalAddRadiusInputData;
	vector<double> corticalAddRadiusInputData;
	// map<int, double>::iterator corticalAddRadiusInputData_it;

	  //map<int, double> corticalCellNumInputData;
	vector<int> corticalCellNumInputData;
	// map<int, double>::iterator corticalCellNumInputData_it;

	double corticalCellWallWidth;
	double corticalPlasmaMembraneThickness;
	double corticalGapCytoTono;
	double corticalGapCellWall;
	double corticalVariationRatio;
	int corticalMinSlice;
	int corticalMaxSlice;
	double corticalCellDiameter;
	int corticalNumFiles;

	double steleCellWallWidth;
	double stelePlasmaMembraneThickness;
	double steleGapCytoTono;
	double steleGapCellWall;
	double steleVariationRatio;
	int steleMinSlice;
	int steleMaxSlice;
	double steleInnestCellDiameter;
	int steleInnerLayerNum;

	double metaXylemCellWallWidth;
	double metaXylemPlasmaMembraneThickness;
	double metaXylemGapCytoTono;
	double metaXylemGapCellWall;
	double metaXylemVariationRatio;
	int metaXylemMinSlice;
	int metaXylemMaxSlice;
	double metaXylemverticalLengthThresholdRatio;
	double metaXylemTangentRingRadiusRatio;
	int metaXylemSteleCellNumBetween;
	int metaXylemNum;
	double metaXylemAverageRingRadius;
	int metaXylemSurroundingCellRingNum;

	double protoXylemCellWallWidth;
	double protoXylemPlasmaMembraneThickness;
	double protoXylemGapCytoTono;
	double protoXylemGapCellWall;
	double protoXylemVariationRatio;
	int protoXylemMinSlice;
	int protoXylemMaxSlice;
	double protoXylemGapRadius;
	int protoXylemNum;
	double protoXylemAverageRingRadius;
	int protoXylemSurroundingCellRingNum;
	double protoXylemSurroundingCellRingRadius;

	double epidermisCellWallWidth;
	double epidermisPlasmaMembraneThickness;
	double epidermisGapCytoTono;
	double epidermisGapCellWall;
	double epidermisVariationRatio;
	int epidermisMinSlice;
	int epidermisMaxSlice;
	double epidermisCellDiameter;
	int epidermisCellNum;

	double endodermisCellWallWidth;
	double endodermisPlasmaMembraneThickness;
	double endodermisGapCytoTono;
	double endodermisGapCellWall;
	double endodermisVariationRatio;
	int endodermisMinSlice;
	int endodermisMaxSlice;
	double endodermisCellDiameter;

	double exodermisCellWallWidth;
	double exodermisPlasmaMembraneThickness;
	double exodermisGapCytoTono;
	double exodermisGapCellWall;
	double exodermisVariationRatio;
	int exodermisMinSlice;
	int exodermisMaxSlice;
	double exodermisCellDiameter;

	double sclerenchymaCellWallWidth;
	double sclerenchymaPlasmaMembraneThickness;
	double sclerenchymaGapCytoTono;
	double sclerenchymaGapCellWall;
	double sclerenchymaVariationRatio;
	int sclerenchymaMinSlice;
	int sclerenchymaMaxSlice;
	double sclerenchymaCellDiameter;

	double pericycleCellWallWidth;
	double pericyclePlasmaMembraneThickness;
	double pericycleGapCytoTono;
	double pericycleGapCellWall;
	double pericycleVariationRatio;
	int pericycleMinSlice;
	int pericycleMaxSlice;
	double pericycleCellDiameter;

	double totalHeight = atof(main->Attribute("height"));
	double rcaRatio;

	double baseRadius;
	double thickness;

	// READ PARAMETERS FROM XML FILE //
	//********** CORTICAL DATA *************//
	TiXmlElement* corticalInput = main->FirstChildElement("Cortical");
	if (corticalInput) {
		baseRadius = atof(corticalInput->FirstChildElement("BaseRadius")->GetText());
		thickness = atof(corticalInput->FirstChildElement("Thickness")->GetText());
		corticalCellWallWidth = atof(corticalInput->FirstChildElement("CellwallWidth")->GetText());
		corticalPlasmaMembraneThickness = atof(corticalInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		corticalGapCytoTono = atof(corticalInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		corticalGapCellWall = corticalCellWallWidth + corticalPlasmaMembraneThickness;
		corticalVariationRatio = atof(corticalInput->Attribute("variationRatio"));
		corticalMinSlice = atoi(corticalInput->FirstChildElement("Slices")->Attribute("min"));
		corticalMaxSlice = atoi(corticalInput->FirstChildElement("Slices")->Attribute("max"));
		corticalNumFiles = atoi(corticalInput->FirstChildElement("NumFiles")->GetText());
		rcaRatio = atof(corticalInput->FirstChildElement("RCARatio")->GetText());
		corticalCellDiameter = atof(corticalInput->FirstChildElement("CellDiameter")->GetText());
	}
	else {
		cout << "Cortical Data Missing." << endl;
		return 1;
	}

	//********** STELE DATA *************//
	TiXmlElement* steleInput = main->FirstChildElement("Stele");
	if (steleInput) {
		steleMinSlice = atoi(steleInput->FirstChildElement("Slices")->Attribute("min"));
		steleMaxSlice = atoi(steleInput->FirstChildElement("Slices")->Attribute("max"));
		steleCellWallWidth = atof(steleInput->FirstChildElement("CellwallWidth")->GetText());
		stelePlasmaMembraneThickness = atof(steleInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		steleGapCytoTono = atof(steleInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		steleGapCellWall = steleCellWallWidth + stelePlasmaMembraneThickness;
		steleVariationRatio = atof(steleInput->Attribute("variationRatio"));
		steleInnestCellDiameter = atof(steleInput->FirstChildElement("InnestCellDiameer")->GetText());
		steleInnerLayerNum = atoi(steleInput->FirstChildElement("InnerLayerNum")->GetText());
	}
	else {
		cout << "Stele Parameters Missing." << endl;
		return 2;
	}

	//********** METAXYLEM DATA *************//
	TiXmlElement* metaXylemInput = main->FirstChildElement("MetaXylem");
	if (metaXylemInput) {
		metaXylemMinSlice = atoi(metaXylemInput->FirstChildElement("Slices")->Attribute("min"));
		metaXylemMaxSlice = atoi(metaXylemInput->FirstChildElement("Slices")->Attribute("max"));
		metaXylemCellWallWidth = atof(metaXylemInput->FirstChildElement("CellwallWidth")->GetText());
		metaXylemPlasmaMembraneThickness = atof(metaXylemInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		metaXylemGapCytoTono = atof(metaXylemInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		metaXylemGapCellWall = metaXylemCellWallWidth + metaXylemPlasmaMembraneThickness;
		metaXylemVariationRatio = atof(metaXylemInput->Attribute("variationRatio"));
		metaXylemverticalLengthThresholdRatio = atof(metaXylemInput->FirstChildElement("VerticalLengthThresholdRatio")->GetText());
		metaXylemTangentRingRadiusRatio = atof(metaXylemInput->FirstChildElement("TangentRingRadiusRatio")->GetText());
		metaXylemSteleCellNumBetween = atoi(metaXylemInput->FirstChildElement("SteleCellNumBetween")->GetText());
		metaXylemNum = atoi(metaXylemInput->FirstChildElement("MXNum")->GetText());
		metaXylemAverageRingRadius = atof(metaXylemInput->FirstChildElement("MXAverageRingRadius")->GetText());
		metaXylemSurroundingCellRingNum = atoi(metaXylemInput->FirstChildElement("SurroundingCellRingNum")->GetText());
	}
	else {
		cout << "MetaXylem Parameters Missing." << endl;
		return 3;
	}

	//********** PROTOXYLEM DATA *************//
	TiXmlElement* protoXylemInput = main->FirstChildElement("ProtoXylem");
	if (protoXylemInput) {
		protoXylemMinSlice = atoi(protoXylemInput->FirstChildElement("Slices")->Attribute("min"));
		protoXylemMaxSlice = atoi(protoXylemInput->FirstChildElement("Slices")->Attribute("max"));
		protoXylemCellWallWidth = atof(protoXylemInput->FirstChildElement("CellwallWidth")->GetText());
		protoXylemPlasmaMembraneThickness = atof(protoXylemInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		protoXylemGapCytoTono = atof(protoXylemInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		protoXylemGapCellWall = protoXylemCellWallWidth + protoXylemPlasmaMembraneThickness;
		protoXylemVariationRatio = atof(protoXylemInput->Attribute("variationRatio"));
		protoXylemGapRadius = atof(protoXylemInput->FirstChildElement("GapRadius")->GetText());
		protoXylemNum = atoi(protoXylemInput->FirstChildElement("PXNum")->GetText());
		protoXylemAverageRingRadius = atof(protoXylemInput->FirstChildElement("PXAverageRingRadius")->GetText());
		protoXylemSurroundingCellRingNum = atoi(protoXylemInput->FirstChildElement("SurroundingCellRingNum")->GetText());
		protoXylemSurroundingCellRingRadius = atof(protoXylemInput->FirstChildElement("SurroundingCellRingRadius")->GetText());
	}
	else {
		cout << "protoXylem Parameters Missing." << endl;
		return 3;
	}

	//********** EPIDERMIS DATA *************//
	TiXmlElement* epidermisInput = main->FirstChildElement("Epidermis");
	if (epidermisInput) {
		epidermisMinSlice = atoi(epidermisInput->FirstChildElement("Slices")->Attribute("min"));
		epidermisMaxSlice = atoi(epidermisInput->FirstChildElement("Slices")->Attribute("max"));
		epidermisCellWallWidth = atof(epidermisInput->FirstChildElement("CellwallWidth")->GetText());
		epidermisPlasmaMembraneThickness = atof(epidermisInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		epidermisGapCytoTono = atof(epidermisInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		epidermisGapCellWall = epidermisCellWallWidth + epidermisPlasmaMembraneThickness;
		epidermisVariationRatio = atof(epidermisInput->Attribute("variationRatio"));
		epidermisCellDiameter = atof(epidermisInput->FirstChildElement("CellDiameter")->GetText());
		epidermisCellNum = atoi(epidermisInput->FirstChildElement("CellNum")->GetText());
	}
	else {
		cout << "epidermis Parameters Missing." << endl;
	}

	//********** ENDODERMIS DATA *************//
	TiXmlElement* endodermisInput = main->FirstChildElement("Endodermis");
	if (endodermisInput) {
		endodermisMinSlice = atoi(endodermisInput->FirstChildElement("Slices")->Attribute("min"));
		endodermisMaxSlice = atoi(endodermisInput->FirstChildElement("Slices")->Attribute("max"));
		endodermisCellWallWidth = atof(endodermisInput->FirstChildElement("CellwallWidth")->GetText());
		endodermisPlasmaMembraneThickness = atof(endodermisInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		endodermisGapCytoTono = atof(endodermisInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		endodermisGapCellWall = endodermisCellWallWidth + endodermisPlasmaMembraneThickness;
		endodermisVariationRatio = atof(endodermisInput->Attribute("variationRatio"));
		endodermisCellDiameter = atof(endodermisInput->FirstChildElement("CellDiameter")->GetText());
	}
	else {
		cout << "endodermis Parameters Missing." << endl;
	}

	//********** EXODERMIS DATA *************//
	TiXmlElement* exodermisInput = main->FirstChildElement("Exodermis");
	if (exodermisInput) {
		exodermisMinSlice = atoi(exodermisInput->FirstChildElement("Slices")->Attribute("min"));
		exodermisMaxSlice = atoi(exodermisInput->FirstChildElement("Slices")->Attribute("max"));
		exodermisCellWallWidth = atof(exodermisInput->FirstChildElement("CellwallWidth")->GetText());
		exodermisPlasmaMembraneThickness = atof(exodermisInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		exodermisGapCytoTono = atof(exodermisInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		exodermisGapCellWall = exodermisCellWallWidth + exodermisPlasmaMembraneThickness;
		exodermisVariationRatio = atof(exodermisInput->Attribute("variationRatio"));
		exodermisCellDiameter = atof(exodermisInput->FirstChildElement("CellDiameter")->GetText());
	}
	else {
		cout << "exodermis Parameters Missing." << endl;
	}

	//********** SCLERENCHYMA DATA *************//
	TiXmlElement* sclerenchymaInput = main->FirstChildElement("Sclerenchyma");
	if (sclerenchymaInput) {
		sclerenchymaMinSlice = atoi(sclerenchymaInput->FirstChildElement("Slices")->Attribute("min"));
		sclerenchymaMaxSlice = atoi(sclerenchymaInput->FirstChildElement("Slices")->Attribute("max"));
		sclerenchymaCellWallWidth = atof(sclerenchymaInput->FirstChildElement("CellwallWidth")->GetText());
		sclerenchymaPlasmaMembraneThickness = atof(sclerenchymaInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		sclerenchymaGapCytoTono = atof(sclerenchymaInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		sclerenchymaGapCellWall = sclerenchymaCellWallWidth + sclerenchymaPlasmaMembraneThickness;
		sclerenchymaVariationRatio = atof(sclerenchymaInput->Attribute("variationRatio"));
		sclerenchymaCellDiameter = atof(sclerenchymaInput->FirstChildElement("CellDiameter")->GetText());
	}
	else {
		cout << "sclerenchyma Parameters Missing." << endl;
	}

	//********** PERICYCLE DATA *************//
	TiXmlElement* pericycleInput = main->FirstChildElement("Pericycle");
	if (pericycleInput) {
		pericycleMinSlice = atoi(pericycleInput->FirstChildElement("Slices")->Attribute("min"));
		pericycleMaxSlice = atoi(pericycleInput->FirstChildElement("Slices")->Attribute("max"));
		pericycleCellWallWidth = atof(pericycleInput->FirstChildElement("CellwallWidth")->GetText());
		pericyclePlasmaMembraneThickness = atof(pericycleInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		pericycleGapCytoTono = atof(pericycleInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		pericycleGapCellWall = pericycleCellWallWidth + pericyclePlasmaMembraneThickness;
		pericycleVariationRatio = atof(pericycleInput->Attribute("variationRatio"));
		pericycleCellDiameter = atof(pericycleInput->FirstChildElement("CellDiameter")->GetText());
	}
	else {
		cout << "pericycle Parameters Missing." << endl;
	}

	// Get the data of cortical;
	/*TiXmlElement* layer = corticalInput->FirstChildElement("Cortical");

	while (layer)
	{
		corticalAddRadiusInputData.push_back
		(atof(layer->FirstChildElement("AddRadius")->GetText()));
		corticalCellNumInputData.push_back
		(atof(layer->FirstChildElement("CellNumber")->GetText()));
		cout << "RingNum: " << layer->FirstChildElement("RingNum")->GetText() << endl;
		cout << "CellNumber: " << layer->FirstChildElement("CellNumber")->GetText() << endl;
		layer = layer->NextSiblingElement();
	}*/
	/// PlantNum validation end
	//doc.SaveFile("Iamhere.txt");

	//////////////////////////////////////// Visualization //////////////////////////////////////////////

	   /// we visualize in the same renderer - Keep static;
	vtkSmartPointer<vtkRenderer> renL = vtkSmartPointer<vtkRenderer>::New();

	/////////////////////////////////////// Dynamic Output /////////////////////////////////////////

	double corticalCellAddRadiusMinInput = corticalCellDiameter;
	double gapCytoTonoInput = corticalGapCytoTono;
	double gapCellWallInput = corticalGapCellWall;
	double PM_thick = corticalPlasmaMembraneThickness;
	
	double rcaRatioInput;
	int rcaRatioInt;

	/// Keep the cortex radius unchanged;
 //   corticalCellAddRadiusMinInput = 0;
 //   int corticalAddRadiusDBSelectInput = 1;
 //   int corticalCellNumSelectInput = 1;
 //   double cortexRadiusInput = 300;

	/// Change the cortex radius;
 //   for (corticalCellAddRadiusMinInput);
 //   int corticalAddRadiusDBSelectInput = 1;
 //   int corticalCellNumSelectInput = 1;
 //   double cortexRadiusInput = 0;


	for (rcaRatioInt = 0; rcaRatioInt <= 1; rcaRatioInt++) {
		rcaRatioInput = rcaRatio * rcaRatioInt;
		/////////////////////////////////////// Cortex ////////////////////////////////
		rsDynamicDataOutput* RsDynamicDataOutput = new rsDynamicDataOutput;
		int setUResolution = 12;
		int setVResolution = 12;
		int setWResolution = 12;

		/// Cortical;
		int corticalAddRadiusDBSelectInput = 1;
		int corticalCellNumSelectInput = 1;
		int corticalSliceNum = corticalMinSlice + (rand() % (corticalMaxSlice - corticalMinSlice +1));
		double initZPosition = -225;
		int vectorNum = 200;
		double corticalCellMultiplyRatio = 0.1;
		double cortexRadiusInput = 0;

		  /*Stele parameters*/
		double steleInnestCellRadiusInput = steleInnestCellDiameter/2.0;

		/// Output filename;

		/// steleRadius to string;
		string steleRadiusName = "SteleRadius(um)";
		stringstream steleRadiusSS;
		string steleRadiusString;
		steleRadiusSS << baseRadius;
		steleRadiusSS >> steleRadiusString;

		/// corticalRingNum to string;
		string ringNumName = "RingNum";
		stringstream ringNumSS;
		string ringNumString;
		ringNumSS << corticalNumFiles;
		ringNumSS >> ringNumString;

		/// CorticalInnestCellDiameter to string;
		string corticalInnermostCellDiameterName = "CorticalInnermostCellDiameter(um)";
		stringstream corticalInnermostCellDiameterSS;
		string corticalInnermostCellDiameterString;
		corticalInnermostCellDiameterSS << corticalCellAddRadiusMinInput;
		corticalInnermostCellDiameterSS >> corticalInnermostCellDiameterString;

		/// rca2CortexRatio to string;
		string rca2CortexRatioName = "RCA2CortexRatio";
		stringstream rca2CortexRatioSS;
		string rca2CortexRatioString;
		rca2CortexRatioSS << rcaRatioInput;
		rca2CortexRatioSS >> rca2CortexRatioString;

		/// gapCytoTono to string;
		string gapCytoTonoName = "GapCytoTono(um)";
		stringstream gapCytoTonoSS;
		string gapCytoTonoString;
		gapCytoTonoSS << gapCytoTonoInput;
		gapCytoTonoSS >> gapCytoTonoString;

		/// totalheight to string ** Jagdeep 12-2-2020
		string TotalHeightName = "TotalHeight";
		stringstream TotalHeightSS;
		string TotalHeightString;
		TotalHeightSS << totalHeight;
		TotalHeightSS >> TotalHeightString;

		string blankSpace = " ";

		string prefix = steleRadiusName + blankSpace + steleRadiusString + blankSpace
			+ ringNumName + blankSpace + ringNumString + blankSpace
			+ corticalInnermostCellDiameterName + blankSpace + corticalInnermostCellDiameterString + blankSpace
			+ gapCytoTonoName + blankSpace + gapCytoTonoString + blankSpace
			+ rca2CortexRatioName + blankSpace + rca2CortexRatioString + blankSpace
			+ TotalHeightName + blankSpace + TotalHeightString;

		string prefixCortical = "Cortical";
		string prefixCorticalVacuole = "CorticalVacuole";
		string prefixPlasmaMembrane = "CorticalPlasmaMembrane";
		string suffix = ".vtp";
		string tempCortical = filePrefix + prefixCortical + prefix + suffix;
		string tempCorticalVacuole = filePrefix + prefixCorticalVacuole + prefix + suffix;
		string tempCorticalPlasmaMembrane = filePrefix + prefixPlasmaMembrane + prefix + suffix;
		const char* CorticalXMLVtpFileNameInput = tempCortical.c_str();
		const char* CorticalVacuoleXMLVtpFileNameInput = tempCorticalVacuole.c_str();
		const char* CorticalPlasmaMembraneVtpFileNameInput = tempCorticalPlasmaMembrane.c_str();


		/// RCA;
		int rcaNumInput;
		if (rcaRatioInput <= 0.05)
		{
			rcaNumInput = 10;
		}
		else
		{
			rcaNumInput = 15;
		}
		int standardOuterLayerInput = 1;
		int standardInnerLayerInput = 1;
		double gapAngleBetweenRcaRatio = 0.005;
		double variationRatioRca = 0.2;

		/// Plasma Membrane
		double plasmaMembraneWidth = corticalPlasmaMembraneThickness;

		/// Sclerenchyma
		int sclerenSliceNum = sclerenchymaMinSlice + (rand() % (sclerenchymaMaxSlice - sclerenchymaMinSlice + 1));
		double sclerenAddRadiusData = sclerenchymaCellDiameter/2.0;

		/// Scleren Output filename;
		string prefixScleren = "Sclerenchyma";
		string tempScleren = filePrefix + prefixScleren + prefix + suffix;
		const char* SclerenXMLVtpFileNameInput = tempScleren.c_str();

		/// Epidermis;
		int epidermisSliceNum = epidermisMinSlice + (rand() % (epidermisMaxSlice - epidermisMinSlice + 1));
		double epidermisAddRadiusData = epidermisCellDiameter/2.0;
		double variationRatioDermis = epidermisVariationRatio;

		/// Epi Output filename;
		string prefixEpidermis = "Epidermis";
		string tempEpidermis = filePrefix + prefixEpidermis + prefix + suffix;
		const char* EpidermisXMLVtpFileNameInput = tempEpidermis.c_str();

		/// Endodermis;
		int endodermisSliceNum = endodermisMinSlice + (rand() % (endodermisMaxSlice - endodermisMinSlice + 1));
		double endodermisAddRadiusData = endodermisCellDiameter/2.0;

		/// Endo Output filename;
		string prefixEndodermis = "Endodermis";
		string tempEndodermis = filePrefix + prefixEndodermis + prefix + suffix;
		const char* EndodermisXMLVtpFileNameInput = tempEndodermis.c_str();

		/// Pericycle
		int pericycleSliceNum = pericycleMinSlice + (rand() % (pericycleMaxSlice - pericycleMinSlice + 1));
		double pericycleAddRadiusData = pericycleCellDiameter/2.0;

		/// Peric Output filename;
		string prefixPericycle = "Pericycle";
		string tempPericycle = filePrefix + prefixPericycle + prefix + suffix;
		const char* PericycXMLVtpFileNameInput = tempPericycle.c_str();


		/// Apoplast and Symplast Output filename;
		string prefixApoplast = "Apoplast";
		string prefixSymplast = "Symplast";
		string tempApoplast = filePrefix + prefixApoplast + prefix + suffix;
		string tempSymplast = filePrefix + prefixSymplast + prefix + suffix;
		const char* ApoplastXMLVtpFileNameInput = tempApoplast.c_str();
		const char* SymplastXMLVtpFileNameInput = tempSymplast.c_str();

		/// DataOutputName
		string prefixDataOutput = "DataOutput";
		string txtSuffix = ".txt";
		string tempDataOutput = filePrefix + prefixDataOutput + prefix + txtSuffix;
		const char* dataOutputNameInput = tempDataOutput.c_str();


		/// Judge whether the rcaRatioInput is 0;
		if (rcaRatioInput == 0)
		{
			RsDynamicDataOutput->InitEpiCortexEndoNonRCADB
			(
				setUResolution,
				setVResolution,
				setWResolution,
				baseRadius,
				thickness,
				totalHeight,

				/// Cortical;
				corticalAddRadiusInputData,
				corticalCellNumInputData,
				corticalAddRadiusDBSelectInput,
				corticalCellNumSelectInput,
				corticalSliceNum,
				initZPosition,
				vectorNum,
				corticalVariationRatio,
				corticalNumFiles,
				corticalCellMultiplyRatio,
				corticalCellAddRadiusMinInput,
				cortexRadiusInput,

				/// Pure Cortical Cell;
				gapCellWallInput,

				/// Cortical Vacuole;
				gapCytoTonoInput,

				/// Plasma Membrane
				plasmaMembraneWidth,

				/// Sclerenchyma
				sclerenSliceNum,
				sclerenAddRadiusData,

				/// Epi;
				epidermisSliceNum,
				epidermisAddRadiusData,
				//                        epidermisCellNum,
				variationRatioDermis,

				/// Endo;
				endodermisSliceNum,
				endodermisAddRadiusData,
				//                        endodermisCellNum,

				// Pericycle
				pericycleSliceNum,
				pericycleAddRadiusData,


										   /// OutXMLVtpFileName;
				CorticalXMLVtpFileNameInput,
				CorticalVacuoleXMLVtpFileNameInput,
				CorticalPlasmaMembraneVtpFileNameInput,
				SclerenXMLVtpFileNameInput,
				EpidermisXMLVtpFileNameInput,
				EndodermisXMLVtpFileNameInput,
				ApoplastXMLVtpFileNameInput,
				SymplastXMLVtpFileNameInput,
				PericycXMLVtpFileNameInput,

				/// DataOutputName;
				dataOutputNameInput,

				/// Others
				renL,
				steleVariationRatio,
				steleMinSlice,
				steleInnestCellRadiusInput,
				steleInnerLayerNum,
				metaXylemverticalLengthThresholdRatio,
				metaXylemTangentRingRadiusRatio,
				metaXylemSteleCellNumBetween,
				metaXylemNum,
				metaXylemAverageRingRadius,
				metaXylemSurroundingCellRingNum,
				protoXylemGapRadius,
				protoXylemNum,
				protoXylemAverageRingRadius,
				protoXylemSurroundingCellRingNum,
				protoXylemSurroundingCellRingRadius
			);
		}
		else
		{
			RsDynamicDataOutput->InitEpiCortexEndoAllDB
			(
				setUResolution,
				setVResolution,
				setWResolution,
				baseRadius,
				thickness,
				totalHeight,

				/// Cortical;
				corticalAddRadiusInputData,
				corticalCellNumInputData,
				corticalAddRadiusDBSelectInput,
				corticalCellNumSelectInput,
				corticalSliceNum,
				initZPosition,
				vectorNum,
				corticalVariationRatio,
				corticalNumFiles,
				corticalCellMultiplyRatio,
				corticalCellAddRadiusMinInput,
				cortexRadiusInput,

				/// RCA;
				rcaRatioInput,
				rcaNumInput,
				standardOuterLayerInput,
				standardInnerLayerInput,
				gapAngleBetweenRcaRatio,
				variationRatioRca,

				/// Pure Cortical Cell;
				gapCellWallInput,

				/// Cortical Vacuole;
				gapCytoTonoInput,

				/// Plasma Membrane
				plasmaMembraneWidth,

				/// Sclerenchyma
				sclerenSliceNum,
				sclerenAddRadiusData,

				/// Epi;
				epidermisSliceNum,
				epidermisAddRadiusData,
				//                        epidermisCellNum,
				variationRatioDermis,

				/// Endo;
				endodermisSliceNum,
				endodermisAddRadiusData,
				//                        endodermisCellNum,

				// Pericycle
				pericycleSliceNum,
				pericycleAddRadiusData,
										   /// OutXMLVtpFileName;
				CorticalXMLVtpFileNameInput,
				CorticalVacuoleXMLVtpFileNameInput,
				CorticalPlasmaMembraneVtpFileNameInput,
				SclerenXMLVtpFileNameInput,
				EpidermisXMLVtpFileNameInput,
				EndodermisXMLVtpFileNameInput,
				ApoplastXMLVtpFileNameInput,
				SymplastXMLVtpFileNameInput,
				PericycXMLVtpFileNameInput,

				/// DataOutputName;
				dataOutputNameInput,

				/// Others
				renL
			);

		}
	}
	return 0;
}