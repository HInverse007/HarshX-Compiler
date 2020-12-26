int n1,m1,n2,m2,arr1[1000][1000],arr2[1000][1000],answer[1000][1000],i,j,k;
scan(n1);
scan(m1);
for(i=0;i<n1;i+=1) {
    for(j=0;j<m1;j+=1) {
        scan(arr1[i][j]);
    }
}
scan(n2);
scan(m2);
for(i=0;i<n2;i+=1) {
    for(j=0;j<m2;j+=1) {
        scan(arr2[i][j]);
    }
}
for(i=0;i<n1;i+=1) {
    for(j=0;j<m2;j+=1) {
        answer[i][j] = 0;
        for(k=0;k<m1;k+=1) {
            answer[i][j] += (arr1[i][k]) * (arr2[k][j]);
        }
    }
}
for(i=0;i<n1;i+=1) {
    for(j=0;j<m1;j+=1) {
        print(answer[i][j]);
    }
}
return 0;