#include "Util.h"

using namespace std;

string Util::welcome()
{
	return Greetings[rand() % Greetings.size()];
}

void Util::error(Error e){
  switch(e){
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_INTENT:
      cout << "ERROR: wrong intent name" << endl;
      break;
    case ERR_EXAMPLE:
      cout << "ERROR: wrong example id" << endl;
      break;
    case ERR_RESPONSE:
      cout << "Lo siento, pero no tengo respuesta para eso" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_THRESHOLD:
      cout << "ERROR: the threshold value must be between 0 and 1" << endl;
      break;
    case ERR_SIMILARITY:
      cout << "ERROR: valid values are \"jc\" (Jaccard) and \"ng\" (n-grams)" << endl;
      break;
    case ERR_EMPTY:
      cout << "ERROR: empty strings are not permited" << endl;
      break;
    case ERR_MAXEXAMPLES:
      cout << "ERROR: cannot add more examples" << endl;
  }
}

string Util::CleanString(string str)
{
	for (int i = 0; i < str.length(); i++)
		str[i] = tolower(str[i]);
	return str;
}

string Util::CleanString(char* str)
{
	return CleanString(string(str));
}

vector<string> Util::extractTokens(string text)
{
	vector<string> tokens;
	int pos = 0;
	bool isWord = false;
	string str1;
	int last = text.length() - 1;

	for (int i = 0; i <= last; i++)
	{
		if (isalnum(static_cast<unsigned char>(text[i])) != 0)
		{
			if (!isWord)
			{
				pos = i;
				isWord = true;
			}

			if (i == last)
			{
				string word = CleanString(text.substr(pos, last - pos));

				if (find(tokens.begin(), tokens.end(), word) != tokens.end())
				{
					tokens.push_back(text.substr(pos, last - pos + 1));
				}
			}
		}
		else if (isWord)
		{
			isWord = false;
			string word = CleanString(text.substr(pos, last - pos));

			if (find(tokens.begin(), tokens.end(), word) != tokens.end())
			{
				tokens.push_back(text.substr(pos, last - pos + 1));
			}
		}
	}

	return tokens;
}