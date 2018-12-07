#include "MD5.h"

using namespace std;

int main(void) {
	try {
		string testData;
		cout << "\n\tInput the source string: ";
		getline(cin, testData);
		MD5 mainMD5(testData);
		cout << "\n\tMD5(\"" << testData << "\"): " << mainMD5.getResultStr() << endl;
		return 0;
	}
	catch(...) {
		cerr << "\n\tUnknown exception is captured.\n";
		return 0;
	}
}
