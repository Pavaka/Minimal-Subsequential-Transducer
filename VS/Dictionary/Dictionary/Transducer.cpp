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
	std::shared_ptr<State> NewState;
	for (int i = k; i < m; ++i)
	{

		//Incorrect 
		//NewState = this->T[i]->GetStateWithTransitionLetter(Word[i]);
		//T[i]->SetDeltaTransition(Word[i], NewState);
		//this->T.push_back(NewState);
		//this->QminusT.erase(this->QminusT.find(*NewState));


		//OLD BUT WORKING
		//Ti WordI  copy of current Ti with word state
		std::shared_ptr<State>& NewState = T[i]->GetStateWithTransitionLetter(Word[i])->CopyOfState();
		T[i]->SetDeltaTransition(Word[i], NewState);
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

	//std::cout << __LINE__ << std::endl;
	//std::string LongestPrefixOfWord = this->LongestPrefixOfWordInDictionary(Word);
	//std::string CommonPrefixOfMinExceptAndWord = CommonPrefix(LongestPrefixOfWord, Word);
	//this->PrintTransducer();
	//std::cout << Word << " " << this->MinimalExceptWord << " " << LongestPrefixOfWord << std::endl;
	std::string CommonPrefixOfMinExceptAndWord = CommonPrefix(this->MinimalExceptWord, Word);

	//std::cout << Word << " " << LongestPrefixOfWord << std::endl;

	this->MakeMinimalExceptPrefixInDictionary(CommonPrefixOfMinExceptAndWord);
	//std::cout << "Afterwards " << this->MinimalExceptWord << std::endl;
	int k = CommonPrefixOfMinExceptAndWord.size();
	int m = Word.size();
	//std::cout << k << m << this->T.size() << std::endl;
	//Add new states in T and their proper Delta transitions
	for (int i = k + 1; i <= m; ++i)
	{
		this->T.push_back(std::make_shared<State>());
		this->T[i - 1]->AddDeltaTransition(Word[i - 1], this->T[i]);
	}
	//Make last state in T final
	this->T[this->T.size() - 1]->SetIsFinal(true);

	//Calculate updates in lambda after that apply them, thus we calculate them with old transducer
	VecOfVecOfPairCharStr_t UpdatesOfTransitions;
	UpdatesOfTransitions.resize(this->T.size());
	//std::cout << __LINE__ << std::endl << k << m;
	//std::cout << "Crash report" << this->T.size() << __LINE__ << std::endl;
	//std::cout << "Crash report" <<  __LINE__ << std::endl;

	//udpates part one
	//possible optimizations
	//this->PrintTransducer();
	for (int i = 1; i <= k; ++i)
	{
		//std::cout << __LINE__ << " Enter loop " + Word.substr(0, i) <<std::endl;
		//std::cout << i << " " << Word << std::endl;
		std::string Substractor = CommonPrefix( this->LambdaTraverse(Word.substr(0, i - 1) ), WordImage);
		//this->LambdaTraverse(Word.substr(0, i));

		//std::cout << __LINE__ << std::endl;
		std::string RightOutput = CommonPrefix(this->LambdaTraverse(Word.substr(0, i)), WordImage);
		//std::cout << "Substractor right output < " << Substractor << " " << RightOutput << std::endl;
		std::string NewOutput = SubtractStringFromLeft(Substractor, RightOutput);

		UpdatesOfTransitions[i - 1].push_back(std::make_pair(Word[i - 1], 
			NewOutput
			//SubtractStringFromLeft(CommonPrefix(this->LambdaTraverse(Word.substr(0, i - 1)), WordImage), CommonPrefix(this->LambdaTraverse(Word.substr(0, i)), WordImage))
			));
		
	}
	//std::cout << "Crash report" << __LINE__ << std::endl;

	//part two
	char Sigma;
	std::string AllLettersMinusOne;
	for (int i = 1; i <= k; ++i)
	{
		AllLettersMinusOne = this->T[i]->AllTransitionalLettersExceptOne(Word[i]);
		for (int j = 0; j < AllLettersMinusOne.size(); ++j)
		{
			Sigma = AllLettersMinusOne[j];
			//std::string Subtractor = CommonPrefix(this->LambdaTraverse(Word.substr(0, i)), WordImage);
			//std::string RightPart = this->LambdaTraverse(Word.substr(0, i) + Sigma);
			//std::string Result = SubtractStringFromLeft(Subtractor, RightPart);
			UpdatesOfTransitions[i].push_back(std::make_pair(Sigma,
				//Result
				SubtractStringFromLeft(CommonPrefix(this->LambdaTraverse(Word.substr(0, i)), WordImage), this->LambdaTraverse(Word.substr(0, i) + Sigma))
				));
		}
	}
	//part three
	if(k < Word.size())
	{
		std::string OutputWithFirstKLetters = this->LambdaTraverse(Word.substr(0, k));
		std::string Substractor = CommonPrefix(OutputWithFirstKLetters, WordImage);
		//std::string Result = SubtractStringFromLeft(Substractor, WordImage);
		UpdatesOfTransitions[k].push_back(std::make_pair(Word[k],
			SubtractStringFromLeft(Substractor, WordImage)
			));
	}

	//part four
	for (int i = k + 1; i < m; ++i)
	{
		this->T[i]->AddLambdaTransition(Word[i], std::string(""));
	}

	std::string FirstILettersOfWord;
	std::string OutputWithFirstILetters;
	//std::cout << k << m << " HERE\n";

	//Update Psi Values
	for (int i = 1; i <= k; ++i)
	{
		if (this->T[i]->GetIsFinal())
		{
			FirstILettersOfWord = Word.substr(0, i);
			OutputWithFirstILetters = this->LambdaTraverse(FirstILettersOfWord);
			std::string Subtractor = CommonPrefix(OutputWithFirstILetters, WordImage);
			std::string Result = SubtractStringFromLeft(Subtractor, OutputWithFirstILetters) + T[i]->GetPsi();
			T[i]->SetPsi(
				Result
				//SubtractStringFromLeft(CommonPrefix(OutputWithFirstILetters, WordImage), this->LambdaTraverse(FirstILettersOfWord)) + T[i]->GetPsi()
				);
		}
	}


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
	//this->PrintTransducer();
	//std::cout << "Exit add \n";
}

std::string Transducer::TraverseAndConcatenateOutputs(std::string Word)
{
	//std::shared_ptr<State> CurrentState = this->InitialState;
	std::shared_ptr<State> CurrentState = this->T[0];

	std::string Result("");
	for (int i = 0; i < Word.size(); ++i)
	{
		Result += CurrentState->GetOutputWithTransitonLetter(Word[i]);
		CurrentState = CurrentState->GetStateWithTransitionLetter(Word[i]);
	}
	Result += CurrentState->GetPsi();
	if (!CurrentState->GetIsFinal())
	{
		return  Word + " Not Found in the dictionary";
	}
	return Result;
}
//BAD SOFTWARE ENGINERING DUPICATE CODE
std::string Transducer::LambdaTraverse(std::string Word)
{

	std::shared_ptr<State> CurrentState = this->T[0];
	std::string Result("");
	//std::cout << Word << std::endl;
	for (int i = 0; i < Word.size(); ++i)
	{
		//DANGER
		Result += CurrentState->GetOutputWithTransitonLetter(Word[i]);
		CurrentState = CurrentState->GetStateWithTransitionLetter(Word[i]);

	}
	return Result;
}

std::string Transducer::LambdaPsiTraverse(std::string Word)
{
	//this->InitialState ?!?
	std::shared_ptr<State> CurrentState = this->T[0];
	std::string Result("");
	for (int i = 0; i < Word.size(); ++i)
	{
		Result += CurrentState->GetOutputWithTransitonLetter(Word[i]);
		CurrentState = CurrentState->GetStateWithTransitionLetter(Word[i]);
	}
	Result += CurrentState->GetPsi();
	return Result;
}

std::string Transducer::LongestPrefixOfWordInDictionary(std::string Word)
{		
	//std::cout << "Enter longsst prefix with word , " << Word << std::endl;
	//std::shared_ptr<State>& CurrentState = this->InitialState;
	std::shared_ptr<State> CurrentState = this->T[0];
	for (int i = 0; i < Word.size(); ++i)
	{
		//std::cout << CurrentState->HasTransitionWithLetter(Word[i]) << Word[i];
		if (! (CurrentState->HasTransitionWithLetter(Word[i])))
		{
			//std::cout << "HERE = "<< Word.substr(0, i)<< std::endl;
			return Word.substr(0, i);
		}
		CurrentState = CurrentState->GetStateWithTransitionLetter(Word[i]);
	}
	
	return Word;
}


