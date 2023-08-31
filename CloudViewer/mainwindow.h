#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QListWidget>
#include <QDebug>
#include <QPainter>

#include "cloudProjection.h"

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
    void openFileSlot();  // 打开文件
    void openFolderSlot();  // 打开文件夹
    void exitSlot();  // 退出

    void on_filelist_currentRowChanged(int currentRow);

    // 修改缩放尺度
    void on_scalenum_valueChanged(double scale);

    // 修改背景颜色
    void on_bgcolor_r_valueChanged(double arg1);
    void on_bgcolor_g_valueChanged(double arg1);
    void on_bgcolor_b_valueChanged(double arg1);

private:
    QString openFileName;
    QString openFolderName;
    cloudProjecter cper;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
