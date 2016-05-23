#include "booktablemodel.h"
#include "bookparser.h"

BookTableModel::BookTableModel(QObject *parent)
    :QAbstractTableModel(parent)
{
    header.push_back("ID");
    header.push_back("Authors");
    header.push_back("Title");
    header.push_back("Publisher");
    header.push_back("Year");
    header.push_back("Code");
    header.push_back("Borrowed");
}

int BookTableModel::rowCount(const QModelIndex & /*parent*/) const
{
   return collection.size();
}

int BookTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return header.size();
}

QVariant BookTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
            case 0:
                return collection.at(index.row()).id;
            case 1:
                /// @todo Implement
                return collection.at(index.row()).authors.at(0);
            case 2:
                return collection.at(index.row()).title;
            case 3:
                return collection.at(index.row()).publisher;
            case 4:
                return collection.at(index.row()).year;
            case 5:
                return collection.at(index.row()).code;
            case 6:
                return collection.at(index.row()).borrowed;
            default:
                return QString("Row%1, Column%2")
                                .arg(index.row() + 1)
                                .arg(index.column() +1);
        }
    }
    return QVariant();
}

QVariant BookTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((role == Qt::DisplayRole) && (section >= 0) && (section <= (int)header.size()) && (orientation == Qt::Horizontal))
        return header.at(section);

    return QAbstractTableModel::headerData(section, orientation, role);
}

void BookTableModel::clear()
{
    beginResetModel();
    collection.clear();
    endResetModel();
}

int BookTableModel::add(Book *book)
{
    beginInsertRows(QAbstractTableModel::index(collection.size(),0),collection.size(),collection.size());
    collection.push_back(*book);
    endInsertRows();

    return collection.size();
}
