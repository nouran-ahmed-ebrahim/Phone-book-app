#include <iostream>
#include <string>
#include <fstream>
#define ll long long
using namespace std;


//structures
struct date
{
	int day ,month ,year;
};

struct number
{
	string numb, type;
	float balance;
	date start, renew;
};

struct information
{
	int id, password , nNum;
	string name,email ,addres;
	number numbers[3];
} info[4];

//variables

  //Serial num
ll SNum[40];
   //package type
string PacType[3] = { "connect","control","kiks" };
  //user data
information MyData;
int my_data_ind;

//functions

void read_data();
void read_SN();
bool search( string email, int pass);
int findNumber();
bool check_balacne(float min,int ind);
void make_call ();
void send_messege ();
void recharge();
void request(int ind);
void change_type(int ind);
void renew();
void transfer ();

int main()
{
	read_data();
	read_SN();

	int pass , OpNum  ;
	string email , op;
    bool in = 0, end = 0;

	cout << "#####################################################################################################################\n";
	cout << "################# \t\t\t Welcome in telcome App  \t\t\t\t\t#############\n\n";
	
	//validate email and password
	while (true)
	{
		cout << "Please, Enter your Email : ";
		cin >> email;
		cout << "Please, Enter your password : ";
		cin >> pass;
		if (!search(email ,pass))
		{
			cout << "invalid password or email \n\n";
		}
		else
			break;
	}

	cout << "\n\t\t\tWelcome  " << MyData.name<<"\n\n";

	while (true)
	{
		cout << "Operations : \n";
	    cout << "1.renew      2.call      3.SMS     4.recharge    5.transfer_balance \n\n";
	    cout << "Enter operation number :";
	    cin >> OpNum;
		
		switch (OpNum)
		{
		  case 1 :
			   
			  renew();
			  break;

		  case 2 :
			  make_call();
			  break;

		  case 3 :
			  send_messege();
			  break;

		  case 4 :
			  recharge();

			  break;

		  case 5 :
			  transfer();
			  break;

		  default:
			  cout << "Invalid option !! \n";
			   break;
		}

		do
		{
			bool  in = 0;
			cout << "DO you anther operation (yes/no) : ";
			cin >> op;
			if (op == "yes" || op == "Yes")
			{
				cout << "\n";
				break;
			}
			else if (op == "no" || op == "No")
			{
				cout << "End ... \n";
				end = 1;
				break;
			}
			else
			{
				cout << "Invalid !! \n";
			}
		} while (!in);

		if (end)
			break;
	}
	system("pause");
	return 0;

}



// read users data from file

void read_data()
{
	ifstream myfile("Data.txt");

	int i = 0;
	while (myfile >> info[i].id)
	{
		myfile >> info[i].password;
		myfile >> info[i].addres;
		myfile >> info[i].email;
		myfile >> info[i].nNum;

		//read all numbers data

		for (int j = 0; j < info[i].nNum; j++)
		{
			myfile >> info[i].numbers[j].numb;
			myfile >> info[i].numbers[j].type;
			myfile >> info[i].numbers[j].balance;
			myfile >> info[i].numbers[j].start.day;
			myfile >> info[i].numbers[j].start.month;
			myfile >> info[i].numbers[j].start.year;
			myfile >> info[i].numbers[j].renew.day;
			myfile >> info[i].numbers[j].renew.month;
			myfile >> info[i].numbers[j].renew.year;

		}
		myfile >> info[i].name;
		i++;
	}
}


//read serial number
void read_SN()
{
	ifstream file("SNumber.txt");

	int i = 0;
	while (file >> SNum[i])
	{
		i++;
	}
}

//find user's data
bool search(string email ,int pass )
{
	for (int i = 0; i < 4; i++)
	{
		if (info[i].email == email && info[i].password == pass)
		{
			MyData = info[i];
			my_data_ind = i;
			return 1;
		}
	}

	return 0;
}

  //find the number
int findNumber()
{
	string num;
	if (MyData.nNum == 1)
	{
		return 0;
	}
	else
	{
		cout << "Enter your number : ";
		cin >> num;
		for (int i = 0; i < MyData.nNum; i++)
		{
			if (num == MyData.numbers[i].numb)
			{
				return i;
			}
		}

		cout << "invalid number !! \n\n";
		return 5;
	}

}

//check that balance is enough 
bool check_balacne(float min,int ind)
{
	if (MyData.numbers[ind].balance >= min)
		return 1;

	cout << "your balance is not enough..\n\n";
	return 0;
}


//renew request
void request(int ind)
{ 

	if (ind == 5)
	{
		cout << "request failed...\n\n";
	}
	else
	{	
		if (MyData.numbers[ind].type==PacType[0])
		{
			if (check_balacne(30,ind))
			{
				MyData.numbers[ind].balance -= 30;
				cout << "\nDone..\n\n";
			}
		}
		else if (MyData.numbers[ind].type == PacType[1])
		{
			if (check_balacne(15,ind))
			{
				MyData.numbers[ind].balance -= 15;
				cout << "\nDone..\n\n";
			}
		}
		else if (MyData.numbers[ind].type == PacType[2])
		{
			if (check_balacne(10,ind))
			{
				MyData.numbers[ind].balance -= 10;
				cout << "\nDone..\n\n";
			}
		}
	}
}


void change_type(int ind)
{
	if (ind == 5)
	{
		cout << "Failed ......\n";
	}
	else
	{
		string type;
		cout << "Choose the new type : (";
		for (int i = 0; i < 3; i++)
		{
			if (PacType[i] != MyData.numbers[ind].type)
			{
				cout << PacType[i] << " ";
				if (i < 2)
					cout << "or ";
			}
			
		}
		cout << ")\nThe new type : ";
		cin >> type;

		MyData.numbers[ind].type = type;
		request(ind);
	}
}

void renew()
{
	int reqNum;
	cout << "\n1.renew       2.change type and renew\n";
	cout << "Enter request number : ";
	cin >> reqNum;

	switch (reqNum)
	{
	case 1:
		request(findNumber());
		break;

	case 2:
		change_type(findNumber());
		break;

	default:
		break;
	}
}


void make_call()
{
	bool nfound=0;
	string num;
	   
	 cout << "Enter the number you want to call :";
	cin >> num;
	if (MyData.nNum == 1)
	{   
		if (check_balacne(0.25,0))
		{
			MyData.numbers[0].balance -= 0.25;
			cout << "Calling...\n\n";
		}
	
	}
	else
	{
		cout << "Enter your number : ";
		cin >> num;
		for (int i = 0; i < MyData.nNum; i++)
		{
			if (num == MyData.numbers[i].numb)
			{ 
				nfound = 1;
				if (check_balacne(0.25,i))
				{
					
					MyData.numbers[i].balance -= 0.25;
					cout << "Calling...\n\n";
				}
			}	
		}
		if (!nfound)
			cout << "invalid number \n";
	}
}


void send_messege()
{
	ll number;
	bool nfound = 0;
	string num,messege;
	
	cout << "Enter your messege : ";
	cin>> messege;

	cout << "Enter the number you want to send him the SMS :";
	cin >> number;

	if (MyData.nNum == 1)
	{
		if (check_balacne(0.25,0))
		{
			MyData.numbers[0].balance -= 0.25;
			cout << "send...\n\n";
		}
	}
	else
	{
		cout << "Enter your number : ";
		cin >> num;
		for (int i = 0; i < MyData.nNum; i++)
		{
			if (num == MyData.numbers[i].numb)
			{
				nfound = 1;
				if (check_balacne(0.25,i))
				{
					
					MyData.numbers[i].balance -= 0.25;
					cout << "send...\n\n";

				}
			}	
		}
		if (!nfound)
				cout << "invalid number \n";
	}
	
}

void recharge()
{
	int SN ,value ;
	bool found=0 ,nfound=0;
	string num;
	
	
	cout << "Enter serial number :";
	cin >> SN;
	
	for (int i = 0; i < 40; i++)
	{
		if (SN == SNum[i] && SNum[i] !=0)
		{
			found = 1;
			if (i > 30)
			{
				value = 100;
				SNum[i] = 0;
			}
			else if (i > 20)
			{
				value = 50;
				SNum[i] = 0;
			}
			else if (i > 10)
			{
				value = 10;
				SNum[i] = 0;
			}
			else
			{
				value = 5;
				SNum[i] = 0;
			}
			break;
		}
	}
	if (!found)
	{
		cout << "invalid serial  number \n";
	}
	else
	{
		if (MyData.nNum == 1)
		{
			MyData.numbers[0].balance+=value;
			cout << "Done..your balance now is  " << MyData.numbers[0].balance << "\n\n";
		}
		else
		{
			cout << "Enter your number : ";
			cin >> num;
			for (int i = 0; i < MyData.nNum; i++)
			{
				if (num == MyData.numbers[i].numb)
				{
					nfound = 1;
					MyData.numbers[i].balance += value;
					
					cout << "Done..your balance now is  "<< MyData.numbers[i].balance<<"\n\n";
				}
			}
			if (!nfound)
				cout << "invalid number \n";
		}
	}
}


void transfer()
{
	int ind = findNumber();
	if (ind == 5)
	{
		cout << "Failed ......\n";
	}
	else
	{
		bool found = 0;
		int money;
		string num;
		cout << "Enter the amount of money : ";
		cin >> money;
		cout << "Enter the number you want to send him money : ";
		cin >> num;

		if (check_balacne(money,ind))
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < info[i].nNum; j++)
				{
					if (info[i].numbers[j].numb == num)
					{
						found = 1;
						info[i].numbers[j].balance += money;
						MyData.numbers[ind].balance -= money;
						if (i == my_data_ind)
						{
							MyData.numbers[j].balance += money;
						}
						cout <<"done...\n\n";
						break;
					}
				}
			}
			if (!found)
				cout << "invalid number\n";
	    }
	}
}