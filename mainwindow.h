#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>

#include "myeditcompleter.h"
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
private:
    QAbstractItemModel  * modelFromFile(const QString& fileName);
    QCompleter          * completer;
    MyEditCompleter     * completingTextEdit;
private:
    void setWordRecognition();
private slots:
    void on_actionObjekte_im_Bild_triggered();
    void on_actionLetzten_Schritt_R_ckg_ngig_machen_triggered();
    void on_action_ber_Qt_triggered();
    void on_action3D_Welt_triggered();
    void on_action2D_Welt_triggered();
    void on_actionWort_Recognition_triggered();
    void on_actionFormular_Designer_triggered();
};

extern MainWindow *mainWin;
#endif // MAINWINDOW_H
