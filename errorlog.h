#ifndef ERRORLOG_H
#define ERRORLOG_H
#include<QString>
#include<QVector>

#define INVALID_CHAR "invalid character!"
#define INVALID_IDENTIFIER "invalid identifier!"
#define INVALID_DIGITAL "invalid digital!"
#define INVALID_FLOAT "There can only be one decimal point!"

class ErrorLog
{
private:
	static QVector<QString> lexicalErrors;
public:
    ErrorLog();
    static void generateLexicalError(int row, int column, const QString& reason);
    static QVector<QString> getLexicalErrors();
    static void clear();
};

#endif // ERRORLOG_H
