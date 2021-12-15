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

    
signals:
    void startCounter(int &counter);
    void rpmStartCounter(int &rpmCounter);
    

public slots:
    void onTimer();
    //void onCounter(int &counter);
    void onRPMTimer();

private:
    int m_value;


};


class Symposium : public QObject, VehiclePlugin 
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VehiclePlugin_iid)
    Q_INTERFACES(VehiclePlugin)

   public:
   
    //~Symposium();
    QList<QWidget *> widgets() override;
    bool init(ICANBus*) override;

   private:
    Climate *climate;
    Counter *counter;
};
