//
//  BaseLayout.cpp
//  Cocosdroid
//
//  Created by Görkem Oktay on 5.06.2019.
//

#include "BaseLayout.h"
#include "../LayoutUtils.h"

using namespace std;
using namespace cocos2d;
using namespace cocosdroid;

// DESTRUCTOR
BaseLayout::Layout::~Layout() {
    delete this;
}

// VIRTUAL FUNCTIONS

void BaseLayout::Layout::addOtherProperties(Node *node, shared_ptr<Params> params) {
}

// PUBLIC FUNCTIONS

void BaseLayout::Layout::setLayoutParams(shared_ptr<Params> params) {
    this->params = params;
}

shared_ptr<BaseLayout::Params> BaseLayout::Layout::getLayoutParams()
{
    return this->params;
}

int BaseLayout::Layout::getChildCount() {
    return (int) children.size();
}

BaseLayout::Child& BaseLayout::Layout::getChild(int index) {
    return children[index];
}

Size BaseLayout::Layout::getSize() {
    return this->size;
}

void BaseLayout::Layout::setSize(Size size) {
    this->size = size;
}

void BaseLayout::Layout::addView(Node *child, shared_ptr<Params> params) {
    this->children.push_back(Child(child, params));
    this->addChild(child);
}

void BaseLayout::Layout::buildBase(Node *node, shared_ptr<Params> params) {
    Size size = calculateSize(node, params->width, params->height);
    calculateScale(node, size.width, size.height);
    node->setPosition(params->position.x, params->position.y);
    addOtherProperties(node, params);
    addMargins(node, params->margin);
}

void BaseLayout::Layout::buildNode(Node *node, shared_ptr<Params> params) {
    buildBase(node, params);
}

void BaseLayout::Layout::build() {
    buildBase(this, params);
    for (int i = 0; i < children.size(); ++i) {
        if (utils::layout::isLayout(children[i].node)) {
            ((Layout *) children[i].node)->build();
        } else {
            buildNode(children[i].node, children[i].params);
        }
    }
}

// PRIVATE FUNCTIONS

Size BaseLayout::Layout::calculateSize(Node *node, const float width, const float height) {
    Size size;
    if (width == MATCH_PARENT) {
        auto parent = node->getParent();
        if (parent) {
            size.width = utils::layout::getSize(parent).width;
        } else {
            size.width = Director::getInstance()->getVisibleSize().width;
        }
    } else {
        size.width = width;
    }
    
    if (height == MATCH_PARENT) {
        auto parent = node->getParent();
        if (parent) {
            size.height = utils::layout::getSize(parent).height;
        } else {
            size.height = Director::getInstance()->getVisibleSize().height;
        }
    } else {
        size.height = height;
    }
    
    if (utils::layout::isLayout(node)) {
        setSize(size);
    }
    
    return size;
}

void BaseLayout::Layout::calculateScale(Node *node, const float width, const float height) {
    if (utils::layout::isLayout(node) || typeid(node) == typeid(Node)) {
        return;
    } else if (width == 0.f && height > 0.f) {
        utils::layout::fitToHeight(node, height);
    } else if (width > 0.f && height == 0.f) {
        utils::layout::fitToWidth(node, width);
    } else if (width > 0.f && height > 0.f) {
        utils::layout::fitToWidthAndHeight(node, width, height);
    }
}

void BaseLayout::Layout::addMargins(Node *node, const Margin margins) {
    float x = node->getPositionX();
    float y = node->getPositionY();
    
    x += margins.left;
    x -= margins.right;
    
    y += margins.bottom;
    y -= margins.top;
    
    node->setPositionX(x);
    node->setPositionY(y);
}
