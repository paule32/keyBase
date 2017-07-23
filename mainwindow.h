#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>

#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
private slots:
    void on_actionObjekte_im_Bild_triggered();
    void on_actionLetzten_Schritt_R_ckg_ngig_machen_triggered();
    void on_action_ber_Qt_triggered();
};

extern MainWindow *mainWin;
#endif // MAINWINDOW_H
