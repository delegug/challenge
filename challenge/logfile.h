#ifndef LOGFILE_H
#define LOGFILE_H

#include <QtCore>

/// @class logfile
/// @brief class to write a logfile
/// logfile writes two files, a .log file and a .bak file
class logfile
{
public:
    logfile(const QByteArray& logFileName);
    bool writeLogFile(const QString &data, const QByteArray &className=QByteArray());
private:
    QString m_logFilePath;
    QString m_bakFilePath;

};

#endif // LOGFILE_H
