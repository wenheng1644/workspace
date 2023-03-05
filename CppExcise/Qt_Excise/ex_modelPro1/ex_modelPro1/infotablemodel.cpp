#include "infotablemodel.h"

InfoTableModel::InfoTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    m_headers << "name" << "age" << "addr";

    QStringList list1;
    list1 << "xwz" << "23" << "guangzhou";
    m_infos.append(list1);
}

int InfoTableModel::rowCount(const QModelIndex &parent) const
{
    return m_infos.size();
}

int InfoTableModel::columnCount(const QModelIndex &parent) const
{
    return m_headers.size();
}

QVariant InfoTableModel::data(const QModelIndex &index, int role) const
{
    QVariant defaultValue;
    if(!index.isValid())
        return defaultValue;

    int row = index.row();
    int col = index.column();
    if(row < 0 || row >= m_infos.size())
        return defaultValue;

    if(col < 0 || col >= m_headers.size())
        return defaultValue;

    if(role != Qt::DisplayRole)
        return defaultValue;

    QStringList curStrInfos = m_infos.at(row);
    QString text = curStrInfos.at(col);


    return text;
}

bool InfoTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;

    if(role != Qt::DisplayRole)
        return false;

    int row = index.row();
    int col = index.column();

    if(row < 0 || row >= m_infos.size())
        return false;

    if(col < 0 || col >= m_headers.size())
        return false;

    QString data = value.toString();

    m_infos[row][col] = data;

    return true;
}

QVariant InfoTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    qDebug() << QString("section = %1, orient = %2, role = %3").arg(section).arg(orientation).arg(role);
    if(orientation != Qt::Orientation::Horizontal || role != Qt::DisplayRole)
        return QAbstractTableModel::headerData(section, orientation, role);
    QString head = m_headers[section];
    qDebug() << "head = " << head;
    return head;
}
