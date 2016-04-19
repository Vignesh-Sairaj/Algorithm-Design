#include<iostream>
#include<string>
using namespace std;

const string articles [6] = {" a ", " an ", " the ", "The ", "A ", "An "};

int main(void) {
    //I/O
    string line;
    cout << "Enter a line of text: ";
    getline(cin, line);

    int art_count = 0;

    string::size_type pos;

    for(int i = 0; i < 6; i++) {

        pos = 0;
        while( (pos = line.find(articles[i], pos)) != string::npos) {

            art_count++;
            pos++;
        }
    }

    cout << "\nNo. of occurrences of articles in given piece of text = " << art_count << endl;
    return 0;
}


