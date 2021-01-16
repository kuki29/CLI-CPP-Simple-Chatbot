#ifndef CHATBOT_H
#define CHATBOT_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Intent.h"

using namespace std;

class Chatbot
{
private:
	float Threshold;
	char Similarity[3];
	vector<Intent*> Intents;

public:
	Chatbot();
	Chatbot(float threshold, const char similarity[]);

	float getThreshold() const;
	string getSimilarity() const;

	bool addIntent(Intent* intent);
	bool deleteIntent(string name = "", bool askConfirm = true);
	bool addExample(string intentName = "");
	bool deleteExample(unsigned int id = 0);
	bool addResponse(string name = "", string response = "");

	void Test(bool debug = false) const;
	void Configure(float threshold = -1, const char similarity[] = "");

private:
	int SearchIntent(string name) const;
	string BestResponse(string query, bool debug) const;

public:
	friend ostream& operator<<(ostream& out, const Chatbot& chatbot);
};

#endif