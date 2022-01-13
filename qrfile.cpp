#include <QtWidgets>
#include <QStatusBar>
#include "qrfile.h"

QRFile::QRFile(QWidget *parent) : QWidget(parent)
{
    gridGroupBox = new QGroupBox(tr("New Zealand COVID Pass URI"));
    QVBoxLayout *layout = new QVBoxLayout;

    button = new QPushButton(tr("&Open file"));

    connect(button, &QAbstractButton::clicked, this, &QRFile::fileOpen);

    // smallEditor = new QTextEdit;
    // smallEditor->setAcceptRichText(false);
    // smallEditor->setMinimumSize(QSize(0, 250));
    // smallEditor->setPlaceholderText(tr("NZCP:/1/..."));

    layout->addWidget(button);

    QHBoxLayout *layout2 = new QHBoxLayout;
    QHBoxLayout *layout3 = new QHBoxLayout;

    liveButton = new QRadioButton(tr("Live"));
    liveButton->setChecked(true);
    exampleButton = new QRadioButton(tr("Example"));

    layout3->addWidget(liveButton);
    layout3->addWidget(exampleButton);
    layout3->setAlignment(Qt::AlignLeft);


    layout2->addLayout(layout3);
    button = new QPushButton(tr("Verify"));
    button->setAutoDefault(false);
    button->setFixedWidth(100);
    layout2->addWidget(button);
    layout->addLayout(layout2);


    gridGroupBox->setLayout(layout);

    setLayout(layout);

}



void QRFile::fileOpen()
{
    QFileDialog fileDialog(this, tr("Open File..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setMimeTypeFilters({"image/gif", "image/jpeg", "image/png"});
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    const QString fn = fileDialog.selectedFiles().constFirst();
    if (load(fn)) {
        // QMessageBox::information(this, "Opened", "Ok?");
    }
    else {
        QMessageBox::information(this, "Error", tr("Could not open \"%1\"").arg(QDir::toNativeSeparators(fn)));
    }
}


bool QRFile::load(const QString &f)
{
    if (!QFile::exists(f))
        return false;
    QFile file(f);
    if (!file.open(QFile::ReadOnly))
        return false;

//     QByteArray data = file.readAll();
//     QMimeDatabase db;
//     const QString &mimeTypeName = db.mimeTypeForFileNameAndData(f, data).name();
//     if (mimeTypeName == u"text/html") {
//         auto encoding = QStringDecoder::encodingForHtml(data);
//         QString str = QStringDecoder(encoding ? *encoding : QStringDecoder::Utf8)(data);
//         QUrl fileUrl = f.startsWith(u':') ? QUrl(f) : QUrl::fromLocalFile(f);
//         textEdit->document()->setBaseUrl(fileUrl.adjusted(QUrl::RemoveFilename));
//         textEdit->setHtml(str);
// #if QT_CONFIG(textmarkdownreader)
//     } else if (mimeTypeName == u"text/markdown") {
//         textEdit->setMarkdown(QString::fromUtf8(data));
// #endif
//     } else {
//         textEdit->setPlainText(QString::fromUtf8(data));
//     }

//     setCurrentFileName(f);
    return true;
}