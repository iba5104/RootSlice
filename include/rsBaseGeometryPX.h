#ifndef RSBASEGEOMETRYPROTOXYLEM_H_INCLUDED
#define RSBASEGEOMETRYPROTOXYLEM_H_INCLUDED

#include "rsBaseGeometry.h"
#include <fstream>
class rsBaseGeometryPX : public rsBaseGeometry
{
public:

   /// Get steleBoundaryRingRadius;
   double steleBoundaryRingRadius;
   double SteleBoundaryRingRadius( double endodermisBaseRadius );

   /// Get pxBoundaryRingRadius;
   double pxBoundaryRingRadius;
   double PXBoundaryRingRadius( double pxGapRadius );

   /// Get pxNum;
   int pxNum;
   int PXNum( int setPXNum );

   /// Get pxAverageRingRadius;
   double pxAverageRingRadius;
   int PXAverageRingRadius( double setPXAverageRingRadius );

   /// Get RandomRange;
   double randomRange;
   int RandomRange( double setRandomRange );

   /// Calculate random data of radius for each ring (metaxylem);
   vector<double> eachRingRadius;
   vector<double> eachRingRadiusAdd;
   double eachRingDiameterSum;
   void RandomRadius( double variationRatio );

   /// Get angle and radian of X and Y in center circle by random generated in eachRingRadius;
   vector<double> centerRingRotateAngle;
   vector<double> centerRingRotateRadian;
   void CenterXYRotate();

};

#endif // RSBASEGEOMETRYPROTOXYLEM_H_INCLUDED
