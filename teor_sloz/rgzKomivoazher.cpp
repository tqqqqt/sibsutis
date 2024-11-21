#include<iostream>
#include<fstream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

int** mas=NULL;
int record = 0;

int C(int x, int y) {
	return mas[x][y]!=9999 ? mas[x][y] : 0;
}

int InitRecord(int n) {
	int temp = 0, kolvo = n - 1;
	int* check = new int[n];
	for(int i=0;i<n;i++) check[i]=0;
	check[0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if(!C(i,j)) continue;
			if (check[j] == 0) {
				check[j] = 1;
				temp += C(i, j);
				kolvo--;
				break;
			}
		}
	}
	if (kolvo) return 1;
	record = temp;
	return 0;
}

map<int, int> InitMap(vector<int>& points) {
	map<int, int> newMap;
	for (int i = 0; i < points.size(); i++) newMap[points[i]] = 1;
	return newMap;
}

int** InitNewMas(int n, vector<int>& curPoints, int newPoint, int* sX, int* sY) {
	int str = n - curPoints.size(), stlb = curPoints.size() > 1 ? n - (curPoints.size() - 1) - 1 : n - 1;
	str=str<0 ? 0 : str;
	stlb=stlb<0 ? 0 : stlb;
	*sX = str;
	*sY = stlb;
	int** newMas = new int* [str];
	for (int i = 0; i < str; i++){
		newMas[i] = new int[stlb];
		for(int j=0;j<stlb;j++) newMas[i][j]=0;	
	}
	map<int, int> mpStr, mpStlb;
	for (int i = 0; i < curPoints.size(); i++) mpStr[curPoints[i]] = 1;
	for (int i = 1; i < curPoints.size(); i++) mpStlb[curPoints[i]] = 1;
	mpStlb[newPoint] = 1;
	int x = 0, y = 0;
	for (int i = 0; i < n; i++) {
		if (!mpStr[i]) {
			for (int j = 0; j < n; j++) {
				if (!mpStlb[j]) {
					newMas[x][y] = mas[i][j];
					y++;
				}
			}
			x++;
			y = 0;
		}
	}
	return newMas;
}

int* FindMinStr(int** mass, int sizeX, int sizeY) {
	int* masss = new int[sizeX];
	for(int i=0;i<sizeX;i++) masss[i]=0;
	int temp = 999999;
	for (int i = 0; i < sizeX; i++) {
		temp = 9999;
		for (int j = 0; j < sizeY; j++) {
			//if(mass[i][j]!=9999) 
			temp = min(temp, mass[i][j]);
		}
		masss[i] = temp;
	}
	return masss;
}

void SubMinStr(int** newMas, int* masMin, int sizeX, int sizeY) {
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) newMas[i][j] -= masMin[i];
	}
}

int* FindMinStd(int** mass, int sizeX, int sizeY) {
	int* masss = new int[sizeY];
	for(int i=0;i<sizeY;i++) masss[i]=0;
	int temp=0;
	for (int i = 0; i < sizeX; i++) {
		temp = 999999;
		for (int j = 0; j < sizeY; j++) temp = min(temp, mass[j][i]);
		masss[i] = temp;
	}
	return masss;
}

int CheckForH(int n, vector<int>& curPoints, int newPoint) {
	int sizeX = 0, sizeY = 0;
	int** newMas = InitNewMas(n, curPoints, newPoint, &sizeX, &sizeY);

	int* minStr = FindMinStr(newMas, sizeX, sizeY);
	SubMinStr(newMas, minStr, sizeX, sizeY);
	int* minStd = FindMinStd(newMas, sizeX, sizeY);

	int resZn=0;
	for (int i = 1; i < curPoints.size(); i++) resZn += C(curPoints[i - 1], curPoints[i]);
	for (int i = 0; i < sizeX; i++) resZn += minStr[i];
	for (int i = 0; i < sizeY; i++) resZn += minStd[i];
//	delete[] newMas;
//	delete[] minStr;
//	delete[] minStd;
	return resZn;
}

int CheckPath(vector<int>& points) {
	int res = 0;
	for (int i = 1; i < points.size(); i++) res += C(points[i - 1], points[i]);
	return res;
}

int Komivoazher(int n, int curentKPoints, vector<int>& curPoints, int curentH) {
	std::vector<int> points = curPoints;
	map<int, int> checkPoints ;//= InitMap(points);
	
	//debug
	for(int i=0;i<points.size();i++) checkPoints[points[i]]=1;
	cout<<"{";
	for (int i = 0; i < points.size(); i++) cout << points[i] << "->";
	cout<<"}\n";
	//
	
	for (int i = 0; i < n; i++) {
		cout<<"["<<i<<"]";
		if(checkPoints[i] || !C(points[points.size()-1],i)) continue;
		cout<<"be";
		try{
			points.push_back(i);
		}
		catch(const char* error_message){
			cout<<error_message;
		}
		//points.push_back(i);
		cout<<"st";
		int tempH = CheckForH(n, points, i);
		cout<<"en";
		if (tempH <= record) {
//			cout<<"*";
			checkPoints[i] = 1;
			Komivoazher(n, curentKPoints + 1, points, tempH);
		}
		points.erase(points.end()-1);
//		cout<<"["<<i<<"]-"<<points.size()<<"]\n";
	}
	cout<<"endKomi\n";
//	cout<<points.size()<<'\n';
	if (points.size() < n) return 0;
	//
	int tempPoint=points[0];
	points.push_back(tempPoint);
	curentH=CheckPath(points);
	//
	for (int i = 0; i < points.size(); i++) cout << points[i] << "->";
	cout << " Path = " << CheckPath(points);
	if (curentH < record) {
		cout << "\n Old record = " << record << " New record = " << curentH<<'\n';
		record = curentH;
	}
	cout<<'\n';
	return 0;
}

int main() {
	int n=0, temp=0;
	ifstream file("rgz.txt");
	file >> n;
	mas = new int* [n];
	for (int i = 0; i < n; i++){
		mas[i] = new int[n];
		for(int j=0;j<n;j++) mas[i][j]=0;	
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			file >> temp;
			if (temp == -1) mas[i][j] = 9999;
			else mas[i][j] = temp;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cout << std::setiosflags(ios::left) << setw(6) << mas[i][j];
		cout << '\n';
	}
	cout << '\n';
	int error = InitRecord(n);
	if (error) return 4;
	vector<int> points;
	points.push_back(0);
	error=Komivoazher(n, 1, points, 0);
//	for(int i=0;i<n;i++) delete[] mas[i];
	delete[] mas;
	if(error) return 4;
	return 0;
}
