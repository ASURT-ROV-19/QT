#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QAbstractTableModel>

class tableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    tableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};




#endif // TABLEMODEL_H
