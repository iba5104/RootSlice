#define _USE_MATH_DEFINES
#include <cmath> 
#include "rsPhloemDB.h"

/** \brief InterRadianStartAndEndDB
 *
 * \param vector<double> RsPXBoundaryDB -> interRadianStartDB;
 * \param vector<double> RsPXBoundaryDB -> interRadianEndDB;
 * \param vector<double> RsPXBoundaryDB -> interIntersectionRadianDB;
 * \return vector<double> interRadianStartDB;
 * \return vector<double> interRadianEndDB;
 * \return vector<double> interIntersectionRadianDB;
 *
 */
void rsPhloemDB::InterRadianStartAndEndDB(rsPXBoundaryDB* RsPXBoundaryDB)
{
	vector<double>::iterator itVecStart;
	vector<double>::iterator itVecEnd;
	vector<double>::iterator itVec;
	vector<double>::iterator itVecInterStart;
	vector<double>::iterator itVecInterEnd;
	double temp;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "/////////////////////////////////////// rsPhloemDB ///////////////////////////////////////////////" << endl;
	fout << "InterRadianStartAndEndDB" << endl;
	for (itVecEnd = RsPXBoundaryDB->boundaryRadianEndDB.begin();
		itVecEnd != RsPXBoundaryDB->boundaryRadianEndDB.end();
		itVecEnd++)
	{
		interRadianStartDB.push_back(*itVecEnd);
		fout << "interRadianStartDB: " << *itVecEnd << endl;
	}
	/// Append from the second one to the last one as the last one  in boundaryRadianStartDB
	/// to interRadianStartDB;
	for (itVecStart = RsPXBoundaryDB->boundaryRadianStartDB.begin() + 1;
		itVecStart != RsPXBoundaryDB->boundaryRadianStartDB.end();
		itVecStart++)
	{
		interRadianEndDB.push_back(*itVecStart);
		fout << "interRadianEndDB: " << *itVecStart << endl;
	}
	/// Append the first one in boundaryRadianStartDB as the last one in interRadianStartDB;
	itVec = RsPXBoundaryDB->boundaryRadianStartDB.begin();
	temp = *itVec + +2 * M_PI;
	interRadianEndDB.push_back(temp);
	fout << "interRadianEndDB: " << temp << endl;

	for (itVecInterEnd = interRadianEndDB.begin(), itVecInterStart = interRadianStartDB.begin();
		itVecInterEnd != interRadianEndDB.end();
		itVecInterEnd++, itVecInterStart++)
	{
		temp = *itVecInterEnd - *itVecInterStart;
		interIntersectionRadianDB.push_back(temp);
		fout << "interIntersectionRadianDB: " << temp << endl;
	}
}

/** \brief upVerticalLengthTotalDB
 *
 * \param vector<double> RsPXBoundaryDB -> boundaryRadiusDB;
 * \return vector<double> upVerticalLengthTotalDB;
 *
 */
void rsPhloemDB::UpVerticalLengthTotalDB(rsPXBoundaryDB* RsPXBoundaryDB)
{
	vector<double>::iterator itVec;
	double temp;
	for (itVec = RsPXBoundaryDB->boundaryRadiusDB.begin();
		itVec != RsPXBoundaryDB->boundaryRadiusDB.end();
		itVec++)
	{
		temp = (*itVec) * 2;
		upVerticalLengthTotalDB.push_back(temp);
	}
}

/** \brief phloemVerticalLengthHalfDB;
 *
 * \param vector<double> upVerticalLengthTotalDB;
 * \return vector<double> phloemVerticalLengthHalfDB;
 *
 */
void rsPhloemDB::PhloemVerticalLengthHalfDB()
{
	vector<double>::iterator itVec;
	double temp;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "PhloemVerticalLengthHalfDB" << endl;
	for (itVec = upVerticalLengthTotalDB.begin();
		itVec != upVerticalLengthTotalDB.end();
		itVec++)
	{
		temp = (*itVec) / 4;
		phloemVerticalLengthHalfDB.push_back(temp);
		fout << "temp: " << temp << endl;
	}
}

/** \brief upAppendVerticalLengthDB
 *
 * \param vector<double> phloemVerticalLengthHalfDB;
 * \return vector<double> upAppendVerticalLengthDB;
 *
 */
void rsPhloemDB::UpAppendVerticalLengthDB()
{
	upAppendVerticalLengthDB = phloemVerticalLengthHalfDB;
}

/** \brief upAppendVerticalLengthHalfDB
 *
 * \param vector<double> upAppendVerticalLengthDB;
 * \return vector<double> upAppendVerticalLengthHalfDB;
 *
 */
void rsPhloemDB::UpAppendVerticalLengthHalfDB()
{
	vector<double>::iterator itVec;
	double temp;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpAppendVerticalLengthHalfDB" << endl;
	for (itVec = upAppendVerticalLengthDB.begin();
		itVec != upAppendVerticalLengthDB.end();
		itVec++)
	{
		temp = (*itVec) / 2;
		upAppendVerticalLengthHalfDB.push_back(temp);
		fout << "temp: " << temp << endl;
	}
}

/** \brief boundaryMXPXRingRadiusDeliver
 *
 * \param double RsPXBoundaryDB -> boundaryMXPXRingRadius;
 * \return double boundaryMXPXRingRadiusDeliver;
 *
 */
void rsPhloemDB::BoundaryMXPXRingRadiusDeliver(rsPXBoundaryDB* RsPXBoundaryDB)
{
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "BoundaryMXPXRingRadiusDeliver" << endl;
	boundaryMXPXRingRadiusDeliver = RsPXBoundaryDB->boundaryMXPXRingRadius;
	fout << boundaryMXPXRingRadiusDeliver << endl;
}

/** \brief upFirstCenterRadius upSecondCenterRadius;
 *
 * \param double boundaryMXPXRingRadiusDeliver;
 * \param vector<double> upVerticalLengthTotalDB;
 * \return vector<double> upFirstPhloemCenterRadiusDB;
 * \return vector<double> upSecondPhloemCenterRadiusDB;
 *
 */
void rsPhloemDB::PhloemCenterRadius()
{
	vector<double>::iterator itVec;
	double tempFirst;
	double tempSecond;
	for (itVec = upVerticalLengthTotalDB.begin();
		itVec != upVerticalLengthTotalDB.end();
		itVec++)
	{
		tempFirst = boundaryMXPXRingRadiusDeliver + double(1) / double(4) * (*itVec);
		tempSecond = boundaryMXPXRingRadiusDeliver + double(3) / double(4) * (*itVec);
		upFirstPhloemCenterRadiusDB.push_back(tempFirst);
		upSecondPhloemCenterRadiusDB.push_back(tempSecond);
	}
}

/** \brief upFirstSecondPhloemParallelNumDB
 *
 * \param vector<double> interIntersectionRadianDB;
 * \return vector<int> upFirstPhloemParallelNumDB;
 * \return vector<int> upSecondPhloemParallelNumDB;
 *
 */
void rsPhloemDB::UpFirstSecondPhloemParallelNumDB()
{
	vector<double>::iterator itVec;
	int tempFirst;
	int tempSecond;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpFirstSecondPhloemParallelNumDB" << endl;
	for (itVec = interIntersectionRadianDB.begin();
		itVec != interIntersectionRadianDB.end();
		itVec++)
	{  //srand(( rand()% (rand()% 1000) ) );
		tempFirst = rand() % 2 + 1;
		//srand(( rand()% (rand()% 1000) ) );
		tempSecond = rand() % 2 + 2;
		upFirstPhloemParallelNumDB.push_back(tempFirst);
		upSecondPhloemParallelNumDB.push_back(tempSecond);
		fout << "tempFirst: " << tempFirst << "  tempSecond: " << tempSecond << endl;
	}
}

/** \brief phloemRadianRatioDB
 *
 * \param
 * \param
 * \return vector<double> phloemRadianRatioDB;
 *
 */
void rsPhloemDB::PhloemRadianRatioDB()
{
	double array[3] = { double(1) / double(3),
					  double(2) / double(3),
					  double(3) / double(4)
	};
	int i;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "PhloemRadianRatioDB" << endl;
	for (i = 0; i != 3; i++)
	{
		phloemRadianRatioDB.push_back(array[i]);
		fout << array[i] << endl;
	}
}

/** \brief upFirstSecondPhloemParallelRadianTotalDB
 *
 * \param vector<double> phloemRadianRatioDB;
 * \param vector<double> interIntersectionRadianDB;
 * \param vector<double> upFirstPhloemParallelNumDB;
 * \param vector<double> upSecondPhloemParallelNumDB;
 * \return vector<double> upFirstPhloemParallelRadianTotalDB;
 * \return vector<double> upSecondPhloemParallelRadianTotalDB;
 *
 */
void rsPhloemDB::UpFirstSecondPhloemParallelRadianTotalDB()
{
	vector<double>::iterator itVec;
	vector<int>::iterator itVecFirstNum;
	vector<int>::iterator itVecSecondNum;
	double tempFirst;
	double tempSecond;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpFirstSecondPhloemParallelRadianTotalDB" << endl;
	for (itVec = interIntersectionRadianDB.begin(), itVecFirstNum = upFirstPhloemParallelNumDB.begin(),
		itVecSecondNum = upSecondPhloemParallelNumDB.begin();
		itVec != interIntersectionRadianDB.end();
		itVec++, itVecFirstNum++, itVecSecondNum++)
	{
		tempFirst = (*itVec) * (phloemRadianRatioDB[(*itVecFirstNum) - 1]);
		tempSecond = (*itVec) * (phloemRadianRatioDB[(*itVecSecondNum) - 1]);
		upFirstPhloemParallelRadianTotalDB.push_back(tempFirst);
		upSecondPhloemParallelRadianTotalDB.push_back(tempSecond);
		fout << "tempFirst: " << tempFirst << "  tempSecond: " << tempSecond
			<< "  *itVecFirstNum: " << *itVecFirstNum << "  *itVecSecondNum: " << *itVecSecondNum << endl;
		fout << "phloemRadianRatioDB[ (*itVecFirstNum) - 1 ]: " << phloemRadianRatioDB[(*itVecFirstNum) - 1]
			<< "  phloemRadianRatioDB[ (*itVecSecondNum) - 1 ]: " << phloemRadianRatioDB[(*itVecSecondNum) - 1] << endl;
		fout << "interIntersectionRadianDB: " << *itVec << endl;
	}
}

/** \brief upAppendCenterRadiusDB
 *
 * \param double boundaryMXPXRingRadiusDeliver;
 * \param vector<double> upAppendVerticalLengthDB;
 * \param vector<double> upAppendVerticalLengthHalfDB;
 * \return map<int, vector<double> > upAppendCenterRadiusDB;
 *
 */
void rsPhloemDB::UpAppendCenterRadiusDB()
{
	vector<double>::iterator itVec;
	vector<double>::iterator itVecHalf;
	vector<double> upAppendCenterRadius;
	int i;
	int layer;
	double temp;

	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpAppendCenterRadiusDB" << endl;

	for (itVecHalf = upAppendVerticalLengthHalfDB.begin(), itVec = upAppendVerticalLengthDB.begin(), i = 0;
		itVecHalf != upAppendVerticalLengthHalfDB.end();
		itVecHalf++, itVec++, i++)
	{
		upAppendCenterRadius.clear();
		for (layer = 0; layer != 4; layer++)
		{
			temp = boundaryMXPXRingRadiusDeliver + *itVec * layer + *itVecHalf;
			upAppendCenterRadius.push_back(temp);
			fout << "i: " << i << "  layer: " << layer << "  UpAppendCenterRadiusDB: " << temp << endl;
		}
		upAppendCenterRadiusDB.insert(pair<int, vector<double> >(i, upAppendCenterRadius));
	}
}

/** \brief upFirstSecondAppendParallelRadianTotalDB
 *
 * \param vector<double> interIntersectionRadianDB;
 * \param vector<double> upFirstPhloemParallelRadianTotalDB;
 * \param vector<double> upSecondPhloemParallelRadianTotalDB;
 * \return vector<double> upFirstAppendParallelRadianTotalDB;
 * \return vector<double> upSecondAppendParallelRadianTotalDB;
 *
 */
void rsPhloemDB::UpFirstSecondAppendParallelRadianTotalDB()
{
	vector<double>::iterator itVec;
	vector<double>::iterator itVecFirst;
	vector<double>::iterator itVecSecond;
	double tempFirst;
	double tempSecond;

	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpFirstSecondAppendParallelRadianTotalDB" << endl;
	for (itVec = interIntersectionRadianDB.begin(), itVecFirst = upFirstPhloemParallelRadianTotalDB.begin(),
		itVecSecond = upSecondPhloemParallelRadianTotalDB.begin();
		itVec != interIntersectionRadianDB.end();
		itVec++, itVecFirst++, itVecSecond++)
	{
		tempFirst = *itVec - *itVecFirst;
		tempSecond = *itVec - *itVecSecond;
		upFirstAppendParallelRadianTotalDB.push_back(tempFirst);
		upSecondAppendParallelRadianTotalDB.push_back(tempSecond);
		fout << "tempFirst: " << tempFirst << "  tempSecond: " << tempSecond << endl;
	}
}

/** \brief upAppendParallelStartAndEndRadianTotalRatioDB
 *
 * \param
 * \param
 * \return vector<double> upAppendParallelStartAndEndRadianTotalRatioDB;
 *
 */
void rsPhloemDB::UpAppendParallelRadianTotalRatioDB()
{
	double array[3] = { double(1) / double(3),
					  double(1) / double(2),
					  double(2) / double(3)
	};
	int i;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpAppendParallelRadianTotalRatioDB" << endl;
	for (i = 0; i != 3; i++)
	{
		upAppendParallelStartAndEndRadianTotalRatioDB.push_back(array[i]);
		fout << array[i] << endl;
	}
}

/** \brief upFirstSecondAppendParallelStartAndEndRadianTotalDB;
 *
 * \param
 * \param
 * \return vector<double> upFirstAppendParallelStartRadianTotalDB;
 * \return vector<double> upFirstAppendParallelEndRadianTotalDB;
 * \return vector<double> upSecondAppendParallelStartRadianTotalDB;
 * \return vector<double> upSecondAppendParallelEndRadianTotalDB;
 *
 */
void rsPhloemDB::UpFirstSecondAppendParallelStartAndEndRadianTotalDB()
{
	vector<double>::iterator itVec;
	vector<double>::iterator itVecFirst;
	vector<double>::iterator itVecSecond;
	double tempFirstStart;
	double tempSecondStart;
	double tempFirstEnd;
	double tempSecondEnd;
	int ratioFirst;
	int ratioSecond;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpFirstSecondAppendParallelStartAndEndRadianTotalDB" << endl;
	for (itVecFirst = upFirstAppendParallelRadianTotalDB.begin(),
		itVecSecond = upSecondAppendParallelRadianTotalDB.begin();
		itVecFirst != upFirstAppendParallelRadianTotalDB.end();
		itVecFirst++, itVecSecond++)
	{  //srand(( rand()% (rand()% 1000) ) );
		ratioFirst = rand() % 3;
		//srand(( rand()% (rand()% 1000) ) );
		ratioSecond = rand() % 3;
		fout << "ratioFirst: " << ratioFirst << "  ratioSecond: " << ratioSecond << endl;
		tempFirstStart = *itVecFirst * upAppendParallelStartAndEndRadianTotalRatioDB[ratioFirst];
		tempFirstEnd = *itVecFirst - tempFirstStart;
		tempSecondStart = *itVecSecond * upAppendParallelStartAndEndRadianTotalRatioDB[ratioSecond];
		tempSecondEnd = *itVecSecond - tempSecondStart;

		upFirstAppendParallelStartRadianTotalDB.push_back(tempFirstStart);
		upFirstAppendParallelEndRadianTotalDB.push_back(tempFirstEnd);
		upSecondAppendParallelStartRadianTotalDB.push_back(tempSecondStart);
		upSecondAppendParallelEndRadianTotalDB.push_back(tempSecondEnd);
	}
}
/** \brief upAppendParallelStartAndEndRadianTotal
 *
 * \param vector<double> upFirstAppendParallelStartRadianTotalDB;
 * \param vector<double> upFirstAppendParallelEndRadianTotalDB;
 * \param vector<double> upSecondAppendParallelStartRadianTotalDB;
 * \param vector<double> upSecondAppendParallelEndRadianTotalDB;
 * \param
 * \return map<int, vector<double> > upAppendParallelStartRadianTotalDB;
 * \return map<int, vector<double> > upAppendParallelEndRadianTotalDB;
 *
 */
void rsPhloemDB::UpAppendParallelRadianTotal()
{
	vector<double> upAppendParallelStartRadianTotal;
	vector<double> upAppendParallelEndRadianTotal;
	vector<double>::iterator itVecFirst;
	vector<double>::iterator itVecSecond;
	int i;
	int rep;

	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpAppendParallelRadianTotal" << endl;
	fout << "Start" << endl;
	/// Start;
	for (itVecFirst = upFirstAppendParallelStartRadianTotalDB.begin(),
		itVecSecond = upSecondAppendParallelStartRadianTotalDB.begin(), i = 0;
		itVecFirst != upFirstAppendParallelStartRadianTotalDB.end();
		itVecFirst++, itVecSecond++, i++)
	{
		upAppendParallelStartRadianTotal.clear();
		for (rep = 0; rep != 2; rep++)
		{
			upAppendParallelStartRadianTotal.push_back(*itVecFirst);
			fout << "  *itVecFirst: " << *itVecFirst;
		}
		for (rep = 0; rep != 2; rep++)
		{
			upAppendParallelStartRadianTotal.push_back(*itVecSecond);
			fout << "  *itVecSecond: " << *itVecSecond;
		}
		fout << endl;
		upAppendParallelStartRadianTotalDB.insert(pair<int, vector<double> >(i, upAppendParallelStartRadianTotal));
	}
	/// End;
	for (itVecFirst = upFirstAppendParallelEndRadianTotalDB.begin(),
		itVecSecond = upSecondAppendParallelEndRadianTotalDB.begin(), i = 0;
		itVecFirst != upFirstAppendParallelEndRadianTotalDB.end();
		itVecFirst++, itVecSecond++, i++)
	{
		upAppendParallelEndRadianTotal.clear();
		for (rep = 0; rep != 2; rep++)
		{
			upAppendParallelEndRadianTotal.push_back(*itVecFirst);
		}
		for (rep = 0; rep != 2; rep++)
		{
			upAppendParallelEndRadianTotal.push_back(*itVecSecond);
		}
		upAppendParallelEndRadianTotalDB.insert(pair<int, vector<double> >(i, upAppendParallelEndRadianTotal));
	}
}

/** \brief upAppendParallelStartAndEndLengthTotalDB
 *
 * \param map<int, vector<double> > upAppendParallelStartRadianTotalDB;
 * \param map<int, vector<double> > upAppendParallelEndRadianTotalDB;
 * \param map<int, vector<double> > upAppendCenterRadiusDB;
 * \return map<int, vector<double> > upAppendParallelStartLengthTotalDB;
 * \return map<int, vector<double> > upAppendParallelEndLengthTotalDB;
 *
 */
void rsPhloemDB::UpAppendParallelLengthTotalDB()
{
	map<int, vector<double> >::iterator itMapStart;
	map<int, vector<double> >::iterator itMapEnd;
	map<int, vector<double> >::iterator itMapRadius;
	vector<double>::iterator itVecStart;
	vector<double>::iterator itVecEnd;
	vector<double>::iterator itVecRadius;
	vector<double> upAppendParallelStartLengthTotal;
	vector<double> upAppendParallelEndLengthTotal;
	double tempStart;
	double tempEnd;
	int i;

	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpAppendParallelLengthTotalDB" << endl;

	for (itMapRadius = upAppendCenterRadiusDB.begin(),
		itMapStart = upAppendParallelStartRadianTotalDB.begin(),
		itMapEnd = upAppendParallelEndRadianTotalDB.begin(), i = 0;
		itMapRadius != upAppendCenterRadiusDB.end();
		itMapRadius++, itMapStart++, itMapEnd++, i++)
	{
		upAppendParallelStartLengthTotal.clear();
		upAppendParallelEndLengthTotal.clear();
		for (itVecRadius = (*itMapRadius).second.begin(),
			itVecStart = (*itMapStart).second.begin(),
			itVecEnd = (*itMapEnd).second.begin();
			itVecRadius != (*itMapRadius).second.end();
			itVecRadius++, itVecStart++, itVecEnd++)
		{
			tempStart = 2 * M_PI * (*itVecRadius) * (*itVecStart / (2 * M_PI));
			tempEnd = 2 * M_PI * (*itVecRadius) * (*itVecEnd / (2 * M_PI));
			upAppendParallelStartLengthTotal.push_back(tempStart);
			upAppendParallelEndLengthTotal.push_back(tempEnd);
			fout << "tempStart: " << tempStart << "  tempEnd: " << tempEnd << endl;
		}
		upAppendParallelStartLengthTotalDB.insert(pair<int, vector<double> >(i, upAppendParallelStartLengthTotal));
		upAppendParallelEndLengthTotalDB.insert(pair<int, vector<double> >(i, upAppendParallelEndLengthTotal));
	}
}

/** \brief upFirstSecondParallelLengthTotalDB
 *
 * \param vector<double> upFirstPhloemCenterRadiusDB;
 * \param vector<double> upSecondPhloemCenterRadiusDB;
 * \param vector<double> interIntersectionRadianDB;
 * \return vector<double> upFirstParallelLengthTotalDB;
 * \return vector<double> upSecondParallelLengthTotalDB;
 *
 */
void rsPhloemDB::UpParallelLengthTotalDB()
{
	vector<double>::iterator itVecFirst;
	vector<double>::iterator itVecSecond;
	vector<double>::iterator itVecRadian;
	double tempFirst;
	double tempSecond;
	for (itVecRadian = interIntersectionRadianDB.begin(),
		itVecFirst = upFirstPhloemCenterRadiusDB.begin(),
		itVecSecond = upSecondPhloemCenterRadiusDB.begin();
		itVecRadian != interIntersectionRadianDB.end();
		itVecRadian++, itVecFirst++, itVecSecond++)
	{
		tempFirst = 2 * M_PI * (*itVecFirst) * (*itVecRadian / (2 * M_PI));
		tempSecond = 2 * M_PI * (*itVecSecond) * (*itVecRadian / (2 * M_PI));
		upFirstParallelLengthTotalDB.push_back(tempFirst);
		upSecondParallelLengthTotalDB.push_back(tempSecond);
	}
}
/** \brief upAppendParallelLengthThresholdDB
 *
 * \param double setUpAppendParallelLengthThresholdRatio
 * \param vector<double> upFirstParallelLengthTotalDB;
 * \param vector<double> upSecondParallelLengthTotalDB;
 * \return vector<double> upAppendParallelLengthThresholdDB;
 *
 */
void rsPhloemDB::UpAppendParallelLengthThresholdDB(double setUpAppendParallelLengthThresholdRatio)
{
	vector<double>::iterator itVecFirst;
	vector<double>::iterator itVecSecond;
	double temp;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpAppendParallelLengthThresholdDB" << endl;
	for (itVecFirst = upFirstParallelLengthTotalDB.begin(),
		itVecSecond = upSecondParallelLengthTotalDB.begin();
		itVecFirst != upFirstParallelLengthTotalDB.end();
		itVecFirst++, itVecSecond++)
	{
		temp = (*itVecFirst + *itVecSecond) / 2 * setUpAppendParallelLengthThresholdRatio;
		upAppendParallelLengthThresholdDB.push_back(temp);
	}
	fout << "setUpAppendParallelLengthThresholdRatio: " << setUpAppendParallelLengthThresholdRatio << endl;
}

/** \brief upAppendParallelStartAndEndNumDB
 *
 * \param vector<double> upAppendParallelLengthThresholdDB;
 * \param map<int, vector<double> > upAppendParallelStartLengthTotalDB;
 * \param map<int, vector<double> > upAppendParallelEndLengthTotalDB;
 * \return map<int, vector<double> > upAppendParallelStartNumDB;
 * \return map<int, vector<double> > upAppendParallelEndNumDB;
 *
 */
void rsPhloemDB::UpAppendParallelNumDB()
{
	map<int, vector<double> >::iterator itMapStart;
	map<int, vector<double> >::iterator itMapEnd;
	vector<double>::iterator itVecStart;
	vector<double>::iterator itVecEnd;
	vector<double>::iterator itVecThreshold;
	vector<double> upAppendParallelStartNum;
	vector<double> upAppendParallelEndNum;
	double doubleNumStart;
	double doubleNumEnd;
	int intNumStart;
	int intNumEnd;
	int i;

	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpAppendParallelNumDB" << endl;

	for (itVecThreshold = upAppendParallelLengthThresholdDB.begin(),
		itMapStart = upAppendParallelStartLengthTotalDB.begin(),
		itMapEnd = upAppendParallelEndLengthTotalDB.begin(), i = 0;
		itMapStart != upAppendParallelStartLengthTotalDB.end();
		itVecThreshold++, itMapStart++, itMapEnd++, i++)
	{
		upAppendParallelStartNum.clear();
		upAppendParallelEndNum.clear();
		for (itVecStart = (*itMapStart).second.begin(),
			itVecEnd = (*itMapEnd).second.begin();
			itVecStart != (*itMapStart).second.end();
			itVecStart++, itVecEnd++)
		{
			doubleNumStart = *itVecStart / *itVecThreshold;
			doubleNumEnd = *itVecEnd / *itVecThreshold;
			intNumStart = int(doubleNumStart + 0.5);
			intNumEnd = int(doubleNumEnd + 0.5);
			upAppendParallelStartNum.push_back(intNumStart);
			upAppendParallelEndNum.push_back(intNumEnd);

			fout << "StartNumDB: " << intNumStart
				<< "  *itVecStart: " << *itVecStart << "  *itVecThreshold: " << *itVecThreshold << endl;
			fout << "  EndNumDB: " << intNumEnd << "  *itVecEnd: " << *itVecEnd << endl;
		}
		upAppendParallelStartNumDB.insert(pair<int, vector<double> >(i, upAppendParallelStartNum));
		upAppendParallelEndNumDB.insert(pair<int, vector<double> >(i, upAppendParallelEndNum));
	}
}

/** \brief upAppendParallelStartAndEndLengthHalfDB
 *
 * \param map<int, vector<double> > upAppendParallelStartLengthTotalDB;
 * \param map<int, vector<double> > upAppendParallelEndLengthTotalDB;
 * \param map<int, vector<double> > upAppendParallelStartNumDB;
 * \param map<int, vector<double> > upAppendParallelEndNumDB;
 * \return map<int, vector<double> > upAppendParallelStartLengthHalfDB;
 * \return map<int, vector<double> > upAppendParallelEndLengthHalfDB;
 *
 */
void rsPhloemDB::UpAppendParallelLengthHalfDB()
{
	map<int, vector<double> >::iterator itMapStart;
	map<int, vector<double> >::iterator itMapEnd;
	map<int, vector<double> >::iterator itMapStartNum;
	map<int, vector<double> >::iterator itMapEndNum;
	vector<double>::iterator itVecStartNum;
	vector<double>::iterator itVecEndNum;
	vector<double>::iterator itVecEnd;
	vector<double>::iterator itVecStart;
	vector<double> upAppendParallelStartLengthHalf;
	vector<double> upAppendParallelEndLengthHalf;
	double tempStart;
	double tempEnd;
	int i;
	for (itMapStartNum = upAppendParallelStartNumDB.begin(),
		itMapEndNum = upAppendParallelEndNumDB.begin(),
		itMapStart = upAppendParallelStartLengthTotalDB.begin(),
		itMapEnd = upAppendParallelEndLengthTotalDB.begin(), i = 0;
		itMapStart != upAppendParallelStartLengthTotalDB.end();
		itMapStart++, itMapEnd++, itMapStartNum++, itMapEndNum++, i++)
	{
		upAppendParallelStartLengthHalf.clear();
		upAppendParallelEndLengthHalf.clear();
		for (itVecStart = (*itMapStart).second.begin(),
			itVecEnd = (*itMapEnd).second.begin(),
			itVecStartNum = (*itMapStartNum).second.begin(),
			itVecEndNum = (*itMapEndNum).second.begin();
			itVecStart != (*itMapStart).second.end();
			itVecStart++, itVecEnd++, itVecStartNum++, itVecEndNum++)
		{
			tempStart = *itVecStart / *itVecStartNum / double(2);
			tempEnd = *itVecEnd / *itVecEndNum / double(2);
			upAppendParallelStartLengthHalf.push_back(tempStart);
			upAppendParallelEndLengthHalf.push_back(tempEnd);
		}
		upAppendParallelStartLengthHalfDB.insert(pair<int, vector<double> >(i, upAppendParallelStartLengthHalf));
		upAppendParallelEndLengthHalfDB.insert(pair<int, vector<double> >(i, upAppendParallelEndLengthHalf));
	}
}

/** \brief upAppendParallelStartAndEndRadianDevideDB
 *
 * \param map<int, vector<double> > upAppendParallelStartRadianTotalDB;
 * \param map<int, vector<double> > upAppendParallelEndRadianTotalDB;
 * \param map<int, vector<double> > upAppendParallelStartNumDB;
 * \param map<int, vector<double> > upAppendParallelEndNumDB;
 * \return map<int, vector<double> > upAppendParallelStartRadianDevideDB;
 * \return map<int, vector<double> > upAppendParallelEndRadianDevideDB;
 *
 */
void rsPhloemDB::UpAppendParallelRadianDevideDB()
{
	map<int, vector<double> >::iterator itMapStart;
	map<int, vector<double> >::iterator itMapEnd;
	map<int, vector<double> >::iterator itMapStartNum;
	map<int, vector<double> >::iterator itMapEndNum;
	vector<double>::iterator itVecStartNum;
	vector<double>::iterator itVecEndNum;
	vector<double>::iterator itVecEnd;
	vector<double>::iterator itVecStart;
	vector<double> upAppendParallelStartRadianDevide;
	vector<double> upAppendParallelEndRadianDevide;
	double tempStart;
	double tempEnd;
	int i;
	for (itMapStartNum = upAppendParallelStartNumDB.begin(),
		itMapEndNum = upAppendParallelEndNumDB.begin(),
		itMapStart = upAppendParallelStartRadianTotalDB.begin(),
		itMapEnd = upAppendParallelEndRadianTotalDB.begin(), i = 0;
		itMapStart != upAppendParallelStartRadianTotalDB.end();
		itMapStart++, itMapEnd++, itMapStartNum++, itMapEndNum++, i++)
	{
		upAppendParallelStartRadianDevide.clear();
		upAppendParallelEndRadianDevide.clear();
		for (itVecStart = (*itMapStart).second.begin(),
			itVecEnd = (*itMapEnd).second.begin(),
			itVecStartNum = (*itMapStartNum).second.begin(),
			itVecEndNum = (*itMapEndNum).second.begin();
			itVecStart != (*itMapStart).second.end();
			itVecStart++, itVecEnd++, itVecStartNum++, itVecEndNum++)
		{
			tempStart = *itVecStart / *itVecStartNum;
			tempEnd = *itVecEnd / *itVecEndNum;
			upAppendParallelStartRadianDevide.push_back(tempStart);
			upAppendParallelEndRadianDevide.push_back(tempEnd);
		}
		upAppendParallelStartRadianDevideDB.insert(pair<int, vector<double> >(i, upAppendParallelStartRadianDevide));
		upAppendParallelEndRadianDevideDB.insert(pair<int, vector<double> >(i, upAppendParallelEndRadianDevide));
	}
}

/** \brief upAppendParallelStartAndEndCenterRadianDB
 *
 * \param vector<double> RsPXBoundaryDB -> interRadianStartDB;
 * \param vector<double> RsPXBoundaryDB -> interRadianEndDB;
 * \param map<int, vector<double> > upAppendParallelStartRadianDevideDB;
 * \param map<int, vector<double> > upAppendParallelEndRadianDevideDB;
 * \param map<int, vector<double> > upAppendParallelStartNumDB;
 * \param map<int, vector<double> > upAppendParallelEndNumDB;
 * \return map<int, vector<vector<double> > >  upAppendParallelStartCenterRadianDB;
 * \return map<int, vector<vector<double> > >  upAppendParallelEndCenterRadianDB;
 *
 */
void rsPhloemDB::UpAppendParallelCenterRadianDB()
{
	map<int, vector<double> >::iterator  itMapNum;
	map<int, vector<double> >::iterator  itMapRadianDivide;
	vector<double>::iterator itVecNum;
	vector<double>::iterator itVecRadianDivide;

	vector<double>::iterator itVecRadianStart;
	vector<double>::iterator itVecRadianEnd;

	vector<vector<double> > upAppendParallelStartCenterRadianVec2;
	vector<vector<double> > upAppendParallelEndCenterRadianVec2;
	vector<double> upAppendParallelStartCenterRadianVec1;
	vector<double> upAppendParallelEndCenterRadianVec1;
	double sum;
	double tempSum;
	double temp;
	int i;
	int j;
	int k;
	int num;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpAppendParallelCenterRadianDB" << endl;
	fout << "Start" << endl;
	/// Start;
	for (itMapNum = upAppendParallelStartNumDB.begin(),
		itVecRadianStart = interRadianStartDB.begin(),
		itMapRadianDivide = upAppendParallelStartRadianDevideDB.begin(), i = 0;
		itMapNum != upAppendParallelStartNumDB.end();
		itMapNum++, itVecRadianStart++, itMapRadianDivide++, i++)
	{
		upAppendParallelStartCenterRadianVec2.clear();
		for (itVecNum = (*itMapNum).second.begin(), itVecRadianDivide = (*itMapRadianDivide).second.begin(), j = 0;
			itVecNum != (*itMapNum).second.end();
			itVecNum++, itVecRadianDivide++, j++)
		{
			upAppendParallelStartCenterRadianVec1.clear();
			sum = 0;
			tempSum = 0;
			for (num = 0, k = 0; num != *itVecNum; num++, k++)
			{
				if (num == 0)
				{
					tempSum = 0;
					sum = tempSum + *itVecRadianDivide / 2;
					temp = *itVecRadianStart + sum;
					upAppendParallelStartCenterRadianVec1.push_back(temp);
				}
				else
				{
					tempSum += *itVecRadianDivide;
					sum = tempSum + *itVecRadianDivide / 2;
					temp = *itVecRadianStart + sum;
					upAppendParallelStartCenterRadianVec1.push_back(temp);
				}
				fout << "i: " << i << "  j: " << j << "  k: " << k <<
					"  temp: " << temp << endl;
			}
			upAppendParallelStartCenterRadianVec2.push_back(upAppendParallelStartCenterRadianVec1);
		}
		upAppendParallelStartCenterRadianDB.insert
		(pair<int, vector<vector<double> > >(i, upAppendParallelStartCenterRadianVec2));
	}
	/// End;
	fout << "End" << endl;
	for (itMapNum = upAppendParallelEndNumDB.begin(),
		itVecRadianEnd = interRadianEndDB.begin(),
		itMapRadianDivide = upAppendParallelEndRadianDevideDB.begin(), i = 0;
		itMapNum != upAppendParallelEndNumDB.end();
		itMapNum++, itVecRadianEnd++, itMapRadianDivide++, i++)
	{
		upAppendParallelEndCenterRadianVec2.clear();
		for (itVecNum = (*itMapNum).second.begin(), itVecRadianDivide = (*itMapRadianDivide).second.begin(), j = 0;
			itVecNum != (*itMapNum).second.end();
			itVecNum++, itVecRadianDivide++, j++)
		{
			upAppendParallelEndCenterRadianVec1.clear();
			sum = 0;
			tempSum = 0;
			for (num = 0, k = 0; num != *itVecNum; num++, k++)
			{
				if (num == 0)
				{
					tempSum = 0;
					sum = tempSum + *itVecRadianDivide / 2;
					temp = *itVecRadianEnd - sum;
					upAppendParallelEndCenterRadianVec1.push_back(temp);
				}
				else
				{
					tempSum += *itVecRadianDivide;
					sum = tempSum + *itVecRadianDivide / 2;
					temp = *itVecRadianEnd - sum;
					upAppendParallelEndCenterRadianVec1.push_back(temp);
				}
				fout << "i: " << i << "  j: " << j << "  k: " << k <<
					"  temp: " << temp << endl;
			}
			upAppendParallelEndCenterRadianVec2.push_back(upAppendParallelEndCenterRadianVec1);
		}
		upAppendParallelEndCenterRadianDB.insert
		(pair<int, vector<vector<double> > >(i, upAppendParallelEndCenterRadianVec2));
	}
}
/** \brief UpAppendParallelStartAndEndCenterRotateAngleDB
 *
 * \param map<int, vector<vector<double> > >  upAppendParallelStartCenterRadianDB;
 * \param map<int, vector<vector<double> > >  upAppendParallelEndCenterRadianDB;
 * \return map<int, vector<vector<double> > >  upAppendParallelStartCenterRotateAngleDB
 * \return map<int, vector<vector<double> > >  upAppendParallelEndCenterRotateAngleDB
 *
 */
void rsPhloemDB::UpAppendParallelCenterRotateAngleDB()
{
	map<int, vector<vector<double> > >::iterator  itMap;
	vector<vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;

	vector<vector<double> > upAppendParallelStartCenterRotateAngleVec2;
	vector<vector<double> > upAppendParallelEndCenterRotateAngleVec2;
	vector<double> upAppendParallelStartCenterRotateAngleVec1;
	vector<double> upAppendParallelEndCenterRotateAngleVec1;
	double tempAngle;
	int i;
	int j;
	int k;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpAppendParallelCenterRotateAngleDB" << endl;
	/// Start;
	fout << "Start" << endl;
	for (itMap = upAppendParallelStartCenterRadianDB.begin(), i = 0;
		itMap != upAppendParallelStartCenterRadianDB.end();
		itMap++, i++)
	{
		upAppendParallelStartCenterRotateAngleVec2.clear(), j = 0;
		for (itVec2 = (*itMap).second.begin();
			itVec2 != (*itMap).second.end();
			itVec2++, j++)
		{
			upAppendParallelStartCenterRotateAngleVec1.clear();
			for (itVec1 = (*itVec2).begin(), k = 0;
				itVec1 != (*itVec2).end();
				itVec1++, k++)
			{
				tempAngle = (-1) * (*itVec1) / M_PI * 180;
				upAppendParallelStartCenterRotateAngleVec1.push_back(tempAngle);
				fout << "i: " << i << "  j: " << j << "  k: " << k <<
					"  tempAngle: " << tempAngle << endl;
			}
			upAppendParallelStartCenterRotateAngleVec2.push_back(upAppendParallelStartCenterRotateAngleVec1);
		}
		upAppendParallelStartCenterRotateAngleDB.insert
		(pair<int, vector<vector<double> > >(i, upAppendParallelStartCenterRotateAngleVec2));
	}
	/// End;
	fout << "End" << endl;
	for (itMap = upAppendParallelEndCenterRadianDB.begin(), i = 0;
		itMap != upAppendParallelEndCenterRadianDB.end();
		itMap++, i++)
	{
		upAppendParallelEndCenterRotateAngleVec2.clear();
		for (itVec2 = (*itMap).second.begin(), j = 0;
			itVec2 != (*itMap).second.end();
			itVec2++, j++)
		{
			upAppendParallelEndCenterRotateAngleVec1.clear();
			for (itVec1 = (*itVec2).begin(), k = 0;
				itVec1 != (*itVec2).end();
				itVec1++, k++)
			{
				tempAngle = (-1) * (*itVec1) / M_PI * 180;
				upAppendParallelEndCenterRotateAngleVec1.push_back(tempAngle);
				fout << "i: " << i << "  j: " << j << "  k: " << k <<
					"  tempAngle: " << tempAngle << endl;
			}
			upAppendParallelEndCenterRotateAngleVec2.push_back(upAppendParallelEndCenterRotateAngleVec1);
		}
		upAppendParallelEndCenterRotateAngleDB.insert
		(pair<int, vector<vector<double> > >(i, upAppendParallelEndCenterRotateAngleVec2));
	}
}

/** \brief UpAppendCellXYDB
 *
 * \param map<int, vector<vector<double> > >  upAppendParallelStartCenterRadianDB;
 * \param map<int, vector<vector<double> > >  upAppendParallelEndCenterRadianDB;
 * \param map<int, vector<double> > upAppendCenterRadiusDB;
 * \return map<int, vector<vector<double> > > upAppendParallelStartCellXDB;
 * \return map<int, vector<vector<double> > > upAppendParallelStartCellYDB;
 * \return map<int, vector<vector<double> > > upAppendParallelEndCellXDB;
 * \return map<int, vector<vector<double> > > upAppendParallelEndCellYDB;
 *
 */
void rsPhloemDB::UpAppendCellXYDB()
{
	map<int, vector<vector<double> > >::iterator  itMap;
	vector<vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;

	map<int, vector<double> >::iterator  itMapRadius;
	vector<double>::iterator itVecRadius;

	vector<vector<double> > appendCellXVec2;
	vector<double> appendCellXVec1;
	vector<vector<double> > appendCellYVec2;
	vector<double> appendCellYVec1;

	double tempX;
	double tempY;
	int i;
	int j;
	int k;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpAppendCellXYDB" << endl;
	fout << "Start" << endl;
	/// Start;
	for (itMap = upAppendParallelStartCenterRadianDB.begin(),
		itMapRadius = upAppendCenterRadiusDB.begin(), i = 0;
		itMap != upAppendParallelStartCenterRadianDB.end();
		itMap++, itMapRadius++, i++)
	{
		appendCellXVec2.clear();
		appendCellYVec2.clear();
		for (itVec2 = (*itMap).second.begin(), itVecRadius = (*itMapRadius).second.begin(), j = 0;
			itVec2 != (*itMap).second.end();
			itVec2++, itVecRadius++, j++)
		{
			appendCellXVec1.clear();
			appendCellYVec1.clear();
			for (itVec1 = (*itVec2).begin(), k = 0;
				itVec1 != (*itVec2).end();
				itVec1++, k++)
			{
				tempX = (*itVecRadius) * cos(*itVec1);
				tempY = (*itVecRadius) * sin(*itVec1);
				appendCellXVec1.push_back(tempX);
				appendCellYVec1.push_back(tempY);
				fout << "i: " << i << "  j: " << j << "  k: " << k <<
					"  tempX: " << tempX << "  tempY: " << tempY
					<< "  appendVerticalCenterRadiusDB: " << *itVecRadius
					<< "  appendCellCenterRadianDB: " << *itVec1 << endl;
			}
			appendCellXVec2.push_back(appendCellXVec1);
			appendCellYVec2.push_back(appendCellYVec1);
		}
		upAppendStartCellXDB.insert(pair<int, vector<vector<double> > >(i, appendCellXVec2));
		upAppendStartCellYDB.insert(pair<int, vector<vector<double> > >(i, appendCellYVec2));
	}
	fout << "End" << endl;
	/// End;
	for (itMap = upAppendParallelEndCenterRadianDB.begin(),
		itMapRadius = upAppendCenterRadiusDB.begin(), i = 0;
		itMap != upAppendParallelEndCenterRadianDB.end();
		itMap++, itMapRadius++, i++)
	{
		appendCellXVec2.clear();
		appendCellYVec2.clear();
		for (itVec2 = (*itMap).second.begin(), itVecRadius = (*itMapRadius).second.begin(), j = 0;
			itVec2 != (*itMap).second.end();
			itVec2++, itVecRadius++, j++)
		{
			appendCellXVec1.clear();
			appendCellYVec1.clear();
			for (itVec1 = (*itVec2).begin(), k = 0;
				itVec1 != (*itVec2).end();
				itVec1++, k++)
			{
				tempX = (*itVecRadius) * cos(*itVec1);
				tempY = (*itVecRadius) * sin(*itVec1);
				appendCellXVec1.push_back(tempX);
				appendCellYVec1.push_back(tempY);
				fout << "i: " << i << "  j: " << j << "  k: " << k <<
					"  tempX: " << tempX << "  tempY: " << tempY
					<< "  appendVerticalCenterRadiusDB: " << *itVecRadius
					<< "  appendCellCenterRadianDB: " << *itVec1 << endl;
			}
			appendCellXVec2.push_back(appendCellXVec1);
			appendCellYVec2.push_back(appendCellYVec1);
		}
		upAppendEndCellXDB.insert(pair<int, vector<vector<double> > >(i, appendCellXVec2));
		upAppendEndCellYDB.insert(pair<int, vector<vector<double> > >(i, appendCellYVec2));
	}
}

/******************************************************
// Create RandomHeightDB;
*******************************************************/
void rsPhloemDB::RandomHeightDB(double totalHeight, int sliceNum, double initZPosition, int VectorNum)
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

/** \brief UpAppendObjectHeightAndZPositionDB
 *
 * \param map<int, vector<vector<double> > > upAppendStartCellXDB;
 * \param map<int, vector<vector<double> > > upAppendEndCellXDB;
 * \return map<int, vector<vector<vector<double> > > > upAppendStartCellObjectHeightDB;
 * \return map<int, vector<vector<vector<double> > > > upAppendStartCellObjectZPositionDB;
 * \return map<int, vector<vector<vector<double> > > > upAppendEndCellObjectHeightDB;
 * \return map<int, vector<vector<vector<double> > > > upAppendEndCellObjectZPositionDB;
 *
 */
void rsPhloemDB::UpAppendObjectHeightAndZPositionDB(int sliceNum)
{  /// declare iterator;
	map<int, vector <vector<double> > >::iterator itMap;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;
	/// Height
	vector< vector <vector<double> > > objectHeightVec3;
	vector< vector<double> >           objectHeightVec2;
	vector<double>                     objectHeightVec1;
	/// ZPosition
	vector< vector <vector<double> > > objectZPositionVec3;
	vector< vector<double> >           objectZPositionVec2;
	vector<double>                     objectZPositionVec1;

	/// declare int;
	int i;
	int iRingNum;
	int cellNum;
	int sliceTempNum;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpAppendObjectHeightAndZPositionDB" << endl;
	/// Start;
	fout << "Start" << endl;
	for (i = 0, itMap = upAppendStartCellXDB.begin();
		itMap != upAppendStartCellXDB.end();
		i++, itMap++)
	{
		objectHeightVec3.clear();
		objectZPositionVec3.clear();
		for (iRingNum = 0, itVec2 = (*itMap).second.begin();
			itVec2 != (*itMap).second.end();
			iRingNum++, itVec2++)
		{
			objectHeightVec2.clear();
			objectZPositionVec2.clear();
			for (cellNum = 0, itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				cellNum++, itVec1++)
			{
				objectHeightVec1.clear();
				objectZPositionVec1.clear();
				int randomHeightZPosition = rand() % 200;
				for (sliceTempNum = 0;
					sliceTempNum != sliceNum;
					sliceTempNum++)
				{  /// Height;
					objectHeightVec1.push_back
					(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio);
					fout << "i: " << i << "  iRingNum: " << iRingNum << "  cellNum: " << cellNum
						<< "  sliceTempNum: " << sliceTempNum << "  Height: " << longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum]
						<< endl;
					/// ZPosition;
					objectZPositionVec1.push_back
					(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
					fout << "i: " << i << "  iRingNum: " << iRingNum << "  cellNum: " << cellNum
						<< "  sliceTempNum: " << sliceTempNum << "  ZPosition: " << longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]
						<< endl;
				}
				objectHeightVec2.push_back(objectHeightVec1);
				objectZPositionVec2.push_back(objectZPositionVec1);
			}
			objectHeightVec3.push_back(objectHeightVec2);
			objectZPositionVec3.push_back(objectZPositionVec2);
		}
		upAppendStartCellObjectHeightDB.insert
		(pair<int, vector< vector <vector<double> > > >(i, objectHeightVec3));
		upAppendStartCellObjectZPositionDB.insert
		(pair<int, vector< vector <vector<double> > > >(i, objectZPositionVec3));
	}
	/// End;
	fout << "End" << endl;
	for (i = 0, itMap = upAppendEndCellXDB.begin();
		itMap != upAppendEndCellXDB.end();
		i++, itMap++)
	{
		objectHeightVec3.clear();
		objectZPositionVec3.clear();
		for (iRingNum = 0, itVec2 = (*itMap).second.begin();
			itVec2 != (*itMap).second.end();
			iRingNum++, itVec2++)
		{
			objectHeightVec2.clear();
			objectZPositionVec2.clear();
			for (cellNum = 0, itVec1 = (*itVec2).begin();
				itVec1 != (*itVec2).end();
				cellNum++, itVec1++)
			{
				objectHeightVec1.clear();
				objectZPositionVec1.clear();
				int randomHeightZPosition = rand() % 200;
				for (sliceTempNum = 0;
					sliceTempNum != sliceNum;
					sliceTempNum++)
				{  /// Height;
					objectHeightVec1.push_back
					(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio);
					fout << "i: " << i << "  iRingNum: " << iRingNum << "  cellNum: " << cellNum
						<< "  sliceTempNum: " << sliceTempNum << "  Height: " << longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum]
						<< endl;
					/// ZPosition;
					objectZPositionVec1.push_back
					(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
					fout << "i: " << i << "  iRingNum: " << iRingNum << "  cellNum: " << cellNum
						<< "  sliceTempNum: " << sliceTempNum << "  ZPosition: " << longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]
						<< endl;
				}
				objectHeightVec2.push_back(objectHeightVec1);
				objectZPositionVec2.push_back(objectZPositionVec1);
			}
			objectHeightVec3.push_back(objectHeightVec2);
			objectZPositionVec3.push_back(objectZPositionVec2);
		}
		upAppendEndCellObjectHeightDB.insert
		(pair<int, vector< vector <vector<double> > > >(i, objectHeightVec3));
		upAppendEndCellObjectZPositionDB.insert
		(pair<int, vector< vector <vector<double> > > >(i, objectZPositionVec3));
	}
}



///////////////////////////////// Phloem /////////////////////////////////////////////////


/** \brief UpPhloemParallelLengthTotalDB
 *
 * \param vector<double> upFirstPhloemParallelRadianTotalDB;
 * \param vector<double> upSecondPhloemParallelRadianTotalDB;
 * \param vector<double> upFirstPhloemCenterRadiusDB;
 * \param vector<double> upSecondPhloemCenterRadiusDB;
 * \return vector<double> upFirstPhloemParallelLengthTotalDB;
 * \return vector<double> upSecondPhloemParallelLengthTotalDB;
 *
 */
vector<double> upFirstPhloemParallelLengthTotalDB;
vector<double> upSecondPhloemParallelLengthTotalDB;
void rsPhloemDB::UpPhloemParallelLengthTotalDB()
{
	vector<double>::iterator itVecRadius;
	vector<double>::iterator itVecRadian;
	double temp;
	/// First;
	for (itVecRadian = upFirstPhloemParallelRadianTotalDB.begin(),
		itVecRadius = upFirstPhloemCenterRadiusDB.begin();
		itVecRadian != upFirstPhloemParallelRadianTotalDB.end();
		itVecRadian++, itVecRadius++)
	{
		temp = 2 * M_PI * (*itVecRadius) * (*itVecRadian / (2 * M_PI));
		upFirstPhloemParallelLengthTotalDB.push_back(temp);
	}
	/// Second;
	for (itVecRadian = upSecondPhloemParallelRadianTotalDB.begin(),
		itVecRadius = upSecondPhloemCenterRadiusDB.begin();
		itVecRadian != upSecondPhloemParallelRadianTotalDB.end();
		itVecRadian++, itVecRadius++)
	{
		temp = 2 * M_PI * (*itVecRadius) * (*itVecRadian / (2 * M_PI));
		upSecondPhloemParallelLengthTotalDB.push_back(temp);
	}
}





/** \brief UpPhloemParallelLengthSegmentDB
 *
 * \param vector<double> upFirstPhloemParallelLengthTotalDB;
 * \param vector<double> upSecondPhloemParallelLengthTotalDB;
 * \param vector<int> upFirstPhloemParallelNumDB;
 * \param vector<int> upSecondPhloemParallelNumDB;
 * \return map<int, vector<double> > upFirstPhloemParallelLengthSegmentDB;
 * \return map<int, vector<double> > upSecondPhloemParallelLengthSegmentDB;
 * \return map<int, vector<double> > upFirstPhloemParallelLengthSegmentAddDB;
 * \return map<int, vector<double> > upSecondPhloemParallelLengthSegmentAddDB;
 *
 */

void rsPhloemDB::UpPhloemParallelLengthSegmentDB(double variationRatio)
{
	vector<int>::iterator itVecNum;
	vector<double>::iterator itVecLengthTotal;
	vector<double> upFirstPhloemParallelLengthSegment;
	vector<double> upFirstPhloemParallelLengthSegmentAdd;
	vector<double> upSecondPhloemParallelLengthSegment;
	vector<double> upSecondPhloemParallelLengthSegmentAdd;
	int i;
	ofstream fout(getFolderName() + "CalculateRandom.txt", ios::app);
	fout << "UpPhloemParallelLengthSegmentDB" << endl;
	/// First;
	fout << "First" << endl;
	for (itVecLengthTotal = upFirstPhloemParallelLengthTotalDB.begin(),
		itVecNum = upFirstPhloemParallelNumDB.begin(), i = 0;
		itVecLengthTotal != upFirstPhloemParallelLengthTotalDB.end();
		itVecLengthTotal++, itVecNum++, i++)
	{
		RandomRatioButSameSumAndNumber(upFirstPhloemParallelLengthSegment,
			upFirstPhloemParallelLengthSegmentAdd,
			*itVecLengthTotal,
			*itVecNum,
			variationRatio);
		upFirstPhloemParallelLengthSegmentDB.insert
		(pair<int, vector<double> >(i, upFirstPhloemParallelLengthSegment));
		upFirstPhloemParallelLengthSegmentAddDB.insert
		(pair<int, vector<double> >(i, upFirstPhloemParallelLengthSegmentAdd));
		fout << "i: " << i << "  *itVecLengthTotal: " << *itVecLengthTotal
			<< "  *itVecNum: " << *itVecNum << endl;
	}
	/// Second;
	fout << "Second" << endl;
	for (itVecLengthTotal = upSecondPhloemParallelLengthTotalDB.begin(),
		itVecNum = upSecondPhloemParallelNumDB.begin(), i = 0;
		itVecLengthTotal != upSecondPhloemParallelLengthTotalDB.end();
		itVecLengthTotal++, itVecNum++, i++)
	{
		RandomRatioButSameSumAndNumber(upSecondPhloemParallelLengthSegment,
			upSecondPhloemParallelLengthSegmentAdd,
			*itVecLengthTotal,
			*itVecNum,
			variationRatio);
		upSecondPhloemParallelLengthSegmentDB.insert
		(pair<int, vector<double> >(i, upSecondPhloemParallelLengthSegment));
		upSecondPhloemParallelLengthSegmentAddDB.insert
		(pair<int, vector<double> >(i, upSecondPhloemParallelLengthSegmentAdd));
		fout << "i: " << i << "  *itVecLengthTotal: " << *itVecLengthTotal << "  *itVecNum: " << *itVecNum << endl;
	}
}

/** \brief UpPhloemParallelLengthSegmentHalfDB
 *
 * \param map<int, vector<double> > upFirstPhloemParallelLengthSegmentDB;
 * \param map<int, vector<double> > upSecondPhloemParallelLengthSegmentDB;
 * \return map<int, vector<double> > upFirstPhloemParallelLengthSegmentHalfDB;
 * \return map<int, vector<double> > upSecondPhloemParallelLengthSegmentHalfDB;
 *
 */
map<int, vector<double> > upFirstPhloemParallelLengthSegmentHalfDB;
map<int, vector<double> > upSecondPhloemParallelLengthSegmentHalfDB;
void rsPhloemDB::UpPhloemParallelLengthSegmentHalfDB()
{
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec;
	vector<double> itVecHalf;
	double temp;
	int i;
	/// First;
	for (itMap = upFirstPhloemParallelLengthSegmentDB.begin(), i = 0;
		itMap != upFirstPhloemParallelLengthSegmentDB.end();
		itMap++, i++)
	{
		itVecHalf.clear();
		for (itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			itVec++)
		{
			temp = *itVec / 2;
			itVecHalf.push_back(temp);
		}
		upFirstPhloemParallelLengthSegmentHalfDB.insert
		(pair<int, vector<double> >(i, itVecHalf));
	}

	/// Second;
	for (itMap = upSecondPhloemParallelLengthSegmentDB.begin(), i = 0;
		itMap != upSecondPhloemParallelLengthSegmentDB.end();
		itMap++, i++)
	{
		itVecHalf.clear();
		for (itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			itVec++)
		{
			temp = *itVec / 2;
			itVecHalf.push_back(temp);
		}
		upSecondPhloemParallelLengthSegmentHalfDB.insert
		(pair<int, vector<double> >(i, itVecHalf));
	}
}


/** \brief UpPhloemParallelRadianSegmentDB
 *
 * \param map<int, vector<double> > upFirstPhloemParallelLengthSegmentDB;
 * \param map<int, vector<double> > upSecondPhloemParallelLengthSegmentDB;
 * \param map<int, vector<double> > upFirstPhloemParallelLengthSegmentAddDB;
 * \param map<int, vector<double> > upSecondPhloemParallelLengthSegmentAddDB;
 * \param vector<double> upFirstParallelLengthTotalDB;
 * \param vector<double> upSecondParallelLengthTotalDB;
 * \param vector<double> interIntersectionRadianDB;
 * \return map<int, vector<double> > upFirstPhloemParallelRadianSegmentDB;
 * \return map<int, vector<double> > upSecondPhloemParallelRadianSegmentDB;
 * \return map<int, vector<double> > upFirstPhloemParallelRadianSegmentAddDB;
 * \return map<int, vector<double> > upSecondPhloemParallelRadianSegmentAddDB;
 *
 */
map<int, vector<double> > upFirstPhloemParallelRadianSegmentDB;
map<int, vector<double> > upSecondPhloemParallelRadianSegmentDB;
map<int, vector<double> > upFirstPhloemParallelRadianSegmentAddDB;
map<int, vector<double> > upSecondPhloemParallelRadianSegmentAddDB;
void rsPhloemDB::UpPhloemParallelRadianSegmentDB()
{
	map<int, vector<double> >::iterator itMap;
	map<int, vector<double> >::iterator itMapAdd;
	vector<double>::iterator itVec;
	vector<double>::iterator itVecAdd;

	vector<double>::iterator itVecRadian;
	vector<double>::iterator itVecLengthTotal;

	vector<double> upFirstPhloemParallelRadianSegment;
	vector<double> upSecondPhloemParallelRadianSegment;
	vector<double> upFirstPhloemParallelRadianSegmentAdd;
	vector<double> upSecondPhloemParallelRadianSegmentAdd;
	double temp;
	double tempAdd;
	int i;
	ofstream fout(getFolderName() + "CalculateRandom.txt", ios::app);
	fout << "UpPhloemParallelRadianSegmentDB" << endl;
	/// First;
	fout << "First" << endl;
	for (itMap = upFirstPhloemParallelLengthSegmentDB.begin(),
		itMapAdd = upFirstPhloemParallelLengthSegmentAddDB.begin(),
		itVecRadian = interIntersectionRadianDB.begin(),
		itVecLengthTotal = upFirstParallelLengthTotalDB.begin(),
		i = 0;
		itMap != upFirstPhloemParallelLengthSegmentDB.end();
		itMap++, itMapAdd++, itVecRadian++, itVecLengthTotal++, i++)
	{
		upFirstPhloemParallelRadianSegment.clear();
		upFirstPhloemParallelRadianSegmentAdd.clear();
		for (itVec = (*itMap).second.begin(), itVecAdd = (*itMapAdd).second.begin();
			itVec != (*itMap).second.end();
			itVec++, itVecAdd++)
		{
			temp = (*itVec / (*itVecLengthTotal)) * (*itVecRadian);
			tempAdd = (*itVecAdd / (*itVecLengthTotal)) * (*itVecRadian);
			upFirstPhloemParallelRadianSegment.push_back(temp);
			upFirstPhloemParallelRadianSegmentAdd.push_back(tempAdd);
			fout << "i: " << i << "  temp: " << temp << "  tempAdd: " << tempAdd << endl;
		}
		upFirstPhloemParallelRadianSegmentDB.insert
		(pair<int, vector<double> >(i, upFirstPhloemParallelRadianSegment));
		upFirstPhloemParallelRadianSegmentAddDB.insert
		(pair<int, vector<double> >(i, upFirstPhloemParallelRadianSegmentAdd));
	}
	/// Second;
	fout << "Second" << endl;
	for (itMap = upSecondPhloemParallelLengthSegmentDB.begin(),
		itMapAdd = upSecondPhloemParallelLengthSegmentAddDB.begin(),
		itVecRadian = interIntersectionRadianDB.begin(),
		itVecLengthTotal = upSecondParallelLengthTotalDB.begin(),
		i = 0;
		itMap != upSecondPhloemParallelLengthSegmentDB.end();
		itMap++, itMapAdd++, itVecRadian++, itVecLengthTotal++, i++)
	{
		upSecondPhloemParallelRadianSegment.clear();
		upSecondPhloemParallelRadianSegmentAdd.clear();
		for (itVec = (*itMap).second.begin(), itVecAdd = (*itMapAdd).second.begin();
			itVec != (*itMap).second.end();
			itVec++, itVecAdd++)
		{
			temp = *itVec / (*itVecLengthTotal) * (*itVecRadian);
			tempAdd = *itVecAdd / (*itVecLengthTotal) * (*itVecRadian);
			upSecondPhloemParallelRadianSegment.push_back(temp);
			upSecondPhloemParallelRadianSegmentAdd.push_back(tempAdd);
			fout << "i: " << i << "  temp: " << temp << "  tempAdd: " << tempAdd << endl;
		}
		upSecondPhloemParallelRadianSegmentDB.insert
		(pair<int, vector<double> >(i, upSecondPhloemParallelRadianSegment));
		upSecondPhloemParallelRadianSegmentAddDB.insert
		(pair<int, vector<double> >(i, upSecondPhloemParallelRadianSegmentAdd));
	}
}

/** \brief UpPhloemParallelCenterRadianDB
 *
 * \param map<int, vector<double> > upFirstPhloemParallelRadianSegmentDB;
 * \param map<int, vector<double> > upSecondPhloemParallelRadianSegmentDB;
 * \param map<int, vector<double> > upFirstPhloemParallelRadianSegmentAddDB;
 * \param map<int, vector<double> > upSecondPhloemParallelRadianSegmentAddDB;
 * \param vector<double> interRadianStartDB;
 * \param vector<double> upFirstAppendParallelStartRadianTotalDB;
 * \param vector<double> upSecondAppendParallelStartRadianTotalDB;
 * \return map<int, vector<double> > upFirstPhloemParallelCenterRadianDB;
 * \return map<int, vector<double> > upSecondPhloemParallelCenterRadianDB;
 *
 */
map<int, vector<double> > upFirstPhloemParallelCenterRadianDB;
map<int, vector<double> > upSecondPhloemParallelCenterRadianDB;
void rsPhloemDB::UpPhloemParallelCenterRadianDB()
{
	map<int, vector<double> >::iterator  itMapRadianSegmentAdd;
	vector<double>::iterator itVecRadianSegmentAdd;
	map<int, vector<double> >::iterator  itMapRadianSegment;
	vector<double>::iterator itVecRadianSegment;

	vector<double>::iterator itVecAppendStartRadian;
	vector<double>::iterator itVecRadianStart;
	vector<double> upFirstPhloemParallelCenterRadian;
	vector<double> upSecondPhloemParallelCenterRadian;

	double temp;
	int i;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpPhloemParallelCenterRadianDB" << endl;
	/// First;
	fout << "First" << endl;
	for (itMapRadianSegmentAdd = upFirstPhloemParallelRadianSegmentAddDB.begin(),
		itMapRadianSegment = upFirstPhloemParallelRadianSegmentDB.begin(),
		itVecRadianStart = interRadianStartDB.begin(),
		itVecAppendStartRadian = upFirstAppendParallelStartRadianTotalDB.begin(),
		i = 0;
		itMapRadianSegmentAdd != upFirstPhloemParallelRadianSegmentAddDB.end();
		itMapRadianSegmentAdd++, itVecRadianStart++, itVecAppendStartRadian++, itMapRadianSegment++, i++)
	{
		upFirstPhloemParallelCenterRadian.clear();
		for (itVecRadianSegmentAdd = (*itMapRadianSegmentAdd).second.begin(),
			itVecRadianSegment = (*itMapRadianSegment).second.begin();
			itVecRadianSegmentAdd != (*itMapRadianSegmentAdd).second.end();
			itVecRadianSegmentAdd++, itVecRadianSegment++)
		{
			temp = *itVecRadianStart + *itVecAppendStartRadian + *itVecRadianSegmentAdd + *itVecRadianSegment / 2;
			upFirstPhloemParallelCenterRadian.push_back(temp);
			fout << "i: " << i << "  temp: " << temp << endl;
		}
		upFirstPhloemParallelCenterRadianDB.insert(pair<int, vector<double> >(i, upFirstPhloemParallelCenterRadian));
	}
	/// Second;
	fout << "First" << endl;
	for (itMapRadianSegmentAdd = upSecondPhloemParallelRadianSegmentAddDB.begin(),
		itMapRadianSegment = upSecondPhloemParallelRadianSegmentDB.begin(),
		itVecRadianStart = interRadianStartDB.begin(),
		itVecAppendStartRadian = upSecondAppendParallelStartRadianTotalDB.begin(),
		i = 0;
		itMapRadianSegmentAdd != upSecondPhloemParallelRadianSegmentAddDB.end();
		itMapRadianSegmentAdd++, itVecRadianStart++, itVecAppendStartRadian++, itMapRadianSegment++, i++)
	{
		upSecondPhloemParallelCenterRadian.clear();
		for (itVecRadianSegmentAdd = (*itMapRadianSegmentAdd).second.begin(),
			itVecRadianSegment = (*itMapRadianSegment).second.begin();
			itVecRadianSegmentAdd != (*itMapRadianSegmentAdd).second.end();
			itVecRadianSegmentAdd++, itVecRadianSegment++)
		{
			temp = *itVecRadianStart + *itVecAppendStartRadian + *itVecRadianSegmentAdd + *itVecRadianSegment / 2;
			upSecondPhloemParallelCenterRadian.push_back(temp);
			fout << "i: " << i << "  temp: " << temp << endl;
		}
		upSecondPhloemParallelCenterRadianDB.insert(pair<int, vector<double> >(i, upSecondPhloemParallelCenterRadian));
	}
}
/** \brief UpPhloemParallelCenterRotateAngleDB
 *
 * \param map<int, vector<double> > upFirstPhloemParallelCenterRadianDB;
 * \param map<int, vector<double> > upSecondPhloemParallelCenterRadianDB;
 * \return map<int, vector<double> >  upFirstPhloemParallelCenterRotateAngleDB
 * \return map<int, vector<double> >  upSecondPhloemParallelCenterRotateAngleDB
 *
 */
void rsPhloemDB::UpPhloemParallelCenterRotateAngleDB()
{
	map<int, vector<double> >::iterator  itMap;
	vector<double>::iterator itVec;

	vector<double> upFirstPhloemParallelCenterRotateAngle;
	vector<double> upSecondPhloemParallelCenterRotateAngle;
	double tempAngle;
	int i;
	int j = 0;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpPhloemParallelCenterRotateAngleDB" << endl;
	/// First;
	fout << "First" << endl;
	for (itMap = upFirstPhloemParallelCenterRadianDB.begin(), i = 0;
		itMap != upFirstPhloemParallelCenterRadianDB.end();
		itMap++, i++)
	{
		upFirstPhloemParallelCenterRotateAngle.clear();
		for (itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			itVec++, j++)

		{
			tempAngle = (-1) * (*itVec) / M_PI * 180;
			upFirstPhloemParallelCenterRotateAngle.push_back(tempAngle);
			fout << "i: " << i << "  j: " << j <<
				"  tempAngle: " << tempAngle << endl;
		}
		upFirstPhloemParallelCenterRotateAngleDB.insert
		(pair<int, vector<double> >(i, upFirstPhloemParallelCenterRotateAngle));
	}
	/// Second;
	fout << "Second" << endl;
	for (itMap = upSecondPhloemParallelCenterRadianDB.begin(), i = 0;
		itMap != upSecondPhloemParallelCenterRadianDB.end();
		itMap++, i++)
	{
		upSecondPhloemParallelCenterRotateAngle.clear();
		for (itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			itVec++, j++)
		{
			tempAngle = (-1) * (*itVec) / M_PI * 180;
			upSecondPhloemParallelCenterRotateAngle.push_back(tempAngle);
			fout << "i: " << i << "  j: " << j <<
				"  tempAngle: " << tempAngle << endl;
		}
		upSecondPhloemParallelCenterRotateAngleDB.insert
		(pair<int, vector<double> >(i, upSecondPhloemParallelCenterRotateAngle));
	}
}

/** \brief UpPhloemCellXYDB
 *
 * \param map<int, vector<double> > upFirstPhloemParallelCenterRadianDB;
 * \param map<int, vector<double> > upSecondPhloemParallelCenterRadianDB;
 * \param vector<double> upFirstPhloemCenterRadiusDB;
 * \param vector<double> upSecondPhloemCenterRadiusDB;
 * \return map<int, vector<double> > upFirstPhloemParallelCellXDB;
 * \return map<int, vector<double> > upFirstPhloemParallelCellYDB;
 * \return map<int, vector<double> > upSecondPhloemParallelCellXDB;
 * \return map<int, vector<double> > upSecondPhloemParallelCellYDB;
 *
 */
map<int, vector<double> > upFirstPhloemParallelCellXDB;
map<int, vector<double> > upFirstPhloemParallelCellYDB;
map<int, vector<double> > upSecondPhloemParallelCellXDB;
map<int, vector<double> > upSecondPhloemParallelCellYDB;
void rsPhloemDB::UpPhloemCellXYDB()
{
	map<int, vector<double> >::iterator  itMap;
	vector<double>::iterator itVec;
	vector<double>::iterator itVecRadius;
	vector<double> phloemCellXVec;
	vector<double> phloemCellYVec;

	double tempX;
	double tempY;
	int i;
	int j;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpPhloemCellXYDB" << endl;
	fout << "First" << endl;
	/// First;
	for (itMap = upFirstPhloemParallelCenterRadianDB.begin(),
		itVecRadius = upFirstPhloemCenterRadiusDB.begin(), i = 0;
		itMap != upFirstPhloemParallelCenterRadianDB.end();
		itMap++, itVecRadius++, i++)
	{
		phloemCellXVec.clear();
		phloemCellYVec.clear();
		for (itVec = (*itMap).second.begin(), j = 0;
			itVec != (*itMap).second.end();
			itVec++, j++)
		{
			tempX = (*itVecRadius) * cos(*itVec);
			tempY = (*itVecRadius) * sin(*itVec);
			phloemCellXVec.push_back(tempX);
			phloemCellYVec.push_back(tempY);
			fout << "i: " << i << "  j: " << j <<
				"  tempX: " << tempX << "  tempY: " << tempY << endl;
		}
		upFirstPhloemParallelCellXDB.insert(pair<int, vector<double> >(i, phloemCellXVec));
		upFirstPhloemParallelCellYDB.insert(pair<int, vector<double> >(i, phloemCellYVec));
	}
	fout << "Second" << endl;
	/// Second;
	for (itMap = upSecondPhloemParallelCenterRadianDB.begin(),
		itVecRadius = upSecondPhloemCenterRadiusDB.begin(), i = 0;
		itMap != upSecondPhloemParallelCenterRadianDB.end();
		itMap++, itVecRadius++, i++)
	{
		phloemCellXVec.clear();
		phloemCellYVec.clear();
		for (itVec = (*itMap).second.begin(), j = 0;
			itVec != (*itMap).second.end();
			itVec++, j++)
		{
			tempX = (*itVecRadius) * cos(*itVec);
			tempY = (*itVecRadius) * sin(*itVec);
			phloemCellXVec.push_back(tempX);
			phloemCellYVec.push_back(tempY);
			fout << "i: " << i << "  j: " << j <<
				"  tempX: " << tempX << "  tempY: " << tempY << endl;
		}
		upSecondPhloemParallelCellXDB.insert(pair<int, vector<double> >(i, phloemCellXVec));
		upSecondPhloemParallelCellYDB.insert(pair<int, vector<double> >(i, phloemCellYVec));
	}
}

/** \brief UpPhloemObjectHeightAndZPositionDB
 *
 * \param map<int, vector<double> > upFirstPhloemParallelCellXDB;
 * \param map<int, vector<double> > upSecondPhloemParallelCellXDB;
 * \return map<int, vector<vector<double> > > upFirstPhloemCellObjectHeightDB;
 * \return map<int, vector<vector<double> > > upFirstPhloemCellObjectZPositionDB;
 * \return map<int, vector<vector<double> > > upSecondPhloemCellObjectHeightDB;
 * \return map<int, vector<vector<double> > > upSecondPhloemCellObjectZPositionDB;
 *
 */
void rsPhloemDB::UpPhloemObjectHeightAndZPositionDB(int sliceNum)
{  /// declare iterator;
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec;
	/// Height
	vector< vector<double> >           objectHeightVec2;
	vector<double>                     objectHeightVec1;
	/// ZPosition
	vector< vector<double> >           objectZPositionVec2;
	vector<double>                     objectZPositionVec1;

	/// declare int;
	int i;
	int cellNum;
	int sliceTempNum;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpPhloemObjectHeightAndZPositionDB" << endl;
	/// First;
	fout << "First" << endl;
	for (i = 0, itMap = upFirstPhloemParallelCellXDB.begin();
		itMap != upFirstPhloemParallelCellXDB.end();
		i++, itMap++)
	{
		objectHeightVec2.clear();
		objectZPositionVec2.clear();
		for (cellNum = 0, itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			cellNum++, itVec++)
		{
			objectHeightVec1.clear();
			objectZPositionVec1.clear();
			int randomHeightZPosition = rand() % 200;
			for (sliceTempNum = 0;
				sliceTempNum != sliceNum;
				sliceTempNum++)
			{  /// Height;
				objectHeightVec1.push_back
				(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio);
				fout << "i: " << i << "  cellNum: " << cellNum << "  sliceTempNum: " << sliceTempNum
					<< "  Height: " << longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] << endl;
				/// ZPosition;
				objectZPositionVec1.push_back
				(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
				fout << "i: " << i << "  cellNum: " << cellNum << "  sliceTempNum: " << sliceTempNum
					<< "  ZPosition: " << longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum] << endl;
			}
			objectHeightVec2.push_back(objectHeightVec1);
			objectZPositionVec2.push_back(objectZPositionVec1);
		}
		upFirstPhloemCellObjectHeightDB.insert
		(pair<int, vector <vector<double> > >(i, objectHeightVec2));
		upFirstPhloemCellObjectZPositionDB.insert
		(pair<int, vector <vector<double> > >(i, objectZPositionVec2));
	}
	/// Second;
	fout << "Second" << endl;
	for (i = 0, itMap = upSecondPhloemParallelCellXDB.begin();
		itMap != upSecondPhloemParallelCellXDB.end();
		i++, itMap++)
	{
		objectHeightVec2.clear();
		objectZPositionVec2.clear();
		for (cellNum = 0, itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			cellNum++, itVec++)
		{
			objectHeightVec1.clear();
			objectZPositionVec1.clear();
			int randomHeightZPosition = rand() % 200;
			for (sliceTempNum = 0;
				sliceTempNum != sliceNum;
				sliceTempNum++)
			{  /// Height;
				objectHeightVec1.push_back
				(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio);
				fout << "i: " << i << "  cellNum: " << cellNum << "  sliceTempNum: " << sliceTempNum
					<< "  Height: " << longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] << endl;
				/// ZPosition;
				objectZPositionVec1.push_back
				(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
				fout << "i: " << i << "  cellNum: " << cellNum << "  sliceTempNum: " << sliceTempNum
					<< "  ZPosition: " << longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum] << endl;
			}
			objectHeightVec2.push_back(objectHeightVec1);
			objectZPositionVec2.push_back(objectZPositionVec1);
		}
		upSecondPhloemCellObjectHeightDB.insert
		(pair<int, vector <vector<double> > >(i, objectHeightVec2));
		upSecondPhloemCellObjectZPositionDB.insert
		(pair<int, vector <vector<double> > >(i, objectZPositionVec2));
	}
}

/** \brief InitAppendCell
 *
 * \param
 * \param
 * \return
 *
 */

void rsPhloemDB::InitUpCell
(rsPXBoundaryDB* RsPXBoundaryDB,
	double setUpAppendParallelLengthThresholdRatio,
	double totalHeight,
	int sliceNum,
	double initZPosition,
	int vectorNum,
	double variationRatio
)
{
	InterRadianStartAndEndDB(RsPXBoundaryDB);

	UpVerticalLengthTotalDB(RsPXBoundaryDB);

	PhloemVerticalLengthHalfDB();

	UpAppendVerticalLengthDB();

	UpAppendVerticalLengthHalfDB();

	BoundaryMXPXRingRadiusDeliver(RsPXBoundaryDB);

	PhloemCenterRadius();

	UpFirstSecondPhloemParallelNumDB();

	PhloemRadianRatioDB();

	UpFirstSecondPhloemParallelRadianTotalDB();

	UpAppendCenterRadiusDB();

	UpFirstSecondAppendParallelRadianTotalDB();

	UpAppendParallelRadianTotalRatioDB();

	UpFirstSecondAppendParallelStartAndEndRadianTotalDB();

	UpAppendParallelRadianTotal();

	UpAppendParallelLengthTotalDB();

	UpParallelLengthTotalDB();

	UpAppendParallelLengthThresholdDB(setUpAppendParallelLengthThresholdRatio);

	UpAppendParallelNumDB();

	UpAppendParallelLengthHalfDB();

	UpAppendParallelRadianDevideDB();

	UpAppendParallelCenterRadianDB();

	UpAppendParallelCenterRotateAngleDB();

	UpAppendCellXYDB();

	RandomHeightDB(totalHeight, sliceNum, initZPosition, vectorNum);

	/// must initialize objectXYZRadiusRatio before UpAppendObjectHeightAndZPositionDB calculate;
	SetObjectXYZRadiusRatio();
	UpAppendObjectHeightAndZPositionDB(sliceNum);

	/////////////////// Phloem ////////////////////////////

	ofstream fout(getFolderName() + "CalculateRandom.txt", ios::app);
	fout << "Phloem" << endl;

	UpPhloemParallelLengthTotalDB();

	UpPhloemParallelLengthSegmentDB(variationRatio);

	UpPhloemParallelLengthSegmentHalfDB();

	UpPhloemParallelRadianSegmentDB();

	//   UpPhloemParallelLengthHalfDB();

	UpPhloemParallelCenterRadianDB();

	UpPhloemParallelCenterRotateAngleDB();

	UpPhloemCellXYDB();

	UpPhloemObjectHeightAndZPositionDB(sliceNum);

	/// Initialize in BaseGeometry for visualization;

	MapRGB();

	SetSuperEllipsoidResolution();
}

/****************************************************************************************************************
//////////////////////////////////////////// Down ///////////////////////////////////////////////////////////////
*****************************************************************************************************************/
/******************
First
******************/

/** \brief downVerticalLengthTotalDB
 *
 * \param vector<double> upVerticalLengthTotalDB;
 * \return vector<double> downVerticalLengthTotalDB;
 *
 */
vector<double> downVerticalLengthTotalDB;
void rsPhloemDB::DownVerticalLengthTotalDB(rsPXBoundaryDB* RsPXBoundaryDB)
{
	vector<double>::iterator itVec;
	double temp;
	ofstream fout(getFolderName() + "downCell.txt", ios::app);
	fout << "DownVerticalLengthTotalDB" << endl;
	for (itVec = upVerticalLengthTotalDB.begin();
		itVec != upVerticalLengthTotalDB.end();
		itVec++)
	{
		temp = RsPXBoundaryDB->steleBoundaryRingRadius - boundaryMXPXRingRadiusDeliver - *itVec;
		downVerticalLengthTotalDB.push_back(temp);
		fout << "steleBoundaryRingRadius: " << RsPXBoundaryDB->steleBoundaryRingRadius << "  boundaryMXPXRingRadiusDeliver"
			<< boundaryMXPXRingRadiusDeliver << "  *itVec: " << *itVec << "  temp: " << temp << endl;
	}
}

/** \brief downFirstSecondVerticalLengthDB
 *
 * \param vector<double> upVerticalLengthTotalDB;
 * \return vector<double> downFirstVerticalLengthDB;
 * \return vector<double> downSecondVerticalLengthDB;
 *
 */
vector<double> downFirstVerticalLengthDB;
vector<double> downSecondVerticalLengthDB;
void rsPhloemDB::DownFirstSecondVerticalLengthDB()
{
	vector<double>::iterator itVec;
	double tempFirst;
	double tempSecond;
	ofstream fout(getFolderName() + "downCell.txt", ios::app);
	fout << "DownFirstSecondVerticalLengthDB" << endl;
	for (itVec = downVerticalLengthTotalDB.begin();
		itVec != downVerticalLengthTotalDB.end();
		itVec++)
	{
		tempFirst = *itVec * (double(1) / double(3));
		tempSecond = *itVec * (double(2) / double(3));
		downFirstVerticalLengthDB.push_back(tempFirst);
		downSecondVerticalLengthDB.push_back(tempSecond);
		fout << "tempFirst: " << tempFirst << "  tempSecond: " << tempSecond << endl;
	}
}

/** \brief DownFirstSecondVerticalLengthHalfDB
 *
 * \param vector<double> downFirstVerticalLengthDB;
 * \param vector<double> downSecondVerticalLengthDB;
 * \return vector<double> downFirstVerticalLengthHalfDB;
 * \return vector<double> downSecondVerticalLengthHalfDB;
 *
 */
vector<double> downFirstVerticalLengthHalfDB;
vector<double> downSecondVerticalLengthHalfDB;
void rsPhloemDB::DownFirstSecondVerticalLengthHalfDB()
{
	vector<double>::iterator itVec;
	double tempFirst;
	double tempSecond;

	for (itVec = downFirstVerticalLengthDB.begin();
		itVec != downFirstVerticalLengthDB.end();
		itVec++)
	{
		tempFirst = *itVec / 2;
		downFirstVerticalLengthHalfDB.push_back(tempFirst);
	}
	for (itVec = downSecondVerticalLengthDB.begin();
		itVec != downSecondVerticalLengthDB.end();
		itVec++)
	{
		tempSecond = *itVec / 2;
		downSecondVerticalLengthHalfDB.push_back(tempSecond);
	}
}


/** \brief downFirstParallelLengthThresholdDB
 *
 * \param  vector<double> downFirstVerticalLengthDB;
 * \return vector<double> downFirstParallelLengthThresholdDB;
 *
 */
vector<double> downFirstParallelLengthThresholdDB;
void rsPhloemDB::DownFirstParallelLengthThresholdDB()
{
	downFirstParallelLengthThresholdDB = downFirstVerticalLengthDB;
}

/** \brief downFirstSecondCenterRadiusDB;
 *
 * \param double boundaryMXPXRingRadiusDeliver;
 * \param vector<double> upVerticalLengthTotalDB;
 * \return vector<double> downFirstCenterRadiusDB;
 * \return vector<double> downSecondCenterRadiusDB;
 *
 */
vector<double> downFirstCenterRadiusDB;
vector<double> downSecondCenterRadiusDB;
void rsPhloemDB::DownFirstSecondCenterRadiusDB()
{
	vector<double>::iterator itVec;
	vector<double>::iterator itVecFirst;
	vector<double>::iterator itVecSecond;
	double tempFirst;
	double tempSecond;
	for (itVec = upVerticalLengthTotalDB.begin(),
		itVecFirst = downFirstVerticalLengthDB.begin(),
		itVecSecond = downSecondVerticalLengthDB.begin();
		itVec != upVerticalLengthTotalDB.end();
		itVec++, itVecFirst++, itVecSecond++)
	{
		tempFirst = boundaryMXPXRingRadiusDeliver + *itVec + (*itVecFirst / 2);
		tempSecond = boundaryMXPXRingRadiusDeliver + *itVec + *itVecFirst + (*itVecSecond / 2);
		downFirstCenterRadiusDB.push_back(tempFirst);
		downSecondCenterRadiusDB.push_back(tempSecond);
	}
}

/** \brief downFirstSecondParallelLengthTotalDB
 *
 * \param vector<double> interIntersectionRadianDB;
 * \param vector<double> downFirstCenterRadiusDB;
 * \param vector<double> downSecondCenterRadiusDB;
 * \return vector<double> downFirstParallelLengthTotalDB;
 * \return vector<double> downSecondParallelLengthTotalDB;
 *
 */
vector<double> downFirstParallelLengthTotalDB;
vector<double> downSecondParallelLengthTotalDB;
void rsPhloemDB::DownFirstSecondParallelLengthTotalDB()
{
	vector<double>::iterator itVec;
	vector<double>::iterator itVecFirst;
	vector<double>::iterator itVecSecond;
	double tempFirst;
	double tempSecond;

	ofstream fout(getFolderName() + "downCell.txt", ios::app);
	fout << "DownFirstSecondParallelLengthTotalDB" << endl;
	for (itVec = interIntersectionRadianDB.begin(),
		itVecFirst = downFirstCenterRadiusDB.begin(),
		itVecSecond = downSecondCenterRadiusDB.begin();
		itVec != interIntersectionRadianDB.end();
		itVec++, itVecFirst++, itVecSecond++)
	{
		tempFirst = 2 * M_PI * (*itVecFirst) * (*itVec / (2 * M_PI));
		tempSecond = 2 * M_PI * (*itVecSecond) * (*itVec / (2 * M_PI));
		downFirstParallelLengthTotalDB.push_back(tempFirst);
		downSecondParallelLengthTotalDB.push_back(tempSecond);
		fout << "*itVecFirst: " << *itVecFirst << "  *itVec: " << *itVec << endl;
		fout << "tempFirst: " << tempFirst << "  tempSecond: " << tempSecond << endl;
	}
}

/** \brief downFirstCellNumDB
 *
 * \param vector<double> downFirstParallelLengthTotalDB;
 * \param vector<double> downFirstParallelLengthThresholdDB;
 * \return vector<int> downFirstCellNumDB;
 *
 */
vector<int> downFirstCellNumDB;
void rsPhloemDB::DownFirstCellNumDB()
{
	vector<double>::iterator itVecTotal;
	vector<double>::iterator itVecThreshold;
	int num;

	ofstream fout(getFolderName() + "downCell.txt", ios::app);
	fout << "DownFirstCellNumDB" << endl;
	for (itVecTotal = downFirstParallelLengthTotalDB.begin(),
		itVecThreshold = downFirstParallelLengthThresholdDB.begin();
		itVecTotal != downFirstParallelLengthTotalDB.end();
		itVecTotal++, itVecThreshold++)
	{
		num = int(*itVecTotal / (*itVecThreshold) + 0.5);
		downFirstCellNumDB.push_back(num);
		fout << "num: " << num << "  *itVecTotal: " << *itVecTotal
			<< "  *itVecThreshold: " << *itVecThreshold << endl;
	}
}

/** \brief downFirstParallelLengthDB; downFirstParallelLengthAddDB;
 *
 * \param vector<double> downFirstParallelLengthTotalDB;
 * \param vector<int> downFirstCellNumDB;
 * \return map<int, vector<double> > downFirstParallelLengthDB;
 * \return map<int, vector<double> > downFirstParallelLengthAddDB;
 *
 */
map<int, vector<double> > downFirstParallelLengthDB;
map<int, vector<double> > downFirstParallelLengthAddDB;
void rsPhloemDB::DownFirstParallelLengthDB(double variationRatio)
{
	vector<int>::iterator itVecNum;
	vector<double>::iterator itVecLengthTotal;
	vector<double> downFirstParallelLength;
	vector<double> downFirstParallelLengthAdd;
	int i;
	ofstream fout(getFolderName() + "downCell.txt", ios::app);
	fout << "DownFirstParallelLengthDB" << endl;

	for (itVecLengthTotal = downFirstParallelLengthTotalDB.begin(),
		itVecNum = downFirstCellNumDB.begin(), i = 0;
		itVecLengthTotal != downFirstParallelLengthTotalDB.end();
		itVecLengthTotal++, itVecNum++, i++)
	{
		RandomRatioButSameSumAndNumber(downFirstParallelLength,
			downFirstParallelLengthAdd,
			*itVecLengthTotal,
			*itVecNum,
			variationRatio);
		downFirstParallelLengthDB.insert
		(pair<int, vector<double> >(i, downFirstParallelLength));
		downFirstParallelLengthAddDB.insert
		(pair<int, vector<double> >(i, downFirstParallelLengthAdd));
		fout << "i: " << i << "  *itVecLengthTotal: " << *itVecLengthTotal
			<< "  *itVecNum: " << *itVecNum << endl;
	}
}

/** \brief downSecondParallelLengthHalfDB
 *
 * \param map<int,vector<double> > downFirstParallelLengthDB;
 * \return map<int,vector<double> > downFirstParallelLengthHalfDB;
 *
 */
map<int, vector<double> > downFirstParallelLengthHalfDB;
void rsPhloemDB::DownFirstParallelLengthHalfDB()
{
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec;

	vector<double> downFirstParallelLengthHalf;
	double temp;
	int i;
	for (itMap = downFirstParallelLengthDB.begin(), i = 0;
		itMap != downFirstParallelLengthDB.end();
		itMap++, i++)
	{
		downFirstParallelLengthHalf.clear();
		for (itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			itVec++)
		{
			temp = *itVec / 2;
			downFirstParallelLengthHalf.push_back(temp);
		}
		downFirstParallelLengthHalfDB.insert(pair<int, vector<double> >(i, downFirstParallelLengthHalf));
	}
}

/** \brief downFirstParallelRadianDivideDB; downFirstParallelRadianDivideAddDB;
 *
 * \param vector<double> interIntersectionRadianDB;
 * \param map<int, vector<double> > downFirstParallelLengthDB;
 * \param map<int, vector<double> > downFirstParallelLengthAddDB;
 * \param vector<double> downFirstParallelLengthTotalDB;
 * \return map<int, vector<double> > downFirstParallelRadianDivideDB;
 * \return map<int, vector<double> > downFirstParallelRadianDivideAddDB;
 *
 */
map<int, vector<double> > downFirstParallelRadianDivideDB;
map<int, vector<double> > downFirstParallelRadianDivideAddDB;
void rsPhloemDB::DownFirstParallelRadianDivideDB()
{
	map<int, vector<double> >::iterator itMap;
	map<int, vector<double> >::iterator itMapAdd;
	vector<double>::iterator itVec;
	vector<double>::iterator itVecAdd;

	vector<double>::iterator itVecRadian;
	vector<double>::iterator itVecLengthTotal;

	vector<double> downFirstParallelRadianDivide;
	vector<double> downFirstParallelRadianDivideAdd;

	double temp;
	double tempAdd;
	int i;
	ofstream fout(getFolderName() + "downCell.txt", ios::app);
	fout << "DownFirstParallelRadianDivideDB" << endl;

	for (itMap = downFirstParallelLengthDB.begin(),
		itMapAdd = downFirstParallelLengthAddDB.begin(),
		itVecRadian = interIntersectionRadianDB.begin(),
		itVecLengthTotal = downFirstParallelLengthTotalDB.begin(),
		i = 0;
		itMap != downFirstParallelLengthDB.end();
		itMap++, itMapAdd++, itVecRadian++, itVecLengthTotal++, i++)
	{
		downFirstParallelRadianDivide.clear();
		downFirstParallelRadianDivideAdd.clear();
		for (itVec = (*itMap).second.begin(), itVecAdd = (*itMapAdd).second.begin();
			itVec != (*itMap).second.end();
			itVec++, itVecAdd++)
		{
			temp = (*itVec / (*itVecLengthTotal)) * (*itVecRadian);
			tempAdd = (*itVecAdd / (*itVecLengthTotal)) * (*itVecRadian);
			downFirstParallelRadianDivide.push_back(temp);
			downFirstParallelRadianDivideAdd.push_back(tempAdd);
			fout << "i: " << i << "  temp: " << temp << "  tempAdd: " << tempAdd << endl;
		}
		downFirstParallelRadianDivideDB.insert
		(pair<int, vector<double> >(i, downFirstParallelRadianDivide));
		downFirstParallelRadianDivideAddDB.insert
		(pair<int, vector<double> >(i, downFirstParallelRadianDivideAdd));
	}
}

/** \brief DownFirstParallelCenterRadianDB
 *
 * \param map<int, vector<double> > downFirstParallelRadianDivideDB;
 * \param map<int, vector<double> > downFirstParallelRadianDivideAddDB;
 * \param vector<double> interRadianStartDB;
 * \return map<int, vector<double> > downFirstParallelCenterRadianDB;
 *
 */
map<int, vector<double> > downFirstParallelCenterRadianDB;
void rsPhloemDB::DownFirstParallelCenterRadianDB()
{
	map<int, vector<double> >::iterator  itMapRadianDivideAdd;
	vector<double>::iterator itVecRadianDivideAdd;
	map<int, vector<double> >::iterator  itMapRadianDivide;
	vector<double>::iterator itVecRadianDivide;

	vector<double>::iterator itVecRadianStart;
	vector<double> downFirstParallelCenterRadian;

	double temp;
	int i;
	ofstream fout(getFolderName() + "downCell.txt", ios::app);
	fout << "DownFirstParallelCenterRadianDB" << endl;
	for (itMapRadianDivideAdd = downFirstParallelRadianDivideAddDB.begin(),
		itMapRadianDivide = downFirstParallelRadianDivideDB.begin(),
		itVecRadianStart = interRadianStartDB.begin(),
		i = 0;
		itMapRadianDivideAdd != downFirstParallelRadianDivideAddDB.end();
		itMapRadianDivideAdd++, itMapRadianDivide++, itVecRadianStart++, i++)
	{
		downFirstParallelCenterRadian.clear();
		for (itVecRadianDivideAdd = (*itMapRadianDivideAdd).second.begin(),
			itVecRadianDivide = (*itMapRadianDivide).second.begin();
			itVecRadianDivideAdd != (*itMapRadianDivideAdd).second.end();
			itVecRadianDivideAdd++, itVecRadianDivide++)
		{
			temp = *itVecRadianStart + *itVecRadianDivideAdd + *itVecRadianDivide / 2;
			downFirstParallelCenterRadian.push_back(temp);
			fout << "temp: " << temp << endl;
		}
		downFirstParallelCenterRadianDB.insert(pair<int, vector<double> >(i, downFirstParallelCenterRadian));
	}
}

/** \brief DownFirstParallelRotateAngleDB;
 *
 * \param map<int, vector<double> > downFirstParallelCenterRadianDB;
 * \return map<int, vector<double> >  downFirstParallelCenterRotateAngleDB;
 *
 */
map<int, vector<double> >  downFirstParallelCenterRotateAngleDB;
void rsPhloemDB::DownFirstParallelRotateAngleDB()
{
	map<int, vector<double> >::iterator  itMap;
	vector<double>::iterator itVec;
	vector<double> downFirstParallelCenterRotateAngle;
	double tempAngle;
	int i;
	int j = 0;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "DownFirstParallelRotateAngleDB" << endl;

	for (itMap = downFirstParallelCenterRadianDB.begin(), i = 0;
		itMap != downFirstParallelCenterRadianDB.end();
		itMap++, i++)
	{
		downFirstParallelCenterRotateAngle.clear();
		for (itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			itVec++, j++)

		{
			tempAngle = (-1) * (*itVec) / M_PI * 180;
			downFirstParallelCenterRotateAngle.push_back(tempAngle);
			fout << "i: " << i << "  j: " << j <<
				"  tempAngle: " << tempAngle << endl;
		}
		downFirstParallelCenterRotateAngleDB.insert
		(pair<int, vector<double> >(i, downFirstParallelCenterRotateAngle));
	}
}

/** \brief DownFirstCellXYDB
 *
 * \param map<int, vector<double> > downFirstParallelCenterRadianDB;
 * \param vector<double> downFirstCenterRadiusDB;
 * \return map<int, vector<double> > downFirstCellXDB;
 * \return map<int, vector<double> > downFirstCellYDB;
 *
 */
map<int, vector<double> > downFirstCellXDB;
map<int, vector<double> > downFirstCellYDB;
void rsPhloemDB::DownFirstCellXYDB()
{
	map<int, vector<double> >::iterator  itMap;
	vector<double>::iterator itVec;
	vector<double>::iterator itVecRadius;
	vector<double> cellXVec;
	vector<double> cellYVec;

	double tempX;
	double tempY;
	int i;
	int j;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpPhloemCellXYDB" << endl;

	for (itMap = downFirstParallelCenterRadianDB.begin(),
		itVecRadius = downFirstCenterRadiusDB.begin(), i = 0;
		itMap != downFirstParallelCenterRadianDB.end();
		itMap++, itVecRadius++, i++)
	{
		cellXVec.clear();
		cellYVec.clear();
		for (itVec = (*itMap).second.begin(), j = 0;
			itVec != (*itMap).second.end();
			itVec++, j++)
		{
			tempX = (*itVecRadius) * cos(*itVec);
			tempY = (*itVecRadius) * sin(*itVec);
			cellXVec.push_back(tempX);
			cellYVec.push_back(tempY);
			fout << "i: " << i << "  j: " << j <<
				"  tempX: " << tempX << "  tempY: " << tempY << endl;
		}
		downFirstCellXDB.insert(pair<int, vector<double> >(i, cellXVec));
		downFirstCellYDB.insert(pair<int, vector<double> >(i, cellYVec));
	}
}

/** \brief DownFirstObjectHeightAndZPositionDB
 *
 * \param map<int, vector<double> > downFirstCellXDB;
 * \return map<int, vector<vector<double> > > downFirstCellObjectHeightDB;
 * \return map<int, vector<vector<double> > > downFirstCellObjectZPositionDB;
 *
 */
map<int, vector<vector<double> > > downFirstCellObjectHeightDB;
map<int, vector<vector<double> > > downFirstCellObjectZPositionDB;
void rsPhloemDB::DownFirstObjectHeightAndZPositionDB(int sliceNum)
{  /// declare iterator;
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec;
	/// Height
	vector< vector<double> >           objectHeightVec2;
	vector<double>                     objectHeightVec1;
	/// ZPosition
	vector< vector<double> >           objectZPositionVec2;
	vector<double>                     objectZPositionVec1;

	/// declare int;
	int i;
	int cellNum;
	int sliceTempNum;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "DownFirstObjectHeightAndZPositionDB" << endl;

	for (i = 0, itMap = downFirstCellXDB.begin();
		itMap != downFirstCellXDB.end();
		i++, itMap++)
	{
		objectHeightVec2.clear();
		objectZPositionVec2.clear();
		for (cellNum = 0, itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			cellNum++, itVec++)
		{
			objectHeightVec1.clear();
			objectZPositionVec1.clear();
			int randomHeightZPosition = rand() % 200;
			for (sliceTempNum = 0;
				sliceTempNum != sliceNum;
				sliceTempNum++)
			{  /// Height;
				objectHeightVec1.push_back
				(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio);
				fout << "i: " << i << "  cellNum: " << cellNum << "  sliceTempNum: " << sliceTempNum
					<< "  Height: " << longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] << endl;
				/// ZPosition;
				objectZPositionVec1.push_back
				(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
				fout << "i: " << i << "  cellNum: " << cellNum << "  sliceTempNum: " << sliceTempNum
					<< "  ZPosition: " << longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum] << endl;
			}
			objectHeightVec2.push_back(objectHeightVec1);
			objectZPositionVec2.push_back(objectZPositionVec1);
		}
		downFirstCellObjectHeightDB.insert
		(pair<int, vector <vector<double> > >(i, objectHeightVec2));
		downFirstCellObjectZPositionDB.insert
		(pair<int, vector <vector<double> > >(i, objectZPositionVec2));
	}
}

/******************
Second
******************/
/** \brief DownSecondParallelLengthTotalAverage
 *
 * \param  vector<double> downSecondParallelLengthTotalDB;
 * \return double downSecondParallelLengthTotalAverage;
 *
 */
double downSecondParallelLengthTotalAverage;
void rsPhloemDB::DownSecondParallelLengthTotalAverage()
{
	vector<double>::iterator itVec;
	double temp;
	double sum = 0;
	int i = 0;
	ofstream fout(getFolderName() + "downCell.txt", ios::app);
	fout << "DownSecondParallelLengthTotalAverage" << endl;
	for (itVec = downSecondParallelLengthTotalDB.begin();
		itVec != downSecondParallelLengthTotalDB.end();
		itVec++)
	{
		sum += *itVec;
		i++;
	}
	temp = sum / i;
	downSecondParallelLengthTotalAverage = temp;
	fout << "temp" << endl;
}

/** \brief DownSecondParallelCellNum;
 *
 * \param vector<double> downSecondParallelLengthTotalDB;
 * \param double downSecondParallelLengthTotalAverage;
 * \return vector<int> downSecondParallelCellNumDB;
 *
 */
vector<int> downSecondParallelCellNumDB;
void rsPhloemDB::DownSecondParallelCellNum()
{
	vector<double>::iterator itVec;
	int temp;
	ofstream fout(getFolderName() + "downCell.txt", ios::app);
	fout << "DownSecondParallelCellNum" << endl;
	for (itVec = downSecondParallelLengthTotalDB.begin();
		itVec != downSecondParallelLengthTotalDB.end();
		itVec++)
	{
		if (*itVec < downSecondParallelLengthTotalAverage)
		{
			temp = 5;
			downSecondParallelCellNumDB.push_back(temp);
		}
		else
		{
			temp = 6;
			downSecondParallelCellNumDB.push_back(temp);
		}
		fout << temp << endl;
	}
}

/** \brief downSecondParallelLengthRatio56DB
 *
 * \param double array5;
 * \param double array6;
 * \return vector<double> downSecondParallelLengthRatio5DB;
 * \return vector<double> downSecondParallelLengthRatio6DB;
 *
 */
vector<double> downSecondParallelLengthRatio5DB;
vector<double> downSecondParallelLengthRatio6DB;
void rsPhloemDB::DownSecondParallelLengthRatio56DB()
{
	double array5[5] = { double(7.5) / double(50),
					   double(10) / double(50),
					   double(15) / double(50),
					   double(10) / double(50),
					   double(7.5) / double(50)
	};
	double array6[6] = { double(7) / double(60),
						 double(10) / double(60),
						 double(13) / double(60),
						 double(13) / double(60),
						 double(10) / double(60),
						 double(7) / double(60)
	};
	int i;
	double temp;
	for (i = 0; i != 5; i++)
	{
		temp = array5[i];
		downSecondParallelLengthRatio5DB.push_back(temp);
	}
	for (i = 0; i != 6; i++)
	{
		temp = array6[i];
		downSecondParallelLengthRatio6DB.push_back(temp);
	}
}

/** \brief
 *
 * \param vector<double> downSecondParallelLengthRatio5DB;
 * \param vector<double> downSecondParallelLengthRatio6DB;
 * \param vector<int> downSecondParallelCellNumDB;
 * \return map<int,vector<double> > downSecondParallelLengthRatioDB;
 *
 */
map<int, vector<double> > downSecondParallelLengthRatioDB;
void rsPhloemDB::DownSecondParallelLengthRatioDB()
{
	vector<int>::iterator itVec;
	int i;
	vector<double> downSecondParallelLengthRatio;
	ofstream fout(getFolderName() + "downCell.txt", ios::app);
	fout << "DownSecondParallelLengthRatioDB" << endl;
	for (itVec = downSecondParallelCellNumDB.begin(), i = 0;
		itVec != downSecondParallelCellNumDB.end();
		itVec++, i++)
	{
		downSecondParallelLengthRatio.clear();
		if ((*itVec) == 5)
		{
			downSecondParallelLengthRatio = downSecondParallelLengthRatio5DB;
		}
		else
		{
			downSecondParallelLengthRatio = downSecondParallelLengthRatio6DB;
		}
		downSecondParallelLengthRatioDB.insert(pair<int, vector<double> >(i, downSecondParallelLengthRatio));
		fout << *itVec << endl;
	}
}

/** \brief downSecondParallelLengthDB
 *
 * \param map<int,vector<double> > downSecondParallelLengthRatioDB;
 * \param vector<double> downSecondParallelLengthTotalDB;
 * \return map<int,vector<double> > downSecondParallelLengthDB;
 *
 */
map<int, vector<double> > downSecondParallelLengthDB;
void rsPhloemDB::DownSecondParallelLengthDB()
{
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec;
	vector<double>::iterator itVecTotal;

	vector<double> downSecondParallelLength;
	double temp;
	int i;
	for (itMap = downSecondParallelLengthRatioDB.begin(),
		itVecTotal = downSecondParallelLengthTotalDB.begin(), i = 0;
		itMap != downSecondParallelLengthRatioDB.end();
		itMap++, itVecTotal++, i++)
	{
		downSecondParallelLength.clear();
		for (itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			itVec++)
		{
			temp = *itVecTotal * (*itVec);
			downSecondParallelLength.push_back(temp);
		}
		downSecondParallelLengthDB.insert(pair<int, vector<double> >(i, downSecondParallelLength));
	}
}

/** \brief downSecondParallelLengthHalfDB
 *
 * \param map<int,vector<double> > downSecondParallelLengthDB;
 * \return map<int,vector<double> > downSecondParallelLengthHalfDB;
 *
 */
map<int, vector<double> > downSecondParallelLengthHalfDB;
void rsPhloemDB::DownSecondParallelLengthHalfDB()
{
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec;

	vector<double> downSecondParallelLengthHalf;
	double temp;
	int i;
	for (itMap = downSecondParallelLengthDB.begin(), i = 0;
		itMap != downSecondParallelLengthDB.end();
		itMap++, i++)
	{
		downSecondParallelLengthHalf.clear();
		for (itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			itVec++)
		{
			temp = *itVec / 2;
			downSecondParallelLengthHalf.push_back(temp);
		}
		downSecondParallelLengthHalfDB.insert(pair<int, vector<double> >(i, downSecondParallelLengthHalf));
	}
}

/** \brief downSecondParallelLengthDB
 *
 * \param map<int,vector<double> > downSecondParallelLengthDB;
 * \return map<int,vector<double> > downSecondParallelLengthAddDB;
 *
 */
map<int, vector<double> > downSecondParallelLengthAddDB;
void rsPhloemDB::DownSecondParallelLengthAddDB()
{
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec;

	vector<double> downSecondParallelLengthAdd;
	double temp;
	double tempSum;
	double sum;
	int i;
	ofstream fout(getFolderName() + "downCell.txt", ios::app);
	fout << "DownSecondParallelLengthAddDB" << endl;
	for (itMap = downSecondParallelLengthDB.begin(), i = 0, temp = 0, tempSum = 0, sum = 0;
		itMap != downSecondParallelLengthDB.end();
		itMap++, i++)
	{
		downSecondParallelLengthAdd.clear();
		tempSum = 0;
		for (itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			itVec++)
		{
			temp = *itVec;
			tempSum += temp;
			sum = tempSum - temp;
			downSecondParallelLengthAdd.push_back(sum);
			fout << "sum: " << sum << endl;
		}
		downSecondParallelLengthAddDB.insert(pair<int, vector<double> >(i, downSecondParallelLengthAdd));
	}
}

/** \brief downSecondParallelRadianSegmentDB; downSecondParallelRadianSegmentAddDB;
 *
 * \param vector<double> interIntersectionRadianDB;
 * \param map<int,vector<double> > downSecondParallelLengthDB;
 * \param map<int,vector<double> > downSecondParallelLengthAddDB;
 * \param vector<double> downSecondParallelLengthTotalDB;
 * \return map<int, vector<double> > downSecondParallelRadianSegmentDB;
 * \return map<int, vector<double> > downSecondParallelRadianSegmentAddDB;
 *
 */
map<int, vector<double> > downSecondParallelRadianSegmentDB;
map<int, vector<double> > downSecondParallelRadianSegmentAddDB;
void rsPhloemDB::DownSecondParallelRadianSegmentDB()
{
	map<int, vector<double> >::iterator itMap;
	map<int, vector<double> >::iterator itMapAdd;
	vector<double>::iterator itVec;
	vector<double>::iterator itVecAdd;

	vector<double>::iterator itVecRadian;
	vector<double>::iterator itVecLengthTotal;

	vector<double> downSecondParallelRadianSegment;
	vector<double> downSecondParallelRadianSegmentAdd;

	double temp;
	double tempAdd;
	int i;
	ofstream fout(getFolderName() + "CalculateRandom.txt", ios::app);
	fout << "DownFirstParallelRadianDivideDB" << endl;

	for (itMap = downSecondParallelLengthDB.begin(),
		itMapAdd = downSecondParallelLengthAddDB.begin(),
		itVecRadian = interIntersectionRadianDB.begin(),
		itVecLengthTotal = downSecondParallelLengthTotalDB.begin(),
		i = 0;
		itMap != downSecondParallelLengthDB.end();
		itMap++, itMapAdd++, itVecRadian++, itVecLengthTotal++, i++)
	{
		downSecondParallelRadianSegment.clear();
		downSecondParallelRadianSegmentAdd.clear();
		for (itVec = (*itMap).second.begin(), itVecAdd = (*itMapAdd).second.begin();
			itVec != (*itMap).second.end();
			itVec++, itVecAdd++)
		{
			temp = (*itVec / (*itVecLengthTotal)) * (*itVecRadian);
			tempAdd = (*itVecAdd / (*itVecLengthTotal)) * (*itVecRadian);
			downSecondParallelRadianSegment.push_back(temp);
			downSecondParallelRadianSegmentAdd.push_back(tempAdd);
			fout << "i: " << i << "  temp: " << temp << "  tempAdd: " << tempAdd << endl;
		}
		downSecondParallelRadianSegmentDB.insert
		(pair<int, vector<double> >(i, downSecondParallelRadianSegment));
		downSecondParallelRadianSegmentAddDB.insert
		(pair<int, vector<double> >(i, downSecondParallelRadianSegmentAdd));
	}
}

/** \brief DownSecondParallelCenterRadianDB
 *
 * \param map<int, vector<double> > downSecondParallelRadianSegmentDB;
 * \param map<int, vector<double> > downSecondParallelRadianSegmentAddDB;
 * \param vector<double> interRadianStartDB;
 * \return map<int, vector<double> > downSecondParallelCenterRadianDB;
 *
 */
map<int, vector<double> > downSecondParallelCenterRadianDB;
void rsPhloemDB::DownSecondParallelCenterRadianDB()
{
	map<int, vector<double> >::iterator  itMapRadianSegmentAdd;
	vector<double>::iterator itVecRadianSegmentAdd;
	map<int, vector<double> >::iterator  itMapRadianSegment;
	vector<double>::iterator itVecRadianSegment;

	vector<double>::iterator itVecRadianStart;
	vector<double> downSecondParallelCenterRadian;

	double temp;
	int i;
	ofstream fout(getFolderName() + "downCell.txt", ios::app);
	fout << "DownSecondParallelCenterRadianDB" << endl;
	for (itMapRadianSegmentAdd = downSecondParallelRadianSegmentAddDB.begin(),
		itMapRadianSegment = downSecondParallelRadianSegmentDB.begin(),
		itVecRadianStart = interRadianStartDB.begin(),
		i = 0;
		itMapRadianSegmentAdd != downSecondParallelRadianSegmentAddDB.end();
		itMapRadianSegmentAdd++, itMapRadianSegment++, itVecRadianStart++, i++)
	{
		downSecondParallelCenterRadian.clear();
		for (itVecRadianSegmentAdd = (*itMapRadianSegmentAdd).second.begin(),
			itVecRadianSegment = (*itMapRadianSegment).second.begin();
			itVecRadianSegmentAdd != (*itMapRadianSegmentAdd).second.end();
			itVecRadianSegmentAdd++, itVecRadianSegment++)
		{
			temp = *itVecRadianStart + *itVecRadianSegmentAdd + *itVecRadianSegment / 2;
			downSecondParallelCenterRadian.push_back(temp);
			fout << "temp: " << temp << endl;
			fout << "*itVecRadianStart: " << *itVecRadianStart << "  *itVecRadianSegmentAdd" << *itVecRadianSegmentAdd
				<< "  *itVecRadianSegment/2: " << *itVecRadianSegment / 2 << endl;
		}
		downSecondParallelCenterRadianDB.insert(pair<int, vector<double> >(i, downSecondParallelCenterRadian));
	}
}

/** \brief DownSecondParallelRotateAngleDB;
 *
 * \param map<int, vector<double> > downSecondParallelCenterRadianDB;
 * \return map<int, vector<double> >  downSecondParallelCenterRotateAngleDB;
 *
 */
map<int, vector<double> >  downSecondParallelCenterRotateAngleDB;
void rsPhloemDB::DownSecondParallelRotateAngleDB()
{
	map<int, vector<double> >::iterator  itMap;
	vector<double>::iterator itVec;
	vector<double> downSecondParallelCenterRotateAngle;
	double tempAngle;
	int i;
	int j = 0;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "DownSecondParallelRotateAngleDB" << endl;

	for (itMap = downSecondParallelCenterRadianDB.begin(), i = 0;
		itMap != downSecondParallelCenterRadianDB.end();
		itMap++, i++)
	{
		downSecondParallelCenterRotateAngle.clear();
		for (itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			itVec++, j++)

		{
			tempAngle = (-1) * (*itVec) / M_PI * 180;
			downSecondParallelCenterRotateAngle.push_back(tempAngle);
			fout << "i: " << i << "  j: " << j <<
				"  tempAngle: " << tempAngle << endl;
		}
		downSecondParallelCenterRotateAngleDB.insert
		(pair<int, vector<double> >(i, downSecondParallelCenterRotateAngle));
	}
}

/** \brief DownSecondCellXYDB
 *
 * \param map<int, vector<double> > downSecondParallelCenterRadianDB;
 * \param vector<double> downSecondCenterRadiusDB;
 * \return map<int, vector<double> > downSecondCellXDB;
 * \return map<int, vector<double> > downSecondCellYDB;
 *
 */
map<int, vector<double> > downSecondCellXDB;
map<int, vector<double> > downSecondCellYDB;
void rsPhloemDB::DownSecondCellXYDB()
{
	map<int, vector<double> >::iterator  itMap;
	vector<double>::iterator itVec;
	vector<double>::iterator itVecRadius;
	vector<double> cellXVec;
	vector<double> cellYVec;

	double tempX;
	double tempY;
	int i;
	int j;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "DownSecondCellXYDB" << endl;

	for (itMap = downSecondParallelCenterRadianDB.begin(),
		itVecRadius = downSecondCenterRadiusDB.begin(), i = 0;
		itMap != downSecondParallelCenterRadianDB.end();
		itMap++, itVecRadius++, i++)
	{
		cellXVec.clear();
		cellYVec.clear();
		for (itVec = (*itMap).second.begin(), j = 0;
			itVec != (*itMap).second.end();
			itVec++, j++)
		{
			tempX = (*itVecRadius) * cos(*itVec);
			tempY = (*itVecRadius) * sin(*itVec);
			cellXVec.push_back(tempX);
			cellYVec.push_back(tempY);
			fout << "i: " << i << "  j: " << j <<
				"  tempX: " << tempX << "  tempY: " << tempY << endl;
		}
		downSecondCellXDB.insert(pair<int, vector<double> >(i, cellXVec));
		downSecondCellYDB.insert(pair<int, vector<double> >(i, cellYVec));
	}
}

/** \brief DownSecondObjectHeightAndZPositionDB
 *
 * \param map<int, vector<double> > downSecondCellXDB;
 * \return map<int, vector<vector<double> > > downSecondCellObjectHeightDB;
 * \return map<int, vector<vector<double> > > downSecondCellObjectZPositionDB;
 *
 */
map<int, vector<vector<double> > > downSecondCellObjectHeightDB;
map<int, vector<vector<double> > > downSecondCellObjectZPositionDB;
void rsPhloemDB::DownSecondObjectHeightAndZPositionDB(int sliceNum)
{  /// declare iterator;
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec;
	/// Height
	vector< vector<double> >           objectHeightVec2;
	vector<double>                     objectHeightVec1;
	/// ZPosition
	vector< vector<double> >           objectZPositionVec2;
	vector<double>                     objectZPositionVec1;

	/// declare int;
	int i;
	int cellNum;
	int sliceTempNum;
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "DownSecondObjectHeightAndZPositionDB" << endl;

	for (i = 0, itMap = downSecondCellXDB.begin();
		itMap != downSecondCellXDB.end();
		i++, itMap++)
	{
		objectHeightVec2.clear();
		objectZPositionVec2.clear();
		for (cellNum = 0, itVec = (*itMap).second.begin();
			itVec != (*itMap).second.end();
			cellNum++, itVec++)
		{
			objectHeightVec1.clear();
			objectZPositionVec1.clear();
			int randomHeightZPosition = rand() % 200;
			for (sliceTempNum = 0;
				sliceTempNum != sliceNum;
				sliceTempNum++)
			{  /// Height;
				objectHeightVec1.push_back
				(longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] / 2 / objectXYZRadiusRatio);
				fout << "i: " << i << "  cellNum: " << cellNum << "  sliceTempNum: " << sliceTempNum
					<< "  Height: " << longitudeSegmentHeightDB[randomHeightZPosition][sliceTempNum] << endl;
				/// ZPosition;
				objectZPositionVec1.push_back
				(longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum]);
				fout << "i: " << i << "  cellNum: " << cellNum << "  sliceTempNum: " << sliceTempNum
					<< "  ZPosition: " << longitudeZPositionAddDB[randomHeightZPosition][sliceTempNum] << endl;
			}
			objectHeightVec2.push_back(objectHeightVec1);
			objectZPositionVec2.push_back(objectZPositionVec1);
		}
		downSecondCellObjectHeightDB.insert
		(pair<int, vector <vector<double> > >(i, objectHeightVec2));
		downSecondCellObjectZPositionDB.insert
		(pair<int, vector <vector<double> > >(i, objectZPositionVec2));
	}
}

void rsPhloemDB::InitDownCell
(rsPXBoundaryDB* RsPXBoundaryDB,
	double variationRatio,
	int sliceNum
)
{  /******************
   First
   ******************/
	DownVerticalLengthTotalDB(RsPXBoundaryDB);

	DownFirstSecondVerticalLengthDB();

	DownFirstSecondVerticalLengthHalfDB();

	DownFirstParallelLengthThresholdDB();

	DownFirstSecondCenterRadiusDB();

	DownFirstSecondParallelLengthTotalDB();

	DownFirstCellNumDB();

	DownFirstParallelLengthDB(variationRatio);

	DownFirstParallelLengthHalfDB();

	DownFirstParallelRadianDivideDB();

	DownFirstParallelCenterRadianDB();

	DownFirstParallelRotateAngleDB();

	DownFirstCellXYDB();

	DownFirstObjectHeightAndZPositionDB(sliceNum);

	/******************
	Second
	******************/
	DownSecondParallelLengthTotalAverage();

	DownSecondParallelCellNum();

	DownSecondParallelLengthRatio56DB();

	DownSecondParallelLengthRatioDB();

	DownSecondParallelLengthDB();

	DownSecondParallelLengthHalfDB();

	DownSecondParallelLengthAddDB();

	DownSecondParallelRadianSegmentDB();

	DownSecondParallelCenterRadianDB();

	DownSecondParallelRotateAngleDB();

	DownSecondCellXYDB();

	DownSecondObjectHeightAndZPositionDB(sliceNum);
}