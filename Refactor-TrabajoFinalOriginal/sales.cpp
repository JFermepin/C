/***************
***	INCLUDES ***
****************/

#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

/**************
***	DEFINES ***
***************/

#define DATA_BIN_FILE "data.bin"

#define TABLE_COL_NAME_SIZE 17
#define TABLE_COL_MONTH_SIZE 12

/*************
***	MACROS ***
**************/

#define GetSalesSumAmountByRegion(data, region) GetSalesSumAmount(data, region, -1, -1)
#define GetSalesSumAmountBySeller(data, seller) GetSalesSumAmount(data, -1, seller, -1)
#define GetSalesSumAmountByMonth(data, month) GetSalesSumAmount(data, -1, -1, month)
#define GetSalesSumAmountBySellerMonth(data, seller, month) GetSalesSumAmount(data, -1, seller, month)

/*************
***	USINGS ***
**************/

using namespace std;

using Data = array<array<array<int,12>,3>,4>;	//REGION - VENDEDOR - MES
using Sales = vector<int>;

/**************
***	STRUCTS ***
***************/

struct BestSeller{

	unsigned count{};
	array<int, 12> list{};

};

/*****************
***	PROTOTYPES ***
******************/

void LoadTxtFile(Data&, Sales&);
bool LoadBinData(Data&, Sales&);
void SaveBinData(Data&, Sales&);
void AddSale(Data&, Sales&, int, int, int, int);

string GetMonthName(int month);
string GetSellerName(int seller);

int GetSalesSumAmount(const Data&, int = -1, int = -1, int = -1);
unsigned GetSalesSumAmountByRegionSeller(const Data&, int, int);
unsigned GetSalesSumAmountByRegionMonth(const Data&, int, int);

array<BestSeller,4> GetBestSellers(const Data&);
array<BestSeller,4> GetBestMonths(const Data&);

void PrintBestSellersNames(const array<BestSeller,4>&);
void PrintBestMonths(const array<BestSeller,4>&);
void PrintStatistics(const Data&, const Sales&);
void PrintTable(const Data&, int);

/***********
***	MAIN ***
************/

int main()
{
	Data data{};
	Sales firstSellerSales{};

	//LoadTxtFile(data, firstSellerSales);
	LoadBinData(data, firstSellerSales);

	PrintStatistics(data, firstSellerSales);

	return 0;
}

/****************
***	FUNCTIONS ***
*****************/

void LoadTxtFile(Data& data, Sales& sellerSales)
{
	for (int region{}, seller{}, month{}, amount{}; cin >> region >> seller >> month >> amount;)
		AddSale(data, sellerSales, region, seller, month, amount);

	SaveBinData(data, sellerSales);
}

bool LoadBinData(Data &data, Sales& sellerSales)
{
	unsigned total{};

	ifstream file;
	try
	{
		file.open(DATA_BIN_FILE, ios::in | ios::binary);
		file.read(reinterpret_cast<char *>(&data), sizeof(data));
		file.read(reinterpret_cast<char *>(&sellerSales), sizeof(sellerSales));
		file.close();
	}
	catch (int error)
	{
		if (file.is_open())
			file.close();
		return false;
	}

	return total > 0;
}

void SaveBinData(Data &data, Sales& sellerSales)
{
	ofstream file;
	unsigned size = sizeof(data) + sizeof(sellerSales);

	file.open(DATA_BIN_FILE, ios::out | ios::binary);

	file.write(reinterpret_cast<char *>(&data), sizeof(data));
	file.write(reinterpret_cast<char *>(&sellerSales), sizeof(sellerSales));

	file.close();

	cout << "The file <" << DATA_BIN_FILE << "> used <" << size << "> bytes.\n";
}

void AddSale(Data& data, Sales& sellerSales, int region, int seller, int month, int amount)
{
	data.at(region-1).at(seller-1).at(month-1) += amount;

	if (region == 1 && seller == 1){
		sellerSales.push_back(amount);
	}
}

string GetRegionName(int region)
{
	switch (region)
	{
	case 1:
		return "North";
	case 2:
		return "West";
	case 3:
		return "South";
	case 4:
		return "East";
	default:
		return "Not defined";
	}
}

string GetMonthName(int month)
{
	switch (month)
	{
	case 1:
		return "January";
	case 2:
		return "February";
	case 3:
		return "March";
	case 4:
		return "April";
	case 5:
		return "May";
	case 6:
		return "June";
	case 7:
		return "July";
	case 8:
		return "August";
	case 9:
		return "September";
	case 10:
		return "October";
	case 11:
		return "November";
	case 12:
		return "December";
	default:
		return "Not defined";
	}
}

string GetSellerName(int seller)
{
	switch (seller)
	{
	case 1:
		return "Roger Caceres";
	case 2:
		return "German Ceballos";
	case 3:
		return "Jeronimo Fermepin";
	default:
		return "Not defined";
	}
}

int GetSalesSumAmount(const Data &data, int region, int seller, int month)
{
	int sum{};
	for (int ix_region{region != -1 ? region : 0}; ix_region < ((region != -1) ? region + 1 : 4); ix_region++)
		for (int ix_seller{seller != -1 ? seller : 0}; ix_seller < ((seller != -1) ? seller + 1 : 3); ix_seller++)
			for (int ix_month{month != -1 ? month : 0}; ix_month < ((month != -1) ? month + 1 : 12); ix_month++)
				sum += data.at(ix_region).at(ix_seller).at(ix_month);
	return sum;
}

unsigned GetSalesSumAmountByRegionSeller(const Data &data, int region, int seller)
{
    unsigned total{};
    for(int month{} ; month < 12 ; month++)
        total += data.at(region).at(seller).at(month);
    return total;
}

unsigned GetSalesSumAmountByRegionMonth(const Data &data, int region, int month)
{
    unsigned total{};
    for(int seller{} ; seller < 3 ; seller++)
        total += data.at(region).at(seller).at(month);
    return total;
}

array<BestSeller,4> GetBestSellers(const Data &data)
{
	array<BestSeller,4> bestSellers{};

	for (int ix_region{}; ix_region < 4; ix_region++)
	{
		int maxAmount{};

		for (int ix_seller{}; ix_seller < 3; ix_seller++){

			int max = GetSalesSumAmountByRegionSeller(data, ix_region, ix_seller);

			if (max > maxAmount)
			{
				maxAmount = max;
				bestSellers.at(ix_region).count = 0;
                bestSellers.at(ix_region).list.fill(0);
			}
			if (max >= maxAmount)
			{
				bestSellers.at(ix_region).list.at(bestSellers.at(ix_region).count) = ix_seller;
			    bestSellers.at(ix_region).count++;
			}
		}
	}

	return bestSellers;
}

array<BestSeller,4> GetBestMonths(const Data &data)
{
	array<BestSeller,4> bestMonths{};

	for (int ix_region{}; ix_region < 4; ix_region++)
	{
		int maxAmount{};

		for (int ix_month{}; ix_month < 12; ix_month++){

			int max = GetSalesSumAmountByRegionMonth(data, ix_region, ix_month);

			if (max > maxAmount)
			{
				maxAmount = max;
				bestMonths.at(ix_region).count = 0;
                bestMonths.at(ix_region).list.fill(0);
			}
			if (max >= maxAmount)
			{
				bestMonths.at(ix_region).list.at(bestMonths.at(ix_region).count) = ix_month;
			    bestMonths.at(ix_region).count++;
			}
		}
	}

	return bestMonths;
}

void PrintBestSellersNames(const array<BestSeller,4> bestSellers, int region)
{
	cout << "[";
	for (int ix{}; ix < bestSellers.at(region).count; ix++)
	{
		cout << (ix > 0 ? ", " : "") << GetSellerName(bestSellers.at(region).list.at(ix) + 1);
	}
	cout << "]";
}

void PrintBestMonths(const array<BestSeller,4> bestMonths, int region)
{
	cout << "[";
	for (int ix{}; ix < bestMonths.at(region).count; ix++)
	{
		cout << (ix > 0 ? ", " : "") << GetMonthName(bestMonths.at(region).list.at(ix) + 1);
	}
	cout << "]";
}

void PrintStatistics(const Data &data, const Sales& sellerSales)
{
	/*
	cout << "Sales for the region 1, seller 1: [";
	for (unsigned ix{}; ix < sellerSales.size(); ix++)
	{
		cout << (ix > 0 ? ", " : "") << sellerSales.at(ix);
	}
	cout << "]\n\n";
	*/

	array<BestSeller,4> bestSellers = GetBestSellers(data);
	array<BestSeller,4> bestMonths = GetBestMonths(data);

	for (int ix_region{}; ix_region < 4; ix_region++)
	{
		cout << "Statistics for Region <" << GetRegionName(ix_region + 1) << ">:\n";
		cout << "\tMax amount of the year: $" << GetSalesSumAmountByRegion(data, ix_region) << "\n";
		cout << "\tBest seller/s of the year: ";
		PrintBestSellersNames(bestSellers, ix_region);
		cout << "\n";
		cout << "\tBest months/s of the year: ";
		PrintBestMonths(bestMonths, ix_region);
		cout << "\n";
		cout << "\n";
		PrintTable(data, ix_region);
	}
}

string FixedLengthString(string txt, unsigned length)
{
	string ret{};
	for (unsigned i{}; i < length; i++)
		ret += txt.length() > i ? txt[i] : ' ';
	return ret;
}

void PrintTable(const Data &data, int ix_region)
{
	// Print headers
	cout << "\t" << FixedLengthString("Seller", TABLE_COL_NAME_SIZE);
	for (int i{}; i < 12; i++)
		cout << " | " << FixedLengthString(GetMonthName(i + 1), TABLE_COL_MONTH_SIZE);

	cout << " | " << FixedLengthString("Total", TABLE_COL_MONTH_SIZE) << "\t";

	// Print div line
	for (int i{}; i < (TABLE_COL_NAME_SIZE + 13 * (TABLE_COL_MONTH_SIZE + 3) - 5); i++)
		cout << "-";
	cout << "\n";

	// Print amounts by seller
	for (int ix_seller{}; ix_seller < 3; ix_seller++)
	{
		cout << "\t" << FixedLengthString(GetSellerName(ix_seller + 1), TABLE_COL_NAME_SIZE);
		for (int ix_month{}; ix_month < 12; ix_month++)
		{
			cout << " | $" << FixedLengthString(to_string(GetSalesSumAmount(data, ix_region, ix_seller, ix_month)), (TABLE_COL_MONTH_SIZE - 1));
		}
		cout << " | $" << FixedLengthString(to_string(GetSalesSumAmountByRegionSeller(data, ix_region, ix_seller)), (TABLE_COL_MONTH_SIZE - 1));
	}

	// Print div line
	cout << "\t";
	for (int i{}; i < (TABLE_COL_NAME_SIZE + 13 * (TABLE_COL_MONTH_SIZE + 3) - 5); i++)
		cout << "-";
	cout << "\n";

	// Print Total amounts
	cout << "\t" << FixedLengthString("Total", TABLE_COL_NAME_SIZE);
	for (int ix_month{}; ix_month < 12; ix_month++)
	{
		cout << " | $" << FixedLengthString(to_string(GetSalesSumAmountByRegionMonth(data, ix_region, ix_month)), (TABLE_COL_MONTH_SIZE - 1));
	}
	cout << " | $" << FixedLengthString(to_string(GetSalesSumAmountByRegion(data, ix_region)), (TABLE_COL_MONTH_SIZE - 1)) << "\n";

	cout << "\n";
}