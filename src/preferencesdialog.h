#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>

namespace Ui {
class PreferencesDialog;
}

class AsciiArtImageGeneratorSettings;
class QAbstractButton;

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget *parent = 0);
    ~PreferencesDialog();

private slots:
    void save();

    void on_selectFontColorButton_clicked();

    void on_selectBackgroundColorButton_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    void init();
    void load();
    void addFileNameString(const QString &str);
    QColor selectColor(const QColor &initialColor);

    Ui::PreferencesDialog* ui;
    AsciiArtImageGeneratorSettings* m_settings;
    QColor m_fontColor;
    QColor m_backgroundColor;
};

#endif // PREFERENCESDIALOG_H
