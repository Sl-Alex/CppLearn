#ifndef BOOKTABLEMODEL_H
#define BOOKTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include "book.h"

class BookTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    BookTableModel(QObject *parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void clear(void);
    int add(Book * book);
private:
    std::vector<QString> header;
    std::vector<Book> collection;
};

#endif // BOOKTABLEMODEL_H
