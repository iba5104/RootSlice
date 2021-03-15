#define _USE_MATH_DEFINES
#include <cmath> 
#include "rsBaseGeometryMX.h"


/** Get mxBoundaryRingRadiusDeliver from rsPXCoreDB class;
 *
 * \param rsPXCoreDB -> boundaryMXPXRingRadius;
 * \return mxBoundaryRingRadiusDeliver
 *
 */

double boundaryMXPXRingRadiusDeliver;
double rsBaseGeometryMX::BoundaryMXPXRingRadiusDeliver
( rsPXCoreDB *RsPXCoreDB)
{  boundaryMXPXRingRadiusDeliver = RsPXCoreDB -> boundaryMXPXRingRadius;
   ofstream fout("a.txt",ios::app);
   fout << "BoundaryMXPXRingRadiusDeliver: " << boundaryMXPXRingRadiusDeliver << endl;
   return boundaryMXPXRingRadiusDeliver;
}

/** Get mxNum;
 *
 * \param int setMXNum;
 * \return int mxNum;
 *
 */
int rsBaseGeometryMX::MXNum( int setMXNum )
{  mxNum = setMXNum;
   return mxNum;
}

/** Get mxAverageRingRadius;
 *
 * \param int setMXAverageRingRadius;
 * \return int mxAverageRingRadius;
 *
 */

double mxAverageRingRadius;
int rsBaseGeometryMX::MXAverageRingRadius( double setMXAverageRingRadius )
{  mxAverageRingRadius = setMXAverageRingRadius;
   return mxAverageRingRadius;
}

/** Get RandomRange;
 *
 * \param int setPXAverageRingRadius;
 * \return int pxNum;
 *
 */
double randomRange;
int rsBaseGeometryMX::RandomRange( double setRandomRange )
{  randomRange = setRandomRange;
   return randomRange;
}

/******************************************************
// Calculate random data of radius for each ring of mx;
   To get:
   vector<double> eachRingRadius;
   vector<double> eachRingRadiusAdd;
   double eachRingDiameterSum;
*******************************************************/
void rsBaseGeometryMX::RandomRadius( double variationRatio )
{  double mxRadiusTotal;
   double eachRingRadiusSum;
   mxRadiusTotal = mxAverageRingRadius * mxNum;
   RandomRatioButSameSumAndNumber( eachRingRadius,
                                   eachRingRadiusAdd,
                                   eachRingRadiusSum,
                                   mxRadiusTotal,
                                   mxNum,
                                   variationRatio);
   eachRingDiameterSum = eachRingRadiusSum * 2;
}

/** Get position of X and Y in center circle by random generated in eachRingRadius for mx;
 *
 * \param int pxNum: the number of object(Ellipsoid) in each ring/circle;
 * \return vector<double> centerRingRotateRadian;
 * \return vector<double> centerRingRotateAngle;
 *
 */

void rsBaseGeometryMX::CenterXYRotate()
{  double temp = 0;
   double sum = 0;

//   ofstream fout("a.txt",ios::app);
//   fout << "rsBaseGeometryMX.cpp" << endl;
   for (int i =0; i < mxNum; i++ )
   {  if ( i == 0 )
      {  sum = 0;
         centerRingRotateRadian.push_back( sum );
         centerRingRotateAngle.push_back( sum );
//         fout << "centerRingRotateRadian: " << i <<": "<< 0 << endl;
      }
      else
      {  temp = eachRingRadius[i] + eachRingRadius[i-1];
         sum += temp;
         centerRingRotateRadian.push_back( 2*M_PI* sum / eachRingDiameterSum );
         centerRingRotateAngle.push_back ( -360 *  sum / eachRingDiameterSum );

//         fout << "centerRingRotateRadian: " << i <<": "
//              << 2*M_PI* sum / eachRingDiameterSum << endl;
      }
   }
}
