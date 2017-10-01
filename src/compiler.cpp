#include "header/login.h"
#include "header/compiler.h"
#include <QDebug>
#include <QList>
#include <QFile>
#include <QMessageBox>

compiler::~compiler()
{
    if ( m_Process != NULL )
        delete m_Process;
}

compiler::compiler(QString compileFile, QString fileName, int in_StopKey, QStringList Hint, QString deadline, QList<KeyType> in_KeyList, QList<unsigned char> in_PressKey)
{
    m_FileName = fileName;
    m_EndKey = in_StopKey;
    m_KeyList = in_KeyList;
    m_PressKey = in_PressKey;
    m_deadline = deadline;
    m_compileFile = compileFile;
    //qDebug() << m_compileFile;
    m_Main = "int main()\n{\n";
    m_Main += "if ( !checkMac(\"" + login::getMacAddress() + "\") || !checkDate(\"" + deadline + "\") )\n";
    m_Main += "     return 0;\n";
    m_Main += "\n";
    m_Main += "\n";
    m_Main += "cout << \" -----------------------------------------\" << endl;\n";
    m_Main += "cout << \"|AutoBot - 腳本不求人 			           \" << endl;\n";
    m_Main += "cout << \"|https://www.facebook.com/AutoBotEx/	   \" << endl;\n";
    m_Main += "cout << \" -----------------------------------------\" << endl;\n";
    //m_Main += "cout << \"" + m_FileName + "\" << endl;\n";

    for ( QString s : Hint )
        m_Main += "cout << \"" + s +  "\" << endl;\n";
    m_Main += "StopRun = false, RealStop = false;\n";
    m_Main += "CreateThread(NULL, 0, ThreadExit, NULL, 0, NULL);\n";
}

bool compiler::execute()
{
    if ( m_compileFile.isEmpty() ){
        QMessageBox::information(0, "Error",
            "Compile資料遺失");
        return false;
    } // if


    m_Global = "#define exitKey " + QString::number(m_EndKey) + "\n";
    m_Global += m_compileFile;

    qDebug() << "processInstruction" << m_KeyList.size();
    for ( QList<KeyType>::iterator it = m_KeyList.begin(); it < m_KeyList.end(); it++ )
    {
        processInstruction(it);
    } // for

    m_Main += "while(!RealStop) Sleep(100);\n";
    m_Main += makeReleaseKey();
    m_Main += "return 0;\n}\n";

    QFile ff( "./FUCK.cpp" );
    if ( !ff.open(QIODevice::WriteOnly | QIODevice::Text) )
        return false;
    qDebug() << "Output";
    QTextStream out(&ff);
    out << m_Global << "\n";
    for( Function f : m_Functions )
        out << f.content << "\n";
    out << m_Main;
    ff.close();

    compile();
    return true;
}

void compiler::deleteCppFile(int exitCode, QProcess::ExitStatus exitStatus)
{
    //remove("./FUCK.cpp");
    qDebug() << "remove";
    QMessageBox::information(0, "Success",
        "製作完成");
}
#include <windows.h>
bool compiler::compile()
{
    //system("C:\\Users\\wns\\Desktop\\AutoBot\\Compile\\bin\\g++ -o C:\\Users\\wns\\Desktop\\AutoBot\\Compile\\123444.exe C:\\Users\\wns\\Desktop\\AutoBot\\Compile\\bin\\FUCK.cpp");
    /*QString program = "./Compile/bin/g++";
    QStringList arguments;
    arguments  << "./Compile/bin/FUCK.cpp" << "-o" << "" + m_FileName;*/

    QString program = "g++";
    QStringList arguments;
    arguments  << "FUCK.cpp" << "-o" << "" + m_FileName;

    /*QString qs = "-o ./Compile/bin/" + m_FileName + ".exe ./Compile/bin/FUCK.cpp";
    QString gg = "./Compile/bin/g++.exe";
    ShellExecute(NULL, NULL, (const wchar_t*)gg.utf16(), (const wchar_t*)qs.utf16(), NULL, SW_SHOW);
    qDebug() << "FUCKFUCK";
    QMessageBox::information(0, "FUCKFUCK",
        "FUCKFUCK");*/
    /*QString program = "g++";
    QStringList arguments;
    arguments << "-o" << m_FileName + ".exe" << "./bin/FUCK.cpp"*/;
    m_Process = new QProcess();
    m_Process->start(program, arguments);
    connect(m_Process, SIGNAL(finished(int , QProcess::ExitStatus )), this, SLOT(deleteCppFile(int , QProcess::ExitStatus )));
    m_Process->waitForFinished();
    QString s(m_Process->readAllStandardOutput());


}

QString compiler::makeKeyboardAndMouse(KeyType key)
{

    QString ret = "";
    if ( key.keyName.compare( "左鍵點擊" ) == 0 )
        {
             ret += "Sleep(50);\n";
             ret += "SetCursorPos( " + QString::number(key.startPosition) + ", " + QString::number(key.endPosition) + " );\n";
             ret += "Sleep(50);\n";
            ret += "mouse_event (MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );\n";
        } // else if
        else if ( key.keyName.compare( "右鍵點擊" ) == 0 )
        {
             ret += "Sleep(100);\n";
             ret += "SetCursorPos( " + QString::number(key.startPosition) + ", " + QString::number(key.endPosition) + " );\n";
             ret += "Sleep(100);\n";
             ret += "mouse_event (MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );\n";
        } // else if
        else if ( key.keyName.compare( "同時點擊" ) == 0 )
        {
            ret += "keybd_event(" + QString::number(key.keyValue) + ", MapVirtualKey(" + QString::number(key.keyValue) + ", 0), KEYEVENTF_EXTENDEDKEY | 0, 0);\n";
            ret += "keybd_event(" + QString::number(key.keyValue) + ", MapVirtualKey(" + QString::number(key.keyValue) + ", 0), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);\n";
            ret += "keybd_event(" + QString::number(key.secondKey) + ", MapVirtualKey(" + QString::number(key.secondKey) + ", 0), KEYEVENTF_EXTENDEDKEY | 0, 0);\n";
            ret += "keybd_event(" + QString::number(key.secondKey) + ", MapVirtualKey(" + QString::number(key.secondKey) + ", 0), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);\n";
        } // else if
    else if ( key.keyName.compare( "滑鼠滾輪向上" ) == 0 )
    {
        ret += "mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 120, 0);\n";
    } // else if
    else if ( key.keyName.compare( "滑鼠滾輪向下" ) == 0 )
    {
        ret += "mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -120, 0);\n";
    } // else if
        else if ( key.keyName.compare( "}" ) != 0 )
        {
             if ( key.keyStatus == Press )
             {
                 if ( key.keyValue == 0x01 )
                     ret += "mouse_event (MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 );\n";
                 else if ( key.keyValue == 0x02 )
                     ret += "mouse_event (MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );\n";
                 else
                     {

                    ret += "keybd_event(" + QString::number(key.keyValue) + ", MapVirtualKey(" + QString::number(key.keyValue) + ", 0), KEYEVENTF_EXTENDEDKEY | 0, 0);\n";

                    } // else
             } // if
             else if ( key.keyStatus == Release )
             {
                 if ( key.keyValue == 0x01 )
                     ret += "mouse_event (MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );\n";
                 else if ( key.keyValue == 0x02 )
                     ret += "mouse_event (MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );\n";
                 else
                    ret += "keybd_event(" + QString::number(key.keyValue) + ", MapVirtualKey(" + QString::number(key.keyValue) + ", 0), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);\n";
             } // else if
             else{
                if ( key.keyValue == 0x01 )
                    ret += "mouse_event (MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );\n";
                else if ( key.keyValue == 0x02 )
                    ret += "mouse_event (MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );\n";
                else
                {
                    ret += "keybd_event(" + QString::number(key.keyValue) + ", MapVirtualKey(" + QString::number(key.keyValue) + ", 0), KEYEVENTF_EXTENDEDKEY | 0, 0);\n";
                    ret += "keybd_event(" + QString::number(key.keyValue) + ", MapVirtualKey(" + QString::number(key.keyValue) + ", 0), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);\n";
                } // if
             }
        } // else

    return ret;
}

QString compiler::makeLoop(QList<KeyType>::iterator &it)
{
    m_numOfLoop++;
    qDebug() << "makeLoop";
    QString ret = "";
    QString var = "a" + QString::number(m_numOfLoop);
    bool isInfinite = it->times == -1;
    int maxNum = isInfinite ?  88888 : it->times;
    ret += "for ( int " + var + " = 0; " + var + " < " + QString::number(maxNum) + "; " + var + "++ )\n{\n";
    it++;
    for ( ; it->keyName.compare( "}") != 0; it++ )
    {
        ret += makeInsideInstructions(it);
    } // for

    if ( isInfinite )
        ret += var + " = 0;\n";
    ret += "if ( RealStop ) break;\n";
    ret += "\n}\n";
    qDebug() << ret;
    return ret;
}

Function compiler::makeExecutePerMs(QList<KeyType>::iterator &it)
{
    m_numOfFunction++;
    qDebug() << "makeExecutePerMs";
    Function fun;
    fun.name = "function" + QString::number(m_numOfFunction);
    QString ret = "DWORD WINAPI " + fun.name + "(LPVOID pM)\n{\n";
    ret += "while(!StopRun) {";
    for ( ; it->keyName.compare( "}") != 0; it++ )
    {
        ret += makeInsideInstructions(it);
    } // for

    ret += "\n}\nreturn 0;\n}\n";
    fun.content = ret;
    return fun;
}

Function compiler::makeConditionExecute(QList<KeyType>::iterator &it, bool NTimes)
{
    m_numOfFunction++;
    qDebug() << "makeConditionExecute";
    Function fun;
    fun.name = "function" + QString::number(m_numOfFunction);
    QString ret = "DWORD WINAPI " + fun.name + "(LPVOID pM)\n{\n";
    ret += "CondEx* ce = static_cast<CondEx*>(pM);\n";
    ret += "HANDLE hThread = NULL;\n";
    ret += "while ( true )\n";
    ret += "{\n";
    ret += "if ( GetKeyState(ce->startKey) < 0 && ( StopRun || hThread == NULL ) ){\n";
    ret += "StopRun = false;\n";
    ret += "hThread = CreateThread(NULL, 0, ThreadStop, ce, 0, NULL);\n";
    if ( !NTimes )
        ret += "while (!StopRun)\n";
    else
        ret += "for ( int mkcon = 0; mkcon < " + QString::number(it->times) + "; mkcon++ )\n";
    ret += "{\n";
    it++;
    for ( ; it->keyName.compare( "}") != 0; it++ )
    {
        ret += makeInsideInstructions(it);
    } // for

    ret += "}\n";
    // release
    ret += makeReleaseKey();
    // end release
    ret += "StopRun = true;\n";
    ret += "CloseHandle(hThread);\n";
    ret += "} // if\n";
    ret += "Sleep(50);\n";
    ret += "} // while\n";
    ret += "ce->isStop = true;\n";
    ret += "return 0;\n";
    ret += "}\n";
    fun.content = ret;
    return fun;
}

QString compiler::makeInsideInstructions(QList<KeyType>::iterator &it)
{
    qDebug() << "makeInsideInstructions";
    QString ret = "";
    if ( it->keyName.compare( "loop" ) == 0 )
    {
        ret += makeLoop(it);
    } // else if
    else if ( it->keyName.compare( "MouseStopX" ) == 0 ) // MouseStop X/Y
    {
        ret += "mMoveX.isStop = true;\n";
    } // else if
    else if ( it->keyName.compare( "MouseStopY" ) == 0 ) // MouseStop X/Y
    {
        ret += "mMoveY.isStop = true;\n";
    } // else if
    else if ( it->keyName.compare( "停止滑鼠移動" ) == 0 ) // MouseStop X/Y
    {
        ret += "mMoveX.isStop = true;\n";
        ret += "mMoveY.isStop = true;\n";

    } // else if
    else if ( it->keyName.compare( "延遲" ) == 0 )
    {
         ret += "aSleep(" + QString::number(it->millisecond) + ");\n";
    } // else if
    else if ( it->keyName.compare( "移動滑鼠X軸" ) == 0 ) // 移動滑鼠X軸 100 500 10 -> move x軸 從100到500 每移動1個pixel停10ms
    {
        ret += "mMoveX.isX = true;\n";
        ret += "mMoveX.isStop = false;\n";
        ret += "mMoveX.startPos = " + QString::number(it->startPosition)+ ";\n";
        ret += "mMoveX.endPos = " + QString::number(it->endPosition)+ ";\n";
        ret += "mMoveX.perMS = " + QString::number(it->millisecond)+ ";\n";
        ret += "CreateThread(NULL, 0, MoveMouse, &mMoveX, 0, NULL);\n";

    } // else if
    else if ( it->keyName.compare( "移動滑鼠Y軸" ) == 0 ) // 移動滑鼠X軸 100 500 10 -> move x軸 從100到500 每移動1個pixel停10ms
    {
        ret += "mMoveY.isX = false;\n";
        ret += "mMoveY.isStop = false;\n";
        ret += "mMoveY.startPos = " + QString::number(it->startPosition)+ ";\n";
        ret += "mMoveY.endPos = " + QString::number(it->endPosition)+ ";\n";
        ret += "mMoveY.perMS = " + QString::number(it->millisecond)+ ";\n";
        ret += "CreateThread(NULL, 0, MoveMouse, &mMoveY, 0, NULL);\n";
    } // else if
    else if ( it->keyName.compare( "}" ) != 0 )
        ret += makeKeyboardAndMouse(*it);


    return ret;
}

void compiler::processInstruction(QList<KeyType>::iterator &it )
{
    //qDebug() << "WTFFFFFFFFFFFFFFF" << it->keyName;

    if ( it->keyName.compare( "Execute" ) == 0 ) // Execute per 1000 ms {
    {
        Function fun = makeExecutePerMs(it);
        m_Functions.push_back(fun);
        m_Main += "CreateThread(NULL, 0, " + fun.name + ", NULL, 0, NULL);\n";
    } // else if
    else if ( it->keyName.compare( "按下執行N次" ) == 0 ) // 當按下 ... 時執行,按下 ... 時結束 {
    {
        static int numOfConEx = 0;
        QString strConEx = "ce" + QString::number(numOfConEx++);
        m_Main += "CondEx " + strConEx + ";\n";
        m_Main += strConEx + ".startKey =" + QString::number(it->startKey) + ";\n";
        m_Main += strConEx + ".endKey = " + QString::number(it->suspendKey) + ";\n";
        m_Main += strConEx + ".isStop = false;\n";
        Function fun = makeConditionExecute(it, true);
        m_Main += "CreateThread(NULL, 0, " + fun.name + ", &" + strConEx + ", 0, NULL);\n";
        m_Functions.push_back(fun);
    } // else if
    else if ( it->keyName.compare( "當按下" ) == 0 ) // 當按下 ... 時執行,按下 ... 時結束 {
    {
        static int numOfConEx = 0;
        QString strConEx = "ce" + QString::number(numOfConEx++);
        m_Main += "CondEx " + strConEx + ";\n";
        m_Main += strConEx + ".startKey =" + QString::number(it->startKey) + ";\n";
        m_Main += strConEx + ".endKey = " + QString::number(it->suspendKey) + ";\n";
        m_Main += strConEx + ".isStop = false;\n";
        Function fun = makeConditionExecute(it, false);
        m_Main += "CreateThread(NULL, 0, " + fun.name + ", &" + strConEx + ", 0, NULL);\n";
        m_Functions.push_back(fun);
    } // else if
    else
        m_Main += makeInsideInstructions(it);
}

QString compiler::makeReleaseKey()
{
    QString ret = "";
    for ( unsigned char c : m_PressKey )
    {
        if ( c == 0x01 )
            ret += "mouse_event (MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );\n";
        else if ( c == 0x02 )
            ret += "mouse_event (MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );\n";
        else
           ret += "keybd_event(" + QString::number(c) + ", MapVirtualKey(" + QString::number(c) + ", 0), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);\n";
    } // for

    return ret;
}
