//
//  homeWord.c
//  Learn4_ndk
//
//  Created by qgg on 2017/8/1.
//  Copyright © 2017年 lhc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct BilateralNode{
    void* data;
    struct BilateralNode *prev;
    struct BilateralNode *next;
}*head,*end;

int size;

void enqueue(void* data);
bool change(int pos,void* data);
struct BilateralNode* query(int pos);
struct BilateralNode* queryFromHead(int pos);
struct BilateralNode* queryFromEnd(int pos);
void sortByPop(int (*)(void*,void*));
void sortByInster(int(*)(void*,void*));
void swap(void **a ,void **b);
int numCmp(int *,int *);
void swapNode(struct BilateralNode *,struct BilateralNode *);
void saveNum();
void saveChar();

void enqueue(void* data){
    struct BilateralNode *node = (struct BilateralNode*)malloc(sizeof(struct BilateralNode));
    node->data = data;
    node->next = NULL;
    node->prev = end;
    
    size++;
    
    if(head == NULL){
        head = node;
    }
    
    if(end == NULL){
        end = node;
    }else{
        end->next = node;
        end = end->next;
    }
}

bool change(int pos,void* data){
    struct BilateralNode *point = query(pos);
    if(point ==NULL){
        return false;
    }else{
        point->data = data;
        return true;
    }
}

struct BilateralNode* pop(){
    
    if(size <= 0){
        printf("没有数据可删除\n");
        return NULL;
    }
    
    struct BilateralNode *node = end;
    end = end->prev;
    end->next = NULL;
    
    size--;
    
    return node;
}

struct BilateralNode* query(int pos){
    if(pos < 0 || pos >= size){
        printf("链表越界\n");
        return NULL;
    }
    
    if(pos < size /2){
        return queryFromHead(pos);
    }else{
        return queryFromEnd(pos);
    }
}

struct BilateralNode* queryFromHead(int pos){
    struct BilateralNode* point = head;
    for(int i= 0;i <pos;i++,point = point->next);
    return point;
}

struct BilateralNode* queryFromEnd(int pos){
    struct BilateralNode* point = end;
    for(int i= size;i >pos;i--,point = point->prev);
    return point;
}

void printNumPosSeq(struct BilateralNode *node){
    printf("---正序打印---\n");
    printf("---一共%d条数据---\n",size);
    while(node != NULL){
        printf("data:%d\n",*(int *)node->data);
        node = node->next;
    }
}

void printCharPosSeq(struct BilateralNode *node){
    printf("---正序打印---\n");
    printf("---一共%d条数据---\n",size);
    while(node != NULL){
        printf("data:%s\n",node->data);
        node = node->next;
    }
}

void printNegSeq(struct BilateralNode *node){
    printf("---逆序打印---\n");
    printf("---一共%d条数据---\n",size);
    while(node != NULL){
        printf("data:%d\n",*(int *)node->data);
        node = node->prev;
    }
}

/**
 ** 冒泡排序
 **/
void sortByPop(int(*cmp)(void* ,void*)){
    struct BilateralNode *tmpHead;
    struct BilateralNode *tmpEnd = end;
    for(;tmpEnd->prev != NULL;tmpEnd = tmpEnd->prev){
        tmpHead = head;
        for(;tmpHead != tmpEnd; tmpHead = tmpHead->next){
            if((*cmp)(tmpHead->data,tmpHead->next->data) > 0){
                swap(&(tmpHead->data), &(tmpHead->next->data));
            }
        }
    }
}

/**
 ** 插入排序
 **/
void sortByInster(int(*cmp)(void*,void*)){
    struct BilateralNode *point;
    struct BilateralNode *sortPos;
    void *tmpNum;
    for(sortPos = head->next;sortPos !=NULL;sortPos= sortPos->next){
        tmpNum = sortPos->data;
        for(point = sortPos->prev;point != NULL && (*cmp)(point->data,tmpNum) >0;point = point->prev){
            point->next->data = point->data;
        }
        if(point == NULL){
            swap(&(head->data), &tmpNum);
        }else{
            swap(&(point->next->data), &tmpNum);
        }
        
    }
}

void swapNode(struct BilateralNode * node1,struct BilateralNode * node2){
    struct BilateralNode *tmpNode = node1;
    node1->next = node2->next;
    node1->prev = node2->prev;
    node2->next->prev = node1;
    node2->prev->next = node1;
    
    node2->next = tmpNode->next;
    node2->prev = tmpNode->prev;
}

int numCmp(int *a,int *b){
    return *a- *b;
}

void swap(void **a,void **b){
    void* tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(int argc, const char * argv[]) {
    saveChar();
//    saveNum();
    return 0;
}

void saveChar(){
     struct BilateralNode *node;
    char* str[8] ={"jack","mike","kony","kitty","ally","bobo","antouny","question"};

    
    for(int i=0;i < 8;i++){
        enqueue(str[i]);
    }
    
    printCharPosSeq(head);

    
    node = query(4);
    printf("查询的数据:%s\n",(char *)node->data);
    
    sortByInster((int(*)(void*,void*))strcmp);
    printCharPosSeq(head);
    
}

void saveNum(){
    struct BilateralNode *node;
    
    pop();
    int *num = (int *) malloc(sizeof(int) * 10);
    
    
    for(int i = 0;i < 10;i++){
        *(num + i) = i;
        enqueue(num + i);
    }
    
    int j = 12;
    change(0, &j);
    
    int k = 10;
    change(3, &k);
    
    int m = 8;
    change(4, &m);
    
    node = query(3);
    printf("查询的数据:%d\n",*(int *)node->data);
    
    printNumPosSeq(head);
    
    node = pop();
    printf("删除的数据:%d\n",*(int *)node->data);
    
    
    //    sortByPop((int(*)(void*,void*))numCmp);
    sortByInster((int(*)(void*,void*))numCmp);
    
    printNumPosSeq(head);
    
//    printNegSeq(end);
}

