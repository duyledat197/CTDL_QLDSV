#include <iostream>
#include <fstream>
using namespace std;
const int MAXM = 100;
ofstream ofs;
ifstream ifs;
struct MONHOC {
	string MAMH;
	string TENMH;
	int STCLT;
	int STCTH;
	MONHOC* left;
	MONHOC* right;
};

struct DSMH {
	MONHOC* root;
	int n = 0;
};
struct SinhVienDK {
	string MASV;
	int DIEM;
};
struct nodesvdk{
	SinhVienDK data;
	nodesvdk* pnext;
};
struct DSSVDK {
	nodesvdk *phead;
	int n;
};

struct 	LOPTC {
	int MALOPTC;
	string MAMH;
	int NIENKHOA;
	int HOCKI;
	int NHOM;
	int SOSV_MAX;
	int SOSV_MIN;
	DSSVDK dssvdk;
}; 
struct DsLOP{
	LOPTC* LOP[MAXM];
 	int n = 0;	
 	int bosinh = 0; 
};
struct SinhVien {
	string MASV;
	string HO;
	string TEN;
	string PHAI;
	string SDT;
	string MALOP;
	int NAMNHAP = -1;
};
struct node{
	SinhVien data;
	node* pnext;
};
struct DSSV{
	node* phead;
	int n = 0;
};




// set up data


/* #### MON HOC ##### */
void init_MONHOC(DSMH &ds) {
	ds.root = NULL;
}
MONHOC* getNodeMH(string MAMH, string TENMH, int SLTCLT, int STCTH) {
	MONHOC* newMH = new MONHOC;
	newMH->MAMH = MAMH;
	newMH->TENMH = TENMH;
	newMH->STCLT = SLTCLT;
	newMH->STCTH = STCTH;
	newMH->left = NULL;
	newMH->right = NULL;
	return newMH;
}

void addNodeMH(MONHOC* &nodee, MONHOC* p, DSMH &dsmh){
	if(nodee == NULL){
		nodee = p;
		dsmh.n ++;
		return;
	}
	else { 
		if(p->MAMH.compare(nodee->MAMH) > 0) addNodeMH(nodee->right, p, dsmh);
		else addNodeMH(nodee->left, p, dsmh);		
	}
}
MONHOC* laygiatritrainhat(MONHOC* nodee){
	while(nodee->left != NULL) {
		nodee = nodee->left;
	}
	return nodee;
}
MONHOC* xoa_node_MH(MONHOC* &nodee, string premh)
{
	if(nodee == NULL)
	{
		return nodee;
	}
		if(premh.compare(nodee->MAMH)==0)
		{
			
			if(nodee->left == NULL){
				MONHOC* x = nodee;
				nodee = nodee->right;
		
				delete x;	
				return nodee;
			
			}
			else if(nodee->right == NULL){
				MONHOC* x = nodee;
				nodee = nodee->left;
			
				delete x;
				return nodee;
			
			}
			else{
				MONHOC* tempt = laygiatritrainhat(nodee->right);
				nodee->MAMH = tempt->MAMH;
				nodee->STCLT = tempt->STCLT;
				nodee->STCTH = tempt->STCTH;
				nodee->TENMH = tempt->TENMH;
				xoa_node_MH(tempt, tempt->MAMH);
			}
		
		}
	if(premh.compare(nodee->MAMH) > 0) {
		xoa_node_MH(nodee->right, premh);
	}
	if(premh.compare(nodee->MAMH) < 0) {
		xoa_node_MH(nodee->left,premh);
	}
}

int checkMonhoc(MONHOC* nodee, string mh){
	if(nodee == NULL) return 0;
	if(mh.compare(nodee->MAMH) == 0) return 1;
	 return checkMonhoc(nodee->right,mh) + checkMonhoc(nodee->left,mh);
}
// find_Monhoc 
void find_Monhoc(MONHOC* nodee,MONHOC* &holder, int i,int &j) {
	if(nodee != NULL) {	
		find_Monhoc(nodee->left,holder, i, j);
		if(j == i) holder = nodee;
		j++;
		find_Monhoc(nodee->right,holder, i, j);
	}
		
}

int check_MH_inloptc(MONHOC* nodee,DsLOP ds){
	for(int i=0;i <= ds.n - 1 ; i++){
	if(nodee->MAMH.length() != 0 && nodee->MAMH.compare(ds.LOP[i]->MAMH) ==0 ) {
	return 1; 	
					 }
	
	}
	return -1;		
}

/*#### SINH VIEN DK #####*/
void init_DSSVDK(DSSVDK &dssvdk){
	dssvdk.phead = NULL;
	dssvdk.n = 0;
}
nodesvdk* getsvdk( string MASV){
	nodesvdk* newsvdk = new nodesvdk;
	newsvdk->data.MASV = MASV;
	newsvdk->data.DIEM = -1;
	newsvdk->pnext = NULL;
	return newsvdk;
}
void themsvdk(DSSVDK &dssvdk, nodesvdk* newsvdk){
	if(dssvdk.phead == NULL){
		dssvdk.phead = newsvdk;
		dssvdk.n ++;
		return;
	}
	else{
		nodesvdk* pe = dssvdk.phead;
		while(pe->pnext != NULL){
			pe = pe->pnext;
		}
		pe->pnext = newsvdk;
		dssvdk.n ++;
	}
}

/* #### LOP TIN CHI ##### */

void Them_sv_cho_loptc(DsLOP &dsl,int loptc, string mssv){
	for(int i = 0;i < dsl.n;i++){
		if(loptc == dsl.LOP[i]->MALOPTC){
			nodesvdk* svdk = getsvdk(mssv);
			themsvdk(dsl.LOP[i]->dssvdk, svdk);
			return;
		}	
	}
}
int check_sv_in_lop(DsLOP &ds, int loptc, string masv) {
	for(int i = 0; i < ds.n;i++) {
		if(ds.LOP[i]->MALOPTC == loptc) {
			for(nodesvdk* p = ds.LOP[i]->dssvdk.phead; p != NULL;p = p->pnext) {
				if(p->data.MASV == masv) {
					return 1;
				}
			}
		}
	}
	return -1;
}
void sua_sv_in_lop(DsLOP &ds,int loptc, string presv, SinhVienDK svdk){
	for(int i = 0; i < ds.n ;i++) {
		if(ds.LOP[i]->MALOPTC == loptc) {
			if(ds.LOP[i]->dssvdk.phead == NULL){
				return;
			}
			else {
				for(nodesvdk* k = ds.LOP[i]->dssvdk.phead;k != NULL;k = k->pnext){
					if(k->data.MASV == presv){
						k->data = svdk;
						return;				
					}
				}
			}
		}
	}
}

nodesvdk* find_sv_by_lop_vitri(DsLOP &ds,int loptc, int e) {
	for(int i = 0; i < ds.n ;i++) {
		if(ds.LOP[i]->MALOPTC == loptc) {
			if(ds.LOP[i]->dssvdk.phead == NULL) return NULL;
			if(e == 0) return ds.LOP[i]->dssvdk.phead;
			int j = 0;
			for(nodesvdk* k = ds.LOP[i]->dssvdk.phead;k != NULL;k = k->pnext, j++){
				if(j == e){
					return k;				
				}
			}
			return NULL;
		}
	}
	return NULL;
}
void Xoa_svdk(DsLOP &dsl,int loptc, int e){
	for(int i = 0;i < dsl.n; i++){
		if(dsl.LOP[i]->MALOPTC == loptc){
			if(dsl.LOP[i]->dssvdk.phead == NULL) {
				return;
			}	
			else {
				if(e == 0) {
					dsl.LOP[i]->dssvdk.phead = dsl.LOP[i]->dssvdk.phead->pnext;
					dsl.LOP[i]->dssvdk.n --;
				}
				else {
					int j = 0 ;
					for(nodesvdk* k = dsl.LOP[i]->dssvdk.phead;k->pnext != NULL;k = k->pnext, j++){
						nodesvdk* g = k->pnext;
						if(j + 1 == e){
							k->pnext = g->pnext;
							dsl.LOP[i]->dssvdk.n --;
							delete (g);
							return;
						}
					}
				}
			}
		}
	}
}

void init_LOPTC(DsLOP &ds) {
	for(int i = 0; i < MAXM ;i++) {
		ds.LOP[i] = new LOPTC;
		ds.LOP[i]->dssvdk.phead = NULL;
	}
}

void ThemLopTC(LOPTC* loptc, DsLOP &dslop) {
	loptc->MALOPTC = dslop.bosinh;
	nodesvdk* p = dslop.LOP[dslop.n]->dssvdk.phead;
	while(p != NULL) {
		nodesvdk* k = p;
		p = p->pnext;
		delete k;
	}
	dslop.LOP[dslop.n]->dssvdk.phead = NULL;
	loptc->dssvdk.n = 0;
	dslop.LOP[dslop.n] = loptc;
	dslop.n ++;
	dslop.bosinh++;
}

int checklop(int maloptc, DsLOP dslop){
	for(int i = 0; i < dslop.n; i++){
		if(dslop.LOP[i]->MALOPTC == maloptc){
			return i;
		}
	}
	return -1;
}


int XoaLopTC(DsLOP &ds,int i){
	if(i >= ds.n) return -1;
	ds.n --;
	for(int j = i; j < ds.n; j++){
		ds.LOP[j] = ds.LOP[j + 1];
	}
	return 1;
}
void SuaLopTC(DsLOP &ds, LOPTC* lopsua,int masua){
	for(int i = 0; i < ds.n; i++){
		if(ds.LOP[i]->MALOPTC == masua){
			ds.LOP[i] = lopsua;
			ds.LOP[i]->MALOPTC = masua;
			break;
		}
	}
}

LOPTC* findLOpById(DsLOP &ds, int malop) {
	for(int i = 0; i < ds.n ;i ++) {
		if(ds.LOP[i]->MALOPTC == malop) return ds.LOP[i];
	}
	return NULL;
}



/*#### SINH VIEN ####*/
void init_DSSV(DSSV &ds){
	ds.phead = NULL;
}

node* getnode(SinhVien sv){
	node* newnode = new node;
	newnode->data = sv;
	newnode->pnext = NULL;
	return newnode;
}
void themsinhvien(DSSV &ds,node* sv ){
	if(ds.phead == NULL){
		ds.phead = sv;
		ds.n ++;
	}
	
	else{
	node* pe = ds.phead;
		while(pe->pnext != NULL){
			pe = pe->pnext;
		}
	pe->pnext = sv;
	ds.n ++;
}
}
int checksv(DSSV &ds, string mssv){
	for(node* pe = ds.phead;pe != NULL;pe=pe->pnext){
		if(pe->data.MASV == mssv ){
			return 1;
		}
	}
	return -1;
}
node* find_sinhvien(DSSV &ds, int i) {
	if(ds.phead == NULL) return NULL;
	if(i == 0) return ds.phead;
	int j = 0;
	for(node* k = ds.phead;k != NULL;k = k->pnext, j++){
		if(j == i){
			return k;				
		}
	}
	return NULL;
}

node* find_sinhvien_by_masv(DSSV &ds, string masv) {
	for(node* k = ds.phead; k!= NULL; k = k->pnext) {
		if(k->data.MASV == masv) return k;
	}
	return NULL;
}

void xoasinhvien(DSSV &ds, int i){
	if(ds.phead == NULL){
		return;
	}
	else {
		if(i == 0) {
			ds.phead = ds.phead->pnext;
			ds.n --;
		}
		else {
			int j = 0 ;
			for(node* k = ds.phead;k != NULL;k = k->pnext, j++){
				//node* e = k->pnext;
				if(j  == i){
				
					k = k->pnext;
					ds.n --;
					//delete (e);
					return;
				}
			}
		}
	}
}


void suasinhvien(DSSV &ds, string mssv, SinhVien dt){
	if(ds.phead == NULL){
		return;
	}
	else {
		for(node* k = ds.phead;k != NULL;k = k->pnext){
			if(k->data.MASV == mssv){
				k->data = dt;
				return;				
			}
		}
	}
}

/* Nhap xuat file */
void doc_lop_file(DsLOP &ds) {
	ifs.open("LOPTC.txt");
	ifs >> ds.n;
	for(int i = 0; i < ds.n;i++) {
		ifs >> ds.LOP[i]->MALOPTC;
		ifs >> ds.LOP[i]->MAMH;
		ifs >> ds.LOP[i]->HOCKI;
		ifs >> ds.LOP[i]->NHOM;
		ifs >> ds.LOP[i]->NIENKHOA;
		ifs >> ds.LOP[i]->SOSV_MIN;
		ifs >> ds.LOP[i]->SOSV_MAX;
	}
	ifs.close();
}

void doc_dslop_file(DsLOP &ds) {
	for(int i = 0; i < ds.n;i++) {
		string s = "SVLOPTC[" + to_string(ds.LOP[i]->MALOPTC) +"].txt";
		ifs.open(s);
	//	cout << s;
		int sl = 0;
		ifs >> sl;
	//	cout << ds.LOP[i]->dssvdk.n;
		for(int j = 0; j < sl ; j++) {
			SinhVienDK dk;
			ifs >> dk.MASV;
			ifs >> dk.DIEM;
			nodesvdk* svdk = getsvdk(dk.MASV);
			svdk->data.DIEM = dk.DIEM;
			themsvdk(ds.LOP[i]->dssvdk, svdk);
			
		}
		ifs.close();
	}
}

void xuat_lop_file(DsLOP ds) {
	ofs.open("LOPTC.txt");
	ofs << ds.n << endl;
	for(int i = 0; i < ds.n;i++) {
		ofs << ds.LOP[i]->MALOPTC << endl;
		ofs << ds.LOP[i]->MAMH << endl;
		ofs << ds.LOP[i]->HOCKI << endl;
		ofs << ds.LOP[i]->NHOM << endl;
		ofs << ds.LOP[i]->NIENKHOA << endl;
		ofs << ds.LOP[i]->SOSV_MIN << endl;
		ofs << ds.LOP[i]->SOSV_MAX << endl;
	}
	ofs.close();
}

void xuat_svdk_file(int i ,DSSVDK dssvdk) {
	ofs.open("SVLOPTC[" + to_string(i) +"].txt");
	ofs << dssvdk.n << endl;
	for(nodesvdk* p = dssvdk.phead; p != NULL; p = p->pnext) {
		ofs << p->data.MASV << endl;
		ofs << p->data.DIEM << endl;
	}
	ofs.close();
} 

void xuat_sinhvien_file(DSSV dssv) {
	ofs.open("Sinhvien.txt");
	ofs << dssv.n << endl;
	for(node* p = dssv.phead ; p != NULL ; p = p->pnext) {
		ofs << p->data.MASV << endl;
		ofs << p->data.HO << endl;
		ofs << p->data.TEN << endl;
		ofs << p->data.PHAI << endl;
		ofs << p->data.SDT << endl;
		ofs << p->data.MALOP << endl;
		ofs << p->data.NAMNHAP << endl;

	}
	ofs.close();
}
void doc_sinhvien_file(DSSV &dssv) {
	ifs.open("Sinhvien.txt");
	int t;
	ifs >> t;
	for(int i = 0; i < t; i++) {
		SinhVien sv;
//		ifs.getline(sv.MASV, 100);
		ifs >> sv.MASV;
//	getline(ifs, sv.MASV);
		ifs >> sv.HO;
		ifs >> sv.TEN;
		ifs >> sv.PHAI;
		ifs >> sv.SDT;
		ifs >> sv.MALOP;
		ifs >> sv.NAMNHAP;
		node* no = getnode(sv);
		themsinhvien(dssv, no);
	}
	ifs.close();
}

void xuat_MH(MONHOC* mh) {
	if(mh == NULL) return;
	ofs << mh->MAMH << endl;
	ofs << mh->TENMH << endl;
	ofs << mh->STCLT << endl;
	ofs << mh->STCTH << endl;
	xuat_MH(mh->left);
	xuat_MH(mh->right); 
} 

void xuat_monhoc_file(DSMH ds) {
	ofs.open("C:\\Users\\tan10\\Desktop\\CTDL\\DSM.TXT");
	ofs << ds.n << endl;
	xuat_MH(ds.root);
	ofs.close();
}


void doc_monhoc_file(DSMH &ds) {
	ifs.open("C:\\Users\\tan10\\Desktop\\CTDL\\DSM.TXT");
	int t;
	ifs >> t;
	for(int i = 0;i < t ;i ++) {
		MONHOC k;
		ifs >> k.MAMH;
		ifs >> k.TENMH;
		ifs >> k.STCLT;
		ifs >> k.STCTH;
		MONHOC* gett = getNodeMH(k.MAMH, k.TENMH, k.STCLT, k.STCTH);
		addNodeMH(ds.root, gett, ds);
	}
	ifs.close();
}
//void addNodeMH(MONHOC* &nodee, MONHOC* p, DSMH &dsmh){
//	if(nodee == NULL){
//		nodee = p;
//		dsmh.n ++;
//		return;
//	}
//	else { 
//		if(p->MAMH.compare(nodee->MAMH) > 0) addNodeMH(nodee->right, p, dsmh);
//		else addNodeMH(nodee->left, p, dsmh);		
//	}
//}

