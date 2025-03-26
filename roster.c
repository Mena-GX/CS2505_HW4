#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Add the student to the students array if there is space and return the current number of students
int add_student(FILE* in, FILE* out, char* students[], int current_students, int const max_students){

    char firstName[100];
    char lastName[100];

    //takes in the strings until a whitespace and assigns them
    fscanf(in, "%s %s", firstName, lastName);

    //Concatenates first and last name with a space in the middle
    strcat(firstName, " ");
    strcat(firstName, lastName);

    char *wholeName = firstName;
    

    fprintf(out, "Command: add %s\n", wholeName);
    
    //if the class is at capacity, then print that we can't add any more students
    //and return current student
    //if not, continue on
    if(current_students == max_students){
        fprintf(out, "    Student %s was not added. The class is already at capacity.\n", wholeName);
        return current_students;
    }

    //allocate memory to the spot in the students array
    students[current_students] = (char *)malloc(strlen(wholeName) * sizeof(char));
    //copy the string to that spot in the array
    strcpy(students[current_students], wholeName);
    fprintf(out, "    %s was added. %d spot(s) remain.\n", wholeName, max_students-current_students-1);
    return current_students+1;


}

//If the student exists in the students array, remove them and move all the students ahead of it back
//by one and return current students, if not, state that and return current students
int remove_student(FILE* in, FILE* out, char* students[], int current_students, int const max_students){
    char firstName[100];
    char lastName[100];

    //takes in the first two strings and assigns them
    fscanf(in, "%s %s", firstName, lastName);

    //concatenates the name with a space in the middle
    strcat(firstName, " ");
    strcat(firstName, lastName);

    fprintf(out, "Command: remove %s\n", firstName);

    //iterates through all the current students to find the student we want to remove
    //if it finds it, frees that spot and moves all the students in front of it back one
    for(int i = 0; i < current_students; i++){
        if(strcmp(firstName, students[i]) == 0){
            free(students[i]);

            for(int j = i; j < current_students-1; j++){
                students[j] = students[j+1];
            }

            fprintf(out, "Student %s removed. The course now has %d seats remaining.", firstName, max_students-current_students+1);
            return current_students-1;
            
        }
    }
    
    //if no match was found, print out statement and return current students
    fprintf(out, "    No student named %s was found to remove.\n", firstName);
    return current_students;
    
}

//delete all the students in the class and free up that spot in memory
void delete_class(FILE* out, char* students[], int* current_students){
    fprintf(out,"Command: delete\n");

    //Go through all the current students
    //print out their name before freeing that space in memory
    for (int i= 0; i < *current_students; i++) {
        fprintf(out, "    %s removed in class delete.\n", students[i]);
        free(students[i]); 
    }

    //set current students to zero
    *current_students = 0;

    fprintf(out, "    Class was restarted and reopened for enrollment.\n\n");
}

//Take in two names
//Look for the first name and if found, replace it with the second name
//If not found report that the name wasn't found
void modify_name(FILE* in, FILE* out, char* students[], int current_students){
    char firstName[100];
    char firstlastname[100];

    char colon[2];

    char firstname[100];
    char seclastname[100];

    //take in the names
    fscanf(in, "%s %[^:] %1s %s %s", firstName, firstlastname, colon, firstname, seclastname);
    fprintf(out, "Command: modify %s %s:%s %s\n", firstName, firstlastname, firstname, seclastname);


    //concatenate the first name together with a space
    strcat(firstName, " ");
    strcat(firstName, firstlastname);

    //concatenate the second name together with a space
    strcat(firstname, " ");
    strcat(firstname, seclastname);

    char* wholefirstName = firstName;
    char* wholesecName = firstname;

    int check = 0;

    //check all the students to find the first name
    //if the name is found, change it to the second name
    for(int i = 0; i < current_students; i++){
        if(strcmp(wholefirstName, students[i]) == 0){
            fprintf(out, "    Student %s name modified to %s.\n", wholefirstName, wholesecName);
            
            strcpy(students[i], wholesecName);

            check = 1;
            break;

        }
        break;
    }

    //if the name isn't found, print out that it wasn't found
    if(check == 0){
        fprintf(out, "    No student with name %s found.\n", wholefirstName);
    }

}

//display all the students currently enrolled in the class and their
//position in the class
void display_class(FILE* out, char* students[], int current_students){
    fprintf(out, "Command: display\n");
    fprintf(out,"   Currently Enrolled:\n");

    //go through the students one by one and print out their name and 
    //current position in class
    for(int i = 0; i < current_students; i++){
        fprintf(out,"    Student %d: %s\n", i+1, students[i]);
    }
}