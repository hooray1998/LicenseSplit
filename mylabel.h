#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QtDebug>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QPixmap>
#include <QKeyEvent>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget*parent = 0);

    void setNewLayout();
    void setNewLicense(QString filename);

    bool makeSaveDir();
    bool saveAll();
    bool judgeSave();

    int pianyileft,
        pianyiright,
        pianyitop,
        pianyibottom;

    bool isSaved;
    bool isModify;

protected:
private:

    QPainter painter;

    QPixmap *curLicense;
    QString curName;

    //layout
    int wid,
        hei,
        sidewidth,
        blackwidth,
        topheight,
        lwidth,
        lheight,
        mainwidth,
        mainheight,
        mainx,
        mainy;

    QRect mark[7];
    QRect captureLicense[7];
    QPixmap capturePixmap[7];
    QPixmap labelPicture;

signals:

public slots:
    void paintEvent(QPaintEvent *);
};

#endif // MYLABEL_H
