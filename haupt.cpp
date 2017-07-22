#include <QMessageBox>
#include <QLabel>
#include <QString>
#include <QModelIndex>
#include <QPixmap>
#include <QClipboard>

#include "mainwindow.h"
#include "haupt.h"
#include "ui_haupt.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_listWidget_3_doubleClicked(const QModelIndex &index)
{
    if (index.row() < 1) return;

    QString fname = mainWin->ui->formWindow->ui->listWidget_3->currentItem()->text();

    mainWin->ui->formWindow->ui->editorGutter->setEnabled(false);
    mainWin->ui->formWindow->ui->editorGutter->hide();

    QPixmap pix(QString("./images/%1").arg(fname));
    QLabel *img = new QLabel;
    ui->editLayout->addWidget(img);
    img->setObjectName("ocr_image");
    img->setPixmap(pix);
    img->show();

    QClipboard *clip = QApplication::clipboard();
    clip->setText("ocr:image");
}
