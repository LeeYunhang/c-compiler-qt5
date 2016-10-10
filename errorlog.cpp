#include "errorlog.h"

ErrorLog::ErrorLog()
{

}

QString ErrorLog::generateLexicalError(int row, int column, const QString &reason)
{
    return QString("Error in: row %1, column %2 reason:%3.").arg (row).arg (column).arg(reason);
}
