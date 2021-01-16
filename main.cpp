#include <iostream>
#include <vector>
#include <cstdlib>

#include "Chatbot.h"
#include "Intent.h"
#include "Util.h"

using namespace std;

void showTrainMenu()
{
	cout << "1- Add intent" << endl
		<< "2- Delete intent" << endl
		<< "3- Add example" << endl
		<< "4- Delete example" << endl
		<< "5- Add response" << endl
		<< "b- Back to main menu" << endl
		<< "Option: ";
}

void train(Chatbot &megabot, vector<Intent*> &intents)
{
	char option;

	do
	{
		showTrainMenu();
		cin >> option;
		cin.get();

		switch (option)
		{
		case '1':
			try
			{
				string name;
				cout << "Intent name: ";
				getline(cin, name);
				Intent *newIntent = new Intent(name);
				intents.push_back(newIntent);
				megabot.addIntent(newIntent);
			} catch (Error e)
			{
				Util::error(e);
			}
			break;
		case '2':
			megabot.deleteIntent();
			break;
		case '3':
			megabot.addExample();
			break;
		case '4':
			megabot.deleteExample();
			break;
		case '5':
			megabot.addResponse();
			break;
		case 'b':
			break;
		default:
			Util::error(ERR_OPTION);
			break;
		}
	} while (option != 'b');
}

void showMainMenu()
{
	cout << "1- Train" << endl
		<< "2- Test" << endl
		<< "3- Report" << endl
		<< "4- Configure" << endl
		<< "q- Quit" << endl
		<< "Option: ";
}

int main(int argc, char *argv[])
{
	vector<Intent*> intents;
	Chatbot megabot;

	srand(666);
	char option;

	do
	{
		showMainMenu();
		cin >> option;
		cin.get();

		switch (option)
		{
		case '1':
			train(megabot, intents);
			break;
		case '2':
			megabot.Test();
			break;
		case '3':
			cout << megabot << endl;
			break;
		case '4':
			megabot.Configure();
			break;
		case 'q':
			break;
		default:
			Util::error(ERR_OPTION);
		}
	} while (option != 'q');

	return 0;
}
