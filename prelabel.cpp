#include "prelabel.h"

preLabel::preLabel(QWidget *parent) :
    QLabel(parent)
{

    showSwitch =false;


    name[0]=   "0";
    name[1]=   "1";
    name[2]=   "2";
    name[3]=   "3";
    name[4]=   "4";
    name[5]=   "5";
    name[6]=   "6";
    name[7]=   "7";
    name[8]=   "8";
    name[9]=   "9";
    name[10]=  "A";
    name[11]=  "B";
    name[12]=  "C";
    name[13]=  "D";
    name[14]=  "E";
    name[15]=  "F";
    name[16]=  "G";
    name[17]=  "H";
    name[18]=  "J";
    name[19]=  "K";
    name[20]=  "L";
    name[21]=  "M";
    name[22]=  "N";
    name[23]=  "P";
    name[24]=  "Q";
    name[25]=  "R";
    name[26]=  "S";
    name[27]=  "T";
    name[28]=  "U";
    name[29]=  "V";
    name[30]=  "W";
    name[31]=  "X";
    name[32]=  "Y";
    name[33]=  "Z";
    name[34]=  "苏";
    name[35]=  "浙";
    name[36]=  "鲁";
    name[37]=  "沪";
    name[38]=  "皖";
    name[39]=  "冀";
    name[40]=  "豫";
    name[41]=  "津";
    name[42]=  "辽";
    name[43]=  "湘";
    name[44]=  "鄂";
    name[45]=  "赣";
    name[46]=  "甘";
    name[47]=  "闽";
    name[48]=  "黑";
    name[49]=  "粤";
    name[50]=  "贵";
    name[51]=  "渝";
    name[52]=  "京";
    name[53]=  "晋";
    name[54]=  "吉";
    name[55]=  "蒙";
    name[56]=  "桂";
    name[57]=  "琼";
    name[58]=  "川";
    name[59]=  "云";
    name[60]=  "藏";
    name[61]=  "陕";
    name[62]=  "青";
    name[63]=  "宁";
    name[64]=  "新";
    name[65]=  "港";
    name[66]=  "澳";
    name[67]=  "使";
    name[68]=  "领";
    name[69]=  "学";
    name[70]=  "警";


}

void preLabel::setid(int i)
{
    id = i;
}

void preLabel::paintEvent(QPaintEvent *)
{

    painter.begin(this);

    painter.setPen(QPen(Qt::gray, 5, Qt::SolidLine, Qt::FlatCap));    //设置画笔;
    painter.setFont(QFont(NULL,80));

    if(id==2)
    {
        for(int i=0;i<5;i++)
        {
            if(i!=1)
            {
                QPixmap tempGray(curPixmap[i].size());
                tempGray.fill(QColor(0,0,0,180));
                QPainter p(&curPixmap[i]);
                p.drawPixmap(0,0,tempGray);
            }
            painter.drawPixmap(rect[i].x(), rect[i].y(), curPixmap[i].scaled(rect[i].size()));
        }

    }

    if(!historyName.isEmpty())
    {
        QFile *file = new QFile(listpath+QString("/%1.txt").arg(historyName));

        bool ok = false;
        if(file->exists())
        ok = file->open(QIODevice::ReadOnly|QIODevice::Text);

        if(ok)
        {
            int historyChar;
            QTextStream in(file);
            in>>historyChar;
            file->close();
            delete file;
            painter.drawText(QRect(rect[0].x()+50,rect[0].y()+rect[0].height(),rect[0].width(),rect[0].height()),name[historyChar]);
        }
    }
    if(!curCharname.isEmpty())
    {
        painter.setFont(QFont(NULL,120));
        QFile *file = new QFile(listpath+QString("/%1.txt").arg(curCharname));

        bool ok = false;
        if(file->exists())
        {
            ok = file->open(QIODevice::ReadOnly|QIODevice::Text);
            if(ok)
            {
                int cur;
                QTextStream in(file);
                in>>cur;
                file->close();
                delete file;
                painter.drawText(QRect(rect[1].x()+70,rect[1].y()+rect[1].height(),rect[1].width(),rect[1].height()),name[cur]);
            }
        }

    }

        painter.setFont(QFont(NULL,25));
        painter.drawText(QRect(rect[1].x()+20,rect[1].y()/2,rect[1].width(),50),curCharname);


    if(showSwitch)
    {

        QStringList ll = showList.split(".");

        for(int i=0;i<ll.size();i++)
        {
            painter.drawText(QRect(rect[1].x()+20,rect[1].y()+rect[1].height()+i*50,rect[1].width(),50),ll.at(i));
        }
    }



    painter.end();
}


bool preLabel::readCharFileinfo()
{
    QFile *file = new QFile("fileinfo_mode2");
    bool ok = file->open(QIODevice::ReadOnly|QIODevice::Text);
    if(ok)
    {
        QTextStream in(file);
        in>>curNum>>curCharname;
        QString filename;
        if(newList.size()!=0)
        filename =newList.at(curNum).fileName().split(".").at(0);
        if(curNum==0)
        {
            curCharname = filename;
        }
        else
        {
            if(filename!=curCharname)
            {
                for(int i=0;i<newList.size();i++)
                {
                   if(newList.at(i).fileName().split(".").at(0) == curCharname)
                   {
                       curNum = i;
                       writeCharFileinfo();
                       break;
                   }
                }
            }
        }
        file->close();
        delete file;
    }

    return true;
}
bool preLabel::writeCharFileinfo()
{
    QFile *file = new QFile("fileinfo_mode2");
    bool ok = file->open(QIODevice::WriteOnly|QIODevice::Text);
    if(ok)
    {
        QTextStream out(file);
        out<<curNum<<"  "<<curCharname;
        file->close();
        delete file;
    }
    return true;
}

bool preLabel::loadAllChar(bool next)
{

    for(int i=-1;i<4;i++)
    {
        loadCurChar(i);
    }

    update();

}
bool preLabel::loadCurChar(int num)
{

    if(newList.size()==0)
    {
        QMessageBox::warning(this,"Error Message:","该路径下符文件.");
        return false;
    }
    int nn = curNum+num;
    if(curNum==newList.size())
    {
        QMessageBox::information(this,"Good Job", "everything is ok.");
        curNum--;
        return false;
    }
    if(nn<0) return false;

    if(nn<newList.size())
    {
        //progress
        //update Mainwindows
        //progress.setValue(100*(num+1)/newList.size());

        QFileInfo finfo =newList.at(nn);
        QString filename= finfo.fileName();
        if(num == 0)
        {
            curCharname = filename.split(".").at(0);
            if(nn>0)
                historyName = newList.at(nn-1).fileName().split(".").at(0);
            else
                historyName.clear();
        }
        curPixmap[num+1] = QPixmap(finfo.filePath());
        return true;
    }

    return false;

}
bool preLabel::initCurLabel()
{
    QFileInfoList list;
    QDir dir;
    listpath = QString("licenseSplitData/characters_in_licenses");
    dir.setPath(listpath);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);

    list = dir.entryInfoList();
    if(list.size()==0) return false;

    for(int i=0;i<list.size();i++)
    {
        if(list.at(i).fileName().contains(".jpg"))
            newList.append(list.at(i));
    }

    if(newList.size()!=0)
    {
        readCharFileinfo();
        loadAllChar(true);
        writeCharFileinfo();
    }


    //init 5 rect
    int lw = width()/20;
    int lh = height()/20;

    rect[0].setRect(1*lw,3.5*lh,3*lw,6*lh);
    rect[1].setRect(5*lw,3*lh,3.5*lw,7*lh);
    rect[2].setRect(10*lw,3.5*lh,3*lw,6*lh);
    rect[3].setRect(14*lw,4*lh,2.5*lw,5*lh);
    rect[4].setRect(17*lw,4.5*lh,2*lw,4*lh);

}

bool preLabel::saveCurCharTxt(int Class)
{
    QFile *file = new QFile(listpath+"/"+curCharname+".txt");
    bool ok = file->open(QIODevice::WriteOnly|QIODevice::Text);
    if(ok)
    {
        QTextStream out(file);
        out<<Class;
        file->close();
        delete file;
    }
    else
    {
        qDebug()<<"fail open "<<file->fileName();
    }
    return true;
}

void preLabel::findNextUnsaved()
{
    QFile *file = new QFile();
    for(int i=0;i<newList.size();i++)
    {
        QString curPath = newList.at(i).filePath().split(".").at(0)+QString(".txt");
        file->setFileName(curPath);
        if(!file->exists())
        {
            qDebug()<<file->fileName();
            curNum = i;
            loadAllChar(true);
            writeCharFileinfo();
            break;
        }
    }

}
