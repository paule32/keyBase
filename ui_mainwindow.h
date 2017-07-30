/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <haupt.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionObjekte_im_Bild;
    QAction *actionLetzten_Schritt_R_ckg_ngig_machen;
    QAction *action_ber_Qt;
    QAction *action3D_Welt;
    QAction *actionBeenden;
    QAction *action2D_Welt;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    Form *formWindow;
    QMenuBar *menubar;
    QMenu *menuDatei;
    QMenu *menuErkennung;
    QMenu *menuBearbeiten;
    QMenu *menuHilfe;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(574, 461);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionObjekte_im_Bild = new QAction(MainWindow);
        actionObjekte_im_Bild->setObjectName(QStringLiteral("actionObjekte_im_Bild"));
        actionLetzten_Schritt_R_ckg_ngig_machen = new QAction(MainWindow);
        actionLetzten_Schritt_R_ckg_ngig_machen->setObjectName(QStringLiteral("actionLetzten_Schritt_R_ckg_ngig_machen"));
        action_ber_Qt = new QAction(MainWindow);
        action_ber_Qt->setObjectName(QStringLiteral("action_ber_Qt"));
        action3D_Welt = new QAction(MainWindow);
        action3D_Welt->setObjectName(QStringLiteral("action3D_Welt"));
        actionBeenden = new QAction(MainWindow);
        actionBeenden->setObjectName(QStringLiteral("actionBeenden"));
        action2D_Welt = new QAction(MainWindow);
        action2D_Welt->setObjectName(QStringLiteral("action2D_Welt"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        formWindow = new Form(centralwidget);
        formWindow->setObjectName(QStringLiteral("formWindow"));

        verticalLayout->addWidget(formWindow);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 574, 22));
        menubar->setNativeMenuBar(true);
        menuDatei = new QMenu(menubar);
        menuDatei->setObjectName(QStringLiteral("menuDatei"));
        menuDatei->setTearOffEnabled(false);
        menuErkennung = new QMenu(menubar);
        menuErkennung->setObjectName(QStringLiteral("menuErkennung"));
        menuBearbeiten = new QMenu(menubar);
        menuBearbeiten->setObjectName(QStringLiteral("menuBearbeiten"));
        menuHilfe = new QMenu(menubar);
        menuHilfe->setObjectName(QStringLiteral("menuHilfe"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuDatei->menuAction());
        menubar->addAction(menuBearbeiten->menuAction());
        menubar->addAction(menuErkennung->menuAction());
        menubar->addAction(menuHilfe->menuAction());
        menuDatei->addAction(actionBeenden);
        menuErkennung->addAction(actionObjekte_im_Bild);
        menuErkennung->addAction(action3D_Welt);
        menuErkennung->addAction(action2D_Welt);
        menuBearbeiten->addAction(actionLetzten_Schritt_R_ckg_ngig_machen);
        menuHilfe->addAction(action_ber_Qt);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "KI Testumgebung (c) 2017 - de.sci.informatik.ki", Q_NULLPTR));
        actionObjekte_im_Bild->setText(QApplication::translate("MainWindow", "Objekte im Bild", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionObjekte_im_Bild->setToolTip(QApplication::translate("MainWindow", "Objekte im Bild erkennen ...", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionLetzten_Schritt_R_ckg_ngig_machen->setText(QApplication::translate("MainWindow", "Letzten Schritt R\303\274ckg\303\244ngig machen", Q_NULLPTR));
        action_ber_Qt->setText(QApplication::translate("MainWindow", "\303\234ber Qt ...", Q_NULLPTR));
        action3D_Welt->setText(QApplication::translate("MainWindow", "3D Welt", Q_NULLPTR));
        actionBeenden->setText(QApplication::translate("MainWindow", "Beenden", Q_NULLPTR));
        actionBeenden->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", Q_NULLPTR));
        action2D_Welt->setText(QApplication::translate("MainWindow", "2D Welt", Q_NULLPTR));
        menuDatei->setTitle(QApplication::translate("MainWindow", "Datei", Q_NULLPTR));
        menuErkennung->setTitle(QApplication::translate("MainWindow", "Erkennung", Q_NULLPTR));
        menuBearbeiten->setTitle(QApplication::translate("MainWindow", "Bearbeiten", Q_NULLPTR));
        menuHilfe->setTitle(QApplication::translate("MainWindow", "Hilfe", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
