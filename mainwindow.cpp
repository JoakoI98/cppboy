#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

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

void MainWindow::refreshList(QStringList toUpdate)
{
    ui->lst_showList->clear();
    ui->lst_showList->addItems(toUpdate);
}


void MainWindow::on_actionLoadROM_triggered()
{
    QString file = QFileDialog::getOpenFileName();
    qDebug() << "Se abrio:  " << file;

}

void MainWindow::on_btn_Continue_clicked()
{
    cpu->ejec();
    QStringList newData = cpu->getInfo(true) + cpu->getInfo(0x40, 0x48, false) + cpu->getInfo(0xFF0B, 0xFF0F, false) + cpu->getInfo(0xFFFB, 0xFFFF, false);
    refreshList(newData);
}
