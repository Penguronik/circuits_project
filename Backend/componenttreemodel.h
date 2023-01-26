#ifndef COMPONENTTREEMODEL_H
#define COMPONENTTREEMODEL_H

#include "componenttreeitem.h"
#include <QFile>
#include <QAbstractItemModel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class ComponentTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ComponentTreeModel(QObject *parent = nullptr);
    ~ComponentTreeModel();

    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;
    virtual QMimeData *mimeData(const QModelIndexList &indexes) const override;
    virtual Qt::DropActions supportedDropActions() const override;
    virtual QStringList mimeTypes() const override;
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
    virtual bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles) override;

    bool load();

private:
    ComponentTreeItem *rootItem_;
    QFile loadFile_;
    QJsonDocument loadDoc_;

};

#endif // COMPONENTTREEMODEL_H
