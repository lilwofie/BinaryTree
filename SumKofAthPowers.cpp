/* For given n and a, determine the smallest number k for which n can be expressed as a sum of k positive integers each of which is a perfect a-th power. 
Print the number k and the representation of n as the sum of k perfect a-th powers. 
Create the program that uses data structures based on balanced binary search trees to achieve the polynomial complexity. */

#include <iostream>
using namespace std;

int exponent(double x, double y) {
	int output = 1;

	for (int i = 0; i < y; ++i) {
		output = output * x;
	}

	return output;
}

void solution(int& n, int& alpha, int* prevSequence, int pos, int& k) {
	int sum = 0;
	int total = 0;

	for (int i = 0; i < n; i++) {
		sum = sum + prevSequence[i];
		if (prevSequence[i] > 0) {
			total++;
		}
	}

	if (sum == n) {
		if (total < k) {
			k = total;
		}
	}

	if (sum < n) {
		if (pos < n) {
			for (int i = 0; exponent(i, alpha) < n + 1; i++) {
				prevSequence[pos] = exponent(i, alpha);
				solution(n, alpha, prevSequence, pos + 1, k);
			}
		}
	}
}

int main() {
	int n, alpha, k;
	cout << "Please enter your desired n value: ";
	cin >> n;
	cout << "Please enter your desired alpha value: ";
	cin >> alpha;
	k = n;

	int* sequence = new int[n];
	for (int i = 0; i < n; i++) {
		sequence[i] = 0;
	}

	solution(n, alpha, sequence, 0, k);
	cout << "K - Value = " << k << endl;

	return 0;
}
