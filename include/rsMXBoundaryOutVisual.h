#ifndef RSMXBOUNDARYOUTVISUAL_H_INCLUDED
#define RSMXBOUNDARYOUTVISUAL_H_INCLUDED

#include "rsMXCoreVisual.h"

class rsMXBoundaryOutVisual
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
