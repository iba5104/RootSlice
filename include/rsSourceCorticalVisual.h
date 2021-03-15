#ifndef RSSOURCECORTICALVISUAL_H_INCLUDED
#define RSSOURCECORTICALVISUAL_H_INCLUDED

#include "rsSourceCorticalDB.h"
#include "rsBaseGeometry.h"

#include "vtkParametricSuperEllipsoid.h"
#include "vtkParametricFunctionSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkProperty.h"

#include "vtkSmartPointer.h"
#include <vtkAppendPolyData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkPolyData.h>
#include <vtkCellData.h>
#include "vtkPointData.h"
#include <vtkPoints.h>
#include "vtkFloatArray.h"

class rsSourceCorticalVisual : public rsBaseGeometry
{
public:

   double colorR, colorG, colorB;
   double opacity;

   ///////////////// Calculate Cortical Object Total; //////////////////////////
   //void CorticalVisualInit();

   void CorticalVisual
   ( rsSourceCorticalDB *CorticalDB,
     vtkSmartPointer<vtkRenderer> renL );

   void VacuoleVisual
   ( rsSourceCorticalDB *CorticalDB,
     vtkSmartPointer<vtkRenderer> renL );

};

#endif // RSSOURCECORTICALVISUAL_H_INCLUDED
