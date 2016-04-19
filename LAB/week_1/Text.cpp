#include<iostream>
#include<string>
using namespace std;

const int SIZE = 18;

const string articles [6] = {" a ", " an ", " the ", "The ", "A ", "An "};
const char vowels [5] = {'a', 'e', 'i', 'o', 'u'};

const string male [SIZE] = {" he ", " him ", " himself ", " boy ", " man ", " son ", "He ", "Father,", " father'", "Father'", "Brother,", 
                                " brother'", "Appa,", "Husband,", " son,", " male ", "Appa and Amma ", " brother "};
                                
const string female [SIZE] = {" she ", " her ", " herself ", " girl ", " woman ", " daughter ", "She ", "Mother,", " mother'", "Mother'",
                                "Sister,", " sister'", "Amma,", "Wife,", " daughter,", " female ", "Amma and Amma ", " sister "};
                                
const string neutral [SIZE] = {" they ", " them ", " themselves ", " child ", " person ", " child ", "They ", "Parent,", " parent'", "Parent'",
                                "Sibling,", " sibling'", "Parent,", "Spouse,", " child,", " ", "Parents ", " sibing "};



class Text {
private:
    string line;
    string::size_type len;
public:
    Text(string l);
    int countArt(void);
    int countVowels(void);
    int numChars(void);
    void neuter(void);
    string str(void);
};


int main(void) {
    //I/O
    string line;
    cout << "Enter a line of text: ";
    getline(cin, line);

    Text t(line);

    cout << "\nNo. of occurrences of articles in given piece of text = " << t.countArt() << endl;
    cout << "\nNo. of occurrences of vowels in given piece of text = " << t.countVowels() << endl;
    cout << "\nNo. of characters given piece of text = " << t.numChars() << endl;

    cout << "\n\nGender-neutering...\n" << endl;
    t.neuter();

    cout << "Neutered text:\n" << endl << "\"" << t.str() << "\"" << endl << endl;
    return 0;
}

Text::Text(string l) {
    line = l;
    len = line.length();
}

int Text::countArt(void) {
    int art_count = 0;

    string::size_type pos; //Index

    for(int i = 0; i < 6; i++) {

        pos = 0;
        while( (pos = line.find(articles[i], pos)) != string::npos) {

            art_count++;
            pos++;
        }
    }
    return art_count;
}

int Text::countVowels(void) {
    int vow_count = 0;

    string::size_type pos;

    for(int i = 0; i < 5; i++) {

        pos = 0;
        while( (pos = line.find(vowels[i], pos)) != string::npos) {

            vow_count++;
            pos++;
        }
    }
    return vow_count;
}

string Text::str(void) {
    return line;
}

int Text::numChars(void) {
    len = line.length();
    return len;
}

void Text::neuter(void) {
    string::size_type pos;

    for(int i = 0; i < SIZE; i++) {
        pos = 0;
        while( (pos = line.find(male[i])) != string::npos) {
            line.erase(pos, male[i].length());
            line.insert(pos, neutral[i]);
        }
    }

    for(int i = 0; i < SIZE; i++) {
        pos = 0;
        while( (pos = line.find(female[i])) != string::npos) {
            line.erase(pos, female[i].length());
            line.insert(pos, neutral[i]);
        }
    }
}
