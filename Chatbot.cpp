#include "Chatbot.h"

Chatbot::Chatbot()
{
	Threshold = .25f;
	strcpy(Similarity, "jc");
}

Chatbot::Chatbot(float threshold, const char similarity[])
{
	if (threshold < 0 || threshold > 1)
	{
		throw ERR_THRESHOLD;
		return;
	}
	else
	{
		Threshold = threshold;
	}

	if (strcmp("jc", similarity) && strcmp("ng", similarity))
	{
		throw ERR_SIMILARITY;
		return;
	}
	else
	{
		strcpy(Similarity, similarity);
	}
}

float Chatbot::getThreshold() const
{
	return Threshold;
}

string Chatbot::getSimilarity() const
{
	return string(Similarity);
}

bool Chatbot::addIntent(Intent* intent)
{
	if (SearchIntent(intent->getName()) != -1)
	{
		throw ERR_INTENT;
		return false;
	}
	else
	{
		Intents.push_back(intent);
		return true;
	}
}

bool Chatbot::deleteIntent(string name, bool askConfirm)
{
	if (name == "")
	{
		char name[1024];
		cout << "Input intent name: ";
		cin.getline(name, 1023);
	}

	if (askConfirm)
	{
		char confirm;
		cout << "Are you sure? [Y/N]: ";
		do
		{
			cin >> confirm;
		} while (confirm != 'n' && confirm != 'N' && confirm != 'y' && confirm != 'Y');

		if (confirm == 'n' || confirm == 'N')
		{
			return false;
		}
	}

	int index = SearchIntent(name);
	if (index != -1)
	{
		Intents.erase(Intents.begin() + index);
		return true;
	}
	else
	{
		throw ERR_INTENT;
		return false;
	}
}

bool Chatbot::addExample(string intentName)
{
	if (intentName == "")
	{
		char name[1024];
		cout << "Input intent name: ";
		cin.getline(name, 1023);
	}

	int index = SearchIntent(intentName);
	if (index == -1)
	{
		throw ERR_INTENT;
		return false;
	}

	char str[1024];
	bool returnVal = false;
	while (true)
	{
		memset(str, 0, sizeof(str));	//clear str buffer

		cout << "Input example: ";

		cin.getline(str, 1023);

		if (str[0] == 'q')
			break;

		try
		{
			Intents[index]->addExample(Example(string(str)));
			returnVal = true;
		}
		catch (Error err)
		{
			Util::error(err);
		}
	}

	return returnVal;
}

bool Chatbot::deleteExample(unsigned int id)
{
	bool deleted = false;
	if (id == 0)
	{
		int id;
		cout << "Input example id: ";
		cin >> id;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	for (Intent* intent : Intents)
	{
		if (intent->deleteExample(id))
		{
			deleted = true;
		}
	}

	return deleted;
}

bool Chatbot::addResponse(string name, string response)
{
	if (name == "")
	{
		char str[1024];
		cout << "Input intent name: ";
		cin.getline(str, 1023);
	}

	if (SearchIntent(name) == -1)
	{
		throw ERR_INTENT;
		return false;
	}

	if (response == "")
	{
		char str[1024];
		cout << "Input new response: ";
		cin.getline(str, 1023);
	}

	try
	{
		Intents[SearchIntent(name)]->addResponse(response);
		return true;
	}
	catch (Error err)
	{
		Util::error(err);
		return false;
	}
}

void Chatbot::Test(bool debug) const
{
	cout << "\t>> " << Util::welcome() << endl;

	char userInput[1024];

	while (true)
	{
		cout << "\t<< ";

		cin.getline(userInput, 1023);

		if (string(userInput) == ".exit")
		{
			break;
		}

		try
		{
			string response = BestResponse(userInput, debug);
			cout << "\t>> " << response << endl;
		}
		catch (Error err)
		{
			Util::error(err);
		}
	}
}

void Chatbot::Configure(float threshold, const char similarity[])
{
	float thre = threshold;

	if (thre < 0 || thre > 1)
	{
		cout << "Enter treshold: ";
		cin >> thre;
	}

	if (thre < 0 || thre >= 1)
	{
		throw ERR_THRESHOLD;
		return;
	}

	Threshold = thre;

	char algorithm[3];
	strcpy(algorithm, similarity);

	if (strcmp(algorithm, "ng") && strcmp(algorithm, "jc"))
	{
		cout << "Choose similarity agorithm[jc/ng]: ";

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.getline(algorithm, 3);
	}

	if (strcmp(algorithm, "jc") && strcmp(algorithm, "ng"))
	{
		throw ERR_SIMILARITY;
		return;
	}

	strcpy(Similarity, algorithm);
}

int Chatbot::SearchIntent(string name) const
{
	auto it = find_if(Intents.begin(), Intents.end(), 
						[&](const Intent* intent)
						{
							if (intent->getName() == name)
							{
								return true;
							}
							return false;
						});

	if (it == Intents.end())
	{
		return -1;
	}
	else
	{
		return distance(Intents.begin(), it);
	}
}

string Chatbot::BestResponse(string query, bool debug) const
{
	string response;
	float maxSimilarity = 0;

	for (Intent* intent : Intents)
	{
		float curretSimilarity = intent->calculateSimilarity(query, Similarity);
		if (curretSimilarity > maxSimilarity)
		{
			maxSimilarity = curretSimilarity;
			response = intent->getResponse();
		}
	}

	if (maxSimilarity <= Threshold)
	{
		throw ERR_RESPONSE;
		return "";
	}

	if (debug)
	{
		response = "(" + to_string(maxSimilarity) + ") " + response;
	}

	return response;
}

ostream& operator<<(ostream& out, const Chatbot& chatbot)
{
	cout << "Similarity: ";
	if (!strcmp(chatbot.Similarity, "jc"))
	{
		cout << "Jaccard";
	}
	else if (!strcmp(chatbot.Similarity, "ng"))
	{
		cout << "N-grams";
	}
	cout << endl;
	
	cout << "Treshold: " << chatbot.Threshold << endl;

	unsigned int examplesQuantity = 0;

	for (Intent* intent : chatbot.Intents)
	{
		cout << *intent << endl;
		examplesQuantity += intent->getExamplesQuantity();
	}

	cout << "Total intents: " << chatbot.Intents.size() << endl;
	cout << "Total examples: " << examplesQuantity << endl;;
	cout << "Examples per intent: " << (float) examplesQuantity / (float) chatbot.Intents.size();

	return out;
}