//
//  Student.h
//  S2Project
//
//  Created by Adil on 3/10/16.
//  Copyright © 2016 Adil. All rights reserved.
//

#ifndef Student_h
#define Student_h

#include "LinkedList.h"
#include "App.h"

#define NAME_LEN 30

typedef struct {
    int         id;
    char        firstName[NAME_LEN];
    char        lastName[NAME_LEN];
    char        class[NAME_LEN];
    LinkedList* marks;
} Student ;

Student* student_new(int id, char* firstName, char*lastName, char* class,LinkedList* marks);

void student_free(Student* s);



#endif /* Student_h */
