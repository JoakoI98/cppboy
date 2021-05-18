#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "../cpu/cpu.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void refreshList(QStringList toUpdate);
    cppb::CPU *cpu = nullptr;

private slots:
    void on_actionLoadROM_triggered();

    void on_btn_Continue_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
