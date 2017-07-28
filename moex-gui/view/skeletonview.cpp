//
//  Created by everettjf
//  Copyright © 2017 everettjf. All rights reserved.
//
#include "skeletonview.h"
#include "../utility/utility.h"
#include "../controller/workspacemanager.h"


SkeletonView::SkeletonView(QWidget *parent) : QWidget(parent)
{
    controller = nullptr;
    treeView = new QTreeView(this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(treeView);
    setLayout(layout);

    connect(treeView,SIGNAL(clicked(QModelIndex)),this,SLOT(clickedTreeNode(QModelIndex)));
}

void SkeletonView::openFile(const QString &filePath)
{
    if(controller) delete controller;
    controller = new SkeletonController();

    controller->setFilePath(filePath);
    QString error;
    if(!controller->initModel(error)){
        util::showError(this,error);
        return;
    }

    treeView->setModel(controller->model());
    treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    treeView->setColumnWidth(0,300);

    treeView->expandAll();

}

void SkeletonView::clickedTreeNode(QModelIndex index)
{
    QStandardItem *item = controller->model()->itemFromIndex(index);
    if(!item)
        return;

    moex::ViewNode *node = static_cast<moex::ViewNode*>(item->data().value<void*>());

    qDebug() << QString::fromStdString(node->GetDisplayName());
    WorkspaceManager::current()->showNode(node);

}
