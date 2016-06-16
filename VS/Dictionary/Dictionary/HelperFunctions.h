#include <string>
#include "MyTypes.h"
//Hashes a string to an int
int StringToIntHashing(std::string Word);

//Takes the opened stream with file and reads it pairwise in the defined vector type
void ReadInputFile(std::ifstream& ConstructionData, VecPairStrStr_t& ConstructionPairs);
