#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <windows.h>
#include "mylib.h"
#define TRUE 1
#define FALSE 0
#define kc "\t\t\t"
using namespace std;
const int MAXLTC = 10000;
struct  MonHoc { //DANH SACH MON HOC 
	char MAMH[10];
	char TENMH[50];
	int STCLT;
	int STCTH;
};
struct  nodeMH { //CAY NHI PHAN AVL 
	MonHoc mh;
	int height;
	nodeMH* left; nodeMH* right;
};
typedef nodeMH* PTRMH;

struct DangKy { // Dang ky : DSLK don
	char MASV[15];
	float DIEM;
	bool HUYDANGKY = false;
};

struct nodeDK {
	DangKy dky;
	nodeDK* next;
};
typedef nodeDK* PTRDK;

struct LopTinChi { //DANH SACH LOP TIN CHI (ds tuyen tinh)
	int MALOPTC;
	char MAMH[10];
	char NIENKHOA[10];
	int HOCKY, NHOM;
	int SOSVMIN, SOSVMAX;
	bool HUYLOP = false;
	PTRDK FirstDK = NULL;
};

struct LIST_LTC {
	LopTinChi* nodes[MAXLTC]; //1 ptu la 1 dslkd
	int n = 0;
};

struct SinhVien {
	char MASV[15], MALOP[15];
	char HO[30], TEN[10], PHAI[5], SDT[100];
};
struct nodeSV {
	SinhVien sv;
	nodeSV* next;
};
typedef nodeSV* PTRSV;

//cac ham khac
int menu();
int XacNhan(string s);
char* uppercase(char* s);
char* Chuan_Hoa_Ten(char* r);
char* delete_space(char* str);
bool checkSDT(char S[100]);
int so(string s);
void gotoxy(int x, int y);
bool checkDoDai(string s, int i);
int main();

//ve khung de in
void ve1();
void ve2();
void ve1_12();
void ve2_12();
void ve1_13();
void ve2_13();
void ve1_14();
void ve11_14(int r);
void ve2_14();
void ve22_14(int m, string s);
void ve3_14();
void ve33_14(int r);
void vengang_LTC();
void vekhung_LTC();
void vekhungtren_DSDK(PTRMH root, char s[10]);
void vekhungduoi_DSDK();
void vekhung_DSSV();
void vengang_DSSV();
void vengang_DSMH();
void vekhung_DSMH();

//lop tin chi
LopTinChi* input_LTC(LIST_LTC& dsLTC, LopTinChi* tc, PTRMH& root, int i);
bool CheckTrungMaMH(LIST_LTC dsLTC, char s[10]);
void ADD_LTC(LIST_LTC& dsLTC, PTRMH root);
void print_LTC(LopTinChi* tc);
void Traverse_LTC(LIST_LTC dsLTC);
void delete_ltc(LIST_LTC& dsLTC, char s[10]);
void delete_LTC(LIST_LTC& dsLTC);
void fix_LTC(LIST_LTC& dsLTC, PTRMH& root);
void tudong_LTC(LIST_LTC& dsLTC);
void nhapdiem_LTC(LIST_LTC& dsLTC, PTRSV& First);
int TongSoTinChi(LIST_LTC dsLTC, PTRMH root, char s[15], char nk[10]);

//DSDK
PTRDK CheckTrung_SVDK(PTRDK& FirstDK, char s[15]);
void add_dsdk(PTRDK& FirstDK, DangKy dk);
void Traverse_DSDK(LIST_LTC dsLTC, PTRDK FirstDK, PTRSV First, PTRMH root);
void delete_DSDK(PTRDK& FirstDK, PTRDK p);
void clearlist_DSDK(PTRDK& First);
void Dki_huyDki(PTRMH& root, PTRSV& First, PTRDK& FirstDK, LIST_LTC& dsLTC);

//DSSV
bool CheckTrungSDT(PTRSV First, char s[100]);
SinhVien input_DSSV(PTRSV& First, SinhVien& sv);
PTRSV CheckTrungMSSV(PTRSV First, char s[15]);
void add_dssv(PTRSV& First, SinhVien sv);
void ADD_DSSV(PTRSV& First);
void Create_DSSV(PTRSV& First);
void Sapxepten(PTRSV& First);
void print_DSSV(PTRSV p);
void Traverse_DSSV(PTRSV First, char s[15]);
void delete_DSSV(PTRSV& First, LIST_LTC& dsLTC);
void fix_DSSV(PTRSV& First, LIST_LTC& dsLTC);
PTRSV checkLOP(PTRSV First, char sv[15], char ml[15]);
void clearlist(PTRSV& First);

//Danh sach mon hoc
MonHoc input_DSMH(PTRMH& root, MonHoc& mh);
PTRMH newNode(PTRMH& p, MonHoc b);
PTRMH rightRotate(PTRMH y);
PTRMH leftRotate(PTRMH x);
int height(PTRMH N);
int getBalanceFactor(PTRMH N);
PTRMH nodeWithMimumValue(PTRMH node);
PTRMH CheckTrung(PTRMH root, char a[10]);
void add_dsmh(PTRMH& root, MonHoc mh);
void ADD_DSMH(PTRMH& root);
void delete_dsmh(PTRMH& root, MonHoc b);
void delete_DSMH(PTRMH& root, LIST_LTC& dsLTC);
void print_DSMH(PTRMH p);
void Traverse_DSMH(PTRMH root);
void fix_DSMH(PTRMH& root, LIST_LTC& dsLTC);

// Doc file
int DocFile_LTC(char* duongDan, LIST_LTC& dsLTC);
int DocFile_DSSV(char* duongDan, PTRSV& First);
int DocFile_DSMH(char* duongDan, PTRMH& root);

//Ghi file
int GhiFile_LTC(char* duongDan, LIST_LTC& dsLTC);
int GhiFile_DSSV(char* duongDan, PTRSV& First);
void GhiFile_DSMH_LNR(PTRMH root, ofstream& f);
int GhiFile_DSMH(char* duongDan, PTRMH root);

//bang diem
void bangdiem(LIST_LTC dsLTC, PTRSV First, PTRMH root);
void Traverse_KhoaHoc(LIST_LTC dsLTC, PTRSV First, PTRMH root);
void Traverse_TongKet(LIST_LTC dsLTC, PTRSV First, PTRMH root);

int menu() {
	char cn[10000];
	do {
		system("cls");
		printf("\n\n\n\t\t\t\tCHUONG TRINH QUAN LY DIEM SINH VIEN THEO HE TIN CHI");
		printf("\n\n\t\t\tCac chuc nang cua chuong trinh:\n");
		printf("\t\t\t   1: Cap nhap thong tin lop tin chi\n");
		printf("\t\t\t   2: Cap nhap danh sach sinh vien\n");
		printf("\t\t\t   3: Cap nhap mon hoc\n");
		printf("\t\t\t   4: Xem danh sach lop tin chi\n");
		printf("\t\t\t   5: Xem danh sach sinh vien dang ki lop tin chi\n");
		printf("\t\t\t   6: Xem danh sach sinh vien(theo ma lop)\n");
		printf("\t\t\t   7: Xem danh sach mon hoc\n");
		printf("\t\t\t   8: Xem bang diem mon hoc cua 1 lop tin chi\n");
		printf("\t\t\t   9: Dang ki/Huy dang ki lop tin chi\n");
		printf("\t\t\t  10: Huy lop tin chi tu dong\n");
		printf("\t\t\t  11: Nhap Diem/Hieu chinh diem\n");
		printf("\t\t\t  12: Bang thong ke diem trung binh khoa hoc\n");
		printf("\t\t\t  13: Bang diem tong ket\n");
		printf("\t\t\t   0: Ket thuc chuong trinh\n");
		printf("\t\t\tChuc nang ban chon: ");
		cin>>cn;
		if (strlen(cn) == 2&&cn[0]=='1') {
			if (cn[1] >= '0' && cn[1] <= '3') return atoi(cn);
		}
		if (strlen(cn) == 1 && cn[0] >= '0' && cn[0] <= '9') return atoi(cn);
	} while (1);
}

int XacNhan(string s) {
	cout << s;
	char kt;
	do {
		kt = toupper(_getch()); //toupper: giup tat ca cac ki tu nhap vao deu in hoa.
	} while (kt != 'Y' && kt != 'N');
	cout << kt;
	return kt == 'Y';
}

char* uppercase(char* s) {
	delete_space(s);
	for (int i = 0; i < 15; ++i) {
		if (s[i] >= 'a' && s[i] <= 'z') s[i] -= 32;
		if (s[i] == '\0') break;
	}
	return s;
}

char* Chuan_Hoa_Ten(char* r) {
	string s(r);
	int n = s.length();
	if (n == 1 && s[0] >= 'a' && s[0] <= 'z') s[0] -= 32;
	else {
		for (int i = 0; i < s.length(); ++i) {
			if (s[0] == ' ') {
				s.erase(s.begin() + i);
				i--;
			}
			else if (s[0] >= 'a' && s[0] <= 'z') {
				s[0] -= 32;
				i--;
			}
			else if (s[i] == ' ' && s[i + 1] == ' ') {
				s.erase(s.begin() + i);
				i--;
			}
			else if (s[i] == ' ' && s[i + 1] != ' ') {
				if (s[i + 1] >= 'a' && s[i + 1] <= 'z') s[i + 1] -= 32;
				i++;
			}
			else if (i == s.length() - 1 && s[i] == ' ') {
				s.erase(s.begin() + i);
				break;
			}
			else if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 32;
		}
	}
	char* c = new char[n + 1];
	for (int i = 0; i < n; ++i)
		c[i] = s[i];
	c[n] = '\0';
	return c;
}

char* delete_space(char* str) {
	int pos = 0;
	int n = strlen(str);
	for (int i = 0; i < n; i++)
		if (str[i] == 32)
		{
			for (int j = i; j < n; j++)
			{
				str[j] = str[j + 1];
				i--;
			}
		}
	return str;
}

bool checkSDT(char s[100]) {
	delete_space(s);
	if (strlen(s) == 10) {
		for (int i = 0; i < 10; ++i) {
			if (s[i] < '0' || s[i]>'9') return 0;
		}
		return 1;
	}
	return 0;
}


///////////////////////////////////...VE KHUNG.../////////////// 
void ve1() {
	cout << setfill(char(196));
	cout << "\n" << kc << char(218) << setw(102) << char(196) << char(191) << endl;
	cout << setfill(' ');
	cout << kc << char(179) << setw(69) << left << " \t\t\t\t\t  DANH SACH LOP TIN CHI ";
	cout << char(179) << endl;
	cout << setfill(char(196));
	cout << kc << char(195) << setw(10) << left << "" << char(194);
	cout << setw(50) << left << "" << char(194);
	cout << setw(6) << left << "" << char(194);
	cout << setw(13) << left << "" << char(194);
	cout << setw(19) << left << "" << char(180) << endl;
	cout << setfill(' ');
	cout << kc << char(179) << setw(10) << left << "  MaMH" << char(179);
	cout << setw(50) << left << "                 Ten Mon Hoc  " << char(179);
	cout << setw(6) << left << " Nhom " << char(179);
	cout << setw(13) << left << " So SV da DK " << char(179);
	cout << setw(19) << left << " So Slot Con Trong " << char(179);
	cout << setfill(char(196));
}
void ve2() {
	cout << setfill(char(196));
	cout << "\n" << kc << char(195) << setw(10) << left << "" << char(197);
	cout << setw(50) << left << "" << char(197);
	cout << setw(6) << left << "" << char(197);
	cout << setw(13) << left << "" << char(197);
	cout << setw(19) << left << "" << char(197) << endl;
}
void ve1_12() {
	cout << setfill(char(196));
	cout << "\n\n" << kc << char(218) << setw(3) << left << "" << char(194);
	cout << setw(15) << left << "" << char(194);
	cout << setw(30) << left << "" << char(194);
	cout << setw(10) << left << "" << char(194);
	cout << setw(6) << left << "" << char(191) << endl;
	cout << setfill(' ');
	cout << kc << char(179) << setw(3) << left << "STT" << char(179);
	cout << setw(15) << left << "   MaSV" << char(179);
	cout << setw(30) << left << "               HO" << char(179);
	cout << setw(10) << left << "   TEN" << char(179);
	cout << setw(6) << left << " DIEM " << char(179);
	cout << setfill(char(196));
}
void ve2_12() {
	cout << setfill(char(196));
	cout << "\n" << kc << char(195) << setw(3) << left << "" << char(197);
	cout << setw(15) << left << "" << char(197);
	cout << setw(30) << left << "" << char(197);
	cout << setw(10) << left << "" << char(197);
	cout << setw(6) << left << "" << char(180) << endl;
	cout << setfill(' ');
}
void ve1_13() {
	cout << setfill(char(196));
	cout << "\n\n" << kc << char(218) << setw(3) << left << "" << char(194);
	cout << setw(15) << left << "" << char(194);
	cout << setw(30) << left << "" << char(194);
	cout << setw(10) << left << "" << char(194);
	cout << setw(9) << left << "" << char(191) << endl;
	cout << setfill(' ');
	cout << kc << char(179) << setw(3) << left << "STT" << char(179);
	cout << setw(15) << left << "   MaSV" << char(179);
	cout << setw(30) << left << "               HO" << char(179);
	cout << setw(10) << left << "   TEN" << char(179);
	cout << setw(9) << left << " DIEM TB " << char(179);
	cout << setfill(char(196));
}
void ve2_13() {
	cout << setfill(char(196));
	cout << "\n" << kc << char(195) << setw(3) << left << "" << char(197);
	cout << setw(15) << left << "" << char(197);
	cout << setw(30) << left << "" << char(197);
	cout << setw(10) << left << "" << char(197);
	cout << setw(9) << left << "" << char(180) << endl;
	cout << setfill(' ');
}
void ve1_14() {
	cout << setfill(char(196));
	cout << "\n\n" << kc << char(218) << setw(3) << left << "" << char(194);
	cout << setw(15) << left << "" << char(194);
	cout << setw(40) << left << "" << char(194);
}
void ve11_14(int z) {
	while (z != 1) {
		cout << setfill(char(196));
		cout << setw(10) << left << "" << char(194);
		z--;
	}
	cout << setw(10) << left << "" << char(191) << endl;
}
void ve2_14() {
	cout << setfill(' ');
	cout << kc << char(179) << setw(3) << left << "STT" << char(179);
	cout << setw(15) << left << "     MaSV" << char(179);
	cout << setw(40) << left << "                 HO TEN" << char(179);
}
void ve22_14(int m, string s) {
	while (m--) {
		int found = s.find(" ");
		string tmp = s.substr(1, found - 1);
		cout << setw(10) << left << tmp << char(179);
		s.erase(0, found + 1);
	}
	cout << endl;
}
void ve3_14() {
	cout << setfill(char(196));
	cout << kc << char(195) << setw(3) << left << "" << char(197);
	cout << setw(15) << left << "" << char(197);
	cout << setw(40) << left << "" << char(197);
}
void ve33_14(int r) {
	while (r != 1) {
		cout << setfill(char(196));
		cout << setw(10) << left << "" << char(197);
		r--;
	}
	cout << setw(10) << left << "" << char(180) << endl;
}
void vengang_LTC() {
	cout << setfill(char(196));
	cout << "\n" << kc << char(195) << setw(7) << left << "" << char(197);
	cout << setw(9) << left << "" << char(197);
	cout << setw(12) << left << "" << char(197);
	cout << setw(8) << left << "" << char(197);
	cout << setw(8) << left << "" << char(197);
	cout << setw(9) << left << "" << char(197);
	cout << setw(9) << left << "" << char(197);
	cout << setw(12) << left << "" << char(180) << endl;
}
void vekhung_LTC() {
	cout << setfill(char(196));
	cout << "\n" << kc << char(218) << setw(81) << char(196) << char(191) << endl;
	cout << setfill(' ');
	cout << kc << char(179) << setw(62) << left << " \t\t\t  DANH SACH LOP TIN CHI ";
	cout << char(179) << endl;
	cout << setfill(char(196));
	cout << kc << char(195) << setw(7) << left << "" << char(194);
	cout << setw(9) << left << "" << char(194);
	cout << setw(12) << left << "" << char(194);
	cout << setw(8) << left << "" << char(194);
	cout << setw(8) << left << "" << char(194);
	cout << setw(9) << left << "" << char(194);
	cout << setw(9) << left << "" << char(194);
	cout << setw(12) << left << "" << char(180) << endl;
	cout << setfill(' ');
	cout << kc << char(179) << setw(7) << left << " MLTC" << char(179);
	cout << setw(9) << left << "  MaMH" << char(179);
	cout << setw(12) << left << "  NienKhoa" << char(179);
	cout << setw(8) << left << " Hocki" << char(179);
	cout << setw(8) << left << "  Nhom" << char(179);
	cout << setw(9) << left << "  SVmin" << char(179);
	cout << setw(9) << left << "  SVmax" << char(179);
	cout << setw(12) << left << " Trang thai" << char(179);
	cout << setfill(char(196));
	vengang_LTC();
}
void vekhungtren_DSDK(PTRMH root, char s[10]) {
	PTRMH p;
	p = CheckTrung(root, s);
	cout << setfill(char(196));
	cout << "\n\t" << kc << char(218) << setw(84) << char(196) << char(191) << endl;
	cout << setfill(' ');
	cout << "\t" << kc << char(179) << setw(65) << left << " \t\t\t     DANH SACH SINH VIEN DANG KI" << char(179);
	cout << setfill(char(196));
	cout << "\n\t" << kc << char(195) << setw(84) << left << "" << char(180);
	cout << setfill(' ');
	cout << "\n\t" << kc << char(179) << setw(8) << left << " MaMH : " << setw(10) << left << p->mh.MAMH;
	cout << "  Ten mon hoc : " << setw(50) << p->mh.TENMH << char(179);
	cout << endl;
}
void vekhungduoi_DSDK() {
	cout << setfill(char(196));
	cout << "\t" << kc << char(195) << setw(3) << left << "" << char(194);
	cout << setw(14) << left << "" << char(194);
	cout << setw(14) << left << "" << char(194);
	cout << setw(19) << left << "" << char(194);
	cout << setw(9) << left << "" << char(194);
	cout << setw(9) << left << "" << char(194);
	cout << setw(10) << left << "" << char(180) << endl;
	cout << setfill(' ');
	cout << "\t" << kc << char(179) << setw(3) << left << "STT" << char(179);
	cout << setw(14) << left << "    MALOP" << char(179);
	cout << setw(14) << left << "     MASV" << char(179);
	cout << setw(19) << left << "       HO" << char(179);
	cout << setw(9) << left << "  TEN" << char(179);
	cout << setw(9) << left << "  PHAI" << char(179);
	cout << setw(10) << left << "   SDT" << char(179);
	cout << setfill(char(196));
}
void vekhung_DSSV() {
	cout << setfill(char(196));
	cout << "\n\t" << kc << char(218) << setw(84) << char(196) << char(191) << endl;
	cout << setfill(' ');
	cout << "\t" << kc << char(179) << setw(65) << left << " \t\t\t         DANH SACH SINH VIEN ";
	cout << char(179) << endl;
	cout << setfill(char(196));
	cout << "\t" << kc << char(195) << setw(3) << left << "" << char(194);
	cout << setw(14) << left << "" << char(194);
	cout << setw(14) << left << "" << char(194);
	cout << setw(19) << left << "" << char(194);
	cout << setw(9) << left << "" << char(194);
	cout << setw(9) << left << "" << char(194);
	cout << setw(10) << left << "" << char(180) << endl;
	cout << setfill(' ');
	cout << "\t" << kc << char(179) << setw(3) << left << "STT" << char(179);
	cout << setw(14) << left << "    MALOP" << char(179);
	cout << setw(14) << left << "     MASV" << char(179);
	cout << setw(19) << left << "       HO" << char(179);
	cout << setw(9) << left << "  TEN" << char(179);
	cout << setw(9) << left << "  PHAI" << char(179);
	cout << setw(10) << left << "   SDT" << char(179);
	cout << setfill(char(196));
	vengang_DSSV();
}
void vengang_DSSV() {
	cout << setfill(char(196));
	cout << "\n\t" << kc << char(195) << setw(3) << left << "" << char(197);
	cout << setw(14) << left << "" << char(197);
	cout << setw(14) << left << "" << char(197);
	cout << setw(19) << left << "" << char(197);
	cout << setw(9) << left << "" << char(197);
	cout << setw(9) << left << "" << char(197);
	cout << setw(10) << left << "" << char(180) << endl;
}
void vengang_DSMH() {
	cout << setfill(char(196));
	cout << "\n" << kc << char(195) << setw(3) << left << "" << char(197);
	cout << setw(10) << left << "" << char(197);
	cout << setw(50) << left << "" << char(197);
	cout << setw(5) << left << "" << char(197);
	cout << setw(5) << left << "" << char(180) << endl;
}
void vekhung_DSMH() {
	cout << setfill(char(196));
	cout << "\n" << kc << char(218) << setw(77) << char(196) << char(191) << endl;
	cout << setfill(' ');
	cout << kc << char(179) << setw(58) << left << " \t\t\t      DANH SACH MON HOC ";
	cout << char(179) << endl;
	cout << setfill(char(196));
	cout << kc << char(195) << setw(3) << left << "" << char(194);
	cout << setw(10) << left << "" << char(194);
	cout << setw(50) << left << "" << char(194);
	cout << setw(5) << left << "" << char(194);
	cout << setw(5) << left << "" << char(180) << endl;
	cout << setfill(' ');
	cout << kc << char(179) << setw(3) << left << "STT" << char(179);
	cout << setw(10) << left << "  Ma MH" << char(179);
	cout << setw(50) << left << "                 Ten Mon Hoc" << char(179);
	cout << setw(5) << left << "STCLT" << char(179);
	cout << setw(5) << left << "STCTH" << char(179);
	cout << setfill(char(196));
	vengang_DSMH();
}

/////////////////////////////...LOP TIN CHI...////////////////////////

LopTinChi* input_LTC(LIST_LTC& dsLTC, LopTinChi* tc, PTRMH& root, int i) {
	MonHoc a;
nhaplai:
	cout << endl << kc << "Nhap MA Mon Hoc: ";	gets_s(tc->MAMH);
	uppercase(tc->MAMH);
	if (i == 1) {
		if (CheckTrung(root, tc->MAMH) == NULL) {
			cout << kc;
			int xn = XacNhan("Ban co muon them mon hoc nay vao danh sach mon hoc khong(Y / N) ?");
			if (xn == 1) {
				cout << "\n\n" << kc << "* THEM MON HOC *\n";
				strcpy_s(a.MAMH, tc->MAMH);
				cout << endl << kc << "Nhap TEN mon hoc : ";	gets_s(a.TENMH);
				Chuan_Hoa_Ten(a.TENMH);
				cout << kc << "Nhap SO TC ly thuyet: "; cin >> a.STCLT;
				cout << kc << "Nhap SO TC thuc hanh: "; cin >> a.STCTH;
				add_dsmh(root, a);
				cin.ignore();
				goto nhap;
			}
			else {
				cout << "\n " << kc << "Nhap lai ma mon hoc !";
				goto nhaplai;
			}
		}
	}
nhap:
	cout << kc << "Nhap Nien Khoa: ";	gets_s(tc->NIENKHOA); delete_space(tc->NIENKHOA);
	cout << kc << "Hoc Ky: "; cin >> tc->HOCKY;
	cout << kc << "Nhom: ";	cin >> tc->NHOM;
	if (i == 1) {
		if (CheckTrungMaMH(dsLTC, tc->MAMH) == 1) {
			for (int i = 0; i < dsLTC.n; ++i) {
				if (strcmp(tc->NIENKHOA, dsLTC.nodes[i]->NIENKHOA) == 0 && dsLTC.nodes[i]->HOCKY == tc->HOCKY && dsLTC.nodes[i]->NHOM == tc->NHOM) {
					cout << "\n " << kc << "Ma mon hoc bi trung, vui long nhap lai !";
					cin.ignore();
					goto nhaplai;
				}
			}
		}
	}
	cout << kc << "So Sinh Vien Toi Thieu (it nhat 1 sv ): ";	cin >> tc->SOSVMIN;
	if (tc->SOSVMIN < 1) {
		do {
			cout << kc << "Khong hop le, vui long nhap lai so sv > " << tc->SOSVMIN << ": ";
			cin >> tc->SOSVMIN;
		} while (tc->SOSVMIN < 1);
	}
	cout << kc << "So Sinh Vien Toi Da: "; cin >> tc->SOSVMAX;
	if (tc->SOSVMAX <= tc->SOSVMIN) {

		do {
			cout << kc << "Khong hop le, vui long nhap lai so sv >  " << tc->SOSVMIN << ": ";
			cin >> tc->SOSVMAX;
		} while (tc->SOSVMAX < tc->SOSVMIN);
	}
	tc->HUYLOP = 0;
	return tc;
}

bool CheckTrungMaMH(LIST_LTC dsLTC, char s[10]) {
	for (int i = 0; i < dsLTC.n; i++) {
		int x = strcmp(dsLTC.nodes[i]->MAMH, s);
		if (x == 0) return true;
	}
	return false;
}

void ADD_LTC(LIST_LTC& dsLTC, PTRMH root) {
	cout << "\n" << kc << "Nhap thong tin can THEM ! \n\n";
	LopTinChi* tc = new LopTinChi;
	tc->MALOPTC = dsLTC.nodes[dsLTC.n-1]->MALOPTC + 1;
	dsLTC.nodes[dsLTC.n] = input_LTC(dsLTC, tc, root, 1);
	dsLTC.n++;
	cout << "\n" << kc << "Them lop tin chi thanh cong!";
}

void print_LTC(LopTinChi* tc) {
	cout << kc << char(179) << setw(7) << left << tc->MALOPTC << char(179);
	cout << setw(9) << left << tc->MAMH << char(179);
	cout << setw(12) << left << tc->NIENKHOA << char(179);
	cout << setw(8) << left << tc->HOCKY << char(179);
	cout << setw(8) << left << tc->NHOM << char(179);
	cout << setw(9) << left << tc->SOSVMIN << char(179);
	cout << setw(9) << left << tc->SOSVMAX << char(179);
	if (tc->HUYLOP == true) {
		cout << setw(12) << left << "DA HUY LOP" << char(179);
	}
	else {
		cout << setw(12) << left << "CHUA HUY LOP" << char(179);
	}
}

void Traverse_LTC(LIST_LTC dsLTC) {
	vekhung_LTC();
	for (int i = 0; i < dsLTC.n; ++i) {
		cout << setfill(' ');
		print_LTC(dsLTC.nodes[i]);
		vengang_LTC();
	}
}

void delete_ltc(LIST_LTC& dsLTC, char s[10]) {
	for (int i = 0; i < dsLTC.n; ++i) {
		if (strcmp(dsLTC.nodes[i]->MAMH, s) == 0) {
			for (int j = i; j < dsLTC.n - 1; ++j) {
				dsLTC.nodes[j] = dsLTC.nodes[j + 1];
			}
			dsLTC.n--;
			cout << "\n" << kc << "Xoa thanh cong !";
			break;
		}
	}
	return;
}

void delete_LTC(LIST_LTC& dsLTC) {
	char malop[10];
	cout << "\n" << kc << " Nhap ma mon hoc can XOA : ";
	gets_s(malop); uppercase(malop);
	for (int i = 0; i < dsLTC.n; ++i) {
		if (strcmp(dsLTC.nodes[i]->MAMH,malop)==0) {
			LopTinChi* tmp = dsLTC.nodes[i];
			cout << "\n" << kc"Thong tin cu : \n";
			vekhung_LTC();
			cout << setfill(' ');
			print_LTC(tmp);
			vengang_LTC();
			cout << kc;
			int yn = XacNhan("Ban co that su muon xoa khong ? (Y/N)  ");
			if (yn == 1) {
				delete_ltc(dsLTC, dsLTC.nodes[i]->MAMH);
				return;
			}
			else {
				cout << "\n" << kc << "Huy xoa !";
				return;
			}
		}
	}
	cout << "\n" << kc << "Ma mon hoc khong ton tai ! ";
}

void fix_LTC(LIST_LTC& dsLTC, PTRMH& root) {
	LopTinChi* tc;
	tc = new LopTinChi;
	char s[10];
	cout << "\n\t" << kc << "Nhap ma mon hoc chi can CHINH SUA : "; gets_s(s);
	uppercase(s);
	for (int i = 0; i < dsLTC.n; ++i) {
		if (strcmp(dsLTC.nodes[i]->MAMH, s) == 0) {
			LopTinChi* tmp = dsLTC.nodes[i];
			cout << "\n" << kc << "Thong tin cu : \n";
			vekhung_LTC();
			cout << setfill(' ');
			print_LTC(tmp);
			vengang_LTC();
			PTRMH p = CheckTrung(root, dsLTC.nodes[i]->MAMH);
			MonHoc m;
			m.STCLT = p->mh.STCLT;
			m.STCTH = p->mh.STCTH;
			strcpy_s(m.TENMH,p->mh.TENMH);
			delete_dsmh(root,p->mh);
			strcpy_s(dsLTC.nodes[i]->MAMH, "");
			cout << "\n" << kc << "Chinh sua thong tin : \n";
			input_LTC(dsLTC, tc, root, 2);
			strcpy_s(m.MAMH, tc->MAMH);
			add_dsmh(root, m);
			strcpy_s(dsLTC.nodes[i]->MAMH, tc->MAMH);
			strcpy_s(dsLTC.nodes[i]->NIENKHOA, tc->NIENKHOA);
			dsLTC.nodes[i]->HOCKY = tc->HOCKY;
			dsLTC.nodes[i]->NHOM = tc->NHOM;
			dsLTC.nodes[i]->SOSVMIN = tc->SOSVMIN;
			dsLTC.nodes[i]->SOSVMAX = tc->SOSVMAX;
			dsLTC.nodes[i]->HUYLOP = tc->HUYLOP;
			cout << "\n" << kc << "Chinh sua thanh cong !";
			return;
		}
	}
	cout << kc << "Ma mon hoc khong ton tai ! ";
}

void tudong_LTC(LIST_LTC& dsLTC) {
	char nk[10];
	int hk;
	int dem;
	cout << "\n" << kc << "Nhap nien khoa: "; gets_s(nk);
	delete_space(nk);
	cout << "\n" << kc << "Nhap hoc ki: "; cin >> hk;
	for (int i = 0; i < dsLTC.n; ++i) {
		if (strcmp(dsLTC.nodes[i]->NIENKHOA, nk) == 0 && dsLTC.nodes[i]->HOCKY == hk) {
			cin.ignore();
			cout << "\n" << kc;
			int xn = XacNhan("Ban co thuc su muon xoa LTC khong du yeu cau sinh vien khong ? (Y/N)");
			if (xn == 1) {
				for (int i = 0; i < dsLTC.n; ++i) {
					if (strcmp(dsLTC.nodes[i]->NIENKHOA, nk) == 0 && dsLTC.nodes[i]->HOCKY == hk) {
						dem = 0;
						PTRDK p = dsLTC.nodes[i]->FirstDK;
						while (p != NULL) {
							if (p->dky.HUYDANGKY == 0) ++dem;
							p = p->next;
						}
						if (dem < dsLTC.nodes[i]->SOSVMIN) dsLTC.nodes[i]->HUYLOP = 1;
					}
				} cout << "\n" << kc << "Huy lop tin chi thanh cong !";
				return;
			}
		}
	}
	cout << "\n" << kc << "Nien Khoa hoac Hoc ki khong ton tai ! ";
}

void nhapdiem_LTC(LIST_LTC& dsLTC, PTRSV& First) {
	LopTinChi* tc = new LopTinChi;
	cout << "\n\n" << kc << "Ma mon hoc cua lop tin chi can xem: "; gets_s(tc->MAMH);
	uppercase(tc->MAMH);
	if (CheckTrungMaMH(dsLTC, tc->MAMH) == 0) cout << "\nMa mon hoc khong ton tai !";
	else {
		cout << kc << "Nien Khoa: "; gets_s(tc->NIENKHOA);
		cout << kc << "Hoc ki: "; cin >> tc->HOCKY;
		cout << kc << "Nhom: "; cin >> tc->NHOM;
		cin.ignore();
		for (int i = 0; i < dsLTC.n; ++i) {
			if (strcmp(dsLTC.nodes[i]->NIENKHOA, tc->NIENKHOA) == 0 && strcmp(dsLTC.nodes[i]->MAMH, tc->MAMH) == 0
				&& dsLTC.nodes[i]->HOCKY == tc->HOCKY && dsLTC.nodes[i]->NHOM == tc->NHOM && dsLTC.nodes[i]->HUYLOP == 0) {
				PTRDK p = dsLTC.nodes[i]->FirstDK;
				ve1_12();
				ve2_12();
				string a = "";
				int dem = 0;
				while (p != NULL) {
					a += p->dky.MASV;
					cout << kc << char(179) << setw(3) << left << ++dem << char(179);
					cout << setw(15) << left << p->dky.MASV << char(179);
					PTRSV tmp = CheckTrungMSSV(First, p->dky.MASV);
					cout << setw(30) << left << tmp->sv.HO << char(179);
					cout << setw(10) << left << tmp->sv.TEN << char(179);
					cout << setw(6) << left << p->dky.DIEM << char(179);
					ve2_12();
					p = p->next;
				}
			nhaplai:
				char b[15];
				cout << "\n\n" << kc << "Ban muon nhap/hieu chinh diem cua MaSV nao, nhap MASV: "; gets_s(b);
				uppercase(b);
				int found = a.find(b);
				if (found != -1) {
					cout << "\n" << kc << "Nhap diem: ";
					float c;
					cin >> c;
					PTRDK w = CheckTrung_SVDK(dsLTC.nodes[i]->FirstDK, b);
					w->dky.DIEM = c;
					cout << "\n" << kc << "Thay doi diem thanh cong !" << "\n" << kc;
					int xn = XacNhan("Tiep tuc nhap diem ? (Y/N) ");
					if (xn == 1) {
						cin.ignore();
						goto nhaplai;
					}
					else return;
				}
				else {
					cout << "\n" << kc << "Khong ton tai MASV nay trong danh sach, vui long nhap lai !";
					goto nhaplai;
				}
			}
		}
		cout << "\n" << kc << "Khong ton tai lop tin chi hoac lop tin chi da bi huy ! ";
	}
}

int TongSoTinChi(LIST_LTC dsLTC, PTRMH root, char s[15], char nk[10]) {
	int ttc = 0;
	for (int i = 0; i < dsLTC.n; ++i) {
		if (strcmp(dsLTC.nodes[i]->NIENKHOA, nk) == 0 && dsLTC.nodes[i]->HUYLOP == 0) {
			PTRDK p = dsLTC.nodes[i]->FirstDK;
			while (p != NULL) {
				if (strcmp(p->dky.MASV, s) == 0 && p->dky.HUYDANGKY == 0) {
					PTRMH q = CheckTrung(root, dsLTC.nodes[i]->MAMH);
					ttc = ttc + q->mh.STCLT + q->mh.STCTH;
					break;
				}
				p = p->next;
			}
		}
	}
	return ttc;
}

/////////////////////////...DANH SACH DANG KI .../////////////////////////
PTRDK CheckTrung_SVDK(PTRDK& FirstDK, char s[15]) {
	PTRDK p;
	p = FirstDK;
	while (p != NULL) {
		if (strcmp(p->dky.MASV, s) == 0) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

void add_dsdk(PTRDK& FirstDK, DangKy dk) {
	PTRDK p, Last;
	p = new nodeDK;
	p->dky = dk;
	if (FirstDK == NULL) {
		FirstDK = p;
	}
	else {
		for (Last = FirstDK; Last->next != NULL; Last = Last->next);
		Last->next = p;
	}
	p->next = NULL;
}

void Traverse_DSDK(LIST_LTC dsLTC, PTRDK FirstDK, PTRSV First, PTRMH root) {
	LopTinChi* tc = new LopTinChi;
	PTRSV tmp, b;
	b = First;
	tmp = NULL;
	cout << "\n\n" << kc << "Ma mon hoc cua lop tin chi can xem: "; gets_s(tc->MAMH);
	uppercase(tc->MAMH);
	if (CheckTrung(root, tc->MAMH) == NULL) cout << "\nMa mon hoc khong ton tai !";
	else {
		cout << kc << "Nien Khoa: "; gets_s(tc->NIENKHOA);
		cout << kc << "Hoc ki: "; cin >> tc->HOCKY;
		cout << kc << "Nhom: "; cin >> tc->NHOM;
		for (int i = 0; i < dsLTC.n; ++i) {
			if (strcmp(dsLTC.nodes[i]->NIENKHOA, tc->NIENKHOA) == 0 && strcmp(dsLTC.nodes[i]->MAMH, tc->MAMH) == 0 && dsLTC.nodes[i]->HOCKY == tc->HOCKY && dsLTC.nodes[i]->NHOM == tc->NHOM) {
				PTRDK p;
				p = dsLTC.nodes[i]->FirstDK;
				while (p != NULL) {
					if (p->dky.HUYDANGKY == 0) {
						while (b != NULL) {
							if (strcmp(p->dky.MASV, b->sv.MASV) == 0) {
								add_dssv(tmp, b->sv);
								b = First;
								break;
							}
							b = b->next;
						}
					}
					p = p->next;
				}
				if (tmp != NULL) {
					vekhungtren_DSDK(root, tc->MAMH);
					vekhungduoi_DSDK();
					vengang_DSSV();
					Sapxepten(tmp);
					int stt = 0;;
					while (tmp != NULL) {
						cout << setfill(' ');
						cout << "\t" << kc << char(179) << setw(3) << left << ++stt << char(179);
						print_DSSV(tmp);
						vengang_DSSV();
						tmp = tmp->next;
					}
					clearlist(tmp);
					return;
				}
				else {
					cout << "\n" << kc << kc << "Danh sach RONG (chua co sinh vien nao dang ki mon hoc nay) ! ";
					return;
				}
			}
		}
		cout << kc << "Khong ton tai lop tin chi nay ! ";
	}
}

void delete_DSDK(PTRDK& FirstDK, PTRDK p) {
	if (p == FirstDK) {
		FirstDK = p->next;
		delete p;
		p = NULL;
		return;
	}
	PTRDK tmp = FirstDK;
	while (tmp->next != NULL) {
		if (tmp->next == p) {
			PTRDK q = tmp->next;
			tmp->next = q->next;
			delete q;
			q = NULL;
			return;
		}
		tmp = tmp->next;
	}
	if (tmp == p) tmp = NULL;
}

void clearlist_DSDK(PTRDK& First) {
	PTRDK p;
	p = First;
	while (First != NULL) {
		p = First;
		First = First->next;
		delete p;
	}
}

void Dki_huyDki(PTRMH& root, PTRSV& First, PTRDK& FirstDK, LIST_LTC& dsLTC) {
	char s[15];
	PTRSV b;
	LopTinChi* tc = new LopTinChi;
	cout << "\n\n" << kc << "Nhap MSSV: ";
	gets_s(s); uppercase(s);
	if (CheckTrungMSSV(First, s) != NULL) {
		PTRSV tmp = CheckTrungMSSV(First, s);
		cout << "\n" << kc << "Thong tin cu: \n";
		vekhung_DSSV();
		cout << setfill(' ');
		cout << "\t" << kc << char(179) << setw(3) << left << "1" << char(179);
		print_DSSV(tmp);
		vengang_DSSV();
		cout << "\n" << kc << "* LOC LOP TIN CHI *\n\n";
		cout << kc << "Nhap nien Khoa: "; gets_s(tc->NIENKHOA);
		cout << kc << "Nhap hoc ki: "; cin >> tc->HOCKY;
		ve1(); ve2();
		string m = "";
		for (int i = 0; i < dsLTC.n; ++i) {
			if (strcmp(dsLTC.nodes[i]->NIENKHOA, tc->NIENKHOA) == 0 && dsLTC.nodes[i]->HOCKY == tc->HOCKY) {
				m += dsLTC.nodes[i]->MAMH;
				int dem = 0;
				PTRDK a = dsLTC.nodes[i]->FirstDK;
				while (a != NULL) {
					if (a->dky.HUYDANGKY == 0) ++dem;
					a = a->next;
				}
				cout << setfill(' ');
				cout << kc << char(179) << setw(10) << left << dsLTC.nodes[i]->MAMH << char(179);
				PTRMH b = CheckTrung(root, dsLTC.nodes[i]->MAMH);
				cout << setw(50) << left << b->mh.TENMH << char(179);
				cout << setw(6) << left << dsLTC.nodes[i]->NHOM << char(179);
				cout << setw(13) << left << dem << char(179);
				cout << setw(19) << left << dsLTC.nodes[i]->SOSVMAX - dem << char(179);
				ve2();
			}
		}
		char q[15];
		cin.ignore();
	nhaplai:
		cout << "\n" << kc << "Nhap MA MON HOC ban muon dang ki/huy dang ki : "; gets_s(q);
		uppercase(q);
		int found = m.find(q);
		if (found != -1) {
			for (int i = 0; i < dsLTC.n; ++i) {
				if (strcmp(q, dsLTC.nodes[i]->MAMH) == 0) {
					if (CheckTrung_SVDK(dsLTC.nodes[i]->FirstDK, s) != NULL) {
						PTRDK o = CheckTrung_SVDK(dsLTC.nodes[i]->FirstDK, s);
						if (o->dky.HUYDANGKY == 0) {
							cout << "\n" << kc;
							int xn = XacNhan("Ban da DANG KI mon hoc nay, ban co muon HUY DANG KI khong (Y/N) ?");
							if (xn == 1) {
								o->dky.HUYDANGKY = 1;
								cout << "\n" << kc << "Huy dang ki thanh cong ! ";
							}
							else {
								cout << "\n" << kc << "Dang ki thanh cong !";
							}
						}
						else {
							cout << "\n" << kc;
							int xn = XacNhan("Ban da HUY DANG KI mon nay, ban co muon DANG KI khong (Y/N) ?");
							if (xn == 1) {
								o->dky.HUYDANGKY = 0;
								cout << "\n" << kc << "Dang ki thanh cong !";
							}
							else {
								cout << "\n" << kc << "Huy dang ki thanh cong !";
							}
						}
					}
					else {
						cout << "\n" << kc;
						int xn = XacNhan("Ban CHUA DANG KI mon hoc nay, ban co muon DANG KI khong (Y/N) ?");
						if (xn == 1) {
							DangKy r;
							r.HUYDANGKY = 0;
							strcpy_s(r.MASV, tmp->sv.MASV);
							r.DIEM = 0.0;
							add_dsdk(dsLTC.nodes[i]->FirstDK, r);
							cout << "\n" << kc << "Dang ki thanh cong !";
						}
						else {
							cout << "\n" << kc << "Huy dang ki thanh cong !";
						}
					}
					return;
				}

			}

		}
		else {
				cout << "\n" << kc << "Ma mon hoc khong ton tai trong danh sach tren, vui long nhap lai ! \n";
				goto nhaplai;
		}
	}
	else cout << "\n" << kc << "Ma so sinh vien khong ton tai !";
}

/////////////////////////...DANH SACH SINH VIEN...//////////////////////////

bool CheckTrungSDT(PTRSV First, char s[100]) {
	PTRSV p = First;
	while (p != NULL) {
		if (strcmp(p->sv.SDT, s) == 0) return 1;
		p = p->next;
	}
	return 0;
}

SinhVien input_DSSV(PTRSV& First, SinhVien& sv) {
	cout << kc << "Nhap ho : "; gets_s(sv.HO);
	strcpy_s(sv.HO, Chuan_Hoa_Ten(sv.HO));
	cout << kc << "Nhap ten : "; gets_s(sv.TEN);
	strcpy_s(sv.TEN, Chuan_Hoa_Ten(sv.TEN));
	cout << kc << "Gioi tinh : "; gets_s(sv.PHAI);
	strcpy_s(sv.PHAI, Chuan_Hoa_Ten(sv.PHAI));
	nhaplai:
	cout << kc << "So dien thoai: "; gets_s(sv.SDT);
	if (checkSDT(sv.SDT)==0) {
			cout << kc << "So dien thoai khong hop le, vui long nhap lai: \n";
			goto nhaplai;
	}
	if (CheckTrungSDT(First, sv.SDT) == 1) {
		cout << kc << "So dien thoai bi trung, vui long nhap lai: \n";
		goto nhaplai;
	}
	return sv;
}


PTRSV CheckTrungMSSV(PTRSV First, char s[15]) {
	PTRSV p;
	p = First;
	while (p != NULL) {
		if (strcmp(p->sv.MASV, s) == 0) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

void add_dssv(PTRSV& First, SinhVien sv) {
	PTRSV p, Last;
	p = new nodeSV;
	p->sv = sv;
	if (First == NULL) {
		First = p;
	}
	else {
		for (Last = First; Last->next != NULL; Last = Last->next);
		Last->next = p;
	}
	p->next = NULL;
}

void ADD_DSSV(PTRSV& First) {
	SinhVien sv;
	cout << "\n" << kc << "\t Nhap thong tin can THEM : ";
	cout << "\n" << kc << "Nhap ma lop : ";
	gets_s(sv.MALOP);
	uppercase(sv.MALOP);
	int i = 1;
	do {
		cout << kc << "Nhap MSSV : "; gets_s(sv.MASV);
		if (sv.MASV[0] == '\0') return;
		uppercase(sv.MASV);
		if (CheckTrungMSSV(First, sv.MASV) != NULL) {
			cout << kc << "MSSV da ton tai, nhap lai: \n";
			continue;
		}
		i++;
	} while (i == 1);
	input_DSSV(First, sv);
	add_dssv(First, sv);
	cout << kc << "Them vao danh sach sinh vien thanh cong ! ";
}

void Create_DSSV(PTRSV& First) {
	SinhVien sv;
	char s[15];
	cout << "\n" << kc << "Nhap ma lop: ";
	gets_s(s);
	uppercase(s);
	do {
		strcpy_s(sv.MALOP, s);
		cout << kc << "Nhap MSSV : "; gets_s(sv.MASV);
		if (sv.MASV[0] == '\0') return;
		uppercase(sv.MASV);
		if (CheckTrungMSSV(First, sv.MASV) != NULL) {
			cout << kc << "MSSV da ton tai, nhap lai: \n";
			continue;
		}
		input_DSSV(First, sv);
		add_dssv(First, sv);
	} while (1);
}

void Sapxepten(PTRSV& First) {
	PTRSV p, q, pmin;
	SinhVien min;
	for (p = First; p->next != NULL; p = p->next) {
		min = p->sv;
		pmin = p;
		for (q = p->next; q != NULL; q = q->next) {
			if (strcmp(min.TEN, q->sv.TEN) == 1) {
				min = q->sv;
				pmin = q;
			}
			else if (strcmp(min.TEN, q->sv.TEN) == 0) {
				if (strcmp(min.HO, q->sv.HO) == 1) {
					min = q->sv;
					pmin = q;
				}
			}
		}
		pmin->sv = p->sv;
		p->sv = min;
	}
}

void print_DSSV(PTRSV p) {
	cout << setw(14) << left << p->sv.MALOP << char(179);
	cout << setw(14) << left << p->sv.MASV << char(179);
	cout << setw(19) << left << p->sv.HO << char(179);
	cout << setw(9) << left << p->sv.TEN << char(179);
	cout << setw(9) << left << p->sv.PHAI << char(179);
	cout << setw(10) << left << p->sv.SDT << char(179);
}

PTRSV checkLOP(PTRSV First, char sv[15], char ml[15]) {
	PTRSV p;
	p = First;
	while (p != NULL) {
		if (strcmp(p->sv.MALOP, ml) == 0 && strcmp(p->sv.MASV, sv) == 0) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

void clearlist(PTRSV& First) {
	PTRSV p;
	p = First;
	while (First != NULL) {
		p = First;
		First = First->next;
		delete p;
	}
}

void Traverse_DSSV(PTRSV First, char s[15]) {
	PTRSV p, tmp;
	tmp = NULL;
	int stt = 0;
	p = First;
	if (p == NULL) {
		cout << "\n    (Khong co sinh vien trong danh sach)";
		return;
	}
	while (p != NULL) {
		if (strcmp(p->sv.MALOP, s) == 0) add_dssv(tmp, p->sv);
		p = p->next;
	}
	if (tmp == NULL) {
		cout << "\n    (Khong co sinh vien trong danh sach)";
		return;
	}
	else {
		Sapxepten(tmp);
		vekhung_DSSV();
		while (tmp != NULL) {
			cout << setfill(' ');
			cout << "\t" << kc << char(179) << setw(3) << left << ++stt << char(179);
			print_DSSV(tmp);
			vengang_DSSV();
			tmp = tmp->next;
		}
	}
	clearlist(tmp);
}

void delete_DSSV(PTRSV& First, LIST_LTC& dsLTC) {
	SinhVien sv;
	PTRSV p, tmp;
	p = First;
	char s[15];
	int a = 1;
	cout << "\n" << kc << "Nhap ma so sinh vien can XOA : ";
	gets_s(s);
	uppercase(s);
	while (p->next != NULL) {
		if (a == 1 && strcmp(First->sv.MASV, s) == 0) {
			tmp = First;
			a++;
			goto nhaplai;
		}
		if (strcmp(p->next->sv.MASV, s) == 0) {
			tmp = p->next;
		nhaplai:
			cout << "\n" << kc << "Thong tin cu : \n";
			vekhung_DSSV();
			cout << setfill(' ');
			cout << "\t" << kc << char(179) << setw(3) << "0" << char(179);
			print_DSSV(tmp);
			vengang_DSSV();
			cout << kc;
			int yn = XacNhan("Ban co that su muon xoa khong ? (Y/N)  ");
			if (yn == 1) {
				if (p == First) {
					First = p->next;
					delete p;
					p = NULL;
				}
				else if (p->next->next == NULL) {
					p->next = NULL;
				}
				else {
					PTRSV q = p->next;
					p->next = q->next;
					delete q;
					q = NULL;
				}
				for (int i = 0; i < dsLTC.n; ++i) {
					PTRDK p = dsLTC.nodes[i]->FirstDK;
					while (p != NULL) {
						if (strcmp(p->dky.MASV, s) == 0) {
							delete_DSDK(dsLTC.nodes[i]->FirstDK, p);
							break;
						}
						p = p->next;
					}
				}
				cout << "\n" << kc << " Xoa thanh cong !";
				return;
			}
			else {
				cout << "\n" << kc << "Huy xoa !";
				return;
			}
		}
		p = p->next;
	}
	cout << kc << "Ma so sinh vien khong ton tai ! ";
}

void fix_DSSV(PTRSV& First, LIST_LTC& dsLTC) {
	SinhVien sv;
	PTRSV p;
	p = First;
	char s[15];
	cout << "\n" << kc << "Nhap ma so sinh vien can CHINH SUA : ";
	gets_s(s);
	uppercase(s);
	while (p != NULL) {
		if (strcmp(p->sv.MASV, s) == 0) {
			cout << "\n" << kc << "Thong tin cu : \n";
			vekhung_DSSV();
			cout << setfill(' ');
			cout << "\t" << kc << char(179) << setw(3) << "0" << char(179);
			print_DSSV(p);
			vengang_DSSV();
			strcpy_s(p->sv.MASV, "");
			cout << "\n" << kc << "Chinh sua thong tin : \n";
			cout << kc << "Nhap ma lop :"; gets_s(p->sv.MALOP);
			uppercase(p->sv.MALOP);
			cout << kc << "Nhap MSSV : "; gets_s(sv.MASV);
			uppercase(sv.MASV);
			if (CheckTrungMSSV(First, sv.MASV) != NULL) {
				do {
					cout << kc << "MSSV da ton tai, nhap lai:";
					gets_s(sv.MASV);
					uppercase(sv.MASV);
				} while (CheckTrungMSSV(First, sv.MASV) != NULL);
			}
			for (int i = 0; i < dsLTC.n; ++i) {
				PTRDK p = dsLTC.nodes[i]->FirstDK;
				while (p != NULL) {
					if (strcmp(p->dky.MASV, s) == 0) {
						strcpy_s(p->dky.MASV, sv.MASV);
						break;
					}
					p = p->next;
				}
			}
			strcpy_s(p->sv.MASV, sv.MASV);
			input_DSSV(First, p->sv);
			cout << "\n" << kc << "Chinh sua thanh cong !";
			return;
		}
		else p = p->next;
	}
	cout << "\n" << kc << "Ma so sinh vien khong ton tai !";
}

//DANH SACH MON HOC...

MonHoc input_DSMH(PTRMH& root, MonHoc& mh) {
	cout << kc << "Nhap ten mon hoc: "; gets_s(mh.TENMH);
	strcpy_s(mh.TENMH, Chuan_Hoa_Ten(mh.TENMH));
	cout << kc << "Nhap so tin chi ly thuyet: "; cin >> mh.STCLT;
	cout << kc << "Nhap so tin chi thuc hanh: "; cin >> mh.STCTH;
	cin.ignore();
	return mh;
}

PTRMH newNode(PTRMH& p, MonHoc b) {
	p = new nodeMH;
	p->mh = b;
	p->left = NULL;
	p->right = NULL;
	p->height = 1;
	return p;
}

PTRMH rightRotate(PTRMH y) {
	PTRMH x = y->left;
	PTRMH T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = max(height(y->left),
		height(y->right)) +
		1;
	x->height = max(height(x->left),
		height(x->right)) +
		1;
	return x;
}

PTRMH leftRotate(PTRMH x) {
	PTRMH y = x->right;
	PTRMH T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	return y;
}

int height(PTRMH N) {
	if (N == NULL)
		return 0;
	return N->height;
}

int getBalanceFactor(PTRMH N) {
	if (N == NULL)
		return 0;
	return height(N->left) -
		height(N->right);
}

PTRMH nodeWithMimumValue(PTRMH node) {
	PTRMH current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

PTRMH CheckTrung(PTRMH root, char a[10]) {
	PTRMH p, q;
	p = root;
	while (p != NULL) {
		int x = strcmp(a, p->mh.MAMH);
		if (x == 0) return p; // bi trung khoa
		if (x == -1) q = p->left;
		else q = p->right;
		p = q; //dieu kien de chay
	}
	return NULL;
}

void add_dsmh(PTRMH& root, MonHoc b) {
	if (root == NULL) root = newNode(root, b);
	else {
		PTRMH p = root;
		int x = strcmp(b.MAMH, root->mh.MAMH);
		if (x == -1) add_dsmh(root->left, b);
		else add_dsmh(root->right, b);
		root->height = 1 + max(height(root->left), height(root->right));
		int balanceFactor = getBalanceFactor(root);
		if (balanceFactor > 1) { //lech phai
			if (strcmp(b.MAMH, root->mh.MAMH) == -1) { //vi du 
				root = rightRotate(root);
				return;
			}
			else {
				root->left = leftRotate(root->left);
				root = rightRotate(root);
				return;
			}
		}
		if (balanceFactor < -1) {//lech trai
			if (strcmp(b.MAMH, root->mh.MAMH) == 1) {  //
				root = leftRotate(root);
				return;
			}
			else {
				root->right = rightRotate(root->right);
				root = leftRotate(root);
				return;
			}
		}
	}
}

void ADD_DSMH(PTRMH& root) {
	MonHoc a;
nhaplai:
	cout << endl << kc << "Nhap ma mon hoc: ";
	gets_s(a.MAMH);
	uppercase(a.MAMH);
	if (CheckTrung(root, a.MAMH) != NULL) {
		cout << kc << "Ma mon hoc bi trung, vui long nhap lai !\n";
		goto nhaplai;
	}
	input_DSMH(root, a);
	add_dsmh(root, a);
	cout << kc << "Them mon hoc thanh cong ! ";
}

void delete_dsmh(PTRMH& root, MonHoc b) {
	PTRMH p = root;
	int x = strcmp(b.MAMH, root->mh.MAMH);
	if (x == -1) delete_dsmh(root->left, b);
	else if (x == 1) delete_dsmh(root->right, b);
	else { //key=root->key 
		if ((root->left == NULL) || (root->right == NULL)) {
			PTRMH temp = root->left ? root->left : root->right; //la root->left neu dung thi root->left sai thi root->right (bang cai nao !=null)
			if (temp == NULL) {
				temp = root;
				root = NULL;
			}
			else
				root = temp;
		}
		else {
			PTRMH temp = nodeWithMimumValue(root->right);//cay la nho nhat ben trai
			root->mh = temp->mh; 
			delete_dsmh(root->right, temp->mh);
		}
	}
	if (root == NULL)
		return;
	root->height = 1 + max(height(root->left), height(root->right));
	int balanceFactor = getBalanceFactor(root);
	if (balanceFactor > 1) {
		if (getBalanceFactor(root->left) >= 0) { //bi lech trai trai
			root = rightRotate(root);
			return;
		}
		else {
			root->left = leftRotate(root->left);
			root = rightRotate(root);
			return;
		}
	}
	if (balanceFactor < -1) {
		if (getBalanceFactor(root->right) <= 0) {
			root = leftRotate(root);
			return;
		}
		else {
			root->right = rightRotate(root->right);
			root = leftRotate(root);
			return;
		}
	}
}
void delete_DSMH(PTRMH& root, LIST_LTC& dsLTC) {
	char s[15];
	int a = 1;
	cout << "\n" << kc << "Nhap ma mon hoc can XOA : ";
	gets_s(s);
	uppercase(s);
	if (CheckTrung(root, s) != NULL) {
		PTRMH tmp = CheckTrung(root, s);
		cout << "\n" << kc << "Thong tin cu : \n";
		vekhung_DSMH();
		print_DSMH(tmp);
		cout << "\n" << kc;
		int yn = XacNhan("Ban co that su muon xoa khong ? (Y/N)  ");
		if (yn == 1) {
			delete_dsmh(root, tmp->mh);
			for (int i = 0; i < dsLTC.n; ++i) {
				if (strcmp(dsLTC.nodes[i]->MAMH, s) == 0) {
					delete_ltc(dsLTC, dsLTC.nodes[i]->MAMH);
					break;
				}
			}
		}
		else cout << "\n" << kc << "Huy xoa !";
	}
	else cout << "\n" << kc << "Ma mon hoc khong ton tai !";
}

int mh = 0;
void print_DSMH(PTRMH p) {
	cout << setfill(' ');
	cout << kc << char(179) << setw(3) << left << ++mh << char(179);
	cout << setw(10) << left << p->mh.MAMH << char(179);
	cout << setw(50) << left << p->mh.TENMH << char(179);
	cout << setw(5) << left << p->mh.STCLT << char(179);
	cout << setw(5) << left << p->mh.STCTH << char(179);
	vengang_DSMH();
}

void Traverse_DSMH(PTRMH root) { //duyet trung tu
	if (root != NULL) {
		Traverse_DSMH(root->left);
		print_DSMH(root);
		Traverse_DSMH(root->right);
	}
}

void fix_DSMH(PTRMH& root, LIST_LTC& dsLTC) { //CHINH SUA MA MON HOC THI MA MON HOC CUA LOP TIN CHI CUNG SE BI CHINH SUA THEO
	char s[10];
	cout << "\n" << kc << "Nhap ma mon hoc can CHINH SUA : ";
	gets_s(s);
	uppercase(s);
	PTRMH p, q;
	p = root;
	while (p != NULL) {
		int x = strcmp(s, p->mh.MAMH);
		if (x == 0) { // bi trung khoa
			cout << kc << "Thong tin cu: ";
			vekhung_DSMH();
			print_DSMH(p);
			delete_dsmh(root, p->mh);
			cout << "\n" << kc << "Chinh sua thong tin ";
			MonHoc a;
		nhaplai:
			cout << endl << kc << "Nhap ma mon hoc: ";
			gets_s(a.MAMH);
			uppercase(a.MAMH);
			if (CheckTrung(root, a.MAMH) != NULL) {
				cout << kc << "Ma mon hoc bi trung, vui long nhap lai !\n";
				goto nhaplai;
			}
			input_DSMH(root, a);
			add_dsmh(root, a);
			for (int i = 0; i < dsLTC.n; ++i) {
				if (strcmp(dsLTC.nodes[i]->MAMH, s) == 0) {
					strcpy_s(dsLTC.nodes[i]->MAMH, a.MAMH);
					break;
				}
			}
			cout << "\n" << kc << "Chinh sua thanh cong !";
			return;
		}
		if (x == -1) q = p->left;
		else q = p->right;
		p = q; //dieu kien de chay
	}
	cout << kc << "\n Ma mon hoc khong ton tai. ";
}

/////////////////....DOC FILE...////////////

int DocFile_LTC(char* duongDan, LIST_LTC& dsLTC) {
	ifstream f(duongDan);
	if (!f) return 0;
	string data;
	while (getline(f, data)) {
		LopTinChi* tc = new LopTinChi();
		int n = data.length();
		string d = "";
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			if (data[i] == ',') {
				switch (cnt) {
				case 0:
					tc->MALOPTC = dsLTC.n + 1;
					break;
				case 1:
					strcpy_s(tc->MAMH, d.c_str());
					break;
				case 2:
					strcpy_s(tc->NIENKHOA, d.c_str());
					break;
				case 3:
					tc->HOCKY = stoi(d);
					break;
				case 4:
					tc->NHOM = stoi(d);
					break;
				case 5:
					tc->SOSVMIN = stoi(d);
					break;
				case 6:
					tc->SOSVMAX = stoi(d);
					break;
				case 7:
					tc->HUYLOP = stoi(d);
					break;
				case 8:
					int b = 0;
					while (getline(f, data)) {
						int m = data.length();
						PTRDK p = new nodeDK;
						string a = "";
						int mo = 0;
						for (int i = 0; i < m; ++i) {
							if (data[i] == ',') {
								switch (mo) {
								case 0:
									strcpy_s(p->dky.MASV, a.c_str());
									break;
								case 1:
									p->dky.DIEM = stoi(a);
									break;
								case 2:
									p->dky.HUYDANGKY = stoi(a);
									break;
								case 3:
									b++;
									break;
								}
								mo++;
								a = "";
							}
							else {
								a += data[i];
							}
						}
						add_dsdk(tc->FirstDK, p->dky);
						if (b != 0) break;
					}
				}
				cnt++;
				d = "";
			}
			else {
				d += data[i];
			}
		}
		dsLTC.nodes[dsLTC.n] = tc;
		dsLTC.n++;
	}
	f.close();
	return 1;
}

int DocFile_DSSV(char* duongDan, PTRSV& First) {
	ifstream f(duongDan);
	if (!f) return 0;
	string data;
	while (getline(f, data)) {
		PTRSV p = new nodeSV;
		int n = data.length();
		string d = "";
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			if (data[i] == ',') {
				switch (cnt) {
				case 0:
					strcpy_s(p->sv.MALOP, d.c_str());
					break;
				case 1:
					strcpy_s(p->sv.MASV, d.c_str());
					break;
				case 2:
					strcpy_s(p->sv.HO, d.c_str());
					break;
				case 3:
					strcpy_s(p->sv.TEN, d.c_str());
					break;
				case 4:
					strcpy_s(p->sv.PHAI, d.c_str());
					break;
				case 5:
					strcpy_s(p->sv.SDT, d.c_str());
					break;
				}
				cnt++;
				d = "";
			}
			else {
				d += data[i];
			}
		}
		add_dssv(First, p->sv);
	}
	f.close();
	return 1;
}

int DocFile_DSMH(char* duongDan, PTRMH& root) {
	ifstream f(duongDan);
	if (!f) return 0;
	string data;
	while (getline(f, data)) {
		PTRMH p = new nodeMH;
		int n = data.length();
		string d = "";
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			if (data[i] == ',') {
				switch (cnt) {
				case 0:
					strcpy_s(p->mh.MAMH, d.c_str());
					break;
				case 1:
					strcpy_s(p->mh.TENMH, d.c_str());
					break;
				case 2:
					p->mh.STCLT = stoi(d);
					break;
				case 3:
					p->mh.STCTH = stoi(d);
					break;
				}
				cnt++;
				d = "";
			}
			else {
				d += data[i];
			}
		}
		add_dsmh(root, p->mh);
	}
	f.close();
	return 1;
}

///////////////////...GHI FILE...////////////////

int GhiFile_LTC(char* duongDan, LIST_LTC& dsLTC) {
	ofstream f(duongDan);
	if (!f) return 0;
	for (int i = 0; i < dsLTC.n; ++i) {
		f << "0," << dsLTC.nodes[i]->MAMH << "," << dsLTC.nodes[i]->NIENKHOA << ",";
		f << dsLTC.nodes[i]->HOCKY << "," << dsLTC.nodes[i]->NHOM << "," << dsLTC.nodes[i]->SOSVMIN << ",";
		f << dsLTC.nodes[i]->SOSVMAX << "," << dsLTC.nodes[i]->HUYLOP << ",0," << endl;
		PTRDK p = dsLTC.nodes[i]->FirstDK;
		while (p->next != NULL) {
			f << p->dky.MASV << "," << p->dky.DIEM << "," << p->dky.HUYDANGKY << ",\n";
			p = p->next;
		}
		f << p->dky.MASV << "," << p->dky.DIEM << "," << p->dky.HUYDANGKY << ",2,\n";
	}
	f.close();
	return 1;
}


int GhiFile_DSSV(char* duongDan, PTRSV& First) {
	ofstream f(duongDan);
	if (!f) return 0;
	PTRSV p = First;
	while (p != NULL) {
		f << p->sv.MALOP << "," << p->sv.MASV << "," << p->sv.HO << "," << p->sv.TEN << "," << p->sv.PHAI << "," << p->sv.SDT << "," << endl;
		p = p->next;
	}
	f.close();
	return 1;
}


void GhiFile_DSMH_LNR(PTRMH root, ofstream& f) {
	if (root != NULL) {
		GhiFile_DSMH_LNR(root->left, f);
		f << root->mh.MAMH << "," << root->mh.TENMH << "," << root->mh.STCLT << "," << root->mh.STCTH << "," << endl;
		GhiFile_DSMH_LNR(root->right, f);
	}
}

int GhiFile_DSMH(char* duongDan, PTRMH root) {
	ofstream f(duongDan);
	if (!f) return 0;
	GhiFile_DSMH_LNR(root, f);
	return 1;
}

/////////////////////////...BANG DIEM.../////////////////////////

void bangdiem(LIST_LTC dsLTC, PTRSV First, PTRMH root) {
	LopTinChi* tc = new LopTinChi;
	cout << "\n\n" << kc << "Ma mon hoc cua lop tin chi can xem: "; gets_s(tc->MAMH);
	uppercase(tc->MAMH);
	if (CheckTrungMaMH(dsLTC, tc->MAMH) == NULL) cout << "\n" << kc << "Ma mon hoc khong ton tai !";
	else {
		cout << kc << "Nien Khoa: "; gets_s(tc->NIENKHOA);
		cout << kc << "Hoc ki: "; cin >> tc->HOCKY;
		cout << kc << "Nhom: "; cin >> tc->NHOM;
		cin.ignore();
		for (int i = 0; i < dsLTC.n; ++i) {
			if (strcmp(dsLTC.nodes[i]->NIENKHOA, tc->NIENKHOA) == 0 && strcmp(dsLTC.nodes[i]->MAMH, tc->MAMH) == 0
				&& dsLTC.nodes[i]->HOCKY == tc->HOCKY && dsLTC.nodes[i]->NHOM == tc->NHOM && dsLTC.nodes[i]->HUYLOP == 0) {
				PTRDK p = dsLTC.nodes[i]->FirstDK;
				PTRMH d = CheckTrung(root, dsLTC.nodes[i]->MAMH);
				cout << "\n" << kc << "            BANG DIEM MON HOC " << d->mh.TENMH << "\n";
				cout << "\n" << kc << "            Nien khoa: " << dsLTC.nodes[i]->NIENKHOA << " " << "Hoc ky: " << dsLTC.nodes[i]->HOCKY << " " << "Nhom: " << dsLTC.nodes[i]->NHOM << "\n";
				ve1_12();
				ve2_12();
				string a = "";
				int dem = 0;
				while (p != NULL) {
					if (p->dky.HUYDANGKY == 0) {
						a += p->dky.MASV;
						cout << kc << char(179) << setw(3) << left << ++dem << char(179);
						cout << setw(15) << left << p->dky.MASV << char(179);
						PTRSV tmp = CheckTrungMSSV(First, p->dky.MASV);
						cout << setw(30) << left << tmp->sv.HO << char(179);
						cout << setw(10) << left << tmp->sv.TEN << char(179);
						cout << setw(6) << left << p->dky.DIEM << char(179);
						ve2_12();
					}
					p = p->next;
				}
				return;
			}
		}
		cout << "\n" << kc << "Khong ton tai lop tin chi hoac lop tin chi da bi huy ! ";
		return;
	}
}

void Traverse_KhoaHoc(LIST_LTC dsLTC, PTRSV First, PTRMH root) {
nhaplai:
	char ml[15];
	cout << "\n" << kc << "Nhap ma lop: "; gets_s(ml); uppercase(ml);
	char nk[10];
	PTRDK tmp = NULL;
	cout << "\n" << kc << "Nhap nien khoa: "; gets_s(nk); delete_space(nk);
	for (int i = 0; i < dsLTC.n; ++i) {
		if (strcmp(dsLTC.nodes[i]->NIENKHOA, nk) == 0 && dsLTC.nodes[i]->HUYLOP == 0) {
			PTRDK p = dsLTC.nodes[i]->FirstDK;
			while (p != NULL) {
				if (checkLOP(First, p->dky.MASV, ml) != NULL) {
					if (p->dky.HUYDANGKY == 0) {
						PTRMH q = CheckTrung(root, dsLTC.nodes[i]->MAMH);
						int stc = q->mh.STCLT + q->mh.STCTH;
						if (CheckTrung_SVDK(tmp, p->dky.MASV) != NULL) {
							PTRDK r = CheckTrung_SVDK(tmp, p->dky.MASV);
							r->dky.DIEM = r->dky.DIEM + (p->dky.DIEM * stc);
						}
						else {
							DangKy e;
							e = p->dky;
							e.DIEM *= stc;
							add_dsdk(tmp, e);
						}
					}
				}
				p = p->next;
			}
		}
	}
	int stt = 0;
	PTRSV t = First;
	if (tmp != NULL) {
		cout << "\n" << kc << kc << "BANG THONG KE DIEM TRUNG BINH KHOA HOC\n";
		cout << kc << kc << "     " << "LOP: " << ml;
		ve1_13();
		ve2_13();
		while (t != NULL) {
			if (strcmp(t->sv.MALOP, ml) == 0) {
				cout << kc << char(179) << setw(3) << left << ++stt << char(179);
				cout << setw(15) << left << t->sv.MASV << char(179);
				cout << setw(30) << left << t->sv.HO << char(179);
				cout << setw(10) << left << t->sv.TEN << char(179);
				PTRDK mo = CheckTrung_SVDK(tmp, t->sv.MASV);
				if (mo != NULL) {
					int ttc = TongSoTinChi(dsLTC, root, t->sv.MASV, nk);//tong tin chi
					cout << setw(9) << left << fixed << setprecision(1) << mo->dky.DIEM / ttc << char(179);
					ve2_13();
				}
				else {
					cout << setw(9) << left << "Rong" << char(179);
					ve2_13();
				}
			}
			t = t->next;
		}
		cout << "\n\n" << kc << "*Chu thich: ";
		cout << "\n" << kc << "*Rong : SINH VIEN KHONG DANG KI MON NAO O NIEN KHOA NAY ! ";
		return;
	}
	else {
		cout << "\n\n" << kc << "Ma lop hoac nien khoa khong ton tai, vui long nhap lai: ";
		goto nhaplai;
	}
}

void Traverse_TongKet(LIST_LTC dsLTC, PTRSV First, PTRMH root) {
	char nk[10], ml[15];
	int dem = 0; //dem so lop tc;
nhaplai:
	cout << "\n " << kc << "Nhap ma lop : "; gets_s(ml); uppercase(ml);
	cout << "\n " << kc << "Nhap nien khoa: "; gets_s(nk); uppercase(nk);
	string s = "";
	for (int i = 0; i < dsLTC.n; ++i) {
		if (strcmp(dsLTC.nodes[i]->NIENKHOA, nk) == 0 && dsLTC.nodes[i]->HUYLOP == 0) {
			PTRDK p = dsLTC.nodes[i]->FirstDK;
			while (p != NULL) {
				if (checkLOP(First, p->dky.MASV, ml) != NULL && p->dky.HUYDANGKY == 0) {
					dem++;
					s = s + to_string(dem) + dsLTC.nodes[i]->MAMH + " ";
					break;
				}
				p = p->next;
			}
		}
	}
	if (s.length() != 0) {
		cout << "\n" << kc << kc << "BANG DIEM TONG KET";
		cout << "\n" << kc << kc << " LOP: " << ml;
		ve1_14();
		ve11_14(dem);
		ve2_14();
		ve22_14(dem, s);
		ve3_14();
		ve33_14(dem);
		PTRSV p = First;
		int stt = 0;
		while (p != NULL) {
			cout << setfill(' ');
			if (strcmp(p->sv.MALOP, ml) == 0) {
				cout << kc << char(179) << setw(3) << left << ++stt << char(179);
				cout << setw(15) << left << p->sv.MASV << char(179);
				cout << setw(strlen(p->sv.HO) + 1) << left << p->sv.HO;
				cout << setw(40 - strlen(p->sv.HO) - 1) << left << p->sv.TEN << char(179);
				int z = dem;
				string z1 = s;
				while (z--) {
					int found = z1.find(" ");
					string tmp = z1.substr(1, found - 1);
					for (int i = 0; i < dsLTC.n; ++i) {
						if (strcmp(dsLTC.nodes[i]->MAMH, tmp.c_str()) == 0) {
							PTRDK l = CheckTrung_SVDK(dsLTC.nodes[i]->FirstDK, p->sv.MASV);
							if (l == NULL || l->dky.HUYDANGKY == 1) cout << setw(10) << left << " Khong DK " << char(179);
							else cout << "     " << setw(5) << left << l->dky.DIEM << char(179);
							break;
						}
					}
					z1.erase(0, found + 1);
				}
				cout << endl;
				ve3_14();
				ve33_14(dem);
			}
			p = p->next;
		}
	}
	else {
		cout << "\n" << kc << "Ma lop hoac nien khoa khong ton tai, vui long nhap lai !\n";
		goto nhaplai;
	}
}

int main() {
	system("Color 2");
	PTRMH root = NULL;
	LIST_LTC dsLTC;
	PTRSV FirstSV = NULL;
	PTRDK FirstDK = NULL;
	DangKy dk;
	SinhVien sv;
	MonHoc h;
	int chucnang;
	LopTinChi tc;
	//tc = new LopTinChi;
	char fileLTC[] = "LTC.txt";
	char fileDSSV[] = "DSSV.txt";
	char fileDSMH[] = "DSMH.txt";
	DocFile_LTC(fileLTC, dsLTC);
	DocFile_DSSV(fileDSSV, FirstSV);
	DocFile_DSMH(fileDSMH, root);
	do {
		system("cls");
		chucnang = menu();
		system("cls");
		cin.ignore();
		switch (chucnang) {
		case 1:
		{	
			char n;
			do {
				system("cls");
				cout << "\n\n" << kc << "\t* CAP NHAP DANH SACH LOP TIN CHI *\n";
				cout << "\n" << kc << "Ban muon THEM(1),XOA(2) hay CHINH SUA(3) ?";
				cout << "\n" << kc << "vui long nhap 1 hoac 2 hoac 3: ";
				n = _getche();
			} while (n < '1' || n > '3');
			if (n == '1') {
				ADD_LTC(dsLTC, root);
				_getch();
				break;
			}
			else if (n == '2') {
				delete_LTC(dsLTC);
				_getche();
				break;
			}
			else if (n == '3') {
				fix_LTC(dsLTC, root);
				_getche();
				break;
			}
		}
		case 2:
		{
			char n;
			do {
				system("cls");
				cout << "\n\n" << kc << "\t* CAP NHAP DANH SACH SINH VIEN *\n";
			cout << "\n" << kc << "Ban muon THEM(1),XOA(2), CHINH SUA(3) hay TAO LOP(4) ?";
				cout << "\n" << kc << "vui long nhap 1 hoac 2 hoac 3 hoac 4: ";
				n = _getche();
			} while (n < '1' || n > '4');
			if (n == '1') {
				ADD_DSSV(FirstSV);
				_getch();
				break;
			}
			else if (n == '2') {
				delete_DSSV(FirstSV, dsLTC);
				_getche();
				break;
			}
			else if (n == '3') {
				fix_DSSV(FirstSV, dsLTC);
				_getche();
				break;
			}
			else if (n == '4') {
				Create_DSSV(FirstSV);
				_getche();
				break;
			}
		}
		case 3:
		{
			
			char n;
			do {
				system("cls");
				cout << "\n\n" << kc << "\t* CAP NHAP DANH SACH MON HOC *\n";
			cout << "\n" << kc << "Ban muon THEM(1),XOA(2) hay CHINH SUA(3) ?";
				cout << "\n" << kc << "vui long nhap 1 hoac 2 hoac 3: ";
				n = _getche();
			} while (n < '1' || n > '3');
			if (n == '1') {
				ADD_DSMH(root);
				_getch();
				break;
			}
			else if (n == '2') {
				delete_DSMH(root, dsLTC);
				_getche();
				break;
			}
			else if (n == '3') {
				fix_DSMH(root, dsLTC);
				_getche();
				break;
			}
		}
		case 4:
		{
			Traverse_LTC(dsLTC);
			_getch();
			break;
		}
		case 5:
		{
			Traverse_DSDK(dsLTC, FirstDK, FirstSV, root);
			_getch();
			break;
		}
		case 6:
		{
			cout << "\n\n" << kc << "Nhap danh sanh lop (Ma lop) muon xem: ";
			char s[15];
			gets_s(s);
			uppercase(s);
			Traverse_DSSV(FirstSV, s);
			_getch();
			break;
		}
		case 7:
		{
			if (root == NULL) {
				cout << "\n\n" << kc << "(danh sach rong)";
				_getch();
				break;
			}
			else {
				vekhung_DSMH();
				Traverse_DSMH(root);
				mh = 0;
				_getch();
				break;
			}
		}
		case 8:
		{
			bangdiem(dsLTC, FirstSV, root);
			_getche();
			break;
		}
		case 9:
		{
			cout << "\n" << kc << "* DANG KI/HUY DANG KI *\n";
			Dki_huyDki(root, FirstSV, FirstDK, dsLTC);
			_getche();
			break;
		}
		case 10:
		{
			cout << "\n" << kc << "* HUY LOP TIN CHI TU DONG *\n";
			tudong_LTC(dsLTC);
			_getche();
			break;
		}
		case 11:
		{
			cout << "\n" << kc << "* NHAP DIEM/HIEU CHINH DIEM *\n";
			nhapdiem_LTC(dsLTC, FirstSV);
			_getche();
			break;
		}
		case 12:
		{
			Traverse_KhoaHoc(dsLTC, FirstSV, root);
			_getche();
			break;
		}
		case 13:
		{
			Traverse_TongKet(dsLTC, FirstSV, root);
			_getche();
			break;
		}
		}
	} while (chucnang != 0);
	char ex[] = "LTCex.txt";
	char ex1[] = "DSSVex.txt";
	char ex2[] = "DSMHex.txt";
	GhiFile_LTC(ex, dsLTC);
	GhiFile_DSSV(ex1, FirstSV);
	GhiFile_DSMH(ex2, root);
}