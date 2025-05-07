#include <iostream>
#include <string>

#include "Token.h"
#include "TokenCodes.h"

using namespace std;

Token::Token()
{
  setTokenCode(NAL);
  setLexemeString("");
}

Token::Token(TokenCodes tc, string ls)
{
  setTokenCode(tc);
  setLexemeString(ls);
}

string Token::getLexemeString()
{
  return lexemeString;
}

void Token::setLexemeString(string ls)
{
  lexemeString = ls;
}

TokenCodes Token::getTokenCode()
{
  return tokenCode;
}

void Token::setTokenCode(TokenCodes tc)
{
  tokenCode = tc;
}

ostream& operator<<(ostream& os, const Token& t)
{
  string tcs[] =
  {
    "ENDSYM", "LPAREN", "COLON", "DECLARESYM", "ELSESYM", "ANDSYM",
    "CHARACTERSYM", "RPAREN", "TIMES", "GETSYM", "PLUS", "LEQ", "MAINSYM",
    "BITSYM", "COMMA", "LSS", "EXPONENT", "FLOATSYM", "IFSYM", "ORSYM", "GEQ",
    "CALLSYM", "DIVIDE", "EQL", "MINUS", "RETURNSSYM", "WHILESYM", "PUTSYM",
    "NEQ", "SEMICOLON", "PROCEDURESYM", "NOTSYM", "DOSYM", "GTR", "TOSYM",
    "FIXEDSYM", "THENSYM", "BYSYM", "DATASYM", "IDENT", "INTEGERLIT", "REALLIT",
    "EOI", "NAL"
  };

  os << "Next token is: " << tcs[t.tokenCode];
  os << ", lexeme string is \"" << t.lexemeString << "\"";

  return os;
}
