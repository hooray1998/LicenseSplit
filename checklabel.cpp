#include "checklabel.h"

checkLabel::checkLabel(QWidget *parent) :
    QLabel(parent)
{
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

void checkLabel::init(QString path, QString path2)
{
    jpgpath = path;
    txtpath = path2;
    initRects();
    readMergeList();
    readFileinfo();
    if(list.size()!=0)
        getNext();
}
void checkLabel::initRects()
{
    int wid = this->width();
    int hei = this->height();

    titleRect.setRect(0,0,wid,hei/5);
    picRect.setRect(0,hei/5,wid,hei*2/5);
    for(int i=0;i<7;i++)
    {
        rect[i].setRect(i*wid/7,hei*3/5,wid/7,hei*2/5);
    }
}

void checkLabel::paintEvent(QPaintEvent *)
{
    painter.begin(this);
    int fontwidth = rect[0].width()/2;
    painter.setFont(QFont(NULL,fontwidth/2));
    painter.setPen(QPen(Qt::gray, 5, Qt::SolidLine, Qt::FlatCap));    //设置画笔;
    //draw  Title
    if(size!=0)
        painter.drawText(titleRect,Qt::AlignCenter,list.at(curNum));
    painter.setFont(QFont(NULL,fontwidth));
    painter.setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::FlatCap));    //设置画笔;
    //draw License
    painter.drawPixmap(picRect.x(),picRect.y(),curLicense.scaled(picRect.size()));
    //draw Text
    for(int i=0;i<7;i++)
    {
        painter.drawText(rect[i],Qt::AlignCenter,chars[i]);
    }
    //draw Rect
    for(int i=0;i<7;i++)
    {
        painter.drawRect(drawrect[i]);
    }
    painter.end();
}

void checkLabel::readMergeList()
{
    QFile *file = new QFile("mergeList");
    bool ok = file->open(QIODevice::ReadOnly|QIODevice::Text);
    if(ok)
    {
        list.clear();
        QTextStream in(file);
        QString temp;
        while(!in.atEnd())
        {
            in>>temp;
            if(!temp.isEmpty())
                list.append(temp);
        }
        size = list.size();
        file->close();
        delete file;
    }
    else
    {
        QMessageBox::warning(this,"error 8077", "未找到mergeList文件。");
        exit(0);
    }
}

void checkLabel::readFileinfo()
{
    QFile *file = new QFile("fileinfo_mode3");
    bool ok = file->open(QIODevice::ReadOnly|QIODevice::Text);
    if(ok)
    {
        QTextStream in(file);
        in>>curNum;
        file->close();
        delete file;
    }
}

void checkLabel::writeFileinfo()
{
    QFile *file = new QFile("fileinfo_mode3");
    bool ok = file->open(QIODevice::WriteOnly|QIODevice::Text);
    if(ok)
    {
        QTextStream out(file);
        out<<curNum;
        file->close();
        delete file;
    }
}

void checkLabel::getNext()
{
    if(list.size()==0) return ;
    if(curNum<0)
    {
        curNum = 0;
    }
    else if(curNum==list.size())
    {
        curNum = list.size()-1;
    }
    //read Pixmap
    curLicense = QPixmap(QString("%1/%2.jpg").arg(jpgpath).arg(list.at(curNum)));
    //read txt
    QFile *file = new QFile(QString("%1/%2.txt").arg(txtpath).arg(list.at(curNum)));
    bool ok = file->open(QIODevice::ReadOnly|QIODevice::Text);
    if(!ok)
    {
        QMessageBox::warning(this,"error 3251",QString("mergeFolder中txt文件丢失%1").arg(file->fileName()));
        return ;
    }
    QTextStream in(file);
    int mainx = picRect.x();
    int mainy = picRect.y();
    int wid = picRect.width();
    int hei = picRect.height();
    int clas;
    float x,y,w,h;
    for(int i=0;i<7;i++)
    {
        in>>clas>>x>>y>>w>>h;
        chars[i] = name[clas];
        drawrect[i].setRect(mainx+wid*x,mainy+hei*y,wid*w,hei*h);
    }
    file->close();
    delete file;
    update();
}

void checkLabel::removeCur()
{
    QFile *file = new QFile("deleteMergeList");
    bool ok = file->open(QIODevice::Append|QIODevice::Text);
    if(ok)
    {
        QTextStream out(file);
        out<<list.at(curNum)<<endl;
        file->close();
        delete file;
    }
}

void checkLabel::updateWindow()
{
    readMergeList();
    readFileinfo();
    if(list.size()!=0)
        getNext();
}
