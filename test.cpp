#include <bits/stdc++.h>
#include <Windows.h>
#include <conio.h>
#include "mylibrary.h"
#include <string>
using namespace std;
const int ENTER = 13;
const int ESC = 27;
const int F1 = 59;
const int F2 = 60;
const int F3 = 61;
const int F5 = 63;
const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int BACKSPACE = 8;
const int KEY_DELETE = 83;

const int HOVER_COLOR = 55; 
const int NOMAR_COLOR = 241; 
const int MEMU_LEFT = 42; 
const int MEMU_RIGHT = 57;

const int CHIEU_DOC = 15; 

	
DSMH dsmh;
DsLOP dslop;
DSSV dssv;
DSSVDK dssvdk;
int global_var;
string Menu[5] = {"1.Quan Ly Lop", "2.Quan Ly Sinh Vien","3. Quan Ly Mon Hoc"," 4.Quan Ly Diem", "5.Sinh vien theo LOPTC"};

string text[5][10] = {
	{"MALOPTC", "MAMH", "NIEN KHOA", "HOC KY", "NHOM", "SVMIN","SVMAX"},
	{ "MASV", "HO", "TEN","PHAI","SDT", "MALOP","NAMNHAP"},
	{"MAMH", "TENMH", "SLTCLT", "SLTCTH"},
	{"STT", "MASV", "HO", "TEN", "DIEM"},
	{ "MASV", "HO", "TEN","PHAI", "MALOP"}
};

string text2[10][10] = {
	{"MAMH", "NIEN KHOA", "HOC KY", "NHOM","SVMIN", "SVMAX"},
	{"MASV", "HO", "TEN", "PHAI", "SDT", "MALOP", "NAMNHAP"},
	{"MAMH", "TENMH", "SLTCLT", "SLTCTH"},
	{"DIEM"},
	{"MASV"}
};
int khungLon[10] = {92, 92, 80, 80, 80};
int leftKhung[10] = {11,11, 17, 17, 17};
int kichthuocKhung[8][8]= { 
	{14, 14, 12, 12, 12,11,11},    
	{14, 10, 10, 10, 16,15,11},	
	{19, 19, 19, 20},		
	{15, 16, 15, 15, 15,15},
	{15, 16, 15, 15, 15}
};
int sizeArrKhung[] ={7, 7, 4, 5, 5}; 


int KhungNhap[8][10] = {
	{6, 6, 6, 6, 6, 6}, 
	{7,4,4,4,6,7,4}, 
	{6, 6, 6, 6},
	{8},
	{8}
};
int sizeKhungNhap[] = {6,7,4,1,1}; 

string error[][20] = {
	{"LOP nay da duoc tao", "MAMH khong dung", "MAMH RONG", "NIEN KHOA RONG","HOC KI RONG","NHOM RONG","SVMIN RONG","SVMAX RONG","SVMAX NHO HON SVMAX"},
	{"MASV trung", "MASV rong","HO RONG","TEN RONG","PHAI RONG","SDT RONG","MA LOP RONG","NAM NHAP RONG"},
	{"MAMH trung", "MAMH rong","TENMH RONG","SLTCLT RONG","SLTCTH RONG"},
	{},
	{"MASV rong", "MASV trung", "MASV ko ton tai", "Sinh vien day"}
};

void gotoXY (int column, int line){	
	COORD coord; 	
	coord.X = column;  	
	coord.Y = line; 	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void hinhChuNhat(int left, int top, int right, int bottom, int color) {
	for(int i = top; i < bottom; i++) {
		gotoXY(left, i);
		for(int j = left; j < right; j++) cout << "  ";
	}
}
void textColor(string s, int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	cout << s;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
}

void Button(int left, int top, int right, int bottom, int colorFrame, string text) {
	int mid1 = (top + bottom) /2;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorFrame);
	hinhChuNhat(left, top, right, mid1, colorFrame);
	gotoXY(left, (top + bottom)/2);
	int len = text.length();
	int dis = (right - left)*2;
	int space = (dis - len);
	for(int i = 1; i <= space/2; i++) cout << " ";
	cout << text;
	for(int i = 1; i <= space/2 + (space % 2); i++) cout << " ";
	hinhChuNhat(left, mid1 + 1, right, bottom, colorFrame);
}

void TextColor (int color){	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
	}


void init_Menu(int cursor) {
	system("cls");
	system("color b0");
	for(int i = 0; i < 5;i ++) {
		int color = NOMAR_COLOR;
		if(cursor == i) color = HOVER_COLOR;
		Button(MEMU_LEFT,1 + 4*i,MEMU_RIGHT, 1 + 4*i + 3, color, Menu[i]);
	}
}


void change_cursor_main_down(int &cursor) {
	Button(MEMU_LEFT,1 + 4*cursor,MEMU_RIGHT, 1 + 4*cursor + 3, NOMAR_COLOR, Menu[cursor]);
	cursor = (cursor + 1)%5;
	Button(MEMU_LEFT,1 + 4*cursor,MEMU_RIGHT, 1 + 4*cursor + 3, HOVER_COLOR, Menu[cursor]);
}

void change_cursor_main_up(int & cursor) {
	Button(MEMU_LEFT,1 + 4*cursor,MEMU_RIGHT, 1 + 4*cursor + 3, NOMAR_COLOR, Menu[cursor]);
	cursor = (cursor - 1 + 5)%5;
	Button(MEMU_LEFT,1 + 4*cursor,MEMU_RIGHT, 1 + 4*cursor + 3, HOVER_COLOR, Menu[cursor]);
}


void line_Khung(int x, int y, int cursor) {
	gotoXY(x,y);
	cout << "+";
	for(int i = 1; i <= khungLon[cursor];i++) cout << "-";
	cout << "+";
}
void line_Khung1(int x, int y) {
	gotoXY(x,y);
	cout << "+";
	for(int i = 1; i <= 92;i++) cout << "-";
	cout << "+";
}


void print_KEYWORD(int colorW, int colorBG, int i, int left_khung, int current, int total) {
	gotoXY(left_khung + 2,5 + i - 1);
	TextColor(colorW);
	printf(" ESC:");	
	TextColor(colorBG);
	printf(" Exit");
	
	gotoXY(left_khung + 2 + 11*1,5 + i - 1);
	TextColor(colorW);
	printf(" F1:");	
	TextColor(colorBG);
	printf(" Them");
	
	gotoXY(left_khung + 2 + 11*2,5 + i - 1);
	TextColor(colorW);
	printf(" F2:");	
	TextColor(colorBG);
	printf(" Sua");
	
	gotoXY(left_khung + 2 + 11*3,5 + i - 1);
	TextColor(colorW);
	printf(" DELETE:");	
	TextColor(colorBG);
	printf(" Xoa");
	
	gotoXY(left_khung + 2 + 10*5 - 2,5 + i - 1);
	TextColor(colorW);
	printf(" F3:");	
	TextColor(colorBG);
	printf(" SAVE               ");
	TextColor(colorW);
	printf(" %d/%d ",current, total);	
}

void Khung_Xuat(int n, int current, int total) {
	int colorBG = 46;
	int colorW =  252;
	int colorPICK = 190;
	int nav = 233;
	int left_khung = leftKhung[n]; // VI TRI BAT DAU IN
	Button(MEMU_LEFT,1,MEMU_RIGHT,4 ,nav, Menu[n]);
	TextColor(colorBG);
	line_Khung(left_khung, 5, n); // DAU SAO ***
	int i = 1;
	int sum = 0;
	for(int j = 0; j < sizeArrKhung[n] ; j++) {
		gotoXY(left_khung + sum,6);
		cout << "| " << text[n][j];
		sum += kichthuocKhung[n][j] + 1; // IN RA TUNG O NHO TREN KHUNG XUAT
	}
	i++;
	line_Khung(left_khung, 5 + i, n);

	gotoXY(left_khung + sum,6);
	cout << "|"; // IN RA GACH DAU TIEN
//	i ++;
//	line_Khung(left_khung, 5 + i, n);
	i++;
	for( ;i <= 17; i++) {
		gotoXY(left_khung,5 + i);
		cout << "|";
		for(int j = 0; j < sizeArrKhung[n] ; j++) {
			for(int k = 1; k <= kichthuocKhung[n][j] ; k++) cout << " ";
			cout << "|";
		}
	}
	line_Khung(left_khung,5 + i, n);
	i ++;
	gotoXY(left_khung,5 + i);
	cout << "|";
	for(int i = 1; i <= khungLon[n];i++) cout << " ";
	cout << "|";
	i++;
	line_Khung(left_khung,5 + i, n);
	print_KEYWORD(colorW, colorBG, i, left_khung, current, total);	
}

void nhap_screen_lop(int n) {
	TextColor(70);
	hinhChuNhat(17, 11, 60, 14, 70);
	TextColor(252);
	int sum = 0;
	for(int i = 0; i < sizeKhungNhap[n] ;i++) {
		TextColor(252);
		hinhChuNhat(19 + sum, 12, 19 + sum + KhungNhap[n][i], 13, 70);
		TextColor(71);
		gotoXY(19 + sum, 11);
		cout <<text2[n][i];
		sum += KhungNhap[n][i]*2 + 2;
	}
	gotoXY(19, 13);
	TextColor(74);
	cout << "[ESC]:";
	TextColor(77);
	cout << " Exit    "; 
	TextColor(74);
	cout << "[ENTER]:";
	TextColor(77);
	cout << " Save"; 
	gotoXY(19, 12);
}

void print_error(int n,int i) {
	if(n == 0) {
		gotoXY(61,13);
		TextColor(76);
		for(int i = 1; i <= 26; i++) cout << " ";
		gotoXY(61,13);
	}
	if(n == 1) {
		gotoXY(61,13);
		TextColor(76);
		for(int i = 1; i <= 26; i++) cout << " ";
		gotoXY(61,13);
	}
	if(n == 2) {
		gotoXY(61,13);
		TextColor(76);
		for(int i = 1; i <= 26; i++) cout << " ";
		gotoXY(61,13);
	}
	if(n == 3) {
		gotoXY(37, 14);
		TextColor(76);
		for(int i = 1; i <= 26; i++) cout << " ";
		gotoXY(37, 14);
	}
	if(n == 4) {
		gotoXY(30, 14);
		TextColor(76);
		for(int i = 1; i <= 30; i++) cout << " ";
		gotoXY(30, 14);
	}
	TextColor(76);
	cout << "[ERR]: " << error[n][i]; 
}

int xu_li_nhap_lop(string &s, int k) {
	int sum = 0;
	for(int i = 0; i < k;i++) {
		sum += KhungNhap[0][i]*2 + 2;
	}
	
	while(1) {
		int ss =  min((int)s.length(),10);
		gotoXY(19 + sum + ss, 12);
		char c = getch();
		
		if(c == 0 || c == -32) c = getch();
		if(c == ESC) return 0;
		if(c == ENTER) {
			return -100;		
		}
		if(c == KEY_LEFT) {
			
			return -1;
		}
		if(c == KEY_RIGHT) {
			
			return 1;
		}
		
		if(c == BACKSPACE) {
			if(s.length() > 0) {
				gotoXY(19 + sum, 12);
				s[s.length() - 1] = ' ';
				int len = s.length();
				TextColor(252);
				for(int  i = max(0, len - 10) ; i < s.length() ;i++) cout << s[i];
				s.erase(s.length() - 1);
			}
		}
		else {
			if(k == 0 && s.length() < 15 && c != ' ') s.push_back(c);
			if(k > 0 && s.length() < 4 && c >= '0' && c <= '9' && c != ' ') s.push_back(c);
		}
		gotoXY(19 + sum , 12);
		TextColor(252);
		int len = s.length();
		for(int  i = max(0, len - 10) ; i < len ;i++) cout << s[i];
	}
}
void nhap_screen_sinhvien(int n) {
	TextColor(70);
	hinhChuNhat(19, 11, 59, 14, 70);
	TextColor(252);
	int sum = 0;
	for(int i = 0; i < sizeKhungNhap[n] ;i++) {
		TextColor(252);
		hinhChuNhat(20 + sum, 12, 20 + sum + KhungNhap[n][i], 13, 70);
		TextColor(71);
		gotoXY(20 + sum, 11);
		cout <<text2[n][i];
		sum += KhungNhap[n][i]*2 + 1;
	}
	gotoXY(20, 13);
	TextColor(74);
	cout << "[ESC]:";
	TextColor(77);
	cout << " Exit    "; 
	TextColor(74);
	cout << "[ENTER]:";
	TextColor(77);
	cout << " Save";
	gotoXY(20, 12);
}

void nhap_screen_monhoc(int n) {
	TextColor(70);
	hinhChuNhat(30, 11, 59, 14, 70);
	TextColor(252);
	int sum = 0;
	for(int i = 0; i < sizeKhungNhap[n] ;i++) {
		TextColor(252);
		hinhChuNhat(32 + sum, 12, 32 + sum + KhungNhap[n][i], 13, 70);
		TextColor(71);
		gotoXY(32 + sum, 11);
		cout <<text2[n][i];
		sum += KhungNhap[n][i]*2 + 2;
	}
	gotoXY(32, 13);
	TextColor(74);
	cout << "[ESC]:";
	TextColor(77);
	cout << " Exit    "; 
	TextColor(74);
	cout << "[ENTER]:";
	TextColor(77);
	cout << " Save";
	gotoXY(32, 12);
}
void nhap_screen_diem(int n) {
	TextColor(70);
	hinhChuNhat(30, 11, 45, 14, 70);
	TextColor(252);
	int sum = 0;
	for(int i = 0; i < sizeKhungNhap[n] ;i++) {
		TextColor(252);
		hinhChuNhat(37 + sum, 12, 37 + sum + KhungNhap[n][i], 13, 70);
		TextColor(71);
		gotoXY(43 + sum, 11);
		cout <<text2[n][i];
		sum += KhungNhap[n][i]*2 + 2;
	}
	gotoXY(31, 13);
	TextColor(74);
	cout << "[ESC]:";
	TextColor(77);
	cout << " Exit    "; 
	TextColor(74);
	cout << "[ENTER]:";
	TextColor(77);
	cout << " Save";
	gotoXY(37, 12);
}

void nhap_screen_dang_ky(int n) {
	TextColor(70);
	hinhChuNhat(30, 11, 45, 14, 70);
	TextColor(252);
	int sum = 0;
	for(int i = 0; i < sizeKhungNhap[n] ;i++) {
		TextColor(252);
		hinhChuNhat(37 + sum, 12, 37 + sum + KhungNhap[n][i], 13, 70);
		TextColor(71);
		gotoXY(43 + sum, 11);
		cout <<text2[n][i];
		sum += KhungNhap[n][i]*2 + 2;
	}
	gotoXY(31, 13);
	TextColor(74);
	cout << "[ESC]:";
	TextColor(77);
	cout << " Exit    "; 
	TextColor(74);
	cout << "[ENTER]:";
	TextColor(77);
	cout << " Save";
	gotoXY(37, 12);
}

int xu_li_nhap_sinhvien(string &s, int k) {
	int sum = 0;
	for(int i = 0; i < k;i++) {
		sum += KhungNhap[1][i]*2 + 1;
	}
	while(1) {
		int ss =  min((int)s.length(),KhungNhap[1][k]*2 - 1);
		gotoXY(20 + sum + ss, 12);
		
		char c = getch();
		if(c == 0 || c == -32) c = getch();
		if(c == ESC) return 0;
		if(c == ENTER) {
			return -100;	
		}
		if(c == KEY_LEFT) {
			return -1;
		}
		if(c == KEY_RIGHT) {
			return 1;
		}
		if(c == BACKSPACE) {
			if(s.length() > 0) {
				gotoXY(20 + sum, 12);
				s[s.length() - 1] = ' ';
				int len = s.length();
				TextColor(252);
				for(int  i = max(0, len - KhungNhap[1][k]*2 + 1) ; i < s.length() ;i++) cout << s[i];
				s.erase(s.length() - 1);
			}
		}
		else {
			if((k == 3) && s.length() < 15 && c!= ' ') s.push_back(c);
			if( k == 6 && s.length() < 4 && c >= '0' && c <= '9') s.push_back(c);
			if( k == 4 && s.length() < 12 && c >= '0' && c <= '9' ) s.push_back(c);
			if((k == 0)  && s.length() < 12 && c!= ' ' )s.push_back(c);
			if((k != 4 && k != 6 && k != 0 && k != 3) && s.length() < 15 && c!= ' ') s.push_back(c);
		}
		gotoXY(20 + sum , 12);
		TextColor(252);
		int len = s.length();
		for(int  i = max(0, len - KhungNhap[1][k]*2 + 1) ; i < len ;i++) cout << s[i];
	}
}

int validate_lop(LOPTC* loptc){
	if(loptc->MAMH.length() == 0) return 2;
	if(loptc->NIENKHOA == -1) return 3;
	if(loptc->HOCKI == -1) return 4;
	if(loptc->NHOM == -1) return 5;
	if(loptc->SOSV_MIN == -1) return 6;
	if(loptc->SOSV_MAX == -1) return 7;
	if(loptc->SOSV_MAX < loptc->SOSV_MIN) return 8;
	if(checkMonhoc(dsmh.root, loptc->MAMH) == 0) return 1;
	return -1;
}
int validate_sinhvien(SinhVien sv, string presv) {
	if(sv.MASV.length() == 0) return 1;
	if(presv != sv.MASV && checksv(dssv, sv.MASV) == 1) return 0;
	if(sv.HO.length() == 0) return 2;
	if(sv.TEN.length() == 0) return 3;
	if(sv.PHAI.length() == 0) return 4;
	if(sv.SDT.length() == 0) return 5;
	if(sv.MALOP.length() == 0) return 6;
	if(sv.NAMNHAP == -1 ) return 7;

	return -1;
}

int validate_monhoc(MONHOC mh, string premh) {
	if(mh.MAMH.length() == 0) return 1;
	if(premh != mh.MAMH && checkMonhoc(dsmh.root,mh.MAMH) > 0) return 0;
	if(mh.TENMH.length() == 0) return 2;
	if(mh.STCLT == -1) return 3;
	if(mh.STCTH == -1) return 4;
	
	return -1;
}
int validate_dangki(SinhVienDK svdk, string presv) {
	gotoXY(0, 0);
	if(svdk.MASV.length() == 0) return 0;
	if(dslop.LOP[global_var]->SOSV_MAX == dslop.LOP[global_var]->dssvdk.n) return 3;
	if(presv != svdk.MASV && check_sv_in_lop(dslop,global_var,svdk.MASV) > 0) {
		return 1;
	}
	else {
		if(presv != svdk.MASV && checksv(dssv, svdk.MASV) < 1) return 2;
	}
	return -1;
}
string intTostring(int m) {
	string s;
	int n = m;
	while(n > 0){
		int k = n % 10;
		s.push_back(k + '0');
		n /= 10;
	}
	if(s.length() > 0) reverse(s.begin(), s.end());
	return s;
}

int string_to_int(string s) {
	int ans = 0;
	for(int i = 0; i < s.length(); i++) {
		ans = ans * 10 + (s[i] - '0');
	}
	return ans;
}

void print_edit_lop(int sum, string s) {
	gotoXY(19 + sum , 12);
	TextColor(252);
	int len = s.length();
	for(int  i = max(0, len - 10) ; i < len ;i++) cout << s[i];
}


void quan_ly_lop_control(int cursor, LOPTC* &tempt, int type, int prelop) {
	nhap_screen_lop(cursor);
	string s;
	int k = 0;
	if(type == 1) {
		int sum = 0;
		print_edit_lop(sum, tempt->MAMH);
		sum += KhungNhap[0][0]*2 + 2;
		string gs = intTostring(tempt->NIENKHOA);
		if(tempt->NIENKHOA == -1) gs.clear();
		print_edit_lop(sum, gs);
		sum += KhungNhap[0][1]*2 + 2;
		gs = intTostring(tempt->HOCKI);
		if(tempt->HOCKI == -1) gs.clear();
		print_edit_lop(sum, gs);
		gs = intTostring(tempt->NHOM);
		if(tempt->NHOM == -1) gs.clear();
		sum += KhungNhap[0][2]*2 + 2;
		print_edit_lop(sum, gs);
		gs = intTostring(tempt->SOSV_MIN);
		if(tempt->SOSV_MIN == -1) gs.clear();
		sum += KhungNhap[0][3]*2 + 2;
		print_edit_lop(sum, gs);
		gs = intTostring(tempt->SOSV_MAX);
		if(tempt->SOSV_MAX == -1) gs.clear();
		sum += KhungNhap[0][4]*2 + 2;
		print_edit_lop(sum, gs);
	}
	while(1) {
		int g = 0;
		int aa = 0;
		if(k == 0) g = xu_li_nhap_lop(tempt->MAMH, k);
		if(k == 1) {
			string cd = to_string(tempt->NIENKHOA);
			if(tempt->NIENKHOA == -1) cd.clear();
			g = xu_li_nhap_lop(cd, k);
			if(cd.length() == 0) tempt->NIENKHOA = -1;
			else tempt->NIENKHOA = string_to_int(cd);
		}
		if(k == 2) {
			string cd = to_string(tempt->HOCKI);
			if(tempt->HOCKI == -1) cd.clear();
			g = xu_li_nhap_lop(cd, k);
			if(cd.length() == 0) tempt->HOCKI = -1;
			else tempt->HOCKI = string_to_int(cd);
		}
		if(k == 3) {
			string cd = to_string(tempt->NHOM);
			if(tempt->NHOM == -1) cd.clear();
			g = xu_li_nhap_lop(cd, k);
			if(cd.length() == 0) tempt->NHOM = -1;
			else tempt->NHOM = string_to_int(cd);
		}
		if(k == 4) {
			string cd = to_string(tempt->SOSV_MIN);
			if(tempt->SOSV_MIN == -1) cd.clear();
			g = xu_li_nhap_lop(cd, k);
			if(cd.length() == 0) tempt->SOSV_MIN = -1;
			else tempt->SOSV_MIN = string_to_int(cd);
		}
		if( k== 5) {
			string cd = to_string(tempt->SOSV_MAX);
			if(tempt->SOSV_MAX == -1) cd.clear();
			g = xu_li_nhap_lop(cd, k);
			if(cd.length() == 0) tempt->SOSV_MAX = -1;
			else tempt->SOSV_MAX = string_to_int(cd);
		}
		if(g == 0) return;
		if(g == -100) {
			int j = validate_lop(tempt);
			if(j == -1) {
				if(type == 0) ThemLopTC(tempt, dslop);
				if(type == 1) SuaLopTC(dslop, tempt, prelop);
				break;
			}
			else {
				print_error(0, j);
				k = 0;
				continue;
			}
		}
		k = (k + 6 + g) % 6;
	}
}
void print_edit_sinhvien(int sum, string s) {
	gotoXY(20 + sum , 12);
	TextColor(252);
	int len = s.length();
	for(int  i = max(0, len - 10) ; i < len ;i++) cout << s[i];
}

void quan_li_sinhvien_control(int cursor,SinhVien &sv, int type, string presv) {
	nhap_screen_sinhvien(cursor);
	int k = 0;
	if(type == 1) {

		int sum = 0;
		print_edit_sinhvien(sum, sv.MASV);
		sum += KhungNhap[1][0]*2 + 1;
		print_edit_sinhvien(sum,sv.HO);
		sum += KhungNhap[1][1]*2 + 1;
		print_edit_sinhvien(sum, sv.TEN);
		sum += KhungNhap[1][2]*2 + 1;
		print_edit_sinhvien(sum, sv.PHAI);
		sum += KhungNhap[1][3]*2 + 1;
		print_edit_sinhvien(sum, sv.SDT);
		sum += KhungNhap[1][4]*2 + 1;
		print_edit_sinhvien(sum, sv.MALOP);
		string gs = to_string(sv.NAMNHAP);
		if(sv.NAMNHAP == -1) gs.clear();
		sum += KhungNhap[1][5]*2 + 1;
		print_edit_sinhvien(sum, gs);
	}
	while(1) {
		int g = 0;
		if(k == 0) {
		
			g = xu_li_nhap_sinhvien(sv.MASV, k);		
		}
		if(k == 1) {
			g = xu_li_nhap_sinhvien(sv.HO, k);
		}
		if(k == 2) {
			g = xu_li_nhap_sinhvien(sv.TEN, k);
		}
		if(k == 3) {
			g = xu_li_nhap_sinhvien(sv.PHAI, k);
		}
		if(k == 4) {
			g = xu_li_nhap_sinhvien(sv.SDT, k);

		}
		if(k == 5) {
			g = xu_li_nhap_sinhvien(sv.MALOP, k);
		}
		if(k == 6) {
			string cd = to_string(sv.NAMNHAP);
			if(sv.NAMNHAP == -1) cd.clear();
			g = xu_li_nhap_sinhvien(cd, k);
			if(cd.length() == 0) sv.NAMNHAP = -1;
			else sv.NAMNHAP = string_to_int(cd);
		}
		if(g == 0) break;
		if(g == -100) {
			int j = validate_sinhvien(sv, presv);
			if(j == -1) {
				node* nodeSV = getnode(sv);
				gotoXY(0,1);
				if(type == 0) themsinhvien(dssv, nodeSV);
				if(type == 1) suasinhvien(dssv, presv, sv);
				break;
			}
			else {
				print_error(1, j);
				k = 0;
				continue;
			}
		}
		k = (k + 7 + g) % 7;
	}
}
int xu_li_nhap_monhoc(string &s, int k) {
	int sum = 0;
	for(int i = 0; i < k;i++) {
		sum += KhungNhap[2][i]*2 + 2;
	}
	while(1) {
		int ss =  min((int)s.length(),KhungNhap[2][k]*2 - 1);
		gotoXY(32 + sum + ss, 12);
		
		char c = getch();
		if(c == 0 || c == -32) c = getch();
		if(c == ESC) return 0;
		if(c == ENTER) {
			
			return -100;	
		}
		if(c == KEY_LEFT) {
			return -1;
		}
		if(c == KEY_RIGHT) {
			return 1;
		}
		if(c == BACKSPACE) {
			if(s.length() > 0) {
				gotoXY(32 + sum, 12);
				s[s.length() - 1] = ' ';
				int len = s.length();
				TextColor(252);
				for(int  i = max(0, len - KhungNhap[2][k]*2 + 1) ; i < s.length() ;i++) cout << s[i];
				s.erase(s.length() - 1);
			}
		}
		else {
			if(k == 0 && s.length() <= 10 && c != ' ') s.push_back(c);
			if(k == 1 && s.length() <= 20 && c != ' ') s.push_back(c);
			if( k >= 2 && c >= '0' && c <= '9') s.push_back(c);
		}
		gotoXY(32 + sum , 12);
		TextColor(252);
		int len = s.length();
		for(int  i = max(0, len - KhungNhap[2][k]*2 + 1) ; i < len ;i++) cout << s[i];
	}
}
int xu_li_nhap_diem(string &s, int k) {
	int sum = 0;
	for(int i = 0; i < k;i++) {
		sum += KhungNhap[3][i]*2 + 2;
	}
	while(1) {
		int ss =  min((int)s.length(),KhungNhap[3][k]*2 - 1);
		gotoXY(37 + sum + ss, 12);
		
		char c = getch();
		if(c == 0 || c == -32) c = getch();
		if(c == ESC) return 0;
		if(c == ENTER) {
			
			return -100;	
		}
		if(c == KEY_LEFT) {
			return -1;
		}
		if(c == KEY_RIGHT) {
			return 1;
		}
		if(c == BACKSPACE) {
			if(s.length() > 0) {
				gotoXY(37 + sum, 12);
				s[s.length() - 1] = ' ';
				int len = s.length();
				TextColor(252);
				for(int  i = max(0, len - KhungNhap[3][k]*2 + 1) ; i < s.length() ;i++) cout << s[i];
				s.erase(s.length() - 1);
			}
		}
		else {
				if(c >= '0' && c <= '9' && s.length() < 3) s.push_back(c);	
			}
		gotoXY(37 + sum , 12);
		TextColor(252);
		int len = s.length();
		for(int  i = max(0, len - KhungNhap[3][k]*2 + 1) ; i < len ;i++) cout << s[i];
	}
}
int xu_li_nhap_dang_ki(string &s, int k) {
	int sum = 0;
	for(int i = 0; i < k;i++) {
		sum += KhungNhap[4][i]*2 + 2;
	}
	while(1) {
		int ss =  min((int)s.length(),KhungNhap[4][k]*2 - 1);
		gotoXY(37 + sum + ss, 12);
		
		char c = getch();
		if(c == 0 || c == -32) c = getch();
		if(c == ESC) return 0;
		if(c == ENTER) {
			
			return -100;	
		}
		if(c == KEY_LEFT) {
			return -1;
		}
		if(c == KEY_RIGHT) {
			return 1;
		}
		if(c == BACKSPACE) {
			if(s.length() > 0) {
				gotoXY(37 + sum, 12);
				s[s.length() - 1] = ' ';
				int len = s.length();
				TextColor(252);
				for(int  i = max(0, len - KhungNhap[4][k]*2 + 1) ; i < s.length() ;i++) cout << s[i];
				s.erase(s.length() - 1);
			}
		}
		else {
				if(s.length() < 15)s.push_back(c);	
			}
		gotoXY(37 + sum , 12);
		TextColor(252);
		int len = s.length();
		for(int  i = max(0, len - KhungNhap[4][k]*2 + 1) ; i < len ;i++) cout << s[i];
	}
}
void print_edit_monhoc(int sum, string s) {
	gotoXY(32 + sum , 12);
	TextColor(252);
	int len = s.length();
	for(int  i = max(0, len - 10) ; i < len ;i++) cout << s[i];
}
void quan_li_mon_hoc_control(int cursor,MONHOC &mh, int type, string mamh) {
	nhap_screen_monhoc(cursor);
	int k = 0;
	if(type == 1) {
		int sum = 0;
		print_edit_monhoc(sum, mh.MAMH);
		sum += KhungNhap[2][0]*2 + 2;
		print_edit_monhoc(sum,mh.TENMH);
		sum += KhungNhap[2][1]*2 + 2;
		string gs = to_string(mh.STCLT);
		if(mh.STCLT == -1) gs.clear();
		print_edit_monhoc(sum, gs);
		sum += KhungNhap[2][2]*2 + 2;
		gs = to_string(mh.STCTH);
		if(mh.STCTH == -1) gs.clear();
		print_edit_monhoc(sum, gs);
	}
	while(1) {
		int g = 0;
		if(k == 0) {
			g = xu_li_nhap_monhoc(mh.MAMH, k);		
		}
		if(k == 1) {
			g = xu_li_nhap_monhoc(mh.TENMH, k);
		}
		if(k == 2) {	
			string cd = to_string(mh.STCLT);
			if(mh.STCLT == -1) cd.clear();
			g = xu_li_nhap_monhoc(cd, k);
			if(cd.length() == 0) mh.STCLT = -1;
			else mh.STCLT = string_to_int(cd);
		}
		if(k == 3) {
			
			string cd = to_string(mh.STCTH);
			if(mh.STCTH == -1) cd.clear();
			g = xu_li_nhap_monhoc(cd, k);
			if(cd.length() == 0) mh.STCTH = -1;
			else mh.STCTH = string_to_int(cd);
		}
		if(g == 0) break;
		if(g == -100) {
			int j = validate_monhoc(mh, mamh);
			if(j == -1) {
				MONHOC* monhoc = getNodeMH(mh.MAMH, mh.TENMH, mh.STCLT, mh.STCTH);
				if(type == 0) {
					addNodeMH(dsmh.root, monhoc, dsmh);
				}
				if(type == 1) {
					xoa_node_MH(dsmh.root, mamh);
					addNodeMH(dsmh.root,monhoc, dsmh);
				} 
				break;
			}
			else {
				print_error(2, j);
				k = 0;
				continue;
			}
		}
		k = (k + 4 + g) % 4;
	}
}
void print_edit_diem(int sum, string s) {
	gotoXY(37 + sum , 12);
	TextColor(252);
	int len = s.length();
	for(int  i = max(0, len - 16) ; i < len ;i++) cout << s[i];
}

void print_edit_dangki(int sum, string s) {
	gotoXY(37 + sum , 12);
	TextColor(252);
	int len = s.length();
	for(int  i = max(0, len - 16) ; i < len ;i++) cout << s[i];
}

void quan_li_diem_sinh_vien_control(int cursor,SinhVienDK &svdk, int type,string presv) {
	nhap_screen_diem(cursor);
	int k = 0;
	if(type == 1) {
		int sum = 0;
		string gs = to_string(svdk.DIEM);
		if(svdk.DIEM == -1) gs.clear();
		print_edit_diem(sum, gs);
	}
	while(1) {
		int g = 0;
		if(k == 0) {
			string cd = to_string(svdk.DIEM);
			if(svdk.DIEM == -1) cd.clear();
			g = xu_li_nhap_diem(cd, k);
			if(cd.length() == 0) svdk.DIEM = -1;
			else svdk.DIEM = string_to_int(cd);
		}
		if(g == 0) break;
		if(g == -100) {
			int j = -1;
			if(j == -1) {

				if(type == 0) {
					Them_sv_cho_loptc(dslop, global_var,svdk.MASV);
				}
				if(type == 1) {
			
					sua_sv_in_lop(dslop, global_var, presv,svdk);
				} 
				break;
			}
			else {
				print_error(3, j);
				k = 0;
				continue;
			}
		}
		k = (k + 1 + g) % 1;
	}
}

void quan_li_sinh_vien_dang_ki_control(int cursor,SinhVienDK &svdk, int type, string presv) {
	nhap_screen_dang_ky(cursor);
	int k = 0;
	if(type == 1) {
		int sum = 0;
		print_edit_dangki(sum, svdk.MASV);
	}
	while(1) {
		int g = 0;
		if(k == 0) {
			g = xu_li_nhap_dang_ki(svdk.MASV, k);
		}
		if(g == 0) break;
		if(g == -100) {
			
			int j = validate_dangki(svdk, presv);
			if(j == -1) {
				
				if(type == 0) {
					Them_sv_cho_loptc(dslop, global_var,svdk.MASV);
				}
				if(type == 1) {
				
					sua_sv_in_lop(dslop, global_var, presv,svdk);
				} 
				break;
			}
			else {
				print_error(4, j);
				k = 0;
				continue;
			}
		}
		k = (k + 1 + g) % 1;
	}
}
int in_dam(int n, int i, int color, int current) { 

	int left_khung = leftKhung[n]; 
	gotoXY(left_khung,5 + 3 + i);	
	TextColor(color);  
	cout << "|";
	for(int j = 0; j < sizeArrKhung[n] ; j++) { 
		for(int k = 1; k <= kichthuocKhung[n][j] ; k++) cout << " "; 
		cout << "|"; 
	}
					// 0 
	int sum = 1;
	int j = 8;
	int vitri = (current - 1)* CHIEU_DOC + i;
	if(n == 0) {
		if(vitri >= dslop.n) return -1;
		gotoXY(left_khung + sum,j + i);
		cout << dslop.LOP[vitri]->MALOPTC;
		sum += kichthuocKhung[n][0] + 1;
		gotoXY(left_khung + sum,j + i);
		cout << dslop.LOP[vitri]->MAMH;
		sum += kichthuocKhung[n][1] + 1;
		gotoXY(left_khung + sum,j + i);
		if(dslop.LOP[vitri]->NIENKHOA != -1) cout << dslop.LOP[vitri]->NIENKHOA;
		sum += kichthuocKhung[n][2] + 1;
		gotoXY(left_khung + sum,j + i);
		if(dslop.LOP[vitri]->HOCKI != -1) cout << dslop.LOP[vitri]->HOCKI;
		sum += kichthuocKhung[n][3] + 1;
		gotoXY(left_khung + sum,j + i);
		if(dslop.LOP[vitri]->NIENKHOA != -1) cout << dslop.LOP[vitri]->NHOM;
		sum += kichthuocKhung[n][4] + 1;
		gotoXY(left_khung + sum,j + i);
		if(dslop.LOP[vitri]->SOSV_MIN != -1) cout << dslop.LOP[vitri]->SOSV_MIN;
		sum += kichthuocKhung[n][5] + 1;
		gotoXY(left_khung + sum,j + i);
		if(dslop.LOP[vitri]->SOSV_MAX != -1) cout << dslop.LOP[vitri]->SOSV_MAX;
	}
	if(n == 1) {
		node* gett = find_sinhvien(dssv, vitri);
		if(gett == NULL) return -1;
		gotoXY(left_khung + sum,j + i);
		cout << gett->data.MASV;
		sum += kichthuocKhung[n][0] + 1;
		gotoXY(left_khung + sum,j + i);
		cout << gett->data.HO;
		sum += kichthuocKhung[n][1] + 1;
		gotoXY(left_khung + sum,j + i);
		cout << gett->data.TEN;
		sum += kichthuocKhung[n][2] + 1;
		gotoXY(left_khung + sum,j + i);
		cout << gett->data.PHAI;

		sum += kichthuocKhung[n][3] + 1;
		gotoXY(left_khung + sum,j + i);
		cout << gett->data.SDT;
		sum += kichthuocKhung[n][4] + 1;
		gotoXY(left_khung + sum,j + i);
		cout << gett->data.MALOP;
		sum += kichthuocKhung[n][5] + 1;
		gotoXY(left_khung + sum,j + i);
		if(gett->data.NAMNHAP != -1) cout << gett->data.NAMNHAP;	
	}
	if(n == 2){
		MONHOC* gett = NULL;
		int k = 0;
		find_Monhoc(dsmh.root, gett, vitri, k);
		if(gett == NULL) return -1;
		gotoXY(left_khung + sum,j + i);
		cout << gett->MAMH;
		sum += kichthuocKhung[n][0] + 1;
		gotoXY(left_khung + sum,j + i);
		cout << gett->TENMH;
		sum += kichthuocKhung[n][1] + 1;
		gotoXY(left_khung + sum,j + i);
		if(gett->STCLT != -1) cout << gett->STCLT;
		sum += kichthuocKhung[n][2] + 1;
		gotoXY(left_khung + sum,j + i);
		if(gett->STCTH != -1) cout << gett->STCTH;
	}
	if(n == 3) {
		nodesvdk* gett = new nodesvdk;
		gett = find_sv_by_lop_vitri(dslop, global_var,vitri);
		if(gett == NULL) return -1;
		node* xx = find_sinhvien_by_masv(dssv, gett->data.MASV);
		if(xx == NULL) return -1;
		gotoXY(left_khung + sum,j + i);
		cout << vitri;
		sum += kichthuocKhung[n][0] + 1;
		gotoXY(left_khung + sum,j + i);
		cout << xx->data.MASV;
		sum += kichthuocKhung[n][1] + 1;
		gotoXY(left_khung + sum,j + i);
		cout << xx->data.HO;
		sum += kichthuocKhung[n][2] + 1;
		gotoXY(left_khung + sum,j + i);
		cout << xx->data.TEN;

		sum += kichthuocKhung[n][3] + 1;
		gotoXY(left_khung + sum,j + i);
		if(gett->data.DIEM != -1)cout << gett->data.DIEM;
		
	}
	if(n == 4) {
		
		nodesvdk* gett = new nodesvdk;
		gett = find_sv_by_lop_vitri(dslop, global_var,vitri);
		if(gett == NULL) return -1;
		node* xx = find_sinhvien_by_masv(dssv, gett->data.MASV);
		if(xx == NULL) return -1;
			gotoXY(left_khung + sum,j + i);
		cout << xx->data.MASV;
		sum += kichthuocKhung[n][0] + 1;
		gotoXY(left_khung + sum,j + i);
		cout << xx->data.HO;
		sum += kichthuocKhung[n][1] + 1;
		gotoXY(left_khung + sum,j + i);
		cout << xx->data.TEN;
		sum += kichthuocKhung[n][2] + 1;
		gotoXY(left_khung + sum,j + i);
		cout << xx->data.PHAI;

		sum += kichthuocKhung[n][3] + 1;
		gotoXY(left_khung + sum,j + i);
		cout << xx->data.MALOP;
	}
}
void print_table(int n,int gg, int current) {
	if(n == 0) {
		int left_khung = 17;
		int j = 3 + 5;
		for(int i = 0 ; i < CHIEU_DOC; i++) {
			if((current - 1)* CHIEU_DOC + i >= dslop.n) break;
			if(i == gg) in_dam(n, i, 190, current);
			else in_dam(n, i, 46, current);
		}
	}
	if(n == 1){
		for(int i = 0; i < CHIEU_DOC;i++){
			if((current - 1)* CHIEU_DOC + i >= dssv.n) break;
			if(i == gg) in_dam(n, i, 190, current);
			else in_dam(n, i, 46, current);
		}
	}
	if(n == 2) {
		for(int i = 0; i < CHIEU_DOC;i++){
			if((current - 1)* CHIEU_DOC + i >= dsmh.n) break;
			if(i == gg) in_dam(n, i, 190,current);
			else in_dam(n, i, 46, current);
		}
	}
	if(n == 3) {
		for(int i = 0; i < CHIEU_DOC;i++){
			int k = checklop(global_var, dslop);
			if(k == -1) break;
			if((current - 1)* CHIEU_DOC + i >= dslop.LOP[k]->dssvdk.n) break;
			if(i == gg) in_dam(n, i, 190,current);
			else in_dam(n, i, 46, current);
		}
	}
	if(n == 4) {
		for(int i = 0; i < CHIEU_DOC;i++){
			int k = checklop(global_var, dslop);
			if(k == -1) break;
			if((current - 1)* CHIEU_DOC + i >= dslop.LOP[k]->dssvdk.n) break;
			if(i == gg) in_dam(n, i, 190,current);
			else in_dam(n, i, 46, current);
		}
	}
}
int getTotal(int n) {
	int ans = 0;
	if(n == 0) {
		ans = dslop.n;
	}
	if(n == 1) {
		ans = dssv.n;
	}
	if(n == 2) {
		ans = dsmh.n;
	}
	if(n == 3) {
		LOPTC* lc = findLOpById(dslop, global_var);
		ans = lc->dssvdk.n;
	}
	if(n == 4) {
		LOPTC* lc = findLOpById(dslop, global_var);
		ans = lc->dssvdk.n;
	}
	return max(1,ans/CHIEU_DOC + (ans % CHIEU_DOC > 0)); 
	
}
void print_dialog(int cursor, string text) {
	TextColor(74);
	hinhChuNhat(MEMU_LEFT,1 + 4*cursor,MEMU_RIGHT, 1 + 4*cursor + 3, 13);
	TextColor(252);
	hinhChuNhat(MEMU_LEFT + 2, 1 + 4*cursor + 1,MEMU_RIGHT,  1 + 4*cursor + 3 - 1, 11);
	gotoXY(MEMU_LEFT + 1 + 8,1 + 4*cursor);
	TextColor(78);
	cout << text;
	gotoXY(MEMU_LEFT + 1,1 + 4*cursor + 2);
	TextColor(74);
	cout << "[ESC]:";
	TextColor(77);
	cout << " Exit   "; 
	TextColor(74);
	cout << "[ENTER]:";
	TextColor(77);
	cout << " Enter"; 
}
int xu_li_nhap_dialog(int cursor, string &s) {
	int c;
	while(1) {
		int ss =  min((int)s.length(),15);
		gotoXY(MEMU_LEFT + 2 + ss, 1 + 4*cursor + 1);
		c = getch();
		if(c == 0 || c == -32) c = getch();
		if(c == ESC) return -1;
		if(c == ENTER) {
			int cd = string_to_int(s);
			if(s.length() == 0) {
				gotoXY(MEMU_LEFT + 32,1 + 4*cursor + 2);
				TextColor(188);
			for(int i = 1; i <= 26; i++) cout << " ";
			gotoXY(MEMU_LEFT + 32,1 + 4*cursor + 2);
				cout << "[ERR]: " << "Ma lop trong"; 
				continue;	
			}
			if(checklop(cd, dslop) >= 0) return 1;
			else {		
				gotoXY(MEMU_LEFT + 32,1 + 4*cursor + 2);
				TextColor(188);
				for(int i = 1; i <= 20; i++) cout << " ";
				gotoXY(MEMU_LEFT + 32,1 + 4*cursor + 2);
				cout << "[ERR]: " << "Ma lop khong ton tai"; 
				continue;
			}
		}
		if(c == BACKSPACE) {
			if(s.length() > 0) {
				gotoXY(MEMU_LEFT + 2, 1 + 4*cursor + 1);
				s[s.length() - 1] = ' ';
				int len = s.length();
				TextColor(252);
				for(int  i = max(0, len - 16) ; i < s.length() ;i++) cout << s[i];
				s.erase(s.length() - 1);
			}
		}
		if(s.length() < 10 && c >= '0' && c <= '9') s.push_back(c);
		gotoXY(MEMU_LEFT + 2, 1 + 4*cursor + 1);
		TextColor(252);
		int len = s.length();
		for(int  i = max(0, len - 16) ; i < len ;i++) cout << s[i];
	}
}

int save_dialog() {
	TextColor(74);
	hinhChuNhat(MEMU_LEFT,1 + 4*3,MEMU_RIGHT, 1 + 4*3 + 3, 13);
	gotoXY(MEMU_LEFT + 3 ,2 + 4*3);
	TextColor(78);
	cout << "Ban co muon luu khong ?";
	gotoXY(MEMU_LEFT + 1,1 + 4*3 + 2);
	TextColor(74);
	cout << "[ESC]:";
	TextColor(77);
	cout << " Exit   "; 
	TextColor(74);
	cout << "[ENTER]:";
	TextColor(77);
	cout << " Enter"; 
	while(1) {
		int c = getch();
		if(c == ESC) return 0;
		if(c == ENTER) return 1;
	}
}
int xoa_Mh_dia () {
	TextColor(74);
	hinhChuNhat(MEMU_LEFT,1 + 4*3,MEMU_RIGHT, 1 + 4*3 + 3, 13);
	gotoXY(MEMU_LEFT + 3 ,2 + 4*3);
	TextColor(78);
	cout << "CON TON TAI LOPTC";
	gotoXY(MEMU_LEFT + 1,1 + 4*3 + 2);
	TextColor(74);
	cout << "[ESC]:";
	TextColor(77);
	cout << " Exit   "; 
	TextColor(74);
	cout << "[ENTER]:";
	TextColor(77);
	cout << " Enter"; 
	while(1) {
		int c = getch();
		if(c == ESC) return 0;
		if(c == ENTER) return 1;
	}
}


int control_screen(int cursor) {
	system("cls");
	system("color 27");
	int gg = 0; // so dong
	int current = 1; // trang
	int total = getTotal(cursor); // tinh tong so trang
	
	Khung_Xuat(cursor, current, total);
	print_table(cursor, gg, current);
	while(1) {
		in_dam(cursor, gg, 190, current);
		int c = getch();
		if(c == 0 || c == - 32) c = getch();
		if(c == KEY_DOWN) {
			in_dam(cursor, gg, 46, current);
			gg = (gg + 1) % CHIEU_DOC;
		}
		if(c == KEY_UP) {
			in_dam(cursor, gg, 46, current);
			gg = (gg + CHIEU_DOC - 1) % CHIEU_DOC;
		}
		if(c == KEY_LEFT) {
			current = (current - 1 + total)%total;
			if(current == 0) current = total;
			Khung_Xuat(cursor, current, total);
			print_table(cursor, gg, current);
		}
		if(c == KEY_RIGHT) {
			current = (current + 1 + total)%total;
			if(current == 0) current = total;
			Khung_Xuat(cursor, current, total);
			print_table(cursor, gg, current);
		}
		if(c == KEY_DELETE) {
			gotoXY(0, 1);
			//cout<< gg;
			int vitri = (current - 1)*CHIEU_DOC + gg;
			if(cursor == 0) XoaLopTC(dslop,vitri);
			if(cursor == 1) xoasinhvien(dssv, vitri);
			if(cursor == 2) {
				//doc_dslop_file(dslop);
				//doc_lop_file(dslop);
				//xuat_lop_file(dslop);
				//doc_dslop_file(dslop);
				//doc_lop_file(dslop);
				MONHOC* t = new MONHOC;
				int j = 0;
				find_Monhoc(dsmh.root,t,vitri, j);
				int f = check_MH_inloptc(t,dslop);
				if(f == 1){
					xoa_Mh_dia() ;
				
				}
				if(f == -1){
					xoa_node_MH(dsmh.root, t->MAMH);
					dsmh.n--;
				}
			}
			if(cursor == 4) {
				Xoa_svdk(dslop, global_var, vitri);
			}
			total = getTotal(cursor);
			Khung_Xuat(cursor, current, total);
			print_table(cursor, gg, current);
		}
		if(c == ESC) {
			break;
		}
		if(c == F1) {
			if(cursor == 0) {
				LOPTC* loptc = new LOPTC;
				loptc->HOCKI = -1;
				loptc->NHOM = -1;
				loptc->NIENKHOA = -1;
				loptc->SOSV_MIN = -1;
				loptc->SOSV_MAX = -1;
				quan_ly_lop_control(cursor, loptc, 0, 0);
			}
			if(cursor == 1) {
				SinhVien sv;
				sv.NAMNHAP = -1;
				quan_li_sinhvien_control(cursor, sv, 0, "~~~");
			}
			if(cursor == 2) {
				MONHOC mh;
				mh.STCLT = -1;
				mh.STCTH = -1;
				quan_li_mon_hoc_control(cursor, mh, 0, "~~~~");
			}
			if(cursor == 4) {
				SinhVienDK svdk;
				svdk.DIEM = -1;
				quan_li_sinh_vien_dang_ki_control(cursor,svdk, 0, "~~~~");
			
			}
			total = getTotal(cursor);
			Khung_Xuat(cursor, current, total);
			print_table(cursor, gg, current);
		}
		if(c == F2) {
			if(cursor == 0) {
				int vitri = (current - 1)*CHIEU_DOC + gg;
				LOPTC* tc = dslop.LOP[vitri];
				if(vitri < dslop.n) quan_ly_lop_control(cursor, tc, 1 ,dslop.LOP[vitri]->MALOPTC);
			}
			if(cursor == 1) {
				node* nodeSV = find_sinhvien(dssv, (current - 1)*CHIEU_DOC + gg);
				
				if(nodeSV != NULL) {
					SinhVien sv = nodeSV->data;
					quan_li_sinhvien_control(cursor, sv,1, sv.MASV); 
				}
			}
			if(cursor == 2) {
				MONHOC* mhh = new MONHOC; 
				mhh = NULL;
				int h = 0;
				find_Monhoc(dsmh.root, mhh, (current - 1)*CHIEU_DOC + gg, h);	
				int f = check_MH_inloptc(mhh,dslop);
				if(f == 1){
				xoa_Mh_dia();
				}
	
							
				if(mhh != NULL && f == -1) {
				MONHOC temptt;
				temptt.MAMH = mhh->MAMH;
				temptt.TENMH = mhh->TENMH;
				temptt.STCLT = mhh->STCLT;
				temptt.STCTH = mhh->STCTH;
					quan_li_mon_hoc_control(cursor, temptt, 1, mhh->MAMH); 
				}
			}
			if(cursor == 3) {
				nodesvdk* sv = new nodesvdk;
				sv = find_sv_by_lop_vitri(dslop, global_var, (current - 1)*CHIEU_DOC + gg);
				if(sv != NULL) quan_li_diem_sinh_vien_control(cursor, sv->data, 1, sv->data.MASV);
				
			}
			if(cursor== 4) {
				nodesvdk* sv = new nodesvdk;
				sv = find_sv_by_lop_vitri(dslop, global_var, (current - 1)*CHIEU_DOC + gg);
				SinhVienDK ssv = sv->data;
				if(sv != NULL) quan_li_sinh_vien_dang_ki_control(cursor, ssv, 1, sv->data.MASV);
			}
			total = getTotal(cursor);
			Khung_Xuat(cursor, current, total);
			print_table(cursor, gg, current);
		}
		if(c == F3) {
			int f = save_dialog();
			if(f == 1) {
				if(cursor == 0) {
				xuat_lop_file(dslop);
				}
				if(cursor == 1) {
					xuat_sinhvien_file(dssv);
				}
				if(cursor == 2) {
					xuat_monhoc_file(dsmh);
				}
				if(cursor >= 3) {
					int vt = checklop(global_var, dslop);
					xuat_svdk_file(global_var, dslop.LOP[vt]->dssvdk);
				}
			}
			Khung_Xuat(cursor, current, total);
			print_table(cursor, gg, current);
		}
	}
	
}
int main() {	
	init_LOPTC(dslop); //
	doc_lop_file(dslop);//
	doc_dslop_file(dslop);//
	init_DSSV(dssv);//
	doc_sinhvien_file(dssv);//
	init_MONHOC(dsmh);//
	doc_monhoc_file(dsmh);///
	int check = true;
	int cursor = 0;//
	int cursor_table = 0;
	int cursor_phu = 0;
	char c;
	int previous = 0;	
	while(1) {
RERENDER : init_Menu(cursor);// in ra menu va in dam thanh dau tien
CONTINUE:  c = getch();
		if(c == KEY_DOWN) {
			change_cursor_main_down(cursor); // im dam o tiep theo va thay doi cusor
		}
		if(c == KEY_UP) {
			change_cursor_main_up(cursor);
		}
		if(c == ENTER) {
			
			if(cursor <= 2) control_screen(cursor);
			if(cursor >= 3) {
				print_dialog(cursor, "Nhap Ma Lop");
				string tt;
				int gett = xu_li_nhap_dialog(cursor,tt);
				global_var = string_to_int(tt);
				if(gett != -1) {
					control_screen(cursor);
				}  
			}
			
			goto RERENDER;
		}
		goto CONTINUE;	
	}
}
