// fastq2fasta
// Author: Danny Antaki <dantaki@ucsd.edu>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
int main (int argc, char *argv[]) 
{
	const string splash="fastq2fasta converts FASTQ into FASTA\nVersion: 1.0        Author: Danny Antaki <dantaki@ucsd.edu>\n\nUsage: fastq2fasta -i <fastq> -o <output>\n\nOptions:\n"
				"    -i        Input: FASTQ filename\n    -o        Output: FASTA filename\n\n";
	string ifh; // infile
	string ofh; // outfile

	// Parse Arguments
	if ( (argc==1) || 
	     (argc==2 && string(argv[1]) == "-h") || 
	     (argc==2 && string(argv[1]) == "-help") || 
	     (argc==2 && string(argv[1]) == "--help")) {
		cout << "" << endl; cout << splash << endl; 
		return 1;
	}
	
	for(int i=1; i<argc; i++){
		if(string(argv[i]) == "-i" || string(argv[i]) == "--in" || string(argv[i]) == "-in"){
			ifh = string(argv[i+1]);	
			i++;
			continue;
		}
		if(string(argv[i]) == "-o" || string(argv[i]) == "--out" || string(argv[i]) == "-out"){
			ofh = string(argv[i+1]);
			i++;
			continue;
		}
		cerr << "ERROR: Unknown option "<<string(argv[i])<< endl;
		return 1;	
	}
	// check user arguments
	if(ifh == "") { cerr << "ERROR: No FASTQ file given" << endl; return 1; }
	if(ofh == ""){ ofh = ifh.substr(0,ifh.find_last_of('.'))+".fa";  }
	// check if FASTQ file exists
	ifstream fin(ifh.c_str());
	if(!fin) { cerr << "ERROR: Cannot open " << ifh << endl; return 1; } 	
	// open FASTA output for writing
	ofstream fout;
	fout.open (ofh.c_str());
	string line;
	// iterate each line and convert to FASTQ
	unsigned short c=1;
	while(getline(fin,line,'\n')){
		if(c%4==1) { fout << '>' << line.erase(0, 1) << endl; }
		if(c%4==2) { fout << line << endl; } 
		c++;
		if(c==5) {c=1;} 	
	}
	fout.close();
	return 0;
}
