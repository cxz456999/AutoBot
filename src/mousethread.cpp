#include "header/mousethread.h"
#include <windows.h>
#include <thread>
#include <QDebug>
MouseThread::~MouseThread()
{

}

MouseThread::MouseThread(bool isX, int in_StrPo, int in_EndPo, int in_perMS, bool* isEnd, unsigned char in_StopKey)
{
    this->m_IsEnd = isEnd;
    this->m_IsX = isX;
    this->m_StartPo = in_StrPo;
    this->m_EndPo = in_EndPo;
    this->m_PerMS = in_perMS;
    this->m_StopKey = in_StopKey;
}

void MouseThread::stop()
{
    *m_IsEnd = true;
}

bool MouseThread::isStop()
{
    return m_RealEnd;
}

void MouseThread::run()
{
    //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    qDebug() << "MouseThread"  << m_StartPo << m_EndPo << m_PerMS;
    int po = this->m_StartPo;
    if ( po > this->m_EndPo )
    {
        this->m_StartPo = this->m_EndPo;
        this->m_EndPo = po;
        po = m_StartPo;
    } // if

    POINT p;
    m_RealEnd = false;
    int add = 1;
    bool relativedMove = po == -1;

    while ( !*m_IsEnd && po < m_EndPo )
    {
        //qDebug() << "mouse move";
        if ( GetKeyState(m_StopKey) < 0)
        {
            *m_IsEnd = true;
            //qDebug() << "end mouse move";
            break;
        } // if


        GetCursorPos(&p);
        if ( m_IsX )
            SetCursorPos(po, p.y );
        else
            SetCursorPos(p.x, po );

       // if (  )
        if ( (po+=add) == m_EndPo ) {
            add = -1;
            po = m_EndPo -1;
        } // if
        else if ( po == m_StartPo ) {
            add = 1;
            po = m_StartPo + 1;
        } //
        std::this_thread::sleep_for(std::chrono::milliseconds(this->m_PerMS));
    } // while
    //QString mess = QString::fromUtf8("腳本結束") ;
    //QMessageBox::information(0, tr("Warning"), mess) ;
    //this->exec();
    //deleteLater();
    *m_IsEnd = true;
    m_RealEnd = true;
    //qDebug() << "end mouse move";
}
