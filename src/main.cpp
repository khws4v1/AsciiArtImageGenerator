#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QFontDatabase>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator t;
    MainWindow w;

    a.setWindowIcon(QIcon(":/icon/icon.png"));

#ifdef QT_DEBUG
    t.load("qt_ja", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
#else
    {
        QDir appDir(QApplication::applicationDirPath());

        appDir.cd("translation");
        t.load("qt_ja", appDir.absolutePath());
    }
#endif
    a.installTranslator(&t);

    //フォントの読み込み
    QFontDatabase::addApplicationFont(":/monapo-20090423/monapo.ttf");

    w.show();

    return a.exec();
}
