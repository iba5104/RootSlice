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

   /// Get RandomRange;
   double randomRange;
   int RandomRange( double setRandomRange );


   /// Calculate random data of radius for each ring (mx);
   // radius of each ring, not diameter of each ring;
   vector<double> eachRingRadius;
   vector<double> eachRingRadiusAdd;
   double eachRingDiameterSum;
   void RandomRadius( double variationRatio );

   /// Get angle and radian of X and Y in center circle by random generated in eachRingRadius;
   vector<double> centerRingRotateAngle;
   vector<double> centerRingRotateRadian;
   void CenterXYRotate();

};

#endif // RSBASEGEOMETRYMX_H_INCLUDED
