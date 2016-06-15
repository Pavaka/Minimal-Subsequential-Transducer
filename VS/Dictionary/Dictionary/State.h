#include <unordered_map>
static int IdCounter = 0;
class State
{
private:
	std::unordered_map<char, State> Delta;
	std::unordered_map<char, std::string> Lambda;
	std::string Psi;
	bool IsFinal;
public:
	const int Id;
	State();
	bool operator==(const State& Other) const;
	void AddDeltaTransition(char Letter, State& ToState);
	void AddLambdaTransition(char Letter, std::string Output);
	void GetIsFinal();
};

namespace std
{
	template<>
	struct hash<State>
	{
		std::size_t operator()(const State& k) const
		{
			std::size_t HashCode = 0;
			HashCode += State.
			return 1000;
		}
	};
}
