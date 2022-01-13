#include <QtWidgets>
#include <QStatusBar>
#include <zbar.h>
#include <ImageMagick-7/Magick++.h>
#include <iostream>
#include "qrfile.h"

using namespace zbar;

QRFile::QRFile(QWidget *parent) : QWidget(parent)
{
    gridGroupBox = new QGroupBox(tr("New Zealand COVID Pass URI"));
    QVBoxLayout *layout = new QVBoxLayout;

    QPushButton *openFileButton = new QPushButton(tr("Choose file"));
    openFileButton->setAutoDefault(false);
    openFileButton->setFixedWidth(100);
    fileLabel = new QLabel(tr("No file chosen"));

    QLayout *fileInputLayout = new QHBoxLayout;
    fileInputLayout->addWidget(openFileButton);
    fileInputLayout->addWidget(fileLabel);
    fileInputLayout->setAlignment(Qt::AlignCenter);
    QWidget *buttonWidget = new QWidget;
    buttonWidget->setLayout(fileInputLayout);
    buttonWidget->setMinimumSize(QSize(0, 250));

    connect(openFileButton, &QAbstractButton::clicked, this, &QRFile::fileOpen);

    layout->addWidget(buttonWidget);

    QHBoxLayout *layout2 = new QHBoxLayout;

    button = new QPushButton(tr("Verify"));
    button->setAutoDefault(false);
    button->setFixedWidth(100);
    layout2->addWidget(button);
    layout->addLayout(layout2);

    connect(button, &QAbstractButton::clicked, this, &QRFile::verify);

    gridGroupBox->setLayout(layout);

    setLayout(layout);

}



void QRFile::fileOpen()
{
    QFileDialog fileDialog(this, tr("Choose File..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilters({{"Image files (*.png *.jpg *.gif)"}});
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    filePath = fileDialog.selectedFiles().constFirst();
    QFileInfo fi(filePath);
    QString filename = fi.fileName();
    fileLabel->setText(filename);
}


int QRFile::load(const QString &filePath)
{
    if (!QFile::exists(filePath)) {
        return 1;
    }
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly)) {
        return 1;
    }

    std::string stdFilePath = filePath.toStdString();
    const char* cFilePath = stdFilePath.c_str();

    ImageScanner scanner;
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    // TODO: error handling
    Magick::Image magick(cFilePath);

    int width  = magick.columns(); // extract dimensions
    int height = magick.rows();

    Magick::Blob blob; // extract the raw data
    magick.modifyImage();
    magick.write(&blob, "GRAY", 8);
    const void *raw = blob.data();

    Image image(width, height, "Y800", raw, width * height);

    // TODO: error handling
    int n = scanner.scan(image);

    for (Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol) {
        if (symbol->get_type() == ZBAR_QRCODE) {
            std::string data = symbol->get_data();

            verifyPassURISignal(data);

            const char* data_c = data.c_str();
            printf("%s\n", data_c);
        }
    }

    // clean up
    image.set_data(NULL, 0);
    return 0;
}

void QRFile::verify()
{
    if (load(filePath) == 0) {
    }
    else {
        QMessageBox::information(this, "Error", tr("Could not open \"%1\"").arg(QDir::toNativeSeparators(filePath)));
    }
}