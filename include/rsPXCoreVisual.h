#ifndef RSPXCOREVISUAL_H_INCLUDED
#define RSPXCOREVISUAL_H_INCLUDED

#include "rsPXBoundaryDB.h"
#include "rsSourceCorticalVisual.h"

#include "vtkCylinderSource.h"
//#include "vtkParametricSuperEllipsoid.h"
//#include "vtkParametricFunctionSource.h"
//#include "vtkPolyDataMapper.h"
//#include "vtkRenderWindow.h"
//#include "vtkRenderWindowInteractor.h"
//#include "vtkCamera.h"
//#include "vtkActor.h"
//#include "vtkRenderer.h"
//#include "vtkInteractorStyleTrackballCamera.h"
//#include "vtkProperty.h"

#include "vtkSmartPointer.h"

class rsPXCoreVisual
{
public:

   ///////////////// Calculate Cortical Object Total; //////////////////////////
   //
   void PXCoreVisual
   ( rsPXBoundaryDB *RsPXBoundaryDB,
     vtkSmartPointer<vtkRenderer> renL );

   void PXCenterRingVisual
   ( rsPXBoundaryDB *RsPXBoundaryDB,
     vtkSmartPointer<vtkRenderer> renL );

   void PXSmallVisual
   ( rsPXBoundaryDB *RsPXBoundaryDB,
     vtkSmartPointer<vtkRenderer> renL );

};

#endif // RSPXCOREVISUAL_H_INCLUDED
