//neoSaris generator using neoSaris JSON
#include<bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
string contestName;
int numberOfProblems, Time, freezeTime, numberOfTeams;
vector<string> teamList;
bool accepted[1005][1005];

int randint(int l, int r){
	return rng() % (r-l+1) + l;
}

void read(){
	cout << "neoSaris Contest Generator v0.1.0 \n";
	cout << "Enter name of contest (eg. ICPC Asia Hue City 2023): ";
	getline(cin, contestName);
	cout << "Enter number of problems (eg. 7): ";
	cin >> numberOfProblems;
	cout << "Enter contest duration in minutes (eg. 300): ";
	cin >> Time;
	cout << "Enter freeze duration before end of contest in minutes (eg. 60): ";
	cin >> freezeTime;
	cout << "Enter number of teams (eg. 10): ";
	cin >> numberOfTeams;
	string temp;
	getline(cin, temp);
	for(int i = 1; i <= numberOfTeams; i++){
		cout << "Enter name of team " << i << ": ";
		getline(cin, temp);
		teamList.emplace_back(temp);
	}
	return ;
}

void init(){
	ofstream out("data.json");
	out << "{\n";
	out << "  \"contestMetadata\": {\n";
	out << "    \"duration\": " << Time << ",\n";
	out << "    \"frozenTimeDuration\": " << freezeTime << ",\n";
	out << "    \"name\": \"" << contestName << "\",\n";
	out << "    \"type\": \"ICPC\"\n";
	out << "  },\n";

	out << "  \"problems\": [\n";
	for(int i = 0; i < numberOfProblems; i++){
		out << "    { \"index\": \"" << char(i+'A') << "\" }";
		if(i != numberOfProblems - 1) out << ",";
		out << "\n";
	}
	out << "  ],\n";

	out << "  \"contestants\": [\n";
	for(int i = 0; i < (int)teamList.size(); i++){
		out << "    { \"id\": " << i+1 << ", \"name\": \"" << teamList[i] << "\" }";
		if(i != (int)teamList.size() - 1) out << ",";
		out << "\n";
	}
	out << "  ],\n";

	out << "  \"verdicts\": {\n";
	out << "    \"accepted\": [\"AC\"],\n";
	out << "    \"wrongAnswerWithPenalty\": [\"WA\"],\n";
	out << "    \"wrongAnswerWithoutPenalty\": [\"CE\"]\n";
	out << "  },\n";
	return ;
}

void generateSubmissions(){
	ofstream out;
	out.open("data.json", ios_base::app);
	out << "  \"submissions\": [\n";
	for(int i = 1; i <= Time; i++){
		int noSub = randint(1, min(3, numberOfTeams/3));
		for(int j = 1; j <= noSub; j++){
			int team = randint(0, numberOfTeams-1);
			int problem = randint(0, numberOfProblems-1);
			int verdict = randint(0, 3);
			//0 = AC, 1 = WA
			while(verdict == 0 && accepted[team][problem]){
				team = randint(0, numberOfTeams-1);
				problem = randint(0, numberOfProblems-1);
				verdict = randint(0, 5);
			}

			out << "    {\n";
			out << "      \"timeSubmitted\": " << i << ",\n";
			out << "      \"contestantName\": \"" << teamList[team] << "\",\n";
			out << "      \"problemIndex\": \"" << char(problem+'A') << "\",\n";
			out << "      \"verdict\": \"";
			if(verdict == 0){
				out << "AC\"\n";
				accepted[team][problem] = true;
			}
			else out << "WA\"\n";
			out << "    }";
			if(!(i == Time && j == noSub)) out << ",";
			out << "\n";
		}
	}
	out << "  ]\n}";
}

int main(){
	read();
	init();
	generateSubmissions();
	return 0;
}