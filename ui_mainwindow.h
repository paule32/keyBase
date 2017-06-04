/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "editorgutter.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QWidget *widget_5;
    QWidget *widget_7;
    QWidget *widget_8;
    QWidget *widget_9;
    MyEditor *editorGutter;
    QWidget *widget_3;
    QWidget *widget_2;
    QLabel *label;
    QLabel *label_2;
    QWidget *widget_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *widget_6;
    QWidget *tab_2;
    QListWidget *listWidget;
    QMenuBar *menubar;
    QMenu *menuDatei;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 728);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 1021, 700));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(631, 0));
        widget->setSizeIncrement(QSize(0, 0));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(114, 159, 207);"));
        widget_5 = new QWidget(widget);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setGeometry(QRect(290, 30, 731, 501));
        widget_7 = new QWidget(widget_5);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        widget_7->setGeometry(QRect(61, 2, 131, 41));
        widget_7->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 0, 255, 255), stop:1 rgba(255, 255, 255, 255));"));
        widget_8 = new QWidget(widget_5);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        widget_8->setGeometry(QRect(196, 5, 131, 40));
        widget_8->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 255, 167, 255), stop:1 rgba(255, 255, 255, 255));"));
        widget_9 = new QWidget(widget_5);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        widget_9->setGeometry(QRect(0, 40, 61, 431));
        widget_9->setStyleSheet(QStringLiteral("background-color: rgb(186, 189, 182);"));
        editorGutter = new MyEditor(widget_5);
        editorGutter->setObjectName(QStringLiteral("editorGutter"));
        editorGutter->setGeometry(QRect(60, 40, 661, 431));
        QFont font;
        font.setFamily(QStringLiteral("Courier"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        editorGutter->setFont(font);
        editorGutter->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 226, 255, 255), stop:1 rgba(255, 255, 255, 255));"));
        editorGutter->setFrameShape(QFrame::NoFrame);
        editorGutter->setFrameShadow(QFrame::Plain);
        editorGutter->setLineWidth(0);
        editorGutter->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        editorGutter->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(60, 0, 961, 29));
        widget_3->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(0, 0, 110, 681));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy2);
        widget_2->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(25, 30, 50, 31));
        label->setStyleSheet(QStringLiteral("background-color: rgb(252, 233, 79);"));
        label->setTextFormat(Qt::RichText);
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/welcome.png")));
        label->setScaledContents(true);
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 91, 17));
        widget_4 = new QWidget(widget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setGeometry(QRect(0, 670, 1021, 29));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy3);
        widget_4->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));
        tabWidget = new QTabWidget(widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(290, 530, 731, 141));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        widget_6 = new QWidget(tab);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setGeometry(QRect(0, 0, 741, 111));
        widget_6->setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207);"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        listWidget = new QListWidget(widget);
        QBrush brush(QColor(252, 233, 79, 255));
        brush.setStyle(Qt::NoBrush);
        QBrush brush1(QColor(52, 101, 164, 255));
        brush1.setStyle(Qt::SolidPattern);
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setTextAlignment(Qt::AlignCenter);
        __qlistwidgetitem->setFont(font1);
        __qlistwidgetitem->setBackground(brush1);
        __qlistwidgetitem->setForeground(brush);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(110, 30, 179, 639));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy4);
        listWidget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        listWidget->setFrameShape(QFrame::WinPanel);
        listWidget->setFrameShadow(QFrame::Raised);
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        widget_2->raise();
        widget_5->raise();
        widget_3->raise();
        widget_4->raise();
        tabWidget->raise();
        listWidget->raise();
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 22));
        menuDatei = new QMenu(menubar);
        menuDatei->setObjectName(QStringLiteral("menuDatei"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuDatei->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#d3d7cf;\">Willkommen</span></p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "Standard", 0));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MainWindow", "Neues Element", 0));
        listWidget->setSortingEnabled(__sortingEnabled);

        menuDatei->setTitle(QApplication::translate("MainWindow", "Datei", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
