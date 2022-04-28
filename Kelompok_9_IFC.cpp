#include <iostream>
#include <stdlib.h>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <conio.h>
using namespace std;

struct barang{
    string nama;
    int impedance, ep_sens, quantity, harga;
    float pc_size;
};

struct Node{
	barang earphone;
	Node *next;
};

struct barangBelanjaan{
    string nama;
    int quantity, harga, subtotal;
};

struct NodeBelanjaan{
	barangBelanjaan earphone;
	NodeBelanjaan *next;
};

barang arrEarphone[1000];

Node *top = NULL;
NodeBelanjaan *top_belanjaan = NULL;

int banyakBarang(){
	int byk = 0;
	Node *temp = top;
    while (temp != NULL){
    	byk++;
		temp = temp->next;
	}
	return byk;
}

int banyakBelanjaan(){
	int byk = 0;
	NodeBelanjaan *temp = top_belanjaan;
    while (temp != NULL){
    	byk++;
		temp = temp->next;
	}
	return byk;
}

int strtoint(string x){
	int y = 0;
	stringstream degree(x);
	degree >> y;
	return y;
}

void readFile(){
	fstream myFile;
	string temp_var;
	myFile.open("dataEarphone.csv", ios::out | ios::in | ios::binary);
	if (!myFile.is_open()){
		myFile.open("dataEarphone.csv", ios::trunc | ios::out | ios::in | ios::binary);
	}
	while (!myFile.eof()){
		Node *data = new Node();
		getline(myFile,data->earphone.nama,',');
		getline(myFile, temp_var, ',');
		data->earphone.impedance = strtoint(temp_var);
		getline(myFile, temp_var, ',');
		data->earphone.ep_sens = strtoint(temp_var);
		getline(myFile, temp_var, ',');
		data->earphone.pc_size = atof(temp_var.c_str());
		getline(myFile, temp_var, ',');
		data->earphone.quantity = strtoint(temp_var);
		getline(myFile, temp_var, '\n');
		data->earphone.harga = strtoint(temp_var);
		data->next = NULL;
		if (myFile.eof()){
			break;
		}
        if (top == NULL){
        	top = data;
		}
		else{
			Node *temp = top;
			while (temp->next != NULL){
				temp = temp->next;
			}
			temp->next = data;
			data = NULL;
		}
	}
	myFile.close();
}

void writeFile(){
	fstream myFile;
	myFile.open("dataEarphone.csv", ios::trunc | ios::out | ios::in | ios::binary);
	Node *temp = top;
	while(temp != NULL){
		myFile << temp->earphone.nama << "," << temp->earphone.impedance << "," << temp->earphone.ep_sens << "," << temp->earphone.pc_size << "," << temp->earphone.quantity << "," << temp->earphone.harga << "\n";
		temp = temp->next;
	}
	myFile.close();
}

void tampilBarang(){
	int i = 0;
	cout << "+---------------------------------------------------------------------------------------------------------------------------------------------------------------+\n";
	cout << "|\tNo\t|\tNama\t\t|\tImpedance\t|\tSensitivity\t|\tPin Connector Size\t|\tQuantity\t|\tHarga\t|\n";
	cout << "+---------------+-----------------------+-----------------------+-----------------------+-------------------------------+-----------------------+---------------+\n";
	Node *temp = top;
	while (temp != NULL) {
    	if (temp->earphone.nama.length() <= 6){
    		cout << "|\t" << i+1 << "\t|\t" << temp->earphone.nama << "\t\t|\t" << temp->earphone.impedance << "\t\t|\t" << temp->earphone.ep_sens << "\t\t|\t" << temp->earphone.pc_size << "\t\t\t|\t" << temp->earphone.quantity << "\t\t|\t" << temp->earphone.harga << "\t|" << endl;	    		
		}
		else{
			cout << "|\t" << i+1 << "\t|\t" << temp->earphone.nama << "\t|\t" << temp->earphone.impedance << "\t\t|\t" << temp->earphone.ep_sens << "\t\t|\t" << temp->earphone.pc_size << "\t\t\t|\t" << temp->earphone.quantity << "\t\t|\t" << temp->earphone.harga << "\t|" << endl;
		}
		temp = temp->next;
		i++;
	}
	cout << char(212) << "---------------------------------------------------------------------------------------------------------------------------------------------------------------" << char(190) << "\n";
}

void tambahBarang(Node **top){
	Node* nodeBaru = new Node();
	cout << "> Masukkan nama earphone: "; getline(cin, nodeBaru->earphone.nama);
	cout << "> Masukkan impedance earphone: "; cin >> nodeBaru->earphone.impedance;
	cout << "> Masukkan sensitivity earphone: "; cin >> nodeBaru->earphone.ep_sens;
	cout << "> Masukkan pin connector size: "; cin >> nodeBaru->earphone.pc_size;
	cout << "> Masukkan quantity earphone: "; cin >> nodeBaru->earphone.quantity;
	cout << "> Masukkan harga earphone: "; cin >> nodeBaru->earphone.harga;
	nodeBaru->next = NULL;
	if(*top == NULL){
		*top = nodeBaru;
	}
	else{
		nodeBaru->next = *top;
		*top = nodeBaru;
	}
	writeFile();
}

void upJmlBrg(Node **top){
	int noGanti, newJml;
	while (true){
		int byk = banyakBarang();
		tampilBarang();
		cout << "> Masukkan nomor barang yang ingin diupdate jummlah barangnya: ";
		cin >> noGanti;
		if (noGanti <= byk && noGanti > 0){
			Node *temp = *top;
			for (int i = 0; i < noGanti - 1; i++){
				temp = temp->next;
			}
			cout << "> Masukkan jumlah barang yang baru: ";
			cin >> newJml;
			temp->earphone.quantity = newJml;
			writeFile();
			break;
		}
		else{
			system("CLS");
			cout << "> Nomor barang tidak ditemukan!\n\n";
		}
	}
}

void upHrgBrg(Node **top){
	int noGanti, newHrg;
	while (true){
		int byk = banyakBarang();
		tampilBarang();
		cout << "> Masukkan nomor barang yang ingin diupdate harga barangnya: ";
		cin >> noGanti;
		if (noGanti <= byk && noGanti > 0){
			Node *temp = *top;
			for (int i = 0; i < noGanti - 1; i++){
				temp = temp->next;
			}
			cout << "> Masukkan harga barang yang baru: ";
			cin >> newHrg;
			temp->earphone.harga = newHrg;
			writeFile();
			break;
		}
		else{
			system("CLS");
			cout << "> Nomor barang tidak ditemukan!\n\n";
		}
	}
}

void updateBarang(int jenisUpdate, int indeks){
	Node *temp = top;
	for (int i = 0; i < indeks; i++){
		temp = temp->next;
	}
	if (jenisUpdate > 0 && jenisUpdate <= 6 && jenisUpdate != 1 && jenisUpdate != 4){
		int temp_update;
		if (jenisUpdate == 2){
			cout << "> Masukkan impedance yang baru: ";
			cin >> temp_update;
			temp->earphone.impedance = temp_update;
		}
		else if (jenisUpdate == 3){
			cout << "> Masukkan earphone sensitivity yang baru: ";
			cin >> temp_update;
			temp->earphone.ep_sens = temp_update;
		}
		else if (jenisUpdate == 5){
			cout << "> Masukkan quantity yang baru: ";
			cin >> temp_update;
			temp->earphone.quantity = temp_update;
		}
		else if (jenisUpdate == 6){
			cout << "> Masukkan harga yang baru: ";
			cin >> temp_update;
			temp->earphone.harga = temp_update;
		}
	}
	else if (jenisUpdate == 1){
		string temp_update;
		cout << "> Masukkan nama yang baru: ";
		getline(cin, temp_update);
		temp->earphone.nama = temp_update;
	}
	else{
		float temp_update;
		cout << "> Masukkan pin connector size yang baru: ";
		cin >> temp_update;
		temp->earphone.pc_size = temp_update;
	}
	writeFile();
}

void hapusBarang(Node **top){
	Node *temp = *top;
	*top = (*top)->next;
	delete temp;
	writeFile();
}

void shellSwapElement(int j, int gap){
	(*(arrEarphone+j)).impedance = (*(arrEarphone+j-gap)).impedance;
	(*(arrEarphone+j)).nama = (*(arrEarphone+j-gap)).nama;
	(*(arrEarphone+j)).ep_sens = (*(arrEarphone+j-gap)).ep_sens;
	(*(arrEarphone+j)).pc_size = (*(arrEarphone+j-gap)).pc_size;
	(*(arrEarphone+j)).quantity = (*(arrEarphone+j-gap)).quantity;
	(*(arrEarphone+j)).harga = (*(arrEarphone+j-gap)).harga;
}

void shellSort(int n, string us, string usc){
	for (int gap = n/2; gap > 0; gap /= 2){
		for (int i = gap; i < n; i += 1){
			int temp = (*(arrEarphone+i)).impedance;
			string temp2 = (*(arrEarphone+i)).nama;
			int temp3 = (*(arrEarphone+i)).ep_sens;
			float temp4 = (*(arrEarphone+i)).pc_size;
			int temp5 = (*(arrEarphone+i)).quantity;
			int temp6 = (*(arrEarphone+i)).harga;
			int j;
			if (usc == "1"){
				if (us == "1"){
					for (j = i; j >= gap && (*(arrEarphone+j-gap)).impedance > temp; j -= gap){
						shellSwapElement(j,gap);
					}
				}
				else if (us == "2"){
					for (j = i; j >= gap && (*(arrEarphone+j-gap)).ep_sens > temp3; j -= gap){
						shellSwapElement(j,gap);
					}
				}
				else if (us == "3"){
					for (j = i; j >= gap && (*(arrEarphone+j-gap)).pc_size > temp4; j -= gap){
						shellSwapElement(j,gap);
					}
				}
				else if (us == "4"){
					for (j = i; j >= gap && (*(arrEarphone+j-gap)).quantity > temp5; j -= gap){
						shellSwapElement(j,gap);
					}
				}
				else if (us == "5"){
					for (j = i; j >= gap && (*(arrEarphone+j-gap)).harga > temp6; j -= gap){
						shellSwapElement(j,gap);
					}
				}
			}
			else if (usc == "2"){
				if (us == "1"){
					for (j = i; j >= gap && (*(arrEarphone+j-gap)).impedance < temp; j -= gap){
						shellSwapElement(j,gap);
					}
				}
				else if (us == "2"){
					for (j = i; j >= gap && (*(arrEarphone+j-gap)).ep_sens < temp3; j -= gap){
						shellSwapElement(j,gap);
					}
				}
				else if (us == "3"){
					for (j = i; j >= gap && (*(arrEarphone+j-gap)).pc_size < temp4; j -= gap){
						shellSwapElement(j,gap);
					}
				}
				else if (us == "4"){
					for (j = i; j >= gap && (*(arrEarphone+j-gap)).quantity < temp5; j -= gap){
						shellSwapElement(j,gap);
					}
				}
				else if (us == "5"){
					for (j = i; j >= gap && (*(arrEarphone+j-gap)).harga < temp6; j -= gap){
						shellSwapElement(j,gap);
					}
				}
			}
			(*(arrEarphone+j)).impedance = temp;
			(*(arrEarphone+j)).nama = temp2;
			(*(arrEarphone+j)).ep_sens = temp3;
			(*(arrEarphone+j)).pc_size = temp4;
			(*(arrEarphone+j)).quantity = temp5;
			(*(arrEarphone+j)).harga = temp6;
		}
	}
}

void sortBarang(Node **top){
    while(true){
    	string menuSort;
    	cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
    	cout << "<         Urut Sesuai        >\n";
    	cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
    	cout << "< [1] Impedance              >\n";
    	cout << "< [2] Earphone Sensitivity   >\n";
    	cout << "< [3] Pin Connector Size     >\n";
    	cout << "< [4] Quantity               >\n";
    	cout << "< [5] Harga                  >\n";
    	cout << "< [6] Kembali                >\n";
    	cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
    	cout << "> Masukkan menu: ";
    	cin >> menuSort;
    	system("CLS");
    	if (menuSort == "1" || menuSort == "2" || menuSort == "3" || menuSort == "4" || menuSort == "5"){
    	    while (true){
				string sortSecara;
				cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
				cout << "<         Urut Secara        >\n";
				cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
				cout << "< [1] Ascending              >\n";
				cout << "< [2] Descending             >\n";
				cout << "< [3] Kembali                >\n";
				cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
				cout << "> Masukkan menu: ";
				cin >> sortSecara;
				system("CLS");
				if (sortSecara == "1" || sortSecara == "2"){
					Node* temp = *top;
					Node* temp2 = *top;
					int i = 0;
					while(temp != NULL){
					    (*(arrEarphone+i)).nama = temp->earphone.nama;
					    (*(arrEarphone+i)).impedance = temp->earphone.impedance;
					    (*(arrEarphone+i)).ep_sens = temp->earphone.ep_sens;
					    (*(arrEarphone+i)).pc_size = temp->earphone.pc_size;
					    (*(arrEarphone+i)).quantity = temp->earphone.quantity;
					    (*(arrEarphone+i)).harga = temp->earphone.harga;
					    temp = temp->next;
					    i++;
					}
					shellSort(i, menuSort, sortSecara);
					i = 0;
					while(temp2 != NULL){
						temp2->earphone.nama = (*(arrEarphone+i)).nama;
						temp2->earphone.impedance = (*(arrEarphone+i)).impedance;
						temp2->earphone.ep_sens = (*(arrEarphone+i)).ep_sens;
						temp2->earphone.pc_size = (*(arrEarphone+i)).pc_size;
						temp2->earphone.quantity = (*(arrEarphone+i)).quantity;
						temp2->earphone.harga = (*(arrEarphone+i)).harga;
						temp2 = temp2->next;
						i++;
					}
					cout << "> Barang berhasil diurutkan!\n\n";
				}
				else if (sortSecara == "3"){
				    break;
				}
				else{
				    cout << "> Menu tidak ditemukan !\n\n";
				}
    	    }
    	}
    	else if (menuSort == "6"){
    	    break;
    	}
    	else{
    	    cout << "> Menu tidak ditemukan !\n\n";
    	}
    }
}

int min(int x, int y) {
	if( x <= y){
		return x;
	}
	else{
		return y;
	}
}

int jumpSearchFloat(float x, int n, string cs){
	int step = sqrt(n);
	int prev = 0;
	while ((*(arrEarphone+min(step, n)-1)).pc_size < x){
		prev = step;
		step += sqrt(n);
		if (prev >= n)
		return -1;
	}
	while ((*(arrEarphone+prev)).pc_size < x){
		prev++;
		if (prev == min(step, n)){
			return -1;
		}
	}
	if ((*(arrEarphone+prev)).pc_size == x){
		return prev;
	}
	return -1;
}

int jumpSearch(int x, int n, string cs){
	int step = sqrt(n);
	int prev = 0;
	if (cs == "1"){
		while ((*(arrEarphone+min(step, n)-1)).impedance < x){
			prev = step;
			step += sqrt(n);
			if (prev >= n)
			return -1;
		}
		while ((*(arrEarphone+prev)).impedance < x){
			prev++;
			if (prev == min(step, n)){
				return -1;
			}
		}
		if ((*(arrEarphone+prev)).impedance == x){
			return prev;
		}
	}
	else if (cs == "2"){
		while ((*(arrEarphone+min(step, n)-1)).ep_sens < x){
			prev = step;
			step += sqrt(n);
			if (prev >= n)
			return -1;
		}
		while ((*(arrEarphone+prev)).ep_sens < x){
			prev++;
			if (prev == min(step, n)){
				return -1;
			}
		}
		if ((*(arrEarphone+prev)).ep_sens == x){
			return prev;
		}
	}
	else if (cs == "4"){
		while ((*(arrEarphone+min(step, n)-1)).quantity < x){
			prev = step;
			step += sqrt(n);
			if (prev >= n)
			return -1;
		}
		while ((*(arrEarphone+prev)).quantity < x){
			prev++;
			if (prev == min(step, n)){
				return -1;
			}
		}
		if ((*(arrEarphone+prev)).quantity == x){
			return prev;
		}
	}
	else if (cs == "5"){
		while ((*(arrEarphone+min(step, n)-1)).harga < x){
			prev = step;
			step += sqrt(n);
			if (prev >= n)
			return -1;
		}
		while ((*(arrEarphone+prev)).harga < x){
			prev++;
			if (prev == min(step, n)){
				return -1;
			}
		}
		if ((*(arrEarphone+prev)).harga == x){
			return prev;
		}
	}
	return -1;
}

void searchBarang(Node **top){
	while (true){
		string menuSearch;
		cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
		cout << "<         Cari Sesuai        >\n";
		cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
		cout << "< [1] Impedance              >\n";
		cout << "< [2] Earphone Sensitivity   >\n";
		cout << "< [3] Pin Connector Size     >\n";
		cout << "< [4] Quantity               >\n";
		cout << "< [5] Harga                  >\n";
		cout << "< [6] Kembali                >\n";
		cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
		cout << "> Masukkan menu: ";
		cin >> menuSearch;
		system("CLS");
		if (menuSearch == "1" || menuSearch == "2" || menuSearch == "3" || menuSearch == "4" || menuSearch == "5"){
			Node* temp = *top;
			Node* temp2 = *top;
			int index, i = 0;
			while(temp != NULL){
			    (*(arrEarphone+i)).nama = temp->earphone.nama;
			    (*(arrEarphone+i)).impedance = temp->earphone.impedance;
			    (*(arrEarphone+i)).ep_sens = temp->earphone.ep_sens;
			    (*(arrEarphone+i)).pc_size = temp->earphone.pc_size;
			    (*(arrEarphone+i)).quantity = temp->earphone.quantity;
			    (*(arrEarphone+i)).harga = temp->earphone.harga;
			    temp = temp->next;
			    i++;
			}
			shellSort(i, menuSearch, "1");
			i = 0;
			while(temp2 != NULL){
				temp2->earphone.nama = (*(arrEarphone+i)).nama;
				temp2->earphone.impedance = (*(arrEarphone+i)).impedance;
				temp2->earphone.ep_sens = (*(arrEarphone+i)).ep_sens;
				temp2->earphone.pc_size = (*(arrEarphone+i)).pc_size;
				temp2->earphone.quantity = (*(arrEarphone+i)).quantity;
				temp2->earphone.harga = (*(arrEarphone+i)).harga;
				temp2 = temp2->next;
				i++;
			}
			if (menuSearch == "1"){
				int dicari;
				cout << "> Masukkan Impedance: ";
				cin >> dicari;
				index = jumpSearch(dicari, banyakBarang(), menuSearch);
			}
			else if (menuSearch == "2"){
				int dicari;
				cout << "> Masukkan Earphone Sensitivity: ";
				cin >> dicari;
				index = jumpSearch(dicari, banyakBarang(), menuSearch);
			}
			else if (menuSearch == "3"){
				float dicari;
				cout << "> Masukkan Pin Connector Size Earphone: ";
				cin >> dicari;
				index = jumpSearchFloat(dicari, banyakBarang(), menuSearch);
			}
			else if (menuSearch == "4"){
				int dicari;
				cout << "> Masukkan Quantity Earphone: ";
				cin >> dicari;
				index = jumpSearch(dicari, banyakBarang(), menuSearch);
			}
			else if (menuSearch == "5"){
				int dicari;
				cout << "> Masukkan Harga Earphone: ";
				cin >> dicari;
				index = jumpSearch(dicari, banyakBarang(), menuSearch);
			}
			system("CLS");
			if (index == -1){
				cout << "> Data tidak ditemukan!\n\n";
			}
			else{
				cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------+\n";
				cout << "|\tNama\t\t|\tImpedance\t|\tSensitivity\t|\tPin Connector Size\t|\tQuantity\t|\tHarga\t|\n";
				cout << "+-----------------------+-----------------------+-----------------------+-------------------------------+-----------------------+---------------+\n";
		    	if ((*(arrEarphone+index)).nama.length() <= 6){
		    		cout << "|\t" << (*(arrEarphone+index)).nama << "\t\t|\t" << (*(arrEarphone+index)).impedance << "\t\t|\t" << (*(arrEarphone+index)).ep_sens << "\t\t|\t" << (*(arrEarphone+index)).pc_size << "\t\t\t|\t" << (*(arrEarphone+index)).quantity << "\t\t|\t" << (*(arrEarphone+index)).harga << "\t|" << endl;
				}
				else{
					cout << "|\t" << (*(arrEarphone+index)).nama << "\t|\t" << (*(arrEarphone+index)).impedance << "\t\t|\t" << (*(arrEarphone+index)).ep_sens << "\t\t|\t" << (*(arrEarphone+index)).pc_size << "\t\t\t|\t" << (*(arrEarphone+index)).quantity << "\t\t|\t" << (*(arrEarphone+index)).harga << "\t|" << endl;
				}
				cout << char(212) << "-----------------------------------------------------------------------------------------------------------------------------------------------" << char(190) << "\n\n";
			}
		}
		else if (menuSearch == "6"){
			break;
		}
		else{
			cout << "> Menu tidak ditemukan !\n\n";
		}
	}
}

void admin(){
	while (true){
		int byk = banyakBarang();
		string menuAdmin;
		cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
		cout << "<         Menu Admin         >\n";
		cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
		cout << "< [1] Tampil Barang          >\n";
		cout << "< [2] Tambah Barang          >\n";
		cout << "< [3] Update Barang          >\n";
		cout << "< [4] Hapus Barang           >\n";
		cout << "< [5] Urutkan Barang         >\n";
		cout << "< [6] Cari Barang            >\n";
		cout << "< [7] Kembali                >\n";
		cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
		cout << "> Masukkan menu: ";
		cin >> menuAdmin;
		cin.ignore(1,'\n');
		system("CLS");
		if (menuAdmin == "1"){
			if (byk > 0){
				tampilBarang();
			    cout << "> Tekan apa saja untuk kembali...";
			    getch();
			    system("CLS");
			}
			else{
				cout << "> Tidak ada barang. Silahkan tambahkan barang di menu Tambah Barang!\n\n";
			}
		}
		else if (menuAdmin == "2"){
			tambahBarang(&top);
			system("CLS");
			cout << "> Data berhasil ditambahkan!\n\n";
		}
		else if (menuAdmin == "3"){
			if (byk > 0){
				while (true){
					string menuUpdateBarang;
					cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
					cout << "<    Menu Update Barang    >\n";
					cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
					cout << "< [1] Nama                 >\n";
					cout << "< [2] Impedance            >\n";
					cout << "< [3] Earphone Sensitivity >\n";
					cout << "< [4] Pin Connector Size   >\n";
					cout << "< [5] Quantity             >\n";
					cout << "< [6] Harga                >\n";
					cout << "< [7] Kembali              >\n";
					cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
					cout << "> Masukkan menu: ";
					cin >> menuUpdateBarang;
					cin.ignore(1,'\n');
					system("CLS");
					if (menuUpdateBarang == "1" || menuUpdateBarang == "2" || menuUpdateBarang == "3" || menuUpdateBarang == "4" || menuUpdateBarang == "5" || menuUpdateBarang == "6"){
						while (true){
							int indeks;
							tampilBarang();
							cout << "> Masukkan indeks barang yang ingin di update: ";
							cin >> indeks;
							system("CLS");
							if (indeks > 0 && indeks <= byk){
								cin.ignore(1,'\n');
								updateBarang(strtoint(menuUpdateBarang), indeks - 1);
								system("CLS");
								cout << "> Barang berhasil di update!\n\n";
								break;
							}
							else{
								cout << "> Indeks barang tidak ditemukan!\n\n";
							}
						}
					}
					else if (menuUpdateBarang == "7"){
						break;
					}
					else {
						cout << "> Menu tidak di temukan !\n\n";
					}
				}
			}
			else{
				cout << "> Tidak ada barang. Silahkan tambahkan barang di menu Tambah Barang!\n\n";
			}
		}
		else if (menuAdmin == "4"){
			if (byk > 0){
				hapusBarang(&top);
				system("CLS");
				cout << "> Barang berhasil di hapus!\n\n";
			}
			else{
				cout << "> Tidak ada barang!\n\n";
			}
		}
		else if (menuAdmin == "5"){
			if (byk > 1){
				sortBarang(&top);
			}
			else if (byk == 1){
				cout << "> Barang tidak perlu diurutkan!\n\n";
			}
			else {
				cout << "> Tidak ada barang!\n\n";
			}
		}
		else if (menuAdmin == "6"){
			if (byk > 0){
				searchBarang(&top);
			}
			else{
				cout << "> Tidak ada barang!\n\n";
			}
		}
		else if (menuAdmin == "7"){
			break;
		}
		else{
			cout << "> Menu tidak ditemukan !\n\n";
		}
	}
}

void tampilBelanjaan(){
	int i = 0;
	cout << "+---------------------------------------------------------------------------------------------------------------+\n";
	cout << "|\tNo\t|\tNama\t\t|\tQuantity\t|\tHarga\t\t|\tSubtotal\t|\n";
	cout << "+---------------+-----------------------+-----------------------+-----------------------+-----------------------+\n";
	NodeBelanjaan *temp = top_belanjaan;
	while (temp != NULL) {
    	if (temp->earphone.nama.length() <= 6){
    		cout << "|\t" << i+1 << "\t|\t" << temp->earphone.nama << "\t\t|\t" << temp->earphone.quantity << "\t\t|\t" << temp->earphone.harga << "\t\t|\t" << temp->earphone.subtotal << "\t\t|" << endl;	    		
		}
		else{
			cout << "|\t" << i+1 << "\t|\t" << temp->earphone.nama << "\t|\t" << temp->earphone.quantity << "\t\t|\t" << temp->earphone.harga << "\t\t|\t" << temp->earphone.subtotal << "\t\t|" << endl;
		}
		temp = temp->next;
		i++;
	}
	cout << char(212) << "---------------------------------------------------------------------------------------------------------------" << char(190) << "\n";
}

void tambahBelanjaan(NodeBelanjaan **top_belanjaan, Node **top, int indeks){
	int quantity;
	Node *temp = *top;
	NodeBelanjaan *temp2 = *top_belanjaan;
	for (int i = 0; i < indeks; i++){
		temp = temp->next;
	}
	while (true){
		cout << "> Masukkan jumlah barang: ";
		cin >> quantity;
		if (quantity > 0 && quantity <= temp->earphone.quantity){
			while (temp2 != NULL){
				if (temp2->earphone.nama == temp->earphone.nama){
					temp2->earphone.quantity += quantity;
					temp->earphone.quantity -= quantity;
					temp2->earphone.subtotal = temp2->earphone.quantity * temp2->earphone.harga;
					return;
				}
				temp2 = temp2->next;
			}
			NodeBelanjaan *nodeBaru = new NodeBelanjaan();
			nodeBaru->earphone.nama = temp->earphone.nama;
			nodeBaru->earphone.quantity = quantity;
			temp->earphone.quantity -= quantity;
			nodeBaru->earphone.harga = temp->earphone.harga;
			nodeBaru->earphone.subtotal = nodeBaru->earphone.quantity * nodeBaru->earphone.harga;
			nodeBaru->next = NULL;
			if(*top_belanjaan == NULL){
				*top_belanjaan = nodeBaru;
			}
			else{
				nodeBaru->next = *top_belanjaan;
				*top_belanjaan = nodeBaru;
			}
			return;
		}
		else{
			cout << "> Masukkan jumlah barang yang benar!\n\n";
		}
	}
}

void updateBelanjaan(int indeks){
	int quantity;
	NodeBelanjaan *temp = top_belanjaan;
	Node *temp2 = top;
	for (int i = 0; i < indeks; i++){
		temp = temp->next;
	}
	while (temp2->earphone.nama != temp->earphone.nama){
		temp2 = temp2->next;
	}
	temp2->earphone.quantity += temp->earphone.quantity;
	cout << "> Jumlah barang yang tersedia: " << temp2->earphone.quantity << endl;
	while (true){
		cout << "> Masukkan jumlah barang yang baru: ";
		cin >> quantity;
		if (quantity > 0 && quantity <= temp2->earphone.quantity){
			temp->earphone.quantity = quantity;
			temp2->earphone.quantity -= quantity;
			temp->earphone.subtotal = temp->earphone.quantity * temp->earphone.harga;
			break;
		}
		else{
			cout << "> Masukkan jumlah barang yang benar!\n\n";
		}
	}
}

void hapusBelanjaan(NodeBelanjaan **top_belanjaan){
	Node *temp_brg = top;
	while ((*top_belanjaan)->earphone.nama != temp_brg->earphone.nama){
		temp_brg = temp_brg->next;
	}
	temp_brg->earphone.quantity += (*top_belanjaan)->earphone.quantity;
	NodeBelanjaan *temp_blj = *top_belanjaan;
	*top_belanjaan = (*top_belanjaan)->next;
	delete temp_blj;
}

void hapusTransaksi(){
	NodeBelanjaan *temp = top_belanjaan;
	while (top_belanjaan != NULL){
		top_belanjaan = top_belanjaan->next;
	}
	delete temp;
}

void transaksi(){
	int total, bayar, kembalian;
	NodeBelanjaan *temp = top_belanjaan;
	while (temp != NULL){
		total += temp->earphone.subtotal;
		temp = temp->next;
	}
	cout << "> Total yang harus dibayar: " << total << endl;
	cout << "> Masukkan bayaran: "; cin >> bayar;
	system("CLS");
	cout << "+---------------------------------------------------------------------------------------------------------------+\n";
	cout << "|                                                     STRUK                                                     |\n";
	tampilBelanjaan();
	cout << "\n> Total: " << total << endl;
	cout << "> Bayaran: " << bayar << endl;
	cout << "> Kembalian: " << bayar - total << endl;
	cout << "> Terima Kasih\n";
    cout << "> Tekan apa saja untuk kembali...";
    getch();
    hapusTransaksi();
	writeFile();
    system("CLS");
}

void kasir(){
	while (true){
		string menuKasir;
		int byk_brg = banyakBarang();
		int byk_blj = banyakBelanjaan();
		cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
		cout << "<             Menu Kasir             >\n";
		cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
		cout << "< [1] Tampil Stock Barang            >\n";
		cout << "< [2] Tampil Barang Belanjaan        >\n";
		cout << "< [3] Tambah Barang Belanjaan        >\n";
		cout << "< [4] Update Jumlah Barang Belanjaan >\n";
		cout << "< [5] Hapus Barang Belanjaan         >\n";
		cout << "< [6] Transaksi                      >\n";
		cout << "< [7] Kembali                        >\n";
		cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
		cout << "> Masukkan menu: ";
		cin >> menuKasir;
		system("CLS");
		if (menuKasir == "1"){
			while (true){
				string menuTampilStockBarang;
				cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
				cout << "<         Tampil Stock Barang         >\n";
				cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
				cout << "< [1] Semua                           >\n";
				cout << "< [2] Cari                            >\n";
				cout << "< [3] Kembali                         >\n";
				cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
				cout << "> Masukkan menu: ";
				cin >> menuTampilStockBarang;
				system("CLS");
				if (menuTampilStockBarang == "1" || menuTampilStockBarang == "2"){
					if (menuTampilStockBarang == "1"){
						tampilBarang();
					    cout << "> Tekan apa saja untuk kembali...";
					    getch();
					    system("CLS");
					}
					else if (menuTampilStockBarang == "2"){
						searchBarang(&top);
					}
				}
				else if (menuTampilStockBarang == "3"){
					break;
				}
			}
		}
		else if (menuKasir == "2"){
			if (byk_blj > 0){
				tampilBelanjaan();
			    cout << "> Tekan apa saja untuk kembali...";
			    getch();
			    system("CLS");
			}
			else{
				cout << "> Tidak ada belanjaan. Silahkan tambahkan belanjaan di menu Tambah Barang Belanjaan!\n\n";
			}
		}
		else if (menuKasir == "3"){
			while (true){
				int indeks;
				tampilBarang();
				cout << "> Masukkan nomor barang yang dibeli: ";
				cin >> indeks;
				if (indeks <= byk_brg && indeks > 0){
					tambahBelanjaan(&top_belanjaan, &top, indeks-1);
					system("CLS");
					cout << "> Barang Belanjaan berhasil di tambahkan!\n\n";
					break;
				}
				else{
					system("CLS");
					cout << "> Nomor barang tidak ditemukan!\n\n";
				}
			}
		}
		else if (menuKasir == "4"){
			if (byk_blj > 0){
				while (true){
					int indeks;
					tampilBelanjaan();
					cout << "> Masukkan nomor barang yang ingin di update: ";
					cin >> indeks;
					system("CLS");
					if (indeks <= byk_blj && indeks > 0){
						cin.ignore(1,'\n');
						updateBelanjaan(indeks-1);
						system("CLS");
						cout << "> Banyak Barang Belanjaan berhasil di update!\n\n";
						break;
					}
					else{
						cout << "> Nomor barang tidak ditemukan!\n\n";
					}
				}
			}
			else{
				cout << "> Tidak ada belanjaan. Silahkan tambahkan belanjaan di menu Tambah Barang Belanjaan!\n\n";
			}
		}
		else if (menuKasir == "5"){
			if (byk_blj > 0){
				hapusBelanjaan(&top_belanjaan);
				system("CLS");
				cout << "> Barang Belanjaan berhasil di hapus!\n\n";
			}
			else{
				cout << "> Tidak ada belanjaan. Silahkan tambahkan belanjaan di menu Tambah Barang Belanjaan!\n\n";
			}
		}
		else if (menuKasir == "6"){
			string kembali;
			while (true){
				cout << "> Note: Jika mengonfirmasi ya, maka transaksi tidak bisa dibatalkan!\n";
				cout << "> Konfirmasi kembali (y/n): ";
				cin >> kembali;
				system("CLS");
				if (kembali == "y" || kembali == "n"){
					break;
				}
			}
			if (kembali == "y"){
				transaksi();
			}
		}
		else if (menuKasir == "7"){
			string kembali;
			while (true){
				cout << "> Note: Semua barang belanjaan akan dihapus jika kembali ke menu awal!\n";
				cout << "> Konfirmasi kembali (y/n): ";
				cin >> kembali;
				system("CLS");
				if (kembali == "y" || kembali == "n"){
					break;
				}
			}
			if (kembali == "y"){
				hapusTransaksi();
				top = NULL;
				readFile();
				break;
			}
		}
		else{
			cout << "> Menu tidak ditemukan !\n\n";
		}
	}
}

bool login(string as){
	string username, password = "";
	if (as == "1"){
		for (int i = 0; i <= 2; i++){
			cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
			cout << "<             Login Admin             >\n";
			cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
			cout << "> Masukkan username: ";
			fflush(stdin); getline(cin, username);
			cout << "> Masukkan password: ";
			char huruf;
			int j = 0;
			int pass = 55;
			while (true){
				huruf = getch();
				if ((huruf >= 'a' && huruf <= 'z') || (huruf >= 'A' && huruf <= 'Z') || (huruf >= '0' && huruf <= '9')){
					password += huruf;
					j++;
					pass++;
					cout << "*";
				}
				if (huruf == '\b'){
					cout << "\b \b";
					if (pass > 55){
						pass--;
						j--;
						password.erase(j,1);
					}
				}
				if (huruf == '\r'){
					break;
				}
			}
			system("CLS");
			if (username == "admin" && password == "admin"){
				return true;
			}
			else {
				cout << "> Username atau Password salah!\n\n";
			}
		}
	}
	else if (as == "2"){
		for (int i = 0; i <= 2; i++){
			cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
			cout << "<              Login Kasir             >\n";
			cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
			cout << "> Masukkan username: ";
			fflush(stdin); getline(cin, username);
			cout << "> Masukkan password: ";
			char huruf;
			int j = 0;
			int pass = 55;
			while (true){
				huruf = getch();
				if ((huruf >= 'a' && huruf <= 'z') || (huruf >= 'A' && huruf <= 'Z') || (huruf >= '0' && huruf <= '9')){
					password += huruf;
					j++;
					pass++;
					cout << "*";
				}
				if (huruf == '\b'){
					cout << "\b \b";
					if (pass > 55){
						pass--;
						j--;
						password.erase(j,1);
					}
				}
				if (huruf == '\r'){
					break;
				}
			}
			system("CLS");
			if (username == "kasir" && password == "kasir"){
				return true;
			}
			else {
				cout << "> Username atau Password salah!\n\n";
			}
		}
	}
	cout << "> Batas login habis!\n\n";
	cout << "Tekan apa saja untuk melanjutkan...";
	getch();
	return false;
}

int main(){
	readFile();
	while (true){
		string mainMenu;
		cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
		cout << "<        Toko Earphone        >\n";
		cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
		cout << "< [1] Admin                   >\n";
		cout << "< [2] Kasir                   >\n";
		cout << "< [3] Keluar                  >\n";
		cout << "<%%%%%%%%%%%%%%%%%%%%%%%%%%%%%>\n";
		cout << "> Masukkan menu: ";
		cin >> mainMenu;
		system("CLS");
		if (mainMenu == "1"){
			if (login(mainMenu)){
				admin();
			}
		}
		else if (mainMenu == "2"){
			int byk = banyakBarang();
			if (byk > 0){
				if (login(mainMenu)){
					kasir();
				}
			}
			else{
				cout << "> Tidak ada barang!\n\n";
			}
		}
		else if (mainMenu == "3"){
			cout << "d888888b d88888b d8888b. d888888b .88b  d88.  .d8b.         db   dD  .d8b.  .d8888. d888888b db   db" << endl;
			cout << "`~~88~~' 88'     88  `8D   `88'   88'YbdP`88 d8' `8b        88 ,8P' d8' `8b 88'  YP   `88'   88   88" << endl;
			cout << "   88    88ooooo 88oobY'    88    88  88  88 88ooo88        88,8P   88ooo88 `8bo.      88    88ooo88" << endl;
			cout << "   88    88~~~~~ 88`8b      88    88  88  88 88~~~88        88`8b   88~~~88   `Y8b.    88    88~~~88" << endl;
			cout << "   88    88.     88 `88.   .88.   88  88  88 88   88        88 `88. 88   88 db   8D   .88.   88   88" << endl;
			cout << "   YP    Y88888P 88   YD Y888888P YP  YP  YP YP   YP        YP   YD YP   YP `8888Y' Y888888P YP   YP" << endl;
			writeFile();
			break;
		}
		else{
			cout << "> Menu tidak ditemukan !\n\n";
		}
	}
    return 0;
}
