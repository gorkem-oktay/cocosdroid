//
//  RelativeLayout.h
//  Cocosdroid
//
//  Created by Görkem Oktay on 5.06.2019.
//

#ifndef RelativeLayout_h
#define RelativeLayout_h

#include "../Base/BaseLayout.h"
#include "RelativeLayoutParams.h"

namespace cocosdroid {    
    namespace RelativeLayout {
        
        class Layout : public BaseLayout::Layout {
            
        public:
            void addOtherProperties(cocos2d::Node *node, std::shared_ptr<BaseLayout::Params> params) override;
            
            CREATE_FUNC(Layout);
            
        private:
            void alignParent(cocos2d::Node *node, const ParentAlignment alignments);
            void alignNextTo(cocos2d::Node *node, Params *params);
            void alignBaseline(cocos2d::Node *node, const Alignment alignments);
        };
    };
};

#endif /* RelativeLayout_h */
