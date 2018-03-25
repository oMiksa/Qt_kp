#include "dstatistics.h"
#include "ui_dstatistics.h"

DStatistics::DStatistics(QSqlDatabase db, QString login, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DStatistics)
{
    ui->setupUi(this);

    name = login;

    if(db.open())
    {
        qDebug() << "good";
    }

    if(name != "all")
    {
        model = new QSqlQueryModel;
        qry = new QSqlQuery(db);
        qry->prepare("SELECT SUM(loot), SUM(drop1), SUM(drop2), SUM(drop3), SUM(drop4), SUM(drop5) FROM lddddd WHERE login ='" + name + "';");
        qry->exec();

        qDebug() << qry->lastError();

        model->setQuery(*qry);
        ui->tableView->setModel(model);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

        model->setHeaderData(0,Qt::Horizontal,tr("Зарплата"));
        model->setHeaderData(1,Qt::Horizontal,tr("Одежда"));
        model->setHeaderData(2,Qt::Horizontal,tr("Транспорт"));
        model->setHeaderData(3,Qt::Horizontal,tr("Еда"));
        model->setHeaderData(4,Qt::Horizontal,tr("Хобби"));
        model->setHeaderData(5,Qt::Horizontal,tr("ЖКХ"));

        qDebug() << model->lastError().text();

    }else
    {
        model = new QSqlQueryModel;
        qry = new QSqlQuery(db);
        qry->prepare("SELECT SUM(loot), SUM(drop1), SUM(drop2), SUM(drop3), SUM(drop4), SUM(drop5) FROM lddddd ;");
        qry->exec();

        qDebug() << qry->lastError();

        model->setQuery(*qry);
        ui->tableView->setModel(model);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

        model->setHeaderData(0,Qt::Horizontal,tr("Зарплата"));
        model->setHeaderData(1,Qt::Horizontal,tr("Одежда"));
        model->setHeaderData(2,Qt::Horizontal,tr("Транспорт"));
        model->setHeaderData(3,Qt::Horizontal,tr("Еда"));
        model->setHeaderData(4,Qt::Horizontal,tr("Хобби"));
        model->setHeaderData(5,Qt::Horizontal,tr("ЖКХ"));



        qDebug() << model->lastError().text();

    }



}

DStatistics::~DStatistics()
{
    delete qry;
    delete model;
    delete ui;
}

void DStatistics::on_ButtonClose_clicked()
{
    close();
}
