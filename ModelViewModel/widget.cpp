#include "widget.h"
#include "personmodel.h"

#include <QListView>
#include <QTableView>
#include <QTreeView>
#include <QVboxLayout>

Widget::Widget(QWidget *parent)
   : QWidget(parent)
{
    PersonModel * model = new PersonModel(this);

    QListView *listView = new QListView(this);
    listView -> setModel(model);
    QTableView *tableView = new QTableView(this);
    tableView -> setModel(model);
}

Widget::~Widget()
{
}

