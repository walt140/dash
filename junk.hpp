#pragma once

#include <QObject>
#include <QTimer>
#include "plugins/vehicle_plugin.hpp"
#include "app/widgets/climate.hpp"
#include "canbus/socketcanbus.hpp"


class Counter : public QWidget
{
    Q_OBJECT
public:
    //explicit Counter(QObject *parent = nullptr);
	Counter(Arbiter &arbiter, QWidget *parent = nullptr);

    int value() const {return m_value;}

    
signals:
    void startCounter(int &counter);
    void sendDevice(QCanBusDevice &device);


public slots:
    

    void onTimer();
    void onCounter(int &counter, QCanBusDevice &device);
    void onFrame();

private:
    int m_value;
    QTimer* onStartup;


};


class Symposium : public QObject, VehiclePlugin 
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VehiclePlugin_iid)
    Q_INTERFACES(VehiclePlugin)

   public:
   
    ~Symposium();
    QList<QWidget *> widgets() override;
    bool init(ICANBus*) override;

   private:
    Climate *climate;
    Counter *counter;
};


___________________________________________________________________________




#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QTimer>
#include <QDebug>

class Counter : public QObject
{
    Q_OBJECT
public:
    explicit Counter(QObject *parent = nullptr);


    int value() const {return m_value;}

    void tryMessage(int &mess);


signals:
    void startCounter(int &counter);

    void valueChanged(int value);

public slots:
    void setValue(int value);

    void onTimer();
    void onCounter(int &counter);

private:
    int m_value;


};

#endif // COUNTER_H

____________________________________

#pragma once

#include <QString>
#include <iostream>
#include <stdlib.h>
#include <QByteArray>
#include <QPushButton>
#include <QRadioButton>
#include <QPixmap>
#include <QBitmap>
#include <boost/log/trivial.hpp>


#include "plugins/vehicle_plugin.hpp"
#include "app/widgets/climate.hpp"
#include "app/arbiter.hpp"
#include "openauto/Service/InputService.hpp"


class DebugWindow : public QWidget {
    Q_OBJECT

    public:
        DebugWindow(Arbiter &arbiter, QWidget *parent = nullptr);
        QLabel* tpmsOne;
        QLabel* tpmsTwo;
        QLabel* tpmsThree;
        QLabel* tpmsFour;

};




class Buttons : public QWidget {
    Q_OBJECT

    public:
        Buttons(Arbiter &arbiter, QWidget *parent = nullptr);
        
               
        QPushButton *pushButton;
        QPushButton *pushButton_2;
        QPushButton *pushButton_3;        
        QPushButton *pushButton_4;
        QLabel *label;
        QLabel *label_2;
        
        
        
public slots: 

private slots:
    void on_headlights_clicked();

    void on_headlights_2_toggled(bool checked);
    
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_toggled(bool checked);

    void on_pushButton_4_toggled(bool checked);

        
};


class canev : public QObject, VehiclePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VehiclePlugin_iid)
    Q_INTERFACES(VehiclePlugin)

    public:
        ~canev();
        bool init(ICANBus* canbus) override;
        
     public slots:
        bool canDemo(); 
        

    private:
        QList<QWidget *> widgets() override;

        bool duelClimate;

        void monitorHeadlightStatus(QByteArray payload);
        void updateClimateDisplay(QByteArray payload);
        void updateTemperatureDisplay(QByteArray payload);
        void engineUpdate(QByteArray payload);
        void tpmsUpdate(QByteArray payload);



        Climate *climate;
        DebugWindow *debug;
        Buttons *buttons;
        bool engineRunning = false;
};
