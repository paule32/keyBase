#include "mainwindow.h"
#include "mydesignercomponents.h"
#include "mylistwidgetitem.h"
#include "editorgutter.h"

#include <QDebug>

MyDesignerComponents::MyDesignerComponents(QWidget *parent)
    : QListWidget(parent)
{
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::DragOnly);
    setDefaultDropAction(Qt::TargetMoveAction);
    setAlternatingRowColors(true);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSpacing(2);
    setViewMode(QListView::ListMode);
    setModelColumn(0);
    show();

    MyListWidgetItem *li_00 = new MyListWidgetItem(this,"Standard","",1);
    MyListWidgetItem *li_01 = new MyListWidgetItem(this,"Push Button","",0);
    MyListWidgetItem *li_02 = new MyListWidgetItem(this,"Radio Button","",0);

    QListWidget *ptr = mainWin->ui->formWindow->ui->listWidget_3;
    ptr->addItem(li_00);
    ptr->addItem(li_01);
    ptr->addItem(li_02);
}

void MyDesignerComponents::mouseDoubleClickEvent(QMouseEvent *event)
{
    QListWidgetItem * ptr = currentItem();
    if (!ptr) return;

    try {
        if (ptr->text() == QString("Standard"))
        {
            item(1)->setHidden(!true);
            item(2)->setHidden(!true);
        }
    } catch(...) {
        qDebug() << QString("Error detected: ") +
                    QString(__FILE__) +
                    QString(": "    ) +
                    QString(__LINE__) ;
    }
}

void MyDesignerComponents::mousePressEvent(QMouseEvent *event)
{
    QListWidgetItem *itemptr = itemAt(event->pos());
    if (!itemptr) return;

    if (itemptr->text() == QString("Standard")) {
        event->accept();
        QListWidget::mousePressEvent(event);
        return;
    }

    QListWidget::mousePressEvent(event);

    QMimeData * mimeData = new QMimeData;
    mimeData->setText("lops blops\n");

    QDrag * drag = new QDrag(this);
    drag->setMimeData(mimeData);

    Qt::DropAction dropAction =
    drag->exec(
        Qt::CopyAction |
        Qt::MoveAction ,
        Qt::CopyAction);

    Qt::DropAction tar = drag->start();
    MyEditor *ptr = findChild<MyEditor *>("dBaseEditor");
    if ((ptr != nullptr) && (ptr->hasFocus())) {
        ptr->setFocus();
        ptr->on_cursorPositionChanged();
        ptr->setFocus();
        return;
    }
}
