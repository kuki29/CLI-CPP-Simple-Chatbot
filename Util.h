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
  "Hola, ¿en qué puedo ayudarte?",
  "¿Qué puedo hacer hoy por ti?",
  "Oh, gran prócer de los bits, ¿cuál es tu deseo?",
  "Buenas",
  "¿Qué quieres?",
  "¿Otra vez necesitas ayuda?",
  "¡Hola! Soy Megabot 3000. ¿En qué puedo ayudarte?",
  "Bonito día para ser Megabot 3000",
  "Pregunta sin miedo",
  "Soy todo oídos"
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
