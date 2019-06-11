//
//  RelativeLayoutParams.h
//  Cocosdroid
//
//  Created by Görkem Oktay on 5.06.2019.
//

#ifndef RelativeLayoutParams_h
#define RelativeLayoutParams_h

#include "../Base/BaseLayoutParams.h"
#include "cocos2d.h"

namespace cocosdroid {
    
    namespace RelativeLayout {
        
        struct Center {
            cocos2d::Node *vertically = nullptr;
            cocos2d::Node *horizontally = nullptr;
        };
        
        struct Alignment {
            cocos2d::Node *bottom = nullptr;
            cocos2d::Node *top = nullptr;
            cocos2d::Node *left = nullptr;
            cocos2d::Node *right = nullptr;
            Center center;
        };
        
        struct ParentAlignment {
            bool bottom = false;
            bool top = false;
            bool left = false;
            bool right = false;
            bool center = false;
        };
        
        struct Params : public BaseLayout::Params {
            
            Alignment align;
            ParentAlignment alignParent;
            
            cocos2d::Node *toRightOf = nullptr;
            cocos2d::Node *toLeftOf = nullptr;
            cocos2d::Node *below = nullptr;
            cocos2d::Node *above = nullptr;
        };
    };
};

#endif /* RelativeLayoutParams_h */
