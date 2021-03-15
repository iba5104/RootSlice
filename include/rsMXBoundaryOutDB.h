#ifndef RSMXBOUNDARYOUTDB_H_INCLUDED
#define RSMXBOUNDARYOUTDB_H_INCLUDED

#include "rsMXBoundaryDB.h"

class rsMXBoundaryOutDB : public rsMXBoundaryDB
{
public:
///////////////////////////////////// BoundaryInter /////////////////////////////////////////////
   double tangentRingRadius;
   void TangentRingRadius();

   double innerRingRadius;
   void InnerRingRadius( double innerTangentRingRadiusRatioTemp );

   double interVerticalNum;
   void InterVerticalNum( int setInterVerticalNum );

   double interVerticalLengthTotal;
   void InterVerticalLengthTotal();

   double interVerticalLengthAverage;
   void InterVerticalLengthAverage();

   vector<double> interVerticalLengthDB;
   vector<double> interVerticalLengthAddDB;
   void InterVerticalLengthDB( double variationRatio );

   vector<double> interVerticalLengthHalfDB;
   void InterVerticalLengthHalfDB();

   vector<double> interVerticalCenterRadiusDB;
   void InterVerticalCenterRadiusDB();

   vector<double> interRadianStartDB;
   vector<double> interRadianEndDB;
   vector<double> interIntersectionRadianDB;
   void InterRadianStartAndEndDB();

   map<int, vector<double> > interParallelPerimeterDB;
   void InterParallelPerimeterDB();

   map<int, vector<double> > interParallelNumDB;
   void InterParallelNumDB();

   map<int, vector<double> > interParallelLengthDB;
   void InterParallelLengthDB();

   map<int, vector<double> > interParallelLengthHalfDB;
   void InterParallelLengthHalfDB();

   map<int, vector<double> > interIntersectionRadianDivideDB;
   void InterParallelRadianDivideDB();

   map<int, vector<vector<double> > > interCellCenterRadianDB;
   void InterCellCenterRadianDB();

   map<int, vector<vector<double> > > interCellCenterRotateAngleDB;
   void InterCellCenterRotateAngleDB();

   map<int, vector<vector<double> > > interCellXDB;
   map<int, vector<vector<double> > > interCellYDB;
   void InterCellXYDB();

/// InterCellObjectHeightAndZPositionDB
   map<int, vector<vector<vector<double> > > > interCellObjectHeightDB;
   map<int, vector<vector<vector<double> > > > interCellObjectZPositionDB;
   void InterCellObjectHeightAndZPositionDB( int sliceNum );

   void InitBoundaryInterDB
   (  double innerTangentRingRadiusRatioTemp,
      int setInterVerticalNum,
      double variationRatio,
      int sliceNum );
///////////////////////////////////// BoundaryUp /////////////////////////////////////////////
   vector<double> upVerticalLengthTotalDB;
   void UpVerticalLengthTotalDB();

   double upVecticalLengthThreshold;
   void UpVecticalLengthThreshold( double setUpVecticalLengthThresholdRatio );

   vector<double> upVerticalNum;
   void UpVerticalNum();

   vector<double> upVerticalLengthAverageDB;
   void UpVerticalLengthAverageDB();

   map<int, vector<double> > upVerticalLengthDB;
   map<int, vector<double> > upVerticalLengthAddDB;
   void UpVerticalLengthDB( double variationRatio );

   map<int, vector<double> > upVerticalLengthHalfDB;
   void UpVerticalLengthHalfDB();

   map<int, vector<double> > upVerticalCenterRadiusDB;
   void UpVerticalCenterRadiusDB();

   map<int, vector<double> > upParallelPerimeterDB;
   void UpParallelPerimeterDB();

   map<int, vector<double> > upParallelNumDB;
   void UpParallelNumDB();

   map<int, vector<double> > upParallelLengthDB;
   void UpParallelLengthDB();

   map<int, vector<double> > upParallelLengthHalfDB;
   void UpParallelLengthHalfDB();

   map<int, vector<double> > upIntersectionRadianDivideDB;
   void UpParallelRadianDivideDB();

   map<int, vector<vector<double> > > upCellCenterRadianDB;
   void UpCellCenterRadianDB();

   map<int, vector<vector<double> > > upCellCenterRotateAngleDB;
   void UpCellCenterRotateAngleDB();

   map<int, vector<vector<double> > > upCellXDB;
   map<int, vector<vector<double> > > upCellYDB;
   void UpCellXYDB();

/// UpCellObjectHeightAndZPositionDB
   map<int, vector<vector<vector<double> > > > upCellObjectHeightDB;
   map<int, vector<vector<vector<double> > > > upCellObjectZPositionDB;
   void UpCellObjectHeightAndZPositionDB( int sliceNum );

   void InitBoundaryUpDB
   (  double setUpVecticalLengthThresholdRatio,
      double variationRatio,
      int sliceNum );
};

#endif // RSMXBOUNDARYOUTDB_H_INCLUDED
