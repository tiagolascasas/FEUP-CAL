#ifndef STRINGFUNCTIONS_H_
#define STRINGFUNCTIONS_H_

#include <string>
#include <queue>
#include <numeric>

using namespace std;

/**
 * This class holds a string and the "closeness" of that string
 * to other. It is simply used to provide a method to sort strings
 * based on their closeness to a predetermined pattern
 */
class ApproxString
{
private:
	string s;		/// the string
	int closeness;	/// the closeness of the string to the pattern

public:
	/**
	 * Constructor for an ApproxString object
	 * @param s the string
	 * @param closeness the closeness of the string to the pattern
	 */
	ApproxString(string s, int closeness);

	/**
	 * Returns the string
	 * @return the string
	 */
	string getString() const;
	/**
	 * Returns the closeness of the string
	 * @return the closeness of the string
	 */
	int getCloseness() const;

	/**
	 * Compares two ApproxString objects using the < operator
	 * @param as the object to compare to
	 * @return true if closeness of "this" > closeness of "as", false otherwise
	 */
	bool operator<(const ApproxString as) const;
};

/**
 * Removes all whitespaces at the beginning and
 * the ending of a string
 * @param s the string to be trimmed (passed by reference)
 */
void trim(string &s);

/**
 * Checks if a certain pattern can be found in a
 * certain text using the Knuth-Morris-Pratt algorithm
 * @param text the text to analyse
 * @param pattern the pattern to search for
 * @param caseSensitive true to consider case sensitiveness, false to not consider
 * @return string if the pattern was found, empty string otherwise
 */
string kmpStringMatching(string &text, string pattern, bool caseSensitive);

/**
 * Scans a set of strings, ordering them by resemblance to a certain pattern
 * @param text the set of strings
 * @param pattern the pattern to compare to
 * @param caseSensitive true to consider case sensitiveness, false to not consider
 * @return a priority queue with the strings, with the most approximate one at the head
 */
priority_queue<ApproxString> approximateStringMatching(vector<string> &text, string pattern, bool caseSensitive);

/**
 * Compares a string with a pattern to determine the amount of operations (deletion, addition or substitution) needed to turn the string into the pattern
 * @param t the string to be tested
 * @param p the pattern to be used as base for comparison
 * @param caseSensitive true to consider case sensitiveness, false to not consider
 * @return an integer symbolising the amount of operations needed to make both strings similar
 */
int levenshtein_distance(const string &t, const string &p, bool caseSensitive);

#endif /* STRINGFUNCTIONS_H_ */
