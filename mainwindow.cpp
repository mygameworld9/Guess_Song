#include "mainwindow.h"
#include "ui_mainwindow.h" // 包含由 mainwindow.ui 生成的头文件

// 其他必要的 Qt 模块头文件
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QRandomGenerator>
#include <QTimer>
#include <QRegularExpression>
#include <QUrl>
#include <QDebug>
#include <QFile> // 用于 QFileDialog::getExistingDirectory 中 QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog


// =========================================================================
// Trie 类方法的实现
// =========================================================================
Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    delete root;
}

void Trie::insert(const QString& word) {
    TrieNode* current = root;
    for (QChar c : word) {
        if (!current->children.contains(c)) {
            current->children.insert(c, new TrieNode());
        }
        current = current->children[c];
    }
    current->isEndOfWord = true;
}

QList<QString> Trie::search(const QString& prefix) {
    QList<QString> result;
    TrieNode* current = root;

    for (QChar c : prefix) {
        if (!current->children.contains(c)) {
            return result;
        }
        current = current->children[c];
    }

    collectAllWords(current, prefix, result);
    return result;
}

void Trie::collectAllWords(TrieNode* node, QString currentPrefix, QList<QString>& result) {
    if (node->isEndOfWord) {
        result.append(currentPrefix);
    }

    for (QChar c : node->children.keys()) {
        collectAllWords(node->children[c], currentPrefix + c, result);
    }
}
// =========================================================================


// =========================================================================
// MainWindow 类方法的实现
// =========================================================================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_player = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_player->setAudioOutput(m_audioOutput);

    // ======================== 连接信号和槽 ========================
    connect(ui->playPauseButton, &QPushButton::clicked, this, &MainWindow::on_playPauseButton_clicked);
    connect(ui->repeatButton, &QPushButton::clicked, this, &MainWindow::on_repeatButton_clicked);
    connect(ui->startGameButton, &QPushButton::clicked, this, &MainWindow::on_startGameButton_clicked);
    // connect(ui->selectMusicFolderButton, &QPushButton::clicked, this, &MainWindow::on_selectMusicFolderButton_clicked);
    connect(ui->submitAnswerButton, &QPushButton::clicked, this, &MainWindow::on_submitAnswerButton_clicked);

    connect(ui->answerLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_answerLineEdit_textChanged);

    connect(m_player, &QMediaPlayer::playbackStateChanged, this, &MainWindow::onMediaPlayerPlaybackStateChanged);
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onMediaPlayerMediaStatusChanged);

    // ======================== 默认设置 ========================
    ui->durationFullRadioButton->setChecked(true);
    ui->allFoldersRadioButton->setChecked(true);
    ui->statusLabel->setText("请选择 Music 文件夹开始游戏。");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_player;
    delete m_audioOutput;
}

// =========================================================================
// 槽函数实现
// =========================================================================

void MainWindow::on_playPauseButton_clicked()
{
    if (m_player->source().isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择音乐并开始游戏！");
        return;
    }

    if (m_player->playbackState() == QMediaPlayer::PlayingState) {
        m_player->pause();
        ui->playPauseButton->setText("播放");
    } else {
        m_player->play();
        ui->playPauseButton->setText("暂停");
    }
}

void MainWindow::on_repeatButton_clicked()
{
    m_isRepeating = !m_isRepeating;

    if (m_isRepeating) {
        ui->repeatButton->setText("取消重复");
    } else {
        ui->repeatButton->setText("重复播放");
    }

    // 无论当前播放状态如何，都停止当前播放，然后从头开始播放当前歌曲
    // 强制从头开始播放当前歌曲，这会重置播放位置到0
    if (!m_player->source().isEmpty()) { // 确保有歌曲加载
        m_player->stop(); // 停止当前播放，这会重置播放位置
        m_player->play(); // 再次播放，将从头开始
        ui->playPauseButton->setText("暂停"); // 确保按钮显示“暂停”
    } else {
        QMessageBox::warning(this, "提示", "没有歌曲正在播放！");
    }
}

void MainWindow::on_startGameButton_clicked()
{
    if (m_allSongs.isEmpty()) {
        QMessageBox::warning(this, "错误", "请先选择 Music 文件夹并扫描音乐。");
        return;
    }

    int randomIndex = QRandomGenerator::global()->bounded(m_allSongs.size());
    const SongInfo& selectedSong = m_allSongs.at(randomIndex);
    m_currentSongPath = selectedSong.filePath;
    m_correctSongTitle = selectedSong.title;

    m_player->setSource(QUrl::fromLocalFile(m_currentSongPath));
    m_player->stop();
    m_audioOutput->setVolume(1.0);

    m_player->play();
    ui->playPauseButton->setText("暂停");
    ui->statusLabel->setText("歌曲已播放，请猜歌名！");
    ui->answerLineEdit->clear();
    ui->hintListWidget->clear();

    qint64 durationMs = 0;
    if (ui->duration1sRadioButton->isChecked()) {
        durationMs = 1000;
    } else if (ui->duration3sRadioButton->isChecked()) {
        durationMs = 3000;
    } else if (ui->duration5sRadioButton->isChecked()) {
        durationMs = 5000;
    } else {
        durationMs = -1;
    }

    if (durationMs > 0) {
        QTimer::singleShot(durationMs, this, [this]() {
            if (m_player->playbackState() == QMediaPlayer::PlayingState) {
                m_player->pause();
                ui->playPauseButton->setText("播放");
                ui->statusLabel->setText("播放结束，请输入答案。");
            }
        });
    }
}

void MainWindow::on_selectMusicFolderButton_clicked()
{
    // 强制使用 Qt 的非原生对话框，解决可能存在的崩溃问题
    QString musicFolderPath = QFileDialog::getExistingDirectory(
        this,
        tr("选择 Music 文件夹"),
        QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog
        );

    if (!musicFolderPath.isEmpty()) {
        m_allSongs.clear();
        m_titleTrie = Trie(); // 重置字典树

        ui->statusLabel->setText("正在扫描音乐文件...");
        if (ui->specificFolderRadioButton->isChecked()) {
            scanMusicFolderRecursive(musicFolderPath); // 只扫描指定文件夹，尽管递归函数会处理
        } else {
            scanMusicFolderRecursive(musicFolderPath); // 递归扫描所有子文件夹
        }

        for (const SongInfo& song : m_allSongs) {
            m_titleTrie.insert(song.title.toLower());
        }

        ui->statusLabel->setText(QString("扫描完成，找到 %1 首歌曲。").arg(m_allSongs.size()));
        if (m_allSongs.isEmpty()) {
            QMessageBox::warning(this, "提示", "在选定的文件夹中未找到支持的音乐文件 (.mp3, .wav, .flac)。");
        }
    } else {
        ui->statusLabel->setText("未选择 Music 文件夹。");
    }
}

void MainWindow::on_submitAnswerButton_clicked()
{
    if (m_correctSongTitle.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先开始游戏，播放一首歌曲。");
        return;
    }

    QString userAnswer = ui->answerLineEdit->text().trimmed();
    userAnswer = userAnswer.replace(QRegularExpression("\\s+"), " ");

    if (userAnswer.toLower() == m_correctSongTitle.toLower()) {
        ui->statusLabel->setText("恭喜你，回答正确！");
        m_player->stop();
        ui->playPauseButton->setText("播放");
    } else {
        ui->statusLabel->setText(QString("回答错误，正确答案是: %1").arg(m_correctSongTitle));
    }
    ui->hintListWidget->clear();
}

void MainWindow::on_answerLineEdit_textChanged(const QString& text)
{
    ui->hintListWidget->clear();

    if (text.isEmpty()) {
        return;
    }

    QList<QString> hints = m_titleTrie.search(text.toLower());

    for (const QString& hint : hints) {
        ui->hintListWidget->addItem(hint);
    }
}

void MainWindow::onMediaPlayerPlaybackStateChanged(QMediaPlayer::PlaybackState state)
{
    if (state == QMediaPlayer::StoppedState) {
        ui->playPauseButton->setText("播放");
    } else if (state == QMediaPlayer::PlayingState) {
        ui->playPauseButton->setText("暂停");
    } else if (state == QMediaPlayer::PausedState) {
        ui->playPauseButton->setText("播放");
    }
}

void MainWindow::onMediaPlayerMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        if (m_isRepeating) {
            m_player->play();
        } else {
            ui->statusLabel->setText("歌曲播放结束。");
        }
    } else if (status == QMediaPlayer::InvalidMedia) {
        ui->statusLabel->setText("错误：无法播放此媒体文件。请检查文件格式或路径。");
        qDebug() << "QMediaPlayer Error:" << m_player->errorString();
        m_player->stop();
        ui->playPauseButton->setText("播放");
    } else if (status == QMediaPlayer::LoadingMedia) {
        ui->statusLabel->setText("正在加载媒体...");
    } else if (status == QMediaPlayer::LoadedMedia) {
        qDebug() << "Media loaded successfully.";
    }
}

// =========================================================================
// 辅助函数实现
// =========================================================================

void MainWindow::scanMusicFolderRecursive(const QString& folderPath)
{
    QDir directory(folderPath);
    QStringList filters;
    filters << "*.mp3" << "*.wav" << "*.flac";

    QFileInfoList fileList = directory.entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);
    for (const QFileInfo& fileInfo : fileList) {
        m_allSongs.append(parseFileName(fileInfo.absoluteFilePath()));
    }

    // 只有在 "所有文件夹" 模式下才递归扫描子目录
    // 在 "指定文件夹" 模式下，虽然也调用了此函数，但不会进一步递归
    if (ui->allFoldersRadioButton->isChecked()) { // 检查UI状态来决定是否递归
        QFileInfoList dirList = directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
        for (const QFileInfo& dirInfo : dirList) {
            scanMusicFolderRecursive(dirInfo.absoluteFilePath());
        }
    }
}

SongInfo MainWindow::parseFileName(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    QString baseName = fileInfo.baseName();

    baseName = baseName.trimmed();
    baseName = baseName.replace(QRegularExpression("\\s+"), " ");

    QString artist;
    QString title;

    int lastDashIndex = baseName.lastIndexOf('-');
    if (lastDashIndex != -1) {
        artist = baseName.left(lastDashIndex).trimmed();
        title = baseName.mid(lastDashIndex + 1).trimmed();
    } else {
        title = baseName;
    }

    return SongInfo(filePath, artist, title);
}
