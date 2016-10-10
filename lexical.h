
#ifndef LEXICAL_H
#define LEXICAL_H
#include<QString>
#include<QChar>
#include<QStringList>
#include <QTextStream>
#include<QVector>

#include"errorlog.h"
#include "symbol.h"
#include "token.h"

extern QString keyword[26];
extern int keyword_num[26];

extern QChar symbol[9];
extern int symbol_num[9];


class Lexical
{
public:
    Lexical();
    static void lexicalAnalyze(QString code);
    static QVector<Token> getTokens();
    static QVector<Symbol> getSymbols();

private:
    static QVector<Token> tokens;        // token table
    static QVector<Symbol> symbols;  //  symbol table

    static bool isdigit (QChar);
    static bool isletter(QChar);
    static int iskeyword(const QString&);
    static int issymbol(QChar);
    static bool islegal(QChar);
    static Token wordAnalyze(QString::iterator& ite_start, QString::iterator& ite_end);
    static Token digitAnalyze(QString::iterator& ite_start, QString::iterator& ite_end);
    static Token symbolAnalyze(QString::iterator& ite_start, QString::iterator& ite_end);
};

#endif // LEXICAL_H
