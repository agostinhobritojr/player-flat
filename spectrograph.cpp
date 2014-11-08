#include "spectrograph.h"
#include <iostream>
#include <QtCore/qmath.h>
#include <QBrush>
#include <QPen>
#include <QGradient>
#include <QDebug>
#include <QResizeEvent>
#include <QTimerEvent>
#include <QPainterPath>
#include <QEasingCurve>

Spectrograph::Spectrograph(QWidget *parent) :
  AbstractSpectrograph(parent){
  startTimer(15);
  NUM_BANDS = 32;
  spectrum.resize(NUM_BANDS);
  delay.resize(NUM_BANDS);
  for(int i=0; i<NUM_BANDS; i++){
      spectrum[i]=1;
      delay[i]=1;
  }
  leftLevel = rightLevel = 1;
  gradient = QLinearGradient(rect().topLeft(), rect().bottomLeft());
  gradient.setColorAt(1, Qt::black);
  gradient.setColorAt(0, Qt::black);
  gradientBrush = QBrush(gradient);
  gradientBrush.setStyle(Qt::SolidPattern);
  backgroundBrush.setColor(Qt::white);
  backgroundBrush.setStyle(Qt::SolidPattern);
  transparentBrush.setColor(Qt::transparent);
  pen.setColor(qRgb(0,0,0));
  decayBrush.setColor(QColor(255,0,0,255));
  decayBrush.setStyle(Qt::SolidPattern);
  barWidth = MIN_BARWIDTH;
  barSpacing = 1;
}

void Spectrograph::resizeEvent(QResizeEvent *e){
  e->accept();
  gradient = QLinearGradient(rect().topLeft(), rect().bottomLeft());
  gradientBrush = QBrush(gradient);
  NUM_BANDS = width()/barWidth;
  if(NUM_BANDS > BAND_MAX){
    NUM_BANDS = BAND_MAX;
    barWidth = (float)width()/NUM_BANDS;
  }
  else{
    barWidth = MIN_BARWIDTH;
  }
  spectrum.resize(NUM_BANDS);
  delay.resize(NUM_BANDS);
  for(int i=0; i<NUM_BANDS; i++){
      spectrum[i]=1;
      delay[i]=1;
  }
  widgetHeight = height();
  repaint();
}

void Spectrograph::loadLevels(double left, double right){
  if(leftLevel < 5*width()/2*left)
    leftLevel = 5*width()/2*left;
  if(rightLevel < 5*width()/2*right)
    rightLevel = 5*width()/2*right;
}

void Spectrograph::paintEvent(QPaintEvent *e){
  Q_UNUSED(e);
  QPainter p(this);
  QPen pen;
  float p1x, p1y, p2x;

  p.setRenderHint(QPainter::Antialiasing);
  p.setBrush(Qt::black);
  p.drawRect(rect());
  pen.setStyle(Qt::SolidLine);
  pen.setColor(Qt::black);
  pen.setWidth(1);
  p.setPen(pen);
  for(int i=0; i<NUM_BANDS;i++){
    p1x = i*barWidth;
    p2x = p1x+barWidth;
    p1y = widgetHeight-spectrum[i];
    p.setBrush(gradientBrush);
    p.drawRect(QRectF(QPointF(p1x,p1y),QPointF(p2x,widgetHeight)));
    }
  p.setBrush(Qt::black);
  p.drawRect(0,height()-7,width(),7);
  p.setBrush(Qt::red);
  p.drawRoundedRect(width()/2-leftLevel,height()-6,leftLevel,6,3,3);
  p.setBrush(Qt::blue);
  p.drawRoundedRect(width()/2,height()-6,rightLevel,6,3,3);
  p.setPen(pen);
}

void Spectrograph::timerEvent(QTimerEvent *e){
  Q_UNUSED(e);
  for(int i=0; i<NUM_BANDS; i++){
    spectrum[i]-=delay[i];
    if(spectrum[i] <0 ){
      spectrum[i]=0;
    }
    delay[i]++;
  }
  if(leftLevel > 0)
    leftLevel--;
  if(rightLevel > 0)
    rightLevel--;
  repaint();
}

void Spectrograph::loadSamples(QVector<double> &_spectrum){
  int increment, value;
  increment = _spectrum.size()/NUM_BANDS;
  for(int i=0; i<NUM_BANDS;i++){
    value = ceil(_spectrum[i*increment]*height());
    if(value > spectrum[i]){
      spectrum[i] = value;
      delay[i] = 0;
    }
  }
  repaint();
}
