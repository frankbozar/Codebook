const int num[13]={1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
const string str[13]={"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
string rome(int x){
    for(int i=0; i<13; i++) if( x>=num[i] ) return str[i]+rome(x-num[i]);
    return "";
}
int rome(const string& s){
    for(int i=0; i<13; i++)
        if( s.length()>=str[i].length() && s.substr(0, str[i].length())==str[i] )
            return num[i]+rome(s.substr(str[i].length()));
    return 0;
}
