#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstring>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string file, vector<string> &names, vector<int> &scores, vector<char> &grades){
	ifstream list;
	list.open(file);
	string text;
	int a,b,c;
	char name2[100];
	char format[] = "%[^:]: %d %d %d";
	while(getline(list, text)){
		sscanf(text.c_str(), format, &name2, &a, &b, &c);
		names.push_back(name2);
		scores.push_back(a+b+c);
		grades.push_back(score2grade(a+b+c));
	}
	list.close();

}

void getCommand(string &command,string &key){
	string x;
	cout << "Please input your command: ";
	getline(cin,x);
	int z;
	z = x.find_first_of(" ");
	command = x.substr(0,z);
	key = x.erase(0,z+1);
}

void searchName(vector<string> &names,vector<int> &scores,vector<char> &grades,string key){
    int N = names.size();
    int status = 0;
    cout << "---------------------------------\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "'s score = " << scores[i] << endl << names[i] << "'s grade = " << grades[i] << endl;
            status = 1;
        }
    }
    if(status != 1) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names,vector<int> &scores,vector<char> &grades,string key){
    int N = grades.size();
    int status = 0;
    char ikey[100];
    strcpy(ikey,key.c_str());
    cout << "---------------------------------\n";
    for(int i = 0 ; i < N ; i++){
        if(*ikey == grades[i]){
        cout << names[i] << " (" << scores[i] << ")" << endl;
        status = 1;
        }
    }
    if(status != 1) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}