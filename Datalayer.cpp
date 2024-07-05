#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include "MyMarket.h"
#pragma warning(disable:4996)

#define ProductDataPath "data\\product.csv"
#define CustomerDataPath "data\\customer.csv"
#define MerchantDataPath "data\\merchant.csv"
#define AccountDataPath "data\\account.csv"
#define OrderDataPath "data\\order.csv"
using namespace std;
unsigned long long 	StringToPhone(const char* str)
{
	unsigned long long sum = 0;
	char* pch = (char*)str;
	sum = *pch-'0';
	while (*pch != '\0')
	{
		pch++;
		if (*pch == '\0')
			break;
		sum = sum * 10 + (*pch-'0');
		//cout << sum << endl;
		//cout << "pch=" << pch << endl;
	}
	return sum;
}
// ���ַ������ָ����ָ�Ϊ������ַ���
int ParseString(const char* str, char* word[], const char delim)
{
	int count = 0;
	char* pch = (char*)str;

	while (true) {
		// ��count�����ַ�������ʼλ��
		word[count++] = pch;

		// ͨ�����Ѱ�ҷָ���delim�����ַ�������������õ�count�����ַ����Ľ���λ��
		while (*pch != delim && *pch != '\0')
			pch++;

		// ��������������ַ��������˳�
		if (*pch == '\0')
			break;

		// �����ַ�������
		*pch = '\0';

		// ���Ѱ���������ַ���
		do pch++;
		while (*pch == delim);
	}

	return count;
}
// ��ȡ��Ʒ��Ϣ��
bool LoadProductList(ProductArray& ProductList)
{
	ifstream  ifs(ProductDataPath);
	if (!ifs) {
		cout << "Product file open error." << endl;
		return false;
	}

	// ���ڴ洢���ַ����ֽ��õ��ĸ������ַ�������
	char* word[NumOfProductAttrib];

	// ���ж�ȡ�ļ����洢���ַ���LineBuffer֮��
	const int BufferSize = 4096;
	char LineBuffer[BufferSize];
	while (ifs.getline(LineBuffer, BufferSize)) {
		// �ֽ��ַ���Ϊ���ַ����Ӵ����洢���ַ�������֮��
		int nWords = ParseString(LineBuffer, word);

		if (nWords != NumOfProductAttrib) {
			cerr << "Product data error." << endl;
			ifs.close();
			return false;
		}
		// ����ṹ����������ݷֽ�õ����ַ����Ӵ������ṹ������ĸ����Ը�ֵ
		Product product;
		product.ProductID = atoi(word[0]);
		product.AccountID = atoi(word[1]);
		strcpy(product.name, word[2]);
		product.price = atof(word[3]);
		product.stock = atoi(word[4]);
		product.rating = atof(word[5]);
		product.nRatings = atoi(word[6]);
		product.nSales = atoi(word[7]);
		// ���¶������Ʒ��Ϣ�ṹ�����������vector����ProductList��β��
		ProductList.push_back(product);
		//cout << product.name << endl;
	}
	ifs.close();

	return true;
}
bool LoadCustomerList(CustomerArray& CustomerList)
{
	ifstream  ifs(CustomerDataPath);
	if (!ifs) {
		cout << "Customer file open error." << endl;
		return false;
	}
	char* word[NumOfCustomerAttrib];
	const int BufferSize = 1024;
	char LineBuffer[BufferSize];
	while (ifs.getline(LineBuffer, BufferSize)) {
		int nWords = ParseString(LineBuffer, word);
		if (nWords != NumOfCustomerAttrib) {
			cerr << "Customer data error." << endl;
			ifs.close();
			return false;
		}
		Customer customer;
		customer.id = atoi(word[0]);
		strcpy(customer.name, word[1]);
		customer.sex = (Sex)atof(word[2]);
		StringToDate(word[3], customer.birthday);
		//cout << customer.birthday.year<<" "<<customer.birthday .month<<" "<<customer.birthday.day << endl;
		strcpy(customer.address, word[4]);
		customer.phone = StringToPhone(word[5]);
		CustomerList.push_back(customer);
		
		//cout << customer.phone << endl;
	}
	ifs.close();

	return true;
}
bool LoadMerchantList(MerchantArray& MerchantList)
{
	ifstream  ifs(MerchantDataPath);
	if (!ifs) {
		cout << "Merchant file open error." << endl;
		return false;
	}
	char* word[NumOfMerchantAttrib];
	const int BufferSize = 1024;
	char LineBuffer[BufferSize];
	while (ifs.getline(LineBuffer, BufferSize)) {
		int nWords = ParseString(LineBuffer, word);

		if (nWords != NumOfMerchantAttrib) {
			cerr << "Merchant data error." << endl;
			ifs.close();
			return false;
		}
		Merchant merchant;
		merchant.id = atoi(word[0]);
		strcpy(merchant.name , word[1]);
		merchant.phone = StringToPhone(word[2]);
		merchant.totalSales = atof(word[3]);
		merchant.nRatings = atoi(word[4]);
		merchant.rating = atof(word[5]);
		MerchantList.push_back(merchant);
		//cout << merchant.phone << endl;
	}
	ifs.close();
	return true;
}
bool LoadAccountList(AccountArray& AccountList)
{
	ifstream  ifs(AccountDataPath);
	if (!ifs) {
		cout << "Account file open error." << endl;
		return false;
	}
	char* word[NumOfAccountAttrib];
	const int BufferSize = 1024;
	char LineBuffer[BufferSize];
	while (ifs.getline(LineBuffer, BufferSize)) {
		int nWords = ParseString(LineBuffer, word);

		if (nWords != NumOfAccountAttrib) {
			cerr << "Account data error." << endl;
			ifs.close();
			return false;
		}
		Account account;
		account.id = atoi(word[0]);
		strcpy(account.LoginName, word[1]);
		strcpy(account.password, word[2]);
		account.type = (UserType)atoi(word[3]);
		account.money = atof(word[4]);
		AccountList.push_back(account);
	}
	ifs.close();
	return true;
}

bool LoadOrderList(OrderArray& OrderList)
{
	ifstream  ifs(OrderDataPath);
	if (!ifs) {
		cout << "Order file open error." << endl;
		return false;
	}
	char* word[NumOfOrderAttrib];
	const int BufferSize = 2048;
	char LineBuffer[BufferSize];
	while (ifs.getline(LineBuffer, BufferSize)) {
		int nWords = ParseString(LineBuffer, word);

		if (nWords != NumOfOrderAttrib) {
			cerr << "Order data error." << endl;
			ifs.close();
			return false;
		}
		Order order;
		order.orderid = atoi(word[0]);
		order.buyerid  = atoi(word[1]);
		order.storeid = atoi(word[2]);
		order.productid = atoi(word[3]);
		strcpy(order.productname, word[4]);
		order.number = atoi(word[5]);
		StringToTime(word[6], order.time);
		//cout << order.time.date.year << " " << order.time.date.month << " " << order.time.date.day << endl;
		order.price = atof(word[7]);
		strcpy(order.receivername, word[8]);
		strcpy(order.address, word[9]);
		order.phone = StringToPhone(word[10]);
		order.stiuation = atoi(word[11]);
		OrderList.push_back(order);
	}
	ifs.close();
	return true;
}
void StringToDate(const char* str, Date& date)
{
	char* word[3];
	ParseString(str, word, '-');
	date.year = atoi(word[0]);
	//cout << word[0] << " " << word[1] << " " << word[2] << endl;
	date.month = atoi(word[1]);
	date.day = atoi(word[2]);
}
void StringToTime(const char* str, Time& time)
{
	char* word[4];
	ParseString(str, word, '-');
	time.date.year = atoi(word[0]);
	time.date.month = atoi(word[1]);
	time.date.day = *word[2]-'0';
	//cout << time.date.day << endl;
	word[2] += 2;
	char* wor[3];
	ParseString(word[2], wor, ':');
	time.hour = atoi(wor[0]);
	time.minute = atoi(wor[1]);
	time.second = atoi(wor[2]);
	//cout << time.hour << ":" << time.minute << ":" << time.second << endl;
}

// ����Ʒ�ṹ�����дΪ�ļ���һ��
void PutProductRecord(ofstream& ofs, const Product& product)
{
	ofs << product.ProductID << ',';
	ofs << product.AccountID << ',';
	ofs << product.name << ',';
	ofs << product.price << ',';
	ofs << product.stock << ',';
	ofs << product.rating << ',';
	ofs << product.nRatings << ',';
	ofs << product.nSales << endl;
}

bool SaveProductList(ProductArray& ProductList)
{
	ofstream ofs(ProductDataPath);
	if (!ofs) {
		cerr << "Product file open error." << endl;
		return false;
	}

	// �������е�ÿ��Ԫ�ؽ���дΪ���ݱ��е�һ��
	int nProducts = ProductList.size();
	for (int i = 0; i < nProducts; i++)
		PutProductRecord(ofs, ProductList[i]);

	ofs.close();

	return true;
}

void PrintLine(FieldPrintSetting PrintSet[], int nFields)
{
	cout << '|';
	int k = 0;
	while (true) {
		for (int i = 0; i < PrintSet[k].PrintWidth; i++)
			cout << '-';

		if (++k == nFields)
			break;

		cout << '+';
	}
	cout << '|';

	cout << endl;
}
void PrintTableHead(FieldPrintSetting PrintSet[], int nFields)
{
	// ��ʾ��ͷ
	PrintLine(PrintSet, nFields);
	cout << '|';
	for (int i = 0; i < nFields; i++) {
		const FieldPrintSetting& CurrentPrintSet = PrintSet[i];

		cout << setw(CurrentPrintSet.PrintWidth) << std::right;
		cout << CurrentPrintSet.PrintFieldName << "|";
	}
	cout << endl;

	PrintLine(PrintSet, nFields);
}
char* TrimString(const char* src, char* dst, int width, string& remaining)
{
	// �ҵ��ض�λ��
	int i = 0;
	while (i < width && src[i] != '\0') {
		dst[i] = src[i];
		i++;
	}
	// �����ַ���������ʵ���ַ����Ľض�
	dst[i] = '\0';

	// ��ʣ���ַ�����ֵ
	remaining = src + i;

	return dst;
}
void PrintRemaining(FieldPrintSetting PrintSet[], int nFields, string strs[])
{
	char buffer[32];
	string remaining;

	while (true) {
		// �ж��Ƿ�����ʣ���ַ�����Ϊ���ַ���
		bool IsEmpty = true;
		for (int i = 0; i < nFields; i++) {
			IsEmpty = strs[i].length() == 0 && IsEmpty;
		}

		if (IsEmpty)
			break;


		// �������ʣ���ַ������������ӡ����ʣ���ַ�����������ָ���п���нضϣ�
		// ����Ϊ��Ϣ��ʣ���ַ���
		cout << '|';
		for (int i = 0; i < nFields; i++) {
			const char* CurrentString = strs[i].c_str();
			int CurrentWidth = PrintSet[i].PrintWidth;

			cout << setw(CurrentWidth) << std::left;
			cout << TrimString(CurrentString, buffer, CurrentWidth, remaining)
				<< "|";

			strs[i] = remaining;
		}
		cout << endl;
	}
}

void PrintProducts(ProductArray& products)
{
	int nProducts;
	nProducts = products.size();
	// �����ӡ�ı�ͷ�ṹ
	FieldPrintSetting PrintSet[] = { "��Ʒ���", 8,
									 "��Ʒ��", 24,
									 "�۸�", 8,
									 "���", 8,
									 "����", 6,
									 "���۴���", 8,
									 "����", 8,
									 "�̼ұ��", 8
	};

	// ��ӡ��ͷ
	const int nFields = sizeof(PrintSet) / sizeof(FieldPrintSetting);
	PrintTableHead(PrintSet, nFields);


	char buffer[32]; // ���ڴ洢�ַ����ضϲ���
	string strs[nFields]; // ���ڴ洢���ֶνضϺ��ʣ����ַ���
	for (int i = 0; i < nProducts; i++) {
		const Product& currentProduct = products[i];

		// ��ӡ��������
		cout << '|';
		cout << setw(PrintSet[0].PrintWidth) << std::right
			<< currentProduct.ProductID << '|';
		// ������Կ��ܻᳬ�����Χ���ַ��������ݱ���Ƚ���ضϣ����ض�ʣ�µĲ�������
		// ������ӡ
		cout << setw(PrintSet[1].PrintWidth) << std::left
			<< TrimString(currentProduct.name, buffer,
				PrintSet[1].PrintWidth, strs[1])
			<< '|';
		cout << setw(PrintSet[2].PrintWidth) << setiosflags(ios::fixed)
			<< std::right << setprecision(2)
			<< currentProduct.price << '|';
		cout << setw(PrintSet[3].PrintWidth) << std::right
			<< currentProduct.stock << '|';
		cout << setw(PrintSet[4].PrintWidth) << setiosflags(ios::fixed)
			<< std::right << setprecision(2)
			<< currentProduct.rating << '|';
		cout << setw(PrintSet[5].PrintWidth) << std::right
			<< currentProduct.nRatings <<
			'|';
		cout << setw(PrintSet[6].PrintWidth) << std::right
			<< currentProduct.nSales << '|';
		cout << setw(PrintSet[7].PrintWidth) << std::right
			<< currentProduct.AccountID << '|';

		cout << endl;

		// ��ӡ�ضϺ�ʣ�µĲ���
		PrintRemaining(PrintSet, nFields, strs);
		// ��ӡ������֮��ķָ���
		PrintLine(PrintSet, nFields);
	}

	cout << endl;
}
