#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "gamewindow.h"
#include <QCoreApplication> // <-- 添加或确保这行存在
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 获取标准的音乐目录路径
    musicPath = QCoreApplication::applicationDirPath() + "/Music";
    QDir musicDir(musicPath);

    if (!musicDir.exists()) {
        // 如果Music目录不存在，可以提示用户或尝试创建
        QMessageBox::warning(this, "警告", "未找到系统Music目录！");
        // 你也可以禁用所有控件
        ui->startButton->setEnabled(false);
    } else {
        // 2. 加载文件夹列表
        loadMusicFolders();
    }

    // 3. 初始化时，根据 directoryModeComboBox 的默认选项，决定是否显示 specificFolderComboBox
    on_directoryModeComboBox_currentIndexChanged(ui->directoryModeComboBox->currentIndex());

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 加载 Music 目录下的所有子文件夹到下拉列表中
void MainWindow::loadMusicFolders()
{
    QDir musicDir(musicPath);
    // 设置过滤器，只列出目录
    musicDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList folderList = musicDir.entryList();

    // 清空并添加文件夹列表到 specificFolderComboBox
    ui->specificFolderComboBox->clear();
    if (folderList.isEmpty()) {
        ui->specificFolderComboBox->addItem("Music目录下没有子文件夹");
        ui->specificFolderComboBox->setEnabled(false);
    } else {
        ui->specificFolderComboBox->addItems(folderList);
    }
}

// 当目录模式选择改变时，决定是否显示/隐藏“指定文件夹”的下拉框
void MainWindow::on_directoryModeComboBox_currentIndexChanged(int index)
{
    // index 0: 指定Music下的文件夹
    // index 1: Music下的所有文件夹
    if (index == 0) {
        ui->specificFolderComboBox->setVisible(true); // 显示
    } else {
        ui->specificFolderComboBox->setVisible(false); // 隐藏
    }
}

// “开始游戏”按钮的点击事件
void MainWindow::on_startButton_clicked()
{
    // 1. 获取歌曲目录
    QString selectedMusicPath;
    if (ui->directoryModeComboBox->currentIndex() == 0) { // 指定文件夹
        if (ui->specificFolderComboBox->count() == 0 || ui->specificFolderComboBox->currentText().startsWith("Music目录下没有")) {
            QMessageBox::warning(this, "错误", "请选择一个有效的歌曲文件夹！");
            return; // 中断操作
        }
        selectedMusicPath = musicPath + "/" + ui->specificFolderComboBox->currentText();
    } else { // 所有文件夹
        selectedMusicPath = musicPath;
    }
    QDir musicDir(selectedMusicPath);
    QStringList nameFilters;
    nameFilters << "*.mp3" << "*.wav" << "*.flac";
    musicDir.setNameFilters(nameFilters);
    musicDir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

    // 检查过滤后的文件列表是否为空
    // if (musicDir.entryList().isEmpty()) {
    //     QMessageBox::warning(this, "目录无效", "您选择的文件夹中没有找到任何支持的音乐文件！");
    //     return; // 文件夹是空的，中断操作，不进入游戏窗口
    // }
    // 2. 获取游戏难度
    float difficulty = 1.9; // 默认1秒
    if (ui->threeSecondsRadioButton->isChecked()) {
        difficulty = 3;
    } else if (ui->fiveSecondsRadioButton->isChecked()) {
        difficulty = 5;
    } else if (ui->fullSongRadioButton->isChecked()) {
        difficulty = 0; // 用0代表整首歌
    }

    // 3. 隐藏主窗口，创建并显示游戏窗口
    this->hide();

    GameWindow gameWindow(this); // 创建 GameWindow 实例
    gameWindow.setGameSettings(selectedMusicPath, difficulty); // 传递数据！
    gameWindow.exec(); // 以模态方式显示游戏窗口，代码会在此暂停直到窗口关闭

    // 4. 当游戏窗口关闭后，重新显示主窗口
    this->show();
}
