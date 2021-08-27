#define _USE_MATH_DEFINES
#include <cmath> 
#include "rsEpiCortexEndoWaterPathDB.h"

/// Set OutputXMLVtpFileName;
void rsEpiCortexEndoWaterPathDB::OutputXMLVtpFileName
(const char* ApoplastXMLVtpFileNameInput,
	const char* SymplastXMLVtpFileNameInput)
{
	ApoplastXMLVtpFileName = ApoplastXMLVtpFileNameInput;
	SymplastXMLVtpFileName = SymplastXMLVtpFileNameInput;
}


/** \brief EpiCortexEndoCellXYDB
 *
 * \param rsSourceEpidermisDB *RsSourceEpidermisDB->circleXDB;
 * \param rsSourceEpidermisDB *RsSourceEpidermisDB->circleYDB;
 * \param rsSourceCorticalDB *RsSourceCorticalDB->circleXDB;
 * \param rsSourceCorticalDB *RsSourceCorticalDB->circleYDB;
 * \param rsSourceEpidermisDB *RsSourceEndodermisDB->circleXDB;
 * \param rsSourceEpidermisDB *RsSourceEndodermisDB->circleYDB;
 * \return map<int, vector<double> > epiCortexEndoCellXDB;
 * \return map<int, vector<double> > epiCortexEndoCellYDB;
 *
 */

 /// Combine the epidermal, cortical and endodermal cell X and Y database together;
void rsEpiCortexEndoWaterPathDB::EpiCortexEndoCellXYDB
(rsSourceDermisDB* RsSourceEpidermisDB,
	rsSourceCorticalDB* RsSourceCorticalDB,
	rsSourceDermisDB* RsSourceEndodermisDB)
{
	map<int, vector<double> >::reverse_iterator itMap;
	map<int, vector<vector<double> > >::reverse_iterator itMapZHeightReverse;
	map<int, vector<vector<double> > >::reverse_iterator itMapZPositionReverse;
	map<int, vector<double> >::iterator itMapZPosition;
	map<int, vector<double> >::iterator itMapZHeight;

	vector<vector<double> >::iterator itVecZPosition;
	vector<vector<double> >::iterator itVecZHeight;
	int i;
	int mapSize;

	ofstream fout("WaterPath.txt", ios::app);
	fout << "EpiCortexEndoCellXYDB" << endl;

	vector<double> epidermisZPosition;
	/// Insert RsSourceEpidermisDB->circleXDB and RsSourceEpidermisDB->circleYDB;
	epiCortexEndoCellXDB.insert(pair<int, vector<double> >(0, RsSourceEpidermisDB->circleXDB));
	epiCortexEndoCellYDB.insert(pair<int, vector<double> >(0, RsSourceEpidermisDB->circleYDB));
	for (itMapZPosition = RsSourceEpidermisDB->objectZPositionDB.begin(),
		itMapZHeight = RsSourceEpidermisDB->objectHeightDB.begin();
		itMapZPosition != RsSourceEpidermisDB->objectZPositionDB.end();
		itMapZPosition++, itMapZHeight++)
	{
		epidermisZPosition.push_back(itMapZPosition->second[0] + itMapZHeight->second[0]);
		fout << "itMapZPosition->second[0]: " << itMapZPosition->second[0]
			<< "  itMapZHeight->second[0]: " << itMapZHeight->second[0]
			<< "  result: " << itMapZPosition->second[0] + itMapZHeight->second[0] << endl;
	}
	epiCortexEndoCellZDB.insert(pair<int, vector<double> >(0, epidermisZPosition));


	/// Insert RsSourceCorticalDB->circleXDB and RsSourceCorticalDB->circleYDB;
	for (itMap = RsSourceCorticalDB->circleXDB.rbegin(), i = 1;
		itMap != RsSourceCorticalDB->circleXDB.rend();
		itMap++, i++)
	{
		epiCortexEndoCellXDB.insert(pair<int, vector<double> >(i, itMap->second));
	}

	for (itMap = RsSourceCorticalDB->circleYDB.rbegin(), i = 1;
		itMap != RsSourceCorticalDB->circleYDB.rend();
		itMap++, i++)
	{
		epiCortexEndoCellYDB.insert(pair<int, vector<double> >(i, itMap->second));
	}

	vector<double> corticalZPosition;
	for (itMapZPositionReverse = RsSourceCorticalDB->objectZPositionDB.rbegin(),
		itMapZHeightReverse = RsSourceCorticalDB->objectHeightDB.rbegin(), i = 1;
		itMapZPositionReverse != RsSourceCorticalDB->objectZPositionDB.rend();
		itMapZPositionReverse++, itMapZHeightReverse++, i++)
	{
		corticalZPosition.clear();
		for (itVecZPosition = itMapZPositionReverse->second.begin(),
			itVecZHeight = itMapZHeightReverse->second.begin();
			itVecZPosition != itMapZPositionReverse->second.end();
			itVecZPosition++, itVecZHeight++)
		{
			corticalZPosition.push_back((*itVecZPosition)[0] + (*itVecZHeight)[0]);
		}
		epiCortexEndoCellZDB.insert(pair<int, vector<double> >(i, corticalZPosition));
	}

	/// Insert RsSourceEndodermisDB->circleXDB and RsSourceEndodermisDB->circleYDB;
	mapSize = epiCortexEndoCellXDB.size();
	epiCortexEndoCellXDB.insert(pair<int, vector<double> >(mapSize, RsSourceEndodermisDB->circleXDB));
	epiCortexEndoCellYDB.insert(pair<int, vector<double> >(mapSize, RsSourceEndodermisDB->circleYDB));

	vector<double> endodermisZPosition;
	for (itMapZPosition = RsSourceEndodermisDB->objectZPositionDB.begin(),
		itMapZHeight = RsSourceEndodermisDB->objectHeightDB.begin();
		itMapZPosition != RsSourceEndodermisDB->objectZPositionDB.end();
		itMapZPosition++, itMapZHeight++)
	{
		endodermisZPosition.push_back(itMapZPosition->second[0] + itMapZHeight->second[0]);
	}
	epiCortexEndoCellZDB.insert(pair<int, vector<double> >(mapSize, endodermisZPosition));

}

/** \brief EpiCortexEndoRingCellDimensionDB
 *
 * \param rsSourceEpidermisDB *RsSourceEpidermisDB->circleRadiusDB;
 * \param rsSourceCorticalDB *RsSourceCorticalDB->circleRadiusDB;
 * \param rsSourceEpidermisDB *RsSourceEndodermisDB->circleRadiusDB;

 * \param rsSourceEpidermisDB *RsSourceEpidermisDB->objectVerticalDB;
 * \param rsSourceCorticalDB *RsSourceCorticalDB->objectVerticalDB;
 * \param rsSourceEpidermisDB *RsSourceEndodermisDB->objectVerticalDB;

 * \param rsSourceEpidermisDB *RsSourceEpidermisDB->circleSegmentLengthDB;
 * \param rsSourceCorticalDB *RsSourceCorticalDB->circleSegmentLengthDB;
 * \param rsSourceEpidermisDB *RsSourceEndodermisDB->circleSegmentLengthDB;

 * \param rsSourceEpidermisDB *RsSourceEpidermisDB->circleSegmentRotateAngleDB;
 * \param rsSourceCorticalDB *RsSourceCorticalDB->circleSegmentRotateAngleDB;
 * \param rsSourceEpidermisDB *RsSourceEndodermisDB->circleSegmentRotateAngleDB;

 * \return vector<double> epiCortexEndoRingMidCentreRadiusDB;
 * \return vector<double> epiCortexEndoRingObjectVerticalDB;
 * \return map<int, vector<double> > epiCortexEndoRingObjectParallelDB;
 * \return map<int, vector<double> > epiCortexEndoCellMidRotateAngleDB;
 *
 */

 /// Combine circleRadiusDB, objectVerticalDB, circleSegmentLengthDB and circleSegmentRotateAngleDB;
void rsEpiCortexEndoWaterPathDB::EpiCortexEndoRingCellDimensionDB
(rsSourceDermisDB* RsSourceEpidermisDB,
	rsSourceCorticalDB* RsSourceCorticalDB,
	rsSourceDermisDB* RsSourceEndodermisDB)
{
	map<int, vector<double> >::reverse_iterator itMap;
	vector<double>::reverse_iterator itVecRadius;
	vector<double>::reverse_iterator itVecVertical;

	map<int, vector<double> >::iterator itMapParallel;
	vector<double>::iterator itVecParallel;
	int i;
	int mapSize;

	//////////////////////  epiCortexEndoRingMidCentreRadiusDB  ///////////////////////
	   /*****************************
	   Combine RsSourceEpidermisDB->circleRadiusDB,
			   RsSourceCorticalDB->circleRadiusDB,
			   RsSourceEndodermisDB->circleRadiusDB
		   MidCentreRadius = from the cell center(Middle cell) in that ring to circle point;
	   ******************************/

	   /// Insert RsSourceEpidermisDB;
	epiCortexEndoRingMidCentreRadiusDB.push_back(RsSourceEpidermisDB->circleRadiusDB);
	/// Insert RsSourceCorticalDB;
	for (itVecRadius = RsSourceCorticalDB->circleRadiusDB.rbegin();
		itVecRadius != RsSourceCorticalDB->circleRadiusDB.rend();
		itVecRadius++)
	{
		epiCortexEndoRingMidCentreRadiusDB.push_back(*itVecRadius);
	}
	/// Insert RsSourceEndodermisDB;
	epiCortexEndoRingMidCentreRadiusDB.push_back(RsSourceEndodermisDB->circleRadiusDB);

	//////////////////////  epiCortexEndoRingObjectVerticalDB  ///////////////////////
	   /*****************************
		Combine RsSourceEpidermisDB->objectVerticalDB,
				RsSourceCorticalDB->objectVerticalDB,
				RsSourceEndodermisDB->objectVerticalDB;
	   ******************************/

	   /// Insert RsSourceEpidermisDB->objectVerticalDB;
	epiCortexEndoRingObjectVerticalDB.push_back(RsSourceEpidermisDB->objectVerticalDB);
	/// Insert RsSourceCorticalDB->objectVerticalDB;
	for (itVecVertical = RsSourceCorticalDB->objectVerticalDB.rbegin();
		itVecVertical != RsSourceCorticalDB->objectVerticalDB.rend();
		itVecVertical++)
	{
		epiCortexEndoRingObjectVerticalDB.push_back(*itVecVertical);
	}
	/// Insert RsSourceEndodermisDB->objectVerticalDB;
	epiCortexEndoRingObjectVerticalDB.push_back(RsSourceEndodermisDB->objectVerticalDB);

	//////////////////////  epiCortexEndoRingObjectParallelDB  ///////////////////////
	   /*****************************
		Combine RsSourceEpidermisDB->circleSegmentLengthDB,
				RsSourceCorticalDB->circleSegmentLengthDB,
				RsSourceEndodermisDB->circleSegmentLengthDB;
	   ******************************/

	   /// Insert RsSourceEpidermisDB->circleSegmentLengthDB;
	epiCortexEndoRingObjectParallelDB.insert(pair<int, vector<double> >(0, RsSourceEpidermisDB->circleSegmentLengthDB));

	/// Insert RsSourceCorticalDB->circleSegmentLengthDB;
	for (itMap = RsSourceCorticalDB->circleSegmentLengthDB.rbegin(), i = 1;
		itMap != RsSourceCorticalDB->circleSegmentLengthDB.rend();
		itMap++, i++)
	{
		epiCortexEndoRingObjectParallelDB.insert(pair<int, vector<double> >(i, itMap->second));
	}

	/// Insert RsSourceEndodermisDB->circleSegmentLengthDB;
	mapSize = epiCortexEndoRingObjectParallelDB.size();
	epiCortexEndoRingObjectParallelDB.insert
	(pair<int, vector<double> >(mapSize, RsSourceEndodermisDB->circleSegmentLengthDB));

	/// fout;
 //   ofstream fout("WaterPath.txt",ios::app);
 //   fout << "epiCortexEndoRingObjectParallelDB" << endl;
	for (itMapParallel = epiCortexEndoRingObjectParallelDB.begin(), i = 0;
		itMapParallel != epiCortexEndoRingObjectParallelDB.end();
		itMapParallel++, i++)
	{
		for (itVecParallel = itMapParallel->second.begin();
			itVecParallel != itMapParallel->second.end();
			itVecParallel++)
		{
			//          fout << "ringNum: " << i << "  itVecParallel: " << *itVecParallel << endl;
		}
	}

	//////////////////////  epiCortexEndoCellMidRotateAngleDB  ///////////////////////
	   /*****************************
		Combine RsSourceEpidermisDB->circleSegmentRotateAngleDB,
				RsSourceCorticalDB->circleSegmentRotateAngleDB,
				RsSourceEndodermisDB->circleSegmentRotateAngleDB;
	   ******************************/

	   /// Insert RsSourceEpidermisDB->circleSegmentRotateAngleDB;
	epiCortexEndoCellMidRotateAngleDB.insert
	(pair<int, vector<double> >(0, RsSourceEpidermisDB->circleSegmentRotateAngleDB));

	/// Insert RsSourceCorticalDB->circleSegmentRotateAngleDB;
	for (itMap = RsSourceCorticalDB->circleSegmentRotateAngleDB.rbegin(), i = 1;
		itMap != RsSourceCorticalDB->circleSegmentRotateAngleDB.rend();
		itMap++, i++)
	{
		epiCortexEndoCellMidRotateAngleDB.insert(pair<int, vector<double> >(i, itMap->second));
	}

	/// Insert RsSourceEndodermisDB->circleSegmentRotateAngleDB;
	mapSize = epiCortexEndoCellMidRotateAngleDB.size();
	epiCortexEndoCellMidRotateAngleDB.insert
	(pair<int, vector<double> >(mapSize, RsSourceEndodermisDB->circleSegmentRotateAngleDB));

}

/** \brief EpiCortexEndoRingCentreRadiusDB
 *
 * \param rsSourceEpidermisDB *RsSourceEpidermisDB->circleRadiusDB;
 * \param rsSourceEpidermisDB *RsSourceEpidermisDB->objectVerticalDB;
 * \param rsSourceCorticalDB *RsSourceCorticalDB->circleRadiusDB;
 * \param rsSourceCorticalDB *RsSourceCorticalDB->objectVerticalDB;
 * \param rsSourceEpidermisDB *RsSourceEndodermisDB->circleRadiusDB;
 * \param rsSourceEpidermisDB *RsSourceEndodermisDB->objectVerticalDB;
 * \return vector<double> epiCortexEndoRingOuterCentreRadiusDB;
 * \return vector<double> epiCortexEndoRingInnerCentreRadiusDB;
 *
 */

void rsEpiCortexEndoWaterPathDB::EpiCortexEndoRingCentreRadiusDB
(rsSourceDermisDB* RsSourceEpidermisDB,
	rsSourceCorticalDB* RsSourceCorticalDB,
	rsSourceDermisDB* RsSourceEndodermisDB)
{
	vector<double>::iterator itVecRadius;
	vector<double>::iterator itVecVertical;

	for (itVecRadius = epiCortexEndoRingMidCentreRadiusDB.begin(),
		itVecVertical = epiCortexEndoRingObjectVerticalDB.begin();
		itVecRadius != epiCortexEndoRingMidCentreRadiusDB.end();
		itVecRadius++, itVecVertical++)
	{
		epiCortexEndoRingOuterCentreRadiusDB.push_back
		(*itVecRadius + *itVecVertical);

		epiCortexEndoRingInnerCentreRadiusDB.push_back
		(*itVecRadius - *itVecVertical);
	}
}

/** \brief EpiCortexEndoRingPerimeterDB
 *
 * \param vector<double> epiCortexEndoRingOuterCentreRadiusDB;
 * \param vector<double> epiCortexEndoRingMidCentreRadiusDB;
 * \param vector<double> epiCortexEndoRingInnerCentreRadiusDB;
 * \return vector<double> epiCortexEndoRingOuterPerimeterDB;
 * \return vector<double> epiCortexEndoRingMidPerimeterDB;
 * \return vector<double> epiCortexEndoRingInnerPerimeterDB;
 *
 */

void rsEpiCortexEndoWaterPathDB::EpiCortexEndoRingPerimeterDB()
{
	vector<double>::iterator itVec;
	double tempPerimeter;

	//   ofstream fout("WaterPath.txt",ios::app);
	//   fout << "EpiCortexEndoRingPerimeterDB" << endl;

	   /// epiCortexEndoRingOuterPerimeterDB;
	for (itVec = epiCortexEndoRingOuterCentreRadiusDB.begin();
		itVec != epiCortexEndoRingOuterCentreRadiusDB.end();
		itVec++)
	{
		tempPerimeter = CirclePerimeter(*itVec);
		epiCortexEndoRingOuterPerimeterDB.push_back(tempPerimeter);
	}

	//   fout << "epiCortexEndoRingMidPerimeterDB" << endl;
	   /// epiCortexEndoRingMidPerimeterDB;
	for (itVec = epiCortexEndoRingMidCentreRadiusDB.begin();
		itVec != epiCortexEndoRingMidCentreRadiusDB.end();
		itVec++)
	{
		tempPerimeter = CirclePerimeter(*itVec);
		epiCortexEndoRingMidPerimeterDB.push_back(tempPerimeter);
		//      fout << "tempPerimeter: " << tempPerimeter << endl;
	}

	/// epiCortexEndoRingInnerPerimeterDB;
	for (itVec = epiCortexEndoRingInnerCentreRadiusDB.begin();
		itVec != epiCortexEndoRingInnerCentreRadiusDB.end();
		itVec++)
	{
		tempPerimeter = CirclePerimeter(*itVec);
		epiCortexEndoRingInnerPerimeterDB.push_back(tempPerimeter);
	}
}
/** \brief epiCortexEndoCellHalfIntersetionAngleDB;
 *
 * \param map<int, vector<double> > epiCortexEndoRingObjectParallelDB;
 * \param vector<double> epiCortexEndoRingMidPerimeterDB;
 * \return map<int, vector<double> > epiCortexEndoCellHalfIntersetionAngleDB;
 *
 */

 /// The intersection angle between left cell and middle cell or the intersection;

void rsEpiCortexEndoWaterPathDB::EpiCortexEndoCellHalfIntersetionAngleDB()
{
	map<int, vector<double> >::iterator itMapParallel;
	vector<double>::iterator itVecPerimeter;
	vector<double>::iterator itVecParallel;

	vector<double> epiCortexEndoCellHalfIntersetionAngle;
	int i;
	double tempAngle;

	//   ofstream fout("WaterPath.txt",ios::app);
	//   fout << "EpiCortexEndoCellHalfIntersetionAngleDB" << endl;


	for (itMapParallel = epiCortexEndoRingObjectParallelDB.begin(),
		itVecPerimeter = epiCortexEndoRingMidPerimeterDB.begin(), i = 0;
		itMapParallel != epiCortexEndoRingObjectParallelDB.end();
		itMapParallel++, itVecPerimeter++, i++)
	{
		epiCortexEndoCellHalfIntersetionAngle.clear();
		for (itVecParallel = itMapParallel->second.begin();
			itVecParallel != itMapParallel->second.end();
			itVecParallel++)
		{
			//          fout << "*itVecParallel: " << *itVecParallel
			//              << "*itVecPerimeter: " << *itVecPerimeter << endl;
			tempAngle = (*itVecParallel) / (*itVecPerimeter) * 360;
			//         fout << "tempAngle: " << tempAngle << endl;
			epiCortexEndoCellHalfIntersetionAngle.push_back(tempAngle);

		}
		epiCortexEndoCellHalfIntersetionAngleDB.insert
		(pair<int, vector<double> >(i, epiCortexEndoCellHalfIntersetionAngle));

	}
}

/** \brief EpiCortexEndoCellLeftandRightRotateAngleDB;
 *
 * \param map<int, vector<double> > epiCortexEndoCellMidRotateAngleDB
 * \param map<int, vector<double> > epiCortexEndoCellHalfIntersetionAngleDB;
 * \return map<int, vector<double> > epiCortexEndoCellLeftRotateAngleDB;
 * \return map<int, vector<double> > epiCortexEndoCellRightRotateAngleDB;
 *
 */
void rsEpiCortexEndoWaterPathDB::EpiCortexEndoCellLeftandRightRotateAngleDB()
{
	map<int, vector<double> >::iterator itMapMid;
	vector<double>::iterator itVecMid;

	map<int, vector<double> >::iterator itMapIntersection;
	vector<double>::iterator itVecIntersection;

	vector<double> epiCortexEndoCellLeftRotateAngle;
	vector<double> epiCortexEndoCellRightRotateAngle;
	int i;
	double tempLeftAngle;
	double tempRightAngle;

	//   ofstream fout("WaterPath.txt",ios::app);
	//   fout << "EpiCortexEndoCellLeftandRightRotateAngleDB" << endl;

	for (itMapMid = epiCortexEndoCellMidRotateAngleDB.begin(),
		itMapIntersection = epiCortexEndoCellHalfIntersetionAngleDB.begin(), i = 0;
		itMapMid != epiCortexEndoCellMidRotateAngleDB.end();
		itMapMid++, itMapIntersection++, i++)
	{
		epiCortexEndoCellLeftRotateAngle.clear();
		epiCortexEndoCellRightRotateAngle.clear();
		for (itVecMid = itMapMid->second.begin(), itVecIntersection = itMapIntersection->second.begin();
			itVecMid != itMapMid->second.end();
			itVecMid++, itVecIntersection++)
		{
			tempLeftAngle = *itVecMid - *itVecIntersection;
			tempRightAngle = *itVecMid + *itVecIntersection;
			epiCortexEndoCellLeftRotateAngle.push_back(tempLeftAngle);
			epiCortexEndoCellRightRotateAngle.push_back(tempRightAngle);
			//         fout << "i: " << i << "  tempLeftAngle: " << tempLeftAngle
			//              << "  tempRightAngle: " << tempRightAngle << endl;
		}
		epiCortexEndoCellLeftRotateAngleDB.insert
		(pair<int, vector<double> >(i, epiCortexEndoCellLeftRotateAngle));
		epiCortexEndoCellRightRotateAngleDB.insert
		(pair<int, vector<double> >(i, epiCortexEndoCellRightRotateAngle));
	}
}

/** \brief EpiCortexEndoCellXYDB;
 *
 * \param map<int, vector<double> > epiCortexEndoCellLeftRotateAngleDB;
 * \param map<int, vector<double> > epiCortexEndoCellRightRotateAngleDB;
 * \param map<int, vector<double> > epiCortexEndoCellMidRotateAngleDB;
 * \param vector<double> epiCortexEndoRingOuterCentreRadiusDB;
 * \param vector<double> epiCortexEndoRingMidCentreRadiusDB;
 * \param vector<double> epiCortexEndoRingInnerCentreRadiusDB;
 * \return map<int, vector<double> > epiCortexEndoCellLeftRadialOuterXDB
 * \return map<int, vector<double> > epiCortexEndoCellLeftRadialOuterYDB
 * \return map<int, vector<double> > epiCortexEndoCellLeftRadialMidXDB
 * \return map<int, vector<double> > epiCortexEndoCellLeftRadialMidYDB
 * \return map<int, vector<double> > epiCortexEndoCellLeftRadialInnerXDB
 * \return map<int, vector<double> > epiCortexEndoCellLeftRadialInnerYDB
 * \return map<int, vector<double> > epiCortexEndoCellRightRadialOuterXDB
 * \return map<int, vector<double> > epiCortexEndoCellRightRadialOuterYDB
 * \return map<int, vector<double> > epiCortexEndoCellRightRadialMidXDB
 * \return map<int, vector<double> > epiCortexEndoCellRightRadialMidYDB
 * \return map<int, vector<double> > epiCortexEndoCellRightRadialInnerXDB
 * \return map<int, vector<double> > epiCortexEndoCellRightRadialInnerYDB
 * \return map<int, vector<double> > epiCortexEndoCellMidRadialOuterXDB
 * \return map<int, vector<double> > epiCortexEndoCellMidRadialOuterYDB
 * \return map<int, vector<double> > epiCortexEndoCellMidRadialMidXDB
 * \return map<int, vector<double> > epiCortexEndoCellMidRadialMidYDB
 * \return map<int, vector<double> > epiCortexEndoCellMidRadialInnerXDB
 * \return map<int, vector<double> > epiCortexEndoCellMidRadialInnerYDB
 *
 */

void rsEpiCortexEndoWaterPathDB::EpiCortexEndoCellXYDB()
{
	map<int, vector<double> >::iterator itMapLeft;
	map<int, vector<double> >::iterator itMapRight;
	map<int, vector<double> >::iterator itMapMid;

	vector<double>::iterator itVecLeft;
	vector<double>::iterator itVecRight;
	vector<double>::iterator itVecMid;

	vector<double>::iterator itVecOuterRadius;
	vector<double>::iterator itVecMidRadius;
	vector<double>::iterator itVecInnerRadius;

	vector<double> epiCortexEndoCellLeftRadialOuterX;
	vector<double> epiCortexEndoCellLeftRadialOuterY;
	vector<double> epiCortexEndoCellLeftRadialMidX;
	vector<double> epiCortexEndoCellLeftRadialMidY;
	vector<double> epiCortexEndoCellLeftRadialInnerX;
	vector<double> epiCortexEndoCellLeftRadialInnerY;

	vector<double> epiCortexEndoCellRightRadialOuterX;
	vector<double> epiCortexEndoCellRightRadialOuterY;
	vector<double> epiCortexEndoCellRightRadialMidX;
	vector<double> epiCortexEndoCellRightRadialMidY;
	vector<double> epiCortexEndoCellRightRadialInnerX;
	vector<double> epiCortexEndoCellRightRadialInnerY;

	vector<double> epiCortexEndoCellMidRadialOuterX;
	vector<double> epiCortexEndoCellMidRadialOuterY;
	vector<double> epiCortexEndoCellMidRadialMidX;
	vector<double> epiCortexEndoCellMidRadialMidY;
	vector<double> epiCortexEndoCellMidRadialInnerX;
	vector<double> epiCortexEndoCellMidRadialInnerY;

	int i;
	double tempOuterX;
	double tempMidX;
	double tempInnerX;
	double tempOuterY;
	double tempMidY;
	double tempInnerY;

	/// Left;
	for (itMapLeft = epiCortexEndoCellLeftRotateAngleDB.begin(),
		itVecOuterRadius = epiCortexEndoRingOuterCentreRadiusDB.begin(),
		itVecMidRadius = epiCortexEndoRingMidCentreRadiusDB.begin(),
		itVecInnerRadius = epiCortexEndoRingInnerCentreRadiusDB.begin(), i = 0;
		itMapLeft != epiCortexEndoCellLeftRotateAngleDB.end();
		itMapLeft++, itVecOuterRadius++, itVecMidRadius++, itVecInnerRadius++, i++)
	{
		epiCortexEndoCellLeftRadialOuterX.clear();
		epiCortexEndoCellLeftRadialMidX.clear();
		epiCortexEndoCellLeftRadialInnerX.clear();
		epiCortexEndoCellLeftRadialOuterY.clear();
		epiCortexEndoCellLeftRadialMidY.clear();
		epiCortexEndoCellLeftRadialInnerY.clear();
		for (itVecLeft = itMapLeft->second.begin();
			itVecLeft != itMapLeft->second.end();
			itVecLeft++)
		{  /// X;
			tempOuterX = *itVecOuterRadius * cos(-2 * M_PI * (*itVecLeft / 360));
			tempMidX = *itVecMidRadius * cos(-2 * M_PI * (*itVecLeft / 360));
			tempInnerX = *itVecInnerRadius * cos(-2 * M_PI * (*itVecLeft / 360));
			/// Y;
			tempOuterY = *itVecOuterRadius * sin(-2 * M_PI * (*itVecLeft / 360));
			tempMidY = *itVecMidRadius * sin(-2 * M_PI * (*itVecLeft / 360));
			tempInnerY = *itVecInnerRadius * sin(-2 * M_PI * (*itVecLeft / 360));

			epiCortexEndoCellLeftRadialOuterX.push_back(tempOuterX);
			epiCortexEndoCellLeftRadialMidX.push_back(tempMidX);
			epiCortexEndoCellLeftRadialInnerX.push_back(tempInnerX);

			epiCortexEndoCellLeftRadialOuterY.push_back(tempOuterY);
			epiCortexEndoCellLeftRadialMidY.push_back(tempMidY);
			epiCortexEndoCellLeftRadialInnerY.push_back(tempInnerY);
		}
		epiCortexEndoCellLeftRadialOuterXDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellLeftRadialOuterX));
		epiCortexEndoCellLeftRadialMidXDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellLeftRadialMidX));
		epiCortexEndoCellLeftRadialInnerXDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellLeftRadialInnerX));
		epiCortexEndoCellLeftRadialOuterYDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellLeftRadialOuterY));
		epiCortexEndoCellLeftRadialMidYDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellLeftRadialMidY));
		epiCortexEndoCellLeftRadialInnerYDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellLeftRadialInnerY));
	}

	/// Right;
	for (itMapRight = epiCortexEndoCellRightRotateAngleDB.begin(),
		itVecOuterRadius = epiCortexEndoRingOuterCentreRadiusDB.begin(),
		itVecMidRadius = epiCortexEndoRingMidCentreRadiusDB.begin(),
		itVecInnerRadius = epiCortexEndoRingInnerCentreRadiusDB.begin(), i = 0;
		itMapRight != epiCortexEndoCellRightRotateAngleDB.end();
		itMapRight++, itVecOuterRadius++, itVecMidRadius++, itVecInnerRadius++, i++)
	{
		epiCortexEndoCellRightRadialOuterX.clear();
		epiCortexEndoCellRightRadialMidX.clear();
		epiCortexEndoCellRightRadialInnerX.clear();
		epiCortexEndoCellRightRadialOuterY.clear();
		epiCortexEndoCellRightRadialMidY.clear();
		epiCortexEndoCellRightRadialInnerY.clear();
		for (itVecRight = itMapRight->second.begin();
			itVecRight != itMapRight->second.end();
			itVecRight++)
		{  /// X;
			tempOuterX = *itVecOuterRadius * cos(-2 * M_PI * (*itVecRight / 360));
			tempMidX = *itVecMidRadius * cos(-2 * M_PI * (*itVecRight / 360));
			tempInnerX = *itVecInnerRadius * cos(-2 * M_PI * (*itVecRight / 360));
			/// Y;
			tempOuterY = *itVecOuterRadius * sin(-2 * M_PI * (*itVecRight / 360));
			tempMidY = *itVecMidRadius * sin(-2 * M_PI * (*itVecRight / 360));
			tempInnerY = *itVecInnerRadius * sin(-2 * M_PI * (*itVecRight / 360));

			epiCortexEndoCellRightRadialOuterX.push_back(tempOuterX);
			epiCortexEndoCellRightRadialMidX.push_back(tempMidX);
			epiCortexEndoCellRightRadialInnerX.push_back(tempInnerX);

			epiCortexEndoCellRightRadialOuterY.push_back(tempOuterY);
			epiCortexEndoCellRightRadialMidY.push_back(tempMidY);
			epiCortexEndoCellRightRadialInnerY.push_back(tempInnerY);
		}
		epiCortexEndoCellRightRadialOuterXDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellRightRadialOuterX));
		epiCortexEndoCellRightRadialMidXDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellRightRadialMidX));
		epiCortexEndoCellRightRadialInnerXDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellRightRadialInnerX));
		epiCortexEndoCellRightRadialOuterYDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellRightRadialOuterY));
		epiCortexEndoCellRightRadialMidYDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellRightRadialMidY));
		epiCortexEndoCellRightRadialInnerYDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellRightRadialInnerY));
	}

	/// Mid;

 //   ofstream fout("WaterPath.txt",ios::app);
 //   fout << "EpiCortexEndoCellXYDB" << endl;
 //   fout << "Mid" << endl;

	for (itMapMid = epiCortexEndoCellMidRotateAngleDB.begin(),
		itVecOuterRadius = epiCortexEndoRingOuterCentreRadiusDB.begin(),
		itVecMidRadius = epiCortexEndoRingMidCentreRadiusDB.begin(),
		itVecInnerRadius = epiCortexEndoRingInnerCentreRadiusDB.begin(), i = 0;
		itMapMid != epiCortexEndoCellMidRotateAngleDB.end();
		itMapMid++, itVecOuterRadius++, itVecMidRadius++, itVecInnerRadius++, i++)
	{
		epiCortexEndoCellMidRadialOuterX.clear();
		epiCortexEndoCellMidRadialMidX.clear();
		epiCortexEndoCellMidRadialInnerX.clear();

		epiCortexEndoCellMidRadialOuterY.clear();
		epiCortexEndoCellMidRadialMidY.clear();
		epiCortexEndoCellMidRadialInnerY.clear();
		for (itVecMid = itMapMid->second.begin();
			itVecMid != itMapMid->second.end();
			itVecMid++)
		{  /// X;
			tempOuterX = *itVecOuterRadius * cos(-2 * M_PI * (*itVecMid / 360));
			tempMidX = *itVecMidRadius * cos(-2 * M_PI * (*itVecMid / 360));
			tempInnerX = *itVecInnerRadius * cos(-2 * M_PI * (*itVecMid / 360));
			/// Y;
			tempOuterY = *itVecOuterRadius * sin(-2 * M_PI * (*itVecMid / 360));
			tempMidY = *itVecMidRadius * sin(-2 * M_PI * (*itVecMid / 360));
			tempInnerY = *itVecInnerRadius * sin(-2 * M_PI * (*itVecMid / 360));

			//         fout << " tempOuterY: " << tempOuterY << endl;
			epiCortexEndoCellMidRadialOuterX.push_back(tempOuterX);
			epiCortexEndoCellMidRadialMidX.push_back(tempMidX);
			epiCortexEndoCellMidRadialInnerX.push_back(tempInnerX);

			epiCortexEndoCellMidRadialOuterY.push_back(tempOuterY);
			epiCortexEndoCellMidRadialMidY.push_back(tempMidY);
			epiCortexEndoCellMidRadialInnerY.push_back(tempInnerY);
		}
		epiCortexEndoCellMidRadialOuterXDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellMidRadialOuterX));
		epiCortexEndoCellMidRadialMidXDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellMidRadialMidX));
		epiCortexEndoCellMidRadialInnerXDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellMidRadialInnerX));
		epiCortexEndoCellMidRadialOuterYDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellMidRadialOuterY));
		epiCortexEndoCellMidRadialMidYDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellMidRadialMidY));
		epiCortexEndoCellMidRadialInnerYDB.insert(pair<int, vector<double> >(i, epiCortexEndoCellMidRadialInnerY));
	}
}




/** \brief EpiCortexEndoCellMarkerDB;
 *
 * \param map<int, vector<double> > epiCortexEndoCellLeftRotateAngleDB;
 * \param map<int, vector<double> > epiCortexEndoCellMidRotateAngleDB;
 * \return map<int, vector<double> > epiCortexEndoApoplastCellMarkerDB;
 * \return map<int, vector<double> > epiCortexEndoSymplastCellMarkerDB;
 *
 */

void rsEpiCortexEndoWaterPathDB::EpiCortexEndoCellMarkerDB()
{
	map<int, vector<double> >::iterator itMapLeft;
	map<int, vector<double> >::iterator itMapMid;

	vector<double>::iterator itVecLeft;
	vector<double>::iterator itVecMid;

	vector<double>::iterator itVecEpidermisLeftStart;
	vector<double>::iterator itVecEpidermisMidStart;

	vector<double> epiCortexEndoApoplastCellMarker;
	vector<double> epiCortexEndoApoplastCellMarkerLeftRightIndex;
	vector<double> epiCortexEndoSymplastCellMarker;

	vector<double> epidermisLeftTempDB;
	vector<double> epidermisMidTempDB;

	double tempAngle;
	double tempStart;
	double tempMin;
	double tempGap;
	double tempMidGap;
	double tempLeftGap;
	double tempRightGap;
	int i;
	int tempRecord;
	int tempMarker;
	int leftRightIndex;
	int ringNum;

	//   ofstream fout("WaterPath.txt",ios::app);
	//   fout << "EpiCortexEndoCellMarkerDB" << endl;
	//
	//   fout << "Apoplast" << endl;

	epidermisLeftTempDB = epiCortexEndoCellLeftRotateAngleDB[0];


	/******************
	 Apoplast;
	*******************/
	for (itVecEpidermisLeftStart = epidermisLeftTempDB.begin(), i = 0;
		itVecEpidermisLeftStart != epidermisLeftTempDB.end();
		itVecEpidermisLeftStart++, i++)
	{
		tempStart = *itVecEpidermisLeftStart;
		//      fout << "i: " << i <<  "  tempStart: " << tempStart << endl;
		epiCortexEndoApoplastCellMarker.clear();
		epiCortexEndoApoplastCellMarkerLeftRightIndex.clear();
		for (itMapLeft = epiCortexEndoCellLeftRotateAngleDB.begin(), ringNum = 0;
			itMapLeft != epiCortexEndoCellLeftRotateAngleDB.end();
			itMapLeft++, ringNum++)
		{
			tempMin = 10000000;

			for (itVecLeft = itMapLeft->second.begin(), tempRecord = 0;
				itVecLeft != itMapLeft->second.end();
				itVecLeft++, tempRecord++)
			{
				tempGap = fabs(fabs(tempStart) - fabs(*itVecLeft));
				if (tempGap > 180)
				{
					tempLeftGap = 360 - tempGap;
				}
				else
				{
					tempLeftGap = tempGap;
				}

				if (tempMin > tempLeftGap)
				{
					tempMarker = tempRecord;
					tempMin = tempLeftGap;
					tempAngle = *itVecLeft;
				}
			}
			/// leftRightIndex: 0 = Left;  1 = Right;
			leftRightIndex = 0;
			/// Calculate the gap inside the cell through the comparation between left and right rotate angle;
			tempGap = fabs(fabs(tempStart) - fabs(epiCortexEndoCellRightRotateAngleDB[ringNum][tempMarker]));
			if (tempGap > 180)
			{
				tempRightGap = 360 - tempGap;
			}
			else
			{
				tempRightGap = tempGap;
			}

			if (tempMin > tempRightGap)
			{
				tempAngle = epiCortexEndoCellRightRotateAngleDB[ringNum][tempMarker];
				leftRightIndex = 1;
			}

			//         fout << "i: " << i << "  ringNum: " << ringNum
			//              << "  tempMarker: " << tempMarker
			//              << " leftRightIndex: " << leftRightIndex << endl;
			tempStart = tempAngle;
			epiCortexEndoApoplastCellMarker.push_back(tempMarker);
			epiCortexEndoApoplastCellMarkerLeftRightIndex.push_back(leftRightIndex);
		}
		epiCortexEndoApoplastCellMarkerDB.insert
		(pair<int, vector<double> >(i, epiCortexEndoApoplastCellMarker));
		epiCortexEndoApoplastCellMarkerLeftRightIndexDB.insert
		(pair<int, vector<double> >(i, epiCortexEndoApoplastCellMarkerLeftRightIndex));
	}

	/******************
	 Symplast;
	*******************/
	//   fout << endl;
	//   fout << "Symplast" << endl;
	epidermisMidTempDB = epiCortexEndoCellMidRotateAngleDB[0];

	for (itVecEpidermisMidStart = epidermisMidTempDB.begin(), i = 0;
		itVecEpidermisMidStart != epidermisMidTempDB.end();
		itVecEpidermisMidStart++, i++)
	{
		tempStart = *itVecEpidermisMidStart;
		//      fout << "i: " << i <<  "  tempStart: " << tempStart << endl;
		epiCortexEndoSymplastCellMarker.clear();
		for (itMapMid = epiCortexEndoCellMidRotateAngleDB.begin();
			itMapMid != epiCortexEndoCellMidRotateAngleDB.end();
			itMapMid++)
		{
			tempMin = 10000000;
			for (itVecMid = itMapMid->second.begin(), tempRecord = 0;
				itVecMid != itMapMid->second.end();
				itVecMid++, tempRecord++)
			{
				tempGap = fabs(tempStart - *itVecMid);
				if (tempGap > 180)
				{
					tempMidGap = 360 - tempGap;
				}
				else
				{
					tempMidGap = tempGap;
				}

				if (tempMin > tempMidGap)
				{
					tempMarker = tempRecord;
					tempMin = tempMidGap;
					tempAngle = *itVecMid;
				}
			}
			//         fout << "i: " << i << "  ringNum: " << ringNum
			//              << "  tempMin: " << tempMin
			//              << "  tempMarker: " << tempMarker << endl;
			tempStart = tempAngle;
			epiCortexEndoSymplastCellMarker.push_back(tempMarker);
		}
		epiCortexEndoSymplastCellMarkerDB.insert(pair<int, vector<double> >(i, epiCortexEndoSymplastCellMarker));
	}
}

/** \brief EpiCortexEndoPathXYDB;
 *
 * \param map<int, vector<double> > epiCortexEndoCellLeftRadialOuterXDB
 * \param map<int, vector<double> > epiCortexEndoCellLeftRadialOuterYDB
 * \param map<int, vector<double> > epiCortexEndoCellLeftRadialMidXDB
 * \param map<int, vector<double> > epiCortexEndoCellLeftRadialMidYDB
 * \param map<int, vector<double> > epiCortexEndoCellLeftRadialInnerXDB
 * \param map<int, vector<double> > epiCortexEndoCellLeftRadialInnerYDB
 * \param map<int, vector<double> > epiCortexEndoCellMidRadialOuterXDB
 * \param map<int, vector<double> > epiCortexEndoCellMidRadialOuterYDB
 * \param map<int, vector<double> > epiCortexEndoCellMidRadialMidXDB
 * \param map<int, vector<double> > epiCortexEndoCellMidRadialMidYDB
 * \param map<int, vector<double> > epiCortexEndoCellMidRadialInnerXDB
 * \param map<int, vector<double> > epiCortexEndoCellMidRadialInnerYDB
 * \param map<int, vector<double> > epiCortexEndoApoplastCellMarkerDB;
 * \param map<int, vector<double> > epiCortexEndoSymplastCellMarkerDB;
 * \return map<int, vector<double> > epiCortexEndoApoplastXDB;
 * \return map<int, vector<double> > epiCortexEndoApoplastYDB;
 * \return map<int, vector<double> > epiCortexEndoSymplastXDB;
 * \return map<int, vector<double> > epiCortexEndoSymplastYDB;
 *
 */

void rsEpiCortexEndoWaterPathDB::EpiCortexEndoPathXYDB()
{
	map<int, vector<double> >::iterator itMapApoplast;
	map<int, vector<double> >::iterator itMapApoplastLeftRightIndex;
	map<int, vector<double> >::iterator itMapSymplast;

	vector<double>::iterator itVecApoplast;
	vector<double>::iterator itVecApoplastLeftRightIndex;
	vector<double>::iterator itVecSymplast;

	vector<double> epiCortexEndoApoplastX;
	vector<double> epiCortexEndoApoplastY;
	vector<double> epiCortexEndoApoplastZ;
	vector<double> epiCortexEndoSymplastX;
	vector<double> epiCortexEndoSymplastY;
	vector<double> epiCortexEndoSymplastZ;

	int i;
	int ringNum;
	double outerX;
	double midX;
	double innerX;

	double outerY;
	double midY;
	double innerY;

	double sameZ;

	//   ofstream fout("WaterPath.txt",ios::app);
	//   fout << "EpiCortexEndoPathXYDB" << endl;

	   /// Apoplast;
	//   fout << "Apoplast" << endl;

	for (itMapApoplast = epiCortexEndoApoplastCellMarkerDB.begin(),
		itMapApoplastLeftRightIndex = epiCortexEndoApoplastCellMarkerLeftRightIndexDB.begin(), i = 0;
		itMapApoplast != epiCortexEndoApoplastCellMarkerDB.end();
		itMapApoplast++, itMapApoplastLeftRightIndex++, i++)
	{
		epiCortexEndoApoplastX.clear();
		epiCortexEndoApoplastY.clear();
		epiCortexEndoApoplastZ.clear();
		for (itVecApoplast = itMapApoplast->second.begin(),
			itVecApoplastLeftRightIndex = itMapApoplastLeftRightIndex->second.begin(), ringNum = 0;
			itVecApoplast != itMapApoplast->second.end();
			itVecApoplast++, itVecApoplastLeftRightIndex++, ringNum++)
		{
			if (*itVecApoplastLeftRightIndex == 0)
			{
				outerX = epiCortexEndoCellLeftRadialOuterXDB[ringNum][*itVecApoplast];
				midX = epiCortexEndoCellLeftRadialMidXDB[ringNum][*itVecApoplast];
				innerX = epiCortexEndoCellLeftRadialInnerXDB[ringNum][*itVecApoplast];
				outerY = epiCortexEndoCellLeftRadialOuterYDB[ringNum][*itVecApoplast];
				midY = epiCortexEndoCellLeftRadialMidYDB[ringNum][*itVecApoplast];
				innerY = epiCortexEndoCellLeftRadialInnerYDB[ringNum][*itVecApoplast];
			}
			else
			{
				outerX = epiCortexEndoCellRightRadialOuterXDB[ringNum][*itVecApoplast];
				midX = epiCortexEndoCellRightRadialMidXDB[ringNum][*itVecApoplast];
				innerX = epiCortexEndoCellRightRadialInnerXDB[ringNum][*itVecApoplast];
				outerY = epiCortexEndoCellRightRadialOuterYDB[ringNum][*itVecApoplast];
				midY = epiCortexEndoCellRightRadialMidYDB[ringNum][*itVecApoplast];
				innerY = epiCortexEndoCellRightRadialInnerYDB[ringNum][*itVecApoplast];
			}

			sameZ = epiCortexEndoCellZDB[ringNum][*itVecApoplast];
			//         fout << " sameZ: " << sameZ << endl;
			epiCortexEndoApoplastX.push_back(outerX);
			epiCortexEndoApoplastX.push_back(midX);
			epiCortexEndoApoplastX.push_back(innerX);

			epiCortexEndoApoplastY.push_back(outerY);
			epiCortexEndoApoplastY.push_back(midY);
			epiCortexEndoApoplastY.push_back(innerY);

			epiCortexEndoApoplastZ.push_back(sameZ);
			epiCortexEndoApoplastZ.push_back(sameZ);
			epiCortexEndoApoplastZ.push_back(sameZ);
		}
		epiCortexEndoApoplastXDB.insert(pair<int, vector<double> >(i, epiCortexEndoApoplastX));
		epiCortexEndoApoplastYDB.insert(pair<int, vector<double> >(i, epiCortexEndoApoplastY));
		epiCortexEndoApoplastZDB.insert(pair<int, vector<double> >(i, epiCortexEndoApoplastZ));
	}


	/// Symplast;

 //   fout << "Symplast" << endl;

	for (itMapSymplast = epiCortexEndoSymplastCellMarkerDB.begin(), i = 0;
		itMapSymplast != epiCortexEndoSymplastCellMarkerDB.end();
		itMapSymplast++, i++)
	{
		epiCortexEndoSymplastX.clear();
		epiCortexEndoSymplastY.clear();
		epiCortexEndoSymplastZ.clear();
		for (itVecSymplast = itMapSymplast->second.begin(), ringNum = 0;
			itVecSymplast != itMapSymplast->second.end();
			itVecSymplast++, ringNum++)
		{
			outerX = epiCortexEndoCellMidRadialOuterXDB[ringNum][*itVecSymplast];
			midX = epiCortexEndoCellMidRadialMidXDB[ringNum][*itVecSymplast];
			innerX = epiCortexEndoCellMidRadialInnerXDB[ringNum][*itVecSymplast];
			outerY = epiCortexEndoCellMidRadialOuterYDB[ringNum][*itVecSymplast];
			midY = epiCortexEndoCellMidRadialMidYDB[ringNum][*itVecSymplast];
			innerY = epiCortexEndoCellMidRadialInnerYDB[ringNum][*itVecSymplast];

			//         fout << "i: " << i << "  ringNum: " << ringNum
			//              << " cellMarker: " << *itVecSymplast
			//              << "  outerX: " << outerX
			//              << "  midX: " << midX
			//              << "  innerX: " << innerX
			//              << "  outerY: " << outerY
			//              << "  midY: " << midY
			//              << "  innerY: " << innerY
			//              << endl;
			sameZ = epiCortexEndoCellZDB[ringNum][*itVecSymplast];

			epiCortexEndoSymplastX.push_back(outerX);
			epiCortexEndoSymplastX.push_back(midX);
			epiCortexEndoSymplastX.push_back(innerX);
			epiCortexEndoSymplastY.push_back(outerY);
			epiCortexEndoSymplastY.push_back(midY);
			epiCortexEndoSymplastY.push_back(innerY);

			epiCortexEndoSymplastZ.push_back(sameZ);
			epiCortexEndoSymplastZ.push_back(sameZ);
			epiCortexEndoSymplastZ.push_back(sameZ);
		}
		epiCortexEndoSymplastXDB.insert(pair<int, vector<double> >(i, epiCortexEndoSymplastX));
		epiCortexEndoSymplastYDB.insert(pair<int, vector<double> >(i, epiCortexEndoSymplastY));
		epiCortexEndoSymplastZDB.insert(pair<int, vector<double> >(i, epiCortexEndoSymplastZ));
	}

}
/** \brief DeleteCoincidentPoints
 *
 * \param map<int, vector<double> > epiCortexEndoSymplastXDB;
 * \param map<int, vector<double> > epiCortexEndoSymplastYDB;
 *
 */
void rsEpiCortexEndoWaterPathDB::RecordCoincidentPoints()
{  /// record the position of the coincident points in the epiCortexEndoSymplastXDB and epiCortexEndoSymplastYDB;

	vector<int> recordCoincidentPointsPosition;

	map<int, vector<double> >::iterator itMapSymplastX;
	vector<double>::iterator itVecSymplastX;

	int tempRecordPosition;
	int pointPosition;
	int i;
	double tempPoint;
	double tempSequencePoint;
	double tempMinus;
	//   ofstream fout("WaterPath.txt",ios::app);
	//   fout << "RecordCoincidentPoints" << endl;

	for (itMapSymplastX = epiCortexEndoSymplastXDB.begin(), i = 0;
		itMapSymplastX != epiCortexEndoSymplastXDB.end();
		itMapSymplastX++, i++)
	{
		tempPoint = epiCortexEndoSymplastXDB[i].front();
		recordCoincidentPointsPosition.clear();
		for (itVecSymplastX = itMapSymplastX->second.begin() + 1, pointPosition = 1;
			itVecSymplastX != itMapSymplastX->second.end();
			itVecSymplastX++, pointPosition++)
		{
			tempSequencePoint = *itVecSymplastX;
			tempMinus = tempPoint - tempSequencePoint;
			//         fout << "tempPoint: " << tempPoint
			//              << " *itVecSymplastX: " << tempSequencePoint
			//              << " tempMinus: " << tempMinus
			//              << " pointPosition: " << pointPosition << endl;

			if (fabs(tempMinus) < 0.0001)
			{
				tempRecordPosition = pointPosition;
				recordCoincidentPointsPosition.push_back(tempRecordPosition);
				//            fout << " i: " << i
				//                 << " tempRecordPosition: " << tempRecordPosition
				//                 << " tempPoint: " << tempPoint << endl;
			}
			tempPoint = tempSequencePoint;
		}
		recordCoincidentPointsPositionDB.insert(pair<int, vector<int> >(i, recordCoincidentPointsPosition));
	}
}

void rsEpiCortexEndoWaterPathDB::DeleteCoincidentPoints()
{  /// delete the position of the coincident points in the epiCortexEndoSymplastXDB and epiCortexEndoSymplastYDB;

	vector<int>::reverse_iterator itVec;
	map<int, vector<int> >::reverse_iterator itMap;
	int j;
	int i;
	//   ofstream fout("WaterPath.txt",ios::app);
	//   fout << "DeleteCoincidentPoints" << endl;
	for (itMap = recordCoincidentPointsPositionDB.rbegin();
		itMap != recordCoincidentPointsPositionDB.rend();
		itMap++)
	{
		i = (*itMap).first;
		for (itVec = (*itMap).second.rbegin();
			itVec != (*itMap).second.rend();
			itVec++)
		{
			j = *itVec;
			//         fout << "i: " << i << " j: " << j << endl;
			epiCortexEndoSymplastXDB[i].erase(epiCortexEndoSymplastXDB[i].begin() + j - 1);
			epiCortexEndoSymplastYDB[i].erase(epiCortexEndoSymplastYDB[i].begin() + j - 1);
			epiCortexEndoSymplastZDB[i].erase(epiCortexEndoSymplastZDB[i].begin() + j - 1);
		}
	}
}



/** \brief
 *
 * \param map<int, vector<double> > epiCortexEndoApoplastXDB;
 * \param map<int, vector<double> > epiCortexEndoSymplastXDB;
 * \return map<int, vector<double> > epiCortexEndoApoplastUpZDB;
 * \return map<int, vector<double> > epiCortexEndoApoplastDownZDB;
 * \return map<int, vector<double> > epiCortexEndoSymplastUpZDB;
 * \return map<int, vector<double> > epiCortexEndoSymplastDownZDB;
 *
 */

void rsEpiCortexEndoWaterPathDB::EpiCortexEndoPathZDB()
{
	map<int, vector<double> >::iterator itMapApoplast;
	map<int, vector<double> >::iterator itMapSymplast;

	vector<double>::iterator itVecApoplast;
	vector<double>::iterator itVecSymplast;

	vector<double> epiCortexEndoApoplastUpZ;
	vector<double> epiCortexEndoApoplastDownZ;

	vector<double> epiCortexEndoSymplastUpZ;
	vector<double> epiCortexEndoSymplastDownZ;

	int i;
	double up = 335;
	double down = -200;

	//   ofstream fout("WaterPath.txt",ios::app);
	//   fout << "EpiCortexEndoPathZDB" << endl;

	   /// Apoplast;

	for (itMapApoplast = epiCortexEndoApoplastXDB.begin(), i = 0;
		itMapApoplast != epiCortexEndoApoplastXDB.end();
		itMapApoplast++, i++)
	{
		epiCortexEndoApoplastUpZ.clear();
		epiCortexEndoApoplastDownZ.clear();
		for (itVecApoplast = itMapApoplast->second.begin();
			itVecApoplast != itMapApoplast->second.end();
			itVecApoplast++)
		{
			epiCortexEndoApoplastUpZ.push_back(up);
			epiCortexEndoApoplastDownZ.push_back(down);
		}
		epiCortexEndoApoplastUpZDB.insert(pair<int, vector<double> >(i, epiCortexEndoApoplastUpZ));
		epiCortexEndoApoplastDownZDB.insert(pair<int, vector<double> >(i, epiCortexEndoApoplastDownZ));
	}

	/// Symplast;

	for (itMapSymplast = epiCortexEndoSymplastXDB.begin(), i = 0;
		itMapSymplast != epiCortexEndoSymplastXDB.end();
		itMapSymplast++, i++)
	{
		epiCortexEndoSymplastUpZ.clear();
		epiCortexEndoSymplastDownZ.clear();
		for (itVecSymplast = itMapSymplast->second.begin();
			itVecSymplast != itMapSymplast->second.end();
			itVecSymplast++)
		{
			epiCortexEndoSymplastUpZ.push_back(up);
			epiCortexEndoSymplastDownZ.push_back(down);
		}
		epiCortexEndoSymplastUpZDB.insert(pair<int, vector<double> >(i, epiCortexEndoSymplastUpZ));
		epiCortexEndoSymplastDownZDB.insert(pair<int, vector<double> >(i, epiCortexEndoSymplastDownZ));

	}
}

/** \brief
 *
 * \param map<int, vector<double> > epiCortexEndoApoplastXDB;
 * \param map<int, vector<double> > epiCortexEndoApoplastYDB;
 * \param map<int, vector<double> > epiCortexEndoSymplastXDB;
 * \param map<int, vector<double> > epiCortexEndoSymplastYDB;
 * \return vector<double> pathLengthDB;
 * \return double apoplastPathLengthTotal;
 * \return double averagePathLength;
 * \return double longestPathLength;
 * \return double shortestPathLength;
 * \return double deviationPathLength;
 *
 */

void rsEpiCortexEndoWaterPathDB::EpiCortexEndoPathLengthDB()
{
	map<int, vector<double> >::iterator itMapApoplastX;
	map<int, vector<double> >::iterator itMapSymplastX;
	map<int, vector<double> >::iterator itMapApoplastY;
	map<int, vector<double> >::iterator itMapSymplastY;

	vector<double>::iterator itVecApoplastX;
	vector<double>::iterator itVecSymplastX;
	vector<double>::iterator itVecApoplastY;
	vector<double>::iterator itVecSymplastY;

	int i;
	double tempLength;
	double tempLengthMin;
	double tempLengthMax;
	double tempLengthSum;


	double xFront;
	double yFront;

	/// Apoplast;
	apoplastPathLengthTotal = 0;
	tempLengthMin = 100000;
	tempLengthMax = 0;

	for (itMapApoplastX = epiCortexEndoApoplastXDB.begin(),
		itMapApoplastY = epiCortexEndoApoplastYDB.begin(), i = 0;
		itMapApoplastX != epiCortexEndoApoplastXDB.end();
		itMapApoplastX++, itMapApoplastY++, i++)
	{
		tempLengthSum = 0;

		xFront = itMapApoplastX->second.front();
		yFront = itMapApoplastY->second.front();
		for (itVecApoplastX = itMapApoplastX->second.begin() + 1,
			itVecApoplastY = itMapApoplastY->second.begin() + 1;
			itVecApoplastX != itMapApoplastX->second.end();
			itVecApoplastX++, itVecApoplastY++)
		{
			tempLength = pow(pow(xFront - *itVecApoplastX, 2) + pow(yFront - *itVecApoplastY, 2), 0.5);
			tempLengthSum += tempLength;
			xFront = *itVecApoplastX;
			yFront = *itVecApoplastY;
		}

		/// Min;
		if (tempLengthMin > tempLengthSum)
		{
			tempLengthMin = tempLengthSum;
		}
		/// Max
		if (tempLengthMax < tempLengthSum)
		{
			tempLengthMax = tempLengthSum;
		}
		apoplastPathLengthTotal += tempLengthSum;
		//      cout << tempLengthSum << endl;
		epiCortexEndoApoplastPathLengthDB.push_back(tempLengthSum);
		apoplastPathLengthShortest = tempLengthMin;
		apoplastPathLengthLongest = tempLengthMax;
		//      cout << "apoplastPathLengthShortest: " << tempLengthMin
		//           << "  apoplastPathLengthLongest: " << tempLengthMax << endl;

	}
	apoplastPathLengthAverage = apoplastPathLengthTotal / epiCortexEndoApoplastXDB.size();


	/**********************
	Symplast
	***********************/
	symplastPathLengthTotal = 0;
	tempLengthMin = 100000;
	tempLengthMax = 0;

	for (itMapSymplastX = epiCortexEndoSymplastXDB.begin(),
		itMapSymplastY = epiCortexEndoSymplastYDB.begin(), i = 0;
		itMapSymplastX != epiCortexEndoSymplastXDB.end();
		itMapSymplastX++, itMapSymplastY++, i++)
	{
		tempLengthSum = 0;

		xFront = itMapSymplastX->second.front();
		yFront = itMapSymplastY->second.front();
		for (itVecSymplastX = itMapSymplastX->second.begin() + 1,
			itVecSymplastY = itMapSymplastY->second.begin() + 1;
			itVecSymplastX != itMapSymplastX->second.end();
			itVecSymplastX++, itVecSymplastY++)
		{
			tempLength = pow(pow(xFront - *itVecSymplastX, 2) + pow(yFront - *itVecSymplastY, 2), 0.5);
			tempLengthSum += tempLength;
			xFront = *itVecSymplastX;
			yFront = *itVecSymplastY;
		}

		/// Min;
		if (tempLengthMin > tempLengthSum)
		{
			tempLengthMin = tempLengthSum;
		}
		/// Max
		if (tempLengthMax < tempLengthSum)
		{
			tempLengthMax = tempLengthSum;
		}
		symplastPathLengthTotal += tempLengthSum;
		//      cout << tempLengthSum << endl;
		epiCortexEndoSymplastPathLengthDB.push_back(tempLengthSum);
		symplastPathLengthShortest = tempLengthMin;
		symplastPathLengthLongest = tempLengthMax;
		//      cout << "symplastPathLengthShortest: " << tempLengthMin
		//           << "  symplastPathLengthLongest: " << tempLengthMax << endl;

	}
	symplastPathLengthAverage = symplastPathLengthTotal / epiCortexEndoSymplastXDB.size();

}


/** \brief
 *
 * \param map<int, vector<double> > epiCortexEndoApoplastXDB;
 * \param map<int, vector<double> > epiCortexEndoApoplastYDB;
 * \param map<int, vector<double> > epiCortexEndoSymplastXDB;
 * \param map<int, vector<double> > epiCortexEndoSymplastYDB;
 * \param map<int, vector<double> > epiCortexEndoApoplastUpZDB;
 * \param map<int, vector<double> > epiCortexEndoApoplastDownZDB;
 * \param map<int, vector<double> > epiCortexEndoSymplastUpZDB;
 * \param map<int, vector<double> > epiCortexEndoSymplastDownZDB;
 * \return map<int, vector<double> > epiCortexEndoApoplastTriangleStripXDB;
 * \return map<int, vector<double> > epiCortexEndoApoplastTriangleStripYDB;
 * \return map<int, vector<double> > epiCortexEndoApoplastTriangleStripZDB;
 * \return map<int, vector<double> > epiCortexEndoSymplastTriangleStripXDB;
 * \return map<int, vector<double> > epiCortexEndoSymplastTriangleStripYDB;
 * \return map<int, vector<double> > epiCortexEndoSymplastTriangleStripZDB;
 *
 */

void rsEpiCortexEndoWaterPathDB::EpiCortexEndoPathTriangleStripXYZDB()
{
	map<int, vector<double> >::iterator itMapApoplastX;
	map<int, vector<double> >::iterator itMapApoplastY;
	map<int, vector<double> >::iterator itMapApoplastUpZ;
	map<int, vector<double> >::iterator itMapApoplastDownZ;

	map<int, vector<double> >::iterator itMapSymplastX;
	map<int, vector<double> >::iterator itMapSymplastY;
	map<int, vector<double> >::iterator itMapSymplastUpZ;
	map<int, vector<double> >::iterator itMapSymplastDownZ;

	vector<double>::iterator itVecApoplastX;
	vector<double>::iterator itVecApoplastY;
	vector<double>::iterator itVecApoplastUpZ;
	vector<double>::iterator itVecApoplastDownZ;

	vector<double>::iterator itVecSymplastX;
	vector<double>::iterator itVecSymplastY;
	vector<double>::iterator itVecSymplastUpZ;
	vector<double>::iterator itVecSymplastDownZ;

	vector<double> epiCortexEndoApoplastTriangleStripX;
	vector<double> epiCortexEndoApoplastTriangleStripY;
	vector<double> epiCortexEndoApoplastTriangleStripZ;

	vector<double> epiCortexEndoSymplastTriangleStripX;
	vector<double> epiCortexEndoSymplastTriangleStripY;
	vector<double> epiCortexEndoSymplastTriangleStripZ;

	int i;

	//   ofstream fout("WaterPath.txt",ios::app);
	//   fout << "EpiCortexEndoPathTriangleStripXYZDB" << endl;
	//
	//   fout << "Apoplast" << endl;
	   /// Apoplast;
	for (itMapApoplastX = epiCortexEndoApoplastXDB.begin(),
		itMapApoplastY = epiCortexEndoApoplastYDB.begin(),
		itMapApoplastUpZ = epiCortexEndoApoplastUpZDB.begin(),
		itMapApoplastDownZ = epiCortexEndoApoplastDownZDB.begin(), i = 0;
		itMapApoplastX != epiCortexEndoApoplastXDB.end();
		itMapApoplastX++, itMapApoplastY++, itMapApoplastUpZ++, itMapApoplastDownZ++, i++)
	{
		epiCortexEndoApoplastTriangleStripX.clear();
		epiCortexEndoApoplastTriangleStripX.clear();
		epiCortexEndoApoplastTriangleStripY.clear();
		epiCortexEndoApoplastTriangleStripY.clear();
		epiCortexEndoApoplastTriangleStripZ.clear();
		epiCortexEndoApoplastTriangleStripZ.clear();
		for (itVecApoplastX = itMapApoplastX->second.begin(),
			itVecApoplastY = itMapApoplastY->second.begin(),
			itVecApoplastUpZ = itMapApoplastUpZ->second.begin(),
			itVecApoplastDownZ = itMapApoplastDownZ->second.begin();
			itVecApoplastX != itMapApoplastX->second.end();
			itVecApoplastX++, itVecApoplastY++, itVecApoplastUpZ++, itVecApoplastDownZ++)
		{
			epiCortexEndoApoplastTriangleStripX.push_back(*itVecApoplastX);
			epiCortexEndoApoplastTriangleStripX.push_back(*itVecApoplastX);
			epiCortexEndoApoplastTriangleStripY.push_back(*itVecApoplastY);
			epiCortexEndoApoplastTriangleStripY.push_back(*itVecApoplastY);
			epiCortexEndoApoplastTriangleStripZ.push_back(*itVecApoplastUpZ);
			epiCortexEndoApoplastTriangleStripZ.push_back(*itVecApoplastDownZ);

		}
		epiCortexEndoApoplastTriangleStripXDB.insert(pair<int, vector<double> >(i, epiCortexEndoApoplastTriangleStripX));
		epiCortexEndoApoplastTriangleStripYDB.insert(pair<int, vector<double> >(i, epiCortexEndoApoplastTriangleStripY));
		epiCortexEndoApoplastTriangleStripZDB.insert(pair<int, vector<double> >(i, epiCortexEndoApoplastTriangleStripZ));
	}

	//   fout << endl;
	//   fout << "Symplast" << endl;
	   /// Symplast;
	for (itMapSymplastX = epiCortexEndoSymplastXDB.begin(),
		itMapSymplastY = epiCortexEndoSymplastYDB.begin(),
		itMapSymplastUpZ = epiCortexEndoSymplastUpZDB.begin(),
		itMapSymplastDownZ = epiCortexEndoSymplastDownZDB.begin(), i = 0;
		itMapSymplastX != epiCortexEndoSymplastXDB.end();
		itMapSymplastX++, itMapSymplastY++, itMapSymplastUpZ++, itMapSymplastDownZ++, i++)
	{
		epiCortexEndoSymplastTriangleStripX.clear();
		epiCortexEndoSymplastTriangleStripX.clear();
		epiCortexEndoSymplastTriangleStripY.clear();
		epiCortexEndoSymplastTriangleStripY.clear();
		epiCortexEndoSymplastTriangleStripZ.clear();
		epiCortexEndoSymplastTriangleStripZ.clear();
		for (itVecSymplastX = itMapSymplastX->second.begin(),
			itVecSymplastY = itMapSymplastY->second.begin(),
			itVecSymplastUpZ = itMapSymplastUpZ->second.begin(),
			itVecSymplastDownZ = itMapSymplastDownZ->second.begin();
			itVecSymplastX != itMapSymplastX->second.end();
			itVecSymplastX++, itVecSymplastY++, itVecSymplastUpZ++, itVecSymplastDownZ++)
		{
			epiCortexEndoSymplastTriangleStripX.push_back(*itVecSymplastX);
			epiCortexEndoSymplastTriangleStripX.push_back(*itVecSymplastX);
			epiCortexEndoSymplastTriangleStripY.push_back(*itVecSymplastY);
			epiCortexEndoSymplastTriangleStripY.push_back(*itVecSymplastY);
			epiCortexEndoSymplastTriangleStripZ.push_back(*itVecSymplastUpZ);
			epiCortexEndoSymplastTriangleStripZ.push_back(*itVecSymplastDownZ);

		}
		epiCortexEndoSymplastTriangleStripXDB.insert(pair<int, vector<double> >(i, epiCortexEndoSymplastTriangleStripX));
		epiCortexEndoSymplastTriangleStripYDB.insert(pair<int, vector<double> >(i, epiCortexEndoSymplastTriangleStripY));
		epiCortexEndoSymplastTriangleStripZDB.insert(pair<int, vector<double> >(i, epiCortexEndoSymplastTriangleStripZ));
	}
}

void rsEpiCortexEndoWaterPathDB::InitAllDB
(rsSourceDermisDB* RsSourceEpidermisDB,
	rsSourceCorticalDB* RsSourceCorticalDB,
	rsSourceDermisDB* RsSourceEndodermisDB
)
{
	EpiCortexEndoCellXYDB
	(RsSourceEpidermisDB,
		RsSourceCorticalDB,
		RsSourceEndodermisDB);

	EpiCortexEndoRingCellDimensionDB
	(RsSourceEpidermisDB,
		RsSourceCorticalDB,
		RsSourceEndodermisDB);

	EpiCortexEndoRingCentreRadiusDB
	(RsSourceEpidermisDB,
		RsSourceCorticalDB,
		RsSourceEndodermisDB);

	EpiCortexEndoRingPerimeterDB();

	EpiCortexEndoCellHalfIntersetionAngleDB();

	EpiCortexEndoCellLeftandRightRotateAngleDB();

	EpiCortexEndoCellXYDB();

	EpiCortexEndoCellMarkerDB();

	EpiCortexEndoPathXYDB();

	RecordCoincidentPoints();

	DeleteCoincidentPoints();

	EpiCortexEndoPathZDB();

	EpiCortexEndoPathLengthDB();

	EpiCortexEndoPathTriangleStripXYZDB();
}



