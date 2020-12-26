int x,y,z,limit,cnt;
cnt=0;
limit=100;
for (z = 1 ; z <= limit; z+=1)
{
    for (x = 1; x <= limit; x+=1)
    {
        for (y = 1; y <= limit; y+=1)
        {
            int tp;
            tp = ((x) * (x)) + ((y) * (y));
            int t2;
            t2 = (z) * (z);
            if ( tp == t2)
            {
                cnt += 1;
            }
        }
    }
}
print(cnt);
return 0;