//
//  LinearLayout.cpp
//  Cocosdroid
//
//  Created by Görkem Oktay on 5.06.2019.
//

#include "LinearLayout.h"
#include "../LayoutUtils.h"

using namespace std;
using namespace cocos2d;
using namespace cocosdroid;

Size LinearLayout::Layout::calculateWeight(cocos2d::Node *node, const float weight) {
    Size size = utils::layout::getSize(node);
    auto genericParent = node->getParent();
    if (genericParent && typeid(*genericParent) == typeid(LinearLayout::Layout)) {
        auto *layoutParent = ((LinearLayout::Layout*) genericParent);
        auto *paramsParent = (LinearLayout::Params*) layoutParent->getLayoutParams().get();
        
        auto sizeParent = layoutParent->getSize();
        
        const float totalSpacing = (float)(layoutParent->getChildCount() - 1) * paramsParent->spacing;
        const float ratio = weight / paramsParent->weightSum;
        
        if (paramsParent->orientation == Orientation::HORIZONTAL) {
            size.width = (sizeParent.width - totalSpacing) * ratio;
        } else {
            size.height = (sizeParent.height - totalSpacing) * ratio;
        }
    }
    
    return size;
}

void LinearLayout::Layout::addOtherProperties(cocos2d::Node *node, std::shared_ptr<BaseLayout::Params> params) {
    auto *llParams = (LinearLayout::Params*) params.get();
    if (llParams->weight > 0.f) {
        Size size = calculateWeight(node, llParams->weight);
        if (utils::layout::isLayout(node)) {
            ((BaseLayout::Layout*) node)->setSize(size);
        } else {
            calculateScale(node, size.width, size.height);
        }
    }
}

void LinearLayout::Layout::build() {
    BaseLayout::Layout::build();
    auto params = (LinearLayout::Params*) getLayoutParams().get();
    
    float totalLength = 0.f;
    for (int i = 0; i < getChildCount(); i++) {
        auto child = getChild(i);
        
        float positionX = utils::layout::getAnchorDifference(child.node, utils::layout::ReferencePoint::MIN, utils::layout::LengthType::WIDTH);
        float positionY = utils::layout::getAnchorDifference(child.node, utils::layout::ReferencePoint::MIN, utils::layout::LengthType::HEIGHT);
        
        if (params->orientation == Orientation::HORIZONTAL) {
            positionX += totalLength;
        } else {
            positionY += totalLength;
        }
        
        child.node->setPositionX(positionX);
        child.node->setPositionY(positionY);
        
        int lengthToAdd = 0.f;
        if (params->orientation == Orientation::HORIZONTAL) {
            lengthToAdd = utils::layout::getSize(child.node).width;
        } else {
            lengthToAdd = utils::layout::getSize(child.node).height;
        }
        
        if (getChildCount() > 1 && i != getChildCount()) {
            lengthToAdd += params->spacing;
        }
        
        totalLength += lengthToAdd;
    }
}
