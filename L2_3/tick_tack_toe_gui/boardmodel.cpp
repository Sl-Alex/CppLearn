#include "boardmodel.h"

#include <QColor>

BoardModel::BoardModel(int size, int level)
{
    mSize = size;

    mLevel = level;

    mState = ST_ACTIVE;

    pData = new Value[mSize*mSize];
    mFreeMoves.clear();
    mFreeMoves.reserve(mSize*mSize);
    for (int i = 0; i < mSize* mSize; i++)
    {
        mFreeMoves.push_back(i);
    }
    memset(pData,0,mSize*mSize*sizeof(Value));
}

BoardModel::~BoardModel()
{
    delete[] pData;
}

bool BoardModel::setVal(int x, int y, BoardModel::Value val)
{
    // Check limits
    if ((x < 0) || (x >= mSize)) return false;
    if ((y < 0) || (y >= mSize)) return false;
    if (mState != ST_ACTIVE) return false;

    Value * pVal = &pData[x*mSize+y];

    // Check if it is empty
    if (*pVal != VAL_EMPTY) return false;

    // Set value
    *pVal = val;
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

    // Check
    if (mState != ST_ACTIVE)
        return true;

    updateState(x,y);

    if ((mState == ST_ACTIVE) && mFreeMoves.size() == 0)
        mState = ST_WIN_NONE;

    return true;
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
    Value val = pData[index.column()*mSize + index.row()];
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

    Value * pVal;
    curLevel = 0;
    Value val_old = VAL_EMPTY;

    // Check "-" line
    for (int _x = x1; _x <= x2; _x++)
    {
        pVal = &pData[_x*mSize+y];
        if (*pVal != val_old)
            curLevel = 0;

        if (*pVal != VAL_EMPTY)
        {
            curLevel++;
            if (curLevel >= mLevel)
            {
                if (*pVal == VAL_X)
                    mState = ST_WIN_X;
                else
                    mState = ST_WIN_O;
                return;
            }
        }

        val_old = *pVal;
    }
    val_old = VAL_EMPTY;
    // Check "|" line
    for (int _y = y1; _y <= y2; _y++)
    {
        pVal = &pData[x*mSize+_y];
        if (*pVal != val_old)
            curLevel = 0;

        if (*pVal != VAL_EMPTY)
        {
            curLevel++;
            if (curLevel >= mLevel)
            {
                if (*pVal == VAL_X)
                    mState = ST_WIN_X;
                else
                    mState = ST_WIN_O;
                return;
            }
        }

        val_old = *pVal;
    }
    val_old = VAL_EMPTY;
    // Check "\" line
    for (int _x = x1; _x <= x2; _x++)
    {
        pVal = &pData[_x*mSize+y1+_x-x1];
        if (*pVal != val_old)
            curLevel = 0;

        if (*pVal != VAL_EMPTY)
        {
            curLevel++;
            if (curLevel >= mLevel)
            {
                if (*pVal == VAL_X)
                    mState = ST_WIN_X;
                else
                    mState = ST_WIN_O;
                return;
            }
        }

        val_old = *pVal;
    }
    val_old = VAL_EMPTY;
    // Check "/" line
    for (int _x = x1; _x <= x2; _x++)
    {
        pVal = &pData[_x*mSize+y2-_x+x1];
        if (*pVal != val_old)
            curLevel = 0;

        if (*pVal != VAL_EMPTY)
        {
            curLevel++;
            if (curLevel >= mLevel)
            {
                if (*pVal == VAL_X)
                    mState = ST_WIN_X;
                else
                    mState = ST_WIN_O;
                return;
            }
        }
        val_old = *pVal;
    }
}

