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
#include <QtGui/QAction>
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
    QAction *actionSkip;
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
    QLabel *scoreLabel;
    QPushButton *SkipButton;
    QPushButton *StopButton;

    void setupUi(QWidget *gamewindow)
    {
        if (gamewindow->objectName().isEmpty())
            gamewindow->setObjectName("gamewindow");
        gamewindow->resize(400, 300);
        actionSkip = new QAction(gamewindow);
        actionSkip->setObjectName("actionSkip");
        actionSkip->setCheckable(true);
        actionSkip->setChecked(false);
        actionSkip->setEnabled(true);
        actionSkip->setShortcutContext(Qt::ShortcutContext::ApplicationShortcut);
        actionSkip->setMenuRole(QAction::MenuRole::NoRole);
        actionSkip->setShortcutVisibleInContextMenu(true);
        statusLabel = new QLabel(gamewindow);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setGeometry(QRect(60, 100, 261, 16));
        playButton = new QPushButton(gamewindow);
        playButton->setObjectName("playButton");
        playButton->setGeometry(QRect(100, 60, 101, 23));
        playButton->setIconSize(QSize(48, 48));
        answerLineEdit = new QLineEdit(gamewindow);
        answerLineEdit->setObjectName("answerLineEdit");
        answerLineEdit->setGeometry(QRect(60, 130, 113, 21));
        horizontalLayoutWidget = new QWidget(gamewindow);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(80, 190, 160, 80));
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
        submitAnswerButton->setGeometry(QRect(190, 130, 75, 23));
        giveUpButton = new QPushButton(gamewindow);
        giveUpButton->setObjectName("giveUpButton");
        giveUpButton->setGeometry(QRect(280, 130, 75, 23));
        correctAnswerLabel = new QLabel(gamewindow);
        correctAnswerLabel->setObjectName("correctAnswerLabel");
        correctAnswerLabel->setGeometry(QRect(90, 100, 221, 16));
        countdownProgressBar = new QProgressBar(gamewindow);
        countdownProgressBar->setObjectName("countdownProgressBar");
        countdownProgressBar->setGeometry(QRect(60, 160, 291, 23));
        countdownProgressBar->setValue(24);
        scoreLabel = new QLabel(gamewindow);
        scoreLabel->setObjectName("scoreLabel");
        scoreLabel->setGeometry(QRect(290, 10, 53, 15));
        SkipButton = new QPushButton(gamewindow);
        SkipButton->setObjectName("SkipButton");
        SkipButton->setGeometry(QRect(220, 60, 75, 23));
        SkipButton->setCheckable(false);
        StopButton = new QPushButton(gamewindow);
        StopButton->setObjectName("StopButton");
        StopButton->setGeometry(QRect(250, 220, 75, 23));

        retranslateUi(gamewindow);

        submitAnswerButton->setDefault(true);


        QMetaObject::connectSlotsByName(gamewindow);
    } // setupUi

    void retranslateUi(QWidget *gamewindow)
    {
        gamewindow->setWindowTitle(QCoreApplication::translate("gamewindow", "Form", nullptr));
        actionSkip->setText(QCoreApplication::translate("gamewindow", "\344\270\213\344\270\200\351\246\226", nullptr));
#if QT_CONFIG(tooltip)
        actionSkip->setToolTip(QCoreApplication::translate("gamewindow", "Alt+Right \350\267\263\350\277\207\350\277\231\351\246\226\346\255\214", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSkip->setShortcut(QCoreApplication::translate("gamewindow", "Ctrl+B", nullptr));
#endif // QT_CONFIG(shortcut)
        statusLabel->setText(QString());
        playButton->setText(QCoreApplication::translate("gamewindow", "\342\226\266\357\270\217 \346\222\255\346\224\276 / \351\207\215\345\244\215", nullptr));
        answerLineEdit->setPlaceholderText(QCoreApplication::translate("gamewindow", "\345\234\250\346\255\244\350\276\223\345\205\245\346\255\214\346\233\262\345\220\215\347\247\260", nullptr));
        changeFolderButton->setText(QCoreApplication::translate("gamewindow", "\346\233\264\346\224\271\347\233\256\345\275\225", nullptr));
        changeDifficultyButton->setText(QCoreApplication::translate("gamewindow", "\346\233\264\346\224\271\351\232\276\345\272\246", nullptr));
        submitAnswerButton->setText(QCoreApplication::translate("gamewindow", "\346\217\220\344\272\244\347\255\224\346\241\210", nullptr));
        giveUpButton->setText(QCoreApplication::translate("gamewindow", "\346\210\221\346\262\241\346\213\233\345\204\277\344\272\206", nullptr));
        correctAnswerLabel->setText(QString());
        scoreLabel->setText(QCoreApplication::translate("gamewindow", "\345\275\223\345\211\215\346\210\220\347\273\251\357\274\232", nullptr));
        SkipButton->setText(QCoreApplication::translate("gamewindow", "\350\267\263\350\277\207", nullptr));
        StopButton->setText(QCoreApplication::translate("gamewindow", "\346\232\202\345\201\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gamewindow: public Ui_gamewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
