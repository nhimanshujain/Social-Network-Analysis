#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct user
{
    int no_of_friends;
    int id;
    char name[50];
    struct user *link;
}user;

user* create(char*,int);
void insert_front(user*,char *,int);
void display(user*,int);
void read();
void write();
int find_id(char*);

user *all_user[100];
FILE *fp;
int no_of_users;

int main()
{
    system("cls");
    char request_name[500];
    int new,flag1=0,flag2=0;
    int id,request_id,change=1;
    char name[100];
    fp = fopen ("friends.csv", "a+");
    read();
    printf("-------------------------------------------------------------WELCOME-----------------------------------------------------------\n\n\n");

    for(;;)
    {
        printf("\nPress \n\t 1 => New User \n\t 2 => Already have an account \n\t 3 => Exit \n");
        scanf("%d",&new);

        if(new == 1)
        {
            printf("\nEnter your name = ");
            scanf("%s",name);

            
            for(int i=1;i<=no_of_users;i++)
            {            
                if(strcmp(all_user[i]->name,name)==0) 
                {
                    printf("\nYou already have an account!! Please Log In ...\n\n\n");
                    flag1=1;
                }
                break;
            }

            if(flag1==1) continue;

            no_of_users ++;
            all_user[no_of_users] = create(name,no_of_users);
            printf("\nUser created\n\n");
            printf("\t=>Your id = %d\n\n",no_of_users);
            printf("\t=>Remember this to login\n\n\n");
        }

        else if(new == 2)
        {
            printf("\nPlease enter your ID = ");
            scanf("%d",&id);
            printf("%d",id);
            printf("%d",no_of_users);
            if(id<=no_of_users)
            {
                system("cls");
                printf("-------------------------------------------------------Logged in successfully!!------------------------------------------------\n");
                printf("\nUserName = %s\n",all_user[id]->name);
                printf("Number of friends = %d\n\n",all_user[id]->no_of_friends);

                printf("Press \n\t 1 => Display \n\t 2 => Do you want to make friends \n\t 3 => Log Out\n");
                scanf("%d",&change);
                while(change==1||change==2)
                {
                    switch(change)
                    {
                        case 1:
                            printf("\nNumber of friends = %d\n",all_user[id]->no_of_friends);
                            display(all_user[id],id);
                            break;

                        case 2:
                            printf("\n\nEnter the name of the person you want to be friends with = ");
                            scanf("%s",request_name);
                            if(strcmp(request_name,all_user[id]->name))
                            {
                                int request_id;
                                request_id=find_id(request_name);
                                if(request_id==0)
                                    printf("User not found\n\n");
                                else{
                                printf("\nRequest Sent Sucessfully!!\n\n");
                                insert_front(all_user[id],all_user[request_id]->name,request_id);
                                printf("Friend Request Accepted - Friends with %s\n\n",all_user[request_id]->name);
                                flag2=0;
                                }
                            }
                            // if(request_id == id || request_id > no_of_users)
                            // {
                            //     printf("\nUser Not Found\n\n");
                            //     flag2=1;
                            // }
                            break;
                    
                    }

                    printf("Press \n\t 1 => Display \n\t 2 => Do you want to make friends \n\t 3 => Log Out\n");
                    scanf("%d",&change);
                }
                system("cls");
                printf("\n\t\t\t\t\t\tThank You!! Logged Out Successfully!!\n\n");
            }
        }
        else
        {
            break;
        }  
    }
    if(flag1 == 0 && flag2 == 0) write();     
    fclose(fp);

    system("cls");
    printf("\n-------------------------------------------------------------Thank You---------------------------------------------------------\n\n\n");
}

void read()
{
    char line[500],username[100],u[100];
    char *friend;
    int id,temp_id;
    while(fgets(line,500,fp)!=NULL)
    {
        no_of_users ++;
        id=atoi(strtok(line,","));
        strcpy(u,strtok(NULL,","));

        for(int i = 0; i < strlen(u)-1; i++)
        {
            username[i] = u[i]; 
        }
        all_user[id] = create(username,id);

        temp_id=atoi(strtok(NULL,","));
        while(temp_id!=0)
        {
            friend = strtok(NULL,",");
            insert_front(all_user[id],friend,temp_id);
            temp_id = atoi(strtok(NULL,","));
        }
    }
}

user* create(char* name,int id)
{
    char temp[1000];
    user *new_user = (user*)malloc(sizeof(user));
    new_user->no_of_friends = 0;
    new_user->id=id;
    strcpy(new_user->name,name);
    new_user->link = NULL;

    return new_user;
}

void insert_front(user* root,char *name,int id)
{
    user *new_friend,*temp,*p;

    p=root->link;   // Same Friends
    for(;p!=NULL;p=p->link)
    {
        if(!strcmp(p->name , name))
        {
            printf("\n\nHold On!!  You r already...");
            return;
        }
    }
    new_friend=create(name,id);
    temp = root->link;
    root->link = new_friend;
    new_friend->link = temp;
    (root->no_of_friends)++;
}


void display(user* root,int id)
{
    user *temp = root->link;
    int count = 0;
    while(temp!=NULL)
    {
        count++;
        printf("%d %s\n",count,temp->name);
        temp = temp->link;
    }
    printf("\n");
    if(count == 0)
    {
        printf("%s has no friends\n\n",root->name);
    }
}


void write()
{
    int i=1;
    while(i<=no_of_users)
    {
        user* temp = all_user[i]->link;
        fprintf(fp,"%d,%s",all_user[i]->id,all_user[i]->name);
        while(temp!=NULL)
        {
            fprintf(fp,",%d,%s",temp->id,temp->name);
            temp = temp->link;
        }
        fprintf(fp,"\n");
        i++;
    }
}

int find_id(char * name)
{
    for(int i=1;i<=no_of_users;++i)
    {   
        if( !strcmp(name,all_user[i]->name))
        {
            return i;
        }
    }
    return 0;
}