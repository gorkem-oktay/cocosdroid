//
//  LayoutUtils.h
//  Cocosdroid
//
//  Created by Görkem Oktay on 5.06.2019.
//

#ifndef LayoutUtils_h
#define LayoutUtils_h

namespace cocosdroid {
    namespace utils {
        namespace layout {
            
            enum ReferencePoint {
                MIN,
                MID,
                MAX
            };
            
            enum LengthType {
                WIDTH,
                HEIGHT
            };
            
            cocos2d::Rect getCascadeBoundingBox(cocos2d::Node *node);
            
            bool isLayout(cocos2d::Node *node);
            
            cocos2d::Size getSize(cocos2d::Node *node);
            cocos2d::Rect getRect(cocos2d::Node *node);
            
            float calculateAnchorDifference(float length, float anchor, ReferencePoint point);
            float getAnchorDifference(cocos2d::Node *node, ReferencePoint point, LengthType type);
            
            void fitToWidth(cocos2d::Node *node, const float width);
            void fitToHeight(cocos2d::Node *node, const float height);
            void fitToWidthAndHeight(cocos2d::Node *node, const float width, const float height);
            
            void logAnchor(cocos2d::Node *node);
            void logPosition(cocos2d::Node *node);
            void logSize(cocos2d::Node *node);
            void logRect(cocos2d::Node *node);
        };
    };
};

#endif /* LayoutUtils_h */
