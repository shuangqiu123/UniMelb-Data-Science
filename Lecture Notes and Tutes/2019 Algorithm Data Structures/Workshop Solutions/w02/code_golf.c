/* 
    This program was written by Richard Chad Sparrow 
    as a test case for AB-testing the hazard management
    system.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct hazard {
    char *description;
    void *extraData;
    int extraDataType;
    int id;
    char severityClass;
};

void printHazard(struct hazard *hazard);

int main(int argc, char **argv){
    struct hazard hazard1;
    struct hazard hazard2;
    struct hazard *lastHazard;
    
    /* Hazard data setup. */
    hazard1.description = "Brake service required.";
    hazard1.extraData = NULL;
    hazard1.extraDataType = 0;
    hazard1.id = 1;
    hazard1.severityClass = 'A';
    
    hazard2.description = "Unknown issue in fluid level.";
    hazard2.extraData = NULL;
    hazard2.extraDataType = 0;
    hazard2.id = 2;
    hazard2.severityClass = 'U';
    
    lastHazard = &hazard2;
    
    printf("Hazards after setup:\n");
    printHazard(&hazard1);
    printHazard(&hazard2);
    
    /* 
        The brake service hazard has been present for multiple
        services, so needs to be updated to severity class 'B'.
    */
    /* Original: hazard1.severityClass = 'B'; */
    *((char *)(((void *) &hazard1) + offsetof(struct hazard, severityClass))) = 'B';
    /*
    We want to access the severityClass of the struct hazard and assign 'B' to it.
    */

    /* CHANGE THE CODE HERE: */
    hazard1.severityClass = 'B';
    
    printf("Hazard 1 after class B severity update:\n");
    printHazard(&hazard1);
    
    /*
        The next hazard to be evaluted has been evaluated and
        its severity class has been found to be quite serious,
        class 'D'. As part of this issue, the id has also been
        increased to 3 and the hazard description has been 
        changed to "Fluid leak in tank 4".
    */
    /* Original: lastHazard->severityClass = 'D'; */
    *(char *)(((void *)lastHazard) + offsetof(struct hazard, severityClass)) = 'D';
    /* CHANGE THE CODE HERE: */
    lastHazard->severityClass = 'D';
    
    /* Original: lastHazard->description = "Fluid leak in tank 4"; */
    *(char **)(((void *)lastHazard) + offsetof(struct hazard, description)) = "Fluid leak in tank 4";
    /* CHANGE THE CODE HERE: */
    lastHazard->description = "Fluid leak in tank 4";
    
    printf("Hazard 2 after description and D-class update:\n");
    printHazard(&hazard2);
    
    return 0;
}

void printHazard(struct hazard *hazard){
    
    printf("Hazard %d: %s [Class %c, extraDataType: %d]\n", 
        hazard->id, hazard->description, hazard->severityClass, 
        hazard->extraDataType);
}