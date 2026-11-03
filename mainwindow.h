#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qslider.h"
#include "trem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void updateInterface(int,int,int);

private:
    Ui::MainWindow *ui;

    //Cria os objetos TREM's
    Trem *trem_a;
    Trem *trem_b;
    Trem *trem_c;
    Trem *trem_d;
    Trem *trem_e;
    Trem *trem_f;

    QSlider *slider_a;
};

#endif // MAINWINDOW_H
