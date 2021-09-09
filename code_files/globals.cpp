#include "globals.h"

vector<string> globals::allFileNames;
string globals::outputFolderPrefix;
void globals::addToFileNamesVector(string filename)
{
	globals::allFileNames.push_back(filename);
}

void globals::resetFileNameList()
{
	globals::allFileNames.clear();
}

void globals::setFolderName(string folderName)
{
	globals::outputFolderPrefix = folderName+"/";
}

string globals::getFolderName()
{
	return globals::outputFolderPrefix;
}

void globals::writePVDFile(string pvdFileName)
{
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);
	TiXmlElement* elementVTK = new TiXmlElement("VTKFile");
	doc.LinkEndChild(elementVTK);
	TiXmlElement* elementCollection = new TiXmlElement("Collection");
	elementVTK->LinkEndChild(elementCollection);
	elementCollection->SetAttribute("type", "Collection");
	elementCollection->SetAttribute("version", "0.1");
	int numFileNames = globals::allFileNames.size();
	for (int i = 0; i < numFileNames; i++)
	{
		const char* vtpFileName = globals::allFileNames.at(i).c_str();
		TiXmlElement* elementDataSet = new TiXmlElement("DataSet");
		elementCollection->LinkEndChild(elementDataSet);
		elementDataSet->SetAttribute("part", i);
		elementDataSet->SetAttribute("file", vtpFileName);
	}
	pvdFileName = globals::getFolderName() + pvdFileName;
	doc.SaveFile(pvdFileName.c_str());
}