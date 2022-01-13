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

    QPushButton *openFileButton = new QPushButton(tr("&Open file"));

    QLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(openFileButton);
    QWidget *buttonWidget = new QWidget;
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setMinimumSize(QSize(0, 250));

    connect(openFileButton, &QAbstractButton::clicked, this, &QRFile::fileOpen);

    layout->addWidget(buttonWidget);

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
    fileDialog.setMimeTypeFilters({"image/png", "image/jpeg", "image/gif"});
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    const QString fn = fileDialog.selectedFiles().constFirst();
    if (load(fn) == 0) {
        // QMessageBox::information(this, "Opened", "Ok?");
    }
    else {
        QMessageBox::information(this, "Error", tr("Could not open \"%1\"").arg(QDir::toNativeSeparators(fn)));
    }
}


int QRFile::load(const QString &filename)
{
    if (!QFile::exists(filename)) {
        return 1;
    }
    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) {
        return 1;
    }


    std::string std_filename = filename.toStdString();
    const char* f = std_filename.c_str();

    bool isExample = exampleButton->isChecked() ? 1 : 0;

    // create a reader
    ImageScanner scanner;

    // configure the reader
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    // obtain image data
    Magick::Image magick(f); // read an image file

    int width  = magick.columns(); // extract dimensions
    int height = magick.rows();

    Magick::Blob blob; // extract the raw data
    magick.modifyImage();
    magick.write(&blob, "GRAY", 8);
    const void *raw = blob.data();

    // wrap image data
    Image image(width, height, "Y800", raw, width * height);

    // scan the image for barcodes
    int n = scanner.scan(image);

    // extract results
    for (Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol) {
        // do something useful with results
        if (symbol->get_type() == ZBAR_QRCODE) {
            std::string data = symbol->get_data();

            verifyPassURISignal(data, isExample);

            const char* data_c = data.c_str();
            printf("%s\n", data_c);
        }
    }

    // clean up
    image.set_data(NULL, 0);
    return 0;
}