#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QSqlDatabase db, QString login, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    qry = new QSqlQuery(db);

    QRegExp exp("[0-9]{1,7}");
    ui->lineEditPrice->setValidator(new QRegExpValidator(exp,this));

    name = login;
    if(db.open())
    {
        qDebug() << "good";
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButtonClose_clicked()
{
    close();
}

void Dialog::on_pushButtonOk_clicked()
{
    qry->prepare("UPDATE lpht SET targetbuy = :tb, target = :t WHERE login = :name;");
    qry->bindValue(":name", name);
    qry->bindValue(":tb", ui->lineEditPrice->text());
    qry->bindValue(":t", image);
    qry->exec();
    qDebug() << qry->lastError();
    this->close();
}

void Dialog::on_pushButton_clicked()
{
    QString pic = QFileDialog::getOpenFileName(this);
    if(!pic.isEmpty())
    {
        QFile fpix(pic);
        fpix.open(QFile::ReadWrite);
        image = fpix.readAll();
    }
}
