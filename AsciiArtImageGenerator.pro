QT       += core gui widgets

TARGET = AsciiArtImageGenerator
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/asciiartimagegeneratorsettings.cpp \
    src/preferencesdialog.cpp \
    src/tools.cpp

HEADERS  += \
    src/mainwindow.h \
    src/asciiartimagegeneratorsettings.h \
    src/preferencesdialog.h \
    src/tools.h

FORMS    += \
    src/mainwindow.ui \
    src/preferencesdialog.ui

RESOURCES += \
    resource/resource.qrc

macx: ICON = resource/icon/icon.icns
