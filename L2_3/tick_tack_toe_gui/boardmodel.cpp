#include "boardmodel.h"

#include <QColor>

BoardModel::BoardModel(int size, int level)
{
    mSize = size;

    mLevel = level;

    mState = ST_ACTIVE;

    mBoard.reserve(mSize*mSize);
    mFreeMoves.reserve(mSize*mSize);
    for (int i = 0; i < mSize*mSize; ++i)
    {
        mBoard.push_back(VAL_EMPTY);
        mFreeMoves.push_back(i);
    }
}

bool BoardModel::setVal(int x, int y, BoardModel::Value val)
{
    // Check limits
    if ((x < 0) || (x >= mSize)) return false;
    if ((y < 0) || (y >= mSize)) return false;
    if (mState != ST_ACTIVE) return false;

    // Check if it is empty
    if (getVal(x, y) != VAL_EMPTY) return false;

    // Set value
    mBoard.at(x*mSize + y) = val;

    emit dataChanged(this->index(y,x,QModelIndex()),this->index(y,x,QModelIndex()));

    // Remove it from the "mFreeMoves" vector;
    for (auto it = mFreeMoves.begin(); it != mFreeMoves.end(); it++)
    {
        if (*it == x*mSize+y)
        {
            mFreeMoves.erase(it);
            break;
        }
    }

    updateState(x,y);

    if ((mState == ST_ACTIVE) && mFreeMoves.size() == 0)
        mState = ST_WIN_NONE;

    return true;
}

BoardModel::Value BoardModel::getVal(int x, int y) const
{
    if ((x < 0) || (x >= mSize )) return VAL_EMPTY;
    if ((y < 0) || (y >= mSize )) return VAL_EMPTY;
    return mBoard.at(x*mSize+y);
}

int BoardModel::rowCount(const QModelIndex & /*parent*/) const
{
    return mSize;
}

int BoardModel::columnCount(const QModelIndex & /*parent*/) const
{
    return mSize;
}

QVariant BoardModel::data(const QModelIndex &index, int role) const
{
    Value val = getVal(index.column(),index.row());
    if (role == Qt::TextAlignmentRole )
        return QVariant(Qt::AlignCenter | Qt::AlignVCenter);

    if (role == Qt::DisplayRole)
    {
        switch (val) {
        case VAL_EMPTY:
            return "";
        case VAL_X:
            return "X";
        case VAL_O:
            return "O";
        default:
            return "#";
        }
    }
    if (role == Qt::BackgroundColorRole)
    {
        switch (val) {
        case VAL_EMPTY:
            return QVariant(QColor(Qt::transparent));
        case VAL_X:
            return QVariant(QColor(0xAA,0xFF,0x80));
        case VAL_O:
            return QVariant(QColor(0xD5,0x80,0xFF));
        default:
            break;
        }
    }
return QVariant();
}

void BoardModel::updateState(int x, int y)
{
    int x1,y1,x2,y2;

    int curLevel;

    x1 = x - mLevel - 1;
    x2 = x + mLevel - 1;
    y1 = y - mLevel - 1;
    y2 = y + mLevel - 1;

    if (x1 < 0) x1 = 0;
    if (y1 < 0) y1 = 0;
    if (x2 >= mSize) x2 = mSize - 1;
    if (y2 >= mSize) y2 = mSize - 1;

    Value val;
    curLevel = 0;
    Value val_old = VAL_EMPTY;

    // Check "-" line
    for (int _x = x1; _x <= x2; _x++)
    {
        val = getVal(_x, y);
        if (val != val_old)
            curLevel = 0;

        if (val != VAL_EMPTY)
        {
            curLevel++;
            if (curLevel >= mLevel)
            {
                if (val == VAL_X)
                    mState = ST_WIN_X;
                else
                    mState = ST_WIN_O;
                return;
            }
        }

        val_old = val;
    }
    val_old = VAL_EMPTY;
    // Check "|" line
    for (int _y = y1; _y <= y2; _y++)
    {
        val = getVal(x, _y);
        if (val != val_old)
            curLevel = 0;

        if (val != VAL_EMPTY)
        {
            curLevel++;
            if (curLevel >= mLevel)
            {
                if (val == VAL_X)
                    mState = ST_WIN_X;
                else
                    mState = ST_WIN_O;
                return;
            }
        }

        val_old = val;
    }
    val_old = VAL_EMPTY;
    // Check "\" line
    for (int _x = x1; _x <= x2; _x++)
    {
        val = getVal(_x,y1+_x-x1);
        if (val != val_old)
            curLevel = 0;

        if (val != VAL_EMPTY)
        {
            curLevel++;
            if (curLevel >= mLevel)
            {
                if (val == VAL_X)
                    mState = ST_WIN_X;
                else
                    mState = ST_WIN_O;
                return;
            }
        }

        val_old = val;
    }
    val_old = VAL_EMPTY;
    // Check "/" line
    for (int _x = x1; _x <= x2; _x++)
    {
        val = getVal(_x, y2-_x+x1);
        if (val != val_old)
            curLevel = 0;

        if (val != VAL_EMPTY)
        {
            curLevel++;
            if (curLevel >= mLevel)
            {
                if (val == VAL_X)
                    mState = ST_WIN_X;
                else
                    mState = ST_WIN_O;
                return;
            }
        }
        val_old = val;
    }
}

