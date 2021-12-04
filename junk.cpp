
#include "counter.h"

Counter::Counter(QObject *parent) : QObject(parent)
{
    auto timer = new QTimer(this);

    QObject::connect(timer, &QTimer::timeout, this, &Counter::onTimer);
    QObject::connect(this, &Counter::startCounter, this, &Counter::onCounter);

    timer->start(1000);
    m_value = 0;
}

void Counter::setValue(int value)
{
    if (value != m_value) {
            m_value = value;
            emit valueChanged(value);
        }
}

void Counter::onTimer()
{
   static int counter = 0;
   emit onCounter(counter);
}

void Counter::onCounter(int &counter)
{
    uint8_t check = 255;

    if(counter < check)
    {
        QByteArray payload = QByteArray::fromHex("03410D00");
        payload[3] = counter;
        qDebug() << "payload " << payload.toHex();
        qDebug() << "onCounter " << counter;
        counter++;
    }


//counter now = 255 & check = 255
    else
    {
        static int backCounter= 255;
        uint8_t back = 0;

        if(back < backCounter)
        {
          QByteArray payload = QByteArray::fromHex("03410D00");
          payload[3] = backCounter;
          qDebug() << "payload " << payload.toHex();
          qDebug() << "backCounter " << backCounter;
          backCounter --;
        }

        else
        {
          QByteArray payload = QByteArray::fromHex("03410D00");
          qDebug() << "payload " << payload.toHex();
          backCounter = 255;
          counter = 0;
        }
    }

}


___________________________________________________________________________________




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





