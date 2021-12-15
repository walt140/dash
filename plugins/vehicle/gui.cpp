void MainWindow::on_rabbitButton_toggled(bool checked)
{
    if(checked) {

            emit ui->turtleButton->setChecked(false);   //unchecks turtle button when rabbit is clicked
            ui->rabbitButton->setIcon(QIcon(":/images/rabbitOn.png"));


        }

        else {

            ui->rabbitButton->setIcon(QIcon(":/images/rabbitOff.png"));
            ui->rabbitButton->setEnabled(true);
        }

}

void MainWindow::on_turtleButton_toggled(bool checked)
{
    if(checked) {


            emit ui->rabbitButton->setChecked(false);
            ui->turtleButton->setIcon(QIcon(":/images/turtleOn.png"));
        }

        else {

            ui->turtleButton->setIcon(QIcon(":/images/turtleOff.png"));

        }
}



/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef BUTTONSDEMO_H
#define BUTTONSDEMO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *hazardButton;
    QPushButton *lightsButton;
    QPushButton *wipersButton;
    QPushButton *heaterButton;
    QPushButton *arrowUpButton;
    QPushButton *arrowDownButton;
    QLabel *hoistLabel;
    QPushButton *frontDefrostButton;
    QPushButton *rearDefrostButton;
    QLabel *label_2;
    QPushButton *rabbitButton;
    QPushButton *turtleButton;
    QPushButton *pushButton;
    QLabel *batLabel;
    QLabel *logoLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        hazardButton = new QPushButton(centralwidget);
        hazardButton->setObjectName(QString::fromUtf8("hazardButton"));
        hazardButton->setGeometry(QRect(60, 40, 161, 161));
        QIcon icon;
        icon.addFile(QString::fromUtf8("hazardsOff.png"), QSize(), QIcon::Normal, QIcon::Off);
        hazardButton->setIcon(icon);
        hazardButton->setIconSize(QSize(90, 90));
        hazardButton->setCheckable(true);
        lightsButton = new QPushButton(centralwidget);
        lightsButton->setObjectName(QString::fromUtf8("lightsButton"));
        lightsButton->setGeometry(QRect(300, 40, 161, 161));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("images/lightsOff.png"), QSize(), QIcon::Normal, QIcon::Off);
        lightsButton->setIcon(icon1);
        lightsButton->setIconSize(QSize(90, 90));
        lightsButton->setCheckable(true);
        wipersButton = new QPushButton(centralwidget);
        wipersButton->setObjectName(QString::fromUtf8("wipersButton"));
        wipersButton->setGeometry(QRect(1000, 40, 161, 161));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("images/wipersOff.png"), QSize(), QIcon::Normal, QIcon::Off);
        wipersButton->setIcon(icon2);
        wipersButton->setIconSize(QSize(90, 90));
        wipersButton->setCheckable(true);
        heaterButton = new QPushButton(centralwidget);
        heaterButton->setObjectName(QString::fromUtf8("heaterButton"));
        heaterButton->setGeometry(QRect(760, 430, 161, 161));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("images/fireOff.png"), QSize(), QIcon::Normal, QIcon::Off);
        heaterButton->setIcon(icon3);
        heaterButton->setIconSize(QSize(90, 90));
        heaterButton->setCheckable(true);
        arrowUpButton = new QPushButton(centralwidget);
        arrowUpButton->setObjectName(QString::fromUtf8("arrowUpButton"));
        arrowUpButton->setGeometry(QRect(300, 240, 161, 161));
        arrowUpButton->setMinimumSize(QSize(161, 161));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("images/arrowUp.png"), QSize(), QIcon::Normal, QIcon::Off);
        arrowUpButton->setIcon(icon4);
        arrowUpButton->setIconSize(QSize(50, 50));
        arrowDownButton = new QPushButton(centralwidget);
        arrowDownButton->setObjectName(QString::fromUtf8("arrowDownButton"));
        arrowDownButton->setGeometry(QRect(300, 430, 161, 161));
        arrowDownButton->setMinimumSize(QSize(161, 161));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("images/arrowDown.png"), QSize(), QIcon::Normal, QIcon::Off);
        arrowDownButton->setIcon(icon5);
        arrowDownButton->setIconSize(QSize(50, 50));
        hoistLabel = new QLabel(centralwidget);
        hoistLabel->setObjectName(QString::fromUtf8("hoistLabel"));
        hoistLabel->setGeometry(QRect(80, 350, 171, 111));
        hoistLabel->setPixmap(QPixmap(QString::fromUtf8("images/hoist.png")));
        frontDefrostButton = new QPushButton(centralwidget);
        frontDefrostButton->setObjectName(QString::fromUtf8("frontDefrostButton"));
        frontDefrostButton->setGeometry(QRect(530, 430, 161, 161));
        frontDefrostButton->setMinimumSize(QSize(161, 161));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("images/frontDefrostOff.png"), QSize(), QIcon::Normal, QIcon::Off);
        frontDefrostButton->setIcon(icon6);
        frontDefrostButton->setIconSize(QSize(50, 50));
        frontDefrostButton->setCheckable(true);
        rearDefrostButton = new QPushButton(centralwidget);
        rearDefrostButton->setObjectName(QString::fromUtf8("rearDefrostButton"));
        rearDefrostButton->setGeometry(QRect(530, 240, 161, 161));
        rearDefrostButton->setMinimumSize(QSize(161, 161));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("images/rearDefrostOff.png"), QSize(), QIcon::Normal, QIcon::Off);
        rearDefrostButton->setIcon(icon7);
        rearDefrostButton->setIconSize(QSize(50, 50));
        rearDefrostButton->setCheckable(true);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 260, 81, 31));
        label_2->setAlignment(Qt::AlignCenter);
        rabbitButton = new QPushButton(centralwidget);
        rabbitButton->setObjectName(QString::fromUtf8("rabbitButton"));
        rabbitButton->setGeometry(QRect(760, 40, 161, 161));
        rabbitButton->setMinimumSize(QSize(161, 161));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("images/rabbitOff.png"), QSize(), QIcon::Normal, QIcon::Off);
        rabbitButton->setIcon(icon8);
        rabbitButton->setIconSize(QSize(50, 50));
        rabbitButton->setCheckable(true);
        turtleButton = new QPushButton(centralwidget);
        turtleButton->setObjectName(QString::fromUtf8("turtleButton"));
        turtleButton->setGeometry(QRect(760, 240, 161, 161));
        turtleButton->setMinimumSize(QSize(161, 161));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("images/turtleOff.png"), QSize(), QIcon::Normal, QIcon::Off);
        turtleButton->setIcon(icon9);
        turtleButton->setIconSize(QSize(50, 50));
        turtleButton->setCheckable(true);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(530, 40, 161, 161));
        batLabel = new QLabel(centralwidget);
        batLabel->setObjectName(QString::fromUtf8("batLabel"));
        batLabel->setGeometry(QRect(1020, 320, 201, 191));
        batLabel->setPixmap(QPixmap(QString::fromUtf8("images/battery-status-disconnected-100.png")));
        batLabel->setScaledContents(true);
        logoLabel = new QLabel(centralwidget);
        logoLabel->setObjectName(QString::fromUtf8("logoLabel"));
        logoLabel->setGeometry(QRect(20, 600, 1141, 181));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8("images/logotransparent.png")));
        logoLabel->setScaledContents(true);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        hazardButton->setText(QString());
        lightsButton->setText(QString());
        wipersButton->setText(QString());
        heaterButton->setText(QString());
        arrowUpButton->setText(QString());
        arrowDownButton->setText(QString());
        hoistLabel->setText(QString());
        frontDefrostButton->setText(QString());
        rearDefrostButton->setText(QString());
        label_2->setText(QString());
        rabbitButton->setText(QString());
        turtleButton->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        batLabel->setText(QString());
        logoLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // BUTTONSDEMO_H
