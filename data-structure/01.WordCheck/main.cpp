
#include "../WordCheck.hpp"

const int WORDSIZE = 53;

int main()
{
	WordCheck_HashStored wd(string("wordlist.txt"));
	wd.demo_mode();
	
	// HashSet < EnglishWord, decltype(EnglishWord_Hash), decltype(eq) > td(EnglishWord_Hash, eq);
	// td.insert(string("dsvds"));
	// td.insert(string("svsvs"));
	// td.insert(string("dsfgsdgdsdsfds"));
	// auto j = td.getKeysCount();
	

	// WordsCheck wc;
	// wc.demo_mode();
}