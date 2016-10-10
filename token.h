#ifndef TOKEN_H
#define TOKEN_H
#include <QString>

class Token
{
private:
    QString token;
    int value;
    int row;
    int column;
public:
    Token();
    Token(QString token, int value): token(token), value(value) {}
    QString getToken() const;
    void setToken(const QString &value);
    int getValue() const;
    void setValue(int value);
    int getRow() const;
    void setRow(int value);
    int getColumn() const;
    void setColumn(int value);
};

#endif // TOKEN_H
