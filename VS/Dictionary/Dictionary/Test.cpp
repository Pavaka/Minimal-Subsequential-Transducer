#include <iostream>
#include <fstream>
#include <ctime>
#include "Test.h"
#include "Transducer.h"

void Test()
{
	clock_t begin = clock();

	std::ifstream  ConstructionDataStream;
	VecPairStrStr_t ConstructionPairs;
	//ConstructionDataStream.open("narrow.txt");
	ConstructionDataStream.open("100k");
	ReadInputFile(ConstructionDataStream, ConstructionPairs);
	std::cout << "Words in dict = " << ConstructionPairs.size() << std::endl;
	Transducer Trans(ConstructionPairs);
	//std::cout << ConstructionPairs.size();
	//Trans.MakeMinimalExceptPrefixInDictionary(std::string(""));
	for (int i = 0; i < ConstructionPairs.size(); ++i)
	{	
		if (Trans.LambdaPsiTraverse(ConstructionPairs[i].first) != ConstructionPairs[i].second)
		{
			std::cout << "Broken word = " << ConstructionPairs[i].first << std::endl;
			std::cout << Trans.LambdaPsiTraverse(ConstructionPairs[i].first) << " =?= " << ConstructionPairs[i].second << std::endl;
		}
	}

	//Trans.PrintTransducer();
	
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

	//Transducer Trans{};
	//const int sizz = 8;
	//std::vector<std::string> Wordz = {
	//	std::string("ab"), std::string("xx"),
	//	std::string("abc"),std::string("xyy"),
	//	std::string("bab"),std::string("yyx"),
	//	std::string("babc"),std::string("yyyy")
	//};
	//for (int i = 0; i < 6; i += 2)
	//{
	//	Trans.AddPairOfWords(Wordz[i], Wordz[i + 1]);
	//}

	//Trans.PrintTransducer();
	//Trans.AddPairOfWords(std::string("bbbc"), std::string("yzz"));

	//Transducer Trans{};
	//Trans.AddPairOfWords(std::string("bf"), std::string("xxxx"));
	//Trans.AddPairOfWords(std::string("abc"), std::string("xyy"));
	//Trans.AddPairOfWords(std::string("bab"), std::string("yyx"));
	//Trans.AddPairOfWords(std::string("babc"), std::string("yyyy"));
	//std::cout << "miniexcept = "<<Trans.MinimalExceptWord << std::endl;
	////Trans.PrintTransducer();
	//Trans.AddPairOfWords(std::string("ab"), std::string("xx"));
	//Trans.PrintTransducer();
	//std::cout << Trans.LongestPrefixOfWordInDictionary(std::string("b"));
	//Trans.PrintTransducer();
//std::cout << Trans.TraverseAndConcatenateOutputs(std::string("bbbf"));


	//Trans.PrintTransducer();


	//Transducer Trans{};
	//Trans.AddPairOfWords(std::string("pd"), std::string("kn"));
	//Trans.AddPairOfWords(std::string("pdvr"), std::string("viv"));
	//Trans.PrintTransducer();
	//Trans.AddPairOfWords(std::string("pigf"), std::string("ypc"));
	//Trans.PrintTransducer();

	//Trans.MakeMinimalExceptPrefixInDictionary(std::string(""));


	//Trans.MakeMinimalExceptPrefixInDictionary(std::string(""));

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << std::endl << elapsed_secs << std::endl;
}
