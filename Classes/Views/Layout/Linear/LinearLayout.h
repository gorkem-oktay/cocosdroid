//
//  LinearLayout.h
//  Cocosdroid
//
//  Created by Görkem Oktay on 5.06.2019.
//

#ifndef LinearLayout_h
#define LinearLayout_h

#include "../Base/BaseLayout.h"
#include "LinearLayoutParams.h"

namespace cocosdroid {
    namespace LinearLayout {
        
        class Layout : public BaseLayout::Layout {
            
        public:
            void addOtherProperties(cocos2d::Node *node, std::shared_ptr<BaseLayout::Params> params) override;
            void build() override;
            
            CREATE_FUNC(Layout);
            
        private:
            cocos2d::Size calculateWeight(cocos2d::Node *node, const float weight);
        };
    };
};

#endif /* LinearLayout_h */
