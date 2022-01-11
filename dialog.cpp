#include <QtWidgets>
#include "dialog.h"
#include <nzcp.h>

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
    QString uri = smallEditor->toPlainText();

    nzcp_verification_result verification_result;
    nzcp_error error = nzcp_verify_pass_uri((uint8_t*)uri.toStdString().c_str(), &verification_result, 0);

    if (error == NZCP_E_SUCCESS) {
        printf("jti: %s\n", verification_result.jti);
        printf("iss: %s\n", verification_result.iss);
        printf("nbf: %d\n", verification_result.nbf);
        printf("exp: %d\n", verification_result.exp);
        printf("given_name: %s\n", verification_result.given_name);
        printf("family_name: %s\n", verification_result.family_name);
        printf("dob: %s\n", verification_result.dob);
    }
    else {
        printf("error: %s\n", nzcp_error_string(error));
    }

    nzcp_free_verification_result(&verification_result);

}