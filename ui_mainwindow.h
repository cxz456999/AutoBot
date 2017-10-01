/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Press;
    QAction *action_Release;
    QAction *action_Click;
    QAction *action_keyboard_Click;
    QAction *action_keyboard_Press;
    QAction *action_keyboard_Release;
    QAction *action_MouseMoveX;
    QAction *action_MouseMoveY;
    QAction *action_MouseStop;
    QAction *action_LClickPos;
    QAction *action_LClick;
    QAction *action_RClick;
    QAction *action_RClickPos;
    QAction *remember_User;
    QAction *remember_UserAndPasswd;
    QAction *setHotkey_Start;
    QAction *setHotkey_End;
    QAction *open_alertSound;
    QAction *action_WheelDown;
    QAction *action_WheelUp;
    QAction *condition_NeedHotKey;
    QAction *condition_ReleaseEnd;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *newButton;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *startButton;
    QPushButton *pushButton;
    QPushButton *lockButton;
    QLabel *label;
    QLabel *label_2;
    QPushButton *testButton;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *textEdit;
    QVBoxLayout *verticalLayout_2;
    QListView *toolView;
    QListView *vKeyView;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(778, 609);
        action_Press = new QAction(MainWindow);
        action_Press->setObjectName(QStringLiteral("action_Press"));
        action_Release = new QAction(MainWindow);
        action_Release->setObjectName(QStringLiteral("action_Release"));
        action_Click = new QAction(MainWindow);
        action_Click->setObjectName(QStringLiteral("action_Click"));
        action_keyboard_Click = new QAction(MainWindow);
        action_keyboard_Click->setObjectName(QStringLiteral("action_keyboard_Click"));
        action_keyboard_Press = new QAction(MainWindow);
        action_keyboard_Press->setObjectName(QStringLiteral("action_keyboard_Press"));
        action_keyboard_Release = new QAction(MainWindow);
        action_keyboard_Release->setObjectName(QStringLiteral("action_keyboard_Release"));
        action_MouseMoveX = new QAction(MainWindow);
        action_MouseMoveX->setObjectName(QStringLiteral("action_MouseMoveX"));
        action_MouseMoveY = new QAction(MainWindow);
        action_MouseMoveY->setObjectName(QStringLiteral("action_MouseMoveY"));
        action_MouseStop = new QAction(MainWindow);
        action_MouseStop->setObjectName(QStringLiteral("action_MouseStop"));
        action_LClickPos = new QAction(MainWindow);
        action_LClickPos->setObjectName(QStringLiteral("action_LClickPos"));
        action_LClick = new QAction(MainWindow);
        action_LClick->setObjectName(QStringLiteral("action_LClick"));
        action_RClick = new QAction(MainWindow);
        action_RClick->setObjectName(QStringLiteral("action_RClick"));
        action_RClickPos = new QAction(MainWindow);
        action_RClickPos->setObjectName(QStringLiteral("action_RClickPos"));
        remember_User = new QAction(MainWindow);
        remember_User->setObjectName(QStringLiteral("remember_User"));
        remember_User->setCheckable(true);
        remember_UserAndPasswd = new QAction(MainWindow);
        remember_UserAndPasswd->setObjectName(QStringLiteral("remember_UserAndPasswd"));
        remember_UserAndPasswd->setCheckable(true);
        setHotkey_Start = new QAction(MainWindow);
        setHotkey_Start->setObjectName(QStringLiteral("setHotkey_Start"));
        setHotkey_End = new QAction(MainWindow);
        setHotkey_End->setObjectName(QStringLiteral("setHotkey_End"));
        open_alertSound = new QAction(MainWindow);
        open_alertSound->setObjectName(QStringLiteral("open_alertSound"));
        open_alertSound->setCheckable(true);
        open_alertSound->setChecked(true);
        action_WheelDown = new QAction(MainWindow);
        action_WheelDown->setObjectName(QStringLiteral("action_WheelDown"));
        action_WheelUp = new QAction(MainWindow);
        action_WheelUp->setObjectName(QStringLiteral("action_WheelUp"));
        condition_NeedHotKey = new QAction(MainWindow);
        condition_NeedHotKey->setObjectName(QStringLiteral("condition_NeedHotKey"));
        condition_ReleaseEnd = new QAction(MainWindow);
        condition_ReleaseEnd->setObjectName(QStringLiteral("condition_ReleaseEnd"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        newButton = new QPushButton(centralWidget);
        newButton->setObjectName(QStringLiteral("newButton"));
        newButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/icon/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        newButton->setIcon(icon);
        newButton->setFlat(true);

        horizontalLayout->addWidget(newButton);

        loadButton = new QPushButton(centralWidget);
        loadButton->setObjectName(QStringLiteral("loadButton"));
        loadButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/icon/load.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadButton->setIcon(icon1);
        loadButton->setAutoDefault(true);
        loadButton->setFlat(true);

        horizontalLayout->addWidget(loadButton);

        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/icon/save.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        saveButton->setIcon(icon2);
        saveButton->setFlat(true);

        horizontalLayout->addWidget(saveButton);

        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icon/icon/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon3);
        startButton->setFlat(true);

        horizontalLayout->addWidget(startButton);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setEnabled(true);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icon/icon/create.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon4);
        pushButton->setFlat(true);

        horizontalLayout->addWidget(pushButton);

        lockButton = new QPushButton(centralWidget);
        lockButton->setObjectName(QStringLiteral("lockButton"));
        lockButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icon/icon/lock.png"), QSize(), QIcon::Normal, QIcon::Off);
        lockButton->setIcon(icon5);
        lockButton->setIconSize(QSize(20, 20));
        lockButton->setFlat(true);

        horizontalLayout->addWidget(lockButton);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setCursor(QCursor(Qt::ArrowCursor));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        testButton = new QPushButton(centralWidget);
        testButton->setObjectName(QStringLiteral("testButton"));

        horizontalLayout->addWidget(testButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setMinimumSize(QSize(500, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\260\347\264\260\346\230\216\351\253\224-ExtB"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        textEdit->setFont(font);
        textEdit->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textEdit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);

        horizontalLayout_2->addWidget(textEdit);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        toolView = new QListView(centralWidget);
        toolView->setObjectName(QStringLiteral("toolView"));
        toolView->setMinimumSize(QSize(0, 260));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial Black"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        toolView->setFont(font1);
        toolView->setContextMenuPolicy(Qt::CustomContextMenu);
        toolView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        toolView->setDefaultDropAction(Qt::IgnoreAction);

        verticalLayout_2->addWidget(toolView);

        vKeyView = new QListView(centralWidget);
        vKeyView->setObjectName(QStringLiteral("vKeyView"));
        vKeyView->setContextMenuPolicy(Qt::CustomContextMenu);
        vKeyView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_2->addWidget(vKeyView);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_4->addWidget(lineEdit);

        addButton = new QPushButton(centralWidget);
        addButton->setObjectName(QStringLiteral("addButton"));
        addButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icon/icon/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addButton->setIcon(icon6);
        addButton->setFlat(true);

        horizontalLayout_4->addWidget(addButton);

        deleteButton = new QPushButton(centralWidget);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        deleteButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icon/icon/remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteButton->setIcon(icon7);
        deleteButton->setFlat(true);

        horizontalLayout_4->addWidget(deleteButton);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 778, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menu);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menu);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(menu_2->menuAction());
        menu->addAction(menu_3->menuAction());
        menu->addAction(open_alertSound);
        menu_2->addAction(remember_User);
        menu_2->addAction(remember_UserAndPasswd);
        menu_3->addAction(setHotkey_Start);
        menu_3->addAction(setHotkey_End);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "AutoBot - Beta 1.2 [\346\220\266\345\205\210\347\211\210]", Q_NULLPTR));
        action_Press->setText(QApplication::translate("MainWindow", "\346\214\211\344\270\213", Q_NULLPTR));
        action_Release->setText(QApplication::translate("MainWindow", "\346\224\276\351\226\213", Q_NULLPTR));
        action_Click->setText(QApplication::translate("MainWindow", "\351\273\236\346\223\212", Q_NULLPTR));
        action_keyboard_Click->setText(QApplication::translate("MainWindow", "\351\273\236\346\223\212", Q_NULLPTR));
        action_keyboard_Press->setText(QApplication::translate("MainWindow", "\346\214\211\344\270\213", Q_NULLPTR));
        action_keyboard_Release->setText(QApplication::translate("MainWindow", "\346\224\276\351\226\213", Q_NULLPTR));
        action_MouseMoveX->setText(QApplication::translate("MainWindow", "\347\247\273\345\213\225X\350\273\270", Q_NULLPTR));
        action_MouseMoveY->setText(QApplication::translate("MainWindow", "\347\247\273\345\213\225Y\350\273\270", Q_NULLPTR));
        action_MouseStop->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\346\273\221\351\274\240", Q_NULLPTR));
        action_LClickPos->setText(QApplication::translate("MainWindow", "\345\267\246\351\215\265\345\272\247\346\250\231\351\273\236\346\223\212", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_LClickPos->setToolTip(QApplication::translate("MainWindow", "\345\267\246\351\215\265\345\272\247\346\250\231\351\273\236\346\223\212", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_LClick->setText(QApplication::translate("MainWindow", "\345\267\246\351\215\265\351\273\236\346\223\212", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_LClick->setToolTip(QApplication::translate("MainWindow", "\345\267\246\351\215\265\351\273\236\346\223\212", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_RClick->setText(QApplication::translate("MainWindow", "\345\217\263\351\215\265\351\273\236\346\223\212", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_RClick->setToolTip(QApplication::translate("MainWindow", "\345\217\263\351\215\265\351\273\236\346\223\212", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_RClickPos->setText(QApplication::translate("MainWindow", "\345\217\263\351\215\265\345\272\247\346\250\231\351\273\236\346\223\212", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_RClickPos->setToolTip(QApplication::translate("MainWindow", "\345\217\263\351\215\265\345\272\247\346\250\231\351\273\236\346\223\212", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        remember_User->setText(QApplication::translate("MainWindow", "\345\270\263\350\231\237", Q_NULLPTR));
        remember_UserAndPasswd->setText(QApplication::translate("MainWindow", "\345\270\263\350\231\237\345\257\206\347\242\274", Q_NULLPTR));
        setHotkey_Start->setText(QApplication::translate("MainWindow", "\351\226\213\345\247\213\347\206\261\351\215\265", Q_NULLPTR));
        setHotkey_End->setText(QApplication::translate("MainWindow", "\347\265\220\346\235\237\347\206\261\351\215\265", Q_NULLPTR));
        open_alertSound->setText(QApplication::translate("MainWindow", "\351\226\213\345\225\237\346\217\220\347\244\272\351\237\263", Q_NULLPTR));
        action_WheelDown->setText(QApplication::translate("MainWindow", "\346\273\221\351\274\240\346\273\276\350\274\252\345\220\221\344\270\213", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_WheelDown->setToolTip(QApplication::translate("MainWindow", "\346\273\221\351\274\240\346\273\276\350\274\252\345\220\221\344\270\213", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_WheelUp->setText(QApplication::translate("MainWindow", "\346\273\221\351\274\240\346\273\276\350\274\252\345\220\221\344\270\212", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_WheelUp->setToolTip(QApplication::translate("MainWindow", "\346\273\221\351\274\240\346\273\276\350\274\252\345\220\221\344\270\212", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        condition_NeedHotKey->setText(QApplication::translate("MainWindow", "\351\234\200\347\206\261\351\215\265\347\265\220\346\235\237", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        condition_NeedHotKey->setToolTip(QApplication::translate("MainWindow", "\351\234\200\347\206\261\351\215\265\347\265\220\346\235\237", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        condition_ReleaseEnd->setText(QApplication::translate("MainWindow", "\346\214\211\344\275\217\345\237\267\350\241\214", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        condition_ReleaseEnd->setToolTip(QApplication::translate("MainWindow", "\346\214\211\344\275\217\345\237\267\350\241\214", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        newButton->setToolTip(QApplication::translate("MainWindow", "\351\226\213\345\225\237\346\226\260\346\252\224", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        newButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        loadButton->setToolTip(QApplication::translate("MainWindow", "\351\226\213\345\225\237\350\210\212\346\252\224", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        loadButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        saveButton->setToolTip(QApplication::translate("MainWindow", "\345\204\262\345\255\230\346\252\224\346\241\210", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        saveButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        startButton->setToolTip(QApplication::translate("MainWindow", "\347\267\250\350\255\257\350\205\263\346\234\254", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        startButton->setText(QApplication::translate("MainWindow", "\351\225\267\346\214\211F1\351\226\213\345\247\213/F2\347\265\220\346\235\237", Q_NULLPTR));
        pushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        lockButton->setToolTip(QApplication::translate("MainWindow", "\345\212\240\345\257\206\350\205\263\346\234\254", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lockButton->setText(QString());
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><a href=\"https://msdn.microsoft.com/zh-tw/library/windows/desktop/dd375731\"><span style=\" font-weight:600; color:#0000ff;\">\347\211\271\346\256\212\351\215\265\346\237\245\350\251\242</span></a></p></body></html>", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p><a href=\"https://www.facebook.com/%E8%85%B3%E6%9C%AC%E4%B8%8D%E6%B1%82%E4%BA%BA-231999327218315/\"><span style=\" font-weight:600; color:#6590ef;\">\347\262\211\347\265\262\345\260\210\351\240\201</span></a></p></body></html>", Q_NULLPTR));
        testButton->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\346\220\234\345\260\213", Q_NULLPTR));
        addButton->setText(QString());
        deleteButton->setText(QString());
        menu->setTitle(QApplication::translate("MainWindow", "\350\250\255\345\256\232", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("MainWindow", "\350\250\230\344\275\217", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("MainWindow", "\347\206\261\351\215\265", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
