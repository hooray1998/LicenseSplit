#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define STEP 10
#define STEP_Y 18

#include <QMainWindow>
#include <QFile>
#include <QKeyEvent>
#include <QtDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QMessageBox>
#include <QProgressBar>
#include <QSet>
#include <QMap>
#include <QTimer>

#include <QStack>
#include <mythread.h>

class FileInfo{
public:
    int curNum;
};


namespace Ui {
class Mainwindow;
}

class Mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = 0);
    ~Mainwindow();

    void initStyle();
    bool readFileinfo();
    bool writeFileinfo();
    bool readNewPicture();
    bool renameAll();

    bool analyzeKey(int key);
    void initAllMap();
    void showAllReadyList();
protected:
    void keyPressEvent(QKeyEvent *event);

private slots:

    bool removeAll(bool);
    void addProvice();

    void updateCurLabel(int);

    void updataMarkProgress();
    void updataMergeProgress(int p);
    void on_pushButtonMergeAll_clicked();

    void threadOk();
private:
    Ui::Mainwindow *ui;
    QProgressBar progress;

    QString filename;

    QFileInfoList list;
    FileInfo fileinfo;


    QStack<int> keyStack;
    QSet<int> deleteLicense;

    QMap<int, QString> keyToChar_Map;
    //multi  letters
    QMap<QString, QString> pyToWord_Map;
    QMap<QString, int> wordToClass_Map;

    QString curProvince;
    bool recording;
    QStringList readyList;


    QTimer *curProcessTimer;



    ///MODE  3////////
    MyThread *mergeThread;
};

#endif // MAINWINDOW_H
