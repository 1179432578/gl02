//
//  ccMacros.h
//  gl02
//
//  Created by lewis on 16/5/28.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef ccMacros_h
#define ccMacros_h

//定义一些宏

#ifndef FLT_EPSILON
#define FLT_EPSILON     1.192092896e-07F
#endif // FLT_EPSILON

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

#endif /* ccMacros_h */
