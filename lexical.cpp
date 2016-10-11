#include "lexical.h"


QVector<Symbol> Lexical::symbols;
QVector<Token> Lexical::tokens;
int Lexical::row = 0;
int Lexical::column = 1;

QString keyword[26]={
    "main","if","then","while",
    "do","static","defualt","do","int",
    "double","struct","break","else","long",
    "swtich","case","typedf","char","return",
    "const","float","short","continue","for",
    "void","sizeof"
};
int keyword_num[26]={1,2,3,4,5,6,39,40,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};

QChar symbol[SYMBOL_LENGTH]={'+','-','*','/','=',';','(',')','#', '<', '>', '!', '~', '|', '&', '[', ']', '{', '}', '\'', '"', '.'};
 int symbol_num[SYMBOL_LENGTH]={27,28,29,30,38,41,42,43,0, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 62, 63, 64};

 QString symbol_string[6] = {"<=", ">=", "++", "--", "&&", "||"};
 int symbol_string_num[6] = {56, 57, 58, 59, 60, 61};

Lexical::Lexical()
{

}
void Lexical::lexicalAnalyze (QString code)
{
    QTextStream textStream(&code);
    row = 0;
    symbols = QVector<Symbol>();
    tokens    = QVector<Token>();
    ErrorLog::clear ();           // clear error
    bool isMultiLineComment = false;
    while(!textStream.atEnd ()) {
        auto line = textStream.readLine ();
	column = 1;
	auto ite = line.begin(), ite_end = line.end ();
	++row;

	while(ite < ite_end) {

            auto ch = *ite;
	    if (islegal (ch) || isMultiLineComment) {
		Token token;

		if (isdigit (ch) && !isMultiLineComment) {
		    token = digitAnalyze (ite, ite_end);
		    if (token.getValue () == -1) {
			    column += token.getToken ().length (); continue;
		    }
		    symbols.push_back (Symbol(token.getToken ()));

		} else if ((isletter (ch) || ch == '_') && !isMultiLineComment) {
		    token = wordAnalyze (ite, ite_end);
                    if (!iskeyword (token.getToken ())) {
			symbols.push_back (Symbol(token.getToken()));
                    }
		} else if (ch == '\t' || ch == '\n' || ch == 'r' || ch == ' ') {
			ite++; column++; continue;
		} else {
		    if (isMultiLineComment) {
			    token = symbolAnalyze (ite, ite_end, 3);           // pass state
		    } else {
			    token = symbolAnalyze (ite, ite_end);
		    }

		    if (token.getValue () == NO_TOKEN) {
			    continue;
		    } else if (token.getValue () == MULTI_LINE_COMMENT_START) {
			    isMultiLineComment = true;
			    continue;
		    } else if (token.getValue () == MULTI_LINE_COMMENT_END) {
			    isMultiLineComment = false;
			    continue;
		    }
                }
		token.setColumn (column);
		token.setRow (row);
		tokens.push_back (token);

		column += token.getToken ().length ();

            } else {
		ErrorLog::generateLexicalError (row, column, INVALID_CHAR);
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
    for (int i = 0; i < SYMBOL_LENGTH; ++i) {
        if (ch == symbol[i]) {
            return i;
        }
    }
    return -1;
}

int Lexical::issymbolstring(QString& symbolString)
{
	for (int i = 0; i < 6; ++i) {
		if (symbolString == symbol_string[i]) {
			return symbol_string_num[i];
		}
	}
	return -1;
}

bool Lexical::islegal(QChar letter)
{
	return isletter(letter) || isdigit (letter) || issymbol (letter) != -1 || letter == '\n' || letter == '\t' || letter == '\b' || letter == '\r' || letter == ' ';
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
	QString id = *ite_start++;
	auto state = 0;
	while (ite_start < ite_end) {
		auto ch = *ite_start;
		switch(state) {
		case 0:
			if (isdigit (ch)) {
				id += *ite_start++;
			} else if (ch == '.') {
				state = 1;
				id += *ite_start++;
			} else if (!islegal (ch)){
				ErrorLog::generateLexicalError (row, column, INVALID_CHAR);
				return Token(id + *ite_start++, -1);
			} else if (isletter (*ite_start) || *ite_start == '_') {
				state = 2;
				ErrorLog::generateLexicalError (row, column, INVALID_IDENTIFIER);
				id += *ite_start++;
			} else {
				return Token(id, INTEGER_NUM);
			}
			break;
		case 1:
			if (isdigit (ch)) {
				id += *ite_start++;
			} else if (!islegal (ch)) {
				ErrorLog::generateLexicalError (row, column, INVALID_CHAR);
				return Token(id + *ite_start++, NO_TOKEN);
			} else if (isletter (*ite_start) || *ite_start == '_') {
				state = 2;
				ErrorLog::generateLexicalError (row, column, INVALID_IDENTIFIER);
				id += *ite_start++;
			} else if (*ite_start == '.') {
				state = 2;
				id += *ite_start++;
				ErrorLog::generateLexicalError (row, column, INVALID_FLOAT);
			} else {
				return Token(id, FLOAT_NUM);
			}
			break;
		case 2:
			if (isdigit (*ite_start) || isletter (*ite_start) || *ite_start == '_' || *ite_start == '.') {
				id += *ite_start++;
			} else {
				return Token(id, NO_TOKEN);
			}
			break;
		}
	}

	switch (state) {
	case 0:
		return Token(id, INTEGER_NUM);
	case 1:
		return Token(id, FLOAT_NUM);
	case 2:
	case 3:
		return Token(id, NO_TOKEN);
	}
}

Token Lexical::symbolAnalyze(QString::iterator &ite_start, QString::iterator &ite_end, int state)
{
	QString id;
	while (ite_start < ite_end) {
		switch(state) {
		case 0:
			if (*ite_start == '/') {
				id += *ite_start++;
				state = 1;
			} else if(*ite_start == '+' || *ite_start == '-' || *ite_start == '&' || *ite_start == '|') {
				state = 4;
				id += *ite_start++;
			} else if (*ite_start == '<' || *ite_start == '>') {
				state = 5;
				id += *ite_start++;
			} else if (islegal(*ite_start)) {
				id += *ite_start++;
				return Token(id, issymbol (id[0]));
			}
			break;
		case 1:
			if (*ite_start == '/') {
				state = 2;
			} else if (*ite_start == '*') {  // multi-line comment
				state = 3;
			} else if (islegal (*ite_start)){
				return Token(id, issymbol (id[0]));
			}
			ite_start++; break;
		case 2:
			ite_start++; break;
		case 3:
			if (*ite_start == '*' && *(ite_start + 1) == '/') {
				ite_start +=2;
				return Token(QString(), MULTI_LINE_COMMENT_END);
			} else {
				ite_start++; break;
			}
		case 4:
			if (*ite_start == id[0]) {
				id += id;
				return Token(id, issymbolstring (id));
			} else if (islegal (*ite_start)) {
				return Token(id, issymbol(id[0]));
			}
		case 5:
			if (*ite_start == '=') {
				id += *ite_start++;
				return Token(id, issymbolstring (id));
			} else if (islegal(*ite_start)) {
				return Token(id, issymbol (id[0]));
			}
		}
	}

	switch(state) {
	case 2:
		return Token(QString(), NO_TOKEN);  //  no token
	case 3:
		return Token(QString(), MULTI_LINE_COMMENT_START);
	case 4:
	case 5:
		return Token(id, issymbol (id[0]));
	}
}
