/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QTextBrowser *statusTextBrowser;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *AgentLabel;
    QComboBox *agentComboBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *levelLabel;
    QComboBox *levelComboBox;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *startButton;
    QPushButton *stopButton;
    QLabel *statusLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(804, 527);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(280, 10, 500, 500));
        statusTextBrowser = new QTextBrowser(centralWidget);
        statusTextBrowser->setObjectName(QStringLiteral("statusTextBrowser"));
        statusTextBrowser->setGeometry(QRect(12, 180, 256, 331));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(12);
        statusTextBrowser->setFont(font);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(12, 14, 197, 162));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        AgentLabel = new QLabel(layoutWidget);
        AgentLabel->setObjectName(QStringLiteral("AgentLabel"));
        QFont font1;
        font1.setFamily(QStringLiteral("Agency FB"));
        font1.setPointSize(14);
        AgentLabel->setFont(font1);

        horizontalLayout->addWidget(AgentLabel);

        agentComboBox = new QComboBox(layoutWidget);
        agentComboBox->addItem(QString());
        agentComboBox->addItem(QString());
        agentComboBox->setObjectName(QStringLiteral("agentComboBox"));
        agentComboBox->setFont(font1);

        horizontalLayout->addWidget(agentComboBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        levelLabel = new QLabel(layoutWidget);
        levelLabel->setObjectName(QStringLiteral("levelLabel"));
        levelLabel->setFont(font1);

        horizontalLayout_2->addWidget(levelLabel);

        levelComboBox = new QComboBox(layoutWidget);
        levelComboBox->setObjectName(QStringLiteral("levelComboBox"));
        levelComboBox->setFont(font1);

        horizontalLayout_2->addWidget(levelComboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        startButton = new QPushButton(layoutWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setFont(font1);

        horizontalLayout_3->addWidget(startButton);

        stopButton = new QPushButton(layoutWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setFont(font1);

        horizontalLayout_3->addWidget(stopButton);


        verticalLayout->addLayout(horizontalLayout_3);

        statusLabel = new QLabel(layoutWidget);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setFont(font1);

        verticalLayout->addWidget(statusLabel);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        AgentLabel->setText(QApplication::translate("MainWindow", "Agent:", nullptr));
        agentComboBox->setItemText(0, QApplication::translate("MainWindow", "Human", nullptr));
        agentComboBox->setItemText(1, QApplication::translate("MainWindow", "AI", nullptr));

        levelLabel->setText(QApplication::translate("MainWindow", "Level:", nullptr));
        startButton->setText(QApplication::translate("MainWindow", "Start", nullptr));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        statusLabel->setText(QApplication::translate("MainWindow", "Status:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
