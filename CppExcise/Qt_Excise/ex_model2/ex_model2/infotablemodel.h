#ifndef INFOTABLEMODEL_H
#define INFOTABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>

class InfoTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit InfoTableModel(QObject *parent = nullptr);
};

#endif // INFOTABLEMODEL_H
