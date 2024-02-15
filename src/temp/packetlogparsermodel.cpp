
#include "packetlogparsermodel.h"

PacketLogParserModel::PacketLogParserModel(QObject *parent) : QAbstractItemModel(parent)
{
    values.append("1");
    values.append("2");
    values.append("3");
    values.append("4");

    tableHeaders.append("name");
    tableHeaders.append("value");
}

PacketLogParserModel::~PacketLogParserModel()
{

}

QVariant PacketLogParserModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            return tableHeaders.at(section);
        }
    }
    return QVariant();
}

int PacketLogParserModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    //return packetList.size();
    return 1;
}

int PacketLogParserModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    //return tableHeaders.size();
    return 4;
}

QVariant PacketLogParserModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

     int row = index.row();
     if (role == Qt::UserRole)
     {
         return row;
     }
     if (role == Qt::ToolTipRole)
     {
         return (tr("ToolTipRole called"));
     }

     if (role != Qt::DisplayRole && role != Qt::EditRole) {
        return QVariant();
     } else {
        return values.at(index.column());
     }
}

bool PacketLogParserModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    Q_UNUSED(index)
    Q_UNUSED(value)
    Q_UNUSED(role)

    return true;
}

Qt::ItemFlags PacketLogParserModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

bool PacketLogParserModel::setHeaderData(int section, Qt::Orientation orientation,
                   const QVariant &value, int role)
{
    return true;
}

bool PacketLogParserModel::insertColumns(int position, int columns,
                   const QModelIndex &parent)
{
    return true;
}

bool PacketLogParserModel::removeColumns(int position, int columns,
                   const QModelIndex &parent)
{
    return true;
}

bool PacketLogParserModel::insertRows(int position, int rows,
                const QModelIndex &parent)
{
    return true;
}

bool PacketLogParserModel::removeRows(int position, int rows,
                const QModelIndex &parent)
{
    return true;
}

QModelIndex PacketLogParserModel::index(int row, int column,
                  const QModelIndex &parent) const
{

    return QModelIndex();
}

QModelIndex PacketLogParserModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

