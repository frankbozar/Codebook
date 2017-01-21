string rome(int x){
	string s;
	int num[13]={1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
	string str[13]={"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
	for(int i=0; i<13; i++){
		if( x>=num[i] ){
			if( i%4==0 ){
				for(int j=0; j<x/num[i]; j++) s+=str[i];
				x%=num[i];
			}
			else{
				s+=str[i];
				x-=num[i];
			}
		}
	}
	return s;
}
