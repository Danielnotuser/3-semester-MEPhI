#include <iostream>
#include <algorithm>
#include <random>
#include "deck.h"

namespace Lib {

	void FullDeck::full_deck()
	{
		int k = 0;
		for (int i = 2; i < 15; i++)
		{
			for (int j = 1; j < 5; j++)
			{
				arr[k].set(i, j);
			    k++;
			}
		}	
	}
	
    Deck::Deck(int n) : size(n)
    {
		if (size < 0 || size > 52)
			throw std::invalid_argument("invalid size");
		else if (size == 0)
			deck = nullptr;
		else
		{
			deck = new Card[size];
			for (int i = 0; i < size; i++)
			{
				deck[i] = fd.arr[rand() % 52];
			}
		}
    }

	Deck::Deck(const Deck &ob) : deck(nullptr), size(ob.size)
	{
		if (size)
		{
			deck = new Card[size];
			std::copy(ob.deck, ob.deck + size, deck);
		}
	}

	Deck::Deck(Deck &&ob) noexcept : deck(ob.deck), size(ob.size) 
	{
		ob.size = 0;
		ob.deck = nullptr;
	}

	Deck & Deck::operator=(const Deck &ob) 
	{
		if (this != &ob)
		{
			delete [] deck;
			deck = nullptr;
			size = ob.size;
			if (size)
			{
				deck = new Card[size];
				std::copy(ob.deck, ob.deck + size, deck);
			}
		}
		return *this;
	}

	Deck & Deck::operator=(Deck &&ob) noexcept
	{
		if (size) delete [] deck;
		size = ob.size;
		deck = ob.deck;
		ob.size = 0;
		ob.deck = nullptr;
		return *this;
	}

	Card &Deck::operator[](int ind) const
	{
		if (ind < 0 || ind >= size) 
			throw std::invalid_argument("invalid index");
		return deck[ind];
	}

    std::ostream &operator<<(std::ostream& c, const Deck& d)
    {
    	int n = d.getS();
    	for (int i = 0; i < n; i++)
    	{
    		c << d[i] << " ";
    	}
    	c << std::endl;
    	return c;
    }

	std::istream &operator>>(std::istream &c, Deck &d)
	{
		int sz;
		std::cout << "Enter size: ";
		c >> sz;
		if (c.good())
		{
			Deck tmp = Deck(sz);
			d = std::move(tmp);
		}
		return c;
	}

	Deck Deck::operator+(const Deck &other) const
	{
		Deck d;
		d.size = size + other.size;
		d.deck = new Card[d.size];
		std::copy(deck, deck + size, d.deck);
		std::copy(other.deck, other.deck + other.size, d.deck + size);
		return d;
	}

	void Deck::add_rand()
	{
		Card c;
		Card *tmp = new Card[size + 1];
		std::copy(deck, deck + size, tmp);
		delete [] deck;
		tmp[size] = c;
		deck = tmp;
		size++;
	}

	void Deck::add(const Card &c)
	{
		Card *tmp = new Card[size + 1];
		std::copy(deck, deck + size, tmp);
		delete [] deck;
		tmp[size] = c;
		deck = tmp;
		size++;
	}

	void Deck::shuffle()
	{
		std::shuffle(deck, deck + size, std::random_device());
	}

	bool Deck::unique() const
	{
		for (int i = 0; i < size - 1; i++)
			for (int j = i + 1; j < size; j++)
				if (deck[i] == deck[j])
					return false;
		return true;
	}

	Deck Deck::sub_deck(int s) const
	{
		Deck sub;
		int cnt = 0;
		for (int i = 0; i < size; i++)
			if (deck[i].getS() == s) {
				sub.add(deck[i]);
				cnt++;
			}
		sub.size = cnt;
		return sub;
	}

	Deck &Deck::del(int ind)
	{
		if (ind < 0 || ind >= size)
			throw std::invalid_argument("invalid index");
		Card *tmp = new Card[size - 1];
		std::copy(deck, deck + ind, tmp);
		if (ind != size - 1)
			std::copy(deck + ind + 1, deck + size, tmp + ind);
		delete [] deck;
		deck = tmp;
		size -= 1;
		return *this;
	}

	bool Deck::cmp(const Card &c1, const Card &c2)
	{
		return ((c1.getS() < c2.getS()) || (c1.getS() == c2.getS() && c1.getR() < c2.getR()));
	}

	void Deck::sort()
	{
		std::sort(deck, deck + size, cmp);
	}


}
