// gamewindow.h

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

// #include <QDialog>
#include <QWidget>
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

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void setGameSettings(const QString &path, int difficulty);
protected:
    void showEvent(QShowEvent *event) override; // 覆盖 QWidget 的 showEvent
private slots:
    void on_SkipButton_clicked();
    void on_playButton_clicked();
    void on_answerLineEdit_textChanged(const QString &text);
    void on_answerLineEdit_returnPressed();
    void on_changeFolderButton_clicked();
    void on_changeDifficultyButton_clicked();
    void on_submitAnswerButton_clicked();
    void on_giveUpButton_clicked();
    void updateCountdown();
    void handleTimeUp();
    void onDurationChanged(qint64 duration);
private:

    void loadMusicFiles();
    void setInputControlsEnabled(bool enabled);
    void playNextSong();
    void updateScore(int points);
    void parseSongName(const QString& fileName, QString& artist, QString& title);
    void displayCorrectAnswer(const QString& answer);
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

void generateShuffledPlaylist();
    Ui::gamewindow *ui;
    QString currentPlayingFile;
    QString musicDirectory;
    float gameDifficulty;
    QTimer *countdownTimer;
    QElapsedTimer *elapsedTimer;
    const int countdownDuration = 20000;
    QMediaPlayer *player;
    int m_score;
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
    qint64 m_currentSongDuration;
    QString m_lastSubmittedAnswer;
    qint64 randomStartTime;
    // int State = 0;//初始是正在播放
};

#endif // GAMEWINDOW_H
