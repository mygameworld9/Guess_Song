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
    ui->folderListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
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
    connect(ui->selectAllButton, &QPushButton::clicked, this, &MainWindow::on_selectAllButton_clicked);
    connect(ui->deselectAllButton, &QPushButton::clicked, this, &MainWindow::on_deselectAllButton_clicked);
    // 3. 初始化时，根据 directoryModeComboBox 的默认选项，决定是否显示 specificFolderComboBox
    // on_directoryModeComboBox_currentIndexChanged(ui->directoryModeComboBox->currentIndex());

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 加载 Music 目录下的所有子文件夹到下拉列表中
void MainWindow::loadMusicFolders()
{
    QDir musicDir(musicPath);
    musicDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList folderList = musicDir.entryList();

    // 清空列表
    ui->folderListWidget->clear();

    if (folderList.isEmpty()) {
        // 如果没有子文件夹，可以添加一个禁用的提示项
        QListWidgetItem *item = new QListWidgetItem("Music目录下没有子文件夹");
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsUserCheckable); // 禁用选择和勾选
        ui->folderListWidget->addItem(item);
        ui->startButton->setEnabled(false); // 禁用开始按钮
        ui->selectAllButton->setEnabled(false);
        ui->deselectAllButton->setEnabled(false);
    } else {
        // 遍历所有文件夹，为每个文件夹创建一个可勾选的列表项
        for (const QString &folderName : folderList) {
            QListWidgetItem *item = new QListWidgetItem(folderName, ui->folderListWidget);
            // 设置 item 为用户可勾选的
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            // 默认设置为未勾选状态
            item->setCheckState(Qt::Unchecked);
        }
    }
}
// void MainWindow::loadMusicFolders()
// {
//     QDir musicDir(musicPath);
//     // 设置过滤器，只列出目录
//     musicDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
//     QStringList folderList = musicDir.entryList();

//     // 清空并添加文件夹列表到 specificFolderComboBox
//     ui->specificFolderComboBox->clear();
//     if (folderList.isEmpty()) {
//         ui->specificFolderComboBox->addItem("Music目录下没有子文件夹");
//         ui->specificFolderComboBox->setEnabled(false);
//     } else {
//         ui->specificFolderComboBox->addItems(folderList);
//     }
// }

// 当目录模式选择改变时，决定是否显示/隐藏“指定文件夹”的下拉框
// void MainWindow::on_directoryModeComboBox_currentIndexChanged(int index)
// {
//     // index 0: 指定Music下的文件夹
//     // index 1: Music下的所有文件夹
//     if (index == 0) {
//         ui->specificFolderComboBox->setVisible(true); // 显示
//     } else {
//         ui->specificFolderComboBox->setVisible(false); // 隐藏
//     }
// }

// “开始游戏”按钮的点击事件
// void MainWindow::on_startButton_clicked()
// {
//     // 1. 获取歌曲目录
//     QString selectedMusicPath;
//     if (ui->directoryModeComboBox->currentIndex() == 0) { // 指定文件夹
//         if (ui->specificFolderComboBox->count() == 0 || ui->specificFolderComboBox->currentText().startsWith("Music目录下没有")) {
//             QMessageBox::warning(this, "错误", "请选择一个有效的歌曲文件夹！");
//             return; // 中断操作
//         }
//         selectedMusicPath = musicPath + "/" + ui->specificFolderComboBox->currentText();
//     } else { // 所有文件夹
//         selectedMusicPath = musicPath;
//     }
//     QDir musicDir(selectedMusicPath);
//     QStringList nameFilters;
//     nameFilters << "*.mp3" << "*.wav" << "*.flac";
//     musicDir.setNameFilters(nameFilters);
//     musicDir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

//     // 检查过滤后的文件列表是否为空
//     // if (musicDir.entryList().isEmpty()) {
//     //     QMessageBox::warning(this, "目录无效", "您选择的文件夹中没有找到任何支持的音乐文件！");
//     //     return; // 文件夹是空的，中断操作，不进入游戏窗口
//     // }
//     // 2. 获取游戏难度
//     float difficulty = 1.9; // 默认1秒
//     if (ui->threeSecondsRadioButton->isChecked()) {
//         difficulty = 3;
//     } else if (ui->fiveSecondsRadioButton->isChecked()) {
//         difficulty = 5;
//     } else if (ui->fullSongRadioButton->isChecked()) {
//         difficulty = 0; // 用0代表整首歌
//     }

//     // 3. 隐藏主窗口，创建并显示游戏窗口


//     // GameWindow gameWindow(this); // 创建 GameWindow 实例
//     // gameWindow.exec(); // 以模态方式显示游戏窗口，代码会在此暂停直到窗口关闭
//     GameWindow *gameWindow = new GameWindow();
//     gameWindow -> setGameSettings(selectedMusicPath, difficulty); // 传递数据！
//     gameWindow -> setAttribute(Qt::WA_DeleteOnClose);
//     gameWindow -> show();
//     this->hide();
//     // 4. 当游戏窗口关闭后，重新显示主窗口
//     connect(gameWindow, &QObject::destroyed, this, &QWidget::show);
// }
void MainWindow::on_startButton_clicked()
{
    // 1. 获取所有被勾选的目录
    QStringList selectedFolders;
    for (int i = 0; i < ui->folderListWidget->count(); ++i) {
        QListWidgetItem *item = ui->folderListWidget->item(i);
        // 如果 item 被勾选了
        if (item->checkState() == Qt::Checked) {
            // 将文件夹的完整路径添加到列表中
            selectedFolders.append(musicPath + "/" + item->text());
        }
    }

    if (selectedFolders.isEmpty()) {
        QMessageBox::warning(this, "提示", "请至少选择一个歌曲文件夹！");
        return; // 中断操作
    }

    // 2. 从所有选中的目录中，收集所有音乐文件的路径
    QStringList musicFiles;
    QStringList nameFilters;
    nameFilters << "*.mp3" << "*.wav" << "*.flac";

    for (const QString &folderPath : selectedFolders) {
        QDir musicDir(folderPath);
        musicDir.setNameFilters(nameFilters);
        musicDir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

        // 获取当前目录下的所有音乐文件
        QStringList filesInFolder = musicDir.entryList();

        // 将文件路径转换为绝对路径并添加到总列表中
        for(const QString &file : filesInFolder) {
            musicFiles.append(folderPath + "/" + file);
        }
    }

    if (musicFiles.isEmpty()) {
        QMessageBox::warning(this, "目录无效", "您选择的文件夹中没有找到任何支持的音乐文件！");
        return;
    }

    // 3. 获取游戏难度 (这部分逻辑不变)
    float difficulty = 1.9;
    if (ui->threeSecondsRadioButton->isChecked()) {
        difficulty = 3;
    } else if (ui->fiveSecondsRadioButton->isChecked()) {
        difficulty = 5;
    } else if (ui->fullSongRadioButton->isChecked()) {
        difficulty = 0;
    }

    // 4. 隐藏主窗口，创建并显示游戏窗口
    // 注意：这里我们传递的是一个包含所有音乐文件路径的列表 (musicFiles)，而不是单个目录。
    // 你需要确保你的 GameWindow 和 setGameSettings 函数能接收 QStringList。

    GameWindow *gameWindow = new GameWindow();

    // ！！！重要！！！
    // 你的 setGameSettings 函数原型可能需要从
    // void setGameSettings(const QString &path, float difficulty);
    // 修改为
    // void setGameSettings(const QStringList &files, float difficulty);
    gameWindow->setGameSettings(musicFiles, difficulty); // 传递文件列表！

    gameWindow->setAttribute(Qt::WA_DeleteOnClose);
    gameWindow->show();
    this->hide();
    connect(gameWindow, &QObject::destroyed, this, &QWidget::show);
}

void MainWindow::on_selectAllButton_clicked()
{
    for (int i = 0; i < ui->folderListWidget->count(); ++i) {
        QListWidgetItem *item = ui->folderListWidget->item(i);
        // 检查 item 是否是可勾选的
        if (item->flags() & Qt::ItemIsUserCheckable) {
            item->setCheckState(Qt::Checked);
        }
    }
}

// “全不选”按钮的槽函数
void MainWindow::on_deselectAllButton_clicked()
{
    for (int i = 0; i < ui->folderListWidget->count(); ++i) {
        QListWidgetItem *item = ui->folderListWidget->item(i);
        if (item->flags() & Qt::ItemIsUserCheckable) {
            item->setCheckState(Qt::Unchecked);
        }
    }
}
