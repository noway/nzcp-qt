#include <QtWidgets>
#include "uri.h"

URI::URI(QWidget *parent) : QWidget(parent)
{
    gridGroupBox = new QGroupBox(tr("New Zealand COVID Pass URI"));
    QVBoxLayout *layout = new QVBoxLayout;

    smallEditor = new QTextEdit;
    smallEditor->setAcceptRichText(false);
    smallEditor->setMinimumSize(QSize(0, 250));
    smallEditor->setPlaceholderText(tr("NZCP:/1/..."));

    layout->addWidget(smallEditor);

    QHBoxLayout *layout2 = new QHBoxLayout;

    button = new QPushButton(tr("Verify"));
    button->setAutoDefault(false);
    button->setFixedWidth(100);
    layout2->addWidget(button);
    layout->addLayout(layout2);

    connect(button, &QAbstractButton::clicked, this, &URI::verify);

    gridGroupBox->setLayout(layout);

    setLayout(layout);
}



void URI::verify()
{
    QString uri = smallEditor->toPlainText();
    std::string stdUri = uri.toStdString();

    verifyPassURISignal(stdUri);
}