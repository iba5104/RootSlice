#define _USE_MATH_DEFINES
#include "tinyxml.h"
#include "viStringTokenizer.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include "rsDynamicDataOutput.h"
#include "fluxEqns.h"
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

	TiXmlDocument doc("InputData.xml");
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
	
	vector<double> corticalAddRadiusInputData;
	vector<int> corticalCellNumInputData;

	globals cortical;
	globals stele;
	globals metaXylem;
	globals protoXylem;
	globals phloem;
	globals epidermis;
	globals endodermis;
	globals exodermis;
	globals sclerenchyma;
	globals pericycle;
	globals surfaceFlux;
	vector<globals> nutrients;

	globals::totalHeight = atof(main->Attribute("height"));
	globals::type_dicot = (strcmp(main->Attribute("type"), "dicot") == 0);

	vector<double> rcaRatioVals;
	vector<double> baseRadiusVals;
	vector<int> numFilesVals;

	string delimiter = ",";
	size_t pos = 0;

	// READ PARAMETERS FROM XML FILE //
	//********** CORTICAL DATA *************//
	TiXmlElement* corticalInput = main->FirstChildElement("Cortical");
	if (corticalInput) {
		string baseRadiusInput = corticalInput->FirstChildElement("BaseRadius")->GetText();
		while ((pos = baseRadiusInput.find(delimiter)) != std::string::npos) {
			double tempDiameter = stof(baseRadiusInput.substr(0, pos));
			baseRadiusVals.push_back(tempDiameter);
			baseRadiusInput.erase(0, pos + delimiter.length());
		}
		baseRadiusVals.push_back(stof(baseRadiusInput));
		pos = 0;
		//globals::baseRadius = atof(corticalInput->FirstChildElement("BaseRadius")->GetText());
		//globals::thickness = atof(corticalInput->FirstChildElement("Thickness")->GetText());
		//cout << "Thickness: " << globals::thickness;
		if (corticalInput->FirstChildElement("NumFiles")) {
			string numFilesInput = corticalInput->FirstChildElement("NumFiles")->GetText();
			while ((pos = numFilesInput.find(delimiter)) != std::string::npos) {
				double tempDiameter = stof(numFilesInput.substr(0, pos));
				numFilesVals.push_back(tempDiameter);
				numFilesInput.erase(0, pos + delimiter.length());
			}
			numFilesVals.push_back(stof(numFilesInput));
			pos = 0;
			//cortical.numFiles = atoi(corticalInput->FirstChildElement("NumFiles")->GetText());
		}
		else {
			cortical.numFiles = 1;
		}
		cortical.cellWallWidth = atof(corticalInput->FirstChildElement("CellwallWidth")->GetText());
		cortical.plasmaMembraneThickness = atof(corticalInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		cortical.gapCytoTono = atof(corticalInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		cortical.gapCellWall = cortical.cellWallWidth + cortical.plasmaMembraneThickness;
		cortical.variationRatio = atof(corticalInput->Attribute("variationRatio"));
		cortical.minSlice = atoi(corticalInput->FirstChildElement("Slices")->Attribute("min"));
		cortical.maxSlice = atoi(corticalInput->FirstChildElement("Slices")->Attribute("max"));
		double rcaRatioInputCur = atof(corticalInput->FirstChildElement("RCARatio")->Attribute("min"));
		double rcaRatioInputMax = atof(corticalInput->FirstChildElement("RCARatio")->Attribute("max"));
		double rcaRatioInputStep = atof(corticalInput->FirstChildElement("RCARatio")->Attribute("step"));
		rcaRatioVals.reserve((rcaRatioInputMax - rcaRatioInputCur) / rcaRatioInputStep + 1);
		while (rcaRatioInputCur <= rcaRatioInputMax) {
			rcaRatioVals.push_back(rcaRatioInputCur);
			rcaRatioInputCur += rcaRatioInputStep;
		}
		//globals::rcaRatio = atof(corticalInput->FirstChildElement("RCARatio")->GetText());
		string cellDiameterInput = corticalInput->FirstChildElement("CellDiameter")->GetText();
		while ((pos = cellDiameterInput.find(delimiter)) != std::string::npos) {
			double tempDiameter = stof(cellDiameterInput.substr(0, pos));
			cortical.cellDiameter.push_back(tempDiameter);
			cellDiameterInput.erase(0, pos + delimiter.length());
			corticalAddRadiusInputData.push_back(tempDiameter);
		}
		cortical.cellDiameter.push_back(stof(cellDiameterInput));
		cout << "baseRadius: " << globals::baseRadius;
		if (corticalInput->FirstChildElement("MultiplyRatio")) {
			globals::corticalCellMultiplyRatio = atof(corticalInput->FirstChildElement("MultiplyRatio")->GetText());
		}
	}
	else {
		cout << "Cortical Data Missing." << endl;
		return 1;
	}

	if (cortical.cellDiameter.size() > 1) {
		globals::corticalAddRadiusDBSelectInput = 0;
	}

	//********** STELE DATA *************//
	TiXmlElement* steleInput = main->FirstChildElement("Stele");
	if (steleInput) {
		TiXmlElement* curElmnt;
		curElmnt = steleInput->FirstChildElement("Slices");
		if (curElmnt) {
			stele.minSlice = atoi(curElmnt->Attribute("min"));
			stele.maxSlice = atoi(curElmnt->Attribute("max"));
		}
		curElmnt = steleInput->FirstChildElement("CellwallWidth");
		if (curElmnt)
			stele.cellWallWidth = atof(curElmnt->GetText());
		curElmnt = steleInput->FirstChildElement("PlasmaMembraneWidth");
		if (curElmnt)
			stele.plasmaMembraneThickness = atof(curElmnt->GetText());
		curElmnt = steleInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap");
		if (curElmnt)
			stele.gapCytoTono = atof(curElmnt->GetText());
		stele.gapCellWall = stele.cellWallWidth + stele.plasmaMembraneThickness;
		stele.variationRatio = atof(steleInput->Attribute("variationRatio"));
		curElmnt = steleInput->FirstChildElement("InnestCellDiameer");
		if (curElmnt)
			stele.innestCellDiameter = atof(curElmnt->GetText());
		curElmnt = steleInput->FirstChildElement("InnerLayerNum");
		if (curElmnt)
			stele.innerLayerNum = atof(curElmnt->GetText());
	}
	else {
		cout << "Stele Parameters Missing." << endl;
		return 2;
	}

	//********** METAXYLEM DATA *************//
	TiXmlElement* metaXylemInput = main->FirstChildElement("MetaXylem");
	if (metaXylemInput) {
		TiXmlElement* curElmnt;
		curElmnt = metaXylemInput->FirstChildElement("Slices");
		if (curElmnt) {
			metaXylem.minSlice = atoi(curElmnt->Attribute("min"));
			metaXylem.maxSlice = atoi(curElmnt->Attribute("max"));
		}
		curElmnt = metaXylemInput->FirstChildElement("CellwallWidth");
		if (curElmnt)
			metaXylem.cellWallWidth = atof(curElmnt->GetText());
		curElmnt = metaXylemInput->FirstChildElement("PlasmaMembraneWidth");
		if (curElmnt)
			metaXylem.plasmaMembraneThickness = atof(curElmnt->GetText());
		curElmnt = metaXylemInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap");
		if (curElmnt)
			metaXylem.gapCytoTono = atof(curElmnt->GetText());
		metaXylem.gapCellWall = metaXylem.cellWallWidth + metaXylem.plasmaMembraneThickness;
		metaXylem.variationRatio = atof(metaXylemInput->Attribute("variationRatio"));
		curElmnt = metaXylemInput->FirstChildElement("VerticalLengthThresholdRatio");
		if (curElmnt)
			metaXylem.verticalLengthThresholdRatio = atof(curElmnt->GetText());
		curElmnt = metaXylemInput->FirstChildElement("TangentRingRadiusRatio");
		if (curElmnt)
			metaXylem.tangentRingRadiusRatio = atof(curElmnt->GetText());
		curElmnt = metaXylemInput->FirstChildElement("SteleCellNumBetween");
		if (curElmnt)
			metaXylem.steleCellNumBetween = atof(curElmnt->GetText());
		curElmnt = metaXylemInput->FirstChildElement("MXNum");
		if (curElmnt)
			metaXylem.num = atof(curElmnt->GetText());
		curElmnt = metaXylemInput->FirstChildElement("MXAverageRingRadius");
		if (curElmnt)
			metaXylem.averageRingRadius = atof(curElmnt->GetText());
		curElmnt = metaXylemInput->FirstChildElement("MXMaxRingRadius");
		if (curElmnt)
			metaXylem.maxRingRadius = atof(curElmnt->GetText());
		curElmnt = metaXylemInput->FirstChildElement("SurroundingCellRingNum");
		if (curElmnt)
			metaXylem.surroundingCellRingNum = atof(curElmnt->GetText());
		curElmnt = metaXylemInput->FirstChildElement("BoundaryDotNum");
		if (curElmnt)
			metaXylem.dotNum = atof(curElmnt->GetText());
		curElmnt = metaXylemInput->FirstChildElement("BoundaryUpRowNum");
		if (curElmnt)
			metaXylem.setUpRowNum = atof(curElmnt->GetText());
		curElmnt = metaXylemInput->FirstChildElement("BoundaryDownRowNum");
		if (curElmnt)
			metaXylem.setDownRowNum = atof(curElmnt->GetText());
		if (globals::type_dicot)
		{
			curElmnt = metaXylemInput->FirstChildElement("MXRings");
			if (curElmnt)
				metaXylem.numFiles = atof(curElmnt->GetText());
			curElmnt = metaXylemInput->FirstChildElement("MXNumEachRing");
			if (curElmnt)
			{
				string numFilesInput = curElmnt->GetText();
				while ((pos = numFilesInput.find(delimiter)) != std::string::npos)
				{
					double temp = stof(numFilesInput.substr(0, pos));
					metaXylem.eachRingNum.push_back(temp);
					numFilesInput.erase(0, pos + delimiter.length());
				}
				metaXylem.eachRingNum.push_back(stof(numFilesInput));
				pos = 0;
			}
		}
		else
		{
			metaXylem.numFiles = 1;
			metaXylem.eachRingNum.push_back(metaXylem.num);
		}
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

	//********** PHLOEM DATA ****************//
	TiXmlElement* phloemInput = main->FirstChildElement("Phloem");
	if (phloemInput) {
		phloem.setUpAppendParallelLengthThresholdRatio = atof(phloemInput->FirstChildElement("ParallelThresholdRatio")->GetText());
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
		//epidermis.cellDiameter = atof(epidermisInput->FirstChildElement("CellDiameter")->GetText());
		string cellDiameterInput = epidermisInput->FirstChildElement("CellDiameter")->GetText();
		while ((pos = cellDiameterInput.find(delimiter)) != std::string::npos) {
			epidermis.cellDiameter.push_back(stof(cellDiameterInput.substr(0, pos)));
			cellDiameterInput.erase(0, pos + delimiter.length());
		}
		epidermis.cellDiameter.push_back(stof(cellDiameterInput));
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
		//endodermis.cellDiameter = atof(endodermisInput->FirstChildElement("CellDiameter")->GetText());
		string cellDiameterInput = endodermisInput->FirstChildElement("CellDiameter")->GetText();
		while ((pos = cellDiameterInput.find(delimiter)) != std::string::npos) {
			endodermis.cellDiameter.push_back(stof(cellDiameterInput.substr(0, pos)));
			cellDiameterInput.erase(0, pos + delimiter.length());
		}
		endodermis.cellDiameter.push_back(stof(cellDiameterInput));
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
		//exodermis.cellDiameter = atof(exodermisInput->FirstChildElement("CellDiameter")->GetText());
		string cellDiameterInput = exodermisInput->FirstChildElement("CellDiameter")->GetText();
		while ((pos = cellDiameterInput.find(delimiter)) != std::string::npos) {
			exodermis.cellDiameter.push_back(stof(cellDiameterInput.substr(0, pos)));
			cellDiameterInput.erase(0, pos + delimiter.length());
		}
		exodermis.cellDiameter.push_back(stof(cellDiameterInput));
	}
	else {
		cout << "exodermis Parameters Missing." << endl;
	}

	//********** SCLERENCHYMA DATA *************//
	TiXmlElement* sclerenchymaInput = main->FirstChildElement("Sclerenchyma");
	if (sclerenchymaInput) {
		if (sclerenchymaInput->FirstChildElement("NumFiles"))
			sclerenchyma.numFiles = atoi(sclerenchymaInput->FirstChildElement("NumFiles")->GetText());
		else
			sclerenchyma.numFiles = 1;
		sclerenchyma.minSlice = atoi(sclerenchymaInput->FirstChildElement("Slices")->Attribute("min"));
		sclerenchyma.maxSlice = atoi(sclerenchymaInput->FirstChildElement("Slices")->Attribute("max"));
		sclerenchyma.cellWallWidth = atof(sclerenchymaInput->FirstChildElement("CellwallWidth")->GetText());
		sclerenchyma.plasmaMembraneThickness = atof(sclerenchymaInput->FirstChildElement("PlasmaMembraneWidth")->GetText());
		sclerenchyma.gapCytoTono = atof(sclerenchymaInput->FirstChildElement("InnerPlasmaMembraneTonoplastGap")->GetText());
		sclerenchyma.gapCellWall = sclerenchyma.cellWallWidth + sclerenchyma.plasmaMembraneThickness;
		sclerenchyma.variationRatio = atof(sclerenchymaInput->Attribute("variationRatio"));
		//sclerenchyma.cellDiameter = atof(sclerenchymaInput->FirstChildElement("CellDiameter")->GetText());
		string cellDiameterInput = sclerenchymaInput->FirstChildElement("CellDiameter")->GetText();
		while ((pos = cellDiameterInput.find(delimiter)) != std::string::npos) {
			sclerenchyma.cellDiameter.push_back(stof(cellDiameterInput.substr(0, pos)));
			cellDiameterInput.erase(0, pos + delimiter.length());
		}
		sclerenchyma.cellDiameter.push_back(stof(cellDiameterInput));
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
		//pericycle.cellDiameter = atof(pericycleInput->FirstChildElement("CellDiameter")->GetText());
		string cellDiameterInput = pericycleInput->FirstChildElement("CellDiameter")->GetText();
		while ((pos = cellDiameterInput.find(delimiter)) != std::string::npos) {
			pericycle.cellDiameter.push_back(stof(cellDiameterInput.substr(0, pos)));
			cellDiameterInput.erase(0, pos + delimiter.length());
		}
		pericycle.cellDiameter.push_back(stof(cellDiameterInput));
	}
	else {
		cout << "pericycle Parameters Missing." << endl;
	}

	TiXmlDocument fluxDoc("fluxInput.xml");
	fluxDoc.LoadFile();
	if (!fluxDoc.Error()) {
		TiXmlElement* fluxMain = fluxDoc.FirstChildElement("Main");
		//*********** FLUX CALC DATA **********//
		TiXmlElement* fluxInput = fluxMain->FirstChildElement("FluxInput");
		if (fluxInput) {
			surfaceFlux.hydraulicConductance = atof(fluxInput->FirstChildElement("hydraulicConductance")->GetText());
			surfaceFlux.reflectionCoeffecient = atof(fluxInput->FirstChildElement("reflectionCoeffecient")->GetText());
			surfaceFlux.waterPressureDiff = atof(fluxInput->FirstChildElement("waterPressureDiff")->GetText());
			surfaceFlux.osmoticPressureDiff = atof(fluxInput->FirstChildElement("osmoticPressureDiff")->GetText());
			surfaceFlux.radialConductivity = atof(fluxInput->FirstChildElement("radialConductivity")->GetText());
			surfaceFlux.pressurePotentialSurface = atof(fluxInput->FirstChildElement("pressurePotentialSurface")->GetText());
			surfaceFlux.pressurePotentialXylem = atof(fluxInput->FirstChildElement("pressurePotentialXylem")->GetText());
			surfaceFlux.effectiveReflectionCoefficient = atof(fluxInput->FirstChildElement("effectiveReflectionCoefficient")->GetText());
			surfaceFlux.osmoticPotentialSurface = atof(fluxInput->FirstChildElement("osmoticPotentialSurface")->GetText());
			surfaceFlux.osmoticPotentialXylem = atof(fluxInput->FirstChildElement("osmoticPotentialXylem")->GetText());
		}

		//*********** Nutrient DATA *******//
		for (TiXmlElement* nutrInput = fluxMain->FirstChildElement("Nutrient"); nutrInput != NULL; nutrInput = nutrInput->NextSiblingElement()) {
			globals nutrientInfo;
			nutrientInfo.nutriName = nutrInput->Attribute("name");
			if (nutrInput->Attribute("startTime")) {
				nutrientInfo.simTimes.push_back(atof(nutrInput->Attribute("startTime")));
				if (nutrInput->Attribute("endTime"))
					nutrientInfo.simTimes.push_back(atof(nutrInput->Attribute("endTime")));
				if (nutrInput->Attribute("timestep"))
					nutrientInfo.simTimes.push_back(atof(nutrInput->Attribute("timestep")));
			}
			else {
				nutrientInfo.simTimes.push_back(0.0);
				nutrientInfo.simTimes.push_back(10.0);
				nutrientInfo.simTimes.push_back(1);
			}
			nutrientInfo.V_max = atof(nutrInput->FirstChildElement("V_max")->GetText());
			nutrientInfo.k_m = atof(nutrInput->FirstChildElement("k_m")->GetText());
			nutrientInfo.surfaceConcentration = atof(nutrInput->FirstChildElement("surfaceConcentration")->GetText());
			string initConcInput = nutrInput->FirstChildElement("initialConcentration")->GetText();
			while ((pos = initConcInput.find(delimiter)) != std::string::npos) {
				nutrientInfo.initialConcentration.push_back(stof(initConcInput.substr(0, pos)));
				initConcInput.erase(0, pos + delimiter.length());
			}
			nutrientInfo.initialConcentration.push_back(stof(initConcInput));
			nutrientInfo.surface_epi_permeability = atof(nutrInput->FirstChildElement("outer_permeability")->GetText());
			nutrientInfo.permeability = atof(nutrInput->FirstChildElement("cell_permeability")->GetText());
			nutrientInfo.utilisation = atof(nutrInput->FirstChildElement("utilisation")->GetText());
			nutrientInfo.plasmodesmaRadius = atof(nutrInput->FirstChildElement("plasmodesmaRadius")->GetText());
			nutrientInfo.plasmodesmaFrequency = atoi(nutrInput->FirstChildElement("plasmodesmaFrequency")->GetText());
			nutrients.push_back(nutrientInfo);
		}
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
	
	string baseRadiusUpDir = outputFolderName;

	for (double baseRadiusCur : baseRadiusVals) {
		
		int numCells = int((2 * M_PI * baseRadiusCur) / (cortical.cellDiameter[0]));
		globals::baseRadius = numCells * cortical.cellDiameter[0] / (2 * M_PI);
		outputFolderName[0] = '\0';
		strcpy(outputFolderName, baseRadiusUpDir.c_str());
		string baseRadiusFolderName = "/BaseRadius_" + std::to_string(globals::baseRadius);
		strcat(outputFolderName, baseRadiusFolderName.c_str());
		fs::create_directories(outputFolderName);
		globals::setFolderName(outputFolderName);
		string CCFNUpDir = outputFolderName;

		for (int numFilesCur : numFilesVals) {

			cortical.numFiles = numFilesCur;
			outputFolderName[0] = '\0';
			strcpy(outputFolderName, CCFNUpDir.c_str());
			string ccfnFolderName = "/CCFN_" + std::to_string(numFilesCur);
			strcat(outputFolderName, ccfnFolderName.c_str());
			fs::create_directories(outputFolderName);
			globals::setFolderName(outputFolderName);
			string rcaUpDir = outputFolderName;
			
			for (double rcaRatioCur : rcaRatioVals) {
				globals::rcaRatio = rcaRatioCur;
				outputFolderName[0] = '\0';
				strcpy(outputFolderName, rcaUpDir.c_str());
				string rcaFolderName = "/RCA_" + std::to_string(globals::rcaRatio);
				strcat(outputFolderName, rcaFolderName.c_str());
				fs::create_directories(outputFolderName);
				globals::setFolderName(outputFolderName);

				/////////////////////////////////////// Cortex ////////////////////////////////
				rsDynamicDataOutput* RsDynamicDataOutput = new rsDynamicDataOutput;

				/// Cortical;
				int corticalSliceNum = cortical.minSlice + (rand() % (cortical.maxSlice - cortical.minSlice + 1));

				/*Stele parameters*/
				double steleInnestCellRadiusInput = stele.innestCellDiameter;

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
				corticalInnermostCellDiameterSS << cortical.cellDiameter[0] / 2;
				corticalInnermostCellDiameterSS >> corticalInnermostCellDiameterString;

				/// rca2CortexRatio to string;
				string rca2CortexRatioName = "RCA2CortexRatio";
				stringstream rca2CortexRatioSS;
				string rca2CortexRatioString;
				rca2CortexRatioSS << globals::rcaRatio;
				rca2CortexRatioSS >> rca2CortexRatioString;

				/// totalheight to string ** Jagdeep 12-2-2020
				string TotalHeightName = "TotalHeight";
				stringstream TotalHeightSS;
				string TotalHeightString;
				TotalHeightSS << globals::totalHeight;
				TotalHeightSS >> TotalHeightString;

				string blankSpace = " ";

				char* prefix;
				strftime(prefix, 40, folderFormat, startTime);

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
				if (globals::rcaRatio <= 0.05)
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
				double sclerenAddRadiusData = sclerenchyma.cellDiameter[0];

				/// Scleren Output filename;
				string prefixScleren = "Sclerenchyma";
				string tempScleren = filePrefix + prefixScleren + prefix + suffix;
				const char* SclerenXMLVtpFileNameInput = tempScleren.c_str();

				/// Epidermis;
				int epidermisSliceNum = epidermis.minSlice + (rand() % (epidermis.maxSlice - epidermis.minSlice + 1));
				double epidermisAddRadiusData = epidermis.cellDiameter[0];
				double variationRatioDermis = epidermis.variationRatio;

				/// Epi Output filename;
				string prefixEpidermis = "Epidermis";
				string tempEpidermis = filePrefix + prefixEpidermis + prefix + suffix;
				const char* EpidermisXMLVtpFileNameInput = tempEpidermis.c_str();

				/// Endodermis;
				int endodermisSliceNum = endodermis.minSlice + (rand() % (endodermis.maxSlice - endodermis.minSlice + 1));
				double endodermisAddRadiusData = endodermis.cellDiameter[0];

				/// Endo Output filename;
				string prefixEndodermis = "Endodermis";
				string tempEndodermis = filePrefix + prefixEndodermis + prefix + suffix;
				const char* EndodermisXMLVtpFileNameInput = tempEndodermis.c_str();

				/// Pericycle
				int pericycleSliceNum = pericycle.minSlice + (rand() % (pericycle.maxSlice - pericycle.minSlice + 1));
				double pericycleAddRadiusData = pericycle.cellDiameter[0];

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
				if (globals::rcaRatio == 0)
				{
					RsDynamicDataOutput->InitEpiCortexEndoNonRCADB
					(
						/// All objects;
						cortical,
						stele,
						metaXylem,
						protoXylem,
						phloem,
						epidermis,
						endodermis,
						exodermis,
						sclerenchyma,
						pericycle,
						surfaceFlux,
						nutrients,

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
						phloem,
						epidermis,
						endodermis,
						exodermis,
						sclerenchyma,
						pericycle,
						surfaceFlux,
						nutrients,

						/// Cortical;
						corticalAddRadiusInputData,
						corticalCellNumInputData,
						corticalSliceNum,

						/// RCA;
						globals::rcaRatio,
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
				string pvdFileName = "allVTP_RCA " + to_string(globals::rcaRatio) + ".pvd";
				globals::writePVDFile(pvdFileName);
				globals::resetFileNameList();
			}
		}
	}
	return 0;
}