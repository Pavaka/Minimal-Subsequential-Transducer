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
	//Add new states in T and their proper Delta transitions
	for (int i = k + 1; i <= m; ++i)
	{
		this->T.push_back(std::make_shared<State>());
		T[i - 1]->AddDeltaTransition(Word[i - 1], T[i]);
		//@DELETE
		//T[i - 1]->AddLambdaTransition(Word[i - 1], std::string("ZZZ"));
		//std::cout << "Crash Report" << __LINE__ << std::endl;
	}
	//Make last state in T final
	this->T[this->T.size() - 1]->SetIsFinal(true);

	//Update Psi Values
	for (int i = 1; i <= k; ++i)
	{
		if (this->T[i]->GetIsFinal())
		{

			std::string FirstILettersOfWord = Word.substr(0, i);
			this->TraverseAndConcatenateOutputs(FirstILettersOfWord);

			std::string OutputWithFirstILetters = this->TraverseAndConcatenateOutputs(FirstILettersOfWord);
			std::string ComPref = CommonPrefix(OutputWithFirstILetters, WordImage);
			std::string Result =   CommonPrefix(ComPref, OutputWithFirstILetters) + T[i]->GetPsi();
			T[i]->SetPsi(Result);
		}
	}

	//Calculate updates in lambda after that apply them, thus we calculate them with old transducer
	VecOfVecOfPairCharStr_t UpdatesOfTransitions;
	UpdatesOfTransitions.resize(this->T.size());

	//udpates part one
	//possible optimizations
	for (int i = 1; i <= k; ++i)
	{
		std::string Substractor = CommonPrefix(this->TraverseAndConcatenateOutputs(Word.substr(0, i - 1)), WordImage);
		std::string RightOutput = CommonPrefix(this->TraverseAndConcatenateOutputs(Word.substr(0, i)), WordImage);
		std::string NewOutput = SubtractStringFromLeft(Substractor, RightOutput);
		UpdatesOfTransitions[i - 1].push_back(std::make_pair(Word[i - 1], NewOutput));
		
	}

	//part two
	for (int i = 1; i <= k; ++i)
	{
		std::string AllLettersMinusOne = this->T[i]->AllTransitionalLettersExceptOne(Word[i]);
		for (int j = 0; j < AllLettersMinusOne.size(); ++j)
		{
			char Sigma = AllLettersMinusOne[j];
			std::string Subtractor = CommonPrefix(this->TraverseAndConcatenateOutputs(Word.substr(0, i)), WordImage);
			std::string RightPart = this->TraverseAndConcatenateOutputs(Word.substr(0, i) + Sigma);
			std::string Result = SubtractStringFromLeft(Subtractor, RightPart);
			UpdatesOfTransitions[i].push_back(std::make_pair(Sigma, Result));
		}
	}
	//part three
	if(k < Word.size())
	{
		std::string OutputWithFirstKLetters = this->TraverseAndConcatenateOutputs(Word.substr(0, k));

		std::string Substractor = CommonPrefix(OutputWithFirstKLetters, WordImage);
		std::string Result = SubtractStringFromLeft(Substractor, WordImage);
		//std::cout << "CARSAH " << __LINE__ << Word[k] << " " << Result << std::endl;

		UpdatesOfTransitions[k].push_back(std::make_pair(Word[k], Result));
		//this->T[k]->AddLambdaTransition(Word[k], Result);
	}
	//part four
	for (int i = k + 1; i < m; ++i)
	{
		this->T[i]->AddLambdaTransition(Word[i], std::string(""));
	}


	//std::cout << "Crash Report" << __LINE__ << std::endl;
	//Apply updates
	for (int i = 0; i < UpdatesOfTransitions.size(); ++i)
	{
		for (std::pair<char, std::string> Pair : UpdatesOfTransitions[i])
		{
			this->T[i]->SetLambdaTransition(Pair.first, Pair.second);
		}
	}

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
