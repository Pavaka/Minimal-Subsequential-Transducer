#include <iostream>

#include "State.h"
int main()
{
	State state1{};
	State state2{};
	State state3{};


	std::unordered_map<State, int> x;
	x.insert({ state1, 11 });
	state1.AddDeltaTransition('a', state3);
	state1.AddLambdaTransition('a', std::string("tuka"));
	x.insert({ state2, 10000 });
	x.insert({ state3, 331 });
	for (auto It : x)
	{
		std::cout << "3";
		std::cout  << It.second << std::endl;
	}

	//std::cout << (state1 == state2) << std::endl;
	state1.AddDeltaTransition('a', state3);
	state1.AddLambdaTransition('a', std::string("tuka"));
	//std::cout << (state1 == state2) << std::endl;
	//state2.AddDeltaTransition('a', state3);
	//state2.AddLambdaTransition('a', std::string("tuka"));
	//std::cout << (state1 == state2) << std::endl;




	int zztop;
	std::cin >> zztop;
	return 0;
}
