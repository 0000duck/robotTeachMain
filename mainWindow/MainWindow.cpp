#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow()
{
    this->setFixedSize(1280, 800);
    this->move(0, 0);
    this->setAutoFillBackground(true);

    PATH= QDir(qApp->applicationDirPath());
    PATH.cdUp();

    m_robotTeachCount=0;
    m_robotTeach.clear();

    read_Cache();

    initUI();
    initState();

    myProcess = nullptr;

    connectSignalSlot();
}

MainWindow::~MainWindow()
{
}

void MainWindow::showEvent(QShowEvent *)
{
    this->setFocus();
}

QPushButton* MainWindow::initButton(string name)
{
    setStyleSheet("QPushButton{"
                  "border-radius:15px;"
                  "padding:2px 2px;"
                  "width:190px;"
                  "max-width:190px;"
                  "height:142px;"
                  "max-height:142px;"
                  "}" );
    if(name==string("robotTeachHR"))
    {
        m_robotTeachHR=new QPushButton();
        robotHR=1;
        QIcon iconHR(":/images/images/HRrobot.png");
        m_robotTeachHR->setIcon(iconHR);
        m_robotTeachHR->setIconSize(QSize(206,152));
        return m_robotTeachHR;
    }
    if(name==string("robotTeachABB"))
    {
        m_robotTeachABB=new QPushButton();
        robotABB=1;
        QIcon iconABB(":/images/images/ABBrobot.png");
        m_robotTeachABB->setIcon(iconABB);
        m_robotTeachABB->setIconSize(QSize(206,152));
        return m_robotTeachABB;
    }
    if(name==string("robotTeachKUKA"))
    {
        m_robotTeachKUKA=new QPushButton();
        robotKUKA=1;
        QIcon iconKUKA(":/images/images/KUKArobot.png");
        m_robotTeachKUKA->setIcon(iconKUKA);
        m_robotTeachKUKA->setIconSize(QSize(206,152));
        return m_robotTeachKUKA;
    }
    if(name==string("robotTeachFANUC"))
    {
        m_robotTeachFNK=new QPushButton();
        robotFNK=1;
        QIcon iconFNK(":/images/images/FNKrobot.png");
        m_robotTeachFNK->setIcon(iconFNK);
        m_robotTeachFNK->setIconSize(QSize(206,152));
        return m_robotTeachFNK;
    }
    if(name==string("robotTeachYASKAWA"))
    {
        m_robotTeachAC=new QPushButton();
        robotAC=1;
        QIcon iconAC(":/images/images/ACrobot.png");
        m_robotTeachAC->setIcon(iconAC);
        m_robotTeachAC->setIconSize(QSize(206,152));
        return m_robotTeachAC;
    }
    if(name==string("robotTeachGSK"))
    {
        m_robotTeachHS=new QPushButton();
        robotHS=1;
        QIcon iconHS(":/images/images/HSrobot.png");
        m_robotTeachHS->setIcon(iconHS);
        m_robotTeachHS->setIconSize(QSize(206,152));
        return m_robotTeachHS;
    }
}

void MainWindow::initUI()
{

    this->setWindowFlags(Qt::FramelessWindowHint);

    m_labelIP = new QLabel("控制器:");
    m_editIPAddr = new QLineEdit();
    m_editIPAddr->setFocusPolicy(Qt::ClickFocus);
    m_editIPAddr->setFixedSize(150, 50);
    m_editIPPort = new QLineEdit();
    m_editIPPort->setFocusPolicy(Qt::ClickFocus);
    m_editIPPort->setFixedSize(150, 50);

    QHBoxLayout* lineTCP=new QHBoxLayout();
    lineTCP->addWidget(m_labelIP);
    lineTCP->addWidget(m_editIPAddr);
    lineTCP->addWidget(m_editIPPort);

    m_labelLocalAddrTitle=new QLabel("本地IP地址:");

    QString temp;
    read_tcp_local(temp);
    m_labelLocalAddr=new QLabel(temp);

    QHBoxLayout* lineLocal=new QHBoxLayout();
    lineLocal->addWidget(m_labelLocalAddrTitle);
    lineLocal->addWidget(m_labelLocalAddr);

    QVBoxLayout* layoutAddress=new QVBoxLayout();
    layoutAddress->addLayout(lineTCP);
    layoutAddress->addLayout(lineLocal);

    QWidget* widgetTCP=new QWidget(this);
    widgetTCP->move(550,530);
    QVBoxLayout* layoutTCP = new QVBoxLayout(widgetTCP);
    layoutTCP->addLayout(layoutAddress);

    buttonChoice=new QWidget(this);
    buttonChoice->resize(660,330);
    buttonChoice->move(450,150);
    addButton(buttonChoice);

    m_pixLogo.load(":/images/images/logo.png");
    m_labelLogo = new QLabel();
    m_labelLogo->setScaledContents(true);
    m_labelLogo->clear();
    m_labelLogo->setPixmap(m_pixLogo);
    m_labelLogo->show();

    QWidget* widgetLogo = new QWidget(this);
    widgetLogo->move(0,600);
    widgetLogo->setFixedSize(460,106);
    QHBoxLayout* layoutLogo = new QHBoxLayout(widgetLogo);
    layoutLogo->addWidget(m_labelLogo,Qt::AlignVCenter);

    m_pixLogo1.load(":/images/images/robot.png");
    m_labelLogo1 = new QLabel();
    m_labelLogo1->setScaledContents(true);
    m_labelLogo1->clear();
    m_labelLogo1->setPixmap(m_pixLogo1);
    m_labelLogo1->show();

    QWidget* widgetLogo1 = new QWidget(this);
    widgetLogo1->move(65,50);
    widgetLogo1->setFixedSize(294,523);
    QHBoxLayout* layoutLogo1 = new QHBoxLayout(widgetLogo1);
    layoutLogo1->addWidget(m_labelLogo1,Qt::AlignVCenter);

    m_update=new QPushButton(this);
    m_update->setStyleSheet("background-color: rgb(96,96,96)");
    m_update->setText("更新");
    m_update->move(50,700);
    m_update->setFixedSize(100,75);

    tip=new QWidget();
    tip->setWindowFlags(Qt::FramelessWindowHint);
    tip->resize(300,200);
    tip->move(550,300);
    tip_text=new QLabel(tip);
    tip_text->setText("程序正在运行，请稍候");
    tip_text->move(50,80);
    tip->hide();

    tip_update=new QWidget();
    tip_update->setWindowFlags(Qt::FramelessWindowHint);
    tip_update->resize(300,200);
    tip_update->move(550,300);
    tip_text_update=new QLabel(tip_update);
    tip_text_update->setText("正在更新中...");
    tip_text_update->move(50,80);
    tip_update->hide();

    m_version = new QLabel(this);
    m_version->move(1150,720);
    m_version->resize(200,75);
    m_version->setText("版本:1.0.0");

    timer = new QTimer(this);
    timer->start(1000);
}

void MainWindow::addButton(QWidget* m_widget)
{
    QString path = QString(PATH.path());
    FindFile(path,"");

    QPushButton* tmp_button;
    if(m_robotTeachCount<=3)
    {
        layoutMain_H=new QHBoxLayout(m_widget);
        for(int i=0;i<m_robotTeach.size();i++)
        {
            tmp_button=initButton(m_robotTeach[i]);
            layoutMain_H->addWidget(tmp_button);
            tmp_button=nullptr;
        }
    }
    else
    {
        layoutMain_V=new QVBoxLayout(m_widget);
        layoutFirst=new QHBoxLayout();
        layoutSecond=new QHBoxLayout();
        for(int i=0;i<m_robotTeach.size();i++)
        {
            tmp_button=initButton(m_robotTeach[i]);
            if(i<=2)
                layoutFirst->addWidget(tmp_button);
            else
                layoutSecond->addWidget(tmp_button);
            tmp_button=nullptr;
        }
        layoutMain_V->addLayout(layoutFirst);
        layoutMain_V->addLayout(layoutSecond); 
    }

    m_robotTeachCount=0;
    m_robotTeach.clear();
}


void MainWindow::initState()
{
    initTCPConfig();
}

void MainWindow::connectSignalSlot()
{
    QObject::connect(m_editIPAddr, SIGNAL(editingFinished()), this, SLOT(tcpConfigChanged()));
    QObject::connect(m_editIPPort, SIGNAL(editingFinished()), this, SLOT(tcpConfigChanged()));

    if(robotHR)
    {
        QObject::connect(m_robotTeachHR, SIGNAL(clicked()), this, SLOT(buttonHRConnectClicked()));
    }
    if(robotABB)
    {
        QObject::connect(m_robotTeachABB, SIGNAL(clicked()), this, SLOT(buttonABBConnectClicked()));
    }
    if(robotKUKA)
    {
        QObject::connect(m_robotTeachKUKA, SIGNAL(clicked()), this, SLOT(buttonKUKAConnectClicked()));
    }
    if(robotFNK)
    {
        QObject::connect(m_robotTeachFNK, SIGNAL(clicked()), this, SLOT(buttonFNKConnectClicked()));
    }
    if(robotAC)
    {
        QObject::connect(m_robotTeachAC, SIGNAL(clicked()), this, SLOT(buttonACConnectClicked()));
    }
    if(robotHS)
    {
        QObject::connect(m_robotTeachHS, SIGNAL(clicked()), this, SLOT(buttonHSConnectClicked()));
    }

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(tcpLocalChanged()));
    QObject::connect(m_update, SIGNAL(clicked()), this, SLOT(systemUpdate()));

    QObject::connect(this, SIGNAL(signal_tipshow(bool)), this, SLOT(Tipshow(bool)));
    QObject::connect(this, SIGNAL(signal_tipshow_update(bool)), this, SLOT(Tipshow_update(bool)));
}

void MainWindow::deleteSignalSlot()
{
    if(robotHR)
    {
        robotHR=0;
        QObject::disconnect(m_robotTeachHR, SIGNAL(clicked()), this, SLOT(buttonHRConnectClicked()));
    }
    if(robotABB)
    {
        robotABB=0;
        QObject::disconnect(m_robotTeachABB, SIGNAL(clicked()), this, SLOT(buttonABBConnectClicked()));
    }
    if(robotKUKA)
    {
        robotKUKA=0;
        QObject::disconnect(m_robotTeachKUKA, SIGNAL(clicked()), this, SLOT(buttonKUKAConnectClicked()));
    }
    if(robotFNK)
    {
        robotFNK=0;
        QObject::disconnect(m_robotTeachFNK, SIGNAL(clicked()), this, SLOT(buttonFNKConnectClicked()));
    }
    if(robotAC)
    {
        robotAC=0;
        QObject::disconnect(m_robotTeachAC, SIGNAL(clicked()), this, SLOT(buttonACConnectClicked()));
    }
    if(robotHS)
    {
        robotHS=0;
        QObject::disconnect(m_robotTeachHS, SIGNAL(clicked()), this, SLOT(buttonHSConnectClicked()));
    }
}

void MainWindow::initTCPConfig()
{
    m_editIPAddr->setText(QString::fromStdString(m_IP));
    m_editIPPort->setText(QString::number(m_Port, 10));
}

void MainWindow::read_Cache(){
    QDir tmp_Path=PATH;
    tmp_Path.cd("robotTeachMain");
    tmp_Path.cd("config");
    path_cache=tmp_Path.path()+QString("/Cache.xml");
    xmlDocPtr xmlDoc = xmlReadFile(path_cache.toUtf8().data(), "UTF-8", XML_PARSE_NOBLANKS);
    xmlNodePtr rootNode = xmlDocGetRootElement(xmlDoc);

    if(!rootNode)
    {
        cout << "failed to open cache xml" << endl;
        return;
    }

    xmlNodePtr ptrNode = rootNode->children;

    while(ptrNode != NULL){
        xml_judge_read_string("m_IP", ptrNode, m_IP);
        xml_judge_read_num("m_Port", ptrNode, m_Port);

        ptrNode = ptrNode->next;
    }
    xmlFreeDoc(xmlDoc);
}

void MainWindow::write_Cache(){
    xmlDocPtr xmlDoc = xmlNewDoc((const xmlChar*)"1.0");
    xmlNodePtr rootNode = xmlNewNode(0, BAD_CAST "cache");
    xmlDocSetRootElement(xmlDoc, rootNode);

    xml_addchild_string("m_IP", m_IP, rootNode);
    xml_addchild_num("m_Port", m_Port, rootNode);

    xmlSaveFormatFileEnc(path_cache.toUtf8().data(), xmlDoc, "UTF-8", 1);
    xmlFreeDoc(xmlDoc);
}

void MainWindow::tcpConfigChanged()
{
        m_IP = m_editIPAddr->text().toStdString();
        m_Port = m_editIPPort->text().toInt();

        write_Cache();
}

void MainWindow::read_tcp_local(QString &localIP)
{
    foreach (QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        QList<QNetworkAddressEntry> entryList = netInterface.addressEntries();
        foreach(QNetworkAddressEntry entry, entryList)
        {
            if(entry.ip().protocol()==QAbstractSocket::IPv4Protocol)
            {
                localIP=entry.ip().toString();
                if(localIP!=QString("127.0.0.1"))
                    return;
            }
        }
    }
    localIP=QString("127.0.0.1");
}

int MainWindow::FindFile(const QString &path,const QString &name)
{
    QDir dir(path);
    if(!dir.exists())
    {
        cout << "查找的路径不存在" << endl;
        return 1;
    }
    dir.setFilter(QDir::Dirs | QDir::Files);
    dir.setSorting(QDir::DirsFirst);//文件夹排在前面
    QFileInfoList list = dir.entryInfoList();
    int i = 0;

    bool IsDir;
    bool IsFile;
    do
    {
        QFileInfo fileInfo = list.at(i);
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
        {
            ++i;
            continue;
        }
        IsDir = fileInfo.isDir();
        IsFile = fileInfo.isFile();
        if(IsDir)
        {
            m_DirCount++;
            FindFile(fileInfo.filePath(),name);
        }
        else if(IsFile)
        {
            m_FilesCount++;

            if(fileInfo.fileName()==name)
            {
                return 2;
            }
            if(fileInfo.fileName()=="robotTeachHR" || fileInfo.fileName()=="robotTeachABB" || fileInfo.fileName()=="robotTeachKUKA" ||
                    fileInfo.fileName()=="robotTeachFANUC" || fileInfo.fileName()=="robotTeachYASKAWA" || fileInfo.fileName()=="robotTeachGSK")
            {
                string tmp=fileInfo.fileName().toStdString();
                m_robotTeach.push_back(tmp);
                m_robotTeachCount++;
            }
        }
        ++i;
    }while(i < list.size());

    return 0;
}

void MainWindow::time_sleep()
{
    QTime dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
}


void MainWindow::tcpLocalChanged()
{
    QString temp;
    read_tcp_local(temp);
    m_labelLocalAddr->setText(temp);
}

void MainWindow::buttonHRConnectClicked()
{  
    emit signal_tipshow(true);
    time_sleep();
    QString path = PATH.path()+QString("/robotTeachHR/robotTeachHR %1 %2").arg(m_editIPAddr->text()).arg(m_editIPPort->text());
    if(myProcess==nullptr)
    {
        myProcess = new QProcess(this);
        QObject::connect(myProcess, SIGNAL(finished(int)), this, SLOT(nullProcess()));
        myProcess->start(path);
        myProcess->waitForFinished(-1);
        emit signal_tipshow(false);
    }
}

void MainWindow::buttonABBConnectClicked()
{
    emit signal_tipshow(true);
    time_sleep();
    QString path = PATH.path()+QString("/robotTeachABB/robotTeachABB %1 %2").arg(m_editIPAddr->text()).arg(m_editIPPort->text());
    if(myProcess==nullptr)
    {
        myProcess = new QProcess(this);
        QObject::connect(myProcess, SIGNAL(finished(int)), this, SLOT(nullProcess()));
        myProcess->start(path);
        myProcess->waitForFinished(-1);
        emit signal_tipshow(false);
    }
}

void MainWindow::buttonKUKAConnectClicked()
{
    emit signal_tipshow(true);
    time_sleep();
    QString path = PATH.path()+QString("/robotTeachKUKA/robotTeachKUKA");
    if(myProcess==nullptr)
    {
        myProcess = new QProcess(this);
        QObject::connect(myProcess, SIGNAL(finished(int)), this, SLOT(nullProcess()));
        myProcess->start(path);
        myProcess->waitForFinished(-1);
        emit signal_tipshow(false);
    }
}

void MainWindow::buttonFNKConnectClicked()
{
    emit signal_tipshow(true);
    time_sleep();
    QString path = PATH.path()+QString("/robotTeachFANUC/robotTeachFANUC");
    if(myProcess==nullptr)
    {
        myProcess = new QProcess(this);
        QObject::connect(myProcess, SIGNAL(finished(int)), this, SLOT(nullProcess()));
        myProcess->start(path);
        myProcess->waitForFinished(-1);
        emit signal_tipshow(false);
    }
}

void MainWindow::buttonACConnectClicked()
{
    emit signal_tipshow(true);
    time_sleep();
    QString path = PATH.path()+QString("/robotTeachYASKAWA/robotTeachYASKAWA");
    if(myProcess==nullptr)
    {
        myProcess = new QProcess(this);
        QObject::connect(myProcess, SIGNAL(finished(int)), this, SLOT(nullProcess()));
        myProcess->start(path);
        myProcess->waitForFinished(-1);
        emit signal_tipshow(false);
    }
}

void MainWindow::buttonHSConnectClicked()
{
    emit signal_tipshow(true);
    time_sleep();
    QString path = PATH.path()+QString("/robotTeachGSK/robotTeachGSK");
    if(myProcess==nullptr)
    {
        myProcess = new QProcess(this);
        QObject::connect(myProcess, SIGNAL(finished(int)), this, SLOT(nullProcess()));
        myProcess->start(path);
        myProcess->waitForFinished(-1);
        emit signal_tipshow(false);
    }
}

void MainWindow::nullProcess()
{
    QProcess *ps = (QProcess*)sender();

    if(ps == myProcess)
        myProcess = nullptr;

    delete ps;
}

void MainWindow::systemUpdate()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("提示"),
                                    tr("确认更新系统？\n系统更新完成后，会自动重启！"),
                                    QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No)
        return;

    emit signal_tipshow_update(true);

    time_sleep();

    FILE *fp;
    do{
        fp=popen("sudo ./update.sh", "w");
        if(!fp){
            printf("fail to start shell\n");
        }
    }
    while(!fp);
    pclose(fp);
    buttonChoice->deleteLater();

    buttonChoice=new QWidget(this);
    buttonChoice->resize(660,330);
    buttonChoice->move(450,150);

    deleteSignalSlot();
    addButton(buttonChoice);
    connectSignalSlot();

    buttonChoice->show();
    signal_tipshow_update(false);
    QMessageBox::about(this, "提示", "更新已完成, 即将重启！");

    do{
        fp=popen("sudo reboot", "w");
        if(!fp){
            printf("fail to start shell\n");
        }
    }
    while(!fp);
    pclose(fp);
}

void MainWindow::Tipshow_update(bool state)
{
    if(state)
    {
        tip_update->show();
        this->setEnabled(false);
    }
    else
    {
        tip_update->hide();
        this->setEnabled(true);
    }
}

void MainWindow::Tipshow(bool state)
{
    if(state)
    {
        tip->show();
        this->setEnabled(false);
    }
    else
    {
        tip->hide();
        this->setEnabled(true);
    }
}

