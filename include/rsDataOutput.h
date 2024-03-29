#ifndef RSDATAOUTPUT_H_INCLUDED
#define RSDATAOUTPUT_H_INCLUDED

#include "rsSourceCorticalDB.h"
#include "rsRcaDB.h"
#include "rsEpiCortexEndoWaterPathDB.h"
#include <sstream>
#include "globals.h"
#include <rsPXBoundaryDB.h>
#include <rsMXBoundaryOutDB.h>
#include <rsPhloemDB.h>
#include <rsSteleInnerDB.h>

class rsDataOutput : public globals
{

public:

   const char* dataOutputName;
   void DataOutputName( const char* dataOutputNameInput );

   double steleRadius;
   double cortexHeight;
   double dlete;

   int corticalRingNum;
   int corticalTotalCellNum;
   double gapCellWall;
   double gapCytoTono;

   double cortexThickness;
   double corticalInnermostCellDiameter;
   double rootSegment1cmRatio;
   double airSpaceRatio;
   double sectionVolume;
   double cortexTheoreticalVolume;
   double cortex2SectionRatio;
   double corticalTotalCellVolume;
   double corticalPureCellVolume;
   double corticalCellWallVolume;
   double corticalCytoplasmVolume;
   double corticalVacuoleVolume;

   double cytoplasm2SectionRatio;
   double vacuole2SectionRatio;
   double cellWall2CellRatio;
   double cytoplasm2CellRatio;
   double vacuole2CellRatio;
   /// PathVolume;
   double apoplastVolume;
   double symplastVolume;

   
   void CorticalDataOutputCalculate
   ( rsSourceCorticalDB *RsSourceCorticalDB );

   void DermisDataOutputCalculate(rsSourceDermisDB* RsSourceDermisDB);
   void PXDataOutputCalculate(rsPXCoreDB* RsPXCoreDB);
   void MXDataOutputCalculate(rsMXCoreDB* RsMXCoreDB);
   void MXBoundaryDataOutputCalculate(rsMXBoundaryOutDB* RSMXBoundaryOutDB);
   void SteleDataOutputCalculate(rsSteleInnerDB* RsSteleInnerDB);
   void PXBoundaryDataOutputCalculate(rsPXBoundaryDB* RsPXBoundaryDB);
   void PhloemDataOutputCalculate(rsPhloemDB* RsPhloemDB);

   /// RCA;
   double rcaRatioInput;
   double rca2CortexExactRatio;
   double rcaRealVolume;
   void RcaDataOutputCalculate( rsRcaDB *RsRcaDB );

   /// NutrientAndMitochondriaCalculate;
   double nitrogenTotal;
   double nitrogenSolubleTotal;
   double nitrateTotal;
   double ammoniumTotal;
   double aminoAcidTotal;

   double phosphorusTotal;
   double PiTotal;
   double nitrogenPerCorticalVolume;
   double phosphorusPerCorticalVolume;
   double mitoNumTotal;
   void NutrientAndMitochondriaCalculate();

   /// NonRCA;
   void NonRcaDataOutput();

   /// PathLength;
   double apoplastPathLengthTotal;
   double apoplastPathLengthAverage;
   double apoplastPathLengthShortest;
   double apoplastPathLengthLongest;

   double symplastPathLengthTotal;
   double symplastPathLengthAverage;
   double symplastPathLengthShortest;
   double symplastPathLengthLongest;


   void PathLengthDataOutputCalculate( rsEpiCortexEndoWaterPathDB *RsEpiCortexEndoWaterPathDB );

   void AllDataOutput( double baseRadius, double totalHeight);
};

#endif // RSDATAOUTPUT_H_INCLUDED
