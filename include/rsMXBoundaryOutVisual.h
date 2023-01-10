#ifndef RSMXBOUNDARYOUTVISUAL_H_INCLUDED
#define RSMXBOUNDARYOUTVISUAL_H_INCLUDED

#include "globals.h"
#include "rsMXCoreVisual.h"

class rsMXBoundaryOutVisual : public globals
{
public:

   void MXBoundaryInterCellVisual
   (   rsMXBoundaryOutDB *RsMXBoundaryOutDB,
       vtkSmartPointer<vtkRenderer> renL );

   void MXBoundaryUpCellVisual
   (   rsMXBoundaryOutDB *RsMXBoundaryOutDB,
       vtkSmartPointer<vtkRenderer> renL );
};

#endif // RSMXBOUNDARYOUTVISUAL_H_INCLUDED
