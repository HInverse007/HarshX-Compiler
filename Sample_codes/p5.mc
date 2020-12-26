int n,size,temp,arr[100000],i;
scan(n);
size = 0;
int func(int length, int a, int b, int vec[]) {
    int j,t;
    vec[length] = a;
    length += 1;
    for(j=0;j<length;j+=1) {
        print(vec[j]);
    }
    for(j=(a)+(1);j<=b;j+=1) {
        t = func(length,j,b,vec);
    }
    return 0;
}

for(i=1;i<=n;i+=1) {
    temp = func(size,i,n,arr);
}
return 0;