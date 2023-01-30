#include "componenttreemodel.h"
#include <QPixmap>
#include <iostream>
#include <QMimeData>

ComponentTreeModel::ComponentTreeModel(QObject *parent):
    QAbstractItemModel{parent},
    rootItem_{new ComponentTreeItem{}},
    loadFile_{},
    loadDoc_{}
{
    loadFile_.setFileName("C:/Users/ronik/Programming/Qt/circuits_project/Backend/SavedComponents.json");
    load();

}

ComponentTreeModel::~ComponentTreeModel()
{
    delete rootItem_;
    rootItem_ = nullptr;
}

bool ComponentTreeModel::load() {

    if (!loadFile_.open(QIODevice::ReadWrite)) {
        return false;
    }

    loadDoc_ = QJsonDocument::fromJson(loadFile_.readAll());

    if (loadDoc_.isNull()) {
        return false;
    }

    qDebug() << loadDoc_.toJson();

    beginResetModel();
    delete rootItem_;
    rootItem_ = ComponentTreeItem::load(loadDoc_.object());
    endResetModel();

    return true;

}

Qt::ItemFlags ComponentTreeModel::flags(const QModelIndex &index) const {

    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    Qt::ItemFlags itemFlags{QAbstractItemModel::flags(index)};

    ComponentTreeItem *item = static_cast<ComponentTreeItem *>(index.internalPointer());

    if (item->parent() != rootItem_) {
        itemFlags.setFlag(Qt::ItemIsDragEnabled);
    }

    if (item->parent()->key() == "Custom Components") {
        itemFlags.setFlag(Qt::ItemIsEditable);
    }

    return itemFlags;
}

QVariant ComponentTreeModel::data(const QModelIndex &index, int role) const {

//    qDebug() << "Role: " << role;
//    qDebug() << "Index Validity: " << index.isValid();

    if (!index.isValid()) {
        return QVariant{};
    }

    ComponentTreeItem *item = static_cast<ComponentTreeItem *>(index.internalPointer());

    if (role == Qt::DecorationRole) {
        if (item->parent() == rootItem_) {
            return QPixmap{"C:/Users/ronik/Programming/Qt/circuits_project/icons/Folder_Icon.png"}.scaled(QSize{25, 25}, Qt::KeepAspectRatio);
        }
        return QPixmap{"C:/Users/ronik/Programming/Qt/circuits_project/icons/Component_Icon.png"}.scaled(QSize{30, 30}, Qt::KeepAspectRatio);
    }



    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            if (item->parent() == rootItem_) {
                return item->key();
            }

            if (item->parent()->key() == "Custom Components") {
                return item->value().toJsonObject().value("Name");
            }

            return item->value();
        }

//    } else if (role == Qt::EditRole) {
//        if (index.column() == 1) {
//            return item->value();
//        }
    }

    return QVariant{};
}

QVariant ComponentTreeModel::headerData(int section, Qt::Orientation orientation, int role) const {

    return QVariant{};
}

int ComponentTreeModel::rowCount(const QModelIndex &parent) const {
    if (!parent.isValid()) {
        return loadDoc_.object().size();
    }

    if (!parent.parent().isValid()) {
        switch (parent.row()) {
        case 0:
            return loadDoc_.object().value("Base Gates").toArray().size();
        case 1:
            return loadDoc_.object().value("Utility Components").toArray().size();
        case 2:
            return loadDoc_.object().value("Custom Components").toArray().size();
        }
    }

    return 0;
}

int ComponentTreeModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

bool ComponentTreeModel::setData(const QModelIndex &index, const QVariant &value, int role) {

    int col = index.column();
    if (role == Qt::EditRole) {
        if (col == 1) {
            ComponentTreeItem *item = static_cast<ComponentTreeItem *>(index.internalPointer());
            item->setValue(value);
            emit dataChanged(index, index, {Qt::EditRole});
            return true;
        }
    }

    return false;
}

bool ComponentTreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) {
    //when true:
    // emit headerDataChanged()

    return false;
}

QModelIndex ComponentTreeModel::index(int row, int column, const QModelIndex &parent) const {

    if (!hasIndex(row, column, parent)) {
        return QModelIndex{};
    }

    ComponentTreeItem *parentItem{};

    if (!parent.isValid()) {
        parentItem = rootItem_;
    } else {
        parentItem = static_cast<ComponentTreeItem *>(parent.internalPointer());
    }

    ComponentTreeItem *childItem = parentItem->child(row);
    if (childItem) {
        return createIndex(row, column, childItem);
    } else {
        return QModelIndex{};
    }
}

QModelIndex ComponentTreeModel::parent(const QModelIndex &index) const {
    if (!index.isValid()) {
        return QModelIndex{};
    }

    ComponentTreeItem *childItem = static_cast<ComponentTreeItem*>(index.internalPointer());
    ComponentTreeItem *parentItem = childItem->parent();

//    qDebug() << childItem->key() << "k, v" << childItem->value();
//    qDebug() << parentItem;
    QModelIndexList indexes{};
    indexes.append(index);
//    qDebug() << mimeData(indexes)->data("application/json");

    if (parentItem == rootItem_) {
        return QModelIndex{};
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

QMimeData *ComponentTreeModel::mimeData(const QModelIndexList &indexes) const {
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData {};

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    for (const QModelIndex &index : indexes) {
       if (index.isValid()) {
            ComponentTreeItem *item = static_cast<ComponentTreeItem *>(index.internalPointer());
            QJsonObject tempObject{};
            tempObject.insert("Data", item->value().toJsonValue());
            QJsonDocument tempDoc{tempObject};
            stream << tempDoc.toJson();
            qDebug() << "Actual Stream: " << encodedData;
            qDebug() << "Stream: " << tempDoc.toJson();
       }
    }

    mimeData->setData("application/json", encodedData);

    return mimeData;

}

QStringList ComponentTreeModel::mimeTypes() const {
    QStringList typeList{};
    typeList.append("application/json");
    return typeList;
}

Qt::DropActions ComponentTreeModel::supportedDropActions() const {
    return Qt::IgnoreAction | Qt::CopyAction;
}

bool ComponentTreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) {
//    qDebug() << QJsonDocument::fromJson(data->data("application/json"));
    if (action & Qt::IgnoreAction) {
        return true;
    }

    return false;
}

bool ComponentTreeModel::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles) {
    for (const QVariant &value : roles) {
        if(!setData(index, value, roles.key(value))) {
            return false;
        }
    }

    return true;
}
