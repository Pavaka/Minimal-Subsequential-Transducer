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
		//Ti WordI  copy of current Ti with word state
		std::shared_ptr<State>& NewState = T[i]->GetStateWithTransitionLetter(Word[i])->CopyOfState();
		T[i]->SetDeltaTransition(Word[i], NewState);
		//std::cout << "Crash report " << __LINE__ << std::endl;

		this->T.push_back(NewState);
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
	std::cout << "***********Print Transducer\n";
	for (int i = 0; i < this->T.size(); ++i)
	{
		std::cout << " ----   T  ----\n";
		this->T[i]->PrintState();
		std::cout << std::endl;

	}
	for (auto It : QminusT)
	{
		std::cout << " ---- QminusT ----\n";
		It.second->PrintState();
		std::cout << std::endl;

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
	int k = CommonPrefixOfMinExceptAndWord.size();
	int m = Word.size();
	std::cout << "Crash Report" << __LINE__ << std::endl;
	//Add new states in T and their proper Delta transitions
	for (int i = k + 1; i <= m; ++i)
	{
		this->T.push_back(std::make_shared<State>());
		T[i - 1]->AddDeltaTransition(Word[i - 1], T[i]);
		//@DELETE
		T[i - 1]->AddLambdaTransition(Word[i - 1], std::string("dmsmix"));
		//std::cout << "Crash Report" << __LINE__ << std::endl;
	}
	//Make last state in T final
	this->T[this->T.size() - 1]->SetIsFinal(true);

	//Update Psi Values





	//Right ?
	this->MinimalExceptWord = Word;
}

std::string Transducer::TraverseAndConcatenateOutputs(std::string Word)
{
	std::shared_ptr<State> CurrentState = this->InitialState;
	std::string Result("");
	for (int i = 0; i < Word.size(); ++i)
	{
		Result += CurrentState->GetOutputWithTransitonLetter(Word[i]);
		CurrentState = CurrentState->GetStateWithTransitionLetter(Word[i]);
	}

	return Result;
}
