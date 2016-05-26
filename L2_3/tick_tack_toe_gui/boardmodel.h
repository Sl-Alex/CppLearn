#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QAbstractTableModel>

class BoardModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Value {VAL_EMPTY = 0, VAL_X, VAL_O, VAL_MAX};
    enum State {ST_ACTIVE = 0, ST_WIN_X, ST_WIN_O, ST_WIN_NONE};

    BoardModel(int size = 3, int level = 3);
    ~BoardModel();

    int getSize(void) { return mSize; }
    int getFree(void) { return mFreeMoves.size(); }
    int getFreeIdx(int num) { return mFreeMoves.at(num); }
    bool setVal(int x, int y, Value val);
    State getState(){ return mState; }

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:

    void updateState(int x, int y);

    int mSize;
    int mLevel;
    State mState;
    std::vector<int> mFreeMoves;

    Value * pData;
};

#endif // BOARDMODEL_H
