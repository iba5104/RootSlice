#define _USE_MATH_DEFINES
#include <cmath> 
#include "rsBaseGeometryPX.h"

/** Get steleBoundaryRingRadius;
 *
 * \param double endodermisBaseRadius
 * \return double steleBoundaryRingRadius
 *
 */
double rsBaseGeometryPX::SteleBoundaryRingRadius(double endodermisBaseRadius)
{
	steleBoundaryRingRadius = endodermisBaseRadius;
	return steleBoundaryRingRadius;
}

/** Get pxBoundaryRingRadius;
 *
 * \param double pxGapRadius
 * \return double pxBoundaryRingRadius
 *
 */
double rsBaseGeometryPX::PXBoundaryRingRadius(double pxGapRadius)
{
	pxBoundaryRingRadius = steleBoundaryRingRadius - pxGapRadius;
	ofstream fout("a.txt", ios::app);
	fout << "pxBoundaryRingRadius: " << pxBoundaryRingRadius << endl;
	return pxBoundaryRingRadius;
}

/** Get pxNum;
 *
 * \param int setPXNum;
 * \return int pxNum;
 *
 */
int rsBaseGeometryPX::PXNum(int setPXNum)
{
	pxNum = setPXNum;
	return pxNum;
}

/** Get pxAverageRingRadius;
 *
 * \param double setPXAverageRingRadius;
 * \return double pxAverageRingRadius;
 *
 */
 //double pxAverageRingRadius;
int rsBaseGeometryPX::PXAverageRingRadius(double setPXAverageRingRadius)
{
	pxAverageRingRadius = setPXAverageRingRadius;
	return pxAverageRingRadius;
}

/** Get RandomRange;
 *
 * \param int setPXAverageRingRadius;
 * \return int pxNum;
 *
 */
 //double randomRange;
int rsBaseGeometryPX::RandomRange(double setRandomRange)
{
	randomRange = setRandomRange;
	return randomRange;
}

/** Calculate random data of radius for each ring of metaxylem;
 *
 * \param int pxNum: the number of object(Ellipsoid) in each ring/circle;
 * \param double pxAverageRingRadius;
 * \param double randomRange;
 * \return vector<double> eachRingRadius;
 * \return vector<double> eachRingRadiusAdd;
 * \return double eachRingDiameterSum;
 *
 */
void rsBaseGeometryPX::RandomRadius(double variationRatio)
{
	double pxRadiusTotal;
	double eachRingRadiusSum;
	pxRadiusTotal = pxAverageRingRadius * pxNum;
	RandomRatioButSameSumAndNumber(eachRingRadius,
		eachRingRadiusAdd,
		eachRingRadiusSum,
		pxRadiusTotal,
		pxNum,
		variationRatio);
	eachRingDiameterSum = eachRingRadiusSum * 2;
}

/** Get position of X and Y in center circle by random generated in eachRingRadius for metaxylem;
 *
 * \param int pxNum: the number of object(Ellipsoid) in each ring/circle;
 * \return vector<double> centerRingRotateRadian;
 * \return vector<double> centerRingRotateAngle;
 *
 */
 //vector<double> centerRingRotateRadian;
 //vector<double> centerRingRotateAngle;

void rsBaseGeometryPX::CenterXYRotate()
{
	double temp = 0;
	double sum = 0;

	//   ofstream fout("a.txt",ios::app);
	//   fout << "rsBaseGeometryPX.cpp" << endl;
	for (int i = 0; i < pxNum; i++)
	{
		if (i == 0)
		{
			sum = 0;
			centerRingRotateRadian.push_back(sum);
			centerRingRotateAngle.push_back(sum);
			//         fout << "centerRingRotateRadian: " << i <<": "<< 0 << endl;
		}
		else
		{
			temp = eachRingRadius[i] + eachRingRadius[i - 1];
			sum += temp;
			centerRingRotateRadian.push_back(2 * M_PI * sum / eachRingDiameterSum);
			centerRingRotateAngle.push_back(-360 * sum / eachRingDiameterSum);

			//         fout << "centerRingRotateRadian: " << i <<": "
			//              << 2*M_PI* sum / eachRingDiameterSum << endl;
		}
	}
}



