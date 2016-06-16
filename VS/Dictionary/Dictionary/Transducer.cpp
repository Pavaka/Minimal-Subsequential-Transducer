#include "Transducer.h"
#include "HelperFunctions.h"
Transducer::Transducer()
{
	this->InitialState = std::make_shared<State>();
	this->MinimalExceptWord = std::string("");
	this->T.push_back(this->InitialState);
}

Transducer::Transducer(VecPairStrStr_t& ConstructionVector): Transducer()
{
	for (int i = 0; i < ConstructionVector.size(); ++i)
	{
		this->AddPairOfWords(ConstructionVector[i].first, ConstructionVector[i].second);
	}
}

void Transducer::AddPairOfWords(std::string& Word, std::string& WordImage)
{

}
