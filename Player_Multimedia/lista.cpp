#include "lista.h"
#include "ui_lista.h"

lista::lista(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lista)
{
    ui->setupUi(this);
    ui->lst_playlist;
}

lista::~lista()
{
    delete ui;
}
