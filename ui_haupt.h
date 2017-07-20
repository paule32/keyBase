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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
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
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_9;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer;
    QLabel *label_6;
    QLabel *label_5;
    QListView *listView_3;
    QVBoxLayout *verticalLayout_5;
    MyEditor *editorGutter;
    QWidget *widget_9;
    QTabWidget *tabWidget_2;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_3;
    QPlainTextEdit *dataEdit;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QListWidget *logWindow;
    QProgressBar *progressBar_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLCDNumber *lcdNumber_2;
    QWidget *widget_7;
    QWidget *widget_8;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(701, 658);
        Form->setStyleSheet(QStringLiteral("background-color: rgb(215, 230, 247);"));
        verticalLayout_6 = new QVBoxLayout(Form);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetFixedSize);
        widget_6 = new QWidget(Form);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setMinimumSize(QSize(0, 32));
        widget_6->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));

        verticalLayout_4->addWidget(widget_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
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
        verticalLayout_8 = new QVBoxLayout(widget_4);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        label = new QLabel(widget_4);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));
        label->setTextFormat(Qt::RichText);
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/welcome.png")));
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label);

        label_2 = new QLabel(widget_4);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_9->addItem(verticalSpacer_2);

        label_3 = new QLabel(widget_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));
        label_3->setFrameShape(QFrame::NoFrame);
        label_3->setTextFormat(Qt::RichText);
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/img/Help-and-Support-icon.png")));
        label_3->setScaledContents(false);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_3);

        label_4 = new QLabel(widget_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setStyleSheet(QStringLiteral("color: rgb(233, 185, 110);"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_3);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_9->addItem(verticalSpacer);

        label_6 = new QLabel(widget_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/img/Actions-go-next-view-page-icon.png")));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_6);

        label_5 = new QLabel(widget_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setStyleSheet(QStringLiteral("color: rgb(233, 185, 110);"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_5);


        verticalLayout_7->addLayout(verticalLayout_9);


        verticalLayout_8->addLayout(verticalLayout_7);


        horizontalLayout_3->addWidget(widget_4);

        listView_3 = new QListView(Form);
        listView_3->setObjectName(QStringLiteral("listView_3"));
        sizePolicy.setHeightForWidth(listView_3->sizePolicy().hasHeightForWidth());
        listView_3->setSizePolicy(sizePolicy);
        listView_3->setMinimumSize(QSize(150, 0));
        listView_3->setMaximumSize(QSize(150, 16777215));
        listView_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        listView_3->setIconSize(QSize(0, 0));

        horizontalLayout_3->addWidget(listView_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(2);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetFixedSize);
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
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget_2->sizePolicy().hasHeightForWidth());
        tabWidget_2->setSizePolicy(sizePolicy1);
        tabWidget_2->setMinimumSize(QSize(0, 150));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        tabWidget_2->setFont(font);
        tabWidget_2->setStyleSheet(QStringLiteral("background-color: rgb(114, 159, 207);"));
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        verticalLayout_10 = new QVBoxLayout(tab_4);
        verticalLayout_10->setSpacing(3);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(3, 3, 3, 3);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        dataEdit = new QPlainTextEdit(tab_4);
        dataEdit->setObjectName(QStringLiteral("dataEdit"));
        dataEdit->setStyleSheet(QStringLiteral("background-color: rgb(243, 243, 243);"));
        dataEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        dataEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        dataEdit->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        dataEdit->setBackgroundVisible(false);

        verticalLayout_3->addWidget(dataEdit);


        verticalLayout_10->addLayout(verticalLayout_3);

        tabWidget_2->addTab(tab_4, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        sizePolicy1.setHeightForWidth(tab_3->sizePolicy().hasHeightForWidth());
        tab_3->setSizePolicy(sizePolicy1);
        tab_3->setFont(font);
        verticalLayout_2 = new QVBoxLayout(tab_3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(1);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        logWindow = new QListWidget(tab_3);
        new QListWidgetItem(logWindow);
        logWindow->setObjectName(QStringLiteral("logWindow"));
        sizePolicy1.setHeightForWidth(logWindow->sizePolicy().hasHeightForWidth());
        logWindow->setSizePolicy(sizePolicy1);
        logWindow->setMinimumSize(QSize(0, 0));
        logWindow->setMaximumSize(QSize(16777215, 120));
        logWindow->setStyleSheet(QStringLiteral("background-color: rgb(238, 238, 236);"));
        logWindow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        logWindow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        horizontalLayout_4->addWidget(logWindow);


        verticalLayout_2->addLayout(horizontalLayout_4);

        progressBar_2 = new QProgressBar(tab_3);
        progressBar_2->setObjectName(QStringLiteral("progressBar_2"));
        progressBar_2->setStyleSheet(QStringLiteral("background-color: rgb(238, 238, 236);"));
        progressBar_2->setValue(24);

        verticalLayout_2->addWidget(progressBar_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lcdNumber_2 = new QLCDNumber(tab_3);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));
        lcdNumber_2->setMinimumSize(QSize(0, 25));
        lcdNumber_2->setLayoutDirection(Qt::LeftToRight);
        lcdNumber_2->setStyleSheet(QStringLiteral("background-color: rgb(186, 189, 182);"));
        lcdNumber_2->setDigitCount(12);
        lcdNumber_2->setMode(QLCDNumber::Dec);
        lcdNumber_2->setProperty("value", QVariant(1e+8));
        lcdNumber_2->setProperty("intValue", QVariant(100000000));

        horizontalLayout->addWidget(lcdNumber_2);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        tabWidget_2->addTab(tab_3, QString());

        verticalLayout_5->addWidget(tabWidget_2);


        horizontalLayout_3->addLayout(verticalLayout_5);

        widget_7 = new QWidget(Form);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        sizePolicy1.setHeightForWidth(widget_7->sizePolicy().hasHeightForWidth());
        widget_7->setSizePolicy(sizePolicy1);
        widget_7->setMinimumSize(QSize(0, 0));
        widget_7->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));

        horizontalLayout_3->addWidget(widget_7);


        verticalLayout_4->addLayout(horizontalLayout_3);

        widget_8 = new QWidget(Form);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        sizePolicy1.setHeightForWidth(widget_8->sizePolicy().hasHeightForWidth());
        widget_8->setSizePolicy(sizePolicy1);
        widget_8->setMinimumSize(QSize(0, 32));
        widget_8->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));

        verticalLayout_4->addWidget(widget_8);


        verticalLayout_6->addLayout(verticalLayout_4);


        retranslateUi(Form);

        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QApplication::translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600; color:#d3d7cf;\">Willkommen</span></p></body></html>", Q_NULLPTR));
        label_3->setText(QString());
        label_4->setText(QApplication::translate("Form", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Hilfe</span></p></body></html>", Q_NULLPTR));
        label_6->setText(QString());
        label_5->setText(QApplication::translate("Form", "<html><head/><body><p><span style=\" font-weight:600;\">Run App</span></p></body></html>", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("Form", "Data", Q_NULLPTR));

        const bool __sortingEnabled = logWindow->isSortingEnabled();
        logWindow->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = logWindow->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("Form", "Neues Element", Q_NULLPTR));
        logWindow->setSortingEnabled(__sortingEnabled);

        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QApplication::translate("Form", "Logging", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HAUPT_H
