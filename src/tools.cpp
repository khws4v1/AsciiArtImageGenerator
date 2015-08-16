#include "tools.h"
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QString>
#include <functional>
#include <QMap>

namespace AsciiArtImageGenerator {

QString saveFileName(QString name)
{
    using std::function;

    static const QMap<QString, function<QString()>> replaceMap {
        { "%{YEAR}", [&]() {return QDateTime::currentDateTime().toString("yyyy");}},
        { "%{MONTH}", [&]() {return QDateTime::currentDateTime().toString("MM");}},
        { "%{DAY}", [&]() {return QDateTime::currentDateTime().toString("dd");}},
        { "%{HOUR}", [&]() {return QDateTime::currentDateTime().toString("hh");}},
        { "%{MINUTE}", [&]() {return QDateTime::currentDateTime().toString("mm");}},
        { "%{SECOND}", [&]() {return QDateTime::currentDateTime().toString("ss");}},
        { "%{UNIX}", [&]() {return QString::number(QDateTime::currentMSecsSinceEpoch() / 1000);}}
    };

    for (auto &&key : replaceMap.keys())
        name.replace(key, replaceMap[key]());

    return name;
}

}
