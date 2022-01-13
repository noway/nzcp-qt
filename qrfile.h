#ifndef QR_FILE_H
#define QR_FILE_H

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
class QRadioButton;
QT_END_NAMESPACE

class QRFile : public QWidget
{
    Q_OBJECT

public:
    explicit QRFile(QWidget *parent = nullptr);

private:

    void fileOpen();
    QGroupBox *gridGroupBox;
    QTextEdit *smallEditor;
    QRadioButton *liveButton;
    QRadioButton *exampleButton;
    QPushButton *button;
};

#endif // QR_FILE_H