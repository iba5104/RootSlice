#define _USE_MATH_DEFINES
#include <cmath> 
#include "rsRcaDB.h"

/** \brief GetRcaData
 *
 * \param double rcaRatioInput
 * \param int rcaNumInput
 * \param int standardOuterLayerInput
 * \param int standardInnerLayerInput
 * \return double rcaRatio
 * \return int rcaNum
 * \return int standardOuterLayer
 * \return int standardInnerLayer
 *
 */
void rsRcaDB::GetRcaData( double rcaRatioInput, int rcaNumInput, int standardOuterLayerInput, int standardInnerLayerInput )
{  rcaRatio = rcaRatioInput;
   rcaNum = rcaNumInput;
   standardOuterLayer = standardOuterLayerInput;
   standardInnerLayer = standardInnerLayerInput;
//   ofstream fout("RCA.txt",ios::app);
//   fout << "GetRcaData" << endl;
//   fout << "rcaRatio: " << rcaRatio << endl;
//   fout << "rcaNum: " << rcaNum << endl;
//   fout << "standardOuterLayer: " << standardOuterLayer << endl;
//   fout << "standardInnerLayer: " << standardInnerLayer << endl;
}

/** \brief cortexArea
 *
 * \param double baseRadius
 * \param RsSourceCorticalDB -> boundaryRadius
 * \return double cortexArea;
 *
 */
void rsRcaDB::CortexArea( double baseRadius, rsSourceCorticalDB *RsSourceCorticalDB )
{  cortexArea = M_PI * (RsSourceCorticalDB -> boundaryRadius) * (RsSourceCorticalDB -> boundaryRadius)
                - (M_PI * baseRadius * baseRadius);
   ofstream fout("RCA.txt",ios::app); // was commented by Jie - Jagdeep
   fout << "cortexArea: " << cortexArea << endl;
   fout << "baseRadius: " << baseRadius << endl;
   fout << "RsSourceCorticalDB -> boundaryRadius: " << RsSourceCorticalDB -> boundaryRadius << endl;
}

/** \brief rcaTotalArea
 *
 * \param double rcaRatio;
 * \return double rcaTotalArea;
 *
 */
void rsRcaDB::RcaTotalArea()
{  rcaTotalArea = cortexArea * rcaRatio;
ofstream fout("RCA.txt",ios::app); /////jagdeep uncommented
fout << "rcaTotalArea: " << rcaTotalArea << endl; ////jagdeep uncomented
}

/** \brief rcaArea
 *
 * \param double rcaTotalArea;
 * \param int rcaNum;
 * \param double randomRange;
 * \return vector<double> rcaArea;
 * \return vector<double> rcaAddArea;
 *
 */
/// According the rcaNum and total racArea to calculate the area of each rca;
void rsRcaDB::RcaArea( double variationRatio )
{  RandomRatioButSameSumAndNumber
   ( rcaArea,
     rcaAddArea,
     rcaTotalArea,
     rcaNum,
     variationRatio);
}

/** rcaVerticalLengthStoreDB;
 *
 * \param map<int, double> corticalAddRadiusDB;
 * \param int standardOuterLayer;
 * \param int standardInnerLayer;
 * \return map<int, vector<double> > rcaVerticalLengthStoreDB;
 * \return map<int, vector<double> > rcaVerticalLengthStoreStartLayerDB;
 *
 */
/// set standardOuterLayer = 1;
/// set standardInnerLayer = 1; The standardInnerLayer must be bigger than 0;
void rsRcaDB::RcaVerticalLengthStoreDB( rsSourceCorticalDB *RsSourceCorticalDB )
{  int totalLayerNum;
   int midCorticalLayerNum;
   int layerNum;
   int layerSequence;
   int layerPosition;
   double tempSum;
   vector<double> rcaVerticalLengthStore;
   vector<int> rcaVerticalLengthStoreStartLayer;
   totalLayerNum = RsSourceCorticalDB -> corticalAddRadiusDB.size();
   midCorticalLayerNum = totalLayerNum - standardOuterLayer - standardInnerLayer;
//   ofstream fout("RCA.txt",ios::app);
//   fout << "RcaVerticalLengthStoreDB" << endl;
   /// Set the range of cell number that be classified;
   for ( layerNum = 2; layerNum <= midCorticalLayerNum; layerNum++ )
   {  /// Set the range of position of each classification in the corticalAddRadiusDB;
      for ( layerSequence = standardInnerLayer;
            layerSequence <= totalLayerNum - standardOuterLayer - layerNum;
            layerSequence++)
      {  rcaVerticalLengthStore.clear();
         rcaVerticalLengthStoreStartLayer.clear();
         tempSum = 0;
         std::cout << "Ran till 110 RCADB";
         /// Traverse the unit of each classification in the corticalAddRadiusDB;
         for ( layerPosition = 0; layerPosition != layerNum; layerPosition++ )
         {  tempSum += RsSourceCorticalDB -> corticalAddRadiusDB[ layerSequence + layerPosition ];
         }
         std::cout << "Ran till 115 RCADB";
         rcaVerticalLengthStore.push_back( tempSum );
         rcaVerticalLengthStoreStartLayer.push_back( layerSequence );
//         fout << "  layerNum: " << layerNum
//              << "  rcaVerticalLengthStoreStartLayer: " << layerSequence
//              << "  rcaVerticalLengthStore: " << tempSum << endl;
      }
      rcaVerticalLengthStoreDB.insert( pair<int, vector<double> >( layerNum, rcaVerticalLengthStore ) );
      rcaVerticalLengthStoreStartLayerDB.insert( pair<int, vector<int> >( layerNum, rcaVerticalLengthStoreStartLayer ) );
   }
}


/** \brief rcaVerticalLengthStoreSelectRange
 *
 * \param int standardOuterLayer;
 * \param int standardInnerLayer;
 * \param double rcaRatio;
 * \return vector<double> rcaVerticalLengthStoreSelectRange;
 *
 */

/**********************************
That is an important function;


***********************************/

void rsRcaDB::RcaVerticalLengthStoreSelectRange( rsSourceCorticalDB *RsSourceCorticalDB )
{  int i;
   int midCorticalTruncatedLayerNum;
   midCorticalTruncatedLayerNum = RsSourceCorticalDB -> corticalAddRadiusDB.size() - standardOuterLayer - standardInnerLayer;
   double appendValue;
   if ( midCorticalTruncatedLayerNum <= 4 )
   {  appendValue = 1;
   }
   else
   {  appendValue = 2;
   }
   /// rcaRatio(0.15) - double(0.15) != 0;
//   ofstream fout("RCA.txt",ios::app);
//   fout << "RcaVerticalLengthStoreSelectRange" << endl;
   
   if ( rcaRatio >= 0.01 && rcaRatio <= 0.06)
   {  if ( midCorticalTruncatedLayerNum > 10 )
      {  for ( i = 2; i <= 2; i++ )
         {  rcaVerticalLengthStoreSelectRange.push_back( i );
//         fout << "rcaVerticalLengthStoreSelectRange: " << i << endl;
         }
      }

      for ( i = 2; i <= 2; i++ )
      {  rcaVerticalLengthStoreSelectRange.push_back( i );
//         fout << "rcaVerticalLengthStoreSelectRange: " << i << endl;
      }


   }

   /// Why I set i = 1, it will break in cellDiameter = 30;
   if ( rcaRatio > 0.06 && rcaRatio <= 0.16)
   {  if ( midCorticalTruncatedLayerNum >= 15 )
      {  midCorticalTruncatedLayerNum = midCorticalTruncatedLayerNum - 5;
      }
      else if ( midCorticalTruncatedLayerNum >= 10 )
      {  midCorticalTruncatedLayerNum = midCorticalTruncatedLayerNum - 3;
      }
      else if ( midCorticalTruncatedLayerNum >= 8 )
      {  midCorticalTruncatedLayerNum = midCorticalTruncatedLayerNum - 2;
      }
      else if ( midCorticalTruncatedLayerNum >= 6 )
      {  midCorticalTruncatedLayerNum = midCorticalTruncatedLayerNum - 2;
      }

//      cout << "midCorticalTruncatedLayerNum: " << midCorticalTruncatedLayerNum << "  ";
      for ( i = 2; i <= int( double(midCorticalTruncatedLayerNum) / 2 ); i++ )
      {  rcaVerticalLengthStoreSelectRange.push_back( i );
//         fout << "rcaVerticalLengthStoreSelectRange: " << i << endl;
      }
   }

   if ( rcaRatio > 0.16 && rcaRatio <= 0.31 )
   {  for ( i = int( double(midCorticalTruncatedLayerNum) / 2 + 0.5 ); i <= midCorticalTruncatedLayerNum-1; i++ )
      {  rcaVerticalLengthStoreSelectRange.push_back( i );
//         fout << "rcaVerticalLengthStoreSelectRange: " << i << endl;
      }
   }

   if ( rcaRatio > 0.31 && rcaRatio <= 0.51 )
   {  for ( i = int( double(midCorticalTruncatedLayerNum) / 2 + appendValue + 0.5 ); i <= midCorticalTruncatedLayerNum; i++ )
      {  rcaVerticalLengthStoreSelectRange.push_back( i );
//         fout << "rcaVerticalLengthStoreSelectRange: " << i << endl;
      }
   }

   if ( rcaRatio > 0.51 )
   {  rcaVerticalLengthStoreSelectRange.push_back( midCorticalTruncatedLayerNum );
//         cout << "rcaVerticalLengthStoreSelectRange: " << midCorticalTruncatedLayerNum << endl;
   }std::cout << "Ran till 214 RCADB";
}

/** \brief RcaVerticalLengthDB
 *
 * \param int rcaNum;
 * \param map<int, vector<double> > rcaVerticalLengthStoreDB;
 * \param map<int, vector<int> > rcaVerticalLengthStoreStartLayerDB;;
 * \return vector<double> rcaVerticalLengthDB;
 * \return vector<int> rcaVerticalLengthStartLayerDB;
 * \return vector<int> rcaVerticalLayerNumDB;
 *
 */
void rsRcaDB::RcaVerticalLengthDB()
{  int lowest;
   int uppest;
   int randRange;
   int i;
   int vecSize;
   int randVecPosition;
   double verticalDiameter;
   int randLayerPosition;
   lowest = rcaVerticalLengthStoreSelectRange.front();
   uppest = rcaVerticalLengthStoreSelectRange.back();

//   ofstream fout("RCA.txt",ios::app);
//   fout << "RcaVerticalLengthDB" << endl;
   for ( i = 0; i != rcaNum; i++ )
   {  randRange = rand() % (uppest - lowest + 1) + lowest;
      vecSize = rcaVerticalLengthStoreDB[randRange].size();
      randVecPosition = rand() % ( vecSize );
      verticalDiameter = rcaVerticalLengthStoreDB[randRange][randVecPosition];
      randLayerPosition = rcaVerticalLengthStoreStartLayerDB[randRange][randVecPosition];

      rcaVerticalLengthDB.push_back( verticalDiameter / 2 );
      rcaVerticalLayerNumDB.push_back( randRange );
      rcaVerticalLengthStartLayerDB.push_back( randLayerPosition );

//      fout << "  rcaVerticalLengthStartLayerDB: " << randLayerPosition
//           << "  rcaVerticalLayerNumDB: " << randRange
//           << "  rcaVerticalLengthDB: " << verticalDiameter / 2
//           << "  rcaNum: " << rcaNum << endl;
   }std::cout << "Ran till 256 RCADB";
}

/** \brief ParallelRadiusDB
 *
 * \param vector<double> rcaArea;
 * \param vector<double> rcaVerticalLengthDB;
 * \return vector<double> parallelRadiusDB;
 *
 */
void rsRcaDB::ParallelRadiusDB()
{  vector<double>::iterator itVecArea;
   vector<double>::iterator itVecRcaVerticalLength;
   double parallelRadius;
   for ( itVecArea = rcaArea.begin(), itVecRcaVerticalLength = rcaVerticalLengthDB.begin();
         itVecArea != rcaArea.end();
         itVecArea++, itVecRcaVerticalLength++ )
   {  parallelRadius = (*itVecArea) / (M_PI * (*itVecRcaVerticalLength) ) * parallelRadiusAdjustRatio;
      parallelRadiusDB.push_back( parallelRadius );
   }std::cout << "Ran till 275 RCADB";
}


/// This radius is a radius for the whole cross-section;
/** rcaCenterVerticalMiddleRadius;
 *
 * \param double baseRadius;
 * \param map<int, double> corticalAddRadiusDB;
 * \param vector<double> rcaVerticalLengthDB;
 * \param vector<int> rcaVerticalLengthStartLayerDB;
 * \return vector<double> rcaCenterVerticalMiddleRadiusDB;
 *
 */

void rsRcaDB::RcaCenterVerticalMiddleRadiusDB( double baseRadius, rsSourceCorticalDB *RsSourceCorticalDB )
{  vector<int>::iterator itVecPosition;
   vector<double>::iterator itVecRadius;
   int i;
   double tempSum;
   double rcaCenterVerticalMiddleRadius;


   /// this ratio is used to adjust the rcaCenterVerticalMiddleRadius;
   /// the bigger ratio, the smaller rcaIntersetionAngleHalf;


//   ofstream fout("RCA.txt",ios::app);
//   fout << "RcaCenterVerticalMiddleRadiusDB" << endl;
   for ( itVecPosition = rcaVerticalLengthStartLayerDB.begin(), itVecRadius = rcaVerticalLengthDB.begin();
         itVecPosition != rcaVerticalLengthStartLayerDB.end();
         itVecPosition++, itVecRadius++ )
   {  tempSum = 0;

      for( i = 0; i != (*itVecPosition); i++ )
      {  tempSum += RsSourceCorticalDB -> corticalAddRadiusDB[i];
      }
      rcaCenterVerticalMiddleRadius = ( baseRadius + *itVecRadius + tempSum ) * middleRadiusAdjustRatio;
      rcaCenterVerticalMiddleRadiusDB.push_back( rcaCenterVerticalMiddleRadius );
//      fout << "rcaCenterVerticalMiddleRadiusDB: " << rcaCenterVerticalMiddleRadius << endl;
   }std::cout << "Ran till 314 RCADB";
}

/** \brief RcaIntersetionAngleHalfDB
 *
 * \param vector<double> rcaCenterVerticalMiddleRadiusDB;
 * \param vector<double> parallelRadiusDB;
 * \return vector<double> rcaIntersetionAngleHalfDB;
 * \return vector<double> rcaAddIntersetionAngleDB;
 *
 */
void rsRcaDB::RcaIntersetionAngleHalfDB()
{  vector<double>::iterator itVecCenterRadius;
   vector<double>::iterator itVecParallelRadius;
   double rcaIntersetionAngleHalf;
   double rcaIntersetionAngle;
   double tempSum = 0;

//   ofstream fout("RCA.txt",ios::app);
//   fout << "RcaIntersetionAngleHalfDB" << endl;
   for ( itVecCenterRadius = rcaCenterVerticalMiddleRadiusDB.begin(), itVecParallelRadius = parallelRadiusDB.begin();
         itVecCenterRadius != rcaCenterVerticalMiddleRadiusDB.end();
         itVecCenterRadius++, itVecParallelRadius++ )
   {  rcaIntersetionAngleHalf = 360 * (*itVecParallelRadius) / ( 2*M_PI*(*itVecCenterRadius));
      rcaIntersetionAngle = rcaIntersetionAngleHalf * 2;
      tempSum += rcaIntersetionAngle;
      rcaIntersetionAngleHalfDB.push_back( rcaIntersetionAngleHalf );
      rcaAddIntersetionAngleDB.push_back( tempSum - rcaIntersetionAngle );
//      fout << "  rcaIntersetionAngleHalfDB: " << rcaIntersetionAngleHalf
//           << "  rcaAddIntersetionAngleDB: " << tempSum - rcaIntersetionAngle << endl;
   }std::cout << "Ran till 345 RCADB";
}

/** \brief GapAngleBetweenRcaDB
 *
 * \param int rcaNum;
 * \param
 * \return double gapAngleBetweenRca;
 * \return vector<double> gapAddAngleBetweenRcaDB;
 *
 */
void rsRcaDB::GapAngleBetweenRcaDB( double gapAngleBetweenRcaRatio )
{  gapAngleBetweenRca = gapAngleBetweenRcaRatio * 360;
   int i;
   double tempSum = 0;

//   ofstream fout("RCA.txt",ios::app);
//   fout << "RcaIntersetionAngleHalfDB" << endl;
   for ( i = 0; i != rcaNum; i++ )
   {  tempSum += gapAngleBetweenRca;
      gapAddAngleBetweenRcaDB.push_back( tempSum - gapAngleBetweenRca );
//      fout << "tempSum: " << tempSum << "  gapAngleBetweenRca: " << gapAngleBetweenRca << endl;
//      fout << "gapAddAngleBetweenRcaDB: " << tempSum - gapAngleBetweenRca << endl;
   }std::cout << "Ran till 367 RCADB";
}

/** \brief SurplusAngleTotal
 *
 * \param vector<double> rcaIntersetionAngleHalfDB;
 * \param double gapAngleBetweenRca;
 * \return double surplusAngleTotal;
 *
 */
void rsRcaDB::SurplusAngleTotal()
{  vector<double>::iterator itVec;
   double sumAngle = 0;

//   ofstream fout("RCA.txt",ios::app);
//   fout << "RcaTotalArea" << endl;
   for ( itVec = rcaIntersetionAngleHalfDB.begin();
         itVec != rcaIntersetionAngleHalfDB.end();
         itVec++	)
   {  sumAngle += (*itVec) * 2;
   }
   surplusAngleTotal = 360 - sumAngle - rcaNum * gapAngleBetweenRca;

//   fout << "sumAngle: " << sumAngle << endl;
//   fout << "rcaNum * gapAngleBetweenRca: " << rcaNum * gapAngleBetweenRca << endl;
//   fout << "surplusAngleTotal: " << surplusAngleTotal << endl;
}

/** \brief SurplusAngleDistribution
 *
 * \param double surplusAngleTotal;
 * \param int rcaNum;
 * \param double randomRange;
 * \return vector<double> surplusAngleDistribution;
 * \return vector<double> surplusAddAngleDistribution;
 *
 */
void rsRcaDB::SurplusAngleDistribution( double variationRatio )
{  SameSumAndNumberAndRatio
   ( surplusAngleDistribution,
     surplusAddAngleDistribution,
     surplusAngleTotal,
     rcaNum,
     variationRatio); std::cout << "Ran till 410 RCADB";
}

/** RcaMidPointAngleDB;
 *
 * \param vector<double> surplusAngleDistribution;;
 * \param vector<double> surplusAddAngleDistribution;
 * \param double gapAngle;
 * \param vector<double> gapAddAngleBetweenRcaDB;
 * \param vector<double> rcaIntersetionAngleHalfDB;
 * \param vector<double> rcaAddIntersetionAngleDB;
 * \return vector<double> rcaMidPointAngleDB;
 *
 */
void rsRcaDB::RcaMidPointAngleDB()
{  vector<double>::iterator itVecGapAdd;
   vector<double>::iterator itVecSurplus;
   vector<double>::iterator itVecSurplusAdd;
   vector<double>::iterator itVecRcaAngleHalf;
   vector<double>::iterator itVecRcaAddAngle;
   double total;

//   ofstream fout("RCA.txt",ios::app);
//   fout << "RcaMidPointAngleDB" << endl;
   for ( itVecGapAdd = gapAddAngleBetweenRcaDB.begin(), itVecSurplus = surplusAngleDistribution.begin(),
         itVecSurplusAdd = surplusAddAngleDistribution.begin(), itVecRcaAngleHalf = rcaIntersetionAngleHalfDB.begin(),
         itVecRcaAddAngle = rcaAddIntersetionAngleDB.begin();
         itVecGapAdd != gapAddAngleBetweenRcaDB.end();
         itVecGapAdd++, itVecSurplus++, itVecSurplusAdd++, itVecRcaAngleHalf++, itVecRcaAddAngle++	)
   {  total = *itVecGapAdd + gapAngleBetweenRca +
              *itVecSurplus + *itVecSurplusAdd +
              *itVecRcaAddAngle + *itVecRcaAngleHalf;
//      fout << "*itVecGapAdd: " << *itVecGapAdd << "  gapAngleBetweenRca: " << gapAngleBetweenRca << " *itVecSurplus: " << *itVecSurplus
//           << "  *itVecSurplusAdd: " << *itVecSurplusAdd << "  *itVecRcaAddAngle: " << *itVecRcaAddAngle
//           << "  *itVecRcaAngleHalf: " << *itVecRcaAngleHalf << endl;
      rcaMidPointAngleDB.push_back( (-1) * total );
//      fout << "rcaMidPointAngleDB: " << (-1) * total << endl;
   }std::cout << "Ran till 447 RCADB";
}

/** rcaLowerUpperLayerPositionDB;
 *
 * \param vector<double> rcaVerticalLengthDB;
 * \param vector<int> rcaVerticalLengthStartLayerDB;
 * \param vector<int> rcaVerticalLayerNumDB;
 * \param vector<double> rcaCenterVerticalMiddleRadiusDB;
 * \param vector<double> RsSourceCorticalDB -> circleRadiusDB;
 * \return map<int, vector<int> > rcaLowerLayerPosition;
 * \return map<int, vector<int> > rcaUpperLayerPosition;
 *
 */
void rsRcaDB::RcaLowerUpperLayerPositionDB( rsSourceCorticalDB *RsSourceCorticalDB )
{  vector<int>::iterator itVecLayerNum;
   vector<int>::iterator itVecStartPosition;
   vector<double>::iterator itVecRcaCenterRadius;
   vector<int> rcaLowerLayerPosition;
   vector<int> rcaUpperLayerPosition;
   int layerPosition;
   int i;
   double tempRadius;

//   ofstream fout("RCA.txt",ios::app);
//   fout << "RcaLowerUpperLayerPositionDB" << endl;
   for( itVecStartPosition = rcaVerticalLengthStartLayerDB.begin(), itVecLayerNum = rcaVerticalLayerNumDB.begin(),
         itVecRcaCenterRadius = rcaCenterVerticalMiddleRadiusDB.begin(), i = 0;
         itVecStartPosition != rcaVerticalLengthStartLayerDB.end();
         itVecStartPosition++, itVecLayerNum++, itVecRcaCenterRadius++, i++ )
   {
//       fout << "rcaPosition: " << i << endl;
//      fout << "*itVecLayerNum: " << *itVecLayerNum << endl;
//      fout << "*itVecStartPosition: " << *itVecStartPosition << endl;
      rcaLowerLayerPosition.clear();
      rcaUpperLayerPosition.clear();
      for ( layerPosition = *itVecStartPosition;
            layerPosition != (*itVecStartPosition + *itVecLayerNum);
            layerPosition++ )
      {  tempRadius = RsSourceCorticalDB -> circleRadiusDB[layerPosition];

         if ( tempRadius <= *itVecRcaCenterRadius )
         {  rcaLowerLayerPosition.push_back( layerPosition ); /// From the down to up of cell layers;
//            fout << "rcaLowerLayerPosition: " << layerPosition << endl;
         }
         else
         {  rcaUpperLayerPosition.push_back( layerPosition ); /// From the down to up of cell layers;
//            fout << "rcaUpperLayerPosition: " << layerPosition << endl;
         }
      }
      rcaLowerLayerPositionDB.insert( pair<int, vector<int> >( i, rcaLowerLayerPosition ) );
      rcaUpperLayerPositionDB.insert( pair<int, vector<int> >( i, rcaUpperLayerPosition ) );
   }std::cout << "Ran till 499 RCADB";
}

/** RcaLowerLayerIntersectionAngleDB;
 *
 * \param map<int, vector<int> > rcaLowerLayerPositionDB;
 * \param map<int, vector<int> > rcaUpperLayerPositionDB;
 * \param vector<double> rcaIntersetionAngleHalfDB;
 * \return map<int, vector<double> > rcaLowerLayerIntersectionAngleHalfDB;
 * \return map<int, vector<double> > rcaUpperLayerIntersectionAngleHalfDB;
 *
 */
void rsRcaDB::RcaLowerUpperLayerIntersectionAngleDB()
{  map<int, vector<int> >::iterator itMapLower;
   map<int, vector<int> >::iterator itMapUpper;
   vector<int>::iterator itVecLower;
   vector<int>::iterator itVecUpper;
   vector<double>::iterator itVecIntersetionAngleHalf;
   vector<double> rcaLowerLayerIntersectionAngleHalf;
   vector<double> rcaUpperLayerIntersectionAngleHalf;
   int i;
   int exponent;
   double tempAngle;

   ofstream fout("RCA.txt",ios::app);
//   fout << endl;
//   fout << "RcaLowerUpperLayerIntersectionAngleDB" << endl;
//   fout << endl;
//   fout << "Lower" << endl;
//   fout << endl;

   double lowerShapeIndex = 0.98;
   double upperShapeIndex = 0.9;
   for ( itMapLower = rcaLowerLayerPositionDB.begin(),
         itVecIntersetionAngleHalf = rcaIntersetionAngleHalfDB.begin(), i = 0;
         itMapLower != rcaLowerLayerPositionDB.end();
         itMapLower++, itVecIntersetionAngleHalf++, i++ )
   {  //fout << "rcaNum: " << i << endl;
      rcaLowerLayerIntersectionAngleHalf.clear();
//      fout << "size: " << (*itMapLower).second.size() << endl;
      std::cout << "Ran till 539";
      for ( itVecLower = (*itMapLower).second.end() - 1, exponent = 0;
            itVecLower >= (*itMapLower).second.begin();
            itVecLower--, exponent++ )
      {  tempAngle = (*itVecIntersetionAngleHalf) * pow( lowerShapeIndex, exponent );
      std::cout << "Ran till 544 RCADB";
//         fout << "tempAngle: " << tempAngle  << endl;
         /// From the down to up of cell layers;
         /// we must use insert the content at front position to make the order from the down to up of cell layers;
         rcaLowerLayerIntersectionAngleHalf.insert( rcaLowerLayerIntersectionAngleHalf.begin(), tempAngle );
         
      }std::cout << "Ran till 549 RCADB";
      rcaLowerLayerIntersectionAngleHalfDB.insert( pair<int, vector<double> >( i, rcaLowerLayerIntersectionAngleHalf ) );
   }std::cout << "Ran till 549 RCADB";

//   fout << endl;
//   fout << "Upper" << endl;
//   fout << endl;

   for ( itMapUpper = rcaUpperLayerPositionDB.begin(), itVecIntersetionAngleHalf = rcaIntersetionAngleHalfDB.begin(), i = 0;
         itMapUpper != rcaUpperLayerPositionDB.end();
         itMapUpper++, itVecIntersetionAngleHalf++, i++ )
   {  //fout << "rcaNum: " << i << endl;
      rcaUpperLayerIntersectionAngleHalf.clear();
      for ( itVecUpper = (*itMapUpper).second.begin(), exponent = 0;
            itVecUpper != (*itMapUpper).second.end();
            itVecUpper++, exponent++ )
      {  tempAngle = (*itVecIntersetionAngleHalf) * pow( upperShapeIndex, exponent );
//         fout << "tempAngle: " << tempAngle << endl;
         rcaUpperLayerIntersectionAngleHalf.push_back( tempAngle ); /// From the down to up of cell layers;
      }
      rcaUpperLayerIntersectionAngleHalfDB.insert( pair<int, vector<double> >( i, rcaUpperLayerIntersectionAngleHalf ) );
   }std::cout << "Ran till 568 RCADB";
}

/** rcaCellPositionDB;
 *
 * \param map<int, vector<int> > rcaLowerLayerPositionDB;
 * \param map<int, vector<int> > rcaUpperLayerPositionDB;
 * \param map<int, vector<double> > rcaLowerLayerIntersectionAngleHalfDB;
 * \param map<int, vector<double> > rcaUpperLayerIntersectionAngleHalfDB;
 * \param vector<double> rcaMidPointAngleDB;
 * \param map<int, vector<double> > RsSourceCorticalDB -> circleSegmentRotateAngleDB;
 * \return map<int, map<int, vector<int> > > rcaCellPositionDB;
 *
 */
/// 从后面开始删除细胞；
void rsRcaDB::RcaCellPositionDB(  rsSourceCorticalDB *RsSourceCorticalDB )
{  map<int, vector<int> >::iterator itMapPosition;
   map<int, vector<double> >::iterator itMapAngle;

   vector<int>::iterator itVecPosition;
   vector<double>::iterator itVecAngle;
   vector<double>::iterator itVecCellAngle;
   vector<double>::iterator itVecMidPointAngle;

   map<int, vector<int> > rcaCellPositionMap1;
   vector<int> rcaCellPosition;
   int i;
   int cellPosition;
   double absAngle;
   double tempAngle;
   double minAngle;
   double minAnglePosition;
   int tempSize;

//   ofstream fout("RCA.txt",ios::app);
//   fout << endl;
//   fout << "RcaCellPositionDB" << endl;
//   fout << endl;
//   fout << "LowerLayer" << endl;
//   fout << endl;
   /// LowerLayer;
   for ( itMapPosition = rcaLowerLayerPositionDB.begin(), itMapAngle = rcaLowerLayerIntersectionAngleHalfDB.begin(),
         itVecMidPointAngle = rcaMidPointAngleDB.begin(), i = 0;
         itMapPosition != rcaLowerLayerPositionDB.end();
         itMapPosition++, itMapAngle++, itVecMidPointAngle++, i++ )
   {  rcaCellPositionMap1.clear();
//      fout << endl;
//      fout << "rcaPosition： " << i << endl;
      for ( itVecPosition = (*itMapPosition).second.begin(), itVecAngle = (*itMapAngle).second.begin();
            itVecPosition != (*itMapPosition).second.end();
            itVecPosition++, itVecAngle++ )
      {  //fout << "LayerPosition： " << *itVecPosition << endl;
         rcaCellPosition.clear();
         minAngle = 360;
         for ( itVecCellAngle = RsSourceCorticalDB -> circleSegmentRotateAngleDB[*itVecPosition].begin(),
               cellPosition = 0;
               itVecCellAngle != RsSourceCorticalDB -> circleSegmentRotateAngleDB[*itVecPosition].end();
               itVecCellAngle++, cellPosition++ )
         {  tempAngle = *itVecCellAngle - *itVecMidPointAngle;
            absAngle = fabs(tempAngle);
//            fout << "cellAngle: " << *itVecCellAngle
//                 << "  rcaMidPointAngle: " << *itVecMidPointAngle
//                 << "  absAngle: " << absAngle
//                 << "  IntersectionAngle: " << *itVecAngle << endl;
            if ( minAngle > absAngle)
            {  minAngle = absAngle;
               minAnglePosition = cellPosition;
//               fout << "minAngle: " << minAngle
//                    << "  minAnglePosition: " << minAnglePosition << endl;
            }
            if ( absAngle < *itVecAngle )
            {  rcaCellPosition.push_back( cellPosition );
//               fout << "cellPosition: " << cellPosition << endl;
            }
         }
         tempSize = rcaCellPosition.size();
         if ( tempSize == 0 )
         {  rcaCellPosition.push_back( minAnglePosition );
//            fout << "cellPosition: " << minAnglePosition << endl;
         }
         rcaCellPositionMap1.insert(pair<int, vector<int> >(*itVecPosition, rcaCellPosition) );
      }
      rcaCellPositionDB.insert(pair<int, map<int, vector<int> > >(i, rcaCellPositionMap1));
   }

/// UpperLayer;
//   fout << endl;
//   fout << "UpperLayer" << endl;
   for ( itMapPosition = rcaUpperLayerPositionDB.begin(), itMapAngle = rcaUpperLayerIntersectionAngleHalfDB.begin(),
         itVecMidPointAngle = rcaMidPointAngleDB.begin(), i = 0;
         itMapPosition != rcaUpperLayerPositionDB.end();
         itMapPosition++, itMapAngle++, itVecMidPointAngle++, i++ )
   {  //fout << endl;
//      fout << "rcaPosition： " << i << endl;
      for ( itVecPosition = (*itMapPosition).second.begin(), itVecAngle = (*itMapAngle).second.begin();
            itVecPosition != (*itMapPosition).second.end();
            itVecPosition++, itVecAngle++ )
      {  //fout << "LayerPosition： " << *itVecPosition << endl;
         rcaCellPosition.clear();
         minAngle = 360;
         for ( itVecCellAngle = RsSourceCorticalDB -> circleSegmentRotateAngleDB[*itVecPosition].begin(),
               cellPosition = 0;
               itVecCellAngle != RsSourceCorticalDB -> circleSegmentRotateAngleDB[*itVecPosition].end();
               itVecCellAngle++, cellPosition++ )
         {  tempAngle = *itVecCellAngle - *itVecMidPointAngle;
            absAngle = fabs(tempAngle);
//            fout << "cellAngle: " << *itVecCellAngle
//                 << "  rcaMidPointAngle: " << *itVecMidPointAngle
//                 << "  absAngle: " << absAngle
//                 << "  IntersectionAngle: " << *itVecAngle << endl;
            if ( minAngle > absAngle)
            {  minAngle = absAngle;
               minAnglePosition = cellPosition;
//               fout << "minAngle: " << minAngle
//                    << "  minAnglePosition: " << minAnglePosition << endl;
            }
            if ( absAngle < *itVecAngle )
            {  rcaCellPosition.push_back( cellPosition );
//               fout << "cellPosition: " << cellPosition << endl;
            }
         }
         tempSize = rcaCellPosition.size();
         if ( tempSize == 0 )
         {  rcaCellPosition.push_back( minAnglePosition );
//            fout << "cellPosition: " << minAnglePosition << endl;
         }
         rcaCellPositionDB[i].insert(pair<int, vector<int> >(*itVecPosition, rcaCellPosition) );
      }
   }

   map<int, map<int, vector<int> > >::iterator itMap2;
   map<int, vector<int> >::iterator itMap1;
   vector<int>::iterator itVec;

//   fout << "RcaCellPositionDB - Output" << endl;
   for ( itMap2 = rcaCellPositionDB.begin(); itMap2 != rcaCellPositionDB.end(); itMap2++ )
   {  // fout << "rcaPosition: " << (*itMap2).first << endl;
//      fout << endl;
      for ( itMap1 = (*itMap2).second.begin(); itMap1 != (*itMap2).second.end(); itMap1++ )
      {  for ( itVec = (*itMap1).second.begin(); itVec != (*itMap1).second.end(); itVec++)
         {  //fout << "layerPosition: " << (*itMap1).first
            //    << "  cellPosition: " << *itVec << endl;
         }
      }
   }std::cout << "Ran till 712 RCADB";
}

/** \brief RcaCellPositionSimplifyDB
 *
 * \param map<int, map<int, vector<int> > > rcaCellPositionDB;
 * \return map<int, vector<int> > rcaCellPositionSimplifyDB;
 *
 */

void rsRcaDB::RcaCellPositionSimplifyDB()
{  map<int, map<int, vector<int> > >::iterator itMap2;
   map<int, vector<int> >::iterator itMap1;
   vector<int>::iterator itVec;
   int layerPosition;
   for ( itMap2 = rcaCellPositionDB.begin(); itMap2 != rcaCellPositionDB.end(); itMap2++ )
   {  for ( itMap1 = (*itMap2).second.begin(); itMap1 != (*itMap2).second.end(); itMap1++ )
      {  layerPosition = (*itMap1).first;
         rcaCellPositionSimplifyDB[ layerPosition ].insert
         ( rcaCellPositionSimplifyDB[ layerPosition ].end(),
           (*itMap1).second.begin(),
           (*itMap1).second.end()
         );
      }
   }std::cout << "Ran till 736 RCADB";
//   ofstream fout("RCA.txt",ios::app);
//   fout << "RcaCellPositionSimplifyDB" << endl;

   vector<int>::iterator itVecOutput;
   map<int, vector<int> >::iterator itMap;
   for ( itMap = rcaCellPositionSimplifyDB.begin(); itMap != rcaCellPositionSimplifyDB.end(); itMap++ )
   {
//       fout << "layerPosition: " << (*itMap).first << endl;
      for ( itVecOutput = (*itMap).second.begin(); itVecOutput != (*itMap).second.end(); itVecOutput++ )
      {
//          fout << *itVecOutput << endl;
      }
   }

   for ( itMap = rcaCellPositionSimplifyDB.begin(); itMap != rcaCellPositionSimplifyDB.end(); itMap++ )
   {
//       fout << "layerPosition: " << (*itMap).first << endl;
      for ( itVecOutput = (*itMap).second.begin(); itVecOutput != (*itMap).second.end(); itVecOutput++ )
      {
//          fout << *itVecOutput << endl;
      }
   }std::cout << "Ran till 758 RCADB";
}

/** \brief RcaRealRatio
 *
 * \param vector<double> objectVerticalDB;
 * \param map<int, vector<double> > circleSegmentLengthDB;
 * \param map<int, vector< vector<double> > > objectHeightDB;
 * \param map<int, vector<int> > rcaCellPositionSimplifyDB;
 * \return double rcaRealVolume;
 *
 */

void rsRcaDB::RcaRealVolume( rsSourceCorticalDB *RsSourceCorticalDB, double totalHeight )
{  vector<int>::iterator itVec;
   vector<int>::iterator itVecHeight;
   map<int, vector<int> >::iterator itMap;
   int i;
   int j;
   double verticalX;
   double parallelY;
   double tempVolume;
//   ofstream fout("RCA.txt",ios::app);
//   fout << "RcaRealVolume" << endl;
   tempVolume = 0;
   for ( itMap = rcaCellPositionSimplifyDB.begin();
         itMap != rcaCellPositionSimplifyDB.end();
         itMap++ )
   {  i = (*itMap).first;
      for ( itVec = (*itMap).second.begin();
            itVec != (*itMap).second.end();
            itVec++ )
      {  j = *itVec;
         verticalX = RsSourceCorticalDB -> objectVerticalDB[i];
         parallelY = RsSourceCorticalDB -> circleSegmentLengthDB[i][j];
         tempVolume += verticalX*2 * parallelY * 2 * totalHeight;
      }
   }
   rcaRealVolume = tempVolume;
   rca2CortexExactRatio = rcaRealVolume / (cortexArea * totalHeight); std::cout << "Ran till 798 RCADB";
}


/** \brief RcaCellErase
 *
 * \param map<int, vector<double> > circleSegmentLengthDB;
 * \param map<int, vector<double> > circleSegmentRotateAngleDB;
 * \param map<int, vector<double> > circleXDB;
 * \param map<int, vector<double> > circleYDB;
 * \param map<int, vector< vector<double> > > objectHeightDB;
 * \param map<int, vector< vector<double> > > objectZPositionDB;
 *
 */
void rsRcaDB::RcaCellErase( rsSourceCorticalDB *RsSourceCorticalDB )
{  vector<int>::reverse_iterator itVec;
   map<int, vector<int> >::reverse_iterator itMap;
   int i;
   int j;

//   ofstream fout("RCA.txt",ios::app);
//   fout << "RcaCellErase" << endl;
   for ( itMap = rcaCellPositionSimplifyDB.rbegin();
         itMap != rcaCellPositionSimplifyDB.rend();
         itMap++ )
   {  i = (*itMap).first;
      for ( itVec = (*itMap).second.rbegin();
            itVec != (*itMap).second.rend();
            itVec++ )
      {  j = *itVec;
         RsSourceCorticalDB -> circleSegmentLengthDB[i].erase( RsSourceCorticalDB -> circleSegmentLengthDB[i].begin() + j - 1 );
         RsSourceCorticalDB -> circleSegmentRotateAngleDB[i].erase( RsSourceCorticalDB -> circleSegmentRotateAngleDB[i].begin() + j - 1 );
         RsSourceCorticalDB -> circleXDB[i].erase( RsSourceCorticalDB -> circleXDB[i].begin() + j - 1 );
         RsSourceCorticalDB -> circleYDB[i].erase( RsSourceCorticalDB -> circleYDB[i].begin() + j - 1 );
         RsSourceCorticalDB -> objectHeightDB[i].erase( RsSourceCorticalDB -> objectHeightDB[i].begin() + j - 1 );
         RsSourceCorticalDB -> objectZPositionDB[i].erase( RsSourceCorticalDB -> objectZPositionDB[i].begin() + j - 1 );
//         fout << "layerPosition: " << i << "  "<< "cellPosition: " << j << endl;
      }
   }
}




/// Initialize rcaDB;
void rsRcaDB::InitBasicRcaDB( double rcaRatioInput,
                              int rcaNumInput,
                              int standardOuterLayerInput,
                              int standardInnerLayerInput,
                              double baseRadius,
                              rsSourceCorticalDB *RsSourceCorticalDB,
                              double variationRatio
                            )
{
/// GetRcaData
   GetRcaData( rcaRatioInput,
               rcaNumInput,
               standardOuterLayerInput,
               standardInnerLayerInput );

/// cortexArea;
   CortexArea( baseRadius,
               RsSourceCorticalDB );

/// rcaTotalArea;
   RcaTotalArea();

/// rcaArea;
   RcaArea( variationRatio );

/// rcaVerticalLengthStoreDB;
   RcaVerticalLengthStoreDB( RsSourceCorticalDB );

/// The rcaRation must be between 0.01 - 0.60;
   RcaVerticalLengthStoreSelectRange( RsSourceCorticalDB );

/// RcaVerticalLengthDB;
   RcaVerticalLengthDB();



}


void rsRcaDB::CalculateRcaDB(  double baseRadius,
                               rsSourceCorticalDB *RsSourceCorticalDB,
                               double variationRatio,
                               double gapAngleBetweenRcaRatio,
                               double totalHeight)
{
/// ParallelRadiusDB;
   ParallelRadiusDB();

   /// This radius is a radius for the whole cross-section;
/// rcaCenterVerticalMiddleRadius;
   RcaCenterVerticalMiddleRadiusDB( baseRadius,
                                    RsSourceCorticalDB );

/// RcaIntersetionAngleHalfDB;
   RcaIntersetionAngleHalfDB();

/// GapAngleBetweenRcaDB;
   GapAngleBetweenRcaDB( gapAngleBetweenRcaRatio );

/// SurplusAngleTotal;
   SurplusAngleTotal();

/// SurplusAngleDistribution;
   SurplusAngleDistribution( variationRatio );

/// RcaMidPointAngleDB;
   RcaMidPointAngleDB();

/// RcaLowerUpperLayerPositionDB;
   RcaLowerUpperLayerPositionDB( RsSourceCorticalDB );

/// RcaLowerLayerIntersectionAngleDB;
   RcaLowerUpperLayerIntersectionAngleDB();

/// rcaCellPositionDB;
   RcaCellPositionDB( RsSourceCorticalDB );

/// RcaCellPositionSimplifyDB
   RcaCellPositionSimplifyDB();

/// RcaRealVolume;
   RcaRealVolume( RsSourceCorticalDB, totalHeight );
}

void rsRcaDB::JudgeAccuracyRcaDB(double baseRadius,
                                 rsSourceCorticalDB *RsSourceCorticalDB,
                                 double variationRatio,
                                 double gapAngleBetweenRcaRatio,
                                 double totalHeight)
{  middleRadiusAdjustRatio = 1.2;
   parallelRadiusAdjustRatio = 1;
   CalculateRcaDB(  baseRadius,
                    RsSourceCorticalDB,
                    variationRatio,
                    gapAngleBetweenRcaRatio,
                    totalHeight);
   ofstream fout( "gapInput2ExactFabs.txt", ios::app);
   fout << endl;

   double gapInput2Exact = 0;
   double gapInput2ExactFabs = 0;
   gapInput2ExactFabs = fabs( rca2CortexExactRatio - rcaRatio );
   gapInput2Exact = rca2CortexExactRatio - rcaRatio;

   if ( rcaRatio < 0.1 )

   {  while ( gapInput2ExactFabs >= 0.01 )
      {  if ( gapInput2Exact > 0 )
         {  parallelRadiusAdjustRatio = parallelRadiusAdjustRatio - 0.002;
         }
         else
         {  parallelRadiusAdjustRatio = parallelRadiusAdjustRatio + 0.002;
         }
         fout << "gapInput2ExactFabs: " << gapInput2ExactFabs
              << "  gapInput2Exact: " << gapInput2Exact
              << "  parallelRadiusAdjustRatio: " << parallelRadiusAdjustRatio
              << "  rca2CortexExactRatio: " << rca2CortexExactRatio << endl;
         parallelRadiusDB.clear();
         rcaCenterVerticalMiddleRadiusDB.clear();
         rcaIntersetionAngleHalfDB.clear();
         rcaAddIntersetionAngleDB.clear();
         gapAddAngleBetweenRcaDB.clear();
         surplusAngleDistribution.clear();
         surplusAddAngleDistribution.clear();
         rcaMidPointAngleDB.clear();
         rcaLowerLayerPositionDB.clear();
         rcaUpperLayerPositionDB.clear();
         rcaLowerLayerIntersectionAngleHalfDB.clear();
         rcaUpperLayerIntersectionAngleHalfDB.clear();
         rcaCellPositionDB.clear();
         rcaCellPositionSimplifyDB.clear();

         CalculateRcaDB(  baseRadius,
                          RsSourceCorticalDB,
                          variationRatio,
                          gapAngleBetweenRcaRatio,
                          totalHeight);

         gapInput2ExactFabs = fabs( rca2CortexExactRatio - rcaRatio );
         gapInput2Exact = rca2CortexExactRatio - rcaRatio;
      }

      fout << "Last: "<< "  gapInput2ExactFabs: " << gapInput2ExactFabs
           << "  gapInput2Exact: " << gapInput2Exact
           << "  parallelRadiusAdjustRatio: " << parallelRadiusAdjustRatio
           << "  rca2CortexExactRatio: " << rca2CortexExactRatio << endl;

   }
   else
   {  while ( gapInput2ExactFabs >= 0.005 )
      {  if ( gapInput2Exact > 0 )
         {  parallelRadiusAdjustRatio = parallelRadiusAdjustRatio - 0.002;
         }
         else
         {  parallelRadiusAdjustRatio = parallelRadiusAdjustRatio + 0.002;
         }
         fout << "gapInput2ExactFabs: " << gapInput2ExactFabs
              << "  gapInput2Exact: " << gapInput2Exact
              << "  parallelRadiusAdjustRatio: " << parallelRadiusAdjustRatio
              << "  rca2CortexExactRatio: " << rca2CortexExactRatio << endl;
         parallelRadiusDB.clear();
         rcaCenterVerticalMiddleRadiusDB.clear();
         rcaIntersetionAngleHalfDB.clear();
         rcaAddIntersetionAngleDB.clear();
         gapAddAngleBetweenRcaDB.clear();
         surplusAngleDistribution.clear();
         surplusAddAngleDistribution.clear();
         rcaMidPointAngleDB.clear();
         rcaLowerLayerPositionDB.clear();
         rcaUpperLayerPositionDB.clear();
         rcaLowerLayerIntersectionAngleHalfDB.clear();
         rcaUpperLayerIntersectionAngleHalfDB.clear();
         rcaCellPositionDB.clear();
         rcaCellPositionSimplifyDB.clear();

         CalculateRcaDB(  baseRadius,
                          RsSourceCorticalDB,
                          variationRatio,
                          gapAngleBetweenRcaRatio,
                          totalHeight);

         gapInput2ExactFabs = fabs( rca2CortexExactRatio - rcaRatio );
         gapInput2Exact = rca2CortexExactRatio - rcaRatio;
      }

      fout << "Last: "<< "  gapInput2ExactFabs: " << gapInput2ExactFabs
           << "  gapInput2Exact: " << gapInput2Exact
           << "  parallelRadiusAdjustRatio: " << parallelRadiusAdjustRatio
           << "  rca2CortexExactRatio: " << rca2CortexExactRatio << endl;
   }
}

void rsRcaDB::InitRcaDB( double rcaRatioInput,
                         int rcaNumInput,
                         int standardOuterLayerInput,
                         int standardInnerLayerInput,
                         double baseRadius,
                         rsSourceCorticalDB *RsSourceCorticalDB,
                         double variationRatio,
                         double gapAngleBetweenRcaRatio,
                         double totalHeight
                       )
{  InitBasicRcaDB( rcaRatioInput,
                   rcaNumInput,
                   standardOuterLayerInput,
                   standardInnerLayerInput,
                   baseRadius,
                   RsSourceCorticalDB,
                   variationRatio
                 );

   JudgeAccuracyRcaDB(baseRadius,
                      RsSourceCorticalDB,
                      variationRatio,
                      gapAngleBetweenRcaRatio,
                      totalHeight
                     );

   /// RcaCellErase;
   RcaCellErase( RsSourceCorticalDB );

}

