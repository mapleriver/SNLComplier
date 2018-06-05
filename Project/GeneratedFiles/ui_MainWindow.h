/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLexical_Analysis;
    QAction *actionNew_File;
    QAction *actionOpen_File;
    QAction *actionSave;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QTabWidget *editorTabWidget;
    QTabWidget *outputTabWidget;
    QWidget *ConsoleWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *Console;
    QWidget *CompileOutputWidget;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *CompileOutput;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuBuild;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setMaximumSize(QSize(1920, 1080));
        actionLexical_Analysis = new QAction(MainWindow);
        actionLexical_Analysis->setObjectName(QStringLiteral("actionLexical_Analysis"));
        actionNew_File = new QAction(MainWindow);
        actionNew_File->setObjectName(QStringLiteral("actionNew_File"));
        actionNew_File->setEnabled(true);
        actionOpen_File = new QAction(MainWindow);
        actionOpen_File->setObjectName(QStringLiteral("actionOpen_File"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(0, 0));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(2);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        editorTabWidget = new QTabWidget(frame);
        editorTabWidget->setObjectName(QStringLiteral("editorTabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(2);
        sizePolicy1.setHeightForWidth(editorTabWidget->sizePolicy().hasHeightForWidth());
        editorTabWidget->setSizePolicy(sizePolicy1);
        editorTabWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        editorTabWidget->setLayoutDirection(Qt::LeftToRight);
        editorTabWidget->setAutoFillBackground(false);
        editorTabWidget->setInputMethodHints(Qt::ImhNone);
        editorTabWidget->setTabPosition(QTabWidget::North);
        editorTabWidget->setElideMode(Qt::ElideNone);
        editorTabWidget->setUsesScrollButtons(false);
        editorTabWidget->setDocumentMode(false);
        editorTabWidget->setTabsClosable(true);
        editorTabWidget->setMovable(true);
        editorTabWidget->setTabBarAutoHide(false);

        horizontalLayout->addWidget(editorTabWidget);


        verticalLayout_3->addWidget(frame);

        outputTabWidget = new QTabWidget(centralWidget);
        outputTabWidget->setObjectName(QStringLiteral("outputTabWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(outputTabWidget->sizePolicy().hasHeightForWidth());
        outputTabWidget->setSizePolicy(sizePolicy2);
        outputTabWidget->setTabPosition(QTabWidget::South);
        outputTabWidget->setTabShape(QTabWidget::Rounded);
        outputTabWidget->setElideMode(Qt::ElideNone);
        outputTabWidget->setUsesScrollButtons(true);
        ConsoleWidget = new QWidget();
        ConsoleWidget->setObjectName(QStringLiteral("ConsoleWidget"));
        verticalLayout = new QVBoxLayout(ConsoleWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Console = new QTextBrowser(ConsoleWidget);
        Console->setObjectName(QStringLiteral("Console"));

        verticalLayout->addWidget(Console);

        outputTabWidget->addTab(ConsoleWidget, QString());
        CompileOutputWidget = new QWidget();
        CompileOutputWidget->setObjectName(QStringLiteral("CompileOutputWidget"));
        verticalLayout_2 = new QVBoxLayout(CompileOutputWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        CompileOutput = new QTextBrowser(CompileOutputWidget);
        CompileOutput->setObjectName(QStringLiteral("CompileOutput"));

        verticalLayout_2->addWidget(CompileOutput);

        outputTabWidget->addTab(CompileOutputWidget, QString());

        verticalLayout_3->addWidget(outputTabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuBuild = new QMenu(menuBar);
        menuBuild->setObjectName(QStringLiteral("menuBuild"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuBuild->menuAction());
        menuFile->addAction(actionNew_File);
        menuFile->addAction(actionOpen_File);
        menuFile->addAction(actionSave);
        menuBuild->addAction(actionLexical_Analysis);

        retranslateUi(MainWindow);

        editorTabWidget->setCurrentIndex(-1);
        outputTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionLexical_Analysis->setText(QApplication::translate("MainWindow", "Lexical Analysis", Q_NULLPTR));
        actionNew_File->setText(QApplication::translate("MainWindow", "New File", Q_NULLPTR));
        actionOpen_File->setText(QApplication::translate("MainWindow", "Open File", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        outputTabWidget->setTabText(outputTabWidget->indexOf(ConsoleWidget), QApplication::translate("MainWindow", "Console", Q_NULLPTR));
        outputTabWidget->setTabText(outputTabWidget->indexOf(CompileOutputWidget), QApplication::translate("MainWindow", "Compile Output", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuBuild->setTitle(QApplication::translate("MainWindow", "Build", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
