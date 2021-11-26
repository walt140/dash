#include "canev.hpp"

bool canev::init(ICANBus* canbus){
    this->duelClimate=false;
    if (this->arbiter) {
        this->climate = new Climate(*this->arbiter);
        this->climate->max_fan_speed(7);
        this->climate->setObjectName("Climate");

        this->debug = new DebugWindow(*this->arbiter);
        this->buttons = new Buttons(*this->arbiter);

        canbus->registerFrameHandler(0x60D, [this](QByteArray payload){this->monitorHeadlightStatus(payload);});
        canbus->registerFrameHandler(0x54B, [this](QByteArray payload){this->updateClimateDisplay(payload);});
        canbus->registerFrameHandler(0x542, [this](QByteArray payload){this->updateTemperatureDisplay(payload);});
        canbus->registerFrameHandler(0x551, [this](QByteArray payload){this->engineUpdate(payload);});
        canbus->registerFrameHandler(0x385, [this](QByteArray payload){this->tpmsUpdate(payload);});

        G37_LOG(info)<<"loaded successfully";
        return true;
    }
    else{
        G37_LOG(error)<<"Failed to get arbiter";
        return false;
    }
    

}

QList<QWidget *> canev::widgets()
{
    QList<QWidget *> tabs;
    tabs.append(this->climate);
    tabs.append(this->debug);
    tabs.append(this->buttons);
    return tabs;
}

Buttons::Buttons(Arbiter &arbiter, QWidget *parent) : QWidget(parent)
{ this->setObjectName("Buttons");
    
     //this->bus = new ICANBus(this->arbiter);
    
    
     hazardButton = new QPushButton(this);		//created buttons 
     lightsButton = new QPushButton(this);
     wipersButton = new QPushButton(this);
     heaterButton = new QPushButton(this);
     arrowUpButton = new QPushButton(this);
     arrowDownButton = new QPushButton(this);
     frontDefrostButton = new QPushButton(this);
     rearDefrostButton = new QPushButton(this);
     rabbitButton = new QPushButton(this);
     turtleButton = new QPushButton(this);    
     hoistLabel = new QLabel(this);
	
  
    	hazardButton->setObjectName(QString::fromUtf8("hazardButton"));
    	lightsButton->setObjectName(QString::fromUtf8("lightsButton"));
	wipersButton->setObjectName(QString::fromUtf8("wipersButton"));
	heaterButton->setObjectName(QString::fromUtf8("heaterButton"));
	arrowUpButton->setObjectName(QString::fromUtf8("arrowUpButton"));
	arrowDownButton->setObjectName(QString::fromUtf8("arrowDownButton"));
	frontDefrostButton->setObjectName(QString::fromUtf8("frontDefrostButton"));
	rearDefrostButton->setObjectName(QString::fromUtf8("rearDefrostButton"));	
	rabbitButton->setObjectName(QString::fromUtf8("rabbitButton"));
	turtleButton->setObjectName(QString::fromUtf8("turtleButton"));
	hoistLabel->setObjectName(QString::fromUtf8("hoistLabel"));
	
                   
   	hazardButton->setIcon(QIcon("/home/pi/dash/images/hazardsOff.png"));
    	hazardButton->setGeometry(QRect(10, 10, 161, 161));
   	hazardButton->setIconSize(QSize(90, 90));
	hazardButton->setCheckable(true);
	
	lightsButton->setIcon(QIcon("/home/pi/dash/images/lightsOff.png"));
	lightsButton->setGeometry(QRect(290, 10, 161, 161));
	lightsButton->setIconSize(QSize(90, 90));
	lightsButton->setCheckable(true);

	wipersButton->setIcon(QIcon("/home/pi/dash/images/wipersOff.png"));
	wipersButton->setGeometry(QRect(260, 230, 161, 161));
	wipersButton->setIconSize(QSize(90, 90));
    	wipersButton->setCheckable(true);

	heaterButton->setIcon(QIcon("/home/pi/dash/images/heaterOff.png"));
	heaterButton->setGeometry(QRect(560, 230, 161, 161));
	heaterButton->setIconSize(QSize(90, 90));
    	heaterButton->setCheckable(true);

	arrowUpButton->setIcon(QIcon("/home/pi/dash/images/arrowUp.png"));
    	arrowUpButton->setGeometry(QRect(160, 230, 71, 71));
	arrowUpButton->setIconSize(QSize(50, 50));
	
	arrowDownButton->setIcon(QIcon("/home/pi/dash/images/arrowDown.png"));
	arrowDownButton->setGeometry(QRect(160, 320, 71, 71));
	arrowDownButton->setIconSize(QSize(50, 50));
	
	frontDefrostButton->setIcon(QIcon("/home/pi/dash/images/frontDefrostOff.png"));
	frontDefrostButton->setGeometry(QRect(460, 230, 71, 71));
	frontDefrostButton->setIconSize(QSize(50, 50));
	frontDefrostButton->setCheckable(true);
	
	rearDefrostButton->setIcon(QIcon("/home/pi/dash/images/rearDefrostOff.png"));
	rearDefrostButton->setGeometry(QRect(460, 320, 71, 71));
	rearDefrostButton->setIconSize(QSize(50, 50));
    	rearDefrostButton->setCheckable(true);
	
	rabbitButton->setIcon(QIcon("/home/pi/dash/images/rabbitOff.png"));
	rabbitButton->setGeometry(QRect(580, 10, 101, 91));
	rabbitButton->setIconSize(QSize(50, 50));
    	rabbitButton->setCheckable(true);
	
	turtleButton->setIcon(QIcon("/home/pi/dash/images/turtleOff.png"));
	turtleButton->setGeometry(QRect(580, 110, 101, 91));
	turtleButton->setIconSize(QSize(50, 50));
    	turtleButton->setCheckable(true);
    
   	hoistLabel->setPixmap(QPixmap("/home/pi/dash/images/hoist.png"));
   	hoistLabel->setGeometry(QRect(30, 290, 101, 81));

    
    QObject::connect(this->hazardButton, &QPushButton::clicked, this, &Buttons::on_hazardButton_toggled);
    QObject::connect(this->lightsButton, &QPushButton::clicked, this, &Buttons::on_lightsButton_toggled);
    QObject::connect(this->wipersButton, &QPushButton::clicked, this, &Buttons::on_wipersButton_toggled);
    QObject::connect(this->heaterButton, &QPushButton::clicked, this, &Buttons::on_heaterButton_toggled);
    QObject::connect(this->frontDefrostButton, &QPushButton::clicked, this, &Buttons::on_frontDefrostButton_toggled);
    QObject::connect(this->rearDefrostButton, &QPushButton::clicked, this, &Buttons::on_rearDefrostButton_toggled);
    QObject::connect(this->rabbitButton, &QPushButton::clicked, this, &Buttons::on_rabbitButton_toggled);
    QObject::connect(this->turtleButton, &QPushButton::clicked, this, &Buttons::on_turtleButton_toggled);
    
    QObject::connect(this->arrowUpButton, &QPushButton::clicked, [this]() 
    { 
		this->hazardButton->setIcon(QIcon("/home/pi/dash/images/hazardsOn.png"));
		
		QCanBusDevice *device = QCanBus::instance()->createDevice("socketcan", "can0");		
		QByteArray payload = QByteArray::fromHex("03410DFF00000000");
		QCanBusFrame frame(0x7e8, payload);
		device->connectDevice();
		device->writeFrame(frame);
		
					
		//const uint myArray[4] = {0x03, 0x41, 0x0D, 0x00};
		
		});
          
    
}

void Buttons::on_arrowUpButton_clicked()
{
	
}

void Buttons::on_hazardButton_toggled(bool checked)
{
    if(checked) {
            this->hazardButton->setIcon(QIcon("/home/pi/dash/images/hazardsOn.png"));
            
        }
        else {
            this->hazardButton->setIcon(QIcon("/home/pi/dash/images/hazardsOff.png"));
        }
}

void Buttons::on_lightsButton_toggled(bool checked)
{
    if(checked) {
            this->lightsButton->setIcon(QIcon("/home/pi/dash/images/lightsOn.png"));
            
        }
        else {
            this->lightsButton->setIcon(QIcon("/home/pi/dash/images/lightsOff.png"));
        }
}

void Buttons::on_wipersButton_toggled(bool checked)
{
    if(checked) {
            this->wipersButton->setIcon(QIcon("/home/pi/dash/images/wipersOn.png"));
            
        }
        else {
            this->wipersButton->setIcon(QIcon("/home/pi/dash/images/wipersOff.png"));
        }
}

void Buttons::on_heaterButton_toggled(bool checked)
{
    if(checked) {
            this->heaterButton->setIcon(QIcon("/home/pi/dash/images/heaterOn.png"));
            
        }
        else {
            this->heaterButton->setIcon(QIcon("/home/pi/dash/images/heaterOff.png"));
        }
}

void Buttons::on_frontDefrostButton_toggled(bool checked)
{
    if(checked) {
            this->frontDefrostButton->setIcon(QIcon("/home/pi/dash/images/frontDefrostOn.png"));
            
        }
        else {
            this->frontDefrostButton->setIcon(QIcon("/home/pi/dash/images/frontDefrostOff.png"));
        }
}

void Buttons::on_rearDefrostButton_toggled(bool checked)
{
    if(checked) {
            this->rearDefrostButton->setIcon(QIcon("/home/pi/dash/images/rearDefrostOn.png"));
            
        }
        else {
            this->rearDefrostButton->setIcon(QIcon("/home/pi/dash/images/rearDefrostOff.png"));
        }
}

void Buttons::on_rabbitButton_toggled(bool checked)
{
    if(checked) {
            this->rabbitButton->setIcon(QIcon("/home/pi/dash/images/rabbitOn.png"));
            
        }
        else {
            this->rabbitButton->setIcon(QIcon("/home/pi/dash/images/rabbitOff.png"));
        }
}

void Buttons::on_turtleButton_toggled(bool checked)
{
    if(checked) {
            this->turtleButton->setIcon(QIcon("/home/pi/dash/images/turtleOn.png"));
            
        }
        else {
            this->turtleButton->setIcon(QIcon("/home/pi/dash/images/turtleOff.png"));
        }
}
    
// TPMS
// 385
// THIRD BYTE:
//  Tire Pressure (PSI) * 4
// FOURTH BYTE:
//  Tire Pressure (PSI) * 4
// FIFTH BYTE:
//  Tire Pressure (PSI) * 4
// SIXTH BYTE:
//  Tire Pressure (PSI) * 4
// SEVENTH BYTE:
// |Tire 1 Pressure Valid|Tire 2 Pressure Valid|Tire 3 Pressure Valid|Tire 4 Pressure Valid|unknown|unknown|unknown|unknown

// OTHERS UNKNOWN

void canev::tpmsUpdate(QByteArray payload){
    this->debug->tpmsOne->setText(QString::number((uint8_t)payload.at(2)/4));
    this->debug->tpmsTwo->setText(QString::number((uint8_t)payload.at(3)/4));
    this->debug->tpmsThree->setText(QString::number((uint8_t)payload.at(4)/4));
    this->debug->tpmsFour->setText(QString::number((uint8_t)payload.at(5)/4));
}

//551
//(A, B, C, D, E, F, G, H)
// D - Bitfield.

//     0xA0 / 160 - Engine off, "On"
//     0x20 / 32 - Engine turning on (500ms)
//     0x00 / 0 - Engine turning on (2500ms)
//     0x80 / 128 - Engine running
//     0x00 / 0 - Engine shutting down (2500ms)
//     0x20 / 32 - Engine off


void canev::engineUpdate(QByteArray payload){
    if((payload.at(3) == 0x80)) engineRunning = true;
    else
    {
        if(engineRunning)
            this->arbiter->send_openauto_button_press(aasdk::proto::enums::ButtonCode::PAUSE);
        engineRunning = false;
    }
}


// HEADLIGHTS AND DOORS
// 60D
// FIRST BYTE:
// |unknown|RR_DOOR|RL_DOOR|FR_DOOR|FL_DOOR|SIDE_LIGHTS|HEADLIGHTS|unknown|
// SECOND BYTE:
// |unknown|unknown|unknown|unknown|unknown|unknown|unknown|FOGLIGHTS|
// OTHERS UNKNOWN

void canev::monitorHeadlightStatus(QByteArray payload){
    if((payload.at(0)>>1) & 1){
        //headlights are ON - turn to dark mode
        if(this->arbiter->theme().mode == Session::Theme::Light){
            this->arbiter->set_mode(Session::Theme::Dark);
        }
    }
    else{
        //headlights are off or not fully on (i.e. sidelights only) - make sure is light mode
        if(this->arbiter->theme().mode == Session::Theme::Dark){
            this->arbiter->set_mode(Session::Theme::Light);
        }
    }
}

// HVAC
// 54B

// FIRST BYTE 
// |unknown|unknown|unknown|unknown|unknown|unknown|unknown|HVAC_OFF|
// SECOND BYTE
// |unknown|unknown|unknown|unknown|unknown|unknown|unknown|unknown|
// THIRD BYTE - MODE
// |unknown|unknown|MODE|MODE|MODE|unknown|unknown|unknown|
//   mode:
//    defrost+leg
//       1 0 0
//    head
//       0 0 1
//    head+feet
//       0 1 0
//    feet
//       0 1 1
//    defrost
//       1 0 1
// FOURTH BYTE
// |unknown|DUEL_CLIMATE_ON|DUEL_CLIMATE_ON|unknown|unknown|unknown|RECIRCULATE_OFF|RECIRCULATE_ON|
// Note both duel climate on bytes toggle to 1 when duel climate is on
// FIFTH BYTE - FAN LEVEL
// |unknown|unknown|FAN_1|FAN_2|FAN_3|unknown|unknown|unknown|
// FAN_1, FAN_2, FAN_3 scale linearly fan 0 (off) -> 7
//
// ALL OTHERS UNKNOWN

bool oldStatus = true;

void canev::updateClimateDisplay(QByteArray payload){
    duelClimate = (payload.at(3)>>5) & 1;
    bool hvacOff = payload.at(0) & 1;
    if(hvacOff != oldStatus){
        oldStatus = hvacOff;
        if(hvacOff){
            climate->airflow(Airflow::OFF);
            climate->fan_speed(0);
            G37_LOG(info)<<"Climate is off";
            return;
        }
    }
    uint8_t airflow = (payload.at(2) >> 3) & 0b111;
    uint8_t dash_airflow = 0;
    switch(airflow){
        case(1):
            dash_airflow = Airflow::BODY;
            break;
        case(2):
            dash_airflow = Airflow::BODY | Airflow::FEET;
            break;
        case(3):
            dash_airflow = Airflow::FEET;
            break;
        case(4):
            dash_airflow = Airflow::DEFROST | Airflow::FEET;
            break;
        case(5):
            dash_airflow = Airflow::DEFROST;
            break;
    }
    if(climate->airflow()!=dash_airflow)
        climate->airflow(dash_airflow);
    uint8_t fanLevel = (payload.at(4)>>3) & 0b111;
    if(climate->fan_speed()!=fanLevel)
        climate->fan_speed(fanLevel);
}

// Climate
// 542

// FIRST BYTE:
// unknown
// SECOND BYTE:
// entire byte is driver side temperature, 60F->90F
// THIRD BYTE:
// entire byte is passenger side temperature, 60F->90F
// note that this byte is only updated when duel climate is on. When duel climate is off, SECOND BYTE contains accurate passenger temperature.

void canev::updateTemperatureDisplay(QByteArray payload){
    if(climate->driver_temp()!=(unsigned char)payload.at(1))
        climate->driver_temp((unsigned char)payload.at(1));
    if(duelClimate){
        if(climate->passenger_temp()!=(unsigned char)payload.at(2)){
            climate->passenger_temp((unsigned char)payload.at(2));
        }
    }else{
        if(climate->passenger_temp()!=(unsigned char)payload.at(1))
            climate->passenger_temp((unsigned char)payload.at(1));
    }
}




DebugWindow::DebugWindow(Arbiter &arbiter, QWidget *parent) : QWidget(parent)
{
    this->setObjectName("DebugCanEV");


    QLabel* textOne = new QLabel("Front Right PSI", this);
    QLabel* textTwo = new QLabel("Front Left PSI", this);
    QLabel* textThree = new QLabel("Rear Right PSI", this);
    QLabel* textFour = new QLabel("Rear Left PSI", this);
    
    
    //CanEV Button creation
    QPushButton* button = new QPushButton("CanEV", this);
    //Radio, Toggle slot created 
    QRadioButton* radio = new QRadioButton(this);
    

    tpmsOne = new QLabel("--", this);
    tpmsTwo = new QLabel("--", this);
    tpmsThree = new QLabel("--", this);
    tpmsFour = new QLabel("--", this);



    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(button);  //puts button in top layout
    layout->addWidget(radio);   //puts radio in top layout    
    layout->addWidget(textOne);
    layout->addWidget(tpmsOne);
    
    layout->addWidget(Session::Forge::br(false));

    layout->addWidget(textTwo);
    layout->addWidget(tpmsTwo);
    layout->addWidget(Session::Forge::br(false));

    layout->addWidget(textThree);
    layout->addWidget(tpmsThree);
    layout->addWidget(Session::Forge::br(false));

    layout->addWidget(textFour); 
    layout->addWidget(tpmsFour);
    layout->addWidget(Session::Forge::br(false));

    
    //Signal that connects button actino to toggle radio 
	QObject::connect(button, SIGNAL(clicked()), radio, SLOT(toggle()));

}
