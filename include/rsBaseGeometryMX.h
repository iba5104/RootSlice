#ifndef RSBASEGEOMETRYMX_H_INCLUDED
#define RSBASEGEOMETRYMX_H_INCLUDED

#include "rsBaseGeometry.h"
#include "rsPXCoreDB.h"

class rsBaseGeometryMX : public rsBaseGeometry
{
public:

   /// Get mxBoundaryRingRadiusDeliver from rsPXCoreDB class;
   double boundaryMXPXRingRadiusDeliver;
   double BoundaryMXPXRingRadiusDeliver
   ( rsPXCoreDB *RsPXCoreDB);

   /// Get mxNum;
   int mxNum;
   int MXNum( int setMXNum );

   /// Get mxAverageRingRadius;
   double mxAverageRingRadius;
   int MXAverageRingRadius( double setMXAverageRingRadius );

   double mxMaxRingRadius;
   vector<double> eachRingMinRadius;
   int MXMinMaxRingRadius(double setMXMaxRingRadius, vector<double> setMXMinRingRadius);

   /// Get RandomRange;
   double randomRange;
   int RandomRange( double setRandomRange );

   int xylemArms;
   int XylemArms(int pxNum);

   int outRingCellNum;
   int SetOutRingCellNum(int xylemMaxOutRingCellNum);

   double outRingAddRadius;
   int SetOutRingAddRadius(double xylemMaxOutRingAddRadius);

   int mxRingNum;
   int MXRingNum(int setMXRingNum);

   vector<int> eachRingMXNum;
   int EachRingMXNum(vector<int> eachRingNum);

   /// Calculate random data of radius for each ring (mx);
   // radius of each ring, not diameter of each ring;
   vector<double> eachRingRadius;
   vector<double> eachRingRadiusAdd;
   vector<double> eachRingDiameterSum;
   double eachArmDiameterSum;
   bool noCentreMX;
   void RandomRadius( double variationRatio );

   /// Get angle and radian of X and Y in center circle by random generated in eachRingRadius;
   vector<double> centerRingRotateAngle;
   vector<double> centerRingRotateRadian;
   void CenterXYRotate(vector<double> pxRingRotateRadian, vector<double> pxRingRotateAngle);

};

#endif // RSBASEGEOMETRYMX_H_INCLUDED
