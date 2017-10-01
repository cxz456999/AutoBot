#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
class MyThread : public QThread
{
public:
    MyThread(bool isX, int in_StrPo, int in_EndPo, int in_perMS, bool *isEnd);
    ~MyThread();
    void run();
private:
    bool* m_IsEnd = NULL;
    bool m_IsX;
    int m_StartPo;
    int m_EndPo;
    int m_PerMS;
};
#endif // MYTHREAD_H
