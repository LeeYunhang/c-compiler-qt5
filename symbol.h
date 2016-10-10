#ifndef SYMBOL_H
#define SYMBOL_H
#include<QString>

class Symbol
{
private:
    QString name;
public:

    Symbol(QString name) : name(name) {}
    Symbol();
    int length() { return name.length (); }
    QString getName() const;
    void setName(const QString &value);
};

#endif // SYMBOL_H
