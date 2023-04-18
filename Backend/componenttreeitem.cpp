#include "componenttreeitem.h"

ComponentTreeItem::ComponentTreeItem(ComponentTreeItem *parent):
    childsList_{},
    parent_{parent}
{

}

ComponentTreeItem::~ComponentTreeItem() {
    qDeleteAll(childsList_);
    childsList_.clear();
}

void ComponentTreeItem::appendChild(ComponentTreeItem *child) {
    childsList_.append(child);
}

ComponentTreeItem *ComponentTreeItem::child(int row) {
    return childsList_.value(row);
}

ComponentTreeItem *ComponentTreeItem::parent() {
    return parent_;
}

int ComponentTreeItem::childCount() const {
    return childsList_.count();
}

int ComponentTreeItem::row() const {
    // to find the row of the item relative to the parent get the index that the item's parent holds of it
    if (parent_) {
        return parent_->childsList_.indexOf(const_cast<ComponentTreeItem *>(this));
    }

    // if there is no parent then this item is the root item and is at row 0
    return 0;
}

void ComponentTreeItem::setKey(const QString &key) {
    key_ = key;
}

void ComponentTreeItem::setValue(const QVariant &value) {
    value_ = value;
}

QString ComponentTreeItem::key() const {
    return key_;
}

QVariant ComponentTreeItem::value() const {
    return value_;
}

ComponentTreeItem *ComponentTreeItem::load(const QJsonObject& rootValue)
{
    ComponentTreeItem *rootItem {new ComponentTreeItem{}};
    rootItem->setKey("root");
    rootItem->setValue(rootValue);


    QString key {"Base Gates"}; // "Base Gates"
    QJsonArray array = rootValue.value(key).toArray(); // Base Gates Array
    // ^ Important to keep this as assignment instead of constructor as constructor does not work as expected in this case

    ComponentTreeItem *baseGates {new ComponentTreeItem{rootItem}};
    rootItem->appendChild(baseGates);

    baseGates->setKey(key);
    baseGates->setValue(array);

    int index {0};
    for (const QJsonValue &v : array) { //switch to iterator for loop
        ComponentTreeItem *value {new ComponentTreeItem{baseGates}};
        baseGates->appendChild(value);

        value->setKey(QString::number(index));
        value->setValue(v.toString());

        ++index;
    }


    key = "Utility Components"; // "Utility Components"
    array = rootValue.value(key).toArray(); // Utility Components Array

    ComponentTreeItem *utilityComponents {new ComponentTreeItem{rootItem}};
    rootItem->appendChild(utilityComponents);

    utilityComponents->setKey(key);
    utilityComponents->setValue(array);

    index = 0;
    for (const QJsonValue &v : array) { //switch to iterator for loop
        ComponentTreeItem *value {new ComponentTreeItem{utilityComponents}};
        utilityComponents->appendChild(value);

        value->setKey(QString::number(index));
        value->setValue(v.toString());

        ++index;
    }


    key = "Custom Components"; // "Custom Components"
    array = rootValue.value(key).toArray(); // Custom Components Array

    ComponentTreeItem *customComponents {new ComponentTreeItem{rootItem}};
    rootItem->appendChild(customComponents);

    customComponents->setKey(key);
    customComponents->setValue(array);

    index = 0;
    for (const QJsonValue &v : array) { //switch to iterator for loop
        ComponentTreeItem *value {new ComponentTreeItem{customComponents}};
        customComponents->appendChild(value);

        value->setKey(QString::number(index));
        value->setValue(v.toObject());

        ++index;
    }

    return rootItem;
}
