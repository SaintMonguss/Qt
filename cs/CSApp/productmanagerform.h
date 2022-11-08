#ifndef PRODUCTMANAGERFORM_H
#define PRODUCTMANAGERFORM_H

#include <QWidget>
#include <QMap>

class ProduceItem;
class QMenu;
class QTreeWidgetItem;

namespace Ui {
class ProductManagerForm;
}

class ProductManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProductManagerForm(QWidget *parent = nullptr);
    ~ProductManagerForm();
    void loadData();

private slots:
    void on_addPushButton_clicked();
    void on_modifyPushButton_clicked();
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);
    void on_searchPushButton_clicked();
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    /* QTreeWidget을 위한 슬롯 */
    void removeItem();              /* QAction을 위한 슬롯 */
    void acceptProductInfo(int);

signals:
    void productAdded(int, QString);
    void sendProductInfo(QString, int, int);

private:
    int makeId();

    QMap<int, ProduceItem*> productList;
    Ui::ProductManagerForm *ui;
    QMenu* menu;
};

#endif // PRODUCTMANAGERFORM_H
