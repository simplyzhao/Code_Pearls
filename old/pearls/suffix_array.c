#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10001
#define CHARSET 256
int table[4][MAX];
int cnt[CHARSET];
int *sa, *rank, *nsa, *nrank;

void
swap(int **arg1, int **arg2)
{
	int *t = *arg1;
	*arg1 = *arg2;
	*arg2 = t;
}

void
create_suffix_array(const char *s, int n) /* O(nlogn) */
{
	int i, k;
	sa = table[0];
	rank = table[1];
	nsa = table[2];
	nrank = table[3];

	/* 创建起始sa, rank, 即按照第一个字母的顺序，计数排序 */
	memset(cnt, 0, sizeof(cnt));
	for(i=0; i<n; ++i)
		++cnt[s[i]];
	for(i=1; i<CHARSET; ++i)
		cnt[i] += cnt[i-1];
	for(i=n-1; i>=0; --i)
		sa[--cnt[s[i]]] = i;
	rank[sa[0]] = 0;
	for(i=1; i<n; ++i) {
		rank[sa[i]] = rank[sa[i-1]];
		if(s[sa[i]] != s[sa[i-1]])
			++rank[sa[i]];
	}

	/* 倍增法 */
	for(k=1; k<n&&rank[sa[n-1]]<n-1; k<<=1) {
		/* 类似于计数，或者看成分到一个个不同的桶 */
		for(i=0; i<n; ++i)
			cnt[rank[sa[i]]] = i+1;
		/* 根据k级别的sa, rank，计算2k级别的nsa, nrank */
		/* SA(i) <=[2k] SA(j), if SA(i) <=[k] SA(j) && SA(i+k) <=[k] SA(j+k) */
		/* 从后向前遍历k级别的sa，因为i越靠后，SA(sa[i])越大 */
		for(i=n-1; i>=0; --i) {
			if(sa[i] >= k) {
				nsa[--cnt[rank[sa[i]-k]]] = sa[i]-k;
			}
		}
		for(i=n-k; i<n; ++i)
			nsa[--cnt[rank[i]]] = i;
		/* 计数排序 */
		nrank[nsa[0]] = 0;
		for(i=1; i<n; ++i) {
			nrank[nsa[i]] = nrank[nsa[i-1]];
			if(rank[nsa[i]]!=rank[nsa[i-1]] || rank[nsa[i]+k]!=rank[nsa[i-1]+k]) {
				++nrank[nsa[i]];
			}
		}

		swap(&sa, &nsa);
		swap(&rank, &nrank);
	}
}

int
main(int argc, char **argv)
{
	create_suffix_array("banana", 6);
}
