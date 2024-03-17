#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct customer
{
    char name[100];
    char account[100];
    char password[100];
    float balance;
};

int main(void)
{
    struct customer user1,user2;
    char fullname[100],phone[100],password[100],phone2[100];
    FILE *f,*fb;
    int opti,choice,o;
    int amount;
    char cont ='y';
start:
    printf("\t1: Register your account\n");
    printf("\t2: Login to your account\n");
    printf("\n\tplease, enter your choice: ");
    scanf("%d",&opti);

    if(opti == 1)
    {
        system("cls");
        printf("\tenter your Name: \n");
        scanf("%s",user1.name);
        printf("\tenter your account number: \n");
        scanf("%s",user1.account);
        printf("\tenter your password: \n");
        scanf("%s",user1.password);

        if(strcmp(user1.account, user1.password) != 0)
        {
            user1.balance = 0;
            strcpy(fullname,user1.name);
            f = fopen(strcat(fullname,".dat"),"w");
            if (fwrite(&user1, sizeof(struct customer), 1, f) != 0)
                printf("successfully registered");
            fclose(f);
        }
        else
            printf("account and password cannot be the same\n");
    }
    else if(opti == 2)
    {
        system("cls");
        printf("\tNAME: ");
        scanf("%s",phone);
        printf("\tPASSWORD: ");
        scanf("%s",password);
        f = fopen(strcat(phone,".dat"),"r");
        if(f == NULL)
            printf("Not Registered\n");
        else
        {
            fread(&user1,sizeof(struct customer),1,f);
            fclose(f);
            if(strcmp(password,user1.password) == 0)
            {
                do
                {
                    system("cls");
                    printf("\n\tWelcome %s ",user1.name);
                    printf("\n1: Balance Inquiry");
                    printf("\n2: Adding Fund");
                    printf("\n3: Cash Withdraw");
                    printf("\n4: Online Transfer");
                    printf("\n5: Changing Password");
                    printf("\nenter your choice: ");
                    scanf("%d",&choice);

                    switch(choice)
                    {
                    case 1:
                        printf("\n\tYour current balance is %.1f",user1.balance);
                        break;

                    case 2:
                        system("cls");
                        printf("enter the amount you want to add: ");
                        scanf("%d",&amount);
                        user1.balance += amount;
                        f = fopen(phone,"w");
                        if (fwrite(&user1, sizeof(struct customer), 1, f) != 0)
                            printf("\n\tYou have Deposited %d",amount);
                        fclose(f);
                        break;

                    case 3:
                        system("cls");
                        printf("\n\tenter Withdraw amount: ");
                        scanf("%d",&amount);
                        if(amount % 500 != 0)
                            printf("\nsorry insufficient balance");
                        else
                        {
                            user1.balance -= amount;
                            f = fopen(phone,"w");
                            if (fwrite(&user1, sizeof(struct customer), 1, f) != 0)
                                printf("\n\tYou have withdraw %d",amount);
                            fclose(f);
                        }
                        break;

                    case 4:
                        printf("\nPlease, enter name to transfer balance: ");
                        scanf("%s",phone2);
                        printf("\nenter the amount you want to transfer:");
                        scanf("%d",&amount);
                        if(amount > user1.balance)
                            printf("\nsorry insufficient balance");
                        else
                        {
                            fb = fopen(strcat(phone2,".dat"),"r");
                            if(fb == NULL)
                                printf("\nsorry name is not registered");
                            else
                            {
                                fread(&user2,sizeof(struct customer),1,fb);
                                fclose(fb);
                                user2.balance += amount;
                                fb = fopen(phone2,"w");
                                if(fwrite(&user2, sizeof(struct customer), 1, fb) != 0)
                                {
                                    printf("\n\tyour transfer is completed. You have transferred %d To %s",amount,user2.name);
                                    fclose(fb);
                                    user1.balance -= amount;
                                    strcpy(fullname,user1.name);
                                    fb = fopen(strcat(fullname,".dat"),"w");
                                    if (fwrite(&user1, sizeof(struct customer), 1, fb) != 0)
                                        printf("\n\tYour balance updated");
                                    fclose(fb);
                                }
                            }
                        }
                        break;

                    case 5:
                        printf("\nenter your old password: ");
                        scanf("%s",password);
                        if(strcmp(password,user1.password) == 0)
                        {
                            printf("\nenter your new password: ");
                            scanf("%s",password);
                            strcpy(user1.password,password);
                            strcpy(fullname,user1.name);
                            fb = fopen(strcat(fullname,".dat"),"w");
                            if (fwrite(&user1, sizeof(struct customer), 1, fb) != 0)
                                printf("***password successfully changed***");
                            fclose(fb);
                        }
                        else
                            printf("==> sorry, your password is wrong!");
                        break;

                    default:
                        break;
                    }

                    printf("\n\nDo you want to continue:[y/n]: ");
                    scanf(" %c",&cont);
                }
                while(cont == 'y');
            }
            else
            {
                printf("==> Invalid password");
            }
        }
    }

    printf("\n\tpress 1 to go back to the main page OR 0 to finish: ");
    scanf("%d",&o);
    if(o == 1)
        goto start;
    else
        printf("\n\n*****Thank you for banking with Us*****\n\n");

    return 0;
}
