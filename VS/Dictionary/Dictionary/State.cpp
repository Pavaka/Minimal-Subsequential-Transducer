#include <algorithm>
#include "State.h"
State::State():Id(IdCounter++)
{
	this->IsFinal = false;
	this->Psi = std::string("");
}

//Used to check if two states are equivalent 
//Assumption, they are eqivalent iff their delta transitions go to the same state Ids
//not checking the actual rigt languages
bool State::operator==(const State& Other) const
{
	
	if (this->IsFinal != Other.IsFinal)
	{
		return false;
	}
	else if (this->Psi != Other.Psi)
	{
		return false;
	}
	else if (this->Lambda.size() != Other.Lambda.size())
	{
		return false;
	}
	//Check if transitions are equal
	int NumberOfTransitons = this->Lambda.size();
	//Check if Lambda transitions are equal
	std::vector<std::pair<char, std::string>> ThisLambdaTransitions;
	std::vector<std::pair<char, std::string>> OtherLambdaTransitions;

	ThisLambdaTransitions.reserve(NumberOfTransitons);
	OtherLambdaTransitions.reserve(NumberOfTransitons);

	for (auto It : this->Lambda)
	{
		ThisLambdaTransitions.push_back(std::make_pair(It.first, It.second));
	}
	for (auto It : Other.Lambda)
	{
		OtherLambdaTransitions.push_back(std::make_pair(It.first, It.second));
	}

	std::sort(ThisLambdaTransitions.begin(), ThisLambdaTransitions.end());
	std::sort(OtherLambdaTransitions.begin(), OtherLambdaTransitions.end());

	for (int i = 0; i < NumberOfTransitons; ++i)
	{
		if ((ThisLambdaTransitions[i].first != OtherLambdaTransitions[i].first) || (ThisLambdaTransitions[i].second != OtherLambdaTransitions[i].second))
		{
			return false;
		}
	}
	//Now it is left to check if their lambdas are going to the same states 
	std::vector<std::pair<char, int>> ThisDeltaTransitions;
	std::vector<std::pair<char, int>> OtherDeltaTransitions;

	ThisDeltaTransitions.reserve(NumberOfTransitons);
	OtherDeltaTransitions.reserve(NumberOfTransitons);

	for (auto It : this->Delta)
	{
		ThisDeltaTransitions.push_back(std::make_pair(It.first, It.second->Id));
	}

	for (auto It : Other.Delta)
	{
		OtherDeltaTransitions.push_back(std::make_pair(It.first, It.second->Id));
	}

	std::sort(ThisDeltaTransitions.begin(), ThisDeltaTransitions.end());
	std::sort(OtherDeltaTransitions.begin(), OtherDeltaTransitions.end());
	
	for (int i = 0; i < NumberOfTransitons; ++i)
	{
		if (ThisDeltaTransitions[i].second != OtherDeltaTransitions[i].second)
		{
			return false;
		}
	}
	
	return true;
}

void State::AddDeltaTransition(char Letter, std::shared_ptr<State>& ToState)
{
	this->Delta.insert({ Letter, ToState });
}

void State::AddLambdaTransition(char Letter, std::string Output)
{
	this->Lambda.insert({ Letter, Output });
}

bool State::GetIsFinal() const
{
	return this->IsFinal;
}

std::string State::GetPsi() const
{
	return this->Psi;
}

std::vector<std::pair<char, int>> State::GetDeltaAsSortedVectorOfPairs() const
{
	std::vector<std::pair<char, int>> SortedDeltaPairs;
	SortedDeltaPairs.reserve(this->Delta.size());
	for (auto It : this->Delta)
	{
		SortedDeltaPairs.push_back(std::make_pair(It.first, It.second->Id));
	}
	return std::move(SortedDeltaPairs);
}

std::vector<std::pair<char, std::string>> State::GetLambdaAsSortedVectorOfPairs() const
{
	std::vector<std::pair<char, std::string>> SortedLambdaPairs;
	SortedLambdaPairs.reserve(this->Lambda.size());
	for (auto It : this->Lambda)
	{
		SortedLambdaPairs.push_back(std::make_pair(It.first, It.second));
	}

	return std::move(SortedLambdaPairs);
}

void State::SetDeltaTransition(char Letter, std::shared_ptr<State>& ToState)
{

	auto It = this->Delta.find(Letter);
	if (It != this->Delta.end())
	{
		It->second = ToState;
	}
}

void State::PrintState()
{
	std::cout << "State Id = " << this->Id << (this->IsFinal ? " Final" : " Not Final ");
	std::cout << " Psi = " << this->Psi << std::endl;
	std::vector<std::pair<char, int>> Deltas = this->GetDeltaAsSortedVectorOfPairs();
	std::vector<std::pair<char, std::string>> Lambdas = this->GetLambdaAsSortedVectorOfPairs();
	if (Lambdas.size() == 0)
	{
		std::cout << "No Transitions\n";
	}
	for (int i = 0; i < Lambdas.size(); ++i)
	{
		//this Id Transition Letter To State Output
		printf("< %d, %c, <%d, %s >>\n", this->Id, Deltas[i].first, Deltas[i].second, Lambdas[i].second.c_str());
	}
}

std::shared_ptr<State> State::CopyOfState()
{
	std::shared_ptr<State> NewState = std::make_shared<State>();
	NewState->SetIsFinal(this->IsFinal);
	NewState->SetPsi(this->Psi);
	for (auto It : this->Delta)
	{
		NewState->AddDeltaTransition(It.first, It.second);
	}

	for (auto It : this->Lambda)
	{
		NewState->AddLambdaTransition(It.first, It.second);
	}
	return NewState;
}

void State::SetIsFinal(bool Finality)
{
	this->IsFinal = Finality;
}

void State::SetPsi(std::string Psi)
{
	this->Psi = Psi;
}

std::shared_ptr<State>& State::GetStateWithTransitionLetter(char Letter)
{

	return this->Delta.find(Letter)->second;
}

