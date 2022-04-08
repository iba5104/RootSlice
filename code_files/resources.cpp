#include "resources.h"

void rsBaseFunctions::CombineAllDBs(rsSourceCorticalDB* RsSourceCorticalDB, int numDermis, ...)
{
	va_list dermisList;
	vector<rsSourceDermisDB*> allDermisDBs;
	va_start(dermisList, numDermis);
	unordered_map<string, int> typeNumData;
	int vecSize = numDermis + 1;
	int totalCells = accumulate(RsSourceCorticalDB->corticalCellNumCalculateData.begin(), RsSourceCorticalDB->corticalCellNumCalculateData.end(), 0);
	typeNumData[type_cortical] = totalCells;
	for (int i = 0; i < numDermis; i++) {
		allDermisDBs.push_back(va_arg(dermisList, rsSourceDermisDB*));
		totalCells += allDermisDBs.back()->EpidermisCellNumCalculated;
		typeNumData[allDermisDBs.back()->cellType] = totalCells;
	}
	va_end(dermisList);
	/*
	CellData structure:
		vector<int> pointID;
		vector<double> x;
		vector<double> y;
		vector<double> z;
		vector<double> radius;
		vector<double> distanceCenter;
		vector<int> neighbours;
	*/
	allCells.empty();
	allCells.resize(totalCells);

	int i = 0;
	int corticalRingNum = RsSourceCorticalDB->circleXDB.size();
	for (int curRing = 0; curRing < corticalRingNum; curRing++) {
		int numCellsRing = RsSourceCorticalDB->circleXDB[curRing].size();
		for (int cellIdx = 0; cellIdx < numCellsRing; cellIdx++, i++) {
			if (i > allCells.size())
				cout << "Error: Total cells count higher than maximum. resources.cpp: cortical loop";
			allCells[i].ID = i;
			allCells[i].x = RsSourceCorticalDB->circleXDB[curRing][cellIdx];
			allCells[i].y = RsSourceCorticalDB->circleYDB[curRing][cellIdx];
			allCells[i].z = RsSourceCorticalDB->objectZPositionDB[curRing][cellIdx][0] + RsSourceCorticalDB->objectHeightDB[curRing][cellIdx][0];
			allCells[i].radius = RsSourceCorticalDB->objectVerticalDB[curRing];
			allCells[i].height = RsSourceCorticalDB->objectHeightDB[curRing][cellIdx][0];
			allCells[i].distanceCenter = RsSourceCorticalDB->circleRadiusDB[curRing];
			allCells[i].type = type_cortical;
		}
	}
	for (int curDermisIdx = 0; curDermisIdx < numDermis; curDermisIdx++) {
		int curDermisRingNum = allDermisDBs[curDermisIdx]->circleXDB.size();
		for (int curRing = 0; curRing < curDermisRingNum; curRing++) {
			int curDermisRingCells = allDermisDBs[curDermisIdx]->circleXDB[curRing].size();
			int numCellsRing = allDermisDBs[curDermisIdx]->circleXDB[curRing].size();
			for (int cellIdx = 0; cellIdx < numCellsRing; cellIdx++, i++) {
				if (i > allCells.size())
					cout << "Error: Total cells count higher than maximum. resources.cpp: dermis loop";
				allCells[i].ID = i;
				allCells[i].x = allDermisDBs[curDermisIdx]->circleXDB[curRing][cellIdx];
				allCells[i].y = allDermisDBs[curDermisIdx]->circleYDB[curRing][cellIdx];
				allCells[i].z = allDermisDBs[curDermisIdx]->objectZPositionDB[curRing][cellIdx][0] + allDermisDBs[curDermisIdx]->objectHeightDB[curRing][cellIdx][0];
				allCells[i].radius = allDermisDBs[curDermisIdx]->objectVerticalDB[curRing];
				allCells[i].height = allDermisDBs[curDermisIdx]->objectHeightDB[curRing][cellIdx][0];
				allCells[i].distanceCenter = allDermisDBs[curDermisIdx]->circleRadiusDB[curRing];
				allCells[i].type = allDermisDBs[curDermisIdx]->cellType;
			}
		}
	}

	/************************************
	Neighbour cell index calculate
	************************************/

	struct find_type
	{
		string type;
		find_type(string type) : type(type) {}
		bool operator () (const CellData& cd) const
		{
			return cd.type == type;
		}
	};
	vector<CellData>::iterator curCellIt;

	for (curCellIt = allCells.begin(); curCellIt < allCells.end(); curCellIt++) {
		CellData curCell = (*curCellIt);
		vector<string> typesToSearch = {};
		if (curCell.type == type_cortical) {
			typesToSearch.push_back(type_cortical);
			typesToSearch.push_back(type_scleren);
			typesToSearch.push_back(type_endo);
		}
		if (curCell.type == type_epi) {
			typesToSearch.push_back(type_epi);
			typesToSearch.push_back(type_scleren);
		}
		if (curCell.type == type_scleren) {
			typesToSearch.push_back(type_scleren);
		}
		if (curCell.type == type_endo) {
			typesToSearch.push_back(type_endo);
			typesToSearch.push_back(type_peri);
		}
		if (curCell.type == type_peri) {
			typesToSearch.push_back(type_peri);
		}
		if (curCell.type == type_exo) {
			typesToSearch.push_back(type_exo);
		}
		vector<string>::iterator cellTypeSearch;
		for (cellTypeSearch = typesToSearch.begin(); cellTypeSearch < typesToSearch.end(); cellTypeSearch++) {
			int curCellTypeNum = typeNumData[(*cellTypeSearch)];
			vector<CellData>::iterator it = find_if((curCellIt+1), allCells.end(), find_type((*cellTypeSearch)));
			for (int cellCtr = 0; cellCtr < curCellTypeNum; cellCtr++) {
				if (it == allCells.end())
					break;
				CellData tempCell = (*it);
				double cartesianDistance = pow((curCell.x - tempCell.x), 2) + pow((curCell.y - tempCell.y), 2);
				double radialDistance = pow((curCell.radius + tempCell.radius), 2);
				if ((abs(cartesianDistance - radialDistance) < 1) || (cartesianDistance < radialDistance)) {
					(*curCellIt).neighbours.push_back(tempCell.ID);
					(*it).neighbours.push_back(curCell.ID);
				}
				it = find_if(++it, allCells.end(), find_type((*cellTypeSearch)));
			}
		}
	}
}