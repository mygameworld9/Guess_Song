// gamewindow.cpp
#include "ui_gamewindow.h"
#include <QDebug>
#include <QDirIterator> // <-- 用于遍历文件夹
#include <QRandomGenerator> // <-- 用于生成随机数
#include <QTimer> // <-- 用于定时停止播放
#include <QMessageBox>
#include <QStringListModel>
#include "gamewindow.h"
GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gamewindow)
{
    ui->setupUi(this);
    // 1. 创建 QMediaPlayer 实例 (这行是原有的)
    player = new QMediaPlayer(this);

    // 2. 新增：创建 QAudioOutput 实例
    audioOutput = new QAudioOutput(this);

    // 3. 新增：将播放器和输出设备进行绑定
    player->setAudioOutput(audioOutput);

    // 初始化自动补全功能
    completer = new QCompleter(this);
    completerModel = new QStringListModel(this);
    completer->setModel(completerModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive); // 设置不区分大小写
    completer->setFilterMode(Qt::MatchContains);       // 匹配模式，包含即可
    ui->answerLineEdit->setCompleter(completer);       // 将补全器应用到输入框
}
GameWindow::~GameWindow()
{
    delete ui;
}

// 实现这个函数
void GameWindow::setGameSettings(const QString &path, int difficulty)
{
    // 将传递过来的数据存储到成员变量中
    this->musicDirectory = path;
    this->gameDifficulty = difficulty;

    // 【验证】为了确认数据已成功传递，我们可以把信息打印到控制台
    // 或者更新UI，例如更新窗口标题
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

    // 使用 QDirIterator 递归地遍历所有子目录
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
    if (musicFiles.isEmpty()) {
        QMessageBox::warning(this, "错误", "所选目录中未找到任何支持的音乐文件！\n请检查目录或更换目录。");
        ui->playButton->setEnabled(false); // 禁用播放按钮
    } else {
        qDebug() << "成功加载" << musicFiles.count() << "首歌曲。";
    }
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
}
void GameWindow::playNextSong()
{
    if (musicFiles.isEmpty()) return;

    // 随机选择一首歌
    currentSongIndex = QRandomGenerator::global()->bounded(musicFiles.count());
    currentCorrectAnswer = songTitles[currentSongIndex];
    QFileInfo fileInfo(musicFiles[currentSongIndex]);
    QString fileName = fileInfo.baseName();
    QString artist, title;
    parseSongName(fileName, artist, title);
    currentCorrectAnswer = title; // 直接存储原始大小写的正确歌名

    // 清空上一轮的答案并重置状态
    ui->answerLineEdit->clear();
    ui->statusLabel->setText("请听题...");

    qDebug() << "当前播放: " << musicFiles[currentSongIndex];
    qDebug() << "正确答案是: " << currentCorrectAnswer;
    player->stop();
    player->setSource(QUrl::fromLocalFile(musicFiles[currentSongIndex]));
    player->play();

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
}
void GameWindow::on_answerLineEdit_textChanged(const QString &text)
{
    // QCompleter 会自动处理提示，我们这里可以暂时不做任何事
    // 或者可以用我们自己的字典树来更新 Completer，如果需要更复杂的逻辑
    // QVector<QString> suggestions = songTrie.suggest(text.toLower());
    // completerModel->setStringList(QList<QString>::fromVector(suggestions));
    qDebug() << "Input changed to:" << text;
}
void GameWindow::on_answerLineEdit_returnPressed()
{
    if (currentSongIndex == -1) return; // 游戏还没开始

    QString userAnswer = ui->answerLineEdit->text().trimmed();
    player->stop();
    // 判断答案，统一转为小写进行比较，实现不区分大小写
    if (userAnswer.toLower() == currentCorrectAnswer.toLower()) {
        ui->statusLabel->setText("正确! ✔️");
        // 延迟1.5秒后自动播放下一首
        QTimer::singleShot(1500, this, &GameWindow::playNextSong);
    } else {
        ui->statusLabel->setText("错误! ❌ 正确答案是: " + currentCorrectAnswer);
        // 延迟3秒后自动播放下一首
        QTimer::singleShot(3000, this, &GameWindow::playNextSong);
    }

    currentSongIndex = -1; // 防止在进入下一首之前重复判断
}
// 在 gamewindow.cpp 中

void GameWindow::on_submitAnswerButton_clicked()
{
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

    // 在判断答案之前，立即停止当前歌曲的播放和定时器
    // 这是为了防止后续操作与正在播放的歌曲或计时器冲突
    player->stop();


    // 判断答案（统一转为小写进行比较）
    if (userAnswer.toLower() == currentCorrectAnswer.toLower()) {
        ui->statusLabel->setText("正确! ✔️");
        // 延迟1.5秒后自动播放下一首
        QTimer::singleShot(1500, this, &GameWindow::playNextSong);
    } else {
        ui->statusLabel->setText("错误! ❌ 正确答案是: " + currentCorrectAnswer);
        // 延迟3秒后自动播放下一首
        QTimer::singleShot(3000, this, &GameWindow::playNextSong);
    }

}
// 在 gamewindow.cpp 中

// 当点击“更改目录”或“更改难度”时，我们都执行相同的操作：关闭游戏窗口
// 因为游戏窗口是以模态 (exec()) 方式打开的，关闭它后，代码会自动返回到
// MainWindow 中调用它的地方。

void GameWindow::on_changeFolderButton_clicked()
{
    // 调用 accept() 会以“接受”状态关闭对话框
    // 这会让之前调用 a.exec() 的地方返回 QDialog::Accepted

    this->accept();
}

void GameWindow::on_changeDifficultyButton_clicked()
{
    // 调用 reject() 会以“拒绝”状态关闭对话框
    // 两者都可以，作用都是关闭窗口。我们可以都用 accept()。
    this->accept();
}

// 别忘了在 MainWindow.cpp 中，我们是这样调用游戏窗口的：
/*
    GameWindow gameWindow(this);
    gameWindow.setGameSettings(selectedMusicPath, difficulty);
    gameWindow.exec(); // <--- 代码在这里暂停，直到 gameWindow 关闭

    this->show(); // <--- 当 gameWindow 关闭后，主窗口会重新显示
*/
