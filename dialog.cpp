#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QSqlDatabase db, QString login, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

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
//    QPixmap img;
//    QByteArray *qByteArray = new QByteArray();
//    QBuffer *qBuffer = new QBuffer(qByteArray, this);
//    if(img.byteCount()!=0)
//    {
//      qBuffer->open(QIODevice::WriteOnly);
//      img.save(qBuffer,"JPG");
//      qBuffer->close();
//    }

    qry->prepare("UPDATE lpht SET targetbuy = :tb, target = :t WHERE login = :name;");
    qry->bindValue(":name", name);
    qry->bindValue(":tb", ui->lineEditPrice->text());
    //qry->bindValue(":t",QByteArray("C:/Users/Miksa/Desktop/"+ui->lineEditTarget->text()+".jpg"));
    //как записать картинку?!
}
