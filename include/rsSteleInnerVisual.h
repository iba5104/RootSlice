#ifndef RSSTELEINNERVISUAL_H_INCLUDED
#define RSSTELEINNERVISUAL_H_INCLUDED

#include "rsSourceCorticalVisual.h"
#include "rsSteleInnerDB.h"
#include "rsBaseGeometry.h"

class rsSteleInnerVisual
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
