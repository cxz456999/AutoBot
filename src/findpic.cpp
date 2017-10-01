#include "header/findpic.h"
#include "ui_findpic.h"
#include <thread>
QScreen *g_screen = NULL;
bool g_Stop = false;
DWORD WINAPI mouseThread(LPVOID lp)
{

    Ui::findpic *ui = (Ui::findpic*)lp;
    POINT po = {50, 50};

    //qreal width = pix.width(); //获得以前图片的宽和高
    //qreal height = pix.height();

    //pix = pix.scaled(width*2,height*2,Qt::KeepAspectRatio);


    //pix.toImage()

    return 1;
}

DWORD WINAPI captureScreen_Thread(LPVOID lp)
{
    Ui::findpic *ui = (Ui::findpic*)lp;
    QPixmap pix;
    POINT po = {50, 50};
    while(!g_Stop)
    {
        GetCursorPos(&po);
        pix = g_screen->grabWindow(0).copy(QRect(po.x - 4, po.y - 4, 9, 8));
        ui->screen_label->setPixmap(pix.scaled(ui->screen_label->size()/*,
                                    Qt::KeepAspectRatio,Qt::SmoothTransformation*/));
        if ( GetAsyncKeyState(VK_SHIFT) < 0 )
            pix.toImage().save("./test.png", "PNG");
    }

    g_screen = NULL;
    return 1;
}

DWORD WINAPI findImg_Thread(LPVOID lp)
{
    //Ui::findpic *ui = (Ui::findpic*)lp;
    findpic* thisClass = (findpic*)lp;
    QPixmap pix("./test.png");
    QVector<PosVal> srcVec;

   // ui->screen_label->setPixmap(pix.scaled(ui->screen_label->size(),Qt::KeepAspectRatio));
    pix = g_screen->grabWindow(0);
    QImage befImg("./test.png");
    int srcWidth = befImg.width();
    int srcHeight = befImg.height();
    befImg = befImg.scaled(srcWidth/3, srcHeight/3, Qt::KeepAspectRatio);
    //QMessageBox::information(NULL, "desHashCode", QString::number(befImg.pixelColor(0,0).value()));
    for ( int i = 0; i < befImg.width(); i++ )
    {

        for ( int j = 0; j < befImg.height(); j++ )

            if ( befImg.pixelColor(i,j).value() != 0 )
            {
                PosVal pv;
                pv.value = befImg.pixel(i,j);
                pv.x = i, pv.y = j;
                srcVec.append(pv);
            }

    }

    int maxNOfErr = 0.5*srcVec.length();
    //thisClass->convert2Gray(befImg);
    QString srcHashCode = thisClass->getHashCode(befImg);
    //QImage img = pix.toImage();
    QImage img = pix.toImage();
    img = img.scaled(img.width()/3, img.height()/3, Qt::KeepAspectRatio);
    //img.save("./SCREEN.png", "PNG");
    //befImg.save("./div3Test.png", "PNG");
    for ( int i = 0; i < img.width()-srcWidth; i++ )
    {
        for ( int j = 0; j < img.height()-srcHeight; j++ )
        {
            //ui->screen_label->setPixmap(pix.copy(QRect(i, j, 9, 9)).scaled(ui->screen_label->size()));
            QImage partImg = img.copy(QRect(i, j, srcWidth/3, srcHeight/3));//.scaled(srcWidth/3, srcHeight/3, Qt::KeepAspectRatio);;

            //thisClass->convert2Gray(partImg );
            // test
           /* if ( partImg == befImg )dd
                SetCursorPos(i, j);
            //*/

            QString desHashCode = thisClass->getHashCode(partImg);
            //QString differ= QString::number((srcHashCode.toInt() ^ desHashCode.toInt()), 2);
            int numOfDif = 0, indexofDesStr = 0;
            foreach ( QChar c, srcHashCode )
                if ( c != desHashCode[indexofDesStr++] )
                    numOfDif++;

            //QMessageBox::information(NULL, desHashCode,differ);
            if ( numOfDif <= 5 )
                SetCursorPos(i, j);//QMessageBox::information(NULL, "",differ);
            /*int nOfErr = 0;
            foreach ( PosVal pv, srcVec )
                if ( pv.value != img.pixel(i+pv.x, j+pv.y) )
                    nOfErr++;
                else if ( nOfErr >= maxNOfErr )
                    break;
            if ( nOfErr < maxNOfErr ){
                SetCursorPos(i, j);
                g_screen = NULL;
                return 1;
            }*/
        }
    }

    QMessageBox::information(NULL, "","Not Found");
    g_screen = NULL;
    return 1;
}


DWORD WINAPI findImg_Thread_CCCCCCCCCCOO(LPVOID lp)
{
    //Ui::findpic *ui = (Ui::findpic*)lp;
    findpic* thisClass = (findpic*)lp;
    QPixmap pix("./test.png");
   // ui->screen_label->setPixmap(pix.scaled(ui->screen_label->size(),Qt::KeepAspectRatio));
    pix = g_screen->grabWindow(0);
    QImage befImg("./test.png");
    thisClass->convert2Gray(befImg);
    QString srcHashCode = thisClass->getHashCode(befImg);
    SetCursorPos(0, 0);
    QImage img = pix.toImage();
    for ( int i = 0; i < pix.width()-9; i++ )
    {
        for ( int j = 0; j < pix.height()-8; j++ )
        {
            //ui->screen_label->setPixmap(pix.copy(QRect(i, j, 9, 9)).scaled(ui->screen_label->size()));
            QImage partImg = img.copy(QRect(i, j, 9, 8));
            thisClass->convert2Gray(partImg );
            // test
           /* if ( partImg == befImg )
                SetCursorPos(i, j);
            //*/

            QString desHashCode = thisClass->getHashCode(partImg);
            QString differ= QString::number((srcHashCode.toInt() ^ desHashCode.toInt()), 2);
            QMessageBox::information(NULL, desHashCode,differ);
            if ( differ.count("1") < 3/*srcHashCode.compare(desHashCode) == 0*/ )
                //QMessageBox::information(NULL, "",differ);
                SetCursorPos(i, j);
        }
    }

    g_screen = NULL;
    return 1;
}

bool findpic::captureScreen()
{

    m_hcaptureScreen_Thread = CreateThread(NULL, 0, captureScreen_Thread,ui,0,NULL);
    //delete ui;
    return true;
}

bool findpic::findImg(int similar)
{
    m_hfindImg_Thread = CreateThread(NULL, 0, findImg_Thread,ui,0,NULL);
    return true;
}

int findpic::convert2Gray(QImage & img)
{
    int width = img.width(), height = img.height();
    int value = 0;
    for ( int i = 0; i < width; i++)
    {
        for ( int j = 0; j < height; j++)
        {
            QRgb pixel = img.pixel(i, j);
            int gray = qGray(pixel);
            QRgb grayPixel = qRgb(gray, gray, gray);
            img.setPixel(i,j,grayPixel);

        }
    }
}

QString findpic::getHashCode(QImage img)
{
    uchar* bits = img.bits();
    int width = img.width(), height = img.height();
    //QString ss = "";
    QByteArray barry;
    uchar ch = '\0';
    //int nBit = 0;
    for ( int i = 0; i < height; i++)
    {
        int row_start_index = i * width;
        ch = '\0';
        //nBit = 0;
        for ( int j = 0; j <  width-1; j++)
        {
            //int index = row_start_index + j;
            //ch = (ch << 1) | bits[index] < bits[index+1];
            ch = (ch << 1) | img.pixel(i, j) < img.pixel(i+1, j);
            //nBit = (nBit << 1) | (int )(bits[index] < bits[index+1]);
            /*QMessageBox::information(this, "",
                        QString::number(bits[index] < bits[index+1]));*/

        }

        /*QMessageBox::information(this, "",
            QString::number((int)ch, 2));*/
         barry.append( ch );
       //ss += QString::number(nBit, 16);

    }

    //QMessageBox::information(this, tr(""),
    //    QString(barry.toHex()));

    return barry.toHex();
}

findpic::findpic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findpic)
{

    ui->setupUi(this);
    /*m_scene = new QGraphicsScene(this);
    m_hdc = GetDC((HWND)ui->screenView->winId());
    */
    //NULL, 0, mouseThread, NULL ,0, NULL);
    g_screen = QGuiApplication::primaryScreen();
    if (const QWindow *window = windowHandle())
            g_screen = window->screen();
    if (!g_screen)
    {
            QMessageBox::information(this, tr("擷取螢幕失敗"),
                tr("擷取螢幕失敗"));
            return ;
    }

    g_Stop = false;
    /*QPixmap pix("./test.png");
    QImage ii = pix.toImage();
    //getHashCode(ii);
    //convert2Gray(ii);
    //ui->screen_label->setPixmap(QPixmap::fromImage(ii).scaled(ui->screen_label->size(),Qt::KeepAspectRatio));
   ui->screen_label->setMask(pix.mask());
    ui->screen_label->setPixmap(pix.scaled(ui->screen_label->size(),Qt::KeepAspectRatio));

    getHashCode(ii);
    g_screen = NULL;
    return;

    //m_hMouseThread = CreateThread(NULL, 0, mouseThread, ui, 0, NULL);
    captureScreen();*/
    findImg(0);
}

findpic::~findpic()
{
    g_Stop = true;
    CloseHandle(m_hMouseThread);
    CloseHandle(m_hcaptureScreen_Thread);
    CloseHandle(m_hfindImg_Thread);
    while( g_screen != NULL )
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    delete ui;
}
