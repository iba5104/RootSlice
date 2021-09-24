#ifndef RSPHLOEMDB_H_INCLUDED
#define RSPHLOEMDB_H_INCLUDED

#include "rsPXBoundaryDB.h"
#include "globals.h"

class rsPhloemDB : public rsBaseGeometry, public globals
{
public:
   /// InterRadianStartAndEndDB
   vector<double> interRadianStartDB;
   vector<double> interRadianEndDB;
   vector<double> interIntersectionRadianDB;
   void InterRadianStartAndEndDB( rsPXBoundaryDB *RsPXBoundaryDB );

   /// upVerticalLengthTotalDB
   vector<double> upVerticalLengthTotalDB;
   void UpVerticalLengthTotalDB( rsPXBoundaryDB *RsPXBoundaryDB );

   ///phloemVerticalLengthHalfDB;
   vector<double> phloemVerticalLengthHalfDB;
   void PhloemVerticalLengthHalfDB();

   /// upAppendVerticalLengthDB
   vector<double> upAppendVerticalLengthDB;
   void UpAppendVerticalLengthDB();

   /// upAppendVerticalLengthHalfDB
   vector<double> upAppendVerticalLengthHalfDB;
   void UpAppendVerticalLengthHalfDB();

/// boundaryMXPXRingRadiusDeliver
   double boundaryMXPXRingRadiusDeliver;
   void BoundaryMXPXRingRadiusDeliver( rsPXBoundaryDB *RsPXBoundaryDB );

   /// upFirstCenterRadius upSecondCenterRadius;
   vector<double> upFirstPhloemCenterRadiusDB;
   vector<double> upSecondPhloemCenterRadiusDB;
   void PhloemCenterRadius();

/// upFirstSecondPhloemParallelNumDB
   vector<int> upFirstPhloemParallelNumDB;
   vector<int> upSecondPhloemParallelNumDB;
   void UpFirstSecondPhloemParallelNumDB();

/// phloemRadianRatioDB
   vector<double> phloemRadianRatioDB;
   void PhloemRadianRatioDB();

/// upFirstSecondPhloemParallelRadianTotalDB
   vector<double> upFirstPhloemParallelRadianTotalDB;
   vector<double> upSecondPhloemParallelRadianTotalDB;
   void UpFirstSecondPhloemParallelRadianTotalDB();

/// upAppendCenterRadiusDB
   map<int, vector<double> > upAppendCenterRadiusDB;
   void UpAppendCenterRadiusDB();

/// upFirstSecondAppendParallelRadianTotalDB
   vector<double> upFirstAppendParallelRadianTotalDB;
   vector<double> upSecondAppendParallelRadianTotalDB;
   void UpFirstSecondAppendParallelRadianTotalDB();

/// upAppendParallelStartAndEndRadianTotalRatioDB
   vector<double> upAppendParallelStartAndEndRadianTotalRatioDB;
   void UpAppendParallelRadianTotalRatioDB();

/// upFirstSecondAppendParallelStartAndEndRadianTotalDB;
   vector<double> upFirstAppendParallelStartRadianTotalDB;
   vector<double> upFirstAppendParallelEndRadianTotalDB;
   vector<double> upSecondAppendParallelStartRadianTotalDB;
   vector<double> upSecondAppendParallelEndRadianTotalDB;
   void UpFirstSecondAppendParallelStartAndEndRadianTotalDB();

/// upAppendParallelStartAndEndRadianTotal
   map<int, vector<double> > upAppendParallelStartRadianTotalDB;
   map<int, vector<double> > upAppendParallelEndRadianTotalDB;
   void UpAppendParallelRadianTotal();

/// upAppendParallelStartAndEndLengthTotalDB
   map<int, vector<double> > upAppendParallelStartLengthTotalDB;
   map<int, vector<double> > upAppendParallelEndLengthTotalDB;
   void UpAppendParallelLengthTotalDB();

/// upFirstSecondParallelLengthTotalDB
   vector<double> upFirstParallelLengthTotalDB;
   vector<double> upSecondParallelLengthTotalDB;
   void UpParallelLengthTotalDB();

/// upAppendParallelLengthThresholdDB
   vector<double> upAppendParallelLengthThresholdDB;
   void UpAppendParallelLengthThresholdDB( double setUpAppendParallelLengthThresholdRatio );

/// upAppendParallelStartAndEndNumDB
   map<int, vector<double> > upAppendParallelStartNumDB;
   map<int, vector<double> > upAppendParallelEndNumDB;
   void UpAppendParallelNumDB();

/// upAppendParallelStartAndEndLengthDB
   map<int, vector<double> > upAppendParallelStartLengthHalfDB;
   map<int, vector<double> > upAppendParallelEndLengthHalfDB;
   void UpAppendParallelLengthHalfDB();

/// upAppendParallelStartAndEndRadianDevideDB
   map<int, vector<double> > upAppendParallelStartRadianDevideDB;
   map<int, vector<double> > upAppendParallelEndRadianDevideDB;
   void UpAppendParallelRadianDevideDB();

/// upAppendParallelStartAndEndCenterRadianDB
   map<int, vector<vector<double> > >  upAppendParallelStartCenterRadianDB;
   map<int, vector<vector<double> > >  upAppendParallelEndCenterRadianDB;
   void UpAppendParallelCenterRadianDB();

/// UpAppendParallelStartAndEndCenterRotateAngleDB
   map<int, vector<vector<double> > >  upAppendParallelStartCenterRotateAngleDB;
   map<int, vector<vector<double> > >  upAppendParallelEndCenterRotateAngleDB;
   void UpAppendParallelCenterRotateAngleDB();

/// UpAppendCellXYDB
   map<int, vector<vector<double> > > upAppendStartCellXDB;
   map<int, vector<vector<double> > > upAppendStartCellYDB;
   map<int, vector<vector<double> > > upAppendEndCellXDB;
   map<int, vector<vector<double> > > upAppendEndCellYDB;
   void UpAppendCellXYDB();

/// Create RandomHeightDB;
   map<int, vector<double> > longitudeSegmentHeightDB;
   map<int, vector<double> > longitudeZPositionAddDB;
   void RandomHeightDB( double totalHeight, int sliceNum, double initZPosition, int VectorNum );

/// UpAppendObjectHeightAndZPositionDB
   map<int, vector<vector<vector<double> > > > upAppendStartCellObjectHeightDB;
   map<int, vector<vector<vector<double> > > > upAppendStartCellObjectZPositionDB;
   map<int, vector<vector<vector<double> > > > upAppendEndCellObjectHeightDB;
   map<int, vector<vector<vector<double> > > > upAppendEndCellObjectZPositionDB;
   void UpAppendObjectHeightAndZPositionDB( int sliceNum );

///////////////////////// Phloem //////////////////////////////
   vector<double> upFirstPhloemParallelLengthTotalDB;
   vector<double> upSecondPhloemParallelLengthTotalDB;
   void UpPhloemParallelLengthTotalDB();
/// UpPhloemParallelLengthSegmentDB
   map<int, vector<double> > upFirstPhloemParallelLengthSegmentDB;
   map<int, vector<double> > upSecondPhloemParallelLengthSegmentDB;
   map<int, vector<double> > upFirstPhloemParallelLengthSegmentAddDB;
   map<int, vector<double> > upSecondPhloemParallelLengthSegmentAddDB;
   void UpPhloemParallelLengthSegmentDB( double variationRatio );

/// UpPhloemParallelLengthSegmentHalfDB
   map<int, vector<double> > upFirstPhloemParallelLengthSegmentHalfDB;
   map<int, vector<double> > upSecondPhloemParallelLengthSegmentHalfDB;
   void UpPhloemParallelLengthSegmentHalfDB();

/// UpPhloemParallelRadianSegmentDB
   map<int, vector<double> > upFirstPhloemParallelRadianSegmentDB;
   map<int, vector<double> > upSecondPhloemParallelRadianSegmentDB;
   map<int, vector<double> > upFirstPhloemParallelRadianSegmentAddDB;
   map<int, vector<double> > upSecondPhloemParallelRadianSegmentAddDB;
   void UpPhloemParallelRadianSegmentDB();

///// UpPhloemParallelLengthHalfDB;
//   map<int, vector<double> > upFirstPhloemParallelLengthHalfDB;
//   map<int, vector<double> > upSecondPhloemParallelLengthHalfDB;
//   void UpPhloemParallelLengthHalfDB();

/// UpPhloemParallelCenterRadianDB
   map<int, vector<double> > upFirstPhloemParallelCenterRadianDB;
   map<int, vector<double> > upSecondPhloemParallelCenterRadianDB;
   void UpPhloemParallelCenterRadianDB();

/// UpPhloemParallelCenterRotateAngleDB
   map<int, vector<double> >upFirstPhloemParallelCenterRotateAngleDB;
   map<int, vector<double> >upSecondPhloemParallelCenterRotateAngleDB;
   void UpPhloemParallelCenterRotateAngleDB();

/// UpPhloemCellXYDB
   map<int, vector<double> > upFirstPhloemParallelCellXDB;
   map<int, vector<double> > upFirstPhloemParallelCellYDB;
   map<int, vector<double> > upSecondPhloemParallelCellXDB;
   map<int, vector<double> > upSecondPhloemParallelCellYDB;
   void UpPhloemCellXYDB();

/// UpPhloemObjectHeightAndZPositionDB;
   map<int, vector<vector<double> > > upFirstPhloemCellObjectHeightDB;
   map<int, vector<vector<double> > > upFirstPhloemCellObjectZPositionDB;
   map<int, vector<vector<double> > > upSecondPhloemCellObjectHeightDB;
   map<int, vector<vector<double> > > upSecondPhloemCellObjectZPositionDB;
   void UpPhloemObjectHeightAndZPositionDB( int sliceNum );


/// Initialize Up Cell;
   void InitUpCell
   ( rsPXBoundaryDB *RsPXBoundaryDB,
     double setUpAppendParallelLengthThresholdRatio,
     double totalHeight,
     int sliceNum,
     double initZPosition,
     int vectorNum,
     double variationRatio  );

   /****************************************************************************************************************
   //////////////////////////////////////////// Down ////////////////////////////////////////////////////////////////
   *****************************************************************************************************************/
   /******************
   First
   ******************/
/// DownVerticalLengthTotalDB;
   vector<double> downVerticalLengthTotalDB;
   void DownVerticalLengthTotalDB( rsPXBoundaryDB *RsPXBoundaryDB );

/// DownFirstSecondVerticalLengthDB;
   vector<double> downFirstVerticalLengthDB;
   vector<double> downSecondVerticalLengthDB;
   void DownFirstSecondVerticalLengthDB();

/// DownFirstSecondVerticalLengthHalfDB
   vector<double> downFirstVerticalLengthHalfDB;
   vector<double> downSecondVerticalLengthHalfDB;
   void DownFirstSecondVerticalLengthHalfDB();

/// DownFirstParallelLengthThresholdDB;
   vector<double> downFirstParallelLengthThresholdDB;
   void DownFirstParallelLengthThresholdDB();

/// DownFirstSecondCenterRadiusDB;
   vector<double> downFirstCenterRadiusDB;
   vector<double> downSecondCenterRadiusDB;
   void DownFirstSecondCenterRadiusDB();

/// DownFirstSecondParallelLengthTotalDB;
   vector<double> downFirstParallelLengthTotalDB;
   vector<double> downSecondParallelLengthTotalDB;
   void DownFirstSecondParallelLengthTotalDB();

/// DownFirstCellNumDB;
   vector<int> downFirstCellNumDB;
   void DownFirstCellNumDB();

/// DownFirstParallelLengthDB;
   map<int, vector<double> > downFirstParallelLengthDB;
   map<int, vector<double> > downFirstParallelLengthAddDB;
   void DownFirstParallelLengthDB( double variationRatio );

/// DownFirstParallelLengthHalfDB;
   map<int,vector<double> > downFirstParallelLengthHalfDB;
   void DownFirstParallelLengthHalfDB();
/// DownFirstParallelRadianDivideDB;
   map<int, vector<double> > downFirstParallelRadianDivideDB;
   map<int, vector<double> > downFirstParallelRadianDivideAddDB;
   void DownFirstParallelRadianDivideDB();

/// DownFirstParallelCenterRadianDB;
   map<int, vector<double> > downFirstParallelCenterRadianDB;
   void DownFirstParallelCenterRadianDB();

/// DownFirstParallelRotateAngleDB;
   map<int, vector<double> >  downFirstParallelCenterRotateAngleDB;
   void DownFirstParallelRotateAngleDB();

/// DownFirstCellXYDB;
   map<int, vector<double> > downFirstCellXDB;
   map<int, vector<double> > downFirstCellYDB;
   void DownFirstCellXYDB();

/// DownFirstObjectHeightAndZPositionDB;
   map<int, vector<vector<double> > > downFirstCellObjectHeightDB;
   map<int, vector<vector<double> > > downFirstCellObjectZPositionDB;
   void DownFirstObjectHeightAndZPositionDB( int sliceNum );

   /******************
   Second
   ******************/
/// DownSecondParallelLengthTotalAverage
   double downSecondParallelLengthTotalAverage;
   void DownSecondParallelLengthTotalAverage();

/// DownSecondParallelCellNum
   vector<int> downSecondParallelCellNumDB;
   void DownSecondParallelCellNum();

/// DownSecondParallelLengthRatio56DB;
   vector<double> downSecondParallelLengthRatio5DB;
   vector<double> downSecondParallelLengthRatio6DB;
   void DownSecondParallelLengthRatio56DB();

/// DownSecondParallelLengthRatioDB;
   map<int,vector<double> > downSecondParallelLengthRatioDB;
   void DownSecondParallelLengthRatioDB();

/// DownSecondParallelLengthDB;
   map<int,vector<double> > downSecondParallelLengthDB;
   void DownSecondParallelLengthDB();

/// DownSecondParallelLengthHalfDB;
   map<int,vector<double> > downSecondParallelLengthHalfDB;
   void DownSecondParallelLengthHalfDB();

/// DownSecondParallelLengthAddDB;
   map<int,vector<double> > downSecondParallelLengthAddDB;
   void DownSecondParallelLengthAddDB();

/// DownSecondParallelRadianSegmentDB;
   map<int, vector<double> > downSecondParallelRadianSegmentDB;
   map<int, vector<double> > downSecondParallelRadianSegmentAddDB;
   void DownSecondParallelRadianSegmentDB();

/// DownSecondParallelCenterRadianDB;
   map<int, vector<double> > downSecondParallelCenterRadianDB;
   void DownSecondParallelCenterRadianDB();

/// DownSecondParallelRotateAngleDB;
   map<int, vector<double> >  downSecondParallelCenterRotateAngleDB;
   void DownSecondParallelRotateAngleDB();

/// DownSecondCellXYDB;
   map<int, vector<double> > downSecondCellXDB;
   map<int, vector<double> > downSecondCellYDB;
   void DownSecondCellXYDB();

/// DownSecondObjectHeightAndZPositionDB;
   map<int, vector<vector<double> > > downSecondCellObjectHeightDB;
   map<int, vector<vector<double> > > downSecondCellObjectZPositionDB;
   void DownSecondObjectHeightAndZPositionDB( int sliceNum );

////////////////////////  Initialize down cell  ////////////////////////////
   void InitDownCell
   ( rsPXBoundaryDB *RsPXBoundaryDB,
     double variationRatio,
     int sliceNum
   );


};


#endif // RSPHLOEMDB_H_INCLUDED
