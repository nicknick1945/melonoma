#include "widget.h"
#include "ui_widget.h"
/*!
 * \brief Конструктор главного окна.
 * \details Отвечает за предварительную форму главного окна (Раскрывает полностью), настраивает и свзывает элементы
 * формы между собой, обучает классификатор clf по данныи из clf.sqlite или, если существует, из clf.csv.
 * \param parent - родительский виджет (0)
 */
Widget::Widget(QWidget *parent) :
    DefaultWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    showMaximized();
    int MW_width= QApplication::desktop()->availableGeometry().right()+1;
    int MW_height= QApplication::desktop()->availableGeometry().bottom()+1;
    ui->gridLayoutWidget->setGeometry(5,5,MW_width-10,MW_height-70);

    ui->GV_main->setScene(new QGraphicsScene);

    connect(ui->PB_Open,SIGNAL(clicked()),this,SLOT(Open()));
    connect(ui->PB_table,SIGNAL(clicked()),this,SLOT(GenerateTable()));
    connect(ui->PB_answers,SIGNAL(clicked()),this,SLOT(GenerateAnswers()));
    connect(ui->LW_images,SIGNAL(currentRowChanged(int)),this,SLOT(Load(int)));
    connect(ui->PB_classifier,SIGNAL(clicked(bool)),this,SLOT(GenerateClassifier()));
    folder.setNameFilters({"*.jpg"});

    SDataFrame sample;
    if (QFile("clf.csv").exists())
    {
        sample = SDataFrame("clf.csv");
    }
    else
    {
        Database db("clf.sqlite");
        sample = db.getTable("sample");
    }
    std::vector<double> Y = sample.col(0);
    std::vector<int> iY(Y.size());
    for(size_t i=0;i<Y.size();++i)
        if (Y[i]!=0) iY[i]=1;
    sample.removeColumn(0);
    clf.fit(sample,iY);
}

/*!
 * \brief Деструктор формы.
 */
Widget::~Widget()
{
    delete ui;
}

/*!
 * \brief Обработчик события - (пере)выбор папки с изображениями.
 * \details Срабатывает при нажатии на кнопку PB_open. Открывает стандартное диалговое окно ОС в которой нужно выбрать папку
 * с изображениями в формате .jpg. При этом в списке LW_images отобразяться найденные изображения.
 */
void Widget::Open()
{
    folder.reset();
    ui->LW_images->clear();
    QStringList list = folder.entryList();
    ui->progressBar->setMaximum(folder.size());
    ui->LW_images->addItems(list);    
}
//QTime t; t.start();qDebug()<<t.elapsed();

/*!
 * \brief Обработчик события - загрузка изображения.
 * \details Обеспечиает загрузку выбранного в LW_images изображения. При этом запускается основной алгоритм программы.
 * \param num - номер строки в списке LW_images
 */
void Widget::Load(int num)
{
    if (num!=-1)
    {

        ui->GV_main->scene()->clear();
        QString path = folder[num];

        QImage image(path);
        SMainComponents mc(image);
        SMatrix first(image,mc.first());
        SThreshold<BINARY> bin;
        SSegmentationMap map(bin.bypass(first));
        map.combine(7000);

        SImageDescriptor master(image,map);
        master.addFeatures(new SHistogram());
        master.addComponent("B",S::Blue());
        SDataFrame X=master.run();
        std::vector<int> predictions = clf.predict(X);
        std::vector<int> segments = map.IDs();

        assert(predictions.size()==segments.size());

        std::vector<int> skin;
        for (size_t i=0;i<predictions.size();++i)
            if (!predictions[i]) skin.push_back(segments[i]);
        for (size_t i=1;i<skin.size();++i)
            map.join(skin[0],skin[i]);

        map.onImage(image);

        QPixmap diagram(QPixmap::fromImage(image));
        ui->GV_main->scene()->addPixmap(diagram);

        ui->label->clear();
        ui->label->setText(folder.name(num));
    }
}

/*!
 * \brief Обработчик события - генерирование таблицы-"Объекты признаки".
 * \details При нажатии на PB_table по всем изображениям папки выполняет процедуру описания сегментов по планам R,G,B,H,S,Br и
 * Fm,Sm,Tm(см. SMainComponents). Вычисляемые признаки - все из SHistogram и SAdjacencyMatrix (шаг 1).
 * Результат пишется в файл result.csv в той же директории, что и программа.
 */
void Widget::GenerateTable()
{
    SDataFrame result;
    LoggerFactory *loggerFactory = new LoggerFactory();
    Logger *logger = loggerFactory->getInstance();
    for(size_t i=0;i<folder.size();++i)
    {
        ui->progressBar->setValue(i);
        QImage image(folder[i]);
        SMainComponents mc(image);
        SMatrix main_plane(image,mc.first());
        SThreshold<BINARY> bin;
        SSegmentationMap map(bin.bypass(main_plane));
        map.combine(7000);

        SImageDescriptor master(image,map);

        master.addFeatures(new SHistogram());
        master.addFeatures(new SAdjacencyMatrix());

        master.addComponent("R",S::Red());
        master.addComponent("G",S::Green());
        master.addComponent("B",S::Blue());
        master.addComponent("H",S::Hue());
        master.addComponent("S",S::Saturation());
        master.addComponent("V",S::Value());
        master.addComponent("Fm",mc.first());
        master.addComponent("Sm",mc.second());
        master.addComponent("Tm",mc.third());

        result.vstack(master.run(folder.name(i).toStdString()+"_"));

    }
    ui->progressBar->reset();

   // result.toCSV("result.csv");
    ui->label->clear();
    ui->label->setText("result.csv");
}

/*!
 * \brief Обработчик события - генерирование вектора ответов.
 * \details При нажатии PB_answers, в открывшемся диалговом окне нужно задать папку с размеченными изображениями.
 * О том как приготовить разметку см. "Руководство пользователя". Результатом является файл answers.csv (в директории программы)
 * с вектором ответов.
 */
void Widget::GenerateAnswers()
{
    ui->label->clear();

    Content markup_folder;
    markup_folder.setNameFilters({"*.bmp"});
    markup_folder.reset();

    if (markup_folder.size()==folder.size())
    {
        SDataFrame result;
        for(size_t i=0;i<folder.size();++i)
        {
            ui->progressBar->setValue(i);
            QString path = folder[i];
            QImage image(path);
            SMainComponents mc(image);
            SMatrix first(image,mc.first());
            SThreshold<BINARY> bin;
            SSegmentationMap map(bin.bypass(first));
            map.combine(7000);

            QImage markup(markup_folder[i]);
            SImageDescriptor master(markup,map);
            master.addComponent("",S::Lasy());
            master.addFeatures(new STeacher());

            QString name=markup_folder.name(i)+"_";
            result.vstack(master.run(name.toStdString()));

        }
        ui->progressBar->reset();
    //    result.toCSV("answers.csv");
     //   ui->label->setText("answers.csv");
    }
    else
    {
       ui->label->setText("Ошибка");
    }
}

/*!
 * \brief Обработчик события - генерирование обучающей выборки и вектора ответов для классификатора.
 * \details При нажатии PB_сlassifier, в открывшемся диалговом окне нужно задать папку с размеченными изображениями.
 * О том как приготовить разметку см. "Руководство пользователя". Результатом является файл clf.csv (в директории программы)
 * с обучающей выборкой и вектором ответов.
 */
void Widget::GenerateClassifier()
{
    ui->label->clear();

    Content markup_folder;
    markup_folder.setNameFilters({"*.bmp"});
    markup_folder.reset();

    if (markup_folder.size()>0)
    {
        SDataFrame result,answers;
        for(size_t i=0;i<folder.size();++i)
        {
            ui->progressBar->setValue(i);
            QImage image(folder[i]);
            SMainComponents mc(image);
            SMatrix main_plane(image,mc.first());
            SThreshold<BINARY> bin;
            SSegmentationMap map(bin.bypass(main_plane));
            map.combine(7000);

            SImageDescriptor master(image,map);
            master.addFeatures(new SHistogram());
            master.addComponent("B",S::Blue());
            result.vstack(master.run(folder.name(i).toStdString()+"_"));

            QImage markup(markup_folder[i]);
            SImageDescriptor markup_master(markup,map);
            markup_master.addComponent("",S::Lasy());
            markup_master.addFeatures(new STeacher());
            QString name=markup_folder.name(i)+"_";
            answers.vstack(markup_master.run(name.toStdString()));

        }
        ui->progressBar->reset();
        answers+=result;
        answers.toCSV("clf.csv");

        ui->label->setText("clf.csv");
    }
    else
    {
        ui->label->setText("Ошибка");
    }
}

QString* Widget::getWidgetName()
{
    QString *widgetName = new QString("какой-то ебанутый widget");
    return widgetName;
}
