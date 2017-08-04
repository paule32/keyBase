#include <QObject>
#include <QStringList>
#include <QString>
#include <QDir>
#include <QPixmap>
#include <QClipboard>
#include <QListWidgetItem>
#include <QStringListModel>

#include <QDebug>

#include "mainwindow.h"
#include "haupt.h"
#include "dreidworld.h"
#include "my2dworld.h"
#include "myeditcompleter.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , completer(0)
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);
}

void MainWindow::setWordRecognition()
{
    completingTextEdit = new MyEditCompleter;
    completer = new QCompleter(this);
    completer->setModel(modelFromFile("./wordlist.txt"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    completingTextEdit->setCompleter(completer);

    ui->formWindow->ui->editLayout->replaceWidget(
    ui->formWindow->ui->editorGutter,
    completingTextEdit);
}

QAbstractItemModel *
MainWindow::modelFromFile(const QString& fileName)
{
    QFile file1(fileName);
    QFile file2;

    if (!file1.open(QFile::ReadOnly))
        return new QStringListModel(completer);

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    QStringList words; words.clear();

    file1.seek(0);
    while (!file1.atEnd()) {
        QByteArray line = file1.readLine();

        if (!line.isEmpty()) {
            QString strline = line;
            if (strline.at(0) == QChar('#'))
            continue;

            QByteArrayList strlist = line.split(';');
            QString word1 = QString(strlist.at(0)).trimmed();
            QString fnam1 = QString(strlist.at(1)).trimmed();

            qDebug() << fnam1;
            if (fnam1.trimmed().size() < 1)
            continue;

            if (fnam1.contains(QChar('%'))) {
                fnam1  = fnam1.remove(QChar('%'));

                file2.close();
                file2.setFileName(QString("./database/%1").arg(fnam1));

                if (!file2.open(QFile::ReadOnly)) {
                    return new QStringListModel(completer);
                }

                file2.seek(0);
                while (!file2.atEnd()) {
                    QByteArray line2 = file2.readLine();

                    if (!line2.isEmpty()) {
                        QString strline2 = line2;
                        if (strline2.at(0) == QChar('#'))
                        continue;

                        QByteArrayList strlist2 = line2.split(';');
                        QString word2 = QString(strlist2.at(0)).trimmed();

                        qDebug() << word1 << " --  " << word2;

                        if (word2.size() > 0) {
                            words << QString("%1 %2")
                                     .arg(word1)
                                     .arg(word2);
                        }
                    }
                }
            }
        }
    }

    words.removeDuplicates();
    words.sort();

    file2.close();
    file1.close();

    QApplication::restoreOverrideCursor();
    return new QStringListModel(words, completer);
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
    ui->formWindow->ui->listWidget_3->clear();
    ui->formWindow->ui->listWidget_3->addItem(item);

    for(test  = flist.constBegin();
        test != flist.constEnd();
        ++test) {
        item = new QListWidgetItem((*test).toLatin1().constData());
        ui->formWindow->ui->listWidget_3->addItem(item);
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

        ui->formWindow->ui->editLayout->addWidget(
        ui->formWindow->ui->editorGutter        );
        ui->formWindow->ui->editorGutter->setEnabled(true);
        ui->formWindow->ui->editorGutter->show();
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

void MainWindow::on_action2D_Welt_triggered()
{
    my2dworld * m2d = new my2dworld(nullptr);
    m2d->setGeometry(0,0,300,300);
    m2d->show();
}

void MainWindow::on_actionWort_Recognition_triggered()
{
    setWordRecognition();
    ui->formWindow->
    ui->dataEdit->appendPlainText(
    "word recognition on");
}
