// gamewindow.h

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QMediaPlayer>
#include <QAudioOutput> // <--- 新增：包含 QAudioOutput 的头文件
#include <QList>
#include "trie.h"
#include <QCompleter>
#include <QStringListModel>
#include <QElapsedTimer>
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
protected:
    void showEvent(QShowEvent *event) override; // 覆盖 QWidget 的 showEvent
private slots:
    void on_playButton_clicked();
    void on_answerLineEdit_textChanged(const QString &text);
    void on_answerLineEdit_returnPressed();
    void on_changeFolderButton_clicked();
    void on_changeDifficultyButton_clicked();
    void on_submitAnswerButton_clicked();
    void on_giveUpButton_clicked();
    void updateCountdown();
    void handleTimeUp();
private:

    void loadMusicFiles();
    void setInputControlsEnabled(bool enabled);
    void playNextSong();
    void parseSongName(const QString& fileName, QString& artist, QString& title);
    void displayCorrectAnswer(const QString& answer);
void generateShuffledPlaylist();
    Ui::gamewindow *ui;
    QString currentPlayingFile;
    QString musicDirectory;
    int gameDifficulty;
    QTimer *countdownTimer;       // <-- 新增：用于驱动进度条刷新的定时器
    QElapsedTimer *elapsedTimer;    // <-- 新增：用于精确计时的定时器
    const int countdownDuration = 20000; // <-- 新增：20秒，以毫秒为单位
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QList<int> shuffledPlaylist;
    int playlistPosition = 0;
    QStringList musicFiles;
    QStringList songTitles;
    QString currentCorrectAnswer;
    int currentSongIndex = -1;
    bool isFirstShow = true;
    Trie songTrie;
    QCompleter *completer;
    QStringListModel *completerModel;
};

#endif // GAMEWINDOW_H
