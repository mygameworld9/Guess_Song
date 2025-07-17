// gamewindow.cpp
#include "ui_gamewindow.h"
#include <QDebug>
#include <QDirIterator>
#include <QRandomGenerator>
#include <QTimer>
#include <QMessageBox>
#include <QStringListModel>
#include "gamewindow.h"
#include <algorithm>
GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gamewindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);

    audioOutput = new QAudioOutput(this);

    player->setAudioOutput(audioOutput);
    // 初始化自动补全功能
    countdownTimer = new QTimer(this);
    elapsedTimer = new QElapsedTimer();
    connect(countdownTimer, &QTimer::timeout, this, &GameWindow::updateCountdown);

    completer = new QCompleter(this);
    completerModel = new QStringListModel(this);
    completer->setModel(completerModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive); // 设置不区分大小写
    completer->setFilterMode(Qt::MatchContains);

    connect(ui->giveUpButton, &QPushButton::clicked, this, &GameWindow::on_giveUpButton_clicked);
    ui->answerLineEdit->setCompleter(completer);       // 将补全应用到输入框
    ui->countdownProgressBar->setVisible(false);
    ui->countdownProgressBar->setRange(0, 100);
    ui->countdownProgressBar->setValue(100); // 初始值设为满
    m_score = 0;
    ui->scoreLabel->setText(QString("分数: %1").arg(m_score));

}
GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::setGameSettings(const QString &path, int difficulty)
{
    // 将传递过来的数据存储到成员变量中
    this->musicDirectory = path;
    this->gameDifficulty = difficulty;


    QString difficultyText = (difficulty == 0) ? "整首歌" : QString("%1秒").arg(difficulty);
    this->setWindowTitle(QString("游戏进行中 - %1").arg(difficultyText));

    qDebug() << "游戏窗口已加载设置:";
    qDebug() << "歌曲目录:" << this->musicDirectory;
    qDebug() << "游戏难度:" << difficultyText;

    loadMusicFiles();
}
void GameWindow::loadMusicFiles()
{
    musicFiles.clear();
    songTitles.clear();

    QDirIterator it(musicDirectory, {"*.mp3", "*.flac", "*.wav", "*.m4a"}, QDir::Files, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QString filePath = it.next();
        musicFiles.append(filePath);

        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.baseName(); // 获取不带后缀的文件名

        QString artist, title;
        parseSongName(fileName, artist, title); // 解析歌名

        // 如果有歌手，答案就是 "歌手 - 歌名"
        // 英文歌名统一转为小写以忽略大小写
        // QString answer = title.toLower();
        songTitles.append(title);
        // songTitles.append(answer); // 将处理后的歌名存入列表
    }
    for(const QString& title : songTitles) {
        songTrie.insert(title.toLower()); // 插入小写版本用于匹配
    }
    completerModel->setStringList(songTitles);
    // if (musicFiles.isEmpty()) {
    // QMessageBox::warning(this, "错误", "所选目录中未找到任何支持的音乐文件！\n请检查目录或更换目录。");
    // ui->playButton->setEnabled(false); // 禁用播放按钮
    // } else {
    qDebug() << "成功加载" << musicFiles.count() << "首歌曲。";
    // }
    generateShuffledPlaylist(); //开始生成播放列表

}
void GameWindow::parseSongName(const QString& fileName, QString& artist, QString& title)
{
    QString cleanedName = fileName.trimmed(); // 去除首尾空格
    int separatorIndex = cleanedName.indexOf(" - ");

    if (separatorIndex != -1) {
        artist = cleanedName.left(separatorIndex).trimmed();
        title = cleanedName.mid(separatorIndex + 3).trimmed();
    } else {
        artist = ""; // 没有找到分隔符，则歌手为空
        title = cleanedName;
    }
}
void GameWindow::on_playButton_clicked()
{
    // 如果当前有歌曲正在播放（意味着用户想重复听），则重新播放
    if (player->playbackState() == QMediaPlayer::PlayingState || currentSongIndex != -1) {
        player->stop(); // 先停止
        player->setPosition(0); // 将播放位置重置到开头
        player->play(); // 播放
    } else {
        // 否则，播放一首新歌
        playNextSong();
    }
    if (gameDifficulty > 0) {
        // 使用 QTimer::singleShot 可以创建一个只触发一次的定时器
        // 它会在指定毫秒数后执行一个 lambda 函数
        QTimer::singleShot(gameDifficulty * 1000, this, [this]() {
            if (player->source() == QUrl::fromLocalFile(musicFiles[currentSongIndex])) {
                player->stop();
                qDebug() << "播放停止（" << gameDifficulty << "秒）。";
            }
        });
    }
}
void GameWindow::playNextSong()
{

    setInputControlsEnabled(true);
    countdownTimer->stop(); // 先停止上一次的计时器
    if (musicFiles.isEmpty()) return;
    if (playlistPosition >= shuffledPlaylist.size()) {
        QMessageBox::information(this, "提示", "所有歌曲均已播放完毕！\n即将开始新一轮随机播放。");
        // 重新生成一个新的、完全不同的随机播放列表
        generateShuffledPlaylist();
    }
    // 随机选择一首歌
    currentSongIndex = shuffledPlaylist[playlistPosition];
    currentCorrectAnswer = songTitles[currentSongIndex];
    // QFileInfo fileInfo(musicFiles[currentSongIndex]);
    // QString fileName = fileInfo.baseName();
    // QString artist, title;
    // parseSongName(fileName, artist, title);
    // currentCorrectAnswer = title; // 直接存储原始大小写的正确歌名

    // 清空上一轮的答案并重置状态
    ui->answerLineEdit->clear();
    ui->statusLabel->setText("请听题...");
    if (gameDifficulty > 0) { // 难度不为“整首歌”
        ui->countdownProgressBar->setVisible(true); // 显示进度条
        ui->countdownProgressBar->setValue(100);    // 重置为满格
        elapsedTimer->start();                      // 开始计时
        countdownTimer->start(100);                 // 每100毫秒刷新一次
    } else {
        ui->countdownProgressBar->setVisible(false); // “整首歌”难度则隐藏
    }
    qDebug() << "当前播放: " << musicFiles[currentSongIndex];
    qDebug() << "正确答案是: " << currentCorrectAnswer;
    player->stop();
    player->setSource(QUrl::fromLocalFile(musicFiles[currentSongIndex]));
    player->play();
    ui->answerLineEdit->setFocus();
    // 根据难度设置定时停止
    // 难度为 0 代表整首歌，不需要定时器
    if (gameDifficulty > 0) {
        // 使用 QTimer::singleShot 可以创建一个只触发一次的定时器
        // 它会在指定毫秒数后执行一个 lambda 函数
        QTimer::singleShot(gameDifficulty * 1000, this, [this]() {
            if (player->source() == QUrl::fromLocalFile(musicFiles[currentSongIndex])) {
                player->stop();
                qDebug() << "播放停止（" << gameDifficulty << "秒）。";
            }
        });
    }
    playlistPosition++;
}
void GameWindow::on_answerLineEdit_textChanged(const QString &text)
{

    // QVector<QString> suggestions = songTrie.suggest(text.toLower());
    // completerModel->setStringList(QList<QString>::fromVector(suggestions));
    qDebug() << "Input changed to:" << text;
}
void GameWindow::on_answerLineEdit_returnPressed()
{
    on_submitAnswerButton_clicked();
}
// 在 gamewindow.cpp 中

void GameWindow::on_submitAnswerButton_clicked()
{
    ui->answerLineEdit->setFocus();
    QString userAnswer = ui->answerLineEdit->text().trimmed();
    if (userAnswer.isEmpty()) {
        ui->statusLabel->setText("请输入答案！");
        // 使用QTimer短暂显示提示后恢复
        QTimer::singleShot(1500, this, [this](){
            if(ui->statusLabel->text() == "请输入答案！") {
                ui->statusLabel->setText("猜猜这是哪首歌...");
            }
        });
        return;
    }
    // player->stop();
    // 判断答案（统一转为小写进行比较）
    if (userAnswer.toLower() == currentCorrectAnswer.toLower()) {
        ui->statusLabel->setText("正确! ✔️");
        // 延迟1.5秒后自动播放下一首
        updateScore(5); // <-- 答对，+5分
        setInputControlsEnabled(false);
        player->stop();
        QTimer::singleShot(1500, this, &GameWindow::playNextSong);
    } else {
        ui->statusLabel->setText("错误! ❌ 仅此而已了吗" );
        updateScore(-1); // <-- 答错，-1分
        // 延迟3秒后自动播放下一首
        // QTimer::singleShot(3000, this, &GameWindow::playNextSong);
    }
}
void GameWindow::on_giveUpButton_clicked()
{
    qDebug() << "点击了 '我没招儿了' 按钮。";
    updateScore(-3);
    countdownTimer->stop();
    ui->statusLabel->setText("正确答案是：" + currentCorrectAnswer + "自动切换下一首..");
    // displayCorrectAnswer(currentCorrectAnswer); // 显示正确答案
    player->stop();
    setInputControlsEnabled(false);
    QTimer::singleShot(3000, this, &GameWindow::playNextSong); // 3秒后切歌
}
void GameWindow::displayCorrectAnswer(const QString& answer)
{
    ui->correctAnswerLabel->setText("正确答案是：" + answer);
}
void GameWindow::on_changeFolderButton_clicked()
{

    this->accept();
}

void GameWindow::on_changeDifficultyButton_clicked()
{
    // 关闭窗口。
    this->accept();
}

void GameWindow::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    // 检查是否是第一次显示窗口，并且音乐文件已成功加载
    if (isFirstShow && !musicFiles.isEmpty()) {
        isFirstShow = false;

        QTimer::singleShot(0, this, &GameWindow::playNextSong);
    }
}
void GameWindow::generateShuffledPlaylist()
{
    qDebug() << "生成新的随机播放列表...";

    // 1. 清空旧的播放列表
    shuffledPlaylist.clear();

    // 2. 创建一个临时的、从 0 到 n-1 的顺序索引列表
    for (int i = 0; i < musicFiles.size(); ++i) {
        shuffledPlaylist.append(i);
        qDebug() << i << " ";
    }

    // 3. 使用C++标准库的算法来彻底打乱这个索引列表
    // std::random_shuffle(shuffledPlaylist.begin(), shuffledPlaylist.end());//c17被弃用
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffledPlaylist.begin(), shuffledPlaylist.end(), g);
    // 4. 将播放位置重置为0，从新列表的开头开始
    playlistPosition = 0;

    qDebug() << "新列表已生成，包含" << shuffledPlaylist.size() << "首歌曲。";
}
void GameWindow::setInputControlsEnabled(bool enabled)//定时器禁用
{
    ui->answerLineEdit->setEnabled(enabled);
    ui->submitAnswerButton->setEnabled(enabled);
    ui->giveUpButton->setEnabled(enabled);
    ui->playButton->setEnabled(enabled);
}

// gamewindow.cpp

// 在文件的任何地方添加这两个新函数的实现

void GameWindow::updateCountdown()
{
    qint64 elapsed = elapsedTimer->elapsed();
    if (elapsed >= countdownDuration) {
        // 时间到！
        countdownTimer->stop();
        handleTimeUp();
        return;
    }

    int progress = 100 - (elapsed * 100 / countdownDuration);
    ui->countdownProgressBar->setValue(progress);

    int remainingSeconds = (countdownDuration - elapsed + 999) / 1000;
    ui->countdownProgressBar->setFormat(QString("%1 秒").arg(remainingSeconds));
}

void GameWindow::handleTimeUp()
{
    ui->statusLabel->setText("时间到！答案是：" + currentCorrectAnswer);
    updateScore(-5);
    player->stop(); // 时间到了也停止播放音乐
    setInputControlsEnabled(false); // 禁用输入
    QTimer::singleShot(3000, this, &GameWindow::playNextSong); // 3秒后切换到下一首
}
void GameWindow::updateScore(int points)
{
    m_score += points;
    ui->scoreLabel->setText(QString("分数: %1").arg(m_score));
}
