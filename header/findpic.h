#ifndef FINDPIC_H
#define FINDPIC_H

#include <QDialog>
#include <QtGui>
#include<QMessageBox>
#include <QGraphicsScene>
#include <windows.h>

namespace Ui {
class findpic;
}

class findpic : public QDialog
{
    Q_OBJECT

public:
    explicit findpic(QWidget *parent = 0);
    ~findpic();
    bool captureScreen();
    bool findImg(int similar);
    int convert2Gray(QImage & img); // return mean pixel value of image
    QString getHashCode(QImage img);
private:
    Ui::findpic *ui = NULL;
    QGraphicsScene *m_scene;
    HDC m_hdc;
    HANDLE m_hMouseThread = NULL;
    HANDLE m_hcaptureScreen_Thread = NULL;
    HANDLE m_hfindImg_Thread = NULL;
};

struct PosVal
{
    QRgb value;
    int x;
    int y;
};


#endif // FINDPIC_H
