#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <typeinfo>

#include "dialog.h"
#include "dstatistics.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void connectToSql();
    void informationName();
    void reBuild();
    void block(bool status);
    void blockStr(bool status);
    void moneyBoxNew(int num);
    int SUMMERrow(QString id);
    ~MainWindow();

private slots:
    void on_ButtonEnter_clicked();

    void on_ButtonNewLogin_clicked();

    void on_ButtonHelpLogin_clicked();

    void on_ButtonNewRec_clicked();

    void on_ButtonReplace_clicked();

    void on_ButtonDelete_clicked();

    void on_ButtonBuyTarget_clicked();

    void on_ButtonNewTarget_clicked();

    void on_ButtonStatistics_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQueryModel *model;
    QSqlQuery *qry;
    QSqlQuery *qryl;
    QSqlQuery *qryRE;
};

#endif // MAINWINDOW_H
