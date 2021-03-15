#ifndef RSMXCoreDB_H_INCLUDED
#define RSMXCoreDB_H_INCLUDED

#include "rsBaseGeometryMX.h"

/*************************************************
// Need to input:
totalNum = 5
averageRingRadius = 40
centerXYRadius = 70
eachRingMaxOutRingNum = 3
eachRingMaxOutRingAddRadius = 3
eachRingMaxOutRingCellNum = 20
**************************************************/

class rsMXCoreDB : public rsBaseGeometryMX
{
public:

   /// Calculate xylemOutRingAddRadiusDB and xylemOutRingCellNumDB;
   map<int, vector<double> > xylemOutRingAddRadiusDB;
   map<int, vector<int> > xylemOutRingCellNumDB;
   void XylemOutRingDB( double xylemMaxOutRingNum,
                        double xylemMaxOutRingCellNum,
                        double xylemMaxOutRingAddRadius );

   /// Get mxBoundaryRadiusDB;
   vector<double> boundaryRadiusDB;
   void BoundaryRadiusDB();

   /// Get mxMaxBoundaryRadius;
   double mxMaxBoundaryRadius;
   void MXMaxBoundaryRadius();

   /// Get centerXYRadiusDB;
   vector<double> centerXYRadiusDB;
   void CenterXYRadiusDB();

   /// Get CenterXYPosition;
   vector<double> centerX;
   vector<double> centerY;
   void CenterXYPosition();

   /// Calculate the xylemOutRingAppendAddRadiusDB;
   map<int, vector<double> > xylemOutRingAppendAddRadiusDB;
   void XylemOutRingAppendAddRadiusDB();

   /// Create xylemOutRingCircleRadiusDB for each xylem;
   map<int, vector<double> > xylemOutRingCircleRadiusDB;
   void XylemOutRingCircleRadiusDB();

   /// Create XylemOutRingObjectVerticalDB;
   map<int, vector<double> > xylemOutRingObjectVerticalDB;
   void XylemOutRingObjectVerticalDB();

   /// create map RandomHeightDB;
   map<int, vector<double> > longitudeSegmentHeightDB;
   map<int, vector<double> > longitudeZPositionAddDB;
   void RandomHeightDB( double totalHeight, int sliceNum, double initZPosition, int VectorNum );

   /// GetRandomCircleSegmentAndCircleXYNonuniformDB
   map<int, vector< vector<double> > > xylemOutRingCircleSegmentLengthDB;
   map<int, vector<double> > xylemOutRingCircleSegmentLengthSumDB;
   map<int, vector< vector<double> > > xylemOutRingCircleSegmentRotateAngleDB;
   map<int, vector< vector<double> > > xylemOutRingCircleXDB;
   map<int, vector< vector<double> > > xylemOutRingCircleYDB;
   void XylemOutRingCircleSegmentAndCircleXYDB( double variationRatio );

   /// Add centerX and centerY;
   void XylemOutRingAddCenterXY();

   /// Get new xylemOutRingCircleSegmentLengthDB after adjustment of ratio;
   void XylemOutRingCircleSegmentLengthAdjustRatioDB();

   /// Get ObjectHeightDB and ObjectZPositionDB of Xylem Out Ring;
   map<int, vector< vector <vector<double> > > > xylemOutRingObjectHeightDB;
   map<int, vector< vector <vector<double> > > > xylemOutRingObjectZPositionDB;
   void XylemOutRingObjectHeightAndZPositionDB( int sliceNum );

   /// Get ObjectHeightDB and ObjectZPositionDB of Xylem Center Ring;
   map<int, vector<double> > xylemCenterRingObjectHeightDB;
   map<int, vector<double> > xylemCenterRingObjectZPositionDB;
   void XylemCenterRingObjectHeightAndZPositionDB( int sliceNum );

   /// Initialize Xylem OutRing
   void InitXylemOutRing
   (  rsPXCoreDB *RsPXCoreDB,
      int setMXNum,
      double setMXAverageRingRadius,
      double variationRatio,
      double xylemMaxOutRingNum,
      double xylemMaxOutRingCellNum,
      double xylemMaxOutRingAddRadius,
      int setUResolution,
      int setVResolution,
      int setWResolution,
      int sliceNum );

};

#endif // RSMXCoreDB_H_INCLUDED

