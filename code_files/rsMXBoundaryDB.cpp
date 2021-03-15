#define _USE_MATH_DEFINES
#include <cmath> 
#include "rsMXBoundaryDB.h"

/// Boundary = outestRingBoundary;

/** boundaryRotateRadian
 *
 * \param vector<double> centerRingRotateRadian;
 * \return vector<double> boundaryRotateRadian;
 *
 */

void rsMXBoundaryDB::BoundaryRotateRadian()
{  vector<double>::iterator itVec;
   double temp;
   for ( itVec = centerRingRotateRadian.begin();  itVec != centerRingRotateRadian.end(); itVec++ )
   {  temp = *itVec + M_PI;
      boundaryRotateRadian.push_back( temp );
   }
}

/** radianUniformDB
 *
 * \param int dotNum;
 * \return vector<double> radianUniformDB;
 *
 */

void rsMXBoundaryDB::RadianUniformDB( int dotNum )
{  double temp;
   int i;

   //ofstream fout("a.txt",ios::app);
   //fout << "RadianUniformDB" << endl;
   for ( i = 0, temp = 0; i != dotNum; i++ )
   {  temp = 2 * M_PI * i / dotNum;
      radianUniformDB.push_back( temp );
      //fout << "i: " << temp << endl;
   }
}

/** boundaryPointRotateRadianDB
 *
 * \param vector<double> boundaryRotateRadian;
 * \param vector<double> radianUniformDB;
 * \return map<int, vector<double> > boundaryPointRotateRadianDB;
 *
 */

void rsMXBoundaryDB::BoundaryPointRotateRadianDB()
{  vector<double>::iterator itVecRotate;
   vector<double>::iterator itVecUniform;
   vector<double> boundaryPointRotateRadian;
   int i;
   int j;
   double temp;
   //ofstream fout("a.txt",ios::app);
   //fout << "BoundaryPointRotateRadianDB" << endl;
   for ( itVecRotate = boundaryRotateRadian.begin(), i = 0;
         itVecRotate != boundaryRotateRadian.end();
         itVecRotate++, i++ )
   {  boundaryPointRotateRadian.clear();
      for ( itVecUniform = radianUniformDB.begin(), j = 0;
            itVecUniform != radianUniformDB.end();
            itVecUniform++, j++ )
      {  temp = *itVecUniform + *itVecRotate;
         boundaryPointRotateRadian.push_back( temp );
         //fout << "i: " << i << "  j: " << j << "  temp: " << temp << endl;
      }
      boundaryPointRotateRadianDB.insert
      ( pair<int, vector<double> >(i, boundaryPointRotateRadian) );
   }
}


/** BoundaryPointXYLeftAndRightHemisphere
 *
 * \param vector<double> boundaryRadiusDB;
 * \param int dotNum;
 * \param vector<double> centerX;
 * \param vector<double> centerY;
 * \param map<int, vector<double> > boundaryPointRotateRadianDB;
 * \return map<int, vector<double> > boundaryPointXLeftHemisphereDB;
 * \return map<int, vector<double> > boundaryPointYLeftHemisphereDB;
 * \return map<int, vector<double> > boundaryPointXRightHemisphereDB;
 * \return map<int, vector<double> > boundaryPointYRightHemisphereDB;
 *
 */

void rsMXBoundaryDB::BoundaryPointXYLeftAndRightHemisphere( int dotNum )
{  int halfDotNum = dotNum / 2;
   int i;
   int j;
   double tempX;
   double tempY;
   vector<double> boundaryPointXLeftHemisphere;
   vector<double> boundaryPointYLeftHemisphere;
   vector<double> boundaryPointXRightHemisphere;
   vector<double> boundaryPointYRightHemisphere;

   vector<double>::iterator itVec;

   //ofstream fout("a.txt",ios::app);
   //fout << "BoundaryPointXYLeftAndRightHemisphere" << endl;
   /// Right;
   //fout << "Right" << endl;
   for ( itVec = boundaryRadiusDB.begin(), i = 0;
         itVec != boundaryRadiusDB.end();
         itVec++, i++ )
   {  boundaryPointXRightHemisphere.clear();
      boundaryPointYRightHemisphere.clear();
      for ( j = 0; j != halfDotNum; j++ )
      {  tempX = (*itVec) * cos( boundaryPointRotateRadianDB[i][j] ) + centerX[i];
         boundaryPointXRightHemisphere.push_back( tempX );
         tempY = (*itVec) * sin( boundaryPointRotateRadianDB[i][j] ) + centerY[i];
         boundaryPointYRightHemisphere.push_back( tempY );
         //fout << "i: " << i << "  j: " << j << "  tempX: " << tempX << endl;
         //fout << "i: " << i << "  j: " << j << "  tempY: " << tempY << endl;
      }
      boundaryPointXRightHemisphereDB.insert
      ( pair<int, vector<double> >(i, boundaryPointXRightHemisphere) );
      boundaryPointYRightHemisphereDB.insert
      ( pair<int, vector<double> >(i, boundaryPointYRightHemisphere) );
   }
   /// Left;
   //fout << "Left" << endl;
   for ( itVec = boundaryRadiusDB.begin(), i = 0;
         itVec != boundaryRadiusDB.end();
         itVec++, i++ )
   {  boundaryPointXLeftHemisphere.clear();
      boundaryPointYLeftHemisphere.clear();
      for ( j = halfDotNum; j != dotNum; j++ )
      {  tempX = (*itVec) * cos( boundaryPointRotateRadianDB[i][j] ) + centerX[i];
         boundaryPointXLeftHemisphere.push_back( tempX );
         tempY = (*itVec) * sin( boundaryPointRotateRadianDB[i][j] ) + centerY[i];
         boundaryPointYLeftHemisphere.push_back( tempY );
         //fout << "i: " << i << "  j: " << j << "  tempX: " << tempX << endl;
         //fout << "i: " << i << "  j: " << j << "  tempY: " << tempY << endl;
      }
      boundaryPointXLeftHemisphereDB.insert
      ( pair<int, vector<double> >(i, boundaryPointXLeftHemisphere) );
      boundaryPointYLeftHemisphereDB.insert
      ( pair<int, vector<double> >(i, boundaryPointYLeftHemisphere) );
   }
}

/** boundaryHalfCentralRadianDB
 *
 * \param vector<double> boundaryRadiusDB;
 * \param vector<double> centerXYRadiusDB;
 * \return vector<double> boundaryHalfCentralRadianDB;
 *
 */

void rsMXBoundaryDB::BoundaryHalfCentralRadianDB()
{  vector<double>::iterator itVec;
   double sinHalfCentralRadian;
   double asinHalfCentralRadian;
   int i;
   ofstream fout("a.txt",ios::app);
   fout << "BoundaryHalfCentralRadianDB" << endl;
   for ( itVec = boundaryRadiusDB.begin(), i = 0; itVec != boundaryRadiusDB.end(); itVec++, i++ )
   {  sinHalfCentralRadian = *itVec / centerXYRadiusDB[i];
      asinHalfCentralRadian = asin(sinHalfCentralRadian);
      boundaryHalfCentralRadianDB.push_back( asinHalfCentralRadian );
      fout << "i: " << i << "  " << asinHalfCentralRadian << endl;
   }
}

/** boundaryRadianStartDB, boundaryRadianEndDB and boundaryCentralRadianDB;
 *
 * \param vector<double> centerRingRotateRadian;
 * \param vector<double> boundaryHalfCentralRadianDB;
 * \return vector<double> boundaryRadianStartDB;
 * \return vector<double> boundaryRadianEndDB;
 * \return vector<double> boundaryCentralRadianDB;
 *
 */

void rsMXBoundaryDB::BoundaryRadianStartAndEndDB()
{  vector<double>::iterator itVec;
   int i;
   for ( itVec = centerRingRotateRadian.begin(), i = 0;
         itVec != centerRingRotateRadian.end();
         itVec++, i++ )
   {  boundaryRadianStartDB.push_back( *itVec - boundaryHalfCentralRadianDB[i] );
      boundaryRadianEndDB.push_back( *itVec + boundaryHalfCentralRadianDB[i] );
      boundaryCentralRadianDB.push_back( boundaryHalfCentralRadianDB[i] * 2 );
   }
}

/** boundaryMaxCenterRadiusDB and boundaryMinCenterRadiusDB
 *
 * \param vector<double> centerXYRadiusDB;
 * \param vector<double> boundaryRadiusDB;
 * \return vector<double> boundaryMaxCenterRadiusDB;
 * \return vector<double> boundaryMinCenterRadiusDB;
 *
 */

void rsMXBoundaryDB::BoundaryMaxAndMinCenterRadiusDB()
{  vector<double>::iterator itVec;
   int i;
   double min;
   double max;
   ofstream fout( "a.txt", ios::app );
   fout << "BoundaryMaxAndMinCenterRadiusDB" << endl;
   for ( itVec = centerXYRadiusDB.begin(), i = 0;
         itVec != centerXYRadiusDB.end();
         itVec++, i++ )
   {  min = *itVec - boundaryRadiusDB[i];
      max = *itVec + boundaryRadiusDB[i];

      boundaryMinCenterRadiusDB.push_back( min );
      boundaryMaxCenterRadiusDB.push_back( max );
      fout << "Min: " << min << endl;
      fout << "Max: " << max << endl;
   }
}



/** boundaryTangentCenterRadiusDB
 *
 * \param vector<double> centerXYRadiusDB;
 * \param vector<double> boundaryRadiusDB;
 * \return vector<double> boundaryTangentCenterRadiusDB;
 *
 */

void rsMXBoundaryDB::BoundaryTangentCenterRadiusDB()
{  vector<double>::iterator itVec;
   int i;
   double temp;
   for ( itVec = centerXYRadiusDB.begin(), i = 0;
         itVec != centerXYRadiusDB.end();
         itVec++, i++ )
   {  temp = pow( pow( *itVec, 2 ) - pow( boundaryRadiusDB[i], 2 ), 0.5 );
      boundaryTangentCenterRadiusDB.push_back( temp );
   }
}

/** boundaryTangentUpLengthDB and boundaryTangentDownLengthDB;
 *
 * \param vector<double> boundaryTangentCenterRadiusDB;
 * \param vector<double> boundaryMaxCenterRadiusDB;
 * \param vector<double> boundaryMinCenterRadiusDB;
 * \param vector<double> boundaryMaxCenterRadiusDB;
 * \param vector<double> boundaryMinCenterRadiusDB;
 * \return vector<double> boundaryTangentUpLengthDB;
 * \return vector<double> boundaryTangentDownLengthDB;
 */

void rsMXBoundaryDB::BoundaryTangentUpAndDownLengthDB()
{  vector<double>::iterator itVec;
   int i;
   double tempUp;
   double tempDown;
   for ( itVec = boundaryTangentCenterRadiusDB.begin(), i = 0;
         itVec != boundaryTangentCenterRadiusDB.end();
         itVec++, i++ )
   {  tempUp = *itVec - boundaryMinCenterRadiusDB[i];
      boundaryTangentUpLengthDB.push_back( tempUp );

      tempDown = boundaryMaxCenterRadiusDB[i] - *itVec;
      boundaryTangentDownLengthDB.push_back( tempDown );
   }
}

/** SetUpAndDownRowNum
 *
 * \param int setUpRowNum;
 * \param int setDownRowNum;
 * \return int upRowNum;
 * \return int downRowNum;
 * \return double validUpRowNum;
 * \return double validDownRowNum;
 *
 */

void rsMXBoundaryDB::SetUpAndDownRowNum( int setUpRowNum, int setDownRowNum )
{  double tempUpNum;
   double tempDownNum;
   upRowNum = setUpRowNum;
   downRowNum = setDownRowNum;

   tempUpNum = ceil( double(1) / double(2) * double(upRowNum) );
   tempDownNum = ceil( double(2) / double(3) * double(downRowNum) );
   validUpRowNum = tempUpNum;
   validDownRowNum = tempDownNum;
   //cout << "validUpRowNum: " << validUpRowNum << "  validDownRowNum: " << validDownRowNum <<endl;
}

/** boundaryTangentUpLengthSegmentDB and boundaryTangentDownLengthSegmentDB
 *
 * \param vector<double> boundaryTangentUpLengthDB;
 * \param vector<double> boundaryTangentDownLengthDB;
 * \param vector<double> boundaryTangentCenterRadiusDB;
 * \param int upRowNum;
 * \param int downRowNum;
 * \return vector<double> boundaryTangentUpLengthSegmentDB;
 * \return vector<double> boundaryTangentDownLengthSegmentDB;
 *
 */

void rsMXBoundaryDB::BoundaryTangentUpAndDownLengthSegmentDB()
{  vector<double>::iterator itVec;
   int i;
   double tempUp;
   double tempDown;
   ofstream fout("a.txt",ios::app);
   fout << "boundaryTangentLengthSegmentDB: " << endl;
   for ( itVec = boundaryTangentCenterRadiusDB.begin(), i = 0;
         itVec != boundaryTangentCenterRadiusDB.end();
         itVec++, i++ )
   {  tempUp = boundaryTangentUpLengthDB[i] / upRowNum;
      boundaryTangentUpLengthSegmentDB.push_back( tempUp );

      tempDown = boundaryTangentDownLengthDB[i] / downRowNum;
      boundaryTangentDownLengthSegmentDB.push_back( tempDown );
      fout << "i: " << i << "  tempUp: " << tempUp << endl;
      fout << "i: " << i << "  tempDown: " << tempDown << endl;
   }
}

/** boundaryTangentUpLengthSegmentAppendRadiusDB and boundaryTangentDownLengthSegmentAppendRadiusDB;
 *
 * \param vector<double> boundaryTangentUpLengthSegmentDB;
 * \param vector<double> boundaryTangentDownLengthSegmentDB;
 * \param vector<double> boundaryMaxCenterRadiusDB;
 * \param vector<double> boundaryMinCenterRadiusDB;
 * \return map<int, vector<double> > boundaryTangentUpLengthSegmentAppendRadiusDB;
 * \return map<int, vector<double> > boundaryTangentDownLengthSegmentAppendRadiusDB;
 *
 */

void rsMXBoundaryDB::BoundaryTangentUpAndDownLengthSegmentAppendRadiusDB()
{  vector<double>::iterator itVec;
   vector<double> boundaryTangentUpLengthSegmentAppendRadius;
   vector<double> boundaryTangentDownLengthSegmentAppendRadius;
   int i;
   int j;
   double tempUp;
   double tempDown;
   ofstream fout("a.txt",ios::app);
   fout << "BoundaryTangentUpAndDownLengthSegmentAppendRadiusDB" << endl;
   fout << "Up" << endl;
   /// Up;
   for ( itVec = boundaryMinCenterRadiusDB.begin(), i = 0;
         itVec != boundaryMinCenterRadiusDB.end();
         itVec++, i++ )
   {  boundaryTangentUpLengthSegmentAppendRadius.clear();
      for ( j = 0; j != validUpRowNum; j++ )
      {  tempUp = boundaryMinCenterRadiusDB[i] + boundaryTangentUpLengthSegmentDB[i] * (j+1);
         boundaryTangentUpLengthSegmentAppendRadius.push_back( tempUp );
         fout << "i: " << i << "  j: " << j << "  tempUp: " << tempUp << endl;
      }
      boundaryTangentUpLengthSegmentAppendRadiusDB.insert
      ( pair<int, vector<double> >( i, boundaryTangentUpLengthSegmentAppendRadius ) );
   }
   /// Down;
   fout << "Down" << endl;
   for ( itVec = boundaryMaxCenterRadiusDB.begin(), i = 0;
         itVec != boundaryMaxCenterRadiusDB.end();
         itVec++, i++ )
   {  boundaryTangentDownLengthSegmentAppendRadius.clear();
      for ( j = 0; j != validDownRowNum; j++ )
      {  tempDown = boundaryMaxCenterRadiusDB[i] - boundaryTangentDownLengthSegmentDB[i] * (j+1);
         boundaryTangentDownLengthSegmentAppendRadius.push_back( tempDown );
         fout << "i: " << i << "  j: " << j << "  tempDown: " << tempDown << endl;
      }
      boundaryTangentDownLengthSegmentAppendRadiusDB.insert
      ( pair<int, vector<double> >( i, boundaryTangentDownLengthSegmentAppendRadius ) );
   }
}

/** boundaryPointRightHemisphereCenterDistance
 *  :the distance between point in boundary and the centre of the slice;
 *
 * \param map<int, vector<double> > boundaryPointXRightHemisphereDB;
 * \param map<int, vector<double> > boundaryPointYRightHemisphereDB;
 * \return map<int, vector<double> > boundaryPointRightHemisphereCenterDistanceDB;
 *
 */

void rsMXBoundaryDB::BoundaryPointRightHemisphereCenterDistanceDB()
{  map<int, vector<double> >::iterator itMapX;
   map<int, vector<double> >::iterator itMapY;
   vector<double>::iterator itVecX;
   vector<double>::iterator itVecY;
   vector<double> boundaryPointRightHemisphereCenterDistance;
   double temp;
   int i;
   int j;
   ofstream fout("a.txt",ios::app);
   fout << "BoundaryPointRightHemisphereCenterDistanceDB" << endl;

   for ( itMapX = boundaryPointXRightHemisphereDB.begin(),
         itMapY = boundaryPointYRightHemisphereDB.begin(), i = 0;
         itMapX != boundaryPointXRightHemisphereDB.end();
         itMapX++, itMapY++, i++ )
   {  boundaryPointRightHemisphereCenterDistance.clear();
      for ( itVecX = (*itMapX).second.begin(), itVecY = (*itMapY).second.begin(), j = 0;
            itVecX != (*itMapX).second.end();
            itVecX++, itVecY++, j++ )
      {  temp = pow( pow( *itVecX, 2 ) + pow( *itVecY, 2 ), 0.5 );
         boundaryPointRightHemisphereCenterDistance.push_back( temp );
         fout << "i: " << i << "  j: " << j << "  temp: " << temp << " X: " << *itVecX << " Y: " << *itVecY << endl;
      }
      boundaryPointRightHemisphereCenterDistanceDB.insert
      ( pair<int, vector<double> >( i, boundaryPointRightHemisphereCenterDistance ) );
   }
}

/** Search points that equal to boundaryTangentUpAndDownRightLengthSegmentAppendRadiusDB
 *  and record the postions of the target points;
 *  according to boundaryTangentUpLengthSegmentAppendRadiusDB and boundaryTangentDownLengthSegmentAppendRadiusDB;
 *
 * \param map<int, vector<double> > boundaryTangentUpLengthSegmentAppendRadiusDB;
 * \param map<int, vector<double> > boundaryTangentDownLengthSegmentAppendRadiusDB;
 * \param map<int, vector<double> > boundaryPointRightHemisphereCenterDistanceDB;
 * \param map<int, vector<double> > boundaryPointXRightHemisphereDB;
 * \param map<int, vector<double> > boundaryPointYRightHemisphereDB;

 * \return map<int, vector<double> > boundaryPointRightUpXHemisphereTarget;
 * \return map<int, vector<double> > boundaryPointRightUpYHemisphereTarget;
 * \return map<int, vector<double> > boundaryPointRightDownXHemisphereTarget;
 * \return map<int, vector<double> > boundaryPointRightDownYHemisphereTarget;
 *
 */

void rsMXBoundaryDB::BoundaryPointRightUpDownXYHemisphereTargetDB()
{  map<int, vector<double> >::iterator itMap;
   vector<double>::iterator itVec;
   vector<double>::iterator itVecDistance;
   int i;
   int j;
   int k;
   double temp;
   double best;
   double tempX;
   double tempY;
   int record;
   vector<double> boundaryPointRightUpXHemisphereTarget;
   vector<double> boundaryPointRightUpYHemisphereTarget;
   vector<double> boundaryPointRightDownXHemisphereTarget;
   vector<double> boundaryPointRightDownYHemisphereTarget;

   ofstream fout("a.txt",ios::app);
   fout << "BoundaryPointRightUpDownXYHemisphereTargetDB" << endl;
   fout << "Up" << endl;
   /// Up;
   for ( itMap = boundaryTangentUpLengthSegmentAppendRadiusDB.begin(), i = 0;
         itMap != boundaryTangentUpLengthSegmentAppendRadiusDB.end();
         itMap++, i++ )
   {  boundaryPointRightUpXHemisphereTarget.clear();
      boundaryPointRightUpYHemisphereTarget.clear();
      for ( itVec = (*itMap).second.begin(), j = 0;
            itVec != (*itMap).second.end();
            itVec++, j++ )
      {  best = 100;
         for ( itVecDistance = boundaryPointRightHemisphereCenterDistanceDB[i].begin(), k = 0;
               itVecDistance != boundaryPointRightHemisphereCenterDistanceDB[i].end();
               itVecDistance++, k++ )
         {  temp = fabs( *itVecDistance - *itVec );
            if ( best > temp )
            {  best = temp;
               record = k;
            }
         }
         tempX = boundaryPointXRightHemisphereDB[i][record];
         tempY = boundaryPointYRightHemisphereDB[i][record];
         boundaryPointRightUpXHemisphereTarget.push_back( tempX );
         boundaryPointRightUpYHemisphereTarget.push_back( tempY );
         fout << "i: " << i << "  j: " << j << "  tempX: " << tempX << "  tempY: " << tempY
              << "   record: " << record << endl;
      }
      boundaryPointRightUpXHemisphereTargetDB.insert
      ( pair<int, vector<double> >( i, boundaryPointRightUpXHemisphereTarget ) );
      boundaryPointRightUpYHemisphereTargetDB.insert
      ( pair<int, vector<double> >( i, boundaryPointRightUpYHemisphereTarget ) );
   }
   /// Down;
   fout << "Down" << endl;
   for ( itMap = boundaryTangentDownLengthSegmentAppendRadiusDB.begin(), i = 0;
         itMap != boundaryTangentDownLengthSegmentAppendRadiusDB.end();
         itMap++, i++ )
   {  boundaryPointRightDownXHemisphereTarget.clear();
      boundaryPointRightDownYHemisphereTarget.clear();
      for ( itVec = (*itMap).second.begin(), j = 0;
            itVec != (*itMap).second.end();
            itVec++, j++ )
      {  best = 100;
         for ( itVecDistance = boundaryPointRightHemisphereCenterDistanceDB[i].begin(), k = 0;
               itVecDistance != boundaryPointRightHemisphereCenterDistanceDB[i].end();
               itVecDistance++, k++ )
         {  temp = fabs( *itVecDistance - *itVec );
            if ( best > temp )
            {  best = temp;
               record = k;
            }
         }
         tempX = boundaryPointXRightHemisphereDB[i][record];
         tempY = boundaryPointYRightHemisphereDB[i][record];
         boundaryPointRightDownXHemisphereTarget.push_back( tempX );
         boundaryPointRightDownYHemisphereTarget.push_back( tempY );
         fout << "i: " << i << "  j: " << j << "  tempX: " << tempX << "  tempY: " << tempY
              << "   record: " << record << endl;
      }
      boundaryPointRightDownXHemisphereTargetDB.insert
      ( pair<int, vector<double> >( i, boundaryPointRightDownXHemisphereTarget ) );
      boundaryPointRightDownYHemisphereTargetDB.insert
      ( pair<int, vector<double> >( i, boundaryPointRightDownYHemisphereTarget ) );
   }
}

/** boundaryRadianStartPointXDB and boundaryRadianStartPointYDB
    the PointXYDB is used to calculate the vector, so the length is not matter,
    then we used the length in centerXYRadiusDB;
 *
 * \param vector<double> centerXYRadiusDB;
 * \param vector<double> boundaryRadianStartDB;
 * \return vector<double> boundaryRadianStartPointXDB;
 * \return vector<double> boundaryRadianStartPointYDB;
 *
 */

void rsMXBoundaryDB::BoundaryRadianStartPointXYDB()
{  vector<double>::iterator itVecCenter;
   vector<double>::iterator itVecStart;
   double tempX;
   double tempY;
   int i;
   ofstream fout("a.txt",ios::app);
   fout << "BoundaryRadianStartPointXYDB" << endl;
   for ( itVecCenter = centerXYRadiusDB.begin(), itVecStart = boundaryRadianStartDB.begin(), i = 0;
         itVecCenter != centerXYRadiusDB.end();
         itVecCenter++, itVecStart++, i++ )
   {  tempX = (*itVecCenter) * cos( *itVecStart );
      tempY = (*itVecCenter) * sin( *itVecStart );
      boundaryRadianStartPointXDB.push_back( tempX );
      boundaryRadianStartPointYDB.push_back( tempY );
      fout << "i: " << i << "  tempX: " << tempX << "  tempY: " <<  tempY << endl;
   }
}

/** boundaryPointRightHemisphereTargetIntersectionRadian;
    the intersection angle between boundaryPointRightXYHemisphereTarget and boundaryRadianStartPoint;
 *
 * \param map<int, vector<double> > boundaryPointRightUpXHemisphereTargetDB;
 * \param map<int, vector<double> > boundaryPointRightUpYHemisphereTargetDB;
 * \param map<int, vector<double> > boundaryPointRightDownXHemisphereTargetDB;
 * \param map<int, vector<double> > boundaryPointRightDownYHemisphereTargetDB;
 * \param vector<double> boundaryRadianStartPointXDB;
 * \param vector<double> boundaryRadianStartPointYDB;
 * \return map<int, vector<double> > boundaryPointRightUpHemisphereTargetIntersectionRadianDB;
 * \return map<int, vector<double> > boundaryPointRightDownHemisphereTargetIntersectionRadianDB;
 *
 */

void rsMXBoundaryDB::BoundaryPointRightUpAndDownHemisphereTargetIntersectionRadianDB()
{  map<int, vector<double> >::iterator itMapX;
   vector<double>::iterator itVecX;
   map<int, vector<double> >::iterator itMapY;
   vector<double>::iterator itVecY;
   int i;
   int j;
   double temp;
   double acosTemp;
   vector<double> boundaryPointRightUpHemisphereTargetIntersectionRadian;
   vector<double> boundaryPointRightDownHemisphereTargetIntersectionRadian;

   ofstream fout("a.txt",ios::app);
   fout << "BoundaryPointRightUpAndDownHemisphereTargetIntersectionRadianDB: " << endl;

   /// Up;
   fout << "Up" << endl;
   for ( itMapX = boundaryPointRightUpXHemisphereTargetDB.begin(), i = 0,
         itMapY = boundaryPointRightUpYHemisphereTargetDB.begin();
         itMapX != boundaryPointRightUpXHemisphereTargetDB.end();
         itMapX++, itMapY++, i++ )
   {  boundaryPointRightUpHemisphereTargetIntersectionRadian.clear();
      for ( itVecX = (*itMapX).second.begin(), j = 0, itVecY = (*itMapY).second.begin();
            itVecX != (*itMapX).second.end();
            itVecX++, itVecY++, j++ )
      {  temp = ( (*itVecX) *  boundaryRadianStartPointXDB[i] + (*itVecY) * boundaryRadianStartPointYDB[i] )
                / ( pow( pow(*itVecX, 2) + pow(*itVecY, 2), 0.5 )
                    * pow( pow(boundaryRadianStartPointXDB[i], 2) + pow(boundaryRadianStartPointYDB[i], 2), 0.5 ) );
         acosTemp = acos( temp );
         boundaryPointRightUpHemisphereTargetIntersectionRadian.push_back( acosTemp );
         fout << "i: " << i << "  j: " << j << "  Up: " << acosTemp << endl;
      }
      boundaryPointRightUpHemisphereTargetIntersectionRadianDB.insert
      ( pair<int, vector<double> >( i, boundaryPointRightUpHemisphereTargetIntersectionRadian ) );
   }
   fout << "Down" << endl;
   /// Down;
   for ( itMapX = boundaryPointRightDownXHemisphereTargetDB.begin(), i = 0,
         itMapY = boundaryPointRightDownYHemisphereTargetDB.begin();
         itMapX != boundaryPointRightDownXHemisphereTargetDB.end();
         itMapX++, itMapY++, i++ )
   {  boundaryPointRightDownHemisphereTargetIntersectionRadian.clear();
      for ( itVecX = (*itMapX).second.begin(), j = 0, itVecY = (*itMapY).second.begin();
            itVecX != (*itMapX).second.end();
            itVecX++, itVecY++, j++ )
      {  temp = ( (*itVecX) *  boundaryRadianStartPointXDB[i] + (*itVecY) * boundaryRadianStartPointYDB[i] )
                / ( pow( pow(*itVecX, 2) + pow(*itVecY, 2), 0.5 )
                    * pow( pow(boundaryRadianStartPointXDB[i], 2) + pow(boundaryRadianStartPointYDB[i], 2), 0.5 ) );
         acosTemp = acos( temp );
         boundaryPointRightDownHemisphereTargetIntersectionRadian.push_back( acosTemp );
         fout << "i: " << i << "  j: " << j << "  Down: " << acosTemp << endl;
      }
      boundaryPointRightDownHemisphereTargetIntersectionRadianDB.insert
      ( pair<int, vector<double> >( i, boundaryPointRightDownHemisphereTargetIntersectionRadian ) );
   }
}

/** boundaryPointRightUpAndDownHemisphereTargetCenterRadian
 ** boundaryPointLeftUpAndDownHemisphereTargetCenterRadian
 *
 * \param vector<double> boundaryRadianStartDB;
 * \param vector<double> boundaryRadianEndDB;
 * \param map<int, vector<double> > boundaryPointRightUpAndDownHemisphereTargetIntersectionRadianDB;
 * \param map<int, vector<double> > boundaryPointRightDownAndDownHemisphereTargetIntersectionRadianDB;
 * \return map<int, vector<double> > boundaryPointRightUpHemisphereTargetCenterRadian;
 * \return map<int, vector<double> > boundaryPointRightDownHemisphereTargetCenterRadian;
 * \return map<int, vector<double> > boundaryPointLeftUpHemisphereTargetCenterRadianDB;
 * \return map<int, vector<double> > boundaryPointLeftDownHemisphereTargetCenterRadianDB;
 *
 */

void rsMXBoundaryDB::BoundaryPointRightAndLeftUpAndDownHemisphereTargetCenterRadian()
{  map<int, vector<double> >::iterator itMap;
   vector<double>::iterator itVec;

   int i;
   double tempLeft;
   double tempRight;

   vector<double> boundaryPointRightUpHemisphereTargetCenterRadian;
   vector<double> boundaryPointRightDownHemisphereTargetCenterRadian;
   vector<double> boundaryPointLeftUpHemisphereTargetCenterRadian;
   vector<double> boundaryPointLeftDownHemisphereTargetCenterRadian;
   /// Calculate up;
   for ( itMap = boundaryPointRightUpHemisphereTargetIntersectionRadianDB.begin(), i = 0;
         itMap != boundaryPointRightUpHemisphereTargetIntersectionRadianDB.end();
         itMap++, i++ )
   {  boundaryPointRightUpHemisphereTargetCenterRadian.clear();
      boundaryPointLeftUpHemisphereTargetCenterRadian.clear();
      for ( itVec = (*itMap).second.begin();
            itVec != (*itMap).second.end();
            itVec++ )
      {  tempRight = boundaryRadianStartDB[i] + *itVec;
         tempLeft =  boundaryRadianEndDB[i] - *itVec;
         boundaryPointRightUpHemisphereTargetCenterRadian.push_back( tempRight );
         boundaryPointLeftUpHemisphereTargetCenterRadian.push_back( tempLeft );
      }
      boundaryPointRightUpHemisphereTargetCenterRadianDB.insert
      ( pair<int, vector<double> >( i, boundaryPointRightUpHemisphereTargetCenterRadian ) );
      boundaryPointLeftUpHemisphereTargetCenterRadianDB.insert
      ( pair<int, vector<double> >( i, boundaryPointLeftUpHemisphereTargetCenterRadian ) );
   }
   /// Calculate down;
   for ( itMap = boundaryPointRightDownHemisphereTargetIntersectionRadianDB.begin(), i = 0;
         itMap != boundaryPointRightDownHemisphereTargetIntersectionRadianDB.end();
         itMap++, i++ )
   {  boundaryPointRightDownHemisphereTargetCenterRadian.clear();
      boundaryPointLeftDownHemisphereTargetCenterRadian.clear();
      for ( itVec = (*itMap).second.begin();
            itVec != (*itMap).second.end();
            itVec++ )
      {  tempRight = boundaryRadianStartDB[i] + *itVec;
         tempLeft =  boundaryRadianEndDB[i] - *itVec;
         boundaryPointRightDownHemisphereTargetCenterRadian.push_back( tempRight );
         boundaryPointLeftDownHemisphereTargetCenterRadian.push_back( tempLeft );
      }
      boundaryPointRightDownHemisphereTargetCenterRadianDB.insert
      ( pair<int, vector<double> >( i, boundaryPointRightDownHemisphereTargetCenterRadian ) );
      boundaryPointLeftDownHemisphereTargetCenterRadianDB.insert
      ( pair<int, vector<double> >( i, boundaryPointLeftDownHemisphereTargetCenterRadian ) );
   }

}

/** BoundaryUpAndDownCellObjectVerticalDB
 *
 * \param vector<double> boundaryTangentUpLengthSegmentDB;
 * \param vector<double> boundaryTangentDownLengthSegmentDB;
 * \return vector<double> boundaryUpCellObjectVerticalDB;
 * \return vector<double> boundaryDownCellObjectVerticalDB;
 *
 */

void rsMXBoundaryDB::BoundaryUpAndDownCellObjectVerticalDB()
{  vector<double>::iterator itVecUp;
   vector<double>::iterator itVecDown;
   double tempUp;
   double tempDown;
   ofstream fout("a.txt",ios::app);
   fout << "UpAndDownCellObjectVerticalDB: " << endl;
   for ( itVecUp = boundaryTangentUpLengthSegmentDB.begin(), itVecDown = boundaryTangentDownLengthSegmentDB.begin();
         itVecUp != boundaryTangentUpLengthSegmentDB.end();
         itVecUp++, itVecDown++ )
   {  tempUp = *itVecUp / 2;
      tempDown = *itVecDown /2;
      boundaryUpCellObjectVerticalDB.push_back( tempUp );
      boundaryDownCellObjectVerticalDB.push_back( tempDown );
      fout << "  tempUp: " << tempUp  << "  tempDown: " << tempDown << endl;
   }
}

/** BoundaryUpAndDownCellCenterRadiusDB
    the radius between the centre of slice and the centre of cell;
 *
 * \param map<int, vector<double> > boundaryTangentUpLengthSegmentAppendRadiusDB;
 * \param map<int, vector<double> > boundaryTangentDownLengthSegmentAppendRadiusDB;
 * \param vector<double> boundaryTangentUpLengthSegmentDB;
 * \param vector<double> boundaryTangentDownLengthSegmentDB;
 * \return map<int, vector<double> > boundaryUpCellCenterRadiusDB;
 * \return map<int, vector<double> > boundaryDownCellCenterRadiusDB;
 *
 */

void rsMXBoundaryDB::BoundaryUpAndDownCellCenterRadiusDB()
{  map<int, vector<double> >::iterator itMapUp;
   map<int, vector<double> >::iterator itMapDown;
   vector<double>::iterator itVecUp;
   vector<double>::iterator itVecDown;
   vector<double> boundaryUpCellCenterRadius;
   vector<double> boundaryDownCellCenterRadius;
   double tempUp;
   double tempDown;
   int i;
   int j;
   ofstream fout("a.txt",ios::app);
   fout << "boundaryCellCenterRadiusDB" << endl;
   /// Up;
   fout << "Up" << endl;
   for ( itMapUp = boundaryTangentUpLengthSegmentAppendRadiusDB.begin(), i = 0;
         itMapUp != boundaryTangentUpLengthSegmentAppendRadiusDB.end();
         itMapUp++, i++ )
   {  boundaryUpCellCenterRadius.clear();
      for ( itVecUp = (*itMapUp).second.begin(), j = 0; itVecUp != (*itMapUp).second.end(); itVecUp++, j++ )
      {  tempUp = *itVecUp - boundaryTangentUpLengthSegmentDB[i] / 2;
         boundaryUpCellCenterRadius.push_back( tempUp );
         fout << "i: " << i << "  j: " << j << "  tempUp: " << tempUp << endl;
      }
      boundaryUpCellCenterRadiusDB.insert
      ( pair<int, vector<double> >( i, boundaryUpCellCenterRadius ) );
   }
   /// Down;
   fout << "Down" << endl;
   for ( itMapDown = boundaryTangentDownLengthSegmentAppendRadiusDB.begin(), i = 0;
         itMapDown != boundaryTangentDownLengthSegmentAppendRadiusDB.end();
         itMapDown++, i++ )
   {  boundaryDownCellCenterRadius.clear();
      for ( itVecDown = (*itMapDown).second.begin(), j = 0; itVecDown != (*itMapDown).second.end(); itVecDown++, j++ )
      {  tempDown = *itVecDown + boundaryTangentDownLengthSegmentDB[i] / 2;
         boundaryDownCellCenterRadius.push_back( tempDown );
         fout << "i: " << i << "  j: " << j << "  tempDown: " << tempDown << endl;
      }
      boundaryDownCellCenterRadiusDB.insert
      ( pair<int, vector<double> >( i, boundaryDownCellCenterRadius ) );
   }
}

/** appendCellUpAndDownNumDB;
 *
 * \param double upDotNum;
 * \param double downDotNum;
 * \return vector<double> boundaryCellUpNumDB;
 * \return vector<double> boundaryCellDownNumDB;
 *
 */

/// ceil: Returns the smallest integral value that is not less than x.
void rsMXBoundaryDB::BoundaryCellUpAndDownNumDB()
{  int i;
   int tempRound;
   ofstream fout("a.txt",ios::app);
   fout << "boundaryCellUpNumDB" << endl;
   for ( i = validUpRowNum; i != 0; i-- )
   {  tempRound = ceil( double(i) / double(2) );
      boundaryCellUpNumDB.push_back( tempRound );
      fout << "boundaryCellUpNumDB: "  << tempRound << endl;
   }
   for ( i = validDownRowNum; i != 0; i-- )
   {  tempRound = ceil( double(i) / double(1.5) );
      boundaryCellDownNumDB.push_back( tempRound );
   }
}

/** boundaryUpAndDownCellObjectParallelDB;
 *
 * \param map<int, vector<double> > boundaryPointRightUpHemisphereTargetIntersectionRadianDB;
 * \param map<int, vector<double> > boundaryPointRightDownHemisphereTargetIntersectionRadianDB;
 * \param map<int, vector<double> > boundaryUpCellCenterRadiusDB;
 * \param map<int, vector<double> > boundaryDownCellCenterRadiusDB;
 * \param vector<double> boundaryCellUpNumDB;
 * \param vector<double> boundaryCellDownNumDB;
 * \return map<int, vector<double> > boundaryUpCellObjectParallelDB;
 * \return map<int, vector<double> > boundaryDownCellObjectParallelDB;
 *
 */

void rsMXBoundaryDB::BoundaryUpAndDownCellObjectParallelDB()
{  map<int, vector<double> >::iterator itMapUp;
   map<int, vector<double> >::iterator itMapDown;
   vector<double>::iterator itVecUp;
   vector<double>::iterator itVecDown;
   vector<double> boundaryUpCellObjectParallel;
   vector<double> boundaryDownCellObjectParallel;
   double tempUp;
   double tempDown;
   int i;
   int j;

   ofstream fout("a.txt",ios::app);
   fout << "BoundaryUpAndDownCellObjectParallelDB: " << endl;
   /// calculate Up;
   for ( itMapUp = boundaryPointRightUpHemisphereTargetIntersectionRadianDB.begin(), i = 0;
         itMapUp != boundaryPointRightUpHemisphereTargetIntersectionRadianDB.end();
         itMapUp++, i++ )
   {  boundaryUpCellObjectParallel.clear();
      for ( itVecUp = (*itMapUp).second.begin(), j = 0;
            itVecUp != (*itMapUp).second.end();
            itVecUp++, j++ )
      {  tempUp = *itVecUp / (2*M_PI) *CirclePerimeter( boundaryUpCellCenterRadiusDB[i][j] )
                  / boundaryCellUpNumDB[j] / 2;
         boundaryUpCellObjectParallel.push_back( tempUp );
         fout << "boundaryCellUpNumDB[j]: " << j << "  " << boundaryCellUpNumDB[j] << endl;
         fout << "i: " << i << "  j: " << j << "  tempUp: " << tempUp << endl;
      }
      boundaryUpCellObjectParallelDB.insert
      ( pair<int, vector<double> >( i, boundaryUpCellObjectParallel ) );
   }
   /// calculate Down;
   fout << "DownCellObjectParallelDB: " << endl;
   for ( itMapDown = boundaryPointRightDownHemisphereTargetIntersectionRadianDB.begin(), i = 0;
         itMapDown != boundaryPointRightDownHemisphereTargetIntersectionRadianDB.end();
         itMapDown++, i++ )
   {  boundaryDownCellObjectParallel.clear();
      for ( itVecDown = (*itMapDown).second.begin(), j = 0;
            itVecDown != (*itMapDown).second.end();
            itVecDown++, j++ )
      {  tempDown = *itVecDown / (2*M_PI) *CirclePerimeter( boundaryDownCellCenterRadiusDB[i][j] )
                    / boundaryCellDownNumDB[j] / 2;
         boundaryDownCellObjectParallel.push_back( tempDown );
         fout << "boundaryCellDownNumDB[j]: " << j << "  " << boundaryCellDownNumDB[j] << endl;
         fout << "i: " << i << "  j: " << j << "  tempDown: " << tempDown << endl;
      }
      boundaryDownCellObjectParallelDB.insert
      ( pair<int, vector<double> >( i, boundaryDownCellObjectParallel ) );
   }
}

/** boundaryPointRightUpAndDownHemisphereTargetIntersectionRadianDivideDB;
 *
 * \param map<int, vector<double> > boundaryPointRightUpHemisphereTargetIntersectionRadianDB;
 * \param map<int, vector<double> > boundaryPointRightDownHemisphereTargetIntersectionRadianDB;
 * \param vector<double> boundaryCellUpNumDB;
 * \param vector<double> boundaryCellDownNumDB;
 * \return map<int, vector<double> > boundaryPointRightUpHemisphereTargetIntersectionRadianDivideDB;
 * \return map<int, vector<double> > boundaryPointRightDownHemisphereTargetIntersectionRadianDivideDB;
 *
 */

void rsMXBoundaryDB::BoundaryPointRightUpAndDownHemisphereTargetIntersectionRadianDivideDB()
{  map<int, vector<double> >::iterator itMapUp;
   map<int, vector<double> >::iterator itMapDown;
   vector<double>::iterator itVecUp;
   vector<double>::iterator itVecDown;
   vector<double> boundaryPointRightUpHemisphereTargetIntersectionRadianDivide;
   vector<double> boundaryPointRightDownHemisphereTargetIntersectionRadianDivide;
   double tempUp;
   double tempDown;
   int i;
   int j;
   /// Up;
   for ( itMapUp = boundaryPointRightUpHemisphereTargetIntersectionRadianDB.begin(), i = 0;
         itMapUp != boundaryPointRightUpHemisphereTargetIntersectionRadianDB.end();
         itMapUp++, i++ )
   {  boundaryPointRightUpHemisphereTargetIntersectionRadianDivide.clear();
      for ( itVecUp = (*itMapUp).second.begin(), j = 0;
            itVecUp != (*itMapUp).second.end();
            itVecUp++, j++ )
      {  tempUp = *itVecUp / boundaryCellUpNumDB[j];
         boundaryPointRightUpHemisphereTargetIntersectionRadianDivide.push_back( tempUp );
      }
      boundaryPointRightUpHemisphereTargetIntersectionRadianDivideDB.insert
      ( pair<int, vector<double> >( i, boundaryPointRightUpHemisphereTargetIntersectionRadianDivide ) );
   }

   /// Down;
   for ( itMapDown = boundaryPointRightDownHemisphereTargetIntersectionRadianDB.begin(), i = 0;
         itMapDown != boundaryPointRightDownHemisphereTargetIntersectionRadianDB.end();
         itMapDown++, i++ )
   {  boundaryPointRightDownHemisphereTargetIntersectionRadianDivide.clear();
      for ( itVecDown = (*itMapDown).second.begin(), j = 0;
            itVecDown != (*itMapDown).second.end();
            itVecDown++, j++ )
      {  tempDown = *itVecDown / boundaryCellDownNumDB[j];
         boundaryPointRightDownHemisphereTargetIntersectionRadianDivide.push_back( tempDown );
      }
      boundaryPointRightDownHemisphereTargetIntersectionRadianDivideDB.insert
      ( pair<int, vector<double> >( i, boundaryPointRightDownHemisphereTargetIntersectionRadianDivide ) );
   }
}

/** boundaryCellLeftAndRightUpAndDownCenterRadianDB;
 *
 * \param vector<double> boundaryRadianStartDB;
 * \param vector<double> boundaryRadianEndDB;
 * \param map<int, vector<double> > boundaryPointRightUpHemisphereTargetIntersectionRadianDivideDB;
 * \param map<int, vector<double> > boundaryPointRightDownHemisphereTargetIntersectionRadianDivideDB;
 * \param vector<double> boundaryCellUpNumDB;
 * \param vector<double> boundaryCellDownNumDB;
 * \return map<int, vector<vector<double> > > boundaryCellLeftUpCenterRadianDB;
 * \return map<int, vector<vector<double> > > boundaryCellRightUpCenterRadianDB;
 * \return map<int, vector<vector<double> > > boundaryCellLeftDownCenterRadianDB;
 * \return map<int, vector<vector<double> > > boundaryCellRightDownCenterRadianDB;
 *
 */

void rsMXBoundaryDB::BoundaryCellLeftAndRightUpAndDownCenterRadianDB()
{  map<int, vector<double> >::iterator itMapUp;
   map<int, vector<double> >::iterator itMapDown;
   vector<double>::iterator itVecUp;
   vector<double>::iterator itVecDown;
   vector<double> boundaryCellLeftUpCenterRadianVec1;
   vector<double> boundaryCellRightUpCenterRadianVec1;
   vector<double> boundaryCellLeftDownCenterRadianVec1;
   vector<double> boundaryCellRightDownCenterRadianVec1;
   vector<vector<double> > boundaryCellLeftUpCenterRadianVec2;
   vector<vector<double> > boundaryCellRightUpCenterRadianVec2;
   vector<vector<double> > boundaryCellLeftDownCenterRadianVec2;
   vector<vector<double> > boundaryCellRightDownCenterRadianVec2;
   double tempLeft;
   double tempRight;
   int i;
   int j;
   int k;

   ofstream fout("a.txt",ios::app);
   fout << "BoundaryCellLeftAndRightUpAndDownCenterRadianDB - Up" << endl;
   /// Up;
   for ( itMapUp = boundaryPointRightUpHemisphereTargetIntersectionRadianDivideDB.begin(), i = 0;
         itMapUp != boundaryPointRightUpHemisphereTargetIntersectionRadianDivideDB.end();
         itMapUp++, i++ )
   {  boundaryCellRightUpCenterRadianVec2.clear();
      boundaryCellLeftUpCenterRadianVec2.clear();
      for ( itVecUp = (*itMapUp).second.begin(), j = 0;
            itVecUp != (*itMapUp).second.end();
            itVecUp++, j++ )
      {  boundaryCellRightUpCenterRadianVec1.clear();
         boundaryCellLeftUpCenterRadianVec1.clear();
         for ( k = 0; k != boundaryCellUpNumDB[j]; k++ )
         {  if ( k == 0 )
            {  tempRight = boundaryRadianStartDB[i] + *itVecUp / 2;
               tempLeft = boundaryRadianEndDB[i] - *itVecUp / 2;
            }
            else
            {  tempRight += *itVecUp;
               tempLeft -= *itVecUp;
            }

            boundaryCellRightUpCenterRadianVec1.push_back( tempRight );
            boundaryCellLeftUpCenterRadianVec1.push_back( tempLeft );
            fout << "i: " << i << " j: " << j << " k: " << k
                 << "  tempRight: " << tempRight << "  " << "  tempLeft: " << tempLeft << endl;
         }
         boundaryCellRightUpCenterRadianVec2.push_back( boundaryCellRightUpCenterRadianVec1 );
         boundaryCellLeftUpCenterRadianVec2.push_back( boundaryCellLeftUpCenterRadianVec1 );
      }
      boundaryCellRightUpCenterRadianDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellRightUpCenterRadianVec2 ) );
      boundaryCellLeftUpCenterRadianDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellLeftUpCenterRadianVec2 ) );
   }

   /// Down;
   //fout << "BoundaryCellLeftAndRightUpAndDownCenterRadianDB - Down" << endl;
   for ( itMapDown = boundaryPointRightDownHemisphereTargetIntersectionRadianDivideDB.begin(), i = 0;
         itMapDown != boundaryPointRightDownHemisphereTargetIntersectionRadianDivideDB.end();
         itMapDown++, i++ )
   {  boundaryCellRightDownCenterRadianVec2.clear();
      boundaryCellLeftDownCenterRadianVec2.clear();
      for ( itVecDown = (*itMapDown).second.begin(), j = 0;
            itVecDown != (*itMapDown).second.end();
            itVecDown++, j++ )
      {  boundaryCellRightDownCenterRadianVec1.clear();
         boundaryCellLeftDownCenterRadianVec1.clear();
         for ( k = 0; k != boundaryCellDownNumDB[j]; k++ )
         {  if ( k == 0 )
            {  tempRight = boundaryRadianStartDB[i] + *itVecDown / 2;
               tempLeft = boundaryRadianEndDB[i] - *itVecDown / 2;
            }
            else
            {  tempRight += *itVecDown;
               tempLeft -= *itVecDown;
            }
            boundaryCellRightDownCenterRadianVec1.push_back( tempRight );
            boundaryCellLeftDownCenterRadianVec1.push_back( tempLeft );
            //fout << "i: " << i << " j: " << j << " k: " << k << endl;
            //fout << "tempRight: " << tempRight << "  " << "tempLeft: " << tempLeft << endl;
         }
         boundaryCellRightDownCenterRadianVec2.push_back( boundaryCellRightDownCenterRadianVec1 );
         boundaryCellLeftDownCenterRadianVec2.push_back( boundaryCellLeftDownCenterRadianVec1 );
      }
      boundaryCellRightDownCenterRadianDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellRightDownCenterRadianVec2 ) );
      boundaryCellLeftDownCenterRadianDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellLeftDownCenterRadianVec2 ) );
   }
}

/** BoundaryCellLeftAndRightUpAndDownCenterRotateAngleDB;
 *
 * \param map<int, vector<vector<double> > > boundaryCellLeftUpCenterRadianDB;
 * \param map<int, vector<vector<double> > > boundaryCellRightUpCenterRadianDB;
 * \param map<int, vector<vector<double> > > boundaryCellLeftDownCenterRadianDB;
 * \param map<int, vector<vector<double> > > boundaryCellRightDownCenterRadianDB;
 * \return map<int, vector<vector<double> > > boundaryCellLeftUpCenterRotateAngleDB;
 * \return map<int, vector<vector<double> > > boundaryCellRightUpCenterRotateAngleDB;
 * \return map<int, vector<vector<double> > > boundaryCellLeftDownCenterRotateAngleDB;
 * \return map<int, vector<vector<double> > > boundaryCellRightDownCenterRotateAngleDB;
 *
 */

void rsMXBoundaryDB::BoundaryCellLeftAndRightUpAndDownCenterRotateAngleDB()
{  map<int, vector<vector<double> > >::iterator itMap;
   vector<vector<double> >::iterator itVec2;
   vector<double>::iterator itVec1;

   vector<vector<double> > boundaryCellLeftUpCenterRotateAngleVec2;
   vector<vector<double> > boundaryCellRightUpCenterRotateAngleVec2;
   vector<vector<double> > boundaryCellLeftDownCenterRotateAngleVec2;
   vector<vector<double> > boundaryCellRightDownCenterRotateAngleVec2;
   vector<double> boundaryCellLeftUpCenterRotateAngleVec1;
   vector<double> boundaryCellRightUpCenterRotateAngleVec1;
   vector<double> boundaryCellLeftDownCenterRotateAngleVec1;
   vector<double> boundaryCellRightDownCenterRotateAngleVec1;
   int i;
   int j;
   int k;
   double tempRight;
   double tempLeft;
   ofstream fout("a.txt",ios::app);
   fout << "BoundaryCellLeftAndRightUpAndDownCenterRotateAngleDB" << endl;
   /// Up;
   for ( itMap = boundaryCellRightUpCenterRadianDB.begin(), i = 0;
         itMap != boundaryCellRightUpCenterRadianDB.end();
         itMap++, i++ )
   {  boundaryCellRightUpCenterRotateAngleVec2.clear();
      boundaryCellLeftUpCenterRotateAngleVec2.clear();
      for ( itVec2 = (*itMap).second.begin(), j = 0;
            itVec2 != (*itMap).second.end();
            itVec2++, j++ )
      {  boundaryCellRightUpCenterRotateAngleVec1.clear();
         boundaryCellLeftUpCenterRotateAngleVec1.clear();
         for ( itVec1 = (*itVec2).begin(), k = 0;
               itVec1 != (*itVec2).end();
               itVec1++, k++ )
         {  /// we must mutiply (-1) to get the right rotate angle;
            tempRight = ( -1) * boundaryCellRightUpCenterRadianDB[i][j][k] / M_PI * 180;
            tempLeft = ( -1) * boundaryCellLeftUpCenterRadianDB[i][j][k] / M_PI * 180;
            boundaryCellRightUpCenterRotateAngleVec1.push_back( tempRight );
            boundaryCellLeftUpCenterRotateAngleVec1.push_back( tempLeft );
            fout << "i: " << i << "  j: " << j << "  k: " << k
                 << "  tempRight: " << tempRight << "  tempLeft: " << tempLeft << endl;
         }
         boundaryCellRightUpCenterRotateAngleVec2.push_back
         ( boundaryCellRightUpCenterRotateAngleVec1 );
         boundaryCellLeftUpCenterRotateAngleVec2.push_back
         ( boundaryCellLeftUpCenterRotateAngleVec1 );
      }
      boundaryCellRightUpCenterRotateAngleDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellRightUpCenterRotateAngleVec2 ) );
      boundaryCellLeftUpCenterRotateAngleDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellLeftUpCenterRotateAngleVec2 ) );
   }

   /// Down;
   for ( itMap = boundaryCellRightDownCenterRadianDB.begin(), i = 0;
         itMap != boundaryCellRightDownCenterRadianDB.end();
         itMap++, i++ )
   {  boundaryCellRightDownCenterRotateAngleVec2.clear();
      boundaryCellLeftDownCenterRotateAngleVec2.clear();
      for ( itVec2 = (*itMap).second.begin(), j = 0;
            itVec2 != (*itMap).second.end();
            itVec2++, j++ )
      {  boundaryCellRightDownCenterRotateAngleVec1.clear();
         boundaryCellLeftDownCenterRotateAngleVec1.clear();
         for ( itVec1 = (*itVec2).begin(), k = 0;
               itVec1 != (*itVec2).end();
               itVec1++, k++ )
         {  /// we must mutiply (-1) to get the right rotate angle;
            tempRight = ( -1) * boundaryCellRightDownCenterRadianDB[i][j][k] / M_PI * 180;
            tempLeft = ( -1) * boundaryCellLeftDownCenterRadianDB[i][j][k] / M_PI * 180;
            boundaryCellRightDownCenterRotateAngleVec1.push_back( tempRight );
            boundaryCellLeftDownCenterRotateAngleVec1.push_back( tempLeft );
         }
         boundaryCellRightDownCenterRotateAngleVec2.push_back
         ( boundaryCellRightDownCenterRotateAngleVec1 );
         boundaryCellLeftDownCenterRotateAngleVec2.push_back
         ( boundaryCellLeftDownCenterRotateAngleVec1 );
      }
      boundaryCellRightDownCenterRotateAngleDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellRightDownCenterRotateAngleVec2 ) );
      boundaryCellLeftDownCenterRotateAngleDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellLeftDownCenterRotateAngleVec2 ) );
   }
}

/** boundaryCellLeftAndRighUpAndDownXYDB;
 *
 * \param map<int, vector<double> > boundaryUpCellCenterRadiusDB;
 * \param map<int, vector<double> > boundaryDownCellCenterRadiusDB;
 * \param map<int, vector<vector<double> > > boundaryCellLeftUpCenterRadianDB;
 * \param map<int, vector<vector<double> > > boundaryCellRightUpCenterRadianDB;
 * \param map<int, vector<vector<double> > > boundaryCellLeftDownCenterRadianDB;
 * \param map<int, vector<vector<double> > > boundaryCellRightDownCenterRadianDB;
 * \return map<int, vector<vector<double> > > boundaryCellLeftUpXDB;
 * \return map<int, vector<vector<double> > > boundaryCellRightUpXDB;
 * \return map<int, vector<vector<double> > > boundaryCellLeftDownXDB;
 * \return map<int, vector<vector<double> > > boundaryCellRightDownXDB;
 * \return map<int, vector<vector<double> > > boundaryCellLeftUpYDB;
 * \return map<int, vector<vector<double> > > boundaryCellRightUpYDB;
 * \return map<int, vector<vector<double> > > boundaryCellLeftDownYDB;
 * \return map<int, vector<vector<double> > > boundaryCellRightDownYDB;
 *
 */

void rsMXBoundaryDB::BoundaryCellLeftAndRighUpAndDownXYDB()
{  map<int, vector<vector<double> > >::iterator itMap;
   vector<vector<double> >::iterator itVec2;
   vector<double>::iterator itVec1;
   double tempRightX;
   double tempLeftX;
   double tempRightY;
   double tempLeftY;
   int i;
   int j;
   int k;
   vector<vector<double> > boundaryCellLeftUpXVec2;
   vector<vector<double> > boundaryCellRightUpXVec2;
   vector<vector<double> > boundaryCellLeftDownXVec2;
   vector<vector<double> > boundaryCellRightDownXVec2;
   vector<vector<double> > boundaryCellLeftUpYVec2;
   vector<vector<double> > boundaryCellRightUpYVec2;
   vector<vector<double> > boundaryCellLeftDownYVec2;
   vector<vector<double> > boundaryCellRightDownYVec2;
   vector<double> boundaryCellLeftUpXVec1;
   vector<double> boundaryCellRightUpXVec1;
   vector<double> boundaryCellLeftDownXVec1;
   vector<double> boundaryCellRightDownXVec1;
   vector<double> boundaryCellLeftUpYVec1;
   vector<double> boundaryCellRightUpYVec1;
   vector<double> boundaryCellLeftDownYVec1;
   vector<double> boundaryCellRightDownYVec1;

//   ofstream fout("a.txt",ios::app);
//   fout << "boundaryCellLeftAndRighUpXYDB: " << endl;
//   fout << "boundaryCellLeftUpXDB" << endl;
   /// Up;
   for ( itMap = boundaryCellRightUpCenterRadianDB.begin(), i = 0;
         itMap != boundaryCellRightUpCenterRadianDB.end();
         itMap++, i++ )
   {  boundaryCellRightUpXVec2.clear();
      boundaryCellLeftUpXVec2.clear();
      boundaryCellRightUpYVec2.clear();
      boundaryCellLeftUpYVec2.clear();
      for ( itVec2 = (*itMap).second.begin(), j = 0;
            itVec2 != (*itMap).second.end();
            itVec2++, j++ )
      {  boundaryCellRightUpXVec1.clear();
         boundaryCellLeftUpXVec1.clear();
         boundaryCellRightUpYVec1.clear();
         boundaryCellLeftUpYVec1.clear();
         for ( itVec1 = (*itVec2).begin(), k = 0;
               itVec1 != (*itVec2).end();
               itVec1++, k++ )
         {  tempRightX = boundaryUpCellCenterRadiusDB[i][j] * cos( *itVec1 );
            tempRightY = boundaryUpCellCenterRadiusDB[i][j] * sin( *itVec1 );
            tempLeftX = boundaryUpCellCenterRadiusDB[i][j] * cos( boundaryCellLeftUpCenterRadianDB[i][j][k] );
            tempLeftY = boundaryUpCellCenterRadiusDB[i][j] * sin( boundaryCellLeftUpCenterRadianDB[i][j][k] );
            boundaryCellRightUpXVec1.push_back( tempRightX );
            boundaryCellRightUpYVec1.push_back( tempRightY );
            boundaryCellLeftUpXVec1.push_back( tempLeftX );
            boundaryCellLeftUpYVec1.push_back( tempLeftY );
//            fout << "i: " << i << "  j: " << j << "  k: " << k
//                 << "  tempLeftX: " << boundaryCellLeftUpXVec1[k] << "  tempLeftY: " << tempLeftY << endl;

//            fout << "tempRightX: " << tempRightX << "  tempRightY: " << tempRightY << endl;

         }
         boundaryCellRightUpXVec2.push_back( boundaryCellRightUpXVec1 );
         boundaryCellRightUpYVec2.push_back( boundaryCellRightUpYVec1 );
         boundaryCellLeftUpXVec2.push_back( boundaryCellLeftUpXVec1 );
         boundaryCellLeftUpYVec2.push_back( boundaryCellLeftUpYVec1 );
      }
      boundaryCellRightUpXDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellRightUpXVec2 ) );
      boundaryCellRightUpYDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellRightUpYVec2 ) );
      boundaryCellLeftUpXDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellLeftUpXVec2 ) );
      boundaryCellLeftUpYDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellLeftUpYVec2 ) );
   }
   //fout << "boundaryCellLeftAndRighDownXYDB: " << endl;
   /// Down;
   for ( itMap = boundaryCellRightDownCenterRadianDB.begin(), i = 0;
         itMap != boundaryCellRightDownCenterRadianDB.end();
         itMap++, i++ )
   {  boundaryCellRightDownXVec2.clear();
      boundaryCellLeftDownXVec2.clear();
      boundaryCellRightDownYVec2.clear();
      boundaryCellLeftDownYVec2.clear();
      for ( itVec2 = (*itMap).second.begin(), j = 0;
            itVec2 != (*itMap).second.end();
            itVec2++, j++ )
      {  boundaryCellRightDownXVec1.clear();
         boundaryCellLeftDownXVec1.clear();
         boundaryCellRightDownYVec1.clear();
         boundaryCellLeftDownYVec1.clear();
         for ( itVec1 = (*itVec2).begin(), k = 0;
               itVec1 != (*itVec2).end();
               itVec1++, k++ )
         {  tempRightX = boundaryDownCellCenterRadiusDB[i][j] * cos( *itVec1 );
            tempRightY = boundaryDownCellCenterRadiusDB[i][j] * sin( *itVec1 );
            tempLeftX = boundaryDownCellCenterRadiusDB[i][j] * cos( boundaryCellLeftDownCenterRadianDB[i][j][k] );
            tempLeftY = boundaryDownCellCenterRadiusDB[i][j] * sin( boundaryCellLeftDownCenterRadianDB[i][j][k] );
            boundaryCellRightDownXVec1.push_back( tempRightX );
            boundaryCellRightDownYVec1.push_back( tempRightY );
            boundaryCellLeftDownXVec1.push_back( tempLeftX );
            boundaryCellLeftDownYVec1.push_back( tempLeftY );
            //fout << "i: " << i << "  j: " << j << "  k: " << k << endl;
            //fout << "tempRightX: " << tempRightX << "  tempRightY: " << tempRightY << endl;
            //fout << "tempLeftX: " << tempLeftX << "  tempLeftY: " << tempLeftY << endl;
         }
         boundaryCellRightDownXVec2.push_back( boundaryCellRightDownXVec1 );
         boundaryCellRightDownYVec2.push_back( boundaryCellRightDownYVec1 );
         boundaryCellLeftDownXVec2.push_back( boundaryCellLeftDownXVec1 );
         boundaryCellLeftDownYVec2.push_back( boundaryCellLeftDownYVec1 );
      }
      boundaryCellRightDownXDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellRightDownXVec2 ) );
      boundaryCellRightDownYDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellRightDownYVec2 ) );
      boundaryCellLeftDownXDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellLeftDownXVec2 ) );
      boundaryCellLeftDownYDB.insert
      ( pair<int, vector<vector<double> > >( i, boundaryCellLeftDownYVec2 ) );
   }
}

/** BoundaryCellObjectHeightAndZPositionDB
 *
 * \param map<int, vector<double> > longitudeSegmentHeightDB;
 * \param map<int, vector<double> > longitudeZPositionAddDB;
 * \param map<int, vector<vector<double> > > boundaryCellRightUpXDB;
 * \param map<int, vector<vector<double> > > boundaryCellRightDownXDB;
 * \param double objectXYZRadiusRatio;
 * \return map<int, vector <vector<vector<double> > > >boundaryCellLeftUpObjectHeightDB;
 * \return map<int, vector <vector<vector<double> > > >boundaryCellRightUpObjectHeightDB;
 * \return map<int, vector <vector<vector<double> > > >boundaryCellLeftDownObjectHeightDB;
 * \return map<int, vector <vector<vector<double> > > >boundaryCellRightDownObjectHeightDB;
 * \return map<int, vector <vector<vector<double> > > >boundaryCellLeftUpObjectZPositionDB;
 * \return map<int, vector <vector<vector<double> > > >boundaryCellRightUpObjectZPositionDB;
 * \return map<int, vector <vector<vector<double> > > >boundaryCellLeftDownObjectZPositionDB;
 * \return map<int, vector <vector<vector<double> > > >boundaryCellRightDownObjectZPositionDB;
 *
 */

void rsMXBoundaryDB::BoundaryCellObjectHeightAndZPositionDB( int sliceNum )
{  /// declare iterator;
   map<int, vector <vector<double> > >::iterator itMap;
   vector< vector<double> >::iterator itVec2;
   vector<double>::iterator itVec1;
   /// Left Height
   vector< vector <vector<double> > > objectHeightLeftVec3;
   vector< vector<double> >           objectHeightLeftVec2;
   vector<double>                     objectHeightLeftVec1;
   /// Right Height
   vector< vector <vector<double> > > objectHeightRightVec3;
   vector< vector<double> >           objectHeightRightVec2;
   vector<double>                     objectHeightRightVec1;
   /// Left ZPosition
   vector< vector <vector<double> > > objectZPositionLeftVec3;
   vector< vector<double> >           objectZPositionLeftVec2;
   vector<double>                     objectZPositionLeftVec1;
   /// Right ZPosition
   vector< vector <vector<double> > > objectZPositionRightVec3;
   vector< vector<double> >           objectZPositionRightVec2;
   vector<double>                     objectZPositionRightVec1;

   /// declare int;
   int i;
   int iRingNum;
   int cellNum;
   int sliceTempNum;
//   ofstream fout("a.txt",ios::app);
//   fout << "BoundaryCellObjectHeightAndZPositionDB" << endl;
//   fout << "Left Up: " << endl;
   /// Up;
   for ( i = 0, itMap = boundaryCellRightUpXDB.begin();
         itMap != boundaryCellRightUpXDB.end();
         i++, itMap++ )
   {  objectHeightLeftVec3.clear();
      objectZPositionLeftVec3.clear();
      objectHeightRightVec3.clear();
      objectZPositionRightVec3.clear();
      for ( iRingNum=0, itVec2 = (*itMap).second.begin();
            itVec2 !=  (*itMap).second.end();
            iRingNum++, itVec2++)
      {  objectHeightLeftVec2.clear();
         objectZPositionLeftVec2.clear();
         objectHeightRightVec2.clear();
         objectZPositionRightVec2.clear();
         for ( cellNum=0, itVec1 = (*itVec2).begin();
               itVec1 !=  (*itVec2).end();
               cellNum++, itVec1++)
         {  objectHeightLeftVec1.clear();
            objectZPositionLeftVec1.clear();
            objectHeightRightVec1.clear();
            objectZPositionRightVec1.clear();
            int randomHeightZPosition = rand() % 200;
            for ( sliceTempNum = 0;
                  sliceTempNum != sliceNum;
                  sliceTempNum++  )
            {  /// Height;
               objectHeightLeftVec1.push_back
               ( longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio );
               objectHeightRightVec1.push_back
               ( longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio );
//               fout << "i: " << i << "  iRingNum: " << iRingNum << "  cellNum: " << cellNum
//                    << "  sliceTempNum: " << sliceTempNum << "  Height: " << longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum]
//                    << endl;
               /// ZPosition;
               objectZPositionLeftVec1.push_back
               ( longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum] );
//               fout << "i: " << i << "  iRingNum: " << iRingNum << "  cellNum: " << cellNum
//                    << "  sliceTempNum: " << sliceTempNum << "  ZPosition: " << longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]
//                    << endl;
               objectZPositionRightVec1.push_back
               ( longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum] );
            }
            objectHeightLeftVec2.push_back( objectHeightLeftVec1 );
            objectZPositionLeftVec2.push_back( objectZPositionLeftVec1 );

            objectHeightRightVec2.push_back( objectHeightRightVec1 );
            objectZPositionRightVec2.push_back( objectZPositionRightVec1 );
         }
         objectHeightLeftVec3.push_back( objectHeightLeftVec2 );
         objectZPositionLeftVec3.push_back( objectZPositionLeftVec2 );

         objectHeightRightVec3.push_back( objectHeightRightVec2 );
         objectZPositionRightVec3.push_back( objectZPositionRightVec2 );
      }
      boundaryCellLeftUpObjectHeightDB.insert
      ( pair<int, vector< vector <vector<double> > > >( i, objectHeightLeftVec3 ) );
      boundaryCellLeftUpObjectZPositionDB.insert
      ( pair<int, vector< vector <vector<double> > > >( i, objectZPositionLeftVec3 ) );

      boundaryCellRightUpObjectHeightDB.insert
      ( pair<int, vector< vector <vector<double> > > >( i, objectHeightRightVec3 ) );
      boundaryCellRightUpObjectZPositionDB.insert
      ( pair<int, vector< vector <vector<double> > > >( i, objectZPositionRightVec3 ) );
   }
   /// Down;
   for ( i = 0, itMap = boundaryCellRightDownXDB.begin();
         itMap != boundaryCellRightDownXDB.end();
         i++, itMap++ )
   {  objectHeightLeftVec3.clear();
      objectZPositionLeftVec3.clear();
      objectHeightRightVec3.clear();
      objectZPositionRightVec3.clear();
      for ( iRingNum=0, itVec2 = (*itMap).second.begin();
            itVec2 !=  (*itMap).second.end();
            iRingNum++, itVec2++)
      {  objectHeightLeftVec2.clear();
         objectZPositionLeftVec2.clear();
         objectHeightRightVec2.clear();
         objectZPositionRightVec2.clear();
         for ( cellNum=0, itVec1 = (*itVec2).begin();
               itVec1 !=  (*itVec2).end();
               cellNum++, itVec1++)
         {  objectHeightLeftVec1.clear();
            objectZPositionLeftVec1.clear();
            objectHeightRightVec1.clear();
            objectZPositionRightVec1.clear();
            int randomHeightZPosition = rand() % 200;
            for ( sliceTempNum = 0;
                  sliceTempNum != sliceNum;
                  sliceTempNum++  )
            {  /// Height;
               objectHeightLeftVec1.push_back
               ( longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio );
               objectHeightRightVec1.push_back
               ( longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio );
               /// ZPosition;
               objectZPositionLeftVec1.push_back
               ( longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum] );
               objectZPositionRightVec1.push_back
               ( longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum] );
            }
            objectHeightLeftVec2.push_back( objectHeightLeftVec1 );
            objectZPositionLeftVec2.push_back( objectZPositionLeftVec1 );

            objectHeightRightVec2.push_back( objectHeightRightVec1 );
            objectZPositionRightVec2.push_back( objectZPositionRightVec1 );
         }
         objectHeightLeftVec3.push_back( objectHeightLeftVec2 );
         objectZPositionLeftVec3.push_back( objectZPositionLeftVec2 );

         objectHeightRightVec3.push_back( objectHeightRightVec2 );
         objectZPositionRightVec3.push_back( objectZPositionRightVec2 );
      }
      boundaryCellLeftDownObjectHeightDB.insert
      ( pair<int, vector< vector <vector<double> > > >( i, objectHeightLeftVec3 ) );
      boundaryCellLeftDownObjectZPositionDB.insert
      ( pair<int, vector< vector <vector<double> > > >( i, objectZPositionLeftVec3 ) );

      boundaryCellRightDownObjectHeightDB.insert
      ( pair<int, vector< vector <vector<double> > > >( i, objectHeightRightVec3 ) );
      boundaryCellRightDownObjectZPositionDB.insert
      ( pair<int, vector< vector <vector<double> > > >( i, objectZPositionRightVec3 ) );
   }
}


void rsMXBoundaryDB::InitBoundaryCell
( int dotNum,
  int setUpRowNum,
  int setDownRowNum,
  int sliceNum )
{  BoundaryRotateRadian();

   RadianUniformDB( dotNum );

   BoundaryPointRotateRadianDB();

   BoundaryPointXYLeftAndRightHemisphere( dotNum );

   BoundaryHalfCentralRadianDB();

   BoundaryRadianStartAndEndDB();

   BoundaryMaxAndMinCenterRadiusDB();

   BoundaryTangentCenterRadiusDB();

   BoundaryTangentUpAndDownLengthDB();

   SetUpAndDownRowNum( setUpRowNum, setDownRowNum );

   BoundaryTangentUpAndDownLengthSegmentDB();

   BoundaryTangentUpAndDownLengthSegmentAppendRadiusDB();

   BoundaryPointRightHemisphereCenterDistanceDB();

   BoundaryPointRightUpDownXYHemisphereTargetDB();

   BoundaryRadianStartPointXYDB();

   BoundaryPointRightUpAndDownHemisphereTargetIntersectionRadianDB();

   BoundaryPointRightAndLeftUpAndDownHemisphereTargetCenterRadian();

   BoundaryUpAndDownCellObjectVerticalDB();

   BoundaryUpAndDownCellCenterRadiusDB();

   BoundaryCellUpAndDownNumDB();

   BoundaryUpAndDownCellObjectParallelDB();

   BoundaryPointRightUpAndDownHemisphereTargetIntersectionRadianDivideDB();

   BoundaryCellLeftAndRightUpAndDownCenterRadianDB();

   BoundaryCellLeftAndRightUpAndDownCenterRotateAngleDB();

   BoundaryCellLeftAndRighUpAndDownXYDB();

   BoundaryCellObjectHeightAndZPositionDB( sliceNum );

}
