#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>

using namespace std;

enum Error{
  ERR_OPTION,
  ERR_INTENT,
  ERR_EXAMPLE,
  ERR_RESPONSE,
  ERR_FILE,
  ERR_THRESHOLD,
  ERR_SIMILARITY,
  ERR_EMPTY,
  ERR_MAXEXAMPLES
}; 

const vector<string> Greetings = {
  "Hola, �en qu� puedo ayudarte?",
  "�Qu� puedo hacer hoy por ti?",
  "Oh, gran pr�cer de los bits, �cu�l es tu deseo?",
  "Buenas",
  "�Qu� quieres?",
  "�Otra vez necesitas ayuda?",
  "�Hola! Soy Megabot 3000. �En qu� puedo ayudarte?",
  "Bonito d�a para ser Megabot 3000",
  "Pregunta sin miedo",
  "Soy todo o�dos"
};


class Util
{
  public:
	static string welcome();
	static void error(Error e);
	static string CleanString(string str);
	static string CleanString(char* str);
	static vector<string> extractTokens(string text);
};

#endif
