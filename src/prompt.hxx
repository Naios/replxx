#ifndef REPLXX_PROMPT_HXX_INCLUDED
#define REPLXX_PROMPT_HXX_INCLUDED 1

#include <cstdlib>

#include "unicodestring.hxx"
#include "io.hxx"

namespace replxx {

class Prompt {           // a convenience struct for grouping prompt info
public:
	UnicodeString _text;   // our copy of the prompt text, edited

	// Dynamically set
	int _extraLines{0};       // extra lines (beyond 1) occupied by prompt
	int _lastLinePosition{0}; // index into _text where last line begins
	int _previousInputLen{0}; // _characterCount of previous input line, for clearing
	int _previousLen{0};      // help erasing

	// Set based on the particular UnicodeString string
	int _characterCount{0};   // chars in _text
	int _byteCount{0};        // bytes in _text
	int _indentation{0};      // column offset to end of prompt
	int _cursorRowOffset{0};  // where the cursor is relative to the start of the prompt

private:
	int _screenColumns{0};    // width of screen in columns [cache]
	Terminal& _terminal;
public:
	Prompt( Terminal& );
	void set_text( UnicodeString const& textPtr );
	void update_text( UnicodeString const& textPtr );
	void update_screen_columns( void );
	int screen_columns() const {
		return ( _screenColumns );
	}
	void write();
};

// changing prompt for "(reverse-i-search)`text':" etc.
//
struct DynamicPrompt : public Prompt {
	UnicodeString _searchText; // text we are searching for
	int _direction;            // current search _direction, 1=forward, -1=reverse

	DynamicPrompt( Terminal&, int initialDirection );
	void updateSearchPrompt(void);
};

}

#endif
