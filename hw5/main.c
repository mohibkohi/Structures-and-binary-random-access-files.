//
//  main.c
//  hw5
//
//  Created by Mohib Kohi on 5/31/16.
//  Copyright © 2016 Mohib Kohi. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "animal.h"
#include <stdlib.h>
void searchId();
void deleteId();
void writeToFile();
void addAnimal();
int getAction();

//main
int main(int argc, const char * argv[]) {
    int select = getAction();
    
    while(select != 0) {
    
        if (select == 1) {
            addAnimal();
        } else if (select == 2) {
            deleteId();
        } else if (select == 3) {
            searchId();
        } else if (select == 4) {
            writeToFile();
        }else {
            printf("Wrong number enter again");
        }
        select = getAction();
    }
    return 0;
}

//seach the id.
void searchId() {
    int booleanFind = 0;
    short int searchId;
    short int findId;
    char name[20];
    
    printf("Enter id: ");
    scanf("%hu", &searchId);
    FILE *reads;
    reads = fopen("rescue.dat", "rb+");

    //move to the ids.
    long int offset = 22;
    fseek(reads, offset, SEEK_SET);
    fseek(reads, searchId * sizeof(struct animal_st) - sizeof(struct animal_st), SEEK_CUR);

    fread(&findId, sizeof(findId), 1, reads);
    
    //if the ids are matching
    if (searchId == findId) {
        fread(name, sizeof(name), 1, reads);
        //if the name is not unknown
        if (strcmp(name, "unknown") != 0) {
            animalPtr tempAnimal = createAnimal();
            tempAnimal->id = findId;
            strcpy(tempAnimal-> name,name);
            fread(&tempAnimal->species, sizeof(tempAnimal->species), 1, reads);
            fread(&tempAnimal->size, sizeof(tempAnimal->size), 1, reads);
            fread(&tempAnimal->age, sizeof(tempAnimal->age), 1, reads);
            printf("%hu, ", tempAnimal -> id);
            printf("%s, ", tempAnimal -> name);
            printf("%s, ", tempAnimal -> species);
            printf("%c, ", tempAnimal -> size);
            printf("%hu\n\n", tempAnimal -> age);
            free(tempAnimal);
            tempAnimal = NULL;
            booleanFind = 1;
        }
    }
    if (booleanFind == 0) {
        printf("Error no id match found\n");
    }
            
    fclose(reads);
}

//Delted the id.
void deleteId() {
    FILE *reads;
    short int searchId;
    short int findId;

    short int numberAvailibleId;
    
    int booleanUnknown = 0;
    
    printf("Enter id: ");
    scanf("%hu", &searchId);
    
    //max ids availible is 10
    short int idAvail[10];
    
    //open file to start reading.
    reads = fopen("rescue.dat", "rb+");
    
    //read the ids.
    fread(&numberAvailibleId, sizeof(short int), 1, reads);
    int i;
    
    for (i = 0; i < 10; i++) {
        fread(&idAvail[i], sizeof(idAvail[0]), 1, reads);
        if (idAvail[i] == searchId) {
            booleanUnknown = 1;
            //break;
        }
    }
    if (booleanUnknown == 0) {
        //char array to store the name.
        char name[20];
        
        //char array to store the amount of ids.
        char idAmount[2];
        
        //char array to store all the ids.
        char allId[20];
        
        //move to the ids.
        long int offset = 22;
        fseek(reads, offset, SEEK_SET);
        
        fseek(reads, searchId * sizeof(struct animal_st) - sizeof(struct animal_st), SEEK_CUR);
        
        //read the id from file.
        fread(&findId, sizeof(findId), 1, reads);
        
        if (searchId == findId) {
            //read the name.
            fread(name, sizeof(name), 1, reads);
            //if name exiset.
            if (strcmp(name, "unknown") != 0) {
                //move back to the begigning ofthe name.
                fseek(reads, -sizeof(name), SEEK_CUR);
                //write unknown to the file.
                fwrite("unknown", sizeof(name), 1, reads);
                
                //rewind to the start of the fie.
                fseek(reads, 0, SEEK_SET);

                //copy the new delted id.
                idAvail[numberAvailibleId] = searchId;
                
                numberAvailibleId++;
                
                //copy the number of ids.
                memcpy(idAmount, (char*)&numberAvailibleId, 2);
                
                //write the new amount of ids.
                fwrite(&idAmount, sizeof(short int), 1, reads);
                
                int count = 0;
                //move the ids into the temporary char array.
                for (i = 0; i < 20; i+=2) {
                    allId[i] = idAvail[count] & 0xff;
                    allId[i + 1] = (idAvail[count] >> 8) & 0xff;
                    count++;
                }
                fwrite(&allId, sizeof(short int) * 10, 1, reads);
                printf("Deleted ID: %hu\n\n", searchId);
                
            } else {
                booleanUnknown = 1;
            }
        } else {
            booleanUnknown = 1;
        }
        
        
    }
    //If no matched id was found.
    if (booleanUnknown == 1) {
        printf("Error no id match found\n");
    }
    fclose(reads);
}

//Add the new animal.
void addAnimal() {
    
    animalPtr animalPtr = createAnimal();
    FILE *reads;
    
    //char array to store all the ids.
    char allId[20];
    
    //char array to store the amount of ids.
    char idAmount[2];
    
    //max ids availible is 10
    short int idAvail[10];
    
    //max ids availible is 10
    short int newId[10];
    
    short int numberAvailibleId;
    
    //open file to start reading.
    reads = fopen("rescue.dat", "rb+");
    
    //read the ids.
    fread(&numberAvailibleId, sizeof(short int), 1, reads);
    //the id to add to.
    short int idToAdd;
    
    if (numberAvailibleId > 0 && numberAvailibleId <= 10) {
        int i;
        for (i = 0; i < 10; i++) {
            fread(&idAvail[i], sizeof(idAvail[0]), 1, reads);
        }
        idToAdd =idAvail[0];
        
        //shift the array values.
        for (i = 0; i < 10; i++) {
            newId[i] = idAvail[i+1];
        }
        newId[9] = 0;
        numberAvailibleId--;
        
    } else {
        int i;
        for (i = 0; i < 10; i++) {
            newId[i] = 0;
        }
        
        //move to the last animal
        fseek(reads, -sizeof(struct animal_st), SEEK_END);
        //read the last id.
        fread(&idToAdd, sizeof(numberAvailibleId), 1, reads);
        //add one to make it the new id.
        idToAdd++;
    }
    
    //copy the number of ids.
    memcpy(idAmount, (char*)&numberAvailibleId, 2);
    
    printf("New animal at id: %hu\n", idToAdd);
    printf("Enter name: ");
    scanf(" %s", animalPtr->name);
    printf("Enter species: ");
    scanf(" %[^\n]s", animalPtr->species);
    printf("Enter size: ");
    scanf(" %c", &animalPtr->size);
    printf("Enter age: ");
    scanf(" %hu", &animalPtr->age);
    
    //rewind to the start of the fie.
    fseek(reads, 0, SEEK_SET);
    
    //write the new amount of ids.
    fwrite(&idAmount, sizeof(short int), 1, reads);
    
    int count = 0;
    int i;
    //move the ids into the temporary char array.
    for (i = 0; i < 20; i+=2) {
        allId[i] = newId[count] & 0xff;
        allId[i + 1] = (newId[count] >> 8) & 0xff;
        count++;
    }
    //write the new ids.
    fwrite(&allId, sizeof(short int) * 10, 1, reads);
    
    //skip to the new location.
    fseek(reads, idToAdd * sizeof(struct animal_st) - sizeof(struct animal_st), SEEK_CUR);
    char new_id_add[2];
    char new_age_add[2];
    char new_size_add[1];
    
    //copy the number of ids.
    memcpy(new_id_add, (char*)&idToAdd, 2);
    
    //copy new size.
    new_size_add[0] = animalPtr -> size;
    
    //copy new age
    memcpy(new_age_add, (char*)&animalPtr->age, 2);
    
    //wirte the new animal
    fwrite(&new_id_add, sizeof(idToAdd), 1, reads);
    fwrite(animalPtr -> name, sizeof(animalPtr -> name), 1, reads);
    fwrite(animalPtr -> species, sizeof(animalPtr -> species), 1, reads);
    
    fwrite(&new_size_add, sizeof(animalPtr ->size), 1, reads);
    
    fwrite(&new_id_add, sizeof(animalPtr ->age), 1, reads);
    
    printf("New Animal added.\n\n");
    free(animalPtr);
    animalPtr = NULL;
    fclose(reads);
}

//write to the csv.
void writeToFile() {
    
    //create new instance of animal.
    animalPtr animalPtr = createAnimal();
    //open file.
    FILE *reads = fopen("rescue.dat", "r");
    
    //  move to the ids.
    long int offset = 22;
    fseek(reads, offset, SEEK_SET);
    fseek(reads, animalPtr->id * sizeof(struct animal_st) - sizeof(struct animal_st), SEEK_CUR);
    
    // create a pointer to the file to write.
    FILE* wptr = fopen("animals.csv", "w");
    while (fread(&animalPtr->id, sizeof(animalPtr->id), 1, reads) == 1) {
        fread(&animalPtr->name, sizeof(animalPtr->name), 1, reads);
        fread(&animalPtr->species, sizeof(animalPtr->species), 1, reads);
        fread(&animalPtr->size, sizeof(animalPtr->size), 1, reads);
        fread(&animalPtr->age, sizeof(animalPtr->age), 1, reads);
        if(strcmp(animalPtr->name, "unknown") != 0) {
           // printf("%d,%s,%s,%c,%d\n", animalPtr->id, animalPtr->name, animalPtr->species,animalPtr->size, animalPtr->age);
            fprintf(wptr, "%d,%s,%s,%c,%d\n", animalPtr->id, animalPtr->name, animalPtr->species,animalPtr->size, animalPtr->age);
        }
    }
    free(animalPtr);
    animalPtr = NULL;
    fclose(wptr);
    fclose(reads);
}
/**
 * Ask user for an option.
 */
int getAction() {
    int temp;
    char instruction[] = "press:\n1 to add an animal\n2 to delete an animal\n3 search an animal\n4 to wirte animal information to ASCII.\n";
    printf("%s", instruction);
    printf("Enter 0 to quit\n\n");
    scanf(" %d", &temp);
    return temp;
}