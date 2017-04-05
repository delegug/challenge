/// @file logfile.cpp
/// @brief writing a logfile
/// @author M. Gugenhan

#include "logfile.h"

logfile::logfile(const QByteArray &logFileName)
{
    m_logFilePath=QDir::currentPath() + QDir::separator() + logFileName + ".log";
    m_bakFilePath=QDir::currentPath() + QDir::separator() + logFileName + ".bak";
}

/// Writes data in the Logfile
/// if logfile > 8MB a .bak file is created
/// @param data Text to write in the file
/// @param className Class name of the writing class
/// @return returns true on success
bool logfile::writeLogFile(const QString& data,const QByteArray& className)
{
    QDateTime date=QDateTime::currentDateTime();
    QFile file(m_logFilePath);
    QStringList tmpList=QStringList();
    QString space=QString(),tmpText=QString();
    int indent=-1;
    //create bak if .log > 8MB
    if (file.size()>8000000) {
        // remove old .bak and copy the .log to .bak
        if (QFile::exists(m_bakFilePath)) {
            QFile::remove(m_bakFilePath);
        }
        if (QFile::copy(m_logFilePath,m_bakFilePath)) {
            // Remove old logfile
            if (!QFile::remove(m_logFilePath)) {
                return false;
            }
        } else {
            return false;
        }
    }
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        return false;
    }
    //Create text
    tmpText=date.toString("dd.MM.yyyy hh:mm:ss")+" ";
    //add classname
    if (!className.isEmpty()) {
        tmpText.append("["+className+"]   ");
    }
    indent=tmpText.size();
    tmpText.append(data);
    tmpList=tmpText.split("\r\n");
    tmpText.clear();
    tmpText=tmpList.at(0)+"\r\n";
    space.fill(QChar(32),indent-2);
    space.append("\t");
    for (int i=1;i<tmpList.size();i++)
    {
        tmpText.append(space + tmpList.at(i)+"\r\n");
    }
    file.write(tmpText.toLatin1());
    file.close();
    return true;
}
