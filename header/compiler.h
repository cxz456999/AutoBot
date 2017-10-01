#ifndef COMPILER_H
#define COMPILER_H
#include "header/autobot.h"
#include <QProcess>
#include <QObject>
struct Function
{
    QString name;
    QString content;
};

class compiler;

class compiler : public QObject
{
    Q_OBJECT
public:
    ~compiler();
    compiler(QString compileFile, QString fileName, int in_strStopKey, QStringList Hint, QString deadline, QList<KeyType> in_KeyList, QList<unsigned char>in_PressKey);
    bool execute();
private slots:
    void deleteCppFile(int exitCode, QProcess::ExitStatus exitStatus);
private:
    void processInstruction(QList<KeyType>::iterator &it );
    QString makeKeyboardAndMouse( KeyType key );
    Function makeExecutePerMs(QList<KeyType>::iterator &init);
    QString makeLoop(QList<KeyType>::iterator &it);
    QString makeInsideInstructions(QList<KeyType>::iterator &it);
    Function makeConditionExecute(QList<KeyType>::iterator &it, bool NTimes);
    QString makeReleaseKey();
    bool compile();
    QString m_compileFile = "";
    QString m_FileName = "";
    int m_StartKey = 0x71;
    int m_EndKey = 0x72;
    QList<KeyType> m_KeyList;
    QList<unsigned char> m_PressKey;
    QList<Function> m_Functions;
    QString m_Main = "";
    QString m_Global = "";
    int m_numOfLoop = 0; // 幾層迴圈
    int m_numOfFunction = 0;
    QProcess* m_Process = NULL;
    QString m_deadline;
};

#endif // COMPILER_H
