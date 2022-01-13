#include <QtWidgets>
#include <QStatusBar>
#include <zbar.h>
#include <ImageMagick-7/Magick++.h>
#include <iostream>
#include "qrfile.h"

#define InitializeMagick(f) MagickWandGenesis()
#define DestroyMagick	    MagickWandTerminus
#define MagickSetImageIndex MagickSetIteratorIndex
#define MagickGetImagePixels MagickExportImagePixels

using namespace zbar;

QRFile::QRFile(QWidget *parent) : QWidget(parent)
{
    gridGroupBox = new QGroupBox(tr("New Zealand COVID Pass URI"));
    QVBoxLayout *layout = new QVBoxLayout;

    button = new QPushButton(tr("&Open file"));

    QLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(button);
    QWidget *buttonWidget = new QWidget;
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setMinimumSize(QSize(0, 250));

    connect(button, &QAbstractButton::clicked, this, &QRFile::fileOpen);

    // smallEditor = new QTextEdit;
    // smallEditor->setAcceptRichText(false);
    // smallEditor->setMinimumSize(QSize(0, 250));
    // smallEditor->setPlaceholderText(tr("NZCP:/1/..."));

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

static int notfound = 0, exit_code = 0;
static zbar_processor_t *processor = NULL;

char *xmlbuf	   = NULL;
unsigned xmlbuflen = 0;
static int num_images = 0, num_symbols = 0;
static int xmllvl  = 0;
static int oneshot = 0;
static int binary  = 0;

// static inline int dump_error(MagickWand *wand)
// {
//     char *desc;
//     ExceptionType severity;
//     desc = MagickGetException(wand, &severity);

//     if (severity >= FatalErrorException)
//         exit_code = 2;
//     else if (severity >= ErrorException)
//         exit_code = 1;
//     else
//         exit_code = 0;

//     static const char *sevdesc[] = { "WARNING", "ERROR", "FATAL" };
//     fprintf(stderr, "%s: %s\n", sevdesc[exit_code], desc);

//     MagickRelinquishMemory(desc);
//     return (exit_code);
// }

int QRFile::load(const QString &filename)
{
//     // if (!QFile::exists(f))
//     //     return false;
//     // QFile file(f);
//     // if (!file.open(QFile::ReadOnly))
//     //     return false;


    std::string std_filename = filename.toStdString();
    const char* f = std_filename.c_str();

//     int found	       = 0;
//     MagickWand *images = NewMagickWand();
//     if (!MagickReadImage(images, f) && dump_error(images))
// 	return (-1);

//     unsigned seq, n = MagickGetNumberImages(images);
//     for (seq = 0; seq < n; seq++) {
//         if (exit_code == 3)
//             return (-1);

//         if (!MagickSetImageIndex(images, seq) && dump_error(images))
//             return (-1);

//         zbar_image_t *zimage = zbar_image_create();
//         assert(zimage);
//         zbar_image_set_format(zimage, zbar_fourcc('Y', '8', '0', '0'));

//         int width  = MagickGetImageWidth(images);
//         int height = MagickGetImageHeight(images);
//         zbar_image_set_size(zimage, width, height);

//         // extract grayscale image pixels
//         // FIXME color!! ...preserve most color w/422P
//         // (but only if it's a color image)
//         size_t bloblen	    = width * height;
//         unsigned char *blob = (unsigned char *) malloc(bloblen);
//         zbar_image_set_data(zimage, blob, bloblen, zbar_image_free_data);

//         if (!MagickGetImagePixels(images, 0, 0, width, height, "I", CharPixel,
//                     blob))
//             return (-1);

//         if (xmllvl == 1) {
//             xmllvl++;
//             printf("<source href='%s'>\n", f);
//         }
//         processor = zbar_processor_create(0);
//         if (zbar_processor_init(processor, NULL, 0)) {
//             zbar_processor_error_spew(processor, 0);
//             return (1);
//         }

//         zbar_process_image(processor, zimage);

//         // output result data
//         const zbar_symbol_t *sym = zbar_image_first_symbol(zimage);
//         for (; sym; sym = zbar_symbol_next(sym)) {
//             zbar_symbol_type_t typ = zbar_symbol_get_type(sym);
//             unsigned len	   = zbar_symbol_get_data_length(sym);
//             if (typ == ZBAR_PARTIAL)
//                 continue;
//             else if (xmllvl <= 0) {
//                 if (!xmllvl)
//                     printf("%s:", zbar_get_symbol_name(typ));
//                 if (len &&
//                     fwrite(zbar_symbol_get_data(sym), len, 1, stdout) != 1) {
//                     exit_code = 1;
//                     return (-1);
//                 }
//             } else {
//                 if (xmllvl < 3) {
//                     xmllvl++;
//                     printf("<index num='%u'>\n", seq);
//                 }
//                 zbar_symbol_xml(sym, &xmlbuf, &xmlbuflen);
//                 if (fwrite(xmlbuf, xmlbuflen, 1, stdout) != 1) {
//                     exit_code = 1;
//                     return (-1);
//                 }
//             }
//             found++;
//             num_symbols++;

//             if (!binary) {
//                 if (oneshot) {
//                     if (xmllvl >= 0)
//                     printf("\n");
//                     break;
//                 } else
//                     printf("\n");
//             }
//         }
//         if (xmllvl > 2) {
//             xmllvl--;
//             printf("</index>\n");
//         }
//         fflush(stdout);

//         zbar_image_destroy(zimage);

//         num_images++;
//         if (zbar_processor_is_visible(processor)) {
//             int rc = zbar_processor_user_wait(processor, -1);
//             if (rc < 0 || rc == 'q' || rc == 'Q')
//                 exit_code = 3;
//         }
//     }

//     if (xmllvl > 1) {
//         xmllvl--;
//         printf("</source>\n");
//     }

//     if (!found)
//         notfound++;

//     DestroyMagickWand(images);
//     zbar_processor_destroy(processor);


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
    return 0;
}