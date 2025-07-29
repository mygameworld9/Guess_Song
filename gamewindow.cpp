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
#include <QKeySequence>
#include <QShortcut>
GameWindow::GameWindow(QWidget *parent) :
    // QDialog(parent),
    QWidget(parent),

    ui(new Ui::gamewindow)
{
    ui->setupUi(this);
    m_lastSubmittedAnswer = "";
    player = new QMediaPlayer(this);

    audioOutput = new QAudioOutput(this);
    // QKeySequence keySequence(tr("Alt+Right"));
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

    // connect(ui->giveUpButton, &QPushButton::clicked, this, &GameWindow::on_giveUpButton_clicked);
    ui->answerLineEdit->setCompleter(completer);       // 将补全应用到输入框
    ui->countdownProgressBar->setVisible(false);
    ui->countdownProgressBar->setRange(0, 100);
    ui->countdownProgressBar->setValue(100); // 初始值设为满
    m_score = 0;
    ui->scoreLabel->setText(QString("分数: %1").arg(m_score));
    connect(player, &QMediaPlayer::durationChanged, this, &GameWindow::onDurationChanged);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &GameWindow::onMediaStatusChanged);
    connect(ui->actionSkip, &QAction::triggered, ui->SkipButton, &QPushButton::click);


    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+D"), this);

    // 设置为ApplicationShortcut，解决焦口问题
    shortcut->setContext(Qt::ApplicationShortcut);

    // 连接
    QObject::connect(shortcut, &QShortcut::activated, ui -> SkipButton, &QPushButton::click);
}
GameWindow::~GameWindow()
{
    delete ui;
}

// void GameWindow::setGameSettings(const QString &path, int difficulty)
// {
//     // 将传递过来的数据存储到成员变量中
//     this->musicDirectory = path;
//     this->gameDifficulty = difficulty;


//     QString difficultyText = (difficulty == 0) ? "整首歌" : QString("%1秒").arg(difficulty);
//     this->setWindowTitle(QString("游戏进行中 - %1").arg(difficultyText));

//     qDebug() << "游戏窗口已加载设置:";
//     qDebug() << "歌曲目录:" << this->musicDirectory;
//     qDebug() << "游戏难度:" << difficultyText;

//     loadMusicFiles();
// }
void GameWindow::setGameSettings(const QStringList &musicFiles, float difficulty)
{
    // 1. 将传递过来的“文件列表”和“难度”存储到成员变量中
    this->playlist = musicFiles; // 直接存储最终的文件列表
    this->gameDifficulty = difficulty;

    // 2. 更新窗口标题 (这部分逻辑不变)
    QString difficultyText = (difficulty == 0) ? "整首歌" : QString("%1秒").arg(difficulty);
    this->setWindowTitle(QString("游戏进行中 - %1").arg(difficultyText));

    // 3. 打印日志，确认接收到的信息
    qDebug() << "游戏窗口已加载设置:";
    qDebug() << "接收到的歌曲数量:" << this->playlist.count(); // 打印文件的数量更有意义
    qDebug() << "游戏难度:" << difficultyText;
    // qDebug() << "歌曲列表:" << this->playlist;

    // 4. 调用 loadMusicFiles() 来准备播放
    // 现在的 loadMusicFiles() 不再是去“加载”，而是去“准备播放列表”，比如随机排序等
    loadMusicFiles();
}
// void GameWindow::loadMusicFiles()
// {
//     musicFiles.clear();
//     songTitles.clear();

//     QDirIterator it(musicDirectory, {"*.mp3", "*.flac", "*.wav", "*.m4a"}, QDir::Files, QDirIterator::Subdirectories);

//     while (it.hasNext()) {
//         QString filePath = it.next();
//         musicFiles.append(filePath);

//         QFileInfo fileInfo(filePath);
//         QString fileName = fileInfo.baseName(); // 获取不带后缀的文件名

//         QString artist, title;
//         parseSongName(fileName, artist, title); // 解析歌名

//         // 如果有歌手，答案就是 "歌手 - 歌名"
//         // 英文歌名统一转为小写以忽略大小写
//         // QString answer = title.toLower();
//         songTitles.append(title);
//         // songTitles.append(answer); // 将处理后的歌名存入列表
//     }
//     for(const QString& title : songTitles) {
//         songTrie.insert(title.toLower()); // 插入小写版本用于匹配
//     }
//     completerModel->setStringList(songTitles);
//     // if (musicFiles.isEmpty()) {
//     // QMessageBox::warning(this, "错误", "所选目录中未找到任何支持的音乐文件！\n请检查目录或更换目录。");
//     // ui->playButton->setEnabled(false); // 禁用播放按钮
//     // } else {
//     qDebug() << "成功加载" << musicFiles.count() << "首歌曲。";
//     // }
//     generateShuffledPlaylist(); //开始生成播放列表

// }
void GameWindow::loadMusicFiles()
{

    if (playlist.isEmpty()) {
        qDebug() << "错误：播放列表为空，无法加载音乐。";
        // 在这里可以显示一个错误消息给用户，然后关闭窗口
        QMessageBox::critical(this, "错误", "没有可播放的音乐文件！");
        this->close(); // 关闭游戏窗口
        return;
    }
    for (int i = 0; i < playlist.size(); ++i) {
        shuffledPlaylist.append(i);
    }
    for (const QString& filePath : playlist) {
        // --- 从这里开始，是你写的正确逻辑 ---
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.baseName(); // 获取不带后缀的文件名

        QString artist, title;
        parseSongName(fileName, artist, title); // 解析歌名

        songTitles.append(title);
        // --- 到这里结束 ---
    }
    completerModel->setStringList(songTitles);
    generateShuffledPlaylist();
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
void GameWindow::on_StopButton_clicked()
{
    if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->stop(); // 先停止
    }
    else{
        player->play();
    }
}
void GameWindow::on_playButton_clicked()
{
    // 如果当前有歌曲正在播放（意味着用户想重复听），则重新播放
    if (player->playbackState() == QMediaPlayer::PlayingState || currentSongIndex != -1) {
        player->stop(); // 先停止
        if(gameDifficulty > 0){
            player->setSource(QUrl::fromLocalFile(playlist[currentSongIndex]));
            player->setPosition(randomStartTime + 10);
        }
        else{
            player->setPosition(0); // 将播放位置重置到开头
        }
    }
    player->play();

    if (gameDifficulty > 0) {
        // 使用 QTimer::singleShot 可以创建一个只触发一次的定时器
        // 它会在指定毫秒数后执行一个 lambda 函数
        QTimer::singleShot( gameDifficulty * 1000, this, [this]() {
            // 再次检查，确保是在操作同一首歌时才停止
            if(player->source() == QUrl::fromLocalFile(playlist[currentSongIndex])) {
                player->stop();
                qDebug() << "片段播放停止。";
            }
        });
    }
    qint64 elapsed = elapsedTimer->elapsed();
    if (elapsed >= countdownDuration) {
        // 时间到！
        countdownTimer->stop();
        handleTimeUp();
        return;
    }
}
void GameWindow::playNextSong()
{

    setInputControlsEnabled(true);
    countdownTimer->stop(); // 先停止上一次的计时器
    m_currentSongDuration = 0;

    if (playlist.isEmpty()) return;
    if (playlistPosition >= playlist.size()) {
        player->stop();
        QMessageBox::information(this, "提示", "所有歌曲均已播放完毕！\n即将开始新一轮随机播放。");
        // 重新生成一个新的、完全不同的随机播放列表
        generateShuffledPlaylist();
    }

    currentSongIndex = shuffledPlaylist[playlistPosition];
    // 随机选择一首歌
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
    qDebug() << "当前播放: " << songTitles[currentSongIndex];
    qDebug() << "正确答案是: " << currentCorrectAnswer;
    player->stop();
    player->setSource(QUrl::fromLocalFile(playlist[currentSongIndex]));
    player->play();
    const int clipDurationMs = gameDifficulty * 1000;

    // --- 核心改动：随机播放逻辑 ---
    // 使用一个短暂延时来确保歌曲信息已加载
    if (gameDifficulty == 0) {
        // *** 整首歌播放模式 ***
        qDebug() << "模式：整首歌播放";

        // 隐藏倒计时进度条
        ui->countdownProgressBar->setVisible(false);

        // 直接从头开始播放，不需要任何定时停止
        player->play();

    }
    else{
        QTimer::singleShot(200, this, [this, clipDurationMs]() {
            // 检查歌曲总时长是否已成功获取，并且长于我们要播放的片段
            if (m_currentSongDuration > clipDurationMs) {
                // 计算一个安全的随机起始点
                // 最晚的起始点 = 总时长 - 片段时长
                qint64 latestStartTime = m_currentSongDuration - clipDurationMs - 10;
                // 生成一个从 0 到 latestStartTime 的随机数
                randomStartTime = QRandomGenerator::global()->bounded(latestStartTime);

                qDebug() << "跳转到随机位置:" << randomStartTime << "ms";
                player->setPosition(randomStartTime + 10); // 跳转到该位置
            }
            // 如果歌曲本身很短或时长获取失败，就从头播放
            else {
                qDebug() << "歌曲太短或时长无效，从头播放。";
                player->setPosition(0);
            }

            // 设置一个定时器，在播放了 clipDurationMs 毫秒后停止播放
            QTimer::singleShot(clipDurationMs, this, [this]() {
                // 再次检查，确保是在操作同一首歌时才停止
                if(player->source() == QUrl::fromLocalFile(playlist[currentSongIndex])) {
                    player->stop();
                    qDebug() << "片段播放停止。";
                }
            });
        });
    }
    ui->answerLineEdit->setFocus();
    // 根据难度设置定时停止
    // 难度为 0 代表整首歌，不需要定时器
    if (gameDifficulty > 0) {
        // 使用 QTimer::singleShot 可以创建一个只触发一次的定时器
        // 它会在指定毫秒数后执行一个 lambda 函数
        QTimer::singleShot(gameDifficulty * 1000, this, [this]() {
            if (player->source() == QUrl::fromLocalFile(playlist[currentSongIndex])) {
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
    if(userAnswer == m_lastSubmittedAnswer) return;
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
        int addScore = countdownDuration - elapsedTimer->elapsed();
        if(gameDifficulty){
            updateScore(5 + addScore / 1000.0 / 5); // <-- 答对，+5分 2000 *0.05
        }
        else{
            updateScore(5);
        }
        /*setInputControlsEnabled*/(false);
        player->stop();
        QTimer::singleShot(1500, this, &GameWindow::playNextSong);
    } else {
        ui->statusLabel->setText("错误! ❌ 仅此而已了吗" );
        updateScore(-1); // <-- 答错，-1分
        // 延迟3秒后自动播放下一首
        // QTimer::singleShot(3000, this, &GameWindow::playNextSong);
    }
    m_lastSubmittedAnswer = userAnswer;
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

    this->close();
}

void GameWindow::on_changeDifficultyButton_clicked()
{
    // 关闭窗口。
    this->close();
}

void GameWindow::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    // 检查是否是第一次显示窗口，并且音乐文件已成功加载
    if (isFirstShow && !playlist.isEmpty()) {
        isFirstShow = false;

        QTimer::singleShot(0, this, &GameWindow::playNextSong);
    }
}
void GameWindow::generateShuffledPlaylist()
{
    m_lastSubmittedAnswer = "";
    qDebug() << "生成新的随机播放列表...";

    // 1. 清空旧的播放列表

    // 2. 创建一个临时的、从 0 到 n-1 的顺序索引列表

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
    QString userAnswer = ui->answerLineEdit->text().trimmed();
    // if(userAnswer == m_lastSubmittedAnswer) return;
    if (userAnswer.toLower() == currentCorrectAnswer.toLower()) {
        ui->statusLabel->setText("正确! ✔️");
        // 延迟1.5秒后自动播放下一首
        // int addScore = countdownDuration - elapsedTimer->elapsed();
        updateScore(5); // <-- 答对，+5分 2000 *0.05
        /*setInputControlsEnabled*/(false);
        player->stop();
        QTimer::singleShot(1500, this, &GameWindow::playNextSong);
    }
    else{
        ui->statusLabel->setText("时间到！答案是：" + currentCorrectAnswer);
        updateScore(-5);
        player->stop(); // 时间到了也停止播放音乐
        // setInputControlsEnabled(false); // 禁用输入
        QTimer::singleShot(3000, this, &GameWindow::playNextSong); // 3秒后切换到下一首
    }
}
void GameWindow::updateScore(int points)
{
    m_score += points;
    ui->scoreLabel->setText(QString("分数: %1").arg(m_score));
}
void GameWindow::onDurationChanged(qint64 duration)
{
    qDebug() << "歌曲总时长已获取:" << duration << "ms";
    m_currentSongDuration = duration;
}


void GameWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    // 检查状态是否为“媒体播放结束”
    if (status == QMediaPlayer::EndOfMedia) {
        qDebug() << "媒体播放结束 (EndOfMedia)。";

        // 并且，仅在“整首歌”模式下才自动切换
        if (gameDifficulty == 0) {
            // QString userAnswer = ui->answerLineEdit->text().trimmed();
            qDebug() << "模式为“整首歌”，将在1秒后自动切换到下一首。";

            QTimer::singleShot(1000, this, &GameWindow::playNextSong);
        }
    }
}
void GameWindow::on_SkipButton_clicked()
{
    playNextSong();
}
