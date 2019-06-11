//
//  LinearLayoutParams.h
//  Cocosdroid
//
//  Created by Görkem Oktay on 5.06.2019.
//

#ifndef LinearLayoutParams_h
#define LinearLayoutParams_h

#include "../Base/BaseLayoutParams.h"

namespace cocosdroid {
    namespace LinearLayout {
        
        enum Orientation {
            VERTICAL,
            HORIZONTAL
        };
        
        struct Params : public BaseLayout::Params {
            
            Orientation orientation = VERTICAL;
            float spacing = 0.f;
            float weightSum = 1.f;
            float weight = 0.f;
        };
    };
};

#endif /* LinearLayoutParams_h */
