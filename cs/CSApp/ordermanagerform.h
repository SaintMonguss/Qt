#ifndef ORDERMANAGERFORM_H
#define ORDERMANAGERFORM_H

#include <QWidget>

class OrderItem;
class QMenu;
class QTreeWidgetItem;

namespace Ui {
class OrderManagerForm;
}

class OrderManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit OrderManagerForm(QWidget *parent = nullptr);
    ~OrderManagerForm();

    void loadData();

private:
    int makeId();
    Ui::OrderManagerForm *ui;
    QList<int> clientIDList;
    QList<int> productIDList;
    QMap<int, OrderItem*> orderList;
    QMenu* menu;

public slots:
    void addClient(int, QString);
    void addProduct(int, QString);
    void getClientInfo(QString, QString, QString);     // 응답
    void getProductInfo(QString, int, int);     // 응답

    /* QTreeWidget을 위한 슬롯 */
    void removeItem();              /* QAction을 위한 슬롯 */

signals:
    void getClientInfo(int);            // 요청
    void getProductInfo(int);           // 요청

private slots:
    void on_clientComboBox_currentIndexChanged(int index);
    void on_productComboBox_currentIndexChanged(int index);
    void on_quantitySpinBox_valueChanged(int arg1);
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_addPushButton_clicked();
    void on_modifyPushButton_clicked();
    void on_searchPushButton_clicked();
};

#endif // ORDERMANAGERFORM_H
