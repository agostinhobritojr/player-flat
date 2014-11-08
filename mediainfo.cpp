#include "mediainfo.h"
#include "ui_mediainfo.h"
#include <QDebug>

MediaInfo::MediaInfo(QWidget *parent) :
  AbstractMediaInfo(parent),
  ui(new Ui::MediaInfo){
  ui->setupUi(this);
}

MediaInfo::~MediaInfo(){
  delete ui;
}

// this function just assemble a large string with all information
// that is passed. you should modify it for your needs
void MediaInfo::setAtribute(QString property, QString value){
  QString text;
  if(property == "AlbumArtist")
    artist = value;
  if(property == "Title")
    title = value;
  if(property == "AlbumTitle")
    album = value;
  if(property == "TrackNumber")
    track = value;
  if(property == "AudioBitRate")
    bitrate = value;
  if(property == "AudioCodec")
    codec = value;
  text = artist+"/"+title+"/"+
      album+"/"+track+"/"+
      bitrate+"/"+codec;

  // just display the text into the label :P
  ui->label->setText(text);
}
