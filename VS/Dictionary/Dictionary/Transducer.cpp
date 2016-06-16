#include "Transducer.h"
#include "HelperFunctions.h"
#include <cassert>
//Needs to be tested
void Transducer::ReduceToMinimalExceptPrefixInDictionary(std::string & Word)
{
	assert(IsPrefix(Word, this->MinimalExceptWord));
	if (this->MinimalExceptWord == Word)
	{
		return;
	}
	int k = Word.size();
	int m = this->MinimalExceptWord.size();
	for (int i = m; i > k; --i)
	{
		//If no equivalent state in QminusT
		std::shared_ptr<State>& EquivalentState = this->EquivalentStateInQminusT(T[i]);
		if (!EquivalentState)
		{
			this->AddStateInQminusT(T[i]);
		}
		else
		{
			//Redirect transition
			char Letter = this->MinimalExceptWord[i - 1];
			T[i - 1]->SetDeltaTransition(Letter, EquivalentState);
		}
		this->T.pop_back();
	}
	this->MinimalExceptWord = Word;

}
void Transducer::IncreaseToMinimalExceptPrefixInDictionary(std::string & Word)
{
	if (this->MinimalExceptWord == Word)
	{
		return;
	}
	int k = this->MinimalExceptWord.size();
	int m = Word.size();
	std::cout << k << m << this->T.size();
	
	for (int i = k; i < m; ++i)
	{
		std::cout << i << this->T.size();
		T.push_back(std::shared_ptr<State>());
		//std::cout << "Crash report " << __LINE__ << std::endl;
		T[i]->SetDeltaTransition(Word[i], T[i+1]);
	}
	this->MinimalExceptWord = Word;
}
void Transducer::MakeMinimalExceptPrefixInDictionary(std::string& Word)
{
	if (Word == this->MinimalExceptWord)
	{
		return;
	}
	std::string ComPref = CommonPrefix(Word, this->MinimalExceptWord);
	this->ReduceToMinimalExceptPrefixInDictionary(ComPref);
	this->IncreaseToMinimalExceptPrefixInDictionary(Word);

}
std::shared_ptr<State> Transducer::EquivalentStateInQminusT(std::shared_ptr<State>& CurrentState)
{
	auto Iterator = this->QminusT.find(*CurrentState);
	if (Iterator == QminusT.end())
	{
	return std::shared_ptr<State>();
	}
	else
	{
		return Iterator->second;
	}
}
void Transducer::AddStateInQminusT(std::shared_ptr<State>& CurrentState)
{
	this->QminusT.insert({ *CurrentState, CurrentState });
}
void Transducer::PrintTransducer()
{
	std::cout << "Print Transducer\n";
	for (auto It : QminusT)
	{
		std::cout << " ---- QminusT ----\n";
		It.second->PrintState();
	}
	for (int i = 0; i < this->T.size(); ++i)
	{
		std::cout << " ----   T  ----\n";
		this->T[i]->PrintState();
	}
}
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
	std::string CommonPrefixOfMinExceptAndWord = CommonPrefix(this->MinimalExceptWord, Word);
	this->MakeMinimalExceptPrefixInDictionary(CommonPrefixOfMinExceptAndWord);

	
}
