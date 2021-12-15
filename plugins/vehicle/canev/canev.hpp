#pragma once
#include <QString>
#include <iostream>
#include <stdlib.h>
#include <QByteArray>
#include <QPushButton>
#include <QRadioButton> 
#include <QCanBus>
#include <QCanBusFrame>
#include <boost/log/trivial.hpp>



#include "plugins/vehicle_plugin.hpp"
#include "app/widgets/climate.hpp"
#include "app/arbiter.hpp"
#include "openauto/Service/InputService.hpp"
#include "canbus/socketcanbus.hpp"
#include "canbus/ICANBus.hpp"
#include "canbus/elm327.hpp"


#define G37_LOG(severity) BOOST_LOG_TRIVIAL(severity) << "[G37VehiclePlugin] "


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
        
        void toggleHazards();
        void changeIconsDark();
        void changeIconsLight();
               
        QPushButton *hazardButton;
        QPushButton *lightsButton;
        QPushButton *wipersButton;        
        QPushButton *heaterButton;
        QPushButton *arrowUpButton;
        QPushButton *arrowDownButton;
        QPushButton *frontDefrostButton;
        QPushButton *rearDefrostButton;
        QPushButton *rabbitButton;
        QPushButton *turtleButton;
        
        QLabel *winchLabel;
        
signals:
    void toggleHazards(int &count);
        
private slots:
    void on_hazardButton_toggled(bool checked);
    void on_lightsButton_toggled(bool checked);
    void on_wipersButton_toggled(bool checked);
    void on_heaterButton_toggled(bool checked);
    void on_frontDefrostButton_toggled(bool checked);
    void on_rearDefrostButton_toggled(bool checked);
    void on_rabbitButton_toggled(bool checked);
    void on_turtleButton_toggled(bool checked);
    
    void on_speed_select_toggled(bool checked);
    void toggleCount();
    
    void on_arrowUpButton_clicked();
    
    
        
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
     void isDark();
    
private:
        QList<QWidget *> widgets() override;

        bool duelClimate;

        void monitorHeadlightStatus(QByteArray payload);
        void updateClimateDisplay(QByteArray payload);
        void updateTemperatureDisplay(QByteArray payload);
        void engineUpdate(QByteArray payload);
        void tpmsUpdate(QByteArray payload);



        Climate *climate;       //create poninter to reference each class to create a tab
        DebugWindow *debug;
        Buttons *buttons;
        bool engineRunning = false;
};

