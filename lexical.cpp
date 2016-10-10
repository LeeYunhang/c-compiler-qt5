#include "lexical.h"
#define INTEGER_NUM 44
#define FLOAT_NUM 45

QVector<Symbol> Lexical::symbols;
QVector<Token> Lexical::tokens;

QString keyword[26]={
    "main","if","then","while",
    "do","static","defualt","do","int",
    "double","struct","break","else","long",
    "swtich","case","typedf","char","return",
    "const","float","short","continue","for",
    "void","sizeof"
};
int keyword_num[26]={1,2,3,4,5,6,39,40,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};

QChar symbol[9]={'+','-','*','/','=',';','(',')','#'};

 int symbol_num[9]={27,28,29,30,38,41,42,43,0};

Lexical::Lexical()
{

}
void Lexical::lexicalAnalyze (QString code)
{
    QTextStream textStream(&code);
    int row = 0;

    while(!textStream.atEnd ()) {
        auto line = textStream.readLine ();
	auto column = 1;
	auto ite = line.begin(), ite_end = line.end ();
	++row;

	while(ite < ite_end) {

            auto ch = *ite;
            if (islegal (ch)) {
		Token token;

                if (isdigit (ch)) {
		    token = digitAnalyze (ite, ite_end);
		    symbols.push_back (Symbol(token.getToken ()));
                } else if (isletter (ch) || ch == '_') {
		    token = wordAnalyze (ite, ite_end);
                    if (!iskeyword (token.getToken ())) {
			symbols.push_back (Symbol(token.getToken()));
                    }
		} else if (ch == '\t' || ch == '\n' || ch == 'r' || ch == ' ') {
			ite++; column++; continue;
		} else {
		    token = symbolAnalyze (ite, ite_end);
                }
		tokens.push_back (token);
		token.setColumn (column);
		token.setRow (row);
		column += token.getToken ().length ();

            } else {
                // TODO:
            }
        }
    }
}

QVector<Token> Lexical::getTokens()
{
    return tokens;
}

QVector<Symbol> Lexical::getSymbols()
{
    return symbols;
}

bool Lexical::isdigit(QChar ch)
{
    return ch <= '9' && ch >= '0';
}

bool Lexical::isletter(QChar ch)
{
    return (ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z');
}

int Lexical::iskeyword(const QString & string)
{
    int i = 0;
    for (; i < 26; ++i) {
        if (string == keyword[i]) {
            return keyword_num[i];
        }
    }
    return 25;    // id
}

int Lexical::issymbol(QChar ch)
{
    for (int i = 0; i < 9; ++i) {
        if (ch == symbol[i]) {
            return i;
        }
    }
    return -1;
}

bool Lexical::islegal(QChar letter)
{
    return !(!isletter(letter) && !isdigit (letter) && !issymbol(letter) && letter != '\n' && letter != '\t' && letter != '\b' && letter != '\r');
}

Token Lexical::wordAnalyze(QString::iterator& ite_start, QString::iterator& ite_end)
{
	QString id = *ite_start++;
	while (ite_start != ite_end) {
		if (isletter (*ite_start) || isdigit (*ite_start) || *ite_start == '_') {
			id += *ite_start++;
		} else {
			break;
		}
	}
	return Token(id, iskeyword (id));
}

Token Lexical::digitAnalyze(QString::iterator &ite_start, QString::iterator &ite_end)
{
}

Token Lexical::symbolAnalyze(QString::iterator &ite_start, QString::iterator &ite_end)
{

}
