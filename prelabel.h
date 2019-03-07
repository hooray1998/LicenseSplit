#ifndef PRELABEL_H
#define PRELABEL_H

#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QtDebug>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QFileInfoList>
#include <QFileInfo>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QPixmap>


class preLabel : public QLabel
{
public:
    explicit preLabel(QWidget*parent = 0);

    void setid(int i=0);

    bool readCharFileinfo();
    bool writeCharFileinfo();
    //void searchChar()
    bool loadAllChar(bool next);
    bool loadCurChar(int num);
    bool initCurLabel();//curLabel

    bool saveCurCharTxt(int Class);

    int curNum;
    QString curCharname;
    QString showList;
    bool showSwitch;
    QFileInfoList newList;

    void findNextUnsaved();
public slots:
    void paintEvent(QPaintEvent *);
private:
    QPainter painter;
    int id;

    QRect rect[5];
    QPixmap curPixmap[5];
    QString preCharname;
    QString listpath;

    QString historyName;

    QString name[71];
};

#endif // PRELABEL_H
