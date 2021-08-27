#ifndef RSDYNAMICDATAOUTPUT_H_INCLUDED
#define RSDYNAMICDATAOUTPUT_H_INCLUDED

#include "tinyxml.h"
#include "viStringTokenizer.h"

#include <iostream>
#include <map>
#include <vector>
#include <math.h>

#include "vtkRenderLargeImage.h"
#include "vtkJPEGWriter.h"
#include "vtkAVIWriter.h"
#include "vtkWindowToImageFilter.h"
#include "vtkCamera.h"
#include "vtkLight.h"

#include "rsBaseGeometry.h"

#include "rsSourceCorticalDB.h"
#include "rsSourceCorticalVisual.h"

#include "rsRcaDB.h"

#include "rsDataOutput.h"

#include "rsSourceDermisDB.h"
#include "rsSourceDermisVisual.h"

#include "rsEpiCortexEndoWaterPathDB.h"
#include "rsEpiCortexEndoWaterPathDBVisual.h"

#include "rsMXBoundaryOutDB.h"
#include "rsMXCoreVisual.h"
#include "rsMXBoundaryVisual.h"
#include "rsMXBoundaryOutVisual.h"

#include "rsPXBoundaryDB.h"
#include "rsPXCoreVisual.h"
#include "rsPXBoundaryVisual.h"

#include "rsPhloemDB.h"
#include "rsPhloemVisual.h"

#include "rsSteleInnerDB.h"
#include "rsSteleInnerVisual.h"

class rsDynamicDataOutput
{
public:

   void SetRenderer( vtkSmartPointer<vtkRenderer> renL );

   void InitEpiCortexEndoAllDB
   (
      int setUResolution,
      int setVResolution,
      int setWResolution,
      double baseRadius,
      double thickness,
      double totalHeight,
      /// Cortical;
      vector<double> corticalAddRadiusInputData,
      vector<int> corticalCellNumInputData,
      int corticalAddRadiusDBSelectInput,

      int corticalCellNumSelectInput,
      int corticalSliceNum,
      double initZPosition,
      int vectorNum,
      double variationRatioCotical,
      int cortexLayerNum,
      double corticalCellMultiplyRatio,
      double corticalCellAddRadiusMinInput,
      double cortexRadiusInput,
      /// RCA;
      double rcaRatioInput,
      int rcaNumInput,
      int standardOuterLayerInput,
      int standardInnerLayerInput,
      double gapAngleBetweenRcaRatio,
      double variationRatioRca,

      /// Pure Cortical Cell;
      double gapCellWallInput,

      /// Cortical Vacuole;
      double gapCytoTono,

      /// Plasma Membrane
      double plasmaMembraneWidth,

       /// Sclerenchyma
       int sclerenSliceNum,
       double sclerenAddRadiusData,

      /// Epi;
      int epidermisSliceNum,
      double epidermisAddRadiusData,
//      int epidermisCellNum,
      double variationRatioDermis,

      /// Endo;
      int endodermisSliceNum,
      double endodermisAddRadiusData,
//      int endodermisCellNum,
      
      // Pericycle
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

      /// Others
      vtkSmartPointer<vtkRenderer> renL
   );


   void InitEpiCortexEndoNonRCADB
   (
      int setUResolution,
      int setVResolution,
      int setWResolution,
      double baseRadius,
      double thickness,
      double totalHeight,
      /// Cortical;
      vector<double> corticalAddRadiusInputData,
      vector<int> corticalCellNumInputData,
      int corticalAddRadiusDBSelectInput,

      int corticalCellNumSelectInput,
      int corticalSliceNum,
      double initZPosition,
      int vectorNum,
      double variationRatioCotical,
      int cortexLayerNum,
      double corticalCellMultiplyRatio,
      double corticalCellAddRadiusMinInput,
      double cortexRadiusInput,

      /// Pure Cortical Cell;
      double gapCellWallInput,

      /// Cortical Vacuole;
      double gapCytoTono,

       /// Plasma Membrane
       double plasmaMembraneWidth,

      /// Sclerenchyma
      int sclerenSliceNum,
      double sclerenAddRadiusData,

      /// Epi;
      int epidermisSliceNum,
      double epidermisAddRadiusData,
//      int epidermisCellNum,
      double variationRatioDermis,

      /// Endo;
      int endodermisSliceNum,
      double endodermisAddRadiusData,
//      int endodermisCellNum,
      
       // Pericycle
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

      /// Others
      vtkSmartPointer<vtkRenderer> renL,
       double variationRatio,
       int sliceNum,
       double steleInnestCellRadiusInput,
       int steleInnerLayerNumInput,
       double setUpVecticalLengthThresholdRatio,
       double innerTangentRingRadiusRatioTemp,
       int setInterVerticalNum,
       int setMXNum,
       double setMXAverageRingRadius,
       double xylemMaxOutRingNum,
       double pxGapRadius,
       int setPXNum,
       double setPXAverageRingRadius,
       double xylemMaxOutRingCellNum,
       double xylemMaxOutRingAddRadius
   );


   void RenderTogether( vtkSmartPointer<vtkRenderer> renL );

};


#endif // RSDYNAMICDATAOUTPUT_H_INCLUDED
