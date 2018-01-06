#include <iostream>
#include <fstream>
#include <string>

class Object
{
public:
	//klucz
	long key_;
	//wartoœæ
	std::string txt_;
	//e-empty||c-next||f-full
	char flag_='e';
	Object::Object(long _key, std::string _txt)
	{
		key_ = _key;
		txt_ = _txt;
	}
	Object::Object()
	{
	}
	Object::~Object()
	{
	}
};
class HashTable
{
public:
	//tworzenie tablicy dynamicznej
	long size_ = 0;
	Object *tab_;
	HashTable::HashTable()
	{
		tab_ = new Object;
	}
	HashTable::~HashTable()
	{
		//usuwanie tablicy
		delete[] tab_;
	}

	void createtable()
	{
		tab_ = new Object[size_];
		for (long i = 0; i < size_; i++)
		{
			tab_[i].flag_ = 'e';
		}
	}
	void Size(long _size)
	{
		size_ = _size;
		createtable();
	}
	//wyœwietlanie tablicy
	void Print()
	{
		for (long i = 0; i < size_; i++)
		{
			if (tab_[i].flag_ != 'e')
			{
				std::cout << i << " " << tab_[i].key_ << "  " << tab_[i].txt_ << " "<<tab_[i].flag_<< std::endl;
			}
		}
		std::cout << std::endl;
	}
	//funkcja hashuj¹ca
	long F_hash(long _key, long _size)
	{
		return _key % _size;
	}
	//dodawanie elementu do tablicy
	void Add(Object &o)
	{
		long n = F_hash(o.key_, size_);
		//dzia³a do puki nie znajdzie wolnego miejsca w tablicy
		while (tab_[n].flag_ != 'e')
		{
			//jeœli flaga =f to zamienia j¹ na c
			if (tab_[n].flag_ == 'f')
			{
				tab_[n].flag_ = 'c';
			}
			//jeœli trafimy na ostatni index w tablicy to zaczynamy od pocz¹tku(0)
			if (n == size_ - 1)
			{
				n = 0;
			}
			//pracujemy na indeksach rosn¹co
			else
			{
				n++;
			}
		}
		//jeœli znajdziemy wolne miejsce w tablicy(takie gdzie flaga == e) to wpisujemy do niego obiekt i nadajemy mu flagê f
		tab_[n] = o;
		tab_[n].flag_ = 'f';
	}
	//usuwanie elementu z tablicy po kluczu (ko¿ysta z usuwania po indeksie)
	void Del(long n)
	{
		for (int pom = 0; pom != size_;pom++)
		{
			if (tab_[pom].flag_ != 'e' || tab_[pom].key_== n)
			{
				std::cout << pom << std::endl;
				Del_zle(pom);
			}
		}
	}
	//usuwanie z tablicy po indeksie
	void Del_zle(long n)
	{
		//dzia³ania dla flagi == f
		if (tab_[n].flag_ == 'f')
		{
			long pom = F_hash(tab_[n].key_, size_);
			//usuwanie n elementu z tablicy
			tab_[n].flag_ = 'e';
			//jeœli 0 to zacznij od ostatniego elementu w tablicy
			if (n == 0)
			{
				n = size_-1;
			}
			//pracujemy na indeksach malej¹co
			else
			{
				n--;
			}
			//jeœli flaga == c to zamieniamy j¹ na f
			if (tab_[n].flag_ == 'c')
			{
				tab_[n].flag_ = 'f';
			}
			//pêtla dzia³¹ dopuki wynik funkcji hashuj¹cej [n] jest ró¿ny od zmiennej pomocniczej równej funkcji hasuj¹cej od pocz¹tkowego n 
			while (F_hash(tab_[n].key_, size_) != pom)
			{
				// jeœli 0 to zacznij od ostatniego elementu w tablicy
				if (n == 0)
				{
					n = size_ - 1;
				}
				//pracujemy na indeksach malej¹co
				else
				{
					n--;
				}
				//jeœli znajdziemy szukane n to obiekt znajduj¹cy siê pod tym indeksem jest usuwany i dodawany ponownie
				if (F_hash(tab_[n].key_, size_) == pom)
				{
					tab_[n].flag_ = 'e';
					Add(tab_[n]);
				}
			}
		}
		//dzia³ania dla flagi == c
		else if (tab_[n].flag_ == 'c')
		{
			//usuwamy element n
			tab_[n].flag_ = 'e';
			// jeœli 0 to zacznij od pierwszego elementu tablicy(0)
			if (n == size_ - 1)
			{
				n = 0;
			}
			//pracujemy na indeksach rosn¹co
			else
			{
				n++;
			}
			//pracuje do puki nie natrafi na element o fladze ==f(usuwa i dodaje wszystkie elementy a¿ do napotkania takiego o fladze == f)
			while (tab_[n].flag_ != 'f')
			{
				//usuwa element n i dodaje go ponownie
				tab_[n].flag_ = 'e';
				Add(tab_[n]);
				// jeœli 0 to zacznij od pierwszego elementu tablicy(0)
				if (n == size_ - 1)
				{
					n = 0;
				}
				//pracujemy na indeksach rosn¹co
				else
				{
					n++;
				}
			}
			//jeœli znajdziemy element o fladze == f to go usuwamy i dodajemy ponownie
			if (tab_[n].flag_ == 'f')
			{
				tab_[n].flag_ = 'e';
				Add(tab_[n]);
			}
		}
	}
	//koniec dzia³ania na tablicy(koniec programu lub rozpoczêcie pracy na nowej tablicy)
	void stop()	
	{
		for (int i = 0; i < size_; i++)
		{
			tab_[i].flag_ = 'e';
		}
	}


};



int main()
{
	HashTable h_;
	//pom wraz z N okreœlaj¹ ile mamy przypadków testowych
	long pom = 0;
	long N = 0;
	std::string x;
	long y;
	std::cin >> N;


	while (pom < N)
	{
		std::cin >> x;
		if (x == "size")
		{
			std::cin >> y;
			h_.Size(y);
		}
		else if (x=="add")
		{
			std::cin >> y;
			std::cin >> x;
			Object o(y, x);
			h_.Add(o);

		}
		else if (x == "print")
		{
			h_.Print();
		}
		else if (x == "delete")
		{
			std::cin >> y;
			h_.Del(y);

		}
		else if (x == "stop")
		{
			h_.stop();
			pom += 1;
		}
	}

	system("pause");

	return 0;
}

