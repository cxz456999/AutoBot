#include "header/autobot.h"
#include <windows.h>
#include <QFile>
#include <QDebug>
#include <QTime>
#include <thread>
#include <QTextStream>
#include <QMessageBox>
/*
左箭頭 0x25
上箭頭 0x26
右箭頭 0x27
下箭頭 0x28
空白 0x20
Ctrl 0x11
*/

//static bool* stop_Run = NULL;
//static unsigned char* EndKey = NULL;
struct sThread{
    bool* stop_Run;
    unsigned char* EndKey;
};

DWORD WINAPI ThreadStop(LPVOID pM)
{

    sThread *st = static_cast<sThread*>(pM);
    while ( !*st->stop_Run )
    {
        //qDebug() << "RUNNNNNNNNNNNNN" << *EndKey;
        if ( GetKeyState(*st->EndKey) < 0 )
            break;
        Sleep(10);
    } // while

    //qDebug() << "WTFFFFFFFFFF STOP";
    Sleep(300);
    *st->stop_Run = true;
    return 0;
}

void AutoBot::setHotKey(int start, int end, bool openAlert)
{
    m_StartKey = start;
    m_EndKey = end;
    m_openAlert = openAlert;
}

unsigned char AutoBot::getVirtualKey(QString str)
{
    //qDebug() << "getVirtualKey" << str << str.size() << m_virKeyMap.size();
    /*if ( QString::compare(str, "a", Qt::CaseInsensitive) == 0 )
        return 0x41;*/
    if ( m_virKeyMap.contains(str) )
    {

        QMap<QString, unsigned char>::iterator it = m_virKeyMap.find(str);
        //qDebug() << "24 WTF" << it.key() << (int)it.value();
        return it.value();
    } // if
    /*else if ( !m_virKeyMap.contains(str) )
    {
        // qDebug() << "31 WTF";;
        for ( auto a: m_virKeyList )
            // qDebug() << a.keyName << (int)a.keyVal;
        return 0x254;
    }*/
    else if ( str.size() == 1 && ( ('a' <= str[0] && str[0] <= 'z') || ('A' <= str[0] && str[0] <= 'Z')) ) // a - z or A - Z
    {
        uchar unchar = 0x41;
        char ch = str[0].toLatin1();
        if ( 'a' <= str[0] && str[0] <= 'z' )
            unchar = (ch - 'a');
        else if ( 'A' <= str[0] && str[0] <= 'Z' )
            unchar =(ch - 'A');
        return 0x41 + unchar;
    } // else if
    else if ( str.size() == 1 && ( '0' <= str[0] && str[0] <= '9' )) // 0 - 9
    {
        uchar unchar = 0x30;
        char ch = str[0].toLatin1();
        unchar =(ch - '0');
        return 0x30 + unchar;
    } // else if
    else if ( QString::compare(str, "延遲", Qt::CaseInsensitive) == 0 )
        return 0x253;
    else{
        qDebug() << "is else";
        return 0x254;
    } // else
}

AutoBot::AutoBot(QTextEdit *in_txtEdit)
{
    this->m_txtEdit = in_txtEdit;
    m_StartKey = VK_F1;
    m_EndKey = VK_F2;
}

AutoBot::AutoBot(QTextEdit * in_txtEdit, QList<KeyType>::iterator in_Init , QList<unsigned char> PressKey)
{
    this->m_txtEdit = in_txtEdit;
    this->m_insideIt = in_Init;
    this->m_insideThread = true;
    m_StartKey = VK_F1;
    m_EndKey = VK_F2;
    m_PressKey = PressKey;
    readVirtualKeyTable();
}

AutoBot::AutoBot(QTextEdit * in_txtEdit, QList<KeyType>::iterator in_Init, unsigned char in_OEKey, unsigned char in_StartKey, unsigned char in_EndKey, QList<unsigned char> PressKey, bool in_executeOneTime)
{
    this->m_txtEdit = in_txtEdit;
    this->m_insideIt = in_Init;
    this->m_isConditionExecute = true;
    this->m_OutsideEndKey = in_OEKey;
    this->m_StartKey = in_StartKey;
    this->m_EndKey = in_EndKey;
    m_executeOneTime = in_executeOneTime;
    m_PressKey = PressKey;
    readVirtualKeyTable();
}

AutoBot::~AutoBot()
{

   //delete this;
}

void AutoBot::endThread()
{
    m_NumOfThread--;
}

bool AutoBot::recordMouseAndKeyboard()
{

    return true;
}

bool AutoBot::saveData( QFile* file )
{

    QTextStream out(file);
    out << this->m_txtEdit->toPlainText();
    file->close();
    this->m_KeyList.clear();

    return true;
}

bool AutoBot::saveData(QFile *file, QString content)
{
    QTextStream out(file);
    out << content;
    file->close();
    this->m_KeyList.clear();
    return true;
}

void AutoBot::deselectedAllText()
{
    QTextCursor c = m_txtEdit->textCursor();
    c.setPosition(0);
    c.setPosition(m_txtEdit->toPlainText().size(), QTextCursor::KeepAnchor);
    m_txtEdit->setTextCursor(c);
    m_txtEdit->setTextBackgroundColor(QColor(255, 255, 255));

}

void AutoBot::selectedTextByPos(int start, int length)
{
    QTextCursor c = m_txtEdit->textCursor();
    c.setPosition(start);
    c.setPosition(start + length, QTextCursor::KeepAnchor);
    m_txtEdit->setTextCursor(c);
    m_txtEdit->setTextBackgroundColor(QColor(255, 10, 10));
}

void AutoBot::selectedTextByText( QString target )
{
    int start =  m_txtEdit->toPlainText().indexOf(target);
    QTextCursor c = m_txtEdit->textCursor();
    c.setPosition(start);
    c.setPosition(start + target.size(), QTextCursor::KeepAnchor);
    m_txtEdit->setTextCursor(c);
    m_txtEdit->setTextBackgroundColor(QColor(255, 10, 10));
}

bool AutoBot::str2Digit( QString str, int* ret )
{
    bool ok;
    int toInt = str.toInt( &ok );
    *ret = ok ? toInt : 0;
    return ok;
}

bool AutoBot::readDataFromTxtEdit( QStringList all )
{

    bool inside = false;
    this->m_KeyList.clear();
    int length = 0;
    foreach ( QString strLine, all )
    {
        strLine.remove("\n");
        strLine.remove("\r");
        QStringList strList = strLine.split(" ");
        KeyType keyType;
        keyType.millisecond = 0;
        //// qDebug()<< strList;
        if ( strList.at(0).size() == 0 ) continue;
        if ( strList.at(0).compare("延遲") == 0 )
        {
            keyType.keyName = strList.at(0);
            if ( !str2Digit( strList.at(1), &keyType.millisecond ) )
            {
                selectedTextByText( strList.at(1) );
                return false;
            } // if
        } // if
        else if ( strList.at(0).compare("loop") == 0 )
        {           
            keyType.keyName = strList.at(0);
            inside = true;
            if ( !str2Digit( strList.at(2), &keyType.times ) )
            {
                selectedTextByText( strList.at(2) );
                return false;
            } // if
        } // else if
        else if ( strList.at(0).compare("}") == 0 )
        {          
            keyType.keyName = "}";
            inside = false;
        } // else if
        // 移動滑鼠X軸 100 500 10 -> move x軸 從100到500 每移動1個pixel停10ms
        else if ( strList.at(0).compare("移動滑鼠X軸") == 0 || strList.at(0).compare("移動滑鼠Y軸") == 0 )
        {
            keyType.keyName = strList.at(0);
            if ( !str2Digit( strList.at(1), &keyType.startPosition ) )
            {
                selectedTextByText( strList.at(1) );
                return false;
            } // if

            if ( !str2Digit( strList.at(2), &keyType.endPosition ) )
            {
                selectedTextByText( strList.at(2) );
                return false;
            } // if

            if ( !str2Digit( strList.at(3), &keyType.millisecond ) )
            {
                selectedTextByText( strList.at(3) );
                return false;
            } // if
        } // else if
        else if ( strList.at(0).compare("左鍵點擊") == 0 || strList.at(0).compare("右鍵點擊") == 0 )
        {
            keyType.keyName = strList.at(0);
            if ( !str2Digit( strList.at(1), &keyType.startPosition ) )
            {
                selectedTextByText( strList.at(1) );
                return false;
            } // if

            if ( !str2Digit( strList.at(2), &keyType.endPosition ) )
            {
                selectedTextByText( strList.at(2) );
                return false;
            } // if
        } // else if
        else if ( strList.at(0).compare("停止滑鼠移動") == 0 || strList.at(0).compare("MouseStopX") == 0 || strList.at(0).compare("MouseStopY") == 0 )
        {
            keyType.keyName = strList.at(0);
        } // else if
        else if ( strList.at(0).compare("Execute") == 0 ) // Execute per 1000 ms {
        {
            if ( inside )
            {
                selectedTextByPos( m_txtEdit->toPlainText().indexOf(strLine, length), strLine.size());
                QMessageBox::information(m_txtEdit, "注意!!", "此指令無法被包覆");
                return false;
            } // if

            inside = true;
            keyType.keyName = strList.at(0);
            if ( !str2Digit( strList.at(2), &keyType.millisecond ) )
            {
                selectedTextByText( strList.at(2) );
                return false;
            } // if
        } // else if
        else if ( strList.at(0).compare("當按下") == 0 )  // 當按下 ... 時執行,按下 ... 時暫停 {
        {
            qDebug() << "298--------------->"<<strList.at(1);
            if ( strList.at(2).compare("時執行") == 0 ) // 當按下 ... 時執行 ... 次 {
            {
                if ( inside )
                {
                    selectedTextByPos( m_txtEdit->toPlainText().indexOf(strLine, length), strLine.size());
                    QMessageBox::information(this->m_txtEdit, "注意!!", "此指令無法被包覆");
                    return false;
                } // if

                inside = true;
                keyType.keyName = "按下執行N次";

                // qDebug() << ( int)getVirtualKey(strList.at(1)) << (int)getVirtualKey(strList.at(3));
                if ( !isKeyExsit( strList.at(1) ) )
                {
                    selectedTextByText( strList.at(1) );
                    return false;
                } // if

                if ( !str2Digit( strList.at(3), &keyType.times ) )
                {
                    selectedTextByText( strList.at(3) );
                    return false;
                } // if

                keyType.startKey = getVirtualKey(strList.at(1));
                //qDebug() << "325" << strList;
            } // if
            else if ( strList.at(2).compare("時執行,按下") == 0 )
            {
                if ( inside )
                {
                    selectedTextByPos( m_txtEdit->toPlainText().indexOf(strLine, length), strLine.size());
                    QMessageBox::information(this->m_txtEdit, "注意!!", "此指令無法被包覆");
                    return false;
                } // if

                inside = true;
                keyType.keyName = strList.at(0);
                // qDebug() << "156" << strList.at(1) << strList.at(3);
                // qDebug() << ( int)getVirtualKey(strList.at(1)) << (int)getVirtualKey(strList.at(3));
                if ( !isKeyExsit( strList.at(1) ) )
                {
                    selectedTextByText( strList.at(1) );
                    return false;
                } // if

                if ( !isKeyExsit( strList.at(3) ) )
                {
                    selectedTextByText( strList.at(3) );
                    return false;
                } // if

                keyType.startKey = getVirtualKey(strList.at(1));
                keyType.suspendKey = getVirtualKey(strList.at(3));
            } // else if
        } // else if
        else if ( strList.at(0).compare( "點擊" ) == 0 || strList.at(0).compare( "按下" ) == 0 || strList.at(0).compare( "放開" ) == 0 )
        {
            keyType.keyName = strList.at(0);
            if ( !isKeyExsit( strList.at(1) ) )
            {
                selectedTextByText( strList.at(1) );
                return false;
            } // if

            if ( strList.at(0).compare( "點擊" ) == 0 )
                keyType.keyStatus = Click;
            else if ( strList.at(0).compare( "放開" ) == 0 )
                keyType.keyStatus = Release;
            else if ( strList.at(0).compare( "按下" ) == 0 )
            {
                keyType.keyStatus = Press;
                //qDebug() << "pRESS---------------------------" << strList.at(1) << getVirtualKey(strList.at(1));
                m_PressKey.push_back( getVirtualKey(strList.at(1)) );
            } // else


            keyType.keyValue = getVirtualKey( strList.at(1) );
            keyType.millisecond = 0;       
        } // else if
        else if ( strList.at(0).compare( "同時點擊" ) == 0 )
        {
            if ( strList.size() != 4 )
            {
                qDebug() << strList;
                selectedTextByText( strList.at(0) );
                return false;
            } // if

            keyType.keyName = "同時點擊";
            keyType.keyValue = getVirtualKey( strList.at(1) );
            keyType.millisecond = 0;
            keyType.secondKey = getVirtualKey( strList.at(2) );
        } // else if
        else if ( strList.at(0).compare( "滑鼠滾輪向上" ) == 0 || strList.at(0).compare( "滑鼠滾輪向下" ) == 0 )
        {
            keyType.keyName = strList.at(0);
        } // else if
        else
        {
            selectedTextByPos( m_txtEdit->toPlainText().indexOf(strLine), strLine.size());
            return false;
        } // else

        m_KeyList.push_back(keyType);
        length += strLine.size();
    } // while

    return true;
}

QString AutoBot::readData(QFile *file)
{

    this->m_KeyList.clear();
    QString strContent;
    while(!file->atEnd())
    {
        const char*tmpChar = file->readLine();
        QString strLine = QString::fromLocal8Bit(tmpChar);
        strContent += strLine;
    } // while

    file->close();

    //this->m_txtEdit->setText(strContent);

    return strContent;
}

int AutoBot::executeLoop( QList<KeyType>::iterator& it )
{
    int times = it->times;
    QList<KeyType>::iterator initIt = (it+1);
    //// qDebug() << "loop" << times;
    int numOfInstruc = 0;
    for ( int i = 1; times == -1 || i < times; i++ )
    {       
        if ( m_StopRun ) return 0;
        for ( it = initIt; it->keyName.compare( "}") != 0; it++ )
        {          
            if ( m_StopRun ) return 0;
            processInstruction(it);
            numOfInstruc++;
        } // for     
    } // for

    it++;
    return numOfInstruc;
}

void AutoBot::executeMouseMove(QList<KeyType>::iterator& it)
{

}

bool AutoBot::executeKey(KeyType key)
{

    if ( key.keyName.compare( "延遲" ) == 0 )
    {
        // qDebug() << "Sleep" << key.millisecond;
        aSleep(key.millisecond);
        // qDebug() << "End Sleep" << key.millisecond;
    } // if
    else if ( key.keyName.compare( "左鍵點擊" ) == 0 )
    {
         Sleep(100);
         SetCursorPos( key.startPosition, key.endPosition );
         Sleep(100);
         mouse_event (MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
    } // else if
    else if ( key.keyName.compare( "右鍵點擊" ) == 0 )
    {
         Sleep(100);
         SetCursorPos( key.startPosition, key.endPosition );
         Sleep(100);
         mouse_event (MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
    } // else if
    else if ( key.keyName.compare( "同時點擊" ) == 0 )
    {
        //qDebug() << "same.......";
        keybd_event(key.keyValue, MapVirtualKey(key.keyValue, 0), KEYEVENTF_EXTENDEDKEY | 0, 0);
        keybd_event(key.keyValue, MapVirtualKey(key.keyValue, 0), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
        keybd_event(key.secondKey, MapVirtualKey(key.secondKey, 0), KEYEVENTF_EXTENDEDKEY | 0, 0);
        keybd_event(key.secondKey, MapVirtualKey(key.secondKey, 0), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    } // else if
    else if ( key.keyName.compare( "滑鼠滾輪向上" ) == 0 )
    {
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 120, 0);
    } // else if
    else if ( key.keyName.compare( "滑鼠滾輪向下" ) == 0 )
    {
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -120, 0);
    } // else if
    else if ( key.keyName.compare( "}" ) != 0 )
    {

         // qDebug() << "keyName" << key.keyName << "virvalue" << QString::number(keyValue);
         if ( key.keyStatus == Press )
         {
             if ( key.keyValue == 0x01 )
                 mouse_event (MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 );
             else if ( key.keyValue == 0x02 )
                 mouse_event (MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );
             else
                 {

                keybd_event(key.keyValue, MapVirtualKey(key.keyValue, 0), KEYEVENTF_EXTENDEDKEY | 0, 0);

                } // else
         } // if
         else if ( key.keyStatus == Release )
         {
             if ( key.keyValue == 0x01 )
                 mouse_event (MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
             else if ( key.keyValue == 0x02 )
                 mouse_event (MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
             else
                keybd_event(key.keyValue, MapVirtualKey(key.keyValue, 0), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
         } // else if
         else{
            if ( key.keyValue == 0x01 )
                mouse_event (MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
            else if ( key.keyValue == 0x02 )
                mouse_event (MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
            else
            {
                keybd_event(key.keyValue, MapVirtualKey(key.keyValue, 0), KEYEVENTF_EXTENDEDKEY | 0, 0);
                keybd_event(key.keyValue, MapVirtualKey(key.keyValue, 0), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
            } // if
         }

         Sleep(50);
    } // else

    return true;
}

void AutoBot::processInstruction( QList<KeyType>::iterator& it )
{
    //qDebug() << "504" << it->keyName;
    if ( it->keyName.compare( "loop" ) == 0 )
    {
        int nS =  executeLoop( it );
        //// qDebug() << "341 --->" << nS << it->keyName;
    } // else if
    else if ( it->keyName.compare( "移動滑鼠X軸" ) == 0 ) // 移動滑鼠X軸 100 500 10 -> move x軸 從100到500 每移動1個pixel停10ms
    {

        while( m_MTX != NULL && !m_MTX->isStop() )
            m_MTX->stop();
         this->m_killMouseThread_X = false;
         // qDebug() << "367------>" << it->keyName << "start";
         m_MTX = new MouseThread(true, it->startPosition, it->endPosition, it->millisecond, &m_killMouseThread_X, m_EndKey);
         m_MTX->start();
         //executeMouseMove( it );
    } // else if
    else if ( it->keyName.compare( "移動滑鼠Y軸" ) == 0 ) // 移動滑鼠X軸 100 500 10 -> move x軸 從100到500 每移動1個pixel停10ms
    {
        while( m_MTY != NULL && !m_MTY->isStop() )
            m_MTY->stop();

         this->m_killMouseThread_Y = false;
         m_MTY = new MouseThread(false, it->startPosition, it->endPosition, it->millisecond, &m_killMouseThread_Y, m_EndKey);
         m_MTY->start();

        //executeMouseMove( it );
    } // else if
    else if ( it->keyName.compare( "停止滑鼠移動" ) == 0 ) // MouseStop X/Y
    {
        this->m_killMouseThread_X = true;
        this->m_killMouseThread_Y = true;

    } // else if
    else if ( it->keyName.compare( "MouseStopX" ) == 0 ) // MouseStop X/Y
    {
        this->m_killMouseThread_X = true;
        // qDebug() << "clear mTKX";
    } // else if
    else if ( it->keyName.compare( "MouseStopY" ) == 0 ) // MouseStop X/Y
    {
        this->m_killMouseThread_Y = true;
    } // else if
    else if ( it->keyName.compare( "Execute" ) == 0 ) // Execute per 1000 ms {
    {


        AutoBot* insideT = new AutoBot(m_txtEdit, it, m_PressKey);
        connect(insideT, SIGNAL(finished()),this, SLOT(endThread()));
        insideT->start();
        m_NumOfThread++;

        int nEnd = 1;
        while ( nEnd > 0 )
        {
            if ( m_StopRun ) return;
            if ( (++it)->keyName.compare( "loop" ) == 0 || it->keyName.compare( "Execute" ) == 0 || it->keyName.compare( "當按下" ) == 0 )
                nEnd++;
            else if ( it->keyName.compare( "}" ) == 0 )
                nEnd--;
        } // while
    } // else if
    else if ( it->keyName.compare( "按下執行N次" ) == 0 ) // 當按下 ... 時執行 ... 次 {
    {
        qDebug() << "603" << "按下執行N次";
        AutoBot* insideT = new AutoBot(m_txtEdit, it, m_EndKey, it->startKey, it->startKey, m_PressKey, true);
        connect(insideT, SIGNAL(finished()),this, SLOT(endThread()));
        insideT->start();
        m_NumOfThread++;

        int nEnd = 1;
        while ( nEnd > 0 )
        {
            if ( m_StopRun ) return;
            if ( (++it)->keyName.compare( "loop" ) == 0 || it->keyName.compare( "Execute" ) == 0 || it->keyName.compare( "當按下" ) == 0)
                nEnd++;
            else if ( it->keyName.compare( "}" ) == 0 )
                nEnd--;
        } // while
    } // else if
    else if ( it->keyName.compare( "當按下" ) == 0 ) // 當按下 ... 時執行,按下 ... 時結束 {
    {
        //qDebug() << "330" << (int)m_EndKey << (int)it->startKey << (int)it->suspendKey;
        AutoBot* insideT = new AutoBot(m_txtEdit, it, m_EndKey, it->startKey, it->suspendKey, m_PressKey, false);
        //qDebug() << "WTF--->" << insideT;
        connect(insideT, SIGNAL(finished()),this, SLOT(endThread()));
        insideT->start();
        m_NumOfThread++;

        int nEnd = 1;
        while ( nEnd > 0 )
        {
            if ( m_StopRun ) return;
            if ( (++it)->keyName.compare( "loop" ) == 0 || it->keyName.compare( "Execute" ) == 0 || it->keyName.compare( "當按下" ) == 0)
                nEnd++;
            else if ( it->keyName.compare( "}" ) == 0 )
                nEnd--;
        } // while

        // qDebug() << "358" << it->keyName;
    } // else if
    else if ( it->keyName.compare( "}" ) != 0 )
        executeKey(*it);
}

bool AutoBot::executeAutoBot()
{
    for ( QList<KeyType>::iterator it = m_KeyList.begin(); it < m_KeyList.end(); it++ )
    {
        // qDebug() << "111------>" << it->keyName;
        if ( m_StopRun ) break;
        processInstruction(it);
    } // for

    // qDebug() << "Out side End";

    return true;
}

bool AutoBot::executeAutoBot( QList<KeyType>::iterator init )
{
    QList<KeyType>::iterator begin = (init+1);
    while ( !m_StopRun )
    {
        for ( QList<KeyType>::iterator it = begin; it->keyName.compare( "}") != 0; it++ )
        {
            // qDebug() << "inside 385------>" << it->keyName;
            if ( m_StopRun ) return true;
            processInstruction(it);
        } // for


        if ( !aSleep(init->millisecond) || m_executeOneTime ) break;
        // qDebug() << "392";
    } // while

    m_StopRun = true;
    return true;
}

void AutoBot::run()
{
    m_killMouseThread_X = true;
    m_killMouseThread_Y = true;
    m_NumOfThread = 0;
    m_StopRun = false;

    sThread* st = new sThread();
    st->stop_Run = &m_StopRun;
    st->EndKey = &m_EndKey;
    while ( !m_insideThread && !m_isConditionExecute && !(GetKeyState(m_StartKey) < 0) )
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } // while

    //CreateThread(NULL, 0, ThreadStop, NULL, 0, NULL);

    if ( m_openAlert ) Beep( 500, 800);
    //qDebug() << this;

    HANDLE hThread = NULL;
    if ( m_isConditionExecute )
    {
        //// qDebug() << "run condition";
        while (!(GetKeyState(m_OutsideEndKey) < 0))
        {
            //// qDebug() << " running";

            if ( GetKeyState(m_StartKey) < 0 && !m_StopRun )
            {
                //qDebug() << "712" << (int)m_EndKey << (int)m_StartKey << (int)m_OutsideEndKey;
                hThread = CreateThread(NULL, 0, ThreadStop, st, 0, NULL);
                executeAutoBot( m_insideIt );
            } // if
            else if ( m_StopRun )
            {
                CloseHandle(hThread);
                *st->stop_Run = true;
                //qDebug() << "Stop" << (int)m_EndKey << (int)m_StartKey << (int)m_OutsideEndKey;;
                m_StopRun = false;
                releasePressKey();
            } // else if

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        } // while
    } // if
    else if ( m_insideThread )
    {
        hThread = CreateThread(NULL, 0, ThreadStop, st, 0, NULL);
        this->executeAutoBot( m_insideIt );
    } // else if
    else
    {
        hThread = CreateThread(NULL, 0, ThreadStop, st, 0, NULL);
        this->executeAutoBot();
    } // else

    while ( !this->m_killMouseThread_X || !this->m_killMouseThread_Y || m_NumOfThread > 0 ){
        if ( (GetKeyState(m_EndKey) < 0) && m_insideThread ) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    //// qDebug() << "out side end";
   CloseHandle(hThread);
    m_killMouseThread_X = true;
    m_killMouseThread_Y = true;
    m_NumOfThread = 0;
    m_insideThread = false;
    releasePressKey();
    m_PressKey.clear();
    this->quit();
    //this->exit(0);
}

bool AutoBot::readVirtualKeyTable()
{
    QFile file( "autoBot.key" );
    //qDebug() << "r1";
    if ( !file.open(QIODevice::ReadOnly) )
        return false;
    //qDebug() << "r2";
    while(!file.atEnd())
    {
        //qDebug() << "r3";
        const char*tmpChar = file.readLine();
        QString strLine = QString::fromLocal8Bit(tmpChar);
        // qDebug() << strLine;
        strLine.remove("\n");
        strLine.remove("\r");
        if ( strLine.size() <= 0 ) continue;
        QStringList strList = strLine.split(" ");
        VirKey vKey;
        bool bStatus = false;

        vKey.keyName = strList.at(0);
        vKey.keyVal = strList.at(1).toUInt(&bStatus,16);
        // qDebug() << vKey.keyName << vKey.keyVal;
        this->m_virKeyList.push_back(vKey);
        this->m_virKeyMap[vKey.keyName] = vKey.keyVal;
    } // while
    //qDebug() << "r4";
    file.close();
    // qDebug() << "readVirtualKeyTable" << m_virKeyList.size() << " map: " << m_virKeyMap.size();
    return true;
}

QStringList AutoBot::getAllVirtualKeys()
{
    QStringList sList;
    foreach( VirKey vKey, this->m_virKeyList )
        sList << vKey.keyName;
    return sList;
}

bool AutoBot::isKeyExsit(QString str)
{
    if ( str.compare("延遲") == 0 ||
         ( str.size() == 1 && (( ('a' <= str[0] && str[0] <= 'z') || ('A' <= str[0] && str[0] <= 'Z')) || ('0' <= str[0] && str[0] <= '9') ) ))
        return true;
    return this->m_virKeyMap.contains(str);
}

bool AutoBot::aSleep(int ms)
{
    int div = ms / 100;
    int mod = ms % 100;
    for ( int i = 0; i < div; i++ ) {
        if ( m_StopRun ) return false;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } // for


    std::this_thread::sleep_for(std::chrono::milliseconds(mod));
    if ( m_StopRun ) return false;
    return true;
}

bool AutoBot::addVirtualKey2Table( QStringList sList )
{

    QFile file( "autoBot.key" );
    if ( !file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text) )
        return false;
    QTextStream out(&file);
    for ( int i = 0; i < sList.size(); i+= 2 )
    {
        out << "\n" << sList[i] << " " << sList[i+1];
        VirKey vKey;
        bool bStatus;
        vKey.keyName = sList.at(i);
        vKey.keyVal = sList.at(i+1).toUInt(&bStatus,16);
        m_virKeyList.push_back(vKey);
        m_virKeyMap[vKey.keyName] = vKey.keyVal;
    } // for

    file.close();
    return true;
}

bool AutoBot::removeVirtualKey2Table(QString str)
{
    for ( int i = 0; i < this->m_virKeyList.size(); i++ )
    {
        //// qDebug() << m_virKeyList[i].keyName << str;
        if ( m_virKeyList[i].keyName.compare(str) == 0 )
            m_virKeyList.removeAt(i);
    } // for

    m_virKeyMap.remove(str);

    QFile file( "autoBot.key" );
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Text) )
        return false;

    QTextStream out(&file);
    for ( int i = 0; i < m_virKeyList.size(); i++ )
        out << m_virKeyList[i].keyName << " " << "0x" << QString::number(m_virKeyList[i].keyVal, 16) << "\n";
    file.close();
    return true;
}

void AutoBot::releasePressKey()
{
    //qDebug() << "num of press key" << m_PressKey.size();
    for ( unsigned char c : m_PressKey )
    {
        //qDebug() << c;
        if ( c == 0x01 )
            mouse_event (MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
        else if ( c == 0x02 )
            mouse_event (MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
        else
           keybd_event(c, MapVirtualKey(c, 0), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    } // for


}

QList<KeyType> AutoBot::getData()
{
    return this->m_KeyList;
}

QList<unsigned char> AutoBot::getPressKey()
{
    return this->m_PressKey;
}
