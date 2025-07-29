/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *oneSecondRadioButton;
    QRadioButton *threeSecondsRadioButton;
    QRadioButton *fiveSecondsRadioButton;
    QRadioButton *fullSongRadioButton;
    QPushButton *startButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QListWidget *folderListWidget;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *selectAllButton;
    QPushButton *deselectAllButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(365, 429);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 320, 321, 66));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        oneSecondRadioButton = new QRadioButton(groupBox);
        oneSecondRadioButton->setObjectName("oneSecondRadioButton");

        horizontalLayout->addWidget(oneSecondRadioButton);

        threeSecondsRadioButton = new QRadioButton(groupBox);
        threeSecondsRadioButton->setObjectName("threeSecondsRadioButton");

        horizontalLayout->addWidget(threeSecondsRadioButton);

        fiveSecondsRadioButton = new QRadioButton(groupBox);
        fiveSecondsRadioButton->setObjectName("fiveSecondsRadioButton");

        horizontalLayout->addWidget(fiveSecondsRadioButton);

        fullSongRadioButton = new QRadioButton(groupBox);
        fullSongRadioButton->setObjectName("fullSongRadioButton");
        fullSongRadioButton->setChecked(true);

        horizontalLayout->addWidget(fullSongRadioButton);

        startButton = new QPushButton(groupBox);
        startButton->setObjectName("startButton");

        horizontalLayout->addWidget(startButton);


        verticalLayout_2->addLayout(horizontalLayout);

        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(60, 10, 258, 279));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        verticalLayout_3->addWidget(label);

        folderListWidget = new QListWidget(layoutWidget);
        folderListWidget->setObjectName("folderListWidget");

        verticalLayout_3->addWidget(folderListWidget);

        groupBox_3 = new QGroupBox(layoutWidget);
        groupBox_3->setObjectName("groupBox_3");
        horizontalLayout_2 = new QHBoxLayout(groupBox_3);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        selectAllButton = new QPushButton(groupBox_3);
        selectAllButton->setObjectName("selectAllButton");

        horizontalLayout_2->addWidget(selectAllButton);

        deselectAllButton = new QPushButton(groupBox_3);
        deselectAllButton->setObjectName("deselectAllButton");

        horizontalLayout_2->addWidget(deselectAllButton);


        verticalLayout_3->addWidget(groupBox_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 365, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\270\270\346\210\217\351\232\276\345\272\246", nullptr));
        oneSecondRadioButton->setText(QCoreApplication::translate("MainWindow", "\344\270\200\347\247\222", nullptr));
        threeSecondsRadioButton->setText(QCoreApplication::translate("MainWindow", "\344\270\211\347\247\222", nullptr));
        fiveSecondsRadioButton->setText(QCoreApplication::translate("MainWindow", "\344\272\224\347\247\222", nullptr));
        fullSongRadioButton->setText(QCoreApplication::translate("MainWindow", "\346\225\264\351\246\226\346\255\214", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\255\214\346\233\262\347\233\256\345\275\225", nullptr));
        groupBox_3->setTitle(QString());
        selectAllButton->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\200\211", nullptr));
        deselectAllButton->setText(QCoreApplication::translate("MainWindow", "\345\205\250\344\270\215\351\200\211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
