#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectToSql();
    block(false);

    model = new QSqlQueryModel;
    qry = new QSqlQuery(db);
    qryl = new QSqlQuery(db);
}

void MainWindow::connectToSql()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("E:\\Code\\test\\Qt\\kp\\kursovoi.db");
    if(db.open())
    {
        qDebug()<<"good";
    }else
    {
        qDebug() << db.lastError().text();
    }
}

void MainWindow::informationName()
{
    if(ui->labelName->text() != "admin")
    {
        qry->prepare("SELECT id, month, year, loot, drop1, drop2, drop3, drop4, drop5 FROM lddddd WHERE login ='" + ui->lineEditLogin->text() + "';");
        qry->exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        //ui->tableView->horizontalHeader()->setStretchLastSection(true);

        model->setHeaderData(0,Qt::Horizontal,tr("id"));
        model->setHeaderData(1,Qt::Horizontal,tr("Месяц"));
        model->setHeaderData(2,Qt::Horizontal,tr("Год"));
        model->setHeaderData(3,Qt::Horizontal,tr("Зарплата"));
        model->setHeaderData(4,Qt::Horizontal,tr("Одежда"));
        model->setHeaderData(5,Qt::Horizontal,tr("Транспорт"));
        model->setHeaderData(6,Qt::Horizontal,tr("Еда"));
        model->setHeaderData(7,Qt::Horizontal,tr("Хобби"));
        model->setHeaderData(8,Qt::Horizontal,tr("ЖКХ"));

        ui->tableView->setColumnHidden(0, true);

        //заполняем строки псодней щаписью
        ui->spinBoxMonth->setValue(qry->value("month").toInt());
        ui->spinBoxYear->setValue(qry->value("year").toInt());
        ui->lineEditLoot->setText(qry->value("loot").toString());
        ui->lineEditDrop1->setText(qry->value("drop1").toString());
        ui->lineEditDrop2->setText(qry->value("drop2").toString());
        ui->lineEditDrop3->setText(qry->value("drop3").toString());
        ui->lineEditDrop4->setText(qry->value("drop4").toString());
        ui->lineEditDrop5->setText(qry->value("drop5").toString());

        qDebug() << model->lastError().text();
    }else
    {
        qry->prepare("SELECT * FROM lpht;");
        qry->exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

        model->setHeaderData(0,Qt::Horizontal,tr("id"));
        model->setHeaderData(1,Qt::Horizontal,tr("login"));
        model->setHeaderData(2,Qt::Horizontal,tr("password"));
        model->setHeaderData(3,Qt::Horizontal,tr("help"));
        model->setHeaderData(4,Qt::Horizontal,tr("moneybox"));
        model->setHeaderData(5,Qt::Horizontal,tr("targetbuy"));
        model->setHeaderData(6,Qt::Horizontal,tr("target"));
    }
}

void MainWindow::block(bool status)
{
    if(ui->labelName->text() != "admin")
    {
        ui->ButtonBuyTarget->setEnabled(status);
        ui->ButtonDelete->setEnabled(status);
        ui->ButtonNewRec->setEnabled(status);
        ui->ButtonNewTarget->setEnabled(status);
        ui->ButtonReplace->setEnabled(status);
        ui->ButtonStatistics->setEnabled(status);
    }else
    {
        ui->ButtonBuyTarget->setEnabled(false);
        ui->ButtonDelete->setEnabled(false);
        ui->ButtonNewRec->setEnabled(true);
        ui->ButtonNewTarget->setEnabled(false);
        ui->ButtonReplace->setEnabled(true);
        ui->ButtonStatistics->setEnabled(false);
    }
}

void MainWindow::blockStr(bool status)
{
    QRegExp exp("[0-9]{1,7}");
    if(status)
    {
        ui->lineEditLoot->setValidator(new QRegExpValidator(exp,this));
        ui->lineEditDrop1->setValidator(new QRegExpValidator(exp,this));
        ui->lineEditDrop2->setValidator(new QRegExpValidator(exp,this));
        ui->lineEditDrop3->setValidator(new QRegExpValidator(exp,this));
        ui->lineEditDrop4->setValidator(new QRegExpValidator(exp,this));
        ui->lineEditDrop5->setValidator(new QRegExpValidator(exp,this));
    }else
    {
        ui->lineEditLoot->setValidator(0);
        ui->lineEditDrop1->setValidator(0);
        ui->lineEditDrop2->setValidator(0);
        ui->lineEditDrop3->setValidator(0);
        ui->lineEditDrop4->setValidator(0);
        ui->lineEditDrop5->setValidator(0);
    }
}

void MainWindow::moneyBoxNew(int num)
{
    //ошипка запроса
    qDebug() << num;
    qryl->prepare("UPDATE lpht SET moneybox = :mBox WHERE login = :login;");
    int temp = ui->labelMoneyBox->text().toInt() + num;

    qryl->bindValue(":mBox", temp);
    qryl->bindValue(":login", ui->labelName->text());
    qryl->exec();

    qDebug() << qryl->lastError();
}

int MainWindow::SUMMERrow(QString id)
{
    qry->prepare("SELECT loot, drop1, drop2, drop3, drop4, drop5 FROM lddddd WHERE id = :id;");
    qry->bindValue(":id", id);
    qry->exec();

    qry->first();

    int loot = qry->value("loot").toInt();
    int drop1 = qry->value("drop1").toInt();
    int drop2 = qry->value("drop2").toInt();
    int drop3 = qry->value("drop3").toInt();
    int drop4 = qry->value("drop4").toInt();
    int drop5 = qry->value("drop5").toInt();
    int result = loot-(drop1+drop2+drop3+drop4+drop5);
    qDebug() << qry->lastError();
    //qDebug() <<result;
    return result;
}

MainWindow::~MainWindow()
{
    delete model;
    delete qry;
    delete qryl;
    delete ui;
}

void MainWindow::on_ButtonEnter_clicked()
{

    qryl->prepare("SELECT login, password, help, moneybox, targetbuy, target FROM lpht;");
    qryl->exec();
    while(qryl->next())
    {
        if(ui->lineEditLogin->text()==qryl->value("login").toString())
        {
            if(ui->lineEditPassword->text()==qryl->value("password").toString())
            {
                ui->labelName->setText(ui->lineEditLogin->text());
                ui->labelPriceTarget->setText(qryl->value("targetbuy").toString());
                ui->labelMoneyBox->setText(qryl->value("moneybox").toString());
                QPixmap art = QPixmap();
                art.loadFromData(qryl->value("target").toByteArray());
                ui->labelArtTarget->setPixmap(art);

                block(true);
                //if admin
                if(ui->labelName->text() != "admin")
                {
                    blockStr(true);
                    ui->labelDrop1->setText("Drop1");
                    ui->labelDrop2->setText("Drop2");
                    ui->labelDrop3->setText("Drop3");
                    ui->labelDrop4->setText("Drop4");
                }else
                {
                    blockStr(false);
                    ui->labelDrop1->setText("!login!");
                    ui->labelDrop2->setText("!password!");
                    ui->labelDrop3->setText("!help!");
                    ui->labelDrop4->setText("!moneybox!");
                }

                ui->comboBoxTypeStatistics->clear();
                ui->comboBoxTypeStatistics->addItem(ui->labelName->text());
                ui->comboBoxTypeStatistics->addItem("all");

                informationName();
            }else QMessageBox::critical(this,"Ошипка", "неверный пароль");
        }
    }

}

void MainWindow::on_ButtonNewLogin_clicked()
{
    qryl->prepare("SELECT MAX(id) FROM lpht;");
    qryl->exec();

    qDebug() << qry->lastError();

    qryl->next();

    //id новой ячейки
    int count = qryl->value(0).toInt()+1;

    qryl->prepare("INSERT INTO lpht VALUES (:id, :login, :password, :help, :moneybox, :targetbuy, :target);");
    qryl->bindValue(":id", count);
    qryl->bindValue(":login", ui->lineEditLogin->text());
    qryl->bindValue(":password", ui->lineEditPassword->text());
    qryl->bindValue(":help", ui->lineEditPassword->text());
    qryl->bindValue(":moneybox", "");
    qryl->bindValue(":targetbuy", "");
    qryl->bindValue(":target", "");
    qryl->exec();

    qDebug() << qryl->lastError();
}

void MainWindow::on_ButtonHelpLogin_clicked()
{
    qryl->prepare("SELECT login, password, help, moneybox, targetbuy, target FROM lpht;");
    qryl->exec();
    while(qryl->next())
    {
        if(ui->lineEditLogin->text()==qryl->value("login").toString())
            QMessageBox::information(this,"Подсказка",qryl->value("help").toString());
    }
}

void MainWindow::on_ButtonNewRec_clicked()
{
    if(ui->labelName->text() != "admin")
    {
    QString name = ui->labelName->text();
    QString month = QString::number(ui->spinBoxMonth->value());
    QString year = QString::number(ui->spinBoxYear->value());
    QString loot = ui->lineEditLoot->text();
    QString drop1 = ui->lineEditDrop1->text();
    QString drop2 = ui->lineEditDrop2->text();
    QString drop3 = ui->lineEditDrop3->text();
    QString drop4 = ui->lineEditDrop4->text();
    QString drop5 = ui->lineEditDrop5->text();

    qry->prepare("SELECT MAX(id) FROM lddddd;");
    qry->exec();
    qry->next();

    //id новой ячейки
    int count = qry->value(0).toInt()+1;

    qry->prepare("INSERT INTO lddddd VALUES (:id, :login, :month, :year, :loot, :drop1, :drop2, :drop3, :drop4, :drop5);");
    qry->bindValue(":id", count);
    qry->bindValue(":login", name);
    qry->bindValue(":month", month);
    qry->bindValue(":year", year);
    qry->bindValue(":loot", loot);
    qry->bindValue(":drop1", drop1);
    qry->bindValue(":drop2", drop2);
    qry->bindValue(":drop3", drop3);
    qry->bindValue(":drop4", drop4);
    qry->bindValue(":drop5", drop5);
    qry->exec();

    moneyBoxNew(SUMMERrow(QString::number(count)));

    //informationName();
    on_ButtonEnter_clicked();
    qDebug() << qry->lastError();

    }else{
        qryl->prepare("SELECT MAX(id) FROM lpht;");
        qryl->exec();

        qDebug() << qry->lastError();

        qryl->next();

        //id новой ячейки
        int count = qryl->value(0).toInt()+1;

        qryl->prepare("INSERT INTO lpht VALUES (:id, :login, :password, :help, :moneybox, :targetbuy, :target);");
        qryl->bindValue(":id", count);
        qryl->bindValue(":login", "");
        qryl->bindValue(":password", "");
        qryl->bindValue(":help", "");
        qryl->bindValue(":moneybox", "");
        qryl->bindValue(":targetbuy", "");
        qryl->bindValue(":target", "");
        qryl->exec();


        on_ButtonEnter_clicked();
        qDebug() << qryl->lastError();
    }
}

void MainWindow::on_ButtonReplace_clicked()
{
    if(ui->labelName->text() != "admin")
    {
        //находим id выделеноий строки
        QString idRow = model->data(model->index(ui->tableView->currentIndex().row(),0),Qt::DisplayRole).toString();

        int before = SUMMERrow(idRow);

        QString month = QString::number(ui->spinBoxMonth->value());
        QString year = QString::number(ui->spinBoxYear->value());
        QString loot = ui->lineEditLoot->text();
        QString drop1 = ui->lineEditDrop1->text();
        QString drop2 = ui->lineEditDrop2->text();
        QString drop3 = ui->lineEditDrop3->text();
        QString drop4 = ui->lineEditDrop4->text();
        QString drop5 = ui->lineEditDrop5->text();

        int after = loot.toInt() - (drop1.toInt() + drop2.toInt()+drop3.toInt()+drop4.toInt()+drop5.toInt());

        qry->prepare("UPDATE lddddd SET month = :month, year = :year, loot = :loot, drop1 = :drop1, drop2 = :drop2, drop3 = :drop3, drop4 = :drop4, drop5 = :drop5 WHERE id = :id;");

        qry->bindValue(":id",idRow);
        qry->bindValue(":month", month);
        qry->bindValue(":year", year);
        qry->bindValue(":loot", loot);
        qry->bindValue(":drop1", drop1);
        qry->bindValue(":drop2", drop2);
        qry->bindValue(":drop3", drop3);
        qry->bindValue(":drop4", drop4);
        qry->bindValue(":drop5", drop5);
        qry->exec();

        moneyBoxNew(after - before);

        //informationName();
        on_ButtonEnter_clicked();

        qDebug() << qry->lastError();
    }else
    {
        //находим id выделеноий строки
        QString idRow = model->data(model->index(ui->tableView->currentIndex().row(),0),Qt::DisplayRole).toString();

        QString login = ui->lineEditDrop1->text();
        QString password = ui->lineEditDrop2->text();
        QString help = ui->lineEditDrop3->text();
        QString moneybox = ui->lineEditDrop4->text();

        qryl->prepare("UPDATE lpht SET login = :login, password = :password, help = :help, moneybox = :moneybox WHERE id = :id;");

        qryl->bindValue(":id",idRow);
        qryl->bindValue(":login", login);
        qryl->bindValue(":password", password);
        qryl->bindValue(":help", help);
        qryl->bindValue(":moneybox", moneybox);
        qryl->exec();
    }
}

void MainWindow::on_ButtonDelete_clicked()
{
    QString idRow = model->data(model->index(ui->tableView->currentIndex().row(),0),Qt::DisplayRole).toString();
    QMessageBox::StandardButton bYes;
    bYes = QMessageBox::question(this,"Удаление","Удалить строку?!",
            QMessageBox::Yes|QMessageBox::No);
   if(bYes == QMessageBox::Yes)
   {
       moneyBoxNew(-1*SUMMERrow(idRow));

       //удаление строки
       qry->prepare("DELETE FROM lddddd WHERE id = :idRow");
       qry->bindValue(":idRow",idRow);
       qry->exec();

       //informationName();
       on_ButtonEnter_clicked();
       qDebug() << qry->lastError();
   }
}

void MainWindow::on_ButtonBuyTarget_clicked()
{
    int price = ui->labelPriceTarget->text().toInt();
    int moneyBox = ui->labelMoneyBox->text().toInt();
    if(price <= moneyBox)
    {
        moneyBoxNew(-1*price);
    }else QMessageBox::information(this,"Ошипка","Недостаточно средств");
    on_ButtonEnter_clicked();
}

void MainWindow::on_ButtonNewTarget_clicked()
{
    Dialog dial(db,ui->labelName->text());
    dial.exec();

    on_ButtonEnter_clicked();
}

void MainWindow::on_ButtonStatistics_clicked()
{
    DStatistics dstats(db,ui->comboBoxTypeStatistics->currentText());
    qDebug() << ui->comboBoxTypeStatistics->currentText();
    dstats.exec();
}
