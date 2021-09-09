#ifndef RSPHLOEMVISUAL_H_INCLUDED
#define RSPHLOEMVISUAL_H_INCLUDED

#include "globals.h"
#include "rsPhloemDB.h"
#include "rsSourceCorticalVisual.h"

//#include "vtkCylinderSource.h"
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

class rsPhloemVisual : public globals
{
public:
   void UpAppendCellVisual
   ( rsPhloemDB *RsPhloemDB,
     vtkSmartPointer<vtkRenderer> renL );

   void UpPhloemCellVisual
   ( rsPhloemDB *RsPhloemDB,
     vtkSmartPointer<vtkRenderer> renL);

   void DownCellVisual
   ( rsPhloemDB *RsPhloemDB,
     vtkSmartPointer<vtkRenderer> renL );
};

#endif // RSPHLOEMVISUAL_H_INCLUDED
