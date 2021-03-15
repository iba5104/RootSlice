#ifndef RSEPICORTEXENDOWATERPATHDBOUTPUT_H_INCLUDED
#define RSEPICORTEXENDOWATERPATHDBOUTPUT_H_INCLUDED

#include "rsEpiCortexEndoWaterPathDB.h"

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

class rsEpiCortexEndoWaterPathDBVisual
{
public:

void ApoplastTriangleStripXMLVtp( rsEpiCortexEndoWaterPathDB * RsEpiCortexEndoWaterPathDB );
void SymplastTriangleStripXMLVtp( rsEpiCortexEndoWaterPathDB * RsEpiCortexEndoWaterPathDB );
void ApoplastTubeXMLVtp( rsEpiCortexEndoWaterPathDB * RsEpiCortexEndoWaterPathDB );
void SymplastTubeXMLVtp( rsEpiCortexEndoWaterPathDB * RsEpiCortexEndoWaterPathDB );
};

#endif // RSEPICORTEXENDOWATERPATHDBOUTPUT_H_INCLUDED
