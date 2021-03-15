#ifndef RSSOURCECORTICALDB_H_INCLUDED
#define RSSOURCECORTICALDB_H_INCLUDED

#include "rsBaseGeometry.h"

/**************************************
/// We need to store for each ring in Cortical cell;
corticalAppendRadiusDB           vector<double> ;
circleRadiusDB                   vector<double> ;
objectVerticalDB                 vector<double> ;
circleSegmentLengthDB            map<int, vector<double> > ;
circleSegmentLengthSumDB         vector<double> ;
circleSegmentRotateLengthAddDB   map<int, vector<double> > ;
circleXDB                        map<int, vector<double> > ;
circleYDB                        map<int, vector<double> > ;
***************************************/

class rsSourceCorticalDB : public rsBaseGeometry
{
public:
//   rsSourceCorticalDB( void )
//   {  cout << "rsSourceCorticalDB - constructor" << endl;
//   }
//
//   ~rsSourceCorticalDB( void )
//   {  cout << "rsSourceCorticalDB - destructor" << endl;
//   }

   /// Set OutputXMLVtpFileName;
   const char* CorticalXMLVtpFileName;
   const char* CorticalVacuoleXMLVtpFileName;
   void OutputXMLVtpFileName
   ( const char* CorticalXMLVtpFileNameInput,
     const char* CorticalVacuoleXMLVtpFileNameInput );

   /// CorticalAddRadiusCalculateRatioData;
   vector<double> corticalAddRadiusCalculateSingleRatioData;
   vector<double> corticalAddRadiusCalculateMixRatioData;
   void CorticalAddRadiusCalculateRatioData
   ( int cortexLayerNum,
     double corticalCellMultiplyRatio );

   /// CorticalAddRadiusCalculateFromMinCellData;
   vector<double> corticalAddRadiusCalculateFromMinCellData;

   void CorticalAddRadiusCalculateFromMinCellData();

   /// CorticalAddRadiusCalculateFromCortexRadiusData;
   vector<double> corticalAddRadiusCalculateFromCortexRadiusData;
   double corticalInnermostCellDiameterCalculate;
   void CorticalAddRadiusCalculateFromCortexRadiusData();

   /// CorticalAddRadiusCalculateData
   vector<double> corticalAddRadiusCalculateData;
   double corticalCellAddRadiusMin;
   double cortexRadius;
   void CorticalAddRadiusCalculateData
   ( double corticalCellAddRadiusMinInput,
     double cortexRadiusInput );

   /// CorticalAddRadiusDataSelect
   vector<double> corticalAddRadiusDB;
   void CorticalAddRadiusDataSelect
   ( int corticalAddRadiusDBSelectInput,
     vector<double> corticalAddRadiusInputData );

   /// create vector corticalAppendRadiusDB to store corticalAppendRadius;
   vector<double> corticalAppendRadiusDB;
   void CorticalAppendRadiusDB();

   /// create the radius of outest ring in cortical;
   double boundaryRadius;
   void BoundaryRadius( double baseRadius );

   /// CorticalCellNumCalculateData;
   vector<int>  corticalCellNumCalculateData;
   void CorticalCellNumCalculateData();

   /// CorticalCellNumSelect;
   vector<int>  corticalCellNumDB;
   void CorticalCellNumSelect( int corticalCellNumSelectInput, vector<int>  corticalCellNumInputData );

   /// create vector circleRadiusDB to store circleRadius;
   vector<double> circleRadiusDB;
   void CircleRadiusDB
   ( double baseRadius,
     vector<double> corticalAppendRadiusDB );

   /// create vector objectVectorDB to store corticalAddRadiusData;
   vector<double> objectVerticalDB;
   void ObjectVerticalDB();

   /// create map RandomHeightDB;
   map<int, vector<double> > longitudeSegmentHeightDB;
   map<int, vector<double> > longitudeZPositionAddDB;
   void RandomHeightDB( double totalHeight, int sliceNum, double initZPosition, int VectorNum );

   /*** create ... to store Random data and circleXYDB;
   circleSegmentLengthDB;
   circleSegmentLengthSumDB;
   circleSegmentRotateLengthAddDB;
   circleXDB;
   circleYDB;
   ***/
   map<int, vector<double> > circleSegmentLengthDB;
   vector<double> circleSegmentLengthSumDB;
   map<int, vector<double> > circleSegmentRotateAngleDB;
   map<int, vector<double> > circleXDB;
   map<int, vector<double> > circleYDB;

   void GetRandomCircleSegmentAndCircleXYNonuniformDB
   ( vector<int> corticalCellNumDB,
     double variationRatio
   );

   ///
   void CircleSegmentLengthAdjustRatioDB();

   /// To get ObjectHeight and ObjectZPosition;
   map<int, vector< vector<double> > > objectHeightDB;
   map<int, vector< vector<double> > > objectZPositionDB;
   void ObjectHeightAndZPositionDB( int sliceNum );

   /// Initialize all database;
   void InitAllDB ( double baseRadius,
                    int cortexLayerNum,
                    double corticalCellMultiplyRatio,
                    double corticalCellAddRadiusMinInput,
                    double cortexRadiusInput,
                    int corticalAddRadiusDBSelectInput,
                    vector<double> corticalAddRadiusInputData,
                    vector<int> corticalCellNumInputData,
                    int corticalCellNumSelectInput,
                    double variationRatio,
                    int setUResolution,
                    int setVResolution,
                    int setWResolution,
                    int sliceNum
                  );

   /// Initialize pure cell Database;
   double gapCellWall;
   vector<double> pureCellVerticalDB;
   map<int, vector<double> > pureCellParallelDB;
   map<int, vector< vector<double> > > pureCellHeightDB;
   void InitPureCellDB( double gapCellWallInput );

   /// Initialize vacuole Database;
   double gapCytoTono;
   vector<double> vacuoleVerticalDB;
   map<int, vector<double> > vacuoleParallelDB;
   map<int, vector< vector<double> > > vacuoleHeightDB;
   void InitVacuoleDB( double gapCytoTonoInput );



};

#endif // RSSOURCECORTICALDB_H_INCLUDED
