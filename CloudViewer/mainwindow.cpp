#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->exit, &QAction::triggered, this, &MainWindow::exitSlot);
    connect(ui->aboutCloudViewer, &QAction::triggered, [this]()
    {
        QMessageBox::information(this, "关于 Cloud Viewer", "weidong8988@qq.com\nsupport bin and pcd.");
    });
    connect(ui->openfile, &QAction::triggered, this, &MainWindow::openFileSlot);
    connect(ui->openfolder, &QAction::triggered, this, &MainWindow::openFolderSlot);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 打开文件
void MainWindow::openFileSlot()
{
    QString fn = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Cloud Files (*.bin *.pcd)"));
    if(fn.isEmpty())
    {
        return;
    }
    openFileName = fn;
    openFolderName = QString("");

    ui->filename->setText(QString("file path: ")+openFileName);

    ui->filelist->clear();

    cper.readPointCloud(openFileName.toStdString());
    ui->imagelabel->setPixmap(QPixmap::fromImage(cper.getImage(730, ui->scalenum->value(), ui->bgcolor_r->value(), ui->bgcolor_g->value(), ui->bgcolor_b->value())));

    ui->filetotal->setText(QString(""));
    ui->pointnum->setText(QString("共 ")+QString::number(cper.cloud_size)+QString(" 个点"));
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue,4));
    painter.drawLine(20,20,800,800);
}

// 打开文件夹
void MainWindow::openFolderSlot()
{
    QString fn = QFileDialog::getExistingDirectory(this, tr("Open Folder"), "/home");
    if(fn.isEmpty())
    {
        return;
    }
    openFolderName = fn;
    openFileName = QString("");

    ui->filename->setText(QString("folder path: ")+openFolderName);

    ui->imagelabel->clear();


    QDir dir(openFolderName);
    QStringList fileNames = dir.entryList(QStringList({"*.bin", "*.pcd"}), QDir::Files);
    ui->filelist->clear();
    ui->filelist->addItems(fileNames);
    ui->filetotal->setText(QString("共 ")+QString::number(fileNames.size())+QString(" 项"));

}

// 退出
void MainWindow::exitSlot()
{
    this->close();
}

// 修改scale
void MainWindow::on_scalenum_valueChanged(double scale)
{
    if(openFileName.length()==0)
    {
        return;
    }
    ui->imagelabel->setPixmap(QPixmap::fromImage(cper.getImage(730, ui->scalenum->value(), ui->bgcolor_r->value(), ui->bgcolor_g->value(), ui->bgcolor_b->value())));
}

// 选择list中的一项
void MainWindow::on_filelist_currentRowChanged(int currentRow)
{
    qDebug()<<currentRow<<endl;
    if(currentRow==-1)
    {
        return;
    }
    openFileName = openFolderName + QString("/") + ui->filelist->item(currentRow)->text();

    cper.readPointCloud(openFileName.toStdString());
    ui->imagelabel->setPixmap(QPixmap::fromImage(cper.getImage(730, ui->scalenum->value(), ui->bgcolor_r->value(), ui->bgcolor_g->value(), ui->bgcolor_b->value())));
    ui->pointnum->setText(QString("共 ")+QString::number(cper.cloud_size)+QString(" 个点"));
}

void MainWindow::on_bgcolor_r_valueChanged(double arg1)
{
    if(openFileName.length()==0)
    {
        return;
    }
    ui->imagelabel->setPixmap(QPixmap::fromImage(cper.getImage(730, ui->scalenum->value(), ui->bgcolor_r->value(), ui->bgcolor_g->value(), ui->bgcolor_b->value())));
}


void MainWindow::on_bgcolor_g_valueChanged(double arg1)
{
    if(openFileName.length()==0)
    {
        return;
    }
    ui->imagelabel->setPixmap(QPixmap::fromImage(cper.getImage(730, ui->scalenum->value(), ui->bgcolor_r->value(), ui->bgcolor_g->value(), ui->bgcolor_b->value())));
}


void MainWindow::on_bgcolor_b_valueChanged(double arg1)
{
    if(openFileName.length()==0)
    {
        return;
    }
    ui->imagelabel->setPixmap(QPixmap::fromImage(cper.getImage(730, ui->scalenum->value(), ui->bgcolor_r->value(), ui->bgcolor_g->value(), ui->bgcolor_b->value())));
}

