#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QMap>
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    QNetworkAccessManager *manager = NULL;
    QString m_user = "";
    QString m_passwd = "";
    QString m_mac = "";
    QString m_deadline = "2016-12-31";
    explicit login(QWidget *parent = 0);
    ~login();
    void logout();
    QString getSetting(bool needUser, bool needPasswd);
    void setSetting(QStringList strList);
    int exec();
    static QString getMacAddress();
    QString decode(QString str);
    QString encode(QString str);
private slots:
    void reject();
    void on_loginButton_clicked();
    void replyFinished(QNetworkReply *reply);
    void on_leaveButton_clicked();

    void on_label_3_linkActivated(const QString &link);

private:



    Ui::login *ui;

    bool m_LoginStatus = false;
    QString m_key = "asdf43sdddgf";
    QMap<QString, QString>* m_ch2FaceMap = NULL;
    QMap<QString, QString>* m_face2ChMap = NULL;
    QString m_Version = "version. Beta1.1";
};

#endif // LOGIN_H


