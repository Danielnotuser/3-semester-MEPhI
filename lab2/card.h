#ifndef CARD_H
#define CARD_H

namespace Lib {
    class Card {
        friend class Deck;
        private:
            int suit;
            int rank;
            void randcard();
            void correct();
        public:
            // constructors
            Card() {randcard();};
            Card(int r, int s) {rank = r; suit = s; correct();};
            // setters
            Card &set(int r, int s) {
                rank = r; suit = s; correct();
                return *this;
            }
            // getters
            int getR() const {return rank;}
            int getS() const {return suit;}
            // overload
            Card & operator=(const Card&ob) {rank = ob.rank; suit = ob.suit; return *this;}
            friend std::ostream &operator<<(std::ostream&, const Card&);
            friend std::istream &operator>>(std::istream&, Card&);
            std::partial_ordering operator<=>(const Card&) const;
            bool operator == (const Card&) const = default;
            
    };
    
}

#endif
