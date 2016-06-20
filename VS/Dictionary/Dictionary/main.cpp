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
	//std::cout << "Enter name of file to construct automata\n";
	//std::cin >> ConstructionFileName;
	//ConstructionDataStream.open(ConstructionFileName.c_str());
	//ReadInputFile(ConstructionDataStream, ConstructionPairs);
	//Transducer Trans(ConstructionPairs);

	while (!ExitProgram)
	{
		std::cout << "Enter a command, type help to list them all" << std::endl;
		std::cin >> Command;	

		if (Command == "help")
		{
			//TODO - write text describing the commands
			std::cout << "HELP\n";
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
		//else if (Command == "add")
		//{
		//	std::string Word, WordImage;
		//	std::cin >> Word;
		//	std::cin >> WordImage;
		//	Trans.MakeMinimalExceptPrefixInDictionary(std::string(""));
		//	Trans.AddPairOfWords(Word, WordImage);
		//}
		//else if (Command == "print")
		//{
		//	Trans.PrintTransducer();
		//}
		//else if (Command == "traverse")
		//{
		//	std::string Word;
		//	std::cin >> Word;
		//	std::cout << Word << " -> " << Trans.TraverseAndConcatenateOutputs(Word) << std::endl;
		//}
		else if (Command == "testpairs")
		{

		}
	}
	return 0;
}
