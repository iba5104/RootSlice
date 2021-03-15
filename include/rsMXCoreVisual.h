#ifndef RSMXCoreVISUAL_H_INCLUDED
#define RSMXCoreVISUAL_H_INCLUDED


#include "rsMXBoundaryOutDB.h"
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
#include <math.h>

#include "vtkSmartPointer.h"

using namespace std;

class rsMXCoreVisual
{
public:

   ///////////////// Visual //////////////////////////
   //
   void MXVisual( rsMXBoundaryOutDB *RsMXBoundaryOutDB, vtkSmartPointer<vtkRenderer> renL );

   void MXCenterRingVisual
   (  rsMXBoundaryOutDB *RsMXBoundaryOutDB,
      vtkSmartPointer<vtkRenderer> renL );
};




#endif // RSMXCoreVISUAL_H_INCLUDED
