// Specification file for the CD class
// Modified by: Aman Grewal
// IDE: xCode

#ifndef CD_H
#define CD_H

using std::string;
using std::ostream;

class CD;

// Function Prototypes for Overloaded Stream Operators
ostream &operator << (ostream &, const CD &);

class CD
{
private:
    string barcode, composer, title, conductor;
    int year;

public:
    CD() {barcode = ""; composer = ""; title = ""; conductor = ""; year = -1;}  // Constructor
    CD(string bc, string comp, string t, string cond, int y) // Overloaded Constructor
    {
        barcode = bc;
        composer = comp;
        title = t;
        conductor = cond;
        year = y;
    }

    // Setters and getters
    void setBarcode(string bc) {barcode = bc; }
    void setComposer(string comp) {composer = comp;}
    void setConductor(string cond) {conductor = cond;}
    void setTitle(string t) {title = t;}
    void setYear(int y) {year = y;}


    string getBarcode() const {return barcode;}
    string getComposer() const {return composer;}
    string getConductor() const {return conductor;}
    string getTitle() const {return title;}
    int getYear() const {return year;}


    bool operator >  (const CD &);        // Overloaded >
    bool operator <  (const CD &);        // Overloaded <
    bool operator == (const CD &);       // Overloaded ==
    bool operator != (const CD &);       // Overloaded !=

    // Friends
    friend ostream &operator << (ostream &, const CD &);
};




#endif
