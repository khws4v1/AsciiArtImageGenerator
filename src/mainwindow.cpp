#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "asciiartimagegeneratorsettings.h"
#include "preferencesdialog.h"
#include "tools.h"
#include <QDialog>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QPainter>
#include <QDebug>
#include <QMimeDatabase>
#include <QDesktopServices>

using namespace AsciiArtImageGenerator;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_settings(new AsciiArtImageGeneratorSettings)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openTextFile()
{
    QFileDialog fileDialog(this, tr("開く"));
    QFile file;

    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setMimeTypeFilters(QStringList{"text/plain", "application/octet-stream"});

    if (fileDialog.exec() != QFileDialog::Accepted)
        return;

    file.setFileName(fileDialog.selectedFiles().first());
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::critical(this,
                              tr("エラー"),
                              tr("ファイルを開けませんでした。\n%1").arg(file.errorString()),
                              QMessageBox::Ok);
        return;
    }
    ui->aaTextEdit->setPlainText(QString(file.readAll()));
}

void MainWindow::on_previewButton_clicked()
{
    auto* previewDialog = new QDialog(this);
    auto* previewLabel  = new QLabel(previewDialog);
    auto* button        = new QDialogButtonBox(QDialogButtonBox::Close,
                                               previewDialog);

    previewDialog->setWindowTitle(tr("プレビュー"));

    previewLabel->setPixmap(QPixmap::fromImage(generateImage()));

    previewDialog->setLayout(new QVBoxLayout(previewDialog));
    previewDialog->layout()->addWidget(previewLabel);
    previewDialog->layout()->addWidget(button);
    previewDialog->show();

    connect(button, SIGNAL(accepted()), previewDialog, SLOT(accept()));
    connect(button, SIGNAL(rejected()), previewDialog, SLOT(reject()));
    connect(previewDialog, SIGNAL(finished(int)), previewDialog, SLOT(deleteLater()));
}

void MainWindow::init()
{
    setWindowTitle(QApplication::applicationName());
    ui->actionAbout->setText(QApplication::applicationName() + "について");
    ui->actionAboutqt->setText(QString("Qt %1 について").arg(qVersion()));
    ui->fontComboBox->setCurrentFont(QFont(m_settings->fontFamily()));

    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(openTextFile()));
    connect(ui->action_P, &QAction::triggered, [&]() {
        PreferencesDialog d;
        if (d.exec() == PreferencesDialog::Accepted)
            setCss();
    });
    connect(ui->actionAbout, &QAction::triggered, [&]() {
        QMessageBox::about(this,
                           QApplication::applicationName() + "について",
                           QString(R"(<h3>%1</h3>
                           <p><a href="http://khws4v1.myhome.cx/">Copyright (c) 2015 khws4v1)</a></p>)")
                                     .arg(QApplication::applicationName()));
    });
    connect(ui->actionAboutqt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->fontComboBox, &QFontComboBox::currentFontChanged, [&](const QFont& font) {
        m_settings->setFontFamily(font.family());
        setCss();
    });
    connect(this, SIGNAL(cssChanged(QString)), ui->aaTextEdit, SLOT(setStyleSheet(QString)));
    connect(ui->exitAction, SIGNAL(triggered(bool)), qApp, SLOT(quit()));

    setCss();
    ui->aaTextEdit->setStyleSheet(m_css);
}

void MainWindow::setCss()
{
    m_css =  generateCss(m_settings->fontFamily(),
                         m_settings->fontColor(),
                         m_settings->backgroundColor(),
                         m_settings->fontSize(),
                         m_settings->lineHeight());
    ui->aaTextEdit->setStyleSheet(m_css);
}

QImage MainWindow::generateImage() const
{
    const QPoint           offset(m_settings->leftMargin(), m_settings->topMargin());
    QLabel                 aaLabel(ui->aaTextEdit->toPlainText());
    QSize                  imageSize;
    QScopedPointer<QImage> image;
    QPainter               painter;

    aaLabel.resize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    aaLabel.setStyleSheet(m_css);
    aaLabel.resize(aaLabel.sizeHint());
    aaLabel.setTextFormat(Qt::PlainText);

    imageSize = aaLabel.size();
    imageSize.setHeight(imageSize.height() + m_settings->topMargin() + m_settings->bottomMargin());
    imageSize.setWidth(imageSize.width() + m_settings->leftMargin() + m_settings->rightMargin());

    image.reset(new QImage(imageSize, QImage::Format_ARGB32_Premultiplied));
    image->fill(m_settings->backgroundColor());
    painter.begin(image.data());

    painter.drawImage(offset, aaLabel.grab().toImage());

    painter.end();

    return *image.data();
}

void MainWindow::on_saveButton_clicked()
{
    const QStringList filter{"image/png", "image/gif", "image/jpeg"};
    QMimeDatabase     db;
    QFileDialog       fileDialog(this, tr("保存"), m_lastSelectedDirPath);
    const char*       imageFormat;
    QString           path;
    QString           suffix;

    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setMimeTypeFilters(filter);
    fileDialog.selectFile(saveFileName(m_settings->fileName()));

    if (fileDialog.exec() != QFileDialog::Accepted)
        return;

    m_lastSelectedDirPath = fileDialog.directory().absolutePath();

    path = fileDialog.selectedFiles().first();

    switch(fileDialog.nameFilters().indexOf(fileDialog.selectedNameFilter())) {
    case 0:
        imageFormat = "PNG";
        suffix = ".png";
        break;
    case 1:
        imageFormat = "GIF";
        suffix = "gif";
        break;
    default:
        imageFormat = "JPEG";
        suffix = ".jpg";
        break;
    }
    if (!path.contains(QRegExp("^.+\\..+$")))
        path.append(suffix);

    if (generateImage().save(path,
                             imageFormat,
                             100)) {
        if (QMessageBox::information(this,
                                 tr("保存完了"),
                                 tr("%1に保存しました。").arg(path),
                                 QMessageBox::Ok, QMessageBox::Open) == QMessageBox::Open)
            QDesktopServices::openUrl(QUrl::fromLocalFile(fileDialog.selectedFiles().first()));
    } else {
        if (QMessageBox::critical(this,
                                  tr("エラー"),
                                  tr("保存に失敗しました。"),
                                  QMessageBox::Ok,
                                  QMessageBox::Retry) == QMessageBox::Retry)
            QMetaObject::invokeMethod(this, "on_saveButton_clicked");
    }
}

