#ifndef SWITCH_HPP_
#define SWITCH_HPP_

#include <QtWidgets>

#include "app/theme.hpp"

class Switch : public QAbstractButton {
    Q_OBJECT
    Q_PROPERTY(QColor track_color READ get_track_color WRITE set_track_color)
    Q_PROPERTY(QColor thumb_color READ get_thumb_color WRITE set_thumb_color)
    Q_PROPERTY(int offset READ get_offset WRITE set_offset)

   public:
    Switch(QWidget* parent = 0);

    QSize sizeHint() const override;

    QColor get_track_color() { return this->track_color; };
    QColor get_thumb_color() { return this->thumb_color; };
    int get_offset() { return this->offset; }

    void set_track_color(QColor track_color) { this->track_color = track_color; }
    void set_thumb_color(QColor thumb_color) { this->thumb_color = thumb_color; }
    void set_offset(int offset) { this->offset = offset; }

   protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void nextCheckState() override;

   signals:
    void stateChanged(bool);

   private:
    Theme *theme;

    int track_radius;
    int thumb_radius;

    QColor track_color=Qt::transparent;
    QColor thumb_color=Qt::transparent;
    int offset;
    int margin;
    int base_offset;
    std::function<int(bool)> end_offset;
};

#endif
