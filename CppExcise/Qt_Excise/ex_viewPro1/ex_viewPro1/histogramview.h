#ifndef HISTOGRAMVIEW_H
#define HISTOGRAMVIEW_H

#include <QAbstractItemModel>
#include <QObject>
#include <QRegion>

class HistogramView : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit HistogramView(QObject *parent = nullptr);

    QRect visualRect(const QModelIndex& index) const;
};

#endif // HISTOGRAMVIEW_H
