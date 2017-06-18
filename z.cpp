void Z(const char* s, int z[]){
    int n=z[0]=strlen(s);
	for(int l=0, r=0, i=1; i<n; i++)
        if( r<i || r-i<z[i-l] ){
            if( r<i ) r=i;
            for(l=i; r<n && s[r]==s[r-l]; r++);
            z[i]=r---l;
        }else z[i]=z[i-l];
}
