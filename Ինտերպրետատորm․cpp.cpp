#include <iostream>
#include<vector>
#include<string>
#include<fstream>
#include <unordered_map>
#include<algorithm>
enum my_type { tiv };

std::unordered_map<std::string, int> m;
std::unordered_map<std::string, bool(*)(int, int)> ma;
std::unordered_map <std::string, int(*)(int, int)>ma1;

std::vector<std::string> legal_var_names{ ".-", "-...", "-.-.","-..", ".","..-.","--.","....","..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.","--.-",
".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." };//A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
std::vector<std::string>legal_ops = { ">", "<",".-.-.","/", " -....-", "=" };//,>,<,+,-,
char scopes[] = { '{','}' };
std::string c_out = "print";
std::string re_turn = "..-.-.";//true=1; false=0
std::string legal_condition = "....-.";//if
int is_gumarac(int a, int b) {
	return a + b;
}
int is_hanac(int a, int b) {
	return a - b;
}
int is_bajanac(int a, int b) {
	return a / b;
}
int is_bazmapatkac(int a, int b) {
	return a * b;
}
bool is_mec(int a, int b) {
	
		return (a > b);
}
bool is_poqr(int a, int b) {

		return (a < b);
}
bool is_havasar(int a, int b) {
	
		return (a == b);
}
bool is_poqr_havasar(int a, int b) {
	return (a <= b);
}
bool is_mec_havasar(int a, int b) {
		return (a >= b);
}
bool is_havasar_havasar(int a, int b) {
	
		return true;
}
bool is_havasar_chi(int a, int b) {
	
		return (a != b);
}

void action() {
	ma1[".-.-."]= is_gumarac; 
	 ma1["-....-"]=is_hanac; 
	ma1["-..-."]= is_bajanac; 
	ma1[".----."]=is_bazmapatkac;
}
void fill() {

	ma[">"] = is_mec;
	ma["<"] = is_poqr;
	ma["="] = is_havasar;
	ma["<="] = is_poqr_havasar;
	ma[">="] = is_mec_havasar;
	ma["=="] = is_havasar_havasar;
	ma["!="] = is_havasar_chi;
}


bool is_number(std::string& s) {
	try {
		std::stoi(s);
	}
	catch (...) {
		return false;
	}
	return true;
}
void tokenization(std::string s, std::vector<std::string>& v)
{
	std::string my_string{};
	if (v.size() != 0) {
		v.clear();
	}

	for (int i = 0; i < s.size(); ++i) {
		my_string = {};
		while (i < s.size() && s[i] != ' ' && s[i] != ';') {
			my_string += s[i];
			++i;
		}
		v.push_back(my_string);
		if (s[i] == ';') {
v.push_back(";");
		}
	}
}
void check_function(std::string s, std::vector<std::string>& v, std::ifstream& file);
void legal_condition_function(std::vector<std::string>& v, std::ifstream& file) {
	if (v.size() != 6) {
		std::cout << "Syntax error" << std::endl;
		abort();
	}
	int a = 0; int b = 0;//....-. {.- > -....}
	if ((v[1] == "{") && (v[5] == "}") && (ma.find(v[3]) != ma.end())) {


		if (m.find(v[2]) != m.end()) {
			a = m[v[2]];
		}
		else if (is_number(v[2])) {
			a = stoi(v[2]);
		}
		else {
			std::cout << "Unknown variable" << std::endl;
			abort();
		}
		if (m.find(v[4]) != m.end()) {
			b = m[v[4]];
		}
		else if (is_number(v[4])) {
			b = stoi(v[4]);
		}
		else {
			std::cout << "Unknown variable" << std::endl;
			abort();
		}
	}std::string str;
	getline(file, str);
	if (ma[v[3]](a, b))
	{
		v.clear();
		tokenization(str, v);
		check_function(str, v, file);

	}

}


void legal_variable_name_function(std::vector<std::string>& s) {
	if (m.find(s[1]) == m.end()) {//search map
		if (std::find(legal_var_names.begin(), legal_var_names.end(), s[1]) != legal_var_names.end()) {//searh vector
			if ((s[2] == "=") && (is_number(s[3])) && (s[4] == ";")) {
				m[s[1]] = std::stoi(s[3]);
			}
			else {
				std::cout << "Syntax error " << std::endl;
				abort();
			}
		}
		else {
			std::cout << "Error: unlegal variable name" << std::endl;
			abort();
		}
	}
	else {
		std::cout << "Error: existing variable name" << std::endl;
		abort();
	}
} void final_function(std::vector<std::string>& v) {// .- = .- .-.-. -...;
		
	int tmp1;
	int tmp2;
	int tmp3;
		if (m.find(v[2]) != m.end()) {
			tmp1 = m[v[2]];
		}
		else if (is_number(v[2])) {
			tmp1 = stoi(v[2]);
		}
		else {
			std::cout << "Unknown variable" << std::endl;
			abort();
		}
		if (m.find(v[4]) != m.end()) {
			tmp2 = m[v[4]];
		}
		else if (is_number(v[4])) {
			tmp2 = stoi(v[4]);
		}
		else {
			std::cout << "Unknown variable" << std::endl;
			abort();
		}
		if (v[1] == "=") {
		
			m[v[0]] = ma1[v[3]](tmp1, tmp2);
			
		}
		else { std::cout << "syntax error" << std::endl; }
		
}
void check_function(std::string s, std::vector<std::string>& v, std::ifstream& file) {
	if (v.size() == 0) {
		return;
	}
	if (v[0] == "tiv") {

		legal_variable_name_function(v);
	}
	else if (v[0] == "....-.") {
		legal_condition_function(v, file);


	}
	else if (v[0] == "print") {
		std::cout << m[v[1]] << std::endl;
	}
	else if (v[0] == "..-.-") {
		return;
	}
	else if (m.find(v[0])!=m.end()) {
		final_function(v);
	}

	else {
		std::cout << "Error";
		return;
	}

}

int main()
{
	std::vector<std::string>my_vec;
	std::string str{};
	std::ifstream file("C:\\Users\\user\\Desktop\\morse.txt");
	std::cout << " Welcome to MORSE++ " << std::endl;
	std::cout << "*-*-*-*-*-*-*-*-*-*-*" << std::endl;
	if (!file.is_open()) {
		std::cout << "File is not open" << std::endl;
	}
	fill();
	action();
	while (!file.eof()) {
		getline(file, str);
		my_vec.clear();
		tokenization(str, my_vec);
		check_function(str, my_vec, file);

	}
}


