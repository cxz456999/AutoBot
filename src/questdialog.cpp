#include "header/questdialog.h"
#include "ui_questdialog.h"
#include <QMessageBox>
#include <QDebug>
bool* stop = NULL;
QLineEdit* poX = NULL, *poY = NULL;
QLabel* cur_mouseX = NULL, *cur_mouseY = NULL;
QuestDialog *qd = NULL;


DWORD WINAPI ThreadFun(LPVOID pM)
{
    POINT *po = static_cast<POINT*>(pM);
    while ( !(GetAsyncKeyState(VK_F2) & 1) && !*stop )
    {

        GetCursorPos(po);
        if ( GetKeyState(VK_RBUTTON) < 0 )
        {
            //qDebug() << "( " << QString::number(po.x) << ", " << QString::number(po.y) << " )";
            poX->setText(QString::number(po->x));
            poY->setText(QString::number(po->y));
            //QMessageBox::information(qd, "Error", "尚為增加此按鍵");
        } // if

        cur_mouseX->setText("x: " + QString::number(po->x));
        cur_mouseY->setText("y: " + QString::number(po->y));
    }

    *stop = true;
    return 0;
}

QuestDialog::QuestDialog(POINT *po, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestDialog)
{
    setWindowFlags( Qt::WindowStaysOnTopHint );
    ui->setupUi(this);
    stop = &m_Stop;

    poX = ui->showPosX;
    poY = ui->showPosY;
    cur_mouseX = ui->cur_mouseX;
    cur_mouseY = ui->cur_mouseY;
    m_po = po;
    qd = this;
    m_hThread = CreateThread(NULL, 0, ThreadFun, m_po, 0, NULL);
}

void QuestDialog::closeEvent( QCloseEvent *bar )
{
    m_Stop = true;
    CloseHandle(m_hThread);
}

QuestDialog::~QuestDialog()
{
    m_Stop = true;
    CloseHandle(m_hThread);
    delete ui;
}
