#ifndef RSSTELEINNERDB_H_INCLUDED
#define RSSTELEINNERDB_H_INCLUDED

#include "rsBaseGeometry.h"
#include "rsSourceCorticalDB.h"
#include "rsMXBoundaryOutDB.h"
#include "globals.h"

class rsSteleInnerDB : public rsBaseGeometry
{
public:

   double steleInnerBoundRadius;
   void SteleInnerBoundRadius( rsMXBoundaryOutDB *RsMXBoundaryOutDB);

   double steleInnestCellRadius;
   void SteleInnestCellRadius( double steleInnestCellRadiusInput );

   int steleInnerLayerNum;
   vector<double> steleInnerAddRadiusDB;
   void SteleInnerAddRadiusDB( int steleInnerLayerNumInput );

   vector<double> steleInnerAppendRadiusDB;
   void SteleInnerAppendRadiusDB();

   vector<double> steleInnerRingRadiusDB;
   void SteleInnerRingRadiusDB();

   vector<int> steleInnerCellNumCalculateData;
   void SteleInnerCellNumCalculateData();

   vector<double> steleInnerObjectVerticalDB;
   void SteleInnerObjectVerticalDB();

   map<int, vector<double> > longitudeSegmentHeightDB;
   map<int, vector<double> > longitudeZPositionAddDB;
   void RandomHeightDB( double totalHeight, int sliceNum, double initZPosition, int VectorNum );

   map<int, vector<double> > circleSegmentLengthDB;
   vector<double> circleSegmentLengthSumDB;
   map<int, vector<double> > circleSegmentRotateAngleDB;
   map<int, vector<double> > circleXDB;
   map<int, vector<double> > circleYDB;
   void GetRandomCircleSegmentAndCircleXYNonuniformDB( double variationRatio );

   void CircleSegmentLengthAdjustRatioDB();

   map<int, vector< vector<double> > > objectHeightDB;
   map<int, vector< vector<double> > > objectZPositionDB;
   void ObjectHeightAndZPositionDB( int sliceNum );

   vector<double> steleInnestObjectHeightDB;
   vector<double> steleInnestObjectZPositionDB;
   void SteleInnestObjectHeightAndZPositionDB( int sliceNum );

   void InitAllDB ( rsMXBoundaryOutDB *RsMXBoundaryOutDB,
                    double steleInnestCellRadiusInput,
                    int steleInnerLayerNumInput,
                    double totalHeight,
                    double initZPosition,
                    int vectorNum,
                    double variationRatio,
                    int sliceNum );

};

#endif // RSSTELEINNERDB_H_INCLUDED
