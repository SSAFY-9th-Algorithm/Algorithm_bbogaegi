#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<char, int> termsGuide;
struct DateForm{
    int y;
    int m;
    int d;
};
char privaciesType[101];
DateForm privaciesList[101];
DateForm todayDate;

int removedOrNot(int now){
    char type = privaciesType[now];
    int period = termsGuide[type];
    
    int compm = privaciesList[now].m + period;
    int moreyear = 0;
    
    while(compm > 12){
        compm -= 12;
        moreyear++;
    }
    int compy = privaciesList[now].y + moreyear;
    int compd = privaciesList[now].d - 1;
    if(privaciesList[now].m == 1 && privaciesList[now].d == 1){
        compy = privaciesList[now].y + moreyear - 1;
        compm = 12;
        compd = 28;
    }else if(privaciesList[now].d == 1){
        compm--;
        compd = 28;
    }
    
    int flag = 0;
    if(compy < todayDate.y)
        flag = 1;
    else if(compy == todayDate.y && compm < todayDate.m )
        flag = 1;
    else if(compy == todayDate.y && compm == todayDate.m && compd < todayDate.d)
        flag = 1;
    
    return flag;
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;
    
    string tyear = "";
    for(int j=0; j<=3;j++)
        tyear += today[j];
    int nyear = stoi(tyear);
    todayDate.y = nyear;
    //월
    string tmonth = "";
    for(int j=5; j<=6;j++)
        tmonth += today[j];
    int nmonth = stoi(tmonth);
    todayDate.m = nmonth;
    //일
    string tday = "";
    for(int j=8; j<=9;j++)
        tday += today[j];
    int nday = stoi(tday);
    todayDate.d = nday;
    //terms를 key:알파벳, value:개월로 정리
    for(int i=0; i<terms.size(); i++){
        string tmpnum = "";
        for(int j=2; j<terms[i].length();j++)
            tmpnum += terms[i][j];
        int num = stoi(tmpnum);
        termsGuide.insert({terms[i][0], num});
    }
    
    //privacies를 privaciesType와 privaciesList로 정리
    for(int i=0; i<privacies.size(); i++){
        DateForm privacy;
        //년
        string tmpyear = "";
        for(int j=0; j<=3;j++)
            tmpyear += privacies[i][j];
        int year = stoi(tmpyear);
        privacy.y = year;
        //월
        string tmpmonth = "";
        for(int j=5; j<=6;j++)
            tmpmonth += privacies[i][j];
        int month = stoi(tmpmonth);
        privacy.m = month;
        //일
        string tmpday = "";
        for(int j=8; j<=9;j++)
            tmpday += privacies[i][j];
        int day = stoi(tmpday);
        privacy.d = day;
        
        char term = privacies[i][11];
        
        privaciesType[i] = term;
        privaciesList[i] = privacy;
    }
    
    for(int i=0; i<privacies.size(); i++){
        int result = removedOrNot(i);
        if(result == 1)
            answer.push_back(i+1);
    }
    return answer;
}
