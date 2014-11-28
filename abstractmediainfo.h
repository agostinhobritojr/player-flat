#ifndef ABSTRACTMEDIAINFO_H
#define ABSTRACTMEDIAINFO_H

#include <QWidget>
#include <QString>
// class to display media info
class AbstractMediaInfo : public QWidget{
  Q_OBJECT
public:
  /**
   * @brief AbstractMediaInfo constructor only inform the widget who is its parent
   * @param parent is the pointer to parent widget (it is supposed to be the place
     * where this widget has to be drawn)
   */

  explicit AbstractMediaInfo(QWidget *parent = 0):QWidget(parent){}

public slots:
  /**
   * @brief setAtribute receives a pair property/value from mainwindow widget
   * @details Stuff like artists, album title and music title are communicated to this slot
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
    virtual void setAtribute(QString property, QString value)=0;
};

#endif // ABSTRACTMEDIAINFO_H
