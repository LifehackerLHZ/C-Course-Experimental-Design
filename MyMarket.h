#ifndef _MY_MARKET_H
#define _MY_MARKET_H

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include<vector>
#include<cstring>
#define UsrNameBuffSize 32
#define ProdNameBuffSize 128
#define PwdBuffSize 16
#define AddressBuffSize	256
#define NumOfProductAttrib 8
#define NumOfCustomerAttrib 6
#define NumOfAccountAttrib 5
#define NumOfMerchantAttrib 6
#define NumOfOrderAttrib 12
using namespace std;
enum UserType
{
	ADMIN,
	MERCHANT,
	CUSTOMER,
};

enum Sex
{
	male, female,
};

struct Date {
	int month;
	int year;
	int day;
};

struct Time {
	Date date;
	int minute;
	int hour;
	int second;
};

struct Customer {
	int id;
	char name[UsrNameBuffSize];
	Sex sex;
	Date birthday;
	char address[AddressBuffSize];
	unsigned long long phone;
};

struct Merchant {
	int id;
	char name[UsrNameBuffSize];
	unsigned long long phone;
	double totalSales;
	int	nRatings;
	float rating;
};

struct Product
{
	int ProductID;
	int AccountID;
	char name[ProdNameBuffSize];
	float price;
	int stock;
	float rating;
	int nRatings;
	int nSales;
};

struct Account {
	int id;
	char LoginName[UsrNameBuffSize];
	char password[PwdBuffSize];
	UserType type;
	double money;
};

struct Order {
	int orderid;
	int buyerid;
	int productid;
	char productname[2048];
	int storeid;
	char receivername[2048];
	unsigned long long number;
	double price;
	Time time;
	unsigned long long phone;
	char address[AddressBuffSize];
	bool stiuation;
};

struct FieldPrintSetting
{
	char PrintFieldName[16]; // 需要打印的字段名
	int PrintWidth; // 打印的字段宽度
};

int ParseString(const char* str, char* word[], const char delim = ',');
void StringToDate(const char* str, Date& date);
void StringToTime(const char* str, Time& time);
unsigned long long 	StringToPhone(const char* str);

typedef std::vector<Customer> CustomerArray;
typedef std::vector<Merchant> MerchantArray;
typedef std::vector<Product> ProductArray;
typedef std::vector<Account> AccountArray;
typedef std::vector<Order> OrderArray;

extern bool LoadCustomerList(CustomerArray& CustomerList);
extern bool SaveCustomerList(const CustomerArray& CustomerList);
extern bool AddCustomer(const Customer& customer);
extern bool DeleteCustomer(int ID);
extern bool GetCustomerAddress(int ID,char* name, char* adress, long &phone);

extern bool LoadMerchantList(MerchantArray& MerchantList);
extern bool SaveMerchantList(const MerchantArray& MerchantList);
extern bool AddMerchant(const Merchant& merchant);
extern bool DeleteMerchant(int ID);
extern bool UpdateMerchantSales(int ID,double Salechange);

extern bool LoadProductList(ProductArray& ProductList);
extern bool SaveProductList(ProductArray& ProductList);
extern bool AddProductList(const ProductArray& ProductList);
extern int AddProductList(int ID,const char *name,double price,int stock);

extern void PrintTableHead(FieldPrintSetting PrintSet[], int nFields);
extern void PrintLine(FieldPrintSetting PrintSet[], int nFields);
extern void PrintProducts(ProductArray &products);
extern void PrintRemaining(FieldPrintSetting PrintSet[], int nFields, string strs[]);
extern char* TrimString(const char* src, char* dst, int width, string& remaining);

bool LoadMerchantList(MerchantArray& MerchantList);
bool LoadCustomerList(CustomerArray& CustomerList);
bool LoadAccountList(AccountArray& AccountList);
bool LoadOrderList(OrderArray& OrderList);

#endif // _MY_MARKET_H


/*#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include <string.h>
using namespace std;
int n;
int tem;
struct P {
	char s[40];
	int score;
	int num;
	P() {
		score = 0; num = 0;
	}
};
void build(P* w, char q[])
{
	bool t = 0;
	for (int i = 1; i <= tem; i++)
	{
		//cout << "i=" << i << endl;
		//cout << (w + i)->s << "   " << "Q[]=" << q << endl;
		if (!strcmp((w+i)->s, q))
			t = 1;
	}
	if(t==0)
	{
		tem++;
		strcpy((w+tem)->s, q);
	}

}
void find(P *w, char q[])
{
	for (int i = 1; i <= tem; i++)
	{
		if (!strcmp((w+i)->s, q))
			(w+i)->score++;
	}
}
void add(P* w, char q[], int nn)
{
	for (int i = 1; i <= n; i++)
	{
		if (!strcmp((w+i)->s, q))
			(w+i)->num += nn;
	}
}
int main()
{
	while(scanf(" %d", &n) != EOF)
	{
		P s[11];
		tem = 0;
		int temm = n * (n - 1) / 2;
		for (int i = 1; i <= temm; i++)
		{
			char w;
			P s1, s2;
			w = getchar();
			cin.getline(s1.s, 20, ':');
			//w = getchar();
			cin.getline(s2.s, 20, ' ');
			//w = getchar();
			cin >> s1.score;
			w = getchar();
			cin >> s2.score;
			//cout << s1.s << endl;
			//cout << s1.s << " " << s2.s << " " << s1.score << " " << s2.score << endl;
			build(s, s1.s);
			build(s, s2.s);
			if (s1.score > s2.score)
				find(s, s1.s), find(s, s1.s), find(s, s1.s),add(s, s1.s, s1.score - s2.score);
			else if (s1.score == s2.score)
				find(s, s1.s), find(s, s2.s);
			else
				find(s, s2.s), find(s, s2.s), find(s, s2.s),add(s, s2.s, s2.score - s1.score);
		}
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
			{
				if (s[i].score < s[j].score)
				{
					P t;
					t = s[i];
					s[i] = s[j];
					s[j] = t;
				}
				else if (s[i].score == s[j].score)
				{
					if (s[i].num < s[j].num)
					{
						P t;
						t = s[i];
						s[i] = s[j];
						s[j] = t;
					}
					else if (s[i].num == s[j].num)
					{
						if (strcmp(s[i].s, s[j].s) > 0)
						{
							P t;
							t = s[i];
							s[i] = s[j];
							s[j] = t;
						}
					}
				}
			}

		for (int i = 1; i <= n; i++)
			cout << s[i].s << " ";
		cout << endl;
	}
}*/