// входные данные
int n;
vector<int> a (n);
 

int len = (int) sqrt (n + .0) + 1; 
vector<int> b (len);
for (int i=0; i<n; ++i)
	b[i / len] += a[i];
 
// ответ на запросы
for (;;) {
	int l, r; 
	int sum = 0;
	for (int i=l; i<=r; )
		if (i % len == 0 && i + len - 1 <= r) {
			sum += b[i / len];
			i += len;
		}
		else {
			sum += a[i];
			++i;
		}
}