#include "stringlistmodel.h"

StringListModel::StringListModel(QStringList list, QObject *parent)
    : QAbstractListModel{parent}, m_list(list)
{

}

int StringListModel::rowCount(const QModelIndex &parent) const
{
    return m_list.count();
}

QVariant StringListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    if(index.row() < 0 || index.row() >= m_list.size())
        return QVariant();

    return m_list.at(index.row());

}

QVariant StringListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal)
        return QString("colum %1").arg(section);
    else
        return QString("row %1").arg(section);
}

Qt::ItemFlags StringListModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

bool StringListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;
//    qDebug() << "role = " << role;
    if(role != Qt::EditRole && role != Qt::DisplayRole)
        return false;

    if(value.toString().isEmpty())
        return false;

    m_list.replace(index.row(), value.toString());
    emit dataChanged(index, index);

    return true;
}

bool StringListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row+count-1);
    for(int i = 0;i < count; i++)
    {
        m_list.insert(row, "");
    }
    endInsertRows();
    return true;
}

bool StringListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), row, row+count+1);
    for(int i = 0; i< count; i++)
        m_list.removeAt(row);

    endRemoveRows();
    return true;
}

Qt::DropActions StringListModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

QStringList StringListModel::mimeTypes() const
{
    QStringList types;
    types << "application/vnd.text.list";
    return types;
}

QMimeData *StringListModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData * mimedata = new QMimeData();
    QByteArray endcodeData;
    QDataStream stream(&endcodeData, QIODevice::WriteOnly);

    for(const QModelIndex& index : indexes)
    {
        if(index.isValid())
        {
            QString text = data(index, Qt::DisplayRole).toString();
            stream << text;
            qDebug() << QString("(%1, %2) = %3").arg(index.row()).arg(index.column()).arg(text);
        }
    }

    mimedata->setData("application/vnd.text.list", endcodeData);
    return mimedata;
}

bool StringListModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if(action == Qt::IgnoreAction)
        return true;

    if(!data->hasFormat("application/vnd.text.list"))
        return false;

    if(column > 0)
        return false;

    int beginRow;
    qDebug() << QString("dropMimeData(%1, %2)").arg(row).arg(column);
    if(row != -1)
        beginRow = row;
    else if(parent.isValid())
    {
        beginRow = parent.row();
        qDebug() << QString("parent.isValid() = %1").arg(beginRow);
    }
    else
    {
        beginRow = rowCount(parent);
        qDebug() << QString("rowCount(parent) = %1").arg(beginRow);
    }

    QByteArray arry = data->data("application/vnd.text.list");
    QDataStream stream(&arry, QIODevice::ReadOnly);

    QStringList itemlists;
    int rows = 0;

    while(!stream.atEnd())
    {
        QString text;
        stream >> text;
        itemlists << text;
        rows++;
    }

    insertRows(beginRow, rows, QModelIndex());

    for(const auto& str : itemlists)
    {
        QModelIndex idx = index(beginRow);
        setData(idx, str, Qt::DisplayRole);
        beginRow++;
    }

    return true;
}
