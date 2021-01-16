#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <string>
#include <vector>

#include "Util.h"

using namespace std;

class Example
{
private:
	unsigned int Id;
	string Text;
	vector<string> Tokens;
	static unsigned int NextId;

public:
	Example(string text);
	void resetNextId();

	int getId() const;
	string getText() const;
	vector<string> getTokens() const;

	float jaccardSimilarity(string text) const;
	float ngramSimilarity(string text) const;

	friend ostream& operator<<(ostream& out, const Example& example);

private:
	static vector<string> Create3Grams(string str);
};

#endif