#include "symbol.h"

QString Symbol::getName() const
{
    return name;
}

void Symbol::setName(const QString &value)
{
    name = value;
}

Symbol::Symbol()
{

}
