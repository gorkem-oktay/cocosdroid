//
//  RelativeLayout.cpp
//  Cocosdroid
//
//  Created by Görkem Oktay on 5.06.2019.
//

#include "RelativeLayout.h"
#include "../LayoutUtils.h"

using namespace std;
using namespace cocos2d;
using namespace cocosdroid;
using namespace cocosdroid::utils::layout;

void RelativeLayout::Layout::addOtherProperties(Node *node, shared_ptr<BaseLayout::Params> params) {
    auto *rlParams = (RelativeLayout::Params *) params.get();
    alignParent(node, rlParams->alignParent);
    alignNextTo(node, rlParams);
    alignBaseline(node, rlParams->align);
}

void RelativeLayout::Layout::alignParent(cocos2d::Node *node, const ParentAlignment alignments) {
    
    float positionX = node->getPositionX();
    float positionY = node->getPositionY();
    
    if (node->getParent() != nullptr) {
        
        Size sizeParent = ::getSize(node->getParent());
        
        if (alignments.center) {
            positionX = sizeParent.width * 0.5f + getAnchorDifference(node, ReferencePoint::MID, LengthType::WIDTH);
            positionY = sizeParent.height * 0.5f + getAnchorDifference(node, ReferencePoint::MID, LengthType::HEIGHT);
        }
        
        if (alignments.bottom) {
            positionY = getAnchorDifference(node, ReferencePoint::MIN, LengthType::HEIGHT);
        } else if (alignments.top) {
            positionY = sizeParent.height + getAnchorDifference(node, ReferencePoint::MAX, LengthType::HEIGHT);
        }
        
        if (alignments.left) {
            positionX = getAnchorDifference(node, ReferencePoint::MIN, LengthType::WIDTH);
        } else if (alignments.right) {
            positionX = sizeParent.width + getAnchorDifference(node, ReferencePoint::MAX, LengthType::WIDTH);
        }
    }
    
    node->setPosition(positionX, positionY);
}

void RelativeLayout::Layout::alignNextTo(cocos2d::Node *node, Params *params) {
    
    float positionX = node->getPositionX();
    float positionY = node->getPositionY();
    
    if (params->toRightOf) {
        positionX = getRect(params->toRightOf).getMaxX() - getAnchorDifference(node, ReferencePoint::MAX, LengthType::WIDTH);
    }
    
    if (params->toLeftOf) {
        positionX = getRect(params->toLeftOf).getMinX() - getAnchorDifference(node, ReferencePoint::MIN, LengthType::WIDTH);
    }
    
    if (params->below) {
        positionY = getRect(params->below).getMinY() - getAnchorDifference(node, ReferencePoint::MIN, LengthType::HEIGHT);
    }
    
    if (params->above) {
        positionY = getRect(params->above).getMaxY() - getAnchorDifference(node, ReferencePoint::MAX, LengthType::HEIGHT);
    }
    
    node->setPosition(positionX, positionY);
}

void RelativeLayout::Layout::alignBaseline(cocos2d::Node *node, const Alignment alignments) {
    
    float positionX = node->getPositionX();
    float positionY = node->getPositionY();
    
    if (alignments.center.vertically) {
        positionY = getRect(alignments.center.vertically).getMidY() + getAnchorDifference(node, ReferencePoint::MID, LengthType::WIDTH);
    }
    
    if (alignments.center.horizontally) {
        positionX = getRect(alignments.center.vertically).getMidX() + getAnchorDifference(node, ReferencePoint::MID, LengthType::WIDTH);
    }
    
    if (alignments.left) {
        positionX = getRect(alignments.left).getMinX() + getAnchorDifference(node, ReferencePoint::MIN, LengthType::WIDTH);
    } else if (alignments.right) {
        positionX = getRect(alignments.right).getMaxX() + getAnchorDifference(node, ReferencePoint::MAX, LengthType::WIDTH);
    }
    
    if (alignments.bottom) {
        positionY = getRect(alignments.bottom).getMinY() + getAnchorDifference(node, ReferencePoint::MIN, LengthType::HEIGHT);
    } else if (alignments.top) {
        positionY = getRect(alignments.top).getMaxY() + getAnchorDifference(node, ReferencePoint::MAX, LengthType::HEIGHT);
    }
    
    node->setPosition(positionX, positionY);
}
