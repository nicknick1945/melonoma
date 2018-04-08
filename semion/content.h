#ifndef CONTENT_H
#define CONTENT_H

#include <QDir>
#include <QFileDialog>
#include <vector>
/*!
 @brief Класс-список элементов папки.
 @details Данный класс обеспечивает удобный интерфейс для создания списка имен элементов папки, посредством вызова стандартного диалгового окна.
 */
class Content: public QDir
{
    std::vector<QString> fileNames;
public:
    Content();
    size_t size();
    void reset();
    QString operator [](int i);
    QString name(int i);
};

#endif // CONTENT_H
