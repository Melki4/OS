#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QPixmap pix_barber_main("D:/Загрузки/77f02bcd-b1af-43ec-96dc-9d0dd707629b.png");
    QPixmap pix_barber_brother("D:/Загрузки/77f02bcd-b1af-43ec-96dc-9d0dd707629b (1).png");

    ui->barber_main->setPixmap(pix_barber_main);
    ui->barber_main->setScaledContents(true);

    ui->barber_brother->setPixmap(pix_barber_brother);
    ui->barber_brother->setScaledContents(true);
}

Dialog::~Dialog()
{
    delete ui;
}