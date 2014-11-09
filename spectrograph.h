#ifndef SPECTROGRAPH_H
#define SPECTROGRAPH_H
#include "abstractspectrograph.h"

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QAudioBuffer>
#include <complex>
#include <QVector>
#include <QDebug>
#include <QTimer>
#include <QGradient>
#include <QAction>

// spectrograph class is used to display fourier spectrum
// bars
class Spectrograph : public AbstractSpectrograph{
  Q_OBJECT
public:
  /**
   * @brief Spectrograph Class constructor. Setup initial behavior for the widget
   * @param parent pointer to widget parent
   *
   */
  explicit Spectrograph(QWidget *parent = 0);

signals:

public slots:
  /**
   * @brief paintEvent Paints the screen for spectrum displaing
   * @param e stores information about the painting event
   */
  void paintEvent(QPaintEvent *e);
  /*!brief Load samples to be displayed
  */
  void loadSamples(QVector<double> &_spectrum);
  /**
   * @brief timerEvent
   * Used to modify spectrum while a new sample
   * does not arrive
   * @param e
   */
  void timerEvent(QTimerEvent *e);

  /**
   * @brief resizeEvent what to do when widget size changes
   * it is used to recalculate the width of the bars and some gradient colors
   * @param e stores information about resize event
   */
  void resizeEvent(QResizeEvent *e);

  /**
   * @brief contextMenuEvent Open context menu when user clicks on the component using mouse right button
   * @param e
   */
  void contextMenuEvent(QContextMenuEvent *e);

  /**
   * @brief loadLevels Loads mean left and right audio channel values
   * @param left left mean audio value
   * @param right right mean audio value
   */
  void loadLevels(double left, double right);

  /**
   * @brief doAction Do some example action when user activates context menu
   */
  void doAction();
private:
  /**
   * @brief spectrum stores fft spectrum
   */
  QVector<int> spectrum;
  /**
   * @brief delay stores the delay for decay bars to simulate gravity
   */
  QVector<int> delay;

  /**
   * @brief leftLevel left level bar size
   * @brief rightLevel right level bar size
   */
  int leftLevel, rightLevel;
  /**
   * @brief NUM_BANDS number of spectrum bands (MAX=512!!!)
   */
  int NUM_BANDS;
  /**
   * @brief gradient defines the gradient for drawing the spectrum bars
   */
  QLinearGradient gradient;
  /**
   * @brief gradientBrush brush for drawing the gradient patterns
   * @brief backgroundBrush brush for drawing the background pattern
   */
  QBrush gradientBrush, backgroundBrush;
  /**
   * @brief pen default pen for drawing lines
   */
  QPen pen;
  /**
   * @brief barSpacing spacing between spectrum bars. Usually, just one pixel
   */
  float barSpacing, barWidth, widgetHeight;
  QAction *acao;
};

#endif // SPECTROGRAM_H
