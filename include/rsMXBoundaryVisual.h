#ifndef RSMXBOUNDARYVISUAL_H_INCLUDED
#define RSMXBOUNDARYVISUAL_H_INCLUDED

#include "globals.h"
#include "rsMXCoreVisual.h"

class rsMXBoundaryVisual : public globals
{
public:

   void MXBoundaryCellVisual
   (   rsMXBoundaryOutDB *RsMXBoundaryOutDB,
       vtkSmartPointer<vtkRenderer> renL );

};

#endif // RSMXBOUNDARYVISUAL_H_INCLUDED
