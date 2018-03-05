//
//  animal.h
//  hw5
//
//  Created by Mohib Kohi on 5/31/16.
//  Copyright © 2016 Mohib Kohi. All rights reserved.
//

#ifndef animal_h
#define animal_h

#pragma pack(1)

struct animal_st {
    short int id;
    char name[20];
    char species[35];
    char size;
    short int age;
};


//animal pointer to struct animal.
typedef struct animal_st *animalPtr;

animalPtr createAnimal();


//void setId(animalPtr aPtr, short int theId);
//
//void setName(animalPtr aPtr, char theName[]);
//
//void setSpecies(animalPtr aPtr, char theSpecies[]);
//
//void setSize(animalPtr aPtr, char theSize);
//
//void setAge(animalPtr aPtr, int theAge)


#endif /* animal_h */
