#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

//�C�Ӧ����Ӹ` 
struct user{
	char username[13];//�Τ�W�� 
	char accountname[13];//�b��W�� 
	char password[13];//�K�X 
	int login_number;//�n�J���� 
	int money;//�x�Ȫ� 
	int XAXBwin;
	int XAXBlose;
	int Sodokuwin;
	int Sodokulose;
};

//�����`�� 
struct userlist{          //users
	int user_number;
	user member[100];
};

//�C�M���ƲӸ`
struct drinks{           //drink
	int buyer_id;        //�R�a��user_id 
	int finish;          //0�O������ 1�O���� 
	int name;
	int ice;//0--�h�B,1--�L�B,2--�֦B 
	int sugar;//0--�L�},1--�L�},2--�b�},3--���} 
	int size;//0--medium,1--large
	//�t�Ʀ��ŦA��int topping;
	int price;
};                                    //�@���I�ܦh�M?????????? 

//�q���`��
struct orderlist{         //orders
	int order_number;     //�q���`�� 
	int order_now;
	drinks member[100];
}; 



//�n�Jfunction 
userlist LoadUsers();
int Login(userlist users);
void input_accountname(char un[]);
void input_password(char un[],char pw[]);

//���Ufunction
void addaccount(char nun[],char nan[],char npw[],userlist users);
void input_username(char un[]);
void SaveUser(userlist users); 

//�d�q��function
void CheckOrder(orderlist orders,int user_id); 

//MainScreen
void MainScreen(int select,userlist users,int j);
int MainUI(int select,userlist users,int j);

//SellerMainScree
void SellerMainScreen(int sellerselect);
int SellerMainUI(int sellerselect);
void SellerCheckOrder(orderlist orders);
void AddValue(userlist users);
void CheckUnfinishedOrder(orderlist orders,int order_id);
void CheckFinishedOrder(orderlist orders);

//OrderMainScreen
orderlist LoadOrders();
void OrderMain(userlist users,int user_id,orderlist orders,int ordernumber);
void SaveOrder(orderlist orders);

//���ƲӶ�
void OrderAScreen(int choice);//�~�� 
int OrderAUI(int choice);
void OrderBScreen(int choice);//�B�� 
int OrderBUI(int choice);
void OrderCScreen(int choice);//���� 
int OrderCUI(int choice);
void OrderDScreen(int choice);//�ؤo 
int OrderDUI(int choice);
void OrderEScreen(int choice);//�t�Ʀ��ŦA�� 
int OrderEUI(int choice); 


//�ƿWfunction 
void Sudoku_init(int p[][9][10]);
void Sudoku_update(int p[][9][10],int R,int C,int N);
void Sudoku_Read(int Qno, int Q[][9], int p[][9][10]);
void Sudoku_Print(int Q[][9],int A[][9],int R,int C);
int Sudoku_Check(int p[][9][10],int R,int C);
void Sudoku_MainUI(int Q[][9],int A[][9]);
void Sudoku_main(userlist users,int user_id);

//XAXBfunction
void XAXBnumtodigit(int num,int digit[]);
bool XAXBislegal(int num);
void XAXB(int guess,int answer,int AB[]);
void XAXBmain(userlist users,int user_id);

//Chatroomfunction
void Chatroom(userlist users,int user_id);

//�ק�|�����functon
void ChangeAccount(userlist users,int user_id); 



//tool
void anykey()
{
	char c = getch();
	if(c==0||c==-32)
		getch();
}


int main()
{
	char newusername[13],newaccountname[13],newpassword[13]; 
	int user_id;
	int order_id;
	orderlist orders;
	userlist users;
	orders=LoadOrders();
	users = LoadUsers();
	
	
	
	if(orders.order_number==0)
		order_id=0;
	else
		order_id=orders.order_number-1;
		
	user_id = Login(users);
	while(user_id==-3)
		user_id = Login(users);
		
		
	if(user_id==-2)
	{
		int sellerselect=1;
		do
		{
			sellerselect=SellerMainUI(sellerselect);
			switch(sellerselect)
			{
				case 1:
					SellerCheckOrder(orders);
					orders=LoadOrders();
					getch();
					break;
				case 2:
					AddValue(users);
					users = LoadUsers();
					getch();
					break;
				case 3:
					CheckUnfinishedOrder(orders,order_id);
					orders=LoadOrders();
					getch();
					break;
				case 4:
					CheckFinishedOrder(orders);
					orders=LoadOrders();
					getch();
					break;
			}
		}while(sellerselect!=0);
	}
	system("cls");
	

	if(user_id>=-1)
	{	
		if(user_id==-1)//���s�|�� 
		{	
			addaccount(newusername,newaccountname,newpassword,users); 
			users = LoadUsers();
			user_id=users.user_number-1;
		}
	
		users.member[user_id].login_number++;
		SaveUser(users);
	
		if(order_id!=0)
			order_id++;
					
		int select = 1;
		do
		{
			select = MainUI(select,users,user_id);
			switch(select)
			{
				case 1:  //Order
					orders.order_number++;
					OrderMain(users,user_id,orders,order_id); 
					order_id++;
					orders= LoadOrders();
					users = LoadUsers();
					getch();
					break;
				case 2:
					CheckOrder(orders,user_id);
					getch();
					break;
				case 3:
					ChangeAccount(users,user_id); 
					users = LoadUsers();
					getch();
					break;
				case 4:
					Chatroom(users,user_id);
					getch();
					break;
				case 5:
					Sudoku_main(users,user_id);
					users = LoadUsers();
					getch();
					break;
				case 6:
					XAXBmain(users,user_id);
					users = LoadUsers();
					getch();
					break;
			}
		}while(select!=0);
	} 
	system("cls");
	
		
		
	return 0;
}


void SellerMainScreen(int sellerselect)
{
	system("cls");
	int i;
	char L[5],R[5];
	for(i=0;i<5;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[sellerselect] = '[';
	R[sellerselect] = ']';
	cout << endl<< endl<< endl<< endl<< endl<<endl;
	cout<<"								 __         ___.          __             " <<endl; 
	cout<<" 								|  | __ ____\\_ |__  __ __|  | __ ____  	 " <<endl; 
	cout<<"							 	|  |/ // __ \\| __ \\|  |  \\  |/ // __ \\    " <<endl; 
	cout<<"							 	|    <\\  ___/| \\_\\ \\  |  /    <\\  __/    " <<endl; 
	cout<<"							 	|__|__\\\\____ >____ /____/|__|__\\\\____ >   " <<endl; 
	cout<<"							 ____________________________________________________                                               " <<endl; 
	cout<<"							 ____________________________________________________                                      			"<<endl<<endl<<endl<<endl;
	cout<<"                                       						                                                                   "<<endl<<endl<<endl;
	cout <<"      				    		     "<< L[1] << "1" << R[1] << " �d�ݩҦ��q��" << endl;
	cout <<"        					     "<< L[2] << "2" << R[2] << " �U���x��" << endl;
	cout <<"         				  	     "<< L[3] << "3" << R[3] << " ��s�q��" << endl;
	cout <<"         					     "<< L[4] << "4" << R[4] << " �d�ݤw�����q�����~�B" << endl;
	cout <<"          					     "<< L[0] << "5" << R[0] << " ���}�t��" << endl;
}



int SellerMainUI(int sellerselect)
{ 
	char x,x1;
	do{
		SellerMainScreen(sellerselect);
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==72)  //�W 
				sellerselect = (sellerselect + 4)%5;
			if(x1==80)  //�U 
				sellerselect = (sellerselect + 1)%5;
			if(x1==77)  //�k 
				x=13;  //enter
		}
		if(x>='0' && x<='4')
			sellerselect = x - '0';
	}while(x!=13);
	return sellerselect;
}


void CheckFinishedOrder(orderlist orders)
{
	system("cls");
	int i,sum=0;
	for(i=0;i<orders.order_number;i++)
	{
		orders=LoadOrders();
		if(orders.member[i].finish==1)
		{	
			switch(orders.member[i].name)
			{
				case 1:
					cout<<"��������"<<endl;
					break;
				case 2:
					cout<<"�R�K����"<<endl;
					break;
				case 3:
					cout<<"�Ӧm����"<<endl;
					break;
				case 4:
					cout<<"���ì���"<<endl;
					break;
				case 5:
					cout<<"�����N�S"<<endl;
					break;
				case 6:
					cout<<"����N�S"<<endl;
					break;
				case 7:
					cout<<"�K�ާN�S"<<endl;
					break;
				case 8:
					cout<<"�K�޺��"<<endl;
					break;
				case 9:
					cout<<"�K���B��"<<endl;
					break;
				case 10:
					cout<<"�N�S����"<<endl;
					break;
				case 11:
					cout<<"��������"<<endl;
					break;
				case 12:
					cout<<"�եɼ���"<<endl;
					break;
				case 13:
					cout<<"���ɼ���"<<endl;
					break;
				case 14:
					cout<<"���ɼگS"<<endl;
					break;
				case 15:
					cout<<"�گ׬���"<<endl;
					break;
				case 0:
					cout<<"�گצh�h"<<endl;
					break;
			}
			switch(orders.member[i].ice)
			{
				case 1:
					cout<<"�h�B"<<endl;
					break;
				case 2:
					cout<<"�L�B"<<endl;
					break;
				case 0:
					cout<<"�֦B"<<endl;
					break;	
			}
			switch(orders.member[i].sugar)
			{
				case 1:
					cout<<"�L�}"<<endl;
					break;
				case 2:
					cout<<"�L�}"<<endl;
					break;
				case 3:
					cout<<"�b�}"<<endl;
					break;
				case 0:
					cout<<"���}"<<endl;
					break;
			}
			switch(orders.member[i].size)
			{
				case 1:
					cout<<"�p�M"<<endl;
					break;
				case 2:
					cout<<"���M"<<endl;
					break;
				case 0:
					cout<<"�j�M"<<endl;
					break;
			}
			cout<<"���B: "<<orders.member[i].price<<" ��"<<endl<<endl;
			sum=sum+orders.member[i].price;
		} 
	}
	cout<<"�`���J: "<<sum<<" ��"<<endl; 
	cout<< "Press any key to continue";
}

void CheckUnfinishedOrder(orderlist orders,int order_id)
{
	system("cls");
	char x,x1;
	int i;
	for(i=0;i<orders.order_number;i++)
	{	
		orders=LoadOrders();
		if(orders.member[i].finish==0)
		{	
			system("cls");
			switch(orders.member[i].name)
			{
				case 1:
					cout<<"��������"<<endl;
					break;
				case 2:
					cout<<"�R�K����"<<endl;
					break;
				case 3:
					cout<<"�Ӧm����"<<endl;
					break;
				case 4:
					cout<<"���ì���"<<endl;
					break;
				case 5:
					cout<<"�����N�S"<<endl;
					break;
				case 6:
					cout<<"����N�S"<<endl;
					break;
				case 7:
					cout<<"�K�ާN�S"<<endl;
					break;
				case 8:
					cout<<"�K�޺��"<<endl;
					break;
				case 9:
					cout<<"�K���B��"<<endl;
					break;
				case 10:
					cout<<"�N�S����"<<endl;
					break;
				case 11:
					cout<<"��������"<<endl;
					break;
				case 12:
					cout<<"�եɼ���"<<endl;
					break;
				case 13:
					cout<<"���ɼ���"<<endl;
					break;
				case 14:
					cout<<"���ɼگS"<<endl;
					break;
				case 15:
					cout<<"�گ׬���"<<endl;
					break;
				case 0:
					cout<<"�گצh�h"<<endl;
					break;
			}
			switch(orders.member[i].ice)
			{
				case 1:
					cout<<"�h�B"<<endl;
					break;
				case 2:
					cout<<"�L�B"<<endl;
					break;
				case 0:
					cout<<"�֦B"<<endl;
					break;	
			}
			switch(orders.member[i].sugar)
			{
				case 1:
					cout<<"�L�}"<<endl;
					break;
				case 2:
					cout<<"�L�}"<<endl;
					break;
				case 3:
					cout<<"�b�}"<<endl;
					break;
				case 0:
					cout<<"���}"<<endl;
					break;
			}
			switch(orders.member[i].size)
			{
				case 1:
					cout<<"�p�M"<<endl;
					break;
				case 2:
					cout<<"���M"<<endl;
					break;
				case 0:
					cout<<"�j�M"<<endl;
					break;
			}
			cout<<"���B: "<<orders.member[i].price<<" ��"<<endl;
			cout<<endl<<"Press down arrow key to finish the order."<<endl;
			x=getch();
			if(x==-32)
			{
				x1=getch();
				if(x1==80)
				{
					orders.member[i].finish=1;
					orders.order_now++;
			    	SaveOrder(orders);
			    	if(i==order_id)
			    		cout<<endl<<"�q��w�����B�z����!"<<endl; 
				}
			}
			else if(x1!=80)
				break;
		} 
	}
	cout << "Press any key to continue";
}

void AddValue(userlist users)
{
	char c1,c2,un[13];
	int n=0,i,j,value=0;
	do
	{
		system("cls");
		cout << "�|���W��: ";
		for(i=0;i<n;i++)
			cout << un[i];
		c1 = getch();
		if(c1==-32 || c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z') || (c1>='A'&&c1<='Z') || (c1>='0'&&c1<='9') || c1=='_')
		{
			if(n==12)
			{
				un[11] = c1;
			}
			else
			{
				un[n] = c1;
				n++;
			}
		}
		if(c1==8 && n>0)
			n--;
	}while(c1!=13 || n==0);
	un[n] = '\0';
	
	for(j=0;j<users.user_number;j++)
	{
		if(strcmp(un,users.member[j].accountname)==0)
		{
			system("cls");
			cout<<"�A�n�� "<<users.member[j].accountname<<" �[�Ȧh�ֿ�: ";
			cin>>value;
			users.member[j].money=users.member[j].money+value;
			SaveUser(users);
			cout<<endl<<"�n���w�g�[�ȧ����o~~~";
			break;
		}
		else
		{
			system("cls");
			cout<<"�S���o�ӤH��!"<<endl; 
		}
	}
	cout << endl << "Press any key to continue";
}





void SellerCheckOrder(orderlist orders)
{
	system("cls");
	int i;
	for(i=0;i<orders.order_number;i++)
	{
		switch(orders.member[i].name)
		{
			case 1:
				cout<<"��������"<<endl;
				break;
			case 2:
				cout<<"�R�K����"<<endl;
				break;
			case 3:
				cout<<"�Ӧm����"<<endl;
				break;
			case 4:
				cout<<"���ì���"<<endl;
				break;
			case 5:
				cout<<"�����N�S"<<endl;
				break;
			case 6:
				cout<<"����N�S"<<endl;
				break;
			case 7:
				cout<<"�K�ާN�S"<<endl;
				break;
			case 8:
				cout<<"�K�޺��"<<endl;
				break;
			case 9:
				cout<<"�K���B��"<<endl;
				break;
			case 10:
				cout<<"�N�S����"<<endl;
				break;
			case 11:
				cout<<"��������"<<endl;
				break;
			case 12:
				cout<<"�եɼ���"<<endl;
				break;
			case 13:
				cout<<"���ɼ���"<<endl;
				break;
			case 14:
				cout<<"���ɼگS"<<endl;
				break;
			case 15:
				cout<<"�گ׬���"<<endl;
				break;
			case 0:
				cout<<"�گצh�h"<<endl;
				break;
		}
		switch(orders.member[i].ice)
		{
			case 1:
				cout<<"�h�B"<<endl;
				break;
			case 2:
				cout<<"�L�B"<<endl;
				break;
			case 0:
				cout<<"�֦B"<<endl;
				break;	
		}
		switch(orders.member[i].sugar)
		{
			case 1:
				cout<<"�L�}"<<endl;
				break;
			case 2:
				cout<<"�L�}"<<endl;
				break;
			case 3:
				cout<<"�b�}"<<endl;
				break;
			case 0:
				cout<<"���}"<<endl;
				break;
		}
		switch(orders.member[i].size)
		{
			case 1:
				cout<<"�p�M"<<endl;
				break;
			case 2:
				cout<<"���M"<<endl;
				break;
			case 0:
				cout<<"�j�M"<<endl;
				break;
		}
		switch(orders.member[i].finish)
		{
			case 0:
				cout<<"�|������"<<endl;
				break;
			case 1:
				cout<<"�w����"<<endl; 
				break;
		}
		cout<< "���B�G "<<orders.member[i].price<<" ��"<<endl<<endl;
		
	}
	cout << "Press any key to continue";
}
void XAXBnumtodigit(int num,int digit[])
{
	digit[0]=num/1000;
	digit[1]=(num%1000)/100;
	digit[2]=(num%100)/10;
	digit[3]=num%10;
}


bool XAXBislegal(int num)
{
	int d[4],i,j;
	XAXBnumtodigit(num,d);
	for(i=0;i<3;i++)
	{
		for(j=i+1;j<4;j++)
		{
			if(d[i]==d[j])
				return false;
		}
	}
	return true;
}

void XAXB(int guess,int answer,int AB[])
{
	AB[0]=0;
	AB[1]=0;
	int guessdigit[4];
	int answerdigit[4];
	XAXBnumtodigit(guess,guessdigit);
	XAXBnumtodigit(answer,answerdigit);
	int i,j;
	for(i=0;i<4;i++)
	{
		if(guessdigit[i]==answerdigit[i])
			AB[0]++;
	}
	for(i=0;i<=4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(guessdigit[i]==answerdigit[j])
				AB[1]++;
		}
	}
	AB[1]=AB[1]-AB[0];
}



void XAXBmain(userlist users,int user_id)
{
	system("cls");
	srand(time(NULL));//�ü� 
	int comguess,comans,userguess,userans,comAB[2],userAB[2],tmpAB[2],usercount=0,comcount=0;
	do{
		comans=rand()%10000;
	}while(XAXBislegal(comans)==false);
	
	do{
		cout<<"Please input your answer.";
		cin>>userans;
	}while(XAXBislegal(userans)==false);
	
	int pool[10000];
	int i;
	for(i=0;i<10000;i++)
	{
		if(XAXBislegal(i)==true)//==true�i�ٲ� 
			pool[i]=1;//�N��i��O���� 
		else
			pool[i]=0;//�N���i��O���� 
	}
	
	do{
		cout<<"Please input your guess.";
		cin>>userguess;
		while(XAXBislegal(userguess)==false)
		{
			cout<<"Please change your guess.";
			cin>>userguess;
		}
		XAXB(userguess,comans,userAB);
		usercount++;
		cout<<"("<<usercount<<")"<<"�A�q"<<userguess<<"    "<<userAB[0]<<"A"<<userAB[1]<<"B"<<endl;
		
		
		
		for(i=0;i<10000;i++)
		{
			if(pool[i]==1)
				break;
		}
		comguess=i;//�q���q���Ĥ@�ӼƦr 
		XAXB(comguess,userans,comAB);
		comcount++;
		cout<<"("<<comcount<<")"<<"�q���q"<<comguess<<"    "<<comAB[0]<<"A"<<comAB[1]<<"B"<<endl;
		for(i=0;i<10000;i++)
		{
			if(pool[i]==1)
			{
				XAXB(comguess,i,tmpAB);
				if(tmpAB[0]!=comAB[0] || tmpAB[1]!=comAB[1])
					pool[i]=0;
			} 
		}
	}while(userAB[0]!=4 && comAB[0]!=4);
	
	if(userAB[0]==4 && comAB[0]==4)
	{
		cout<<endl<<"����!"<<endl<<"���ߧA��o�x�Ȫ�10��~~~";
		users.member[user_id].money=users.member[user_id].money+10;
	}
		
	else if(comAB[0]==4)
	{
		cout<<endl<<"�q��Ĺ!"<<endl<<"�Q�ȿ��N���Ӥ@���a~~~";
		users.member[user_id].XAXBlose++;
	}
		
	else if(userAB[0]==4)
	{
		cout<<endl<<"�ϥΪ�Ĺ"<<endl<<"���ߧA��o�x�Ȫ�20��~~~"; 
		users.member[user_id].money=users.member[user_id].money+20;
		users.member[user_id].XAXBwin++;
	} 
		
	SaveUser(users); 
}



void Sudoku_main(userlist users,int user_id)
{
	int r,c,n,modified = 1;
	int Q[9][9];
	int A[9][9];
	int A2[9][9];
	int pool[9][9][10];
	Sudoku_init(pool);
	Sudoku_Read(1,Q,pool);
	for(r=0;r<9;r++)
		for(c=0;c<9;c++)
		{
			A[r][c] = Q[r][c];
			A2[r][c] = Q[r][c];
		}
	cout << endl;
	Sudoku_MainUI(Q,A2);
	while(modified==1)
	{
		modified = 0;
		for(r=0;r<9;r++)
		{
			for(c=0;c<9;c++)
			{
				if(A[r][c]==0)
				{
					n = Sudoku_Check(pool,r,c); //0-9
					if(n>0)
					{
						A[r][c] = n;
						Sudoku_update(pool,r,c,n);
						modified = 1;
					}
				}
			}
		}
	}
	
	int flag=0;
	for(r=0;r<9;r++)
	{
		for(c=0;c<9;c++)
		{
			if(A[r][c]!=A2[r][c])
			{	
				flag++;
			}
		}
	}
	if(flag==0)
	{
		cout<<"�A����F��!"<<endl<<"���ߧA��o�x�Ȫ�20��~~~";
		users.member[user_id].Sodokuwin++;
		users.member[user_id].money=users.member[user_id].money+20;
	}
		
	else
	{
		cout<<"�����F���P"<<endl;
		users.member[user_id].Sodokulose++;
	}
	SaveUser(users); 
}

void Sudoku_MainUI(int Q[][9],int A[][9])
{
	int r=0,c=0;
	char c1,c2;
	do
	{
		Sudoku_Print(Q,A,r,c);
		c1 = getch();
		if(c1==-32)
		{
			c2 = getch();
			switch(c2)
			{
				case 72:
					r = (r+8)%9;
					break;
				case 75:
					c = (c+8)%9;
					break;
				case 77:
					c = (c+1)%9;
					break;
				case 80:
					r = (r+1)%9; 
					break;
			}	
		}
		if(c1>='0'&&c1<='9')
		{
			if(Q[r][c]==0)
				A[r][c] = c1-'0';
		}
	}while(c1!=13);
}

void Sudoku_init(int p[][9][10])
{
	int r,c,n;
	for(r=0;r<9;r++)
		for(c=0;c<9;c++)
			for(n=1;n<=9;n++)
				p[r][c][n] = 1;
}

void Sudoku_update(int p[][9][10],int R,int C,int N)
{	
	//
	int r,c,n;
	// the same row
	for(c=0;c<9;c++) 
		p[R][c][N] = 0;
	// the same col
	for(r=0;r<9;r++)
		p[r][C][N] = 0;
	// the same block
	for(r=R/3*3;r<=R/3*3+2;r++)
		for(c=C/3*3;c<=C/3*3+2;c++)
			p[r][c][N] = 0;
	for(n=0;n<=9;n++)
		if(n!=N)
			p[R][C][n] = 0;
	p[R][C][N] = 1;
}

void Sudoku_Read(int Qno, int Q[][9], int p[][9][10])
{
	int r,c,n,m;
	ifstream fin;
	srand(time(NULL));
	m=rand()%3;
	if(m==0)
		fin.open("Q1.txt");
	else if(m==1)
		fin.open("Q2.txt");
	else if(m==2)
		fin.open("Q3.txt");
	for(r=0;r<9;r++)
	{
		for(c=0;c<9;c++)
		{
			fin >> n;
			Q[r][c] = n;
			if(n>0)
				Sudoku_update(p,r,c,n);
		}
	}
	fin.close();
}

void Sudoku_Print(int Q[][9],int A[][9],int R,int C)
{
	int r,c;
	system("cls");
	char left[9][9],right[9][9];
	for(r=0;r<9;r++)
		for(c=0;c<9;c++)
		{
			left[r][c] = ' ';
			right[r][c] = ' ';
		}
	if(Q[R][C]==0)
	{
		left[R][C] = '<';
		right[R][C] = '>';
	}
	else
	{
		left[R][C] = '[';
		right[R][C] = ']';
	}
	for(r=0;r<9;r++)
	{
		for(c=0;c<9;c++)
		{
			cout<<left[r][c];
			if(A[r][c]==0)
				cout << " ";
			else
				cout << A[r][c];
			cout <<right[r][c];
			if(c==2||c==5)
				cout <<"|";
		}
		cout << endl;
		if(r==2||r==5)
			cout << "----------------------------"<<endl;
	}
}

int Sudoku_Check(int p[][9][10],int R,int C)
{
	int sum=0,n,a,r,c;
	for(n=1;n<=9;n++)
	{
		int flag=1;
		for(r=R/3*3;r<=R/3*3+2;r++)
		{
			for(c=C/3*3;c<=C/3*3+2;c++)
			{
				if(r==R && c==C)
					continue;
				if(p[r][c][n]==1)
					flag=0;
			}
		}
			if(flag==1)
				return n;
	}
	
	for(n=1;n<=9;n++)
	{
		sum += p[R][C][n];
		if(p[R][C][n]==1)
			a = n;
	}
	if(sum==1)
		return a;
	else
		return 0;
}

userlist LoadUsers()
{
	int i;
	userlist users;
	fstream fin;
	fin.open("memberlist.txt");
	fin >> users.user_number;
	for(i=0;i<users.user_number;i++)
	{
		fin >> users.member[i].username;
		fin >> users.member[i].accountname;
		fin >> users.member[i].password;
		fin >> users.member[i].login_number;
		fin >> users.member[i].money;
	    fin >> users.member[i].XAXBwin;
	    fin >> users.member[i].XAXBlose;
	    fin >> users.member[i].Sodokuwin;
	    fin >> users.member[i].Sodokulose;
	}
	fin.close();
	return users;
}


orderlist LoadOrders()
{
	int i;
	orderlist orders;
	fstream fin;
	fin.open("orderlist.txt");
	fin >> orders.order_number;
	fin >> orders.order_now;
	for(i=0;i<orders.order_number;i++)
	{
		fin >> orders.member[i].buyer_id;
		fin >> orders.member[i].finish;
		fin >> orders.member[i].name;
		fin >> orders.member[i].ice;
		fin >> orders.member[i].sugar;
		fin >> orders.member[i].size;
		fin >> orders.member[i].price;
	}
	fin.close();
	return orders;
}

int Login(userlist users)
{
	char accountname[13];
	char password[13];
	int i;
	do{
		input_accountname(accountname);
		input_password(accountname,password);
		if(strcmp("Kebuke",accountname)==0 || strcmp("kebuke",accountname)==0)
		{
			if(strcmp("kebuke",password)==0)
				return -2;
			else
			{
				cout<<endl<<"Incorrect password"<<endl;
				cout<<"Press any key to continue......"<<endl;
				getch();
				return -3;
				break;
			}
		}
		for(i=0;i<users.user_number;i++)
		{
			if(strcmp(accountname,users.member[i].accountname)==0)
			{
				if(strcmp(password,users.member[i].password)==0)
					return i;
				else
				{
					cout<<endl<<"Incorrect password"<<endl;
					cout<<"Press any key to continue......"<<endl;
					getch();
					break;
				}
			}
		}
		if(i==users.user_number)
			return -1;
	}while(true);
	
}

void input_accountname(char un[])
{
	char c1,c2;
	int n=0,i;
	do
	{
		system("cls");
		cout << "Username: ";
		for(i=0;i<n;i++)
			cout << un[i];
		c1 = getch();
		if(c1==-32 || c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z') || (c1>='A'&&c1<='Z') || (c1>='0'&&c1<='9') || c1=='_')
		{
			if(n==12)
			{
				un[11] = c1;
			}
			else
			{
				un[n] = c1;
				n++;
			}
		}
		if(c1==8 && n>0)
			n--;
	}while(c1!=13 || n==0);
	un[n] = '\0';
}

void input_password(char un[],char pw[])
{
	char c1,c2;
	int n=0,i;
	do
	{
		system("cls");
		cout << "Username: ";
		cout << un << endl;
		cout << "Password: ";
		for(i=0;i<n;i++)
			cout << '*';
		c1 = getch();
		if(c1==-32 || c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z') || (c1>='A'&&c1<='Z') || (c1>='0'&&c1<='9') || c1=='_')
		{
			if(n==12)
			{
				pw[11] = c1;
			}
			else
			{
				pw[n] = c1;
				n++;
			}
		}
		if(c1==8&&n>0)
			n--;
	}while(c1!=13||n==0);
	pw[n] = '\0';
}


void input_username(char un[])
{
	char c1,c2;
	int n=0,i;
	do
	{
		system("cls");
		cout<<"�ݨӧA�٨S���U�L��!���ڭ̲{�b�N�ӵ��U�a!"<<endl;
		cout << "Your name: ";
		for(i=0;i<n;i++)
			cout << un[i];
		c1 = getch();
		if(c1==-32 || c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z') || (c1>='A'&&c1<='Z') || (c1>='0'&&c1<='9') || c1=='_')
		{
			if(n==12)
			{
				un[11] = c1;
			}
			else
			{
				un[n] = c1;
				n++;
			}
		}
		if(c1==8 && n>0)
			n--;
	}while(c1!=13 || n==0);
	un[n] = '\0';
}

void addaccount(char nun[],char nan[],char npw[],userlist users)
{
	system("cls");
	input_username(nun);
	input_accountname(nan);
	input_password(nan,npw);
	int i;
	i=users.user_number;
	strcpy(users.member[i].username,nun);
	strcpy(users.member[i].accountname,nan);
	strcpy(users.member[i].password,npw);
	users.member[i].login_number=0;
	users.member[i].money=100;
	users.member[i].XAXBwin=0;
	users.member[i].XAXBlose=0;
	users.member[i].Sodokuwin=0;
	users.member[i].Sodokulose=0;
	users.user_number++;
	SaveUser(users);
}

void SaveUser(userlist users)//�g�� 
{
	ofstream fout;
	fout.open("memberlist.txt");
	fout<<users.user_number<<endl;
	int i;
	for(i=0;i<users.user_number;i++)
	{
		fout << users.member[i].username<<endl;
		fout << users.member[i].accountname<<endl;
		fout << users.member[i].password<<endl;
		fout << users.member[i].login_number<<endl;
		fout << users.member[i].money<<endl;
	    fout << users.member[i].XAXBwin<<endl;
	    fout << users.member[i].XAXBlose<<endl;
	    fout << users.member[i].Sodokuwin<<endl;
	    fout << users.member[i].Sodokulose<<endl;	
	}
	fout.close();
}

void SaveOrder(orderlist orders)
{
	ofstream fout;
	fout.open("orderlist.txt");
	fout<<orders.order_number<<endl;
	fout<<orders.order_now<<endl;
	int i;
	for(i=0;i<orders.order_number;i++)
	{
		fout << orders.member[i].buyer_id <<endl;
		fout << orders.member[i].finish <<endl;
		fout << orders.member[i].name <<endl;
		fout << orders.member[i].ice <<endl;
		fout << orders.member[i].sugar <<endl;
		fout << orders.member[i].size <<endl;
		fout << orders.member[i].price <<endl;
	}
	fout.close();
}


void MainScreen(int select,userlist users,int j)
{
	system("cls");
	int i;
	char L[7],R[7];
	for(i=0;i<7;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[select] = '[';
	R[select] = ']';
	cout << endl<< endl<< endl<< endl<< endl<<endl;
	cout<<"								 __         ___.          __             " <<endl; 
	cout<<" 								|  | __ ____\\_ |__  __ __|  | __ ____  	 " <<endl; 
	cout<<"							 	|  |/ // __ \\| __ \\|  |  \\  |/ // __ \\    " <<endl; 
	cout<<"							 	|    <\\  ___/| \\_\\ \\  |  /    <\\  __/    " <<endl; 
	cout<<"							 	|__|__\\\\____ >____ /____/|__|__\\\\____ >   " <<endl; 
	cout<<"							 ____________________________________________________                                               " <<endl; 
	cout<<"							 ____________________________________________________                                      			"<<endl<<endl<<endl<<endl;
	users = LoadUsers();
	cout<<"                                                        "<<users.member[j].username<<"�A�n�A�w��Ө�i���i��!�A�w�n�J�t�� "<<users.member[j].login_number<<" ��"<<endl<<endl<<"                                                        "<<"�A�{�b�� "<<users.member[j].money<<" ���@~~~"<<endl<<endl;
	cout <<"                                                        "<< L[1] << "1" << R[1] << " Order" << endl;
	cout <<"                                                        "<< L[2] << "2" << R[2] << " �d�q��" << endl;
	cout <<"                                                        "<< L[3] << "3" << R[3] << " �ק�|�����" << endl;
	cout <<"                                                        "<< L[4] << "4" << R[4] << " ��ѫ�" << endl;
	cout <<"                                                        "<< L[5] << "5" << R[5] << " �ƿW�C��" << endl;
	cout <<"                                                        "<< L[6] << "6" << R[6] << " XAXB" << endl;
	cout <<"                                                        "<< L[0] << "7" << R[0] << " ���}�t��" << endl;
}



int MainUI(int select,userlist users,int j)
{ 
	char x,x1;
	do{
		MainScreen(select,users,j);
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==72)  //�W 
				select = (select + 6)%7;
			if(x1==80)  //�U 
				select = (select + 1)%7;
			if(x1==77)  //�k 
				x=13;  //enter
		}
		if(x>='0' && x<='6')
			select = x - '0';
	}while(x!=13);
	return select;
}


void OrderAScreen(int choice)//�~�� 
{
	system("cls");
	char L[16],R[16];
	int i;
	for(i=0;i<16;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[choice]='[';
	R[choice]=']';
	cout<<"�~���G "<<endl;
	cout <<"             "<< L[1] << "1" << R[1] << " ��������" << "         30��"<<endl;
	cout <<"             "<< L[2] << "2" << R[2] << " �R�K����" << "         30��"<<endl;
	cout <<"             "<< L[3] << "3" << R[3] << " �Ӧm����" << "         30��"<<endl;
	cout <<"             "<< L[4] << "4" << R[4] << " ���ì���" << "         30��"<<endl;
	cout <<"             "<< L[5] << "5" << R[5] << " �����N�S" << "         30��"<<endl;
	cout <<"             "<< L[6] << "6" << R[6] << " ����N�S" << "         30��"<<endl;
	cout <<"             "<< L[7] << "7" << R[7] << " �K�ާN�S" << "         30��"<<endl;
	cout <<"             "<< L[8] << "8" << R[8] << " �K�޺��" << "         30��"<<endl;
	cout <<"             "<< L[9] << "9" << R[9] << " �K���B��" << "         30��"<<endl;
	cout <<"             "<< L[10] << "10" << R[10] << " �N�S����" << "         40��"<<endl;
	cout <<"             "<< L[11] << "11" << R[11] << " ��������" << "         40��"<<endl;
	cout <<"             "<< L[12] << "12" << R[12] << " �եɼ���" << "         40��"<<endl;
	cout <<"             "<< L[13] << "13" << R[13] << " ���ɼ���" << "         40��"<<endl;
	cout <<"             "<< L[14] << "14" << R[14] << " ���ɼگS" << "         40��"<<endl;
	cout <<"             "<< L[15] << "15" << R[15] << " �گ׬���" << "         40��"<<endl;
	cout <<"             "<< L[0] << "16" << R[0] << " �گצh�h" << "         40��"<<endl;
}

int OrderAUI(int choice)//�~�� 
{
	char oc,oc1;
	do
	{
		OrderAScreen(choice);
		oc = getch();
		if(oc==-32)
		{
			oc1 = getch();
			if(oc1==72)
				choice = (choice+15)%16;
			if(oc1==80)
				choice = (choice+1)%16;
			if(oc1==77)
				oc=13;
		}
		if(oc>='0' && oc<='15')     
			choice = oc - '0';
	}while(oc!=13);
	return choice;
}

void OrderBScreen(int choice)//�B�� 
{
	system("cls");
	char L[3],R[3];
	int i;
	for(i=0;i<3;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[choice]='[';
	R[choice]=']';
	cout<<"�B���G "<<endl;
	cout <<"             "<< L[1] << "1" << R[1] << " �h�B " << endl;
	cout <<"             "<< L[2] << "2" << R[2] << " �L�B " << endl;
	cout <<"             "<< L[0] << "3" << R[0] << " �֦B " << endl;
}

int OrderBUI(int choice)//�B�� 
{
	char oc,oc1;
	do
	{
		OrderBScreen(choice);
		oc = getch();
		if(oc==-32)
		{
			oc1 = getch();
			if(oc1==72)
				choice = (choice+2)%3;
			if(oc1==80)
				choice = (choice+1)%3;
			if(oc1==77)
				oc=13;
		}
		if(oc>='0' && oc<='2')
			choice = oc - '0';
	}while(oc!=13);
	return choice;
} 
void OrderCScreen(int choice)//���� 
{
	system("cls");
	char L[4],R[4];
	int i;
	for(i=0;i<4;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[choice]='[';
	R[choice]=']';
	cout<<"���סG "<<endl;
	cout <<"             "<< L[1] << "1" << R[1] << " �L�} " << endl;
	cout <<"             "<< L[2] << "2" << R[2] << " �L�} " << endl;
	cout <<"             "<< L[3] << "3" << R[3] << " �b�} " << endl;
	cout <<"             "<< L[0] << "4" << R[0] << " ���} " << endl;
}
int OrderCUI(int choice)//���� 
{
	char oc,oc1;
	do
	{
		OrderCScreen(choice);
		oc = getch();
		if(oc==-32)
		{
			oc1 = getch();
			if(oc1==72)
				choice = (choice+3)%4;
			if(oc1==80)
				choice = (choice+1)%4;
			if(oc1==77)
				oc=13;
		}
		if(oc>='0' && oc<='3')
			choice = oc - '0';
	}while(oc!=13);
	return choice;
}

void OrderDScreen(int choice)//�ؤo
{
	system("cls");
	char L[3],R[3];
	int i;
	for(i=0;i<3;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[choice]='[';
	R[choice]=']';
	cout<<"�ؤo�G "<<endl;
	cout <<"             "<< L[1] << "1" << R[1] << " �p�M " << endl;
	cout <<"             "<< L[2] << "2" << R[2] << " ���M " << "+10��"<< endl;
	cout <<"             "<< L[0] << "3" << R[0] << " �j�M " << "+20��"<< endl;
} 
int OrderDUI(int choice)
{
	char oc,oc1;
	do
	{
		OrderDScreen(choice);
		oc = getch();
		if(oc==-32)
		{
			oc1 = getch();
			if(oc1==72)
				choice = (choice+2)%3;
			if(oc1==80)
				choice = (choice+1)%3;
			if(oc1==77)
				oc=13;
		}
		if(oc>='0' && oc<='2')
			choice = oc - '0';
	}while(oc!=13);
	return choice;
}

void OrderMain(userlist users,int user_id,orderlist orders,int order_id)
{
	int choice=1;
	orders.member[order_id].name=OrderAUI(choice);
	choice=1;
	orders.member[order_id].ice=OrderBUI(choice);
	choice=1;
	orders.member[order_id].sugar=OrderCUI(choice);
	choice=1;
	orders.member[order_id].size=OrderDUI(choice);
	orders.member[order_id].buyer_id=user_id;
	orders.member[order_id].finish=0;
	
	int total=0;
	
	switch(orders.member[order_id].name)
	{
		case 1:
			total=30;
			break;
		case 2:
			total=30;
			break;
		case 3:
			total=30;
			break;
		case 4:
			total=30;
			break;
		case 5:
			total=30;
			break;
		case 6:
			total=30;
			break;
		case 7:
			total=30;
			break;
		case 8:
			total=30;
			break;
		case 9:
			total=30;
			break;
		case 10:
			total=40;
			break;
		case 11:
			total=40;
			break;
		case 12:
			total=40;
			break;
		case 13:
			total=40;
			break;
		case 14:
			total=40;
			break;
		case 15:
			total=40;
			break;
		case 0:
			total=40;
			break;
	}
	switch(orders.member[order_id].size)
	{
		case 2:
			total=total+10;
			break;
		case 0:
			total=total+20;
			break;
	}
	
	orders.member[order_id].price=total;
	
	if(users.member[user_id].money>=total)
	{
		users.member[user_id].money=users.member[user_id].money-total; 
		SaveOrder(orders);
		SaveUser(users);
		system("cls");
		cout <<"�q�槹��         ��O���B�� "<<orders.member[order_id].price<<" ��"<<endl<<"�A�ٳ� "<<users.member[user_id].money<<" ���@~~~"<<endl;  
	}
	else
	{
		int lack;
		lack=total-users.member[user_id].money;
		system("cls");
		cout<<"�A���x�Ȫ��l�B���� "<<lack<<" ���A�h���C���ȿ��άO�x�Ȱ�!"<<endl; 
	}	
	cout << "Press any key to continue~~";
	
} 

void CheckOrder(orderlist orders,int user_id)
{
	system("cls");
	int i;
	for(i=0;i<orders.order_number;i++)
	{
		if(orders.member[i].buyer_id==user_id)
		{
			switch(orders.member[i].name)
			{
				case 1:
					cout<<"��������"<<endl;
					break;
				case 2:
					cout<<"�R�K����"<<endl;
					break;
				case 3:
					cout<<"�Ӧm����"<<endl;
					break;
				case 4:
					cout<<"���ì���"<<endl;
					break;
				case 5:
					cout<<"�����N�S"<<endl;
					break;
				case 6:
					cout<<"����N�S"<<endl;
					break;
				case 7:
					cout<<"�K�ާN�S"<<endl;
					break;
				case 8:
					cout<<"�K�޺��"<<endl;
					break;
				case 9:
					cout<<"�K���B��"<<endl;
					break;
				case 10:
					cout<<"�N�S����"<<endl;
					break;
				case 11:
					cout<<"��������"<<endl;
					break;
				case 12:
					cout<<"�եɼ���"<<endl;
					break;
				case 13:
					cout<<"���ɼ���"<<endl;
					break;
				case 14:
					cout<<"���ɼگS"<<endl;
					break;
				case 15:
					cout<<"�گ׬���"<<endl;
					break;
				case 0:
					cout<<"�گצh�h"<<endl;
					break;
			}
			switch(orders.member[i].ice)
			{
				case 1:
					cout<<"�h�B"<<endl;
					break;
				case 2:
					cout<<"�L�B"<<endl;
					break;
				case 0:
					cout<<"�֦B"<<endl;
					break;	
			}
			switch(orders.member[i].sugar)
			{
				case 1:
					cout<<"�L�}"<<endl;
					break;
				case 2:
					cout<<"�L�}"<<endl;
					break;
				case 3:
					cout<<"�b�}"<<endl;
					break;
				case 0:
					cout<<"���}"<<endl;
					break;
			}
			switch(orders.member[i].size)
			{
				case 1:
					cout<<"�p�M"<<endl;
					break;
				case 2:
					cout<<"���M"<<endl;
					break;
				case 0:
					cout<<"�j�M"<<endl;
					break;
			}
			if(orders.member[i].finish==0)
				cout<<"�|�����"<<endl;
			else if(orders.member[i].finish==1)
				cout<<"�w���"<<endl; 
			cout<< "���B�G "<<orders.member[i].price<<endl<<endl;
		}
	}
	cout << "Press any key to continue";
}


void Chatroom(userlist users,int user_id)
{
	ifstream fin;
	ofstream fout;
	char buffer[100];
	char input[100];
	do
	{
		system("cls");
		fin.open("msg.txt");
		while(fin.getline(buffer,99))
		{
			cout << buffer << endl;
		}
		fin.close();
		cout << "Please input your words:";
		cin.getline(input,99);
		if(strcmp(input,"Exit")!=0 && strcmp(input,"exit")==0)
			break;
		fout.open("msg.txt",ios::app);
		fout << users.member[user_id].accountname<<" :" << input << endl;
		fout.close();
	}while(strcmp(input,"Exit")!=0 && strcmp(input,"exit")!=0);
	cout<<endl<<endl<< "Press any key to continue~~";
}






void ChangeAccount(userlist users,int user_id)
{
	char c1,c2,c3,c4,c5,c6;
	char pw[13],npw[13],nnpw[13];
	int n=0,i;
	do
	{
		system("cls");
		cout<<"�A�n��|����Ʈ@~~~~  ���A�n����J�쥻�K�X�@! "<<endl<<endl; 
		cout << "Password: ";
		for(i=0;i<n;i++)
			cout << '*';
		c1 = getch();
		if(c1==-32 || c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z') || (c1>='A'&&c1<='Z') || (c1>='0'&&c1<='9') || c1=='_')
		{
			if(n==12)
			{
				pw[11] = c1;
			}
			else
			{
				pw[n] = c1;
				n++;
			}
		}
		if(c1==8&&n>0)
			n--;
	}while(c1!=13||n==0);
	pw[n] = '\0';
	
	if(strcmp(pw,users.member[user_id].password)==0)
	{
		n=0;
		do
		{
			system("cls");
			cout<<"�ЧA��J�s�K�X! "<<endl<<endl; 
			cout << "Password: ";
			for(i=0;i<n;i++)
				cout << '*';
			c3 = getch();
			if(c3==-32 || c3==0)
				c4 = getch();
			if((c3>='a'&&c3<='z') || (c3>='A'&&c3<='Z') || (c3>='0'&&c3<='9') || c3=='_')
			{
				if(n==12)
				{
					npw[11] = c3;
				}
				else
				{
					npw[n] = c3;
					n++;
				}
			}
			if(c3==8&&n>0)
				n--;
		}while(c3!=13||n==0);
		npw[n] = '\0';
		
		n=0;
		do
		{
			system("cls");
			cout<<"�ЧA�A��J�@���s�K�X! "<<endl<<endl; 
			cout << "Password: ";
			for(i=0;i<n;i++)
				cout << '*';
			c5 = getch();
			if(c5==-32 || c5==0)
				c6 = getch();
			if((c5>='a'&&c5<='z') || (c5>='A'&&c5<='Z') || (c5>='0'&&c5<='9') || c5=='_')
			{
				if(n==12)
				{
					nnpw[11] = c5;
				}
				else
				{
					nnpw[n] = c5;
					n++;
				}
			}
			if(c5==8&&n>0)
				n--;
		}while(c5!=13||n==0);
		nnpw[n] = '\0';
		
		if(strcmp(npw,nnpw)==0)
		{
			cout<<endl<<"�K�X�w��s����"<<endl;
			strcpy(users.member[user_id].password,npw);
			SaveUser(users);
		}
		else
		{
			cout<<"�A���o���@���� ���Ӱ�!"<<endl; 
		}
	}
	
	else
		cout<<"�A�骺�K�X������ ���Ӱ�!"<<endl;
	
	cout << "Press any key to continue";
}
