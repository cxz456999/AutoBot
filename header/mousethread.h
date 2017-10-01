#ifndef MOUSETHREAD_H
#define MOUSETHREAD_H
#include <QThread>
class MouseThread : public QThread
{
public:
    MouseThread(bool isX, int in_StrPo, int in_EndPo, int in_perMS, bool *isEnd, unsigned char in_StopKey);
    ~MouseThread();
    void run();
    void stop();
    bool isStop();
private:
    bool* m_IsEnd = NULL;
    bool m_RealEnd = false;
    bool m_IsX;
    int m_StartPo = 0;
    int m_EndPo = 0;
    int m_PerMS = 10;
    unsigned char m_StopKey;
};

#endif // MOUSETHREAD_H
