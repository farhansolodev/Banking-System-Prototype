#include <stdio.h>
#include <conio.h>
#include <stdlib.h> // for various functions such as the strtok() and strtol() function
#include <string.h> //to use strcmp(), strcpy() etc.
#include <stdbool.h> //for bool datatype
#include <ctype.h> //to use isalpha() and isdigit() functions

void home();
void customerMenu();
void registration();
void c_logInPage();
void a_logInPage();
void customerHome(long accnum);
void personalDetails(long accnum);
void accDetails(long accnum);
void c_transactionList(long accnum);
void a_transactionList();
void removeUser();
void withdraw(long accnum);
void deposit(long accnum);
void adminMenu();

struct {
	FILE* cListptr;
	FILE* trans;
}a;

struct {
	char name[100];
	char mobnum[100];
	int sex;
	char username[100];
	char pass[100];
	long accnum;
	int acctype;
	int balance;
}std, std1, file, personal, acc;

int main() {
	home();
}

void home() { //Main menu
	system("cls");
	char choice[100];
    int input_int;
	char *endptr;
	printf("\nPress 1 to log in as Admin\nPress 2 if you are a customer\nPress 0 to to exit program\n");
	scanf("%s", &choice);
	if(strlen(choice) == 1 && isdigit(choice[0])){
        input_int = strtol(choice,&endptr,10);
        switch (input_int)
        {
        case 1:
            a_logInPage();
            break;
        case 2:
            customerMenu();
            break;
        case 0:
            exit(0);
        default:
            printf("\a");
            home();
        }

	} else {
        printf("\a");
        home();
	}
}

void a_logInPage() { //Admin log in
	struct {
		char username[30];
		char password[30];
	}admin;
	bool loginSuccess = false;
	while (!loginSuccess)
	{
		char username[] = "farhan";
		char password[] = "pass";
		loginSuccess = false;
		system("cls");
		printf("\nEnter Username (Hint: 'farhan')\n");
		scanf("%s", &admin.username);
		printf("Enter Password (Hint: 'pass')\n");
		scanf("%s", &admin.password);
		if (strcmp(admin.username , username) == 0) {
			if (strcmp(admin.password , password) == 0) {
				loginSuccess = true;
			}
		}
		if (!loginSuccess)
		{
            system("cls");
			int choice;
            incorrect_label:
			printf("\a\nWrong username or password.\n\nPress 1 to try again\nPress 2 to go back to the home screen\n");
			scanf("%d", &choice);
			switch (choice) {
			case 1:
				break;
			case 2:
				home();
				break;
			default:
			    system("cls");
				goto incorrect_label;
			}

		}
	}
	adminMenu();
}

void adminMenu() {
    system("cls");
	a.cListptr = fopen("customerList.txt", "r+");
	if (a.cListptr == NULL) {
        printf("\nNo existing users\n\nPress any key to log out...");
        _getch();
        home();
	}
	else {
        while (fscanf(a.cListptr, "%s%s%d%s%s%ld%d%d", &file.name, &file.mobnum, &file.sex, &file.username, &file.pass, &file.accnum, &file.acctype, &file.balance) != EOF) {
			if (file.sex == 1) {
				if (file.acctype == 1) {
					printf("\nName: %s  ||  Mobile Number: %s  ||  Gender: Male  ||  Username: %s  ||  Password: %s  ||\n  Account Number: %ld  ||  Account Type: Savings Account  || Balance: %d MYR\n\n", file.name, file.mobnum, file.username, file.pass, file.accnum, file.balance);
				}
				else if (file.acctype == 2) {
					printf("\nName: %s  ||  Mobile Number: %s  ||  Gender: Male  ||  Username: %s  ||  Password: %s  ||\n  Account Number: %ld  ||  Account Type: Current Account  || Balance: %d MYR\n\n", file.name, file.mobnum, file.username, file.pass, file.accnum, file.balance);
				}
			}
			else if (file.sex == 2) {
				if (file.acctype == 1) {
					printf("\nName: %s  ||  Mobile Number: %s  ||  Gender: Female  ||  Username: %s  ||  Password: %s  ||\n  Account Number: %ld  ||  Account Type: Savings Account  || Balance: %d MYR\n\n", file.name, file.mobnum, file.username, file.pass, file.accnum, file.balance);
				}
				else if (file.acctype == 2) {
					printf("\nName: %s  ||  Mobile Number: %s  ||  Gender: Female  ||  Username: %s  ||  Password: %s  ||\n  Account Number: %ld  ||  Account Type: Current Account  || Balance: %d MYR\n\n", file.name, file.mobnum, file.username, file.pass, file.accnum, file.balance);
				}
			}

		}
		fclose(a.cListptr);
	}
	char choice[100];
    int input_int;
	char *endptr;
	printf("\nPress 1 to view system transaction history\nPress 2 to remove a user\nPress 0 to to log out\n");
	scanf("%s", &choice);
	if(strlen(choice) == 1 && isdigit(choice[0])){
        input_int = strtol(choice,&endptr,10);
        switch (input_int)
        {
        case 1:
            a_transactionList();
        case 2:
            removeUser();
        case 0:
            home();
        default:
            printf("\a");
            adminMenu();
        }

	} else {
        printf("\a");
        adminMenu();
	}
}

void removeUser(){
    system("cls");
    char input[200];
	FILE* tmp;
	int input_int;
	char *endptr;
	char cList[] = "customerList.txt";

    accnum_label:
    printf("\nPlease enter the account number of the account you wish to remove:\n");
    scanf("%s",&input);
    for (int i=0;i<strlen(input); i++){
        if (!isdigit(input[i])){
            system("cls");
            printf("Invalid input");
            goto accnum_label;
        }
    }
    input_int = strtol(input,&endptr,10);

    bool accnumExists = false;
    a.cListptr = fopen("customerList.txt", "r");
	tmp = fopen("tmp_customerList.txt", "a+");
	while (fscanf(a.cListptr, "%s%s%d%s%s%ld%d%d", &file.name, &file.mobnum, &file.sex, &file.username, &file.pass, &file.accnum, &file.acctype, &file.balance) != EOF) {
		if(input_int == file.accnum){
            accnumExists = true;
            break;
		}
	}
	fclose(a.cListptr);
    a.cListptr = fopen("customerList.txt", "r");
    if(accnumExists){
        while (fscanf(a.cListptr, "%s%s%d%s%s%ld%d%d", &file.name, &file.mobnum, &file.sex, &file.username, &file.pass, &file.accnum, &file.acctype, &file.balance) != EOF) {
            if (input_int != file.accnum) {
                fprintf(tmp, "%s\t%s\t%d\t%s\t%s\t%ld\t%d\t%d\n", file.name, file.mobnum, file.sex, file.username, file.pass, file.accnum, file.acctype, file.balance);
            }
        }
    } else {
        while (fscanf(a.cListptr, "%s%s%d%s%s%ld%d%d", &file.name, &file.mobnum, &file.sex, &file.username, &file.pass, &file.accnum, &file.acctype, &file.balance) != EOF) {
            fprintf(tmp, "%s\t%s\t%d\t%s\t%s\t%ld\t%d\t%d\n", file.name, file.mobnum, file.sex, file.username, file.pass, file.accnum, file.acctype, file.balance);
        }
        printf("\nAccount number %d does not exist\n\nPress any key to continue...", input_int);
        fclose(a.cListptr);
        fclose(tmp);
        remove(cList);
        rename("tmp_customerList.txt", cList);
        _getch();
        adminMenu();
    }
    fclose(a.cListptr);

    fseek(tmp,0,SEEK_END);
    int len = ftell(tmp);
	fclose(tmp);
    remove(cList);
    if(len != 0)
        rename("tmp_customerList.txt", cList);
    else
        remove("tmp_customerList.txt");

	system("cls");
	printf("\nAccount number %d has been removed successfully\n\nPress any key to continue...", input_int);
	_getch();
	adminMenu();
}

void a_transactionList(){
    system("cls");
    int transaction;
    bool trans_exists = false;
    a.trans = fopen("transList.txt","r");
    if(a.trans != NULL){
        printf("Account Number\tTransaction\n\n");
        while(fscanf(a.trans,"%ld%d",&file.accnum,&transaction) != EOF){
            trans_exists = true;
            if(transaction > 0){
                printf("%ld\t\tDeposit: %d MYR\n",file.accnum,transaction);
            } else if(transaction < 0){
                printf("%ld\t\tWithdraw: %d MYR\n",file.accnum,abs(transaction));
            }
        }
        if(!trans_exists){
            printf("No transactions available\n");
        }
    } else {
        printf("No transactions available\n");
    }
    fclose(a.trans);

    printf("\nPress any key to exit...");
	_getch();
	adminMenu();
}

void customerMenu() { //Customer main menu
    system("cls");
    char choice[100];
    int input_int;
	char *endptr;
	printf("\nPress 1 to log in\nPress 2 to register as a new user\nPress 0 to go back\n");
	scanf("%s", &choice);
	if(strlen(choice) == 1 && isdigit(choice[0])){
        input_int = strtol(choice,&endptr,10);
        switch (input_int)
        {
        case 1:
            c_logInPage();
            break;
        case 2:
            registration();
            break;
        case 0:
            home();
            break;
        default:
            printf("\a");
            customerMenu();
        }
	} else {
        printf("\a");
        customerMenu();
	}
}

void registration() { //Customer registration
	system("cls");
	char input[100];
    int input_int;
	char *endptr;

	a.cListptr = fopen("customerList.txt", "a+");

	char name[35];
	firstname_label:
	printf("\nEnter first name\n");
	scanf("%s",name);
    for (int i=0;i<strlen (name); i++){
        if (!isalpha(name[i]))
        {
            system("cls");
            printf ("No numerals or special characters");
            goto firstname_label;
        }
    }
    strcpy(std1.name,name);
	fprintf(a.cListptr,"%s",std1.name);

    char mobnum[50];
    int mobcntr = 0;
    system("cls");
    printf("\nE");
	mobnum_label:
	printf("nter your Malaysian mobile number\n");
	mymobnum_label:
	scanf("%s", &mobnum);
	for (int i=0;i<strlen (mobnum); i++){
        if (isdigit(mobnum[i]))
        {
            if(strlen(mobnum) != 10 || mobnum[0] != '0' || mobnum[1] != '1') //has to start with 01, no special characters
            {
                if (mobcntr >= 2){
                    system("cls");
                    printf ("\nHint: Your number should be 10 digits long and should begin with '01'\n");
                    mobcntr = 0;
                    goto mymobnum_label;
                }
                system("cls");
                mobcntr++;
                printf ("Invalid format\nPlease enter a valid Malaysian number:\n");
                goto mymobnum_label;
            }
        } else {
            system("cls");
            printf ("Invalid input\nPlease e");
            goto mobnum_label;
        }
    }
    strcpy(std1.mobnum,mobnum);
	fprintf(a.cListptr, "\t%s", std1.mobnum);

	system("cls");
	sex_label:
	printf("\nEnter 1 if you are male - Enter 2 if you are female\n");
	scanf("%s",&input);
	for(int i=0;i<strlen(input);i++){
        if(!isdigit(input[i])) {
            system("cls");
            printf("Invalid Input");
            goto sex_label;
        }
    }
	input_int = strtol(input,&endptr,10);
    if(input_int == 1 || input_int == 2)
    {
        std1.sex = input_int;
    } else {
        system("cls");
        printf("Invalid Input");
        goto sex_label;
    }
	fprintf(a.cListptr, "\t%d", std1.sex);

    system("cls");
    uname_label1:
	printf("\nEnter username\n");
	uname_label2:
	scanf("%s", &input);
	for (int i=0;i<strlen (input); i++) {
        if(isalpha(input[i]) || isdigit(input[i]))//no special characters
        {
            if (strlen (input)<5 || strlen(input)>20) {
                system("cls");
                printf ("Username must be 5 to 20 characters long\nTry again:\n");
                goto uname_label2;
            }

        } else {
            system("cls");
            printf ("No special characters");
            goto uname_label1;
        }
    }
    strcpy(std1.username,input);
	fprintf(a.cListptr, "\t%s", std1.username);

	char pass2[100];
	system("cls");
	password_label:
	printf("\nEnter password\n");
	scanf("%s", &input);
	printf("Re-enter password\n");
	scanf("%s", &pass2);
	if (strcmp(input, pass2) == 0) {
        strcpy(std1.pass,input);
        fprintf(a.cListptr, "\t%s", std1.pass);
	} else {
		system("cls");
		printf("Passwords do not match");
		goto password_label;
	}

	char chaccnum[100];
	char accnum2[100];
	system("cls");
	accnum_label:
	printf("\nEnter a 5-digit account number\n");
	scanf("%s", &input);
	for (int i=0;i<strlen (input); i++){
        if (isdigit(input[i]))
        {
            if(strlen(input) != 5) {
                system("cls");
                printf("Invalid format");
                goto accnum_label;
            }

        } else {
            system("cls");
            printf("Invalid input");
            goto accnum_label;
        }
	}
	strcpy(chaccnum,input);
	printf("Re-enter account number\n");
	scanf("%s", &accnum2);
	if (strcmp(chaccnum,accnum2)==0) {
        std1.accnum = strtol(chaccnum,&endptr,10);
        fprintf(a.cListptr, "\t%ld", std1.accnum);
	} else {
        system("cls");
		printf("Account Numbers do not match");
		goto accnum_label;
	}

	system("cls");
	acctype_label:
	printf("\nEnter 1 to create Savings account - Enter 2 to create Current account\n");
	scanf("%s",&input);
	input_int = strtol(input,&endptr,10);
    if(input_int == 1 || input_int == 2)
    {
        std1.acctype = input_int;
    } else {
        system("cls");
        printf("Invalid Input");
        goto acctype_label;
    }
	fprintf(a.cListptr, "\t%d", std1.acctype);

	std1.balance = 0;
	fprintf(a.cListptr, "\t%d\n", std1.balance);

	fclose(a.cListptr);
	system("cls");
	printf("Account created\n\nPress any key to continue...");
	_getch();
	customerHome(std1.accnum);

}

void c_logInPage() { //Customer log in
	system("cls");
    a.cListptr = fopen("customerList.txt", "r");
    if (a.cListptr == NULL) {
        printf("\nNo existing users\n\nPress any key to continue...");
        _getch();
        home();
    } else {
        bool loginSuccess = false;
        while (!loginSuccess)
        {
            loginSuccess = false;
            printf("\nEnter Username\n");
            scanf("%s", &std.username);
            printf("Enter Password\n");
            scanf("%s", &std.pass);
            while (fscanf(a.cListptr,"%s%s%d%s%s%ld%d%d", &file.name, &file.mobnum, &file.sex, &file.username, &file.pass, &file.accnum, &file.acctype, &file.balance)!= EOF) {
                if (strcmp(std.username, file.username) == 0) {
                    if (strcmp(std.pass, file.pass) == 0) {
                        std.accnum = file.accnum;
                        loginSuccess = true;
                    }
                }
            }
            fclose(a.cListptr);
            if (!loginSuccess)
            {
                char choice[100];
                int input_int;
                char *endptr;
                system("cls");
                fclose(a.cListptr);
                printf("\nWrong username or password. Press 1 to try again - Press 2 to go back to the home screen\n\a");
                incorrect_label:
                scanf("%s",&choice);
                if(strlen(choice) == 1 && isdigit(choice[0]))
                {
                    input_int = strtol(choice,&endptr,10);
                    switch (input_int) {
                    case 1:
                        system("cls");
                        a.cListptr = fopen("customerList.txt", "r");
                        break;
                    case 2:
                        home();
                        break;
                    default:
                        system("cls");
                        printf("\a");
                        printf("\nPress 1 to try again - Press 2 to go back to the home screen\n\a");
                        goto incorrect_label;
                    }
                } else {
                    system("cls");
                    printf("\a");
                    printf("\nPress 1 to try again - Press 2 to go back to the home screen\n\a");
                    goto incorrect_label;
                }
            }
        }
        customerHome(std.accnum);
    }
}

void customerHome(long accnum) { // Customer homepage
	system("cls");
    char choice[100];
    int input_int;
	char *endptr;

	printf("From the list of choices below:\n\n");
	printf("Press 1 to view personal details\nPress 2 to view account details\nPress 3 to view your transactions\nPress 0 to log out\n");
	scanf("%s",&choice);
	if(strlen(choice) == 1 && isdigit(choice[0])){
        input_int = strtol(choice,&endptr,10);
        switch (input_int)
        {
        case 1:
            personalDetails(accnum);
            break;
        case 2:
            accDetails(accnum);
            break;
        case 3:
            c_transactionList(accnum);
            break;
        case 0:
            home();
            break;
        default:
            printf("\a");
            customerHome(accnum);
        }
    } else {
        printf("\a");
        customerHome(accnum);
	}
}

void personalDetails(long accnum) { //Customer personal details page
	system("cls");
	FILE* tmp;
	char cList[] = "customerList.txt";

	a.cListptr = fopen("customerList.txt", "r");
	while (fscanf(a.cListptr, "%s%s%d%s%s%ld%d%d", &file.name, &file.mobnum, &file.sex, &file.username, &file.pass, &file.accnum, &file.acctype, &file.balance) != EOF) {
		if (accnum == file.accnum) {
			strcpy(personal.name, file.name);
			strcpy(personal.mobnum, file.mobnum);
			personal.sex = file.sex;
		}
	}
	fclose(a.cListptr);

	printf("\nName:\n%s\n", personal.name);
	printf("Press 1 to update\n\n");

	printf("Mobile number:\n%s\n", personal.mobnum);
	printf("Press 2 to update\n\n");
	if (personal.sex == 1) {
		printf("Gender:\nMale\n\n");
	} else if (personal.sex == 2) {
		printf("Gender:\nFemale\n\n");
	}

	printf("Press 0 to go back\n");

    char choice[100];
	scanf("%s",&choice);
	if(strlen(choice) == 1 && isdigit(choice[0])){
        int mobcntr = 0;
        char mobnum[50];
        char name[50];
        char *endptr;
        int input_int = strtol(choice,&endptr,10);
        switch (input_int) {
        case 1:
            for (int i=0;i<strlen (personal.name); i++){
                personal.name[i] = " ";
            }
            system("cls");
            printf("Enter first name\n");
            firstname_label:
            scanf("%s",name);
            for (int i=0;i<strlen (name); i++){
                if (!isalpha(name[i]))
                {
                    system("cls");
                    printf ("No numerals or special characters\n\nEnter first name\n");
                    goto firstname_label;
                }
            }
            strcpy(personal.name,name);
            break;
        case 2:
            system("cls");
            printf("E");
            mobnum_label:
            printf("nter your Malaysian mobile number\n");
            mymobnum_label:
            scanf("%s", &mobnum);
            for (int i=0;i<strlen (mobnum); i++){
                if (isdigit(mobnum[i]))
                {
                    if(strlen(mobnum) != 10 || mobnum[0] != '0' || mobnum[1] != '1') //has to start with 01, no special characters
                    {
                        if (mobcntr >= 2){
                         system("cls");
                         printf ("Hint: Your number should be 10 digits long and should begin with '01'\n");
                         mobcntr = 0;
                         goto mymobnum_label;
                        }
                        system("cls");
                        mobcntr++;
                        printf ("Invalid format -- Please enter a valid Malaysian number:\n");
                        goto mymobnum_label;
                    }
                } else {
                    system("cls");
                    printf ("Invalid input - Please e");
                    goto mobnum_label;
                }
            }
            strcpy(personal.mobnum,mobnum);
            break;
        case 0:
            customerHome(accnum);
        default:
            printf("\a");
            personalDetails(accnum);
        }
    } else {
        printf("\a");
        personalDetails(accnum);
	}

	a.cListptr = fopen("customerList.txt", "r");
	tmp = fopen("tmp_customerList.txt", "a+");
	while (fscanf(a.cListptr, "%s%s%d%s%s%ld%d%d", &file.name, &file.mobnum, &file.sex, &file.username, &file.pass, &file.accnum, &file.acctype, &file.balance) != EOF) {
		if (accnum == file.accnum) {
			fprintf(tmp, "%s\t%s\t%d\t%s\t%s\t%ld\t%d\t%d\n", personal.name, personal.mobnum, file.sex, file.username, file.pass, file.accnum,file.acctype, file.balance);
		} else {
			fprintf(tmp, "%s\t%s\t%d\t%s\t%s\t%ld\t%d\t%d\n", file.name, file.mobnum, file.sex, file.username, file.pass, file.accnum, file.acctype, file.balance);
		}
	}
	fclose(a.cListptr);
	fclose(tmp);
	remove(cList);
	rename("tmp_customerList.txt", cList);

	printf("Succesfully updated\n\nPress any key to continue...");
	_getch();
	customerHome(accnum);
}

void accDetails(long accnum) { //Customer account details page
	system("cls");
	a.cListptr = fopen("customerList.txt", "r");
	while (fscanf(a.cListptr, "%s%s%d%s%s%ld%d%d", &file.name, &file.mobnum, &file.sex, &file.username, &file.pass, &file.accnum, &file.acctype, &file.balance) != EOF) {
        if (accnum == file.accnum) {
            strcpy(acc.username, file.username);
            strcpy(acc.pass, file.pass);
            acc.accnum = file.accnum;
            acc.acctype = file.acctype;
            acc.balance = file.balance;
        }
	}

    fclose(a.cListptr);

    printf("\nUsername:\n%s\n\n", acc.username);
    printf("Password:\n%s\n\n", acc.pass);
    printf("Account number:\n%ld\n\n", acc.accnum);
    if (acc.acctype == 1) {
        printf("Account type:\nSavings_Account\n\n");
    } else if (acc.acctype == 2) {
        printf("Account type:\nCurrent_Account\n\n");
    }
    printf("Balance:\n%d MYR\n\n", acc.balance);
	printf("Press 1 to make a deposit\nPress 2 to withdraw cash\n\nPress 0 to go back\n");

	char choice[100];
    int input_int;
	char *endptr;
	scanf("%s", &choice);
	if(strlen(choice) == 1 && isdigit(choice[0])){
        input_int = strtol(choice,&endptr,10);
        switch (input_int)
        {
        case 1:
            deposit(accnum);
            break;
        case 2:
            withdraw(accnum);
            break;
        case 0:
            customerHome(accnum);
        default:
            printf("\a");
            accDetails(accnum);
        }
    } else {
        printf("\a");
        accDetails(accnum);
	}

}

void c_transactionList(long accnum) {
    system("cls");
    int transaction;
    bool trans_exists = false;
    a.trans = fopen("transList.txt","r");
    if(a.trans != NULL){
        while(fscanf(a.trans,"%ld%d",&file.accnum,&transaction) != EOF){
            if(file.accnum == accnum){
                trans_exists = true;
                if(transaction > 0){
                    printf("Deposit: %d MYR\n",transaction);
                } else if(transaction < 0){
                    printf("Withdraw: %d MYR\n",abs(transaction));
                }
            }
        }
        if(!trans_exists){
            printf("No transactions available\n");
        }
    } else {
        printf("No transactions available\n");
    }
    fclose(a.trans);

    printf("\nPress any key to exit...");
	_getch();
	customerHome(accnum);
}

void deposit(long accnum) {
    system("cls");
    char input[100];
    int input_int;
	char *endptr;
    printf("Note: You may only make a deposit of MAXIMUM 500 MYR at a time.\n");
    deposit_label:
    printf("Enter the amount you wish to deposit:\n");
    scanf("%s",&input);
    for(int i=0;i<strlen(input);i++){
        if(!isdigit(input[i])) {
            system("cls");
            printf("\aInvalid input\n");
            goto deposit_label;
        }
    }
    input_int = strtol(input,&endptr,10);
    if (input_int>500){
        system("cls");
        printf("You may only make a deposit of MAXIMUM 500 MYR at a time.\n");
        goto deposit_label;
    } else if(input_int == 0){
        system("cls");
        printf("Cannot deposit 0 MYR\n");
        goto deposit_label;
    }
    int deposit = input_int;

    a.trans = fopen("transList.txt", "a+");
    fprintf(a.trans,"%ld\t%d\n",accnum,deposit);
    fclose(a.trans);

	char cList[] = "customerList.txt";
    a.cListptr = fopen("customerList.txt", "r");
    FILE* tmp = fopen("tmp_customerList.txt", "a+");
	while (fscanf(a.cListptr,"%s%s%d%s%s%ld%d%d", &file.name, &file.mobnum, &file.sex, &file.username, &file.pass, &file.accnum, &file.acctype, &file.balance) != EOF) {
		if (accnum == file.accnum) {
            int balance = file.balance;
            int newBalance = balance + deposit;
            fprintf(tmp,"%s\t%s\t%d\t%s\t%s\t%ld\t%d\t%d\n", file.name, file.mobnum, file.sex, file.username, file.pass, file.accnum, file.acctype, newBalance);
		} else {
            fprintf(tmp,"%s\t%s\t%d\t%s\t%s\t%ld\t%d\t%d\n", file.name, file.mobnum, file.sex, file.username, file.pass, file.accnum, file.acctype, file.balance);
		}
	}
	fclose(a.cListptr);
	fclose(tmp);
	remove(cList);
	rename("tmp_customerList.txt", cList);

	system("cls");
	printf("\n%d MYR has been deposited into your account\n\nPress any key to continue...", deposit);
	_getch();
	customerHome(accnum);
}

void withdraw(long accnum) {
    system("cls");
    char input[100];
    int input_int;
	char *endptr;
	char cList[] = "customerList.txt";
	a.cListptr = fopen("customerList.txt", "r");
	while (fscanf(a.cListptr, "%s%s%d%s%s%ld%d%d", &file.name, &file.mobnum, &file.sex, &file.username, &file.pass, &file.accnum, &file.acctype, &file.balance) != EOF) {
		if (accnum == file.accnum) {
            if(file.balance == 0)
            {
                system("cls");
                printf("You have insufficient funds to make withdrawals\nPress any key to continue...");
                fclose(a.cListptr);
                _getch();
                accDetails(accnum);
            }
		}
	}
	fclose(a.cListptr);
    withdraw_label:
    printf("Enter the amount you wish to withdraw:\n");
    scanf("%s",&input);
    for(int i=0;i<strlen(input);i++){
        if(!isdigit(input[i])) {
            system("cls");
            printf("\aInvalid input\n");
            goto withdraw_label;
        }
    }
    input_int = strtol(input,&endptr,10);
    if(input_int == 0){
        system("cls");
        printf("Cannot withdraw 0 MYR\n");
        goto withdraw_label;
    }
    int withdrawal = input_int;

    a.cListptr = fopen("customerList.txt", "r");
    FILE* tmp = fopen("tmp_customerList.txt", "a+");
    int newBalance;
	while (fscanf(a.cListptr, "%s%s%d%s%s%ld%d%d", &file.name, &file.mobnum, &file.sex, &file.username, &file.pass, &file.accnum, &file.acctype, &file.balance) != EOF) {
		if (accnum == file.accnum) {
            if (withdrawal>file.balance){
                system("cls");
                printf("Insufficient balance\n");
                fclose(a.cListptr);
                fclose(tmp);
                goto withdraw_label;
            }
            newBalance = file.balance - withdrawal;
            fprintf(tmp,"%s\t%s\t%d\t%s\t%s\t%ld\t%d\t%d\n", file.name, file.mobnum, file.sex, file.username, file.pass, file.accnum, file.acctype, newBalance);
		} else {
            fprintf(tmp,"%s\t%s\t%d\t%s\t%s\t%ld\t%d\t%d\n", file.name, file.mobnum, file.sex, file.username, file.pass, file.accnum, file.acctype, file.balance);
		}
	}
	fclose(a.cListptr);
	fclose(tmp);
	remove(cList);
	rename("tmp_customerList.txt", cList);

    a.trans = fopen("transList.txt", "a+");
    fprintf(a.trans,"%ld\t-%d\n",accnum,withdrawal);
    fclose(a.trans);

	system("cls");
	printf("%d MYR has been withdrawn from your account\n\nPress any key to continue...", withdrawal);
	_getch();
	customerHome(accnum);
}

