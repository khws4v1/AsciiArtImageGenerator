#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"
#include "asciiartimagegeneratorsettings.h"
#include "tools.h"
#include <QColorDialog>

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog),
    m_settings(new AsciiArtImageGeneratorSettings),
    m_fontColor(m_settings->fontColor()),
    m_backgroundColor(m_settings->backgroundColor())
{
    init();
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::init()
{
    ui->setupUi(this);

    connect(this, SIGNAL(accepted()), this, SLOT(save()));
    connect(ui->fileNameLine, &QLineEdit::textChanged, [&](const QString &text) {
        ui->realFileNameLine->setText(AsciiArtImageGenerator::saveFileName(text));
    });
    connect(ui->createdYearButton, &QPushButton::clicked, [&]() {
        addFileNameString("%{YEAR}");
    });
    connect(ui->createdMonthButton, &QPushButton::clicked, [&]() {
        addFileNameString("%{MONTH}");
    });
    connect(ui->createdDayButton, &QPushButton::clicked, [&]() {
        addFileNameString("%{DAY}");
    });
    connect(ui->createdHourButton, &QPushButton::clicked, [&]() {
        addFileNameString("%{HOUR}");
    });
    connect(ui->createdMinuteButton, &QPushButton::clicked, [&]() {
        addFileNameString("%{MINUTE}");
    });
    connect(ui->createdSecondButton, &QPushButton::clicked, [&]() {
        addFileNameString("%{SECOND}");
    });
    connect(ui->createdUnixTimeButton, &QPushButton::clicked, [&]() {
        addFileNameString("%{UNIX}");
    });

    load();
}

void PreferencesDialog::save()
{
    m_settings->setFontSize(ui->fontSizeBox->value());
    m_settings->setLineHeight(ui->lineHeightBox->value());
    m_settings->setFontColor(m_fontColor);
    m_settings->setBackgroundColor(ui->transparentBackgroundBox->isChecked()
                                   ? QColor(Qt::transparent)
                                   : m_backgroundColor);
    m_settings->setTopMargin(ui->topMarginBox->value());
    m_settings->setBottomMargin(ui->bottomMarginBox->value());
    m_settings->setLeftMargin(ui->leftMarginBox->value());
    m_settings->setRightMargin(ui->rightMarginBox->value());
    m_settings->setFileName(ui->fileNameLine->text());
}

void PreferencesDialog::load()
{
    ui->fontSizeBox->setValue(m_settings->fontSize());
    ui->lineHeightBox->setValue(m_settings->lineHeight());
    ui->fontColorCodeLine->setText(m_fontColor.name());
    if (m_backgroundColor == QColor(Qt::transparent))
        ui->transparentBackgroundBox->setChecked(true);
    else
        ui->backgroundColorCodeLine->setText(m_backgroundColor.name());
    ui->topMarginBox->setValue(m_settings->topMargin());
    ui->bottomMarginBox->setValue(m_settings->bottomMargin());
    ui->leftMarginBox->setValue(m_settings->leftMargin());
    ui->rightMarginBox->setValue(m_settings->rightMargin());
    ui->fileNameLine->setText(m_settings->fileName());
}

void PreferencesDialog::addFileNameString(const QString &str)
{
    ui->fileNameLine->setText(ui->fileNameLine->text() + str);
}

QColor PreferencesDialog::selectColor(const QColor &initialColor)
{
    QColorDialog d(initialColor, this);

    if (d.exec() == QColorDialog::Accepted)
        return d.selectedColor();
    else
        return QColor();
}

void PreferencesDialog::on_selectFontColorButton_clicked()
{
    const QColor color = selectColor(m_fontColor);

    if (color.isValid()) {
        m_fontColor = color;
        ui->fontColorCodeLine->setText(color.name());
    }
}

void PreferencesDialog::on_selectBackgroundColorButton_clicked()
{
    const QColor color = selectColor(m_backgroundColor);

    if (color.isValid()) {
        m_backgroundColor = color;
        ui->backgroundColorCodeLine->setText(color.name());
    }
}

void PreferencesDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch (ui->buttonBox->standardButton(button)) {
    case QDialogButtonBox::Ok:
        accept();
        break;
    case QDialogButtonBox::Cancel:
        reject();
        break;
    case QDialogButtonBox::RestoreDefaults:
        ui->fontSizeBox->setValue(AsciiArtImageGeneratorSettings::defaultFontSize());
        ui->lineHeightBox->setValue(AsciiArtImageGeneratorSettings::defaultLineHeight());
        ui->fontColorCodeLine->setText
                ((m_fontColor = AsciiArtImageGeneratorSettings::defaultFontColor()).name());
        ui->transparentBackgroundBox->setChecked
                ((m_backgroundColor = AsciiArtImageGeneratorSettings::defaultBackgroundColor())
                 == QColor(Qt::transparent));
        if (m_backgroundColor != QColor(Qt::transparent))
            ui->backgroundColorCodeLine->setText(m_backgroundColor.name());
        ui->topMarginBox->setValue(AsciiArtImageGeneratorSettings::defaultTopMargin());
        ui->bottomMarginBox->setValue(AsciiArtImageGeneratorSettings::defaultBottomMargin());
        ui->leftMarginBox->setValue(AsciiArtImageGeneratorSettings::defaultLeftMargin());
        ui->rightMarginBox->setValue(AsciiArtImageGeneratorSettings::defaultRightMargin());
        ui->fileNameLine->setText(AsciiArtImageGeneratorSettings::defaultFileName());
        break;
    default:
        break;
    }
}
