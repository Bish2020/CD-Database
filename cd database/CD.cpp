#include <iostream>
#include <iomanip>
#include <string>

#include "CD.h"

using namespace std;

//*~*~*
// Overloaded > operator. Returns true if the current object
// is set to a value less than that of right.
//*~*~*
bool CD::operator> (const CD &right)
{
    bool status = false;

    if (title > right.title)
        status = true;

    return status;
}

//*~*~*
// Overloaded < operator. Returns true if the current object
// is set to a value less than that of right.
//*~*~*
bool CD::operator< (const CD &right)
{
    bool status = false;

    if (title < right.title)
        status = true;

    return status;
}

//*~*~*
// Overloaded == operator. Returns true if the current object
// is set to a value equal to that of right.
//*~*~*
bool CD::operator ==(const CD &right)
{
    bool status = false;
    
    if (title == right.title)
        status = true;

    return status;
}


//*~*~*
// Overloaded != operator. Returns true if the current object
// is not set to a value equal to that of right.
//*~*~*
bool CD::operator !=(const CD &right)
{
    bool status = false;

    if (barcode != right.barcode)
        status = true;

    return status;
}


ostream &operator << (ostream &strm, const CD &obj)
{
   strm << left << setw(12) << obj.getBarcode() << "   "
        << left << setw(15) << obj.getComposer() << "   "
        << left << setw(24) << obj.getTitle() << "    "
        << left << setw(23) << obj.getConductor()<< "    "
        << right << setw(4) << obj.getYear() << endl;

   return strm;
}
