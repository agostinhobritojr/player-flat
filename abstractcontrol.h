#ifndef ABSTRACTCONTROL_H
#define ABSTRACTCONTROL_H

#include <QWidget>

// this is the abstract class to implement audio controls

/**
 * @brief The AbstractControl class provides an generic interface for controls widgets
 * @details The user may maintain several instances of different widgets for controlling the user interface
 *
 * When some of these widgets are activated, it state may be communicated to other widgets. For this reason,
 * this class provides public slots to receive such information.
 *
 * It also provides information to tell other widgets that user events has arrived
 */
class AbstractControl : public QWidget{
private:
  Q_OBJECT
public:
  // constructor does nothing
  /**
   * @brief AbstractControl constructor only inform the widget who is its parent
   * @param parent is the pointer to parent widget (it is supposed to be the place
     * where this widget has to be drawn)
   */
  explicit AbstractControl(QWidget *parent = 0):QWidget(parent){}

public slots:
  /**
   * @brief onPlayPauseClicked should be activated when the user presses play/pause button
   */
  virtual void onPlayPauseClicked(void)=0;

  /**
   * @brief onPrevClicked should be activated when the user presses prev button
   */
  virtual void onPrevClicked(void)=0;

  /**
   * @brief onNextClicked should be activated when the user presses next button
   */
  virtual void onNextClicked(void)=0;

  // someone changed the volume somewhere
  /**
   * @brief onVolumeChanged should be activated when the user changes the volume
   * @param value receives the volume in range [0-100] (percent)
   */
  virtual void onVolumeChanged(int value)=0;

  // elapsed time has changed somewhere
  /**
   * @brief onElapsedChanged should be activated when the user changes the stream
   * position for current media being played (e.g., using a scrollbar)
   * @param value the value of the current position in range [0-100] (percent)
   */
  virtual void onElapsedChanged(qint64 value)=0;

 // void myElapsedChanged(int)=0;
  /**
   * @brief onDurationChanged should be activated when a new media arrives on the player
   * @details Once the player retrieves the media total elapsing time, it tells this
   * information to Qt. We can display it using some nice widget.
   * @param value stores the total playing time for current media in milisseconds.
   */
  virtual void onDurationChanged(qint64 value)=0;

signals:
  /**
   * @brief playPause should tell when someone has pressed play/pause button
   */
  void playPause();

  /**
   * @brief next should tell when someone has pressed next button
   */
  void next();

  /**
   * @brief prev should tell when someone has pressed prev button
   */
  void prev();

  // tells when user pressed stop button
  /**
   * @brief stop should tell when someone has pressed stop button
   */
  void stop();

  // tells when user changed volume
  /**
   * @brief volumeSelected should tell when someone has selected a new volume
   */
  void volumeSelected(int);

  // tells when user change music position
  /**
   * @brief elapsedSelected should tell when someone has selected a new position to play
   */
  void elapsedSelected(qint64);
};

#endif // ABSTRACTCONTROL_H
