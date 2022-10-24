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
#include "fluxEqns.h"
#include "globals.h"
#include "resources.h"

class rsDynamicDataOutput : public globals
{
public:

   void SetRenderer( vtkSmartPointer<vtkRenderer> renL );

   void InitEpiCortexEndoAllDB
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

       //Other
       vtkSmartPointer<vtkRenderer> renL
   );


   void InitEpiCortexEndoNonRCADB
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
      const char* dataOutputNameInput, //Other
       vtkSmartPointer<vtkRenderer> renL
   );

   void RenderTogether( vtkSmartPointer<vtkRenderer> renL );

   void InitInnertructure(
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
   );

};


#endif // RSDYNAMICDATAOUTPUT_H_INCLUDED
