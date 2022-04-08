#ifndef RSSOURCEEPIDERMISDB_H_INCLUDED
#define RSSOURCEEPIDERMISDB_H_INCLUDED

#include "rsBaseGeometry.h"
#include <string>
#include <iostream>

/**************************************
/// We need to store for each ring in Cortical cell;
baseRadiusDB                     double ;
circleRadiusDB                   vector<double> ;
objectVerticalDB                 vector<double> ;
circleSegmentLengthDB            map<int, vector<double> > ;
circleSegmentLengthSumDB         vector<double> ;
circleSegmentRotateLengthAddDB   map<int, vector<double> > ;
circleXDB                        map<int, vector<double> > ;
circleYDB                        map<int, vector<double> > ;
***************************************/


class rsSourceDermisDB : public rsBaseGeometry
{
public:

   /// Set OutputXMLVtpFileName;
   const char* outputXMLVtpFileName;
   const char* cellType;
   void OutputXMLVtpFileName( const char* outputXMLVtpFileNameInput, const char* cellTypeInput );

   /// create circleRadiusDB;
   vector<double> circleRadiusDB;
   void CircleRadiusDB(double epidermisBaseRadius,
                       vector<double> dermisAppendRadiusDB);
   

   /// createobjectVerticalDB;
   vector<double> objectVerticalDB;
   void ObjectVerticalDB( vector<double> epidermisAddRadius );

   /// create map RandomHeightDB;
   map<int, vector<double> > longitudeSegmentHeightDB;
   map<int, vector<double> > longitudeZPositionAddDB;
   void RandomHeightDB( double totalHeight, int sliceNum, double initZPosition, int VectorNum );

   int EpidermisCellNumCalculated;
   vector<int> DermisCellNumDB;
   void EpidermisCellNumCalculate( vector<double> epidermisAddRadiusData );

   /// Create GetRandomCircleSegmentAndCircleXYNonuniformDB;
   map<int, vector<double> > circleSegmentLengthDB;
   vector<double> circleSegmentLengthSumDB;
   map<int, vector<double> > circleSegmentRotateAngleDB;
   map<int, vector<double> > circleXDB;
   map<int, vector<double> > circleYDB;
   
   void GetRandomCircleSegmentAndCircleXYNonuniformDB
   ( vector<double> epidermisAddRadiusData,
     double baseRadius,
//     int epidermisCellNum,
     double variationRatio );

   /// Get circleSegmentLengthAdjustRatioDB;
   void CircleSegmentLengthAdjustRatioDB();

   /// Get ObjectHeightDB and ObjectZPositionDB;
   map<int, vector< vector<double> > > objectHeightDB;
   map<int, vector< vector<double> > > objectZPositionDB;

   void ObjectHeightAndZPositionDB( int sliceNum );

   /// Initialize other Database;
   void InitAllDB ( const char* outputXMLVtpFileNameInput,
                    const char* cellTypeInput,
                    vector<double> epidermisAddRadiusData,
                    double epidermisBaseRadius,
                    //                    int epidermisCellNum,
                    double variationRatio,
                    int sliceNum, int numFiles );

   /// Initialize pure cell Database;
   double gapCellWall;
   vector<double> pureCellVerticalDB;
   map<int, vector<double> > pureCellParallelDB;
   map<int, vector< vector<double> > > pureCellHeightDB;
   void InitPureCellDB(double gapCellWallInput);

   /// Initialize vacuole Database;
   double gapCytoTono;
   vector<double> vacuoleVerticalDB;
   map<int, vector<double> > vacuoleParallelDB;
   map<int, vector< vector<double> > > vacuoleHeightDB;
   void InitVacuoleDB(double gapCytoTonoInput);
};



#endif // RSSOURCEEPIDERMISDB_H_INCLUDED
