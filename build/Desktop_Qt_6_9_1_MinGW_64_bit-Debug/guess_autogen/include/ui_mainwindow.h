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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
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
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QComboBox *directoryModeComboBox;
    QComboBox *specificFolderComboBox;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *oneSecondRadioButton;
    QRadioButton *threeSecondsRadioButton;
    QRadioButton *fiveSecondsRadioButton;
    QRadioButton *fullSongRadioButton;
    QPushButton *startButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(339, 386);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(groupBox_2);
        label->setObjectName("label");

        verticalLayout_3->addWidget(label);

        directoryModeComboBox = new QComboBox(groupBox_2);
        directoryModeComboBox->addItem(QString());
        directoryModeComboBox->addItem(QString());
        directoryModeComboBox->setObjectName("directoryModeComboBox");
        directoryModeComboBox->setModelColumn(0);

        verticalLayout_3->addWidget(directoryModeComboBox);

        specificFolderComboBox = new QComboBox(groupBox_2);
        specificFolderComboBox->setObjectName("specificFolderComboBox");

        verticalLayout_3->addWidget(specificFolderComboBox);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
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


        verticalLayout->addWidget(groupBox);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 339, 21));
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
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\255\214\346\233\262\347\233\256\345\275\225", nullptr));
        directoryModeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\346\214\207\345\256\232Music\344\270\213\347\232\204\346\226\207\344\273\266\345\244\271", nullptr));
        directoryModeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Music\344\270\213\347\232\204\346\211\200\346\234\211\346\226\207\344\273\266\345\244\271", nullptr));

        groupBox->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\270\270\346\210\217\351\232\276\345\272\246", nullptr));
        oneSecondRadioButton->setText(QCoreApplication::translate("MainWindow", "\344\270\200\347\247\222", nullptr));
        threeSecondsRadioButton->setText(QCoreApplication::translate("MainWindow", "\344\270\211\347\247\222", nullptr));
        fiveSecondsRadioButton->setText(QCoreApplication::translate("MainWindow", "\344\272\224\347\247\222", nullptr));
        fullSongRadioButton->setText(QCoreApplication::translate("MainWindow", "\346\225\264\351\246\226\346\255\214", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
