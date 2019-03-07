#include "mainwindow.h"
#include "ui_mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainwindow)
{

    curProcessTimer = new QTimer();
    QObject::connect(curProcessTimer,SIGNAL(timeout()),this,SLOT(updataMarkProgress()));
    curProcessTimer->start(100);




    ui->setupUi(this);
    //set Size
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    setWindowState(Qt::WindowMaximized);


    QObject::connect(ui->pushButtonClose,SIGNAL(clicked(bool)),this,SLOT(removeAll(bool)));


    initStyle();
    int dwid = QApplication::desktop()->width();
    int dhei = QApplication::desktop()->height();

    /////mode1
    ui->widget->resize(dwid-20,30);
    ui->tabWidget->resize(dwid,dhei-30);
    ui->label->resize(dwid-20,dhei-80);

    ui->label->setNewLayout();
    //////////mode2
    ///

    //set size
    ui->curlabel->setGeometry(0,0,dwid,dhei-80);
    ui->pushButton->setGeometry(dwid-60,dhei/2-120,40,160);

    //////////mode3
    ui->checklabel->setGeometry(dwid/5,dhei/18,dwid*3/5,dhei*5/7);



    //init setting
    //ui->tabWidget->setCurrentIndex(0);
    //set id
    ui->curlabel->setid(2);
    ui->curlabel->initCurLabel();
    //add ProgressBar
    progress.setFixedWidth(dwid-20);
    ui->statusBar->addWidget(&progress);

    //ui->curlabel->update();
//////////////////////////Mode 1////////////////////////////////

    //read Pictures
    QDir dir;
    dir.setPath("licenseSplitData/all_licenses");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);

    list = dir.entryInfoList();
    readFileinfo();
    readNewPicture();
    deleteLicense.clear();
    update();

    /////////////////////////////////////Mode 2//////////////////////////
    /// \brief QObject::connect
    ///

    QObject::connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(updateCurLabel(int)));
    initAllMap();
    recording = false;

    ///////////////MODE 3//////////////////////////
    mergeThread = new MyThread(1,"licenseSplitData/licenses_no_class","licenseSplitData/characters_in_licenses");
    connect(mergeThread,SIGNAL(Progress(int)),this,SLOT(updataMergeProgress(int)));
    ui->checklabel->init("licenseSplitData/licenses_no_class","licenseSplitData/mergeFolder");

    //set id
    ui->tabWidget->setCurrentIndex(0);
}

Mainwindow::~Mainwindow()
{
    delete ui;
}

void Mainwindow::initStyle()
{
    //加载样式表
    QFile file(":/new/prefix1/style/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void Mainwindow::keyPressEvent(QKeyEvent *event)
{
    if(ui->tabWidget->currentIndex()==2)
    {

        if(event->key()==Qt::Key_Up||event->key()==Qt::Key_K)
        {
            if(ui->checklabel->curNum>0)
            {
                ui->checklabel->curNum--;
                ui->checklabel->getNext();
                ui->checklabel->writeFileinfo();
            }
        }
        else if(event->key()==Qt::Key_Backspace)
        {
            ui->checklabel->removeCur();
            if(ui->checklabel->curNum==ui->checklabel->size-1) return;
            ui->checklabel->curNum++;
            ui->checklabel->getNext();
            ui->checklabel->writeFileinfo();
        }
        else if(event->key()==Qt::Key_Down||event->key()==Qt::Key_J)
        {
            if(ui->checklabel->curNum==ui->checklabel->size-1) return;
            ui->checklabel->curNum++;
            ui->checklabel->getNext();
            ui->checklabel->writeFileinfo();
        }

    }
    else if(ui->tabWidget->currentIndex()==1)
    {
        if(event->key()==Qt::Key_Up||event->key()==Qt::Key_Backspace)
        {
            if(ui->curlabel->curNum>0)
            {
                ui->curlabel->curNum--;
                ui->curlabel->loadAllChar(false);
                ui->curlabel->writeCharFileinfo();
            }
            curProvince.clear();
            recording = false;
                    ui->curlabel->showSwitch = false;
                    ui->curlabel->showList.clear();

        }
        else if(event->key()==Qt::Key_Down)
        {
                ui->curlabel->curNum++;
                ui->curlabel->loadAllChar(true);
                ui->curlabel->writeCharFileinfo();
                curProvince.clear();
                recording = false;
                    ui->curlabel->showSwitch = false;
                    ui->curlabel->showList.clear();
        }
        else if(event->key()==Qt::Key_Return)
        {
            qDebug("start find");
            ui->curlabel->findNextUnsaved();
            ui->curlabel->update();

        }
        else//if vaild
        {
            qDebug()<<QString::number(event->key(),16);
            ui->curlabel->update();
                if(analyzeKey(event->key()))
                {
                    ui->curlabel->curNum++;
                    ui->curlabel->loadAllChar(true);
                    ui->curlabel->writeCharFileinfo();
                    curProvince.clear();
                    recording = false;
                }
        }

        return ;
    }
    else if(ui->tabWidget->currentIndex()==0)
    {

        if(event->key()==Qt::Key_J)
        {
            if(!ui->label->isSaved||ui->label->isModify)
            ui->label->saveAll();
            if(fileinfo.curNum>=(list.size()-1)) return ;
            fileinfo.curNum++;
            while(deleteLicense.contains(fileinfo.curNum))
                fileinfo.curNum++;
            writeFileinfo();
            readNewPicture();
        }
        else if(event->key()==Qt::Key_Backspace)
        {
            deleteLicense.insert(fileinfo.curNum);
            if(fileinfo.curNum==0)
            while(deleteLicense.contains(fileinfo.curNum))
                fileinfo.curNum++;
            else if(fileinfo.curNum==(list.size()-1)) while(deleteLicense.contains(fileinfo.curNum))
                fileinfo.curNum--;
            else
            {
                bool dir = true;
                while(deleteLicense.contains(fileinfo.curNum))
                {
                    if(dir)
                    {
                        if(fileinfo.curNum<(list.size()-1))
                            fileinfo.curNum++;
                        else
                            dir = false;
                    }
                    else
                    {
                        if(fileinfo.curNum>0)
                            fileinfo.curNum--;
                        else
                            dir = true;
                    }
                }
            }

            writeFileinfo();
            readNewPicture();

        }
        else if(event->key()==Qt::Key_Down)
        {
            if(fileinfo.curNum>=(list.size()-1)) return ;
            fileinfo.curNum++;
            while(deleteLicense.contains(fileinfo.curNum))
                fileinfo.curNum++;
            writeFileinfo();
            readNewPicture();
        }
        else if(event->key()==Qt::Key_K||event->key()==Qt::Key_Up)
        {
            if(fileinfo.curNum==0) return ;
            fileinfo.curNum--;
            while(deleteLicense.contains(fileinfo.curNum))
                fileinfo.curNum--;
            writeFileinfo();
            readNewPicture();
        }
        else if(event->key()==Qt::Key_F)
        {
            ui->label->pianyiright+=STEP;
            ui->label->isModify = true;
            ui->label->update();
            keyStack.push(1);
        }
        else if(event->key()==Qt::Key_S)
        {
            ui->label->pianyileft+=STEP;
            ui->label->isModify = true;
            ui->label->update();
            keyStack.push(2);
        }
        else if(event->key()==Qt::Key_D)
        {
            ui->label->pianyibottom+=STEP_Y;
            ui->label->isModify = true;
            ui->label->update();
            keyStack.push(3);
        }
        else if(event->key()==Qt::Key_E)
        {
            ui->label->pianyitop+=STEP_Y;
            ui->label->isModify = true;
            ui->label->update();
            keyStack.push(4);
        }
        else if(event->key()==Qt::Key_R)
        {
            if(!keyStack.empty())
            switch (keyStack.pop()) {
                case 1:{
                    ui->label->pianyiright-=STEP;
                    break;
                }
                case 2:{
                    ui->label->pianyileft-=STEP;
                    break;
                }
                case 3:{
                    ui->label->pianyibottom-=STEP_Y;
                    break;
                }
                case 4:{
                    ui->label->pianyitop-=STEP_Y;
                    break;
                }
            }
            ui->label->isModify = true;
            ui->label->update();
        }



    }


}

bool Mainwindow::readNewPicture()
{

    keyStack.clear();
    if(list.size()==0)
    {
        QMessageBox::warning(this,"Error Message:","该路径下无图片文件.");
        return false;
    }
    int   num = fileinfo.curNum;

    if(num<list.size())
    {
        //progress
        progress.setValue(100*(num+1)/list.size());


        QFileInfo finfo = list.at(num);

        filename = finfo.fileName();
        ui->label->setNewLicense(finfo.filePath());

    }


    return true;

}

bool Mainwindow::readFileinfo()
{

    QFile *file = new QFile("fileinfo_mode1");
    bool ok = file->open(QIODevice::ReadOnly|QIODevice::Text);

    if(ok)
    {
        QTextStream in(file);
        in>>fileinfo.curNum;

        file->close();
        delete file;
        return true;
    }

    return false;
}

bool Mainwindow::writeFileinfo()
{

    QFile *file = new QFile("fileinfo_mode1");
    bool ok = file->open(QIODevice::WriteOnly|QIODevice::Text);

    if(ok)
    {
        QTextStream out(file);
        out<<fileinfo.curNum;

        file->close();
        delete file;
        return true;
    }

    return false;
}


bool Mainwindow::removeAll(bool)
{
    QSetIterator<int> i(deleteLicense);

    int small = 0;
    int cur = fileinfo.curNum;
     while (i.hasNext())
     {
         int dd = i.next();
         if(dd<cur)
             small++;

         QString filepath = list.at(dd).filePath();
         QString filename = list.at(dd).fileName().split(".").at(0);
         //remove origin file
         QFile file(filepath);
         if(!file.remove())
         {
             QMessageBox::warning(this,"Error123", "移除失败");
                qDebug()<<"123";
             exit(0);
         }
         else
         {
             qDebug() <<"remove:"<<dd;
         }

         if(ui->label->isSaved)
         {
             //remove locate txt and copy jpg
             QString txtfilepath("licenseSplitData/licenses_no_class/");
             QFile file1(txtfilepath+filename+".jpg");
             if(file1.exists())
                 if(!file1.remove())
                     qDebug()<<"jpgfile remove fail";
             QFile file2(txtfilepath+filename+".txt");
             if(file2.exists())
                 if(!file2.remove())
                     qDebug()<<"txtfile remove fail";

             //remove character jpg
             QString charPath = "licenseSplitData/characters_in_licenses/";
             QFile *ff = new QFile();
             for(int i=0;i<7;i++)
             {
                 ff->setFileName(charPath+QString("%1_%2.jpg").arg(filename).arg(i));
                 if(!ff->exists())
                     qDebug()<<"charFile no exist";
                 if(!ff->remove())
                     qDebug()<<"charFile remove fail";
             }

         }

     }

     fileinfo.curNum-=small;
     writeFileinfo();


     this->close();
     return true;
}

bool Mainwindow::renameAll()
{

    /*
    for(int num=0; num<list.size(); num++)
    {

        QFileInfo finfo = list.at(num);

        QPixmap *curp = new QPixmap(finfo.filePath());
        if(curp->save(QString("2/%1.jpg").arg(num)))
        qDebug()<<num<<"ddd";

    }
    ui->statusBar->showMessage("ok");

    */
    return true;
}

bool Mainwindow::analyzeKey(int key)
{

    //QMap<int, QString> keyToChar_Map;
    //QMap<QString, QString> pyToWord_Map;
    //QMap<QString, int> wordToClass_Map;
    //QMap<QString, int> wordToClass_Map;



    if(keyToChar_Map.contains(key))
    {
        bool isProvince = false;
        isProvince = (ui->curlabel->curCharname.split("_").at(1)=="0")?true:false;

        if(!isProvince)
        {
            QString value = keyToChar_Map.value(key);
            if(value=="I")
            {
                value=QString("1");
            }
            else if(value=="O")
            {
               value=QString("0");
            }

            int clas =wordToClass_Map.value(value);
            ui->curlabel->saveCurCharTxt(clas);
                ui->curlabel->showSwitch = false;
                ui->curlabel->showList.clear();
            return true;
        }
        else
        {
            QString value = keyToChar_Map.value(key);
            if(!recording)
                curProvince = value;
            else
            {
                curProvince.append(value);
            }

            QStringList prolist = pyToWord_Map.keys();
            readyList.clear();
            foreach (QString curs, prolist) {
                if(curs.toUpper()==(curProvince))
                {

                    int clas = wordToClass_Map.value(pyToWord_Map.value(curs));
                    ui->curlabel->saveCurCharTxt(clas);
                    recording = false;
                    curProvince.clear();
                    ui->curlabel->showSwitch = false;
                    ui->curlabel->showList.clear();
                    return true;
                }
                else if(curs.toUpper().contains(curProvince)&&curs.toUpper().indexOf(curProvince)==0)
                {
                    readyList.append(curs);
                }
            }

            if(readyList.size()==1)
            {
                int clas = wordToClass_Map.value(pyToWord_Map.value(readyList.at(0)));
                ui->curlabel->saveCurCharTxt(clas);
                recording = false;
                curProvince.clear();
                ui->curlabel->showSwitch = false;
                ui->curlabel->showList.clear();
                return true;
            }
            else if(readyList.size()==0)
            {
                curProvince.clear();
                recording = false;
                ui->curlabel->showSwitch = false;
                ui->curlabel->showList.clear();
                return false;
            }
            else
            {
                showAllReadyList();
                recording = true;
                return false;
            }

        }
    }
    return false;



}

void Mainwindow::initAllMap()
{

    //key to char

    //number
    keyToChar_Map.insert(48,"0");
    keyToChar_Map.insert(49,"1");
    keyToChar_Map.insert(50,"2");
    keyToChar_Map.insert(51,"3");
    keyToChar_Map.insert(52,"4");
    keyToChar_Map.insert(53,"5");
    keyToChar_Map.insert(54,"6");
    keyToChar_Map.insert(55,"7");
    keyToChar_Map.insert(56,"8");
    keyToChar_Map.insert(57,"9");

    //letter
    keyToChar_Map.insert(65,"A");
    keyToChar_Map.insert(66,"B");
    keyToChar_Map.insert(67,"C");
    keyToChar_Map.insert(68,"D");
    keyToChar_Map.insert(69,"E");
    keyToChar_Map.insert(70,"F");
    keyToChar_Map.insert(71,"G");
    keyToChar_Map.insert(72,"H");
    keyToChar_Map.insert(73,"I");
    keyToChar_Map.insert(74,"J");
    keyToChar_Map.insert(75,"K");
    keyToChar_Map.insert(76,"L");
    keyToChar_Map.insert(77,"M");
    keyToChar_Map.insert(78,"N");
    keyToChar_Map.insert(79,"O");
    keyToChar_Map.insert(80,"P");
    keyToChar_Map.insert(81,"Q");
    keyToChar_Map.insert(82,"R");
    keyToChar_Map.insert(83,"S");
    keyToChar_Map.insert(84,"T");
    keyToChar_Map.insert(85,"U");
    keyToChar_Map.insert(86,"V");
    keyToChar_Map.insert(87,"W");
    keyToChar_Map.insert(88,"X");
    keyToChar_Map.insert(89,"Y");
    keyToChar_Map.insert(90,"Z");

    //pinYin to word


    QFile *file = new QFile("pinYin_of_provinces");
    bool ok = file->open(QIODevice::ReadOnly|QIODevice::Text);

    if(ok)
    {

        QTextStream in(file);
        QString py, word;

        while(!in.atEnd())
        {
            in>>py>>word;
            if(py=="#end")
            {
                break;
            }
            pyToWord_Map.insert(py,word);
        }
        file->close();
        delete file;
    }
    else
    {
        QMessageBox::warning(this, "error 9008", "丢失拼音文件,请创建");
        return ;
    }


    //char To class

    //number
    wordToClass_Map.insert("0",0);
    wordToClass_Map.insert("1",1);
    wordToClass_Map.insert("2",2);
    wordToClass_Map.insert("3",3);
    wordToClass_Map.insert("4",4);
    wordToClass_Map.insert("5",5);
    wordToClass_Map.insert("6",6);
    wordToClass_Map.insert("7",7);
    wordToClass_Map.insert("8",8);
    wordToClass_Map.insert("9",9);

    //letter
    wordToClass_Map.insert("A",10);
    wordToClass_Map.insert("B",11);
    wordToClass_Map.insert("C",12);
    wordToClass_Map.insert("D",13);
    wordToClass_Map.insert("E",14);
    wordToClass_Map.insert("F",15);
    wordToClass_Map.insert("G",16);
    wordToClass_Map.insert("H",17);
    wordToClass_Map.insert("J",18);
    wordToClass_Map.insert("K",19);
    wordToClass_Map.insert("L",20);
    wordToClass_Map.insert("M",21);
    wordToClass_Map.insert("N",22);
    wordToClass_Map.insert("P",23);
    wordToClass_Map.insert("Q",24);
    wordToClass_Map.insert("R",25);
    wordToClass_Map.insert("S",26);
    wordToClass_Map.insert("T",27);
    wordToClass_Map.insert("U",28);
    wordToClass_Map.insert("V",29);
    wordToClass_Map.insert("W",30);
    wordToClass_Map.insert("X",31);
    wordToClass_Map.insert("Y",32);
    wordToClass_Map.insert("Z",33);


    //provice to Class

    wordToClass_Map.insert("苏",34);
    wordToClass_Map.insert("浙",35);
    wordToClass_Map.insert("鲁",36);
    wordToClass_Map.insert("沪",37);
    wordToClass_Map.insert("皖",38);
    wordToClass_Map.insert("冀",39);
    wordToClass_Map.insert("豫",40);
    wordToClass_Map.insert("津",41);
    wordToClass_Map.insert("辽",42);
    wordToClass_Map.insert("湘",43);
    wordToClass_Map.insert("鄂",44);
    wordToClass_Map.insert("赣",45);
    wordToClass_Map.insert("甘",46);
    wordToClass_Map.insert("闽",47);
    wordToClass_Map.insert("黑",48);
    wordToClass_Map.insert("粤",49);
    wordToClass_Map.insert("贵",50);
    wordToClass_Map.insert("渝",51);
    wordToClass_Map.insert("京",52);
    wordToClass_Map.insert("晋",53);
    wordToClass_Map.insert("吉",54);
    wordToClass_Map.insert("蒙",55);
    wordToClass_Map.insert("桂",56);
    wordToClass_Map.insert("琼",57);
    wordToClass_Map.insert("川",58);
    wordToClass_Map.insert("云",59);
    wordToClass_Map.insert("藏",60);
    wordToClass_Map.insert("陕",61);
    wordToClass_Map.insert("青",62);
    wordToClass_Map.insert("宁",63);
    wordToClass_Map.insert("新",64);
    wordToClass_Map.insert("港",65);
    wordToClass_Map.insert("澳",66);
    wordToClass_Map.insert("使",67);
    wordToClass_Map.insert("领",68);
    wordToClass_Map.insert("学",69);
    wordToClass_Map.insert("警",70);


}

void Mainwindow::addProvice()
{

}

void Mainwindow::updateCurLabel(int )
{
    ui->curlabel->initCurLabel();
}

void Mainwindow::showAllReadyList()
{
    QString l;
    foreach (QString c, readyList) {
        l.append(QString("%1    %2.").arg(c).arg(pyToWord_Map.value(c)));
    }

    ui->curlabel->showSwitch = true;
    ui->curlabel->showList = l;
}

void Mainwindow::updataMarkProgress()
{
    if(ui->tabWidget->currentIndex()==1)
    {

        int curnum = ui->curlabel->curNum;
        int s = ui->curlabel->newList.size();

        if(s!=0)
        progress.setValue((curnum+1)*100/s);
    }
    else if(ui->tabWidget->currentIndex()==2)
    {

        int curnum = ui->checklabel->curNum;
        int s = ui->checklabel->size;
        qDebug()<<curnum<<"---"<<s<<endl;

        if(s!=0)
        progress.setValue((curnum+1)*100/s);
    }

}

void Mainwindow::on_pushButtonMergeAll_clicked()
{
    mergeThread->start();
    connect(this->mergeThread,SIGNAL(finished()),this,SLOT(threadOk()));
    qDebug()<<"Start merge:";
}

void Mainwindow::updataMergeProgress(int p)
{
    ui->pushButtonMergeAll->setText(QString("%1\%").arg(p));
}

void Mainwindow::threadOk()
{
        ui->checklabel->updateWindow();
}
