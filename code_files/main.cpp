#include "tinyxml.h"
#include "viStringTokenizer.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include "rsDynamicDataOutput.h"
#include "rsSteleInnerVisual.h"
#include "globals.h"
#include <ctime>
#include <filesystem>

namespace fs = std::filesystem;

/////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	//////////////////////////////////////// Visualization //////////////////////////////////////////////
	vtkSmartPointer<vtkRenderer> renL = vtkSmartPointer<vtkRenderer>::New();

	TiXmlDocument doc("CorticalData.xml");
	doc.LoadFile();
	TiXmlElement* main = doc.FirstChildElement("Main");
	const char* filePrefix = main->Attribute("name");
	std::time_t curTime = time(NULL);

	const tm *startTime = localtime(&curTime);
	char outputFolderName [80];

	char formatSpecifier[80]{};
	strcpy(formatSpecifier, filePrefix);
	strcat(formatSpecifier, "_%F_%H-%M");
	const char* folderFormat = formatSpecifier;
	strftime(outputFolderName, 80, folderFormat, startTime);
	
	fs::create_directory(outputFolderName);
	globals::setFolderName(outputFolderName);

	vector<double> corticalAddRadiusInputData;
	vector<int> corticalCellNumInputData;

	globals cortical;
	globals stele;
	globals metaXylem;
	globals protoXylem;
	globals epidermis;
	globals endodermis;
	globals exodermis;
	globals sclerenchyma;
	globals pericycle;

	globals::totalHeight = atof(main->Attribute("height"));

	// READ PARAMETERS FROM XML FILE //
	//********** CORTICAL DATA *************//
	TiXmlElement* corticalInput = main->FirstChildElement("Cortical");
	if (corticalInput) {
		globals::baseRadius = atof(corticalInput->FirstChildElement("BaseRadius")->GetText());
		globals::thickness = atof(corticalInput->FirstChildElement("Thickness")->GetText());
		cout << "baseRadius: " << globals::baseRadius;
		cout << "Thickness: " << globals::thickness;
		cortical.cellWallWidth = atof(corticalInput->FirstChildElement("CellwallWidth")->GetText());
		cortical.plasmaMembraneThickness = atof(corticalInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		cortical.gapCytoTono = atof(corticalInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		cortical.gapCellWall = cortical.cellWallWidth + cortical.plasmaMembraneThickness;
		cortical.variationRatio = atof(corticalInput->Attribute("variationRatio"));
		cortical.minSlice = atoi(corticalInput->FirstChildElement("Slices")->Attribute("min"));
		cortical.maxSlice = atoi(corticalInput->FirstChildElement("Slices")->Attribute("max"));
		cortical.numFiles = atoi(corticalInput->FirstChildElement("NumFiles")->GetText());
		globals::rcaRatio = atof(corticalInput->FirstChildElement("RCARatio")->GetText());
		cortical.cellDiameter = atof(corticalInput->FirstChildElement("CellDiameter")->GetText());
	}
	else {
		cout << "Cortical Data Missing." << endl;
		return 1;
	}

	//********** STELE DATA *************//
	TiXmlElement* steleInput = main->FirstChildElement("Stele");
	if (steleInput) {
		stele.minSlice = atoi(steleInput->FirstChildElement("Slices")->Attribute("min"));
		stele.maxSlice = atoi(steleInput->FirstChildElement("Slices")->Attribute("max"));
		stele.cellWallWidth = atof(steleInput->FirstChildElement("CellwallWidth")->GetText());
		stele.plasmaMembraneThickness = atof(steleInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		stele.gapCytoTono = atof(steleInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		stele.gapCellWall = stele.cellWallWidth + stele.plasmaMembraneThickness;
		stele.variationRatio = atof(steleInput->Attribute("variationRatio"));
		stele.innestCellDiameter = atof(steleInput->FirstChildElement("InnestCellDiameer")->GetText());
		stele.innerLayerNum = atoi(steleInput->FirstChildElement("InnerLayerNum")->GetText());
	}
	else {
		cout << "Stele Parameters Missing." << endl;
		return 2;
	}

	//********** METAXYLEM DATA *************//
	TiXmlElement* metaXylemInput = main->FirstChildElement("MetaXylem");
	if (metaXylemInput) {
		metaXylem.minSlice = atoi(metaXylemInput->FirstChildElement("Slices")->Attribute("min"));
		metaXylem.maxSlice = atoi(metaXylemInput->FirstChildElement("Slices")->Attribute("max"));
		metaXylem.cellWallWidth = atof(metaXylemInput->FirstChildElement("CellwallWidth")->GetText());
		metaXylem.plasmaMembraneThickness = atof(metaXylemInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		metaXylem.gapCytoTono = atof(metaXylemInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		metaXylem.gapCellWall = metaXylem.cellWallWidth + metaXylem.plasmaMembraneThickness;
		metaXylem.variationRatio = atof(metaXylemInput->Attribute("variationRatio"));
		metaXylem.verticalLengthThresholdRatio = atof(metaXylemInput->FirstChildElement("VerticalLengthThresholdRatio")->GetText());
		metaXylem.tangentRingRadiusRatio = atof(metaXylemInput->FirstChildElement("TangentRingRadiusRatio")->GetText());
		metaXylem.steleCellNumBetween = atoi(metaXylemInput->FirstChildElement("SteleCellNumBetween")->GetText());
		metaXylem.num = atoi(metaXylemInput->FirstChildElement("MXNum")->GetText());
		metaXylem.averageRingRadius = atof(metaXylemInput->FirstChildElement("MXAverageRingRadius")->GetText());
		metaXylem.surroundingCellRingNum = atoi(metaXylemInput->FirstChildElement("SurroundingCellRingNum")->GetText());
	}
	else {
		cout << "MetaXylem Parameters Missing." << endl;
		return 3;
	}

	//********** PROTOXYLEM DATA *************//
	TiXmlElement* protoXylemInput = main->FirstChildElement("ProtoXylem");
	if (protoXylemInput) {
		protoXylem.minSlice = atoi(protoXylemInput->FirstChildElement("Slices")->Attribute("min"));
		protoXylem.maxSlice = atoi(protoXylemInput->FirstChildElement("Slices")->Attribute("max"));
		protoXylem.cellWallWidth = atof(protoXylemInput->FirstChildElement("CellwallWidth")->GetText());
		protoXylem.plasmaMembraneThickness = atof(protoXylemInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		protoXylem.gapCytoTono = atof(protoXylemInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		protoXylem.gapCellWall = protoXylem.cellWallWidth + protoXylem.plasmaMembraneThickness;
		protoXylem.variationRatio = atof(protoXylemInput->Attribute("variationRatio"));
		protoXylem.gapRadius = atof(protoXylemInput->FirstChildElement("GapRadius")->GetText());
		protoXylem.num = atoi(protoXylemInput->FirstChildElement("PXNum")->GetText());
		protoXylem.averageRingRadius = atof(protoXylemInput->FirstChildElement("PXAverageRingRadius")->GetText());
		protoXylem.surroundingCellRingNum = atoi(protoXylemInput->FirstChildElement("SurroundingCellRingNum")->GetText());
		protoXylem.surroundingCellRingRadius = atof(protoXylemInput->FirstChildElement("SurroundingCellRingRadius")->GetText());
	}
	else {
		cout << "protoXylem Parameters Missing." << endl;
		return 3;
	}

	//********** EPIDERMIS DATA *************//
	TiXmlElement* epidermisInput = main->FirstChildElement("Epidermis");
	if (epidermisInput) {
		epidermis.minSlice = atoi(epidermisInput->FirstChildElement("Slices")->Attribute("min"));
		epidermis.maxSlice = atoi(epidermisInput->FirstChildElement("Slices")->Attribute("max"));
		epidermis.cellWallWidth = atof(epidermisInput->FirstChildElement("CellwallWidth")->GetText());
		epidermis.plasmaMembraneThickness = atof(epidermisInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		epidermis.gapCytoTono = atof(epidermisInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		epidermis.gapCellWall = epidermis.cellWallWidth + epidermis.plasmaMembraneThickness;
		epidermis.variationRatio = atof(epidermisInput->Attribute("variationRatio"));
		epidermis.cellDiameter = atof(epidermisInput->FirstChildElement("CellDiameter")->GetText());
		epidermis.cellNum = atoi(epidermisInput->FirstChildElement("CellNum")->GetText());
	}
	else {
		cout << "epidermis Parameters Missing." << endl;
	}

	//********** ENDODERMIS DATA *************//
	TiXmlElement* endodermisInput = main->FirstChildElement("Endodermis");
	if (endodermisInput) {
		endodermis.minSlice = atoi(endodermisInput->FirstChildElement("Slices")->Attribute("min"));
		endodermis.maxSlice = atoi(endodermisInput->FirstChildElement("Slices")->Attribute("max"));
		endodermis.cellWallWidth = atof(endodermisInput->FirstChildElement("CellwallWidth")->GetText());
		endodermis.plasmaMembraneThickness = atof(endodermisInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		endodermis.gapCytoTono = atof(endodermisInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		endodermis.gapCellWall = endodermis.cellWallWidth + endodermis.plasmaMembraneThickness;
		endodermis.variationRatio = atof(endodermisInput->Attribute("variationRatio"));
		endodermis.cellDiameter = atof(endodermisInput->FirstChildElement("CellDiameter")->GetText());
	}
	else {
		cout << "endodermis Parameters Missing." << endl;
	}

	//********** EXODERMIS DATA *************//
	TiXmlElement* exodermisInput = main->FirstChildElement("Exodermis");
	if (exodermisInput) {
		exodermis.minSlice = atoi(exodermisInput->FirstChildElement("Slices")->Attribute("min"));
		exodermis.maxSlice = atoi(exodermisInput->FirstChildElement("Slices")->Attribute("max"));
		exodermis.cellWallWidth = atof(exodermisInput->FirstChildElement("CellwallWidth")->GetText());
		exodermis.plasmaMembraneThickness = atof(exodermisInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		exodermis.gapCytoTono = atof(exodermisInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		exodermis.gapCellWall = exodermis.cellWallWidth + exodermis.plasmaMembraneThickness;
		exodermis.variationRatio = atof(exodermisInput->Attribute("variationRatio"));
		exodermis.cellDiameter = atof(exodermisInput->FirstChildElement("CellDiameter")->GetText());
	}
	else {
		cout << "exodermis Parameters Missing." << endl;
	}

	//********** SCLERENCHYMA DATA *************//
	TiXmlElement* sclerenchymaInput = main->FirstChildElement("Sclerenchyma");
	if (sclerenchymaInput) {
		sclerenchyma.minSlice = atoi(sclerenchymaInput->FirstChildElement("Slices")->Attribute("min"));
		sclerenchyma.maxSlice = atoi(sclerenchymaInput->FirstChildElement("Slices")->Attribute("max"));
		sclerenchyma.cellWallWidth = atof(sclerenchymaInput->FirstChildElement("CellwallWidth")->GetText());
		sclerenchyma.plasmaMembraneThickness = atof(sclerenchymaInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		sclerenchyma.gapCytoTono = atof(sclerenchymaInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		sclerenchyma.gapCellWall = sclerenchyma.cellWallWidth + sclerenchyma.plasmaMembraneThickness;
		sclerenchyma.variationRatio = atof(sclerenchymaInput->Attribute("variationRatio"));
		sclerenchyma.cellDiameter = atof(sclerenchymaInput->FirstChildElement("CellDiameter")->GetText());
	}
	else {
		cout << "sclerenchyma Parameters Missing." << endl;
	}

	//********** PERICYCLE DATA *************//
	TiXmlElement* pericycleInput = main->FirstChildElement("Pericycle");
	if (pericycleInput) {
		pericycle.minSlice = atoi(pericycleInput->FirstChildElement("Slices")->Attribute("min"));
		pericycle.maxSlice = atoi(pericycleInput->FirstChildElement("Slices")->Attribute("max"));
		pericycle.cellWallWidth = atof(pericycleInput->FirstChildElement("CellwallWidth")->GetText());
		pericycle.plasmaMembraneThickness = atof(pericycleInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		pericycle.gapCytoTono = atof(pericycleInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		pericycle.gapCellWall = pericycle.cellWallWidth + pericycle.plasmaMembraneThickness;
		pericycle.variationRatio = atof(pericycleInput->Attribute("variationRatio"));
		pericycle.cellDiameter = atof(pericycleInput->FirstChildElement("CellDiameter")->GetText());
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

	/////////////////////////////////////// Dynamic Output /////////////////////////////////////////

	//double gapCytoTonoInput = cortical.gapCytoTono;
	//double gapCellWallInput = cortical.gapCellWall;
	//double PM_thick = cortical.plasmaMembraneThickness;
	
	double rcaRatioInput;
	int rcaRatioInt;

	for (rcaRatioInt = 0; rcaRatioInt <= 1; rcaRatioInt++) {
		rcaRatioInput = globals::rcaRatio * rcaRatioInt;
		/////////////////////////////////////// Cortex ////////////////////////////////
		rsDynamicDataOutput* RsDynamicDataOutput = new rsDynamicDataOutput;

		/// Cortical;
		int corticalSliceNum = cortical.minSlice + (rand() % (cortical.maxSlice - cortical.minSlice +1));

		  /*Stele parameters*/
		double steleInnestCellRadiusInput = stele.innestCellDiameter/2.0;

		/// Output filename;

		/// steleRadius to string;
		string steleRadiusName = "SteleRadius(um)";
		stringstream steleRadiusSS;
		string steleRadiusString;
		steleRadiusSS << globals::baseRadius;
		steleRadiusSS >> steleRadiusString;

		/// corticalRingNum to string;
		string ringNumName = "RingNum";
		stringstream ringNumSS;
		string ringNumString;
		ringNumSS << cortical.numFiles;
		ringNumSS >> ringNumString;

		/// CorticalInnestCellDiameter to string;
		string corticalInnermostCellDiameterName = "CorticalInnermostCellDiameter(um)";
		stringstream corticalInnermostCellDiameterSS;
		string corticalInnermostCellDiameterString;
		corticalInnermostCellDiameterSS << cortical.cellDiameter/2;
		corticalInnermostCellDiameterSS >> corticalInnermostCellDiameterString;

		/// rca2CortexRatio to string;
		string rca2CortexRatioName = "RCA2CortexRatio";
		stringstream rca2CortexRatioSS;
		string rca2CortexRatioString;
		rca2CortexRatioSS << rcaRatioInput;
		rca2CortexRatioSS >> rca2CortexRatioString;

		/// totalheight to string ** Jagdeep 12-2-2020
		string TotalHeightName = "TotalHeight";
		stringstream TotalHeightSS;
		string TotalHeightString;
		TotalHeightSS << globals::totalHeight;
		TotalHeightSS >> TotalHeightString;

		string blankSpace = " ";

		string prefix = steleRadiusName + blankSpace + steleRadiusString + blankSpace
			+ ringNumName + blankSpace + ringNumString + blankSpace
			+ corticalInnermostCellDiameterName + blankSpace + corticalInnermostCellDiameterString + blankSpace
			+ rca2CortexRatioName + blankSpace + rca2CortexRatioString + blankSpace
			+ TotalHeightName + blankSpace + TotalHeightString;

		string prefixCortical = " Cortical ";
		string prefixCorticalVacuole = " CorticalVacuole ";
		string prefixPlasmaMembrane = " CorticalPlasmaMembrane ";
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
		double plasmaMembraneWidth = cortical.plasmaMembraneThickness;

		/// Sclerenchyma
		int sclerenSliceNum = sclerenchyma.minSlice + (rand() % (sclerenchyma.maxSlice - sclerenchyma.minSlice + 1));
		double sclerenAddRadiusData = sclerenchyma.cellDiameter/2.0;

		/// Scleren Output filename;
		string prefixScleren = "Sclerenchyma";
		string tempScleren = filePrefix + prefixScleren + prefix + suffix;
		const char* SclerenXMLVtpFileNameInput = tempScleren.c_str();

		/// Epidermis;
		int epidermisSliceNum = epidermis.minSlice + (rand() % (epidermis.maxSlice - epidermis.minSlice + 1));
		double epidermisAddRadiusData = epidermis.cellDiameter/2.0;
		double variationRatioDermis = epidermis.variationRatio;

		/// Epi Output filename;
		string prefixEpidermis = "Epidermis";
		string tempEpidermis = filePrefix + prefixEpidermis + prefix + suffix;
		const char* EpidermisXMLVtpFileNameInput = tempEpidermis.c_str();

		/// Endodermis;
		int endodermisSliceNum = endodermis.minSlice + (rand() % (endodermis.maxSlice - endodermis.minSlice + 1));
		double endodermisAddRadiusData = endodermis.cellDiameter/2.0;

		/// Endo Output filename;
		string prefixEndodermis = "Endodermis";
		string tempEndodermis = filePrefix + prefixEndodermis + prefix + suffix;
		const char* EndodermisXMLVtpFileNameInput = tempEndodermis.c_str();

		/// Pericycle
		int pericycleSliceNum = pericycle.minSlice + (rand() % (pericycle.maxSlice - pericycle.minSlice + 1));
		double pericycleAddRadiusData = pericycle.cellDiameter/2.0;

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
				/// All objects;
				cortical,
				stele,
				metaXylem,
				protoXylem,
				epidermis,
				endodermis,
				exodermis,
				sclerenchyma,
				pericycle,

				/// Cortical;
				corticalAddRadiusInputData,
				corticalCellNumInputData,
				corticalSliceNum,

				/// Sclerenchyma
				sclerenSliceNum,
				sclerenAddRadiusData,

				/// Epi;
				epidermisSliceNum,
				epidermisAddRadiusData,

				/// Endo;
				endodermisSliceNum,
				endodermisAddRadiusData,

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

				//Other
				renL
			);
		}
		else
		{
			RsDynamicDataOutput->InitEpiCortexEndoAllDB
			(
				/// All objects;
				cortical,
				stele,
				metaXylem,
				protoXylem,
				epidermis,
				endodermis,
				exodermis,
				sclerenchyma,
				pericycle,

				/// Cortical;
				corticalAddRadiusInputData,
				corticalCellNumInputData,
				corticalSliceNum,
				
				/// RCA;
				rcaRatioInput,
				rcaNumInput,
				standardOuterLayerInput,
				standardInnerLayerInput,
				gapAngleBetweenRcaRatio,
				variationRatioRca,

				/// Plasma Membrane
				plasmaMembraneWidth,

				/// Sclerenchyma
				sclerenSliceNum,
				sclerenAddRadiusData,

				/// Epi;
				epidermisSliceNum,
				epidermisAddRadiusData,

				/// Endo;
				endodermisSliceNum,
				endodermisAddRadiusData,

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

				//Other
				renL
			);
		}
		string pvdFileName = "allVTP_RCA " + to_string(rcaRatioInput) + ".pvd";
		globals::writePVDFile(pvdFileName);
		globals::resetFileNameList();
	}
	return 0;
}