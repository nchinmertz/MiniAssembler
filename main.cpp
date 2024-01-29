#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
using namespace std;

unordered_map<string, string> make_labels(const string& infile_name);
vector<string> get_outfile_strings(const string& infile_name, unordered_map<string, string> labels,
                                   unordered_map<string, string> opcode_rep,
                                   unordered_map<string, int> opcode_addressing);
string get_operand(string next, unordered_map<string, string> labels);
void write_outfile(const string& outfile_name, const vector<string>& strings);

int main(int argc, char *argv[]) {
    unordered_map<string, string> opcodes_rep;
    unordered_map<string, int> opcodes_addressing_modes;
    ifstream operands_file;
    operands_file.open("instructions.txt");
    string line;
    while(operands_file >> line){  // maps the opcode to the "machine" representation and the addressing mode
        string rep;
        int address;
        operands_file >> rep;
        operands_file >> address;
        opcodes_rep[line]=rep;
        opcodes_addressing_modes[line]=address;
    }
    string infile_name = argv[1]; // path of input file
    string outfile_name = argv[2];  // path of output file
    unordered_map<string, string> labels = make_labels(infile_name);
    if(labels.find("NONE") != labels.end()){
        cerr <<"ASSEMBLER ERROR: label defined multiple times.\n";
        return 0;
    }
    vector<string> outfile_strings = get_outfile_strings(infile_name, labels, opcodes_rep, opcodes_addressing_modes);
    if(outfile_strings[0]=="Undefined"){
        cerr<<"ASSEMBLER ERROR: undefined label.\n";
        return 0;
    }
    if(outfile_strings[0]=="Addressing"){
        cerr<<"ASSEMBLER ERROR: instruction using unsupported addressing mode.\n";
        return 0;
    }
    write_outfile(outfile_name, outfile_strings);
    return 0;
}

// read through file, converts label names to values and stores in a map
unordered_map<string, string> make_labels(const string& infile_name){
    unordered_map<string, string> labels;
    ifstream infile;
    infile.open(infile_name);
    string line;
    int num_instructions = 0;
    while (getline(infile, line)){
        if (islower(line[0])){
            size_t index = line.find_last_of(':');
            string label = line.substr(0, index);
            if (labels.find(label) != labels.end()){
                infile.close();
                unordered_map<string, string> empty={{"NONE", "NONE"}};
                return empty;
            }
            stringstream s;
            s << hex << uppercase << num_instructions;
            string hex_string = s.str();
            if (hex_string.length() == 1) {hex_string.insert(0, "00");}
            else if (hex_string.length() == 2) {hex_string.insert(0, "0");}
            labels[label] = hex_string;
        }
        else{num_instructions += 1;}
    }
    infile.close();
    return labels;
}

// reads through the file line by line and the corresponding "machine" code instruction, stores in a list of strings
vector<string> get_outfile_strings(const string& infile_name, unordered_map<string, string> labels,
                                   unordered_map<string, string> opcode_rep,
                                   unordered_map<string, int> opcode_addressing){
    vector<string> outfile_strings; // each instruction is a different string
    ifstream infile;
    infile.open(infile_name);
    string line;
    while(infile>>line){
        string output;
        if(line==".word"){
            string word;
            infile>>word;
            if (word.length() == 1) {word.insert(0, "00000");}
            else if (word.length() == 2) {word.insert(0, "0000");}
            else if (word.length() == 3) {word.insert(0, "000");}
            else if (word.length() == 4) {word.insert(0, "00");}
            else if (word.length() == 5) {word.insert(0, "0");}
            outfile_strings.push_back(word);
        }
        if(isupper(line[0])){
            if(opcode_addressing[line] == 0){ // this is an operate instruction and therefore already has an opcode
                output = opcode_rep[line];
            }
            else{  // this is an operand instruction which is an opcode followed by the addressing mode and an operand
                output += opcode_rep[line];
                int addressing_mode = opcode_addressing[line];
                string address1;
                infile >> address1;
                if(address1=="#"){ // checks the opcode supports the addressing mode of the operand instruction
                    if(addressing_mode!=1){
                        infile.close();
                        vector<string> empty = {"Addressing"};
                        return empty;
                    }
                    string next;
                    infile >> next;
                    if(next == "!"){ //addressing mode #! represented by 1 in machine
                        output += "1";
                        infile >> next;
                    }
                    else{output += "0";} //addressing mode # represented by 0 in machine
                    string operand = get_operand(next, labels);
                    if(operand=="NONE"){ // checks operand is there and valid
                        infile.close();
                        vector<string> empty={"Undefined"};
                        return empty;
                    }
                    else{output+=operand;}
                }
                else if(address1=="+"){
                    string next;
                    infile >> next;
                    if(next == "!"){  //addressing mode +! represented by 5 in machine
                        output += "5";
                        infile >> next;
                    }
                    else{output += "4";} //addressing mode + represented by 4 in machine
                    string operand = get_operand(next, labels);
                    if(operand=="NONE"){
                        infile.close();
                        vector<string> empty={"Undefined"};
                        return empty;
                    }
                    else{output+=operand;}
                }
                else if(address1=="*"){
                    string next;
                    infile >> next;
                    if(next == "!"){  //addressing mode *! represented by 7 in machine
                        output += "7";
                        infile >> next;
                    }
                    else{output += "6";} //addressing mode * represented by 6 in machine
                    string operand = get_operand(next, labels);
                    if(operand=="NONE"){
                        infile.close();
                        vector<string> empty={"Undefined"};
                        return empty;
                    }
                    else{output+=operand;}
                }
                else if(address1=="&"){
                    string next;
                    infile >> next;
                    if(next == "!"){ //addressing mode &! represented by 9 in machine
                        output += "9";
                        infile >> next;
                    }
                    else{output += "8";} //addressing mode & represented by 8 in machine
                    string operand = get_operand(next, labels);
                    if(operand=="NONE"){
                        infile.close();
                        vector<string> empty={"Undefined"};
                        return empty;
                    }
                    else{output+=operand;};
                }
                else if(address1=="!"){ //addressing mode ! represented by 3 in machine
                    output += "3";
                    string next;
                    infile >> next;
                    string operand = get_operand(next, labels);
                    if(operand=="NONE"){
                        infile.close();
                        vector<string> empty={"Undefined"};
                        return empty;
                    }
                    else{output+=operand;}
                }
                else{ //addressing mode is represented by nothing represented by 2 in machine
                    output += "2";
                    string operand = get_operand(address1, labels);
                    if(operand=="NONE"){
                        infile.close();
                        vector<string> empty={"Undefined"};
                        return empty;
                    }
                    else{output+=operand;}
                }
            }
            outfile_strings.push_back(output);
        }
    }
    return outfile_strings;
}

// this gets the operand of an operand instruction
string get_operand(string next, unordered_map<string, string> labels){
    string operand;
    if(labels.find(next) != labels.end()){ // if the operand is a label
        operand=labels[next];
    }
    else if(next[0]==36){ //if the operand is a number in base 16
        operand=next.substr(1, next.length());
        if(operand.length()==1){operand.insert(0, "00");}
        else if(operand.length()==2){operand.insert(0, "0");}
    }
    else if (next.find_first_not_of( "0123456789" ) == std::string::npos){ //if operand is a number
        int i;
        istringstream ss(next);
        ss >> i;
        stringstream s;
        s << hex << uppercase << i;
        operand = s.str();
        if(operand.length()==1){operand.insert(0, "00");}
        else if(operand.length()==2){operand.insert(0, "0");}
    }
    else if(labels.find(next) == labels.end()){ //error
        operand = "NONE";
    }
    return operand;
}

void write_outfile(const string& outfile_name, const vector<string>& strings){
    ofstream outfile;
    outfile.open(outfile_name);
    for(auto & string : strings){
        outfile<<string;
        outfile<<"\n";
    }
    outfile.close();
}