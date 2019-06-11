//
//  LayoutUtils.cpp
//  Cocosdroid
//
//  Created by Görkem Oktay on 5.06.2019.
//

#include "LayoutUtils.h"
#include "Base/BaseLayout.h"
#include "Relative/RelativeLayout.h"
#include "Linear/LinearLayout.h"

using namespace cocos2d;

Rect cocosdroid::utils::layout::getCascadeBoundingBox(Node *node) {
    Rect cbb;
    Size contentSize = node->getContentSize();
    
    Node *child = nullptr;
    bool merge = false;
    for (auto object : node->getChildren()) {
        child = dynamic_cast<Node *>(object);
        if (!child->isVisible()) continue;
        
        Rect box = getCascadeBoundingBox(child);
        box.origin.x *= node->getScaleX();
        box.origin.y *= node->getScaleY();
        if (box.size.width <= 0 || box.size.height <= 0) continue;
        
        if (!merge) {
            cbb = box;
            merge = true;
        } else {
            cbb.merge(box);
        }
    }
    
    if (contentSize.width > 0 && contentSize.height > 0) {
        Rect bb = node->getBoundingBox();
        if (node->getParent() == nullptr)
            bb.origin = bb.origin + node->getAnchorPointInPoints();
        if (!merge) {
            cbb = bb;
        } else {
            if (node->getParent() != nullptr)
                cbb.origin = cbb.origin + node->getPosition() - node->getAnchorPointInPoints();
            cbb.merge(bb);
        }
    }
    
    return cbb;
}

bool cocosdroid::utils::layout::isLayout(Node *node) {
    if (typeid(*node) == typeid(BaseLayout::Layout) ||
        typeid(*node) == typeid(RelativeLayout::Layout) ||
        typeid(*node) == typeid(LinearLayout::Layout)) {
        return true;
    }
    return false;
}

Size cocosdroid::utils::layout::getSize(Node *node) {
    return getRect(node).size;
}

Rect cocosdroid::utils::layout::getRect(Node *node) {
    if (isLayout(node)) {
        Size size = ((BaseLayout::Layout *) node)->getSize();
        
        const float x = ((BaseLayout::Layout *) node)->getPositionX() - size.width * node->getAnchorPoint().x;
        const float y = ((BaseLayout::Layout *) node)->getPositionY() - size.height * node->getAnchorPoint().y;
        auto rect = Rect(x, y, size.width, size.height);
        
        return rect;
    } else if (typeid(node) == typeid(Node)) {
        return cocosdroid::utils::layout::getCascadeBoundingBox(node);
    } else {
        return node->getBoundingBox();
    }
    
}

float cocosdroid::utils::layout::calculateAnchorDifference(float length, float anchor, ReferencePoint point) {
    float factor;
    
    switch (point) {
        case MIN:
            factor = anchor;
            break;
        case MID:
            factor = anchor - 0.5f;
            break;
        case MAX:
            factor = anchor * -1.f;
            break;
    }
    
    return length * factor;
}

float cocosdroid::utils::layout::getAnchorDifference(cocos2d::Node *node, ReferencePoint point, LengthType type) {
    Size size = getSize(node);
    Vec2 anchor = node->getAnchorPoint();
    
    if (type == WIDTH) {
        return calculateAnchorDifference(size.width, anchor.x, point);
    }
    
    return calculateAnchorDifference(size.height, anchor.y, point);
}

void cocosdroid::utils::layout::fitToWidth(Node *node, const float width) {
    node->setScale(width / node->getContentSize().width);
}

void cocosdroid::utils::layout::fitToHeight(Node *node, const float height) {
    node->setScale(height / node->getContentSize().height);
}

void cocosdroid::utils::layout::fitToWidthAndHeight(Node *node, const float width, const float height) {
    node->setScale(width / node->getContentSize().width, height / node->getContentSize().height);
}

void cocosdroid::utils::layout::logAnchor(cocos2d::Node *node) {
    if (isLayout(node)) {
        std::shared_ptr<BaseLayout::Params> params = ((BaseLayout::Layout*)node)->getLayoutParams();
        log("Anchor (%i, %s)", params->id, params->tag.c_str());
    } else {
        log("Anchor");
    }
    log("x:%f, y:%f", node->getAnchorPoint().x, node->getAnchorPoint().y);
}

void cocosdroid::utils::layout::logPosition(Node *node) {
    if (isLayout(node)) {
        std::shared_ptr<BaseLayout::Params> params = ((BaseLayout::Layout*)node)->getLayoutParams();
        log("Position (%i, %s)", params->id, params->tag.c_str());
    } else {
        log("Position");
    }
    log("x:%f, y:%f", node->getPositionX(), node->getPositionY());
}

void cocosdroid::utils::layout::logSize(cocos2d::Node *node) {
    Size size = getSize(node);
    
    if (isLayout(node)) {
        std::shared_ptr<BaseLayout::Params> params = ((BaseLayout::Layout*)node)->getLayoutParams();
        log("Size (%i, %s)", params->id, params->tag.c_str());
    } else {
        log("Size");
    }
    
    log("width:%f, height:%f", size.width, size.height);
}

void cocosdroid::utils::layout::logRect(cocos2d::Node *node) {
    Rect rect = getRect(node);
    
    if (isLayout(node)) {
        std::shared_ptr<BaseLayout::Params> params = ((BaseLayout::Layout*)node)->getLayoutParams();
        log("Rect (%i, %s)", params->id, params->tag.c_str());
    } else {
        log("Rect");
    }
    
    log("x:%f, y:%f", rect.origin.x, rect.origin.y);
    log("width:%f, height:%f", rect.size.width, rect.size.height);
    log("minX:%f, midX:%f, maxX:%f", rect.getMinX(), rect.getMidX(), rect.getMaxX());
    log("minY:%f, midY:%f, maxY:%f", rect.getMinY(), rect.getMidY(), rect.getMaxY());
}
