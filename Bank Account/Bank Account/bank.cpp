#include <iostream>
#include<string>
#include<fstream>
#include<windows.h>
#include<sstream>
using namespace std;

class Account {
private:
	string AccountNo, Password;
	int Balance;
public:
	Account() {
		AccountNo = "";
		Password = "";
		Balance = 0;
	}

	void setaccountno(string id) {
		AccountNo = id;
	}
	void setPW(string pw) {
		Password = pw;
	}
	void setbalance(int bal) {
		Balance = bal;
	}

	string getaccountno() {
		return AccountNo;
	}
	string getPW() {
		return Password;
	}
	int getbal() {
		return Balance;
	}
};


void openAccount(Account user) {
	system("cls");
	string ID, pw;
	cout << " Enter Account Number: " << endl;
	cin >> ID;
	user.setaccountno(ID);
	cout << " Enter a Strong Password: " << endl;
	cin >> pw;
	user.setPW(pw);

	user.setbalance(0);

	ofstream outfile("C:\Account.txt", ios::app);
	if (!outfile) {
		cout << " Error! File Can't Open: " << endl;
	}
	else {
		outfile << " " << user.getaccountno() << " : " << user.getPW() << " : " << user.getbal() << endl << endl;
		cout << " Account Created Successfully! " << endl;
	}
	outfile.close();
	Sleep(5000);
}

void addCash() {
	system("cls");
	string id;
	cout << " Enter Account No: " << endl;
	cin >> id;
	ifstream infile("C:\Account.txt");
	ofstream outfile("C:\Account temp.txt");
	if (!infile || !outfile) {
		cout << " Error! File Not Found: " << endl;
	}
	
	string line;
	bool found = false;
	while (getline(infile, line)) {
		stringstream ss;
		ss << line;
		string userID, userpw;
		int userbal;
		char delimiter;
		ss >> userID >> delimiter >> userpw >> delimiter >> userbal;
		if (id == userID) {
			found = true;
			int cash;
			cout << " Enter Cash: " << endl;
			cin >> cash;

			int newbal = userbal + cash;
			userbal = newbal;
			outfile << " " << userID << " : " << userpw << " : " << userbal << endl << endl;
			cout << " New Balance Is: " << userbal << endl;
		}
		else {
			outfile << line << endl;
		}

	}
	if (!found) {
		cout << " Enter Valid Account No! " << endl;

	}
	outfile.close();
	infile.close();
	remove("C:\Account.txt");
	rename("C:\Account temp.txt", "C:\Account.txt");
	Sleep(5000);
}


void withdraw(Account user) {
	system("cls");
	string id, pw;
	cout << " Enter Account No: " << endl;
	cin >> id;

	cout << " Enter Password: " << endl;
	cin >> pw;

	ifstream infile("C:\Account.txt");
	ofstream outfile("C:\Account temp.txt");
	if (!infile || !outfile) {
		cout << " Error! File Not Found: " << endl;
	}
	string line;
	bool found = false;

	while (getline(infile, line)) {
		stringstream ss;
		ss << line;

		string UserID, userpw;
		int userbalance;
		char delimiter;

		ss >> UserID >> delimiter >> userpw >> delimiter >> userbalance;

		if (id == UserID && pw == userpw) {
			found = true;
			int cash;
			cout << " Enter Cash! " << endl;
			cin >> cash;
			if (cash <= userbalance) {
				int newbal = userbalance - cash;
				userbalance = newbal;
				outfile << " " << UserID << " : " << userpw << " : " << userbalance << endl << endl;
				cout << " Transaction Successfull: "<< endl;
				cout << " Remaining Balance Is: " << userbalance << endl;
			}
			else {
				cout << " Low Balance! " << endl;
				outfile << " " << UserID << " : " << userpw << " : " << userbalance << endl << endl;
			}
		}
		else {
			outfile << line << endl;
		}
	}
	if (!found) {
		cout << " Invalid Account No or Password! " << endl;
	}
	outfile.close();
	infile.close();
	remove("C:\Account.txt");
	rename("C:\Account temp.txt", "C:\Account.txt");
	Sleep(5000);
}
int main() {
	Account user;
	bool exit = false;

	while (!exit) {
		system("cls");

		int val;
		cout << " Welcome To Bank Account Management: " << endl;
		cout << " *********************************** " << endl;
		cout << " 1.Open New Account: " << endl;
		cout << " 2.Add Cash: " << endl;
		cout << " 3.Withdraw Cash: " << endl;
		cout << " 4.Exit! " << endl;
		cout << " Enter Your Choice: " ;
		cin >> val;
		
		if (val == 1) {
			openAccount(user);
		}
		else if (val == 2) {
			addCash();
		}
		else if (val == 3) {
			withdraw(user);
		}
		else if (val == 4) {
			system("cls");
			exit = true;
			cout << " Exiting the Program...." << endl;
			Sleep(3000);
		}
		Sleep(3000);
	}
	return 0;
}