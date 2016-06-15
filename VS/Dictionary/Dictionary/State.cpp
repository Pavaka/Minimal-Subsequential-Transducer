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
		ThisDeltaTransitions.push_back(std::make_pair(It.first, It.second.Id));
	}

	for (auto It : Other.Delta)
	{
		OtherDeltaTransitions.push_back(std::make_pair(It.first, It.second.Id));
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

void State::AddDeltaTransition(char Letter, State & ToState)
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
		SortedDeltaPairs.push_back(std::make_pair(It.first, It.second.Id));
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

