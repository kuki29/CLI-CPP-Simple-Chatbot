#include "Example.h"

unsigned int Example::NextId = 1;

Example::Example(string text)
{
	if (text.length() == 0)
	{
		throw ERR_EMPTY;
		return;
	}

	Text = text;
	Id = NextId;
	NextId++;
	Tokens = Util::extractTokens(Text);
	
	if (Tokens.size() == 0)
	{
		throw ERR_EMPTY;
	}
}

void Example::resetNextId()
{
	NextId = 1;
}

int Example::getId() const
{
	return Id;
}
string Example::getText() const
{
	return Text;
}
vector<string> Example::getTokens() const
{
	return Tokens;
}

float Example::jaccardSimilarity(string text) const
{
	vector<string> textTokens = Util::extractTokens(text);
	unsigned int coincidencies = 0;

	for (string token : Tokens)
	{
		if (find(textTokens.begin(), textTokens.end(), token) != textTokens.end())
		{
			coincidencies++;
		}
	}

	float result = ((float) coincidencies) / 
		((float) Tokens.size() + (float) textTokens.size() - (float) coincidencies);

	return result;
}

float Example::ngramSimilarity(string text) const
{	
	vector<string> exampleTokens = Create3Grams(Text);
	vector<string> textTokens = Create3Grams(text);
	unsigned int coincidencies = 0;

	for (string token : exampleTokens)
	{
		if (find(textTokens.begin(), textTokens.end(), token) != textTokens.end())
		{
			coincidencies++;
		}
	}

	float result = ((float) coincidencies) / 
		((float) exampleTokens.size() + (float) textTokens.size() - (float) coincidencies);

	return result;
}


vector<string> Example::Create3Grams(string str)
{
	vector<string> tokens = Util::extractTokens(str);
	vector<string> str3grams;

	for (string token : tokens)
	{
		if (token.length() < 3)
		{
			continue;
		}
		else if (token.length() == 3)
		{
			if (find(tokens.begin(), tokens.end(), token) != tokens.end())
			{
				str3grams.push_back(token);
			}
		}
		else
		{
			for (int i = 0; i < token.length() - 2; i++)
			{
				if (find(tokens.begin(), tokens.end(), token.substr(i, 3)) != tokens.end())
				{
					str3grams.push_back(token.substr(i, 3));
				}
			}
		}
	}

	return str3grams;
}

ostream& operator<<(ostream& out, const Example& example)
{
	out << "Example " << example.getId() << ": " << example.getText() << endl;
	out << "Tokens " << example.getId() << ": ";

	vector<string> tokens = example.getTokens();
	for (string token : tokens)
	{
		out << "<" << token << ">";
	}

	return out;
}