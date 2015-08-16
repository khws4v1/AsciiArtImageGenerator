#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardPaths>

namespace Ui {
class MainWindow;
}

class AsciiArtImageGeneratorSettings;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void cssChanged(const QString& css);

private slots:
    void openTextFile();
    void on_previewButton_clicked();
    void on_saveButton_clicked();

private:
    void   init();
    void   setCss();
    void   setAATextEditFont();
    QImage generateImage() const;

    Ui::MainWindow* ui;
    AsciiArtImageGeneratorSettings* m_settings;
    QString m_css;
    QString m_lastSelectedDirPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
};

#endif // MAINWINDOW_H
