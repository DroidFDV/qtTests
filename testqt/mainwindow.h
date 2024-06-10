#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <vector>
#include "liquid.h"
#include "bottle.h"
#include "enterdata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_CloseButton_clicked();

    void on_CreateBottlButton_clicked();

    void on_DeleteBottleButton_clicked();

    void on_InitLiquidButton_clicked();

private:
    Ui::MainWindow *ui;

    std::vector<Bottle<Liquid>> bottles;

    std::vector<Liquid> liquids;

protected:
    virtual void keyPressEvent(QKeyEvent *event);

};
#endif // MAINWINDOW_H
