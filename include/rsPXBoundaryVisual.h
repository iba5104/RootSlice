#ifndef RSPXBOUNDARYVISUAL_H_INCLUDED
#define RSPXBOUNDARYVISUAL_H_INCLUDED

#include "globals.h"
#include "rsPXCoreVisual.h"

class rsPXBoundaryVisual : public globals
{
public:

   void BoundaryCellVisual
   (   rsPXBoundaryDB *RsPXBoundaryDB,
       vtkSmartPointer<vtkRenderer> renL );

};

#endif // RSPXBOUNDARYVISUAL_H_INCLUDED
