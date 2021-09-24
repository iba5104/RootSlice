#ifndef RSPXCOREDB_H_INCLUDED
#define RSPXCOREDB_H_INCLUDED

#include "rsBaseGeometryPX.h"

class rsPXCoreDB : public rsBaseGeometryPX
{
public:
   /// Calculate xylemOutRingAddRadiusDB and xylemOutRingCellNumDB;
   map<int, double> xylemOutRingAddRadiusDB;
   map<int, int> xylemOutRingCellNumDB;
   void XylemOutRingDB( double xylemMaxOutRingCellNum,
                        double xylemMaxOutRingAddRadius );

   /// Get pxMaxBoundaryRadius;
   double pxMaxBoundaryRadius;
   void PXMaxBoundaryRadius();

   /// Get boundaryMXPXRingRadius
   double boundaryMXPXRingRadius;
   double BoundaryMXPXRingRadius();

   /// Get centerXYRadiusDB;
   vector<double> centerXYRadiusDB;
   void CenterXYRadiusDB();

   /// Get CenterXYPosition;
   vector<double> centerX;
   vector<double> centerY;
   void CenterXYPosition();


/// Create xylemOutRingCircleRadiusDB for each xylem;
   map<int, double> xylemOutRingCircleRadiusDB;
   void XylemOutRingCircleRadiusDB();

/// Create XylemOutRingObjectVerticalDB;
   map<int, double> xylemOutRingObjectVerticalDB;
   void XylemOutRingObjectVerticalDB();

/// Create RandomHeightDB;
   map<int, vector<double> > longitudeSegmentHeightDB;
   map<int, vector<double> > longitudeZPositionAddDB;
   void RandomHeightDB( double totalHeight, int sliceNum, double initZPosition, int VectorNum );

/// GetRandomCircleSegmentAndCircleXYNonuniformDB
   map<int, vector<double> > xylemOutRingCircleSegmentLengthDB;
   map<int, double> xylemOutRingCircleSegmentLengthSumDB;
   map<int, vector<double> > xylemOutRingCircleSegmentRotateAngleDB;
   map<int, vector<double> > xylemOutRingCircleXDB;
   map<int, vector<double> > xylemOutRingCircleYDB;
   void XylemOutRingCircleSegmentAndCircleXYDB( double variationRatio );


///Add centerX and centerY to XylemOutRing;
   void XylemOutRingAddCenterXY();


/// Get new xylemOutRingCircleSegmentLengthDB after adjustment of ratio;
   void XylemOutRingCircleSegmentLengthAdjustRatioDB();

/// Get ObjectHeightDB and ObjectZPositionDB;
   map<int, vector <vector<double> > > xylemOutRingObjectHeightDB;
   map<int, vector <vector<double> > > xylemOutRingObjectZPositionDB;
   void XylemOutRingObjectHeightAndZPositionDB( int sliceNum );

/// Get ObjectHeightDB and ObjectZPositionDB of Xylem Center Ring;
   map<int, vector<double> > xylemCenterRingObjectHeightDB;
   map<int, vector<double> > xylemCenterRingObjectZPositionDB;
   void XylemCenterRingObjectHeightAndZPositionDB( int sliceNum );

/// Initialize other Database;
   void InitXylemOutRing( double endodermisBaseRadius,
                          double pxGapRadius,
                          int setPXNum,
                          double setPXAverageRingRadius,
                          double variationRatio,
                          double xylemMaxOutRingCellNum,
                          double xylemMaxOutRingAddRadius,
                          int sliceNum );

//////////////////////////// PXSmall //////////////////////////////////////
/// Get boundaryRadiusDB
   vector<double> boundaryRadiusDB;
   void BoundaryRadiusDB();
/// Get boundaryMaxAndMinCenterRadiusDB;
   map<int, double> boundaryMaxCenterRadiusDB;
   map<int, double> boundaryMinCenterRadiusDB;
   void BoundaryMaxAndMinCenterRadiusDB();

/// EachRingMaxAndMinRadius
   double eachRingMaxRadius;
   double eachRingMinRadius;
   void EachRingMaxAndMinRadius();

/// Get pxSmallRadiusDB
   vector<double> pxSmallVerticalRadiusDB;
   vector<double> pxSmallParallelRadiusDB;
   void PXSmallVerticalAndParallelRadiusDB();

/// Get centerXYRadiusPXSmallDB
   map<int, double> centerXYRadiusPXSmallDB;
   void CenterXYRadiusPXSmallDB();

/// Get centerXYPXSmall;
   vector<double> centerXPXSmall;
   vector<double> centerYPXSmall;
   void CenterXYPXSmall();

/// Get ObjectHeightDB and ObjectZPositionDB of PXSmall Center Ring;
   map<int, vector<double> > pxSmallCenterRingObjectHeightDB;
   map<int, vector<double> > pxSmallCenterRingObjectZPositionDB;
   void PXSmallCenterRingObjectHeightAndZPositionDB();

/// Initialize PXSmall;
   void InitPXSamll();

};


#endif // RSPXCOREDB_H_INCLUDED
