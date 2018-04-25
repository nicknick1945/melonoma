#ifndef FEATURE_TABLES_H
#define FEATURE_TABLES_H

#include <QMainWindow>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include "platform_headers/defaultwidget.h"
namespace Ui {
    class feature_tables;
}

class feature_tables : public DefaultWidget
{
    Q_OBJECT

public:
    QString* getWidgetName();
    explicit feature_tables(QWidget *parent = 0);
    ~feature_tables();

private slots:
    void on_pushButton_creating_globules_table_clicked();
    void on_pushButton_for_insert_clicked();
    void on_pushButton_creating_hair_table_clicked();
private:
    Ui::feature_tables *ui;
    //vector for saving data from another parts of programm
      std::vector<double> globules_charact;
      std::vector<double> hair_charact;
      std::vector<double> cell_charact;
      std::vector<double> grid_charact;
      std::vector<double> birthmark_charact;
      QSqlDatabase db, db1, db2, db3, db4;
      QSqlTableModel* model;
      QSqlTableModel* model1;
      QSqlTableModel* model2;
      QSqlTableModel* model3;
      QSqlTableModel* model4;
};

#endif // FEATURE_TABLES_H
