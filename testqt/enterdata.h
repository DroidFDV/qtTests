#ifndef ENTERDATA_H
#define ENTERDATA_H

#include <QDialog>
#include <QObject>

class QLineEdit;
class QPushButton;

class EnterData : public QDialog
{
    Q_OBJECT

public:
    EnterData(QWidget *parent = nullptr);
    ~EnterData();

    QString getEnteredRo();

    QString getEnteredColor();

public slots:
    void enterClicked();

private:
    QPushButton *enterButton;
    QLineEdit *inputRoLine;
    QLineEdit *inputColorLine;
    QString inputRo;
    QString inputColor;

};

#endif // ENTERDATA_H
