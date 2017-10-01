/********************************************************************************
** Form generated from reading UI file 'questdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUESTDIALOG_H
#define UI_QUESTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuestDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *cur_mouseX;
    QSpacerItem *horizontalSpacer_6;
    QLabel *cur_mouseY;
    QSpacerItem *horizontalSpacer_7;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QLineEdit *showPosX;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QLineEdit *showPosY;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *QuestDialog)
    {
        if (QuestDialog->objectName().isEmpty())
            QuestDialog->setObjectName(QStringLiteral("QuestDialog"));
        QuestDialog->resize(253, 156);
        layoutWidget = new QWidget(QuestDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 251, 156));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        cur_mouseX = new QLabel(layoutWidget);
        cur_mouseX->setObjectName(QStringLiteral("cur_mouseX"));

        horizontalLayout_3->addWidget(cur_mouseX);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        cur_mouseY = new QLabel(layoutWidget);
        cur_mouseY->setObjectName(QStringLiteral("cur_mouseY"));

        horizontalLayout_3->addWidget(cur_mouseY);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        showPosX = new QLineEdit(layoutWidget);
        showPosX->setObjectName(QStringLiteral("showPosX"));
        showPosX->setReadOnly(true);

        horizontalLayout->addWidget(showPosX);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        showPosY = new QLineEdit(layoutWidget);
        showPosY->setObjectName(QStringLiteral("showPosY"));
        showPosY->setReadOnly(true);

        horizontalLayout_2->addWidget(showPosY);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Ignored);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QuestDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), QuestDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), QuestDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(QuestDialog);
    } // setupUi

    void retranslateUi(QDialog *QuestDialog)
    {
        QuestDialog->setWindowTitle(QApplication::translate("QuestDialog", "\345\272\247\346\250\231\346\237\245\350\251\242", Q_NULLPTR));
        label_3->setText(QApplication::translate("QuestDialog", "\343\200\200\343\200\200\343\200\200\345\260\215\347\233\256\346\250\231\350\231\225\351\273\236\346\223\212\345\217\263\351\215\265\357\274\214\347\242\272\350\252\215\347\233\256\346\250\231\345\276\214\345\206\215\351\273\236\346\223\212\347\242\272\345\256\232", Q_NULLPTR));
        cur_mouseX->setText(QApplication::translate("QuestDialog", "X:", Q_NULLPTR));
        cur_mouseY->setText(QApplication::translate("QuestDialog", "Y:", Q_NULLPTR));
        label->setText(QApplication::translate("QuestDialog", "X\345\272\247\346\250\231", Q_NULLPTR));
        label_2->setText(QApplication::translate("QuestDialog", "Y\345\272\247\346\250\231", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QuestDialog: public Ui_QuestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUESTDIALOG_H
