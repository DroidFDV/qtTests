#include <QtGui>
#include "enterdata.h"

EnterData::EnterData(QWidget *parent)
    : QDialog(parent)
{
    QLabel *roLabel = new QLabel(tr("Enter ro:"));
    QLabel *colorLabel = new QLabel(tr("Enter color:"));

    inputRoLine = new QLabelEdit;
    inputColorLine = new QLabelEdit;
    inputRo = "";
    inputColor = "";
    enterButton = new QPushButton(tr("&Enter"));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(roLabel);
    layout->addWidget(inputRoLine);
    layout->addWidget(colorLabel);
    layout->addWidget(inputColorLine);
    layout->addWidget(enterButton);

    setLayout(layout);
    setWindowTitle(tr("Filling liquids parameters"));
    connect(enterButton, clicked(), this, enterClicked());
    connect(enterButton, clicked(), this, accept());
}
void EnterData::enterClicked()
{
    QString textRo = inputRoLine->text();
    QString textColor = inputColorLine->text();

    if (inputRoLine.isEmpty() || inputColorLine.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter parameters."));
        return;
    } else {
        inputRo = textRo;
        inputColor = textColor
        inputRoLine->clear();
        inputColorLine->clear();
        hide();
    }
}

QString EnterData::getEnteredRo()
{
    return inputRo;
}

QString EnterData::getEnteredColor()
{
    return inputColor;
}
