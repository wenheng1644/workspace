#include "filesizefilter.h"
#include <QFileSystemModel>
FileSizeFilter::FileSizeFilter(QObject *parent)
    : QSortFilterProxyModel{parent}, m_minBytes(0)
{

}

void FileSizeFilter::setMinBytes(quint64 bytes)
{
    beginResetModel();

    m_minBytes = bytes;

    endResetModel();

}

bool FileSizeFilter::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    bool ok;
    QString str = sourceModel()->index(source_row, 0, source_parent).data().toString();
    quint64 bytes = sourceModel()->index(source_row, 1, source_parent).data().toUInt(&ok);
//    qDebug() << "name = " << str << " bytes = " << bytes << " status = " << (ok ? "yes" : "no") << " source str = " << source_parent.data().toString() ;

    QFileSystemModel* source = dynamic_cast<QFileSystemModel*>(sourceModel());
    if(!source)
    {
        qDebug() << "error";
    }
    else
    {
//        qDebug() << QString(10, '*');
//        qDebug() << source->index(source_row, 1, source_parent);

        QFileInfo info = source->fileInfo(sourceModel()->index(source_row, 0, source_parent));
//        qDebug() << "curMinBytes = " << m_minBytes << " name = " << info.fileName() << " asPath" << info.absoluteFilePath() << " size = " << info.size() << "bytes";

        if(info.isFile())
        {
            if(info.size() >= m_minBytes)
            {
//                qDebug() << QString(10, '&') << "yes";
                return true;
            }
            return false;
        }
    }
    return true;
}
