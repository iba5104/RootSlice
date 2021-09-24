#ifndef RSBASEGEOMETRY_H_INCLUDED
#define RSBASEGEOMETRY_H_INCLUDED

#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <string>

/// for random data generate;
#include <stdlib.h>
#include <time.h>
#include "globals.h"
using namespace std;

class rsBaseGeometry : public globals
{
public:

/// Set SuperEllipsoid Resolution;
   int uResolution;
   int vResolution;
   int wResolution;
   void SetSuperEllipsoidResolution(  );

   /// SetObjectVerticalRatio;
   double objectXYZRadiusRatio;
   void SetObjectXYZRadiusRatio( double temp );
   void SetObjectXYZRadiusRatio();

   /// Set object opacity;
   double objectOpacity;
   void SetObjectOpacity( double temp );
   void SetObjectOpacity();

   /// Set vacuole opacity;
   double vacuoleOpacity;
   void SetVacuoleOpacity( double temp );
   void SetVacuoleOpacity();

   //////////////////////////////////////// Functions ///////////////////////////////////
   /// circleRadius = Radius of each ring/circle;  // Jagdeep - 11-3-2020 - I think here Jia means radius of each cortical layer
   double circleRadius;
   double CircleRadius( double basicRadius, double appendRadius, double addRadius);

   /// Length of object in radial direction or in vertical of ring);
   double objectVertical;
   double ObjectVertical( double addRadius );

   /// Perimeter of ring for each object; // Jagdeep - 11-3-2020 what is object here?
   double circlePerimeter;
   double CirclePerimeter( double circleRadius);

   /// Get position of Z of circle;
   // Z position of circle;
   double zPosition;
   double ZPosition( double zPositionInput);

   /// Random data generate;
   vector<double> circleSegmentLength;
   vector<double> circleSegmentLengthAdd;
   double circleSegmentLengthSum;
   // define the range of random data generate, the bigger the smaller range;
   double randomRange;

   void SameSumAndNumberButDifferentSTDEVRatio
   ( vector<double> &circleSegmentLengthTemp,
     vector<double> &circleSegmentLengthAddTemp,
     double totalLength,
     int cellNum,
     double stdevRatio );

   void SameSumAndNumberButDifferentSTDEVRatio
   ( vector<double> &circleSegmentLengthTemp,
     vector<double> &circleSegmentLengthAddTemp,
     double &circleSegmentLengthSumTemp,
     double totalLength,
     int cellNum,
     double stdevRatio );

   void RandomRatioButSameSumAndNumber( vector<double> &circleSegmentLengthTemp,
                                        vector<double> &circleSegmentLengthAddTemp,
                                        double totalLength,
                                        int cellNum,
                                        double variationRatio);

   void RandomRatioButSameSumAndNumber( vector<double> &circleSegmentLengthTemp,
                                        vector<double> &circleSegmentLengthAddTemp,
                                        double &circleSegmentLengthSumTemp,
                                        double totalLength,
                                        int cellNum,
                                        double variationRatio);

   void SameSumAndNumberAndRatio( vector<double> &circleSegmentLengthTemp,
                                  vector<double> &circleSegmentLengthAddTemp,
                                  double &circleSegmentLengthSumTemp,
                                  double totalLength,
                                  int cellNum,
                                  double variationRatio);

   void SameSumAndNumberAndRatio ( vector<double> &circleSegmentLengthTemp,
                                   vector<double> &circleSegmentLengthAddTemp,
                                   double totalLength,
                                   int cellNum,
                                   double variationRatio);

   /// Get position of X and Y of circle and rotate radians in Nonuniform;
   // create vector to store X and Y position of object in each ring;
   vector<double> circleX;
   vector<double> circleY;

   vector<double> circleSegmentRotateAngle;
   void CircleXYNonuniform( int objectNumber, double circleRadius );

   /// Calculate random data of objectHeight length for each XYPosition;
   vector<double> longitudeSegmentHeight;
   vector<double> longitudeZPositionAdd;
   void NonRandomHeight
   ( double totalHeight,
     int sliceNum,
     double initZPosition);

   void RandomHeight
   ( double totalHeight,
     int sliceNum,
     double initZPosition);

   /// Create mapRGB database;
   map<int, vector<double> > mapRGB;
   void MapRGB();

   /// setRGBTime;
   int rgbTime;
   void RGBTime( int setRGBTime );

   /// setRGBStart;
   int rgbStart;
   void RGBStart( int setRGBStart );


};
#endif // RSBASEGEOMETRY_H_INCLUDED
