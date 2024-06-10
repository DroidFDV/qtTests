#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_CloseButton_clicked()
{
   close();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key_1)
    {
        on_CreateBottlButton_clicked();
    }

    if(event->key()==Qt::Key_2)
    {
        on_DeleteBottleButton_clicked();
    }

    if(event->key()==Qt::Key_3)
    {
        on_DeleteBottleButton_clicked();
    }

    if(event->key()==Qt::Key_4)
    {
        on_DeleteBottleButton_clicked();
    }

    if(event->key()==Qt::Key_5)
    {
        on_DeleteBottleButton_clicked();
    }

    if(event->key()==Qt::Key_6)
    {
        on_DeleteBottleButton_clicked();
    }

    if(event->key()==Qt::Key_7)
    {
        on_DeleteBottleButton_clicked();
    }

    if(event->key()==Qt::Key_Escape)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "", "Are you sure you want to close the app?");
        if (reply == QMessageBox::Yes) {
            on_CloseButton_clicked();
        }
        else
        {
            ;
        }
    }
}

void MainWindow::on_CreateBottlButton_clicked()
{
    Bottle<Liquid> b;

    bottles.push_back(b);

    QString str = "Bottle No. " + QString::number(bottles.size());

    ui->BottleList->addItem(str);
    QMessageBox::information(this, "", "Bottle created!");
}

void MainWindow::on_DeleteBottleButton_clicked()
{
    if(ui->BottleList->currentRow() >= 0)
    {
        delete ui->BottleList->takeItem(ui->BottleList->currentRow());

        QMessageBox::information(this, "", "Bottle deleted!");
    }
    else
    {
        QMessageBox::information(this, "", "First choose bootle from list.");
    }
}

void MainWindow::on_InitLiquidButton_clicked()
{
    Liquid l;

    QMessageBox::information(this, "", "Enter density.");
}
