// Correção: OK. 1,0 ponto.
#include <stdio.h>
#include <omp.h>

int main (int argc , char *argv[]) {
    int max;
    sscanf (argv[1], "%d", &max);
    int ts = omp_get_max_threads();
    int r = max % ts;
	int sums[ts];
	#pragma omp parallel
	{
		int t = omp_get_thread_num ();
		int lo, hi;
		if(t < r) {
			lo = (max / ts) * (t + 0) + 1 + t;
			hi = (max / ts) + lo;
		} else {
			lo = (max / ts) * (t + 0) + 1 + r;
			hi = (max / ts) + lo - 1;
		}
		sums[t] = 0;
		printf("t%d lo: %d hi: %d hi - lo: %d\n", t, lo, hi, hi - lo);
		for (int i = lo; i <= hi; i++)
			sums[t] = sums[t] + i;
	}
    int sum = 0;
    for (int t = 0; t < ts; t++) sum = sum + sums[t];
    printf ("%d\n", sum);
    return 0;
}
