#define _USE_MATH_DEFINES
#include <cmath> 
#include "rsSteleInnerDB.h"

/** \brief SteleInnerBoundRadius
 *
 * \param rsMXBoundaryOutDB *RsMXBoundaryOutDB->innerRingRadius;
 * \return double steleInnerBoundRadius;
 *
 */
void rsSteleInnerDB::SteleInnerBoundRadius(rsMXBoundaryOutDB* RsMXBoundaryOutDB)
{
	steleInnerBoundRadius = RsMXBoundaryOutDB->innerRingRadius;
}

/** \brief SteleInnestCellRadius
 *
 * \param double steleInnestCellRadiusInput;
 * \return double steleInnestCellRadius;
 *
 */
void rsSteleInnerDB::SteleInnestCellRadius(double steleInnestCellRadiusInput)
{
	steleInnestCellRadius = steleInnestCellRadiusInput;
}

/** \brief SteleInnerAddRadiusDB
 *
 * \param int steleInnerLayerNumInput
 * \param double steleInnerBoundRadius;
 * \param double steleInnestCellRadius;
 * \return int steleInnerLayerNum;
 * \return vector<double> steleInnerAddRadiusDB;
 *
 */
void rsSteleInnerDB::SteleInnerAddRadiusDB(int steleInnerLayerNumInput)
{
	steleInnerLayerNum = steleInnerLayerNumInput;
	double aveAddRadius = (steleInnerBoundRadius - steleInnestCellRadius) / steleInnerLayerNum;
	int i;
	for (i = 0; i != steleInnerLayerNum; i++)
	{
		steleInnerAddRadiusDB.push_back(aveAddRadius);
	}
}

/** \brief
 *
 * \param vector<double> steleInnerAddRadiusDB;
 * \return vector<double> steleInnerAppendRadiusDB;
 *
 */
void rsSteleInnerDB::SteleInnerAppendRadiusDB()
{
	vector<double>::iterator itVec;
	double temp = 0;
	for (itVec = steleInnerAddRadiusDB.begin(); itVec != steleInnerAddRadiusDB.end(); itVec++)
	{
		steleInnerAppendRadiusDB.push_back(temp);
		temp += (*itVec);
	}
}


/** \brief SteleInnerRingRadiusDB
 *
 * \param double steleInnestCellRadius;
 * \param vector<double> steleInnerAddRadiusDB;
 * \param vector<double> steleInnerAppendRadiusDB;
 * \return vector<double> steleInnerRingRadiusDB;
 *
 */
void rsSteleInnerDB::SteleInnerRingRadiusDB()
{
	int iRingNum;
	/// declare iterator;
	vector<double>::iterator itVecAdd;

	for (iRingNum = 0, itVecAdd = steleInnerAddRadiusDB.begin();
		itVecAdd != steleInnerAddRadiusDB.end();
		itVecAdd++, iRingNum++)
	{
		steleInnerRingRadiusDB.push_back(CircleRadius(steleInnestCellRadius,
			steleInnerAppendRadiusDB[iRingNum],
			(*itVecAdd))
		);

	}
}

/** \brief SteleInnerCellNumCalculateData;
 *
 * \param vector<double> steleInnerRingRadiusDB;
 * \param vector<double> steleInnerAddRadiusDB;
 * \return vector<int> steleInnerCellNumCalculateData
 *
 */
void rsSteleInnerDB::SteleInnerCellNumCalculateData()
{
	vector<double>::iterator itVecAdd;
	vector<double>::iterator itVec;
	int tempNum;
	double perimeterLayer;
	int i;
	cout << "SteleCellNumCalculateData" << endl;
	for (itVecAdd = steleInnerAddRadiusDB.begin(), itVec = steleInnerRingRadiusDB.begin(), i = 0;
		itVecAdd != steleInnerAddRadiusDB.end();
		itVecAdd++, itVec++, i++)
	{
		perimeterLayer = 2 * M_PI * (*itVec);
		tempNum = int(perimeterLayer / (*itVecAdd));
		cout << tempNum << endl;
		steleInnerCellNumCalculateData.push_back(tempNum);
	}
}


/** \brief SteleInnerObjectVerticalDB
 *
 * \param vector<double> steleInnerAddRadiusDB;
 * \return vector<double> steleInnerObjectVerticalDB;
 *
 */
void rsSteleInnerDB::SteleInnerObjectVerticalDB()
{
	int iRingNum;
	vector<double>::iterator itVecAdd;

	for (iRingNum = 0, itVecAdd = steleInnerAddRadiusDB.begin();
		itVecAdd != steleInnerAddRadiusDB.end();
		itVecAdd++, iRingNum++)
	{
		steleInnerObjectVerticalDB.push_back(ObjectVertical(*itVecAdd));
	}
}

/******************************************************
// Create RandomHeightDB;
*******************************************************/
void rsSteleInnerDB::RandomHeightDB(double totalHeight, int sliceNum, double initZPosition, int vectorNum)
{
	int temp;
	srand((unsigned)time(NULL));
	for (temp = 0;
		temp != vectorNum;
		temp++)
	{
		RandomHeight(totalHeight, sliceNum, initZPosition);
		longitudeSegmentHeightDB.insert(pair<int, vector<double> >(temp, longitudeSegmentHeight));
		longitudeZPositionAddDB.insert(pair<int, vector<double> >(temp, longitudeZPositionAdd));
	}
}

/** \brief GetRandomCircleSegmentAndCircleXYNonuniformDB
 *
 * \param double variationRatio;
 * \param vector<double> steleInnerAddRadiusDB;
 * \param vector<int> steleInnerCellNumCalculateData;
 * \param vector<double> steleInnerRingRadiusDB;
 * \return map<int, vector<double> > circleSegmentLengthDB;
 * \return vector<double> circleSegmentLengthSumDB;
 * \return map<int, vector<double> > circleSegmentRotateAngleDB;
 * \return map<int, vector<double> > circleXDB;
 * \return map<int, vector<double> > circleYDB;
 *
 */
void rsSteleInnerDB::GetRandomCircleSegmentAndCircleXYNonuniformDB
(double variationRatio)
{
	int iRingNum;
	/// declare corticalAddRadiusDB iterator;
	vector<double>::iterator itVecAdd;
	vector<int>::iterator itVecCellNum;

	ofstream fout(getFolderName() + "cortex.txt", ios::app);
	cout << "circleSegmentRotateAngleDB" << endl;
	for (iRingNum = 0, itVecCellNum = steleInnerCellNumCalculateData.begin(),
		itVecAdd = steleInnerAddRadiusDB.begin();
		itVecAdd != steleInnerAddRadiusDB.end();
		itVecAdd++, iRingNum++, itVecCellNum++)
	{
		CirclePerimeter(steleInnerRingRadiusDB[iRingNum]);
		SameSumAndNumberAndRatio(circleSegmentLength,
			circleSegmentLengthAdd,
			circleSegmentLengthSum,
			circlePerimeter,
			*itVecCellNum,
			variationRatio);
		
		circleSegmentLengthDB.insert(pair<int, vector<double> >(iRingNum, circleSegmentLength));
		circleSegmentLengthSumDB.push_back(circleSegmentLengthSum);

		CircleXYNonuniform(*itVecCellNum, steleInnerRingRadiusDB[iRingNum]);
		circleXDB.insert(pair<int, vector<double> >(iRingNum, circleX));
		circleYDB.insert(pair<int, vector<double> >(iRingNum, circleY));
		circleSegmentRotateAngleDB.insert(pair<int, vector<double> >(iRingNum, circleSegmentRotateAngle));
	}
}

/******************************************************
// Get circleSegmentLengthAdjustRatioDB;
*******************************************************/
void rsSteleInnerDB::CircleSegmentLengthAdjustRatioDB()
{
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVector;

	for (itMap = circleSegmentLengthDB.begin();
		itMap != circleSegmentLengthDB.end();
		itMap++)
	{
		for (itVector = (*itMap).second.begin(); itVector != (*itMap).second.end(); itVector++)
		{
			*itVector = (*itVector) / 2;
		}
	}
}

/*******************************************
to get ObjectHeightDB and ObjectZPositionDB;
********************************************/
void rsSteleInnerDB::ObjectHeightAndZPositionDB(int sliceNum)
{  /// declare iterator;
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVector;

	vector< vector<double> > objectHeightVec2;
	vector<double>           objectHeightVec1;

	vector< vector<double> > objectZPositionVec2;
	vector<double>           objectZPositionVec1;
	/// declare int;
	int iRingNum;
	int i;
	int sliceTempNum;
	/// cout << circleSegmentLengthDB;
	for (iRingNum = 0, itMap = circleXDB.begin();
		itMap != circleXDB.end();
		iRingNum++, itMap++)
	{
		objectHeightVec2.clear();
		objectZPositionVec2.clear();
		for (i = 0, itVector = (*itMap).second.begin(); itVector != (*itMap).second.end(); i++, itVector++)
		{
			int randomHeightZPosition = rand() % 200;
			objectHeightVec1.clear();
			objectZPositionVec1.clear();
			for (sliceTempNum = 0; sliceTempNum != sliceNum; sliceTempNum++)
			{
				objectHeightVec1.push_back
				(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2);

				objectZPositionVec1.push_back
				(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
			}
			objectHeightVec2.push_back(objectHeightVec1);
			objectZPositionVec2.push_back(objectZPositionVec1);
		}
		objectHeightDB.insert(pair<int, vector< vector<double> > >(iRingNum, objectHeightVec2));
		objectZPositionDB.insert(pair<int, vector< vector<double> > >(iRingNum, objectZPositionVec2));
	}
}

vector<double> steleInnestObjectHeightDB;
vector<double> steleInnestObjectZPositionDB;
void rsSteleInnerDB::SteleInnestObjectHeightAndZPositionDB(int sliceNum)
{
	int sliceTempNum;
	int randomHeightZPosition = rand() % 200;
	for (sliceTempNum = 0; sliceTempNum != sliceNum; sliceTempNum++)
	{
		steleInnestObjectHeightDB.push_back
		(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2);

		steleInnestObjectZPositionDB.push_back
		(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
	}
}


/*******************************************
Initialize other Database;
********************************************/
void rsSteleInnerDB::InitAllDB(rsMXBoundaryOutDB* RsMXBoundaryOutDB,
	double steleInnestCellRadiusInput,
	int steleInnerLayerNumInput,
	double totalHeight,
	double initZPosition,
	int vectorNum,
	double variationRatio,
	int sliceNum)
{
	SteleInnerBoundRadius(RsMXBoundaryOutDB);

	SteleInnestCellRadius(steleInnestCellRadiusInput);

	SteleInnerAddRadiusDB(steleInnerLayerNumInput);

	SteleInnerAppendRadiusDB();

	SteleInnerRingRadiusDB();

	SteleInnerCellNumCalculateData();

	SteleInnerObjectVerticalDB();

	RandomHeightDB(totalHeight, sliceNum, initZPosition, vectorNum);

	GetRandomCircleSegmentAndCircleXYNonuniformDB(variationRatio);

	CircleSegmentLengthAdjustRatioDB();

	ObjectHeightAndZPositionDB(sliceNum);

	SteleInnestObjectHeightAndZPositionDB(sliceNum);

	SetSuperEllipsoidResolution();

	SetObjectOpacity();

}