#ifndef RSSOURCEEPIDERMISVISUAL_H_INCLUDED
#define RSSOURCEEPIDERMISVISUAL_H_INCLUDED

#include "globals.h"
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

class rsSourceDermisVisual : public globals
{
public:

   double colorR, colorG, colorB;
   double opacity;

   ///////////////// Calculate Cortical Object Total; //////////////////////////
   //
   void EpidermisVisual
   ( rsSourceDermisDB *EpidermisDB,
     vtkSmartPointer<vtkRenderer> renL,
     int vacuolePlasmaFlag,
     vector<double> result,
       string filePrefix);

};

#endif // RSSOURCEEPIDERMISVISUAL_H_INCLUDED
