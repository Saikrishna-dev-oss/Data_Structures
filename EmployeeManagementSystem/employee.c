#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct employee
{
    char name[50];
    int emp_code;
    char doj[25];
    int basic_salary ;
    int HRA;     //House rent Allowence
    int DA;     //Dearness Allowence
    int CA;     //Conveyance Allowance
    int total_salary;

    struct employee *next;
}employee;

employee *head = NULL;
employee *last = NULL;

int calculate_total_salary(int basic, int hra, int da, int ca) {
    return basic + hra + da + ca;
}
void add_employee() {

    employee *newnode = (employee*)malloc(sizeof(employee));
    printf("\nEnter the Name : ");
    scanf("%49s",newnode->name);

    printf("Enter the Employee Code : ");
    scanf("%24d",&newnode->emp_code);

    printf("Enter Date of Joining (DD-MM-YYYY): ");
    scanf("%s",newnode->doj);

    printf("Enter Basic Salary, HRA, DA, CA: "); 
    scanf("%d %d %d %d",&newnode->basic_salary, &newnode->HRA, &newnode->DA, &newnode->CA);

    if(newnode->basic_salary < 0 || newnode->HRA < 0 || newnode->DA < 0 || newnode->CA < 0) 
    {
    printf(" Invalid salary values. Must be non-negative.\n");
    free(newnode);
    return;
    }
    
    newnode->total_salary = calculate_total_salary(newnode->basic_salary, newnode->HRA, newnode->DA, newnode->CA);
    
    if(head == NULL) {
        head = last = newnode;
        last->next = head;
    } else {
        last ->next = newnode;
        newnode ->next = head;
        last = newnode;
    }
    printf("\nEmployee Added Successfully ..");
}

void delete_employee() {
    int code,flag;
    printf("\nEnter the code: ");
    scanf("%d",&code);
    if(head == NULL) {
        printf("\nNo Records to Delete !!");
        return;
    }
    employee *curr = head;
    employee *prev = head;
    do {
        if(curr->emp_code == code) {
            flag = 1;
            if(curr == head && curr == last) {      //If one node is present
                head = last = NULL;
                
            } else {
                prev ->next = curr->next;
                if(curr == head)  
                    head = curr->next;
                if(curr == last)
                    last = prev;
            }
            free(curr);
            printf("\nEmployee Deleted Successfully ..");
            break;
        }
        prev = curr;
        curr = curr -> next;
    } while (curr != head);
    if(!flag)
        printf("\nEmployee Not Found !!");
}

void modify_employee() {
    int code;
    printf("\nEnter Employee Code to Modify: ");
    scanf("%d", &code);
    employee *temp = head;
    if (head == NULL) {
        printf("No records found.\n");
        return;
    }
    do {
        if (temp->emp_code == code) {
            printf("Enter New Name: "); scanf("%s", temp->name);
            printf("Enter New DOJ: "); scanf("%s", temp->doj);
            printf("Enter New Basic, HRA, DA, CA: "); scanf("%d %d %d %d", &temp->basic_salary, &temp->HRA, &temp->DA, &temp->CA);
            temp->total_salary = temp->basic_salary + temp->HRA + temp->DA + temp->CA;
            printf(" Employee modified.\n");
            return;
        }
        temp = temp->next;
    } while (temp != head);
    printf(" Employee not found.\n");
}


void search_employee() {
    int code;
    printf("\nEnter Employee Code to Search: ");
    scanf("%d", &code);
    employee *temp = head;
    if (head == NULL) {
        printf("No records found.\n");
        return;
    }
    do {
        if (temp->emp_code == code) {
            printf("\nName: %s\nCode: %d\nDOJ: %s\nBasic: %d\nHRA: %d\nDA: %d\nCA: %d\nTotal: %d\n",
                   temp->name, temp->emp_code, temp->doj, temp->basic_salary, temp->HRA, temp->DA, temp->CA, temp->total_salary);
            return;
        }
        temp = temp->next;
    } while (temp != head);
    printf(" Employee not found.\n");
}


void display_all() {
    if (head == NULL) {
        printf("No employees to display.\n");
        return;
    }

    employee *temp = head;

    printf("\n Employee Records:\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("| %-20s | %-6s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s |\n",
           "Name", "Code", "DOJ", "Basic", "HRA", "DA", "CA", "Total");
    printf("---------------------------------------------------------------------------------------------\n");

    do {
        printf("| %-20s | %-6d | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d |\n",
               temp->name, temp->emp_code, temp->doj,
               temp->basic_salary, temp->HRA, temp->DA, temp->CA, temp->total_salary);
        temp = temp->next;
    } while (temp != head);

    printf("---------------------------------------------------------------------------------------------\n");
}

void sort_by_name() {
    if (head == NULL || head->next == head) return;
    employee *i, *j;
    for (i = head; i->next != head; i = i->next) {
        for (j = i->next; j != head; j = j->next) {
            if (strcmp(i->name, j->name) > 0) {
                employee temp = *i;
                *i = *j;
                *j = temp;
                employee *swap = i->next;
                i->next = j->next;
                j->next = swap;
            }
        }
    }
    printf(" Sorted by name.\n");
}

void show_duplicates() {
    if (head == NULL) return;
    employee *i = head;
    int found = 0;
    do {
        employee *j = i->next;
        while (j != head) {
            if (strcmp(i->name, j->name) == 0 && i->emp_code != j->emp_code) {
                printf("🔁 Duplicate Name: %s (Codes: %d & %d)\n", i->name, i->emp_code, j->emp_code);
                found = 1;
                break;
            }
            j = j->next;
        }
        i = i->next;
    } while (i != head);
    if (!found) printf(" No duplicate names found.\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n Menu:\n1. Add\n2. Delete\n3. Modify\n4. Search\n5. Display All\n6. Sort by Name\n7.vShow Same Name Employees\n8. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: add_employee(); break;
            case 2: delete_employee(); break;
            case 3: modify_employee(); break;
            case 4: search_employee(); break;
            case 5: display_all(); break;
            case 6: sort_by_name(); break;
            case 7: show_duplicates(); break;
            case 8: exit(0);
            default: printf(" Invalid choice.\n");
        }
    }
}

