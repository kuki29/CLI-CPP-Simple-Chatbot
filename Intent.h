#ifndef INTENT_H
#define INTENT_H

#include <string>
#include <vector>

#include "Example.h"
#include "Util.h"

using namespace std;

class Intent
{
public:
	static const unsigned int MaxExamples = 10;

private:
	string Name;
	string Response;

	vector<Example> Examples;

public:
	Intent(string name);
	Intent(char* name);

	string getName() const;
	string getResponse() const;
	vector<Example> getExamples() const;
	unsigned int getExamplesQuantity() const;

	void addExample(const Example& example);
	bool deleteExample(int id);
	void addResponse(string response);

	float calculateSimilarity(string text, const char* similarity) const;

	friend ostream& operator<<(ostream& out, const Intent& intent);
};

#endif