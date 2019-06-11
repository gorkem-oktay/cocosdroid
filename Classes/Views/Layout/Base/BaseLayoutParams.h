//
//  BaseLayoutParams.h
//  Cocosdroid
//
//  Created by Görkem Oktay on 5.06.2019.
//

#ifndef BaseLayoutParams_h
#define BaseLayoutParams_h

#include "cocos2d.h"

namespace cocosdroid {

    namespace BaseLayout {
        
        const float MATCH_PARENT = -1.f;
        const float WRAP_CONTENT = 0.f;
        
        struct Margin {
            float bottom = 0.f;
            float top = 0.f;
            float left = 0.f;
            float right = 0.f;
        };
        
        struct Params {
            int id = 0;
            std::string tag = "";
            
            float width = 0.f;
            float height = 0.f;
            
            cocos2d::Vec2 position;
            Margin margin;
        };
    };
};
#endif /* BaseLayoutParams_h */
