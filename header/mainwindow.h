#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QInputDialog>
#include <QMainWindow>
#include <QShortcut>
#include "header/autobot.h"
#include "header/tree/treemodel.h"
#include "header/login.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void replyFinished(QNetworkReply *reply);
    //bool eventFilter(QObject *obj, QEvent *event);
    void closeEvent( QCloseEvent *event);
    void insertTxtToTxtEdit( QString str );
    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_toolView_clicked(const QModelIndex &index);

    void on_startButton_clicked();

    void on_startButton_Pressed();

    void on_deleteButton_clicked();

    void on_pushButton_clicked();

    void on_vKeyView_customContextMenuRequested(const QPoint &pos);

    void on_action_Press_triggered();

    void on_action_Release_triggered();

    void on_action_Click_triggered();
    void endBot();
    void on_label_linkActivated(const QString &link);

    void on_addButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_toolView_customContextMenuRequested(const QPoint &pos);

    void on_action_keyboard_Click_triggered();

    void on_action_keyboard_Press_triggered();

    void on_action_keyboard_Release_triggered();

    void on_action_MouseMoveX_triggered();

    void on_action_MouseMoveY_triggered();

    void on_action_MouseStop_triggered();

    void on_action_LClickPos_triggered();

    void on_textEdit_textChanged();

    void on_newButton_clicked();

    void on_lockButton_clicked();

    void on_label_2_linkActivated(const QString &link);

    void on_action_LClick_triggered();

    void on_action_RClick_triggered();

    void on_action_RClickPos_triggered();

    void on_remember_User_triggered();

    void on_remember_UserAndPasswd_triggered();

    void on_setHotkey_Start_triggered();

    void on_setHotkey_End_triggered();

    void on_open_alertSound_triggered();

    void on_action_WheelUp_triggered();

    void on_action_WheelDown_triggered();

    void on_condition_NeedHotKey_triggered();

    void on_condition_ReleaseEnd_triggered();

    void on_testButton_clicked();

private:
    Ui::MainWindow *ui;
    AutoBot * m_autoBot;
    bool m_isCompressFile = false;
    QString m_currentFileName;
    TreeModel* m_treeModel;
    TreeModel* m_vKeyModel;
    QString m_Username = "45";
    login m_login;
    bool m_successLogout = false;
    bool m_openAlert = true;
    QString m_strStartKey = "F1";
    QString m_strEndKey = "F2";
    QShortcut * m_stStart = NULL;
    //QInputDialog* m_inputDlg;
    void deselectedAllText();
    bool saveSetting();
    void loadSetting();
};

#endif // MAINWINDOW_H
