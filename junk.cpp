bool canev::canDemo() 
{
	QCanBusFrame *frame = new QCanBusFrame(0x7df, QByteArray::fromHex("0201100000000000"));
	Buttons->label_2->setText("CAN Message Sent");
	SocketCANBus->writeFrame(*frame);
}

//11/24 4:50 
Buttons::Buttons(Arbiter &arbiter, QWidget *parent) : QWidget(parent)
{
    this->setObjectName("Buttons");
    
    
    
    pushButton = new QPushButton(this);
    pushButton_2 = new QPushButton(this);
    pushButton_3 = new QPushButton(this);
    pushButton_4 = new QPushButton(this);
    pushButton_5 = new QPushButton(this);
  
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
    pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
    pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
  
    label = new QLabel(this);
    label_2 = new QLabel(this);
    
    label->setObjectName(QString::fromUtf8("label"));
    label_2->setObjectName(QString::fromUtf8("label_2"));
    
    pushButton->setText(QApplication::translate("Buttons", "Push Me", nullptr));
    pushButton_2->setText(QApplication::translate("Buttons", "No Me", nullptr));
    
    
    pushButton_3->setCheckable(true);
    pushButton_3->setText(QApplication::translate("Buttons", "Lights Off", nullptr));
    
    //pushButton_4->setText(QString("Hazard"));
    
    pushButton_4->setCheckable(true);
    pushButton_4->setIcon(QIcon("/home/pi/dash/assets/hazardsOff.png"));
    
    pushButton_5->setText(QApplication::translate("Buttons", "Send Message", nullptr));
   
   
    label->setText(QString("Here is Label 1"));
    label_2->setText(QString("Here is Label 2"));
    
    label->setScaledContents(true);
    label->setPixmap(QPixmap(":/splash.png"));
    
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    layout->addWidget(pushButton);  //puts button in top layout
    layout->addWidget(pushButton_2);
    layout->addWidget(pushButton_3);
    layout->addWidget(pushButton_4);
    layout->addWidget(label);
    layout->addWidget(label_2);
    
    QObject::connect(this->pushButton, &QPushButton::clicked, this, &Buttons::on_pushButton_clicked);
    QObject::connect(this->pushButton_2, &QPushButton::clicked, this, &Buttons::on_pushButton_2_clicked);
    QObject::connect(this->pushButton_3, &QPushButton::toggled, this, &Buttons::on_pushButton_3_toggled);
    QObject::connect(this->pushButton_4, &QPushButton::toggled, this, &Buttons::on_pushButton_4_toggled);
    QObject::connect(this->pushButton_5, &QPushButton::clicked, this, &Buttons::on_pushButton_4_toggled);
    
    
}



Buttons::Buttons(Arbiter &arbiter, QWidget *parent) : QWidget(parent)
{
    this->setObjectName("Buttons");
    
     //Create vertical layout container
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    //CanEV Button creation
    QPushButton* button = new QPushButton("CanEV", this);
    
    //Radio, Toggle slot created 
    QRadioButton* radio = new QRadioButton(this);
    
    QPushButton* headlights = new QPushButton(this);
     //headlights->setCheckable(true);
     
    QPixmap pixmap(QPixmap(":/headlightsOn.png"));
    QSplashScreen splash(pixmap);
    splash.setMask(pixmap.mask());
    splash.show();

        
    
    layout->addWidget(button);  //puts button in top layout
    layout->addWidget(radio);   //puts radio in top layout    
    layout->addWidget(headlights);
    
    //Signal that connects button action to toggle radio 
	QObject::connect(button, SIGNAL(clicked()), radio, SLOT(toggle()));
    
}



  QPixmap* pixmap = new QPixmap(QPixmap(":/headlightsOn.png"));
    QPixmap* pixmap_2 = new QPixmap(":/logo.png");
    
     //Create vertical layout container
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    //CanEV Button creation
    QPushButton* button = new QPushButton("CanEV", this);
    
    //Radio, Toggle slot created 
    QRadioButton* radio = new QRadioButton(this);
    
    QLabel* label = new QLabel(this); 
    label->setText("Label Over Here!!!");
    label->setPixmap(QPixmap(":/headlightOff.png"));
    
    
    headlights = new QPushButton(this);
    headlights->setIcon(QIcon(":/add.svg"));
    headlights->setCheckable(true);
    
    if(
    
    headlights_2 = new QPushButton(this);
    headlights_2->setIcon(QIcon(":/headlightOff.png"));
    
    
    headlights->setStyleSheet(QString::fromUtf8("#headlights {\n"
        "	background-color: transparent; \n"
        "	border-image: url(:/headlightsOff.png);\n"
        "	background: none;\n"
        "	\n"
        "}\n"
        "\n"
        "#headlights:pressed{\n"
        "	border-image: url(:/headlightsOn.png);\n"
        "	\n"
        "}")); 
     
    
    layout->addWidget(button);  //puts button in top layout
    layout->addWidget(radio);   //puts radio in top layout    
    layout->addWidget(headlights);
    layout->addWidget(headlights_2);
    layout->addWidget(label);
    
    
    //Signal that connects button action to toggle radio 
	QObject::connect(button, SIGNAL(clicked()), radio, SLOT(toggle()));




}



#include "canev.hpp"

canev::~canev()
{
    if (this->climate)
        delete this->climate;
}

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

        //G37_LOG(info)<<"loaded successfully";
        return true;
    }
    else{
        //G37_LOG(error)<<"Failed to get arbiter";
        return false;
    }
    

}

QList<QWidget *> canev::widgets()
{
    QList<QWidget *> tabs;
    tabs.append(this->climate);
    //tabs.append(this->debug);
    //tabs.append(this->buttons);
    
    return tabs;
}

DebugWindow::DebugWindow(Arbiter &arbiter, QWidget *parent) : QWidget(parent)
{
    this->setObjectName("DebugCanEV");


    QLabel* textOne = new QLabel("Front Right PSI", this);
    QLabel* textTwo = new QLabel("Front Left PSI", this);
    QLabel* textThree = new QLabel("Rear Right PSI", this);
    QLabel* textFour = new QLabel("Rear Left PSI", this);
        

    tpmsOne = new QLabel("--", this);
    tpmsTwo = new QLabel("--", this);
    tpmsThree = new QLabel("--", this);
    tpmsFour = new QLabel("--", this);


    //Create vertical layout container
    QVBoxLayout *layout = new QVBoxLayout(this);   
    

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

    
}   



Buttons::Buttons(Arbiter &arbiter, QWidget *parent) : QWidget(parent)
{
    this->setObjectName("Buttons");
    
    
    pushButton = new QPushButton(this);
    pushButton_2 = new QPushButton(this);
    pushButton_3 = new QPushButton(this);
    pushButton_4 = new QPushButton(this);
  
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
    pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
  
    label = new QLabel(this);
    label_2 = new QLabel(this);
    
    label->setObjectName(QString::fromUtf8("label"));
    label_2->setObjectName(QString::fromUtf8("label_2"));
    
    pushButton->setText(QApplication::translate("Buttons", "Push Me", nullptr));
    pushButton_2->setText(QApplication::translate("Buttons", "No Me", nullptr));
    pushButton_3->setText(QApplication::translate("Buttons", "Lights Off", nullptr));
    pushButton_4->setText(QString("Hazard"));
    pushButton_4->setCheckable(true);
    label->setText(QString("Here is Label 1"));
    label_2->setText(QString("Here is Label 2"));
    
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    layout->addWidget(pushButton);  //puts button in top layout
    layout->addWidget(pushButton_2);
    layout->addWidget(pushButton_3);
    layout->addWidget(pushButton_4);
    layout->addWidget(label);
    layout->addWidget(label_2);
    
    //QObject::connect(this->pushButton, &QPushButton::clicked, this, &Buttons::on_pushButton_clicked);
    //QObject::connect(pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_3_toggled()));
    
    
}
/*
void Buttons::on_pushButton_clicked()
{
    this->label_2->setText("Hello World!!");
}

void Buttons::on_pushButton_2_clicked()
{
    this->label_2->setText("See ya Later");
}

void Buttons::on_pushButton_3_toggled(bool checked)
{
    if(checked) {
            this->pushButton_3->setText("Lights On");
            this->label->setPixmap(QPixmap(":/headlightsOn.png"));
        }

        else {
            this->pushButton_3->setText("Lights Off");
            this->label->setPixmap(QPixmap(":/headlightsOff.png"));

        }
}

void Buttons::on_pushButton_4_toggled(bool checked)
{
    if(checked) {
            this->label_2->setText("Hazard was toggled on");
            this->pushButton_4->setIcon(QIcon(":/hazardsOn.png"));
        }

        else {
            this->label_2->setText("Hazard was toggled off");
            this->pushButton_4->setIcon(QIcon(":/hazardsOff.png"));

        }

}




  void Buttons::symposium(QByte Array payload) 
{
        
}
*/

/*
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
*/
void canev::tpmsUpdate(QByteArray payload){
    this->debug->tpmsOne->setText(QString::number((uint8_t)payload.at(2)/4));
    this->debug->tpmsTwo->setText(QString::number((uint8_t)payload.at(3)/4));
    this->debug->tpmsThree->setText(QString::number((uint8_t)payload.at(4)/4));
    this->debug->tpmsFour->setText(QString::number((uint8_t)payload.at(5)/4));
}

/*
//551
//(A, B, C, D, E, F, G, H)
// D - Bitfield.

//     0xA0 / 160 - Engine off, "On"
//     0x20 / 32 - Engine turning on (500ms)
//     0x00 / 0 - Engine turning on (2500ms)
//     0x80 / 128 - Engine running
//     0x00 / 0 - Engine shutting down (2500ms)
//     0x20 / 32 - Engine off
*/

void canev::engineUpdate(QByteArray payload){
    if((payload.at(3) == 0x80)) engineRunning = true;
    else
    {
        if(engineRunning)
            this->arbiter->send_openauto_button_press(aasdk::proto::enums::ButtonCode::PAUSE);
        engineRunning = false;
    }
}

/*
// HEADLIGHTS AND DOORS
// 60D
// FIRST BYTE:
// |unknown|RR_DOOR|RL_DOOR|FR_DOOR|FL_DOOR|SIDE_LIGHTS|HEADLIGHTS|unknown|
// SECOND BYTE:
// |unknown|unknown|unknown|unknown|unknown|unknown|unknown|FOGLIGHTS|
// OTHERS UNKNOWN
*/
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

/*
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
*/

bool oldStatus = true;

void canev::updateClimateDisplay(QByteArray payload){
    duelClimate = (payload.at(3)>>5) & 1;
    bool hvacOff = payload.at(0) & 1;
    if(hvacOff != oldStatus){
        oldStatus = hvacOff;
        if(hvacOff){
            climate->airflow(Airflow::OFF);
            climate->fan_speed(0);
            //G37_LOG(info)<<"Climate is off";
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

/*
// Climate
// 542

// FIRST BYTE:
// unknown
// SECOND BYTE:
// entire byte is driver side temperature, 60F->90F
// THIRD BYTE:
// entire byte is passenger side temperature, 60F->90F
// note that this byte is only updated when duel climate is on. When duel climate is off, SECOND BYTE contains accurate passenger temperature.
*/

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





