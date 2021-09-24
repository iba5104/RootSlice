#ifndef RSSOURCEEPIDERMISDB_H_INCLUDED
#define RSSOURCEEPIDERMISDB_H_INCLUDED

#include "rsBaseGeometry.h"

/**************************************
/// We need to store for each ring in Cortical cell;
baseRadiusDB                     double ;
circleRadiusDB                   double ;
objectVerticalDB                 double ;
circleSegmentLengthDB            vector<double> ;
circleSegmentLengthSumDB         double ;
circleSegmentRotateLengthAddDB   vector<double> ;
circleXDB                        vector<double> ;
circleYDB                        vector<double> ;
***************************************/


class rsSourceDermisDB : public rsBaseGeometry
{
public:

   /// Set OutputXMLVtpFileName;
   const char* outputXMLVtpFileName;
   void OutputXMLVtpFileName( const char* outputXMLVtpFileNameInput );

   /// create circleRadiusDB;
   double circleRadiusDB;
   void CircleRadiusDB( double epidermisBaseRadius,
                        double epidermisAddRadius);

   /// createobjectVerticalDB;
   double objectVerticalDB;
   void ObjectVerticalDB( double epidermisAddRadius );

   /// create map RandomHeightDB;
   map<int, vector<double> > longitudeSegmentHeightDB;
   map<int, vector<double> > longitudeZPositionAddDB;
   void RandomHeightDB( double totalHeight, int sliceNum, double initZPosition, int VectorNum );

   int EpidermisCellNumCalculated;
   void EpidermisCellNumCalculate( double epidermisAddRadiusData );

   /// Create GetRandomCircleSegmentAndCircleXYNonuniformDB;
   vector<double> circleSegmentLengthDB;
   double circleSegmentLengthSumDB;
   vector<double> circleSegmentRotateAngleDB;
   vector<double> circleXDB;
   vector<double> circleYDB;
   void GetRandomCircleSegmentAndCircleXYNonuniformDB
   ( double epidermisAddRadiusData,
     double baseRadius,
//     int epidermisCellNum,
     double variationRatio );

   /// Get circleSegmentLengthAdjustRatioDB;
   void CircleSegmentLengthAdjustRatioDB();

   /// Get ObjectHeightDB and ObjectZPositionDB;
   map<int, vector<double> > objectHeightDB;
   map<int, vector<double> > objectZPositionDB;

   void ObjectHeightAndZPositionDB( int sliceNum );

   /// Initialize other Database;
   void InitAllDB ( const char* outputXMLVtpFileNameInput,
                    double epidermisAddRadiusData,
                    double epidermisBaseRadius,
//                    int epidermisCellNum,
                    double variationRatio,
                    int sliceNum );

   /// Initialize pure cell Database;
   double gapCellWall;
   double pureCellVerticalDB;
   vector<double> pureCellParallelDB;
   map<int, vector<double> > pureCellHeightDB;
   void InitPureCellDB(double gapCellWallInput);

   /// Initialize vacuole Database;
   double gapCytoTono;
   double vacuoleVerticalDB;
   vector<double> vacuoleParallelDB;
   map<int, vector<double> > vacuoleHeightDB;
   void InitVacuoleDB(double gapCytoTonoInput);
};



#endif // RSSOURCEEPIDERMISDB_H_INCLUDED
