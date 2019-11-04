#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QApplication>
#include "frmInput/frminput.h"
#include "./mainWindow/MainWindow.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication app(argc, argv);
    QFont font = app.font();
    font.setPointSize(15);
    app.setFont(font);

    MainWindow* mainwindow = new MainWindow();
    mainwindow->setFocusPolicy(Qt::ClickFocus);

    QPalette palette;

    QPixmap pixmap;
    pixmap.load(":/images/images/screen.png");

    palette.setBrush(mainwindow->backgroundRole(),QBrush(pixmap.scaled(mainwindow->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    palette.setColor(QPalette::WindowText, "#000000");
    palette.setColor(QPalette::ButtonText, "#FFFFFF");
    palette.setColor(QPalette::Button, "#000000");
    palette.setColor(QPalette::Base,"#F6F5FE");
    mainwindow->setPalette(palette);

    frmInput::Instance()->Init();
    frmInput::Instance()->setMain(mainwindow);
    frmInput::Instance()->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus);

    mainwindow->show();

    return app.exec();
}
