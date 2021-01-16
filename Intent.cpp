#include "Intent.h"

Intent::Intent(string name)
{
	if (name.length() > 0)
	{
		Name = name;
	}
	else
	{
		throw ERR_EMPTY;
	}
}

Intent::Intent(char* name)
{
	if (name != '\0')
	{
		Name = string(name);
	}
	else
	{
		throw ERR_EMPTY;
	}
}

string Intent::getName() const
{
	return Name;
}

string Intent::getResponse() const
{
	return Response;
}

vector<Example> Intent::getExamples() const
{
	return Examples;
}

unsigned int Intent::getExamplesQuantity() const
{
	return Examples.size();
}

void Intent::addExample(const Example& example)
{
	if (Examples.size() < MaxExamples)
	{
		Examples.push_back(example);
	}
	else
	{
		throw ERR_MAXEXAMPLES;
	}
}

bool Intent::deleteExample(int id)
{
	if (id >= 0 && id < MaxExamples)
	{
		Examples.erase(Examples.begin() + id);
		return true;
	}
	else
	{
		throw ERR_EXAMPLE;
		return false;
	}
}

void Intent::addResponse(string response)
{
	char str[1024];
	cout << "Input new response: ";
	cin.getline(str, 1023);

	Response = string(str);
}

float Intent::calculateSimilarity(string text, const char* similarity) const
{
	float (Example::*similarityAlgorithm)(string) const;

	if (!strcmp("jc", similarity))
	{
		similarityAlgorithm = &Example::jaccardSimilarity;
	}
	else if (!strcmp("ng", similarity))
	{
		similarityAlgorithm = &Example::ngramSimilarity;
	}
	else
	{
		throw ERR_SIMILARITY;
		return 0;
	}

	float maxSimilarity = 0;
	for (Example example : Examples)
	{
		if (maxSimilarity < (example.*similarityAlgorithm)(text))
		{
			maxSimilarity = (example.*similarityAlgorithm)(text);
		}
	}

	return maxSimilarity;
}

ostream& operator<<(ostream& out, const Intent& intent)
{
	out << "Intent: " << intent.Name << endl;
	out << "Response: " << intent.Response << endl;
	
	for (int i = 0; i < intent.getExamplesQuantity(); i++)
	{
		out << intent.Examples[i];

		if (i < intent.getExamplesQuantity() - 1)
		{
			out << endl;
		}
	}

	return out;
}