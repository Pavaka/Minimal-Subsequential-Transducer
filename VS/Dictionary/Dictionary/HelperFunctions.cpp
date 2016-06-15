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