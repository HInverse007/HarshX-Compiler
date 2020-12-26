int N;
scan(N);
int ans;
ans = 1;
if(N==1) {
	ans = 0;
} else {
	int i;
    for(i=2;(i<N)and(ans==1);i+=1) {
        if((N)%(i)==0) {
            ans = 0;
        }
    }
}
print(ans);
return 0;