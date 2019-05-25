#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtCore>
#include "tilescalc.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void finished();

private slots:
    void on_pushButton_clicked();
    void downloadReadyRead();
    void downloadFinished();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);



    void on_pushButton_2_clicked();

    void on_pushButton_calculate_clicked();

public:

    //TilesCalc *MyTilesCalc;


private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager;
    QNetworkReply *currentDownload = nullptr;
    QFile output;
    QTime downloadTime;

    int totalMapCount = 0;
    int downloadedCount = 0;
};

#endif // MAINWINDOW_H
