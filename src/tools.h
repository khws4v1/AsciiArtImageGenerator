#ifndef TOOLS_H
#define TOOLS_H

#include <QString>
#include <QColor>

namespace AsciiArtImageGenerator {

QString saveFileName(QString name);

inline QString rgbaToString(const QColor& color)
{
    return QString("%1,%2,%3,%4").arg(QString::number(color.red()),
                                      QString::number(color.green()),
                                      QString::number(color.blue()),
                                      QString::number(color.alpha()));
}

inline QString generateCss(const QString& fontFamily,
                           const QColor& fontColor,
                           const QColor& backgroundColor,
                           double fontSize,
                           double lineHeight)
{
    return QString(R"(font-family: %1;
            color: %2;
            background-color: rgba(%3);
            font-size: %4px;
            line-height: %5px;)")
        .arg(fontFamily,
             fontColor.name(),
             rgbaToString(backgroundColor),
             QString::number(fontSize),
             QString::number(lineHeight));
}

}

#endif // TOOLS_H
