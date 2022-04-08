#define _USE_MATH_DEFINES
#include "rsBaseGeometry.h"
#include <cmath> 
using namespace std;

/// Set SuperEllipsoid Resolution;
void rsBaseGeometry::SetSuperEllipsoidResolution()
{
	uResolution = setUResolution;
	vResolution = setVResolution;
	wResolution = setWResolution;
}

/// SetObjectXYZRadiusRatio;
void rsBaseGeometry::SetObjectXYZRadiusRatio(double temp)
{
	objectXYZRadiusRatio = temp;
}

void rsBaseGeometry::SetObjectXYZRadiusRatio()
{
	double temp = 1;
	objectXYZRadiusRatio = temp;
}

/// Set opacity;
void rsBaseGeometry::SetObjectOpacity(double temp)
{
	objectOpacity = temp;
}

void rsBaseGeometry::SetObjectOpacity()
{
	double temp = 1;
	objectOpacity = temp;
}

void rsBaseGeometry::SetVacuoleOpacity(double temp)
{
	vacuoleOpacity = temp;
}

void rsBaseGeometry::SetVacuoleOpacity()
{
	double temp = 1;
	vacuoleOpacity = temp;
}

/*********************************************
// Radius of ring which contains objects(cylinders);
Output:
 Create "circleRadius"
Input:
 addRadius = The add radius of the new ring of cortical; //Jagdeep - 11-3-2020 actually the diameter of new cortical cell file
 basicRadius = The radius of stele;
 appendRadius = Append the radius that added before to shape the radius of current cortical; // Jagdeep - 11-3-2020 (1stCCF_addRadius)+ (2ndCCF_addRadius) = Append_radius for 3rd cell file
 *********************************************/
double rsBaseGeometry::CircleRadius(double basicRadius, double appendRadius, double addRadius)
{
	circleRadius = basicRadius + appendRadius + addRadius / 2;
	return circleRadius;
}

/// Length of the object in radial direction or in vertical of ring);
// addRadius = The add radius of the new ring of cortical; // 11-10-2020 Jia means addRadius = adddiameter
double rsBaseGeometry::ObjectVertical(double addRadius)
{
	objectVertical = addRadius / 2;
	return objectVertical;
}

/// Calculate perimeter of the circle for the ring;
double rsBaseGeometry::CirclePerimeter(double circleRadius)
{
	circlePerimeter = 2 * M_PI * circleRadius;
	return circlePerimeter;
}

/// Calculate position of Z of circle; //Jagdeep - 11-3-2020 - calculate Z position of the circle 
double rsBaseGeometry::ZPosition(double zPositionInput)
{
	zPosition = zPositionInput;
	return zPosition;
}

/******************************************************
// Calculate random data of objectVertical length for each ring;
*******************************************************/


/** \brief SameSumAndNumberButDifferentSTDEVRatio
 *
 * \param
 * \param
 * \return
 *
 */
void rsBaseGeometry::SameSumAndNumberButDifferentSTDEVRatio
(vector<double>& circleSegmentLengthTemp,
	vector<double>& circleSegmentLengthAddTemp,
	double totalLength,
	int cellNum,
	double stdevRatio)
{  /// define tmeporaty variables;
	double aveLength;
	double sum = 0;

	int stdevLength;


	ofstream fout("CalculateRandom.txt", ios::app);
	fout << "Cortical" << endl;
	cout << "cellNum: " << cellNum << "  totalLength: " << totalLength << endl;

	aveLength = totalLength / cellNum;

	// stdevRatio = standardDeviation / meanValue; // Jagdeep 11-4-2020 is he trying to get at Cofecient of variation??
	stdevLength = aveLength * stdevRatio;
	//
	//   fout << "stdevLength: " << stdevLength << endl;
	//   fout << "aveLength: " << aveLength << endl;

	double remain;
	int cellNumHalf;
	remain = fmod(cellNum, 2.0);
	cellNumHalf = int(cellNum / 2);

	//   fout << "remain: " << remain <<endl;
	//   fout << "cellNumHalf: " << cellNumHalf <<endl;

	vector<double> tempSTDEVRecordDB;
	int i;
	double tempDeviation;
	double tempLengthAdd;
	double tempLengthMinus;
	circleSegmentLengthTemp.clear();
	circleSegmentLengthAddTemp.clear();
	/// If cellNum belongs to even number;
	srand((unsigned)time(NULL));
	if (remain == 0)
	{  //fout << "OK" <<endl;
		for (i = 0; i != cellNumHalf; i++)
		{
			tempDeviation = rand() % stdevLength;
			tempSTDEVRecordDB.push_back(tempDeviation);

			tempLengthAdd = aveLength - tempDeviation;
			tempLengthMinus = aveLength + tempDeviation;

			sum += tempLengthAdd;
			circleSegmentLengthTemp.push_back(tempLengthAdd);
			circleSegmentLengthAddTemp.push_back(sum - tempLengthAdd);

			sum += tempLengthMinus;
			circleSegmentLengthTemp.push_back(tempLengthMinus);
			circleSegmentLengthAddTemp.push_back(sum - tempLengthMinus);
			//         fout << "tempLengthAdd: " << tempLengthAdd << endl;
			//         fout << "tempLengthMinus: " << tempLengthMinus << endl;
		}
	}
	/// If cellNum belongs to odd number;
	else
	{  //fout << "OK" <<endl;
		for (i = 0; i != cellNumHalf; i++)
		{  //srand((unsigned)time(NULL));
			tempDeviation = rand() % stdevLength;
			tempSTDEVRecordDB.push_back(tempDeviation);

			tempLengthAdd = aveLength - tempDeviation;
			tempLengthMinus = aveLength + tempDeviation;

			sum += tempLengthAdd;
			circleSegmentLengthTemp.push_back(tempLengthAdd);
			circleSegmentLengthAddTemp.push_back(sum - tempLengthAdd);

			sum += tempLengthMinus;
			circleSegmentLengthTemp.push_back(tempLengthMinus);
			circleSegmentLengthAddTemp.push_back(sum - tempLengthMinus);
			//         fout << "tempLengthAdd: " << tempLengthAdd << endl;
			//         fout << "tempLengthMinus: " << tempLengthMinus << endl;
		}
		sum += aveLength;
		circleSegmentLengthTemp.push_back(aveLength);
		circleSegmentLengthAddTemp.push_back(sum - aveLength);
	}
}


/** \brief SameSumAndNumberButDifferentSTDEVRatio
 *
 * \param
 * \param
 * \return
 *
 */
void rsBaseGeometry::SameSumAndNumberButDifferentSTDEVRatio
(vector<double>& circleSegmentLengthTemp,
	vector<double>& circleSegmentLengthAddTemp,
	double& circleSegmentLengthSumTemp,
	double totalLength,
	int cellNum,
	double stdevRatio)
{  /// define tmeporaty variables;
	double aveLength;
	double sum = 0;
	int stdevLength;

	//
	//   ofstream fout("CalculateRandom.txt",ios::app);
	//   fout << "Cortical" << endl;
	//   fout << "cellNum: " << cellNum << "  totalLength: " << totalLength << endl;

	aveLength = totalLength / cellNum;

	// stdevRatio = standardDeviation / meanValue;
	stdevLength = aveLength * stdevRatio;

	//   fout << "stdevLength: " << stdevLength << endl;
	//   fout << "aveLength: " << aveLength << endl;

	double remain;
	int cellNumHalf;
	remain = fmod(cellNum, 2.0);
	cellNumHalf = int(cellNum / 2);

	//   fout << "remain: " << remain <<endl;
	//   fout << "cellNumHalf: " << cellNumHalf <<endl;

	vector<double> tempSTDEVRecordDB;
	int i;
	double tempDeviation;
	double tempLengthAdd;
	double tempLengthMinus;
	circleSegmentLengthTemp.clear();
	circleSegmentLengthAddTemp.clear();
	/// If cellNum belongs to even number;
	srand((unsigned)time(NULL));
	if (remain == 0)
	{  //fout << "OK" <<endl;
		for (i = 0; i != cellNumHalf; i++)
		{
			tempDeviation = rand() % stdevLength;
			tempSTDEVRecordDB.push_back(tempDeviation);

			tempLengthAdd = aveLength - tempDeviation;
			tempLengthMinus = aveLength + tempDeviation;

			sum += tempLengthAdd;
			circleSegmentLengthTemp.push_back(tempLengthAdd);
			circleSegmentLengthAddTemp.push_back(sum - tempLengthAdd);

			sum += tempLengthMinus;
			circleSegmentLengthTemp.push_back(tempLengthMinus);
			circleSegmentLengthAddTemp.push_back(sum - tempLengthMinus);
			//
			//         fout << "tempLengthAdd: " << tempLengthAdd << endl;
			//         fout << "tempLengthMinus: " << tempLengthMinus << endl;
		}
		circleSegmentLengthSumTemp = sum;
	}
	/// If cellNum belongs to odd number;
	else
	{
		//       fout << "OK" <<endl;
		for (i = 0; i != cellNumHalf; i++)
		{  //srand((unsigned)time(NULL));
			tempDeviation = rand() % stdevLength;
			tempSTDEVRecordDB.push_back(tempDeviation);

			tempLengthAdd = aveLength - tempDeviation;
			tempLengthMinus = aveLength + tempDeviation;

			sum += tempLengthAdd;
			circleSegmentLengthTemp.push_back(tempLengthAdd);
			circleSegmentLengthAddTemp.push_back(sum - tempLengthAdd);

			sum += tempLengthMinus;
			circleSegmentLengthTemp.push_back(tempLengthMinus);
			circleSegmentLengthAddTemp.push_back(sum - tempLengthMinus);
			//
			//         fout << "tempLengthAdd: " << tempLengthAdd << endl;
			//         fout << "tempLengthMinus: " << tempLengthMinus << endl;
		}
		sum += aveLength;
		circleSegmentLengthTemp.push_back(aveLength);
		circleSegmentLengthAddTemp.push_back(sum - aveLength);

		circleSegmentLengthSumTemp = sum;
	}
}


/** \brief RandomRatioButSameSumAndNumber
 *
 * \param
 * \param
 * \return
 *
 */
void rsBaseGeometry::RandomRatioButSameSumAndNumber
(vector<double>& circleSegmentLengthTemp,
	vector<double>& circleSegmentLengthAddTemp,
	double totalLength,
	int cellNum,
	double variationRatio)
{  /// define tmeporaty variables;
	double aveLength;
	double sum = 0;
	double temp = 0;

	/** New */
	//double standardTotalLength = 2000;
	double standardTotalLength = int(totalLength);
	int variationLength;
	vector<int> randomVals;
	vector<double> ratioDB;
	vector<double> ratioAddDB;

	double tempCompare;
	double tempTotalLength;
	tempTotalLength = totalLength;
	tempCompare = tempTotalLength / cellNum;

	while (tempCompare < 50)
	{
		standardTotalLength *= 5;
		tempTotalLength *= 5;
		tempCompare = tempTotalLength / cellNum;
	}


	//   ofstream fout("CalculateRandom.txt",ios::app);
	//   fout << "CalculateRandom" << endl;
	//   fout << "cellNum: " << cellNum << "  totalLength: " << totalLength << endl;

	aveLength = round(standardTotalLength / cellNum);

	// variationRatio = standardDeviation / meanValue;
	variationLength = round(aveLength * variationRatio);

	//   fout << "variationLength: " << variationLength << endl;
	//   fout << "aveLength: " << aveLength << endl;

	srand((unsigned)time(NULL));
	/*while (sum != standardTotalLength)
	{
		ratioDB.clear();
		ratioAddDB.clear();
		sum = 0;

		for (int i = 0; i < cellNum; i++)
		{
			temp = (rand() % variationLength) + round(aveLength - variationLength / 2);
			sum += temp;
			ratioDB.push_back(temp / standardTotalLength);
			ratioAddDB.push_back((sum - temp) / standardTotalLength);
		}
	}*/
	//Sankalp - Hopefully a faster way:
	ratioDB.clear();
	ratioAddDB.clear();
	sum = 0;

	for (int i = 0; i < cellNum; i++)
	{
		temp = (rand() % variationLength) + round(aveLength - variationLength / 2);
		sum += temp;
		randomVals.push_back(temp);
	}
	double mulCoeff = standardTotalLength / sum;
	sum = 0;
	for (int i = 0; i < cellNum; i++)
	{
		temp = randomVals[i] * mulCoeff;
		sum += temp;
		ratioDB.push_back(temp / standardTotalLength);
		ratioAddDB.push_back((sum - temp) / standardTotalLength);
	}
	vector<double>::iterator itVec;
	vector<double>::iterator itVecAdd;
	int i;
	circleSegmentLengthTemp.clear();
	circleSegmentLengthAddTemp.clear();
	for (itVec = ratioDB.begin(), itVecAdd = ratioAddDB.begin(), i = 0;
		itVec != ratioDB.end();
		itVec++, itVecAdd++, i++)
	{
		circleSegmentLengthTemp.push_back((*itVec) * totalLength);
		circleSegmentLengthAddTemp.push_back((*itVecAdd) * totalLength);
		//      fout << "circleSegmentLengthTemp: " << "i: "  << i << "  " << (*itVec) * totalLength
		//           << "  circleSegmentLengthAddTemp: " << (*itVecAdd) * totalLength << endl;
	}
}

/** \brief RandomRatioButSameSumAndNumber
 *
 * \param
 * \param
 * \return
 *
 */
void rsBaseGeometry::RandomRatioButSameSumAndNumber
(vector<double>& circleSegmentLengthTemp,
	vector<double>& circleSegmentLengthAddTemp,
	double& circleSegmentLengthSumTemp,
	double totalLength,
	int cellNum,
	double variationRatio)
{  /// define tmeporaty variables;
	double aveLength;
	double sum = 0;
	double temp = 0;
	//   ofstream fout("CalculateRandom.txt",ios::app);
	//   fout << "CalculateRandom" << endl;
	//   fout << "cellNum: " << cellNum << "  totalLength: " << totalLength << endl;


	   /** New */
	   //double standardTotalLength = 2000;
	double standardTotalLength = int(totalLength);
	int variationLength;
	vector<double> ratioDB;
	vector<double> ratioAddDB;
	double ratioSum;

	double tempCompare;
	double tempTotalLength;
	tempTotalLength = totalLength;
	tempCompare = tempTotalLength / cellNum;
	while (tempCompare < 50)
	{
		standardTotalLength *= 5;
		tempTotalLength *= 5;
		tempCompare = tempTotalLength / cellNum;
	}

	aveLength = round(standardTotalLength / cellNum);

	// variationRatio = standardDeviation / meanValue;
	variationLength = round(aveLength * variationRatio);

	//   fout << "variationLength: " << variationLength << endl;
	//   fout << "aveLength: " << aveLength << endl;

	srand((unsigned)time(NULL));
	while (sum != standardTotalLength)
	{
		ratioDB.clear();
		ratioAddDB.clear();
		sum = 0;

		for (int i = 0; i < cellNum; i++)
		{
			temp = (rand() % variationLength) + round(aveLength - variationLength / 2);
			sum += temp;
			ratioDB.push_back(temp / standardTotalLength);
			ratioAddDB.push_back((sum - temp) / standardTotalLength);
			ratioSum = sum / standardTotalLength;
		}
	}
	vector<double>::iterator itVec;
	vector<double>::iterator itVecAdd;
	int i;
	circleSegmentLengthTemp.clear();
	circleSegmentLengthAddTemp.clear();
	for (itVec = ratioDB.begin(), itVecAdd = ratioAddDB.begin(), i = 0;
		itVec != ratioDB.end();
		itVec++, itVecAdd++, i++)
	{
		circleSegmentLengthTemp.push_back((*itVec) * totalLength);
		circleSegmentLengthAddTemp.push_back((*itVecAdd) * totalLength);
		//      fout << "circleSegmentLengthTemp: " << "i: "  << i << "  " << (*itVec) * totalLength
		//           << "  circleSegmentLengthAddTemp: " << (*itVecAdd) * totalLength << endl;
	}
	circleSegmentLengthSumTemp = ratioSum * totalLength;
}

/** \brief SameSumAndNumberAndRatio
 *
 * \param vector<double>& circleSegmentLength
 * \param vector<double>& circleSegmentLengthAdd
 * \param double& circleSegmentLengthSum
 * \param double circlePerimeter
 * \param int *itVecCellNum
 * \param double variationRatio
 *
 */
void rsBaseGeometry::SameSumAndNumberAndRatio
(vector<double>& circleSegmentLengthTemp,
	vector<double>& circleSegmentLengthAddTemp,
	double& circleSegmentLengthSumTemp,
	double totalLength,
	int cellNum,
	double variationRatio)
{  /// define tmeporaty variables;
	double aveLength;
	double sum = 0;
	int i;

	aveLength = totalLength / cellNum;

	circleSegmentLengthTemp.clear();
	circleSegmentLengthAddTemp.clear();

	for (i = 0; i != cellNum; i++)
	{
		sum += aveLength;
		circleSegmentLengthTemp.push_back(aveLength);
		circleSegmentLengthAddTemp.push_back(sum - aveLength);
	}
	circleSegmentLengthSumTemp = totalLength;
}

/** \brief SameSumAndNumberAndRatio
 *
 * \param
 * \param
 * \return
 *
 */
void rsBaseGeometry::SameSumAndNumberAndRatio
(vector<double>& circleSegmentLengthTemp,
	vector<double>& circleSegmentLengthAddTemp,
	double totalLength,
	int cellNum,
	double variationRatio)
{  /// define tmeporaty variables;
	double aveLength;
	double sum = 0;
	int i;

	aveLength = totalLength / cellNum;

	circleSegmentLengthTemp.clear();
	circleSegmentLengthAddTemp.clear();

	for (i = 0; i != cellNum; i++)
	{
		sum += aveLength;
		circleSegmentLengthTemp.push_back(aveLength);
		circleSegmentLengthAddTemp.push_back(sum - aveLength);
	}
}





/*******************************************************
// Get position of X and Y in circle by random generated in paralell length;
 objectNum = the number of object(Ellipsoid) in each ring/circle;
 circleRadius = Radius of each ring/circle;
*******************************************************/
void rsBaseGeometry::CircleXYNonuniform(int objectNumber, double circleRadius)
{
	double temp = 0;
	double sum = 0;
	vector<double> circleSegmentRotateLengthAdd;
	circleSegmentRotateLengthAdd.clear();
	circleSegmentRotateAngle.clear();
	circleX.clear();
	circleY.clear();
	//   ofstream fout("cortex.txt",ios::app);
	for (int i = 0; i < objectNumber; i++)
	{
		if (i == 0)
		{
			circleX.push_back(circleRadius *
				cos(2 * M_PI * (circleSegmentLengthAdd[i]
					/ circleSegmentLengthSum)));
			circleY.push_back(circleRadius *
				sin(2 * M_PI * (circleSegmentLengthAdd[i]
					/ circleSegmentLengthSum)));
			sum = 0;
			circleSegmentRotateLengthAdd.push_back(sum);
			circleSegmentRotateAngle.push_back(-360 * sum / circleSegmentLengthSum);
			//         fout << -360 * sum / circleSegmentLengthSum << endl;
		}
		else
		{
			temp = (circleSegmentLength[i] + circleSegmentLength[i - 1]) / 2;

			circleX.push_back(circleRadius *
				cos(2 * M_PI * ((sum + temp)
					/ circleSegmentLengthSum)));
			circleY.push_back(circleRadius *
				sin(2 * M_PI * ((sum + temp)
					/ circleSegmentLengthSum)));
			sum += temp;
			circleSegmentRotateLengthAdd.push_back(sum);
			circleSegmentRotateAngle.push_back(-360 * sum / circleSegmentLengthSum);
			//         fout << -360 * sum / circleSegmentLengthSum << endl;
		}
	}
}

/***************************************************************************
/Jagdeep 11/22/2020 The next two functions are for creating Non-Random and random longitudenal (axial length) data.
/sliceNum - number of cell slices, default is 3, total height - total length of all the slices - default = 450,
/longitudeSegmentHeight = Axial length of each slice - default = 150,
/longitudeZPosition = Zposition of individual slice - default = 75
/initZposition - sum of longitudeZPositionAdd - default = 225,
/
*/
/******************************************************
// Calculate random data of objectHeight length for each XYPosition;
*******************************************************/

void rsBaseGeometry::NonRandomHeight
(double totalHeight,
	int sliceNum,
	double initZPosition)
{  /// define tmeporaty variables;
	double aveLength;
	double sum = 0;
	double zPositionSum = 0;

	aveLength = totalHeight / sliceNum;

	longitudeSegmentHeight.clear();
	longitudeZPositionAdd.clear();

	for (int i = 0; i < sliceNum; i++)
	{
		longitudeSegmentHeight.push_back(aveLength);
	}

	for (int i = 0; i < sliceNum; i++)
	{
		if (i == 0)
		{
			longitudeZPositionAdd.push_back(zPositionSum + initZPosition);
		}
		else
		{
			zPositionSum += ((longitudeSegmentHeight[i] + longitudeSegmentHeight[i - 1]) / 2);
			longitudeZPositionAdd.push_back(zPositionSum + initZPosition);
		}
		ofstream fout(getFolderName() + "Zposition.txt", ios::app);
		fout << "loop" << endl;
		fout << "longitudeSegmentHeight = " << longitudeSegmentHeight.back() << endl;
		fout << "longtiudeZpositionAdd   " << longitudeZPositionAdd.back() << endl;
		fout << "total height  " << totalHeight << endl;
		fout << "SliceNum  = " << sliceNum << endl;
		fout << "initZPosition = " << initZPosition << endl;
	}
}


/******************************************************
// Calculate random data of objectHeight length for each XYPosition;
*******************************************************/

void rsBaseGeometry::RandomHeight
(double totalHeight,
	int sliceNum,
	double initZPosition)
{  /// define tmeporaty variables;
	int roundLength;
	double aveLength;
	double lengthTemp;
	int rangeLength;

	double sum = 0;
	double temp = 0;

	double zPositionSum = 0;

	//sliceNum = ( rand()% (sliceNum/2) ) + sliceNum/2;

	/// Initialize input;
	roundLength = round(totalHeight);
	lengthTemp = roundLength * 100.0;
	aveLength = round(lengthTemp / sliceNum);
	/// define the range of random data generate, the bigger the smaller range;
	randomRange = 1;
	rangeLength = round(aveLength / randomRange);

	//srand ( time(NULL) );
	srand((rand() % ((rand() % 1000)+1)));
	//srand((unsigned)time(NULL));
	while (sum != roundLength)
	{
		longitudeSegmentHeight.clear();
		longitudeZPositionAdd.clear();
		sum = 0;

		for (int i = 0; i < sliceNum; i++)
		{
			temp = (rand() % rangeLength) + round(aveLength - rangeLength / 2);
			temp = temp / 100;
			//cout << temp << '\t';
			sum += temp;
			longitudeSegmentHeight.push_back(temp);
		}

		for (int i = 0; i < sliceNum; i++)
		{
			if (i == 0)
			{
				zPositionSum = 0;
				longitudeZPositionAdd.push_back(zPositionSum + initZPosition);
			}
			else
			{
				zPositionSum += ((longitudeSegmentHeight[i] + longitudeSegmentHeight[i - 1]) / 2);
				longitudeZPositionAdd.push_back(zPositionSum + initZPosition);
			}
		}
		//cout << endl;
	}
}

/*************************************************
// Create mapRGB database;
**************************************************/
void rsBaseGeometry::MapRGB()
{

	vector<double> vecRGB;
	int r, g, b;
	int i = 0;

	int range = 2;
	for (r = 0; r <= range; r++)
	{
		for (g = 0; g <= range; g++)
		{
			for (b = 0; b <= range; b++)
			{
				vecRGB.push_back(double(r) / double(range));
				vecRGB.push_back(double(g) / double(range));
				vecRGB.push_back(double(b) / double(range));
				//            cout << "r: " << vecRGB[0] << "  g: " << vecRGB[1] << "  b: " << vecRGB[2] << endl;
				mapRGB.insert(pair<int, vector<double> >(i, vecRGB));
				i++;
				vecRGB.clear();
			}
		}
	}
}
/** \brief rgbTime;
 *
 * \param int setRGBTime;
 * \return int rgbTime;
 *
 */
void rsBaseGeometry::RGBTime(int setRGBTime)
{
	rgbTime = setRGBTime;
}
/** \brief rgbStart;
 *
 * \param int setRGBStart;
 * \return int rgbStart;
 *
 */
void rsBaseGeometry::RGBStart(int setRGBStart)
{
	rgbStart = setRGBStart;
}
