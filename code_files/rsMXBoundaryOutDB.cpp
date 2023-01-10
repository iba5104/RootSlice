#define _USE_MATH_DEFINES
#include <cmath> 
#include "rsMXBoundaryOutDB.h"

/** \brief tangentRingRadius: the frontier ring radius;
 *
 * \param double boundaryMXPXRingRadiusDeliver;
 * \param double mxMaxBoundaryRadius;
 * \return double tangentRingRadius;
 *
 */
double tangentRingRadius;
void rsMXBoundaryOutDB::TangentRingRadius()
{
	tangentRingRadius = boundaryMXPXRingRadiusDeliver - mxMaxBoundaryRadius * 2;
}

/** \brief innerRingRadius;
 *
 * \param double innerTangentRingRadiusRatioTemp = innerRingRadius/tangentRingRadius;
 * \return double innerRingRadius;;
 *
 */
double innerRingRadius;
void rsMXBoundaryOutDB::InnerRingRadius(double innerTangentRingRadiusRatioTemp)
{
	innerRingRadius = innerTangentRingRadiusRatioTemp * tangentRingRadius;
	if (type_dicot)
		innerRingRadius = (noCentreMX) ? 0.0 : boundaryRadiusDB[0];
}

void rsMXBoundaryOutDB::SetInnerRingRadius(double setInnerRingRadius)
{
	innerRingRadius = setInnerRingRadius;
}

/********************************************************************
								 MXInter
*********************************************************************/

/** \brief
 *
 * \param int setInterVerticalNum = 8;
 * \return double interVerticalNum;
 *
 */
double interVerticalNum;
void rsMXBoundaryOutDB::InterVerticalNum(int setInterVerticalNum)
{
	interVerticalNum = setInterVerticalNum;
}

/** \brief interVerticalLengthTotal
 *
 * \param double boundaryMXPXRingRadiusDeliver;
 * \param double innerRingRadius;
 * \return double interVerticalLengthTotal;
 *
 */
double interVerticalLengthTotal;
void rsMXBoundaryOutDB::InterVerticalLengthTotal()
{
	interVerticalLengthTotal = boundaryMXPXRingRadiusDeliver - innerRingRadius;
}

void rsMXBoundaryOutDB::CalculateInterVerticalLengthTotal(double maxRadius)
{
	interVerticalLengthTotal = maxRadius - innerRingRadius;
}

/** \brief interVerticalLengthAverage
 *
 * \param double interVerticalLengthTotal;
 * \param double interVerticalNum;
 * \return double interVerticalLengthAverage;
 *
 */
double interVerticalLengthAverage;
void rsMXBoundaryOutDB::InterVerticalLengthAverage()
{
	interVerticalLengthAverage = interVerticalLengthTotal / interVerticalNum;
}

vector<double> interVerticalLengthDB;
vector<double> interVerticalLengthAddDB;
void rsMXBoundaryOutDB::InterVerticalLengthDB(double variationRatio)
{  //ofstream fout("a.txt",ios::app);
   //fout << "InterVerticalLengthDB" << endl;
	vector<double> interVerticalLengthTemp;
	vector<double> interVerticalLengthAddTemp;
	
	RandomRatioButSameSumAndNumber(interVerticalLengthTemp,
		interVerticalLengthAddTemp,
		interVerticalLengthTotal,
		interVerticalNum,
		variationRatio);

	for (double var1 : interVerticalLengthTemp)
		interVerticalLengthDB.push_back(var1);
	for (double var1 : interVerticalLengthAddTemp)
		interVerticalLengthAddDB.push_back(var1);
	
	//   fout << "interVerticalLengthTotal: " << interVerticalLengthTotal << "  interVerticalNum: " << interVerticalNum
	//        << "  randomRange: " << randomRange << endl;
}
/** \brief interVerticalLengthHalfDB
 *
 * \param vector<double> interVerticalLengthDB;
 * \return vector<double> interVerticalLengthHalfDB;
 *
 */

vector<double> interVerticalLengthHalfDB;
void rsMXBoundaryOutDB::InterVerticalLengthHalfDB()
{
	vector<double>::iterator itVec;
	double temp;
	//   ofstream fout("a.txt",ios::app);
	//   fout << "InterVerticalLengthHalfDB" << endl;
	for (itVec = interVerticalLengthDB.begin();
		itVec != interVerticalLengthDB.end();
		itVec++)
	{
		temp = *itVec / 2.0;
		interVerticalLengthHalfDB.push_back(temp);
		//      fout << "temp: " << temp << endl;
	}
}

/** \brief interVerticalCenterRadiusDB
 *
 * \param vector<double> interVerticalLengthDB;
 * \param vector<double> interVerticalLengthAddDB;
 * \param double innerRingRadius;;

 * \return vector<double> interVerticalCenterRadiusDB;
 *
 */

vector<double> interVerticalCenterRadiusDB;
void rsMXBoundaryOutDB::InterVerticalCenterRadiusDB()
{
	vector<double>::iterator itVec;
	vector<double>::iterator itVecAdd;
	double temp;
	//   ofstream fout("a.txt",ios::app);
	//   fout << "InterVerticalCenterRadiusDB" << endl;
	for (itVec = interVerticalLengthDB.begin(), itVecAdd = interVerticalLengthAddDB.begin();
		itVec != interVerticalLengthDB.end();
		itVec++, itVecAdd++)
	{
		temp = innerRingRadius + *itVecAdd + (*itVec) / 2.0;
		interVerticalCenterRadiusDB.push_back(temp);
		//      fout << "temp: " << temp << "  interVerticalLengthAddDB: " << *itVecAdd
		//           << "  interVerticalLengthDB: " << *itVec << endl;
	}
}

/** \brief InterRadianStartAndEndDB
 *
 * \param vector<double> boundaryRadianEndDB;
 * \param vector<double> boundaryRadianStartDB;
 * \return vector<double> interRadianStartDB;
 * \return vector<double> interRadianEndDB;
 * \return vector<double> interIntersectionRadianDB;
 *
 */

vector<double> interRadianStartDB;
vector<double> interRadianEndDB;
vector<double> interIntersectionRadianDB;
void rsMXBoundaryOutDB::InterRadianStartAndEndDB()
{
	vector<double>::iterator itVecStart;
	vector<double>::iterator itVecEnd;
	vector<double>::iterator itVec;
	vector<double>::iterator itVecInterStart;
	vector<double>::iterator itVecInterEnd;
	double temp;
	//   ofstream fout("a.txt",ios::app);
	//   fout << "InterRadianStartAndEndDB" << endl;
	for (itVecEnd = boundaryRadianEndDB.begin();
		itVecEnd != boundaryRadianEndDB.end();
		itVecEnd++)
	{
		interRadianStartDB.push_back(*itVecEnd);
		//      fout << "interRadianStartDB: " << *itVecEnd << endl;
	}
	/// Append from the second one to the last one as the last one  in boundaryRadianStartDB
	/// to interRadianStartDB;
	for (itVecStart = boundaryRadianStartDB.begin() + 1;
		itVecStart != boundaryRadianStartDB.end();
		itVecStart++)
	{
		interRadianEndDB.push_back(*itVecStart);
		//      fout << "interRadianEndDB: " << *itVecStart << endl;
	}
	/// Append the first one in boundaryRadianStartDB as the last one in interRadianStartDB;
	itVec = boundaryRadianStartDB.begin();
	temp = *itVec + +2 * M_PI;
	interRadianEndDB.push_back(temp);
	//   fout << "interRadianEndDB: " << temp << endl;

	for (itVecInterEnd = interRadianEndDB.begin(), itVecInterStart = interRadianStartDB.begin();
		itVecInterEnd != interRadianEndDB.end();
		itVecInterEnd++, itVecInterStart++)
	{
		temp = *itVecInterEnd - *itVecInterStart;
		interIntersectionRadianDB.push_back(temp);
		//      fout << "interIntersectionRadianDB: " << temp << endl;
	}
}
/** \brief interParallelPerimeterDB
 *
 * \param vector<double> interIntersectionRadianDB;
 * \param vector<double> interVerticalCenterRadiusDB;
 * \return map<int, vector<double> > interParallelPerimeterDB;
 *
 */

map<int, vector<double> > interParallelPerimeterDB;
void rsMXBoundaryOutDB::InterParallelPerimeterDB()
{
	vector<double>::iterator itVecRadian;
	vector<double>::iterator itVecRadius;
	vector<double>::iterator itVec;
	vector<double> interParallelPerimeter;
	double temp;
	int i;
	int j;

	//   ofstream fout("a.txt",ios::app);
	//   fout << "InterParallelPerimeterDB" << endl;
	for (itVecRadian = interIntersectionRadianDB.begin(), i = 0;
		itVecRadian != interIntersectionRadianDB.end();
		itVecRadian++, i++)
	{
		interParallelPerimeter.clear();
		for (itVecRadius = interVerticalCenterRadiusDB.begin(), j = 0;
			itVecRadius != interVerticalCenterRadiusDB.end();
			itVecRadius++, j++)
		{
			temp = (*itVecRadius) * (*itVecRadian);
			interParallelPerimeter.push_back(temp);
			//         fout << "i: " << i << "  j: " << j << "  "<< temp << endl;
		}
		interParallelPerimeterDB.insert(pair<int, vector<double> >(i, interParallelPerimeter));
	}
}

void rsMXBoundaryOutDB::DicotInterRadian(int rIdx, int numIter)
{
	int prev = interRadianEndDB.size();

	for (int i = 0; i < numIter; i++)
	{
		interRadianStartDB.push_back(boundaryRadianEndDB[rIdx+i]);
		double endVal = boundaryRadianStartDB[rIdx + i];
		if (endVal < 0)
			endVal += 2 * M_PI;
		interRadianEndDB.push_back(endVal);
	}
	rotate(interRadianEndDB.begin()+prev, interRadianEndDB.begin() + 1+prev, interRadianEndDB.end());
}

void rsMXBoundaryOutDB::DicotInterRadianDB()
{
	vector<double>::iterator itVecInterStart;
	vector<double>::iterator itVecInterEnd;
	double temp;

	for (itVecInterEnd = interRadianEndDB.begin(), itVecInterStart = interRadianStartDB.begin();
		itVecInterEnd != interRadianEndDB.end();
		itVecInterEnd++, itVecInterStart++)
	{
		temp = *itVecInterEnd - *itVecInterStart;
		interIntersectionRadianDB.push_back(temp);
	}
}

void rsMXBoundaryOutDB::DicotInterRadianAndParallelPerimeterDB()
{
	vector<double> radianDiff;
	vector<double> radianStartTemp;

	vector<double>::iterator itVecInterStart;
	vector<double>::iterator itVecInterEnd;
	double temp;
	//int numSections = *max_element(eachRingMXNum.begin(), eachRingMXNum.end());
	int start_pos = 0;

	for (int i = 0; i < eachRingMXNum.size(); i++)
	{
		radianDiff.clear();
		radianStartTemp.clear();
		for (int j = 0; j < eachRingMXNum[i]; j++)
		{
			int startIdx = (i == 0) ? j : (j + (i * eachRingMXNum[i-1]));
			int endIdx = (j == (eachRingMXNum[i] - 1)) ? 0 : (startIdx + 1);
			double startVal = boundaryRadianEndDB[startIdx];
			double endVal = boundaryRadianStartDB[endIdx];
			if (endVal < 0)
				endVal += 2 * M_PI;
			double diffTemp = endVal - startVal;
			if (diffTemp < 0)
				diffTemp = 0;
			radianDiff.push_back(diffTemp);
			radianStartTemp.push_back(startVal);
		}
		/*if (j < numSections) {
			int end_pos = j + start_pos + eachRingMXNum[i];
			int nextI = ((i + 1) < eachRingMXNum.size()) ? (i + 1) : 0;
			if (j >= eachRingMXNum[nextI])
				end_pos--;
			if (end_pos >= boundaryRadianStartDB.size())
				end_pos = j + 1;
			double startVal = boundaryRadianEndDB[start_pos + j - 1];
			double endVal = boundaryRadianStartDB[end_pos];
			if (endVal < 0)
				endVal += 2 * M_PI;
			double diffTemp = endVal - startVal;
			radianDiff.push_back(diffTemp);
			radianStartTemp.push_back(startVal);
		}*/
		interIntersectionRadianDicot.insert(pair<int, vector<double> >(i, radianDiff));
		interRadianStartDicot.insert(pair<int, vector<double>>(i, radianStartTemp));
	}

	map<int, vector<double>>::iterator itMapRadian;
	vector<double>::iterator itVecRadian;
	vector<double>::iterator itVecRadius;
	vector<double>::iterator itVec;
	vector<double> interParallelPerimeter;
	int i = 0;
	
	for (itMapRadian = interIntersectionRadianDicot.begin(), i = 0;
		itMapRadian != interIntersectionRadianDicot.end();
		itMapRadian++, i++)
	{
		interParallelPerimeter.clear();
		itVecRadius = interVerticalCenterRadiusDB.begin();
		int sectionCount = ceil(interVerticalCenterRadiusDB.size() / mxRingNum);
		for (itVecRadian = (*itMapRadian).second.begin();
			itVecRadian != (*itMapRadian).second.end();
			itVecRadian++)
		{
			int j = 0;
			while (j < sectionCount)
			{
				if (interParallelPerimeter.size() == interVerticalCenterRadiusDB.size())
					break;
				temp = (*itVecRadius) * (*itVecRadian);
				interParallelPerimeter.push_back(temp);
				itVecRadius++;
				j++;
			}
		}
		interParallelPerimeterDB.insert(pair<int, vector<double> >(i, interParallelPerimeter));
	}
}

/** \brief interParallelNumDB
 *
 * \param map<int, vector<double> > interParallelPerimeterDB;
 * \param vector<double> interVerticalLengthDB
 * \return map<int, vector<double> > interParallelNumDB;
 *
 */

map<int, vector<double> > interParallelNumDB;
void rsMXBoundaryOutDB::InterParallelNumDB()
{
	map<int, vector<double> >::iterator  itMapPerimeter;
	vector<double>::iterator itVecPerimeter;
	vector<double>::iterator itVecLength;
	vector<double> interParallelNum;
	double doubleNum;
	int intNum;
	int i;
	int j;

	//   ofstream fout("a.txt",ios::app);
	//   fout << "InterParallelNumDB" << endl;
	for (itMapPerimeter = interParallelPerimeterDB.begin(), i = 0;
		itMapPerimeter != interParallelPerimeterDB.end();
		itMapPerimeter++, i++)
	{
		interParallelNum.clear();
		for (itVecPerimeter = (*itMapPerimeter).second.begin(), itVecLength = interVerticalLengthDB.begin(), j = 0;
			itVecPerimeter != (*itMapPerimeter).second.end();
			itVecPerimeter++, itVecLength++, j++)
		{
			doubleNum = *itVecPerimeter / *itVecLength;
			if (doubleNum < 1)
			{
				intNum = 1;
			}
			else
			{
				intNum = int(doubleNum + 0.5);
			}
			interParallelNum.push_back(intNum);
			//         fout << "i: " << i << "  j: " << j <<
			//              "  intNum: " << intNum << endl;
		}
		interParallelNumDB.insert(pair<int, vector<double> >(i, interParallelNum));
	}
}

/** \brief interParallelLengthDB
 *
 * \param map<int, vector<double> > interParallelPerimeterDB;
 * \param map<int, vector<double> > interParallelNumDB;
 * \return map<int, vector<double> > interParallelLengthDB;
 *
 */

map<int, vector<double> > interParallelLengthDB;
void rsMXBoundaryOutDB::InterParallelLengthDB()
{
	map<int, vector<double> >::iterator  itMapPerimeter;
	vector<double>::iterator itVecPerimeter;
	map<int, vector<double> >::iterator  itMapNum;
	vector<double>::iterator itVecNum;
	vector<double> interParallelLength;
	double temp;
	int i;
	int j;
	//   ofstream fout("a.txt",ios::app);
	//   fout << "InterParallelLengthDB" << endl;
	for (itMapPerimeter = interParallelPerimeterDB.begin(), itMapNum = interParallelNumDB.begin(), i = 0;
		itMapPerimeter != interParallelPerimeterDB.end();
		itMapPerimeter++, itMapNum++, i++)
	{
		interParallelLength.clear();
		for (itVecPerimeter = (*itMapPerimeter).second.begin(), itVecNum = (*itMapNum).second.begin(), j = 0;
			itVecPerimeter != (*itMapPerimeter).second.end();
			itVecPerimeter++, itVecNum++, j++)
		{
			if (*itVecNum == 0)
				temp = 0;
			else
				temp = *itVecPerimeter / *itVecNum;
			interParallelLength.push_back(temp);
			//         fout << "i: " << i << "  j: " << j
			//              << "  temp: " << temp << "  interParallelPerimeterDB: " << *itVecPerimeter
			//              << "  interParallelNumDB: " << *itVecNum << endl;
		}
		interParallelLengthDB.insert(pair<int, vector<double> >(i, interParallelLength));
	}
}

/** \brief
 *
 * \param map<int, vector<double> > interParallelLengthDB;
 * \return map<int, vector<double> > interParallelLengthHalfDB;
 *
 */
map<int, vector<double> > interParallelLengthHalfDB;
void rsMXBoundaryOutDB::InterParallelLengthHalfDB()
{
	map<int, vector<double> >::iterator  itMap;
	vector<double>::iterator itVec;
	vector<double> interParallelLengthHalf;
	double temp;
	int i;
	int j;
	for (itMap = interParallelLengthDB.begin(), i = 0;
		itMap != interParallelLengthDB.end();
		itMap++, i++)
	{
		interParallelLengthHalf.clear();
		for (itVec = (*itMap).second.begin(), j = 0;
			itVec != (*itMap).second.end();
			itVec++, j++)
		{
			temp = *itVec / 2.0;
			interParallelLengthHalf.push_back(temp);
		}
		interParallelLengthHalfDB.insert(pair<int, vector<double> >(i, interParallelLengthHalf));
	}
}

/** \brief interParallelRadianDivideDB
 *
 * \param vector<double> interIntersectionRadianDB;
 * \param map<int, vector<double> > interParallelNumDB;
 * \return map<int, vector<double> > interIntersectionRadianDivideDB;
 *
 */

map<int, vector<double> > interIntersectionRadianDivideDB;
void rsMXBoundaryOutDB::InterParallelRadianDivideDB()
{
	map<int, vector<double> >::iterator  itMapNum;
	vector<double>::iterator itVecNum;
	map<int, vector<double>>::iterator itMapRadian;
	vector<double>::iterator itVecRadian;
	vector<double> interIntersectionRadianDivide;
	double temp;
	int i;
	int j;
	//   ofstream fout("a.txt",ios::app);
	//   fout << "InterParallelRadianDivideDB" << endl;
	//if (type_dicot)
	//{
	//	for (itMapNum = interParallelNumDB.begin(), itMapRadian = interIntersectionRadianDicot.begin(), i = 0;
	//		itMapNum != interParallelNumDB.end();
	//		itMapNum++, itMapRadian++, i++)
	//	{
	//		interIntersectionRadianDivide.clear();
	//		for (itVecNum = (*itMapNum).second.begin(), itVecRadian = (*itMapRadian).second.begin(), j = 0;
	//			itVecNum != (*itMapNum).second.end();
	//			itVecNum++)
	//		{
	//			temp = *itVecRadian / *itVecNum;
	//			interIntersectionRadianDivide.push_back(temp);
	//			j++;
	//			if (j == (*itMapRadian).second.size())
	//			{
	//				itVecRadian++;
	//				j = 0;
	//			}
	//			//         fout << "i: " << i << "  j: " << j
	//			//              << "  temp: " << temp << endl;
	//			//         fout << "interIntersectionRadianDB: " << *itVecRadian << "  interParallelNumDB: " << *itVecNum << endl;
	//		}
	//		interIntersectionRadianDivideDB.insert(pair<int, vector<double> >(i, interIntersectionRadianDivide));
	//	}
	//}
	//else
	//{
		for (itMapNum = interParallelNumDB.begin(), itVecRadian = interIntersectionRadianDB.begin(), i = 0;
			itMapNum != interParallelNumDB.end();
			itMapNum++, itVecRadian++, i++)
		{
			interIntersectionRadianDivide.clear();
			for (itVecNum = (*itMapNum).second.begin(), j = 0;
				itVecNum != (*itMapNum).second.end();
				itVecNum++, j++)
			{
				temp = *itVecRadian / *itVecNum;
				interIntersectionRadianDivide.push_back(temp);
				//         fout << "i: " << i << "  j: " << j
				//              << "  temp: " << temp << endl;
				//         fout << "interIntersectionRadianDB: " << *itVecRadian << "  interParallelNumDB: " << *itVecNum << endl;
			}
			interIntersectionRadianDivideDB.insert(pair<int, vector<double> >(i, interIntersectionRadianDivide));
		}
	//}
}
/** \brief interParallelCenterRadianDB
 *
 * \param vector<double> interRadianStartDB;
 * \param map<int, vector<double> > interIntersectionRadianDivideDB;
 * \param map<int, vector<double> > interParallelNumDB;
 * \return map<int, vector<vector<double> > > interCellCenterRadianDB;
 *
 */

map<int, vector<vector<double> > > interCellCenterRadianDB;
void rsMXBoundaryOutDB::InterCellCenterRadianDB()
{
	map<int, vector<double>>::iterator itMapRadianStart;
	vector<double>::iterator itVecRadianStart;
	map<int, vector<double> >::iterator  itMapNum;
	vector<double>::iterator itVecNum;
	map<int, vector<double> >::iterator  itMapRadianDivide;
	vector<double>::iterator itVecRadianDivide;

	vector<vector<double> > interCellCenterRadianVec2;
	vector<double> interCellCenterRadianVec1;
	double sum;
	double tempSum;
	double temp;
	int i;
	int j;
	int k;
	int num;
	ofstream fout(getFolderName() + "a.txt", ios::app);
	fout << "InterCellCenterRadianDB" << endl;
	//if (type_dicot)
	//{
	//	for (itMapNum = interParallelNumDB.begin(), itMapRadianStart = interRadianStartDicot.begin(),
	//			itMapRadianDivide = interIntersectionRadianDivideDB.begin(), i = 0;
	//		itMapNum != interParallelNumDB.end(); itMapNum++, itMapRadianStart++, itMapRadianDivide++, i++)
	//	{
	//		interCellCenterRadianVec2.clear();
	//		for (itVecNum = (*itMapNum).second.begin(), itVecRadianStart = (*itMapRadianStart).second.begin(),
	//				itVecRadianDivide = (*itMapRadianDivide).second.begin(), j = 0;
	//			itVecNum != (*itMapNum).second.end(); itVecNum++, itVecRadianDivide++)
	//		{
	//			interCellCenterRadianVec1.clear();
	//			sum = 0;
	//			tempSum = 0;
	//			for (num = 0, k = 0; num != *itVecNum; num++, k++)
	//			{
	//				if (num == 0)
	//				{
	//					tempSum = 0;
	//					sum = tempSum + *itVecRadianDivide / 2;
	//					temp = *itVecRadianStart + sum;
	//					interCellCenterRadianVec1.push_back(temp);
	//				}
	//				else
	//				{
	//					tempSum += *itVecRadianDivide;
	//					sum = tempSum + *itVecRadianDivide / 2;
	//					temp = *itVecRadianStart + sum;
	//					interCellCenterRadianVec1.push_back(temp);
	//				}
	//				//            fout << "i: " << i << "  j: " << j << "  k: " << k <<
	//				//                 "  temp: " << temp << endl;
	//			}
	//			j++;
	//			if (j == (*itMapRadianStart).second.size())
	//			{
	//				itVecRadianStart++;
	//				j = 0;
	//			}
	//			interCellCenterRadianVec2.push_back(interCellCenterRadianVec1);
	//		}
	//		interCellCenterRadianDB.insert(pair<int, vector<vector<double> > >(i, interCellCenterRadianVec2));
	//	}
	//}
	//else
	//{
		for (itMapNum = interParallelNumDB.begin(), itVecRadianStart = interRadianStartDB.begin(),
			itMapRadianDivide = interIntersectionRadianDivideDB.begin(), i = 0;
			itMapNum != interParallelNumDB.end();
			itMapNum++, itVecRadianStart++, itMapRadianDivide++, i++)
		{
			interCellCenterRadianVec2.clear();
			for (itVecNum = (*itMapNum).second.begin(), itVecRadianDivide = (*itMapRadianDivide).second.begin(), j = 0;
				itVecNum != (*itMapNum).second.end();
				itVecNum++, itVecRadianDivide++, j++)
			{
				interCellCenterRadianVec1.clear();
				sum = 0;
				tempSum = 0;
				for (num = 0, k = 0; num != *itVecNum; num++, k++)
				{
					if (num == 0)
					{
						tempSum = 0;
						sum = tempSum + *itVecRadianDivide / 2;
						temp = *itVecRadianStart + sum;
						interCellCenterRadianVec1.push_back(temp);
					}
					else
					{
						tempSum += *itVecRadianDivide;
						sum = tempSum + *itVecRadianDivide / 2;
						temp = *itVecRadianStart + sum;
						interCellCenterRadianVec1.push_back(temp);
					}
					//            fout << "i: " << i << "  j: " << j << "  k: " << k <<
					//                 "  temp: " << temp << endl;
				}
				interCellCenterRadianVec2.push_back(interCellCenterRadianVec1);
			}
			interCellCenterRadianDB.insert(pair<int, vector<vector<double> > >(i, interCellCenterRadianVec2));
		}
	//}
}
/** \brief interParallelCenterRotateAngleDB
 *
 * \param map<int, vector<vector<double> > > interCellCenterRadianDB;
 * \return map<int, vector<vector<double> > > interCellCenterRotateAngleDB;
 *
 */

map<int, vector<vector<double> > > interCellCenterRotateAngleDB;
void rsMXBoundaryOutDB::InterCellCenterRotateAngleDB()
{
	map<int, vector<vector<double> > >::iterator  itMap;
	vector<vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;

	vector<vector<double> > interCellCenterRotateAngleVec2;
	vector<double> interCellCenterRotateAngleVec1;
	double tempAngle;
	int i;
	for (itMap = interCellCenterRadianDB.begin(), i = 0;
		itMap != interCellCenterRadianDB.end();
		itMap++, i++)
	{
		interCellCenterRotateAngleVec2.clear();
		for (itVec2 = (*itMap).second.begin();
			itVec2 != (*itMap).second.end();
			itVec2++)
		{
			interCellCenterRotateAngleVec1.clear();
			for (itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				itVec1++)
			{
				tempAngle = (-1) * (*itVec1) / M_PI * 180;
				interCellCenterRotateAngleVec1.push_back(tempAngle);
			}
			interCellCenterRotateAngleVec2.push_back(interCellCenterRotateAngleVec1);
		}
		interCellCenterRotateAngleDB.insert(pair<int, vector<vector<double> > >(i, interCellCenterRotateAngleVec2));
	}
}
/** \brief interCellXYDB
 *
 * \param map<int, vector<vector<double> > > interCellCenterRadianDB;
 * \param vector<double> interVerticalCenterRadiusDB;
 * \return map<int, vector<vector<double> > > interCellXDB;
 * \return map<int, vector<vector<double> > > interCellYDB;
 *
 */

map<int, vector<vector<double> > > interCellXDB;
map<int, vector<vector<double> > > interCellYDB;
void rsMXBoundaryOutDB::InterCellXYDB()
{
	map<int, vector<vector<double> > >::iterator  itMap;
	vector<vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;
	vector<double>::iterator itVec;

	vector<vector<double> > interCellXVec2;
	vector<double> interCellXVec1;
	vector<vector<double> > interCellYVec2;
	vector<double> interCellYVec1;

	double tempX;
	double tempY;
	int i;
	int j;
	int k;
	//   ofstream fout("a.txt",ios::app);
	//   fout << "InterCellXYDB" << endl;
	for (itMap = interCellCenterRadianDB.begin(), i = 0;
		itMap != interCellCenterRadianDB.end();
		itMap++, i++)
	{
		interCellXVec2.clear();
		interCellYVec2.clear();
		for (itVec2 = (*itMap).second.begin(), itVec = interVerticalCenterRadiusDB.begin(), j = 0;
			itVec2 != (*itMap).second.end();
			itVec2++, itVec++, j++)
		{
			interCellXVec1.clear();
			interCellYVec1.clear();
			for (itVec1 = (*itVec2).begin(), k = 0;
				itVec1 != (*itVec2).end();
				itVec1++, k++)
			{
				tempX = (*itVec) * cos(*itVec1);
				tempY = (*itVec) * sin(*itVec1);
				interCellXVec1.push_back(tempX);
				interCellYVec1.push_back(tempY);
				//            fout << "i: " << i << "  j: " << j << "  k: " << k <<
				//                 "  tempX: " << tempX  << "  tempY: " << tempY
				//                 << "  interVerticalCenterRadiusDB: " << *itVec
				//                 << "  interCellCenterRadianDB: " << *itVec1 << endl;
			}
			interCellXVec2.push_back(interCellXVec1);
			interCellYVec2.push_back(interCellYVec1);
		}
		interCellXDB.insert(pair<int, vector<vector<double> > >(i, interCellXVec2));
		interCellYDB.insert(pair<int, vector<vector<double> > >(i, interCellYVec2));
	}
}
/** \brief InterCellObjectHeightAndZPositionDB
 *
 * \param map<int, vector<vector<double> > > interCellXDB;
 * \param map<int, vector<vector<double> > > interCellYDB;
 * \return map<int, vector<vector<vector<double> > > > interCellObjectHeightDB;
 * \return map<int, vector<vector<vector<double> > > > interCellObjectZPositionDB;
 *
 */

 /// InterCellObjectHeightAndZPositionDB
map<int, vector<vector<vector<double> > > > interCellObjectHeightDB;
map<int, vector<vector<vector<double> > > > interCellObjectZPositionDB;

void rsMXBoundaryOutDB::InterCellObjectHeightAndZPositionDB(int sliceNum)
{  /// declare iterator;
	map<int, vector <vector<double> > >::iterator itMap;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;
	/// Height
	vector< vector <vector<double> > > objectHeightVec3;
	vector< vector<double> >           objectHeightVec2;
	vector<double>                     objectHeightVec1;
	/// ZPosition
	vector< vector <vector<double> > > objectZPositionVec3;
	vector< vector<double> >           objectZPositionVec2;
	vector<double>                     objectZPositionVec1;

	/// declare int;
	int i;
	int iRingNum;
	int cellNum;
	int sliceTempNum;
	//   ofstream fout("a.txt",ios::app);
	//   fout << "InterCellObjectHeightAndZPositionDB" << endl;

	for (i = 0, itMap = interCellXDB.begin();
		itMap != interCellXDB.end();
		i++, itMap++)
	{
		objectHeightVec3.clear();
		objectZPositionVec3.clear();
		for (iRingNum = 0, itVec2 = (*itMap).second.begin();
			itVec2 != (*itMap).second.end();
			iRingNum++, itVec2++)
		{
			objectHeightVec2.clear();
			objectZPositionVec2.clear();
			for (cellNum = 0, itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				cellNum++, itVec1++)
			{
				objectHeightVec1.clear();
				objectZPositionVec1.clear();
				int randomHeightZPosition = rand() % 200;
				for (sliceTempNum = 0;
					sliceTempNum != sliceNum;
					sliceTempNum++)
				{  /// Height;
					objectHeightVec1.push_back
					(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio);
					//               fout << "i: " << i << "  iRingNum: " << iRingNum << "  cellNum: " << cellNum
					//                    << "  sliceTempNum: " << sliceTempNum << "  Height: " << longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum]
					//                    << endl;
								   /// ZPosition;
					objectZPositionVec1.push_back
					(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
					//               fout << "i: " << i << "  iRingNum: " << iRingNum << "  cellNum: " << cellNum
					//                    << "  sliceTempNum: " << sliceTempNum << "  ZPosition: " << longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]
					//                    << endl;
				}
				objectHeightVec2.push_back(objectHeightVec1);
				objectZPositionVec2.push_back(objectZPositionVec1);
			}
			objectHeightVec3.push_back(objectHeightVec2);
			objectZPositionVec3.push_back(objectZPositionVec2);
		}
		interCellObjectHeightDB.insert
		(pair<int, vector< vector <vector<double> > > >(i, objectHeightVec3));
		interCellObjectZPositionDB.insert
		(pair<int, vector< vector <vector<double> > > >(i, objectZPositionVec3));
	}
}

void rsMXBoundaryOutDB::InitBoundaryInterDB
(	double innerTangentRingRadiusRatioTemp,
	int setInterVerticalNum,
	double variationRatio,
	int sliceNum)
{
	if (type_dicot)
	{
		InterVerticalNum(setInterVerticalNum);

		double maxRadius = boundaryMXPXRingRadiusDeliver;
		int mxNumSum = 0;
		for (int i = 0, j = mxRingNum - 1; i < mxRingNum; i++, j--)
		{
			int rIdx = boundaryRadiusDB.size() - mxNumSum - 1;
			mxNumSum += eachRingMXNum[j];
			double setInnerR = maxRadius - boundaryRadiusDB[rIdx] * 2;
			SetInnerRingRadius(setInnerR);

			CalculateInterVerticalLengthTotal(maxRadius);
			maxRadius -= setInnerR;

			InterVerticalLengthAverage();

			InterVerticalLengthDB(variationRatio);

			DicotInterRadian(boundaryRadiusDB.size() - mxNumSum, eachRingMXNum[j]);
		}
		InterVerticalLengthHalfDB();
		InterVerticalCenterRadiusDB();
		DicotInterRadianDB();
		InterParallelPerimeterDB();

		InterParallelNumDB();

		InterParallelLengthDB();
		InterParallelLengthHalfDB();

		InterParallelRadianDivideDB();

		InterCellCenterRadianDB();

		InterCellCenterRotateAngleDB();

		InterCellXYDB();

		InterCellObjectHeightAndZPositionDB(sliceNum);
	}
	else
	{
		TangentRingRadius();

		InnerRingRadius(innerTangentRingRadiusRatioTemp);

		InterVerticalNum(setInterVerticalNum);

		InterVerticalLengthTotal();

		InterVerticalLengthAverage();

		InterVerticalLengthDB(variationRatio);

		InterVerticalLengthHalfDB();

		InterVerticalCenterRadiusDB();
		
		InterRadianStartAndEndDB();
		
		InterParallelPerimeterDB();
		
		InterParallelNumDB();

		InterParallelLengthDB();
		InterParallelLengthHalfDB();

		InterParallelRadianDivideDB();

		InterCellCenterRadianDB();

		InterCellCenterRotateAngleDB();

		InterCellXYDB();

		InterCellObjectHeightAndZPositionDB(sliceNum);
	}
}


////////////////////////////////////// BoundaryUp /////////////////////////////////////////////////




/** \brief upVerticalLengthTotalDB
 *
 * \param double boundaryMXPXRingRadiusDeliver;
  * \param double innerRingRadius;
 * \param vector<double> boundaryRadiusDB;
 * \return vector<double> upVerticalLengthTotalDB;
 *
 */

vector<double> upVerticalLengthTotalDB;
void rsMXBoundaryOutDB::UpVerticalLengthTotalDB()
{
	vector<double>::iterator itVec;
	double temp;
	ofstream fout(getFolderName() + "a.txt", ios::app);
	fout << "UpVerticalLengthTotalDB" << endl;
	for (itVec = boundaryRadiusDB.begin(); itVec != boundaryRadiusDB.end(); itVec++)
	{
		temp = boundaryMXPXRingRadiusDeliver - innerRingRadius - (*itVec) * 2;
		if (type_dicot)
			temp = 0;
		upVerticalLengthTotalDB.push_back(temp);
		fout << "temp: " << temp << endl;
	}
}

/** \brief upVecticalLengthThreshold;
 *
 * \param double tangentRingRadius;
 * \param double innerRingRadius;
 * \return double upVecticalLengthThreshold;
 *
 */

double upVecticalLengthThreshold;
void rsMXBoundaryOutDB::UpVecticalLengthThreshold(double setUpVecticalLengthThresholdRatio)
{
	double temp;
	temp = (tangentRingRadius - innerRingRadius) * setUpVecticalLengthThresholdRatio;
	upVecticalLengthThreshold = temp;
}

/** \brief upVerticalNum
 *
 * \param vector<double> upVerticalLengthTotalDB;
 * \param double upVecticalLengthThreshold;
 * \return vector<double> upVerticalNum;
 *
 */

vector<double> upVerticalNum;
void rsMXBoundaryOutDB::UpVerticalNum()
{
	vector<double>::iterator itVec;
	int num;
	if (upVecticalLengthThreshold == 0)
		upVecticalLengthThreshold = 1;
	//ofstream fout("a.txt",ios::app);
	//cout << "upVerticalNum" << endl;
	for (itVec = upVerticalLengthTotalDB.begin(); itVec != upVerticalLengthTotalDB.end(); itVec++)
	{
		num = int(*itVec / upVecticalLengthThreshold + 0.5);
		if (num == 0)
		{
			num = 1;
		}
		upVerticalNum.push_back(num);
		//cout << "upVerticalNum: " << num << endl;
	}
}

/** \brief upVerticalLengthAverageDB
 *
 * \param vector<double> upVerticalLengthTotalDB;
 * \param vector<double> upVerticalNum;
 * \return vector<double> upVerticalLengthAverageDB;
 *
 */

vector<double> upVerticalLengthAverageDB;
void rsMXBoundaryOutDB::UpVerticalLengthAverageDB()
{
	vector<double>::iterator itVec;
	vector<double>::iterator itVecNum;
	double temp;
	ofstream fout(getFolderName() + "a.txt", ios::app);
	fout << "UpVerticalLengthAverageDB" << endl;
	for (itVec = upVerticalLengthTotalDB.begin(), itVecNum = upVerticalNum.begin();
		itVec != upVerticalLengthTotalDB.end();
		itVec++, itVecNum++)
	{
		temp = (*itVec) / (*itVecNum);
		upVerticalLengthAverageDB.push_back(temp);
		fout << "temp: " << temp << endl;
	}
}

/** \brief upVerticalLengthDB;
 *
 * \param
 * \param
 * \return
 *
 */
map<int, vector<double> > upVerticalLengthDB;
map<int, vector<double> > upVerticalLengthAddDB;
void rsMXBoundaryOutDB::UpVerticalLengthDB(double variationRatio)
{
	vector<double> upVerticalLength;
	vector<double> upVerticalLengthAdd;

	vector<double>::iterator itVec;
	vector<double>::iterator itVecNum;
	int i;
	for (itVec = upVerticalLengthTotalDB.begin(), itVecNum = upVerticalNum.begin(), i = 0;
		itVec != upVerticalLengthTotalDB.end();
		itVec++, itVecNum++, i++)
	{  //cout << "UpVerticalLengthDB: " << "  i: " << i << endl;
	   //cout << "upVerticalLengthTotalDB: " << *itVec << "  upVerticalNum: " << *itVecNum << endl;
		SameSumAndNumberAndRatio(
			upVerticalLength,
			upVerticalLengthAdd,
			*itVec,
			*itVecNum,
			variationRatio
		);
//		RandomRatioButSameSumAndNumber(upVerticalLength,
//			upVerticalLengthAdd,
//			*itVec,
//			*itVecNum,
//			variationRatio);
		upVerticalLengthDB.insert(pair<int, vector<double> >(i, upVerticalLength));
		upVerticalLengthAddDB.insert(pair<int, vector<double> >(i, upVerticalLengthAdd));
	}
}

/** \brief upVerticalLengthHalfDB
 *
 * \param map<int, vector<double> > upVerticalLengthDB;
 * \return map<int, vector<double> > upVerticalLengthHalfDB;
 *
 */

map<int, vector<double> > upVerticalLengthHalfDB;
void rsMXBoundaryOutDB::UpVerticalLengthHalfDB()
{
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec;
	vector<double> upVerticalLengthHalf;
	double temp;
	int i;
	ofstream fout(getFolderName() + "a.txt", ios::app);
	fout << "UpVerticalLengthHalfDB" << endl;
	for (itMap = upVerticalLengthDB.begin(), i = 0;
		itMap != upVerticalLengthDB.end();
		itMap++, i++)
	{
		upVerticalLengthHalf.clear();
		for (itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			itVec++)
		{
			temp = *itVec / 2.0;
			upVerticalLengthHalf.push_back(temp);
			fout << "temp: " << temp << endl;
		}
		upVerticalLengthHalfDB.insert(pair< int, vector<double> >(i, upVerticalLengthHalf));
	}
}

/** \brief upVerticalCenterRadiusDB
 *
 * \param map<int, vector<double> > upVerticalLengthDB;
 * \param map<int, vector<double> > upVerticalLengthAddDB;
 * \param double innerRingRadius;;

 * \return map<int, vector<double> > upVerticalCenterRadiusDB;
 *
 */

map<int, vector<double> > upVerticalCenterRadiusDB;
void rsMXBoundaryOutDB::UpVerticalCenterRadiusDB()
{
	map<int, vector<double> >::iterator itMap;
	map<int, vector<double> >::iterator itMapAdd;
	vector<double>::iterator itVec;
	vector<double>::iterator itVecAdd;

	vector<double> upVerticalCenterRadius;
	double temp;
	int i;
	ofstream fout(getFolderName() + "a.txt", ios::app);
	fout << "UpVerticalLengthHalfDB" << endl;
	for (itMap = upVerticalLengthDB.begin(), itMapAdd = upVerticalLengthAddDB.begin(), i = 0;
		itMap != upVerticalLengthDB.end();
		itMap++, itMapAdd++, i++)
	{
		upVerticalCenterRadius.clear();
		for (itVec = (*itMap).second.begin(), itVecAdd = (*itMapAdd).second.begin();
			itVec != (*itMap).second.end();
			itVec++, itVecAdd++)
		{
			temp = innerRingRadius + *itVecAdd + (*itVec) / 2.0;
			upVerticalCenterRadius.push_back(temp);
			fout << "temp: " << temp << "  upVerticalLengthAddDB: " << *itVecAdd
				<< "  upVerticalLengthDB: " << *itVec << endl;
		}
		upVerticalCenterRadiusDB.insert(pair< int, vector<double> >(i, upVerticalCenterRadius));
	}
}

/** \brief upParallelPerimeterDB
 *
 * \param vector<double> boundaryCentralRadianDB;
 * \param map<int, vector<double> > upVerticalCenterRadiusDB;
 * \return map<int, vector<double> > upParallelPerimeterDB;
 *
 */

map<int, vector<double> > upParallelPerimeterDB;
void rsMXBoundaryOutDB::UpParallelPerimeterDB()
{
	map<int, vector<double> >::iterator itMapRadius;
	vector<double>::iterator itVecRadius;
	vector<double>::iterator itVecRadian;

	vector<double> upParallelPerimeter;
	double temp;
	int i;
	int j;

	ofstream fout(getFolderName() + "a.txt", ios::app);
	fout << "UpParallelPerimeterDB" << endl;
	for (itMapRadius = upVerticalCenterRadiusDB.begin(), itVecRadian = boundaryCentralRadianDB.begin(), i = 0;
		itMapRadius != upVerticalCenterRadiusDB.end();
		itMapRadius++, itVecRadian++, i++)
	{
		upParallelPerimeter.clear();
		for (itVecRadius = (*itMapRadius).second.begin(), j = 0;
			itVecRadius != (*itMapRadius).second.end();
			itVecRadius++, j++)
		{
			temp = 2.0 * M_PI * (*itVecRadius) * ((*itVecRadian) / (2.0 * M_PI));
			upParallelPerimeter.push_back(temp);
			fout << "i: " << i << "  j: " << j << "  " << temp << endl;
		}
		upParallelPerimeterDB.insert(pair<int, vector<double> >(i, upParallelPerimeter));
	}
}

/** \brief upParallelNumDB
 *
 * \param map<int, vector<double> > upParallelPerimeterDB;
 * \param map<int, vector<double> > upVerticalLengthDB
 * \return map<int, vector<double> > upParallelNumDB;
 *
 */

map<int, vector<double> > upParallelNumDB;
void rsMXBoundaryOutDB::UpParallelNumDB()
{
	map<int, vector<double> >::iterator  itMapPerimeter;
	vector<double>::iterator itVecPerimeter;
	map<int, vector<double> >::iterator  itMapLength;
	vector<double>::iterator itVecLength;
	vector<double> upParallelNum;
	double doubleNum;
	int intNum;
	int i;
	int j;

	ofstream fout(getFolderName() + "a.txt", ios::app);
	fout << "UpParallelNumDB" << endl;
	for (itMapPerimeter = upParallelPerimeterDB.begin(), itMapLength = upVerticalLengthDB.begin(), i = 0;
		itMapPerimeter != upParallelPerimeterDB.end();
		itMapPerimeter++, itMapLength++, i++)
	{
		upParallelNum.clear();
		for (itVecPerimeter = (*itMapPerimeter).second.begin(), itVecLength = (*itMapLength).second.begin(), j = 0;
			itVecPerimeter != (*itMapPerimeter).second.end();
			itVecPerimeter++, itVecLength++, j++)
		{
			if (*itVecLength == 0)
			{
				intNum = 0;
				upParallelNum.push_back(intNum);
				fout << "i: " << i << "  j: " << j <<
					"  intNum: " << intNum << endl;
				continue;
			}
			doubleNum = *itVecPerimeter / *itVecLength;
			if (doubleNum < 1)
			{
				intNum = 1;
			}
			else
			{
				intNum = int(doubleNum + 0.5);
			}
			upParallelNum.push_back(intNum);
			fout << "i: " << i << "  j: " << j <<
				"  intNum: " << intNum << endl;
		}
		upParallelNumDB.insert(pair<int, vector<double> >(i, upParallelNum));
	}
}

/** \brief upParallelLengthDB
 *
 * \param map<int, vector<double> > upParallelPerimeterDB;
 * \param map<int, vector<double> > upParallelNumDB;
 * \return map<int, vector<double> > upParallelLengthDB;
 *
 */

map<int, vector<double> > upParallelLengthDB;
void rsMXBoundaryOutDB::UpParallelLengthDB()
{
	map<int, vector<double> >::iterator  itMapPerimeter;
	vector<double>::iterator itVecPerimeter;
	map<int, vector<double> >::iterator  itMapNum;
	vector<double>::iterator itVecNum;
	vector<double> upParallelLength;
	double temp;
	int i;
	int j;
	ofstream fout(getFolderName() + "a.txt", ios::app);
	fout << "UpParallelLengthDB" << endl;
	for (itMapPerimeter = upParallelPerimeterDB.begin(), itMapNum = upParallelNumDB.begin(), i = 0;
		itMapPerimeter != upParallelPerimeterDB.end();
		itMapPerimeter++, itMapNum++, i++)
	{
		upParallelLength.clear();
		for (itVecPerimeter = (*itMapPerimeter).second.begin(), itVecNum = (*itMapNum).second.begin(), j = 0;
			itVecPerimeter != (*itMapPerimeter).second.end();
			itVecPerimeter++, itVecNum++, j++)
		{
			temp = *itVecPerimeter / *itVecNum;
			upParallelLength.push_back(temp);
			fout << "i: " << i << "  j: " << j
				<< "  temp: " << temp << "  upParallelPerimeterDB: " << *itVecPerimeter
				<< "  upParallelNumDB: " << *itVecNum << endl;
		}
		upParallelLengthDB.insert(pair<int, vector<double> >(i, upParallelLength));
	}
}

/** \brief upParallelLengthHalfDB
 *
 * \param map<int, vector<double> > upParallelLengthDB;
 * \return map<int, vector<double> > upParallelLengthHalfDB;
 *
 */
map<int, vector<double> > upParallelLengthHalfDB;
void rsMXBoundaryOutDB::UpParallelLengthHalfDB()
{
	map<int, vector<double> >::iterator  itMap;
	vector<double>::iterator itVec;
	vector<double> upParallelLengthHalf;
	double temp;
	int i;
	int j;
	for (itMap = upParallelLengthDB.begin(), i = 0;
		itMap != upParallelLengthDB.end();
		itMap++, i++)
	{
		upParallelLengthHalf.clear();
		for (itVec = (*itMap).second.begin(), j = 0;
			itVec != (*itMap).second.end();
			itVec++, j++)
		{
			temp = *itVec / 2.0;
			upParallelLengthHalf.push_back(temp);
		}
		upParallelLengthHalfDB.insert(pair<int, vector<double> >(i, upParallelLengthHalf));
	}
}

/** \brief upParallelRadianDivideDB
 *
 * \param vector<double> boundaryCentralRadianDB;
 * \param map<int, vector<double> > upParallelNumDB;
 * \return map<int, vector<double> > upIntersectionRadianDivideDB;
 *
 */

map<int, vector<double> > upIntersectionRadianDivideDB;
void rsMXBoundaryOutDB::UpParallelRadianDivideDB()
{
	map<int, vector<double> >::iterator  itMapNum;
	vector<double>::iterator itVecNum;
	vector<double>::iterator itVecRadian;
	vector<double> upIntersectionRadianDivide;
	double temp;
	int i;
	int j;
	ofstream fout(getFolderName() + "a.txt", ios::app);
	fout << "UpParallelRadianDivideDB" << endl;
	for (itMapNum = upParallelNumDB.begin(), itVecRadian = boundaryCentralRadianDB.begin(), i = 0;
		itMapNum != upParallelNumDB.end();
		itMapNum++, itVecRadian++, i++)
	{
		upIntersectionRadianDivide.clear();
		for (itVecNum = (*itMapNum).second.begin(), j = 0;
			itVecNum != (*itMapNum).second.end();
			itVecNum++, j++)
		{
			temp = *itVecRadian / *itVecNum;
			upIntersectionRadianDivide.push_back(temp);
			fout << "i: " << i << "  j: " << j
				<< "  temp: " << temp << endl;
			fout << "upIntersectionRadianDB: " << *itVecRadian << "  upParallelNumDB: " << *itVecNum << endl;
		}
		upIntersectionRadianDivideDB.insert(pair<int, vector<double> >(i, upIntersectionRadianDivide));
	}
}

/** \brief upParallelCenterRadianDB
 *
 * \param vector<double> boundaryRadianStartDB;
 * \param map<int, vector<double> > upIntersectionRadianDivideDB;
 * \param map<int, vector<double> > upParallelNumDB;
 * \return map<int, vector<vector<double> > > upCellCenterRadianDB;
 *
 */

map<int, vector<vector<double> > > upCellCenterRadianDB;
void rsMXBoundaryOutDB::UpCellCenterRadianDB()
{
	vector<double>::iterator itVecRadianStart;
	map<int, vector<double> >::iterator  itMapNum;
	vector<double>::iterator itVecNum;
	map<int, vector<double> >::iterator  itMapRadianDivide;
	vector<double>::iterator itVecRadianDivide;

	vector<vector<double> > upCellCenterRadianVec2;
	vector<double> upCellCenterRadianVec1;
	double sum;
	double tempSum;
	double temp;
	int i;
	int j;
	int k;
	int num;
	ofstream fout(getFolderName() + "a.txt", ios::app);
	fout << "UpCellCenterRadianDB" << endl;
	for (itMapNum = upParallelNumDB.begin(), itVecRadianStart = boundaryRadianStartDB.begin(),
		itMapRadianDivide = upIntersectionRadianDivideDB.begin(), i = 0;
		itMapNum != upParallelNumDB.end();
		itMapNum++, itVecRadianStart++, itMapRadianDivide++, i++)
	{
		upCellCenterRadianVec2.clear();
		for (itVecNum = (*itMapNum).second.begin(), itVecRadianDivide = (*itMapRadianDivide).second.begin(), j = 0;
			itVecNum != (*itMapNum).second.end();
			itVecNum++, itVecRadianDivide++, j++)
		{
			upCellCenterRadianVec1.clear();
			sum = 0;
			tempSum = 0;
			for (num = 0, k = 0; num != *itVecNum; num++, k++)
			{
				if (num == 0)
				{
					tempSum = 0;
					sum = tempSum + *itVecRadianDivide / 2;
					temp = *itVecRadianStart + sum;
					upCellCenterRadianVec1.push_back(temp);
				}
				else
				{
					tempSum += *itVecRadianDivide;
					sum = tempSum + *itVecRadianDivide / 2;
					temp = *itVecRadianStart + sum;
					upCellCenterRadianVec1.push_back(temp);
				}
				fout << "i: " << i << "  j: " << j << "  k: " << k <<
					"  temp: " << temp << endl;
			}
			upCellCenterRadianVec2.push_back(upCellCenterRadianVec1);
		}
		upCellCenterRadianDB.insert(pair<int, vector<vector<double> > >(i, upCellCenterRadianVec2));
	}
}

/** \brief interParallelCenterRotateAngleDB
 *
 * \param map<int, vector<vector<double> > > upCellCenterRadianDB;
 * \return map<int, vector<vector<double> > > upCellCenterRotateAngleDB;
 *
 */

map<int, vector<vector<double> > > upCellCenterRotateAngleDB;
void rsMXBoundaryOutDB::UpCellCenterRotateAngleDB()
{
	map<int, vector<vector<double> > >::iterator  itMap;
	vector<vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;

	vector<vector<double> > upCellCenterRotateAngleVec2;
	vector<double> upCellCenterRotateAngleVec1;
	double tempAngle;
	int i;
	for (itMap = upCellCenterRadianDB.begin(), i = 0;
		itMap != upCellCenterRadianDB.end();
		itMap++, i++)
	{
		upCellCenterRotateAngleVec2.clear();
		for (itVec2 = (*itMap).second.begin();
			itVec2 != (*itMap).second.end();
			itVec2++)
		{
			upCellCenterRotateAngleVec1.clear();
			for (itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				itVec1++)
			{
				tempAngle = (-1) * (*itVec1) / M_PI * 180;
				upCellCenterRotateAngleVec1.push_back(tempAngle);
			}
			upCellCenterRotateAngleVec2.push_back(upCellCenterRotateAngleVec1);
		}
		upCellCenterRotateAngleDB.insert(pair<int, vector<vector<double> > >(i, upCellCenterRotateAngleVec2));
	}
}

/** \brief upCellXYDB
 *
 * \param map<int, vector<vector<double> > > upCellCenterRadianDB;
 * \param map<int, vector<double> > upVerticalCenterRadiusDB;
 * \return map<int, vector<vector<double> > > upCellXDB;
 * \return map<int, vector<vector<double> > > upCellYDB;
 *
 */

map<int, vector<vector<double> > > upCellXDB;
map<int, vector<vector<double> > > upCellYDB;
void rsMXBoundaryOutDB::UpCellXYDB()
{
	map<int, vector<vector<double> > >::iterator  itMap;
	vector<vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;
	map<int, vector<double> >::iterator  itMapCenterRadius;
	vector<double>::iterator itVecCenterRadius;

	vector<vector<double> > upCellXVec2;
	vector<double> upCellXVec1;
	vector<vector<double> > upCellYVec2;
	vector<double> upCellYVec1;

	double tempX;
	double tempY;
	int i;
	int j;
	int k;
	ofstream fout(getFolderName() + "a.txt", ios::app);
	fout << "UpCellXYDB" << endl;
	for (itMap = upCellCenterRadianDB.begin(), itMapCenterRadius = upVerticalCenterRadiusDB.begin(), i = 0;
		itMap != upCellCenterRadianDB.end();
		itMap++, itMapCenterRadius++, i++)
	{
		upCellXVec2.clear();
		upCellYVec2.clear();
		for (itVec2 = (*itMap).second.begin(), itVecCenterRadius = (*itMapCenterRadius).second.begin(), j = 0;
			itVec2 != (*itMap).second.end();
			itVec2++, itVecCenterRadius++, j++)
		{
			upCellXVec1.clear();
			upCellYVec1.clear();
			for (itVec1 = (*itVec2).begin(), k = 0;
				itVec1 != (*itVec2).end();
				itVec1++, k++)
			{
				tempX = (*itVecCenterRadius) * cos(*itVec1);
				tempY = (*itVecCenterRadius) * sin(*itVec1);
				upCellXVec1.push_back(tempX);
				upCellYVec1.push_back(tempY);
				fout << "i: " << i << "  j: " << j << "  k: " << k <<
					"  tempX: " << tempX << "  tempY: " << tempY
					<< "  upVerticalCenterRadiusDB: " << *itVecCenterRadius
					<< "  upCellCenterRadianDB: " << *itVec1 << endl;
			}
			upCellXVec2.push_back(upCellXVec1);
			upCellYVec2.push_back(upCellYVec1);
		}
		upCellXDB.insert(pair<int, vector<vector<double> > >(i, upCellXVec2));
		upCellYDB.insert(pair<int, vector<vector<double> > >(i, upCellYVec2));
	}
}

/** \brief upCellObjectHeightAndZPositionDB
 *
 * \param map<int, vector<vector<double> > > upCellXDB;
 * \param map<int, vector<vector<double> > > upCellYDB;
 * \return map<int, vector<vector<vector<double> > > > upCellObjectHeightDB;
 * \return map<int, vector<vector<vector<double> > > > upCellObjectZPositionDB;
 *
 */

 /// UpCellObjectHeightAndZPositionDB
map<int, vector<vector<vector<double> > > > upCellObjectHeightDB;
map<int, vector<vector<vector<double> > > > upCellObjectZPositionDB;

void rsMXBoundaryOutDB::UpCellObjectHeightAndZPositionDB(int sliceNum)
{  /// declare iterator;
	map<int, vector <vector<double> > >::iterator itMap;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;
	/// Height
	vector< vector <vector<double> > > objectHeightVec3;
	vector< vector<double> >           objectHeightVec2;
	vector<double>                     objectHeightVec1;
	/// ZPosition
	vector< vector <vector<double> > > objectZPositionVec3;
	vector< vector<double> >           objectZPositionVec2;
	vector<double>                     objectZPositionVec1;

	/// declare int;
	int i;
	int iRingNum;
	int cellNum;
	int sliceTempNum;
	ofstream fout(getFolderName() + "a.txt", ios::app);
	fout << "UpCellObjectHeightAndZPositionDB" << endl;

	for (i = 0, itMap = upCellXDB.begin();
		itMap != upCellXDB.end();
		i++, itMap++)
	{
		objectHeightVec3.clear();
		objectZPositionVec3.clear();
		for (iRingNum = 0, itVec2 = (*itMap).second.begin();
			itVec2 != (*itMap).second.end();
			iRingNum++, itVec2++)
		{
			objectHeightVec2.clear();
			objectZPositionVec2.clear();
			for (cellNum = 0, itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				cellNum++, itVec1++)
			{
				objectHeightVec1.clear();
				objectZPositionVec1.clear();
				int randomHeightZPosition = rand() % 200;
				for (sliceTempNum = 0;
					sliceTempNum != sliceNum;
					sliceTempNum++)
				{  /// Height;
					objectHeightVec1.push_back
					(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio);
					fout << "i: " << i << "  iRingNum: " << iRingNum << "  cellNum: " << cellNum
						<< "  sliceTempNum: " << sliceTempNum << "  Height: " << longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum]
						<< endl;
					/// ZPosition;
					objectZPositionVec1.push_back
					(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
					fout << "i: " << i << "  iRingNum: " << iRingNum << "  cellNum: " << cellNum
						<< "  sliceTempNum: " << sliceTempNum << "  ZPosition: " << longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]
						<< endl;
				}
				objectHeightVec2.push_back(objectHeightVec1);
				objectZPositionVec2.push_back(objectZPositionVec1);
			}
			objectHeightVec3.push_back(objectHeightVec2);
			objectZPositionVec3.push_back(objectZPositionVec2);
		}
		upCellObjectHeightDB.insert
		(pair<int, vector< vector <vector<double> > > >(i, objectHeightVec3));
		upCellObjectZPositionDB.insert
		(pair<int, vector< vector <vector<double> > > >(i, objectZPositionVec3));
	}
}

void rsMXBoundaryOutDB::InitBoundaryUpDB
(
	double setUpVecticalLengthThresholdRatio,
	double variationRatio,
	int sliceNum)
{
	UpVerticalLengthTotalDB();

	UpVecticalLengthThreshold(setUpVecticalLengthThresholdRatio);

	UpVerticalNum();

	UpVerticalLengthDB(variationRatio);

	UpVerticalLengthHalfDB();

	UpVerticalCenterRadiusDB();

	UpParallelPerimeterDB();

	UpParallelNumDB();

	UpParallelLengthDB();

	UpParallelLengthHalfDB();

	UpParallelRadianDivideDB();

	UpCellCenterRadianDB();

	UpCellCenterRotateAngleDB();

	UpCellXYDB();

	UpCellObjectHeightAndZPositionDB(sliceNum);
}