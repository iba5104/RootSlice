#ifndef RSEPICORTEXENDOWATERPATH_H_INCLUDED
#define RSEPICORTEXENDOWATERPATH_H_INCLUDED

#include "rsSourceCorticalDB.h"
#include "rsSourceEpidermisDB.h"

class rsEpiCortexEndoWaterPathDB : public rsBaseGeometry
{
public:

   /// Set OutputXMLVtpFileName;
   const char* ApoplastXMLVtpFileName;
   const char* SymplastXMLVtpFileName;
   void OutputXMLVtpFileName
   ( const char* ApoplastXMLVtpFileNameInput,
     const char* SymplastXMLVtpFileNameInput );

   map<int, vector<double> > epiCortexEndoCellXDB;
   map<int, vector<double> > epiCortexEndoCellYDB;
   map<int, vector<double> > epiCortexEndoCellZDB;
   void EpiCortexEndoCellXYDB
   ( rsSourceEpidermisDB *RsSourceEpidermisDB,
     rsSourceCorticalDB *RsSourceCorticalDB,
     rsSourceEpidermisDB *RsSourceEndodermisDB );

   vector<double> epiCortexEndoRingMidCentreRadiusDB;
   vector<double> epiCortexEndoRingObjectVerticalDB;
   map<int, vector<double> > epiCortexEndoRingObjectParallelDB;
   map<int, vector<double> > epiCortexEndoCellMidRotateAngleDB;
   void EpiCortexEndoRingCellDimensionDB
   ( rsSourceEpidermisDB *RsSourceEpidermisDB,
     rsSourceCorticalDB *RsSourceCorticalDB,
     rsSourceEpidermisDB *RsSourceEndodermisDB );

   vector<double> epiCortexEndoRingOuterCentreRadiusDB;
   vector<double> epiCortexEndoRingInnerCentreRadiusDB;
   void EpiCortexEndoRingCentreRadiusDB
   ( rsSourceEpidermisDB *RsSourceEpidermisDB,
     rsSourceCorticalDB *RsSourceCorticalDB,
     rsSourceEpidermisDB *RsSourceEndodermisDB );

   vector<double> epiCortexEndoRingOuterPerimeterDB;
   vector<double> epiCortexEndoRingMidPerimeterDB;
   vector<double> epiCortexEndoRingInnerPerimeterDB;
   void EpiCortexEndoRingPerimeterDB();

   map<int, vector<double> > epiCortexEndoCellHalfIntersetionAngleDB;
   void EpiCortexEndoCellHalfIntersetionAngleDB();

   map<int, vector<double> > epiCortexEndoCellLeftRotateAngleDB;
   map<int, vector<double> > epiCortexEndoCellRightRotateAngleDB;
   void EpiCortexEndoCellLeftandRightRotateAngleDB();

   map<int, vector<double> > epiCortexEndoCellLeftRadialOuterXDB;
   map<int, vector<double> > epiCortexEndoCellLeftRadialOuterYDB;
   map<int, vector<double> > epiCortexEndoCellLeftRadialMidXDB;
   map<int, vector<double> > epiCortexEndoCellLeftRadialMidYDB;
   map<int, vector<double> > epiCortexEndoCellLeftRadialInnerXDB;
   map<int, vector<double> > epiCortexEndoCellLeftRadialInnerYDB;

   map<int, vector<double> > epiCortexEndoCellRightRadialOuterXDB;
   map<int, vector<double> > epiCortexEndoCellRightRadialOuterYDB;
   map<int, vector<double> > epiCortexEndoCellRightRadialMidXDB;
   map<int, vector<double> > epiCortexEndoCellRightRadialMidYDB;
   map<int, vector<double> > epiCortexEndoCellRightRadialInnerXDB;
   map<int, vector<double> > epiCortexEndoCellRightRadialInnerYDB;

   map<int, vector<double> > epiCortexEndoCellMidRadialOuterXDB;
   map<int, vector<double> > epiCortexEndoCellMidRadialOuterYDB;
   map<int, vector<double> > epiCortexEndoCellMidRadialMidXDB;
   map<int, vector<double> > epiCortexEndoCellMidRadialMidYDB;
   map<int, vector<double> > epiCortexEndoCellMidRadialInnerXDB;
   map<int, vector<double> > epiCortexEndoCellMidRadialInnerYDB;
   void EpiCortexEndoCellXYDB();

   map<int, vector<double> > epiCortexEndoApoplastCellMarkerDB;
   map<int, vector<double> > epiCortexEndoApoplastCellMarkerLeftRightIndexDB;
   map<int, vector<double> > epiCortexEndoSymplastCellMarkerDB;
   void EpiCortexEndoCellMarkerDB();

   map<int, vector<double> > epiCortexEndoApoplastXDB;
   map<int, vector<double> > epiCortexEndoApoplastYDB;
   map<int, vector<double> > epiCortexEndoApoplastZDB;

   map<int, vector<double> > epiCortexEndoSymplastXDB;
   map<int, vector<double> > epiCortexEndoSymplastYDB;
   map<int, vector<double> > epiCortexEndoSymplastZDB;
   void EpiCortexEndoPathXYDB();

   map<int, vector<int> > recordCoincidentPointsPositionDB;
   void RecordCoincidentPoints();

   void DeleteCoincidentPoints();

   map<int, vector<double> > epiCortexEndoApoplastUpZDB;
   map<int, vector<double> > epiCortexEndoApoplastDownZDB;
   map<int, vector<double> > epiCortexEndoSymplastUpZDB;
   map<int, vector<double> > epiCortexEndoSymplastDownZDB;
   void EpiCortexEndoPathZDB();

   vector<double> epiCortexEndoApoplastPathLengthDB;
   vector<double> epiCortexEndoSymplastPathLengthDB;

   double apoplastPathLengthTotal;
   double apoplastPathLengthAverage;
   double apoplastPathLengthShortest;
   double apoplastPathLengthLongest;
   double apoplastPathLengthDeviation;

   double symplastPathLengthTotal;
   double symplastPathLengthAverage;
   double symplastPathLengthShortest;
   double symplastPathLengthLongest;
   double symplastPathLengthDeviation;
   void EpiCortexEndoPathLengthDB();

   map<int, vector<double> > epiCortexEndoApoplastTriangleStripXDB;
   map<int, vector<double> > epiCortexEndoApoplastTriangleStripYDB;
   map<int, vector<double> > epiCortexEndoApoplastTriangleStripZDB;
   map<int, vector<double> > epiCortexEndoSymplastTriangleStripXDB;
   map<int, vector<double> > epiCortexEndoSymplastTriangleStripYDB;
   map<int, vector<double> > epiCortexEndoSymplastTriangleStripZDB;
   void EpiCortexEndoPathTriangleStripXYZDB();

   void InitAllDB
   (rsSourceEpidermisDB *RsSourceEpidermisDB,
    rsSourceCorticalDB *RsSourceCorticalDB,
    rsSourceEpidermisDB *RsSourceEndodermisDB
   );

};




#endif // RSEPICORTEXENDOWATERPATH_H_INCLUDED
