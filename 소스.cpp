#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

string intToBin(int a, int bit) {		//ó�� �Էµ� minterm���� 2������ �ٲ��ִ� �Լ�
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

int compare(string first, string last,int bit) {	//���Ͽ� 1���̳��°��� ������ �Լ�
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
string change(string binary, int idx) {			//1���̳��� ������ '-'�� �ٲٴ�
	binary[idx] = '-';							//�Լ�
	return binary;
}

int contain(int a,int index,vector<int> b,int c) {		//�������� �ȹ��� pi�� ���°�� ��ġ�ߴ���
	int result = 0;										//ã���ִ� �Լ�

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
	vector<string>binary;		// ó�� minterm���� 2������ �ٲ� ����� �� vector�� ��� �ݺ��ϸ鼭 Listing��
	vector<string>binaryCopy;	// 1���� ���� -�� ��ü�� �κ��� �ִ� 2������ ����
	vector<string>copy;			// Listing �� ������ ����.
	vector<string>pi;			// �������� ������ ���� 2�������� ���ϱ� ���ؼ� �ʹ��� minterm���� 2������ �ٲ� �� ����
	vector<int>tmpCopy;			// tmp������ �����ϱ� ���� vector
	vector<string>real;			// ���� P.I���� vector
	vector<int>tmp;				// 1���� ���� �͵��� ��ġ�� ����
	vector<int>idx;				// 2������ ��� �κ��� -�� �ٲ��� �ϴ��� ����

	
	cout << "input bit: ";		//���ϴ� bit�� �Է�
	cin >> bit;
	cout << "input number of minterm: ";	//minterm ���� �Է�
	cin >> numOfMin;
	cout << "input minterm(0~" << pow(2, bit) - 1 << "): ";	//�Է��� ������ �°� minterm�Է�
	
	for (int i = 0; i < numOfMin; i++) {		//�Էµ� minterm���� 2������ �ٲ�
		int minterm;
		cin >> minterm;
		binary.push_back(intToBin(minterm,bit));
	}
	for (int i = 0; i < binary.size(); i++) {	//��ȯ�� 2�������� �� ���� vector�� ����
		real.push_back(binary[i]);
		pi.push_back(binary[i]);
	}
		
	/*
	//vector�ִ� ������ ���Ͽ� '-'�� �ٲٸ� listing�ϰ�.
	//�ٲܰ� ������ �ٲٰ� count++���� ��, �������� count == 0 �̸�
	//���� �� �̻� �ٲ� �� ���ٰ� �Ǵ��Ͽ� ����.
	*/
	int iter = 0;
	while (true) {		
		int count = 0;	
						
		real.swap(copy);
		tmpCopy.swap(tmp);
		copy.clear();
		tmp.clear();
		
		// 2�������� ����ִ� binary�� ��ü������ ���ϸ鼭
		// 1���̰� ���� �ش� 2�������� ��ġ�� �ش� ������
		// binaryCopy�� ����
		for (int i = 0; i < binary.size() - 1; i++) {
			for (int j = i + 1; j < binary.size(); j++) {
				int result = compare(binary[i], binary[j], bit);
				if (result != -1) {
					
					//tmp�� 1���̳��� 2�������� index��
					tmp.push_back(i);
					//binaryCopy�� 1���̳��� 2�������� �� ex)000
					binaryCopy.push_back(binary[i]);
					tmp.push_back(j);
					binaryCopy.push_back(binary[j]);
					//idx�� binaryCopy��� �ڸ��� -�� �ٲ��� �ϴ��� �˷��ִ� vector.
					idx.push_back(result);
					count++;
				}
			}
			
		}	
		//copy�� vector�� ������ ã�� 1 ���̳��� ������
		//- �� ��ü�Ͽ� copy�� ����
		for (int i = 0,j = 0; i < tmp.size(); i += 2,j++) {
			copy.push_back(change(binaryCopy[i], idx[j]));	
		}

		//���� binary���� �ʱ�ȭ �� �� -�� ��ü�� �͵���
		//����Ǿ� �ִ� copy�� ������ binary�� �־���.
		binary.clear();
		for (int i = 0; i < copy.size(); i++) {
			binary.push_back(copy[i]);
		}


		//count == 0 �̶����� �� �̻� 1���̳��� ������ ���� ��.
		//���� ������ �ܰ迡�� ������ ���� �͵��� ã�Ƽ� ���� pi���� ������
		//real vector�� �־��ִ� �۾��� �� �ȿ��� ����.
		if (count == 0) {
			//������ vector�� �ʱ�ȭ
			binaryCopy.clear();
			idx.clear();
			tmp.clear();
			copy.clear();
			
			// ���������� �ϼ��� listing �ٷ� �� �ܰ���� ����
			// �̷��� �ϴ� ������ ��� pi���� ���ΰ��� �ƴϱ� ������
			// �� �ܰ迡�� ������ ���� ������ ã�� ���ؼ� ����
			// ���� �ݺ����� Ƚ���� iter-1 �� while�� ���� �� �� �� ����.
			// �ݺ��� ���� �۾��� while������ �� �۾��̶� �Ȱ���.
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
			// �̷��� ã�� �� ���� ������ ���� pi���� ����ִ� real vector�� �־���.
			for (int i = 0; i < pi.size(); i++) {
				int res = contain(i, tmpCopy.size(),tmpCopy,pi.size());
				if (res != -1)
					real.push_back(pi[res]);
			}
			
			// ���������� pi���� ������ real vector�� ���
			cout << "____________________________________" << endl;
			cout << "P.I" << endl;
			int num = 0;
			// sort�� erase unique�� real �ȿ��� �ߺ��� ������ �����ϱ� ���� ����
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

		// count�� 0�� �ƴϱ� ������ �ݺ�Ƚ�� iter�� +1
		// ���ϴµ� �ʿ��� vector���� �ʱ�ȭ �Ѵ�.
		else {
			iter+=1;
			binaryCopy.clear();
			idx.clear();
			continue;
		}
		

	}
	
	
}