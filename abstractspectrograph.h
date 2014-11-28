#ifndef ABSTRACTSPECTROGRAPH_H
#define ABSTRACTSPECTROGRAPH_H

#include <QWidget>
#include <QVector>

// the spectrum visualization widget
/**
 * @brief The AbstractSpectrograph class provides a generic interface for a
 * spectrograph drawing widget
 * @details Periodically, mainwindows calculates somewhere a FFT transform of audio
 * input signal and extracts its spectrum. This spectrum may be offered to objects of
 * subclasses of AbstractSpectrograph for drawing nice things
 *
 * Moreover, left and audio mean levels are also communicated, so level bars (or something
 * like that) can be drawn.
 */
class AbstractSpectrograph : public QWidget{
  Q_OBJECT
public:
  /**
   * @brief AbstractSpectrograph constructor only inform the widget who is its parent
   * @param parent is the pointer to parent widget (it is supposed to be the place
     * where this widget has to be drawn)
   */
  explicit AbstractSpectrograph(QWidget *parent):QWidget(parent){}

signals:

public slots:
  // load the spectrum to be displayed
  /**
   * @brief loadSamples should be used to load the spectrum to be displayed
   */
  virtual void loadSamples(QVector<double>&)=0;

  //
  /**
   * @brief loadLevels should be used to load left and right mean audio levels
   */
    virtual void loadLevels(double, double)=0;
};

#endif // ABSTRACTSPECTROGRAPH_H
