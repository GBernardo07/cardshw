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

    // While there are remaining inputs
    while (std::cin >> suit >> rank) {

        // Convert integers to ranks
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

        // Inserting card in vector
        hand.push_back(c);
    }
}

// Print cards from vector
void print_cards(const std::vector<Card> hand, int range = 0 ) {

        std::cout << "Cards are: " << "[ ";

        // Default range, when user doesn't specifies
        if (range == 0) {

            // Prints all vector
            for (uint i{0}; i < hand.size(); ++i)
                std::cout << hand[i] << " // ";
        }

        // Personalized range
        else {

            //Prints all elements in the requested range
            for (int i{0}; i < range; ++i)
                std::cout << hand[i] << " // ";
        }
        std::cout << " ]" << std::endl; 
}

// STILL NOT WORKING
// Returns a pointer to the last position of the filtered vector
Card* filter(Card *first, Card *last, bool (condition)(Card)) {

    // Declaring reference pointers
    Card *slow{first}, *fast{first};

    // While vector isn't completely traveled
    while (fast != last) { 

        // If element satisfies the condition proposed
        if (condition(*fast)) {

            // Put it in the "slow" position and advance both pointers
            // Behind slow position are the selected elements
            *slow = *fast;
            slow++;
            fast++;
        }
        else {
            fast++;
        }
    }
    return --slow;
}

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
    else 
        return false;
}

// Checks if the card is a figured rank
bool is_figure(const Card c) {

    if (c.r >= 10)
        return true;
    else
        return false;
}

// Checks if the card is a heart
bool is_hearts(const Card c) {

    if (c.s == Card::suit::hearts)
        return true;
    else
        return false;
}

int main(void)
{

    Card *first, *last, *index;
    std::vector<Card> hand, filteredhand;
    bool (*function)(Card);

    // Reading cards from standard input
    read_cards(hand);

    // Setting dummy vector for filtering later
    filteredhand = hand;

    // Printing cards on standard output
    print_cards(hand);

    // Setting pointers to vector
    first = &hand.front();
    last = &hand.back();

    // Finding first red card
    function = is_red;
    std::cout << "First red card: " << *(find_if(first, last, function)) << std::endl;

    // Finding first figured card
    function = is_figure;
    std::cout << "First figured card: " << *(find_if(first, last, function)) << std::endl;

    std::cout << "\n" << "NOT WORKING PROPERLY STARTING NOW" << "\n" << std::endl;

    //Filtering dummy vector, only for figured cards
    index = filter(&filteredhand.front(), &filteredhand.back(), function);
    std::cout << "Only figured cards: " << std::endl;
    print_cards(filteredhand, index - &filteredhand.front());

    function = is_hearts;

    //Filtering again, only for hearted cards now
    index = filter(&filteredhand.front(), &filteredhand.back(), function);
    std::cout << "Only lovely (hearts) cards: " << std::endl;
    filteredhand = hand;
    print_cards(filteredhand, index - &filteredhand.front());

    return 0;
}