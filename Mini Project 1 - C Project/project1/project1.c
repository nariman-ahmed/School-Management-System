#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student{    		   //student structure.
	int id;
	char name[50];
	int age;
	float gpa;
	}stud;                 //declare struct student stud globally

struct node{
	struct student data;
	struct node *next;      //pointer to node (linker)
};

struct node *head=NULL;     //head node is initially pointing to null


//function declarations:
void addStudent(const struct student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
float calculateAverageGPA(void);
void searchHighestGPA(void);
void deleteStudent(int id);

int main(void){

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	int id,age;
	char name[50];
	float gpa;

	float avg_gpa;
	int id_toBeDeleted, search_id, update_id;

	int choice;

	while(1)
	{
		printf("1. Add Student\n");
		printf("2. Display Students\n");
		printf("3. Search Student by ID\n");
		printf("4. Update Student Information\n");
		printf("5. Delete student\n");
		printf("6. Calculate Average GPA\n");
		printf("7. Search for Student with Highest GPA\n");
		printf("8. Exit\n");
		printf("Enter Choice\n");

		scanf("%d",&choice);

		switch(choice)
		{

		case 1:

			//Add student function

			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("Enter ID:");
			scanf("%d",&id);
			printf("Enter Name:");
			scanf("%s",name);
			printf("Enter Age:");
			scanf("%d",&age);
			printf("Enter GPA:");
			scanf("%f",&gpa);

			//Using stud struct variable declared above.

			stud.id = id;
			strcpy(stud.name, name);
			stud.age = age;
			stud.gpa = gpa;

			addStudent(&stud);

			break;

		case 2:

			//Displaying students

			displayStudents();
			break;

		case 3:

			//Search for a student by ID

			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("Enter ID of student to search for:");
			scanf("%d",&search_id);
			searchStudentByID(search_id);
			break;

		case 4:

			//Update student through ID

			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("Enter ID of student to update:");
			scanf("%d",&update_id);
			updateStudent(update_id);
			break;

		case 5:

			//Delete student by ID

			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("Enter ID of Student to be Deleted:");
			scanf("%d",&id_toBeDeleted);
			deleteStudent(id_toBeDeleted);
			break;

		case 6:

			//Calculate average GPA

			avg_gpa=calculateAverageGPA();
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("The Average GPA is: %0.2f\n",avg_gpa);
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			break;

		case 7:

			//Display student with highest GPA

			searchHighestGPA();
			break;

		case 8:

			//Exit program

			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("Program Terminated.\n");
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			return 0;

		default:

			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("Please Enter a Number from 1 to 8.");
			break;

		}

	}



	return 0;
}

void addStudent(const struct student *const ptr){

	//checking if student with same id already exits
	//start at the head node of the linked list, and loop while comparing to the ptr passed to the function.

	struct node *current = head;

	while(current!=NULL)
	{

		if(current->data.id==ptr->id)
		{
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("Student with ID %d already exists.\n", ptr->id);
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			return;
		}

		current=current->next;
	}


	//since the func didnt stop and return so the id is not repeated, now allocate memory for new node

	struct node *newNode=(struct node *)malloc(sizeof(struct node));

	if(newNode==NULL)
	{

		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("No space to store new student..\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		return;

	}

	//since theres space, we are going to fill in the struct student values now.
	// Copy the student data to the new node

	newNode->data = *ptr;
	newNode->next = head;

	// Add the new node to the end of the linked list

	head=newNode;

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Student added successfully.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

}


void displayStudents(void){

	struct node *current=head;

	//Check if list is empty

	if(head==NULL)
	{
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("List is Empty.\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		return;
	}

	//If there's only one student in the list

	if(current->next==NULL)
	{
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("{ID: %d ,Name: %s, Age: %d, GPA: %0.2f}\n",current->data.id,current->data.name,current->data.age,current->data.gpa);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		return;
	}

	//reversing the linked list first to be printed in ascending order
	//Check using if condition to avoid reversing at each function call
	//and creating a cycle

	struct node *leftnode=NULL;      //node before current
	struct node *rightnode=NULL;     //the one next to current node and reversing pointers with

	if((current->data.id>current->next->data.id) && current->next!=NULL)
	{
		while(current!=NULL)
		{
			rightnode=current->next;
			current->next=leftnode;
			leftnode=current;
			current=rightnode;
		}

		//at the end of the process, let original head = null and original tail = head
		head=leftnode;
		current=head;
	}

	//printing after reversal

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	while(current!=NULL)
	{
		printf("{ID: %d ,Name: %s, Age: %d, GPA: %0.2f}\n",current->data.id,current->data.name,current->data.age,current->data.gpa);
		current=current->next;
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

}


void searchStudentByID(int id){

	struct node *current=head;

	//Loop linked list while comparing ids with the one to be found.

	while(current!=NULL)
	{

		if(current->data.id==id)
		{
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("{ID: %d ,Name: %s, Age: %d, GPA: %0.2f}\n",current->data.id,current->data.name,current->data.age,current->data.gpa);
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			return;
		}

		current=current->next;
	}

	//if function not returned earlier, it means student id isn't found.

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Student Not Found.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

}


void updateStudent(int id){

	struct node *current=head;
	char new_name[50];

	while(current!=NULL)
	{
		if(current->data.id==id)
		{
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("Enter new name:\n");
			scanf("%s",new_name);
			strcpy(current->data.name,new_name);
			printf("Enter new age:\n");
			scanf("%d",&current->data.age);
			printf("Enter new GPA:\n");
			scanf("%f",&current->data.gpa);
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("Update Successful.\n");
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			return;
		}

		current=current->next;
	}

	//if function not returned earlier, it means student id isn't found.

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Student Not Found.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}


float calculateAverageGPA(void){

	//this function loops throught the linked list, counting the number of nodes as well as summing
	//up the values of student GPAs.

	//finally, it returns the avg which is sum / count

	float sum=0;
	int count=0;

	struct node *current=head;
	while(current!=NULL)
	{
		sum+=current->data.gpa;
		count++;
		current=current->next;
	}

	if(count==0)
	{
		return 0;
	}
	else
	{
		return sum/count;
	}

}


void searchHighestGPA(void){

	struct node *current=head;

	//best_stud is like int max, it keeps hold of the address of the node with the highest gpa at each iteration

	struct node *best_stud=current;

	//Check if list is empty

	if(current==NULL)
	{
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("List is Empty.\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		return;
	}

	//Check if only one student is in the list, so print his/her data

	if(current->next==NULL)
	{
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("The student with the highest GPA is:\n");
		printf("{ID: %d, Name: %s, Age: %d, GPA: %0.2f}\n",current->data.id,current->data.name,current->data.age,current->data.gpa);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		return;
	}

	//List is larger so iterate over nodes while comparing each node's GPA to the best_stud GPA

	while(current->next!=NULL)
	{
		if((best_stud->data.gpa)<((current->next)->data.gpa))
		{
			best_stud=current->next;
		}

		current=current->next;

	}

	//print the data of the student with the highest GPA, AKA best_stud.

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("The student with the highest GPA is:\n");
	printf("{ID: %d, Name: %s, Age: %d, GPA: %0.2f}\n",best_stud->data.id,best_stud->data.name,best_stud->data.age,best_stud->data.gpa);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

}


void deleteStudent(int id){

	struct node *current=head;
	struct node *toBeDeleted;

	//check if node to be deleted is the head node

	//if cond: head node is the only node,
	//else cond: head node has other nodes following it.

	if(current->data.id==id)
	{
		if(current->next==NULL)    // so deleted node is the only one in the list and just let current->next=null.
		{
			head=NULL;

			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("Deletion Successful\n");
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

			return;
		}

		else
		{
			toBeDeleted=current;    //aim on first node
			head=current->next;     //new head is now the second node.

			//free the node to be deleted to free up heap space

			free(toBeDeleted);

			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("Deletion Successful\n");
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

			return;
		}
	}

	//node to be deleted isn't the head node

	while(current->next!=NULL)
	{
		//must check if a node exits before and after the deleted node to connect between them
		//the node to be delete is considered current->next while that before it is just current

		if((current->next)->data.id==id)
		{
			//deleted node it the last one and just let current->next=null.

			if(current->next->next==NULL)
			{
				toBeDeleted=current->next;
				current->next=NULL;
				free(toBeDeleted);

				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("Deletion Successful\n");
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

				return;
			}

			// deleted node isn't the last node so connect current with the one 2 spaces after it

			else
			{
				toBeDeleted=current->next;
				current->next=current->next->next;
				free(toBeDeleted);

				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("Deletion Successful\n");
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

				return;
			}
		}
		current=current->next;
	}

	//since function didn't return in any case, then student id isn't found.

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Student Not Found.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

}






