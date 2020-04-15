#include <math.h>

#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include "../include/gui_leenby/joystickwidget.hpp"

JoystickWidget::JoystickWidget( QWidget *parent ) : QWidget( parent )
{
    rBase = 100;
    xBase = rBase+50;
    yBase = rBase+50;
    colorBase = QColor(100,100,100);

    r = 15;
    x=xBase;
    y=yBase;
    color = QColor( 255, 0, 0 );

    isMoving = false;

}

QSize JoystickWidget::sizeHint() const
{
    return QSize( 300, 300 );
}

void JoystickWidget::paintEvent( QPaintEvent* )
{
    QPainter painter( this );

    painter.setRenderHint( QPainter::Antialiasing );
    if(this->isEnabled())
    {
        painter.setPen( colorBase );
        painter.setBrush( colorBase );
        painter.drawEllipse( xBase-rBase, yBase-rBase, 2*rBase, 2*rBase );

        painter.setPen( color );
        painter.setBrush( color );
        painter.drawEllipse( x-r, y-r, 2*r, 2*r );
    }
    else
    {
        painter.setPen( QColor(175,175,175) );
        painter.setBrush( QColor(175,175,175) );
        painter.drawEllipse( xBase-rBase, yBase-rBase, 2*rBase, 2*rBase );

        painter.setPen( QColor(255,100,100) );
        painter.setBrush( QColor(255,100,100) );
        painter.drawEllipse( x-r, y-r, 2*r, 2*r );
    }

}

void JoystickWidget::mouseMoveEvent( QMouseEvent *e )
{
    int dist =(xBase-e->x())*(xBase-e->x()) + (yBase-e->y())*(yBase-e->y());
    int distRedDot = (x-e->x())*(x-e->x()) + (y-e->y())*(y-e->y());

    if( distRedDot < (r*r) )
    {
        isMoving = true;
    }

    if( isMoving)
    {
        if( dist > (rBase*rBase) )
        {
            float ratio = rBase / sqrt(dist);    // ------
            x = xBase + ( e->x() - xBase)*ratio; // Thalès
            y = yBase + ( e->y() - yBase)*ratio; // ------
        }
        else
        {
            x = e->x();
            y = e->y();
        }
        Q_EMIT JoystickWidget::hasMoved();
    }

    update();
}


void JoystickWidget::mouseReleaseEvent( QMouseEvent *e )
{
    reset();
    Q_EMIT JoystickWidget::hasMoved();

}

void JoystickWidget::reset()
{
    x=xBase;
    y=yBase;
    update();
    isMoving = false;
}

double JoystickWidget::getYBase(){
    return yBase;
}

double JoystickWidget::getY(){
    return y;
}

double JoystickWidget::getXBase(){
    return xBase;
}

double JoystickWidget::getX(){
    return x;
}
