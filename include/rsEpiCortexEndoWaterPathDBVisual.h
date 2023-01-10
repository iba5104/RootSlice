#ifndef RSEPICORTEXENDOWATERPATHDBOUTPUT_H_INCLUDED
#define RSEPICORTEXENDOWATERPATHDBOUTPUT_H_INCLUDED

#include "globals.h"
#include "rsEpiCortexEndoWaterPathDB.h"
#include "fluxEqns.h"

#include <vtkSmartPointer.h>

#include <vtkTriangleStrip.h>
#include <vtkAppendPolyData.h>
#include <vtkPolyData.h>
#include <vtkCellData.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkTubeFilter.h>

#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

#include <vtkXMLPolyDataWriter.h>

class rsEpiCortexEndoWaterPathDBVisual : public globals
{
public:

void ApoplastTriangleStripXMLVtp( rsEpiCortexEndoWaterPathDB * RsEpiCortexEndoWaterPathDB, globals surfaceFlux);
void SymplastTriangleStripXMLVtp( rsEpiCortexEndoWaterPathDB * RsEpiCortexEndoWaterPathDB, globals surfaceFlux );
void ApoplastTubeXMLVtp( rsEpiCortexEndoWaterPathDB * RsEpiCortexEndoWaterPathDB );
void SymplastTubeXMLVtp( rsEpiCortexEndoWaterPathDB * RsEpiCortexEndoWaterPathDB );
};

#endif // RSEPICORTEXENDOWATERPATHDBOUTPUT_H_INCLUDED
