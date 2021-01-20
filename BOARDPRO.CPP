 //************************************************************//
 //************WELCOME TO C++ HOTEL MANAGEMENT PROJECT*********//
 //************************************************************//
#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<fstream.h>
#include<stdio.h>
#include<dos.h>
#include<stdlib.h>

 //************************************************************//
 //***********************CLASS HOTEL**************************//
 //************************************************************//

class hotel
{
int room_no;
char name[30];
char address[50];
int check(int);   //to check room status
void modify(int); //to modify the record
void delete_rec(int);//to delete the record
long long unsigned int phone;

public:

void main_menu(); //to display the main menu
void add();       //to book a room
void display();   //to display the customer record
void rooms();     //to display alloted rooms
void edit();      //edit the customer record

};
//*************************************************************//
//************************MAIN MENU****************************//
//*************************************************************//

void hotel::main_menu()
{
char choice;
do
{
clrscr();
setbkcolor(10);
cout<<"\n\t\t\t  *****************************";
cout<<"\n\t\t\t\t  ***MAIN MENU***";
cout<<"\n\t\t\t  *****************************";
cout<<"\n\n\n\t\t\t1.Book A Room\n";
cout<<"\t\t\t2.Customer Record\n";
cout<<"\t\t\t3.Rooms Allotted\n";
cout<<"\t\t\t4.Edit Record\n";
cout<<"\t\t\t5.Exit\n";
cout<<"\n\n\n\t\t\tEnter Your Choice:";
cin>>choice;
switch(choice)
{
case '1':add();
break;
case '2':display();
break;
case '3':rooms();
break;
case '4':edit();
break;
case '5':break;
default:
{
cout<<"\n\n\n\t\t\tWrong Choice....!!!";
cout<<"\nPress any key to continue..!!!";
getch();
}
}
}
while(choice!='5');
}
//************************************************************//
//************FUNCTION TO ADD A CUSTOMER IN RECORDS***********//
//************************************************************//
void hotel::add()
{
clrscr();
setbkcolor(3);
int r,flag;
ofstream fout;
fout.open("Record.dat",ios::app|ios::binary);
as:cout<<"\nEnter Customer Details";
cout<<"---------------------------";
cout<<"\nRoom no:";
cin>>r;
flag=check(r);
if(flag)
{
cout<<"\nSorry..!!!Room is already booked";
goto as;
}
else
{
room_no=r;
cout<<"Name:";
gets(name);
cout<<"Address:";
gets(address);
cout<<"Phone No:";
cin>>phone;
fout.write((char*)this,sizeof(hotel));
cout<<"\nRoom is booked...!!!";
}
cout<<"\nPress any key to continue..!!";
getch();
fout.close();
}
//************************************************************//
//**********FUNCTION TO CHECK THE RECORD OF ANY ROOM**********//
//************************************************************//
void hotel::display()
{
clrscr();
setbkcolor(1);
ifstream fin("Record.dat",ios::in|ios::binary);
int r,flag=0;
cout<<"\nEnter room no:";
cin>>r;
while(!fin.eof())
{
fin.read((char*)this,sizeof(hotel));
if(room_no==r)
{
clrscr();
cout<<"\nCustomer Details";
cout<<"\n------------------------";
cout<<"\nRoom no:"<<room_no;
cout<<"\nName: "<<name;
cout<<"\nAddress:"<<address;
cout<<"\nPhone no:"<<phone;
flag=1;
break;
}
}
if(flag==0)
cout<<"\nSorry Room no.not found or vacant...!!!";
cout<<"\n\nPress any key to continue..!!!";
getch();
fin.close();
}
//************************************************************//
//************FUNCTION TO DISPLAY ALLOTTED ROOMS**************//
//************************************************************//
void hotel::rooms()
{
clrscr();
setbkcolor(2);
ifstream fin("Record.dat",ios::in|ios::binary);
cout<<"\n\t\t\tList Of Rooms Allotted";
cout<<"\n\t\t\t------------------";
cout<<"\n\nRoom No.   Name\t\t\tAddress \t\t      Phone No.\n";
while(!fin.eof())
{
fin.read((char*)this,sizeof(hotel));
if(fin.eof())
break;
cout<<"\n\n"<<room_no<<"       "<<name;
cout<<"        "<<address<<"    "<<phone;
}
cout<<"\n\nPress any key to continue..!!!";
getch();
fin.close();
}
//************************************************************//
//****************FUNCTION TO EDIT THE RECORD*****************//
//************************************************************//
void hotel::edit()
{
clrscr();
setbkcolor(9);
int choice,r;
cout<<"\nEDIT MENU";
cout<<"\n------------------";
cout<<"\n\n1.Modify Customer Record";
cout<<"\n\n2.Delete Customer Record";
cout<<"\n\n3.Go Back To Main Menu";
cout<<"\nEnter your choice:";
cin>>choice;
clrscr();
if(choice!=3)
{
cout<<"\nEnter Room No:";
cin>>r;
switch(choice)
{
case 1:modify(r);
break;
case 2:delete_rec(r);
break;
default:
cout<<"\n\n\n\t\t\tWrong Choice....!!!";
}
}
cout<<"\nPress any key to continue...!!!";
getch();
}
//************************************************************//
//*********FUNCTION TO CHECK IF ROOM IS VACANT OR NOT*********//
//************************************************************//
int hotel::check(int r)
{
int flag=0;
ifstream fin("Record.dat",ios::in|ios::binary);
while(!fin.eof())
{
fin.read((char*)this,sizeof(hotel));
if(room_no==r)
{
flag=1;
break;
}
}

fin.close();
return(flag);
}
//************************************************************//
//*****************FUNCTION TO MODIFY RECORD******************//
//************************************************************//
void hotel::modify(int r)
{
setbkcolor(3);
long pos,flag=0;
fstream file("Record.dat",ios::in|ios::out|ios::binary);
while(!file.eof())
{
pos=file.tellg();
file.read((char*)this,sizeof(hotel));
if(room_no==r)
{
cout<<"You are modifying the data:\n";
cout<<"Enter New Details";
cout<<"\n--------------------\n";
cout<<"Name:";
gets(name);
cout<<"Address:";
gets(address);
cout<<"Phone No:";
cin>>phone;
file.seekg(pos);
file.write((char*)this,sizeof(hotel));
cout<<"\nRecord is modified...!!!";
flag=1;
break;
}
}
if(flag==0)
cout<<"\nSorry Room no.not found or vacant...!!!";
file.close();
}
//************************************************************//
//****************FUNCTION TO DELETE RECORDS******************//
//************************************************************//
void hotel::delete_rec(int r)
{
setbkcolor(8);
ifstream fin("Record.dat",ios::in|ios::ate|ios::binary);
ofstream fout("temp.dat",ios::out|ios::ate|ios::binary);
char found='f',confirm='n';
fin.seekg(0);
fout.seekp(0);
while(!fin.eof())
{
fin.read((char*)this,sizeof(hotel));
if(fin.eof())
break;
if(room_no==r)
{
cout<<"\nName:"<<name;
cout<<"\nAddress:"<<address;
cout<<"\nPhone no:"<<phone;
found='t';
cout<<"\nAre you sure ,you want to delete this record?(y/n)..";
cin>>confirm;
if(confirm=='n')
{
fout.write((char*)this,sizeof(hotel));
}
else if(confirm=='y');
}
else
fout.write((char*)this,sizeof(hotel));
}
if(found=='f')
cout<<"Sorry,record not found!!!..\n";
fin.close();
fout.close();
fflush(stdin);
remove("Record.dat");
rename("temp.dat","Record.dat");
if(found=='t')
cout<<"successfully deleted\n";
getch();
}
//************************************************************//
//**********************MAIN FUNCTION*************************//
//************************************************************//
void main()
{
hotel h;
clrscr();
int gd=DETECT, gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
 setbkcolor(RED);
 rectangle(10,10,630,470);
 settextstyle(GOTHIC_FONT,0,4);
 setcolor(WHITE);
 outtextxy(30,35,"Developed By:-");
 settextstyle(10,0,3);
 setcolor(1);
 settextstyle(1,0,4);
 outtextxy(150,100,"SAURAV KUMAR SINGH");
settextstyle(4,HORIZ_DIR,4);
setcolor(14);
outtextxy(100,350,"WELCOME TO C++ PROJECT");
getch();
for (int c=0;c<=152;++c)
{
setbkcolor(c%15);
setcolor(12);
fillellipse(315,240,c*1.3,c*.65);
delay(80);
}
settextstyle(1,0,4);
setcolor(5);
outtextxy(160,220,"HOTEL MANAGEMENT");
getch();
cleardevice();
setcolor(RED);
setbkcolor(7);
cout<<"\n\t\t\t********************";
cout<<"\n\t\t\t*HOTEL MANAGEMENT PROJECT*";
cout<<"\n\t\t\t********************";
h.main_menu();
   int area, temp1, temp2, left = 25, top = 75;
   void *p;

   initgraph(&gd,&gm,"C:\\TC\\BGI");

   setcolor(YELLOW);
   circle(50,100,25);
   setfillstyle(SOLID_FILL,YELLOW);
   floodfill(50,100,YELLOW);

   setcolor(BLACK);
   setfillstyle(SOLID_FILL,BLACK);
   fillellipse(44,85,2,6);
   fillellipse(56,85,2,6);

   ellipse(50,100,205,335,20,9);
   ellipse(50,100,205,335,20,10);
   ellipse(50,100,205,335,20,11);

   area = imagesize(left, top, left + 50, top + 50);
   p = malloc(area);

   setcolor(WHITE);
   settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);
   outtextxy(155,451,"THANKYOU FOR COMING");

   setcolor(BLUE);
   rectangle(0,0,639,449);

   while(!kbhit())
   {
      temp1 = 1 + random ( 588 );
      temp2 = 1 + random ( 380 );

      getimage(left, top, left + 50, top + 50, p);
      putimage(left, top, p, XOR_PUT);
      putimage(temp1 , temp2, p, XOR_PUT);
      sound(220);
      delay(100);
      nosound;
      left = temp1;
      top = temp2;
   }

   getch();
   closegraph();
}
