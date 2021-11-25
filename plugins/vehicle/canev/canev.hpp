#pragma once

#include <QString>
#include <iostream>
#include <stdlib.h>
#include <QByteArray>
#include <QPushButton>
#include <QRadioButton>
#include <boost/log/trivial.hpp>


#include "plugins/vehicle_plugin.hpp"
#include "app/widgets/climate.hpp"
#include "app/arbiter.hpp"
#include "openauto/Service/InputService.hpp"


#define G37_LOG(severity) BOOST_LOG_TRIVIAL(severity) << "[G37VehiclePlugin]"


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
        QPushButton *pushButton_5;
        
        QLabel *label;
        QLabel *label_2;
        
        
        
public slots:
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
    
        bool init(ICANBus* canbus) override;

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
