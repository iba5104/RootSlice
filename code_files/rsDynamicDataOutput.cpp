#define _USE_MATH_DEFINES
#include "rsDynamicDataOutput.h"

void rsDynamicDataOutput::SetRenderer( vtkSmartPointer<vtkRenderer> renL )
{  /// we visualize in the same renderer - Keep static;

   renL -> TwoSidedLightingOn();
   renL -> AutomaticLightCreationOn();
   renL -> LightFollowCameraOn();
}


/////////////////////////////////////////////// EpiCortexEndoAllDB //////////////////////////////////////////////////

void rsDynamicDataOutput::InitEpiCortexEndoAllDB
(
    /// All objects;
    globals cortical,
    globals stele,
    globals metaXylem,
    globals protoXylem,
    globals phloem,
    globals epidermis,
    globals endodermis,
    globals exodermis,
    globals sclerenchyma,
    globals pericycle,
    globals surfaceFlux,
    vector<globals> nutrients,

   /// Cortical;
   vector<double> corticalAddRadiusInputData,
   vector<int> corticalCellNumInputData,
   int corticalSliceNum,
   /// RCA;
   double rcaRatioInput,
   int rcaNumInput,
   int standardOuterLayerInput,
   int standardInnerLayerInput,
   double gapAngleBetweenRcaRatio,
   double variationRatioRca,

   /// Plasma Membrane
   double plasmaMembraneWidth,

    /// Sclerenchyma
    int sclerenSliceNum,
    double sclerenAddRadiusData,

   /// Epi;
   int epidermisSliceNum,
   double epidermisAddRadiusData,

   /// Endo;
   int endodermisSliceNum,
   double endodermisAddRadiusData,

   /// Pericycle
   int pericycleSliceNum,
   double pericycleAddRadiusData,

   /// OutXMLVtpFileName;
   const char* CorticalXMLVtpFileNameInput,
   const char* CorticalVacuoleXMLVtpFileNameInput,
   const char* CorticalPlasmaMembraneVtpFileNameInput,
   const char* SclerenXMLVtpFileNameInput,
   const char* EpidermisXMLVtpFileNameInput,
   const char* EndodermisXMLVtpFileNameInput,
   const char* ApoplastXMLVtpFileNameInput,
   const char* SymplastXMLVtpFileNameInput,
   const char* PericycXMLVtpFileNameInput,

   /// DataOutputName;
   const char* dataOutputNameInput,

    //Other
    vtkSmartPointer<vtkRenderer> renL
)

{  
   /*************************************
   CorticalDB
   **************************************/
   rsSourceCorticalDB *RsSourceCorticalDB = new rsSourceCorticalDB;

   double minRadius = *min_element(cortical.cellDiameter.begin(), cortical.cellDiameter.end())/2.0;

   RsSourceCorticalDB -> RandomHeightDB( totalHeight, corticalSliceNum, initZPosition, vectorNum );
   RsSourceCorticalDB -> InitAllDB ( baseRadius,
                                     cortical.numFiles,
                                     corticalCellMultiplyRatio,
                                     minRadius,
                                     cortexRadiusInput,
                                     corticalAddRadiusDBSelectInput,
                                     corticalAddRadiusInputData,
                                     corticalCellNumInputData,
                                     corticalCellNumSelectInput,
                                     cortical.variationRatio,
                                     corticalSliceNum );

//////////////////////////////////// RCA ////////////////////////////////////

//   cout << "RcaDB" << endl;

   rsRcaDB *RsRcaDB = new rsRcaDB;
   RsRcaDB -> InitRcaDB( rcaRatioInput,
                         rcaNumInput,
                         standardOuterLayerInput,
                         standardInnerLayerInput,
                         baseRadius,
                         RsSourceCorticalDB,
                         variationRatioRca,
                         gapAngleBetweenRcaRatio,
                         totalHeight
                       );
//////////////////////////////////// RCA ///////////////////////////////////////

   /// pure cortical cell;
   RsSourceCorticalDB -> InitPureCellDB( cortical.gapCellWall );
   /// cortical vacuole
//   cout << "CorticalDB - Vacuole" << endl;
   RsSourceCorticalDB -> InitVacuoleDB( cortical.gapCytoTono );
   /////////////////////////////////// Vacuole ///////////////////////////////

   //////////////////////// OutputXMLVtpFileName ///////////////////////////
   RsSourceCorticalDB -> OutputXMLVtpFileName
   ( CorticalXMLVtpFileNameInput,
     CorticalVacuoleXMLVtpFileNameInput,
     CorticalPlasmaMembraneVtpFileNameInput );

//////////////////////////////////// Sclerenchyma  /////////////////////////////////////////

   /*************************************
   SclerenchymaDB
   **************************************/
    double sclerenBaseRadius;
    sclerenBaseRadius = RsSourceCorticalDB->boundaryRadius;

    rsSourceDermisDB* RsSourceSclerenDB = new rsSourceDermisDB;

    RsSourceSclerenDB->SetObjectXYZRadiusRatio(1.1);

    RsSourceSclerenDB->RandomHeightDB(totalHeight, sclerenSliceNum, initZPosition, vectorNum);
    RsSourceSclerenDB->InitAllDB(SclerenXMLVtpFileNameInput,
                                 type_scleren,
                                 sclerenchyma.cellDiameter,
                                 sclerenBaseRadius,
                                 sclerenchyma.variationRatio,
                                 sclerenSliceNum,
                                 sclerenchyma.numFiles);
    RsSourceSclerenDB->SetObjectOpacity();
    RsSourceSclerenDB->InitPureCellDB(sclerenchyma.gapCellWall);
    RsSourceSclerenDB->InitVacuoleDB(sclerenchyma.gapCytoTono);

//////////////////////////////////// Epidermis  /////////////////////////////////////////

   /*************************************
   EpidermisDB
   **************************************/
//   cout << "EpidermisDB" << endl;
   /// boundaryRadius = epidermisBaseRadiusDB;
   double epidermisBaseRadius;
   epidermisBaseRadius = sclerenBaseRadius + (sclerenAddRadiusData * sclerenchyma.numFiles);

   rsSourceDermisDB *RsSourceEpidermisDB = new rsSourceDermisDB;


   RsSourceEpidermisDB->SetObjectXYZRadiusRatio( 1.1 );

   RsSourceEpidermisDB->RandomHeightDB( totalHeight, epidermisSliceNum, initZPosition, vectorNum );
   RsSourceEpidermisDB -> InitAllDB (EpidermisXMLVtpFileNameInput,
                                     type_epi,
                                     epidermis.cellDiameter,
                                     epidermisBaseRadius,
                                     epidermis.variationRatio,
                                     epidermisSliceNum, 1 );

   RsSourceEpidermisDB->SetObjectOpacity();
   RsSourceEpidermisDB->InitPureCellDB(epidermis.gapCellWall);
   RsSourceEpidermisDB->InitVacuoleDB(epidermis.gapCytoTono);

//////////////////////////////////// Endodermis  /////////////////////////////////////////
   /*************************************
   EndodermisDB
   **************************************/
//   cout << "EndodermisDB" << endl;
   /// boundaryRadius = epidermisBaseRadiusDB;
   double endodermisBaseRadius;
   endodermisBaseRadius = baseRadius - endodermisAddRadiusData;

   rsSourceDermisDB *RsSourceEndodermisDB = new rsSourceDermisDB;

   RsSourceEndodermisDB->SetObjectXYZRadiusRatio( 1 );
   RsSourceEndodermisDB->RandomHeightDB( totalHeight, endodermisSliceNum, initZPosition, vectorNum );
   RsSourceEndodermisDB -> InitAllDB (EndodermisXMLVtpFileNameInput,
                                      type_endo,
                                      endodermis.cellDiameter,
                                      endodermisBaseRadius,
                                      endodermis.variationRatio,
                                      endodermisSliceNum, 1 );

   RsSourceEndodermisDB->SetObjectOpacity();
   RsSourceEndodermisDB->InitPureCellDB(endodermis.gapCellWall);
   RsSourceEndodermisDB->InitVacuoleDB(endodermis.gapCytoTono);

////////////////////////////////////////////// Water Path ////////////////////////////////////////////////

// cout << "Water Path" << endl;
   rsEpiCortexEndoWaterPathDB *RsEpiCortexEndoWaterPathDB = new rsEpiCortexEndoWaterPathDB;

   RsEpiCortexEndoWaterPathDB -> OutputXMLVtpFileName
   ( ApoplastXMLVtpFileNameInput,
     SymplastXMLVtpFileNameInput );

   RsEpiCortexEndoWaterPathDB -> InitAllDB
   (RsSourceEpidermisDB,
    RsSourceCorticalDB,
    RsSourceEndodermisDB
   );

   rsEpiCortexEndoWaterPathDBVisual *RsEpiCortexEndoWaterPathDBVisual = new rsEpiCortexEndoWaterPathDBVisual;
   RsEpiCortexEndoWaterPathDBVisual -> ApoplastTubeXMLVtp( RsEpiCortexEndoWaterPathDB );
   RsEpiCortexEndoWaterPathDBVisual -> SymplastTubeXMLVtp( RsEpiCortexEndoWaterPathDB );
   
   RsEpiCortexEndoWaterPathDBVisual -> ApoplastTriangleStripXMLVtp( RsEpiCortexEndoWaterPathDB, surfaceFlux);
   RsEpiCortexEndoWaterPathDBVisual -> SymplastTriangleStripXMLVtp( RsEpiCortexEndoWaterPathDB, surfaceFlux );

 //////////////////////////////////// Pericycle  /////////////////////////////////////////
      /*************************************
      PericycleDB
      **************************************/
   double pericycleBaseRadius;
   pericycleBaseRadius = endodermisBaseRadius - pericycleAddRadiusData;

   rsSourceDermisDB* RsSourcePericycleDB = new rsSourceDermisDB;

   RsSourcePericycleDB->SetObjectXYZRadiusRatio(1);
   RsSourcePericycleDB->RandomHeightDB(totalHeight, pericycleSliceNum, initZPosition, vectorNum);
   RsSourcePericycleDB->InitAllDB(PericycXMLVtpFileNameInput,
                                  type_peri,
                                  pericycle.cellDiameter,
                                  pericycleBaseRadius,
                                  pericycle.variationRatio,
                                  pericycleSliceNum, 1);

   RsSourcePericycleDB->SetObjectOpacity();
   RsSourcePericycleDB->InitPureCellDB(pericycle.gapCellWall);
   RsSourcePericycleDB->InitVacuoleDB(pericycle.gapCytoTono);

   rsPXCoreDB* RsPXCoreDB = new rsPXCoreDB;
   rsMXBoundaryOutDB* RSMXBoundaryOutDB = new rsMXBoundaryOutDB;
   rsSteleInnerDB* RsSteleInnerDB = new rsSteleInnerDB;
   rsPXBoundaryDB* RsPXBoundaryDB = new rsPXBoundaryDB;
   rsPhloemDB* RsPhloemDB = new rsPhloemDB;

   InitInnertructure(stele, metaXylem, protoXylem, phloem, pericycleBaseRadius, renL, 
       RsPXCoreDB, RSMXBoundaryOutDB, RsSteleInnerDB, RsPXBoundaryDB, RsPhloemDB);

   //////////////////////////////////////// Visualization //////////////////////////////////////////////
   string timePrefix = "";
   vector<double> result_cortical;
   vector<double> result_epi;
   vector<double> result_endo;
   vector<double> result_scleren;
   vector<double> result_peri;
   /************************************
       Epidermis
       *************************************/

   RsSourceEpidermisDB->RGBTime(2);
   RsSourceEpidermisDB->RGBStart(4);

   rsSourceDermisVisual* RsSourceEpidermisVisual = new rsSourceDermisVisual;
   RsSourceEpidermisVisual->EpidermisVisual(RsSourceEpidermisDB, renL, 0, result_epi, timePrefix);
   RsSourceEpidermisVisual->EpidermisVisual(RsSourceEpidermisDB, renL, 1, result_epi, timePrefix);
   RsSourceEpidermisVisual->EpidermisVisual(RsSourceEpidermisDB, renL, 2, result_epi, timePrefix);
   //   // delete Viusal;
   //   delete RsSourceEpidermisVisual;


   /************************************
   Sclerenchyma
   *************************************/
   RsSourceSclerenDB->RGBTime(2);
   RsSourceSclerenDB->RGBStart(4);

   rsSourceDermisVisual* RsSourceSclerenVisual = new rsSourceDermisVisual;
   RsSourceSclerenVisual->EpidermisVisual(RsSourceSclerenDB, renL, 0, result_scleren, timePrefix);
   RsSourceSclerenVisual->EpidermisVisual(RsSourceSclerenDB, renL, 1, result_scleren, timePrefix);
   RsSourceSclerenVisual->EpidermisVisual(RsSourceSclerenDB, renL, 2, result_scleren, timePrefix);

   /*************************************
   Cortical
   **************************************/
   RsSourceCorticalDB->RGBTime(6);
   RsSourceCorticalDB->RGBStart(2);
   ///
   rsSourceCorticalVisual* RsSourceCorticalVisual = new rsSourceCorticalVisual;

   //   /// Cortical vacuole;
   cout << "CorticalDB - VacuoleVisual" << endl;
   RsSourceCorticalVisual->VacuoleVisual(RsSourceCorticalDB, renL, result_cortical, timePrefix);

   cout << "CorticalDB - Plasma Membrane Visual" << endl;
   RsSourceCorticalVisual->CorticalPlasmaMembraneVisual(RsSourceCorticalDB, renL, result_cortical, timePrefix);

   //   /// Cortical cell;
   cout << "CorticalDB - CorticalVisual" << endl;
   RsSourceCorticalVisual->CorticalVisual(RsSourceCorticalDB, renL, result_cortical, timePrefix);
   delete RsSourceCorticalVisual;
   cout << "CorticalDB - Finish" << endl;

   /************************************
   Endodermis
   *************************************/
   RsSourceEndodermisDB->RGBTime(2);
   RsSourceEndodermisDB->RGBStart(4);

   rsSourceDermisVisual* RsSourceEndodermisVisual = new rsSourceDermisVisual;
   RsSourceEndodermisVisual->EpidermisVisual(RsSourceEndodermisDB, renL, 0, result_epi, timePrefix);
   RsSourceEndodermisVisual->EpidermisVisual(RsSourceEndodermisDB, renL, 1, result_epi, timePrefix);
   RsSourceEndodermisVisual->EpidermisVisual(RsSourceEndodermisDB, renL, 2, result_epi, timePrefix);
   //   // delete visual;
   //   delete RsSourceEndodermisVisual;
   /************************************
   Pericycle
   *************************************/
   RsSourcePericycleDB->RGBTime(2);
   RsSourcePericycleDB->RGBStart(4);

   rsSourceDermisVisual* RsSourcePericycleVisual = new rsSourceDermisVisual;
   RsSourcePericycleVisual->EpidermisVisual(RsSourcePericycleDB, renL, 0, result_peri, timePrefix);
   RsSourcePericycleVisual->EpidermisVisual(RsSourcePericycleDB, renL, 1, result_peri, timePrefix);
   RsSourcePericycleVisual->EpidermisVisual(RsSourcePericycleDB, renL, 2, result_peri, timePrefix);

   //////////////////////////////////////// DataOutput /////////////////////////////////////////////////
   rsDataOutput* RsDataOutput = new rsDataOutput;
   string outputName = "dataOutput";

   RsDataOutput->DataOutputName(dataOutputNameInput);
   RsDataOutput->CorticalDataOutputCalculate(RsSourceCorticalDB);
   RsDataOutput->DermisDataOutputCalculate(RsSourceEndodermisDB);
   RsDataOutput->DermisDataOutputCalculate(RsSourceEpidermisDB);
   RsDataOutput->DermisDataOutputCalculate(RsSourceSclerenDB);
   RsDataOutput->DermisDataOutputCalculate(RsSourcePericycleDB);
   RsDataOutput->PXDataOutputCalculate(RsPXCoreDB);   
   RsDataOutput->MXBoundaryDataOutputCalculate(RSMXBoundaryOutDB);
   RsDataOutput->SteleDataOutputCalculate(RsSteleInnerDB);
   RsDataOutput->PXBoundaryDataOutputCalculate(RsPXBoundaryDB);
   RsDataOutput->PhloemDataOutputCalculate(RsPhloemDB);
   RsDataOutput->RcaDataOutputCalculate(RsRcaDB);
   RsDataOutput->NutrientAndMitochondriaCalculate();
   RsDataOutput->PathLengthDataOutputCalculate(RsEpiCortexEndoWaterPathDB);
   RsDataOutput->AllDataOutput(baseRadius, totalHeight);

 //////////////////////////////// VISUALISATIONS AND FLUX ////////////////////////////////

   /************************************
   Call fluxEqns on all DBs
   ************************************/
   rsBaseFunctions* RsBaseFunctions = new rsBaseFunctions;
   RsBaseFunctions->CombineAllDBs(RsSourceCorticalDB, 4, RsSourceEpidermisDB, RsSourceSclerenDB, RsSourceEndodermisDB, RsSourcePericycleDB);
   
   /*
   ofstream allcellsout(getfoldername() + "allcells.csv", ios::app);
   allcellsout << "id,type,centerdistance,radius,x,y,neighbour" << endl;
   for (int cntr = 0; cntr < rsbasefunctions->allcells.size(); cntr++) {
       ostringstream nbrs;
       copy(rsbasefunctions->allcells[cntr].neighbours.begin(), rsbasefunctions->allcells[cntr].neighbours.end(), ostream_iterator<int>(nbrs, ","));
       allcellsout << rsbasefunctions->allcells[cntr].id << "," << rsbasefunctions->allcells[cntr].type << 
           "," << rsbasefunctions->allcells[cntr].distancecenter << "," << rsbasefunctions->allcells[cntr].radius << "," <<
           rsbasefunctions->allcells[cntr].x << "," << rsbasefunctions->allcells[cntr].y << "," << nbrs.str() << endl;
   }
   allcellsout.close();
   */

   map<double, vector<double>> result;
   double ringRadius = RsSourceEpidermisDB->circleRadiusDB.back();
   double epiExternalSurfaceArea = (2 * M_PI * ringRadius * RsSourceEpidermisDB->objectHeightDB[0][0][0]) / RsSourceEpidermisDB->EpidermisCellNumCalculated;
   fluxEqns* FluxEqns = new fluxEqns;
   for (int nutriCntr = 0; nutriCntr < nutrients.size(); nutriCntr++) {
       globals curNutrient = nutrients[nutriCntr];
       if (curNutrient.nutriName == "Phosphorous") {
           FluxEqns->cyto_pi(curNutrient, RsBaseFunctions->allCells, epiExternalSurfaceArea, result);
           ofstream phosOut(getFolderName() + "phosphorous.csv", ios::app);
           phosOut << "Time,Concentrations for each cell" << endl;
           for (auto const& pair : result) {
               ostringstream concentrations;
               copy(pair.second.begin(), pair.second.end(), ostream_iterator<double>(concentrations, ","));
               phosOut << pair.first << "," << concentrations.str() << endl;
           }
           phosOut.close();
       }
   }
   for (auto const& pair : result) {
       timePrefix = "time_" + to_string(pair.first);
       result_cortical;
       result_epi;
       result_endo;
       result_scleren;
       result_peri;
       if (pair.second.size() == RsBaseFunctions->allCells.size()) {
           for (int cntr = 0; cntr < pair.second.size(); cntr++) {
               if (RsBaseFunctions->allCells[cntr].type == type_cortical) {
                   result_cortical.push_back(pair.second[cntr]);
               }
               if (RsBaseFunctions->allCells[cntr].type == type_epi) {
                   result_epi.push_back(pair.second[cntr]);
               }
               if (RsBaseFunctions->allCells[cntr].type == type_endo) {
                   result_endo.push_back(pair.second[cntr]);
               }
               if (RsBaseFunctions->allCells[cntr].type == type_peri) {
                   result_peri.push_back(pair.second[cntr]);
               }
               if (RsBaseFunctions->allCells[cntr].type == type_scleren) {
                   result_scleren.push_back(pair.second[cntr]);
               }
           }
       }
       else {
           cout << "flux output length mismatch with number of cells." << endl;
       }
       /************************************
       Epidermis
       *************************************/

       RsSourceEpidermisDB->RGBTime(2);
       RsSourceEpidermisDB->RGBStart(4);

       rsSourceDermisVisual* RsSourceEpidermisVisual = new rsSourceDermisVisual;
       RsSourceEpidermisVisual->EpidermisVisual(RsSourceEpidermisDB, renL, 0, result_epi, timePrefix);
       RsSourceEpidermisVisual->EpidermisVisual(RsSourceEpidermisDB, renL, 1, result_epi, timePrefix);
       RsSourceEpidermisVisual->EpidermisVisual(RsSourceEpidermisDB, renL, 2, result_epi, timePrefix);
       //   // delete Viusal;
       //   delete RsSourceEpidermisVisual;


       /************************************
       Sclerenchyma
       *************************************/
       RsSourceSclerenDB->RGBTime(2);
       RsSourceSclerenDB->RGBStart(4);

       rsSourceDermisVisual* RsSourceSclerenVisual = new rsSourceDermisVisual;
       RsSourceSclerenVisual->EpidermisVisual(RsSourceSclerenDB, renL, 0, result_scleren, timePrefix);
       RsSourceSclerenVisual->EpidermisVisual(RsSourceSclerenDB, renL, 1, result_scleren, timePrefix);
       RsSourceSclerenVisual->EpidermisVisual(RsSourceSclerenDB, renL, 2, result_scleren, timePrefix);

       /*************************************
       Cortical
       **************************************/
       RsSourceCorticalDB->RGBTime(6);
       RsSourceCorticalDB->RGBStart(2);
       ///
       rsSourceCorticalVisual* RsSourceCorticalVisual = new rsSourceCorticalVisual;

       //   /// Cortical vacuole;
       cout << "CorticalDB - VacuoleVisual" << endl;
       RsSourceCorticalVisual->VacuoleVisual(RsSourceCorticalDB, renL, result_cortical, timePrefix);

       cout << "CorticalDB - Plasma Membrane Visual" << endl;
       RsSourceCorticalVisual->CorticalPlasmaMembraneVisual(RsSourceCorticalDB, renL, result_cortical, timePrefix);

       //   /// Cortical cell;
       cout << "CorticalDB - CorticalVisual" << endl;
       RsSourceCorticalVisual->CorticalVisual(RsSourceCorticalDB, renL, result_cortical, timePrefix);
       delete RsSourceCorticalVisual;
       cout << "CorticalDB - Finish" << endl;

       /************************************
       Endodermis
       *************************************/
       RsSourceEndodermisDB->RGBTime(2);
       RsSourceEndodermisDB->RGBStart(4);

       rsSourceDermisVisual* RsSourceEndodermisVisual = new rsSourceDermisVisual;
       RsSourceEndodermisVisual->EpidermisVisual(RsSourceEndodermisDB, renL, 0, result_epi, timePrefix);
       RsSourceEndodermisVisual->EpidermisVisual(RsSourceEndodermisDB, renL, 1, result_epi, timePrefix);
       RsSourceEndodermisVisual->EpidermisVisual(RsSourceEndodermisDB, renL, 2, result_epi, timePrefix);
       //   // delete visual;
       //   delete RsSourceEndodermisVisual;
       /************************************
       Pericycle
       *************************************/
       RsSourcePericycleDB->RGBTime(2);
       RsSourcePericycleDB->RGBStart(4);

       rsSourceDermisVisual* RsSourcePericycleVisual = new rsSourceDermisVisual;
       RsSourcePericycleVisual->EpidermisVisual(RsSourcePericycleDB, renL, 0, result_peri, timePrefix);
       RsSourcePericycleVisual->EpidermisVisual(RsSourcePericycleDB, renL, 1, result_peri, timePrefix);
       RsSourcePericycleVisual->EpidermisVisual(RsSourcePericycleDB, renL, 2, result_peri, timePrefix);
   }

/// Delete Database;
   delete RsSourceCorticalDB;
   RsSourceCorticalDB = NULL;

   delete RsSourceEpidermisDB;
   RsSourceEpidermisDB = NULL;

   delete RsSourceEndodermisDB;
   RsSourceEndodermisDB = NULL;

   delete RsSourcePericycleDB;
   RsSourcePericycleDB = NULL;

   delete RsRcaDB;
   RsRcaDB = NULL;

   delete RsEpiCortexEndoWaterPathDB;
   RsEpiCortexEndoWaterPathDB = NULL;

   delete RsDataOutput;
   RsDataOutput = NULL;
}


/// InitEpiCortexEndoNonRCADB;
void rsDynamicDataOutput::InitEpiCortexEndoNonRCADB
(
   /// All objects;
   globals cortical,
   globals stele,
   globals metaXylem,
   globals protoXylem,
   globals phloem,
   globals epidermis,
   globals endodermis,
   globals exodermis,
   globals sclerenchyma,
   globals pericycle,
   globals surfaceFlux, 
   vector<globals> nutrients,

   /// Cortical specific;
   vector<double> corticalAddRadiusInputData,

   vector<int> corticalCellNumInputData,

   
   int corticalSliceNum,

   /// Sclerenchyma
   int sclerenSliceNum,


   double sclerenAddRadiusData,

   /// Epi;
   int epidermisSliceNum,


   double epidermisAddRadiusData,

   /// Endo;
   int endodermisSliceNum,
   double endodermisAddRadiusData,

    //   int endodermisCellNum,

    /// Pericycle
    int pericycleSliceNum,


   double pericycleAddRadiusData,

   /// OutXMLVtpFileName;
   const char* CorticalXMLVtpFileNameInput,

   const char* CorticalVacuoleXMLVtpFileNameInput,

   const char* CorticalPlasmaMembraneVtpFileNameInput,

   const char* SclerenXMLVtpFileNameInput,

   const char* EpidermisXMLVtpFileNameInput,

   const char* EndodermisXMLVtpFileNameInput,

   const char* ApoplastXMLVtpFileNameInput,

   const char* SymplastXMLVtpFileNameInput,


   const char* PericycXMLVtpFileNameInput,

    /// DataOutputName;
   const char* dataOutputNameInput, //Other
    vtkSmartPointer<vtkRenderer> renL
)

{  
   /*************************************
   CorticalDB
   **************************************/
   rsSourceCorticalDB *RsSourceCorticalDB = new rsSourceCorticalDB;

   double minRadius = *min_element(cortical.cellDiameter.begin(), cortical.cellDiameter.end()) / 2.0;

   RsSourceCorticalDB -> RandomHeightDB( totalHeight, corticalSliceNum, initZPosition, vectorNum );
   RsSourceCorticalDB -> InitAllDB ( baseRadius,
                                     cortical.numFiles,
                                     corticalCellMultiplyRatio,
                                     minRadius,
                                     cortexRadiusInput,
                                     corticalAddRadiusDBSelectInput,
                                     corticalAddRadiusInputData,
                                     corticalCellNumInputData,
                                     corticalCellNumSelectInput,
                                     cortical.variationRatio,
                                     corticalSliceNum );

      /// pure cortical cell - plasma membrane ?;
   RsSourceCorticalDB -> InitPureCellDB( cortical.gapCellWall );
   /// cortical vacuole
//   cout << "CorticalDB - Vacuole" << endl;
   RsSourceCorticalDB -> InitVacuoleDB( cortical.gapCytoTono );
   /////////////////////////////////// Vacuole ///////////////////////////////

   //////////////////////// OutputXMLVtpFileName ///////////////////////////
   RsSourceCorticalDB -> OutputXMLVtpFileName
   ( CorticalXMLVtpFileNameInput,
     CorticalVacuoleXMLVtpFileNameInput,
     CorticalPlasmaMembraneVtpFileNameInput );

   vector<double> result;
   string timePrefix = "time_";
   /*************************************
   Cortical visualization
   **************************************/
   RsSourceCorticalDB->RGBTime( 6 );
   RsSourceCorticalDB->RGBStart( 2 );
   ///
   rsSourceCorticalVisual *RsSourceCorticalVisual = new rsSourceCorticalVisual;
   RsSourceCorticalDB->SetObjectOpacity( 0.8 );



//   /// Cortical vacuole;
cout << "CorticalDB - VacuoleVisual" << endl;
RsSourceCorticalVisual -> VacuoleVisual( RsSourceCorticalDB, renL, result, timePrefix);

cout << "CorticalDB - Plasma Membrane Visual" << endl;
RsSourceCorticalVisual->CorticalPlasmaMembraneVisual(RsSourceCorticalDB, renL, result, timePrefix);

   /// Cortical cell;
cout << "CorticalDB - CorticalVisual" << endl;
RsSourceCorticalVisual -> CorticalVisual( RsSourceCorticalDB, renL, result, timePrefix);
//   delete RsSourceCorticalVisual;
//   cout << "CorticalDB - Finish" << endl;

//////////////////////////////////// Sclerenchyma  /////////////////////////////////////////

   /*************************************
   SclerenchymaDB
   **************************************/
   double sclerenBaseRadius;
   sclerenBaseRadius = RsSourceCorticalDB->boundaryRadius;
   
   rsSourceDermisDB* RsSourceSclerenDB = new rsSourceDermisDB;
   
   RsSourceSclerenDB->SetObjectXYZRadiusRatio(1.1);
   
   RsSourceSclerenDB->RandomHeightDB(totalHeight, sclerenSliceNum, initZPosition, vectorNum);
   //for (int fileCount = 0; fileCount < sclerenchyma.numFiles; fileCount++) {
       //sclerenBaseRadius += sclerenAddRadiusData * fileCount;
       RsSourceSclerenDB->InitAllDB(SclerenXMLVtpFileNameInput,
           type_scleren,
           sclerenchyma.cellDiameter,
           sclerenBaseRadius,
           sclerenchyma.variationRatio,
           sclerenSliceNum, 1 );
       RsSourceSclerenDB->SetObjectOpacity();
       RsSourceSclerenDB->InitPureCellDB(sclerenchyma.gapCellWall);
       RsSourceSclerenDB->InitVacuoleDB(sclerenchyma.gapCytoTono);

       /************************************
       Sclerenchyma Visualization;
       *************************************/
       RsSourceSclerenDB->RGBTime(2);
       RsSourceSclerenDB->RGBStart(4);

       rsSourceDermisVisual* RsSourceSclerenVisual = new rsSourceDermisVisual;
       RsSourceSclerenVisual->EpidermisVisual(RsSourceSclerenDB, renL, 0, result, timePrefix);
       RsSourceSclerenVisual->EpidermisVisual(RsSourceSclerenDB, renL, 1, result, timePrefix);
       RsSourceSclerenVisual->EpidermisVisual(RsSourceSclerenDB, renL, 2, result, timePrefix);
   //}

//////////////////////////////////// Epidermis  /////////////////////////////////////////

   /*************************************
   EpidermisDB
   **************************************/
//   cout << "EpidermisDB" << endl;
   /// boundaryRadius = epidermisBaseRadiusDB;
   double epidermisBaseRadius;
   epidermisBaseRadius = sclerenBaseRadius + accumulate(RsSourceSclerenDB->circleRadiusDB.begin(), RsSourceSclerenDB->circleRadiusDB.end(), 0.0);

   rsSourceDermisDB *RsSourceEpidermisDB = new rsSourceDermisDB;


   RsSourceEpidermisDB->SetObjectXYZRadiusRatio( 1.1 );

   RsSourceEpidermisDB->RandomHeightDB( totalHeight, epidermisSliceNum, initZPosition, vectorNum );
   RsSourceEpidermisDB -> InitAllDB (EpidermisXMLVtpFileNameInput,
                                     type_epi,
                                     epidermis.cellDiameter,
                                     epidermisBaseRadius,
                                     //                                     epidermisCellNum,
                                     epidermis.variationRatio,
                                     epidermisSliceNum, 1 );

   RsSourceEpidermisDB->SetObjectOpacity();
   RsSourceEpidermisDB->InitPureCellDB(epidermis.gapCellWall);
   RsSourceEpidermisDB->InitVacuoleDB(epidermis.gapCytoTono);

   /************************************
   Epidermis Visualization;
   *************************************/
   RsSourceEpidermisDB->RGBTime( 2 );
   RsSourceEpidermisDB->RGBStart( 4 );

rsSourceDermisVisual *RsSourceEpidermisVisual = new rsSourceDermisVisual;
RsSourceEpidermisVisual->EpidermisVisual(RsSourceEpidermisDB, renL, 0, result, timePrefix);
RsSourceEpidermisVisual->EpidermisVisual(RsSourceEpidermisDB, renL, 1, result, timePrefix);
RsSourceEpidermisVisual->EpidermisVisual(RsSourceEpidermisDB, renL, 2, result, timePrefix);
//   // delete Viusal;
//   delete RsSourceEpidermisVisual;

//////////////////////////////////// Endodermis  /////////////////////////////////////////
   /*************************************
   EndodermisDB
   **************************************/
//   cout << "EndodermisDB" << endl;
   /// boundaryRadius = epidermisBaseRadiusDB;
   double endodermisBaseRadius;
   endodermisBaseRadius = baseRadius - endodermisAddRadiusData;

   rsSourceDermisDB *RsSourceEndodermisDB = new rsSourceDermisDB;

   RsSourceEndodermisDB->SetObjectXYZRadiusRatio( 1 );
   RsSourceEndodermisDB->RandomHeightDB( totalHeight, endodermisSliceNum, initZPosition, vectorNum );
   RsSourceEndodermisDB -> InitAllDB (EndodermisXMLVtpFileNameInput,
                                      type_endo,
                                      endodermis.cellDiameter,
                                      endodermisBaseRadius,
                                      endodermis.variationRatio,
                                      endodermisSliceNum, 1 );

   RsSourceEndodermisDB->SetObjectOpacity();
   RsSourceEndodermisDB->InitPureCellDB(endodermis.gapCellWall);
   RsSourceEndodermisDB->InitVacuoleDB(endodermis.gapCytoTono);

   /************************************
   Endodermis Visualization;
   *************************************/
   RsSourceEndodermisDB->RGBTime( 2 );
   RsSourceEndodermisDB->RGBStart( 4 );

rsSourceDermisVisual *RsSourceEndodermisVisual = new rsSourceDermisVisual;
RsSourceEndodermisVisual->EpidermisVisual( RsSourceEndodermisDB, renL, 0, result, timePrefix);
RsSourceEndodermisVisual->EpidermisVisual(RsSourceEndodermisDB, renL, 1, result, timePrefix);
RsSourceEndodermisVisual->EpidermisVisual(RsSourceEndodermisDB, renL, 2, result, timePrefix);
//   // delete visual;
//   delete RsSourceEndodermisVisual;


////////////////////////////////////////////// Water Path ////////////////////////////////////////////////

//   cout << "Water Path" << endl;
   rsEpiCortexEndoWaterPathDB *RsEpiCortexEndoWaterPathDB = new rsEpiCortexEndoWaterPathDB;

   RsEpiCortexEndoWaterPathDB -> OutputXMLVtpFileName
   ( ApoplastXMLVtpFileNameInput,
     SymplastXMLVtpFileNameInput );

   RsEpiCortexEndoWaterPathDB -> InitAllDB
   (RsSourceEpidermisDB,
    RsSourceCorticalDB,
    RsSourceEndodermisDB
   );

// Check what happens on uncommenting - Sankalp
   rsEpiCortexEndoWaterPathDBVisual *RsEpiCortexEndoWaterPathDBVisual = new rsEpiCortexEndoWaterPathDBVisual;
   RsEpiCortexEndoWaterPathDBVisual -> ApoplastTubeXMLVtp( RsEpiCortexEndoWaterPathDB );
   RsEpiCortexEndoWaterPathDBVisual -> SymplastTubeXMLVtp( RsEpiCortexEndoWaterPathDB );
   
   RsEpiCortexEndoWaterPathDBVisual -> ApoplastTriangleStripXMLVtp( RsEpiCortexEndoWaterPathDB, surfaceFlux );
   RsEpiCortexEndoWaterPathDBVisual -> SymplastTriangleStripXMLVtp( RsEpiCortexEndoWaterPathDB, surfaceFlux );

 //////////////////////////////////// Pericycle  /////////////////////////////////////////
      /*************************************
      PericycleDB
      **************************************/
   double pericycleBaseRadius;
   pericycleBaseRadius = endodermisBaseRadius - pericycleAddRadiusData;

   rsSourceDermisDB* RsSourcePericycleDB = new rsSourceDermisDB;

   RsSourcePericycleDB->SetObjectXYZRadiusRatio(1);
   RsSourcePericycleDB->RandomHeightDB(totalHeight, pericycleSliceNum, initZPosition, vectorNum);
   RsSourcePericycleDB->InitAllDB(PericycXMLVtpFileNameInput,
                                  type_peri,
                                  pericycle.cellDiameter,
                                  pericycleBaseRadius,
                                  pericycle.variationRatio,
                                  pericycleSliceNum, 1);

   RsSourcePericycleDB->SetObjectOpacity();
   RsSourcePericycleDB->InitPureCellDB(pericycle.gapCellWall);
   RsSourcePericycleDB->InitVacuoleDB(pericycle.gapCytoTono);

   /************************************
   Pericycle Visualization;
   *************************************/
   RsSourcePericycleDB->RGBTime(2);
   RsSourcePericycleDB->RGBStart(4);

   rsSourceDermisVisual* RsSourcePericycleVisual = new rsSourceDermisVisual;
   RsSourcePericycleVisual->EpidermisVisual(RsSourcePericycleDB, renL, 0, result, timePrefix);
   RsSourcePericycleVisual->EpidermisVisual(RsSourcePericycleDB, renL, 1, result, timePrefix);
   RsSourcePericycleVisual->EpidermisVisual(RsSourcePericycleDB, renL, 2, result, timePrefix);

   rsPXCoreDB* RsPXCoreDB = new rsPXCoreDB;
   rsMXBoundaryOutDB* RSMXBoundaryOutDB = new rsMXBoundaryOutDB;
   rsSteleInnerDB* RsSteleInnerDB = new rsSteleInnerDB;
   rsPXBoundaryDB* RsPXBoundaryDB = new rsPXBoundaryDB;
   rsPhloemDB* RsPhloemDB = new rsPhloemDB;

   InitInnertructure(stele, metaXylem, protoXylem, phloem, pericycleBaseRadius, renL,
       RsPXCoreDB, RSMXBoundaryOutDB, RsSteleInnerDB, RsPXBoundaryDB, RsPhloemDB);

//////////////////////////////////////// DataOutput /////////////////////////////////////////////////
   rsDataOutput *RsDataOutput = new rsDataOutput;
   string outputName = "dataOutput";

   RsDataOutput -> DataOutputName( dataOutputNameInput );
   RsDataOutput -> CorticalDataOutputCalculate( RsSourceCorticalDB );
   RsDataOutput -> NonRcaDataOutput();
   RsDataOutput -> NutrientAndMitochondriaCalculate();
   RsDataOutput -> PathLengthDataOutputCalculate( RsEpiCortexEndoWaterPathDB );
   RsDataOutput -> AllDataOutput( baseRadius, totalHeight);

/// Delete Database;
   delete RsSourceCorticalDB;
   RsSourceCorticalDB = NULL;

   delete RsSourceEpidermisDB;
   RsSourceEpidermisDB = NULL;

   delete RsSourceEndodermisDB;
   RsSourceEndodermisDB = NULL;

   delete RsSourcePericycleDB;
   RsSourcePericycleDB = NULL;

//   delete RsRcaDB;
//   RsRcaDB = NULL;

   delete RsEpiCortexEndoWaterPathDB;
   RsEpiCortexEndoWaterPathDB = NULL;

   delete RsDataOutput;
   RsDataOutput = NULL;
}

//////////////////////////////////////////  Render  ////////////////////////////////////////////

void rsDynamicDataOutput::RenderTogether( vtkSmartPointer<vtkRenderer> renL )
{

   renL->SetBackground( 1, 1, 1 );
// Set up the lighting.
//
   vtkSmartPointer<vtkLight> light1 = vtkSmartPointer<vtkLight>::New();
   vtkSmartPointer<vtkLight> light2 = vtkSmartPointer<vtkLight>::New();
   vtkSmartPointer<vtkLight> light3 = vtkSmartPointer<vtkLight>::New();
   vtkSmartPointer<vtkLight> light4 = vtkSmartPointer<vtkLight>::New();
   vtkSmartPointer<vtkLight> lightHead = vtkSmartPointer<vtkLight>::New();
   double lightIntensity = 0.2;
   light1 -> SetIntensity( lightIntensity );
   light2 -> SetIntensity( lightIntensity );
   light3 -> SetIntensity( lightIntensity );
   light4 -> SetIntensity( lightIntensity );
// light1->SetFocalPoint(1.875,0.6125,0);
   light1->SetPosition( 500 , 1000, 1 );
   light2->SetPosition( -500 , 1000, 1 );
   light3->SetPosition( 0 , 1000, 500 );
   light4->SetPosition( 0 , 1000, -500 );
// SetLightTypeToHeadlight
   lightHead -> SetLightTypeToHeadlight();

// cout lightIntensity;
   double lightIntensity1;
   lightIntensity1 = light1 -> GetIntensity();
// cout << "lightIntensity1: " << lightIntensity1 << endl;

   renL->AddLight( light1 );
   renL->AddLight( light2 );
   renL->AddLight( light3 );
   renL->AddLight( light4 );
   renL->AddLight( lightHead );

   vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
   renWin->AddRenderer( renL );

   renWin->SetSize( 720, 720 );

   vtkSmartPointer<vtkCamera> cam = renL->GetActiveCamera();
   cam->UseHorizontalViewAngleOff();
   double cameraYposition = 2000;
   cam->SetPosition( 0 , cameraYposition, 1 );
   cam->Zoom(1);

   double cameraThickness;
   cam->SetThickness( 10000 );
   cameraThickness = cam->GetThickness();
   cout << "GetThickness: " << cameraThickness << endl;


   /*******************************
    Image saving;
    *******************************/
//OffScreenRenderingOn;
   renWin->OffScreenRenderingOn();

   vtkSmartPointer<vtkRenderLargeImage> renderLarge = vtkSmartPointer<vtkRenderLargeImage>::New();
   renderLarge->SetInput( renL );

   vtkSmartPointer<vtkJPEGWriter> image  = vtkSmartPointer<vtkJPEGWriter>::New();

   image->SetInputData( renderLarge->GetOutput());
   image->SetFileName( "Layer15_CortexMinCellDiameter17_CytoTonoGap1_VacuoleNoView.jpg" );
   image->SetQuality( 100 );
   image->Write();

}

void rsDynamicDataOutput::InitInnertructure(
    globals stele,
    globals metaXylem,
    globals protoXylem,
    globals phloem,

    double pericycleBaseRadius,

    vtkSmartPointer<vtkRenderer> renL,

    rsPXCoreDB* &RsPXCoreDB,
    rsMXBoundaryOutDB* &RSMXBoundaryOutDB,
    rsSteleInnerDB* &RsSteleInnerDB,
    rsPXBoundaryDB* &RsPXBoundaryDB,
    rsPhloemDB* &RsPhloemDB
) {
    /*************************************
   PXCore
   *************************************/
    cout << "XylemOuterRing" << endl;

    RsPXCoreDB = new rsPXCoreDB;
    int protoXylemSliceNum = protoXylem.minSlice + (rand() % (protoXylem.maxSlice - protoXylem.minSlice + 1));
    /*RsPXCoreDB->RandomHeightDB(totalHeight, protoXylemSliceNum, initZPosition, vectorNum);
    RsPXCoreDB->InitXylemOutRing(pericycleBaseRadius,
        protoXylem.gapRadius,
        protoXylem.num,
        protoXylem.averageRingRadius,
        protoXylem.variationRatio,
        protoXylem.surroundingCellRingNum,
        protoXylem.surroundingCellRingRadius,
        protoXylemSliceNum);
    RsPXCoreDB->InitPXSamll();*/


    /*************************************
    PXBoundaryDB
    **************************************/
    RsPXBoundaryDB = new rsPXBoundaryDB;

    RsPXBoundaryDB->RandomHeightDB(totalHeight, protoXylemSliceNum, initZPosition, vectorNum);
    RsPXBoundaryDB->InitXylemOutRing(pericycleBaseRadius,
        protoXylem.gapRadius,
        protoXylem.num,
        protoXylem.averageRingRadius,
        protoXylem.variationRatio,
        protoXylem.surroundingCellRingNum,
        protoXylem.surroundingCellRingRadius,
        protoXylemSliceNum);
    RsPXBoundaryDB->InitPXSamll();
    RsPXCoreDB = RsPXBoundaryDB;
    RsPXBoundaryDB->InitBoundaryCell
    (RsPXCoreDB,
        metaXylem.dotNum,
        metaXylem.setUpRowNum,
        metaXylem.setDownRowNum,
        protoXylemSliceNum);

    /*************************************
    MetaXylem
    *************************************/
    cout << "rsMXBoundaryOutDB" << endl;

    RSMXBoundaryOutDB = new rsMXBoundaryOutDB;
    int metaXylemSliceNum = metaXylem.minSlice + (rand() % (metaXylem.maxSlice - metaXylem.minSlice + 1));
    RSMXBoundaryOutDB->RandomHeightDB(totalHeight, metaXylemSliceNum, initZPosition, vectorNum);
    RSMXBoundaryOutDB->InitXylemOutRing(RsPXCoreDB,
        metaXylem.num,
        metaXylem.averageRingRadius,
        metaXylem.variationRatio,
        metaXylem.surroundingCellRingNum,
        protoXylem.surroundingCellRingNum,
        protoXylem.surroundingCellRingRadius,
        metaXylem.maxRingRadius,
        metaXylem.numFiles,
        metaXylem.eachRingNum,
        metaXylemSliceNum);
    RSMXBoundaryOutDB->InitBoundaryCell(metaXylem.dotNum, metaXylem.setUpRowNum, metaXylem.setDownRowNum, metaXylemSliceNum);
    RSMXBoundaryOutDB->InitBoundaryInterDB(
        metaXylem.tangentRingRadiusRatio,
        metaXylem.steleCellNumBetween,
        metaXylem.variationRatio,
        metaXylemSliceNum);
    RSMXBoundaryOutDB->InitBoundaryUpDB(
        metaXylem.verticalLengthThresholdRatio,
        metaXylem.variationRatio,
        metaXylemSliceNum);

    //////////////////////////////////// Stele Jagdeep 2-3-2021  /////////////////////////////////////////
    /*************************************
    SteleDB
    **************************************/
    cout << "SteleDB" << endl;

    RsSteleInnerDB = new rsSteleInnerDB;

    RSMXBoundaryOutDB->SetObjectXYZRadiusRatio(1);

    //RsSourceEndodermisDB->RandomHeightDB(totalHeight, endodermisSliceNum, initZPosition, vectorNum);
    int steleSliceNum = stele.minSlice + (rand() % (stele.maxSlice - stele.minSlice + 1));
    RsSteleInnerDB->InitAllDB(RSMXBoundaryOutDB,
        stele.innestCellDiameter / 2.0,
        stele.innerLayerNum,
        totalHeight,
        initZPosition,
        vectorNum,
        stele.variationRatio,
        steleSliceNum);

    RsSteleInnerDB->SetObjectOpacity();

    /*************************************
    Phloem
    **************************************/
    RsPhloemDB = new rsPhloemDB;
    RsPhloemDB->InitUpCell(
        RsPXBoundaryDB,
        phloem.setUpAppendParallelLengthThresholdRatio,
        totalHeight,
        protoXylemSliceNum,
        initZPosition,
        vectorNum,
        protoXylem.variationRatio);
    RsPhloemDB->InitDownCell(RsPXBoundaryDB, protoXylem.variationRatio, protoXylemSliceNum);

    /************************************
    PXCore Visualization;
    *************************************/
    RsPXCoreDB->RGBTime(2);
    RsPXCoreDB->RGBStart(4);

    rsPXCoreVisual* RsPXCoreVisualDB = new rsPXCoreVisual;
    RsPXCoreVisualDB->PXCoreVisual(RsPXBoundaryDB, renL);
    RsPXCoreVisualDB->PXCenterRingVisual(RsPXBoundaryDB, renL);
    RsPXCoreVisualDB->PXSmallVisual(RsPXBoundaryDB, renL);

    /************************************
    PXBoundary Visualization;
    *************************************/
    RsPXBoundaryDB->RGBTime(2);
    RsPXBoundaryDB->RGBStart(4);

    rsPXBoundaryVisual* RsPXBoundaryVisualDB = new rsPXBoundaryVisual;
    RsPXBoundaryVisualDB->BoundaryCellVisual(RsPXBoundaryDB, renL);

    /************************************
    MXCore Visualization;
    *************************************/
    RSMXBoundaryOutDB->RGBTime(2);
    RSMXBoundaryOutDB->RGBStart(4);

    rsMXCoreVisual* RsMXCoreVisualDB = new rsMXCoreVisual;
    RsMXCoreVisualDB->MXCenterRingVisual(RSMXBoundaryOutDB, renL);
    RsMXCoreVisualDB->MXVisual(RSMXBoundaryOutDB, renL);

    /************************************
    MXBoundary Visualization;
    *************************************/
    RSMXBoundaryOutDB->RGBTime(2);
    RSMXBoundaryOutDB->RGBStart(4);

    rsMXBoundaryVisual* RsMXBoundaryVisualDB = new rsMXBoundaryVisual;
    RsMXBoundaryVisualDB->MXBoundaryCellVisual(RSMXBoundaryOutDB, renL);

    /************************************
    MXBoundaryOut Visualization;
    *************************************/
    rsMXBoundaryOutVisual* RsMXBoundaryOutVisualDB = new rsMXBoundaryOutVisual;
    RsMXBoundaryOutVisualDB->MXBoundaryInterCellVisual(RSMXBoundaryOutDB, renL);
    RsMXBoundaryOutVisualDB->MXBoundaryUpCellVisual(RSMXBoundaryOutDB, renL);

    /*************************************
    Phloem Visualization
    **************************************/
    rsPhloemVisual* RsPhloemVisualDB = new rsPhloemVisual;
    RsPhloemVisualDB->DownCellVisual(RsPhloemDB, renL);
    RsPhloemVisualDB->UpAppendCellVisual(RsPhloemDB, renL);
    RsPhloemVisualDB->UpPhloemCellVisual(RsPhloemDB, renL);

    /************************************
    stele Visualization;
    *************************************/
    RsSteleInnerDB->RGBTime(2);
    RsSteleInnerDB->RGBStart(4);

    rsSteleInnerVisual* RsSteleInnerVisualDB = new rsSteleInnerVisual;
    RsSteleInnerVisualDB->SteleInnerVisual(RsSteleInnerDB, renL);

    /// center cell visualization 
    RsSteleInnerVisualDB->SteleInnestVisual(RsSteleInnerDB, renL);

    delete RsSteleInnerDB;
    RsSteleInnerDB = NULL;
}
