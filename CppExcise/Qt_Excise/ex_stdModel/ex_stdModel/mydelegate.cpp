#include "mydelegate.h"

MyDelegate::MyDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

QWidget *MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox * spinBox = new QSpinBox(parent);
    return spinBox;
}

void MyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QSpinBox * spinBox = static_cast<QSpinBox*>(editor);
    int v = index.model()->data(index, Qt::EditRole).toInt();
    spinBox->setValue(v);
}

void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox * spinBox = static_cast<QSpinBox*>(editor);
    spinBox->interpretText();
    int v = spinBox->value();

    model->setData(index, v );
}

void MyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
