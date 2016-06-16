#include <fstream>
#include <algorithm>
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

std::string CommonPrefix(const std::string& FirstWord, const std::string& SecondWord)
{
	int SmallerWordLength = std::min(FirstWord.length(), SecondWord.length());
	std::vector<char> CommonPrefixVector;
	CommonPrefixVector.reserve(SmallerWordLength);
	int i;
	for (i = 0; i < SmallerWordLength; ++i)
	{
		if (FirstWord[i] == SecondWord[i])
		{
			CommonPrefixVector.push_back(FirstWord[i]);
		}
		else
		{
			break;
		}
	}
	CommonPrefixVector.resize(i);
	return std::string(CommonPrefixVector.begin(), CommonPrefixVector.end());
}

bool IsPrefix(const std::string& Prefix, const std::string& Word)
{
	if (CommonPrefix(Prefix, Word).compare(Prefix) == 0)
	{
		return true;
	}
	return false;
}

