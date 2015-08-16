#include "asciiartimagegeneratorsettings.h"
#include <QApplication>

AsciiArtImageGeneratorSettings::AsciiArtImageGeneratorSettings()
    : QSettings(QSettings::IniFormat,
                QSettings::UserScope,
                QApplication::organizationName())
{

}
