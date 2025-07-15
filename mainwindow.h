#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QList>
#include <QString>
#include <QMap> // 用于 TrieNode 中的 QMap

// ======================== Trie 结构和类定义 ========================
// 为了简化，Trie 的定义和实现暂时都放在这里。
// 在大型项目中，Trie 通常会放在独立的 .h 和 .cpp 文件中。
struct TrieNode {
    QMap<QChar, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}

    ~TrieNode() {
        qDeleteAll(children); // 释放 QMap 中存储的指针指向的对象
    }
};

class Trie {
public:
    Trie();
    ~Trie();

    void insert(const QString& word);
    QList<QString> search(const QString& prefix);

private:
    TrieNode* root;

    void collectAllWords(TrieNode* node, QString currentPrefix, QList<QString>& result);
};
// =========================================================================

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// ==================== SongInfo 结构体定义 ====================
// 确保它在 MainWindow 类定义之前
struct SongInfo {
    QString filePath;
    QString artist;
    QString title;
    SongInfo(const QString& path, const QString& art, const QString& tit)
        : filePath(path), artist(art), title(tit) {}
};
// ==============================================================

class MainWindow : public QMainWindow
{
    Q_OBJECT // 这一行至关重要，必须存在

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // UI 控件相关的槽函数
    void on_playPauseButton_clicked();
    void on_repeatButton_clicked();
    void on_startGameButton_clicked();
    void on_selectMusicFolderButton_clicked();
    void on_submitAnswerButton_clicked();
    void on_answerLineEdit_textChanged(const QString& text);

    // QMediaPlayer 状态相关的槽函数 (Qt6 API)
    void onMediaPlayerPlaybackStateChanged(QMediaPlayer::PlaybackState state);
    void onMediaPlayerMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    Ui::MainWindow *ui;

    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;

    bool m_isRepeating = false;
    QString m_currentSongPath;
    QString m_correctSongTitle;

    QList<SongInfo> m_allSongs;
    Trie m_titleTrie;

    // 辅助函数
    void scanMusicFolderRecursive(const QString& folderPath);
    SongInfo parseFileName(const QString& filePath);
};
#endif // MAINWINDOW_H
