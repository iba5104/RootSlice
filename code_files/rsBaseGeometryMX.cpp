#define _USE_MATH_DEFINES
#include <cmath>
#include <random>
#include "rsBaseGeometryMX.h"


/** Get mxBoundaryRingRadiusDeliver from rsPXCoreDB class;
 *
 * \param rsPXCoreDB -> boundaryMXPXRingRadius;
 * \return mxBoundaryRingRadiusDeliver
 *
 */

double boundaryMXPXRingRadiusDeliver;
double rsBaseGeometryMX::BoundaryMXPXRingRadiusDeliver
(rsPXCoreDB* RsPXCoreDB)
{
	boundaryMXPXRingRadiusDeliver = RsPXCoreDB->boundaryMXPXRingRadius;
	ofstream fout(getFolderName() + "a.txt", ios::app);
	fout << "BoundaryMXPXRingRadiusDeliver: " << boundaryMXPXRingRadiusDeliver << endl;
	return boundaryMXPXRingRadiusDeliver;
}

/** Get mxNum;
 *
 * \param int setMXNum;
 * \return int mxNum;
 *
 */
int rsBaseGeometryMX::MXNum(int setMXNum)
{
	mxNum = setMXNum;
	return mxNum;
}

/** Get mxAverageRingRadius;
 *
 * \param int setMXAverageRingRadius;
 * \return int mxAverageRingRadius;
 *
 */

double mxAverageRingRadius;
int rsBaseGeometryMX::MXAverageRingRadius(double setMXAverageRingRadius)
{
	mxAverageRingRadius = setMXAverageRingRadius;
	return mxAverageRingRadius;
}

/** Get mxMaxRingRadius;
 *
 * \param int setMXMaxRingRadius;
 * \return int mxMaxRingRadius;
 *
 */

double mxMaxRingRadius;
vector<double> eachRingMinRadius;
int rsBaseGeometryMX::MXMinMaxRingRadius(double setMXMaxRingRadius, vector<double> setMXMinRingRadius)
{
	mxMaxRingRadius = setMXMaxRingRadius;
	eachRingMinRadius = setMXMinRingRadius;
	return mxMaxRingRadius;
}

/** Get RandomRange;
 *
 * \param int setPXAverageRingRadius;
 * \return int pxNum;
 *
 */
double randomRange;
int rsBaseGeometryMX::RandomRange(double setRandomRange)
{
	randomRange = setRandomRange;
	return randomRange;
}

int xylemArms;
int rsBaseGeometryMX::XylemArms(int pxNum) {
	xylemArms = pxNum;
	return xylemArms;
}

int mxRingNum;
int rsBaseGeometryMX::MXRingNum(int setMXRingNum)
{
	mxRingNum = setMXRingNum;
	return mxRingNum;
}

vector<int> eachRingMXNum;
int rsBaseGeometryMX::EachRingMXNum(vector<int> eachRingNum)
{
	eachRingMXNum = eachRingNum;
	return 0;
}

int outRingCellNum;
int rsBaseGeometryMX::SetOutRingCellNum(int xylemMaxOutRingCellNum)
{
	outRingCellNum = xylemMaxOutRingCellNum;
	return 0;
}

double outRingAddRadius;
int rsBaseGeometryMX::SetOutRingAddRadius(double xylemMaxOutRingAddRadius)
{
	outRingAddRadius = xylemMaxOutRingAddRadius;
	return 0;
}

bool noCentreMX = false;
/******************************************************
// Calculate random data of radius for each ring of mx;
   To get:
   vector<double> eachRingRadius;
   vector<double> eachRingRadiusAdd;
   double eachRingDiameterSum;
*******************************************************/
void rsBaseGeometryMX::RandomRadius(double variationRatio)
{
	double mxRadiusTotal;
	double eachRingRadiusSum;
	mxRadiusTotal = mxAverageRingRadius * mxNum;
	if (type_dicot) {
		int i;
		double maxPXRadius = *max_element(eachRingMinRadius.begin(), eachRingMinRadius.end());
		noCentreMX = (mxNum == accumulate(eachRingMXNum.begin(), eachRingMXNum.end(), 0));
		int divNum = noCentreMX ? mxRingNum : (mxRingNum + 1.0);
		double radiusVariation = pow((maxPXRadius / mxMaxRingRadius), (1.0 / divNum));
		if (!noCentreMX)
			eachRingRadius.push_back(mxMaxRingRadius);
		eachArmDiameterSum = 0;
		for (int ringIdx = 0; ringIdx < mxRingNum; ringIdx++)
		{
			eachRingRadiusSum = 0;
			double aveRadius = mxMaxRingRadius * pow(radiusVariation, (ringIdx+1));
			double variationLength = aveRadius * variationRatio;
			double minRadius = aveRadius - variationLength / 2.0;
			double maxRadius = aveRadius + variationLength / 2.0;
			uniform_real_distribution<double> unif(minRadius, maxRadius);
			default_random_engine re;
			double rndmRadius = unif(re);
			double maxAdd = outRingAddRadius * outRingCellNum * 2.0;
			double dist = (eachRingRadius.size() == 0) ? (rndmRadius + maxAdd) : 
				(eachRingRadius.back() + maxAdd + rndmRadius + maxAdd);
			double diameter = 2 * M_PI * dist;
			if (((rndmRadius + maxAdd) * eachRingMXNum[ringIdx]) > diameter)
				rndmRadius = (diameter / eachRingMXNum[ringIdx]) - maxAdd;
			for (int i = 0; i < eachRingMXNum[ringIdx]; i++) {
				eachRingRadius.push_back(rndmRadius);
				eachRingRadiusSum += eachRingRadius.back();
			}
			eachRingDiameterSum.push_back(eachRingRadiusSum * 2.0);
			eachArmDiameterSum += rndmRadius * 2.0;
		}
	}
	else {
		RandomRatioButSameSumAndNumber(eachRingRadius,
			eachRingRadiusAdd,
			eachRingRadiusSum,
			mxRadiusTotal,
			mxNum,
			variationRatio);
		eachRingDiameterSum.push_back(eachRingRadiusSum * 2);
	}
}

/** Get position of X and Y in center circle by random generated in eachRingRadius for mx;
 *
 * \param int pxNum: the number of object(Ellipsoid) in each ring/circle;
 * \return vector<double> centerRingRotateRadian;
 * \return vector<double> centerRingRotateAngle;
 *
 */

void rsBaseGeometryMX::CenterXYRotate(vector<double> pxRingRotateRadian, vector<double> pxRingRotateAngle)
{
	double temp = 0;
	double sum = 0;

	//   ofstream fout("a.txt",ios::app);
	//   fout << "rsBaseGeometryMX.cpp" << endl;
	if (type_dicot) {
		sum = 0;
		for (int i = 0; i < mxRingNum; i++)
		{
			for (int j = 0; j < eachRingMXNum[i]; j++) {
				if (eachRingMXNum[i] == pxRingRotateRadian.size())
				{
					centerRingRotateRadian.push_back(pxRingRotateRadian[j]);
					centerRingRotateAngle.push_back(pxRingRotateAngle[j]);
					continue;
				}
				if (j == 0)
				{
					sum = 0;
					centerRingRotateRadian.push_back(sum);
					centerRingRotateAngle.push_back(sum);
				}
				else {
					temp = eachRingRadius[j] + eachRingRadius[j - 1];
					sum += temp;
					centerRingRotateRadian.push_back(2 * M_PI * sum / eachRingDiameterSum[i]);
					centerRingRotateAngle.push_back(-360 * sum / eachRingDiameterSum[i]);
				}
			}
		}
	}
	else {
		for (int i = 0; i < mxNum; i++)
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
				centerRingRotateRadian.push_back(2 * M_PI * sum / eachRingDiameterSum[0]);
				centerRingRotateAngle.push_back(-360 * sum / eachRingDiameterSum[0]);

				//         fout << "centerRingRotateRadian: " << i <<": "
				//              << 2*M_PI* sum / eachRingDiameterSum << endl;
			}
		}
	}
}
