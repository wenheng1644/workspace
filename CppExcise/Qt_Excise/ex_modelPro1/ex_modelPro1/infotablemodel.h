#ifndef INFOTABLEMODEL_H
#define INFOTABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>

struct InfoTable{
    QString name;
    ushort age;
    QString addr;
};

class InfoTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit InfoTableModel(QObject *parent = nullptr);


private:
    QStringList m_headers;
    QList<QStringList> m_infos;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // INFOTABLEMODEL_H
