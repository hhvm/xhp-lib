#include "xhp_preprocess.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
  bool in_place = false;
  vector<string> files;

  // Parse args
  for (int ii = 1; ii < argc; ++ii) {
    if (strcmp(argv[ii], "-i") == 0) {
      in_place = true;
    } else if (strcmp(argv[ii], "-h") == 0 || strcmp(argv[ii], "-?") == 0) {
      cerr<< argv[0] << " -i [files] | " << argv[0] << " [file]\n";
      return 1;
    } else {
      files.push_back(argv[ii]);
    }
  }

  // Sanity checking
  if (in_place && files.size() == 0) {
    cerr<< "In place mode must be used with at least one file.\n";
    return 1;
  } else if (!in_place && files.size() > 1) {
    cerr<< "Multiple files must be used with in place mode.\n";
    return 1;
  } else if (files.size() == 0) {
    files.push_back("-");
  }

  // Parse
  for (vector<string>::iterator ii = files.begin(); ii != files.end(); ++ii) {

    ifstream inputFile;
    istream *inputStream;
    if (*ii == "-") {
      inputStream = &cin;
    } else {
      inputFile.open(ii->c_str());
      inputStream = &inputFile;
    }

    string code, error;
    uint32_t errLine;
    XHPResult result = xhp_preprocess(*inputStream, code, false, error, errLine);
    inputFile.close();
    if (result == XHPRewrote) {
      if (in_place) {
        ofstream outputFile(ii->c_str());
        outputFile << code;
        outputFile.close();
      } else {
        cout << code;
        cout.flush();
      }
      cerr<< "File `"<<(*ii)<<"` xhpized.\n";
    } else if (result == XHPErred) {
      cerr<< "Error parsing file `"<<(*ii)<<"`!!\n";
    }
  }

  return 0;
}
