#include "rsPXCoreDB.h"

/////////////////////////////////// Nearly same as mxDB ///////////////////////////////////

/** Calculate xylemOutRingAddRadiusDB and xylemOutRingCellNumDB;
 *
 * \param vector<double> eachRingRadius;
 * \param
 * \return map<int, vector<double> > xylemOutRingAddRadiusDB;
 * \return map<int, vector<int> >    xylemOutRingCellNumDB;
 *
 */
void rsPXCoreDB::XylemOutRingDB
(double xylemMaxOutRingCellNum,
	double xylemMaxOutRingAddRadius)
{
	vector<double>::iterator it;
	double xylemOutRingAddRadius;
	int xylemOutRingCellNum;
	int i;

	//cout << endl;
	//ofstream fout("a.txt",ios::app);
	for (it = eachRingRadius.begin(), i = 0;
		it != eachRingRadius.end();
		it++, i++)
	{  /// according to eachRingRadius to set the ringNum of mx;
	   //cout << "XylemOutRingDB: " << i << endl;
		if (*it <= pxAverageRingRadius)
		{
			xylemOutRingAddRadius = xylemMaxOutRingAddRadius * 0.8;
			xylemOutRingCellNum = round(xylemMaxOutRingCellNum * 0.8);
			//     fout <<"xylemOutRingCellNum: " << i << ": "<< xylemOutRingCellNum << endl;
		}
		else
		{
			xylemOutRingAddRadius = xylemMaxOutRingAddRadius;
			xylemOutRingCellNum = xylemMaxOutRingCellNum;
			//    fout <<"xylemOutRingCellNum: " << i << ": "<< xylemOutRingCellNum << endl;
		}
		xylemOutRingAddRadiusDB.insert(pair<int, double >(i, xylemOutRingAddRadius));
		xylemOutRingCellNumDB.insert(pair<int, int >(i, xylemOutRingCellNum));
	}
	ofstream fout("a.txt", ios::app);
	map<int, double>::iterator itMap;
	for (itMap = xylemOutRingAddRadiusDB.begin(); itMap != xylemOutRingAddRadiusDB.end(); itMap++)
	{
		fout << "xylemOutRingAddRadiusDB - PX: " << (*itMap).second << endl;
	}
}

/** Get pxMaxBoundaryRadius;
 *
 * \param map<int, double> xylemOutRingAddRadiusDB;
 * \param vector<double> eachRingRadius;
 * \return double pxMaxBoundaryRadius;
 *
 */

void rsPXCoreDB::PXMaxBoundaryRadius()
{
	vector<double>::iterator itVec;
	map<int, double>::iterator itMap;
	double max = 0;
	double temp;
	for (itMap = xylemOutRingAddRadiusDB.begin(), itVec = eachRingRadius.begin(), temp = 0;
		itMap != xylemOutRingAddRadiusDB.end();
		itMap++, itVec++)
	{
		temp = (*itMap).second + *itVec;
		if (max < temp)
		{
			max = temp;
		}
	}
	pxMaxBoundaryRadius = max;

	ofstream fout("a.txt", ios::app);
	fout << "pxMaxBoundaryRadius: " << pxMaxBoundaryRadius << endl;
}

/** Get mxBoundaryRingRadius
 *
 * \param double pxBoundaryRingRadius;
 * \param double pxMaxBoundaryRadius
 * \return double mxBoundaryRingRadius;
 *
 */

double rsPXCoreDB::BoundaryMXPXRingRadius()
{
	boundaryMXPXRingRadius = pxBoundaryRingRadius - pxMaxBoundaryRadius * 2;

	ofstream fout("a.txt", ios::app);
	fout << "boundaryMXPXRingRadius: " << boundaryMXPXRingRadius << endl;

	return boundaryMXPXRingRadius;
}

/** Get centerXYRadiusDB;
 *
 * \param map<int, double> xylemOutRingAddRadiusDB;
 * \param vector<double> eachRingRadius;
 * \param  mxBoundaryRingRadius;
 * \return vector<double> centerXYRadiusDB;
 *
 */

void rsPXCoreDB::CenterXYRadiusDB()
{
	vector<double>::iterator itVec;
	map<int, double>::iterator itMap;
	double temp;
	int i;
	ofstream fout("a.txt", ios::app);
	for (itMap = xylemOutRingAddRadiusDB.begin(), itVec = eachRingRadius.begin(), temp = 0, i = 0;
		itMap != xylemOutRingAddRadiusDB.end();
		itMap++, itVec++, i++)
	{
		temp = boundaryMXPXRingRadius + (*itMap).second + *itVec;
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

void rsPXCoreDB::CenterXYPosition()
{
	ofstream fout("a.txt", ios::app);
	for (int i = 0; i < pxNum; i++)
	{
		centerX.push_back(centerXYRadiusDB[i] * cos(centerRingRotateRadian[i]));
		centerY.push_back(centerXYRadiusDB[i] * sin(centerRingRotateRadian[i]));
		fout << "centerX: " << i << "  " << centerXYRadiusDB[i] * cos(centerRingRotateRadian[i]) << endl;
		fout << "centerY: " << i << "  " << centerXYRadiusDB[i] * sin(centerRingRotateRadian[i]) << endl;
	}
}

/** Create xylemOutRingCircleRadiusDB for each xylem;
 *
 * \param vector<double> eachRingRadius;
 * \param map<int, double > xylemOutRingAddRadiusDB;
 * \return map<int, double> xylemOutRingCircleRadiusDB;
 *
 */

void rsPXCoreDB::XylemOutRingCircleRadiusDB()
{
	int i;
	/// declare iterator;
	map<int, double>::iterator itMap;
	double xylemOutRingCircleRadius;

	for (i = 0, itMap = xylemOutRingAddRadiusDB.begin();
		itMap != xylemOutRingAddRadiusDB.end();
		itMap++, i++)
	{
		xylemOutRingCircleRadius = this->CircleRadius
		(eachRingRadius[i],
			0,
			(*itMap).second);
		xylemOutRingCircleRadiusDB.insert(pair<int, double>(i, xylemOutRingCircleRadius));
		//cout << "XylemOutRingCircleRadiusDB: " << i << endl;
	}
}

/******************************************************
// Create XylemOutRingObjectVerticalDB;
*******************************************************/

void rsPXCoreDB::XylemOutRingObjectVerticalDB()
{  /// declare iterator;
	int i;
	map<int, double>::iterator itMap;
	double xylemOutRingObjectVertical;

	for (itMap = xylemOutRingAddRadiusDB.begin(), i = 0;
		itMap != xylemOutRingAddRadiusDB.end();
		itMap++, i++)
	{
		xylemOutRingObjectVertical = ObjectVertical((*itMap).second) / objectXYZRadiusRatio;
		xylemOutRingObjectVerticalDB.insert(pair<int, double>(i, xylemOutRingObjectVertical));
		//cout << "XylemOutRingObjectVerticalDB: " << i << endl;
	}
}


/******************************************************
// Create RandomHeightDB;
*******************************************************/

void rsPXCoreDB::RandomHeightDB(double totalHeight, int sliceNum, double initZPosition, int VectorNum)
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

void rsPXCoreDB::XylemOutRingCircleSegmentAndCircleXYDB(double variationRatio)
{
	int i;
	/// declare iterator;
	map<int, double>::iterator itMapAdd;
	map<int, int>::iterator itMapCellNum;

	vector<double> xylemOutRingCircleSegmentLength;
	double xylemOutRingCircleSegmentLengthSum;

	vector<double> xylemOutRingCircleX;
	vector<double> xylemOutRingCircleY;
	vector<double> xylemOutRingCircleSegmentRotateAngle;

	for (i = 0, itMapAdd = xylemOutRingAddRadiusDB.begin(), itMapCellNum = xylemOutRingCellNumDB.begin();
		itMapAdd != xylemOutRingAddRadiusDB.end();
		itMapAdd++, i++, itMapCellNum++)
	{
		CirclePerimeter(xylemOutRingCircleRadiusDB[i]);
		RandomRatioButSameSumAndNumber(circleSegmentLength,
			circleSegmentLengthAdd,
			circleSegmentLengthSum,
			circlePerimeter,
			(*itMapCellNum).second,
			variationRatio);
		xylemOutRingCircleSegmentLength = circleSegmentLength;
		xylemOutRingCircleSegmentLengthSum = circleSegmentLengthSum;

		CircleXYNonuniform((*itMapCellNum).second, xylemOutRingCircleRadiusDB[i]);
		xylemOutRingCircleX = circleX;
		xylemOutRingCircleY = circleY;
		xylemOutRingCircleSegmentRotateAngle = circleSegmentRotateAngle;

		xylemOutRingCircleSegmentLengthDB.insert
		(pair<int, vector<double> >(i, xylemOutRingCircleSegmentLength));

		xylemOutRingCircleSegmentLengthSumDB.insert
		(pair<int, double>(i, xylemOutRingCircleSegmentLengthSum));

		xylemOutRingCircleXDB.insert
		(pair<int, vector<double> >(i, xylemOutRingCircleX));

		xylemOutRingCircleYDB.insert
		(pair<int, vector<double> >(i, xylemOutRingCircleY));

		xylemOutRingCircleSegmentRotateAngleDB.insert
		(pair<int, vector<double> >(i, xylemOutRingCircleSegmentRotateAngle));

		//cout << "XylemOutRingCircleSegmentAndCircleXYDB: " << i << endl;

	}
}

/** Add centerX and centerY to pxOutRing;
 *
 * \param map<int, vector<double> > xylemOutRingCircleXDB;
 * \param map<int, vector<double> > xylemOutRingCircleYDB;
 * \return map<int, vector<double> > xylemOutRingCircleXDB;
 * \return map<int, vector<double> > xylemOutRingCircleYDB;
 *
 */

void rsPXCoreDB::XylemOutRingAddCenterXY()
{  /// declare iterator;
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec;
	/// declare int;
	int i;
	int cellNum;
	/// cout << circleSegmentLengthDB;
	for (itMap = xylemOutRingCircleXDB.begin(), i = 0;
		itMap != xylemOutRingCircleXDB.end();
		itMap++, i++)
	{
		for (itVec = (*itMap).second.begin(), cellNum = 0;
			itVec != (*itMap).second.end();
			itVec++, cellNum++)
		{
			*itVec += centerX[i];
			xylemOutRingCircleYDB[i][cellNum] += centerY[i];
		}
	}
}

/** Get new xylemOutRingCircleSegmentLengthDB after adjustment of ratio;
 *
 * \param map<int, vector<double> > xylemOutRingCircleSegmentLengthDB;
 * \return map<int, vector<double> > xylemOutRingCircleSegmentLengthDB
 *
 */

void rsPXCoreDB::XylemOutRingCircleSegmentLengthAdjustRatioDB()
{
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec;

	for (itMap = xylemOutRingCircleSegmentLengthDB.begin();
		itMap != xylemOutRingCircleSegmentLengthDB.end();
		itMap++)
	{
		for (itVec = (*itMap).second.begin(); itVec != (*itMap).second.end(); itVec++)
		{
			*itVec = (*itVec) / 2 / objectXYZRadiusRatio;
		}
	}
}

/** Get ObjectHeightDB and ObjectZPositionDB;
 *
 * \param map<int, vector<double> > longitudeSegmentHeightDB;
 * \param map<int, vector<double> > longitudeZPositionAddDB;
 * \return map<int, vector< vector <vector<double> > > > xylemOutRingObjectHeightDB;
 * \return map<int, vector< vector <vector<double> > > > xylemOutRingObjectZPositionDB;
 *
 */

void rsPXCoreDB::XylemOutRingObjectHeightAndZPositionDB(int sliceNum)
{  /// declare iterator;
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec;

	vector< vector<double> >           objectHeightVec2;
	vector<double>                     objectHeightVec1;

	vector< vector<double> >           objectZPositionVec2;
	vector<double>                     objectZPositionVec1;
	/// declare int;

	int i;
	int cellNum;
	int sliceTempNum;

	//ofstream fout("a.txt",ios::app);
	/// cout << circleSegmentLengthDB;
	for (i = 0, itMap = xylemOutRingCircleXDB.begin();
		itMap != xylemOutRingCircleXDB.end();
		i++, itMap++)
	{
		objectHeightVec2.clear();
		objectZPositionVec2.clear();
		for (cellNum = 0, itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			cellNum++, itVec++)
		{
			int randomHeightZPosition = rand() % 200;
			objectHeightVec1.clear();
			objectZPositionVec1.clear();
			for (sliceTempNum = 0;
				sliceTempNum != sliceNum;
				sliceTempNum++)
			{
				objectHeightVec1.push_back
				(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio);

				//            fout << "xylemOutRingObjectHeightDB: " << "i: " << i << " cellNum " << cellNum
				//                 << " sliceTempNum: " << sliceTempNum << ": "
				//                 << longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] << endl;

				//              fout <<  "objectHeightVec1: " << "sliceTempNum: " << sliceTempNum
				//                 << ": " << objectHeightVec1[sliceTempNum] << endl;

				objectZPositionVec1.push_back
				(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
			}
			objectHeightVec2.push_back(objectHeightVec1);
			objectZPositionVec2.push_back(objectZPositionVec1);
		}
		xylemOutRingObjectHeightDB.insert(pair<int, vector <vector<double> > >(i, objectHeightVec2));
		xylemOutRingObjectZPositionDB.insert(pair<int, vector <vector<double> > >(i, objectZPositionVec2));
	}

	//cout << "RsPXCoreDB->xylemOutRingObjectHeightDB" << endl;
	map<int, vector< vector<double> > >::iterator itMap2;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;

	/// cout xylemOutRingCircleSegmentLengthDB;
	for (itMap2 = xylemOutRingObjectHeightDB.begin(), i = 0;
		itMap2 != xylemOutRingObjectHeightDB.end();
		itMap2++, i++)
	{  //cout<< "i: " << i << endl;
		for (itVec2 = (*itMap2).second.begin(), cellNum = 0;
			itVec2 != (*itMap2).second.end();
			itVec2++, cellNum++)
		{
			for (itVec1 = (*itVec2).begin(); itVec1 != (*itVec2).end(); itVec1++)

			{  //cout <<"cellNum: " << cellNum << " " << *itVec1 << endl;
			}
		}
	}
}

/** Get ObjectHeightDB and ObjectZPositionDB of Xylem Center Ring;
 *
 * \param map<int, vector<double> > longitudeSegmentHeightDB;
 * \param map<int, vector<double> > longitudeZPositionAddDB;
 * \return map<int, vector<double> > xylemCenterRingObjectHeightDB;
 * \return map<int, vector<double> > xylemCenterRingObjectZPositionDB;
 *
 */

void rsPXCoreDB::XylemCenterRingObjectHeightAndZPositionDB(int sliceNum)
{  /// declare iterator;
	vector<double>::iterator itVec;

	vector<double> objectHeightVec;
	vector<double> objectZPositionVec;
	/// declare int;

	int i;
	int sliceTempNum;
	/// cout << circleSegmentLengthDB;
	for (i = 0, itVec = centerX.begin();
		itVec != centerX.end();
		i++, itVec++)
	{
		int randomHeightZPosition = rand() % 200;
		objectHeightVec.clear();
		objectZPositionVec.clear();
		for (sliceTempNum = 0;
			sliceTempNum != sliceNum;
			sliceTempNum++)
		{
			objectHeightVec.push_back
			(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / objectXYZRadiusRatio);
			//cout << "objectHeightVec1: " << longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio << endl;

			objectZPositionVec.push_back
			(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
			//cout << "objectZPositionVec1: " << longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum] << endl;
		}
		xylemCenterRingObjectHeightDB.insert(pair<int, vector<double> >(i, objectHeightVec));
		xylemCenterRingObjectZPositionDB.insert(pair<int, vector<double> >(i, objectZPositionVec));
	}
}

/*******************************************
Initialize other Database;
********************************************/
void rsPXCoreDB::InitXylemOutRing
(double endodermisBaseRadius,
	double pxGapRadius,
	int setPXNum,
	double setPXAverageRingRadius,
	double variationRatio,
	double xylemMaxOutRingCellNum,
	double xylemMaxOutRingAddRadius,
	int setUResolution,
	int setVResolution,
	int setWResolution,
	int sliceNum
)
{
	SetObjectXYZRadiusRatio();
	SetObjectOpacity();

	SteleBoundaryRingRadius(endodermisBaseRadius);
	PXBoundaryRingRadius(pxGapRadius);
	PXNum(setPXNum);
	PXAverageRingRadius(setPXAverageRingRadius);

	RandomRadius(variationRatio);

	CenterXYRotate();

	XylemOutRingDB(xylemMaxOutRingCellNum,
		xylemMaxOutRingAddRadius);

	PXMaxBoundaryRadius();
	BoundaryMXPXRingRadius();
	CenterXYRadiusDB();
	CenterXYPosition();
	/// initialize xylemOutRingAppendAddRadiusDB and xylemOutRingCircleRadiusDB
	/// before impletement XylemOutRingCircleSegmentAndCircleXYDB;
	XylemOutRingCircleRadiusDB();

	XylemOutRingObjectVerticalDB();

	XylemOutRingCircleSegmentAndCircleXYDB(variationRatio);

	XylemOutRingAddCenterXY();

	XylemOutRingCircleSegmentLengthAdjustRatioDB();
	XylemOutRingObjectHeightAndZPositionDB(sliceNum);
	XylemCenterRingObjectHeightAndZPositionDB(sliceNum);
	SetSuperEllipsoidResolution(setUResolution, setVResolution, setWResolution);
	MapRGB();
}
/////////////////////////////////////////  PXSmall ///////////////////////////////////////////////////////
/** Get boundaryRadiusDB
 *
 * \param map<int, double> xylemOutRingAddRadiusDB;
 * \param vector<double> eachRingRadius;
 * \return vector<double> boundaryRadiusDB;
 *
 */

void rsPXCoreDB::BoundaryRadiusDB()
{
	vector<double>::iterator itVec;
	map<int, double>::iterator itMap;
	int i;
	double temp;
	for (itMap = xylemOutRingAddRadiusDB.begin(), itVec = eachRingRadius.begin(), i = 0;
		itMap != xylemOutRingAddRadiusDB.end();
		itMap++, itVec++, i++)
	{  // boundaryRadiusDB = xylemOutRingAddRadiusDB * 2 + eachRingRadius * 2;
		temp = (*itMap).second + *itVec;
		boundaryRadiusDB.push_back(temp);
	}
}

/** Get boundaryMaxAndMinCenterRadiusDB;
 *
 * \param vector<double> centerXYRadiusDB;
 * \param vector<double> boundaryRadiusDB;
 * \return map<int, double> boundaryMaxCenterRadiusDB;
 * \return map<int, double> boundaryMinCenterRadiusDB;
 *
 */

void rsPXCoreDB::BoundaryMaxAndMinCenterRadiusDB()
{
	vector<double>::iterator itVec;
	int i;
	double tempMax;
	double tempMin;
	for (itVec = boundaryRadiusDB.begin(), i = 0;
		itVec != boundaryRadiusDB.end();
		itVec++, i++)
	{  // boundaryMaxCenterRadiusDB = pxCenterXYRadius + xylemOutRingAddRadiusDB + eachRingRadius;
		tempMax = centerXYRadiusDB[i] + *itVec;
		boundaryMaxCenterRadiusDB.insert(pair<int, double>(i, tempMax));
		// boundaryMinCenterRadiusDB = pxCenterXYRadius - xylemOutRingAddRadiusDB - eachRingRadius;
		tempMin = centerXYRadiusDB[i] - *itVec;
		boundaryMinCenterRadiusDB.insert(pair<int, double>(i, tempMin));
	}
}

/** \brief eachRingMaxAndMinRadius;
 *
 * \param vector<double> eachRingRadius;
 * \param
 * \return double eachRingMaxRadius;
 * \return double eachRingMinRadius;
 *
 */
double eachRingMaxRadius;
double eachRingMinRadius;
void rsPXCoreDB::EachRingMaxAndMinRadius()
{
	vector<double>::iterator itVec;
	double tempMax;
	double tempMin;
	double max = 0;
	double min = 1000;
	for (itVec = eachRingRadius.begin();
		itVec != eachRingRadius.end();
		itVec++)
	{
		tempMax = *itVec;
		tempMin = *itVec;
		if (max < tempMax)
		{
			max = tempMax;
		}
		if (min > tempMin)
		{
			min = tempMin;
		}
	}
	eachRingMaxRadius = max;
	eachRingMinRadius = min;
}

/** Get pxSmallRadiusDB
 *
 * \param vector<double> eachRingRadius;
 * \return vector<double> pxSmallRadiusDB;
 *
 */
void rsPXCoreDB::PXSmallVerticalAndParallelRadiusDB()
{
	vector<double>::iterator itVec;
	double tempVertical;
	double tempParallel;
	for (itVec = eachRingRadius.begin();
		itVec != eachRingRadius.end();
		itVec++)
	{
		if (*itVec <= pxAverageRingRadius)
		{
			tempVertical = eachRingMaxRadius / 2.5;
			tempParallel = eachRingMaxRadius / 1.5;
		}
		else
		{
			tempVertical = eachRingMinRadius / 3;
			tempParallel = eachRingMinRadius / 2;
		}
		pxSmallVerticalRadiusDB.push_back(tempVertical);
		pxSmallParallelRadiusDB.push_back(tempParallel);
	}
}

/** Get centerXYRadiusPXSmallDB
 *
 * \param map<int, double> boundaryMaxCenterRadiusDB;
 * \param vector<double> pxSmallRadiusDB;
 * \return map<int, double> centerXYRadiusPXSmallDB;
 *
 */
 //map<int, double> centerXYRadiusPXSmallDB;

void rsPXCoreDB::CenterXYRadiusPXSmallDB()
{
	vector<double>::iterator itVec;
	map<int, double>::iterator itMap;
	int i;
	double temp;
	for (itMap = boundaryMaxCenterRadiusDB.begin(), itVec = pxSmallVerticalRadiusDB.begin(), i = 0;
		itMap != boundaryMaxCenterRadiusDB.end();
		itMap++, itVec++, i++)
	{  // CenterXYRadiusPXSmallDB = boundaryMaxCenterRadiusDB + pxSmallVerticalRadiusDB;
		temp = (*itMap).second + *itVec;
		centerXYRadiusPXSmallDB.insert(pair<int, double>(i, temp));
	}
}

/** Get centerXYPXSmall;
 *
 * \param map<int, double> centerXYRadiusPXSmallDB;
 * \param vector<double> centerRingRotateRadian;
 * \return map<int, double> centerXPXSmall;
 * \return map<int, double> centerYPXSmall;
 *
 */
 //vector<double> centerXPXSmall;
 //vector<double> centerYPXSmall;

void rsPXCoreDB::CenterXYPXSmall()
{
	vector<double>::iterator itVec;
	map<int, double>::iterator itMap;
	int i;

	ofstream fout("a.txt", ios::app);
	fout << "rsPXCoreDB.cpp" << endl;
	for (itMap = centerXYRadiusPXSmallDB.begin(), itVec = centerRingRotateRadian.begin(), i = 0;
		itMap != centerXYRadiusPXSmallDB.end();
		itMap++, itVec++, i++)
	{
		centerXPXSmall.push_back((*itMap).second * cos(*itVec));
		centerYPXSmall.push_back((*itMap).second * sin(*itVec));
		fout << "centerXPXSmall: " << i << ": " << centerXPXSmall[i] << endl;
		fout << "centerYPXSmall: " << i << ": " << centerYPXSmall[i] << endl;
		fout << "centerXYRadiusPXSmallDB: " << i << ": " << (*itMap).second << endl;
		fout << "         centerRingRotateRadian: " << i << ": " << *itVec << endl;
	}
}

/** Get ObjectHeightDB and ObjectZPositionDB of PXSmall Center Ring;
 *
 * \param map<int, vector<double> > xylemCenterRingObjectHeightDB;
 * \param map<int, vector<double> > xylemCenterRingObjectZPositionDB;
 * \return map<int, vector<double> > pxSmallCenterRingObjectHeightDB;
 * \return map<int, vector<double> > pxSmallCenterRingObjectZPositionDB;
 *
 */

void rsPXCoreDB::PXSmallCenterRingObjectHeightAndZPositionDB()
{
	map<int, vector<double> >::iterator itMapHeight;
	map<int, vector<double> >::iterator itMapZPosition;
	vector<double>::iterator itVecHeight;
	vector<double>::iterator itVecZPosition;

	vector<double> objectHeightVec;
	vector<double> objectZPositionVec;
	double tempHeight;
	double tempZPosition;
	/// declare int;
	int i;
	for (itMapHeight = xylemCenterRingObjectHeightDB.begin(),
		itMapZPosition = xylemCenterRingObjectZPositionDB.begin(), i = 0;
		itMapHeight != xylemCenterRingObjectHeightDB.end();
		itMapHeight++, itMapZPosition++, i++)
	{
		objectHeightVec.clear();
		objectZPositionVec.clear();
		for (itVecHeight = (*itMapHeight).second.begin(), itVecZPosition = (*itMapZPosition).second.begin();
			itVecHeight != (*itMapHeight).second.end();
			itVecHeight++, itVecZPosition++)
		{
			tempHeight = *itVecHeight / 2;
			tempZPosition = *itVecZPosition / 2;
			objectHeightVec.push_back(tempHeight);
			objectZPositionVec.push_back(tempZPosition);
		}
		pxSmallCenterRingObjectHeightDB.insert(pair<int, vector<double> >(i, objectHeightVec));
		pxSmallCenterRingObjectZPositionDB.insert(pair<int, vector<double> >(i, objectZPositionVec));
	}
}


/** Initialize PXSmall;
 *
 * \param
 * \param
 * \return
 *
 */
void rsPXCoreDB::InitPXSamll()
{
	BoundaryRadiusDB();

	BoundaryMaxAndMinCenterRadiusDB();

	EachRingMaxAndMinRadius();

	PXSmallVerticalAndParallelRadiusDB();

	CenterXYRadiusPXSmallDB();

	PXSmallCenterRingObjectHeightAndZPositionDB();

	CenterXYPXSmall();
}