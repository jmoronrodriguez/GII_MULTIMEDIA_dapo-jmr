#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"
#include <QtWidgets>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QMediaMetaData>
VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);
    player = new QMediaPlayer();
    playlist = new QMediaPlaylist(player);
    player->setPlaylist(playlist);
    play=false;
    ui->cmd_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->cmd_stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->cmd_sig->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->cmd_anterior->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));

    connect(player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
    connect(player, SIGNAL(metaDataChanged()), this, SLOT(updateInfo()));
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
    delete player;
    delete playlist;
}
/**
 * Funcion que añade a la playlist las distintas canciones al abrir*/
void VentanaPrincipal::on_cmd_abrir_clicked()
{
    static QString path = QDir::homePath();
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Files"), path, tr("MP3 files (*.mp3);;All files (*.*)"));
    if (!fileNames.isEmpty()){
        foreach (QString const &argument, fileNames) {
            QFileInfo fileInfo(argument);
            if (fileInfo.exists()) {
                QUrl url = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
                if (fileInfo.suffix().toLower() == QLatin1String("m3u")) {
                    playlist->load(url);
                } else
                    playlist->addMedia(url);
            } else {
                QUrl url(argument);
                if (url.isValid()) {
                    playlist->addMedia(url);
                }
            }
        }
        if (!play){
            player->play();
            ui->cmd_play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        }
        updateInfo();
    }
}
void VentanaPrincipal::seek(int seconds)
{
    player->setPosition(seconds * 1000);
}
void VentanaPrincipal::updateInfo(){
    ui->horizontalSlider->setRange(0, player->duration() / 1000);
    QStringList info;
    QString author = player->metaData(QMediaMetaData::AlbumArtist).toString();
    if (!author.isEmpty())
        info += author;
    QString title = player->metaData(QMediaMetaData::Title).toString();
    if (!title.isEmpty())
        info += title;
    if (!info.isEmpty()){
        ui->lbl_cancion->setText(info.join(tr(" - ")));
        ui->centralWidget->setWindowTitle(info.join(tr(" - ")));
    }
}

void VentanaPrincipal::on_cmd_play_clicked()
{
    updateInfo();
    if (play){
        player->play();
        ui->cmd_play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        play=false;
    }else{
        player->pause();
        ui->cmd_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        play=true;
    }
}

void VentanaPrincipal::on_cmd_stop_clicked()
{
    player->stop();
    play=true;
    ui->cmd_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}

void VentanaPrincipal::updateDurationInfo(qint64 currentInfo)
{
    /*QString tStr;
    if (currentInfo || duration) {
        QTime currentTime((currentInfo/3600)%60, (currentInfo/60)%60, currentInfo%60, (currentInfo*1000)%1000);
        QTime totalTime((duration/3600)%60, (duration/60)%60, duration%60, (duration*1000)%1000);
        QString format = "mm:ss";
        if (duration > 3600)
            format = "hh:mm:ss";
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }*/
    //labelDuration->setText(tStr);
}

void VentanaPrincipal::positionChanged(qint64 progress){
    if (!ui->horizontalSlider->isSliderDown()) {
        ui->horizontalSlider->setValue(progress / 1000);
    }
    //updateDurationInfo(progress / 1000);

}
void VentanaPrincipal::on_cmd_sig_clicked()
{

        playlist->next();
        updateInfo();

}

void VentanaPrincipal::on_cmd_anterior_clicked()
{

        playlist->previous();
        updateInfo();

}
