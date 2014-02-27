#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
namespace Ui {
class VentanaPrincipal;
}

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit VentanaPrincipal(QWidget *parent = 0);
    ~VentanaPrincipal();

private slots:
    void on_cmd_abrir_clicked();
    void updateInfo();
    void positionChanged(qint64 progress);
    void on_cmd_play_clicked();

    void on_cmd_stop_clicked();

    void on_cmd_sig_clicked();
     void seek(int seconds);
     void on_cmd_anterior_clicked();

private:
    Ui::VentanaPrincipal *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    bool play;
    void updateDurationInfo(qint64 currentInfo);
    qint64 duration;
};

#endif // VENTANAPRINCIPAL_H
