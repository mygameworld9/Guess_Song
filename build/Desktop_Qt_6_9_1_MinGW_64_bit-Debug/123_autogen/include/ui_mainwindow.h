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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *playPauseButton;
    QPushButton *repeatButton;
    QLabel *label;
    QGroupBox *groupBox;
    QPushButton *selectMusicFolderButton;
    QPushButton *startGameButton;
    QRadioButton *specificFolderRadioButton;
    QRadioButton *allFoldersRadioButton;
    QLabel *statusLabel;
    QLineEdit *answerLineEdit;
    QPushButton *submitAnswerButton;
    QGroupBox *groupBox_2;
    QRadioButton *duration1sRadioButton;
    QRadioButton *duration3sRadioButton;
    QRadioButton *duration5sRadioButton;
    QRadioButton *durationFullRadioButton;
    QListWidget *hintListWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        playPauseButton = new QPushButton(centralwidget);
        playPauseButton->setObjectName("playPauseButton");
        playPauseButton->setGeometry(QRect(470, 150, 75, 23));
        repeatButton = new QPushButton(centralwidget);
        repeatButton->setObjectName("repeatButton");
        repeatButton->setGeometry(QRect(270, 150, 75, 23));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(270, 180, 111, 16));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(70, 10, 571, 21));
        selectMusicFolderButton = new QPushButton(groupBox);
        selectMusicFolderButton->setObjectName("selectMusicFolderButton");
        selectMusicFolderButton->setGeometry(QRect(80, 0, 131, 23));
        startGameButton = new QPushButton(groupBox);
        startGameButton->setObjectName("startGameButton");
        startGameButton->setGeometry(QRect(220, 0, 111, 23));
        specificFolderRadioButton = new QRadioButton(groupBox);
        specificFolderRadioButton->setObjectName("specificFolderRadioButton");
        specificFolderRadioButton->setGeometry(QRect(340, 0, 95, 19));
        allFoldersRadioButton = new QRadioButton(groupBox);
        allFoldersRadioButton->setObjectName("allFoldersRadioButton");
        allFoldersRadioButton->setGeometry(QRect(460, 0, 95, 19));
        allFoldersRadioButton->setChecked(true);
        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setGeometry(QRect(350, 220, 53, 15));
        answerLineEdit = new QLineEdit(centralwidget);
        answerLineEdit->setObjectName("answerLineEdit");
        answerLineEdit->setGeometry(QRect(350, 180, 113, 21));
        submitAnswerButton = new QPushButton(centralwidget);
        submitAnswerButton->setObjectName("submitAnswerButton");
        submitAnswerButton->setGeometry(QRect(470, 180, 75, 23));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(60, 50, 591, 80));
        duration1sRadioButton = new QRadioButton(groupBox_2);
        duration1sRadioButton->setObjectName("duration1sRadioButton");
        duration1sRadioButton->setGeometry(QRect(110, 20, 95, 19));
        duration3sRadioButton = new QRadioButton(groupBox_2);
        duration3sRadioButton->setObjectName("duration3sRadioButton");
        duration3sRadioButton->setGeometry(QRect(200, 20, 95, 19));
        duration5sRadioButton = new QRadioButton(groupBox_2);
        duration5sRadioButton->setObjectName("duration5sRadioButton");
        duration5sRadioButton->setGeometry(QRect(290, 20, 95, 19));
        durationFullRadioButton = new QRadioButton(groupBox_2);
        durationFullRadioButton->setObjectName("durationFullRadioButton");
        durationFullRadioButton->setGeometry(QRect(380, 20, 95, 19));
        durationFullRadioButton->setChecked(true);
        hintListWidget = new QListWidget(centralwidget);
        hintListWidget->setObjectName("hintListWidget");
        hintListWidget->setGeometry(QRect(370, 150, 81, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
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
        playPauseButton->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276/\346\232\202\345\201\234", nullptr));
        repeatButton->setText(QCoreApplication::translate("MainWindow", "\351\207\215\345\244\215\346\222\255\346\224\276", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\346\255\214\346\233\262\345\220\215:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\270\270\346\210\217\346\250\241\345\274\217", nullptr));
        selectMusicFolderButton->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251 Music \346\226\207\344\273\266\345\244\271", nullptr));
        startGameButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217 / \344\270\213\344\270\200\351\246\226", nullptr));
        specificFolderRadioButton->setText(QCoreApplication::translate("MainWindow", "\346\214\207\345\256\232\346\226\207\344\273\266\345\244\271", nullptr));
        allFoldersRadioButton->setText(QCoreApplication::translate("MainWindow", "\346\211\200\346\234\211\346\226\207\344\273\266\345\244\271", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\345\276\227\345\210\206\357\274\232", nullptr));
        submitAnswerButton->setText(QCoreApplication::translate("MainWindow", "\346\217\220\344\272\244", nullptr));
        groupBox_2->setTitle(QString());
        duration1sRadioButton->setText(QCoreApplication::translate("MainWindow", "\344\270\200\347\247\222", nullptr));
        duration3sRadioButton->setText(QCoreApplication::translate("MainWindow", "\344\270\211\347\247\222", nullptr));
        duration5sRadioButton->setText(QCoreApplication::translate("MainWindow", "\344\272\224\347\247\222", nullptr));
        durationFullRadioButton->setText(QCoreApplication::translate("MainWindow", "\346\225\264\351\246\226\346\255\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
