#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct student
{
    char name[30];
    int roll,sl;
    float mark;
}student;
typedef union search
{
    char name[30];
    int roll,sl;
    float mark;
}search;
void heads(void)
{
    printf("|--------------------------------------------------------|\n");
    printf("|SL.NO.  |  ROLL NO.  |  MARKS  |  NAME                  |\n");
    printf("|--------------------------------------------------------|\n");
}
void names_sort(char str[][30],int n)
{
    char temp[30];
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(strcmp(str[j],str[j+1])>=0)
            {
                strcpy(temp,str[j]);
                strcpy(str[j],str[j+1]);
                strcpy(str[j+1],temp);
            }
        }
    }
}
void roll_sort(int* ptr, int n)
{
    int temp;
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(*(ptr+j)>=*(ptr+j+1))
            {
                temp=*(ptr+j);
                *(ptr+j)=*(ptr+j+1);
                *(ptr+j+1)=temp;
            }
        }
    }
}
void marks_sort(float* ptr,int* ptr1,int n)
{
    int temp;
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(*(ptr+j)<=*(ptr+j+1))
            {
                temp=*(ptr+j);
                *(ptr+j)=*(ptr+j+1);
                *(ptr+j+1)=temp;
                temp=*(ptr1+j);
                *(ptr1+j)=*(ptr1+j+1);
                *(ptr1+j+1)=temp;
            }
        }
    }
}
int count_rec(void)
{
    FILE *fp;
    fp=fopen("DBMS.txt","r");
    if(fp==NULL)
    {
        printf("UNABLE TO COUNT!!!\n");
        printf("TERMINATING PROGRAM......\n");
        for(int i=0;i<32000;i++);
        exit(0);
    }
    int i=0;
    student stu;
    while(fread(&stu,sizeof(student),1,fp))i++;
    fclose(fp);
    return (i);
}
void store_rec()
{
    char ch='y';
    student stu;
    int i=0;
    FILE *fp;
    fp=fopen("DBMS.txt","a+");
    if(fp==NULL)
    {
        printf("UNABLE TO ADD NEW RECORD!!!\n");
        printf("TERMINATING PROGRAM......\n");
        for(int i=0;i<32000;i++);
        exit(0);
    }
    fseek(fp,0,SEEK_SET);                                    /*Since the file has been opened in append mode*/
    while(fread(&stu,sizeof(student),1,fp))i++;              /*For assigning serial numbers*/
    while(toupper(ch)=='Y')
    {
        stu.sl=++i;
        fflush(stdin);
        printf("Enter name       :");
        gets(stu.name);
        printf("Enter roll number:");
        scanf("%d",&stu.roll);
        printf("Enter marks      :");
        scanf("%f",&stu.mark);
        fwrite(&stu,sizeof(student),1,fp);
        fflush(stdin);
        printf("Enter another record:(Y/N)?");
        scanf("%c",&ch);
    }
    fclose(fp);
}
void mod_rec(void)
{
    int n,m,flag=0;
    char ch;
    student stu,s;
    FILE *fp;
    fp=fopen("DBMS.txt","r+");
    if(fp==NULL)
    {
        printf("UNABLE TO MODIFY RECORD!!!\n");
        printf("TERMINATING PROGRAM......\n");
        for(int i=0;i<32000;i++);
        exit(0);
    }
    printf("Enter roll number:\n");
    scanf("%d",&n);
    fseek(fp,0,SEEK_SET);
    m=(-1)*sizeof(student);
    while(fread(&stu,sizeof(student),1,fp))
    {
        if(stu.roll==n)
        {
            fseek(fp,m,1);
            fflush(stdin);
            printf("Edit name?(Y/N)");
            scanf("%c",&ch);
            fflush(stdin);
            if(toupper(ch)=='Y')gets(s.name);
            else strcpy(s.name,stu.name);
            printf("Edit roll number?(Y/N)");
            fflush(stdin);
            scanf("%c",&ch);
            if(toupper(ch)=='Y')scanf("%d",&s.roll);
            else s.roll=stu.roll;
            printf("Edit marks?(Y/N)");
            fflush(stdin);
            scanf("%c",&ch);
            if(toupper(ch)=='Y')scanf("%f",&s.mark);
            else s.mark=stu.mark;
            s.sl=stu.sl;
            fwrite(&s,sizeof(student),1,fp);
            flag=1;
            break;
        }
    }
    if(flag)printf("RECORD MODIFIED SUCCESSFULLY.\n");
    else printf("RECORD NOT FOUND!!!\n");
    fclose(fp);
}
void del_rec(void)
{
    int n,i;
    student stu;
    search ser;
    FILE *fp,*fp1;
    fp=fopen("DBMS.txt","r");
    if(fp==NULL)
    {
        printf("UNABLE TO DELETE RECORD!!!\n");
        printf("TERMINATING PROGRAM......\n");
        for(int i=0;i<32000;i++);
        exit(0);
    }
    fp1=fopen("DBMSnew.txt","w");
    if(fp1==NULL)
    {
        printf("UNABLE TO DELETE RECORD!!!\n");
        printf("TERMINATING PROGRAM......\n");
        for(int i=0;i<32000;i++);
        fclose(fp);
        exit(0);
    }
    printf("ENTER:\n");
    printf("1.NAME.\n2.ROLL NUMBER.\n3.MARKS.\n4.SERIAL NUMBER.\n");
    scanf("%d",&n);
    switch(n)
    {
        case 1:fflush(stdin);
               printf("Enter name:\n");
               gets(ser.name);
               i=0;
               while(fread(&stu,sizeof(stu),1,fp))
               {
                   if(strcmp(stu.name,ser.name)!=0)
                   {
                       stu.sl=++i;
                       fwrite(&stu,sizeof(stu),1,fp1);
                   }
               }
               break;
        case 2:printf("Enter roll number:\n");
               scanf("%d",&ser.roll);
               i=0;
               while(fread(&stu,sizeof(stu),1,fp))
               {
                   if(stu.roll!=ser.roll)
                   {
                       stu.sl=++i;
                       fwrite(&stu,sizeof(stu),1,fp1);
                   }
               }
               break;
        case 3:printf("Enter marks:\n");
               scanf("%f",&ser.mark);
               i=0;
               while(fread(&stu,sizeof(stu),1,fp))
               {
                   if(stu.mark!=ser.mark)
                   {
                       stu.sl=++i;
                       fwrite(&stu,sizeof(stu),1,fp1);
                   }
               }
               break;
        case 4:printf("Enter serial number:\n");
               scanf("%d",&ser.sl);
               i=0;
               while(fread(&stu,sizeof(stu),1,fp))
               {
                   if(stu.sl!=ser.sl)
                   {
                       stu.sl=++i;
                       fwrite(&stu,sizeof(stu),1,fp1);
                   }
               }
               break;
        default:printf("INVALID ACTION NUMBER ENTERED!!!");
    }
    fclose(fp);
    fclose(fp1);
    n=remove("DBMS.txt");
    if(n==0)printf("RECORD DELETED SUCCESSFULLY.\n");
    else if(n==-1)printf("OPERATION FAILED.\n");
    rename("DBMSnew.txt","DBMS.txt");
}
void search_rec()
{
    int n;
    search ser;
    student stu;
    FILE *fp;
    fp=fopen("DBMS.txt","r");
    if(fp==NULL)
    {
        printf("UNABLE TO FIND RECORD!!!\n");
        printf("TERMINATING PROGRAM......\n");
        for(int i=0;i<32000;i++);
        exit(0);
    }
    printf("1.NAME.\n2.ROLL NUMBER.\n3.SERIAL NUMBER.\n4.MARKS.\n");
    scanf("%d",&n);
    switch(n)
    {
        case 1:printf("Enter name:\n");
               fflush(stdin);
               gets(ser.name);
               int i=0;
               while(fread(&stu,sizeof(student),1,fp))
               {
                   if(strcmp(stu.name,ser.name)==0)
                    {
                      if(i==0)heads();
                      printf("  %d           %d         %.2f     %s\n",stu.sl,stu.roll,stu.mark,stu.name);
                      printf("|--------------------------------------------------------|\n");
                      i++;
                    }
               }
               if(i==0)printf("RECORD NOT FOUND!!!\n");
               break;
        case 2:printf("Enter roll number:\n");
               scanf("%d",&ser.roll);
               i=0;
               while(fread(&stu,sizeof(student),1,fp))
               {
                   if(stu.roll==ser.roll)
                    {
                      if(i==0)heads();
                      printf("  %d           %d         %.2f     %s\n",stu.sl,stu.roll,stu.mark,stu.name);
                      printf("|--------------------------------------------------------|\n");
                      i++;
                    }
               }
               if(i==0)printf("RECORD NOT FOUND!!!\n");
               break;
        case 3:printf("Enter serial number:\n");
               scanf("%d",&ser.sl);
               i=0;
               while(fread(&stu,sizeof(student),1,fp))
               {
                   if(stu.sl==ser.sl)
                    {
                      if(i==0)heads();
                      printf("  %d           %d         %.2f     %s\n",stu.sl,stu.roll,stu.mark,stu.name);
                      printf("|--------------------------------------------------------|\n");
                      i++;
                    }
               }
               if(i==0)printf("RECORD NOT FOUND!!!\n");
               break;
        case 4:printf("Enter marks:\n");
               scanf("%f",&ser.mark);
               i=0;
               while(fread(&stu,sizeof(student),1,fp))
               {
                   if(stu.mark==ser.mark)
                    {
                      if(i==0)heads();
                      printf("  %d           %d         %.2f     %s\n",stu.sl,stu.roll,stu.mark,stu.name);
                      printf("|--------------------------------------------------------|\n");
                      i++;
                    }
               }
               if(i==0)printf("RECORD NOT FOUND!!!\n");
               break;
        default:printf("INVALID ACTION NUMBER ENTERED!!!\n");
                break;

    }
    fclose(fp);
}
void disp_rec()
{
    student stu;
    int n;
    FILE *fp;
    fp=fopen("DBMS.txt","r");
    if(fp==NULL)
    {
        printf("UNABLE TO DISPLAY RECORD LIST!!!\n");
        printf("TERMINATING PROGRAM......\n");
        for(int i=0;i<32000;i++);
        exit(0);
    }
    printf("BY:\n");
    printf("1.SERIAL NUMBER.\n2.MARKS.\n3.ROLL NUMBER.\n4.ALPHABETICAL ORDER.\n");
    scanf("%d",&n);
    printf("LIST OF ALL STUDENTS IN THE DATABASE:\n");
    switch(n)
    {
        case 1:printf("BY SERIAL NUMBER:\n");
               heads();
               while(fread(&stu,sizeof(student),1,fp))
              {
                 printf("  %d           %d         %.2f     %s\n",stu.sl,stu.roll,stu.mark,stu.name);
                 printf("|--------------------------------------------------------|\n");
              }
              break;
        case 2:printf("BY MARKS:\n");
               int i=0;
               while(fread(&stu,sizeof(student),1,fp))i++;
               fseek(fp,0,SEEK_SET);
               float* ptr=(float*)malloc(i*sizeof(float));
               if(ptr==NULL)
               {
                 printf("ERROR.\n");
                 printf("TERMINATING PROGRAM......\n");
                 for(int i=0;i<32000;i++);
                 exit(0);
               }
               int* ptr1=(int*)malloc(i*sizeof(int));
               if(ptr1==NULL)
               {
                 printf("ERROR.\n");
                 printf("TERMINATING PROGRAM......\n");
                 for(int i=0;i<32000;i++);
                 exit(0);
               }
               i=0;
               while(fread(&stu,sizeof(student),1,fp)){*(ptr+i)=stu.mark;*(ptr1+i)=stu.sl;i++;}
               marks_sort(ptr,ptr1,i);
               fseek(fp,0,SEEK_SET);
               heads();
               for(int j=0;j<i;j++)
               {
                   while(fread(&stu,sizeof(student),1,fp))
                   {
                       if(stu.sl==*(ptr1+j))
                       {
                         printf("  %d           %d         %.2f     %s\n",stu.sl,stu.roll,stu.mark,stu.name);
                         printf("|--------------------------------------------------------|\n");
                       }
                   }
                   fseek(fp,0,SEEK_SET);
               }
               free(ptr);
               free(ptr1);
               break;
        case 3:printf("BY ROLL NUMBER:\n");
               i=0;
               while(fread(&stu,sizeof(student),1,fp))i++;
               fseek(fp,0,SEEK_SET);
               int* ptr2=(int*)malloc(i*sizeof(int));
               if(ptr2==NULL)
               {
                 printf("ERROR.\n");
                 printf("TERMINATING PROGRAM......\n");
                 for(int i=0;i<32000;i++);
                 exit(0);
               }
               i=0;
               while(fread(&stu,sizeof(student),1,fp)){*(ptr2+i)=stu.roll;i++;}
               roll_sort(ptr2,i);
               fseek(fp,0,SEEK_SET);
               heads();
               for(int j=0;j<i;j++)
               {
                   while(fread(&stu,sizeof(student),1,fp))
                   {
                       if(stu.roll==*(ptr2+j))
                       {
                         printf("  %d           %d         %.2f     %s\n",stu.sl,stu.roll,stu.mark,stu.name);
                         printf("|--------------------------------------------------------|\n");
                       }
                   }
                   fseek(fp,0,SEEK_SET);
               }
               free(ptr2);
               break;
        case 4:printf("IN ALPHABETICAL ORDER:\n");
               i=0;
               int j=0;
               while(fread(&stu,sizeof(student),1,fp))i++;
               fseek(fp,0,SEEK_SET);
               char str[i][30];
               while(fread(&stu,sizeof(student),1,fp))
               {
                   strcpy(str[j],stu.name);
                   j++;
               }
               names_sort(str,i);
               fseek(fp,0,SEEK_SET);
               heads();
               for(int j=0;j<i;j++)
               {
                   while(fread(&stu,sizeof(student),1,fp))
                   {
                       if(strcmp(stu.name,str[j])==0)
                       {
                         printf("  %d           %d         %.2f     %s\n",stu.sl,stu.roll,stu.mark,stu.name);
                         printf("|--------------------------------------------------------|\n");
                       }
                   }
                   fseek(fp,0,SEEK_SET);
               }
               break;
    }
    fclose(fp);
}
int main()
{
    int n;
    char ch='y';
    printf("SUPER-NOVA DATABASE MANAGEMENT SYSTEM:\n");
    do
    {
        printf("MENU:\n");
        printf("\t\t ---------------------------------------------------------------------------\n");
        printf("\t\t|   ADD   ||   EDIT  ||  DELETE || DISPLAY ||   FIND  ||  COUNT  ||   QUIT  |\n");
        printf("\t\t ---------------------------------------------------------------------------\n");
        scanf("%d",&n);
      switch(n)
      {
        case 1:printf("|--------------------------------------------------------------------------------------------------------------|\n");
               printf("INSERT RECORD MODE:\n");
               store_rec();
               printf("|--------------------------------------------------------------------------------------------------------------|\n");
               break;
        case 2:printf("|--------------------------------------------------------------------------------------------------------------|\n");
               printf("EDIT RECORD MODE:\n");
               mod_rec();
               printf("|--------------------------------------------------------------------------------------------------------------|\n");
               break;
        case 3:printf("|--------------------------------------------------------------------------------------------------------------|\n");
               printf("DELETE RECORD MODE:\n");
               del_rec();
               printf("|--------------------------------------------------------------------------------------------------------------|\n");
               break;
        case 4:printf("|--------------------------------------------------------------------------------------------------------------|\n");
               printf("DISPLAY RECORD LIST MODE:\n");
               disp_rec();
               printf("|--------------------------------------------------------------------------------------------------------------|\n");
               break;
        case 5:printf("|--------------------------------------------------------------------------------------------------------------|\n");
               printf("SEARCH RECORD MODE:\n");
               search_rec();
               printf("|--------------------------------------------------------------------------------------------------------------|\n");
               break;
        case 6:printf("|--------------------------------------------------------------------------------------------------------------|\n");
               printf("RECORD COUNTER MODE:\n");
               printf("NUMBER OF RECORDS IN THE DATABASE:%d\n",count_rec());
               printf("|--------------------------------------------------------------------------------------------------------------|\n");
               break;
        case 7:printf("|--------------------------------------------------------------------------------------------------------------|\n");
               printf("QUITTING......\n");
               printf("|--------------------------------------------------------------------------------------------------------------|\n");
               exit(0);
               break;
       default:printf("INVALID OPERATION!\n");
     }
     printf("|--------------------------------------------------------------------------------------------------------------|\n");
     fflush(stdin);
     printf("Return to menu?(Y/N)");
     scanf("%c",&ch);
    }while(toupper(ch)=='Y');
    return 0;
}
