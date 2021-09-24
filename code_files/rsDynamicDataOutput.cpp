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
    globals epidermis,
    globals endodermis,
    globals exodermis,
    globals sclerenchyma,
    globals pericycle,

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

   RsSourceCorticalDB -> RandomHeightDB( totalHeight, corticalSliceNum, initZPosition, vectorNum );
   RsSourceCorticalDB -> InitAllDB ( baseRadius,
                                     cortical.numFiles,
                                     corticalCellMultiplyRatio,
                                     cortical.cellDiameter/2.0,
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

   /*************************************
   Cortical visualization
   **************************************/
   RsSourceCorticalDB->RGBTime( 6 );
   RsSourceCorticalDB->RGBStart( 2 );
   ///
   rsSourceCorticalVisual *RsSourceCorticalVisual = new rsSourceCorticalVisual;



//   /// Cortical vacuole;
cout << "CorticalDB - VacuoleVisual" << endl;
 RsSourceCorticalVisual -> VacuoleVisual( RsSourceCorticalDB, renL );

 cout << "CorticalDB - Plasma Membrane Visual" << endl;
 RsSourceCorticalVisual->CorticalPlasmaMembraneVisual(RsSourceCorticalDB, renL);

//   /// Cortical cell;
cout << "CorticalDB - CorticalVisual" << endl;
RsSourceCorticalVisual -> CorticalVisual( RsSourceCorticalDB, renL );
delete RsSourceCorticalVisual;
cout << "CorticalDB - Finish" << endl;


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
    sclerenAddRadiusData,
    sclerenBaseRadius,
    sclerenchyma.variationRatio,
    sclerenSliceNum);

RsSourceSclerenDB->SetObjectOpacity();
RsSourceSclerenDB->InitPureCellDB(sclerenchyma.gapCellWall);
RsSourceSclerenDB->InitVacuoleDB(sclerenchyma.gapCytoTono);

/************************************
Sclerenchyma Visualization;
*************************************/
RsSourceSclerenDB->RGBTime(2);
RsSourceSclerenDB->RGBStart(4);

rsSourceDermisVisual* RsSourceSclerenVisual = new rsSourceDermisVisual;
RsSourceSclerenVisual->EpidermisVisual(RsSourceSclerenDB, renL, 0);
RsSourceSclerenVisual->EpidermisVisual(RsSourceSclerenDB, renL, 1);
RsSourceSclerenVisual->EpidermisVisual(RsSourceSclerenDB, renL, 2);


//////////////////////////////////// Epidermis  /////////////////////////////////////////

   /*************************************
   EpidermisDB
   **************************************/
//   cout << "EpidermisDB" << endl;
   /// boundaryRadius = epidermisBaseRadiusDB;
   double epidermisBaseRadius;
   epidermisBaseRadius = sclerenBaseRadius + sclerenAddRadiusData;

   rsSourceDermisDB *RsSourceEpidermisDB = new rsSourceDermisDB;


   RsSourceEpidermisDB->SetObjectXYZRadiusRatio( 1.1 );

   RsSourceEpidermisDB->RandomHeightDB( totalHeight, epidermisSliceNum, initZPosition, vectorNum );
   RsSourceEpidermisDB -> InitAllDB (EpidermisXMLVtpFileNameInput,
                                     epidermisAddRadiusData,
                                     epidermisBaseRadius,
                                     epidermis.variationRatio,
                                     epidermisSliceNum );

   RsSourceEpidermisDB->SetObjectOpacity();
   RsSourceEpidermisDB->InitPureCellDB(epidermis.gapCellWall);
   RsSourceEpidermisDB->InitVacuoleDB(epidermis.gapCytoTono);

   /************************************
   Epidermis Visualization;
   *************************************/
   RsSourceEpidermisDB->RGBTime( 2 );
   RsSourceEpidermisDB->RGBStart( 4 );

rsSourceDermisVisual *RsSourceEpidermisVisual = new rsSourceDermisVisual;
RsSourceEpidermisVisual->EpidermisVisual(RsSourceEpidermisDB, renL, 0);
RsSourceEpidermisVisual->EpidermisVisual(RsSourceEpidermisDB, renL, 1);
RsSourceEpidermisVisual->EpidermisVisual( RsSourceEpidermisDB, renL, 2);
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
                                      endodermisAddRadiusData,
                                      endodermisBaseRadius,
                                      endodermis.variationRatio,
                                      endodermisSliceNum );

   RsSourceEndodermisDB->SetObjectOpacity();
   RsSourceEndodermisDB->InitPureCellDB(endodermis.gapCellWall);
   RsSourceEndodermisDB->InitVacuoleDB(endodermis.gapCytoTono);

   /************************************
   Endodermis Visualization;
   *************************************/
   RsSourceEndodermisDB->RGBTime( 2 );
   RsSourceEndodermisDB->RGBStart( 4 );

rsSourceDermisVisual *RsSourceEndodermisVisual = new rsSourceDermisVisual;
RsSourceEndodermisVisual->EpidermisVisual(RsSourceEndodermisDB, renL, 0);
RsSourceEndodermisVisual->EpidermisVisual(RsSourceEndodermisDB, renL, 1);
RsSourceEndodermisVisual->EpidermisVisual(RsSourceEndodermisDB, renL, 2);
//   // delete visual;
//   delete RsSourceEndodermisVisual;


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

RsEpiCortexEndoWaterPathDBVisual -> ApoplastTriangleStripXMLVtp( RsEpiCortexEndoWaterPathDB );
RsEpiCortexEndoWaterPathDBVisual -> SymplastTriangleStripXMLVtp( RsEpiCortexEndoWaterPathDB );


//////////////////////////////////////// DataOutput /////////////////////////////////////////////////
   rsDataOutput *RsDataOutput = new rsDataOutput;
   string outputName = "dataOutput";

   RsDataOutput -> DataOutputName( dataOutputNameInput );
   RsDataOutput -> CorticalDataOutputCalculate( RsSourceCorticalDB );
   RsDataOutput -> RcaDataOutputCalculate( RsRcaDB );
   RsDataOutput -> NutrientAndMitochondriaCalculate();
   RsDataOutput -> PathLengthDataOutputCalculate( RsEpiCortexEndoWaterPathDB );
   RsDataOutput -> AllDataOutput( baseRadius, totalHeight );

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
       pericycleAddRadiusData,
       pericycleBaseRadius,
       pericycle.variationRatio,
       pericycleSliceNum);

   RsSourcePericycleDB->SetObjectOpacity();
   RsSourcePericycleDB->InitPureCellDB(pericycle.gapCellWall);
   RsSourcePericycleDB->InitVacuoleDB(pericycle.gapCytoTono);

   /************************************
   Pericycle Visualization;
   *************************************/
   RsSourcePericycleDB->RGBTime(2);
   RsSourcePericycleDB->RGBStart(4);

   rsSourceDermisVisual* RsSourcePericycleVisual = new rsSourceDermisVisual;
   RsSourcePericycleVisual->EpidermisVisual(RsSourcePericycleDB, renL, 0);
   RsSourcePericycleVisual->EpidermisVisual(RsSourcePericycleDB, renL, 1);
   RsSourcePericycleVisual->EpidermisVisual(RsSourcePericycleDB, renL, 2);

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
   globals epidermis,
   globals endodermis,
   globals exodermis,
   globals sclerenchyma,
   globals pericycle,

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
   const char* dataOutputNameInput,

    //Other
    vtkSmartPointer<vtkRenderer> renL
)

{  
   /*************************************
   CorticalDB
   **************************************/
   rsSourceCorticalDB *RsSourceCorticalDB = new rsSourceCorticalDB;

   RsSourceCorticalDB -> RandomHeightDB( totalHeight, corticalSliceNum, initZPosition, vectorNum );
   RsSourceCorticalDB -> InitAllDB ( baseRadius,
                                     cortical.numFiles,
                                     corticalCellMultiplyRatio,
                                     cortical.cellDiameter/2,
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
RsSourceCorticalVisual -> VacuoleVisual( RsSourceCorticalDB, renL );

cout << "CorticalDB - Plasma Membrane Visual" << endl;
RsSourceCorticalVisual->CorticalPlasmaMembraneVisual(RsSourceCorticalDB, renL);

   /// Cortical cell;
cout << "CorticalDB - CorticalVisual" << endl;
RsSourceCorticalVisual -> CorticalVisual( RsSourceCorticalDB, renL );
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
   RsSourceSclerenDB->InitAllDB(SclerenXMLVtpFileNameInput,
    sclerenAddRadiusData,
    sclerenBaseRadius,
    sclerenchyma.variationRatio,
    sclerenSliceNum);

   RsSourceSclerenDB->SetObjectOpacity();
   RsSourceSclerenDB->InitPureCellDB(sclerenchyma.gapCellWall);
   RsSourceSclerenDB->InitVacuoleDB(sclerenchyma.gapCytoTono);

/************************************
Epidermis Visualization;
*************************************/
   RsSourceSclerenDB->RGBTime(2);
   RsSourceSclerenDB->RGBStart(4);

rsSourceDermisVisual* RsSourceSclerenVisual = new rsSourceDermisVisual;
RsSourceSclerenVisual->EpidermisVisual(RsSourceSclerenDB, renL, 0);
RsSourceSclerenVisual->EpidermisVisual(RsSourceSclerenDB, renL, 1);
RsSourceSclerenVisual->EpidermisVisual(RsSourceSclerenDB, renL, 2);

//////////////////////////////////// Epidermis  /////////////////////////////////////////

   /*************************************
   EpidermisDB
   **************************************/
//   cout << "EpidermisDB" << endl;
   /// boundaryRadius = epidermisBaseRadiusDB;
   double epidermisBaseRadius;
   epidermisBaseRadius = sclerenBaseRadius + sclerenAddRadiusData;

   rsSourceDermisDB *RsSourceEpidermisDB = new rsSourceDermisDB;


   RsSourceEpidermisDB->SetObjectXYZRadiusRatio( 1.1 );

   RsSourceEpidermisDB->RandomHeightDB( totalHeight, epidermisSliceNum, initZPosition, vectorNum );
   RsSourceEpidermisDB -> InitAllDB (EpidermisXMLVtpFileNameInput,
                                     epidermisAddRadiusData,
                                     epidermisBaseRadius,
//                                     epidermisCellNum,
                                     epidermis.variationRatio,
                                     epidermisSliceNum );

   RsSourceEpidermisDB->SetObjectOpacity();
   RsSourceEpidermisDB->InitPureCellDB(epidermis.gapCellWall);
   RsSourceEpidermisDB->InitVacuoleDB(epidermis.gapCytoTono);

   /************************************
   Epidermis Visualization;
   *************************************/
   RsSourceEpidermisDB->RGBTime( 2 );
   RsSourceEpidermisDB->RGBStart( 4 );

rsSourceDermisVisual *RsSourceEpidermisVisual = new rsSourceDermisVisual;
RsSourceEpidermisVisual->EpidermisVisual(RsSourceEpidermisDB, renL, 0);
RsSourceEpidermisVisual->EpidermisVisual(RsSourceEpidermisDB, renL, 1);
RsSourceEpidermisVisual->EpidermisVisual(RsSourceEpidermisDB, renL, 2);
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
                                      endodermisAddRadiusData,
                                      endodermisBaseRadius,
                                      endodermis.variationRatio,
                                      endodermisSliceNum );

   RsSourceEndodermisDB->SetObjectOpacity();
   RsSourceEndodermisDB->InitPureCellDB(endodermis.gapCellWall);
   RsSourceEndodermisDB->InitVacuoleDB(endodermis.gapCytoTono);

   /************************************
   Endodermis Visualization;
   *************************************/
   RsSourceEndodermisDB->RGBTime( 2 );
   RsSourceEndodermisDB->RGBStart( 4 );

rsSourceDermisVisual *RsSourceEndodermisVisual = new rsSourceDermisVisual;
RsSourceEndodermisVisual->EpidermisVisual( RsSourceEndodermisDB, renL, 0);
RsSourceEndodermisVisual->EpidermisVisual(RsSourceEndodermisDB, renL, 1);
RsSourceEndodermisVisual->EpidermisVisual(RsSourceEndodermisDB, renL, 2);
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
//   rsEpiCortexEndoWaterPathDBVisual *RsEpiCortexEndoWaterPathDBVisual = new rsEpiCortexEndoWaterPathDBVisual;
//   RsEpiCortexEndoWaterPathDBVisual -> ApoplastTubeXMLVtp( RsEpiCortexEndoWaterPathDB );
//   RsEpiCortexEndoWaterPathDBVisual -> SymplastTubeXMLVtp( RsEpiCortexEndoWaterPathDB );

//RsEpiCortexEndoWaterPathDBVisual -> ApoplastTriangleStripXMLVtp( RsEpiCortexEndoWaterPathDB );
//RsEpiCortexEndoWaterPathDBVisual -> SymplastTriangleStripXMLVtp( RsEpiCortexEndoWaterPathDB );

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
       pericycleAddRadiusData,
       pericycleBaseRadius,
       pericycle.variationRatio,
       pericycleSliceNum);

   RsSourcePericycleDB->SetObjectOpacity();
   RsSourcePericycleDB->InitPureCellDB(pericycle.gapCellWall);
   RsSourcePericycleDB->InitVacuoleDB(pericycle.gapCytoTono);

   /************************************
   Pericycle Visualization;
   *************************************/
   RsSourcePericycleDB->RGBTime(2);
   RsSourcePericycleDB->RGBStart(4);

   rsSourceDermisVisual* RsSourcePericycleVisual = new rsSourceDermisVisual;
   RsSourcePericycleVisual->EpidermisVisual(RsSourcePericycleDB, renL, 0);
   RsSourcePericycleVisual->EpidermisVisual(RsSourcePericycleDB, renL, 1);
   RsSourcePericycleVisual->EpidermisVisual(RsSourcePericycleDB, renL, 2);


   /*************************************
   PXCore
   *************************************/
   cout << "XylemOuterRing" << endl;

   rsPXCoreDB* RsPXCoreDB = new rsPXCoreDB;
   int protoXylemSliceNum = protoXylem.minSlice + (rand() % (protoXylem.maxSlice - protoXylem.minSlice + 1));
   RsPXCoreDB->RandomHeightDB(totalHeight, protoXylemSliceNum, initZPosition, vectorNum);
   RsPXCoreDB->InitXylemOutRing(pericycleBaseRadius,
       protoXylem.gapRadius,
       protoXylem.num,
       protoXylem.averageRingRadius,
       protoXylem.variationRatio,
       protoXylem.surroundingCellRingNum,
       protoXylem.surroundingCellRingRadius,
       protoXylemSliceNum);
   RsPXCoreDB->InitPXSamll();

   /*************************************
   XylemOuterRing
   *************************************/
   cout << "XylemOuterRing" << endl;

   rsMXCoreDB* RsMXCoreDB = new rsMXCoreDB;
   int metaXylemSliceNum = metaXylem.minSlice + (rand() % (metaXylem.maxSlice - metaXylem.minSlice + 1));
   RsMXCoreDB->RandomHeightDB(totalHeight, metaXylemSliceNum, initZPosition, vectorNum);
   RsMXCoreDB->InitXylemOutRing(RsPXCoreDB,
       metaXylem.num,
       metaXylem.averageRingRadius,
       metaXylem.variationRatio,
       metaXylem.surroundingCellRingNum,
       protoXylem.surroundingCellRingNum,
       protoXylem.surroundingCellRingRadius,
       metaXylemSliceNum);

   /*************************************
   MetaXylum
   *************************************/
   cout << "rsMXBoundaryDB" << endl;

   //rsMXBoundaryDB* RSMXBoundaryDB = new rsMXBoundaryDB;
   int dotNum = 10;
   int setUpRowNum = 8;
   int setDownRowNum = 1;
   double setUpAppendParallelLengthThresholdRatio = 0.5;
   //RSMXBoundaryDB->InitBoundaryCell(RsMXCoreDB, dotNum, setUpRowNum, setDownRowNum, sliceNum);


   cout << "rsMXBoundaryOutDB" << endl;

   rsMXBoundaryOutDB* RSMXBoundaryOutDB = new rsMXBoundaryOutDB;
   RSMXBoundaryOutDB->RandomHeightDB(totalHeight, metaXylemSliceNum, initZPosition, vectorNum);
   RSMXBoundaryOutDB->InitXylemOutRing(RsPXCoreDB,
       metaXylem.num,
       metaXylem.averageRingRadius,
       metaXylem.variationRatio,
       metaXylem.surroundingCellRingNum,
       protoXylem.surroundingCellRingNum,
       protoXylem.surroundingCellRingRadius,
       metaXylemSliceNum);
   RSMXBoundaryOutDB->InitBoundaryCell(dotNum, setUpRowNum, setDownRowNum, metaXylemSliceNum);
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

   rsSteleInnerDB* RsSteleInnerDB = new rsSteleInnerDB;

   RSMXBoundaryOutDB->SetObjectXYZRadiusRatio(1);

   //RsSourceEndodermisDB->RandomHeightDB(totalHeight, endodermisSliceNum, initZPosition, vectorNum);
   int steleSliceNum = stele.minSlice + (rand() % (stele.maxSlice - stele.minSlice + 1));
    RsSteleInnerDB->InitAllDB(RSMXBoundaryOutDB,
        stele.innestCellDiameter/2.0,
        stele.innerLayerNum,
        totalHeight,
        initZPosition,
        vectorNum,
        stele.variationRatio,
        steleSliceNum);

   RsSteleInnerDB ->SetObjectOpacity();


   /*************************************
   PXBoundaryDB
   **************************************/
   rsPXBoundaryDB* RsPXBoundaryDB = new rsPXBoundaryDB;

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
   RsPXBoundaryDB->InitBoundaryCell
   (RsPXCoreDB,
       dotNum,
       setUpRowNum,
       setDownRowNum,
       protoXylemSliceNum);


   /*************************************
   Phloem
   **************************************/
   rsPhloemDB* RsPhloemDB = new rsPhloemDB;
   RsPhloemDB->InitUpCell(
       RsPXBoundaryDB,
       setUpAppendParallelLengthThresholdRatio,
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
   RsMXCoreDB->RGBTime(2);
   RsMXCoreDB->RGBStart(4);

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

   rsSteleInnerVisual *RsSteleInnerVisualDB = new rsSteleInnerVisual;
   RsSteleInnerVisualDB->SteleInnerVisual(RsSteleInnerDB, renL);

   /// center cell visualization 
   RsSteleInnerVisualDB->SteleInnestVisual(RsSteleInnerDB, renL);
   
   /***********************************
   Metaxylemboundary out*************** Jgdp - 2/5/2021*/
   //rsMXBoundaryOutDB* RsMXBoundaryOutDB = new rsMXBoundaryOutDB;
   //RsMXBoundaryOutDB->InitBoundaryUpDB(RsMXCoreDB, setUpVecticalLengthThresholdRatio, variationRatio, sliceNum);
   //RsMXBoundaryOutDB->InitBoundaryInterDB(innerTangentRingRadiusRatioTemp, setInterVerticalNum, variationRatio, sliceNum);


   /// Metaxylem visualization
   //rsMXBoundaryOutVisual* RsMXBoundaryOutVisualDB = new rsMXBoundaryOutVisual;

//vtk Error ~Sankalp
  // RsMXBoundaryOutVisualDB->MXBoundaryInterCellVisual(RSMXBoundaryOutDB, renL);
  // RsMXBoundaryOutVisualDB->MXBoundaryUpCellVisual(RSMXBoundaryOutDB, renL);
   
   /***********************************
   rsMXBoundaryDB*************** Jgdp - 2/5/2021*/
   //rsMXBoundaryDB* RsMXBoundaryDB = new rsMXBoundaryDB;
   //RsMXBoundaryDB -> InitBoundaryCell
   //void rsMXBoundaryDB::InitBoundaryCell
   //(int dotNum,
     //  int setUpRowNum,
       //int setDownRowNum,
       //int sliceNum)
       
   //   // delete visual;
   //   delete RsSourceEndodermisVisual;


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

   delete RsSteleInnerDB;
   RsSteleInnerDB = NULL;
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
