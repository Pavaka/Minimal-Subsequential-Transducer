#include <iostream>
#include <string>
#include <fstream>

#include "MyTypes.h"
#include "Transducer.h"

int main()
{
	bool ExitProgram = false;
	std::string Command;
	std::string ConstructionFileName;
	std::ifstream  ConstructionDataStream;
	VecPairStrStr_t ConstructionPairs;
	std::cout << "Enter name of file to construct automata\n";
	std::cin >> ConstructionFileName;
	ConstructionDataStream.open(ConstructionFileName.c_str());
	ReadInputFile(ConstructionDataStream, ConstructionPairs);
	Transducer Trans(ConstructionPairs);
	return 0;
}
