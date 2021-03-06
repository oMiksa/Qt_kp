#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QBuffer>
#include <QImage>
#include <QFileDialog>
#include <QSqlError>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QSqlDatabase db, QString login, QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButtonClose_clicked();

    void on_pushButtonOk_clicked();

    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    QSqlQuery *qry;
    QString name;
    QByteArray image;
};

#endif // DIALOG_H
