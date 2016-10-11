#include "errorlog.h"

QVector<QString> ErrorLog::lexicalErrors;

QVector<QString> ErrorLog::getLexicalErrors()
{
	return lexicalErrors;
}

void ErrorLog::clear()
{
	lexicalErrors.resize (0);
}

ErrorLog::ErrorLog()
{

}

void ErrorLog::generateLexicalError(int row, int column, const QString &reason)
{
	lexicalErrors.push_back (QString("Error in: row %1, column %2. reason:%3.").arg (row).arg (column).arg(reason));
}
