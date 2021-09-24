#define _USE_MATH_DEFINES
#include <cmath> 
#include "rsSourceDermisDB.h"

//////////////////////////////////////// Functions //////////////////////////////////////////////////

/// Set OutputXMLVtpFileName;
void rsSourceDermisDB::OutputXMLVtpFileName(const char* outputXMLVtpFileNameInput)
{
	outputXMLVtpFileName = outputXMLVtpFileNameInput;
}

/// create circleRadiusDB;
void rsSourceDermisDB::CircleRadiusDB
(double epidermisBaseRadius,
	double epidermisAddRadiusData)
{
	circleRadiusDB = CircleRadius(epidermisBaseRadius, 0, epidermisAddRadiusData);
	cout << "epidermisbase radius " << epidermisBaseRadius;
}

/// createobjectVerticalDB;
void rsSourceDermisDB::ObjectVerticalDB(double epidermisAddRadius)
{
	objectVerticalDB = ObjectVertical(epidermisAddRadius / objectXYZRadiusRatio);
	cout << "epidermisobjectVerticalDB" << objectVerticalDB << endl;
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

void rsSourceDermisDB::EpidermisCellNumCalculate(double epidermisAddRadiusData)
{
	EpidermisCellNumCalculated = int(2 * M_PI * circleRadiusDB / epidermisAddRadiusData);

	cout << "EpidermisCellNumCalculated: " << EpidermisCellNumCalculated << endl;
	cout << "epidermisAddRadiusData" << epidermisAddRadiusData << endl;
	cout << "circleRadiusDB" << circleRadiusDB << endl;
}

/******************************************************
// Create GetRandomCircleSegmentAndCircleXYNonuniformDB;
*******************************************************/

void rsSourceDermisDB::GetRandomCircleSegmentAndCircleXYNonuniformDB
(double epidermisAddRadiusData,
	double epidermisBaseRadius,
	//   int epidermisCellNum,
	double variationRatio)

{
	CircleRadiusDB(epidermisBaseRadius,
		epidermisAddRadiusData);

	CirclePerimeter(circleRadiusDB);

	/// RandomRatioButSameSumAndNumber
	SameSumAndNumberAndRatio(circleSegmentLength,
		circleSegmentLengthAdd,
		circleSegmentLengthSum,
		circlePerimeter,
		EpidermisCellNumCalculated,
		//                             epidermisCellNum,
		variationRatio);

	circleSegmentLengthDB = circleSegmentLength;
	circleSegmentLengthSumDB = circleSegmentLengthSum;

	//   CircleXYNonuniform( epidermisCellNum, circleRadiusDB );
	CircleXYNonuniform(EpidermisCellNumCalculated, circleRadiusDB);
	circleXDB = circleX;
	circleYDB = circleY;
	circleSegmentRotateAngleDB = circleSegmentRotateAngle;
}


/******************************************************
// Get circleSegmentLengthAdjustRatioDB;
*******************************************************/
void rsSourceDermisDB::CircleSegmentLengthAdjustRatioDB()
{
	vector<double>::iterator itVector;

	for (itVector = circleSegmentLengthDB.begin(); itVector != circleSegmentLengthDB.end(); itVector++)
	{
		*itVector = (*itVector) / 2 / objectXYZRadiusRatio;
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

	vector<double>::iterator itVector;

	vector<double> objectHeightVec;
	vector<double> objectZPositionVec;
	/// declare int;
	int i;
	int sliceTempNum;

	for (i = 0, itVector = circleXDB.begin(); itVector != circleXDB.end(); i++, itVector++)
	{
		int randomHeightZPosition = rand() % 200;
		objectHeightVec.clear();
		objectZPositionVec.clear();
		for (sliceTempNum = 0; sliceTempNum != sliceNum; sliceTempNum++)
		{
			objectHeightVec.push_back
			(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio);

			objectZPositionVec.push_back
			(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
		}
		objectHeightDB.insert(pair<int, vector<double> >(i, objectHeightVec));
		objectZPositionDB.insert(pair<int, vector<double> >(i, objectZPositionVec));
	}
}


/*******************************************
Initialize other Database;
********************************************/
void rsSourceDermisDB::InitAllDB(const char* outputXMLVtpFileNameInput,
	double epidermisAddRadiusData,
	double epidermisBaseRadius,
	//                                      int epidermisCellNum,
	double variationRatio,
	int sliceNum)

{  /// first: get boundaryRadius from rsSourceCorticalDB;


	OutputXMLVtpFileName(outputXMLVtpFileNameInput);

	CircleRadiusDB(epidermisBaseRadius,
		epidermisAddRadiusData);

	SetObjectXYZRadiusRatio();

	SetObjectOpacity();

	ObjectVerticalDB(epidermisAddRadiusData);

	EpidermisCellNumCalculate(epidermisAddRadiusData);

	GetRandomCircleSegmentAndCircleXYNonuniformDB
	(epidermisAddRadiusData,
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
	pureCellVerticalDB = objectVerticalDB;

	/// pureCellParallelDB
	for (itVec1 = circleSegmentLengthDB.begin(), i = 0;
		itVec1 != circleSegmentLengthDB.end();
		itVec1++, i++)
	{
		temp = *itVec1 - gapCellWall;
		pureCellParallelDB.push_back(temp);
	}

	/// pureCellHeightDB
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
	vacuoleVerticalDB = objectVerticalDB;
	
	/// vacuoleParallelDB
	for (itVec1 = circleSegmentLengthDB.begin(), i = 0;
		itVec1 != circleSegmentLengthDB.end();
		itVec1++, i++)
	{
		temp = *itVec1 - gapCytoTono - gapCellWall;
		vacuoleParallelDB.push_back(temp);
	}
	/// vacuoleHeightDB
	for (itMap1 = objectHeightDB.begin(), i = 0;
		itMap1 != objectHeightDB.end();
		itMap1++, i++)
	{
		vec1.clear();
		for (itVec1 = (*itMap1).second.begin(); itVec1 != (*itMap1).second.end(); itVec1++)
		{
			temp = *itVec1 - gapCytoTono - gapCellWall;
			vec1.push_back(temp);
		}
		vacuoleHeightDB.insert(pair<int, vector<double> >(i, vec1));
	}
}