#include "mythread.h"

MyThread::MyThread(int function, QString zongPath, QString charsPath)
{
    FUNCTION = function;
    path1 = zongPath;
    path2 = charsPath;

}

void MyThread::run()
{

    if(FUNCTION==1)
    {

        createMergeFolder();
        mergeAllTxt();
        emit ok(true);
    }
}


void MyThread::readMergedList()
{
    QFile *f = new QFile("mergeList");
    if(f->exists())
    {
        bool ok = f->open(QIODevice::ReadOnly|QIODevice::Text);

        if(ok)
        {
            QString temp;
            QTextStream in(f);
            while(!in.atEnd())
            {
                in>>temp;
                mergeSet.insert(temp);
            }
            f->close();
            delete f;
        }
        else
            qDebug()<<"open fail mergelist";
    }

}

void MyThread::mergeAllTxt()
{

    mergeSet.clear();
    readMergedList();

    QFile *fMergeList = new QFile("mergeList");
    bool ok = fMergeList->open(QIODevice::WriteOnly|QIODevice::Text);
    if(ok)
    {

        readTxtList();

        for(int i=0;i<txtList.size();i++)
        {
            Progress((i+1)*100/txtList.size());
            QString fileNumber = txtList.at(i).fileName().split(".").at(0);
            if(mergeSet.contains(fileNumber))
            {
                qDebug()<<fileNumber<<"already merge";
                continue;
            }
            else
            {
                bool fail = false;
                QFile fc[7];  //there are 7 character txt file.
                int clas[7];
                for(int i=0;i<7;i++)
                {
                    fc[i].setFileName(path2+"/"+fileNumber+"_"+QString::number(i)+".txt");
                    if(!fc[i].exists())
                    {
                        qDebug()<<fc[i].fileName()<<"no exist.";
                        fail = true;
                        break;
                    }
                    bool ok = fc[i].open(QIODevice::ReadOnly|QIODevice::Text);
                    if(!ok)
                    {
                       fail = true;
                        qDebug()<<fc[i].fileName()<<"open fail.";
                        break;

                    }

                    clas[i] = fc[i].readAll().toInt();

                    fc[i].close();

                }

                if(fail) continue;

                QFile *fz = new QFile(path1+"/"+fileNumber+".txt");
                bool ok = fz->open(QIODevice::ReadOnly|QIODevice::Text);
                QString line[7];

                if(ok)
                {
                    //QTextStream in(fz);
                    //QString tx,ty,tw,th;

                    for(int i=0;i<7;i++)
                    {
                        line[i] = QString(fz->readLine()).split("\n").at(0);//去掉结尾的\n
                    }
                    fz->close();
                    delete fz;
                }
                else
                {
                    qDebug()<<fz->fileName()<<"open fail   no    have-----------------.";
                    continue;
                }

                QFile *newfz = new QFile("licenseSplitData/mergeFolder/"+fileNumber+".txt");
                bool ok2 = newfz->open(QIODevice::WriteOnly|QIODevice::Text);
                if(ok2)
                {
                    QTextStream out(newfz);
                    for(int i=0;i<7;i++)
                    {
                        out<<clas[i]<<" "<<line[i]<<endl;
                    }
                    newfz->close();
                    delete newfz;

                    mergeSet.insert(fileNumber);
                }
                else
                {
                    qDebug()<<newfz->fileName()<<"open fail in write.";
                    continue;
                }


            }
        }

        //write merge List

        QTextStream out2(fMergeList);
        QSetIterator<QString> it(mergeSet);
        QString temp;
        while(it.hasNext())
        {
            temp = it.next();
            if(!temp.isEmpty())
            out2<<temp<<endl;
        }
        fMergeList->close();
        delete fMergeList;
    }
}

void MyThread::readTxtList()
{

    QDir dir;
    dir.setPath("licenseSplitData/licenses_no_class");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);

    QFileInfoList list = dir.entryInfoList();
    txtList.clear();

    for(int i=0;i<list.size();i++)
    {
        if(list.at(i).fileName().contains(".txt"))
        {
            txtList.append(list.at(i));
        }
    }
}

void MyThread::createMergeFolder()
{
    QDir *dir = new QDir();
    bool ex = dir->exists("licenseSplitData/mergeFolder");

    if(!ex)
    {
        bool ok = dir->mkdir("licenseSplitData/mergeFolder");
        if(!ok )
            QMessageBox::warning(NULL,tr("创建文件夹"),tr("文件夹licenseSplitData/mergeFolder创建失败！"));
    }
}
