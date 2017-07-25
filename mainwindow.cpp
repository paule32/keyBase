#include <QObject>
#include <QStringList>
#include <QString>
#include <QDir>
#include <QPixmap>
#include <QClipboard>
#include <QListWidgetItem>

#include "mainwindow.h"
#include "haupt.h"
#include "dreidworld.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);  
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionObjekte_im_Bild_triggered()
{
    QDir images("./images");
    QStringList filter;

    filter << "*.bmp"
           << "*.png"
           << "*.jpg";
    QStringList flist = images.entryList(filter);
    QStringList::const_iterator test;
    QListWidgetItem *item;

    item = new QListWidgetItem("Bilddatei auswählen...");
    item->setBackgroundColor(Qt::blue);
    item->setForeground(QBrush(Qt::yellow));
    item->font().setBold(true);
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    mainWin->ui->formWindow->ui->listWidget_3->clear();
    mainWin->ui->formWindow->ui->listWidget_3->addItem(item);

    for(test  = flist.constBegin();
        test != flist.constEnd();
        ++test) {
        item = new QListWidgetItem((*test).toLatin1().constData());
        mainWin->ui->formWindow->ui->listWidget_3->addItem(item);
    }
}

void MainWindow::on_actionLetzten_Schritt_R_ckg_ngig_machen_triggered()
{
    QClipboard *clip = QApplication::clipboard();
    if (clip->text() == QString("ocr:image")) {
        QObject *pix = ui->formWindow->findChild<
        QObject *>("ocr_image");

        if (pix == nullptr)
        return;

        QLabel *px = dynamic_cast<QLabel*>(pix);
        px->setEnabled(false);
        px->hide();

        delete px;

        mainWin->ui->formWindow->ui->editLayout->addWidget(
        mainWin->ui->formWindow->ui->editorGutter        );
        mainWin->ui->formWindow->ui->editorGutter->setEnabled(true);
        mainWin->ui->formWindow->ui->editorGutter->show();
    }
}

void MainWindow::on_action_ber_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_action3D_Welt_triggered()
{
    dreidworld * ddw = new dreidworld;
    ddw->setup();
}
