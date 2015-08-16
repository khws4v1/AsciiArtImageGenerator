#ifndef ASCIIARTIMAGEGENERATORSETTINGS_H
#define ASCIIARTIMAGEGENERATORSETTINGS_H

#include <QSettings>
#include <QFont>
#include <QColor>

class AsciiArtImageGeneratorSettings : public QSettings
{
public:
    AsciiArtImageGeneratorSettings();

    inline static QString defaultFontFamily()
    {
        return "monapo";
    }
    inline void setFontFamily(const QString& name)
    {
        setValue("FontFamily", name);
    }
    inline QString fontFamily() const
    {
        return value("FontFamily", defaultFontFamily()).toString();
    }

    inline static double defaultFontSize()
    {
        return 12.0;
    }
    inline void setFontSize(double pixel)
    {
        setValue("FontSize", pixel);
    }
    inline double fontSize() const
    {
        return value("FontSize", defaultFontSize()).toDouble();
    }

    inline static double defaultLineHeight()
    {
        return 2.0;
    }
    inline void setLineHeight(double height)
    {
        setValue("LineHeight", height);
    }
    inline double lineHeight() const
    {
        return value("LineHeight", defaultLineHeight()).toDouble();
    }

    inline static QColor defaultBackgroundColor()
    {
        return QColor(Qt::white);
    }
    inline void setBackgroundColor(const QColor& color)
    {
        setValue("BackgroundColor", color.isValid() ? color : defaultBackgroundColor());
    }
    inline QColor backgroundColor() const
    {
        return value("BackgroundColor", defaultBackgroundColor()).value<QColor>();
    }

    inline static QColor defaultFontColor()
    {
        return QColor(Qt::black);
    }
    inline void setFontColor(const QColor& color)
    {
        setValue("FontColor", color.isValid() ? color : defaultFontColor());
    }
    inline QColor fontColor() const
    {
        return value("FontColor", defaultFontColor()).value<QColor>();
    }

    inline static int defaultTopMargin()
    {
        return 0;
    }
    inline void setTopMargin(int px)
    {
        setValue("TopMargin", px);
    }
    inline int topMargin() const
    {
        return value("TopMargin", defaultTopMargin()).toInt();
    }

    inline static int defaultBottomMargin()
    {
        return 0;
    }
    inline void setBottomMargin(int px)
    {
        setValue("BottomMargin", px);
    }
    inline int bottomMargin()
    {
        return value("BottomMargin", defaultBottomMargin()).toInt();
    }

    inline static int defaultLeftMargin()
    {
        return 0;
    }
    inline void setLeftMargin(int px)
    {
        setValue("LeftMargin", px);
    }
    inline int leftMargin()
    {
        return value("LeftMargin", defaultLeftMargin()).toInt();
    }

    inline static int defaultRightMargin()
    {
        return 0;
    }
    inline void setRightMargin(int px)
    {
        setValue("RightMargin", px);
    }
    inline int rightMargin()
    {
        return value("RightMargin", defaultRightMargin()).toInt();
    }

    inline static QString defaultFileName()
    {
        return "aa";
    }
    inline void setFileName(const QString &name)
    {
        setValue("FileName", name.isEmpty() ? defaultFileName() : name);
    }
    inline QString fileName() const
    {
        return value("FileName", defaultFileName()).toString();
    }
};

#endif // ASCIIARTIMAGEGENERATORSETTINGS_H
