
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

#define SYMBOL_LENGTH 22
#define INTEGER_NUM 44
#define FLOAT_NUM 45
#define NO_TOKEN -1
#define MULTI_LINE_COMMENT_START -2
#define MULTI_LINE_COMMENT_END -3


extern QString keyword[26];
extern int keyword_num[26];

extern QChar symbol[SYMBOL_LENGTH];
extern int symbol_num[SYMBOL_LENGTH];

extern QString symbol_string[6];
extern int symbo_string_num[6];

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
    static int row, column;

    static bool isdigit (QChar);
    static bool isletter(QChar);
    static int iskeyword(const QString&);
    static int issymbol(QChar);
    static int issymbolstring(QString&);
    static bool islegal(QChar);
    static Token wordAnalyze(QString::iterator& ite_start, QString::iterator& ite_end);
    static Token digitAnalyze(QString::iterator& ite_start, QString::iterator& ite_end);
    static Token symbolAnalyze(QString::iterator& ite_start, QString::iterator& ite_end, int state = 0);
};

#endif // LEXICAL_H
