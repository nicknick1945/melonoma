#ifndef DATABASE_H
#define DATABASE_H

#include "QtSql/qsqldatabase.h"
#include "SLib/Core/sdataframe.h"

/*!
 * \brief Класс базы данных
 * \details Класс обеспечивающий считывание таблицы "объекты-признаки" из системного файла clf.sqlite
 * (хранит обучающую выборку по умолчанию)
 */
class Database
{
//    QSqlDatabase DB;
public:
    /*!
     * \brief Конструктор по имени файла и типу базы данных.
     * \details Сразу попытается открыть базу данных. В случаее успеха в отладочной строке появится "[+]: DB is open".
     * \param name - имя файла (полный/относительный путь)
     * \param type - тип (SQLite, MySql и т.д)
     * \warning Создает пустую БД если таковой не находится.
     */
    Database(const QString& name,const QString& type = "QSQLITE"){
//        DB = QSqlDatabase::addDatabase(type);
//        DB.setDatabaseName(name);
//        if (DB.open())
//            qDebug("[+]: DB is open");
    }
    /*!
     * \brief Извлечение Таблицы "Объекты-признаки".
     * \details Используется исключительно для clf.sqlite
     * \param name - имя таблицы в БД
     * \return Таблицу "Объекты-признаки"
     * \warning Использовать только на таблицах с 7-ю колонками: "Names","_Y","B_MIN","B_MAX","B_SPAN","B_MX","B_SD"
     */
    SDataFrame getTable(const QString& name)
    {
        SDataFrame table;
//        table.setHeader(std::list<std::string>{"_Y","B_MIN","B_MAX","B_SPAN","B_MX","B_SD"});
//        if (DB.isOpen())
//        {
//            QSqlQuery qry("SELECT * FROM "+name,DB);
//            if (qry.exec())
//                while (qry.next())
//                {
//                    std::string Name = qry.value(0).toString().toStdString();
//                    std::list<double> Values;
//                    for (int i=1;i<=6;++i) Values.push_back(qry.value(i).toDouble());
//                    table.newObject(Name,Values);
//                }
//        }
        return table;
    }
    /*!
     * \brief Деструктор,закрывающий БД.
     */
    ~Database()
    {
//        if (DB.isOpen())
//            DB.close();
    }
};

#endif // DATABASE_H
