#ifndef RSRCADB_H_INCLUDED
#define RSRCADB_H_INCLUDED

#include "rsSourceCorticalDB.h"
#include "globals.h"

class rsRcaDB : public rsBaseGeometry
{
public:
/// GetRcaData
   double rcaRatio;
   int rcaNum;
   int standardOuterLayer;
   int standardInnerLayer;
   void GetRcaData( double rcaRatioInput, int rcaNumInput, int standardOuterLayerInput, int standardInnerLayerInput );

/// cortexArea;
   double cortexArea;
   void CortexArea( double baseRadius, rsSourceCorticalDB *RsSourceCorticalDB );

/// rcaTotalArea;
   double rcaTotalArea;
   void RcaTotalArea();

/// rcaArea;
   vector<double> rcaArea;
   vector<double> rcaAddArea;
   void RcaArea( double variationRatio );

/// rcaVerticalLengthStoreDB;
/// set standardOuterLayer = 2;
/// set standardInnerLayer = 1; The standardInnerLayer must be bigger than 0;
   map<int, vector<double> > rcaVerticalLengthStoreDB;
   map<int, vector<int> > rcaVerticalLengthStoreStartLayerDB;
   void RcaVerticalLengthStoreDB( rsSourceCorticalDB *RsSourceCorticalDB );

/// The rcaRation must be between 0.01 - 0.60;
/// The number of total cell layers must equal or larger than 6;
   /*************
   1%  -  5%: 2 - 3;
   5%  - 15%: 2 - 4;
   15% - 60%: 4 - upper;
   **************/
/// rcaVerticalLengthStoreSelectRange;
   vector<double> rcaVerticalLengthStoreSelectRange;
   void RcaVerticalLengthStoreSelectRange( rsSourceCorticalDB *RsSourceCorticalDB );

/// RcaVerticalLengthDB;
   vector<double> rcaVerticalLengthDB;
   vector<int> rcaVerticalLengthStartLayerDB;
   vector<int> rcaVerticalLayerNumDB;
   void RcaVerticalLengthDB();

/// ParallelRadiusDB;
   vector<double> parallelRadiusDB;
   double parallelRadiusAdjustRatio;
   void ParallelRadiusDB();

/// This radius is a radius for the whole cross-section;
/// rcaCenterVerticalMiddleRadius;
   vector<double> rcaCenterVerticalMiddleRadiusDB;
   double middleRadiusAdjustRatio;
   void RcaCenterVerticalMiddleRadiusDB( double baseRadius, rsSourceCorticalDB *RsSourceCorticalDB );

/// RcaIntersetionAngleHalfDB;
   vector<double> rcaIntersetionAngleHalfDB;
   vector<double> rcaAddIntersetionAngleDB;
   void RcaIntersetionAngleHalfDB();

/// GapAngleBetweenRcaDB;
   double gapAngleBetweenRca;
   vector<double> gapAddAngleBetweenRcaDB;
   void GapAngleBetweenRcaDB( double gapAngleBetweenRcaRatio );

/// SurplusAngleTotal;
   double surplusAngleTotal;
   void SurplusAngleTotal();

/// SurplusAngleDistribution;
   vector<double> surplusAngleDistribution;
   vector<double> surplusAddAngleDistribution;
   void SurplusAngleDistribution( double randomRange );

/// RcaMidPointAngleDB;
   vector<double> rcaMidPointAngleDB;
   void RcaMidPointAngleDB();

/// RcaLowerUpperLayerPositionDB;
   map<int, vector<int> > rcaLowerLayerPositionDB;
   map<int, vector<int> > rcaUpperLayerPositionDB;
   void RcaLowerUpperLayerPositionDB( rsSourceCorticalDB *RsSourceCorticalDB );

/// RcaLowerLayerIntersectionAngleDB;
   map<int, vector<double> > rcaLowerLayerIntersectionAngleHalfDB;
   map<int, vector<double> > rcaUpperLayerIntersectionAngleHalfDB;
   void RcaLowerUpperLayerIntersectionAngleDB();

/// rcaCellPositionDB;
/// 从后面开始删除细胞；
   map<int, map<int, vector<int> > > rcaCellPositionDB;
   void RcaCellPositionDB(  rsSourceCorticalDB *RsSourceCorticalDB );

   /// RcaCellPositionSimplifyDB
   map<int, vector<int> > rcaCellPositionSimplifyDB;
   void RcaCellPositionSimplifyDB();

   /// RcaRealRatio
   double rcaRealVolume;
   double rca2CortexExactRatio;
   void RcaRealVolume( rsSourceCorticalDB *RsSourceCorticalDB, double totalHeight );

   /// RcaCellErase
   void RcaCellErase( rsSourceCorticalDB *RsSourceCorticalDB );

//   /// RcaDataOutput
//   void RcaDataOutput();

/// Initialize rcaDB;
   void InitBasicRcaDB( double rcaRatioInput,
                        int rcaNumInput,
                        int standardOuterLayerInput,
                        int standardInnerLayerInput,
                        double baseRadius,
                        rsSourceCorticalDB *RsSourceCorticalDB,
                        double variationRatio
                      );

   void CalculateRcaDB(  double baseRadius,
                         rsSourceCorticalDB *RsSourceCorticalDB,
                         double variationRatio,
                         double gapAngleBetweenRcaRatio,
                         double totalHeight);

   void JudgeAccuracyRcaDB(double baseRadius,
                           rsSourceCorticalDB *RsSourceCorticalDB,
                           double variationRatio,
                           double gapAngleBetweenRcaRatio,
                           double totalHeight);

   void InitRcaDB( double rcaRatioInput,
                      int rcaNumInput,
                      int standardOuterLayerInput,
                      int standardInnerLayerInput,
                      double baseRadius,
                      rsSourceCorticalDB *RsSourceCorticalDB,
                      double variationRatio,
                      double gapAngleBetweenRcaRatio,
                      double totalHeight
                    );
};












#endif // RSRCADB_H_INCLUDED
