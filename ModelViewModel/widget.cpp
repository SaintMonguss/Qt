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
    QTreeView *treeView = new QTreeView(this);
    treeView -> setModel(model);

    QVboxLayout *layout = new QVBoxLayout(this);
    layout -> addWidget(listView);
    layout -> addWidget(tableView);
    layout -> addWidget(treeView);
}

Widget::~Widget()
{
}

