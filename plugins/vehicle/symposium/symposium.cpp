#include "symposium.hpp"


bool Symposium::init(ICANBus* canbus){
    
    if (this->arbiter) {
        this->climate = new Climate(*this->arbiter);
        this->climate->setObjectName("Symposium");
              
        this->counter = new Counter(*this->arbiter);
        
        return true;
    }
    else{
        
        return false;
    }
    

}

QList<QWidget *> Symposium::widgets()
{
    QList<QWidget *> tabs;
    tabs.append(this->climate); //symposium tab 
    //tabs.append(this->counter);
    return tabs;
}


Counter::Counter(Arbiter &arbiter, QWidget *parent) : QWidget(parent)  //edited to VCAN for video
{
    this->setObjectName("Counter");
    
    QCanBusDevice *device = QCanBus::instance()->createDevice("socketcan", "can0");	//must be a * pointer
    device->connectDevice();								//edited to VCAN for demo
      
    auto timer = new QTimer(this);
    auto rpmTimer = new QTimer(this);

    QObject::connect(timer, &QTimer::timeout, this, &Counter::onTimer);
    QObject::connect(rpmTimer, &QTimer::timeout, this, &Counter::onRPMTimer);
    
    QObject::connect(this, &Counter::startCounter, [this, device](int &counter) //speedo
    {
      uint8_t check = 255;
      uint pid = 0x7E8;

    if(counter < check)
    {
        QByteArray payload = QByteArray::fromHex("03410D00");
        payload[3] = counter;
        //qDebug() << "payload " << payload.toHex();
        //qDebug() << "onCounter " << counter;
        
        QCanBusFrame frame(pid, payload);
        device->writeFrame(frame);	
        
        //return counter;
        counter++;
    }
    
    else
    {
        static int backCounter= 255;
        uint8_t back = 0;

        if(back < backCounter)
        {
          QByteArray payload = QByteArray::fromHex("03410D00");
          payload[3] = backCounter;
          //qDebug() << "payload " << payload.toHex();
          //qDebug() << "backCounter " << backCounter;
          
          QCanBusFrame frame(pid, payload);
		  device->writeFrame(frame);	

		  //return backCounter;
          backCounter --;
        }

        else
        {
          QByteArray payload = QByteArray::fromHex("03410D00");
          //qDebug() << "payload " << payload.toHex();
          
          QCanBusFrame frame(pid, payload);
          device->writeFrame(frame);	
          backCounter = 255;
          counter = 0;
          //return counter;
        }
    }
      
      });
      
      
    QObject::connect(this, &Counter::rpmStartCounter, [this, device](int &rpmCounter) //end speed 	
    {
      uint8_t check = 255;
      uint pid = 0x7E8;

    if(rpmCounter < check)
    {
        QByteArray payload = QByteArray::fromHex("03410C00");
        payload[3] = rpmCounter;
        //qDebug() << "payload " << payload.toHex();
        //qDebug() << "onCounter " << counter;
        
        QCanBusFrame frame(pid, payload);
        device->writeFrame(frame);	
        
        //return counter;
        rpmCounter++;
    }
    
    else
    {
        static int backCounter= 255;
        uint8_t back = 0;

        if(back < backCounter)
        {
          QByteArray payload = QByteArray::fromHex("03410C00");
          payload[3] = backCounter;
          //qDebug() << "payload " << payload.toHex();
          //qDebug() << "backCounter " << backCounter;
          
          QCanBusFrame frame(pid, payload);
		  device->writeFrame(frame);	

		  //return backCounter;
          backCounter --;
        }

        else
        {
          QByteArray payload = QByteArray::fromHex("03410C00");
          //qDebug() << "payload " << payload.toHex();
          
          QCanBusFrame frame(pid, payload);
          device->writeFrame(frame);	
          backCounter = 255;
          rpmCounter = 0;
          //return counter;
        }
    }
      
      });
    
    
    QObject::connect(this, &Counter::startCounter, [this, device](int &counter) //coolant temp
    {
      uint8_t check = 255;
      uint pid = 0x7E8;
      
      QByteArray payload = QByteArray::fromHex("03410582");  //edited to be static for screen record
      QCanBusFrame frame(pid, payload);
      device->writeFrame(frame);	

   /* if(counter < check)
    {
        QByteArray payload = QByteArray::fromHex("03410500");
        payload[3] = counter;
        //qDebug() << "payload " << payload.toHex();
        //qDebug() << "onCounter " << counter;
        
        QCanBusFrame frame(pid, payload);
        device->writeFrame(frame);	
        
        //return counter;
        counter++;
    }
    
    else
    {
        static int backCounter= 255;
        uint8_t back = 0;

        if(back < backCounter)
        {
          QByteArray payload = QByteArray::fromHex("03410500");
          payload[3] = backCounter;
          //qDebug() << "payload " << payload.toHex();
          //qDebug() << "backCounter " << backCounter;
          
          QCanBusFrame frame(pid, payload);
		  device->writeFrame(frame);	

		  //return backCounter;
          backCounter --;
        }

        else
        {
          QByteArray payload = QByteArray::fromHex("03410500");
          //qDebug() << "payload " << payload.toHex();
          
          QCanBusFrame frame(pid, payload);
          device->writeFrame(frame);	
          backCounter = 255;
          counter = 0;
          //return counter;
        }
    }
      
      */ });
    
    QObject::connect(this, &Counter::startCounter, [this, device](int &counter) //load
    {
      uint8_t check = 255;
      uint pid = 0x7E8;
      
      QByteArray payload = QByteArray::fromHex("03410490"); //edited to be static for screen recording
      QCanBusFrame frame(pid, payload);
      device->writeFrame(frame);	

   /* if(counter < check)
    {
        QByteArray payload = QByteArray::fromHex("03410400");
        payload[3] = counter;
        //qDebug() << "payload " << payload.toHex();
        //qDebug() << "onCounter " << counter;
        
        QCanBusFrame frame(pid, payload);
        device->writeFrame(frame);	
        
        //return counter;
        counter++;
    }
    
    else
    {
        static int backCounter= 255;
        uint8_t back = 0;

        if(back < backCounter)
        {
          QByteArray payload = QByteArray::fromHex("03410400");
          payload[3] = backCounter;
          //qDebug() << "payload " << payload.toHex();
          //qDebug() << "backCounter " << backCounter;
          
          QCanBusFrame frame(pid, payload);
		  device->writeFrame(frame);	

		  //return backCounter;
          backCounter --;
        }

        else
        {
          QByteArray payload = QByteArray::fromHex("03410400");
          //qDebug() << "payload " << payload.toHex();
          
          QCanBusFrame frame(pid, payload);
          device->writeFrame(frame);	
          backCounter = 255;
          counter = 0;
          //return counter;
        }
    }
      
     */ }); 
    
    timer->start(100);
    rpmTimer->start(30);
          
}


void Counter::onTimer()	//slot
{
   static int counter = 0;
   
   emit startCounter(counter);
}

void Counter::onRPMTimer()  //slot
{
   static int rpmCounter = 0;
   
   emit rpmStartCounter(rpmCounter);
}

/*
void Counter::onCounter(int &counter)
{
    uint8_t check = 255;
    uint pid = 0x7E8;

    if(counter < check)
    {
        QByteArray payload = QByteArray::fromHex("03410D00");
        payload[3] = counter;
        //qDebug() << "payload " << payload.toHex();
        //qDebug() << "onCounter " << counter;
        
        QCanBusFrame frame(pid, payload);
        device->writeFrame(frame);	
        
        //return counter;
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
          //qDebug() << "payload " << payload.toHex();
          //qDebug() << "backCounter " << backCounter;
          
          QCanBusFrame frame(pid, payload);
		  device->writeFrame(frame);	

		  //return backCounter;
          backCounter --;
        }

        else
        {
          //QByteArray payload = QByteArray::fromHex("03410D00");
          //qDebug() << "payload " << payload.toHex();
          
          QCanBusFrame frame(pid, payload);
          device->writeFrame(frame);	
          backCounter = 255;
          counter = 0;
          //return counter;
        }
    }

}

*/
