int n,m,arr[1000][1000],i,j,temp;
scan(n);
scan(m);
for(i=0;i<n;i+=1) {
    for(j=0;j<m;j+=1) {
        scan(arr[i][j]);
    }
}
for(i=0;i<n;i+=1) {
    for(j=0;j<m;j+=1) {
        scan(temp);
        arr[i][j] += temp;
    }
}
for(i=0;i<n;i+=1) {
    for(j=0;j<m;j+=1) {
        print(arr[i][j]);
    }
}
return 0;