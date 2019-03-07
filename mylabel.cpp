#include "mylabel.h"
#include <QPainter>
myLabel::myLabel(QWidget *parent) :
    QLabel(parent)
{
    //pn_Number = -1;

    isSaved = false;

    makeSaveDir();
    curLicense = NULL;
    isModify = true;
}

void myLabel::setNewLayout()
{

    //layout


        wid = this->width();
        hei = this->height();

        sidewidth= wid*1/9;
        blackwidth = wid*1/38;
        topheight= hei*1/8;
        lwidth = (wid - 2*sidewidth - 6*blackwidth)/7;
        lheight = hei*1/4;
        mainwidth = wid*2/5;
        mainheight = hei*2/5;
        mainx = (wid-mainwidth)/2;
        mainy = (50+topheight+lheight);



        int tempx = sidewidth;
        int tempy = topheight;
        for(int i=0;i<7;i++)
        {
            mark[i].setRect(tempx,tempy,lwidth,lheight);
            tempx += blackwidth+lwidth;
        }

}
void myLabel::paintEvent(QPaintEvent *)
{
        //clear();

        painter.begin(this);          //进行重绘;




        float licenseWidth = mainwidth-pianyileft-pianyiright;
        float licenseHeight= mainheight-pianyitop-pianyibottom;

        //x 方向， 一个单位
        float gex = (float)licenseWidth/411;

        float gey = ((float)licenseHeight-90*gex)/364;

        QPoint p[7];


        p[0].setX(mainx+pianyileft);
        p[1].setX(p[0].x()+57*gex);
        p[2].setX(p[1].x()+74*gex);
        p[3].setX(p[2].x()+57*gex);
        p[4].setX(p[3].x()+57*gex);
        p[5].setX(p[4].x()+57*gex);
        p[6].setX(p[5].x()+57*gex);


        p[0].setY(mainy+pianyitop);
        p[1].setY(p[0].y()+0*gey);
        p[2].setY(p[1].y()+0*gey);
        p[3].setY(p[2].y()+0*gey);
        p[4].setY(p[3].y()+0*gey);
        p[5].setY(p[4].y()+0*gey);
        p[6].setY(p[5].y()+0*gey);

        int pw = 52*gex;
        int ph = licenseHeight;

        painter.setPen(QPen(Qt::gray, 5, Qt::SolidLine, Qt::FlatCap));    //设置画笔;
        painter.setFont(QFont("Arial",50));
        painter.drawText(QRect(mainx+mainwidth,mainy,mainwidth/2,100),QString("%1").arg(isSaved?"Save":"No"));
        painter.setFont(QFont("Arial",20));
        painter.drawText(QRect(mainx+mainwidth,mainy+100,mainwidth/2,70),QString("%1").arg(curName));

        for(int i=0;i<7;i++)
        {
            captureLicense[i].setRect(p[i].x(),p[i].y(),pw,ph);
            capturePixmap[i] = labelPicture.copy(captureLicense[i]);
        }

        if(curLicense!=NULL)
        {
            painter.drawPixmap(mainx,mainy,curLicense->scaled(QSize(mainwidth,mainheight)));
            for(int i=0;i<7;i++)
            {
                if(!capturePixmap[i].isNull())
                painter.drawPixmap(mark[i],capturePixmap[i].scaled(mark[i].size()));
            }
        }

        painter.end();  //重绘结束;
}



void myLabel::setNewLicense(QString filename)
{

    if(!curLicense==NULL)
        delete curLicense;

    QStringList l= filename.split("all_licenses/");
    curName = l.at(l.size()-1).split(".").at(0);
    curLicense = new QPixmap(filename);

    isSaved = false;
    judgeSave();
    //////////////
    labelPicture = QWidget::grab(this->rect());

    if(!isSaved)
    {
        pianyileft=0;
        pianyiright=0;
        pianyitop = 0;
        pianyibottom=0;
    }
        update();
}

bool myLabel::saveAll()
{

    if(isSaved)
    {
        QMessageBox msgBox;
        msgBox.setText("该图片已经保存");
        //显示文本
        msgBox.setInformativeText("是否覆盖?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret)
        {
          case QMessageBox::Ok:
            break;
          case QMessageBox::Cancel:
            //event->ignore();
            return false;
            break;
          default:
              // should never be reached
            return false;
              break;
          }
        //save the information of locate and size.

        QString  picname= "licenseSplitData/licenses_no_class/"+curName+".jpg";
        QString  txtname= "licenseSplitData/licenses_no_class/"+curName+".txt";

        QFile fp(picname);
        if(fp.exists())
        {
            if(!fp.remove())
                qDebug("覆盖picfile失败");
            else
                qDebug("覆盖picfile成功");
        }
        else
        {
                qDebug("不存在picfile");
        }

        curLicense->save(picname);
        QFile *file0 = new QFile(txtname);
        bool ok = file0->open(QIODevice::WriteOnly|QIODevice::Text);

        if(ok)
        {
            QTextStream out(file0);

            float ix,iy,iw,ih;

            for(int i=0;i<7;i++)
            {
                ix = (float)(captureLicense[i].x()-mainx)/mainwidth;
                iy = (float)(captureLicense[i].y()-mainy)/mainheight;
                iw = (float)captureLicense[i].width()/mainwidth;
                ih = (float)captureLicense[i].height()/mainheight;

                out<<ix<<"  "<<iy<<"  "<<iw<<"  "<<ih<<endl;

            }
            file0->close();
            delete file0;
        }


        //save characters
        for(int i=0;i<7;i++)
        {
            qDebug()<<"start save char"<<i;
            QString filename = "licenseSplitData/characters_in_licenses/"+curName+"_"+QString::number(i)+".jpg";
            qDebug()<<"filename is "<<filename;
            QFile *file = new QFile(filename);
            /////////////////////////////////////////////////////////////////////////////////////////////////////
            /////被360拦截卧槽////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////
            if(file->exists())
            {
                if(!file->remove())
                    qDebug()<<"removeFail"<<filename;
                else
                    qDebug()<<"remove"<<i;
            }
            else
                qDebug()<<"no exist"<<i;

            delete file;
            if(!capturePixmap[i].save(filename))
                qDebug()<<"saveFail"<<filename;
            else
                qDebug()<<"save char"<<i;

        }

    }
    else
    {

        //save the information of locate and size.

        QString  picname= "licenseSplitData/licenses_no_class/"+curName+".jpg";
        QString  txtname= "licenseSplitData/licenses_no_class/"+curName+".txt";

        QFile fp(picname);
        if(fp.exists())
            if(!fp.remove())
                qDebug("覆盖picfile失败");
        curLicense->save(picname);
        QFile *file0 = new QFile(txtname);
        bool ok = file0->open(QIODevice::WriteOnly|QIODevice::Text);

        if(ok)
        {
            QTextStream out(file0);

            float ix,iy,iw,ih;

            for(int i=0;i<7;i++)
            {
                ix = (float)(captureLicense[i].x()-mainx)/mainwidth;
                iy = (float)(captureLicense[i].y()-mainy)/mainheight;
                iw = (float)captureLicense[i].width()/mainwidth;
                ih = (float)captureLicense[i].height()/mainheight;

                out<<ix<<"  "<<iy<<"  "<<iw<<"  "<<ih<<endl;

            }
            file0->close();
            delete file0;
        }


        //save characters
        for(int i=0;i<7;i++)
        {
            QString filename = "licenseSplitData/characters_in_licenses/"+curName+"_"+QString::number(i)+".jpg";
            QFile file(filename);
            if(file.exists())
                if(!file.remove())
                    qDebug()<<"removeFail"<<filename;
            if(!capturePixmap[i].save(filename))
                qDebug()<<"saveFail"<<filename;
        }

    }


    judgeSave();
    if(isSaved)
        isModify = false;
        return true;

}


bool myLabel::makeSaveDir()
{

        QDir *temp = new QDir;
        bool exist;

        exist = temp->exists("licenseSplitData");
        if(!exist)
        {
                QMessageBox::warning(this,tr("警告"),tr("数据文件夹licenseSplitData丢失！"));
                qDebug()<<"111";
                exit(0);
                return false;
        }

        exist = temp->exists("licenseSplitData/all_licenses");
        if(!exist)
        {
                QMessageBox::warning(this,tr("警告"),tr("数据文件夹licenseSplitData/all_licenses丢失！"));
                qDebug()<<"112";
                exit(0);
                return false;
        }


        exist = temp->exists("licenseSplitData/licenses_no_class");
        if(!exist)
        {
            bool ok = temp->mkdir("licenseSplitData/licenses_no_class");
            if(!ok )
                QMessageBox::warning(this,tr("创建文件夹"),tr("文件夹licenseSplitData/licenses_no_class创建失败！"));
        }


        exist = temp->exists("licenseSplitData/characters_in_licenses");
        if(!exist)
        {
            bool ok = temp->mkdir("licenseSplitData/characters_in_licenses");
            if(!ok )
                QMessageBox::warning(this,tr("创建文件夹"),tr("文件夹licenseSplitData/characters_in_licenses创建失败！"));
        }

}


bool myLabel::judgeSave()
{
//    if()

    QString  picname= "licenseSplitData/licenses_no_class/"+curName+".jpg";
    QString  txtname= "licenseSplitData/licenses_no_class/"+curName+".txt";

    QFile *file0 = new QFile(txtname);
    if(file0->exists())
    {
        isSaved = true;
        bool ok = file0->open(QIODevice::ReadOnly|QIODevice::Text);

        if(ok)
        {
            QTextStream in(file0);

            float ix,iy,iw,ih;
            for(int i=0;i<7;i++)
            {
                in>>ix>>iy>>iw>>ih;
                captureLicense[i].setX(ix*mainwidth+mainx);
                captureLicense[i].setY(iy*mainheight+mainy);
                captureLicense[i].setWidth(iw*mainwidth);
                captureLicense[i].setHeight(ih*mainheight);
            }
            file0->close();
            delete file0;
        }
        pianyileft = captureLicense[0].x()-mainx;
        pianyitop =  captureLicense[0].y()-mainy;
        pianyiright = mainx+mainwidth-captureLicense[6].x()-captureLicense[6].width();
        pianyibottom = mainy+mainheight-captureLicense[6].y()-captureLicense[6].height();

    }
    if(isSaved)
        isModify = false;

    return true;
}
