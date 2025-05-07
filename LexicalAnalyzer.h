#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>

#include "Token.h"
#include "TokenCodes.h"

using namespace std;

class LexicalAnalyzer
{
  private:
    char currentChar;
    int currentCharIndex;
    ifstream *sourceCodeFile;
    string line;
    int currentTokenPosition;


    bool isEOI();
    void readNextLine();
    void getNextChar();

    void skipWhitespace();
    Token* recognizeIdentifierOrKeyword();
    Token* recognizeNumber();
    Token* recognizeSymbol();
    Token* createToken(TokenCodes, const string&);
    


  public:
    LexicalAnalyzer(ifstream*);
    Token* getNextToken();
    int getCurrentTokenPosition();
};

#endif
