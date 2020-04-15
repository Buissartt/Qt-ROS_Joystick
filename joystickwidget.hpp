#ifndef JOYSTICKWIDGET_H
#define JOYSTICKWIDGET_H

#include <QWidget>

class JoystickWidget : public QWidget
{
  Q_OBJECT

public:
  JoystickWidget( QWidget *parent=0 );
  ~JoystickWidget(){}
  QSize sizeHint() const;

  void reset();
  double getYBase();
  double getY();
  double getXBase();
  double getX();

Q_SIGNALS : void hasMoved();


protected:
  void paintEvent( QPaintEvent* );

  void mouseMoveEvent( QMouseEvent* );
  void mouseReleaseEvent( QMouseEvent* );

private:
  double x, y, r, xBase, yBase, rBase;
  QColor color, colorBase; 
  bool isMoving;

};

#endif // JOYSTICKWIDGET_H

