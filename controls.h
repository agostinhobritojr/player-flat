#ifndef CONTROLS_H
#define CONTROLS_H
#include "abstractcontrol.h"

#include <QTime>

namespace Ui {
class Controls;
}
/**
 * @brief The Controls class provides support to user control
 * @details This class allows to programm the interface for
 * dealing with play/pause/prev/next/volume/elapsed time commands
 */
class Controls : public AbstractControl{
    Q_OBJECT
public:
  /**
     * @brief Class constructor
     * @param The pointer to parent widget (it is supposed to be the place
     * where this widget has to be drawn)
     */
    explicit Controls(QWidget *parent = 0);

  /**
    * @brief Class destructor, to clean up some mess
    */
    ~Controls();
    
private:
  /**
    * @brief ui access the form that draws the controls user interface
    */
    Ui::Controls *ui;

    /**
     * @brief duration stores the total amount of time of current media
     * that is playing
     */
    qint64 duration;
public slots:
    /**
     * @brief onPlayPauseClicked is activated when the user presses the play/pause button
     */
    void onPlayPauseClicked(void);
    /**
     * @brief onPrevClicked is activated when the user presses prev button
     */
    void onPrevClicked(void);
    /**
     * @brief onNextClicked is activated when the user presses next button
     */
    void onNextClicked(void);
    /**
     * @brief onVolumeChanged is activated when the user turns the dial button
     * @param value is passed to this function by some valueChanged signal
     */
    void onVolumeChanged(int value);
    /**
     * @brief onElapsedChanged is signal activated periodically by mainwindow widget
     * @details every a new part of the song is played, the stream position changes.
     * This position is comunicated to controls widget using some specific signal
     * @param value
     */
    void onElapsedChanged(qint64 value);
    /**
     * @brief onDurationChanged slot is called when a new media arives from the playlist
     * @details When a new media starts to play, mainwindow tells this widget the total amount
     * of time associated to this media.
     * @param value stores the amount of time for the current media
     */
    void onDurationChanged(qint64 value);
protected slots:
    void onSliderReleased();
signals:
    void playPause();
    void next();
    void prev();
    void stop();
    void volumeSelected(int);
    void elapsedSelected(qint64);
};

#endif // CONTROLS_H
