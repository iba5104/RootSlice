#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include <string>
#include <vector>
#include <stdlib.h>
#include "tinyxml.h"

using namespace std;

class globals
{
private:
	static vector<string> allFileNames;
	static string outputFolderPrefix;
public:
	static void addToFileNamesVector(string filename);
	static void resetFileNameList();
	static void setFolderName(string folderName);
	static string getFolderName();
	static void writePVDFile(string pvdFileName);
};
#endif // GLOBALS_H_INCLUDED