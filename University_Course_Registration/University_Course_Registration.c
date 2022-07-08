#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#define CODE_MAX 20
#define NAME_MAX 20
#define CREDIT_MAX 6   // maximum number of credits an student can add to his/her program
#define TXT_MAX 40

//-------------------------------------------------------------------------------STRUCTS
typedef struct courses {
    int capacity;
    int credit;
    char name[CODE_MAX];
    char code[CODE_MAX];
    int *registeredStd;         // registeredStd[capacity]
    int registeredStdNumber;
    struct courses *next;

}COURSE;

typedef struct students {
    int courseSum;
    int creditSum;
    int studentNumber;
    char name[NAME_MAX];
    char surName[NAME_MAX];
    struct students *next;
    struct students *prev;

}STUDENT;


//----------------------------------------------------------------------------------PROTOTYPES
void openCourse(COURSE **head, int *courseSize);
void displayCourseInfo(COURSE *head);
COURSE *searchNodeByString(COURSE *head, char chosenCode[CODE_MAX]);
void closeCourse(STUDENT **head2, COURSE **head, int *courseSize, char myTime[], int *ID);
void displayAllCourses(COURSE *head);
void bubbleSortCourses(COURSE *head);
void swapCourse(COURSE *p1, COURSE *p2);
void addStudent(STUDENT **head, int *studentSize);
STUDENT *searchNodeByNumber(STUDENT *head, int chosenNumber);
void displayStudentInfo(STUDENT *head);
void displayAllStudents(STUDENT *head);
void removeStudent(STUDENT **head, int *studentSize);
void swapStudent(STUDENT *p1, STUDENT *p2);
void bubbleSortStudents(STUDENT *head);
void writeToCourseFile(COURSE *head, int courseSize);
void writeToStudentFile(STUDENT *head, int studentSize);
void readFromCoursesFile(COURSE **head, int *courseSize);
void readFromStudentsFile(STUDENT **head, int *studentSize);
void addCourse(STUDENT **head2, COURSE **head, int courseSize, char myTime[], int *ID);
void dropCourse(STUDENT **head2, COURSE **head, int courseSize, char myTime[], int *ID);
int displayStudentProgram(COURSE *head, int chosenStudentNumber, int courseSize);
void writeToProgramFile(COURSE *head, int chosenStudentNumber, int courseSize);
void displayClassList(STUDENT *head2, COURSE *head);
void sortArray(int registeredStd[], int capacity);
void readFromSCR(STUDENT **head2, COURSE **head, int courseSize,int *ID);
void writeClassList(STUDENT *head2, COURSE *head, char tmpCourseCode[]);
void dropCourse_insideFunction(STUDENT **head2, COURSE **head, int courseSize, char myTime[], int *ID, int tmpStudentNumber, char tmpCourseCode[]);


//####################################################################################################
//############################################### MAIN ###############################################
//####################################################################################################

int main(void) {
    //-------------------------------------------------------Variables for Main and Menu
    COURSE *head;   
    STUDENT *head2; 
    head = NULL;    //head for COURSE
    head2 = NULL;   //head for STUDENT
    int option;     // for menu
    int courseSize=0, studentSize=0;
    int i;
    int tmpNumber, flag=0;
    int ID=0;
    
    //----------------------------------------------------------Variables for Date
    time_t rawtime;
    struct tm *info;
    time( &rawtime );
    info = localtime( &rawtime );
    
    char day[3], month[3], year[5];
    char myTime[20];

    itoa(info->tm_mday, day, 10);
    itoa(info->tm_mon, month, 10);
    itoa((info->tm_year + 1900), year, 10);
    
    strcpy(myTime, day);
    strcat(myTime, "/");
    strcat(myTime, month);
    strcat(myTime, "/");
    strcat(myTime, year);
    

    //----------------------------------------------------Read txt files, Bubble sort linked lists, Write to txt files
    readFromCoursesFile(&head, &courseSize);
    readFromStudentsFile(&head2, &studentSize);
    readFromSCR(&head2, &head, courseSize, &ID);
    bubbleSortCourses(head);
    bubbleSortStudents(head2);
    //writeToCourseFile(head, courseSize);
    //writeToStudentFile(head2, studentSize);
    //printf("works\n");
    
    
    //----------------------------------------------------------------------------------------MENU
    do
    {
        printf("\n------------------ MENU ---------------------------\n");
        printf("1. Open a Course\t2. Close a Course\n");
        printf("3. Add Student\t\t4. Remove Student\n");
        printf("5. Add Course to Student's Program\n");
        printf("6. Drop Course from Student's Program\n");
        printf("7. Display Information of a Course\n");
        printf("8. Display All Courses\n");
        printf("9. Display Information of an Student\n");
        printf("10. Display All Students\n");
        printf("11. Display Program of an Student\n");
        printf("12. Display and Write Class List\n");
        printf("\n0. Exit\n-------------------------------------------------\n");
        scanf("%d", &option);

        if (option == 1)
        {
            openCourse(&head, &courseSize);
            bubbleSortCourses(head);
            writeToCourseFile(head, courseSize);
        }
        else if (option == 2)
        {
            displayAllCourses(head);
            closeCourse(&head2, &head, &courseSize, myTime, &ID);
            writeToStudentFile(head2, studentSize);
            bubbleSortCourses(head);
            writeToCourseFile(head, courseSize);
        }
        else if (option == 3)
        {
            addStudent(&head2, &studentSize);
            bubbleSortStudents(head2);
            writeToStudentFile(head2, studentSize);
        }
        else if (option == 4)
        {
            removeStudent(&head2, &studentSize);
            bubbleSortStudents(head2);
            writeToStudentFile(head2, studentSize);
        }
        else if (option == 5)
        {
            addCourse(&head2, &head, courseSize, myTime, &ID);  // writeToProgramFile() is called inside addCourse()
            writeToCourseFile(head, courseSize);  
            writeToStudentFile(head2, studentSize);
        }
        else if (option == 6)
        {
            dropCourse(&head2, &head, courseSize, myTime, &ID);  // writeToProgramFile() is called inside dropCourse()
            writeToCourseFile(head, courseSize);
            writeToStudentFile(head2, studentSize);
        }
        
        else if (option == 7)
        {
            bubbleSortCourses(head);
            displayCourseInfo(head);
        }
        else if (option == 8)
        {
            bubbleSortCourses(head);
            displayAllCourses(head);

        }
        else if (option == 9)
        {
            bubbleSortStudents(head2);
            displayStudentInfo(head2);
        }
        else if (option == 10)
        {
            bubbleSortStudents(head2);
            displayAllStudents(head2);
        }
        else if (option == 11)
        {
            printf("Please enter Student Number: ");
            scanf("%d", &tmpNumber);
            flag = displayStudentProgram(head, tmpNumber, courseSize);
            if (flag == 0)
            {
                printf("Student Number is Wrong OR Program is Empty!\n");
            }
        }
        else if (option == 12)
        {
            displayClassList(head2, head);
        }
 
    } while (option != 0);


    // Free the allocated memory for course linked list
    for ( i = 0; i < courseSize; i++)
    {
        free(head->registeredStd);
        free(head);
        head = head->next;
    }


    //printf("\nStudentSize=%d\tCourseSize=%d\n", studentSize, courseSize);
    

    return 0;
}

//#########################################################################################################
//############################################### FUNCTIONS ###############################################
//#########################################################################################################

void openCourse(COURSE **head, int *courseSize) {       

    char newCode[CODE_MAX];
    char newName[CODE_MAX];
    int newCapacity;
    int newCredit;
    COURSE *tmp;
    
    printf("Enter course Code: ");
    scanf("%s", newCode);
    tmp = searchNodeByString(*head, newCode);    // if the node is found , tmp=adressOfNode. if the node is not found, tmp=NULL
    
    if (tmp == NULL)   // if tmp->code = NULL, it means there is no duplicate course
    {
        printf("Enter course Name: ");
        scanf("%s", newName);
        printf("Enter course Capacity: ");
        scanf("%d", &newCapacity);
        printf("Enter course Credit: ");
        scanf("%d", &newCredit);

        COURSE *newCourse;                  
        newCourse = (COURSE*)malloc(1*sizeof(COURSE)); 
        strcpy(newCourse->code, newCode);
        strcpy(newCourse->name, newName);
        newCourse->capacity = newCapacity;
        newCourse->registeredStd = (int*)calloc(newCapacity, sizeof(int));   // allocate memory for registeredStd[] in the size of Capacity
        newCourse->registeredStdNumber = 0; 
        newCourse->credit = newCredit;
        newCourse->next = *head;    
        *head = newCourse;          // course is added to the front of list

        (*courseSize)++;

        printf("\nCourse Succesfully Opened!");
    }
    else printf("It is a Duplicate Course. %s CAN NOT BE ADDED!", newCode);
    
}


void closeCourse(STUDENT **head2, COURSE **head, int *courseSize, char myTime[], int *ID) {

    COURSE *tmp, *curNode, **constHead=head;
    char chosenCode[CODE_MAX];
    int i;

    if ((*courseSize) == 0)
    {
        printf("There is No Course in the Program to be Closed!");
        return;
    }

    printf("Enter Code: ");
    scanf("%s", chosenCode);

	if(strcmp((*head)->code, chosenCode) == 0)  // if the data we want to delete, is the first node then the node before the node to be deleted (curNode) = head
    {                                              // so we use an if 
        tmp = *head;

        // When a course is closed , that course must be dropped from every students' program
        for ( i = 0; i < tmp->capacity; i++)
        {
            if (tmp->registeredStd[i] != 0)
            {
                printf("\n%d  %s\n", tmp->registeredStd[i], tmp->code);
                dropCourse_insideFunction(head2, head, *courseSize, myTime, ID, tmp->registeredStd[i], tmp->code);
            }
            
        }
        
		*head = (*head)->next;
        free(tmp->registeredStd);               // first free() the registredStd[]
		free(tmp);                             // free() deletes the previously allocated node
		printf("%s has been Closed Successfully!\n", chosenCode);

        (*courseSize)--;
	}
	else
    {
		curNode=*head;
        //the list has only next , not previous(singly linked list). so curNode is the node before the node to be deleted
		while(curNode->next!=NULL && strcmp(curNode->next->code, chosenCode) != 0)  
        {
			curNode = curNode->next;
	    }
		if(curNode->next!=NULL)
        {
            tmp = curNode->next;

            for ( i = 0; i < tmp->capacity; i++)
            {
                if (tmp->registeredStd[i] != 0)
                {
                    printf("\n%d\n", tmp->registeredStd[i]);
                    dropCourse_insideFunction(head2, head, *courseSize, myTime, ID, tmp->registeredStd[i], tmp->code);
                }
            }

			curNode->next=curNode->next->next;
            free(tmp->registeredStd);               // first free() the registered[]
			free(tmp);                              // free() deletes the previously allocated node
			printf("%s has been Closed Successfully.\n", chosenCode);

            (*courseSize)--;
		}
		else
        {
			printf("There is no course with Code %s.", chosenCode);
		}
	}
}


COURSE *searchNodeByString(COURSE *head, char chosenCode[CODE_MAX]) {
    COURSE *curNode = head;
    
    while ((curNode != NULL) && (strcmp(curNode->code, chosenCode) != 0))   
    {
        curNode = curNode->next;
    }
    return curNode;     // returns adress of the node which is equal to adress of the first variable of the node(structure). 
}    


void displayCourseInfo(COURSE *head) {
    COURSE *tmp;
    char chosenCode[CODE_MAX];

    printf("Enter course Code: ");
    scanf("%s", chosenCode);
    tmp = searchNodeByString(head, chosenCode);
   
    printf("\n");  // decoration
    if (tmp != NULL)
    {
        printf("(code)(name)(capacity)(credit)(freeCapacity)\n");
        printf("%s\t%s\t%d\t%d\t%d", tmp->code, tmp->name, tmp->capacity, tmp->credit, (tmp->capacity)-(tmp->registeredStdNumber));
    }
    else printf("Course Not Found!");
    
}


void displayAllCourses(COURSE *head) {  

    COURSE *tmp = head;   
    printf("\n");  // decoration

    if (tmp == NULL)
    {
        printf("NO Course Added Yet!");
    }
    else
    {
        printf("(code)(name)(capacity)(credit)(freeCapacity)\n");
        while (tmp != NULL)
        {
            printf("%s\t%s\t%d\t%d\t%d\n", tmp->code, tmp->name, tmp->capacity, tmp->credit, (tmp->capacity)-(tmp->registeredStdNumber));
            tmp = tmp->next;
        }
        printf("\n");
    }
   
}


void bubbleSortCourses(COURSE *head) {
	int swapped;
	COURSE *ptr1;
	COURSE *lptr = NULL;

	/* Checking for empty list */
	if (head == NULL)
		return;

	do
	{
		swapped = 0;
		ptr1 = head;

		while (ptr1->next != lptr)
		{
			if (strcmp(ptr1->code, ptr1->next->code) > 0 )
			{
				swapCourse(ptr1, ptr1->next);       // using deep copy
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;

	}while (swapped == 1);
}

void swapCourse(COURSE *p1, COURSE *p2) {       // using deep copy
    char tmpChar[CODE_MAX];
    int tmpInt;
    int *tmpPtr;                 

    strcpy(tmpChar, p1->code);
    strcpy(p1->code, p2->code);
    strcpy(p2->code, tmpChar);

    strcpy(tmpChar, p1->name);
    strcpy(p1->name, p2->name);
    strcpy(p2->name, tmpChar);

    tmpInt = p1->capacity;
    p1->capacity = p2->capacity;
    p2->capacity = tmpInt;

    tmpInt = p1->credit;
    p1->credit = p2->credit;
    p2->credit = tmpInt;

    tmpInt = p1->registeredStdNumber;
    p1->registeredStdNumber = p2->registeredStdNumber;
    p2->registeredStdNumber = tmpInt;

    tmpPtr = p1->registeredStd;
    p1->registeredStd = p2->registeredStd;
    p2->registeredStd = tmpPtr;

}


void addStudent(STUDENT **head, int *studentSize) {
    int newStudentNumber;
    int newCourseSum = 0;
    int newCreditSum = 0;
    char newName[NAME_MAX];
    char newSurName[NAME_MAX];
    STUDENT *tmp;

    printf("Enter Student Number: ");
    scanf("%d", &newStudentNumber);
    tmp = searchNodeByNumber(*head, newStudentNumber);

    if (tmp == NULL)
    {
        printf("Enter Name and Surname respectively: ");
        scanf("%s %s", newName, newSurName); 

        STUDENT *newStudent;
        newStudent = (STUDENT*)malloc(1*sizeof(STUDENT));
        newStudent->studentNumber = newStudentNumber;
        strcpy(newStudent->name, newName);
        strcpy(newStudent->surName, newSurName);
        newStudent->courseSum = newCourseSum;
        newStudent->creditSum = newCreditSum;

        newStudent->next = *head;
        newStudent->prev = NULL;
        if ((*head) != NULL) 
        {
            (*head)->prev = newStudent;
        }
        *head = newStudent;   
        
        (*studentSize)++;

        printf("Student Added Successfully!");
    }
    else printf("There is a Duplicate Student Number! %d CAN NOT BE ADDED!", newStudentNumber);
    
}


STUDENT *searchNodeByNumber(STUDENT *head, int chosenNumber) {

    STUDENT *curNode = head;
    
    while ((curNode != NULL) && (curNode->studentNumber != chosenNumber))   
    {
        curNode = curNode->next;
    }
    return curNode;     // returns adress of the node which is equal to adress of the first variable of the node
}    


void displayStudentInfo(STUDENT *head) {

    STUDENT *tmp;
    int chosenStudentNumber;

    printf("Enter Student Number: ");
    scanf("%d", &chosenStudentNumber);
    tmp = searchNodeByNumber(head, chosenStudentNumber);

    printf("\n");  // decoration
    if (tmp != NULL)
    {
        printf("(number)(name)(surname)(courseSum)(creditSum)\n");
        printf("%d %s %s\t %d\t\t%d", tmp->studentNumber, tmp->name, tmp->surName, tmp->courseSum, tmp->creditSum);
    }
    else printf("Student Not Found!");
    
}


void displayAllStudents(STUDENT *head) {  

    STUDENT *tmp = head;   

    printf("\n");  // decoration
    if (tmp == NULL)
    {
        printf("NO Student Added Yet!");
    }
    else
    {
        printf("(number)(name)(surname)(courseSum)(creditSum)\n");
        while (tmp != NULL)
        {
            printf("%d %s %s\t %d\t\t%d\n", tmp->studentNumber, tmp->name, tmp->surName, tmp->courseSum, tmp->creditSum);
            tmp = tmp->next;
        }
    }
   
}


void removeStudent(STUDENT **head, int *studentSize) {
    STUDENT *curNode;
    int chosenNumber;
    char extension[TXT_MAX];

    if ((*studentSize) == 0)
    {
        printf("There is No Student to be Removed!");
        return;
    }
    

    printf("Enter Student Number: ");
    scanf("%d", &chosenNumber);

    itoa(chosenNumber, extension, 10);
    strcat(extension, "_Program.txt");
    remove(extension);

	if((*head)->studentNumber == chosenNumber)  // if the node to be deleted is the first node
    {                                               
		curNode = *head;                   
		*head = (*head)->next;  // the node to be deleted was the first node. after this line head is pointing to null. no need to change prev...                 
		free(curNode);                                 // free() deletes the previously allocated node
		printf("%d has been Removed Successfully\n", chosenNumber);

        (*studentSize)--;
	}
	else
    {
		curNode=*head;
		while(curNode!=NULL && (curNode->studentNumber != chosenNumber) )  
        {
			curNode = curNode->next;
	    }
        if (curNode == NULL)       // if there is no node with given data and curNode=NULL
        {
            printf("There is no Student with Number %d.", chosenNumber);
        }
		else if(curNode->next!=NULL)         // if the node is a middle node
        {
            curNode->next->prev = curNode->prev;
			curNode->prev->next = curNode->next;
			free(curNode);                              // free() deletes the previously allocated node
		    printf("%d has been Removed Successfully.\n", chosenNumber);

            (*studentSize)--;
		}
		else if (curNode->next == NULL)     // if the node is the last node
        {
            curNode->prev->next = curNode->next;
            printf("%d has been Removed Successfully.\n", chosenNumber);
            free(curNode);

            (*studentSize)--;
        }
	}
}


void bubbleSortStudents(STUDENT *head) {
	int swapped;
	STUDENT *ptr1;
	STUDENT *lptr = NULL; // left ptr

	/* Checking for empty list */
	if (head == NULL)
		return;

	do
	{
		swapped = 0;
		ptr1 = head;

		while (ptr1->next != lptr)
		{
			if (ptr1->studentNumber > ptr1->next->studentNumber )
			{
				swapStudent(ptr1, ptr1->next);       // using deep copy
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;

	}while (swapped == 1);
}


void swapStudent(STUDENT *p1, STUDENT *p2) {       // using deep copy
    char tmpChar[NAME_MAX];
    int tmpInt;

    strcpy(tmpChar, p1->name);
    strcpy(p1->name, p2->name);
    strcpy(p2->name, tmpChar);

    strcpy(tmpChar, p1->surName);
    strcpy(p1->surName, p2->surName);
    strcpy(p2->surName, tmpChar);

    tmpInt = p1->studentNumber;
    p1->studentNumber = p2->studentNumber;
    p2->studentNumber = tmpInt;

    tmpInt = p1->courseSum;
    p1->courseSum = p2->courseSum;
    p2->courseSum = tmpInt;

    tmpInt = p1->creditSum;
    p1->creditSum = p2->creditSum;
    p2->creditSum = tmpInt;

}


void writeToCourseFile(COURSE *head, int courseSize) {
    FILE *fptr;
    char tmpCode[CODE_MAX], tmpName[CODE_MAX];
    int tmpCredit, tmpCapacity;
    int i;

    fptr = fopen("Courses.txt", "w");
    if (fptr == NULL)
    {
        printf("ERROR! File Can not be Opened!");
        return;
    }

    for ( i = 0; i < courseSize-1; i++)  //i from zero to courseSize-1 , to prevent the last line from printing new line (/n)
    {
        strcpy(tmpCode, head->code);
        strcpy(tmpName, head->name);
        tmpCredit = head->credit;
        tmpCapacity = head->capacity;

        fprintf(fptr, "%s %s %d %d\n", tmpCode, tmpName, tmpCapacity, tmpCredit); 
        head = head->next;
    }

    strcpy(tmpCode, head->code);
    strcpy(tmpName, head->name);
    tmpCredit = head->credit;
    tmpCapacity = head->capacity;

    fprintf(fptr, "%s %s %d %d", tmpCode, tmpName, tmpCapacity, tmpCredit);  // it will not print new line (\n) to the last line
    head = head->next;
    
    fclose(fptr);
}


void writeToStudentFile(STUDENT *head, int studentSize) {
    FILE *fptr;
    int tmpNumber, tmpCourse, tmpCredit;
    char tmpName[NAME_MAX], tmpSurname[NAME_MAX];
    int i;

    if (head == NULL)   // if no students added yet , no need to write to students file.
    {
        return;
    }

    fptr = fopen("StudentsList.txt", "w");
    if (fptr == NULL)
    {
        printf("ERROR! File Can not be Opened!");
        return;
    }

    
    for ( i = 0; i < studentSize-1; i++)   //i from zero to studentSize-1 , to prevent the last line from printing new line (/n)
    {
        strcpy(tmpName, head->name);
        strcpy(tmpSurname, head->surName);
        tmpNumber = head->studentNumber;
        tmpCourse = head->courseSum;
        tmpCredit = head->creditSum;

        fprintf(fptr, "%d %s %s %d %d\n", tmpNumber, tmpName, tmpSurname, tmpCourse, tmpCredit);
        head = head->next;
    }

    strcpy(tmpName, head->name);
    strcpy(tmpSurname, head->surName);
    tmpNumber = head->studentNumber;
    tmpCourse = head->courseSum;
    tmpCredit = head->creditSum;

    fprintf(fptr, "%d %s %s %d %d", tmpNumber, tmpName, tmpSurname, tmpCourse, tmpCredit); // it will not print new line (\n) to the last line
    head = head->next;  
    
    fclose(fptr);
}


void readFromCoursesFile(COURSE **head, int *courseSize) {       
    char newCode[CODE_MAX];
    char newName[CODE_MAX];
    char tmpCredit[CODE_MAX];
    char tmpCapacity[CODE_MAX];
    int newCapacity;
    int newCredit;
    FILE *fptr;
    
    fptr = fopen("Courses.txt", "r");
    if (fptr == NULL)   // at the begining there is no Course.txt file to read frrom
    {                   // as we opened the file in read-only mode , if the file does not exist , fopen() returns NULL
        return;  
    }
    
    while (feof(fptr) == 0)
    {
        fscanf(fptr, "%s", newCode);

        fscanf(fptr, "%s", newName);

        fscanf(fptr, "%s", tmpCapacity);
        newCapacity = atoi(tmpCapacity);

        fscanf(fptr, "%s", tmpCredit);
        newCredit = atoi(tmpCredit);

        COURSE *newCourse;                  
        newCourse = (COURSE*)malloc(1*sizeof(COURSE)); 
        strcpy(newCourse->code, newCode);
        strcpy(newCourse->name, newName);
        newCourse->capacity = newCapacity;
        newCourse->registeredStd = (int*)calloc(newCapacity, sizeof(int));  // allocate memory for registeredStd[] in size of Capacity
        newCourse->registeredStdNumber = 0;
        newCourse->credit = newCredit;
        newCourse->next = *head;
        *head = newCourse;

        (*courseSize)++;
    }
    
    fclose(fptr);
}


void readFromStudentsFile(STUDENT **head, int *studentSize) {
    int newStudentNumber;
    int newCourseSum;
    int newCreditSum;
    char newName[NAME_MAX];
    char newSurName[NAME_MAX];
    char tmpCourseSum[NAME_MAX];
    char tmpCreditSum[NAME_MAX];
    char tmpStudentNumber[NAME_MAX];
    FILE *fptr;

    fptr = fopen("StudentsList.txt", "r");
    if (fptr == NULL)
    {
        return;         // at the begining there is no StudentsList.txt file to read frrom
                         // as we opened the file in read-only mode , if the file does not exist , fopen() returns NULL
    }
   
    while (feof(fptr) == 0)
    {
        fscanf(fptr, "%s", tmpStudentNumber);
        newStudentNumber = atoi(tmpStudentNumber);

        fscanf(fptr, "%s", newName);

        fscanf(fptr, "%s", newSurName);

        fscanf(fptr, "%s", tmpCourseSum);       // only for iterating cursor (course sum will be set to 0)
        newCourseSum = atoi(tmpCourseSum);      // this value will not be used. it can be commented

        fscanf(fptr, "%s", tmpCreditSum);       // only for iterating cursor (credit sum will be set to 0)
        newCreditSum = atoi(tmpCreditSum);      // this value will not be used. it can be commented

        STUDENT *newStudent;
        newStudent = (STUDENT*)malloc(1*sizeof(STUDENT));
        newStudent->studentNumber = newStudentNumber;
        strcpy(newStudent->name, newName);
        strcpy(newStudent->surName, newSurName);
        newStudent->courseSum = 0;                      // set course sum to 0
        newStudent->creditSum = 0;                      // set credit sum to 0
        newStudent->next = *head;
        newStudent->prev = NULL;
        if ((*head) != NULL) 
        {
            (*head)->prev = newStudent;
        }

        *head = newStudent;   

        (*studentSize)++;
        
    }
        
    fclose(fptr);
}


void addCourse(STUDENT **head2, COURSE **head, int courseSize, char myTime[], int *ID) {
    int tmpStudentNumber;
    char tmpCourseCode[CODE_MAX];
    char status[CODE_MAX] = "Registered";
    STUDENT *curStudent;
    COURSE *curCourse;
    FILE *fptr;

    fptr = fopen("StudentCourseRegistration.txt", "a");

    printf("Please Enter Your Student Number: ");
    scanf("%d", &tmpStudentNumber);

    curStudent = searchNodeByNumber(*head2, tmpStudentNumber);
    if (curStudent == NULL)
    {
        printf("Student not Found!");
        return;
    }

    displayAllCourses(*head);
    printf("\nChoose one of the Courses by Code(First Column): ");
    scanf("%s", tmpCourseCode);

    curCourse = searchNodeByString(*head, tmpCourseCode);
    if (curCourse == NULL)
    {
        printf("Course does not EXIST!");
        return;
    }

    if ((curCourse->capacity)-(curCourse->registeredStdNumber) == 0)
    {
        printf("There is no Capacity for this Course!");
        return;
    }
    
    if ((curStudent->creditSum)+(curCourse->credit) > CREDIT_MAX)
    {
        printf("You have Reached Maximum Credit! Course Can not be added.\n");
        return;
    }

    // next line , fills the registeredStd[] with studentNumber from the END of array(its filled from last index to first index)!
    curCourse->registeredStd[(curCourse->capacity)-(curCourse->registeredStdNumber)-1] = curStudent->studentNumber;  
    (curCourse->registeredStdNumber)++;                            
    (curStudent->courseSum)++;                          
    (curStudent->creditSum) = (curStudent->creditSum) + (curCourse->credit);
    //printf("Course Added Succesfuly! %d", curCourse->registeredStd[(curCourse->capacity)-(curCourse->registeredStdNumber)]);
    writeToProgramFile(*head, curStudent->studentNumber, courseSize);   // updates students program text file
    //printf("here\n");
    sortArray(curCourse->registeredStd, curCourse->capacity);           //sortArray(registeredStd[], capacity) and then
    writeClassList(*head2, *head, tmpCourseCode);                       // updates class list text file
    
    (*ID)++;

    if ((*ID) == 1)     // to avoid new line at the end of the file
    {
        fprintf(fptr, "%d %s %d %s %s", *ID, curCourse->code, curStudent->studentNumber, myTime, status);
    }
    else fprintf(fptr, "\n%d %s %d %s %s", *ID, curCourse->code, curStudent->studentNumber, myTime, status);
    
    printf("Course Added Succesfully!\n");

    fclose(fptr);
}


void dropCourse(STUDENT **head2, COURSE **head, int courseSize, char myTime[], int *ID) {
    
    int tmpStudentNumber;
    char tmpCourseCode[CODE_MAX];
    char status[CODE_MAX] = "Dropped";
    STUDENT *curStudent;
    COURSE *curCourse;
    int i=0, limit, flag=0, flag2=0;
    FILE *fptr;

    fptr = fopen("StudentCourseRegistration.txt", "a");

    printf("Please Enter Your Student Number: ");
    scanf("%d", &tmpStudentNumber);

    curStudent = searchNodeByNumber(*head2, tmpStudentNumber);
    if (curStudent == NULL)
    {
        printf("Student not Found!\n");
        return;
    }

    flag = displayStudentProgram(*head, tmpStudentNumber, courseSize);
    if (flag == 0)
    {
        printf("Your Program is Empty.\n");
        return;
    }
    
    printf("\nPlease enter Course Code: ");
    scanf("%s", tmpCourseCode);

    curCourse = searchNodeByString(*head, tmpCourseCode);
    if (curCourse == NULL)
    {
        printf("Course Not Found! \n");
        return;
    }
    
    limit = curCourse->capacity;
    while (i < limit && flag2 == 0)
    {
        if (curCourse->registeredStd[i] == tmpStudentNumber)
        {
            curCourse->registeredStd[i] = 0;
            (curCourse->registeredStdNumber)--;
            (curStudent->courseSum)--;
            curStudent->creditSum = (curStudent->creditSum) - curCourse->credit;
            flag2 = 1;

            writeToProgramFile(*head, curStudent->studentNumber, courseSize);   // updates students program text file
            sortArray(curCourse->registeredStd, curCourse->capacity);   //sortArray(registeredStd[], capacity) and then 
            writeClassList(*head2, *head, tmpCourseCode);                       // updates class list text file

            (*ID)++;
            fprintf(fptr, "\n%d %s %d %s %s", *ID, curCourse->code, curStudent->studentNumber, myTime, status);
            printf("Course Droped Succesfully! %d\n", curCourse->registeredStd[i]);
            
        }
        i++;
    }
    if (flag2 == 0)
    {
        printf("%s is NOT in your Program!\n", tmpCourseCode);
    }
    
    fclose(fptr);
}


void sortArray(int registeredStd[], int capacity) {
    int i, j, minIndex, tmp;
    
    for ( i = 0; i < capacity-1; i++)
    {
        minIndex = i;
        for ( j = i+1; j < capacity; j++)
        {
            if (registeredStd[j] < registeredStd[minIndex])
            {
                minIndex = j;
            }
            
        }

        tmp = registeredStd[i];
        registeredStd[i] = registeredStd[minIndex];
        registeredStd[minIndex] = tmp;
        
    }
}


int displayStudentProgram(COURSE *head, int chosenStudentNumber, int courseSize) {
    int i, j, flag=0;

    printf("\n(code)(name)(capacity)(credit)\n");
    for ( i = 0; i < courseSize; i++)
    {        
        for ( j = 0; j < head->capacity; j++)
        {
            if (head->registeredStd[j] == chosenStudentNumber)
            {
                printf("%s\t%s\t%d\t%d\n", head->code, head->name, head->capacity, head->credit);
                flag = 1;
            }
        }
           
        head = head->next;
    }

    if (flag == 1)
    {
        return flag;
    }
    else return 0;
    
}


void writeToProgramFile(COURSE *head, int chosenStudentNumber, int courseSize) {
    int i, j, flag=0, counter=0;
    FILE *fptr3;
    char buffer[TXT_MAX];
    char extension[20] = "_Program.txt";
    itoa(chosenStudentNumber, buffer, 10);
    strcat(buffer, extension);

    fptr3 = fopen(buffer, "w");
    if (fptr3 == NULL)
    {
        printf("ERROR! File can not be Opened.");
    }
    
    for ( i = 0; i < courseSize; i++)
    {        
        for ( j = 0; j < head->capacity; j++)
        {
            if (head->registeredStd[j] == chosenStudentNumber)
            {
                counter++;
                if (counter == 1)   // if we are writing the first line in txt file , then we should avoid new line (\n)
                {
                    fprintf(fptr3, "%s\t%s\t%d\t%d", head->code, head->name, head->capacity, head->credit);  // avoid new line (\n)
                    flag = 1;
                }
                else    // if counter is bigger than 1 (if we are writing second or third line) we need too use new line (\n)
                {
                    fprintf(fptr3, "\n%s\t%s\t%d\t%d", head->code, head->name, head->capacity, head->credit); // uses new line (\n)
                    flag = 1;
                }       
            }
        }
        
        head = head->next;
    }

    fclose(fptr3);
}


void displayClassList(STUDENT *head2, COURSE *head) {
    char tmpCourseCode[CODE_MAX];
    int tmpStudentNumber;
    COURSE *curCourse;
    STUDENT *curStudent;
    int i;
    FILE *fptr;

    printf("Please enter Course Code: ");
    scanf("%s", tmpCourseCode);

    curCourse = searchNodeByString(head, tmpCourseCode);

    if (curCourse == NULL)
    {
        printf("Course does not Exist!");
        return;
    }

    strcat(tmpCourseCode, "_Class_List.txt");
    fptr = fopen(tmpCourseCode, "w");

    if (curCourse->registeredStdNumber == 0)
    {
        printf("List is Empty!");
        fprintf(fptr, "EMPTY");
    }
    else
    {
        for ( i = 0; i < curCourse->capacity; i++)
        {
            tmpStudentNumber = curCourse->registeredStd[i];
            
            if (tmpStudentNumber != 0)  // value of empty cells in registeredStd[] is 0 (beacause of calloc() and dropCourse()) and we wont print 0's to txt file.
            {
                curStudent = searchNodeByNumber(head2, tmpStudentNumber);
                printf("%d\t%s\t%s\n", tmpStudentNumber, curStudent->name, curStudent->surName);
                fprintf(fptr, "%d\t%s\t%s\n", tmpStudentNumber, curStudent->name, curStudent->surName);                
            }
        }        
    }

    fclose(fptr);
}

void writeClassList(STUDENT *head2, COURSE *head, char tmpCourseCode[]) {
    int tmpStudentNumber;
    COURSE *curCourse;
    STUDENT *curStudent;
    int i, counter=0;
    char extension[TXT_MAX];
    FILE *fptr5;

    curCourse = searchNodeByString(head, tmpCourseCode);
    strcpy(extension, tmpCourseCode);
    strcat(extension, "_Class_List.txt");
    fptr5 = fopen(extension, "w");

    if (curCourse->registeredStdNumber == 0)
    {
        fprintf(fptr5, "EMPTY");
    }
    else
    {
        for ( i = 0; i < curCourse->capacity; i++)
        {
            tmpStudentNumber = curCourse->registeredStd[i];
            
            if (tmpStudentNumber != 0)  // value of empty cells in registeredStd[] is 0 (beacause of calloc() and dropCourse()) and we wont print 0's to txt file.
            {
                counter++;
                if (counter == 1)   // if we are writing the first line of txt file , we should avoid new line (\n)
                {
                    curStudent = searchNodeByNumber(head2, tmpStudentNumber);
                    //printf("%d\t%s\t%s\n", tmpStudentNumber, curStudent->name, curStudent->surName);
                    fprintf(fptr5, "%d\t%s\t%s", tmpStudentNumber, curStudent->name, curStudent->surName); // avoids new line           
                }
                else    // if counter is bigger than 1 (if we are writing second o third line) we should USE new line (\n)
                {
                    curStudent = searchNodeByNumber(head2, tmpStudentNumber);
                    //printf("%d\t%s\t%s\n", tmpStudentNumber, curStudent->name, curStudent->surName);
                    fprintf(fptr5, "\n%d\t%s\t%s", tmpStudentNumber, curStudent->name, curStudent->surName);  //uses new line (\n)          
                }
                
                    
            }

        }        
        
    }

    fclose(fptr5);    
}


void readFromSCR(STUDENT **head2, COURSE **head, int courseSize, int *ID) {   // SCR == StudentCourseRegistration.txt
    char tmpStudentNumber[CODE_MAX], tmpID[CODE_MAX];
    int newID, newStudentNumber;
    int i, limit;
    char newCourseCode[CODE_MAX], newDate[CODE_MAX], newStatus[CODE_MAX];
    COURSE *curCourse;
    STUDENT *curStudent;
    FILE *fptr;

    fptr = fopen("StudentCourseRegistration.txt", "r");
    if (fptr == NULL)
    {
        return;   //at the begining we have not added any course to sny students program yet
                  // so there is no SCR.txt file, then NULL is assigned to fptr 
                  // because we opened program in read-only mode
    }
    
    while (feof(fptr) == 0)
    {
        fscanf(fptr, "%s", tmpID);
        newID = atoi(tmpID);
        (*ID) = newID;

        fscanf(fptr, "%s", newCourseCode);

        fscanf(fptr, "%s", tmpStudentNumber);
        newStudentNumber = atoi(tmpStudentNumber);

        fscanf(fptr, "%s", newDate);

        fscanf(fptr, "%s", newStatus);

        if (strcmp(newStatus, "Registered") == 0)
        {
            curCourse = searchNodeByString(*head, newCourseCode);
            curStudent = searchNodeByNumber(*head2, newStudentNumber);

            if (curCourse != NULL && curStudent != NULL)
            {
                // next line , fills the registeredStd[] with studentNumber from the END of array(its filled from last index to first index)!
                curCourse->registeredStd[(curCourse->capacity)-(curCourse->registeredStdNumber)-1] = curStudent->studentNumber;  
                (curCourse->registeredStdNumber)++;                            
                (curStudent->courseSum)++;                          
                (curStudent->creditSum) = (curStudent->creditSum) + (curCourse->credit);
                writeToProgramFile(*head, curStudent->studentNumber, courseSize);
            
                sortArray(curCourse->registeredStd, curCourse->capacity);   //sortArray(registeredStd[], capacity)
            }
        }
        else if (strcmp(newStatus, "Dropped") == 0)
        {
            curCourse = searchNodeByString(*head, newCourseCode);
            curStudent = searchNodeByNumber(*head2, newStudentNumber);
            // we may close a course , but it remains on StudentRegistration.txt and curCourse returns NULL because course is not on the list anymore!
            // we may delete an student , but it remains on StudentRegistration.txt and curStudent returns NULL because student is not on the list anymore!
            if (curCourse != NULL && curStudent != NULL)
            {
                limit = curCourse->capacity;
                i = 0;
                while (i < limit)
                {
                    if (curCourse->registeredStd[i] == newStudentNumber)
                    {
                        curCourse->registeredStd[i] = 0;
                        (curCourse->registeredStdNumber)--;
                        (curStudent->courseSum)--;
                        curStudent->creditSum = (curStudent->creditSum) - curCourse->credit;
                        writeToProgramFile(*head, curStudent->studentNumber, courseSize);   // updates students program text file
                    }
                    i++;
                }
            
                sortArray(curCourse->registeredStd, curCourse->capacity);   //sortArray(registeredStd[], capacity)
            }
        }
        else if (strcmp(newStatus, "Closed") == 0)
        {
            // do nothing!
        }

    }

    fclose(fptr);
}


void dropCourse_insideFunction(STUDENT **head2, COURSE **head, int courseSize, char myTime[], int *ID, int tmpStudentNumber, char tmpCourseCode[]) {
    
    char status[CODE_MAX] = "Closed";
    STUDENT *curStudent;
    COURSE *curCourse;
    int i=0, limit;
    FILE *fptr;

    fptr = fopen("StudentCourseRegistration.txt", "a");

    curStudent = searchNodeByNumber(*head2, tmpStudentNumber);
    if (curStudent == NULL)
    {
        printf("Student not Found!\n");
        return;
    }

    curCourse = searchNodeByString(*head, tmpCourseCode);
    if (curCourse == NULL)
    {
        printf("Course Not Found! \n");
        return;
    }
    
    limit = curCourse->capacity;
    while (i < limit)
    {
        if (curCourse->registeredStd[i] == tmpStudentNumber)
        {
            curCourse->registeredStd[i] = 0;
            (curCourse->registeredStdNumber)--;
            (curStudent->courseSum)--;
            curStudent->creditSum = (curStudent->creditSum) - curCourse->credit;

            writeToProgramFile(*head, tmpStudentNumber, courseSize);   // updates students program text file
            //sortArray(curCourse->registeredStd, curCourse->capacity);   //sortArray(registeredStd[], capacity) and then 
            writeClassList(*head2, *head, tmpCourseCode);                       // updates class list text file

            (*ID)++;
            fprintf(fptr, "\n%d %s %d %s %s", *ID, tmpCourseCode, tmpStudentNumber, myTime, status);
            printf("Course Droped Succesfully! %d\n", curCourse->registeredStd[i]);
        }

        i++;
    }

    fclose(fptr);
}