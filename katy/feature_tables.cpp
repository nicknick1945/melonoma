#include "feature_tables.h"
#include "ui_feature_tables.h"

QString *feature_tables::getWidgetName()
{
    QString *widgetName = new QString("kates widget");
    return widgetName;
}

feature_tables::feature_tables(QWidget *parent) :
    DefaultWidget(parent),
    ui(new Ui::feature_tables)
{
    ui->setupUi(this);
    int a  = cache->b;
    showMaximized();
    // ///////creating of zero table for globules
          db = QSqlDatabase::addDatabase("QSQLITE");
          db.setDatabaseName("globules");
          if (!db.open()){
              qDebug()<< db.lastError().text();
              return;
          }
          else {
              qDebug()<<"Success_0!";
          }
   // ///////creating of first table for hair
          db1 = QSqlDatabase::addDatabase("QSQLITE");
          db1.setDatabaseName("hair");
          if (!db1.open()){
              qDebug()<< db1.lastError().text();
              return;
           }
          else {
              qDebug()<<"Success_1!";
           }
    // ///////creating of second table for cell
          db2 = QSqlDatabase::addDatabase("QSQLITE");
          db2.setDatabaseName("cell");
          if (!db2.open()){
              qDebug()<< db2.lastError().text();
              return;
          }
          else {
              qDebug()<<"Success_2!";
          }
    // ///////creating of third table for grid
          db3 = QSqlDatabase::addDatabase("QSQLITE");
          db3.setDatabaseName("grid");
          if (!db3.open()){
              qDebug()<< db3.lastError().text();
              return;
          }
          else {
              qDebug()<<"Success_3!";
          }
          // ///////creating of fourth table for all area of birthmark
          db4 = QSqlDatabase::addDatabase("QSQLITE");
          db4.setDatabaseName("birthmark");
          if (!db4.open()){
              qDebug()<< db4.lastError().text();
              return;
          }
          else {
              qDebug()<<"Success_4!";
          }
}

void feature_tables::on_pushButton_creating_globules_table_clicked()
{
    QSqlQuery qglobules = QSqlQuery(db);

    qglobules.prepare("CREATE TABLE IF NOT EXISTS globules ( id INTEGER PRIMARY KEY AUTOINCREMENT, picture_id VARCHAR (800), globule_attribute_1 VARCHAR(100), globule_attribute_2 VARCHAR(800), globule_attribute_3 VARCHAR(800), globule_attribute_4 VARCHAR(800), globule_attribute_5 VARCHAR(800), globule_attribute_6 VARCHAR(800), globule_attribute_7 VARCHAR(800), globule_attribute_8 VARCHAR(800))");
    qglobules.exec();

    if(!qglobules.exec())
    {
        qDebug()<< "Failed to create table globules";
    }
}

void feature_tables::on_pushButton_creating_hair_table_clicked()
{
    QSqlQuery qhair = QSqlQuery(db1);

    qhair.prepare("CREATE TABLE IF NOT EXISTS hair ( id INTEGER PRIMARY KEY AUTOINCREMENT, picture_id VARCHAR (800), hair_attribute_1 VARCHAR(100), hair_attribute_2 VARCHAR(800), hair_attribute_3 VARCHAR(800), hair_attribute_4 VARCHAR(800), hair_attribute_5 VARCHAR(800), hair_attribute_6 VARCHAR(800), hair_attribute_7 VARCHAR(800), hair_attribute_8 VARCHAR(800))");
    qhair.exec();

    if(!qhair.exec())
    {
        qDebug()<< "Failed to create table hair";
    }
}
//void feature_tables::on_pushButton_creating_cell_table_clicked()
//{
//    QSqlQuery qcell = QSqlQuery(db2);

//    qcell.prepare("CREATE TABLE IF NOT EXISTS cell ( id INTEGER PRIMARY KEY AUTOINCREMENT, picture_id VARCHAR (800), cell_attribute_1 VARCHAR(100), cell_attribute_2 VARCHAR(800), cell_attribute_3 VARCHAR(800), cell_attribute_4 VARCHAR(800), cell_attribute_5 VARCHAR(800), cell_attribute_6 VARCHAR(800), cell_attribute_7 VARCHAR(800), cell_attribute_8 VARCHAR(800))");
//    qcell.exec();

//    if(!qcell.exec())
//    {
//        qDebug()<< "Failed to create table cell";
//    }
//}
//void feature_tables::on_pushButton_creating_grid_table_clicked()
//{
//    QSqlQuery qgrid = QSqlQuery(db3);

//    qgrid.prepare("CREATE TABLE IF NOT EXISTS grid ( id INTEGER PRIMARY KEY AUTOINCREMENT, picture_id VARCHAR (800), grid_attribute_1 VARCHAR(100), grid_attribute_2 VARCHAR(800), grid_attribute_3 VARCHAR(800), grid_attribute_4 VARCHAR(800), grid_attribute_5 VARCHAR(800), grid_attribute_6 VARCHAR(800), grid_attribute_7 VARCHAR(800), grid_attribute_8 VARCHAR(800))");
//    qgrid.exec();

//    if(!qgrid.exec())
//    {
//        qDebug()<< "Failed to create table grid";
//    }
//}

//void feature_tables::on_pushButton_creating_birthmark_table_clicked()
//{
//    QSqlQuery qbirthmark = QSqlQuery(db4);

//    qbirthmark.prepare("CREATE TABLE IF NOT EXISTS birthmark ( id INTEGER PRIMARY KEY AUTOINCREMENT, picture_id VARCHAR (800), birthmark_attribute_1 VARCHAR(100), birthmark_attribute_2 VARCHAR(800), birthmark_attribute_3 VARCHAR(800), birthmark_attribute_4 VARCHAR(800), birthmark_attribute_5 VARCHAR(800), birthmark_attribute_6 VARCHAR(800), birthmark_attribute_7 VARCHAR(800), birthmark_attribute_8 VARCHAR(800))");
//    qbirthmark.exec();

//    if(!birthmark.exec())
//    {
//        qDebug()<< "Failed to create table birthmark";
//    }
//}

void feature_tables::on_pushButton_for_insert_clicked()
{
    //  it get meaning of features from another part of PROGRAM/ globules_charact[]- for saving some characteristics from other programmer
     QString clasfglob0, clasfglob1, clasfglob2, clasfglob3, clasfglob4, clasfglob5, clasfglob6, clasfglob7, clasfglob8;
     QString clasfhair0, clasfhair1, clasfhair2, clasfhair3, clasfhair4, clasfhair5, clasfhair6, clasfhair7, clasfhair8;
     QString clasfcell0, clasfcell1, clasfcell2, clasfcell3, clasfcell4, clasfcell5, clasfcell6, clasfcell7, clasfcell8;
     QString clasfgrid0, clasfgrid1, clasfgrid2, clasfgrid3, clasfgrid4, clasfgrid5, clasfgrid6, clasfgrid7, clasfgrid8;
     QString clasfbirthmark0, clasfbirthmark1, clasfbirthmark2, clasfbirthmark3, clasfbirthmark4, clasfbirthmark5, clasfbirthmark6, clasfbirthmark7, clasfbirthmark8;
    clasfglob0 = ui->lineEdit1->text(); // this is field for name or id or specific number of image maybe for globules_charact[0]
    clasfglob1 = QString::number(globules_charact[1]);
    clasfglob2 = QString::number(globules_charact[2]);
    clasfglob3 = QString::number(globules_charact[3]);
    clasfglob4 = QString::number(globules_charact[4]);
    clasfglob5 = QString::number(globules_charact[5]);
    clasfglob6 = QString::number(globules_charact[6]);
    clasfglob7 = QString::number(globules_charact[7]);
    clasfglob8 = QString::number(globules_charact[8]);
    // ////////////////////////////////////////////////////////////////////
    clasfhair0 = ui->lineEdit1->text(); // this is field for name or id or specific number of image
    clasfhair1 = QString::number(hair_charact[1]);
    clasfhair2 = QString::number(hair_charact[2]);
    clasfhair3 = QString::number(hair_charact[3]);
    clasfhair4 = QString::number(hair_charact[4]);
    clasfhair5 = QString::number(hair_charact[5]);
    clasfhair6 = QString::number(hair_charact[6]);
    clasfhair7 = QString::number(hair_charact[7]);
    clasfhair8 = QString::number(hair_charact[8]);
    // //////////////////////////////////////////////////////////////////
    clasfcell0 = ui->lineEdit2->text(); // this is field for name or id or specific number of image, maybe for cell_charact[0]
    clasfcell1 = QString::number(cell_charact[1]);
    clasfcell2 = QString::number(cell_charact[2]);
    clasfcell3 = QString::number(cell_charact[3]);
    clasfcell4 = QString::number(cell_charact[4]);
    clasfcell5 = QString::number(cell_charact[5]);
    clasfcell6 = QString::number(cell_charact[6]);
    clasfcell7 = QString::number(cell_charact[7]);
    clasfcell8 = QString::number(cell_charact[8]);
    // ////////////////////////////////////////////////////////////////
    clasfgrid0 = ui->lineEdit3->text(); // this is field for name or id or specific number of image, maybe for grid_charact[0]
    clasfgrid1 = QString::number(grid_charact[1]);
    clasfgrid2 = QString::number(grid_charact[2]);
    clasfgrid3 = QString::number(grid_charact[3]);
    clasfgrid4 = QString::number(grid_charact[4]);
    clasfgrid5 = QString::number(grid_charact[5]);
    clasfgrid6 = QString::number(grid_charact[6]);
    clasfgrid7 = QString::number(grid_charact[7]);
    clasfgrid8 = QString::number(grid_charact[8]);
    // ///////////////////////////////////////////////////////////////
    clasfbirthmark0 = ui->lineEdit4->text(); // this is field for name or id or specific number of image, maybe for birthmark_charact[0]
    clasfbirthmark1 = QString::number(birthmark_charact[1]);
    clasfbirthmark2 = QString::number(birthmark_charact[2]);
    clasfbirthmark3 = QString::number(birthmark_charact[3]);
    clasfbirthmark4 = QString::number(birthmark_charact[4]);
    clasfbirthmark5 = QString::number(birthmark_charact[5]);
    clasfbirthmark6 = QString::number(birthmark_charact[6]);
    clasfbirthmark7 = QString::number(birthmark_charact[7]);
    clasfbirthmark8 = QString::number(birthmark_charact[8]);

    //next rows for exple of work /its not a code
    //check for which table the object to be inserted
     /*

      */
    QSqlQuery qglobules = QSqlQuery(db);
   qglobules.prepare ("INSERT INTO globules (picture_id, globule_attribute_1, globule_attribute_2, globule_attribute_3, globule_attribute_4, globule_attribute_5, globule_attribute_6, globule_attribute_7, globule_attribute_8)VALUES (:picture_id, :globule_attribute_1, :globule_attribute_2, :globule_attribute_3, :globule_attribute_4, :globule_attribute_5, :globule_attribute_6, :globule_attribute_7, :globule_attribute_8);");
    {
       qglobules.bindValue(":picture_id",clasfglob0);
       qglobules.bindValue(":globule_attribute_1",clasfglob1);
       qglobules.bindValue(":globule_attribute_2",clasfglob2);
       qglobules.bindValue(":globule_attribute_3",clasfglob3);
       qglobules.bindValue(":globule_attribute_4",clasfglob4);
       qglobules.bindValue(":globule_attribute_5",clasfglob5);
       qglobules.bindValue(":globule_attribute_6",clasfglob6);
       qglobules.bindValue(":globule_attribute_7",clasfglob7);
       qglobules.bindValue(":globule_attribute_8",clasfglob8);
    }

   if(!qglobules.exec())
    {
        qDebug()<<"no insert features";
    }
       //update();// i am not shure that this string is need

   QSqlQuery qhair = QSqlQuery(db1);
  qhair.prepare ("INSERT INTO hair (picture_id, hair_attribute_1, hair_attribute_2, hair_attribute_3, hair_attribute_4, hair_attribute_5, hair_attribute_6, hair_attribute_7, hair_attribute_8)VALUES (:picture_id, :hair_attribute_1, :hair_attribute_2, :hair_attribute_3, :hair_attribute_4, :hair_attribute_5, :hair_attribute_6, :hair_attribute_7, :hair_attribute_8);");
   {
      qhair.bindValue(":picture_id",clasfhair0);
      qhair.bindValue(":hair_attribute_1",clasfhair1);
      qhair.bindValue(":hair_attribute_2",clasfhair2);
      qhair.bindValue(":hair_attribute_3",clasfhair3);
      qhair.bindValue(":hair_attribute_4",clasfhair4);
      qhair.bindValue(":hair_attribute_5",clasfhair5);
      qhair.bindValue(":hair_attribute_6",clasfhair6);
      qhair.bindValue(":hair_attribute_7",clasfhair7);
      qhair.bindValue(":hair_attribute_8",clasfhair8);
   }

  if(!qhair.exec())
   {
       qDebug()<<"no insert features1";
   }
      //update();// i am not shure that this string is need

  QSqlQuery qcell = QSqlQuery(db2);
 qcell.prepare ("INSERT INTO cell (picture_id, cell_attribute_1, cell_attribute_2, cell_attribute_3, cell_attribute_4, cell_attribute_5, cell_attribute_6, cell_attribute_7, cell_attribute_8)VALUES (:picture_id, :cell_attribute_1, :cell_attribute_2, :cell_attribute_3, :cell_attribute_4, :cell_attribute_5, :cell_attribute_6, :cell_attribute_7, :cell_attribute_8);");
  {
     qcell.bindValue(":picture_id",clasfcell0);
     qcell.bindValue(":cell_attribute_1",clasfcell1);
     qcell.bindValue(":cell_attribute_2",clasfcell2);
     qcell.bindValue(":cell_attribute_3",clasfcell3);
     qcell.bindValue(":cell_attribute_4",clasfcell4);
     qcell.bindValue(":cell_attribute_5",clasfcell5);
     qcell.bindValue(":cell_attribute_6",clasfcell6);
     qcell.bindValue(":cell_attribute_7",clasfcell7);
     qcell.bindValue(":cell_attribute_8",clasfcell8);
  }

 if(!qcell.exec())
  {
      qDebug()<<"no insert features2";
  }
     //update();// i am not shure that this string is need

 QSqlQuery qgrid = QSqlQuery(db3);
qgrid.prepare ("INSERT INTO grid (picture_id, grid_attribute_1, grid_attribute_2, grid_attribute_3, grid_attribute_4, grid_attribute_5, grid_attribute_6, grid_attribute_7, grid_attribute_8)VALUES (:picture_id, :grid_attribute_1, :grid_attribute_2, :grid_attribute_3, :grid_attribute_4, :grid_attribute_5, :grid_attribute_6, :grid_attribute_7, :grid_attribute_8);");
 {
    qgrid.bindValue(":picture_id",clasfgrid0);
    qgrid.bindValue(":grid_attribute_1",clasfgrid1);
    qgrid.bindValue(":grid_attribute_2",clasfgrid2);
    qgrid.bindValue(":grid_attribute_3",clasfgrid3);
    qgrid.bindValue(":grid_attribute_4",clasfgrid4);
    qgrid.bindValue(":grid_attribute_5",clasfgrid5);
    qgrid.bindValue(":grid_attribute_6",clasfgrid6);
    qgrid.bindValue(":grid_attribute_7",clasfgrid7);
    qgrid.bindValue(":grid_attribute_8",clasfgrid8);
 }

if(!qgrid.exec())
 {
     qDebug()<<"no insert features";
 }
    //update();// i am not shure that this string is need

//QSqlQuery qglobules = QSqlQuery(db3);
//qglobules.prepare ("INSERT INTO globules (picture_id, globule_attribute_1, globule_attribute_2, globule_attribute_3, globule_attribute_4, globule_attribute_5, globule_attribute_6, globule_attribute_7, globule_attribute_8)VALUES (:picture_id, :globule_attribute_1, :globule_attribute_2, :globule_attribute_3, :globule_attribute_4, :globule_attribute_5, :globule_attribute_6, :globule_attribute_7, :globule_attribute_8);");
//{
//   qglobules.bindValue(":picture_id",clasfglob0);
//   qglobules.bindValue(":globule_attribute_1",clasfglob1);
//   qglobules.bindValue(":globule_attribute_2",clasfglob2);
//   qglobules.bindValue(":globule_attribute_3",clasfglob3);
//   qglobules.bindValue(":globule_attribute_4",clasfglob4);
//   qglobules.bindValue(":globule_attribute_5",clasfglob5);
//   qglobules.bindValue(":globule_attribute_6",clasfglob6);
//   qglobules.bindValue(":globule_attribute_7",clasfglob7);
//   qglobules.bindValue(":globule_attribute_8",clasfglob8);
//}

//if(!qglobules.exec())
//{
//    qDebug()<<"no insert features";
//}
   //update();// i am not shure that this string is need
}

feature_tables::~feature_tables()
{
    delete ui;
}

