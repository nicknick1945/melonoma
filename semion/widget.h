#ifndef WIDGET_H
#define WIDGET_H

#include <QDebug>
#include <QWidget>
#include <QDesktopWidget>
#include <QString>
#include <QTime>
#include "content.h"
#include "database.h"
#include "SLib/classifying.h"
#include "SLib/components.h"
#include "SLib/core.h"
#include "SLib/features.h"
#include "SLib/processing.h"
#include "platform_headers/defaultwidget.h"


namespace Ui {
class Widget;
}
/*!
 @brief Класс главного окна.
 @details Данный класс обеспечивает обработку событий формы.
 Так же обеспечивает выполнение основного алгоритма программы:
\code
// Блок предобработки
QImage image(path);
SMainComponents mc(image);
SMatrix first(image,mc.first());
SThreshold<BINARY> bin;
SSegmentationMap map(bin.bypass(first));
map.combine(7000);

//Блок описания сегментов
SImageDescriptor master(image,map);
master.addFeatures(new SHistogram());
master.addComponent("B",S::Blue());
SDataFrame X=master.run();

//Блок классификации (кожа/не кожа) сегментов
std::vector<int> predictions = clf.predict(X);
std::vector<int> segments = map.IDs();

//Блок визуализации результата
std::vector<int> skin;
for (size_t i=0;i<predictions.size();++i)
    if (!predictions[i]) skin.push_back(segments[i]);
for (size_t i=1;i<skin.size();++i)
     map.join(skin[0],skin[i]);
map.onImage(image);
\endcode
 */
class Widget : public DefaultWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QString* getWidgetName();
private slots:
    void Open();
    void Load(int);
    void GenerateTable();
    void GenerateAnswers();
    void GenerateClassifier();

private:
    Ui::Widget *ui;
    Content folder;
    SKNeighborsClassifier clf{9,S::manhattan()};
};

#endif // WIDGET_H
