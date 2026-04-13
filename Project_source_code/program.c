#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_T 30
#define MAX_R 50
#define MAX_B 200

// -------- STRUCTURES --------

struct Teacher {
    char name[50];
    char password[10];
};

struct Classroom {
    char name[20];
    int capacity;
    char type[20];
};

struct Booking {
    char teacher[50];
    char division[10];
    char subject[30];
    char classroom[20];
    int day, month;
    int sh, sm;
    int eh, em;
    int checked;
    int cancelled;
};

// -------- DATA --------

struct Teacher teachers[MAX_T] = {
 {"Sayali Nikam","T101"},{"Nikhil Soniminde","T102"},
 {"Arunabh Pandey","T103"},{"Vivek Patel","T104"},
 {"Shital Kahane","T105"},{"Pradnya Deshpande","T106"},
 {"Deepak Prashar","T107"},{"Siddharth Chakrabarti","T108"},
 {"Vrunda Agarkar","T109"},{"Jayashree Aher","T110"},
 {"Geetanjali Dagonnkar","T111"},{"M D Hambarde","T112"},
 {"Anusha Pai","T113"},{"Madhu Jagdesh","T114"},
 {"Aditi Karpe","T115"},{"Kundan Nagare","T116"},
 {"Arunabha Kulkarni","T117"},{"Chaitanya Burande","T118"},
 {"Sagar Kolapkar","T119"},{"Mohini Bagul","T120"},
 {"Shruti Mishra","T121"},{"Samsuzzaman","T122"},
 {"Renuka Mane","T123"},{"Aditi Jahagirdar","T124"},
 {"Rekha Joshi","T125"},{"Sangeeta Natu","T126"},
 {"Shriram Bonder","T127"},{"Bhumi Jaiswal","T128"},
 {"Snehal Jadhav","T129"}
};

int totalTeachers = 29;

struct Classroom rooms[MAX_R];
int roomCount = 0;

struct Booking bookings[MAX_B];
int bookingCount = 0;

// -------- TIME --------
void getTime(int *h,int *m,int *d,int *mo){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    *h = tm.tm_hour;
    *m = tm.tm_min;
    *d = tm.tm_mday;
    *mo = tm.tm_mon+1;
}

// -------- INIT ROOMS (ARYABHATA) --------
void initRooms(){
    strcpy(rooms[0].name,"AB006"); rooms[0].capacity=60; strcpy(rooms[0].type,"mechanics");

    strcpy(rooms[1].name,"AB104"); rooms[1].capacity=70; strcpy(rooms[1].type,"class");
    strcpy(rooms[2].name,"AB105"); rooms[2].capacity=70; strcpy(rooms[2].type,"class");
    strcpy(rooms[3].name,"AB107"); rooms[3].capacity=70; strcpy(rooms[3].type,"class");

    strcpy(rooms[4].name,"AB203"); rooms[4].capacity=60; strcpy(rooms[4].type,"computer");
    strcpy(rooms[5].name,"AB204"); rooms[5].capacity=60; strcpy(rooms[5].type,"computer");
    strcpy(rooms[6].name,"AB205"); rooms[6].capacity=60; strcpy(rooms[6].type,"computer");

    strcpy(rooms[7].name,"AB303"); rooms[7].capacity=70; strcpy(rooms[7].type,"class");
    strcpy(rooms[8].name,"AB304"); rooms[8].capacity=70; strcpy(rooms[8].type,"class");

    strcpy(rooms[9].name,"AB403"); rooms[9].capacity=50; strcpy(rooms[9].type,"chem");
    strcpy(rooms[10].name,"AB404"); rooms[10].capacity=50; strcpy(rooms[10].type,"chem");

    roomCount = 11;
}

// -------- LOGIN --------
int login(){
    char name[50],pass[10];
    printf("\n1.Admin\n2.Faculty\nChoice: ");
    int r; scanf("%d",&r);

    if(r==1){
        printf("Admin pass: ");
        scanf("%s",pass);
        if(strcmp(pass,"admin123")==0) return 100;
        return -1;
    }

    printf("Name: "); scanf(" %[^\n]",name);
    printf("Pass: "); scanf("%s",pass);

    for(int i=0;i<totalTeachers;i++){
        if(strcmp(name,teachers[i].name)==0 &&
           strcmp(pass,teachers[i].password)==0)
           return i;
    }
    return -1;
}

// -------- AUTO CANCEL --------
void autoCancel(){
    int h,m,d,mo;
    getTime(&h,&m,&d,&mo);

    for(int i=0;i<bookingCount;i++){
        if(bookings[i].checked==0 && bookings[i].cancelled==0 &&
           bookings[i].day==d){

            if(h==bookings[i].sh && m>bookings[i].sm+20){
                bookings[i].cancelled=1;
                printf("⚠ Auto cancelled %s\n",bookings[i].subject);
            }
        }
    }
}

// -------- BOOK --------
void book(){
    printf("Teacher: "); scanf(" %[^\n]", bookings[bookingCount].teacher);
    printf("Division: "); scanf("%s", bookings[bookingCount].division);
    printf("Subject: "); scanf("%s", bookings[bookingCount].subject)
    printf("Room: "); scanf("%s", bookings[bookingCount].classroom);

    printf("Date (DD MM): ");
    scanf("%d%d",&bookings[bookingCount].day,
                  &bookings[bookingCount].month);

    printf("Start (HH MM): ");
    scanf("%d%d",&bookings[bookingCount].sh,
                  &bookings[bookingCount].sm);

    printf("End (HH MM): ");
    scanf("%d%d",&bookings[bookingCount].eh,
                  &bookings[bookingCount].em);

    bookings[bookingCount].checked=0;
    bookings[bookingCount].cancelled=0;

    bookingCount++;
    printf("✅ Booked\n");
}

// -------- VIEW --------
void viewAll(){
    for(int i=0;i<bookingCount;i++){
        printf("%d. %s | %s | %s | %s | %02d/%02d | %02d:%02d | %s\n",
        i+1,
        bookings[i].teacher,
        bookings[i].division,
        bookings[i].subject,
        bookings[i].classroom,
        bookings[i].day, bookings[i].month,
        bookings[i].sh, bookings[i].sm,
        bookings[i].cancelled?"Cancelled":
        bookings[i].checked?"Done":"Scheduled");
    }
}

// -------- PUNCH --------
void punch(char name[]){
    int h,m,d,mo;
    getTime(&h,&m,&d,&mo);

    for(int i=0;i<bookingCount;i++){
        if(strcmp(name,bookings[i].teacher)==0 &&
           bookings[i].day==d &&
           bookings[i].sh==h){

            bookings[i].checked=1;
            printf("✅ Checked in\n");
            return;
        }
    }
    printf("❌ No lecture now\n");
}

// -------- MAIN --------
int main(){

    initRooms();

    int user = login();
    if(user==-1){
        printf("Login failed");
        return 0;
    }

    int ch;

    if(user==100){
        while(1){
            autoCancel();

            printf("\n--- ADMIN ---\n");
            printf("1.Book\n2.View\n3.Exit\n");
            scanf("%d",&ch);

            if(ch==1) book();
            else if(ch==2) viewAll();
            else break;
        }
    }
    else{
        while(1){
            autoCancel();

            printf("\n--- FACULTY ---\n");
            printf("1.View My Lectures\n2.Punch In\n3.Exit\n");
            scanf("%d",&ch);

            if(ch==1) viewAll();
            else if(ch==2) punch(teachers[user].name);
            else break;
        }
    }
} add this
