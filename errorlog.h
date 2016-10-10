#ifndef ERRORLOG_H
#define ERRORLOG_H
#include<QString>


class ErrorLog
{
public:
    ErrorLog();
    static QString generateLexicalError(int row, int column, const QString& reason);
};

#endif // ERRORLOG_H
