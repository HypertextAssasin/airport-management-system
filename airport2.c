#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
 
struct User
{
    char name[20];
    int age;
    char address[20];
    char mailID[20];
    int uid;
    struct User *next;
    
};
struct User *user_head = NULL;

struct Flight
{
    int flt_no;
    char src[20];
    char dest[20];
    int seat_price;
    int no_of_seats;
    float start_time;
    float end_time;
    char type;
    struct Flight *next;
};

struct Flight *flight_head = NULL;
struct Bookings
{
    
    char mailID[20];
    char whobooked[20];
    char name[20];
    int age;
    char address[20];
    char src[20];
    char dest[20];
    int flt_no;
    int ticket_price;
    
    struct Bookings *next;
    
};
struct Bookings *bookings_head = NULL;
struct Account 
{

    char mailID[20];
    char password[20];
    int type;
    struct Account *next;
};

struct Account *account_head = NULL;

int search_flight(struct Flight *flight, char src[20], char dest[20])
{
    struct Flight *temp = flight;
    while(temp!=NULL)
    {
        if(strcmp(temp->src, src)==0 && strcmp(temp->dest, dest)==0)
        {
            
            return 1;

        }
        temp = temp->next;
    }
    return 0;
}
void create_admin_accounts() {
    struct User *user = malloc(sizeof(struct User));
    strcpy(user->name, "admin");
    user->age = 18;
    strcpy(user->address, "blr");
    strcpy(user->mailID, "admin@123");
    user_head=user;
    user->next = NULL;
    struct Account *account = malloc(sizeof(struct Account));
    strcpy(account->mailID, "admin@123");
    strcpy(account->password, "123");
    account_head=account;
    account->next = NULL;
    account->type =1;

}
void insert_to_user_list(struct User *p)
{
    struct User *temp = malloc(sizeof(struct User));
    strcpy(temp->name, p->name);
    temp->age = p->age;
    strcpy(temp->address, p->address);
    strcpy(temp->mailID, p->mailID);
    
    temp->next = NULL;
    if(user_head==NULL)
    {
        user_head = temp;
    }
    else
    {
        struct User *temp1 = user_head;
        while(temp1->next!=NULL)
        {
            temp1 = temp1->next;
        }
        temp1->next = temp;
    }
}

void insert_to_account_list(struct Account *p)
{
    struct Account *temp = malloc(sizeof(struct Account));
    strcpy(temp->mailID, p->mailID);
    strcpy(temp->password, p->password);
    temp->next = NULL;
    if(account_head==NULL)
    {
        account_head = temp;
    }
    else
    {
        struct Account *temp1 = account_head;
        while(temp1->next!=NULL)
        {
            temp1 = temp1->next;
        }
        temp1->next = temp;
    }
}
int check_if_account_exists(struct Account *A)
{
    struct Account *temp = account_head;
    while(temp!=NULL)
    {   
        if(strcmp(temp->mailID, A->mailID)==0 && strcmp(temp->password, A->password)==0)
        {
            return 0;
        }
        temp = temp->next;
    }
    
    return 1;
    
    
}

int check_if_user_exists(struct User *U)
{
    struct User *temp = user_head;
    while(temp!=NULL)
    {
        if(strcmp(temp->mailID, U->mailID)==0 )
        {
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}
int u_count =0;
int a_count =0;
int f_count =0;
int get_price(char src[20], char dest[20])
{
    struct Flight *temp = flight_head;
    while(temp!=NULL)
    {
        if(strcmp(temp->src, src)==0 && strcmp(temp->dest, dest)==0)
        {
            int c=temp->seat_price;
            return c;
        }
        temp = temp->next;
    }
    return 0;
}
int get_flt_no(char src[20],char dest[20])
{
    struct Flight *temp = flight_head;
    while(temp!=NULL)
    {
        if(strcmp(temp->src, src)==0 && strcmp(temp->dest, dest)==0)
        {
            int c=temp->flt_no;
            return c;
        }
        temp = temp->next;
    }
    return 0;
}
void seat_deductor(int num,int seats)
{
    struct Flight *temp = flight_head;
    while(temp!=NULL)
    {
        if(num==temp->flt_no)
        {
            temp->no_of_seats = temp->no_of_seats - seats;
        }
        temp = temp->next;
    }
}
int seats_left(int fno )
{
    struct Flight *temp = flight_head;
    while(temp!=NULL)
    {
        if(fno==temp->flt_no)
        {
            int c=temp->no_of_seats;
            return c;
        }
        temp = temp->next;
    }
    
}

void login_page(char name[20])
{
    int clflags = 0;
    while(clflags==0)
    {

        printf("press 1 to book tickets\n");
        printf("press 2 to view bookings\n");
        printf("press 3 to logout\n");
        int choice;
        scanf("%d",&choice);
        if(choice==1)
        {
            printf("enter src: ");
            char src[20];
            scanf("%s",src);
            printf("enter dest: ");
            char dest[20];
            scanf("%s",dest);
            printf("enter no of tickets: ");
            int temp_no=get_flt_no(src,dest);
            int no_of_tickets;
            scanf("%d",&no_of_tickets);
            int s= seats_left(temp_no);
        if(no_of_tickets>s)
        {
            printf("not enough tickets left");
            continue;
        }
        else
        {
            int x=search_flight(flight_head,src,dest);
            if(x==1)
            {
                
                
                for(int i =1;i<=no_of_tickets;i++)
                {   struct Bookings *temp_Book =malloc(sizeof(struct Bookings));
                    strcpy(temp_Book->whobooked, name);
                    printf("enter passenger %d name: ",i);
                    char name2[20];
                    scanf("%s",name2);
                    strcpy(temp_Book->name,name2);
                    printf("enter passenger %d age: ",i);
                    int age;
                    scanf("%d",&age);
                    temp_Book->age = age;
                    strcpy(temp_Book->src,src);
                    strcpy(temp_Book->dest,dest);
                    
                    temp_Book->flt_no=temp_no;
                    temp_Book->next=NULL;
                    int tix=get_price(src,dest);
                    if(temp_Book->age>65)
                    {   
                        printf("tix= %d",tix);
                        temp_Book->ticket_price=tix-((20.0/100.0)*tix);
                    }
                    else
                    {
                        temp_Book->ticket_price=tix;
                    }
                    if(bookings_head == NULL)
                    {
                        bookings_head = temp_Book;
                    }
                    else
                    {
                        struct Bookings *temp1 = bookings_head;
                        while(temp1->next!=NULL)
                        {
                            temp1 = temp1->next;
                        }
                        temp1->next = temp_Book;
                    }
                }

            }
    
           
            else
            {
                printf("no flights available\n");
                return;
            }
            }
        }
            else if(choice==2)
            {
                struct Bookings *temp = bookings_head;
                while(temp!=NULL)
                {
                    if(strcmp(temp->whobooked, name)==0)
                    {
                        printf("name: %s\n",temp->name);
                        printf("age: %d\n",temp->age);
                        printf("src: %s\n",temp->src);
                        printf("dest: %s\n",temp->dest);
                        printf("ticket price: %d\n",temp->ticket_price);
                    }
                    temp = temp->next;
                }
            }
            else if(choice==3)
            {
                return;
            }
        
    }

}

void add_flt_dlt()
{
        struct Flight *temp =malloc(sizeof(struct Flight));
        printf("enter flight number\n");
        scanf("%d",&temp->flt_no);
        printf("enter src\n");
        scanf("%s",temp->src);
        printf("enter dest\n");
        scanf("%s",temp->dest);
        printf("enter seat price\n");
        scanf("%d",&temp->seat_price);
        printf("enter number of seats\n");
        scanf("%d",&temp->no_of_seats);
        printf("enter start time\n");
        scanf("%f",&temp->start_time);
        printf("enter end time\n");
        scanf("%f",&temp->end_time);
        fflush(stdin);
        printf("enter type of flight D:Domestic P:private I:International\n");
        scanf("%c",&temp->type);
        temp->next = NULL;
        if(flight_head==NULL)
        {
            flight_head = temp;
        }
        else
        {
            struct Flight *temp1 = flight_head;
            while(temp1->next!=NULL)
            {
                temp1 = temp1->next;
            }
            temp1->next = temp;
        }
        printf("flight added\n");
}

void get_flt_dlt_seats(int no_of_seats)
{   
    int flag=0; 
    struct Flight *temp = flight_head;
    while(temp!=NULL)
    {
        if(temp->no_of_seats>=no_of_seats)
        {
            printf("flight number: %d\n",temp->flt_no);
            printf("src: %s\n",temp->src);
            printf("dest: %s\n",temp->dest);
            printf("seat price: %d\n",temp->seat_price);
            printf("number of seats: %d\n",temp->no_of_seats);
            printf("start time: %f\n",temp->start_time);
            printf("end time: %f\n",temp->end_time);
            printf("type: %c\n",temp->type);
            flag=1;
        }
        temp = temp->next;
    }
    if(flag==0)
    {
        printf("no flights available as per your requirement\n");
    }
    
}

void get_flt_dlt_type(char type)
{
    int flag=0;
    struct Flight *temp = flight_head;
    while(temp!=NULL)
    {
        if(temp->type==type)
        {
            printf("flight number: %d\n",temp->flt_no);
            printf("src: %s\n",temp->src);
            printf("dest: %s\n",temp->dest);
            printf("seat price: %d\n",temp->seat_price);
            printf("number of seats: %d\n",temp->no_of_seats);
            printf("start time: %f\n",temp->start_time);
            printf("end time: %f\n",temp->end_time);
            printf("type: %c\n",temp->type);
            flag=1;

        }
        temp = temp->next;
    }
    if(flag==0)
    {
        printf("no flights available as per your requirement\n");
    }
}

void all_flt_dlt()
{
    struct Flight *temp = flight_head;
    while(temp!=NULL)
    {
        printf("flight number: %d\n",temp->flt_no);
        printf("src: %s\n",temp->src);
        printf("dest: %s\n",temp->dest);
        printf("seat price: %d\n",temp->seat_price);
        printf("number of seats: %d\n",temp->no_of_seats);
        printf("start time: %f\n",temp->start_time);
        printf("end time: %f\n",temp->end_time);
        printf("type: %c\n",temp->type);
        temp = temp->next;
    }
}
void get_passengers(int flt_no)
{
    struct Bookings *temp = bookings_head;
    while(temp!=NULL)
    {
        if(temp->flt_no==flt_no)
        {
            printf("name: %s\n",temp->name);
            printf("age: %d\n",temp->age);
            printf("src: %s\n",temp->src);
            printf("dest: %s\n",temp->dest);
            printf("ticket price: %d\n",temp->ticket_price);
            temp = temp->next;
        }
    }
}
void admin_page()
{
    int a_flag = 0;
    while(a_flag==0)
    {

    
        printf("press 1 to add details of a flight\n");
        printf("press 2 to sort the details based on number of seats\n");
        printf("press 3 to get details of a flight based on type\n");
        printf("press 4 to get details of all flights\n");
        printf("press 5 to get details of passengers in a particular flight\n");
        printf("press 6 to logout\n");
        int choice;
        scanf("%d",&choice);
        if(choice==1)
        {
            add_flt_dlt();
        }
        else if(choice==2)
        {
            printf("how many seats do you require?\n");
            int no_of_seats;
            scanf("%d",&no_of_seats);
            get_flt_dlt_seats(no_of_seats);
        }
        else if(choice==3)
        {
            printf("enter type of flight D:Domestic P:private I:International\n");
            char type;
            fflush(stdin);
            scanf("%c",&type);
            get_flt_dlt_type(type);
        }
        else if(choice==4)
        {
            all_flt_dlt();
        }
        else if(choice==5)
        {
            printf("enter flight number\n");
            int flt_no;
            scanf("%d",&flt_no);
            get_passengers(flt_no);
        }
        else if(choice==6)
        {
            a_flag=0;
            return;
        }
    }
}
int check_if_admin(char mail[20],char password[20])
{
    struct Account *temp = account_head;
    while(temp!=NULL)
    {
        if(strcmp(temp->mailID,mail)==0 && strcmp(temp->password,password)==0 && temp->type==1)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}




int main()
{   
   
   
    struct Flight flight;
    create_admin_accounts();
    int main_flag = 1;
    while(main_flag==1)
    {
        printf("press 1 to create an account\n");
        printf("press 2 to login\n");
        printf("press 3 to exit\n");
        int choice;
        scanf("%d",&choice);
        if(choice==1)
        {   
             struct Account *account=malloc(sizeof(struct Account));
             printf("enter mailID\n");
             scanf("%s",account->mailID);
             printf("enter password\n");
             scanf("%s",account->password);
             account->type=0;
            
             int x=check_if_account_exists(account);
             if(x==0)
             {
                 printf("account already exists\n");
                 continue;
             }
             else
             {  
                
                insert_to_account_list(account);
                a_count++;
                printf("account created successfully\n");
             
                struct User *user=malloc(sizeof(struct User));
                printf("enter name\n");
                scanf("%s",user->name);
                printf("enter age\n");
                scanf("%d",&user->age);
                printf("enter address\n");
                scanf("%s",user->address);
                strcpy(user->mailID,account->mailID);
                int y= check_if_user_exists(user);
                if(y==0)
                {
                    printf("user already exists\n");
                    continue;
                }
                else
                {
                    insert_to_user_list(user);
                    u_count++;
                    printf("user created successfully\n");
                    printf("you can now login\n"); 
                }
             
             }

        }
        else if(choice==2)
        {
            struct  User *temp_user=malloc(sizeof(struct User));
            struct Account *temp_account=malloc(sizeof(struct Account));
            char name[30];
            printf("enter name\n");
            scanf("%s",name);
            printf("enter mailID\n");
            scanf("%s",temp_account->mailID);
            printf("enter password\n");
            scanf("%s",temp_account->password);
            
            int x=check_if_account_exists(temp_account);
            if(x==0)
            {
                printf("welcome\n");
                int ac_check=check_if_admin(temp_account->mailID,temp_account->password);
                
                if(ac_check==0)
                {
                    login_page(name);
                }
                else if(ac_check==1)
                {
                    admin_page();
                }


            }
            else
            {
                printf("wrong credentials\n");
            }
            
            
        }
        else if(choice==3)
        {
            printf("thank you!\n");
            main_flag=0;
        }

        

    }
}

