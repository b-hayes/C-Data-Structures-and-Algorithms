#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



int f1(long n) {
	int k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			k++;
		}
	}
	return k;
}
void f2(long n) {
	int k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			k++;
		}
		for (int t = 0; t < 10000; t++) {
			k++;
		}
	}
}
void f3(long n) {
	if (n > 0) {
		f3(n / 2);
		f3(n / 2);
	}
}
void f4(long n) {
	if (n > 0) {
		f4(n / 2);
		f4(n / 2);
		f2(n);
	}
}
void f5(long n) {
	int k = 0;
	for (int i = 0; i < 10; i++) {
		while (n > 0) {
			k++;
			n = n / 2;
		}
	}
}
void f6(long n) {
	f2(n);
	f3(n);
	f5(n);
}
void f7(long n) {
	int k = 0;
	for (int i = 0; i < f1(n); i++) {
		k++;
	}
	for (int j = 0; j < n; j++) {
		k++;
	}
}

void main() {
	//set the clock
	long n;
	printf("Enter a value for n\n");
	scanf("%d", &n);
	clock_t start = clock();
	//now lets make the n value in seconds for ease
	n = n * 1000;
	//call the function
	f2(n);
	//show result
	clock_t diff = clock() - start;
	long msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Operation took %d milliseconds\n\n", msec);
}