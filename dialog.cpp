#include <QtWidgets>
#include "dialog.h"

Dialog::Dialog()
{
    createMenu();
    createGridGroupBox();
    createFormGroupBox();

    connect(button, &QPushButton::released, this, &Dialog::handleButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(formGroupBox);
    setLayout(mainLayout);

    setWindowTitle(tr("NZCP-Qt"));
}

void Dialog::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    connect(exitAction, &QAction::triggered, this, &QDialog::accept);
}

void Dialog::createGridGroupBox()
{
    gridGroupBox = new QGroupBox(tr("New Zealand COVID Pass URI"));
    QVBoxLayout *layout = new QVBoxLayout;

    smallEditor = new QTextEdit;
    smallEditor->setAcceptRichText(false);
    smallEditor->setPlaceholderText(tr("NZCP:/1/..."));

    layout->addWidget(smallEditor);

    QHBoxLayout *layout2 = new QHBoxLayout;
    button = new QPushButton(tr("Verify"));
    button->setAutoDefault(false);
    button->setFixedWidth(100);
    layout2->addWidget(button);
    layout->addLayout(layout2);


    gridGroupBox->setLayout(layout);
}

void Dialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("New Zealand COVID Pass Fields"));
    QFormLayout *layout = new QFormLayout;

    layout->addRow(new QLabel(tr("valid:")), new QLineEdit);
    layout->addRow(new QLabel(tr("jti:")), new QLineEdit);
    layout->addRow(new QLabel(tr("iss:")), new QLineEdit);
    layout->addRow(new QLabel(tr("nbf:")), new QLineEdit);
    layout->addRow(new QLabel(tr("exp:")), new QLineEdit);
    layout->addRow(new QLabel(tr("given_name:")), new QLineEdit);
    layout->addRow(new QLabel(tr("family_name:")), new QLineEdit);
    layout->addRow(new QLabel(tr("dob:")), new QLineEdit);

    formGroupBox->setLayout(layout);
}


void Dialog::handleButton()
{
  printf("button pressed\n");
}