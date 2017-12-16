#include <iostream>
#include <vector>
#include <time.h> 
#include <math.h>
#include <fstream>
#include <cstdlib>
#define Random(x) (((rand()-1) % x)+1) //通过取余取得指定范围的随机数
using namespace std;
const double TEnd = 0.1;
int layoutX0 = 0, layoutY0 = 0, layoutX1 = 0, layoutY1 = 0;
class Unit {
public:
	int width;
	int height;
	int area;
	string name;
	void rotate() {
		swap(this->width, this->height);
	}
	
	Unit(int w, int h, string name) {
		this->height = h;
		this->width = w;
		this->name = name; 
		this->area = h * w; 
	} 
//	Unit() 
//	: Unit(0,0,"default name") {

//	}
}; 

class SingleSequence {
public:
	vector<Unit> v;
	vector<Unit> newv; 
	vector<int> s;
	vector<int> news;
	double T;
	int size;
	SingleSequence(vector<Unit> _v) {
		this->v = _v;
		this->newv = _v;

		for(int i = 0; i < _v.size(); i ++) {
			s.push_back(i + 1);
			news.push_back(i + 1);
		}
		
		this->size = _v.size(); 

		this->T = 0;
		for(int i = 0; i < _v.size(); i ++) {
			this->T += (double)_v[i].area;
		}
		this->T *= 2;
	}

	int areaCount() {
		//use news and newv to count the area.
		return 0;
	}
	void refresh() {
		int n = newv.size();
		int a = Random(n)-1;
		int b = Random(n)-1;
		while(a == b) {
			b = Random(n)-1;
		}
		swap(news[a], news[b]);
		if(Random(6) <= 3) {
			a = Random(n)-1;
			newv[a].rotate();
		}
		if(Random(6) <= 3) {
			a = Random(n)-1;
			b = Random(n)-1;
			while(a == b) {
				b = Random(n)-1;
			}
			swap(newv[a], newv[b]);
		}
	}

	void solve() {
		int prevArea = areaCount();
		do {
			cout << "T : " << T << endl; 
			for(int i = 0; i < 20; i ++) {
				this->refresh();
				int newArea = this->areaCount();
				cout << "newArea = " << newArea << endl; 
				if(newArea < prevArea) {
					s = news;
					v = newv;
					prevArea = newArea;
				} else {
					double p = exp((double)(prevArea - newArea)/T);
					double r = (double)Random(1000) * 1.0 / 1000;
					if(r < p) {
						s = news;
						v = newv;
						prevArea = newArea;
					} else {
						news = s;
						newv = v;
					}
				}
			}

			T = T * 0.98;
		} while(T > TEnd);
	}

	void showResult() {
		cout << "=============================================" << endl;
		cout << "result sequence : ";
		for(int i = 0; i < s.size(); i ++) {
			cout << s[i] << " ";
		}
		cout << endl;
		int usedArea = areaCount();
		int needArea = 0;
		for(int i = 0; i < v.size(); i ++) {
			needArea += v[i].area;
		}
		cout << "area : " << needArea << " / " << usedArea << endl;
		cout << "=============================================" << endl;
	}
};


int main() {	
	srand((int)time(NULL));     //每次执行种子不同，生成不同的随机数
	ifstream fin("thu_ami33.in");
	char ch1[100], ch2[100];
	int cellSize = 0;
	string temp;
	fin >> ch1 >> layoutX0 >> layoutY0 >> layoutX1 >> layoutY1;
	fin >> temp;
	fin >> temp;
	fin >> cellSize;
	cout << "cellSize = " << cellSize << endl;
	int w = 0, h = 0;
	string name;
	vector<Unit> tmpv;
	for(int i = 1; i <= cellSize; i++) {
		fin >> name;
		cout<< name <<endl; 
		fin >> w;
		fin >> h;
		Unit m = Unit(w, h, name);
		tmpv.push_back(m);
	}
	cout << "tmpv.size() = " << tmpv.size() << endl;
	SingleSequence s = SingleSequence(tmpv);
	s.solve();
}
