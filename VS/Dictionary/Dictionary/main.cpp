#include <iostream>
#include <string>
#include <fstream>
//#include <cstdio>
//#include <vector>

#include "MyTypes.h"
#include "Transducer.h"
#include "Test.h"
int main()
{
	bool ExitProgram = false;
	std::string Command;
	std::string ConstructionFileName;
	std::ifstream  ConstructionDataStream;
	VecPairStrStr_t ConstructionPairs;
	//std::unique_ptr<Transducer> Trans;
	while (!ExitProgram)
	{
		std::cout << "Enter a command, type help to list them all" << std::endl;
		std::cin >> Command;		
		if (Command == "help")
		{
			//TODO - write text describing the commands
			std::cout << "HELP\n";
		}
		else if (Command == "construct")
		{
			std::cout << "Enter name of file to construct automata\n";
			std::cin >> ConstructionFileName;
			ConstructionDataStream.open(ConstructionFileName.c_str());
			ReadInputFile(ConstructionDataStream, ConstructionPairs);
			Transducer Trans(ConstructionPairs);

		}
		else if (Command == "add")
		{

		}
		else if (Command == "delete")
		{

		}
		else if (Command == "exit")
		{
			ExitProgram = true;
		}
		else if (Command == "test")
		{
			Test();
		}
		else if (Command == "print")
		{
			//Trans->PrintTransducer();
		}
	}


	////State state1{};
	////State state2{};
	////State state3{};
	//std::shared_ptr<State> state1 = std::make_shared<State>();
	//std::shared_ptr<State> state2 = std::make_shared<State>();
	//std::shared_ptr<State> state3 = std::make_shared<State>();
	//std::unordered_map<State, int> x;
	//state1->AddDeltaTransition('a', state3);
	//state1->AddLambdaTransition('a', std::string("tuka"));
	//x.insert({ *state1, 11 });
	//x.insert({ *state2, 10000 });
	//x.insert({ *state3, 331 });
	//for (auto It : x)
	//{
	//	std::cout << "----";
	//	std::cout  << It.second << std::endl;
	//}
	//std::cout << x.bucket(*state1);
	////std::cout << (state1 == state2) << std::endl;
	////state2.AddDeltaTransition('a', state3);
	////state2.AddLambdaTransition('a', std::string("tuka"));
	////std::cout << (state1 == state2) << std::endl;
	return 0;
}
