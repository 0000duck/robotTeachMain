#include "frminput.h"
#include "ui_frminput.h"
#include "QtWidgets/QDesktopWidget"

#include<QDebug>

frmInput *frmInput::_instance = 0;
frmInput::frmInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmInput)
{
    ui->setupUi(this);
    this->InitProperty();
    this->InitForm();
    changeStyle("#4D4D4D", "#292929", "#D9D9D9", "#CACAD0");
}

frmInput::~frmInput()
{
    delete ui;
}

void frmInput::Init()
{
    this->btnFontSize = 10;
    this->labFontSize = 30;
    changeStyle("#4D4D4D", "#292929", "#D9D9D9", "#CACAD0");
    this->ChangeFont();

    ui->btnSpace->hide();
    ui->btnOther17->hide();
    ui->btnOther21->hide();
    ui->btnOther14->hide();
    ui->btnOther18->hide();
    ui->btnOther16->hide();
    ui->btnOther15->hide();
    ui->btnOther13->hide();
    ui->btnOther12->hide();
    ui->btnOther11->hide();
    ui->btnOther20->hide();
    ui->btnOther19->hide();
    ui->btnOther8->hide();
    ui->btnOther7->hide();
    ui->btnOther6->hide();
    ui->btnOther4->hide();
    ui->btnOther3->hide();
    ui->btnOther2->hide();
    ui->btnOther5->hide();
    ui->btnOther1->hide();

    ui->lay1->setContentsMargins(0, 0, 0, 0);
    ui->lay1->setSpacing(0);
}

void frmInput::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void frmInput::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void frmInput::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void frmInput::InitForm()
{
    this->mousePressed = false;
    //this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint); //Qt4和Qt5通用，但是在表格控件中使用会导致程序崩溃
//    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus); //在表格控件中不会崩溃，但是Qt4将无法使用

    QDesktopWidget w;
    deskWidth = w.availableGeometry().width();
    deskHeight = w.availableGeometry().height();
    frmWidth = this->width();
    frmHeight = this->height();

    isFirst = true;
    isPress = false;
    timerPress = new QTimer(this);
    connect(timerPress, SIGNAL(timeout()), this, SLOT(reClicked()));

    currentWidget = 0;
    currentLineEdit = 0;
    currentTextEdit = 0;
    currentPlain = 0;
    currentBrowser = 0;
    currentEditType = "";

    //输入法面板字体大小,如果需要更改面板字体大小,该这里即可
    btnFontSize = 10;
    labFontSize = 10;

    //如果需要更改输入法初始模式,改变currentType这个变量即可
    //min--小写模式  max--大写模式  chinese--中文模式
    currentType = "min";
    changeType(currentType);

    QList<QPushButton *> btn = this->findChildren<QPushButton *>();
    foreach (QPushButton * b, btn) {
        connect(b, SIGNAL(clicked()), this, SLOT(btn_clicked()));
    }

    //绑定全局改变焦点信号槽
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
            this, SLOT(focusChanged(QWidget *, QWidget *)));
}

void frmInput::InitProperty()
{
    ui->btnOther1->setProperty("btnOther", true);
    ui->btnOther2->setProperty("btnOther", true);
    ui->btnOther3->setProperty("btnOther", true);
    ui->btnOther4->setProperty("btnOther", true);
    ui->btnOther5->setProperty("btnOther", true);
    ui->btnOther6->setProperty("btnOther", true);
    ui->btnOther7->setProperty("btnOther", true);
    ui->btnOther8->setProperty("btnOther", true);
    ui->btnOther9->setProperty("btnOther", true);
    ui->btnOther10->setProperty("btnOther", true);
    ui->btnOther11->setProperty("btnOther", true);
    ui->btnOther12->setProperty("btnOther", true);
    ui->btnOther13->setProperty("btnOther", true);
    ui->btnOther14->setProperty("btnOther", true);
    ui->btnOther15->setProperty("btnOther", true);
    ui->btnOther16->setProperty("btnOther", true);
    ui->btnOther17->setProperty("btnOther", true);
    ui->btnOther18->setProperty("btnOther", true);
    ui->btnOther19->setProperty("btnOther", true);
    ui->btnOther20->setProperty("btnOther", true);
    ui->btnOther21->setProperty("btnOther", true);

    ui->btnDot->setProperty("btnOther", true);
    ui->btnSpace->setProperty("btnOther", true);
    ui->btnDelete->setProperty("btnOther", true);

    ui->btn0->setProperty("btnNum", true);
    ui->btn1->setProperty("btnNum", true);
    ui->btn2->setProperty("btnNum", true);
    ui->btn3->setProperty("btnNum", true);
    ui->btn4->setProperty("btnNum", true);
    ui->btn5->setProperty("btnNum", true);
    ui->btn6->setProperty("btnNum", true);
    ui->btn7->setProperty("btnNum", true);
    ui->btn8->setProperty("btnNum", true);
    ui->btn9->setProperty("btnNum", true);
    ui->btn00->setProperty("btnNum", true);

    ui->btna->setProperty("btnLetter", true);
    ui->btnb->setProperty("btnLetter", true);
    ui->btnc->setProperty("btnLetter", true);
    ui->btnd->setProperty("btnLetter", true);
    ui->btne->setProperty("btnLetter", true);
    ui->btnf->setProperty("btnLetter", true);
    ui->btng->setProperty("btnLetter", true);
    ui->btnh->setProperty("btnLetter", true);
    ui->btni->setProperty("btnLetter", true);
    ui->btnj->setProperty("btnLetter", true);
    ui->btnk->setProperty("btnLetter", true);
    ui->btnl->setProperty("btnLetter", true);
    ui->btnm->setProperty("btnLetter", true);
    ui->btnn->setProperty("btnLetter", true);
    ui->btno->setProperty("btnLetter", true);
    ui->btnp->setProperty("btnLetter", true);
    ui->btnq->setProperty("btnLetter", true);
    ui->btnr->setProperty("btnLetter", true);
    ui->btns->setProperty("btnLetter", true);
    ui->btnt->setProperty("btnLetter", true);
    ui->btnu->setProperty("btnLetter", true);
    ui->btnv->setProperty("btnLetter", true);
    ui->btnw->setProperty("btnLetter", true);
    ui->btnx->setProperty("btnLetter", true);
    ui->btny->setProperty("btnLetter", true);
    ui->btnz->setProperty("btnLetter", true);
}

void frmInput::ShowPanel()
{
    this->setVisible(true);
}

bool frmInput::checkPress()
{
    //只有属于输入法键盘的合法按钮才继续处理
    bool num_ok = btnPress->property("btnNum").toBool();
    bool other_ok = btnPress->property("btnOther").toBool();
    bool letter_ok = btnPress->property("btnLetter").toBool();
    if (num_ok || other_ok || letter_ok) {
        return true;
    }
    return false;
}

void frmInput::reClicked()
{
    if (isPress) {
        timerPress->setInterval(30);
        btnPress->click();
    }
}

void frmInput::setMain(QWidget *main)
{
    Main = main;
}

void frmInput::focusChanged(QWidget *oldWidget, QWidget *nowWidget)
{
//    qDebug() << "oldWidget:" << oldWidget << " nowWidget:" << nowWidget;
    if (nowWidget != 0 && !this->isAncestorOf(nowWidget)) {
        //在Qt5和linux系统中(嵌入式linux除外),当输入法面板关闭时,焦点会变成无,然后焦点会再次移到焦点控件处
        //这样导致输入法面板的关闭按钮不起作用,关闭后马上有控件获取焦点又显示.
        //为此,增加判断,当焦点是从有对象转为无对象再转为有对象时不要显示.
        //这里又要多一个判断,万一首个窗体的第一个焦点就是落在可输入的对象中,则要过滤掉
#ifndef __arm__
        if (oldWidget == 0x0 && !isFirst) {
            return;
        }
#endif

        isFirst = false;
        QWidget * pModalWidget = QApplication::activeModalWidget () ;

        if (NULL != pModalWidget && pModalWidget->inherits("QDialog"))
        {
            Qt::WindowModality Modality = pModalWidget->windowModality();
          /*Qt::NonModal       The window is not modal and does not block input to other windows.
          非模态对话框

          Qt::WindowModal        The window is modal to a single window hierarchy and blocks input to its parent window, all grandparent windows, and all siblings of its parent and grandparent windows.
          窗口级模态对话框，即只会阻塞父窗口、父窗口的父窗口及兄弟窗口。（半模态对话框）

          Qt::ApplicationModal       The window is modal to the application and blocks input to all windows.
          应用程序级模态对话框，即会阻塞整个应用程序的所有窗口。（半模态对话框）
          */
            if(Qt::ApplicationModal == Modality)
            {
                //需要将输入法切换到最初的原始状态--小写,同时将之前的对象指针置为零
                currentWidget = 0;
                currentLineEdit = 0;
                currentTextEdit = 0;
                currentPlain = 0;
                currentBrowser = 0;
                currentEditType = "";
                currentType = "min";
                changeType(currentType);
                this->setVisible(false);
                return;
            }
        }
        if (nowWidget->inherits("QLineEdit")) {
            currentLineEdit = (QLineEdit *)nowWidget;
            currentEditType = "QLineEdit";
            ShowPanel();
        } else if (nowWidget->inherits("QTextEdit")) {
            currentTextEdit = (QTextEdit *)nowWidget;
            currentEditType = "QTextEdit";
            ShowPanel();
        } else if (nowWidget->inherits("QPlainTextEdit")) {
            currentPlain = (QPlainTextEdit *)nowWidget;
            currentEditType = "QPlainTextEdit";
            ShowPanel();
        } else if (nowWidget->inherits("QTextBrowser")) {
            currentBrowser = (QTextBrowser *)nowWidget;
            currentEditType = "QTextBrowser";
            ShowPanel();
        } else if (nowWidget->inherits("QComboBox")) {
            QComboBox *cbox = (QComboBox *)nowWidget;
            //只有当下拉选择框处于编辑模式才可以输入
            if (cbox->isEditable()) {
                currentLineEdit = cbox->lineEdit() ;
                currentEditType = "QLineEdit";
                ShowPanel();
            }
        } else if (nowWidget->inherits("QSpinBox") ||
                   nowWidget->inherits("QDoubleSpinBox") ||
                   nowWidget->inherits("QDateEdit") ||
                   nowWidget->inherits("QTimeEdit") ||
                   nowWidget->inherits("QDateTimeEdit")) {
            currentWidget = nowWidget;
            currentEditType = "QWidget";
            ShowPanel();
        } else {
            //需要将输入法切换到最初的原始状态--小写,同时将之前的对象指针置为零
            currentWidget = 0;
            currentLineEdit = 0;
            currentTextEdit = 0;
            currentPlain = 0;
            currentBrowser = 0;
            currentEditType = "";
            currentType = "min";
            changeType(currentType);
            this->setVisible(false);
        }

        QRect rect = nowWidget->rect();
        QPoint pos = QPoint(rect.left(), rect.bottom() + 2);
        pos = nowWidget->mapToGlobal(pos);
        this->setGeometry(pos.x(), pos.y(), frmWidth, frmHeight);
    }
}

void frmInput::changeType(QString type)
{
    if (type == "max")
    {
        changeLetter(true);
        ui->btnType->setText(tr("大写"));
        ui->labInfo->setText(tr("输入法--大写"));
        ui->btnOther12->setText("/");
        ui->btnOther14->setText(":");
        ui->btnOther17->setText(",");
        ui->btnOther18->setText("\\");
        ui->btnOther21->setText("\"");
    }
    else
    {
        changeLetter(false);
        ui->btnType->setText(tr("小写"));
        ui->labInfo->setText(tr("输入法--小写"));
        ui->btnOther12->setText("/");
        ui->btnOther14->setText(":");
        ui->btnOther17->setText(",");
        ui->btnOther18->setText("\\");
        ui->btnOther21->setText("\"");
    }
    //每次切换到模式,都要执行清空之前中文模式下的信息
    ui->labPY->setText("");
}

void frmInput::changeLetter(bool isUpper)
{
    QList<QPushButton *> btn = this->findChildren<QPushButton *>();
    foreach (QPushButton * b, btn) {
        if (b->property("btnLetter").toBool()) {
            if (isUpper) {
                b->setText(b->text().toUpper());
            } else {
                b->setText(b->text().toLower());
            }
        }
    }
}

void frmInput::btn_clicked()
{
    //如果当前焦点控件类型为空,则返回不需要继续处理
    if (currentEditType == "") {
        return;
    }

    QPushButton *btn = (QPushButton *)sender();
    QString objectName = btn->objectName();
    if (objectName == "btnType")
    {
        if (currentType == "min")
        {
            currentType = "max";
        }
        else
        {
            currentType = "min";
        }
        changeType(currentType);
    } else if (objectName == "btnDelete") {
        deleteValue();
    } else if (objectName == "btnClose") {
        Main->setFocus();
        this->setVisible(false);
    } else if (objectName == "btnSpace") {
        insertValue(" ");
    } else {
        QString value = btn->text();
        //如果是&按钮，因为对应&被过滤,所以真实的text为去除前面一个&字符
        if (objectName == "btnOther7") {
            value = value.right(1);
        }

        insertValue(value);
    }
}

void frmInput::insertValue(QString value)
{
    if (currentEditType == "QLineEdit") {
        currentLineEdit->insert(value);
    } else if (currentEditType == "QTextEdit") {
        currentTextEdit->insertPlainText(value);
    } else if (currentEditType == "QPlainTextEdit") {
        currentPlain->insertPlainText(value);
    } else if (currentEditType == "QTextBrowser") {
        currentBrowser->insertPlainText(value);
    } else if (currentEditType == "QWidget") {
        QKeyEvent keyPress(QEvent::KeyPress, 0, Qt::NoModifier, QString(value));
        QApplication::sendEvent(currentWidget, &keyPress);
    }
}

void frmInput::deleteValue()
{
    if (currentEditType == "QLineEdit") {
        currentLineEdit->backspace();
    } else if (currentEditType == "QTextEdit") {
        //获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
        QTextCursor cursor = currentTextEdit->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (currentEditType == "QPlainTextEdit") {
        //获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
        QTextCursor cursor = currentPlain->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (currentEditType == "QTextBrowser") {
        //获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
        QTextCursor cursor = currentBrowser->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (currentEditType == "QWidget") {
        QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier, QString());
        QApplication::sendEvent(currentWidget, &keyPress);
    }
}

void frmInput::ChangeFont()
{
    QFont btnFont(this->font().family(), btnFontSize);
    QFont labFont(this->font().family(), labFontSize);

    QList<QPushButton *> btns = ui->widgetMain->findChildren<QPushButton *>();
    foreach (QPushButton * btn, btns) {
        btn->setFont(btnFont);
    }

    QList<QLabel *> labs = ui->widgetTop->findChildren<QLabel *>();
    foreach (QLabel * lab, labs) {
        lab->setFont(labFont);
    }

    ui->btnClose->setFont(labFont);
}

void frmInput::changeStyle(QString topColor, QString bottomColor, QString borderColor, QString textColor)
{
    QStringList qss;

    qss.append(QString("QWidget#frmInput{background: %1;}")
               .arg(topColor));
    qss.append("QPushButton{padding:5px;border-radius:3px;}");
    qss.append(QString("QPushButton:hover{background: %1;}")
               .arg(bottomColor));
    qss.append(QString("QLabel,QPushButton{color:%1;}").arg(textColor));
    qss.append(QString("QPushButton#btnClose{padding:5px;}"));
    qss.append(QString("QPushButton{border:1px solid %1;}")
               .arg(borderColor));
    qss.append(QString("QLineEdit{border:1px solid %1;border-radius:5px;padding:2px;background:none;selection-background-color:%2;selection-color:%3;}")
               .arg(borderColor).arg(bottomColor).arg(topColor));

    this->setStyleSheet(qss.join(""));
}
