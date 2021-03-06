#include <QtWidgets>
#include "dialog.h"
#include <nzcp.h>
#include "uri.h"
#include "qrfile.h"

Dialog::Dialog()
{
    createMenu();

    createFormGroupBox();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);

    tabWidget = new QTabWidget;
    QRFile *qrFile = new QRFile;
    URI *uri = new URI;
    tabWidget->addTab(qrFile, tr("QR code file"));
    tabWidget->addTab(uri, tr("URI"));

    connect(qrFile, SIGNAL(verifyPassURISignal(std::string)), this, SLOT(verifyPassURI(std::string)));
    connect(uri, SIGNAL(verifyPassURISignal(std::string)), this, SLOT(verifyPassURI(std::string)));

    mainLayout->addWidget(tabWidget);
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

void Dialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("New Zealand COVID Pass result"));

    QWidget *settingsWidget = new QWidget;
    QHBoxLayout *modeLayout = new QHBoxLayout;

    liveButton = new QRadioButton(tr("Live"));
    liveButton->setChecked(true);
    exampleButton = new QRadioButton(tr("Example"));

    modeLayout->addWidget(liveButton);
    modeLayout->addWidget(exampleButton);
    modeLayout->setAlignment(Qt::AlignLeft);
    settingsWidget->setLayout(modeLayout);


    QWidget *formWidget = new QWidget;
    QFormLayout *layout = new QFormLayout;

    errorLine = new QLineEdit;
    errorLine->setReadOnly(true);
    errorLine->setFixedWidth(350);
    jtiLine = new QLineEdit;
    jtiLine->setReadOnly(true);
    jtiLine->setFixedWidth(350);
    issLine = new QLineEdit;
    issLine->setReadOnly(true);
    issLine->setFixedWidth(350);
    nbfLine = new QLineEdit;
    nbfLine->setReadOnly(true);
    nbfLine->setFixedWidth(350);
    expLine = new QLineEdit;
    expLine->setReadOnly(true);
    expLine->setFixedWidth(350);
    givenNameLine = new QLineEdit;
    givenNameLine->setReadOnly(true);
    givenNameLine->setFixedWidth(350);
    familyNameLine = new QLineEdit;
    familyNameLine->setReadOnly(true);
    familyNameLine->setFixedWidth(350);
    dobLine = new QLineEdit;
    dobLine->setReadOnly(true);
    dobLine->setFixedWidth(350);

    layout->addRow(new QLabel(tr("error")), errorLine);
    layout->addRow(new QLabel(tr("jti")), jtiLine);
    layout->addRow(new QLabel(tr("iss")), issLine);
    layout->addRow(new QLabel(tr("nbf")), nbfLine);
    layout->addRow(new QLabel(tr("exp")), expLine);
    layout->addRow(new QLabel(tr("given_name")), givenNameLine);
    layout->addRow(new QLabel(tr("family_name")), familyNameLine);
    layout->addRow(new QLabel(tr("dob")), dobLine);

    formWidget->setLayout(layout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(settingsWidget);
    mainLayout->addWidget(formWidget);
    formGroupBox->setLayout(mainLayout);
}


void Dialog::verifyPassURI(std::string std_uri)
{
    bool isExample = exampleButton->isChecked() ? 1 : 0;
    int is_example = isExample ? 1 : 0;

    nzcp_verification_result verification_result;
    nzcp_error error = nzcp_verify_pass_uri((uint8_t*)std_uri.c_str(), &verification_result, is_example);

    if (error == NZCP_E_SUCCESS) {
        errorLine->setText(QString::fromStdString(nzcp_error_string(error)));
        jtiLine->setText(QString::fromStdString(verification_result.jti));
        issLine->setText(QString::fromStdString(verification_result.iss));
        nbfLine->setText(QString::fromStdString(std::to_string(verification_result.nbf)));
        expLine->setText(QString::fromStdString(std::to_string(verification_result.exp)));
        givenNameLine->setText(QString::fromStdString(verification_result.given_name));
        familyNameLine->setText(QString::fromStdString(verification_result.family_name));
        dobLine->setText(QString::fromStdString(verification_result.dob));
    }
    else {
        errorLine->setText(QString::fromStdString(nzcp_error_string(error)));
        jtiLine->setText(QString::fromStdString(""));
        issLine->setText(QString::fromStdString(""));
        nbfLine->setText(QString::fromStdString(""));
        expLine->setText(QString::fromStdString(""));
        givenNameLine->setText(QString::fromStdString(""));
        familyNameLine->setText(QString::fromStdString(""));
        dobLine->setText(QString::fromStdString(""));
    }

    nzcp_free_verification_result(&verification_result);

}
