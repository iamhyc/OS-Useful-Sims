
/* Disk Scheduler Simulation Program
 * ===========================================
 * Algorithm: FCFS, SSTF, SCAN, C-SCAN, LOOK, C-LOOK
 * Input Param.:
 * 		- Disk Spec:[Disk Range Start][Disk Range End][Lookup Start]
 *		- Lookup Number:[Number N]
 *		- Lookup Series:[<in-range series>]
 * Output Series:
 *		- <6 Rows of each Algorithm simulation results>
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <strings.h>

static int N;
static int *arr, *results;
static int rng_head, rng_tail, start;

int *Sim_FCFS()
{
	return arr;
}

int *Sim_SSTF()
{
	int i, sum = 0, current, next, tmp;
	bool flag[N];

	if(results != NULL)
	{
		free(results);
	}
	results = malloc(N * sizeof(int));

	current = start;
	while(sum < N)
	{
		tmp = INT_MAX;

		for(i = 0; i < N; i++)
		{
			if(!flag[i] && abs(arr[i] - current) < tmp)
			{
				tmp = abs(arr[i] - current);
				next = i;
			}
		}

		results[sum] = arr[next];
		current = arr[next];
		flag[next] = 1;
		sum++;
	}
	return results;
}

int *Sim_SCAN(bool ForwardScan, int pos)
{
	int i, sum = 0;

	if(results != NULL)
	{
		free(results);
	}
	results = malloc((N+1) * sizeof(int));

	if(ForwardScan)
	{
		for(i = pos+1; i < N; i++)
			results[sum++] = arr[i];
		results[sum++] = rng_tail;
		for(i = pos; i >= 0; i--)
			results[sum++] = arr[i];
	}

	return results;
}

int *Sim_CSCAN(bool ForwardScan, int pos)
{
	int i, sum = 0;

	if(results != NULL)
	{
		free(results);
	}
	results = malloc((N+2) * sizeof(int));

	if(ForwardScan)
	{
		for(i = pos+1; i < N; i++)
			results[sum++] = arr[i];
		results[sum++] = rng_tail;
		results[sum++] = rng_head;
		for(i = 0; i <= pos; i++)
			results[sum++] = arr[i];
	}

	return results;
}

int *Sim_LOOK(bool ForwardScan, int pos)
{
	int i, sum = 0;

	if(results != NULL)
	{
		free(results);
	}
	results = malloc(N * sizeof(int));

	if(ForwardScan)
	{
		for(i = pos+1; i < N; i++)
			results[sum++] = arr[i];
		for(i = pos; i >= 0; i--)
			results[sum++] = arr[i];
	}

	return results;
}

int *Sim_CLOOK(bool ForwardScan, int pos)
{
	int i, sum = 0;

	if(results != NULL)
	{
		free(results);
	}
	results = malloc(N * sizeof(int));

	if(ForwardScan)
	{
		for(i = pos+1; i < N; i++)
			results[sum++] = arr[i];
		for(i = 0; i <= pos; i++)
			results[sum++] = arr[i];
	}

	return results;
}

void Sim_Display(char* alg, int number, int* results);
void simple_sort(int N, int* arr);
int simple_locate(int val, int* arr);

int main(int argc, char const *argv[])
{
	int i, pos;
	int *results;

	printf("Disk Spec[Disk Range Start][Disk Range End][Lookup Start]:");
	scanf("%d%d%d", &rng_head, &rng_tail, &start);
	printf("%s", "Lookup Number[Number N]:");
	scanf("%d", &N);

	arr = (int *)malloc(N * sizeof(int));

	printf("%s\n", "Lookup Series[<in-range series>]:");
	for (i = 0; i < N; ++i)
	{
		scanf("%d", &(arr[i]));
	}

	results = Sim_FCFS();		Sim_Display("FCFS", N, results);
	results = Sim_SSTF();		Sim_Display("SSTF", N, results);

	simple_sort(N, arr);
	Sim_Display("After Sort", N, arr);
	pos = simple_locate(start, arr);
	printf("%s%d\n", "Position: ", pos);

	results = Sim_SCAN(1, pos);	Sim_Display("SCAN", N+1, results);
	results = Sim_CSCAN(1, pos);	Sim_Display("CSCAN", N+2, results);
	results = Sim_LOOK(1, pos);	Sim_Display("LOOK", N, results);
	results = Sim_CLOOK(1, pos);	Sim_Display("CLOOK", N, results);

	free(arr);
	return 0;
}

void simple_sort(int N, int * A)
{
	int i, j, tmp;
	for(i = 0; i < N - 1; i++)
	{
		for (j = i+1; j < N; j++)
		{
			if(A[i] > A[j])
			{
				tmp = A[i];
				A[i] = A[j];
				A[j] = tmp;
			}
		}
	}
}

int simple_locate(int val, int *arr)
{
	int i = 0;
	while(arr[i] < val && i <= N) i++;
	return (i-1);
}

void Sim_Display(char* alg, int number, int* results)
{
	int i, sum = 0;
	printf("\n%s:\n", alg);

	printf("Lookup Results: (%d)\t%d\t", start, results[0]);
	sum += abs(results[0] - start);

	for (i = 1; i < number; ++i)
	{
		printf("%d\t", results[i]);
		sum += abs(results[i] - results[i-1]);
	}

	printf("\n%s%d\n", "Total Distance: ", sum);
}
