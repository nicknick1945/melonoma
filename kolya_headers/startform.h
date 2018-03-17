#ifndef STARTFORM_H
#define STARTFORM_H

#include <QWidget>
#include "platform_headers/cachefactory.h"
#include "qstring.h"
#include "platform_headers/defaultwidget.h"

namespace Ui {
class StartForm;
}

class StartForm : public DefaultWidget
{
    Q_OBJECT

public:
    explicit StartForm(QWidget *parent = 0);
    QString* getWidgetName();
    ~StartForm();

private slots:
    void on_downloadPhotoButton_clicked();

private:
    CacheFactory *cahceFactory = new CacheFactory();
    Ui::StartForm *ui;
};

#endif // STARTFORM_H
