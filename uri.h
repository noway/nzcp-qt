#ifndef URI_H
#define URI_H

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

class URI : public QWidget
{
    Q_OBJECT

public:
    explicit URI(QWidget *parent = nullptr);

signals:
    void verifyPassURISignal(std::string uri);

private:
    void verify();

    QGroupBox *gridGroupBox;
    QTextEdit *smallEditor;
    QRadioButton *liveButton;
    QRadioButton *exampleButton;
    QPushButton *button;
};

#endif // URI_H
