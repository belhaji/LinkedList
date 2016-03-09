//
//  main.c
//  S2Project
//
//  Created by Adil on 3/8/16.
//  Copyright © 2016 Adil. All rights reserved.
//

#include "LinkedList.h"
typedef struct {
    int a,
        b;
}Complex;

void complexs_print(LinkedList*l){
    int i;
    Complex *c = NULL;
    for (i=0; i< l->size; i++) {
        c = (Complex*)list_get(l, i);
        printf("a=%5d ,b=%5d\n",c->a,c->b);
    }
}

int main(int argc, const char * argv[]) {
    LinkedList *list = list_new();
    Complex *c = NULL;
    int i;
    for (i=0; i<5; i++) {
        c = (Complex*) malloc(sizeof(Complex));
        c->a = i;
        c->b = i;
        list_add(list, (void*) c);
    }
    c = (Complex*) malloc(sizeof(Complex));
    c->a=c->b= 10;
    complexs_print(list);
    list_delete(list, 4);
    list_replace(list,3, c);
    printf("------------\n");
    complexs_print(list);
    
    
    printf("------------\n");
    complexs_print(list);
    printf("------------\n");
    c = (Complex*) list_get(list, 3);
    printf("a=%5d ,b=%5d\n",c->a,c->b);
    
    list_clean(list);
    list_free(list);

    return 0;
}
