#include <iostream>

#include "Test.h"
#include "Transducer.h"
void Test()
{
	Transducer Trans{};

	
	std::string Word("pavel");

	for (int i = 1; i <= Word.size(); ++i)
	{
		Trans.T.push_back(std::make_shared<State>());

		Trans.T[i - 1]->AddDeltaTransition(Word[i - 1], Trans.T[i]);
		Trans.T[i - 1]->AddLambdaTransition(Word[i - 1], std::string("dms"));
	}



	Trans.MinimalExceptWord = Word;
	Trans.MakeMinimalExceptPrefixInDictionary(std::string("pa"));
	Trans.PrintTransducer();
	//Trans.ReduceToMinimalExceptPrefixInDictionary(std::string("p"));
	//Trans.IncreaseToMinimalExceptPrefixInDictionary(std::string("pav"));
	////std::cout << "Da";
	//Trans.PrintTransducer();
	//Trans.ReduceToMinimalExceptPrefixInDictionary(std::string(""));
	//Trans.PrintTransducer();

	//Trans.QminusT.insert({ *Trans.T[2], Trans.T[2] });
	//std::shared_ptr<State> Nev = Trans.T[2]->CopyOfState();
	//Nev->PrintState();
	//std::shared_ptr<State> eq = Trans.EquivalentStateInQminusT(Nev);
	//eq->PrintState();


	std::shared_ptr<State> State1 = std::make_shared<State>();
	std::shared_ptr<State> State2 = std::make_shared<State>();
	std::shared_ptr<State> State3 = std::make_shared<State>();
	//State1->AddDeltaTransition('a', State2);
	//State1->AddLambdaTransition('a', std::string("thing"));

	//State3->AddDeltaTransition('a', State2);
	//State3->AddLambdaTransition('a', std::string("thing"));

	//State2->AddDeltaTransition('a', State3);
	//State2->AddLambdaTransition('a', std::string("thing"));

	//State1->SetDeltaTransition('a', State3);


	//Trans.QminusT.insert({ *State1, State1 });
	////Trans.QminusT.insert({*State2, State2});
	//if (Trans.EquivalentStateInQminusT(State2))
	//{
	//	std::cout << Trans.EquivalentStateInQminusT(State2)->Id;
	//}

	////if (Trans.EquivalentStateInQminusT(State3))
	////{
	////	std::cout << Trans.EquivalentStateInQminusT(State3)->Id;
	////}

	////if (Trans.EquivalentStateInQminusT(State3))
	////{
	////	std::cout << Trans.EquivalentStateInQminusT(State3)->Id;
	////}
}
