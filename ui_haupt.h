/********************************************************************************
** Form generated from reading UI file 'haupt.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HAUPT_H
#define UI_HAUPT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <editorgutter.h>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_4;
    QLabel *label;
    QLabel *label_2;
    QListView *listView_3;
    QVBoxLayout *verticalLayout_5;
    MyEditor *editorGutter;
    QWidget *widget_9;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QListView *listView_4;
    QLCDNumber *lcdNumber_2;
    QProgressBar *progressBar_2;
    QWidget *tab_4;
    QWidget *widget_7;
    QWidget *widget_8;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(598, 450);
        verticalLayout_6 = new QVBoxLayout(Form);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        widget_6 = new QWidget(Form);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setMinimumSize(QSize(0, 32));
        widget_6->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));

        verticalLayout_4->addWidget(widget_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        widget_4 = new QWidget(Form);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy);
        widget_4->setMinimumSize(QSize(100, 0));
        widget_4->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));
        label = new QLabel(widget_4);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 50, 31));
        label->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));
        label->setTextFormat(Qt::RichText);
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/welcome.png")));
        label->setScaledContents(true);
        label_2 = new QLabel(widget_4);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(6, 40, 91, 17));

        horizontalLayout_3->addWidget(widget_4);

        listView_3 = new QListView(Form);
        listView_3->setObjectName(QStringLiteral("listView_3"));
        sizePolicy.setHeightForWidth(listView_3->sizePolicy().hasHeightForWidth());
        listView_3->setSizePolicy(sizePolicy);
        listView_3->setMinimumSize(QSize(150, 0));
        listView_3->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_3->addWidget(listView_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        editorGutter = new MyEditor(Form);
        editorGutter->setObjectName(QStringLiteral("editorGutter"));

        verticalLayout_5->addWidget(editorGutter);

        widget_9 = new QWidget(Form);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        widget_9->setMinimumSize(QSize(0, 32));
        widget_9->setStyleSheet(QStringLiteral("background-color: rgb(186, 189, 182);"));

        verticalLayout_5->addWidget(widget_9);

        tabWidget_2 = new QTabWidget(Form);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget_2->sizePolicy().hasHeightForWidth());
        tabWidget_2->setSizePolicy(sizePolicy1);
        tabWidget_2->setMinimumSize(QSize(0, 150));
        tabWidget_2->setStyleSheet(QStringLiteral("background-color: rgb(114, 159, 207);"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tab_3->sizePolicy().hasHeightForWidth());
        tab_3->setSizePolicy(sizePolicy2);
        horizontalLayoutWidget_3 = new QWidget(tab_3);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(0, 0, 421, 122));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_4->setSpacing(1);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetMinAndMaxSize);
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        listView_4 = new QListView(horizontalLayoutWidget_3);
        listView_4->setObjectName(QStringLiteral("listView_4"));
        sizePolicy2.setHeightForWidth(listView_4->sizePolicy().hasHeightForWidth());
        listView_4->setSizePolicy(sizePolicy2);
        listView_4->setMinimumSize(QSize(0, 0));
        listView_4->setMaximumSize(QSize(16777215, 120));
        listView_4->setStyleSheet(QStringLiteral("background-color: rgb(238, 238, 236);"));

        horizontalLayout_4->addWidget(listView_4);

        lcdNumber_2 = new QLCDNumber(tab_3);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(430, 10, 151, 31));
        lcdNumber_2->setLayoutDirection(Qt::LeftToRight);
        lcdNumber_2->setStyleSheet(QStringLiteral("background-color: rgb(186, 189, 182);"));
        lcdNumber_2->setDigitCount(12);
        lcdNumber_2->setMode(QLCDNumber::Dec);
        lcdNumber_2->setProperty("value", QVariant(1e+8));
        lcdNumber_2->setProperty("intValue", QVariant(100000000));
        progressBar_2 = new QProgressBar(tab_3);
        progressBar_2->setObjectName(QStringLiteral("progressBar_2"));
        progressBar_2->setGeometry(QRect(430, 50, 151, 23));
        progressBar_2->setStyleSheet(QStringLiteral("background-color: rgb(238, 238, 236);"));
        progressBar_2->setValue(24);
        tabWidget_2->addTab(tab_3, QString());
        horizontalLayoutWidget_3->raise();
        lcdNumber_2->raise();
        progressBar_2->raise();
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tabWidget_2->addTab(tab_4, QString());

        verticalLayout_5->addWidget(tabWidget_2);


        horizontalLayout_3->addLayout(verticalLayout_5);

        widget_7 = new QWidget(Form);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget_7->sizePolicy().hasHeightForWidth());
        widget_7->setSizePolicy(sizePolicy3);
        widget_7->setMinimumSize(QSize(0, 0));
        widget_7->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));

        horizontalLayout_3->addWidget(widget_7);


        verticalLayout_4->addLayout(horizontalLayout_3);

        widget_8 = new QWidget(Form);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        sizePolicy3.setHeightForWidth(widget_8->sizePolicy().hasHeightForWidth());
        widget_8->setSizePolicy(sizePolicy3);
        widget_8->setMinimumSize(QSize(0, 32));
        widget_8->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));

        verticalLayout_4->addWidget(widget_8);


        verticalLayout_6->addLayout(verticalLayout_4);


        retranslateUi(Form);
        QObject::connect(Form, SIGNAL(resizeEvent(QResizeEvent)), Form, SLOT(resizeWidget()));

        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QApplication::translate("Form", "<html><head/><body><p><span style=\" font-weight:600; color:#d3d7cf;\">Willkommen</span></p></body></html>", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QApplication::translate("Form", "Tab 1", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("Form", "Tab 2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HAUPT_H
