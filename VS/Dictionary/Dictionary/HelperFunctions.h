#include <string>
#include "MyTypes.h"
//Hashes a string to an int
int StringToIntHashing(std::string Word);

//Takes the opened stream with file and reads it pairwise in the defined vector type
void ReadInputFile(std::ifstream& ConstructionData, VecPairStrStr_t& ConstructionPairs);

//Find the common prefix of two strings
std::string CommonPrefix(const std::string&, const std::string&);

bool IsPrefix(const std::string& Prefix, const std::string& Word);


//Return Subtractor^-1 * Word
//Works on the assumption that Substractor is a prefix of Word
std::string SubtractStringFromLeft(std::string Subtractor, std::string Word);
