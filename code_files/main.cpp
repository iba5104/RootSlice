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
	TiXmlElement* plantNum = doc.FirstChildElement("Main")
		->FirstChildElement("Plant")
		->FirstChildElement("PlantNum");
	/// if we want to see the condition of the exact slice, we just need to change the data following;
	string Num = "1";
	string rootRank1Num = "3";
	string rootRank2Num = "20";
	string LengthToBase2 = "9";
	string rootRank3Num = "40";
	string LengthToBase3 = "6";
	//map<int, double> corticalAddRadiusInputData;
	vector<double> corticalAddRadiusInputData;
	// map<int, double>::iterator corticalAddRadiusInputData_it;

	  //map<int, double> corticalCellNumInputData;
	vector<int> corticalCellNumInputData;
	// map<int, double>::iterator corticalCellNumInputData_it;

	double baseRadius;
	double thickness;
	/// PlantNum validation
	while (plantNum)
	{
		if (plantNum->GetText() == Num)
		{
			TiXmlElement* rootRank1 = plantNum->FirstChildElement("NodeRank")
				->FirstChildElement("RootRank1");
			/// rootRank1 validation
			while (rootRank1)
			{

				if (rootRank1->FirstAttribute()->Value() == rootRank1Num)
				{  /// rootRank2 validation: root is marked by rank and position;
					TiXmlElement* rootRank2 = rootRank1->FirstChildElement("RootRank2");
					while (rootRank2)
					{

						if (rootRank2->FirstAttribute()->Value() == rootRank2Num &&
							rootRank2->FirstChildElement("LengthToBase2")->GetText() == LengthToBase2)
						{  /// rootRank3 validation: root is marked by rank and position;
							TiXmlElement* rootRank3 = rootRank2->FirstChildElement("RootRank3");
							while (rootRank3)
							{

								if (rootRank3->FirstAttribute()->Value() == rootRank3Num &&
									rootRank3->FirstChildElement("LengthToBase3")->GetText() == LengthToBase3)
								{  /// slice
									TiXmlElement* slice = rootRank3->FirstChildElement("Slice");
									cout << "BaseRadius: " << slice->FirstChildElement("BaseRadius")->GetText() << endl;
									cout << "Thickness: " << slice->FirstChildElement("Thickness")->GetText() << endl;

									// Public data of slice;
									baseRadius = atof(slice->FirstChildElement("BaseRadius")->GetText());
									thickness = atof(slice->FirstChildElement("Thickness")->GetText());
									// Get the data of cortical;
									TiXmlElement* layer = slice->FirstChildElement("Cortical");

									while (layer)
									{
										corticalAddRadiusInputData.push_back
										(atof(layer->FirstChildElement("AddRadius")->GetText()));
										corticalCellNumInputData.push_back
										(atof(layer->FirstChildElement("CellNumber")->GetText()));
										cout << "RingNum: " << layer->FirstChildElement("RingNum")->GetText() << endl;
										cout << "CellNumber: " << layer->FirstChildElement("CellNumber")->GetText() << endl;
										layer = layer->NextSiblingElement();
									}

									/// slice end
								}
								rootRank3 = rootRank3->NextSiblingElement();
							}
							/// rootRank3 validation end
						}
						rootRank2 = rootRank2->NextSiblingElement();
					}
					/// rootRank2 validation end
				}
				rootRank1 = rootRank1->NextSiblingElement();
			}
			/// rootRank1 validation end
		}
		plantNum = plantNum->NextSiblingElement();
	}
	/// PlantNum validation end
	//doc.SaveFile("Iamhere.txt");

	//////////////////////////////////////// Visualization //////////////////////////////////////////////

	   /// we visualize in the same renderer - Keep static;
	vtkSmartPointer<vtkRenderer> renL = vtkSmartPointer<vtkRenderer>::New();




	/////////////////////////////////////// Dynamic Output /////////////////////////////////////////

	double corticalCellAddRadiusMinInput;
	double rcaRatioInput;
	double gapCytoTonoInput;
	double gapCellWallInput;
	double totalHeight;
	double PM_thick; // too change this go to rsDataOutput.cpp line 155.
	int cortexLayerNum;

	int rcaRatioInt;
	double gapCytoTonoInputInt;
	double gapCellWallInputInt;
	double baseRadiusInt;



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


	for (baseRadiusInt = 2; baseRadiusInt <= 2; baseRadiusInt++)
	{
		baseRadius = 100 * baseRadiusInt;

		for (rcaRatioInt = 0; rcaRatioInt <= 2; rcaRatioInt++)
		{
			rcaRatioInput = 0.1 * rcaRatioInt;

			for (corticalCellAddRadiusMinInput = 10; corticalCellAddRadiusMinInput <= 20; corticalCellAddRadiusMinInput += 5)
				//corticalCellAddRadiusMinInput = 0;
			{
				for (gapCellWallInputInt = 1.0; gapCellWallInputInt <= 1.0; gapCellWallInputInt++)
				{
					gapCellWallInput = gapCellWallInputInt * 0.5;

					for (gapCytoTonoInputInt = 1; gapCytoTonoInputInt <= 1; gapCytoTonoInputInt++)
					{
						gapCytoTonoInput = 0.2 * gapCytoTonoInputInt;

						for (cortexLayerNum = 8; cortexLayerNum <= 8; cortexLayerNum = cortexLayerNum + 4)

							// Why is totalHeight being varied? Should be constant for a simulation ~ Sankalp
													   //for (totalHeight = 75; totalHeight <= 300; totalHeight = totalHeight + 75)
													   //{


														   //   for ( rcaRatioInt = 12; rcaRatioInt != 13; rcaRatioInt++ )
														   //   {  rcaRatioInput = 0.05 * rcaRatioInt;
														   //      for ( corticalCellAddRadiusMinInput = 15; corticalCellAddRadiusMinInput != 16; corticalCellAddRadiusMinInput++ )
														   //      {  for ( gapCytoTonoInput = 1; gapCytoTonoInput != 2; gapCytoTonoInput++ )
														   //         {  for ( cortexLayerNum = 7; cortexLayerNum != 8; cortexLayerNum ++ )
						{  /////////////////////////////////////// Cortex ////////////////////////////////
							rsDynamicDataOutput* RsDynamicDataOutput = new rsDynamicDataOutput;
							int setUResolution = 12;
							int setVResolution = 12;
							int setWResolution = 12;

							int corticalAddRadiusDBSelectInput = 1;
							int corticalCellNumSelectInput = 1;

							/// Cortical;
							double totalHeight = 300;
							int corticalSliceNum = 3;
							double initZPosition = -225;
							int vectorNum = 200;
							double variationRatioCotical = 0.2;
							double corticalCellMultiplyRatio = 0.1;
							double cortexRadiusInput = 0;

							/// gapCellWall;

							  /*Stele parameters*/
							double steleInnestCellRadiusInput = 5;
							int steleInnerLayerNumInput = 5;
							double variationRatio = 0.2;
							int sliceNum = 3;

							/****************Metaxylem parameters******************/
							double setUpVecticalLengthThresholdRatio = 0.3;
							double innerTangentRingRadiusRatioTemp = 0.4;
							int setInterVerticalNum = 2;
							int setMXNum = 5;
							double setMXAverageRingRadius = 10;
							double xylemMaxOutRingNum = 2;

							// protoxylem
							double pxGapRadius = 0.2;
							int setPXNum = 8;
							double setPXAverageRingRadius = 1;
							double xylemMaxOutRingCellNum = 15;
							double xylemMaxOutRingAddRadius = 0.2;
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
							ringNumSS << cortexLayerNum;
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
							string suffix = ".vtp";
							string tempCortical = prefixCortical + prefix + suffix;
							string tempCorticalVacuole = prefixCorticalVacuole + prefix + suffix;
							const char* CorticalXMLVtpFileNameInput = tempCortical.c_str();
							const char* CorticalVacuoleXMLVtpFileNameInput = tempCorticalVacuole.c_str();


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

							//   /// Cortical Vacuole;
							//   double gapCytoTonoInput = 4;

												 /// Epidermis;
							int epidermisSliceNum = 3;
							double epidermisAddRadiusData = 10; //corticalCellAddRadiusMinInput; //size is the defining factor epidermisCellNum is not..1-24-2021
							int epidermisCellNum = 150;
							double variationRatioDermis = 0.2;

							/// Epi Output filename;
							string prefixEpidermis = "Epidermis";
							string tempEpidermis = prefixEpidermis + prefix + suffix;
							const char* EpidermisXMLVtpFileNameInput = tempEpidermis.c_str();

							/// Endodermis;
							int endodermisSliceNum = 3;
							double endodermisAddRadiusData = 10; //corticalCellAddRadiusMinInput / 2; //size is the defining factor endodermisCellNum is not..1-24-2021
							int endodermisCellNum = 150;


							/// Endo Output filename;
							string prefixEndodermis = "Endodermis";
							string tempEndodermis = prefixEndodermis + prefix + suffix;
							const char* EndodermisXMLVtpFileNameInput = tempEndodermis.c_str();



							/// Apoplast and Symplast Output filename;
							string prefixApoplast = "Apoplast";
							string prefixSymplast = "Symplast";
							string tempApoplast = prefixApoplast + prefix + suffix;
							string tempSymplast = prefixSymplast + prefix + suffix;
							const char* ApoplastXMLVtpFileNameInput = tempApoplast.c_str();
							const char* SymplastXMLVtpFileNameInput = tempSymplast.c_str();

							/// DataOutputName
							string prefixDataOutput = "DataOutput";
							string txtSuffix = ".txt";
							string tempDataOutput = prefixDataOutput + prefix + txtSuffix;
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
									variationRatioCotical,
									cortexLayerNum,
									corticalCellMultiplyRatio,
									corticalCellAddRadiusMinInput,
									cortexRadiusInput,

									/// Pure Cortical Cell;
									gapCellWallInput,

									/// Cortical Vacuole;
									gapCytoTonoInput,

									/// Epi;
									epidermisSliceNum,
									epidermisAddRadiusData,
									//                        epidermisCellNum,
									variationRatioDermis,

									/// Endo;
									endodermisSliceNum,
									endodermisAddRadiusData,
									//                        endodermisCellNum,




															   /// OutXMLVtpFileName;
									CorticalXMLVtpFileNameInput,
									CorticalVacuoleXMLVtpFileNameInput,
									EpidermisXMLVtpFileNameInput,
									EndodermisXMLVtpFileNameInput,
									ApoplastXMLVtpFileNameInput,
									SymplastXMLVtpFileNameInput,

									/// DataOutputName;
									dataOutputNameInput,

									/// Others
									renL,
									variationRatio,
									sliceNum,
									steleInnestCellRadiusInput,
									steleInnerLayerNumInput,
									setUpVecticalLengthThresholdRatio,
									innerTangentRingRadiusRatioTemp,
									setInterVerticalNum,
									setMXNum,
									setMXAverageRingRadius,
									xylemMaxOutRingNum,
									pxGapRadius,
									setPXNum,
									setPXAverageRingRadius,
									xylemMaxOutRingCellNum,
									xylemMaxOutRingAddRadius
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
									variationRatioCotical,
									cortexLayerNum,
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

									/// Epi;
									epidermisSliceNum,
									epidermisAddRadiusData,
									//                        epidermisCellNum,
									variationRatioDermis,

									/// Endo;
									endodermisSliceNum,
									endodermisAddRadiusData,
									//                        endodermisCellNum,

															   /// OutXMLVtpFileName;
									CorticalXMLVtpFileNameInput,
									CorticalVacuoleXMLVtpFileNameInput,
									EpidermisXMLVtpFileNameInput,
									EndodermisXMLVtpFileNameInput,
									ApoplastXMLVtpFileNameInput,
									SymplastXMLVtpFileNameInput,

									/// DataOutputName;
									dataOutputNameInput,

									/// Others
									renL
								);

							}


							//delete RsDynamicDataOutput;
							//RsDynamicDataOutput = NULL;

						 //RsDynamicDataOutput->RenderTogether(renL);
						}

						// }
					}
				}
			}
		}

		//RsDynamicDataOutput -> RenderTogether( renL );

		return 0;
	}
}