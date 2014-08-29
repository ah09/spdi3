#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    int generation;
    char chromosome;
    int numberOfChildren;
    struct node* parentIs;
};

struct node* makeFamily() {
    struct node* granddaughter = NULL;
    struct node* grandson = NULL;
    struct node* daughter = NULL;
    struct node* son = NULL;
    struct node* mother = NULL;
    granddaughter = malloc(sizeof(struct node));
    grandson = malloc(sizeof(struct node));
    daughter = malloc(sizeof(struct node));
    son = malloc(sizeof(struct node));
    mother = malloc(sizeof(struct node));
    granddaughter->generation = 3;
    granddaughter->chromosome = 'X';
    granddaughter->parentIs = daughter;
    grandson->generation = 3;
    grandson->chromosome = 'Y';
    grandson->parentIs = son;
    daughter->generation = 2;
    daughter->chromosome = 'X';
    daughter->parentIs = mother;
    son->generation = 2;
    son->chromosome = 'Y';
    son->parentIs = mother;
    mother->generation = 1;
    mother->chromosome = 'X';
    mother->parentIs = NULL;
    return grandson;
}

int Length(struct node* member) {
    /*struct node* current = parent;
    int count = 0;
    while (current != NULL) {
        count++;
        current = current->previous;
    }
    return count;*/
    return member->generation;
}

void lineage(struct node* member) {
    struct node* current = member;
    printf("new ");
    while (current != NULL) {
        printf("female member of generation #%d", current->generation);
        current = current->parentIs;
        if (current != NULL) {
            if(current->chromosome == 'X') {
                printf(",\ndaughter of ");
            }
            else {
                printf(",\nson of ");
            }
        }
    }
    printf("\n");
}

void deallocate2(struct node* member) {
    if (member == NULL) return;
    struct node* parent = member->parentIs;
    //printf("parent is %c\n", parent->chromosome);
    if (member->numberOfChildren != 2) {
        printf("deallocating member %c of generation %d\n", member->chromosome, member->generation);
        free(member);
        deallocate2(parent);
    }
    else {
        member->numberOfChildren = 1;
    }
}

void makeNewFamily(struct node* parent) {
    if (parent->generation < 5) {
        /*if (parent->chromosome == 'Y') {
            printf("deallocation starting with member %c of %d\n", parent->chromosome, parent->generation);
            deallocate(parent);
        }*/
        //else {
        srand(time(NULL));
        if (rand()%2 == 0) {
            parent->numberOfChildren = 1;
            struct node* member = NULL;
            member = malloc(sizeof(struct node));
            member->generation = parent->generation+1;
            if (rand()%2 == 0) {
                member->chromosome = 'X';
            }
            else {
                member->chromosome = 'Y';
            }
            member->numberOfChildren = 0;
            member->parentIs = parent;
            lineage(member);
            if (member->chromosome == 'Y') {
                deallocate2(member);
            }
            else {
                makeNewFamily(member);
            }
        }
        else {
            parent->numberOfChildren = 2;
            struct node* member1 = NULL;
            member1 = malloc(sizeof(struct node));
            member1->generation = parent->generation+1;
            if (rand()%2 == 0) {
                member1->chromosome = 'X';
            }
            else {
                member1->chromosome = 'Y';
            }
            member1->numberOfChildren = 0;
            member1->parentIs = parent;
            lineage(member1);
            if (member1->chromosome == 'Y') {
                deallocate2(member1);
            }
            else {
                makeNewFamily(member1);
            }
            struct node* member2 = NULL;
            member2 = malloc(sizeof(struct node));
            member2->generation = parent->generation+1;
            if (rand()%2 == 0) {
                member2->chromosome = 'X';
            }
            else {
                member2->chromosome = 'Y';
            }
            member2->numberOfChildren = 0;
            member2->parentIs = parent;
            lineage(member2);
            if (member2->chromosome == 'Y') {
                deallocate2(member2);
            }
            else {
                makeNewFamily(member2);
            }
        }
        //}
    }
    else {
        printf("deallocate parentage\n");
        deallocate2(parent);
    }
}

struct node* addNewMember(struct node* parent, char gender) {
    struct node* member = NULL;
    member = malloc(sizeof(struct node));
    member->generation = parent->generation+1;
    member->chromosome = gender;
    member->parentIs = parent;
    lineage(member);
    return member;
}

int main1()
{
    struct node* mother;
    mother = malloc(sizeof(struct node));
    mother->generation = 1;
    mother->chromosome = 'X';
    mother->numberOfChildren = 0;
    mother->parentIs = NULL;
    makeNewFamily(mother);

    //struct node* myFamily = makeFamily();
    //addNewMember(myFamily, 'Y');
    return 0;
}

