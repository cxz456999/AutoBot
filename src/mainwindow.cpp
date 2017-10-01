#include "header/mainwindow.h"
#include "header/huffman.h"
#include "ui_mainwindow.h"
#include "header/findpic.h"
#include "header/questdialog.h"
#include "header/global.h"
#include "header/compiler.h"
#include <windows.h>
#include<QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <qDebug>
#include <QKeyEvent>
#include <QDesktopServices>
#include<QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QNetworkInterface>

GlobalV Global;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    loadSetting();
    m_login.exec();
    qDebug() << "stop";
    m_autoBot = new AutoBot(ui->textEdit);
    qDebug() << "stop0";
    if ( !m_autoBot->readVirtualKeyTable() )
        QMessageBox::information(this, tr("無法開啟"),
            "autoBot.key");
    qDebug() << "stop1";
    QStringList headers;
    headers << "Action";
    QStringList datas;
    datas << "重複做...次(圈選)" << "定時(圈選!勿包在重複做裡!)" << "> 條件啟動(圈選!勿包在重複做裡!)" << "延遲...毫秒" << "> 按鍵(字母、數字)" << "> 滑鼠" << "同時點擊";
    this->m_treeModel = new TreeModel(headers, datas );
    ui->toolView->setModel(this->m_treeModel);
    qDebug() << "stop2";
    QStringList headers_vKey;
    headers_vKey << "Name" << "Delete";
    this->m_vKeyModel = new TreeModel(headers, m_autoBot->getAllVirtualKeys() );
    ui->vKeyView->setModel(this->m_vKeyModel);
    qDebug() << "stop3";


    ui->saveButton->setToolTip("存檔腳本檔案");
    connect(m_autoBot, SIGNAL(finished()), this, SLOT(endBot()));
    m_stStart = new QShortcut(QKeySequence(m_strStartKey), this);
    connect( m_stStart, SIGNAL(activated()),this, SLOT(on_startButton_Pressed()));

    qDebug() << "stop4";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *reply)

{
    qDebug() << reply->readAll();
    m_successLogout = true;
}


bool* isEnd = NULL;
DWORD WINAPI ThreadEnd(LPVOID pM)
{

    while ( !*isEnd )
         Sleep(100);
     exit(0);
    return 0;
}

void MainWindow::loadSetting()
{
    QFile file("Config.set");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, tr("無法開啟檔案"),
            file.errorString());
        return;
    } // if

    int height = -1, width = -1;
    while(!file.atEnd())
    {
        const char*tmpChar = file.readLine();
        QString strLine = QString::fromLocal8Bit(tmpChar);
        strLine.remove("\n");
        strLine.remove("\r");
        if ( strLine.size() <= 0 ) continue;
        QStringList strList = strLine.split(":");

        if ( strList.at(0).compare("Remember") == 0 )
        {
            if ( strList.at(1).compare("Username") == 0 )
                ui->remember_User->setChecked(true);
            else if (  strList.at(1).compare("Username&Password") == 0 )
                ui->remember_UserAndPasswd->setChecked(true);
        } // if

        else if ( strList.at(0).compare("帳號") == 0 || strList.at(0).compare("密碼") == 0)
            m_login.setSetting(strList);
        else if ( strList.at(0).compare("Alert") == 0 )
        {
            if ( strList.at(1).compare("Open") == 0 )
            {
                m_openAlert = true;
                ui->open_alertSound->setChecked(true);//m_openAlert = true;
            } // if
            else
            {
                m_openAlert = false;
                ui->open_alertSound->setChecked(false);
            } // else
        } // else if
        /*else if ( strList.at(0).compare("Width") == 0 )
        {
            bool ok;
            width = strList.at(1).toInt( &ok );

        } // else if
        else if ( strList.at(0).compare("Height") == 0 )
        {
            bool ok;
            height = strList.at(1).toInt( &ok );

        } // else if*/
    } // while

    //if ( width != -1 && height != -1 )
    //    this->setSizeIncrement( QSize(width, height));
    file.close();
}

bool MainWindow::saveSetting()
{ // QIODevice::Append |

    bool nUser = false, nPasswd = false;
    if ( ui->remember_UserAndPasswd->isChecked() )
        nPasswd = nUser = true;
    else if ( ui->remember_User->isChecked() )
        nUser = true;
    QString account = m_login.getSetting( nUser, nPasswd );

    QFile file("Config.set");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::information(this, tr("無法儲存檔案"),
            file.errorString());
        return false;
    } // if

    QTextStream out(&file);
    if ( nUser & nPasswd )
        out << "Remember:Username&Password\n";
    else if ( nUser & !nPasswd )
        out << "Remember:Username\n";
    if ( m_openAlert )
        out << "Alert:Open\n";
    else if ( !m_openAlert )
        out << "Alert:Close\n";
    out << account;
    //out << "Width:" << this->size().width() << "\n";
    //out << "Height:" << this->size().height() << "\n";

    file.close();
}

void MainWindow::closeEvent( QCloseEvent *event) {
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("退出"), QString(tr("請問是否要離開腳本製作")), QMessageBox::Yes | QMessageBox::No);
    if ( button == QMessageBox::No) {
        event->ignore();
    }
    else if ( button == QMessageBox::Yes) {

        connect(m_login.manager, SIGNAL(finished(QNetworkReply*)),
                 this, SLOT(replyFinished(QNetworkReply*)));

        m_login.logout();
        isEnd = &m_successLogout;
        CreateThread(NULL, 0, ThreadEnd, NULL, 0, NULL);

        saveSetting();

        QMessageBox::information(this, tr("！！！"),
            "儲存設定,請等待．．．");
        event->ignore();

       // event->accept();
    }
    event->ignore();

}

void MainWindow::endBot()
{
    if ( m_openAlert )
        Beep( 500, 1000);
    QString mess = QString::fromUtf8("腳本結束") ;
    QMessageBox::information(this, tr("Success"), mess) ;
    this->ui->startButton->setEnabled(true);
    this->ui->loadButton->setEnabled(true);
    this->ui->saveButton->setEnabled(true);
    this->ui->newButton->setEnabled(true);
    this->ui->lockButton->setEnabled(true);
    ui->textEdit->setEnabled(true);

}

void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
           tr("儲存腳本"), "",
           tr("腳本 (*.bot);"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::information(this, tr("無法儲存檔案"),
            file.errorString());
        return;
    } // if

    m_currentFileName = fileName;
    m_autoBot->saveData(&file);
    //file.open(QIODevice::ReadOnly);
    //m_autoBot->readData(&file);
    file.close();
}

void MainWindow::on_loadButton_clicked()
{
    deselectedAllText();
    QString fileName = QFileDialog::getOpenFileName(this,
                       tr("開啟腳本"), "",
                       tr("腳本/加密腳本 (*.bot;*.botx)"));//;All Files (*)
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    m_currentFileName = fileName;
    if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("無法開啟檔案"),
                    file.errorString());
                return ;
    } // if

    if ( !Huffman_Management::isCompressingFile(fileName) )
    {
        QString content = m_autoBot->readData(&file);
         ui->textEdit->setEnabled(true);
        ui->textEdit->setText( content );
    } // if
    else
    {
        m_isCompressFile = true;
        ui->textEdit->setText( "這是加密腳本,不給看~" );
        ui->textEdit->setEnabled(false);

    } // else
}

void MainWindow::on_toolView_clicked(const QModelIndex &index)
{
    bool isOK;
    QString strSelect = index.model()->index(index.row(), 0).data().toString();
    if ( strSelect.compare( "重複做...次(圈選)" ) == 0 ) // 延遲...毫秒
    {
        QTextCursor cursor(ui->textEdit->textCursor());
        QString selectedTxt =  cursor.selectedText();
        if ( selectedTxt.size() <= 0 ) {
            QMessageBox::critical(this, tr("Error"),
                "請圈選指令");
            return;
        } // if

        int text = QInputDialog::getInt(this, "輸入",
                                        "輸入重複的次數:(-1 無限次)", QLineEdit::Normal, -1, 2147400000, 1, &isOK);
        if ( !isOK ) return;
        QString changedTxt = "loop ( " + QString::number(text) + " ) {\n" + selectedTxt + "\n}";
        ui->textEdit->textCursor().insertText(changedTxt);
        //qDebug() <<
    } // if
    else if ( strSelect.compare( "定時(圈選!勿包在重複做裡!)" ) == 0 )
    {
        QTextCursor cursor(ui->textEdit->textCursor());
        QString selectedTxt =  cursor.selectedText();
        if ( selectedTxt.size() <= 0 ) {
            QMessageBox::critical(this, tr("Error"),
                "請圈選指令");
            return;
        } // if

        int text = QInputDialog::getInt(this, "輸入",
                             "定時幾毫秒做一次:", QLineEdit::Normal, 1, 2147400000, 1, &isOK);
        if ( !isOK ) return;
        QString changedTxt = "Execute per " + QString::number(text) + " ms {\n" + selectedTxt + "\n}";
        ui->textEdit->textCursor().insertText(changedTxt);
    } // else if
    else if ( strSelect.compare( "延遲...毫秒" ) == 0 )
    {
        int text = QInputDialog::getInt(this, "輸入",
                                        "輸入延遲時間(毫秒):", QLineEdit::Normal, 1, 2147400000, 1, &isOK);
        if ( !isOK ) return;
        insertTxtToTxtEdit("延遲 " + QString::number(text) + " 毫秒");
    } // else if
    else if ( strSelect.compare( "按鍵(字母、數字)" ) == 0 || strSelect.compare( "滑鼠" ) == 0 || strSelect.compare( "條件啟動(圈選!勿包在重複做裡!)" ) == 0 )
    {
        QMessageBox::information(this, tr("Warning"), tr("請用滑鼠右鍵點擊"));
    }
    else if ( strSelect.compare( "同時點擊" ) == 0 )
    {
        QString first, second;
        bool isOK;
        while ( true ) {
            first = QInputDialog::getText(this, "輸入",
                              "第一個按鍵:",
                               QLineEdit::Normal, "", &isOK);
            if ( !isOK ) return;
            if ( this->m_autoBot->isKeyExsit(first) )
                break;
            else
                QMessageBox::critical(this, tr("Error"),
                    "此鍵不存在");
        } // while

        while ( true ) {
            second = QInputDialog::getText(this, "輸入",
                              "第二個按鍵:",
                               QLineEdit::Normal, "", &isOK);
            if ( !isOK ) return;
            if ( this->m_autoBot->isKeyExsit(second) )
                break;
            else
                QMessageBox::critical(this, tr("Error"),
                    "此鍵不存在");
        } // while

        QString changedTxt = "同時點擊 " + first + " " + second + " 鍵\n";
        ui->textEdit->textCursor().insertText(changedTxt);
    } // else if
    else
    {
        QMessageBox::information(this, "Error",
            strSelect);
        return;
    } // else

    //qDebug() << text;
    /*if(isOK) {
        QMessageBox::information(parent, "Information",
                "Your comment is: <b>" + text + "</b>",
                QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }*/
}
//滑鼠在條件執行中出錯
void MainWindow::deselectedAllText()
{
    QTextCursor c = ui->textEdit->textCursor();
    c.setPosition(0);
    c.setPosition(ui->textEdit->toPlainText().size(), QTextCursor::KeepAnchor);
    ui->textEdit->setTextCursor(c);
    ui->textEdit->setTextBackgroundColor(QColor(255, 255, 255));
}

void MainWindow::on_startButton_clicked()
{
    if ( !ui->startButton->isEnabled() ) return;
    deselectedAllText();
    //ui->textEdit->setTextBackgroundColor(QColor(0, 0, 0)); ui->textEdit->toPlainText()
    QString content = ui->textEdit->toPlainText();
    if ( m_isCompressFile )
    {
        qDebug() << "is compress file";
        Huffman_Management hm( m_currentFileName, "", m_login.m_user, "" );
        hm.decompressFile();
        content = hm.getResult();
        qDebug () << content;
    } // if

    if ( content.isEmpty() ) return ;
    if ( !this->m_autoBot->readDataFromTxtEdit(content.split("\n")) )
    {

        QMessageBox::critical(this, tr("Error"), tr("腳本錯誤"));
        return;
    } // if

    m_autoBot->setHotKey(m_autoBot->getVirtualKey(m_strStartKey), m_autoBot->getVirtualKey(m_strEndKey), m_openAlert);
    QString alert = "長按" + m_strStartKey + "開始/" + m_strEndKey + "結束";
    QMessageBox::information(this, tr("Warning"), alert);
    this->m_autoBot->start();
    this->ui->startButton->setEnabled(false);
    this->ui->startButton->setEnabled(false);
    this->ui->loadButton->setEnabled(false);
    this->ui->saveButton->setEnabled(false);
    this->ui->newButton->setEnabled(false);
    this->ui->lockButton->setEnabled(false);
    ui->textEdit->setEnabled(false);
}

void MainWindow::on_startButton_Pressed()
{
    if ( !ui->startButton->isEnabled() ) return;
    deselectedAllText();
    //ui->textEdit->setTextBackgroundColor(QColor(0, 0, 0)); ui->textEdit->toPlainText()
    QString content = ui->textEdit->toPlainText();
    if ( m_isCompressFile )
    {
        qDebug() << "is compress file";
        Huffman_Management hm( m_currentFileName, "", m_login.m_user, "" );
        hm.decompressFile();
        content = hm.getResult();
        qDebug () << content;
    } // if

    if ( content.isEmpty() ) return ;
    if ( !this->m_autoBot->readDataFromTxtEdit(content.split("\n")) )
    {

        QMessageBox::critical(this, tr("Error"), tr("腳本錯誤"));
        return;
    } // if

    //QMessageBox::information(this, tr("Warning"), tr("長按" + m_strStartKey + "開始/" + m_strEndKey + "結束"));
    m_autoBot->setHotKey(m_autoBot->getVirtualKey(m_strStartKey), m_autoBot->getVirtualKey(m_strEndKey), m_openAlert);
    this->m_autoBot->start();
    this->ui->startButton->setEnabled(false);
    this->ui->startButton->setEnabled(false);
    this->ui->loadButton->setEnabled(false);
    this->ui->saveButton->setEnabled(false);
    this->ui->newButton->setEnabled(false);
    this->ui->lockButton->setEnabled(false);
    ui->textEdit->setEnabled(false);
}
void MainWindow::insertTxtToTxtEdit( QString str )
{
    QTextCursor cursor(ui->textEdit->textCursor());
    if ( cursor.position() != 0 && ui->textEdit->toPlainText()[cursor.position()-1] != '\n' )
        cursor.insertText( "\n" );

    char c = ' ';
    if ( cursor.position() < ui->textEdit->toPlainText().size() )
         c = ui->textEdit->toPlainText()[cursor.position()].toLatin1();
    cursor.insertText( str );
    //qDebug() << "->>>>"  << c;
    if ( c == ' ' || c == '\n' || c == '\r' || c == '\t'  )
        return;

    cursor.insertText( "\n" );
    //if (cursor.position() == 0)
    //    cursor.insertText( "\n" );
}

void MainWindow::on_deleteButton_clicked()
{
    QModelIndexList list = ui->vKeyView->selectionModel()->selectedIndexes();
    if ( list.size() > 0 )
    {
        //qDebug() << list[0].data().toString();
        this->m_autoBot->removeVirtualKey2Table(list.at(0).data().toString());
        m_vKeyModel->removeRow(list.at(0).row());
        ui->vKeyView->setUpdatesEnabled(true);

        //this->m_vKeyModel->searchRemove(list[0].data().toString());
    } // if
}

void MainWindow::on_pushButton_clicked()
{
    QFile file( "./Compile.comp" );
    if ( !file.open(QIODevice::ReadOnly) ){
        QMessageBox::information(0, "Error",
            "Compile資料遺失");
        file.close();
        return;
    } // if

    /*QString b = QString::fromLocal8Bit(file.readAll());
    file.close();
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << m_login.encode(b);
    file.close();
    return;*/

    QString bef = QString::fromLocal8Bit(file.readAll()).replace("\n", "").replace("\r", "");
    //qDebug() << bef;
    QString compileFile = m_login.decode(bef);

    /* decode
     * file.close();
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << compileFile;
    file.close();
    return;*/


    //qDebug() << compileFile;
    QString content = ui->textEdit->toPlainText();
    if ( !this->m_autoBot->readDataFromTxtEdit(content.split("\n")) )
    {

        QMessageBox::critical(this, tr("Error"), tr("腳本錯誤"));
        return;
    } // if

    qDebug() << m_autoBot->getData().size();
    bool isOK;
    QString fileName = QFileDialog::getSaveFileName(this,
           tr("儲存腳本執行檔"), "",
           tr("腳本執行檔 (*.exe)"));
    if (fileName.isEmpty())
        return;

    QString text = QInputDialog::getMultiLineText(this, tr("輸入"),
                                                     tr("想出現的文字"), "", &isOK);
    if ( !isOK ) return;
    QString tmp = "長按" + m_strEndKey +  "結束腳本\n" + text;
    tmp.replace("許","許\\");
    tmp.replace("蓋","蓋\\");
    tmp.replace("功","功\\");
    /*fileName.replace("許","許\\");
    fileName.replace("蓋","蓋\\");
    fileName.replace("功","功\\");*/

    compiler c( compileFile, fileName, m_autoBot->getVirtualKey( m_strEndKey ), tmp.split("\n"), m_login.m_deadline, m_autoBot->getData(), m_autoBot->getPressKey());
    c.execute();
}

void MainWindow::on_vKeyView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex it = ui->vKeyView->indexAt(pos);
    if ( it.row() == -1 ) return;
    //qDebug() << it.row();
    QVariant vV = it.model()->index( it.row(),  0, it.parent()).data() ;
    Global.selectedSpecialKey = vV.toString();
    QMenu *popMenu =new QMenu(this);
    popMenu->addAction(ui->action_Click);
    popMenu->addAction(ui->action_Press);
    popMenu->addAction(ui->action_Release);
    popMenu->exec(QCursor::pos());
}

void MainWindow::on_action_Press_triggered()
{
    insertTxtToTxtEdit("按下 " + Global.selectedSpecialKey + " 鍵");
}

void MainWindow::on_action_Release_triggered()
{
    insertTxtToTxtEdit("放開 " + Global.selectedSpecialKey + " 鍵");
}

void MainWindow::on_action_Click_triggered()
{
    insertTxtToTxtEdit("點擊 " + Global.selectedSpecialKey + " 鍵");
}

void MainWindow::on_label_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_addButton_clicked()
{
    bool isOK;
        QString text = QInputDialog::getMultiLineText(this, tr("輸入"),
                                                         tr("依序輸入按鍵名稱(隨意ex:shift)、鍵值(ex:0x10)(以換行區隔):"), "", &isOK);
        if ( !isOK ) return;
        QStringList sList = text.split("\n");
        if (sList.at(sList.size()-1).size() == 0)
            sList.removeAt(sList.size()-1);
        if ( sList.size() % 2 != 0 || sList.size() == 0 )
        {
            QMessageBox::information(this, tr("Error"),
                "格式錯誤");
            return;
        } // if


        if ( !this->m_autoBot->addVirtualKey2Table(sList))
        {
            QMessageBox::information(this, tr("Error"),
                "autoBot.key遺失");
            return ;
        } // if

        for ( int i = 0; i < sList.size(); i+=2 )
        {
            if (!this->m_vKeyModel->insertRow(  m_vKeyModel->rowCount(), QModelIndex() ))
                return;
            m_vKeyModel->setData( m_vKeyModel->index( m_vKeyModel->rowCount() - 1,0), QVariant(sList[i]));
        } // for
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    this->ui->vKeyView->model()->removeRows(0,this->ui->vKeyView->model()->rowCount() );
    for ( auto m : m_autoBot->m_virKeyList)
    {
        if ( m.keyName.indexOf( arg1 ) != -1 )
        {
            m_vKeyModel->insertRow(  m_vKeyModel->rowCount(), QModelIndex() );
            m_vKeyModel->setData( m_vKeyModel->index( m_vKeyModel->rowCount() - 1,0), QVariant(m.keyName));
            //qDebug() << m.keyName;
        } // if
    } // for
}

void MainWindow::on_toolView_customContextMenuRequested(const QPoint &pos)
{
    //"重複做...次(圈選)" << "定時(圈選!勿包在重複做裡!)" << "延遲...毫秒" << "按鍵(字母、數字)" << "移動滑鼠X軸(勿包在重複做裡!)" << "移動滑鼠Y軸(勿包在重複做裡!)"<< "停止滑鼠";

    QModelIndex it = ui->toolView->indexAt(pos);
    //qDebug() << it.row();
    if ( it.row() == -1 ) return;
    if ( it.row() == 4 )
    {
        QVariant vV = it.model()->index( it.row(),  0, it.parent()).data() ;
        Global.selectedSpecialKey = vV.toString();
        QMenu *popMenu =new QMenu(this);
        popMenu->addAction(ui->action_keyboard_Click);
        popMenu->addAction(ui->action_keyboard_Press);
        popMenu->addAction(ui->action_keyboard_Release);
        popMenu->exec(QCursor::pos());
    } // if
    else if ( it.row() == 5 )
    {
        QVariant vV = it.model()->index( it.row(),  0, it.parent()).data() ;
        Global.selectedSpecialKey = vV.toString();
        QMenu *popMenu =new QMenu(this);
        //popMenu->addAction(ui->action_LClick);
        //popMenu->addAction(ui->action_RClick);
        popMenu->addAction(ui->action_LClickPos);
        popMenu->addAction(ui->action_RClickPos);
        popMenu->addAction(ui->action_WheelUp);
        popMenu->addAction(ui->action_WheelDown);
        popMenu->addAction(ui->action_MouseMoveX);
        popMenu->addAction(ui->action_MouseMoveY);
        popMenu->addAction(ui->action_MouseStop);
        popMenu->exec(QCursor::pos());
    } // if
    if ( it.row() == 2 )
    {
        QVariant vV = it.model()->index( it.row(),  0, it.parent()).data() ;
        Global.selectedSpecialKey = vV.toString();
        QMenu *popMenu =new QMenu(this);
        popMenu->addAction(ui->condition_NeedHotKey);
        popMenu->addAction(ui->condition_ReleaseEnd);
        popMenu->exec(QCursor::pos());
    } // if
}

void MainWindow::on_action_keyboard_Click_triggered()
{
    bool isOK;
    QString text = QInputDialog::getText(this, "輸入",
                          "點擊的按鍵:",
                           QLineEdit::Normal, "", &isOK);
    if ( !isOK ) return;
    if ( !this->m_autoBot->isKeyExsit(text) )
    {
        QMessageBox::information(this, tr("Error"),
            "尚未增加此按鍵");
        return ;
    } // if

    insertTxtToTxtEdit("點擊 " + text + " 鍵");
}

void MainWindow::on_action_keyboard_Press_triggered()
{
    bool isOK;
    QString text = QInputDialog::getText(this, "輸入",
                          "按下的按鍵:",
                           QLineEdit::Normal, "", &isOK);
    if ( !isOK ) return;
    if ( !this->m_autoBot->isKeyExsit(text) )
    {
        QMessageBox::information(this, tr("Error"),
            "尚未增加此按鍵");
        return ;
    } // if

    insertTxtToTxtEdit("按下 " + text + " 鍵");
}

void MainWindow::on_action_keyboard_Release_triggered()
{
    bool isOK;
    QString text = QInputDialog::getText(this, "輸入",
                          "放開的按鍵:",
                           QLineEdit::Normal, "", &isOK);
    if ( !isOK ) return;
    if ( !this->m_autoBot->isKeyExsit(text) )
    {
        QMessageBox::information(this, tr("Error"),
            "尚為增加此按鍵");
        return ;
    } // if

    insertTxtToTxtEdit("放開 " + text + " 鍵");
}

void MainWindow::on_action_MouseMoveX_triggered()
{
    bool isOK;
    int iStart = QInputDialog::getInt(this, "輸入",
                                      "起始位置(依解析度)", QLineEdit::Normal, 1, 2147400000, 1, &isOK);
    if ( !isOK ) return;
    int iEnd = QInputDialog::getInt(this, "輸入",
                                    "結束位置(依解析度)", QLineEdit::Normal, 1, 2147400000, 1, &isOK);
    if ( !isOK ) return;
    int iPer = QInputDialog::getInt(this, "輸入",
                                    "毫秒/畫素(標準輸:10)", QLineEdit::Normal, 1, 2147400000, 1, &isOK);
    if ( !isOK ) return;
    insertTxtToTxtEdit("移動滑鼠X軸 " + QString::number(iStart) + " " + QString::number(iEnd) + " " + QString::number(iPer) );
}

void MainWindow::on_action_MouseMoveY_triggered()
{
    bool isOK;
    int iStart = QInputDialog::getInt(this, "輸入",
                                      "起始位置(依解析度)", QLineEdit::Normal, 1, 2147400000, 1, &isOK);
    if ( !isOK ) return;
    int iEnd = QInputDialog::getInt(this, "輸入",
                                    "結束位置(依解析度)", QLineEdit::Normal, 1, 2147400000, 1, &isOK);
    if ( !isOK ) return;
    int iPer = QInputDialog::getInt(this, "輸入",
                                    "毫秒/畫素(標準輸:10)", QLineEdit::Normal, 1, 2147400000, 1, &isOK);
    if ( !isOK ) return;
    insertTxtToTxtEdit("移動滑鼠Y軸 " + QString::number(iStart) + " " + QString::number(iEnd) + " " + QString::number(iPer) );
}

void MainWindow::on_action_MouseStop_triggered()
{
    insertTxtToTxtEdit("停止滑鼠移動" );
}

void MainWindow::on_action_LClickPos_triggered()
{
    bool isOK = true;
   /* int iX = QInputDialog::getInt(this, "輸入",
                                      "起始位置(依解析度)", QLineEdit::Normal, 1, 2147400000, 1, &isOK);
    if ( !isOK ) return;
    int iY = QInputDialog::getInt(this, "輸入",
                                    "結束位置(依解析度)", QLineEdit::Normal, 1, 2147400000, 1, &isOK);*/
    POINT po;
    QuestDialog dd( &po );
    //QMessageBox::information(this, tr("!!!!!"), "對目標處點擊右鍵，確認目標後再點擊確定");
    if (  dd.exec() ) //return;
        insertTxtToTxtEdit("左鍵點擊 " + QString::number(po.x) + " " + QString::number(po.y) );
}

void MainWindow::on_action_LClick_triggered()
{
    insertTxtToTxtEdit("左鍵點擊" );
}

void MainWindow::on_action_RClick_triggered()
{
    insertTxtToTxtEdit("右鍵點擊" );
}

void MainWindow::on_action_RClickPos_triggered()
{
    POINT po;
    QuestDialog dd( &po );
    if (  dd.exec() ) //return;
        insertTxtToTxtEdit("右鍵點擊 " + QString::number(po.x) + " " + QString::number(po.y) );
}

void MainWindow::on_textEdit_textChanged()
{
    //qDebug() << "Not compress file";
    //if ( m_isCompressFile &&  )
    //m_isCompressFile = false;
}

void MainWindow::on_newButton_clicked()
{
    ui->textEdit->setText("");
    ui->textEdit->setEnabled(true);
    m_isCompressFile = false;
    m_currentFileName = "";
    deselectedAllText();
}

void MainWindow::on_lockButton_clicked()
{
    //on_saveButton_clicked();
    QString content = ui->textEdit->toPlainText();
    if ( content.isEmpty() ) return;
    if ( !this->m_autoBot->readDataFromTxtEdit(content.split("\n")) )
    {
        QMessageBox::critical(this, tr("Error"), tr("腳本錯誤"));
        return;
    } // if

    QString fileName = QFileDialog::getSaveFileName(this,
           tr("儲存加密腳本"), "",
           tr("加密腳本 (*.botx)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::information(this, tr("無法儲存檔案"),
            file.errorString());
        return;
    } // if

    QFile tmp( "tmp.lock" );
    if (!tmp.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::information(this, tr("加密出錯"),
            tmp.errorString());
        return;
    } // if
    m_autoBot->saveData(&tmp);

    m_currentFileName = fileName;
    //qDebug() << m_currentFileName.toLatin1();

    bool isOK;
    QString text = QInputDialog::getText(this, "輸入",
                          "加密對象名稱:",
                           QLineEdit::Normal, "", &isOK);
    if ( !isOK ) return;
    Huffman_Management hm( "tmp.lock", m_currentFileName, text, content );
    qDebug() << hm.compressFile();
    DeleteFileA("tmp.lock");
    QMessageBox::information(this, tr("Success"),
        "加密成功");
    //qDebug() << hm.getResult();
}

void MainWindow::on_label_2_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}



void MainWindow::on_remember_User_triggered()
{
    if ( this->ui->remember_User->isChecked() )
    {
        //qDebug() << "remember_User check";
        ui->remember_UserAndPasswd->setChecked(false);
    } // if
    else
    {

        //qDebug() << "remember_User not check";
    } // else if
}

void MainWindow::on_remember_UserAndPasswd_triggered()
{
    if ( this->ui->remember_UserAndPasswd->isChecked() )
    {
        //qDebug() << "remember_UserAndPasswd check";
        ui->remember_User->setChecked(false);
    } // if
    else if ( !this->ui->remember_UserAndPasswd->isChecked() )
    {
        //qDebug() << "remember_UserAndPasswd not check";
    } // else if
}

void MainWindow::on_setHotkey_Start_triggered()
{
    bool isOK;
    QStringList list;
    for (int i = 1; i <= 12; i++ )
        list.append("F" + QString::number(i));
    QString text = QInputDialog::getItem(this, "輸入",
                          "開始熱鍵:",
                           list, 0, false, &isOK);
    if ( !isOK ) return;
    if ( !this->m_autoBot->isKeyExsit(text) )
    {
        QMessageBox::information(this, tr("Error"),
            "尚為增加此按鍵");
        return ;
    } // if

    m_strStartKey = text;
    disconnect( m_stStart, SIGNAL(activated()),this, SLOT(on_startButton_Pressed()));
    delete m_stStart;
    m_stStart = new QShortcut(QKeySequence(m_strStartKey), this);
    connect( m_stStart, SIGNAL(activated()),this, SLOT(on_startButton_Pressed()));
    ui->startButton->setText("長按" + m_strStartKey + "開始/" + m_strEndKey + "結束" );
}

void MainWindow::on_setHotkey_End_triggered()
{
    bool isOK;
    QStringList list;
    for (int i = 1; i <= 12; i++ )
        list.append("F" + QString::number(i));
    QString text = QInputDialog::getItem(this, "輸入",
                          "開始熱鍵:",
                           list, 0, false, &isOK);
    if ( !isOK ) return;
    if ( !this->m_autoBot->isKeyExsit(text) )
    {
        QMessageBox::information(this, tr("Error"),
            "尚為增加此按鍵");
        return ;
    } // if

    m_strEndKey = text;
    ui->startButton->setText("長按" + m_strStartKey + "開始/" + m_strEndKey + "結束" );
}

void MainWindow::on_open_alertSound_triggered()
{
    if ( this->ui->open_alertSound->isChecked() )
        m_openAlert = true;
    else
        m_openAlert = false;
    qDebug() << m_openAlert;
}

void MainWindow::on_action_WheelUp_triggered()
{
    insertTxtToTxtEdit("滑鼠滾輪向上" );
}

void MainWindow::on_action_WheelDown_triggered()
{
    insertTxtToTxtEdit("滑鼠滾輪向下" );
}

void MainWindow::on_condition_NeedHotKey_triggered()
{
    QTextCursor cursor(ui->textEdit->textCursor());
    QString selectedTxt =  cursor.selectedText();
    if ( selectedTxt.size() <= 0 ) {
        QMessageBox::critical(this, tr("Error"),
            "請圈選指令");
        return;
    } // if

    QString txtStart = "", txtEnd = "";
    bool isOK = true;
    while ( true ) {
        txtStart = QInputDialog::getText(this, "輸入",
                          "開始的熱鍵:",
                           QLineEdit::Normal, "", &isOK);
        if ( !isOK ) return;
        if ( this->m_autoBot->isKeyExsit(txtStart) )
            break;
        else
            QMessageBox::critical(this, tr("Error"),
                "此鍵不存在");
    } // while

    while ( true ) {
        txtEnd = QInputDialog::getText(this, "輸入",
                          "結束的熱鍵:",
                           QLineEdit::Normal, "", &isOK);
        if ( !isOK ) return;
        if ( this->m_autoBot->isKeyExsit(txtEnd) )
            break;
        else
            QMessageBox::critical(this, tr("Error"),
                "此鍵不存在");
    } // while

    QString changedTxt = "當按下 " + txtStart + " 時執行,按下 " + txtEnd + " 時結束 {\n" + selectedTxt + "\n}";
    ui->textEdit->textCursor().insertText(changedTxt);
}

void MainWindow::on_condition_ReleaseEnd_triggered()
{
    QTextCursor cursor(ui->textEdit->textCursor());
    QString selectedTxt =  cursor.selectedText();
    if ( selectedTxt.size() <= 0 ) {
        QMessageBox::critical(this, tr("Error"),
            "請圈選指令");
        return;
    } // if

    bool isOK = true;
    QString txtStart;
    while ( true ) {
       txtStart = QInputDialog::getText(this, "輸入",
                          "開始的熱鍵:",
                           QLineEdit::Normal, "", &isOK);
        if ( !isOK ) return;
        if ( this->m_autoBot->isKeyExsit(txtStart) )
            break;
        else
            QMessageBox::critical(this, tr("Error"),
                "此鍵不存在");
    } // while

   int nTimes = QInputDialog::getInt(this, "輸入",
                                      "執行幾次", QLineEdit::Normal, 1, 2147400000, 1, &isOK);
    if ( !isOK ) return;
    QString changedTxt = "當按下 " + txtStart + " 時執行 " + QString::number(nTimes) + " 次 {\n" + selectedTxt + "\n}";
    ui->textEdit->textCursor().insertText(changedTxt);
}

void MainWindow::on_testButton_clicked()
{
    findpic f;
    //QMessageBox::information(this, tr("!!!!!"), "對目標處點擊右鍵，確認目標後再點擊確定");
    f.exec();

}
