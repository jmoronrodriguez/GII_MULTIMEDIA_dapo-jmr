#ifndef LISTA_H
#define LISTA_H

#include <QDialog>

namespace Ui {
class lista;
}

class lista : public QDialog
{
    Q_OBJECT

public:
    explicit lista(QWidget *parent = 0);
    ~lista();

private:
    Ui::lista *ui;
};

#endif // LISTA_H
