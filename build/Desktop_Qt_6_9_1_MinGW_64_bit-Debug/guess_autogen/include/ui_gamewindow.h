/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gamewindow
{
public:
    QLabel *statusLabel;
    QPushButton *playButton;
    QLineEdit *answerLineEdit;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *changeFolderButton;
    QPushButton *changeDifficultyButton;
    QPushButton *submitAnswerButton;
    QPushButton *giveUpButton;
    QLabel *correctAnswerLabel;
    QProgressBar *countdownProgressBar;

    void setupUi(QWidget *gamewindow)
    {
        if (gamewindow->objectName().isEmpty())
            gamewindow->setObjectName("gamewindow");
        gamewindow->resize(400, 300);
        statusLabel = new QLabel(gamewindow);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setGeometry(QRect(70, 120, 261, 16));
        playButton = new QPushButton(gamewindow);
        playButton->setObjectName("playButton");
        playButton->setGeometry(QRect(110, 70, 101, 23));
        playButton->setIconSize(QSize(48, 48));
        answerLineEdit = new QLineEdit(gamewindow);
        answerLineEdit->setObjectName("answerLineEdit");
        answerLineEdit->setGeometry(QRect(90, 150, 113, 21));
        horizontalLayoutWidget = new QWidget(gamewindow);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(90, 210, 160, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        changeFolderButton = new QPushButton(horizontalLayoutWidget);
        changeFolderButton->setObjectName("changeFolderButton");

        horizontalLayout->addWidget(changeFolderButton);

        changeDifficultyButton = new QPushButton(horizontalLayoutWidget);
        changeDifficultyButton->setObjectName("changeDifficultyButton");

        horizontalLayout->addWidget(changeDifficultyButton);

        submitAnswerButton = new QPushButton(gamewindow);
        submitAnswerButton->setObjectName("submitAnswerButton");
        submitAnswerButton->setGeometry(QRect(220, 150, 75, 23));
        giveUpButton = new QPushButton(gamewindow);
        giveUpButton->setObjectName("giveUpButton");
        giveUpButton->setGeometry(QRect(310, 150, 75, 23));
        correctAnswerLabel = new QLabel(gamewindow);
        correctAnswerLabel->setObjectName("correctAnswerLabel");
        correctAnswerLabel->setGeometry(QRect(230, 120, 53, 15));
        countdownProgressBar = new QProgressBar(gamewindow);
        countdownProgressBar->setObjectName("countdownProgressBar");
        countdownProgressBar->setGeometry(QRect(90, 180, 118, 23));
        countdownProgressBar->setValue(24);

        retranslateUi(gamewindow);

        submitAnswerButton->setDefault(true);


        QMetaObject::connectSlotsByName(gamewindow);
    } // setupUi

    void retranslateUi(QWidget *gamewindow)
    {
        gamewindow->setWindowTitle(QCoreApplication::translate("gamewindow", "Form", nullptr));
        statusLabel->setText(QString());
        playButton->setText(QCoreApplication::translate("gamewindow", "\342\226\266\357\270\217 \346\222\255\346\224\276 / \351\207\215\345\244\215", nullptr));
        answerLineEdit->setPlaceholderText(QCoreApplication::translate("gamewindow", "\345\234\250\346\255\244\350\276\223\345\205\245\346\255\214\346\233\262\345\220\215\347\247\260", nullptr));
        changeFolderButton->setText(QCoreApplication::translate("gamewindow", "\346\233\264\346\224\271\347\233\256\345\275\225", nullptr));
        changeDifficultyButton->setText(QCoreApplication::translate("gamewindow", "\346\233\264\346\224\271\351\232\276\345\272\246", nullptr));
        submitAnswerButton->setText(QCoreApplication::translate("gamewindow", "\346\217\220\344\272\244\347\255\224\346\241\210", nullptr));
        giveUpButton->setText(QCoreApplication::translate("gamewindow", "\346\210\221\346\262\241\346\213\233\345\204\277\344\272\206", nullptr));
        correctAnswerLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class gamewindow: public Ui_gamewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
