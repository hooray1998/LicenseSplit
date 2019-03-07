#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QSetIterator>
#include <QMessageBox>
#include <QObject>
#include <QThread>
#include <QtDebug>
#include <QWidget>
#include <time.h>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <string.h>
#include <QSet>
#include <QFileInfoList>
#include <QStringList>



class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(int function, QString zongPath, QString charsPath);
signals:
    Progress(int);
    ok(bool);
protected:
    void run();

    void readMergedList();
    void createMergeFolder();
    void mergeAllTxt();
    void readTxtList();
private:
    int FUNCTION;

    QString path1;
    QString path2;


    //mergeModule
    QSet<QString> mergeSet;
    QFileInfoList txtList;
};

#endif // MYTHREAD_H
