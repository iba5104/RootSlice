#define _USE_MATH_DEFINES
#include <cmath> 
#include "rsSourceCorticalDB.h"

/// Set OutputXMLVtpFileName;
void rsSourceCorticalDB::OutputXMLVtpFileName
(const char* CorticalXMLVtpFileNameInput,
	const char* CorticalVacuoleXMLVtpFileNameInput,
	const char* CorticalPlasmaMembraneVtpFileNameInput)
{
	CorticalXMLVtpFileName = CorticalXMLVtpFileNameInput;
	CorticalVacuoleXMLVtpFileName = CorticalVacuoleXMLVtpFileNameInput;
	CorticalPlasmaMembraneVtpFileName = CorticalPlasmaMembraneVtpFileNameInput;
}


/** \brief CorticalAddRadiusCalculateRatioData;
 *
 * \param int cortexLayerNum;
 * \param double corticalCellMultiplyRatio
 * \return vector<double> corticalAddRadiusCalculateSingleRatioData;
 * \return vector<double> corticalAddRadiusCalculateMixRatioData;
 *
 */
 // Jagdeep 11-8-2020 - tempSingleRatio = 
 // tempMixRatio = 
 // ratioSum =

void rsSourceCorticalDB::CorticalAddRadiusCalculateRatioData  // Jagdeep 11-8-2020 where is this function called??
(int cortexLayerNum,
	double corticalCellMultiplyRatio) // Jagdeep 11-8-2020 corticalCellMultuplyRatio = 0.1, though I don't where is this set I calcualted it back from this function??
{
	double remain;
	int innerHalfLayerNum;
	int outerHalfLayerNum;
	int i;
	double tempSingleRatio;
	double tempMixRatio;
	double ratioSum;
	vector<double>::iterator itVec;
	remain = fmod(cortexLayerNum, 2.0);

	ofstream fout("test.txt", ios::app);
	fout << "CorticalAddRadiusCalculateRatioData" << endl;

	/* Jagdeep 11-8-2020 dividing number of cell files into two halves i.e. inner and outter.
	/  CoritcalCellMultiplyRatio = 0.1 which is 10% increase for each inner files compared to its inner neighbor and
	/  10% decrease for each outer file compared to its inner neighbor except for the transition between inner and outer cell file.
	*/
	if (remain == 0)
	{
		innerHalfLayerNum = cortexLayerNum / 2;
		outerHalfLayerNum = cortexLayerNum / 2;
		fout << "innerHalfLayerNum: " << innerHalfLayerNum << endl;
		fout << "outerHalfLayerNum: " << outerHalfLayerNum << endl;
		for (i = 0; i != innerHalfLayerNum; i++)
		{
			tempSingleRatio = 1 + corticalCellMultiplyRatio * i;
			corticalAddRadiusCalculateSingleRatioData.push_back(tempSingleRatio);
		}
		for (i = outerHalfLayerNum - 1; i >= 0; i--)
		{
			tempSingleRatio = 1 + corticalCellMultiplyRatio * i;
			corticalAddRadiusCalculateSingleRatioData.push_back(tempSingleRatio);
		}
	}
	else
	{
		innerHalfLayerNum = cortexLayerNum / 2 + 1;
		outerHalfLayerNum = cortexLayerNum / 2;
		fout << "innerHalfLayerNum: " << innerHalfLayerNum << endl;
		fout << "outerHalfLayerNum: " << outerHalfLayerNum << endl;

		for (i = 0; i != innerHalfLayerNum; i++)
		{
			tempSingleRatio = 1 + corticalCellMultiplyRatio * i;
			corticalAddRadiusCalculateSingleRatioData.push_back(tempSingleRatio);
		}
		for (i = outerHalfLayerNum - 1; i >= 0; i--)
		{
			tempSingleRatio = 1 + corticalCellMultiplyRatio * i;
			corticalAddRadiusCalculateSingleRatioData.push_back(tempSingleRatio);
		}
	}
	/// Calculate the sum of ratio;
	fout << "corticalAddRadiusCalculateSingleRatioData" << endl;
	ratioSum = 0;
	for (itVec = corticalAddRadiusCalculateSingleRatioData.begin();
		itVec != corticalAddRadiusCalculateSingleRatioData.end();
		itVec++)
	{
		ratioSum += (*itVec);
		fout << *itVec << endl;
		fout << "ratio sum = " << ratioSum << endl;
	}

	/* Jagdeep 11-10-2020 - MixRatio for file x,  which is stored in corticalAddRadiusCalculateMixRatioData, basically is length of cortical radius occupied by file x. e.g. if there are
	/ 4 cell files then individual or single ratio is 1, 1.1, 1.1, and 1. Ratio sum = 4.2. Mixratio for each file (inner to outter) respectively is 1/4.2, 1.1/4.2, 1.1/4.2, and 1/4.2
	*/
	fout << "corticalAddRadiusCalculateMixRatioData" << endl;
	for (itVec = corticalAddRadiusCalculateSingleRatioData.begin();
		itVec != corticalAddRadiusCalculateSingleRatioData.end();
		itVec++)
	{
		tempMixRatio = (*itVec) / ratioSum;
		corticalAddRadiusCalculateMixRatioData.push_back(tempMixRatio);
		fout << "tempmixratio" << tempMixRatio << endl;
	}
}

/** \brief CorticalAddRadiusCalculateFromMinCellData;
 *
 * \param double corticalCellAddRadiusMin;
 * \param vector<double> corticalAddRadiusCalculateSingleRatioData;
 * \return vector<double> corticalAddRadiusCalculateFromMinCellData;
 *
 */
 /* Here cell radius of inner file is used and then by using the corticalAddRadiusSingleRatio, the cell radius of other files is calculated.
 */
void rsSourceCorticalDB::CorticalAddRadiusCalculateFromMinCellData()
{
	double temp;
	vector<double>::iterator itVec;
	int i;
	ofstream fout("test.txt", ios::app);
	fout << "CorticalAddRadiusCalculateFromMinCellData" << endl;
	for (itVec = corticalAddRadiusCalculateSingleRatioData.begin(), i = 0;
		itVec != corticalAddRadiusCalculateSingleRatioData.end();
		itVec++, i++)
	{
		temp = (*itVec) * corticalCellAddRadiusMin;
		corticalAddRadiusCalculateFromMinCellData.push_back(temp);
		cout << "CorticalLayerPosition: " << i << "  CellDiameter: " << temp << endl;
		fout << "CorticalLayerPosition: " << i << "  CellDiameter: " << temp << endl;
	}
}
/** \brief CorticalAddRadiusCalculateFromCortexRadiusData;
 *
 * \param double cortexRadius;
 * \param vector<double> corticalAddRadiusCalculateMixRatioData;
 * \return vector<double> corticalAddRadiusCalculateFromCortexRadiusData;
 *
 */
 /* Here cell radius of each file is calcualted by using corticalAddRadiusSingleRatio i.e. what proportion of cortex radius is occupied by certain cell file radius
  */
void rsSourceCorticalDB::CorticalAddRadiusCalculateFromCortexRadiusData()
{
	double temp;
	vector<double>::iterator itVec;

	ofstream fout("test.txt", ios::app);
	fout << "CorticalAddRadiusCalculateFromCortexRadiusData" << endl;
	for (itVec = corticalAddRadiusCalculateMixRatioData.begin();
		itVec != corticalAddRadiusCalculateMixRatioData.end();
		itVec++)
	{
		temp = (*itVec) * cortexRadius;
		corticalAddRadiusCalculateFromCortexRadiusData.push_back(temp);
		fout << temp << endl;
	}

	corticalInnermostCellDiameterCalculate = corticalAddRadiusCalculateFromCortexRadiusData.front();
}
/** \brief CorticalAddRadiusCalculateData;
 *
 * \param double corticalCellAddRadiusMin;
 * \param double cortexRadius;
 * \return vector<double> corticalAddRadiusCalculateData;
 *
 */

void rsSourceCorticalDB::CorticalAddRadiusCalculateData
(double corticalCellAddRadiusMinInput,
	double cortexRadiusInput)
{
	corticalCellAddRadiusMin = corticalCellAddRadiusMinInput;
	cortexRadius = cortexRadiusInput;  //11-17-2020 need to find where is this cortexRadiusInput value called inputted from??
	/// Judge;
	// 11-17-2020 here it is judged that whether to use inner most cell radius or based on the radius of cortex?
	if (cortexRadius == 0)
	{
		CorticalAddRadiusCalculateFromMinCellData();

		corticalAddRadiusCalculateData = corticalAddRadiusCalculateFromMinCellData;
	}
	else if (corticalCellAddRadiusMin == 0)
	{
		CorticalAddRadiusCalculateFromCortexRadiusData();
		corticalAddRadiusCalculateData = corticalAddRadiusCalculateFromCortexRadiusData;
	}
}
/** \brief CorticalAddRadiusDataSelect;
 *
 * \param double corticalCellAddRadiusMin;
 * \param double cortexRadius;
 * \param vector<double> corticalAddRadiusInputData;
 * \return vector<double> corticalAddRadiusDB;
 *
 * 11 - 17 - 2020 this is the function asking whether to use use input data(I think) or calcualted data ?
 */
void rsSourceCorticalDB::CorticalAddRadiusDataSelect
(int corticalAddRadiusDBSelectInput,
	vector<double> corticalAddRadiusInputData)

{
	if (corticalAddRadiusDBSelectInput == 0)
	{
		corticalAddRadiusDB = corticalAddRadiusInputData;
	}
	else if (corticalAddRadiusDBSelectInput == 1)
	{
		corticalAddRadiusDB = corticalAddRadiusCalculateData;
	}
}

/********************************************************
// Calculate the coritcalAppendRadiusDB;
 corticalAddRadiusDB = map that store addRadius;
 addRadius = diameter of each object;
 Append radius for file x = Sum of diameter of all the file under file x
=∑ from (𝑑𝑖𝑎𝑚𝑒𝑡𝑒𝑟 𝑜𝑓 𝑐𝑒𝑙𝑙 𝑓𝑖𝑙𝑒 = 1) to (x) minus diameter of cell file = x
*********************************************************/
void rsSourceCorticalDB::CorticalAppendRadiusDB()
{
	vector<double>::iterator itVec;
	double temp = 0;
	for (itVec = corticalAddRadiusDB.begin(); itVec != corticalAddRadiusDB.end(); itVec++)
	{
		corticalAppendRadiusDB.push_back(temp);
		temp += (*itVec);
	}
}

/******************************************************
// Create CircleRadiusDB;
Before do this, we must initialize "corticalAppendRadius"
*******************************************************/

void rsSourceCorticalDB::CircleRadiusDB
(double baseRadius,
	vector<double> corticalAppendRadiusDB)
{
	int iRingNum;
	/// declare iterator;
	vector<double>::iterator itVecAdd;

	for (iRingNum = 0, itVecAdd = corticalAddRadiusDB.begin();
		itVecAdd != corticalAddRadiusDB.end();
		itVecAdd++, iRingNum++)
	{
		circleRadiusDB.push_back(CircleRadius(baseRadius,
			corticalAppendRadiusDB[iRingNum],
			(*itVecAdd)
		)
		);
	}
}

/** \brief CorticalCellNumCalculateData;
 *
 * \param vector<double> circleRadiusDB;
 * \param vector<double> corticalAddRadiusDB
 * \return vector<int> corticalCellNumCalculateData
 *
 */
void rsSourceCorticalDB::CorticalCellNumCalculateData()
{
	vector<double>::iterator itVecAdd;
	vector<double>::iterator itVec;
	int tempNum;
	// int num;
	double perimeterLayer;
	int i;
	cout << "CorticalCellNumCalculateData" << endl;
	for (itVecAdd = corticalAddRadiusDB.begin(), itVec = circleRadiusDB.begin(), i = 0;
		itVecAdd != corticalAddRadiusDB.end();
		itVecAdd++, itVec++, i++)
	{
		perimeterLayer = 2 * M_PI * (*itVec);
		tempNum = int(perimeterLayer / (*itVecAdd));
		//num = tempNum;


		corticalCellNumCalculateData.push_back(tempNum);
	}
}

/** \brief CorticalCellNumSelect;
 *
 * \param int corticalCellNumSelectInput;
 * \param vector<int> corticalCellNumCalculateData;
 * \param vector<int> corticalCellNumInputData;
 * \return vector<int> corticalCellNumDB;
 *
 */
void rsSourceCorticalDB::CorticalCellNumSelect
(int corticalCellNumSelectInput,
	vector<int> corticalCellNumInputData)

{
	if (corticalCellNumSelectInput == 0)
	{
		corticalCellNumDB = corticalCellNumInputData; // 11-10-2020 Jagdeep I believe here is where if we want to read from a file?? Need to find where this function is called!
	}
	else if (corticalCellNumSelectInput == 1)
	{
		corticalCellNumDB = corticalCellNumCalculateData;
	}
}

/********************************************************
// Calculate the radius of outest ring in cortical;
 corticalAddRadiusDB = map that store addRadius;
 addRadius = diameter of each object;
*********************************************************/
void rsSourceCorticalDB::BoundaryRadius(double baseRadius)
{
	vector<double>::iterator itVec;
	double sum = 0;
	for (itVec = corticalAddRadiusDB.begin(); itVec != corticalAddRadiusDB.end(); itVec++)
	{
		sum += (*itVec);
	}
	boundaryRadius = baseRadius + sum;
}


/******************************************************
// Create ObjectVerticalDB;
// 11-9-2020 Jagdeep ObjectVertical comes from rsbaseGeometry.cpp and so does ObjectXYZRadiusRatio which is just a variable and its value = 1.
Object vertical is radius of each cell -- 1-24-2021
*******************************************************/
void rsSourceCorticalDB::ObjectVerticalDB()
{
	int iRingNum;
	/// declare iterator;
	vector<double>::iterator itVecAdd;

	for (iRingNum = 0, itVecAdd = corticalAddRadiusDB.begin();
		itVecAdd != corticalAddRadiusDB.end();
		itVecAdd++, iRingNum++)
	{
		objectVerticalDB.push_back(ObjectVertical(*itVecAdd) / objectXYZRadiusRatio);
		cout << "ObjectVertical =" << objectVerticalDB.back() << endl;
		cout << "objectXYZRadiusRatio in rsSourceCorticalDB.cpp is it 1? value =" << objectXYZRadiusRatio << endl;
	}
}

/******************************************************
// Create RandomHeightDB;
// 11-19-2020 need to find out where totalheight - 1-24-2021 its in main.cpp and other variable values are passed on?
// Jagdeep 11/22/2020 The next function calculates longitudenal (axial length) data.
/sliceNum - number of cell slices, default is 3, total height - total length of all the slices - default = 450,
/longitudeSegmentHeight = Axial length of each slice - default = 150,
/longitudeZPosition = initZposition + ZpositionSum - details in rsBaseGeometry.cpp
/initZposition - Z position of first slice longitudeZPositionAdd - default = 75,
*******************************************************/
void rsSourceCorticalDB::RandomHeightDB(double totalHeight, int sliceNum, double initZPosition, int VectorNum) // VectorNum is defined in main.cpp line 178 -- jgdp -- 1-24-2021
{
	int temp;
	for (temp = 0;
		temp != VectorNum;
		temp++)
	{  //srand ( time(NULL) );

	   /// RandomHeight;
		NonRandomHeight(totalHeight, sliceNum, initZPosition);
		longitudeSegmentHeightDB.insert(pair<int, vector<double> >(temp, longitudeSegmentHeight)); // longitudeSegmentHeight is a vector storing average length of each slice - look in rsgeometry line 555
		longitudeZPositionAddDB.insert(pair<int, vector<double> >(temp, longitudeZPositionAdd));
	}

	//for (auto i = longitudeSegmentHeight.begin(); i != longitudeSegmentHeight.end(); ++i) // Jgdp 1-24-2020
		//cout << endl << "Temp " << temp << "longitudeSegmentHeight" << *i << " ";

}



/******************************************************
// GetRandomCircleSegmentAndCircleXYNonuniformDB
*******************************************************/

void rsSourceCorticalDB::GetRandomCircleSegmentAndCircleXYNonuniformDB
(vector<int> corticalCellNumDB,
	double variationRatio
)
{
	int iRingNum;
	/// declare corticalAddRadiusDB iterator;
	vector<double>::iterator itVecAdd;
	vector<int>::iterator itVecCellNum;

	ofstream fout("cortex.txt", ios::app);
	fout << "circleSegmentRotateAngleDB" << endl;
	for (iRingNum = 0, itVecCellNum = corticalCellNumDB.begin(), itVecAdd = corticalAddRadiusDB.begin();
		itVecAdd != corticalAddRadiusDB.end();
		itVecAdd++, iRingNum++, itVecCellNum++)

	{
		CirclePerimeter(circleRadiusDB[iRingNum]);
		/// RandomRatioButSameSumAndNumber
		SameSumAndNumberAndRatio(circleSegmentLength,
			circleSegmentLengthAdd,
			circleSegmentLengthSum,
			circlePerimeter,
			*itVecCellNum,
			variationRatio);

		circleSegmentLengthDB.insert(pair<int, vector<double> >(iRingNum, circleSegmentLength));

		//for (auto i = circleSegmentLength.begin(); i != circleSegmentLength.end(); ++i) // Jgdp 1-24-2020
		   //cout << endl << "iRingNum" << iRingNum << "circleSegmentLength--" << *i << endl;

		circleSegmentLengthSumDB.push_back(circleSegmentLengthSum);

		CircleXYNonuniform(*itVecCellNum, circleRadiusDB[iRingNum]);
		circleXDB.insert(pair<int, vector<double> >(iRingNum, circleX));
		circleYDB.insert(pair<int, vector<double> >(iRingNum, circleY));
		circleSegmentRotateAngleDB.insert(pair<int, vector<double> >(iRingNum, circleSegmentRotateAngle));
		fout << "Ringnum = " << iRingNum << endl;
		fout << "corticalAddRadius = " << *itVecAdd << endl;
		fout << "corticalcellNum = " << *itVecCellNum << endl;
		fout << "circleXDB = " << circleX.at(iRingNum) << endl;
		fout << "circleYDB = " << circleY.at(iRingNum) << endl;
		fout << "circleSegmentRotateAngle = " << circleSegmentRotateAngle.at(iRingNum) << endl;

	}
}

/******************************************************
// Get circleSegmentLengthAdjustRatioDB;
*******************************************************/
void rsSourceCorticalDB::CircleSegmentLengthAdjustRatioDB()
{
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVector;

	for (itMap = circleSegmentLengthDB.begin();
		itMap != circleSegmentLengthDB.end();
		itMap++)
	{
		for (itVector = (*itMap).second.begin(); itVector != (*itMap).second.end(); itVector++)
		{
			*itVector = (*itVector) / 2 / objectXYZRadiusRatio;
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
void rsSourceCorticalDB::ObjectHeightAndZPositionDB(int sliceNum)
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
				(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio);
				//cout << endl << "randomHeightZPosition" << randomHeightZPosition << endl; // jgdp -- 1-24-2021 this is some random number ranges from 1 to 200.
				//cout << endl << "???????" << longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio; // jgdp -- 1-24-2021 confirmed this is slice length.
				objectZPositionVec1.push_back
				(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
			}

			objectHeightVec2.push_back(objectHeightVec1);
			objectZPositionVec2.push_back(objectZPositionVec1);
		}

		objectHeightDB.insert(pair<int, vector< vector<double> > >(iRingNum, objectHeightVec2)); /// // jgdp -- 1-24-2021 confirmed this is slice length divided by 2, esstentially longitudnal radius
		objectZPositionDB.insert(pair<int, vector< vector<double> > >(iRingNum, objectZPositionVec2));

		//for (auto i = objectHeightVec1.begin(); i != objectHeightVec1.end(); ++i) // Jgdp 1-24-2020
			// cout << endl << "iRingNum" << iRingNum << "objectHeightVec2--" << *i << endl;

			 /*for (int i = 0; i < objectHeightVec2.size(); i++) { /// good example to print vector of vectors --jgdp-- 1-24-2021 confirmed this is slice length divided by 2, esstentially longitudnal radius
			for (int j = 0; j < objectHeightVec2[i].size(); j++)
				cout << endl << objectHeightVec2[i][j] << "Object Height ---" << endl*/

	}
}



/*******************************************
Initialize other Database;
********************************************/
void rsSourceCorticalDB::InitAllDB(double baseRadius,
	int cortexLayerNum,
	double corticalCellMultiplyRatio,
	double corticalCellAddRadiusMinInput,
	double cortexRadiusInput,
	int corticalAddRadiusDBSelectInput,
	vector<double> corticalAddRadiusInputData,
	vector<int> corticalCellNumInputData,
	int corticalCellNumSelectInput,
	double variationRatio,
	int setUResolution,
	int setVResolution,
	int setWResolution,
	int sliceNum
)
{
	SetObjectXYZRadiusRatio();

	SetObjectOpacity();


	CorticalAddRadiusCalculateRatioData
	(cortexLayerNum,
		corticalCellMultiplyRatio);


	CorticalAddRadiusCalculateData
	(corticalCellAddRadiusMinInput,
		cortexRadiusInput);

	CorticalAddRadiusDataSelect
	(corticalAddRadiusDBSelectInput,
		corticalAddRadiusInputData);

	CorticalAppendRadiusDB();

	CircleRadiusDB(baseRadius,
		corticalAppendRadiusDB);

	CorticalCellNumCalculateData();

	CorticalCellNumSelect(corticalCellNumSelectInput, corticalCellNumInputData);

	ObjectVerticalDB();

	GetRandomCircleSegmentAndCircleXYNonuniformDB
	(corticalCellNumDB,
		variationRatio);

	CircleSegmentLengthAdjustRatioDB();

	ObjectHeightAndZPositionDB(sliceNum);

	SetSuperEllipsoidResolution(setUResolution, setVResolution, setWResolution);

	MapRGB();

	BoundaryRadius(baseRadius);
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

double gapCellWall;
vector<double> pureCellVerticalDB;
map<int, vector<double> > pureCellParallelDB;
map<int, vector< vector<double> > > pureCellHeightDB;
void rsSourceCorticalDB::InitPureCellDB(double gapCellWallInput)
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

void rsSourceCorticalDB::InitVacuoleDB(double gapCytoTonoInput)
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

	/// Set Vacuole Opacity
	SetVacuoleOpacity();
}