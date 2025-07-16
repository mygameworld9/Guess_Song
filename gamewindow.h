// gamewindow.h

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QMediaPlayer>
#include <QAudioOutput> // <--- 新增：包含 QAudioOutput 的头文件

#include "trie.h"
#include <QCompleter>
#include <QStringListModel>

namespace Ui {
class gamewindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void setGameSettings(const QString &path, int difficulty);

private slots:
    void on_playButton_clicked();
    void on_answerLineEdit_textChanged(const QString &text);
    void on_answerLineEdit_returnPressed();
    void on_changeFolderButton_clicked();
    void on_changeDifficultyButton_clicked();
    void on_submitAnswerButton_clicked();
private:
    void loadMusicFiles();
    void playNextSong();
    void parseSongName(const QString& fileName, QString& artist, QString& title);

    Ui::gamewindow *ui;

    QString musicDirectory;
    int gameDifficulty;

    QMediaPlayer *player;           // 原有的播放器指针
    QAudioOutput *audioOutput;      // <--- 新增：音频输出设备指针

    QStringList musicFiles;
    QStringList songTitles;
    QString currentCorrectAnswer;
    int currentSongIndex = -1;

    Trie songTrie;
    QCompleter *completer;
    QStringListModel *completerModel;
};

#endif // GAMEWINDOW_H
