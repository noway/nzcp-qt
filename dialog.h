#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog();

private slots:
  void handleButton();

private:
    void createMenu();
    void createGridGroupBox();
    void createFormGroupBox();

    QMenuBar *menuBar;
    QGroupBox *gridGroupBox;
    QGroupBox *formGroupBox;
    QTextEdit *smallEditor;
    QPushButton *button;

    QLineEdit *errorLine;
    QLineEdit *jtiLine;
    QLineEdit *issLine;
    QLineEdit *nbfLine;
    QLineEdit *expLine;
    QLineEdit *givenNameLine;
    QLineEdit *familyNameLine;
    QLineEdit *dobLine;

    QMenu *fileMenu;
    QAction *exitAction;
};

#endif // DIALOG_H
