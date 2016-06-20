#include <unordered_map>
#include <memory>
#include "MyTypes.h"
#include "State.h"
class Transducer
{
//@Make it private after testing
public:
	std::unordered_map<State, std::shared_ptr<State>> QminusT;
	std::vector<std::shared_ptr<State>> T;
	std::string MinimalExceptWord;
	std::shared_ptr<State> InitialState;
	//Works on the assumption that that Word is a prefix of this->MinimalExcept
	void ReduceToMinimalExceptPrefixInDictionary(std::string& Word);
	//Works on the assumption that this->MinimalExcept is prefix of Word
	void IncreaseToMinimalExceptPrefixInDictionary(std::string& Word);
	void MakeMinimalExceptPrefixInDictionary(std::string& Word);
	std::shared_ptr<State> EquivalentStateInQminusT(std::shared_ptr<State>&);
	void AddStateInQminusT(std::shared_ptr<State>&);
public:
	void PrintTransducer();
	Transducer();
	//Construct transducer from words
	Transducer(VecPairStrStr_t&);
	void AddPairOfWords(std::string& Word, std::string& WordImage);
	std::string TraverseAndConcatenateOutputs(std::string);
	std::string LambdaTraverse(std::string);
	std::string LambdaPsiTraverse(std::string);
	std::string LongestPrefixOfWordInDictionary(std::string Word);

};