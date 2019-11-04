#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTableWidgetItem>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QListView>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QProcess>
#include <QTimer>
#include <QMutex>
#include <QtNetwork>
#include <QFile>
#include <QDir>

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include <QApplication>
#include <QDir>

#include <thread>

#include <sstream>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlreader.h>

#include "../CFileIO.hpp"
//#include "../macroDefine.h"

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    void showEvent(QShowEvent *);
    QPushButton* initButton(std::string);
    void addButton(QWidget *);

private:
    void initUI();
    void initState();
    void connectSignalSlot();
    void deleteSignalSlot();

    void initTCPConfig();
    bool initTCPConnect();
    void read_Cache();
    void write_Cache();
//    int checkState();

    void read_tcp_local(QString &m_IP);

    int  FindFile(const QString &path,const QString &name);

    void time_sleep();

private:  
    QDir PATH;

    QString path_cache;
    QWidget* buttonChoice;

    std::vector<std::string> m_robotTeach;
    std::string m_IP;
    int m_Port;

    QPushButton* m_robotTeachHR;
    QPushButton* m_robotTeachABB;
    QPushButton* m_robotTeachKUKA;
    QPushButton* m_robotTeachFNK;
    QPushButton* m_robotTeachAC;
    QPushButton* m_robotTeachHS;

    bool robotHR=0;
    bool robotABB=0;
    bool robotKUKA=0;
    bool robotFNK=0;
    bool robotAC=0;
    bool robotHS=0;

    QVBoxLayout* layoutMain_V;
    QHBoxLayout* layoutMain_H;
    QHBoxLayout* layoutFirst;
    QHBoxLayout* layoutSecond;

    QPushButton* m_update;

    QLabel* m_labelIP;
    QLineEdit* m_editIPAddr;
    QLineEdit* m_editIPPort;

    QLabel* m_labelLocalAddrTitle;
    QLabel* m_labelLocalAddr;

    QPixmap m_pixLogo;
    QLabel* m_labelLogo;

    QPixmap m_pixLogo1;
    QLabel* m_labelLogo1;

    QLabel* m_version;

    QTimer* timer;

    QProcess* myProcess;

    int m_DirCount=0;
    int m_FilesCount=0;
    int m_robotTeachCount=0;

    QWidget* tip;
    QLabel* tip_text;

    QWidget* tip_update;
    QLabel* tip_text_update;
private slots:
    void tcpConfigChanged();

    void buttonHRConnectClicked();
    void buttonABBConnectClicked();
    void buttonKUKAConnectClicked();
    void buttonFNKConnectClicked();
    void buttonACConnectClicked();
    void buttonHSConnectClicked();

    void tcpLocalChanged();
    void nullProcess();
    void systemUpdate();

    void Tipshow(bool state);
    void Tipshow_update(bool state);

signals:
    void buttonOneClicked();
    void signal_tipshow(bool);
    void signal_tipshow_update(bool);
};

#endif // MAINWINDOW_H
