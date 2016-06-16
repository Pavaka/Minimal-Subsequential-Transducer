#include <unordered_map>
#include <memory>
#include "MyTypes.h"
#include "State.h"
class Transducer
{
private:
	std::unordered_map<State, std::shared_ptr<State>> QminusT;
	std::vector<std::shared_ptr<State>> T;
	std::string MinimalExceptWord;
	std::shared_ptr<State> InitialState;
public:
	Transducer();
	//Construct transducer from words
	Transducer(VecPairStrStr_t&);
	void AddPairOfWords(std::string& Word, std::string& WordImage);

};