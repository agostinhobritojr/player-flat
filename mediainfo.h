#ifndef MEDIAINFO_H
#define MEDIAINFO_H
#include "abstractmediainfo.h"

#include <QWidget>
#include <QString>
#include <QStandardItemModel>
#include <QStandardItem>

namespace Ui {
class MediaInfo;
}

/**
 * @brief The MediaInfo class is supposed to be able to display
 * information about the current media that is been played
 * @details It receives several properties that are extracted from
 * the current media available on media player
 */
class MediaInfo : public AbstractMediaInfo
{
  Q_OBJECT

public:
  /**
   * @brief Class constructor to perform initial setups
   * @param parent is the pointer to parent widget (it is supposed to be the place where this
   * widget has to be drawn)
   */
  explicit MediaInfo(QWidget *parent = 0);

  /** @brief Class destructor
    */
  ~MediaInfo();

public slots:
  /**
   * @brief setAtribute receives a pair property/value from mainwindow widget
   * @param property receives a string that may hold the following values:
   * - "AlbumArtist" : the album artist
   * - "Title": music title
   * - "AlbumTitle": album title
   * - "TrackNumber": track number
   * - "AudioBitRate": song bitrate
   * - "AudioCodec": song codec

   * @param value receives the information associated to its corresponding property
   * ex: "AlbumArtist" <==> "Elton Jonh"
   */
  void setAtribute(QString property, QString value);
private:
  /**
   * @brief ui access the form that draws the controls user interface
   */
  Ui::MediaInfo *ui;
  /**
   * @brief some handsome strings to store your information
   */
  QString artist, title, album, bitrate, codec, track;
};

#endif // MEDIAINFO_H
