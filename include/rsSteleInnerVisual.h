#ifndef RSSTELEINNERVISUAL_H_INCLUDED
#define RSSTELEINNERVISUAL_H_INCLUDED

#include "rsSourceCorticalVisual.h"
#include "rsSteleInnerDB.h"
#include "rsBaseGeometry.h"
#include "globals.h"

class rsSteleInnerVisual : public globals
{
public:

   void SteleInnerVisual
   ( rsSteleInnerDB *RsSteleInnerDB,
     vtkSmartPointer<vtkRenderer> renL );

   void SteleInnestVisual
   ( rsSteleInnerDB *RsSteleInnerDB,
     vtkSmartPointer<vtkRenderer> renL );

};

#endif // RSSTELEINNERVISUAL_H_INCLUDED
