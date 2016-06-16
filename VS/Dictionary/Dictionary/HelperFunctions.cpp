#include <fstream>
#include "HelperFunctions.h"

int StringToIntHashing(std::string Word)
{
	int Result = 0;
	for (int i = 0; i < Word.size(); ++i)
	{
		Result += Word[i] * Word[i];
	}
	return Result;
}

void ReadInputFile(std::ifstream& ConstructionData, VecPairStrStr_t& ConstructionPairs)
{
	std::string CurrentWord, CurrentWordImage;
	while (!ConstructionData.eof())
	{
		ConstructionData >> CurrentWord;
		ConstructionData >> CurrentWordImage;
		ConstructionPairs.push_back(std::make_pair(CurrentWord, CurrentWordImage));
	}
}
