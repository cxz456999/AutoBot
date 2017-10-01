#ifndef QUESTDIALOG_H
#define QUESTDIALOG_H

#include <QDialog>
#include <windows.h>
namespace Ui {
class QuestDialog;
}

class QuestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QuestDialog(POINT *po, QWidget *parent = 0);

    ~QuestDialog();

private:
    void closeEvent( QCloseEvent *bar );
    Ui::QuestDialog *ui;
    int* m_PosX = NULL;
    int* m_PosY = NULL;
    POINT *m_po;
    bool m_Stop = false;
    HANDLE m_hThread = NULL;
};

#endif // QUESTDIALOG_H
