#include "token.h"

QString Token::getToken() const
{
    return token;
}

void Token::setToken(const QString &value)
{
    token = value;
}

int Token::getValue() const
{
    return value;
}

void Token::setValue(int value)
{
    value = value;
}

int Token::getRow() const
{
    return row;
}

void Token::setRow(int value)
{
    row = value;
}

int Token::getColumn() const
{
    return column;
}

void Token::setColumn(int value)
{
    column = value;
}

Token::Token()
{
    
}
