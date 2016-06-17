#include <iostream>

#include "Test.h"
#include "Transducer.h"
void Test()
{
	Transducer Trans{};

	
	std::string Word("pavel");

	//for (int i = 1; i <= Word.size(); ++i)
	//{
	//	Trans.T.push_back(std::make_shared<State>());

	//	Trans.T[i - 1]->AddDeltaTransition(Word[i - 1], Trans.T[i]);
	//	Trans.T[i - 1]->AddLambdaTransition(Word[i - 1], std::string("dms"));
	//}
	Trans.AddPairOfWords(Word, std::string("dm"));
	Trans.PrintTransducer();
	std::cout <<	Trans.TraverseAndConcatenateOutputs(std::string("pa"));
}
