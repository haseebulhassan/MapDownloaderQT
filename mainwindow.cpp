#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   //MyTilesCalc = new TilesCalc();

    //TilesCalc MyTiles = new TilesCalc;
    ui->setupUi(this);
    QPixmap pix("/home/haseeb/Desktop/Projects/MapDownloaderQT/map_example1.png");
    int w = ui->pic->width();
    int h = ui->pic->height();
    ui->pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->setupUi(this);

    connect(ui->pushButton_calculate, SIGNAL(clicked(bool)), this , SLOT(on_pushButton_calculate_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString url_s = "http://mt1.google.com/vt/lyrs=y&x=100&y=100&z=10";
    QUrl url = QUrl::fromEncoded(url_s.toLocal8Bit());
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();
    QString filename = basename;


    QNetworkRequest request(url);
    currentDownload = manager.get(request);

    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),
            SLOT(downloadProgress(qint64,qint64)));

    connect(currentDownload, SIGNAL(readyRead()),
            SLOT(downloadReadyRead()));

    connect(currentDownload, SIGNAL(finished()),
            SLOT(downloadFinished()));

    downloadTime.start();
    qDebug("Download Started");
}

void MainWindow::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    //progressBar.setStatus(bytesReceived, bytesTotal);
     qDebug("Download Progress");
    // calculate the download speed
    double speed = bytesReceived * 1000.0 / downloadTime.elapsed();
    QString unit;
    if (speed < 1024) {
        unit = "bytes/sec";
    } else if (speed < 1024*1024) {
        speed /= 1024;
        unit = "kB/s";
    } else {
        speed /= 1024*1024;
        unit = "MB/s";
    }



}

void MainWindow::downloadReadyRead()
{
    output.write(currentDownload->readAll());
    qDebug("Download Ready");
}

void MainWindow::downloadFinished()
{
    output.close();
    qDebug("Download Finished");
}

void MainWindow::on_pushButton_2_clicked()
{
    output.setFileName("/Users/haseebulhassan/Desktop/thatq.jpeg");
    output.open(QIODevice::ReadWrite);
    qDebug("File Opened");
}

void MainWindow::on_pushButton_calculate_clicked()
{

   TilesCalc::Latitude_Start =  ui->lineEdit_latB->text().toDouble();
   TilesCalc::Latitude_End = ui->lineEdit_latA->text().toDouble();
   TilesCalc::Longitude_Start = ui->lineEdit_lonA->text().toDouble();
   TilesCalc::Longitude_End  =  ui->lineEdit_lonB->text().toDouble();
   TilesCalc::zoom = ui->lineEdit_zoom->text().toInt();

   double a = ui->lineEdit_latB->text().toDouble();

    TilesCalc::CalculateTiles();

    ui->lineEdit_totaltiles->setText(QString::number(TilesCalc::TotalTiles));
    ui->lineEdit_tilesLat->setText(QString::number(TilesCalc::TotalTilesLat));
    ui->lineEdit_tilesLon->setText(QString::number(TilesCalc::TotalTilesLon));
    ui->lineEdit_timeReq->setText(QString::number(TilesCalc::TotalTimeReq));
    ui->lineEdit_diskReq->setText(QString::number(TilesCalc::TotalDiskReq));




}

