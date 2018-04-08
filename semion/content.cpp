#include "content.h"
//!\brief Конструктор по умолчанию
Content::Content(){}
/*!
 * \brief Возвращает количество элементов папки, удволетворяющим установленным фильтрам
 * \details Подробнее в QDir
 * \return Количество элементов папки, удволетворяющим установленным фильтрам
 */
size_t Content::size()
{
    return fileNames.size();
}
/*!
 * \brief Вызывает стандартное диалоговое окно ОС.
 * \details В данном окне требуется указать папку с файлами, имена которых будут доступны в Content.
 */
void Content::reset()
{
    fileNames.clear();
    setPath(QFileDialog::getExistingDirectory());
    auto EntryList=entryList();
    fileNames.reserve(EntryList.size());
    for (auto i=EntryList.begin();i!=EntryList.end();++i)
        fileNames.push_back(*i);
}
/*!
 * \brief Оператор индекса, возвращающий полное имя (путь+имя) i-го файла в папке.
 * \details По умолчанию имена файлов в классе расположены в лексикографическом порядке.
 * Подробнее в QDir::SortFlags.
 * \param i - Номер файла в папке
 * \return Полное имя (путь+имя) i-го файла
 */
QString Content::operator [](int i)
{
    return absolutePath()+'/'+fileNames[i];
}
/*!
 * \brief Возвращающий i-ое имя файла в папке.
 * \details По умолчанию имена файлов в классе расположены в лексикографическом порядке.
 * Подробнее в QDir::SortFlags
 * \param i - Номер файла в папке
 * \return Имя i-го файла
 */
QString Content::name(int i)
{
    return fileNames[i];
}
