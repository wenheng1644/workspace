#ifndef FILESIZEFILTER_H
#define FILESIZEFILTER_H

#include <QSortFilterProxyModel>
#include <QObject>

class FileSizeFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit FileSizeFilter(QObject *parent = nullptr);
    ~FileSizeFilter() = default;

    void setMinBytes(quint64 bytes);

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    quint64 m_minBytes;
};

#endif // FILESIZEFILTER_H
