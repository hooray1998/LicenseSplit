#ifndef CHECKLABEL_H
#define CHECKLABEL_H

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

class checkLabel : public QLabel
{
public:
    explicit checkLabel(QWidget*parent = 0);

    void init(QString path, QString path2);
    void initRects();
    void readMergeList();
    void getNext();
    void updateWindow();
    void removeCur();//updata mergeFile and folder.
    void readFileinfo();
    void writeFileinfo();

    int curNum;
    int size;
public slots:
    void paintEvent(QPaintEvent *);
private:
    QString jpgpath;
    QString txtpath;
    QPainter painter;
    //layout
    QRect titleRect;
    QRect picRect;
    QRect rect[7];
    //drawRect
    QRect drawrect[7];
    QPixmap curLicense;
    QString chars[7];
    QString name[71];
    QStringList list;
};
#endif // CHECKLABEL_H
