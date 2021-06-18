#ifndef RSPXBOUNDARYDB_H_INCLUDED
#define RSPXBOUNDARYDB_H_INCLUDED

#include "rsPXCoreDB.h"

class rsPXBoundaryDB : public rsPXCoreDB
{
public:

/// boundaryRotateRadian
   vector<double> boundaryRotateRadian;
   void BoundaryRotateRadian();

/// radianUniformDB
   vector<double> radianUniformDB;
   void RadianUniformDB( int dotNum );

/// boundaryPointRotateRadianDB
   map<int, vector<double> > boundaryPointRotateRadianDB;
   void BoundaryPointRotateRadianDB();

/// BoundaryPointXLeftHemisphere
   map<int, vector<double> > boundaryPointXLeftHemisphereDB;
   map<int, vector<double> > boundaryPointYLeftHemisphereDB;
   map<int, vector<double> > boundaryPointXRightHemisphereDB;
   map<int, vector<double> > boundaryPointYRightHemisphereDB;
   void BoundaryPointXYLeftAndRightHemisphere( int dotNum );

/// boundaryHalfCentralRadianDB
   vector<double> boundaryHalfCentralRadianDB;
   void BoundaryHalfCentralRadianDB(rsPXCoreDB* RsPXCoreDB);

/// boundaryRadianStartDB, boundaryRadianEndDB and boundaryCentralRadianDB;
   vector<double> boundaryRadianStartDB;
   vector<double> boundaryRadianEndDB;
   vector<double> boundaryCentralRadianDB;
   void BoundaryRadianStartAndEndDB();

/// boundaryMaxCenterRadiusDB and boundaryMinCenterRadiusDB
   vector<double> boundaryMaxCenterRadiusDB;
   vector<double> boundaryMinCenterRadiusDB;
   void BoundaryMaxAndMinCenterRadiusDB(rsPXCoreDB* RsPXCoreDB);

/// boundaryTangentCenterRadiusDB
   vector<double> boundaryTangentCenterRadiusDB;
   void BoundaryTangentCenterRadiusDB();

/// boundaryTangentUpLengthDB and boundaryTangentDownLengthDB;
   vector<double> boundaryTangentUpLengthDB;
   vector<double> boundaryTangentDownLengthDB;
   void BoundaryTangentUpAndDownLengthDB();

/// SetUpAndDownRowNum
   int upRowNum;
   int downRowNum;
   double validUpRowNum;
   double validDownRowNum;
   void SetUpAndDownRowNum( int setUpRowNum, int setDownRowNum );

/// boundaryTangentUpLengthSegmentDB and boundaryTangentDownLengthSegmentDB
   vector<double> boundaryTangentUpLengthSegmentDB;
   vector<double> boundaryTangentDownLengthSegmentDB;
   void BoundaryTangentUpAndDownLengthSegmentDB();

/// boundaryTangentUpLengthSegmentAppendRadiusDB and boundaryTangentDownLengthSegmentAppendRadiusDB;
   map<int, vector<double> > boundaryTangentUpLengthSegmentAppendRadiusDB;
   map<int, vector<double> > boundaryTangentDownLengthSegmentAppendRadiusDB;
   void BoundaryTangentUpAndDownLengthSegmentAppendRadiusDB();

/// boundaryPointRightHemisphereCenterDistance;
   map<int, vector<double> > boundaryPointRightHemisphereCenterDistanceDB;
   void BoundaryPointRightHemisphereCenterDistanceDB();

/// Search points that equal to boundaryTangentUpAndDownRightLengthSegmentAppendRadiusDB
   map<int, vector<double> > boundaryPointRightUpXHemisphereTargetDB;
   map<int, vector<double> > boundaryPointRightUpYHemisphereTargetDB;
   map<int, vector<double> > boundaryPointRightDownXHemisphereTargetDB;
   map<int, vector<double> > boundaryPointRightDownYHemisphereTargetDB;
   void BoundaryPointRightUpDownXYHemisphereTargetDB();

/// boundaryRadianStartPointXDB and boundaryRadianStartPointYDB
   vector<double> boundaryRadianStartPointXDB;
   vector<double> boundaryRadianStartPointYDB;
   void BoundaryRadianStartPointXYDB();

/// boundaryPointRightHemisphereTargetIntersectionRadian;
   map<int, vector<double> > boundaryPointRightUpHemisphereTargetIntersectionRadianDB;
   map<int, vector<double> > boundaryPointRightDownHemisphereTargetIntersectionRadianDB;
   void BoundaryPointRightUpAndDownHemisphereTargetIntersectionRadianDB();

/// boundaryPointRightUpAndDownHemisphereTargetCenterRadian
   map<int, vector<double> > boundaryPointRightUpHemisphereTargetCenterRadianDB;
   map<int, vector<double> > boundaryPointRightDownHemisphereTargetCenterRadianDB;
   map<int, vector<double> > boundaryPointLeftUpHemisphereTargetCenterRadianDB;
   map<int, vector<double> > boundaryPointLeftDownHemisphereTargetCenterRadianDB;
   void BoundaryPointRightAndLeftUpAndDownHemisphereTargetCenterRadian();

/// BoundaryUpAndDownCellObjectVerticalDB
   vector<double> boundaryUpCellObjectVerticalDB;
   vector<double> boundaryDownCellObjectVerticalDB;
   void BoundaryUpAndDownCellObjectVerticalDB();

/// BoundaryUpAndDownCellCenterRadiusDB
   map<int, vector<double> > boundaryUpCellCenterRadiusDB;
   map<int, vector<double> > boundaryDownCellCenterRadiusDB;
   void BoundaryUpAndDownCellCenterRadiusDB();

/// appendCellUpAndDownNumDB;
   vector<double> boundaryCellUpNumDB;
   vector<double> boundaryCellDownNumDB;
   void BoundaryCellUpAndDownNumDB();

/// boundaryUpAndDownCellObjectParallelDB;
   map<int, vector<double> > boundaryUpCellObjectParallelDB;
   map<int, vector<double> > boundaryDownCellObjectParallelDB;
   void BoundaryUpAndDownCellObjectParallelDB();

/// boundaryPointRightUpAndDownHemisphereTargetIntersectionRadianDivideDB;
   map<int, vector<double> > boundaryPointRightUpHemisphereTargetIntersectionRadianDivideDB;
   map<int, vector<double> > boundaryPointRightDownHemisphereTargetIntersectionRadianDivideDB;
   void BoundaryPointRightUpAndDownHemisphereTargetIntersectionRadianDivideDB();

/// boundaryCellLeftAndRightUpAndDownCenterRadianDB;
   map<int, vector<vector<double> > > boundaryCellLeftUpCenterRadianDB;
   map<int, vector<vector<double> > > boundaryCellRightUpCenterRadianDB;
   map<int, vector<vector<double> > > boundaryCellLeftDownCenterRadianDB;
   map<int, vector<vector<double> > > boundaryCellRightDownCenterRadianDB;
   void BoundaryCellLeftAndRightUpAndDownCenterRadianDB();

/// BoundaryCellLeftAndRightUpAndDownCenterRotateAngleDB;
   map<int, vector<vector<double> > > boundaryCellRightUpCenterRotateAngleDB;
   map<int, vector<vector<double> > > boundaryCellLeftUpCenterRotateAngleDB;
   map<int, vector<vector<double> > > boundaryCellRightDownCenterRotateAngleDB;
   map<int, vector<vector<double> > > boundaryCellLeftDownCenterRotateAngleDB;
   void BoundaryCellLeftAndRightUpAndDownCenterRotateAngleDB();

/// boundaryCellLeftAndRighUpAndDownXYDB;
   map<int, vector<vector<double> > > boundaryCellLeftUpXDB;
   map<int, vector<vector<double> > > boundaryCellRightUpXDB;
   map<int, vector<vector<double> > > boundaryCellLeftDownXDB;
   map<int, vector<vector<double> > > boundaryCellRightDownXDB;
   map<int, vector<vector<double> > > boundaryCellLeftUpYDB;
   map<int, vector<vector<double> > > boundaryCellRightUpYDB;
   map<int, vector<vector<double> > > boundaryCellLeftDownYDB;
   map<int, vector<vector<double> > > boundaryCellRightDownYDB;
   void BoundaryCellLeftAndRighUpAndDownXYDB();

/// BoundaryCellObjectHeightAndZPositionDB;
   map<int, vector <vector<vector<double> > > >boundaryCellLeftUpObjectHeightDB;
   map<int, vector <vector<vector<double> > > >boundaryCellRightUpObjectHeightDB;
   map<int, vector <vector<vector<double> > > >boundaryCellLeftDownObjectHeightDB;
   map<int, vector <vector<vector<double> > > >boundaryCellRightDownObjectHeightDB;

   map<int, vector <vector<vector<double> > > >boundaryCellLeftUpObjectZPositionDB;
   map<int, vector <vector<vector<double> > > >boundaryCellRightUpObjectZPositionDB;
   map<int, vector <vector<vector<double> > > >boundaryCellLeftDownObjectZPositionDB;
   map<int, vector <vector<vector<double> > > >boundaryCellRightDownObjectZPositionDB;

   void BoundaryCellObjectHeightAndZPositionDB( int sliceNum );

/// Initialize Boundary Cells
   void InitBoundaryCell
   ( rsPXCoreDB* RsPXCoreDB,
     int dotNum,
     int setUpRowNum,
     int setDownRowNum,
     int sliceNum );

};

#endif // RSPXBOUNDARYDB_H_INCLUDED
