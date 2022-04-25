#include <iostream>

using namespace std;

// used to empty a given string A of length n
void emptyString(char *A, int n)
{
	for (int i = 0; i < n; i++)
	{
		A[i] = '\0';
	}
}

// copy a string A to B of length n
void stringCopy(char *A, int n, char *B)
{
	for (int i = 0; i < n; i++)
	{
		B[i] = A[i];
	}
}

// return the length of a given string A
int stringLength(char *A)
{
	int size = 0;
	while (A[size] != '\0')
		size++;
	return size; // size is the last index position
}

char* toLowerCaseString(char* a) {
    char* b = new char[stringLength(a) + 1];
    for (int i = 0; a[i] != '\0'; i++) {
        b[i] = a[i];
    }
    b[stringLength(a)] = '\0';
    return b;
}

class myString;

class myString
{
	friend ostream &operator<<(ostream &s, myString &A);

protected:
	char *strArray;
	int size;
	void strCpy(char *A, char *B, int n);

public:
	myString();
	myString(char *inpStr);
	myString(myString &B);
	int Size();
	char *getWord();
	bool operator==(myString &B);
	bool operator>(myString &B);
	bool operator<(myString &B);
	myString &operator=(myString &B);
	myString &operator=(char *B);
};

// outputs a given string A
ostream &operator<<(ostream &s, myString &A)
{
	s << A.strArray;
	return s;
}

// default constructor - initializes with a NULL as the first character
myString::myString() {
    size = 0;
    strArray = new char[1];
    strArray[0] = '\0';
}

// non default constructor - initialize object with an existing string
myString::myString(char* inpStr) {
    int i = 0;
    while (inpStr[i] != '\0')
        i++;
    size = i;
    strArray = new char[size+1];
    emptyString(strArray, size);
    for (int j = 0; j < size; j++)
        strArray[j] = inpStr[j];
    strArray[size] = '\0';
}

// non default constructor - initialize object with an existing mystring object
myString::myString(myString& B) {
    delete[] strArray;
    strArray = NULL;
    size = B.size;
    strArray = new char[size+1];
    emptyString(strArray, size+1);
    stringCopy(B.strArray, size+1, strArray);
    strArray[size] = '\0';
}

char *myString::getWord()
{
	return strArray;
}

// getter for size of myString
int myString::Size()
{
	return size;
}

bool isUrl(char *n)
{
	if (stringLength(n) > 6)
	{
		if (n[0] == 'h' && n[1] == 't' && n[2] == 't' && n[3] == 'p' && n[4] == 's' && n[5] == ':' && n[6] == '/' && n[7] == '/')
		{
			return true;
		}
		if (n[0] == 'h' && n[1] == 't' && n[2] == 't' && n[3] == 'p' && n[4] == ':' && n[5] == '/' && n[6] == '/')
		{
			return true;
		}
	}
	return false;
}

// overloading = operator - initialize object with an existing string
// overloading = operator - initialize object with an existing string
myString& myString::operator = (char* B) {
    delete[] strArray;
    strArray = NULL;
    size = stringLength(B);
    strArray = new char[size+1];
    emptyString(strArray, size);
    stringCopy(B, size, strArray);
    strArray[size] = '\0';
    return *this;
}

// overloading = operator - initialize object with an existing mystring object
myString& myString::operator = (myString& B) {
    delete[] strArray;
    strArray = NULL;
    size = B.size;
    strArray = new char[size+1];
    emptyString(strArray, size);
    stringCopy(B.strArray, size, strArray);
    strArray[size] = '\0';
    return *this;
}

// checking if two myString objects are the same - return true or false
bool myString::operator==(myString &B)
{
	int maxIndex = 0;
	if (this->size == B.size)
	{
		maxIndex = B.size;
	}
	else
	{
		return false;
	}
	char *string1 = toLowerCaseString(this->strArray);
	char *string2 = toLowerCaseString(B.strArray);
	for (int i = 0; i < maxIndex; i++)
	{
		if (string1[i] != string2[i])
		{
			delete[] string1;
			delete[] string2;
			return false;
		}
	}
	delete[] string1;
	delete[] string2;
	return true;
}

// comparison of myString A if less than myString B - return true or false
bool myString::operator<(myString &B)
{
	int maxIndex = 0;
	char *string1 = toLowerCaseString(this->strArray);
	char *string2 = toLowerCaseString(B.strArray);
	if (this->size > B.size)
	{
		maxIndex = B.size;
	}
	else
	{
		maxIndex = this->size;
	}
	for (int i = 0; i < maxIndex; i++)
	{
		if (string1[i] < string2[i])
		{
			delete[] string1;
			delete[] string2;
			return true;
		}
		else if (string1[i] == string2[i])
		{
			continue;
		}
		else
		{
			delete[] string1;
			delete[] string2;
			return false;
		}
	}
	delete[] string1;
	delete[] string2;
	return false;
}

// comparison of myString A if greater than myString B - return true or false
bool myString::operator>(myString &B)
{
	int maxIndex = 0;
	char *string1 = toLowerCaseString(this->strArray);
	char *string2 = toLowerCaseString(B.strArray);
	if (this->size > B.size)
	{
		maxIndex = B.size;
	}
	else
	{
		maxIndex = this->size;
	}
	for (int i = 0; i < maxIndex; i++)
	{
		if (string1[i] > string2[i])
		{
			delete[] string1;
			delete[] string2;
			return true;
		}
		else if (string1[i] == string2[i])
		{
			continue;
		}
		else
		{
			delete[] string1;
			delete[] string2;
			return false;
		}
	}
	delete[] string1;
	delete[] string2;
	return false;
}

// get one URL from redirected input and return it as a string
char *getNextURL()
{
	cout << "getNextUrl" << endl;
	char *str = new char[50]; // assumes a max URL size of 50
	emptyString(str, 50);

	char c;
	int i = 0;
	// read until the next white space or line-break
	while (!cin.eof())
	{
		// cout << "beginning of while loop" << endl;
		cin.get(c);
		// cout << "the current char [" << c << "]" << endl;
		if (!cin.eof())
		{
			if ((c != '\n') && (c != ' '))
			{
				if (((c >= 'a') && (c <= 'z')) ||
					((c >= 'A') && (c <= 'Z')) ||
					((c >= '0') && (c <= '9')) ||
					(c >= ':') || (c >= '/') || (c >= '.') || (c >= '_'))
					str[i++] = c;
			}
			else if ((c == '\n') && (i > 0))
			{
				return str;
			}
			else if ((c == ' ') && (i > 0))
			{
				return str;
			}
		}
		// cout << "test" << endl;

		// g++ -o main main.cpp && ./main < inputs
	}
	// modify the following line of code, so that the function returns only the URLs (i.e., it ignores everything that does not start with http:// or https:// )
	cout << "end of getNextURL" << endl;
	if (i > 0 && isUrl(str))
	{
		return str;
	}
	else return NULL;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class setOfURLs
{
private:
	int binarySearchAndInsert(myString &u);

protected:
	myString *_URLs;
	int *_frequencies;
	int _size;

public:
	setOfURLs();
	setOfURLs(int numOfWords);

	myString *get_Words();
	int *get_Freq();
	int get_size();

	void setSize(int i);

	void addURL(myString &u);												  // insert word w into the array _URLs - keep it sorted alphabetically
	void sortFreq();														  // sort words array based on frequency
	void sortURLs();														  // sort words array alphabetically
	void display();															  // print word followed by a colon followed by a single space and frequencuy
	setOfURLs *removeURLs(myString *URLsToFilterOut, int numURLsToFilterOut); // URLsToFilterOut from _URLs array
	~setOfURLs();
};

// default constructor - initializes with no words
setOfURLs::setOfURLs()
{
	_size = 0;
	_URLs = new myString[1];
	_frequencies = new int[1];
}

// non default constructor - initializes with a known number of words
setOfURLs::setOfURLs(int numOfWords)
{
	_size = numOfWords;
	_URLs = new myString[numOfWords];
	_frequencies = new int[numOfWords];
}

myString *setOfURLs::get_Words()
{
	return _URLs;
}

int *setOfURLs::get_Freq()
{
	return _frequencies;
}

int setOfURLs::get_size()
{
	return _size;
}

void setOfURLs::setSize(int i)
{
	_size = i;
}

// print the bag of words in dictionary format
void setOfURLs::display()
{
	cout << "mySetOfURLs: " << _size << endl;
	for (int i = 0; i < _size; i++)
	{
		cout << _URLs[i] << " " << _frequencies[i] << endl;
	}
}

// sort the _URLs and _frequencies based on frequencies
void setOfURLs::sortFreq()
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = i + 1; j < _size; j++)
		{
			if (_frequencies[i] > _frequencies[j])
			{
				int freq = _frequencies[i];
				_frequencies[i] = _frequencies[j];
				_frequencies[j] = freq;
				myString url = _URLs[i];
				_URLs[i] = _URLs[j];
				_URLs[j] = url;
			}
		}
	}
}

// sort the _URLs and _frequencies, alphabetically
void setOfURLs::sortURLs()
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = i + 1; j < _size; j++)
		{
			if (_URLs[i] > _URLs[j])
			{
				myString url = _URLs[i];
				_URLs[i] = _URLs[j];
				_URLs[j] = url;
				int freq = _frequencies[i];
				_frequencies[i] = _frequencies[j];
				_frequencies[j] = freq;
			}
		}
	}
}

setOfURLs *setOfURLs::removeURLs(myString *URLsToFilterOut, int numURLsToFilterOut)
{
	bool isFilteredURL = false;
	setOfURLs *tempSet = new setOfURLs(_size - numURLsToFilterOut);
	tempSet->_size = _size - numURLsToFilterOut;
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < numURLsToFilterOut; j++)
		{
			if (_URLs[i] == URLsToFilterOut[j])
			{
				isFilteredURL = true;
			}
		}
		if (!isFilteredURL)
		{
			for (int k = 0; k < tempSet->_size; k++)
			{
				if (tempSet->_URLs[k].Size() == 0)
				{
					tempSet->_URLs[k] = _URLs[i];
					tempSet->_frequencies[k] = _frequencies[i];
				}
			}
		}
		else
		{
			isFilteredURL = false;
		}
	}
	return tempSet;
}

// to search for a given word in _URLs - returns 0 if not found, 1 if found
int setOfURLs::binarySearchAndInsert(myString &wordToFind)
{
	int lowerIdx = 0;
	int upperIdx = _size - 1;
	while (lowerIdx <= upperIdx)
	{
		int midIdx = lowerIdx + (upperIdx - lowerIdx) / 2;
		if (wordToFind == (_URLs[midIdx]))
		{
			_frequencies[midIdx] += 1;
			return 1;
		}
		if (wordToFind > (_URLs[midIdx]))
			lowerIdx = midIdx + 1;
		else
			upperIdx = midIdx - 1;
	}
	return 0;
}

// method to add words to the setOfURLs object
void setOfURLs::addURL(myString &newWord)
{
	// if there is already unassigend initlized value
	for (int i = 0; i < _size; i++)
	{
		if (_URLs[i].Size() == 0)
		{
			_URLs[i] = newWord;
			_frequencies[i] = 1;
			return;
		}
	}
	// if there is no empty space creates some
	myString *temp = new myString[_size + 1];
	int *tempFreq = new int[_size + 1];
	for (int i = 0; i < _size; i++)
	{
		temp[i] = _URLs[i];
		tempFreq[i] = _frequencies[i];
	}
	_frequencies[_size] = 1;
	temp[_size] = newWord;
	delete[] _URLs;
	_URLs = temp;
	delete[] temp;
	_size = _size + 1;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class URLLinks
{
	friend ostream &operator<<(ostream &s, URLLinks &A);

protected:
	myString URL;
	int numLinks;
	URLLinks **hyperLinks;

public:
	URLLinks();
	URLLinks(myString &x, int n);
	~URLLinks();
	int getNumLinks();
	URLLinks *getHyperLink(int i);
	myString &getURL();
	void addSite(myString &t);
	void addNeighbor(URLLinks &link);
	void setNeighbors(int nei);
};

ostream &operator<<(ostream &s, URLLinks &A)
{
	s << A.hyperLinks;
	return s;
}

URLLinks::URLLinks()
{
	numLinks = 0;
	hyperLinks = new URLLinks *[0];
}

URLLinks::URLLinks(myString &x, int n)
{
	URL = x;
	numLinks = n;
	hyperLinks = new URLLinks *[numLinks];
	for (int i = 0; i < numLinks; i++)
	{
		hyperLinks[i] = new URLLinks[1];
	}
}

myString &URLLinks::getURL()
{
	return URL;
}

int URLLinks::getNumLinks()
{
	return numLinks;
}

URLLinks *URLLinks::getHyperLink(int i)
{
	return hyperLinks[i];
}

URLLinks::~URLLinks()
{
	for (int i = 0; i < numLinks; i++)
	{
		delete[] hyperLinks[i];
	}
	delete[] hyperLinks;
}
// check this
void URLLinks::addSite(myString &t)
{
	URL = t;
}

void URLLinks::setNeighbors(int nei)
{
	URLLinks **temp = new URLLinks *[numLinks];
	for (int i = 0; i < numLinks; i++)
	{
		for (int j = 0; j < numLinks; j++)
		{
			temp[i][j] = hyperLinks[i][j];
		}
	}
}

void URLLinks::addNeighbor(URLLinks &link)
{

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main()
{

	int numURLsToFilterOut;
	char *url;
	myString *urlString;
	int numPages;
	int pageNo;
	int numNeighbors;
	int neighbor;

	cout << endl
		 << "----------------------------------------------------------" << endl;
	// read the first number from the file that contains the number of stop words
	cin >> numURLsToFilterOut;
	cout << "Number of Stop words: " << numURLsToFilterOut << endl;
	myString *URLsToFilterOutList = new myString[numURLsToFilterOut];
	cout << endl
		 << "----------------------------------------------------------" << endl;
	// read the stop words
	for (int i = 0; i < numURLsToFilterOut; i++)
	{
		url = getNextURL();
		URLsToFilterOutList[i] = url; // calls the overloaded = operator on myString class
	}
	cout << endl
		 << "----------------------------------------------------------" << endl;
	// Now read a text and put them in the setOfURLs instance.
	setOfURLs *mySetOfURLs = new setOfURLs();

	url = getNextURL();
	cout << endl
		 << "----------------------------------------------------------" << endl;
	while (url != NULL)
	{
		cout << "beginning of while loop" << endl;
		urlString = new myString(url); // create a myString object with the URL
		cout << "after first line" << endl;
		(*mySetOfURLs).addURL(*urlString); // add URL to mySetOfURLs
		cout << "after second line" << endl;
		url = getNextURL();
		cout << "last line" << endl;
	}
	cout << endl
		 << "----------------------------------------------------------" << endl;
	// this should display the URL and frequency;
	// note that becuase you are using binary search and insert the URLs will
	// be sorted alphabetically
	cout << endl;
	cout << "Input display:" << endl;
	(*mySetOfURLs).display();

	(*mySetOfURLs).sortFreq();
	cout << endl;
	cout << "mySetOfURLs - Sorted based on frequency:" << endl;
	(*mySetOfURLs).display();

	(*mySetOfURLs).sortURLs();
	cout << endl;
	cout << "mySetOfURLs - Sorted alphabetically:" << endl;
	(*mySetOfURLs).display();

	setOfURLs *newSetOfURLs = (*mySetOfURLs).removeURLs(URLsToFilterOutList, numURLsToFilterOut); // new parameter added here
	cout << endl;
	cout << "newSetOfURLs - Sorted alphabetically:" << endl;
	(*newSetOfURLs).display();

	(*newSetOfURLs).sortFreq();
	cout << endl;
	cout << "newSetOfURLs - Sorted based on frequency:" << endl;
	(*newSetOfURLs).display();

	cin >> numPages;
	cout << "Number of websites: " << numPages << endl;

	URLLinks *myLinkStructure = new URLLinks[numPages];
	for (int i = 0; i < numPages; i++)
	{
		// read all URL and store them in the myLinkStructure array of URLLink objects
	}

	// store the neighbours/hyperlinks
	for (int i = 0; i < numPages; i++)
	{
		cin >> pageNo >> numNeighbors;
		myLinkStructure[i].setNeighbors(numNeighbors);
		for (int j = 0; j < numNeighbors; j++)
		{
			cin >> neighbor;
			myLinkStructure[pageNo].addNeighbor((myLinkStructure[neighbor]));
		}
	}

	// display all URLLink objects using the overloaded << operator

	cout << "~~~~~Webpages contained as hyperLinks:" << endl;
	// display all the incoming nodes here

	// TODO : destructors
	// delete [] URLsToFilterOutList;
	// delete mySetOfURLs;
	// delete newSetOfURLs;

	delete[] myLinkStructure;

	return 0;
}
