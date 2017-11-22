#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char * String;

void swap(String *a , String * b){//String is already a pointer so we dont need to worry about the functioon creating local copies of the values..
	/* so..
	
	a is Strings[X] witch is a char pointer to [c][h][a][r][s]

	*/
	char temp[100];
	strcpy(temp, *a); //chuck a's value into temp
	strcpy(*a, *b);
	strcpy(*b, temp);
}

void quicksort(String *vals, int first, int last){
	if (first < last)
	{
		//use last element as the pivot
		int i = first; //starts at fisrt and keeps moviing to the right
		int j = last - 1; //starts at 2nd last and moves left
		//i->                        <-j,piv
		//[][][][][][][][][][][][][][][][piv]
		while (i<j)//alwasy going to be true untill i&j cross paths
		{
			//note: strcmp(a,b) =
			// 0 if they the same
			// > 0 if a > b
			// < 0 if a < b

			while (i<last && strcmp(vals[i], vals[last]) < 0 )//while i value is smaller than pivot value (stop when you find same or bigger value)
			{
				i++;
			}
			while (j>=first && strcmp(vals[j],vals[last]) > 0 )//while j value is bigger than pivot value (stop when hit a value same or smaller)
			{
				j--;
			}
			if (i<j)//only true if j & i never crossed paths (this after they have moved to find value > or < pivot in while loops above)
			{
				swap(&vals[i], &vals[j]);
			}
		}
		swap(&vals[i], &vals[last]); //i & j crossed path by now so swap i with pivot, pivot is now in the right place and j is infront of it.
		
		//               j   i
		//[][][][][][][][] [piv] [][][][][][][]
		//smaller than piv       bigger than piv
		quicksort(vals, first, j);//recustion call on smaller partition
		quicksort(vals, i + 1, last);//recursion call on larger partition
	}
}

int main(){
	int n = 1;
	char buffer[100];
	String * strings;

	printf("How many strings?\n");
	scanf("%d", &n);

	strings = malloc(sizeof(buffer)*n);

	for (int i = 0; i < n; i++)
	{
		printf("Enter a string\n");
		scanf("%s", buffer);
		printf("\n");

		strings[i] = (String)malloc(strlen(buffer) + 1);
		strcpy(strings[i], buffer);
	}

	for (int i = 0; i < n; i++)
	{
		printf("%d - %s\n", i, strings[i]);
	}
	printf("==============================SORTED======================");

	quicksort(strings, 0, n - 1);

	for (int i = 0; i < n; i++)
	{
		printf("%d - %s\n", i, strings[i]);
	}
	/*for (int i = 0; i < n; i++)
	{
		free(strings[i]);
	}*/
}