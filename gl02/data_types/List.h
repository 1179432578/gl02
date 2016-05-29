//
//  List.hpp
//  gl02
//
//  Created by lewis on 16/5/29.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef List_hpp
#define List_hpp

#include <stdio.h>
#include "CCObject.h"

#define DL_APPEND(head,add,prev,next)                                                         \
do {                                                                                           \
    if (head) {                                                                                  \
        (add)->prev = (head)->prev;                                                              \
        (head)->prev->next = (add);                                                              \
        (head)->prev = (add);                                                                    \
        (add)->next = NULL;                                                                      \
    } else {                                                                                     \
        (head)=(add);                                                                            \
        (head)->prev = (head);                                                                   \
        (head)->next = NULL;                                                                     \
    }                                                                                            \
} while (0)

#endif /* List_hpp */
