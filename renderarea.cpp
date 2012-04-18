#include <QtGui>
#include "renderarea.h"

#include <QDebug>

#define SIDE_LENGTH 40 //15

RenderArea::RenderArea(QWidget* parent) : QWidget(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(next()));
}

RenderArea::~RenderArea() {
    delete timer;
    //delete surface;
}

void RenderArea::next() {
    //surface->next();
    update();
}

void RenderArea::play() {
    timer->start(100);
}

void RenderArea::stop() {
    timer->stop();
}

void RenderArea::save()
{
    //surface->save();
}

void RenderArea::showDimers(QPainter &painter) {
}

void RenderArea::restore() {
    //surface->restore();
    update();
}

int RenderArea::getCoordinate(int cell_index) const {
    return cell_index * SIDE_LENGTH + SIDE_LENGTH / 2;
}

int RenderArea::getIndex(int coordinate) const {
    return (coordinate - SIDE_LENGTH / 2) / SIDE_LENGTH;
}

QSize RenderArea::minimumSizeHint() const
{
    //return QSize(SIDE_LENGTH * (surface->sizeX() + 1), SIDE_LENGTH * (surface->sizeY() + 1));
}

void RenderArea::mousePressEvent(QMouseEvent* event) {
    //surface->invertCell(getIndex(event->x()), getIndex(event->y()));
    update();
}

void RenderArea::paintEvent(QPaintEvent*)
{
//    QRect rect(0, 0, SIDE_LENGTH, SIDE_LENGTH);
//    QPen pen(Qt::black);

//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.setPen(pen);
//    painter.setRenderHint(QPainter::Antialiasing, false);
}
