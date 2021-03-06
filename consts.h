//
// Created by luogan on 16-10-14.
//

#ifndef DBPROJECT_CONSTS_H
#define DBPROJECT_CONSTS_H

#define TYPE_INT 0
#define TYPE_CHAR 1
#define TYPE_VARCHAR 2

#define INDEX_CLUSTERED 'a'
#define INDEX_UNCLUSTERED_UNIQUE 'b'
#define INDEX_UNCLUSTERED 'c'

#define COMPARE_EQUAL 0
#define COMPARE_NOT_EQUAL 1
#define COMPARE_LARGER 2
#define COMPARE_SMALLER 3
#define COMPARE_SMALLER_EQUAL 4
#define COMPARE_LARGER_EQUAL 5
#define COMPARE_UNDEFINED 6

#define PAGE_NORMAL 0
#define PAGE_LEAF 1

#define COL_ERROR -1
#define COL_NULL 0
#define COL_PRI 1
#define COL_UNI 2
#define COL_MUL 3

#endif //DBPROJECT_CONSTS_H
