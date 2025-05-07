#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"
#include <iostream>
#include <cstdlib>

using namespace std;

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer *l)
{
    la = l;
}

void SyntaxAnalyzer::getNextToken()
{
    nextToken = la->getNextToken();
    nextTokenCode = nextToken->getTokenCode();
}

void SyntaxAnalyzer::error(int code)
{
    int pos = la->getCurrentTokenPosition();

    for (int i = 0; i < pos; i++)
        cout << " ";
    cout << "^" << endl;

    switch (code)
    {
        case 1: cout << "Error: identifier expected." << endl; break;
        case 2: cout << "Error: ':' expected." << endl; break;
        case 3: cout << "Error: 'procedure' expected." << endl; break;
        case 4: cout << "Error: '(' expected." << endl; break;
        case 5: cout << "Error: 'main' expected." << endl; break;
        case 6: cout << "Error: ')' expected." << endl; break;
        case 7: cout << "Error: ';' expected." << endl; break;
        case 8: cout << "Error: 'end' expected." << endl; break;
        case 9: cout << "Error: '=' expected." << endl; break;
        case 10: cout << "Error: 'to' expected." << endl; break;
        case 11: cout << "Error: expression expected." << endl; break;
        case 12: cout << "Error: '(' or identifier expected." << endl; break;
        case 13: cout << "Error: type expected (bit, character, fixed, float)." << endl; break;
        case 14: cout << "Error: 'returns' expected." << endl; break;
        case 15: cout << "Syntax error." << endl; break;
    }

    exit(0);
}

void SyntaxAnalyzer::Program()
{
    getNextToken();
    ProgramUnits();
    if (nextTokenCode != EOI)
        error(15);
}

void SyntaxAnalyzer::ProgramUnits()
{
    MainUnit();
    Subprograms();
}

void SyntaxAnalyzer::MainUnit()
{
    if (nextTokenCode == IDENT)
    {
        getNextToken();
        if (nextTokenCode == COLON)
        {
            getNextToken();
            if (nextTokenCode == PROCEDURESYM)
            {
                getNextToken();
                if (nextTokenCode == LPAREN)
                {
                    getNextToken();
                    if (nextTokenCode == MAINSYM)
                    {
                        getNextToken();
                        if (nextTokenCode == RPAREN)
                        {
                            getNextToken();
                            if (nextTokenCode == SEMICOLON)
                            {
                                getNextToken();
                                Block();
                            }
                            else error(7);
                        }
                        else error(6);
                    }
                    else error(5);
                }
                else error(4);
            }
            else error(3);
        }
        else error(2);
    }
    else error(1);
}

void SyntaxAnalyzer::Subprograms()
{
    if (nextTokenCode == IDENT)
    {
        Subprogram();
        Subprograms();
    }

}

void SyntaxAnalyzer::Subprogram()
{
    Header();
    Block();
}

void SyntaxAnalyzer::Header()
{
    if (nextTokenCode == IDENT)
    {
        getNextToken();
        if (nextTokenCode == COLON)
        {
            getNextToken();
            if (nextTokenCode == PROCEDURESYM)
            {
                getNextToken();
                ParamList();
                if (nextTokenCode == RETURNSSYM)
                {
                    getNextToken();
                    if (nextTokenCode == LPAREN)
                    {
                        getNextToken();
                        if (nextTokenCode == BITSYM || nextTokenCode == CHARACTERSYM || nextTokenCode == FIXEDSYM || nextTokenCode == FLOATSYM)
                        {
                            getNextToken();
                            if (nextTokenCode == RPAREN)
                            {
                                getNextToken();
                            }
                            else error(6);
                        }
                        else error(13);
                    }
                    else error(4);
                }
                if (nextTokenCode == SEMICOLON)
                    getNextToken();
                else error(7);
            }
            else error(3);
        }
        else error(2);
    }
    else error(1);
}

void SyntaxAnalyzer::ParamList()
{
    if (nextTokenCode == LPAREN)
    {
        getNextToken();
        IdentList();
        if (nextTokenCode == RPAREN)
            getNextToken();
        else error(6);
    }

}

void SyntaxAnalyzer::IdentList()
{
    if (nextTokenCode == IDENT)
    {
        getNextToken();
        while (nextTokenCode == COMMA)
        {
            getNextToken();
            if (nextTokenCode == IDENT)
                getNextToken();
            else error(1);
        }
    }
    else error(1);
}

void SyntaxAnalyzer::Block()
{
    Types();
    SeqOfStmt();
    if (nextTokenCode == ENDSYM)
    {
        getNextToken();
        if (nextTokenCode == IDENT)
        {
            getNextToken();
            if (nextTokenCode == SEMICOLON)
                getNextToken();
            else error(7);  
        }
        else error(1);  
    }
    else error(8);  
}

void SyntaxAnalyzer::Types()
{
    if (nextTokenCode == DECLARESYM)
    {
        Type();
        Types();
    }

}

void SyntaxAnalyzer::Type()
{
    if (nextTokenCode == DECLARESYM)
    {
        getNextToken();
        Identifiers();
        if (nextTokenCode == BITSYM || nextTokenCode == CHARACTERSYM || nextTokenCode == FIXEDSYM || nextTokenCode == FLOATSYM)
        {
            getNextToken();
            if (nextTokenCode == SEMICOLON)
                getNextToken();
            else error(7);  
        }
        else error(13);  
    }
    else error(15);  
}

void SyntaxAnalyzer::Identifiers()
{
    if (nextTokenCode == IDENT)
    {
        getNextToken();
    }
    else if (nextTokenCode == LPAREN)
    {
        getNextToken();
        IdentList();
        if (nextTokenCode == RPAREN)
            getNextToken();
        else error(6);  
    }
    else error(12);  
}

void SyntaxAnalyzer::SeqOfStmt()
{
    Statement();
    while (nextTokenCode == IDENT || nextTokenCode == CALLSYM || nextTokenCode == DOSYM || nextTokenCode == IFSYM || nextTokenCode == GETSYM || nextTokenCode == PUTSYM)
    {
        Statement();
    }
}

void SyntaxAnalyzer::Statement()
{
    if (nextTokenCode == IDENT)
    {
        getNextToken();
        if (nextTokenCode == EQL)
        {
            getNextToken();
            Or();
            if (nextTokenCode == SEMICOLON)
                getNextToken();
            else error(7);  
        }
        else error(9);  
    }
    else if (nextTokenCode == CALLSYM)
    {
        getNextToken();
        if (nextTokenCode == IDENT)
        {
            getNextToken();
            if (nextTokenCode == LPAREN)
            {
                getNextToken();
                Arguments();
                if (nextTokenCode == RPAREN)
                {
                    getNextToken();
                    if (nextTokenCode == SEMICOLON)
                        getNextToken();
                    else error(7);  
                }
                else error(6);  
            }
            else error(4);  
        }
        else error(1);  
    }
    else if (nextTokenCode == DOSYM)
    {
        getNextToken();
        if (nextTokenCode == IDENT)
        {
            getNextToken();
            if (nextTokenCode == EQL)
            {
                getNextToken();
                Or();
                if (nextTokenCode == TOSYM)
                {
                    getNextToken();
                    Or();
                    if (nextTokenCode == SEMICOLON)
                    {
                        getNextToken();
                        SeqOfStmt();
                        if (nextTokenCode == ENDSYM)
                        {
                            getNextToken();
                            if (nextTokenCode == SEMICOLON)
                                getNextToken();
                            else error(7);
                        }
                        else error(8);
                    }
                    else if (nextTokenCode == BYSYM)
                    {
                        getNextToken();
                        Or();
                        if (nextTokenCode == SEMICOLON)
                        {
                            getNextToken();
                            SeqOfStmt();
                            if (nextTokenCode == ENDSYM)
                            {
                                getNextToken();
                                if (nextTokenCode == SEMICOLON)
                                    getNextToken();
                                else error(7);
                            }
                            else error(8);
                        }
                        else error(7);
                    }
                    else error(7);  
                }
                else error(10);  
            }
            else error(9);  
        }
        else if (nextTokenCode == WHILESYM)
        {
            getNextToken();
            if (nextTokenCode == LPAREN)
            {
                getNextToken();
                Or();
                if (nextTokenCode == RPAREN)
                {
                    getNextToken();
                    if (nextTokenCode == SEMICOLON)
                    {
                        getNextToken();
                        SeqOfStmt();
                        if (nextTokenCode == ENDSYM)
                        {
                            getNextToken();
                            if (nextTokenCode == SEMICOLON)
                                getNextToken();
                            else error(7);
                        }
                        else error(8);
                    }
                    else error(7);
                }
                else error(6);
            }
            else error(4);
        }
        else error(1);  
    }
    else if (nextTokenCode == IFSYM)
    {
        getNextToken();
        Or();
        if (nextTokenCode == THENSYM)
        {
            getNextToken();
            SeqOfStmt();
            if (nextTokenCode == ELSESYM)
            {
                getNextToken();
                SeqOfStmt();
            }
            if (nextTokenCode == ENDSYM)
            {
                getNextToken();
                if (nextTokenCode == SEMICOLON)
                    getNextToken();
                else error(7);
            }
            else error(8);
        }
        else error(15);
    }
    else if (nextTokenCode == GETSYM || nextTokenCode == PUTSYM)
    {
        getNextToken();
        if (nextTokenCode == DATASYM)
        {
            getNextToken();
            if (nextTokenCode == LPAREN)
            {
                getNextToken();
                IdentList();
                if (nextTokenCode == RPAREN)
                {
                    getNextToken();
                    if (nextTokenCode == SEMICOLON)
                        getNextToken();
                    else error(7);
                }
                else error(6);
            }
            else error(4);
        }
        else error(15);
    }
    else error(15);  
}

void SyntaxAnalyzer::Arguments()
{
    if (nextTokenCode == RPAREN)
        return;
    ArgList();
}

void SyntaxAnalyzer::ArgList()
{
    Or();
    while (nextTokenCode == COMMA)
    {
        getNextToken();
        Or();
    }
}

void SyntaxAnalyzer::Or()
{
    And();
    while (nextTokenCode == ORSYM)
    {
        getNextToken();
        And();
    }
}

void SyntaxAnalyzer::And()
{
    Equality();
    while (nextTokenCode == ANDSYM)
    {
        getNextToken();
        Equality();
    }
}

void SyntaxAnalyzer::Equality()
{
    Relational();
    while (nextTokenCode == EQL || nextTokenCode == NEQ)
    {
        getNextToken();
        Relational();
    }
}

void SyntaxAnalyzer::Relational()
{
    AddSub();
    while (nextTokenCode == LSS || nextTokenCode == LEQ || nextTokenCode == GTR || nextTokenCode == GEQ)
    {
        getNextToken();
        AddSub();
    }
}

void SyntaxAnalyzer::AddSub()
{
    MultDiv();
    while (nextTokenCode == PLUS || nextTokenCode == MINUS)
    {
        getNextToken();
        MultDiv();
    }
}

void SyntaxAnalyzer::MultDiv()
{
    Pow();
    while (nextTokenCode == TIMES || nextTokenCode == DIVIDE)
    {
        getNextToken();
        Pow();
    }
}

void SyntaxAnalyzer::Pow()
{
    Not();
    if (nextTokenCode == EXPONENT)
    {
        getNextToken();
        Pow();
    }
}

void SyntaxAnalyzer::Not()
{
    if (nextTokenCode == NOTSYM)
    {
        getNextToken();
        Not();
    }
    else
    {
        Primary();
    }
}

void SyntaxAnalyzer::Primary()
{
    if (nextTokenCode == LPAREN)
    {
        getNextToken();
        Or();
        if (nextTokenCode == RPAREN)
            getNextToken();
        else error(6);
    }
    else if (nextTokenCode == IDENT)
    {
        getNextToken();
        if (nextTokenCode == LPAREN)
        {
            getNextToken();
            Arguments();
            if (nextTokenCode == RPAREN)
                getNextToken();
            else error(6);
        }
    }
    else if (nextTokenCode == INTEGERLIT || nextTokenCode == REALLIT)
    {
        getNextToken();
    }
    else error(11);  
}