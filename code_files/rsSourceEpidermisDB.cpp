#define _USE_MATH_DEFINES
#include <cmath> 
#include "rsSourceEpidermisDB.h"

//////////////////////////////////////// Functions //////////////////////////////////////////////////

/// Set OutputXMLVtpFileName;
void rsSourceEpidermisDB::OutputXMLVtpFileName( const char* outputXMLVtpFileNameInput )
{  outputXMLVtpFileName = outputXMLVtpFileNameInput;
}

/// create circleRadiusDB;
void rsSourceEpidermisDB::CircleRadiusDB
( double epidermisBaseRadius,
  double epidermisAddRadiusData)
{  circleRadiusDB = CircleRadius( epidermisBaseRadius, 0, epidermisAddRadiusData );
cout << "epidermisbase radius " << epidermisBaseRadius;
}

/// createobjectVerticalDB;
void rsSourceEpidermisDB::ObjectVerticalDB( double epidermisAddRadius )
{  objectVerticalDB = ObjectVertical( epidermisAddRadius / objectXYZRadiusRatio );
cout << "epidermisobjectVerticalDB" << objectVerticalDB << endl;
}

/******************************************************
// Create RandomHeightDB; Initialize seperated;
*******************************************************/
void rsSourceEpidermisDB::RandomHeightDB( double totalHeight, int sliceNum, double initZPosition, int VectorNum )
{  int temp;
   for ( temp = 0;
         temp != VectorNum;
         temp++ )
   {  /// RandomHeight;
      NonRandomHeight( totalHeight, sliceNum, initZPosition );
      longitudeSegmentHeightDB.insert( pair<int, vector<double> > (temp, longitudeSegmentHeight) );
      longitudeZPositionAddDB.insert( pair<int, vector<double> > (temp, longitudeZPositionAdd) );
      //cout << "EpidermislongitudeSegmentHeigh" << longitudeSegmentHeight.at(temp) << endl;
   }
}

/******************************************************
// Create GetRandomCircleSegmentAndCircleXYNonuniformDB;
*******************************************************/
/** \brief epidermisCellNumCalculate
 *
 * \param double epidermisAddRadiusData;
 * \param double circleRadiusDB;
 * \return int EpidermisCellNumCalculated
 *
 */

void rsSourceEpidermisDB::EpidermisCellNumCalculate( double epidermisAddRadiusData )
{  EpidermisCellNumCalculated =  int( 2 * M_PI  * circleRadiusDB / epidermisAddRadiusData );

   cout << "EpidermisCellNumCalculated: " << EpidermisCellNumCalculated << endl;
   cout << "epidermisAddRadiusData" << epidermisAddRadiusData << endl;
   cout << "circleRadiusDB" << circleRadiusDB << endl;
}

/******************************************************
// Create GetRandomCircleSegmentAndCircleXYNonuniformDB;
*******************************************************/

void rsSourceEpidermisDB::GetRandomCircleSegmentAndCircleXYNonuniformDB
(  double epidermisAddRadiusData,
   double epidermisBaseRadius,
//   int epidermisCellNum,
   double variationRatio )

{  CircleRadiusDB( epidermisBaseRadius,
                   epidermisAddRadiusData);

   CirclePerimeter( circleRadiusDB );

   /// RandomRatioButSameSumAndNumber
   SameSumAndNumberAndRatio( circleSegmentLength,
                             circleSegmentLengthAdd,
                             circleSegmentLengthSum,
                             circlePerimeter,
                             EpidermisCellNumCalculated,
//                             epidermisCellNum,
                             variationRatio );

   circleSegmentLengthDB = circleSegmentLength;
   circleSegmentLengthSumDB = circleSegmentLengthSum;

//   CircleXYNonuniform( epidermisCellNum, circleRadiusDB );
   CircleXYNonuniform( EpidermisCellNumCalculated, circleRadiusDB );
   circleXDB = circleX;
   circleYDB = circleY;
   circleSegmentRotateAngleDB = circleSegmentRotateAngle;
}


/******************************************************
// Get circleSegmentLengthAdjustRatioDB;
*******************************************************/
void rsSourceEpidermisDB::CircleSegmentLengthAdjustRatioDB()
{  vector<double>::iterator itVector;

   for ( itVector = circleSegmentLengthDB.begin(); itVector !=  circleSegmentLengthDB.end(); itVector++)
   {  *itVector = (*itVector) / 2 / objectXYZRadiusRatio;
   //cout << "EpidermisCirclesegmentlength111 " << *itVector << endl;
   }
}

/*******************************************
to get ObjectHeightDB and ObjectZPositionDB;
********************************************/
/** need to initialize:
"longitudeSegmentHeightDB"
"longitudeZPositionAddDB"
**/

map<int, vector<double> > objectHeightDB;
map<int, vector<double> > objectZPositionDB;


void rsSourceEpidermisDB::ObjectHeightAndZPositionDB( int sliceNum )
{  /// declare iterator;

   vector<double>::iterator itVector;

   vector<double> objectHeightVec;
   vector<double> objectZPositionVec;
   /// declare int;
   int i;
   int sliceTempNum;

   for ( i=0, itVector = circleXDB.begin(); itVector !=  circleXDB.end(); i++, itVector++)
   {  int randomHeightZPosition = rand() % 200;
      objectHeightVec.clear();
      objectZPositionVec.clear();
      for ( sliceTempNum = 0; sliceTempNum != sliceNum; sliceTempNum++  )
      {  objectHeightVec.push_back
         ( longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio );

         objectZPositionVec.push_back
         ( longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum] );
      }
      objectHeightDB.insert( pair<int, vector<double> >( i, objectHeightVec ) );
      objectZPositionDB.insert( pair<int, vector<double> >( i, objectZPositionVec ) );
   }
}


/*******************************************
Initialize other Database;
********************************************/
void rsSourceEpidermisDB::InitAllDB ( const char* outputXMLVtpFileNameInput,
                                      double epidermisAddRadiusData,
                                      double epidermisBaseRadius,
//                                      int epidermisCellNum,
                                      double variationRatio,
                                      int setUResolution,
                                      int setVResolution,
                                      int setWResolution,
                                      int sliceNum )

{  /// first: get boundaryRadius from rsSourceCorticalDB;


   OutputXMLVtpFileName( outputXMLVtpFileNameInput );

   CircleRadiusDB ( epidermisBaseRadius,
                    epidermisAddRadiusData);

   SetObjectXYZRadiusRatio();

   SetObjectOpacity();

   ObjectVerticalDB( epidermisAddRadiusData );

   EpidermisCellNumCalculate( epidermisAddRadiusData );

   GetRandomCircleSegmentAndCircleXYNonuniformDB
   ( epidermisAddRadiusData,
     epidermisBaseRadius,
//     epidermisCellNum,
     variationRatio );

   CircleSegmentLengthAdjustRatioDB();

   ObjectHeightAndZPositionDB( sliceNum );

   SetSuperEllipsoidResolution( setUResolution, setVResolution, setWResolution );

   MapRGB();
}
