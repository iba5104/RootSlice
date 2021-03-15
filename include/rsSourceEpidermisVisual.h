#ifndef RSSOURCEEPIDERMISVISUAL_H_INCLUDED
#define RSSOURCEEPIDERMISVISUAL_H_INCLUDED

#include "rsSourceEpidermisDB.h"
#include "rsSourceCorticalVisual.h"

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
//#include "vtkSmartPointer.h"

class rsSourceEpidermisVisual
{
public:

   double colorR, colorG, colorB;
   double opacity;

   ///////////////// Calculate Cortical Object Total; //////////////////////////
   //
   void EpidermisVisual
   ( rsSourceEpidermisDB *EpidermisDB,
     vtkSmartPointer<vtkRenderer> renL );

};

#endif // RSSOURCEEPIDERMISVISUAL_H_INCLUDED
