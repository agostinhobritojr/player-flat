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
/**
 * @brief The Spectrograph class is used to draw the fourier spectrum on the screen.
 * @details It periodically receives an array containing the spectrum with values
 * scaled within the range [0,1], and the left and right mean audio values
 */
class Spectrograph : public AbstractSpectrograph{
  Q_OBJECT
public:
  /**
   * @bparent is the pointer to parent widget (it is supposed to be the place where this
   * widget has to be drawn)rief Class constructor. Setup initial behavior for the widget
   * @param
   *
   */
  explicit Spectrograph(QWidget *parent = 0);

signals:

public slots:
  /**
   * @brief Paints the screen for spectrum displaing
   * @param e stores information about the painting event
   */
  void paintEvent(QPaintEvent *e);

  /**
   * @brief This method decides what to do when a new spectrum sample
   * has arrived.
   * @detailed This method is called periodically by mainwindow every time a
   * new spectrum is calculated. the _spectrum array reference stores double values
   * within the range [0,1] and it has 256 elements.
   * @param _spectrum stores the spectrum.
   */
  void loadSamples(QVector<double> &_spectrum);

  /**
   * @brief Used to modify spectrum while a new sample does not arrive
   * @param e
   */
  void timerEvent(QTimerEvent *e);

  /**
   * @brief What to do when widget size changes
   * @details It is used to recalculate the width of the bars and
   * some gradient colors
   * @param e stores information about resize event
   */
  void resizeEvent(QResizeEvent *e);

  /**
   * @brief Open context menu
   * @details This is what is called when user clicks on the
   * component using mouse right button
   * @param e This event is used to return the position of mouse click
   * when the context menu is activated
   */
  void contextMenuEvent(QContextMenuEvent *e);

  /**
   * @brief Loads mean left and right audio channel values
   * @details This method is invoked by mainwindow component
   * every time a new audio sample is processed, supplying left
   * and right mean audio values
   *
   * It also performs some scaling for better display purposes

   * @param left left mean audio value
   * @param right right mean audio value
   */
  void loadLevels(double left, double right);

  /**
   * @brief Do some example action when user activates context menu
   * @details You can add new of such functions to allow new context
   * menu entries
   */
  void doAction();
private:
  /**
   * @brief Stores the fft spectrum.
   * @details spectrum is an array that should have a MAXIMUM of 256 entries.
   * You should not trespass this limit
   */
  QVector<int> spectrum;
  /**
   * @brief Stores the delay for decay bars to simulate gravity
   */
  QVector<int> delay;

  /**
   * @brief Left and right level bar size
   */
  int leftLevel, rightLevel;
  /**
   * @brief Number of spectrum bands (MAX=256!!!)
   */
  int NUM_BANDS;
  /**
   * @brief Holds the gradient for drawing the spectrum bars
   */
  QLinearGradient gradient;
  /**
   * @brief Brushes for drawing the gradient and background patterns
   */
  QBrush gradientBrush, backgroundBrush;
  /**
   * @brief A pen for drawing lines
   */
  QPen pen;
  /**
   * @brief Spacing between spectrum bars. Usually, just one pixel
   */
  float barSpacing, barWidth, widgetHeight;
  QAction *acao;
};

#endif // SPECTROGRAM_H
