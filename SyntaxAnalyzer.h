#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

class SyntaxAnalyzer
{
  public:
    SyntaxAnalyzer(LexicalAnalyzer *);
    void Program();

  private:
    LexicalAnalyzer *la;
    Token *nextToken;
    TokenCodes nextTokenCode;

    void getNextToken();
    void error(int code);

    
    void ProgramUnits();
    void MainUnit();
    void Subprograms();
    void Subprogram();
    void Header();
    void ParamList();
    void IdentList();
    void Block();
    void Types();
    void Type();
    void Identifiers();
    void SeqOfStmt();
    void Statement();
    void Arguments();
    void ArgList();

    
    void Or();
    void And();
    void Equality();
    void Relational();
    void AddSub();
    void MultDiv();
    void Pow();
    void Not();
    void Primary();
};

#endif

