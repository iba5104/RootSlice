#include "rsMXCoreDB.h"

/////////////////////////////////////////////
/*************************************************
/// Calculate xylemOutRingAddRadiusDB and xylemOutRingCellNumDB;
//Need to initialize:
eachRingRadius;
//Get:
map<int, vector<double> > xylemOutRingAddRadiusDB;
map<int, vector<int> >    xylemOutRingCellNumDB;
**************************************************/
void rsMXCoreDB::XylemOutRingDB
(double xylemMaxOutRingNum,
	double xylemMaxOutRingCellNum,
	double xylemMaxOutRingAddRadius)
{
	vector<double>::iterator it;
	vector<double> xylemOutRingAddRadius;
	vector<int> xylemOutRingCellNum;
	double xylemOutRingNum;

	double factorAddRaius = 0.6;
	int i;
	int temp;
	int minus;

	//cout << endl;

	for (it = eachRingRadius.begin(), i = 0;
		it != eachRingRadius.end();
		it++, i++)
	{
		xylemOutRingAddRadius.clear();
		xylemOutRingCellNum.clear();
		/// according to eachRingRadius to set the ringNum of mx;
		//cout << "XylemOutRingDB: " << i << endl;
		if (*it <= mxAverageRingRadius)
		{
			xylemOutRingNum = xylemMaxOutRingNum - 1;
			{  for (temp = 0, minus = xylemOutRingNum; temp != xylemOutRingNum; temp++, minus--)
			{
				if (temp == xylemOutRingNum - 1)
				{
					xylemOutRingAddRadius.push_back(xylemMaxOutRingAddRadius);
					xylemOutRingCellNum.push_back(round(xylemMaxOutRingCellNum));
					//cout << round(xylemMaxOutRingCellNum) << endl;
				}
				else
				{
					xylemOutRingAddRadius.push_back(xylemMaxOutRingAddRadius / (minus * factorAddRaius));
					xylemOutRingCellNum.push_back(round(xylemMaxOutRingCellNum));
					//cout << round(xylemMaxOutRingCellNum) << endl;
				}
				//cout << xylemOutRingAddRadius[temp] << endl;
			}
			}
		}
		else
		{
			xylemOutRingNum = xylemMaxOutRingNum;
			{  for (temp = 0, minus = xylemOutRingNum; temp != xylemOutRingNum; temp++, minus--)
			{
				if (temp == xylemOutRingNum - 1)
				{
					xylemOutRingAddRadius.push_back(xylemMaxOutRingAddRadius);
					xylemOutRingCellNum.push_back(round(xylemMaxOutRingCellNum));
					//cout << round(xylemMaxOutRingCellNum) << endl;
				}
				else
				{
					xylemOutRingAddRadius.push_back(xylemMaxOutRingAddRadius / (minus * factorAddRaius));
					xylemOutRingCellNum.push_back(round(xylemMaxOutRingCellNum));
					//cout << round(xylemMaxOutRingCellNum) << endl;
				}
				//cout << xylemOutRingAddRadius[temp] << endl;
			}
			}
		}
		xylemOutRingAddRadiusDB.insert(pair<int, vector<double> >(i, xylemOutRingAddRadius));
		xylemOutRingCellNumDB.insert(pair<int, vector<int> >(i, xylemOutRingCellNum));

	}
}

/** Get mxBoundaryRadiusDB;
 *
 * \param map<int, double> xylemOutRingAddRadiusDB;
 * \param vector<double> eachRingRadius;
 * \return vector<double> mxBoundaryRadius;
 *
 */

void rsMXCoreDB::BoundaryRadiusDB()
{
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec;
	double sum;
	double tempSum;
	int i;
	ofstream fout(getFolderName() + "a.txt", ios::app);
	for (itMap = xylemOutRingAddRadiusDB.begin(), sum = 0, i = 0;
		itMap != xylemOutRingAddRadiusDB.end();
		itMap++, i++)
	{
		for (itVec = (*itMap).second.begin(), tempSum = 0;
			itVec != (*itMap).second.end();
			itVec++)
		{
			tempSum += *itVec;
		}
		sum = tempSum + eachRingRadius[i];
		boundaryRadiusDB.push_back(sum);
		fout << "mxBoundaryRadiusDB: " << sum << endl;
	}
}

/** Get mxMaxBoundaryRadius;
 *
 * \param map<int, double> xylemOutRingAddRadiusDB;
 * \param vector<double> eachRingRadius;
 * \return double mxMaxBoundaryRadius;
 *
 */

void rsMXCoreDB::MXMaxBoundaryRadius()
{
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec;
	double max = 0;
	double sum;
	double tempSum;
	int i;
	for (itMap = xylemOutRingAddRadiusDB.begin(), sum = 0, i = 0;
		itMap != xylemOutRingAddRadiusDB.end();
		itMap++, i++)
	{
		for (itVec = (*itMap).second.begin(), tempSum = 0;
			itVec != (*itMap).second.end();
			itVec++)
		{
			tempSum += *itVec;
		}
		sum = tempSum + eachRingRadius[i];
		if (max < sum)
		{
			max = sum;
		}
	}
	ofstream fout(getFolderName() + "a.txt", ios::app);
	mxMaxBoundaryRadius = max;
	fout << "mxMaxBoundaryRadius: " << mxMaxBoundaryRadius << endl;
}


/** Get centerXYRadiusDB;
 *
 * \param map<int, double> xylemOutRingAddRadiusDB;
 * \param vector<double> eachRingRadius;
 * \return vector<double> centerXYRadiusDB;
 *
 */

void rsMXCoreDB::CenterXYRadiusDB()
{
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec;
	double tempSum;
	double temp;
	int i;
	ofstream fout(getFolderName() + "a.txt", ios::app);
	for (itMap = xylemOutRingAddRadiusDB.begin(), temp = 0, i = 0;
		itMap != xylemOutRingAddRadiusDB.end();
		itMap++, i++)
	{
		for (itVec = (*itMap).second.begin(), tempSum = 0;
			itVec != (*itMap).second.end();
			itVec++)
		{
			tempSum += *itVec;
		}
		temp = boundaryMXPXRingRadiusDeliver - tempSum - eachRingRadius[i];
		centerXYRadiusDB.push_back(temp);
		fout << "centerXYRadiusDB: " << i << "  " << temp << endl;
	}
}

/** Get CenterXYPosition;
 *
 * \param vector<double> centerXYRadiusDB;
 * \param vector<double> centerRingRotateRadian;
 * \return vector<double> centerX;
 * \return vector<double> centerY;
 *
 */

void rsMXCoreDB::CenterXYPosition()
{
	ofstream fout(getFolderName() + "a.txt", ios::app);
	for (int i = 0; i < mxNum; i++)
	{
		centerX.push_back(centerXYRadiusDB[i] * cos(centerRingRotateRadian[i]));
		centerY.push_back(centerXYRadiusDB[i] * sin(centerRingRotateRadian[i]));
		fout << "centerX: " << i << "  " << centerXYRadiusDB[i] * cos(centerRingRotateRadian[i]) << endl;
		fout << "centerY: " << i << "  " << centerXYRadiusDB[i] * sin(centerRingRotateRadian[i]) << endl;
	}
}


/********************************************************
// Calculate xylemOutRingAppendAddRadiusDB;
//Need to initialize:
map<int, vector<double> > xylemOutRingAddRadiusDB
//Get:
map<int, vector<double> > xylemOutRingAppendAddRadiusDB;
*********************************************************/
void rsMXCoreDB::XylemOutRingAppendAddRadiusDB()
{
	map<int, vector<double> >::iterator itMapDouble;
	vector<double>::iterator itVecDouble;
	vector<double> xylemOutRingAppendAddRadius;
	double temp = 0;
	int i;
	int iAppend;
	for (itMapDouble = xylemOutRingAddRadiusDB.begin(), i = 0;
		itMapDouble != xylemOutRingAddRadiusDB.end();
		itMapDouble++, i++)
	{
		xylemOutRingAppendAddRadius.clear();
		temp = 0;
		for (itVecDouble = (*itMapDouble).second.begin(), iAppend = 0;
			itVecDouble != (*itMapDouble).second.end();
			itVecDouble++, iAppend++)
		{
			xylemOutRingAppendAddRadius.push_back(temp);
			temp += *itVecDouble;
		}
		xylemOutRingAppendAddRadiusDB.insert(pair<int, vector<double> >(i, xylemOutRingAppendAddRadius));
		//cout << "XylemOutRingAppendAddRadiusDB: " << i << endl;
	}
}

/******************************************************
// Create xylemOutRingCircleRadiusDB for each xylem;
//Need to initialize:
vector<double> eachRingRadius;
map<int, vector<double> > xylemOutRingAppendAddRadiusDB;
map<int, vector<double> > xylemOutRingAddRadiusDB;
map<int, vector<int> >    xylemOutRingCellNumDB;

*******************************************************/
void rsMXCoreDB::XylemOutRingCircleRadiusDB()
{
	int i;
	int iRingNum;
	/// declare iterator;
	map<int, vector<double> >::iterator itMapAdd;
	map<int, vector<int> >::iterator itMapCellNum;
	vector<double>::iterator itVecDouble;
	vector<int>::iterator itVecInt;

	vector<double> xylemOutRingCircleRadius;

	for (i = 0, itMapAdd = xylemOutRingAppendAddRadiusDB.begin(), itMapCellNum = xylemOutRingCellNumDB.begin();
		itMapAdd != xylemOutRingAppendAddRadiusDB.end();
		itMapAdd++, i++, itMapCellNum++)
	{
		xylemOutRingCircleRadius.clear();
		for (itVecDouble = (*itMapAdd).second.begin(), iRingNum = 0;
			itVecDouble != (*itMapAdd).second.end();
			itVecDouble++, iRingNum++)
		{
			xylemOutRingCircleRadius.push_back(CircleRadius
			(eachRingRadius[i],
				*itVecDouble,
				xylemOutRingAddRadiusDB[i][iRingNum]));
		}
		xylemOutRingCircleRadiusDB.insert(pair<int, vector<double> >(i, xylemOutRingCircleRadius));
		//cout << "XylemOutRingCircleRadiusDB: " << i << endl;
	}

}

/******************************************************
// Create XylemOutRingObjectVerticalDB;
*******************************************************/
void rsMXCoreDB::XylemOutRingObjectVerticalDB()
{  /// declare iterator;
	int i;
	map<int, vector<double> >::iterator itMapAdd;
	vector<double>::iterator itVecDouble;
	vector<double> xylemOutRingObjectVertical;

	for (itMapAdd = xylemOutRingAddRadiusDB.begin(), i = 0;
		itMapAdd != xylemOutRingAddRadiusDB.end();
		itMapAdd++, i++)
	{
		xylemOutRingObjectVertical.clear();
		for (itVecDouble = (*itMapAdd).second.begin();
			itVecDouble != (*itMapAdd).second.end();
			itVecDouble++)
		{
			xylemOutRingObjectVertical.push_back(ObjectVertical(*itVecDouble) / objectXYZRadiusRatio);
		}
		xylemOutRingObjectVerticalDB.insert(pair<int, vector<double> >(i, xylemOutRingObjectVertical));
		//cout << "XylemOutRingObjectVerticalDB: " << i << endl;
	}
}


/******************************************************
// Create RandomHeightDB;
*******************************************************/
void rsMXCoreDB::RandomHeightDB(double totalHeight, int sliceNum, double initZPosition, int VectorNum)
{
	int temp;
	longitudeSegmentHeightDB.clear();
	longitudeZPositionAddDB.clear();
	for (temp = 0;
		temp != VectorNum;
		temp++)
	{  //srand ( time(NULL) );
		RandomHeight(totalHeight, sliceNum, initZPosition);
		longitudeSegmentHeightDB.insert(pair<int, vector<double> >(temp, longitudeSegmentHeight));
		longitudeZPositionAddDB.insert(pair<int, vector<double> >(temp, longitudeZPositionAdd));
	}
}

/******************************************************
// GetRandomCircleSegmentAndCircleXYNonuniformDB
*******************************************************/
void rsMXCoreDB::XylemOutRingCircleSegmentAndCircleXYDB(double variationRatio)
{
	int i;
	int iRingNum;
	/// declare iterator;
	map<int, vector<double> >::iterator itMapAdd;
	map<int, vector<int> >::iterator itMapCellNum;
	vector<double>::iterator itVecDouble;
	vector<int>::iterator itVecInt;

	vector< vector<double> > xylemOutRingCircleSegmentLength;
	vector<double> xylemOutRingCircleSegmentLengthSum;

	vector< vector<double> > xylemOutRingCircleX;
	vector< vector<double> > xylemOutRingCircleY;
	vector< vector<double> > xylemOutRingCircleSegmentRotateAngle;


	for (i = 0, itMapAdd = xylemOutRingAppendAddRadiusDB.begin(), itMapCellNum = xylemOutRingCellNumDB.begin();
		itMapAdd != xylemOutRingAppendAddRadiusDB.end();
		itMapAdd++, i++, itMapCellNum++)
	{
		xylemOutRingCircleSegmentLength.clear();
		xylemOutRingCircleSegmentLengthSum.clear();

		xylemOutRingCircleX.clear();
		xylemOutRingCircleY.clear();
		xylemOutRingCircleSegmentRotateAngle.clear();

		for (itVecDouble = (*itMapAdd).second.begin(), itVecInt = (*itMapCellNum).second.begin(), iRingNum = 0;
			itVecDouble != (*itMapAdd).second.end(), itVecInt != (*itMapCellNum).second.end();
			itVecDouble++, itVecInt++, iRingNum++)
		{
			CirclePerimeter(xylemOutRingCircleRadiusDB[i][iRingNum]);
			RandomRatioButSameSumAndNumber(circleSegmentLength,
				circleSegmentLengthAdd,
				circleSegmentLengthSum,
				circlePerimeter,
				*itVecInt,
				variationRatio);
			xylemOutRingCircleSegmentLength.push_back(circleSegmentLength);
			xylemOutRingCircleSegmentLengthSum.push_back(circleSegmentLengthSum);

			CircleXYNonuniform(*itVecInt, xylemOutRingCircleRadiusDB[i][iRingNum]);
			xylemOutRingCircleX.push_back(circleX);
			xylemOutRingCircleY.push_back(circleY);
			xylemOutRingCircleSegmentRotateAngle.push_back(circleSegmentRotateAngle);
		}
		xylemOutRingCircleSegmentLengthDB.insert
		(pair<int, vector<vector<double> > >(i, xylemOutRingCircleSegmentLength));

		xylemOutRingCircleSegmentLengthSumDB.insert
		(pair<int, vector<double> >(i, xylemOutRingCircleSegmentLengthSum));

		xylemOutRingCircleXDB.insert
		(pair<int, vector<vector<double> > >(i, xylemOutRingCircleX));

		xylemOutRingCircleYDB.insert
		(pair<int, vector<vector<double> > >(i, xylemOutRingCircleY));

		xylemOutRingCircleSegmentRotateAngleDB.insert
		(pair<int, vector<vector<double> > >(i, xylemOutRingCircleSegmentRotateAngle));

		//cout << "XylemOutRingCircleSegmentAndCircleXYDB: " << i << endl;
	}
}

/******************************************
Add centerX and centerY to XylemOutRing;
*******************************************/

void rsMXCoreDB::XylemOutRingAddCenterXY()
{  /// declare iterator;
	map<int, vector< vector<double> > >::iterator itMap;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;
	/// declare int;
	int i;
	int iRingNum;
	int cellNum;
	/// cout << circleSegmentLengthDB;
	for (itMap = xylemOutRingCircleXDB.begin(), i = 0;
		itMap != xylemOutRingCircleXDB.end();
		itMap++, i++)
	{
		for (itVec2 = (*itMap).second.begin(), iRingNum = 0;
			itVec2 != (*itMap).second.end();
			itVec2++, iRingNum++)
		{
			for (itVec1 = (*itVec2).begin(), cellNum = 0;
				itVec1 != (*itVec2).end();
				itVec1++, cellNum++)
			{
				*itVec1 += centerX[i];
				xylemOutRingCircleYDB[i][iRingNum][cellNum] += centerY[i];
			}
		}
	}
}

/******************************************************
// Get new xylemOutRingCircleSegmentLengthDB after adjustment of ratio;
*******************************************************/
void rsMXCoreDB::XylemOutRingCircleSegmentLengthAdjustRatioDB()
{
	map<int, vector <vector<double> > >::iterator itMap;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;

	for (itMap = xylemOutRingCircleSegmentLengthDB.begin();
		itMap != xylemOutRingCircleSegmentLengthDB.end();
		itMap++)
	{
		for (itVec2 = (*itMap).second.begin(); itVec2 != (*itMap).second.end(); itVec2++)
		{
			for (itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				itVec1++)
			{
				*itVec1 = (*itVec1) / 2 / objectXYZRadiusRatio;
			}
		}
	}
}

/*******************************************
to get ObjectHeightDB and ObjectZPositionDB;
********************************************/
/** need to initialize:
"longitudeSegmentHeightDB"
"longitudeZPositionAddDB"
**/

void rsMXCoreDB::XylemOutRingObjectHeightAndZPositionDB(int sliceNum)
{  /// declare iterator;
	map<int, vector <vector<double> > >::iterator itMap;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;

	vector< vector <vector<double> > > objectHeightVec3;
	vector< vector<double> >           objectHeightVec2;
	vector<double>                     objectHeightVec1;

	vector< vector <vector<double> > > objectZPositionVec3;
	vector< vector<double> >           objectZPositionVec2;
	vector<double>                     objectZPositionVec1;
	/// declare int;

	int i;
	int iRingNum;
	int cellNum;
	int sliceTempNum;
	/// cout << circleSegmentLengthDB;
	for (i = 0, itMap = xylemOutRingCircleXDB.begin();
		itMap != xylemOutRingCircleXDB.end();
		i++, itMap++)
	{  //cout << "i: " << i <<endl;
		objectHeightVec3.clear();
		objectZPositionVec3.clear();
		for (iRingNum = 0, itVec2 = (*itMap).second.begin();
			itVec2 != (*itMap).second.end();
			iRingNum++, itVec2++)
		{  //cout << "iRingNum: " << iRingNum <<endl;
			objectHeightVec2.clear();
			objectZPositionVec2.clear();
			for (cellNum = 0, itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				cellNum++, itVec1++)
			{  //cout << "cellNum: " << cellNum <<endl;
				int randomHeightZPosition = rand() % 200;
				objectHeightVec1.clear();
				objectZPositionVec1.clear();
				for (sliceTempNum = 0;
					sliceTempNum != sliceNum;
					sliceTempNum++)
				{
					objectHeightVec1.push_back
					(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio);
					//cout << "objectHeightVec1: " << longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio << endl;

					objectZPositionVec1.push_back
					(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
					//cout << "objectZPositionVec1: " << longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum] << endl;
				}
				objectHeightVec2.push_back(objectHeightVec1);
				objectZPositionVec2.push_back(objectZPositionVec1);
			}
			objectHeightVec3.push_back(objectHeightVec2);
			objectZPositionVec3.push_back(objectZPositionVec2);
		}
		xylemOutRingObjectHeightDB.insert(pair<int, vector< vector <vector<double> > > >(i, objectHeightVec3));
		xylemOutRingObjectZPositionDB.insert(pair<int, vector< vector <vector<double> > > >(i, objectZPositionVec3));
	}
}

/*******************************************
to get ObjectHeightDB and ObjectZPositionDB of Xylem Center Ring;
********************************************/
/** need to initialize:
"longitudeSegmentHeightDB"
"longitudeZPositionAddDB"
**/
void rsMXCoreDB::XylemCenterRingObjectHeightAndZPositionDB(int sliceNum)
{  /// declare iterator;
	vector<double>::iterator itVec;

	vector<double>                     objectHeightVec1;
	vector<double>                     objectZPositionVec1;
	/// declare int;

	int i;
	int sliceTempNum;
	/// cout << circleSegmentLengthDB;
	for (i = 0, itVec = centerX.begin();
		itVec != centerX.end();
		i++, itVec++)
	{
		int randomHeightZPosition = rand() % 200;
		objectHeightVec1.clear();
		objectZPositionVec1.clear();
		for (sliceTempNum = 0;
			sliceTempNum != sliceNum;
			sliceTempNum++)
		{
			objectHeightVec1.push_back
			(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / objectXYZRadiusRatio);
			//cout << "objectHeightVec1: " << longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio << endl;

			objectZPositionVec1.push_back
			(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
			//cout << "objectZPositionVec1: " << longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum] << endl;
		}
		xylemCenterRingObjectHeightDB.insert(pair<int, vector<double> >(i, objectHeightVec1));
		xylemCenterRingObjectZPositionDB.insert(pair<int, vector<double> >(i, objectZPositionVec1));
	}
}

/*******************************************
Initialize other Database;
********************************************/
void rsMXCoreDB::InitXylemOutRing
(rsPXCoreDB* RsPXCoreDB,
	int setMXNum,
	double setMXAverageRingRadius,
	double variationRatio,
	double xylemMaxOutRingNum,
	double xylemMaxOutRingCellNum,
	double xylemMaxOutRingAddRadius,
	int setUResolution,
	int setVResolution,
	int setWResolution,
	int sliceNum)
{
	SetObjectXYZRadiusRatio();
	SetObjectOpacity();
	/*************************
	To get:
	vector<double> eachRingRadius;
	vector<double> eachRingRadiusAdd;
	double eachRingRadiusSum;
	**************************/
	BoundaryMXPXRingRadiusDeliver(RsPXCoreDB);
	MXNum(setMXNum);
	MXAverageRingRadius(setMXAverageRingRadius);

	RandomRadius(variationRatio);
	CenterXYRotate();

	XylemOutRingDB(xylemMaxOutRingNum,
		xylemMaxOutRingCellNum,
		xylemMaxOutRingAddRadius);
	BoundaryRadiusDB();
	MXMaxBoundaryRadius();
	CenterXYRadiusDB();
	CenterXYPosition();

	/// initialize xylemOutRingAppendAddRadiusDB and xylemOutRingCircleRadiusDB
	/// before impletement XylemOutRingCircleSegmentAndCircleXYDB;
	XylemOutRingAppendAddRadiusDB();
	XylemOutRingCircleRadiusDB();

	XylemOutRingObjectVerticalDB();

	XylemOutRingCircleSegmentAndCircleXYDB(variationRatio);

	XylemOutRingAddCenterXY();

	XylemOutRingCircleSegmentLengthAdjustRatioDB();
	XylemOutRingObjectHeightAndZPositionDB(sliceNum);
	XylemCenterRingObjectHeightAndZPositionDB(sliceNum);
	MapRGB();
	SetSuperEllipsoidResolution(setUResolution, setVResolution, setWResolution);
}