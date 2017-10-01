/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *userEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *passwdEdit;
    QLabel *login_status;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QPushButton *loginButton;
    QPushButton *leaveButton;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->setWindowModality(Qt::ApplicationModal);
        login->resize(240, 120);
        login->setMinimumSize(QSize(240, 120));
        login->setMaximumSize(QSize(240, 120));
        layoutWidget = new QWidget(login);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(8, 11, 221, 104));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        userEdit = new QLineEdit(layoutWidget);
        userEdit->setObjectName(QStringLiteral("userEdit"));

        horizontalLayout_2->addWidget(userEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        passwdEdit = new QLineEdit(layoutWidget);
        passwdEdit->setObjectName(QStringLiteral("passwdEdit"));
        passwdEdit->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(passwdEdit);


        verticalLayout->addLayout(horizontalLayout);

        login_status = new QLabel(layoutWidget);
        login_status->setObjectName(QStringLiteral("login_status"));

        verticalLayout->addWidget(login_status);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        loginButton = new QPushButton(layoutWidget);
        loginButton->setObjectName(QStringLiteral("loginButton"));

        horizontalLayout_3->addWidget(loginButton);

        leaveButton = new QPushButton(layoutWidget);
        leaveButton->setObjectName(QStringLiteral("leaveButton"));

        horizontalLayout_3->addWidget(leaveButton);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QApplication::translate("login", "\347\231\273\345\205\245AutoBot", Q_NULLPTR));
        label->setText(QApplication::translate("login", "\345\270\263\350\231\237:", Q_NULLPTR));
        label_2->setText(QApplication::translate("login", "\345\257\206\347\242\274:", Q_NULLPTR));
        login_status->setText(QString());
        label_3->setText(QApplication::translate("login", "<html><head/><body><p><a href=\"https://www.facebook.com/%E8%85%B3%E6%9C%AC%E4%B8%8D%E6%B1%82%E4%BA%BA-231999327218315/\"><span style=\" font-weight:600; color:#6590ef;\">\347\262\211\347\265\262\345\260\210\351\240\201</span></a></p></body></html>", Q_NULLPTR));
        loginButton->setText(QApplication::translate("login", "\347\231\273\345\205\245", Q_NULLPTR));
        leaveButton->setText(QApplication::translate("login", "\351\200\200\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
