//
//  BaseLayout.h
//  Cocosdroid
//
//  Created by Görkem Oktay on 5.06.2019.
//

#ifndef BaseLayout_h
#define BaseLayout_h

#include <memory>
#include "cocos2d.h"
#include "BaseLayoutParams.h"

namespace cocosdroid {
    
    namespace BaseLayout {
        
        struct Child {
            cocos2d::Node *node = nullptr;
            std::shared_ptr<BaseLayout::Params> params;
            
            Child(cocos2d::Node *node, std::shared_ptr<BaseLayout::Params> params) {
                this->node = node;
                this->params = params;
            }
        };
        
        class Layout : public cocos2d::Node {
            
        public:
            virtual ~Layout();
            
            cocos2d::Size getSize();
            void setSize(cocos2d::Size size);
            
            void setLayoutParams(std::shared_ptr<BaseLayout::Params> params);
            std::shared_ptr<BaseLayout::Params> getLayoutParams();
            
            int getChildCount();
            Child& getChild(int index);
            
            void addView(cocos2d::Node *child, std::shared_ptr<BaseLayout::Params> params);
            
            virtual void addOtherProperties(cocos2d::Node *node, std::shared_ptr<BaseLayout::Params> params);
            
            void calculateScale(cocos2d::Node *node, const float width, const float height);
            
            virtual void build();
            
        private:
            std::shared_ptr<BaseLayout::Params> params;
            std::vector<BaseLayout::Child> children;
            cocos2d::Size size;
            
            void buildBase(cocos2d::Node *node, std::shared_ptr<BaseLayout::Params> params);
            
            void buildNode(cocos2d::Node *view, std::shared_ptr<BaseLayout::Params> params);
            
            cocos2d::Size calculateSize(cocos2d::Node *node, const float width, const float height);
            
            void addMargins(cocos2d::Node *node, const Margin margins);
        };
    };
};

#endif /* BaseLayout_h */
