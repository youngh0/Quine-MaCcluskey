#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

// 1.원하는 bit의 수를 입력
// 2.원하는 minterm의 개수 입력
// 3.입력한 개수에 맞는 minterm들을 bit의 범위에 맞게 띄어쓰기로 구분하여 정수로 입력
// 4.결과물 출력.

string intToBin(int a, int bit) {		//처음 입력된 minterm들을 2진수로 바꿔주는 함수
	string bin;
	for (int i = 0; i < bit; i++) {
		if (a % 2 == 0)
			bin.push_back('0');
		else
			bin.push_back('1');
		a /= 2;
	}
	reverse(bin.begin(), bin.end());
	return bin;
}

int compare(string first, string last,int bit) {	//비교하여 1차이나는것을 가리는 함수
	int count = 0, idx = 0;
	for (int i = 0; i < bit; i++) {
		if (first[i] != last[i]) {
			count++;
			idx = i;
		}
	}
	if (count == 1) return idx;
	else return -1;
}
string change(string binary, int idx) {			//1차이나는 것을을 '-'로 바꾸는
	binary[idx] = '-';							//함수
	return binary;
}

int contain(int a,int index,vector<int> b,int c) {		//마지막에 안묶인 pi가 몇번째에 위치했는지
	int result = 0;										//찾아주는 함수

	for(int cycle = 0;cycle< c;cycle++){
		for (int i = 0; i < index; i++) {
			if (a == b[i]) {
				result++;
				break;
			}
		}
	}
	if (result == 0)
		return a;
	else return -1;
}


int main() {
	int bit,numOfMin;
	vector<string>binary;		// 처음 minterm들을 2진수로 바꾼 값들로 이 vector로 계속 반복하면서 Listing함
	vector<string>binaryCopy;	// 1차이 나서 -로 대체될 부분이 있는 2진수들 저장
	vector<string>copy;			// Listing 한 값들을 저장.
	vector<string>pi;			// 마지막에 묶이지 않은 2진수들을 구하기 위해서 초반의 minterm들을 2진수로 바꾼 값 저장
	vector<int>tmpCopy;			// tmp값들을 저장하기 위한 vector
	vector<string>real;			// 최종 P.I들의 vector
	vector<int>tmp;				// 1차이 나는 것들의 위치들 저장
	vector<int>idx;				// 2진수의 어느 부분이 -로 바뀌어야 하는지 저장

	
	cout << "input bit: ";		//원하는 bit수 입력
	cin >> bit;
	cout << "input number of minterm: ";	//minterm 개수 입력
	cin >> numOfMin;
	cout << "input minterm(0~" << pow(2, bit) - 1 << "): ";	//입력한 개수에 맞게 minterm입력
	
	for (int i = 0; i < numOfMin; i++) {		//입력된 minterm들을 2진수로 바꿈
		int minterm;
		cin >> minterm;
		binary.push_back(intToBin(minterm,bit));
	}
	for (int i = 0; i < binary.size(); i++) {	//변환된 2진수들을 두 개의 vector에 저장
		real.push_back(binary[i]);
		pi.push_back(binary[i]);
	}
		
	/*
	//vector있는 값들을 비교하여 '-'로 바꾸며 listing하고.
	//바꿀게 있으면 바꾸고 count++해준 뒤, 마지막에 count == 0 이면
	//이제 더 이상 바꿀 게 없다고 판단하여 종료.
	*/
	int iter = 0;
	while (true) {		
		int count = 0;	
						
		real.swap(copy);
		tmpCopy.swap(tmp);
		copy.clear();
		tmp.clear();
		
		// 2진수들이 들어있는 binary를 전체적으로 비교하면서
		// 1차이가 나면 해당 2진수들의 위치와 해당 값들을
		// binaryCopy에 저장
		for (int i = 0; i < binary.size() - 1; i++) {
			for (int j = i + 1; j < binary.size(); j++) {
				int result = compare(binary[i], binary[j], bit);
				if (result != -1) {
					
					//tmp는 1차이나는 2진수들의 index값
					tmp.push_back(i);
					//binaryCopy는 1차이나는 2진수들의 값 ex)000
					binaryCopy.push_back(binary[i]);
					tmp.push_back(j);
					binaryCopy.push_back(binary[j]);
					//idx는 binaryCopy어느 자리가 -로 바껴야 하는지 알려주는 vector.
					idx.push_back(result);
					count++;
				}
			}
			
		}	
		//copy란 vector에 위에서 찾은 1 차이나는 값들을
		//- 로 대체하여 copy에 저장
		for (int i = 0,j = 0; i < tmp.size(); i += 2,j++) {
			copy.push_back(change(binaryCopy[i], idx[j]));	
		}

		//기존 binary들을 초기화 한 뒤 -로 대체된 것들이
		//저장되어 있는 copy의 값들을 binary에 넣어줌.
		binary.clear();
		for (int i = 0; i < copy.size(); i++) {
			binary.push_back(copy[i]);
		}


		//count == 0 이란것은 더 이상 1차이나는 값들이 없단 뜻.
		//이제 마지막 단계에서 묶이지 않은 것들을 찾아서 최종 pi들의 집합인
		//real vector에 넣어주는 작업을 이 안에서 수행.
		if (count == 0) {
			//기존의 vector들 초기화
			binaryCopy.clear();
			idx.clear();
			tmp.clear();
			copy.clear();
			
			// 최종적으로 완성된 listing 바로 전 단계까지 구현
			// 이렇게 하는 이유는 모든 pi들이 묶인것이 아니기 때문에
			// 전 단계에서 묶이지 않은 값들을 찾기 위해서 구현
			// 따라서 반복문의 횟수는 iter-1 즉 while문 보다 한 번 덜 돈다.
			// 반복문 안의 작업은 while문에서 한 작업이랑 똑같음.
			for(int i = 0;i<iter-1;i++){		
				for (int j = 0; j < pi.size() - 1; j++) {
					for (int q = j+1; q < pi.size(); q++) {
						int com = compare(pi[j], pi[q], bit);
						if (com != -1) {
							tmp.push_back(j);
							binaryCopy.push_back(pi[j]);
							tmp.push_back(q);
							binaryCopy.push_back(pi[q]);
							idx.push_back(com);
							
						}
					}
				}
				for (int i = 0, j = 0; i < tmp.size(); i += 2, j++) {
					copy.push_back(change(binaryCopy[i], idx[j]));
				}
				pi.clear();
				for (int i = 0; i < copy.size(); i++) {
					pi.push_back(copy[i]);
				}
				copy.clear();
				tmp.clear();
				binaryCopy.clear();
				
			}
			// 이렇게 찾은 안 묶인 값들을 최종 pi들이 들어있는 real vector에 넣어줌.
			for (int i = 0; i < pi.size(); i++) {
				int res = contain(i, tmpCopy.size(),tmpCopy,pi.size());
				if (res != -1)
					real.push_back(pi[res]);
			}
			
			// 최종결정된 pi들의 집합인 real vector를 출력
			cout << "____________________________________" << endl;
			cout << "P.I" << endl;
			int num = 0;
			// sort와 erase unique는 real 안에서 중복된 값들을 제거하기 위해 수행
			sort(real.begin(), real.end());
			real.erase(unique(real.begin(), real.end()), real.end());
			for (int i = 0; i < real.size(); i++) {
				cout << "PI[" << i + 1 << "] : " << real[i] << endl;
				num++;
			}
			cout << "size of P.I : " << num << endl;
			cout << "------------------------------------" << endl;
			
			break;
		}

		// count가 0이 아니기 때문에 반복횟수 iter에 +1
		// 비교하는데 필요한 vector들을 초기화 한다.
		else {
			iter+=1;
			binaryCopy.clear();
			idx.clear();
			continue;
		}
		

	}
	
	
}
