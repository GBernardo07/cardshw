#include <iostream>
#include <vector>

// Cards defined as structs with suits and ranks
struct Card {
    enum class suit : int
    {
        clubs    = 0,
        diamonds = 1,
        hearts   = 2,
        spades   = 3,
    };

    suit s;
    unsigned short r; // rank
};

// ?
std::ostream& operator<<( std::ostream& os, const Card & c ) {
    std::string ranks_to_str[]{"as", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king", "joker"};
    std::string suits_to_str[]{ "clubs", "diamonds", "hearts", "spades" };
    os << ranks_to_str[c.r];
    if ( c.r < 13 ) os << " of " << suits_to_str[static_cast<int>(c.s)];

    return os;
}

// Read cards from standard input and store them in vector
void read_cards(std::vector<Card> &hand ) {

    Card c;
    short suit, rank;
    while (std::cin >> suit >> rank) {
        switch (suit) {
            case 0:
                c.s = Card::suit::clubs;
                break;
            case 1:
                c.s = Card::suit::diamonds;
                break;
            case 2:
                c.s = Card::suit::hearts;
                break;
            case 3:
                c.s = Card::suit::spades;
                break;
            default:
                return ;
        }
        c.r = rank;
        hand.push_back(c);
    }
}

// Print cards from vector
void print_cards(const std::vector<Card> hand ) {

    std::cout << "Cards are: " << "[ ";
    for (uint i{0}; i < hand.size(); ++i)
        std::cout << hand[i] << " // ";
    std::cout << " ]" << std::endl;
}

// TODO
// Card* filter()

// Return pointer to first card with matching condition
Card* find_if( Card *first, Card *last, bool (condition)(Card) ) {	
	for (Card *pointer{first}; pointer != last; ++pointer ) {
		if (condition(*pointer))
			return pointer;
	}
		return nullptr;
}

// Checks if the card is red
bool is_red(const Card c) {

    if (c.s == Card::suit::hearts || c.s == Card::suit::diamonds)
        return true; 
    return false;
}

// Checks if the card is a figured rank
bool is_figure(const Card c) {

    if (c.r >= 11)
        return true;
    return false;
}

int main(void)
{

    Card *first, *last;
    std::vector<Card> hand;
    bool (*function)(Card);

    read_cards(hand);
    print_cards(hand);

    first = &hand.front();
    last = &hand.back();

    // Finding first red card
    function = is_red;
    std::cout << "First red card: " << *(find_if(first, last, function)) << std::endl;

    // Finding first figured card
    function = is_figure;
    std::cout << "First figured card: " << *(find_if(first, last, function)) << std::endl;

    return 0;
}