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
	Trans.PrintTransducer();





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