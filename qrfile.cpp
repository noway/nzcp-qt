#include <QtWidgets>
#include "qrfile.h"

QRFile::QRFile(QWidget *parent) : QWidget(parent)
{
    gridGroupBox = new QGroupBox(tr("New Zealand COVID Pass URI"));
    QVBoxLayout *layout = new QVBoxLayout;

    smallEditor = new QTextEdit;
    smallEditor->setAcceptRichText(false);
    smallEditor->setMinimumSize(QSize(0, 250));
    smallEditor->setPlaceholderText(tr("NZCP:/1/..."));

    layout->addWidget(smallEditor);

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
