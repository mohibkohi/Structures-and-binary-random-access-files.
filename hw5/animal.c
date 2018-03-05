//
//  animal.c
//  hw5
//
//  Created by Mohib Kohi on 5/31/16.
//  Copyright © 2016 Mohib Kohi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "animal.h"



animalPtr createAnimal() {
    
    animalPtr animal_ptr = malloc(sizeof (struct animal_st));
    
    
    return animal_ptr;
}

//void setId(animalPtr aPtr, short int theId) {
//    
//    aPtr->id = theId;
//}
//
//void setName(animalPtr aPtr, char theName[]) {
//    
//    strcpy(aPtr->name, theName);
//}
//
//void setSpecies(animalPtr aPtr, char theSpecies[]) {
//    
//    strcpy(aPtr->species, theSpecies);
//}
//
//void setSize(animalPtr aPtr, char theSize) {
//    
//    aPtr->size = theSize;
//}
//
//void setAge(animalPtr aPtr, int theAge) {
//    
//    aPtr->age = theAge;
//}
//
