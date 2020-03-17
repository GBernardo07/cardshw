/*
 * Exercicio:
 * 
 * 1) Ler cartas da entrada padrão. OK
 * 2) Implementar alg. find_if() OK
 * 3) Implementar alg. filter()
 * 4) Aplicar nas situações:
 *      4A) Usar find_if para: Achar a primeira carta cujo valor da face seja uma figura (valete, dama, rei). OK
 *      4B) Usar find_if para: Achar a primeira carta que seja vermelha. OK
 *      4C) Usar filter para: Selecioar em um vetor apenas as cartas de "hearts"
 *      4C) Usar filter para: Selecioar apenas as cartas com figuras.
 */

#include <iostream>

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
std::ostream& operator<<( std::ostream& os, const Card & c )
{
    std::string ranks_to_str[]{"as", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king", "joker"};
    std::string suits_to_str[]{ "clubs", "diamonds", "hearts", "spades" };
    os << ranks_to_str[c.r];
    if ( c.r < 13 ) os << " of " << suits_to_str[static_cast<int>(c.s)];

    return os;
}

Card* find_if( Card *first, Card *last, bool (condition)(Card) )
{	
	for (Card *pointer{first}; pointer != last; ++pointer ) {
		if (condition(*pointer))
			return pointer;
	}
		return nullptr;
}

// Checks if the card is red
bool is_red(Card c) {

    if (c.s == Card::suit::hearts || c.s == Card::suit::diamonds)
        return true; 
    return false;
}

// Checks if the card is a figured rank
bool is_figure(Card c) {

    if (c.r >= 11)
        return true;
    return false;
}

int main(void)
{

    Card hand[20];
    int suit;
    for (int i{0}; std::cin >> suit; ++i) {
        switch (suit) {
            case 0:
                hand[i].s = Card::suit::clubs;
                break;
            case 1:
                hand[i].s = Card::suit::diamonds;
                break;
            case 2:
                hand[i].s = Card::suit::hearts;
                break;
            case 3:
                hand[i].s = Card::suit::spades;
                break;
            default:
                return 0;
        }
        std::cin >> hand[i].r;
    }

    bool (*function)(Card);

    function = is_red;
    std::cout << "first red card: " << *(find_if(hand, std::end(hand), function)) << std::endl;

    function = is_figure;
    std::cout << "first figured card: " << *(find_if(hand, std::end(hand), function)) << std::endl;

    return 0;
}
