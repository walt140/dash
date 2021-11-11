#include <QDebug>
#include <QTimer>

#include "canev.hpp"

canev::~canev()
{
    if (this->climate)
        delete this->climate;
}

QList<QWidget *> canev::widgets()
{
    QList<QWidget *> tabs;
    if (this->climate)
        tabs.append(this->climate);
    return tabs;
}

bool canev::init(ICANBus*)
{
    if (this->arbiter) {
        this->climate = new Climate(*this->arbiter);
        this->climate->setObjectName("boogers");
        this->climate->max_fan_speed(4);

    }
}

QPushButton::QPushButton(const QString &text, QWidget *parent = nullptr)
{
    
}

void Dialog::set_button(QPushButton *button)
{
    if (this->buttons->count() == 0)
        this->add_cancel_button();
    button->setFlat(true);
    this->buttons->addWidget(button, 0, Qt::AlignRight);
    connect(button, &QPushButton::clicked, [this]() { this->close(); });
}
