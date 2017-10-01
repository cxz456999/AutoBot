/********************************************************************************
** Form generated from reading UI file 'findpic.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDPIC_H
#define UI_FINDPIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_findpic
{
public:
    QDialogButtonBox *buttonBox;
    QGraphicsView *screenView;
    QLabel *screen_label;

    void setupUi(QDialog *findpic)
    {
        if (findpic->objectName().isEmpty())
            findpic->setObjectName(QStringLiteral("findpic"));
        findpic->resize(400, 300);
        buttonBox = new QDialogButtonBox(findpic);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(50, 270, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        screenView = new QGraphicsView(findpic);
        screenView->setObjectName(QStringLiteral("screenView"));
        screenView->setGeometry(QRect(30, 10, 331, 21));
        screen_label = new QLabel(findpic);
        screen_label->setObjectName(QStringLiteral("screen_label"));
        screen_label->setGeometry(QRect(0, 40, 391, 231));

        retranslateUi(findpic);
        QObject::connect(buttonBox, SIGNAL(accepted()), findpic, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), findpic, SLOT(reject()));

        QMetaObject::connectSlotsByName(findpic);
    } // setupUi

    void retranslateUi(QDialog *findpic)
    {
        findpic->setWindowTitle(QApplication::translate("findpic", "Dialog", Q_NULLPTR));
        screen_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class findpic: public Ui_findpic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDPIC_H
