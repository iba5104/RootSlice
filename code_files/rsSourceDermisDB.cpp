#define _USE_MATH_DEFINES
#include <cmath> 
#include "rsSourceDermisDB.h"

//////////////////////////////////////// Functions //////////////////////////////////////////////////

/// Set OutputXMLVtpFileName;
void rsSourceDermisDB::OutputXMLVtpFileName(const char* outputXMLVtpFileNameInput, const char* cellTypeInput)
{
	outputXMLVtpFileName = outputXMLVtpFileNameInput;
	cellType = cellTypeInput;
}

/// create circleRadiusDB;
void rsSourceDermisDB::CircleRadiusDB
(double baseRadius,
 vector<double> epidermisAddRadiusVectorDB
)
{
	double appendRadius = 0;
	vector<double>::iterator itVecAdd;
	for (itVecAdd = epidermisAddRadiusVectorDB.begin();
		itVecAdd != epidermisAddRadiusVectorDB.end();
		itVecAdd++)
	{
		circleRadiusDB.push_back(CircleRadius(baseRadius, appendRadius, (*itVecAdd)));
		appendRadius += (*itVecAdd);
	}
}

/// createobjectVerticalDB;
void rsSourceDermisDB::ObjectVerticalDB(vector<double> epidermisAddRadiusVectorDB)
{
	vector<double>::iterator itVecAdd;
	for (itVecAdd = epidermisAddRadiusVectorDB.begin();
		itVecAdd != epidermisAddRadiusVectorDB.end();
		itVecAdd++)
	{
		objectVerticalDB.push_back(ObjectVertical(*itVecAdd) / objectXYZRadiusRatio);
		cout << "epidermisobjectVerticalDB " << objectVerticalDB.back() << endl;
	}
}

/******************************************************
// Create RandomHeightDB; Initialize seperated;
*******************************************************/
void rsSourceDermisDB::RandomHeightDB(double totalHeight, int sliceNum, double initZPosition, int VectorNum)
{
	int temp;
	for (temp = 0;
		temp != VectorNum;
		temp++)
	{  /// RandomHeight;
		NonRandomHeight(totalHeight, sliceNum, initZPosition);
		longitudeSegmentHeightDB.insert(pair<int, vector<double> >(temp, longitudeSegmentHeight));
		longitudeZPositionAddDB.insert(pair<int, vector<double> >(temp, longitudeZPositionAdd));
		//cout << "EpidermislongitudeSegmentHeigh" << longitudeSegmentHeight.at(temp) << endl;
	}
}

/******************************************************
// Create GetRandomCircleSegmentAndCircleXYNonuniformDB;
*******************************************************/
/** \brief epidermisCellNumCalculate
 *
 * \param double epidermisAddRadiusData;
 * \param double circleRadiusDB;
 * \return int EpidermisCellNumCalculated
 *
 */
void rsSourceDermisDB::EpidermisCellNumCalculate(vector<double> epidermisAddRadiusData)
{
	int iRingNum;
	vector<double>::iterator itVecAdd;
	EpidermisCellNumCalculated = 0;
	for (iRingNum = 0, itVecAdd = circleRadiusDB.begin();
		itVecAdd != circleRadiusDB.end();
		itVecAdd++, iRingNum++)
	{
		int curRingCellCount = int(2 * M_PI * (*itVecAdd) / epidermisAddRadiusData[iRingNum]);
		DermisCellNumDB.push_back(curRingCellCount);
		EpidermisCellNumCalculated += curRingCellCount;
		cout << "epidermisAddRadiusData: " << epidermisAddRadiusData[iRingNum] << endl;
	}
	cout << "EpidermisCellNumCalculated: " << EpidermisCellNumCalculated << endl;
	//cout << "circleRadiusDB" << circleRadiusDB << endl;
}

/******************************************************
// Create GetRandomCircleSegmentAndCircleXYNonuniformDB;
*******************************************************/

void rsSourceDermisDB::GetRandomCircleSegmentAndCircleXYNonuniformDB
(vector<double> epidermisAddRadiusData,
	double epidermisBaseRadius,
	//   int epidermisCellNum,
	double variationRatio)
{
	// CircleRadiusDB(epidermisBaseRadius, epidermisAddRadiusData);

	int iRingNum;
	vector<double>::iterator itVecAdd;
	for (iRingNum = 0, itVecAdd = circleRadiusDB.begin();
		itVecAdd != circleRadiusDB.end();
		itVecAdd++, iRingNum++)
	{
		CirclePerimeter((*itVecAdd));
		SameSumAndNumberAndRatio(circleSegmentLength,
			circleSegmentLengthAdd,
			circleSegmentLengthSum,
			circlePerimeter,
			DermisCellNumDB[iRingNum],
			// epidermisCellNum,
			variationRatio);

		circleSegmentLengthDB.insert(pair<int, vector<double> >(iRingNum, circleSegmentLength));
		circleSegmentLengthSumDB.push_back(circleSegmentLengthSum);
		
		CircleXYNonuniform(DermisCellNumDB[iRingNum], (*itVecAdd));
		circleXDB.insert(pair<int, vector<double> >(iRingNum, circleX));
		circleYDB.insert(pair<int, vector<double> >(iRingNum, circleY));
		circleSegmentRotateAngleDB.insert(pair<int, vector<double> >(iRingNum, circleSegmentRotateAngle));
	}
}


/******************************************************
// Get circleSegmentLengthAdjustRatioDB;
*******************************************************/
void rsSourceDermisDB::CircleSegmentLengthAdjustRatioDB()
{
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVector;

	for (itMap = circleSegmentLengthDB.begin(); itMap != circleSegmentLengthDB.end(); itMap++)
	{
		for (itVector = (*itMap).second.begin(); itVector != (*itMap).second.end(); itVector++)
		{
			*itVector = (*itVector) / 2 / objectXYZRadiusRatio;
		}
		//cout << "EpidermisCirclesegmentlength111 " << *itVector << endl;
	}
}

/*******************************************
to get ObjectHeightDB and ObjectZPositionDB;
********************************************/
/** need to initialize:
"longitudeSegmentHeightDB"
"longitudeZPositionAddDB"
**/

map<int, vector<double> > objectHeightDB;
map<int, vector<double> > objectZPositionDB;


void rsSourceDermisDB::ObjectHeightAndZPositionDB(int sliceNum)
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
				(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio); // Why half?
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


/*******************************************
Initialize other Database;
********************************************/
void rsSourceDermisDB::InitAllDB(const char* outputXMLVtpFileNameInput,
	const char* cellTypeInput,
	vector<double> cellDiameter,
	double epidermisBaseRadius,
	//                                      int epidermisCellNum,
	double variationRatio,
	int sliceNum, int numFiles)

{  /// first: get boundaryRadius from rsSourceCorticalDB;

	//sclerenBaseRadius += sclerenAddRadiusData * fileCount;

	OutputXMLVtpFileName(outputXMLVtpFileNameInput, cellTypeInput);

	CircleRadiusDB(epidermisBaseRadius, cellDiameter);

	SetObjectXYZRadiusRatio();

	SetObjectOpacity();

	ObjectVerticalDB(cellDiameter);

	EpidermisCellNumCalculate(cellDiameter);

	GetRandomCircleSegmentAndCircleXYNonuniformDB
	(cellDiameter,
	epidermisBaseRadius,
	//     epidermisCellNum,
	variationRatio);

	CircleSegmentLengthAdjustRatioDB();

	ObjectHeightAndZPositionDB(sliceNum);

	SetSuperEllipsoidResolution();

	MapRGB();
}

/******************************************************************************************************************
Initialize vacuole Database;
*******************************************************************************************************************/
/** \brief
 *
 * \param vector<double> objectVerticalDB;
 * \param map<int, vector<double> > circleSegmentLengthDB;
 * \param map<int, vector< vector<double> > > objectHeightDB;
 * \return vector<double> vacuoleVerticalDB;
 * \return map<int, vector<double> > vacuoleParallelDB;
 * \return map<int, vector< vector<double> > > vacuoleHeightDB;
 *
 */

 /// Pure Cell means the cell without cell wall;

void rsSourceDermisDB::InitPureCellDB(double gapCellWallInput)
{  // Initialize gapCellWall
	gapCellWall = gapCellWallInput;

	map<int, vector< vector<double> > >::iterator itMap2;
	map<int, vector<double> >::iterator itMap1;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;

	vector< vector<double> > vec2;
	vector<double>           vec1;
	double temp;
	int i;

	/// pureCellVerticalDB
	for (itVec1 = objectVerticalDB.begin();
		itVec1 != objectVerticalDB.end();
		itVec1++)
	{
		temp = *itVec1 - gapCellWall;
		pureCellVerticalDB.push_back(temp);
	}
	//pureCellVerticalDB = objectVerticalDB;

	/// pureCellParallelDB
	for (itMap1 = circleSegmentLengthDB.begin(), i = 0;
		itMap1 != circleSegmentLengthDB.end();
		itMap1++, i++)
	{
		vec1.clear();
		for (itVec1 = (*itMap1).second.begin(); itVec1 != (*itMap1).second.end(); itVec1++)
		{
			temp = *itVec1 - gapCellWall;
			vec1.push_back(temp);
		}
		pureCellParallelDB.insert(pair<int, vector<double> >(i, vec1));
	}

	/// pureCellHeightDB
	for (itMap2 = objectHeightDB.begin(), i = 0;
		itMap2 != objectHeightDB.end();
		itMap2++, i++)
	{
		vec2.clear();
		for (itVec2 = (*itMap2).second.begin(); itVec2 != (*itMap2).second.end(); itVec2++)
		{
			vec1.clear();
			for (itVec1 = (*itVec2).begin(); itVec1 != (*itVec2).end(); itVec1++)
			{
				temp = *itVec1 - gapCellWall;
				vec1.push_back(temp);
			}
			vec2.push_back(vec1);
		}
		pureCellHeightDB.insert(pair<int, vector< vector<double> > >(i, vec2));
	}
/*
	for (itMap1 = objectHeightDB.begin(), i = 0;
		itMap1 != objectHeightDB.end();
		itMap1++, i++)
	{
		vec1.clear();
		for (itVec1 = (*itMap1).second.begin(); itVec1 != (*itMap1).second.end(); itVec1++)
		{
			temp = *itVec1 - gapCellWall;
			vec1.push_back(temp);
		}
		pureCellHeightDB.insert(pair<int, vector<double> >(i, vec1));
	}
*/
}

/******************************************************************************************************************
Initialize vacuole Database;
*******************************************************************************************************************/
/** \brief
 *
 * \param vector<double> objectVerticalDB;
 * \param map<int, vector<double> > circleSegmentLengthDB;
 * \param map<int, vector< vector<double> > > objectHeightDB;
 * \return vector<double> vacuoleVerticalDB;
 * \return map<int, vector<double> > vacuoleParallelDB;
 * \return map<int, vector< vector<double> > > vacuoleHeightDB;
 *
 */

void rsSourceDermisDB::InitVacuoleDB(double gapCytoTonoInput)
{
	map<int, vector< vector<double> > >::iterator itMap2;
	map<int, vector<double> >::iterator itMap1;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;

	vector< vector<double> > vec2;
	vector<double>           vec1;
	double temp;
	int i;
	gapCytoTono = gapCytoTonoInput;
	/// vacuoleVerticalDB
	for (itVec1 = objectVerticalDB.begin();
		itVec1 != objectVerticalDB.end();
		itVec1++)
	{
		temp = *itVec1 - gapCytoTono - gapCellWall;
		vacuoleVerticalDB.push_back(temp);
	}
	
	/// vacuoleParallelDB
	for (itMap1 = circleSegmentLengthDB.begin(), i = 0;
		itMap1 != circleSegmentLengthDB.end();
		itMap1++, i++)
	{
		vec1.clear();
		for (itVec1 = (*itMap1).second.begin(); itVec1 != (*itMap1).second.end(); itVec1++)
		{
			temp = *itVec1 - gapCytoTono - gapCellWall;
			vec1.push_back(temp);
		}
		vacuoleParallelDB.insert(pair<int, vector<double> >(i, vec1));
	}
	/// vacuoleHeightDB
	for (itMap2 = objectHeightDB.begin(), i = 0;
		itMap2 != objectHeightDB.end();
		itMap2++, i++)
	{
		vec2.clear();
		for (itVec2 = (*itMap2).second.begin(); itVec2 != (*itMap2).second.end(); itVec2++)
		{
			vec1.clear();
			for (itVec1 = (*itVec2).begin(); itVec1 != (*itVec2).end(); itVec1++)
			{
				temp = *itVec1 - gapCytoTono - gapCellWall;
				vec1.push_back(temp);
			}
			vec2.push_back(vec1);
		}
		vacuoleHeightDB.insert(pair<int, vector< vector<double> > >(i, vec2));
	}
}