



#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
double likelihood[10];
bool isAnswer[10000];
vector<char*> Test;
vector<char*> Result;


void printHighestPosNum(){
    double tmp[10];
    for (int i=0; i<10; i++) {
        tmp[i] = likelihood[i];
    }
    
    sort(tmp, tmp+10);
    bool used[10];
    memset(used, 0, sizeof(used));
    
    printf("最有可能：");
    for (int i=9; i>=5; i--) {
        for (int j=0; j<10; j++) {
            if (tmp[i] == likelihood[j] && used[j]!=true) {
                printf("%d ", j);
                used[j] = true;
                break;
            }
        }
    }
}

void updateLikelihood(char* test, char* result){
    float total = 0;
    int mul[2]; mul[0]=result[0]-'0'; mul[1] = result[2]-'0';
    total = total + mul[0]*2 + mul[1]*1;
    for (int i=0; i<4; i++) {
        likelihood[test[i]-'0'] = likelihood[test[i]-'0'] + total/4;
    }
    
    bool isTest[10];
    for (int i=0; i<10; i++) {
        isTest[i] = false;
    }
    for (int i=0; i<4; i++) {
        isTest[test[i]-'0'] = true;
    }
    
    total = 4-(mul[0] + mul[1]);
    total = total/6;
    for (int i=0; i<10; i++) {
        if (isTest[i]==false) {
            likelihood[i] = likelihood[i] + total;
        }
    }
}

void printLikelihood(){
    printf("各數字可能性：");
    for (int i=0; i<10; i++) {
        printf("%lf\n", likelihood[i]);
    }
    printf("\n\n");
}

void checkContradict(int *candidateAns, int n){
    for (int i=0; i<n; i++) {
        int tmpCand = candidateAns[i];
        char tmp[4];
        tmp[3] = tmpCand%10 + '0'; tmpCand = tmpCand/10;
        tmp[2] = tmpCand%10 + '0'; tmpCand = tmpCand/10;
        tmp[1] = tmpCand%10 + '0'; tmpCand = tmpCand/10;
        tmp[0] = tmpCand + '0';
        
        for (int j=0; j<Test.size(); j++) {
            int aCount = 0, bCount = 0;

            char *histo;
            histo = Test[j];
            if (histo[0]==tmp[0]) aCount++;
            if (histo[1]==tmp[1]) aCount++;
            if (histo[2]==tmp[2]) aCount++;
            if (histo[3]==tmp[3]) aCount++;
            
            for (int n=0; n<4; n++) {
                for (int m=0; m<4; m++) {
                    if (n==m) {
                        continue;
                    }
                    if (histo[n]==tmp[m]) {
                        bCount++;
                    }
                }
            }
            if (aCount!=Result[j][0]-'0' || bCount!=Result[j][2]-'0') {
                isAnswer[candidateAns[i]] = false;
            }
        }
    }
}

void endGame(int n){
    int tmp =0 ;
    int* candidateAns = new int[n+10];
    for (int i=0; i<10000; i++) {
        if (isAnswer[i] == true) {
            candidateAns[tmp++] = i;
        }
    }
    checkContradict(candidateAns, n);
}

void printPossibleAns(){
    int count = 0;
    printf("可能答案：");
    for (int i=0; i<10000; i++) {
        if (isAnswer[i]==true) {
            printf("%d ", i);
            count++;
        }
    }
    printf("count:%d\n", count);
    endGame(count);
}

bool isDup(int a){
    int tmp[4];
    tmp[3] = a%10; a = a/10;
    tmp[2] = a%10; a = a/10;
    tmp[1] = a%10; a = a/10;
    tmp[0] = a;
    
    bool isBreak = false;
    for (int i=0; i<4; i++) {
        for (int j=i+1; j<4; j++) {
            if (tmp[i] == tmp[j]) {
                isBreak = true;
                break;
            }
        }
    }
    return isBreak;
}

int dupCount(char *a, int b){
    int tmp[4], TMP[4];
    tmp[3] = a[3]-'0';
    tmp[2] = a[2]-'0';
    tmp[1] = a[1]-'0';
    tmp[0] = a[0]-'0';
    
    TMP[3] = b%10; b = b/10;
    TMP[2] = b%10; b = b/10;
    TMP[1] = b%10; b = b/10;
    TMP[0] = b;
    
    int Count = 0;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (tmp[i]==TMP[j]) {
                Count++;
            }
        }
    }
    return Count;
}

void initializeIsAnswer(){
    for (int i=0; i<10000; i++) {
        isAnswer[i] = true;
    }
    
    for (int i=0; i<1000; i++) {
        isAnswer[i] = false;
    }
    
    for (int i=1000; i<10000; i++) {
        if (isDup(i)) {
            isAnswer[i] = false;
        }
    }
}

void updateIsAnswer(char *test, char *result){
    int supposeDupCount = (result[0]-'0') + (result[2]-'0');
    for (int i=1000; i<10000; i++) {
        if (isAnswer[i]==true) {
            if (dupCount(test, i)!=supposeDupCount) {
                isAnswer[i] = false;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    
    
    
    bool foundAns = false;
    initializeIsAnswer();

    while (foundAns==false) {
        char *test = new char[4];
        char *result = new char[4];
        
        
        scanf("%c%c%c%c", &test[0], &test[1], &test[2], &test[3]);
        getchar();
        scanf("%c%c%c%c", &result[0], &result[1], &result[2], &result[3]);
        getchar();
        
        Test.push_back(test);
        Result.push_back(result);
        
        updateLikelihood(test, result);
        updateIsAnswer(test, result);
        printLikelihood();
        printPossibleAns();
        printHighestPosNum();
    }
    
    
    return 0;
}
