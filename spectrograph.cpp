#include "spectrograph.h"
#include <iostream>
#include <QtCore/qmath.h>
#include <QBrush>
#include <QPen>
#include <QGradient>
#include <QDebug>
#include <QResizeEvent>
#include <QTimerEvent>
#include <QMessageBox>
#include <QAction>
#include <QMenu>

Spectrograph::Spectrograph(QWidget *parent) :
  AbstractSpectrograph(parent){
  startTimer(15);
  NUM_BANDS = 256;
  spectrum.resize(NUM_BANDS);
  delay.resize(NUM_BANDS);
  for(int i=0; i<NUM_BANDS; i++){
      spectrum[i]=1;
      delay[i]=1;
  }
  leftLevel = rightLevel = 1;
  gradient.setColorAt(1, Qt::black);
  gradient.setColorAt(0, Qt::black);
  gradientBrush.setStyle(Qt::SolidPattern);
  backgroundBrush.setColor(Qt::white);
  backgroundBrush.setStyle(Qt::SolidPattern);

  barSpacing = 1;
  acao = new QAction("Acao",this);
  connect(acao,SIGNAL(triggered()),this,SLOT(doAction()));
}

void Spectrograph::resizeEvent(QResizeEvent *e){
  e->accept();
  gradient = QLinearGradient(rect().topLeft(), rect().bottomLeft());
  gradientBrush = QBrush(gradient);
  barWidth = (float)width()/NUM_BANDS;
  widgetHeight = height();
  repaint();
}

void Spectrograph::contextMenuEvent(QContextMenuEvent *e)
{
  QMenu menu;
  menu.addAction(acao);
  menu.exec(e->globalPos());
}

void Spectrograph::loadLevels(double left, double right){
  // 5 and 2 are two beautiful magic numbers
  // I dont remember why I choose them :]
  if(leftLevel < 5*width()/2*left)
    leftLevel = 5*width()/2*left;
  if(rightLevel < 5*width()/2*right)
    rightLevel = 5*width()/2*right;
}

void Spectrograph::doAction(){

  QMessageBox box; //! Creates the message box
  box.setText(QString("Aha!")); //! defines a text for the box
  box.exec(); //! display the message box
}

void Spectrograph::paintEvent(QPaintEvent *e){
  Q_UNUSED(e); // some events are not necessary.
  //so we marked them as UNUSED to avoid compiler warnings
  QPainter p(this); // p is a painter and it is able
  // to paint into "this" object. The painter has lots of
  // resources to draw, such as pens, brushes and geometric figures
  // that can be activated by calling appropriate methods

  // stores coordinates of the rectangles of the spectrum
  float p1x, p2x, p1y, p2y;

  // draw using antialiasing. The geometric figures will not
  // look like a sawtooth
  p.setRenderHint(QPainter::Antialiasing);

  // put the brush on black (for filling regions)
  p.setBrush(backgroundBrush);

  // draw a rectangle filling the entire component
  // the rect() function returns the rectangle corresponding to
  // the full region of the widget
  p.drawRect(rect());

  // prepares the pen that will draw the bars
  // solid black line with 1 pixel width
  pen.setStyle(Qt::SolidLine);
  pen.setColor(Qt::black);
  pen.setWidth(1);

  // gives the pen to the painter
  p.setPen(pen);

  // stores midline vertical coordinate to draw the mirrowed spectrum
  p2y = widgetHeight/2;

  // gives the brush to the painter (a nice gradient)
  p.setBrush(gradientBrush);

  // draw the bars
  for(int i=0; i<NUM_BANDS;i++){
    // calcs left and right x coordinates of each bar
    p1x = i*barWidth;
    p2x = p1x+barWidth;

    // calcs heights for up spectrum bars
    p1y = p2y - spectrum[i]/2;
    // draw the up bar
    // take a look at the point coordinates that are supplied
    // toe the QRectF rectangle
    p.drawRect(QRectF(QPointF(p1x,p1y),QPointF(p2x,p2y)));

    // calcs heights for down spectrum bars
    p1y = p2y + spectrum[i]/2;
    // draw the down bar
    p.drawRect(QRectF(QPointF(p1x,p1y),QPointF(p2x,p2y)));
  }
  // now, lets draw left and right mean audio values
  // brush is black
  p.setBrush(Qt::black);

  // draw a black rectangle spanning the whole widget width
  // it is 7 pixels height
  // we just called the drawRect(x,y,width,height) overloaded function
  p.drawRect(0,height()-7,width(),7);

  // lets draw the bars
  // left bar is red
  p.setBrush(Qt::red);
  p.drawRoundedRect(width()/2-leftLevel,height()-6,leftLevel,6,3,3);

  // right bar is blue
  p.setBrush(Qt::blue);
  p.drawRoundedRect(width()/2,height()-6,rightLevel,6,3,3);
}

void Spectrograph::timerEvent(QTimerEvent *e){
  Q_UNUSED(e); // who cares about this event,
  // since we just have one timer running

  // the following stuff simulates bar decay with gravity
  for(int i=0; i<NUM_BANDS; i++){
    // spectrum decays according to its delay
    spectrum[i]-=delay[i];
    // get rid of negative spectrum values
    if(spectrum[i] < 0 ){
      spectrum[i]=0;
    }
    // increases the delay. next timer event
    // it will be larger and the bar will decay faster
    delay[i]++;
  }
  // decay left and right mean audio values and just
  // be careful about negative values
  if(leftLevel > 0)
    leftLevel--;
  if(rightLevel > 0)
    rightLevel--;

  // repaint the whole thing!!
  repaint();
}

void Spectrograph::loadSamples(QVector<double> &_spectrum){
  int increment, value;
  // lets subsample the spectrum according to the number of bands
  // selected by user
  increment = _spectrum.size()/NUM_BANDS;

  // processing audio bars...
  for(int i=0; i<NUM_BANDS;i++){
    // calculates values according to the widget height
    value = ceil(_spectrum[i*increment]*height());
    // we just copy the values to its corresponding position on
    // spectrum if it exceeds the current value that is stored
    // this approach ensure smoothness to decay bars
    if(value > spectrum[i]){
      spectrum[i] = value;

      // if the spectrum is updated, we have to restart gravity
      delay[i] = 0;
    }
  }

  // repaint the whole thing!!
  repaint();
}
