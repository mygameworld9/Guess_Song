// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QStandardPaths>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_directoryModeComboBox_currentIndexChanged(int index);
    void on_startButton_clicked();

private:
    void loadMusicFolders(); // 声明一个用于加载文件夹的函数

    Ui::MainWindow *ui;
    QString musicPath; // 用于存储Music目录的路径
};
#endif // MAINWINDOW_H
