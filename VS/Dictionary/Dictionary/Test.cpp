#include <iostream>
#include <fstream>
#include "Test.h"
#include "Transducer.h"
void Test()
{
	std::ifstream  ConstructionDataStream;
	VecPairStrStr_t ConstructionPairs;
	ConstructionDataStream.open("small");
	ReadInputFile(ConstructionDataStream, ConstructionPairs);
	Transducer Trans(ConstructionPairs);

	for (int i = 0; i < ConstructionPairs.size(); ++i)
	{
		std::cout << Trans.TraverseAndConcatenateOutputs(ConstructionPairs[i].first) << " =?= " << ConstructionPairs[i].second << std::endl;
	}
	Trans.MakeMinimalExceptPrefixInDictionary(std::string(""));
	Trans.PrintTransducer();
	
	/*
	ab xx
	abc xyy
	bab yyx
	babc yyyy
	bbb yz
	bbbc yzz
	*/

	//for (int i = 1; i <= Word.size(); ++i)
	//{
	//	Trans.T.push_back(std::make_shared<State>());

	//	Trans.T[i - 1]->AddDeltaTransition(Word[i - 1], Trans.T[i]);
	//	Trans.T[i - 1]->AddLambdaTransition(Word[i - 1], std::string("dms"));
	//}
	//Trans.AddPairOfWords(std::string("ab"), std::string("xx"));
	//Trans.AddPairOfWords(std::string("abc"), std::string("xyy"));
	//Trans.AddPairOfWords(std::string("bab"), std::string("yyx"));

	//Trans.AddPairOfWords(std::string("babc"), std::string("yyyy"));
	//Trans.AddPairOfWords(std::string("bbb"), std::string("yz"));
	//Trans.AddPairOfWords(std::string("bbbc"), std::string("yzz"));
	//Trans.MakeMinimalExceptPrefixInDictionary(std::string(""));


	//Trans.MakeMinimalExceptPrefixInDictionary(std::string(""));
	//Trans.PrintTransducer();

}
