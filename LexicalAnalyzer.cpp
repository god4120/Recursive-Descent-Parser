#include <iostream>
#include <fstream>

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

LexicalAnalyzer::LexicalAnalyzer(ifstream *scf)
{ 
  currentChar = '\n';
  currentCharIndex = 0;
  sourceCodeFile = scf;
  line = "\n";

}

bool LexicalAnalyzer::isEOI()
{
  return (sourceCodeFile->eof() && (currentCharIndex == (line.length() - 1)));
}

void LexicalAnalyzer::readNextLine()
{
  getline(*sourceCodeFile, line);
  line = line + "\n";
  cout<<line;
}
 
int LexicalAnalyzer::getCurrentTokenPosition() 
{ 
return currentTokenPosition; 
}

void LexicalAnalyzer::getNextChar()
{
  if (currentCharIndex == (line.length() - 1))
  {
    readNextLine();
    currentCharIndex = -1;
  }

  currentCharIndex++;
  currentChar = line.at(currentCharIndex);
}


void LexicalAnalyzer::skipWhitespace()
{
  while (isspace(currentChar) && !isEOI())
  {
    getNextChar();
  }
}



Token* LexicalAnalyzer::recognizeIdentifierOrKeyword()
{
  string lexeme;
  while (isalnum(currentChar) || currentChar == '_')
  {
    lexeme += tolower(currentChar);
    getNextChar();
  }
  
  if (lexeme == "end") return new Token(ENDSYM, lexeme);
  if (lexeme == "procedure") return new Token(PROCEDURESYM, lexeme);
  if (lexeme == "main") return new Token(MAINSYM, lexeme);
  if (lexeme == "declare") return new Token(DECLARESYM, lexeme);
  if (lexeme == "fixed") return new Token(FIXEDSYM, lexeme);
  if (lexeme == "if") return new Token(IFSYM, lexeme);
  if (lexeme == "else") return new Token(ELSESYM, lexeme);
  if (lexeme == "while") return new Token(WHILESYM, lexeme);
  if (lexeme == "call") return new Token(CALLSYM, lexeme);
  if (lexeme == "returns") return new Token(RETURNSSYM, lexeme);
  if (lexeme == "put") return new Token(PUTSYM, lexeme);
  if (lexeme == "get") return new Token(GETSYM, lexeme);
  if (lexeme == "bit") return new Token(BITSYM, lexeme);
  if (lexeme == "float") return new Token(FLOATSYM, lexeme);
  if (lexeme == "character") return new Token(CHARACTERSYM, lexeme);
  if (lexeme == "data") return new Token(DATASYM, lexeme);
  if (lexeme == "do") return new Token(DOSYM, lexeme);
  if (lexeme == "by") return new Token(BYSYM, lexeme);
  if (lexeme == "to") return new Token(TOSYM, lexeme);
  if (lexeme == "then") return new Token(THENSYM, lexeme);
  if (lexeme == "and") return new Token(ANDSYM, lexeme);
  if (lexeme == "or") return new Token(ORSYM, lexeme);
  if (lexeme == "not") return new Token(NOTSYM, lexeme);
  
  return new Token(IDENT, lexeme);
}

Token* LexicalAnalyzer::recognizeNumber()
{
  string lexeme;
  bool isReal = false;
  while (isdigit(currentChar) || (!isReal && currentChar == '.'))
  {
    if (currentChar == '.') isReal = true;
    lexeme += currentChar;
    getNextChar();
  }
  return new Token(isReal ? REALLIT : INTEGERLIT, lexeme);
}

Token* LexicalAnalyzer::recognizeSymbol()
{
  string lexeme(1, currentChar);
  getNextChar();
  
  
  if (currentChar == '=' && (lexeme == "<" || lexeme == ">" || lexeme == "~"))
  {
    lexeme += currentChar;
    getNextChar();
    return new Token(lexeme == "<=" ? LEQ : lexeme == ">=" ? GEQ : NEQ, lexeme);
  }
  if (currentChar == '*' && lexeme == "*")
  {
    lexeme += currentChar;
    getNextChar();
    return new Token(EXPONENT, lexeme);
  }
  
  if (lexeme == ":") return new Token(COLON, lexeme);
  if (lexeme == "(") return new Token(LPAREN, lexeme);
  if (lexeme == ")") return new Token(RPAREN, lexeme);
  if (lexeme == ";") return new Token(SEMICOLON, lexeme);
  if (lexeme == ",") return new Token(COMMA, lexeme);
  if (lexeme == "<") return new Token(LSS, lexeme);
  if (lexeme == ">") return new Token(GTR, lexeme);
  if (lexeme == "=") return new Token(EQL, lexeme);
  if (lexeme == "+") return new Token(PLUS, lexeme);
  if (lexeme == "-") return new Token(MINUS, lexeme);
  if (lexeme == "*") return new Token(TIMES, lexeme);
  if (lexeme == "/") return new Token(DIVIDE, lexeme);
  if (lexeme == "&") return new Token(ANDSYM, lexeme);
  if (lexeme == "|") return new Token(ORSYM, lexeme);
  if (lexeme == "~") return new Token(NOTSYM, lexeme);
  
  return new Token(NAL, lexeme);
}

Token* LexicalAnalyzer::getNextToken()
{
  skipWhitespace();
  if (isEOI()) return new Token(EOI, "");
  currentTokenPosition = currentCharIndex;
  if (isalpha(currentChar)) return recognizeIdentifierOrKeyword();
  if (isdigit(currentChar)) return recognizeNumber();
  return recognizeSymbol();
}

