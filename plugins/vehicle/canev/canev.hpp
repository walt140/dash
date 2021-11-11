#pragma once

#include <QObject>
#include "plugins/vehicle_plugin.hpp"
#include "app/widgets/climate.hpp"
#include "canbus/socketcanbus.hpp"
#include "app/widgets/dialog.hpp"

class canev : public QObject, VehiclePlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VehiclePlugin_iid)
    Q_INTERFACES(VehiclePlugin)

   public:
    canev() {};
    ~canev();
    QList<QWidget *> widgets() override;
    bool init(ICANBus*) override;

   private:
    Climate *climate;
};

