#ifndef RSSOURCEEPIDERMISVISUAL_H_INCLUDED
#define RSSOURCEEPIDERMISVISUAL_H_INCLUDED

#include "rsSourceDermisDB.h"
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

class rsSourceDermisVisual
{
public:

   double colorR, colorG, colorB;
   double opacity;

   ///////////////// Calculate Cortical Object Total; //////////////////////////
   //
   void EpidermisVisual
   ( rsSourceDermisDB *EpidermisDB,
     vtkSmartPointer<vtkRenderer> renL,
     int vacuolePlasmaFlag );

};

#endif // RSSOURCEEPIDERMISVISUAL_H_INCLUDED
