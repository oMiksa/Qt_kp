#ifndef DSTATISTICS_H
#define DSTATISTICS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlError>


namespace Ui {
class DStatistics;
}

class DStatistics : public QDialog
{
    Q_OBJECT

public:
    explicit DStatistics(QSqlDatabase db, QString login, QWidget *parent = 0);
    ~DStatistics();

private slots:
    void on_ButtonClose_clicked();

private:
    Ui::DStatistics *ui;
    QSqlQuery *qry;
    QSqlQueryModel *model;
    QString name;
};

#endif // DSTATISTICS_H
