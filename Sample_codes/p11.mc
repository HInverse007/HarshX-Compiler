char filename[100],char contents[100000];
char c;
int i;
i=0;
while(1)
{
	scan(c);	
	if (c == '\n')
	{
		stop;
	}
	filename[i] = c;
	i+=1;
}
filename[i] = '\0';
readFile(filename, contents);
int hist[26];
for(i=0; i<26; i+=1)
{
	hist[i] = 0;
}
i = 0;
while(1)
{
	c = contents[i];
	if(c=='\n')
	{
		stop;
	}
	i+=1;
	int idx;
	idx = ((c) - ('a'));
	hist[idx]+=1;
}
for(i=0; i<26; i+=1)
{
	c = (i) + ('a');
	print(c);
	print(hist[i]);
}