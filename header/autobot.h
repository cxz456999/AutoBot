#ifndef AUTOBOT_H
#define AUTOBOT_H
#include "header/mousethread.h"
#include <QString>
#include <QList>
#include <QThread>
#include <QTextEdit>
#include <QFile>
#include <QList>
#include <QMap>
enum KeyStatus{
    Press = 8787878, Release = 78787878, Click = 5454545454
};
struct VirKey
{
    QString keyName;
    unsigned char keyVal;
};

struct KeyType
{
    QString keyName;
    KeyStatus keyStatus;
    int millisecond;
    bool goBack;
    int times;
    int startPosition; // move X軸
    int endPosition;
    unsigned char startKey;
    unsigned char suspendKey;
    unsigned char keyValue;
    unsigned char secondKey;
};
class AutoBot;
class AutoBot : public QThread
{
    Q_OBJECT

public:
    AutoBot( QTextEdit * in_txtEdit );
    AutoBot(QTextEdit * in_txtEdit, QList<KeyType>::iterator in_Init, QList<unsigned char> PressKey );
    AutoBot(QTextEdit * in_txtEdit, QList<KeyType>::iterator in_Init, unsigned char in_OEKey, unsigned char in_StartKey, unsigned char in_EndKey, QList<unsigned char> PressKey , bool in_executeOneTime);
    ~AutoBot();
    bool recordMouseAndKeyboard(); // use hook SetWindowsHookEx(WH_KEYBOARD_LL,keyboardHookProc,hInstance,0);
    QString readData(QFile *file);
    bool saveData(QFile *file);
    bool saveData(QFile *file, QString content);
    bool readDataFromTxtEdit(QStringList all);
    bool executeAutoBot();
    bool executeAutoBot(QList<KeyType>::iterator init);
    bool executeKey(KeyType key);
    void processInstruction(QList<KeyType>::iterator &it );
    int executeLoop(QList<KeyType>::iterator& it);
    //void executeThread(QList<KeyType>::iterator& it);
    void executeMouseMove(QList<KeyType>::iterator& it);
    bool readVirtualKeyTable();
    bool addVirtualKey2Table(QStringList sList);
    bool removeVirtualKey2Table(QString str);
    QStringList getAllVirtualKeys();
    bool isKeyExsit(QString str);
    bool aSleep(int ms);
    void deselectedAllText();
    void run();
    void releasePressKey();
    unsigned char getVirtualKey(QString str);
    void setHotKey(int start, int end, bool openAlert);
    QList<KeyType> getData();
    QList<unsigned char> getPressKey();
    QList<VirKey> m_virKeyList;
private slots:
    void endThread();
private:
    void selectedTextByPos(int start, int length);
    void selectedTextByText( QString target );
    bool str2Digit( QString str, int* ret );
    QList<KeyType> m_KeyList;
    QTextEdit * m_txtEdit;
    QMap<QString, unsigned char> m_virKeyMap;

    bool m_killMouseThread_X = true;
    bool m_killMouseThread_Y = true;
    MouseThread * m_MTX = NULL;
    MouseThread * m_MTY = NULL;
    // for inside thread
    bool m_insideThread = false;
    QList<KeyType>::iterator m_insideIt;
    QList<AutoBot> m_InsideThreadList;
    int m_NumOfThread = 0;
    // end inside thread
    // for condition execute
    bool m_isConditionExecute = false;
    unsigned char m_OutsideEndKey = 0x10;
    // end condition execute
    bool m_StopRun = false;
    unsigned char m_StartKey = 0x10;
    unsigned char m_EndKey = 0x10;
    QList<unsigned char> m_PressKey;
    bool m_openAlert = true;
    bool m_executeOneTime = false;
};

#endif // AUTOBOT_H
