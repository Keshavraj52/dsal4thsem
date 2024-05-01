#include<iostream>
using namespace std;
# define max 20
class stud
{
int mks[max];
public:
stud()
{
for(int i=0;i<max;i++)
mks[i]=0;
}
void insertheap(int tot);
void displayheap(int tot);
void showmax(int tot);
void showmin();
};
void stud::insertheap(int tot)
{
for(int i=1;i<=tot;i++)
{
cout<<"Enter marks:";
cin>>mks[i];
int j=i;
int par=j/2;
while(mks[j]<=mks[par] && j!=0)
{
int tmp = mks[j];
mks[j]=mks[par];
mks[par]=tmp;
j=par;
par=j/2;
}
}
}
void stud::displayheap(int tot)
{
int i=1,space=6;
cout<<endl;
while(i<=tot)
{
if(i==1 || i==2 || i==4 || i==8 || i==16)
{
cout<<endl<<endl;
for(int j=0;j<space;j++)
cout<<" ";
space-=2;
}
cout<<" "<<mks[i];i++;
}
}
void stud::showmax(int tot)
{
int max1=mks[1];
for(int i=2;i<=tot;i++)
{
if(max1<mks[i])
max1= mks[i];
}
cout<<"Max marks:"<<max1;
}
void stud::showmin()
{
cout<<"Min marks:"<<mks[1];
}
int main()
{
int ch,cont,total,tmp;
int n;
stud s1;
cout<<"Menu";
cout<<endl<<"1.Read marks of the student ";
cout<<endl<<"2.Display Min heap";
cout<<endl<<"3.Find Max Marks";
cout<<endl<<"4.Find Min Marks\n";
do
{
cout<<"---------------------\n";
cout<<"Enter Choice :: ";
cin>>ch;
switch(ch)
{
case 1:
cout<<"---------------------\n";
cout<<"How many students:";
cin>>total;
s1.insertheap(total);
break;
case 2:
cout<<"\n---------------------\n";
s1.displayheap(total);
break;
case 3:
cout<<"\n---------------------\n";
s1.showmax(total);
break;
case 4:
cout<<"\n---------------------\n";
s1.showmin();
break;
}
cout<<"\n---------------------\n";
cout<<"do u want to continue?(1 for continue)";
cin>>cont;
}while(cont==1);
return 0;
}
