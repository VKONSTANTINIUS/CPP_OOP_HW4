//----------Домашнє завдання 4 ООП:
//
// У стартовому класі Vector:
// 
// 1. Додано методи:
//	  - RemoveFront() - метод видаляє значення по індексу 0;
//	  - Insert(value, index) - метод який вставляє значення по індексу без втрати елемента по індексу;
//	  - RemoveByIndex(index) - метод видаляє елемент по індексу;
//	  - RemoveByValue(value) - метод видаляє всі вказані значення з масиву;
//	  - Sort() - метод сортує масив за зростанням;
//	  - Reverse() - метод змінює порядок слідування елементів на протилежний;
//	  - Shuffle() - метод випадковим чином перемішує елементи в масиві.
// 
// 2. Перевантажено операції:
//	  -  << (для сіауту) - для виведення масиву;
//	  -  >> (для сііну) - для введення елементу в кінець масиву;
//	  -  [] - для доступу до елементу масиву;
//	  -  == та != - для можливості порівняння об'єктів класу.
// 
// 3. Додано тестування у функції main.

#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

class Vector {

	unsigned int capacity = 10;								// стартовий запас пам'яті (10 елементів)
	int* data = new int[capacity];							// покажчик на динамічний масив
	unsigned int length = 0;								// фактична кількість елементів, присутніх у масиві

public:
	Vector() {}												// конструктор за замовчуванням

	Vector(const Vector& original) {						// конструктор копіювання
		cout << "COPY C-TOR\n";

		this->length = original.length;
		this->capacity = original.capacity;
		this->data = new int[capacity];

		for (int i = 0; i < length; i++) { 
			this->data[i] = original.data[i]; 
		}
	}

	~Vector() {												// деструктор
		cout << "D-TOR\n";
		if (data != nullptr) {
			delete[] data;
		}
	}

	int Getlength() const {									// гетер для кількості елементів
		return length;
	}

	void Print() const {									// метод виводить всі елементи масиву
		if (length == 0) {
			cout << "масив пустий!\n";
		}
		else {
			cout << "елементи масиву: ";
			for (int i = 0; i < length; i++)
			{
				cout << data[i] << " ";
			}
			cout << "\n";
		}
	}

	void AddToBack(int value) {								// метод додає значення в кінець масиву
		if (length < capacity)								// якщо виділенної пам'яті ВИСТАЧАЄ для додавання чергового елемента
			data[length] = value;
		else { 			
			capacity *= 2;									// збільшуємо запас пам'яті у 2 рази 
			int* temp = new int[capacity]; 
			for (int i = 0; i < length; i++) {
				temp[i] = data[i];
			}
			
			temp[length] = value;
			delete[] data;									// чистимо пам'ять від старого масиву
			data = temp;									// переставляємо покажчик на новий масив
		}
		length++;
	}

	void AddToFront(int value) {							// метод додає значення по індексу 0
		if (length < capacity) { 
			for (int i = length - 1; i >= 0; i--) { 
				data[i + 1] = data[i];
			}
			data[0] = value;
		}
		else { 
			capacity *= 2; 
			int* temp = new int[capacity]; 
			for (int i = 0; i < length; i++) {
				temp[i + 1] = data[i];
			}			
			temp[0] = value;
			delete[] data; 
			data = temp; 
		}
		length++;
	}

	void RemoveFromBack() {										// метод видаляє значення в кінці масиву
		if (length == 0) {
			cout << "масив пустий!\n";
			return;
		}
		length--;
	}
	
	void RemoveFromFront() {									// метод видаляє значення по індексу 0
		if (length == 0) {
			cout << "масив пустий!\n";
			return;
		}
		for (int i = 0; i < length - 1; i++) {
			data[i] = data[i + 1];
		}
		length--;
	
	} 
	
	void Insert(int value, unsigned int index) {				// метод який вставляє значення по індексу 
		
		if (length > capacity) {								// якщо пам'яті не вистачає
			capacity *= 2; 
			int* temp = new int[capacity]; 
			for (int i = 0; i < length; i++) {
				temp[i] = data[i];
			}
			temp[length] = value;
			delete[] data; 
			data = temp; 
		}

		if (index > length) {									// якщо індекс поза межами масиву - додаємо в кінець
			AddToBack(value); 
			return;
		} 
		
		for (int i = length; i > index; i--) {
			data[i] = data[i - 1];
		}
		data[index] = value;
		length++;
	}  
	
	void RemoveByIndex(unsigned int index) {					// метод видаляє елемент по індесу
		if (length == 0) {
			cout << "масив пустий!\n";
			return;
		}
		if (index > length) {									// якщо індекс поза межами масиву - видаляємо останній
			RemoveFromBack();
			return;
		}
		for (int i = index; i < length - 1; i++) {
			data[i] = data[i + 1];
		}
		length--;
	}	
	
	void RemoveByValue(int value) {								// метод видаляє всі вказані значення з масиву
		if (length == 0) {
			cout << "масив пустий!\n";
			return;
		}
		for(int i = 0; i < length; i++){
			if (data[i] == value) {
				for (int j = i; j < length; j++) {
					data[j] = data[j + 1];					
				}
				length--;
				i--;
				
			}			
		}
	}
	
	void Sort() {											// метод сортує масив за зростанням
		sort(data, data + length);
	} 
	
	void Reverse() {										// метод змінює порядок слідуанн елементів на протилежний
		reverse(data, data + length);
	}
	
	void Shuffle() {										// метод випадковим чином перемішує елементи в масиві
		if (length < 2) return;

		for (int i = length - 1; i > 0; i--) {
			int rand_i = rand() % (i + 1);
			swap(data[i], data[rand_i]);
		}

	}
	// Перевантаження через дружні функції

	friend ostream& operator<<(ostream& out, const Vector& arr);	// перевантаження <<  
	friend static istream& operator>>(istream& in, Vector& arr);	// перевантаження >>  
	friend bool operator==(const Vector& arr1, const Vector& arr2);	// перевантаження == 
	friend bool operator!=(const Vector& arr1, const Vector& arr2);	// перевантаження !=
	
	// Перевантаження через метод класу
	const int& operator[](unsigned int index) const {				// перевантаження []
		if (index >= length) {
			throw out_of_range("елемент за межами масиву");
		}
		return data[index];
	}	
};

bool operator==(const Vector& arr1, const Vector& arr2) {	// перевантаження == 
	for (int i = 0; i < arr1.Getlength(); i++) {
		if (arr1.data[i] != arr2.data[i]) {
			return false;
		}
	}
	return true;
}

bool operator!=(const Vector& arr1, const Vector& arr2) {	// перевантаження !=
	return !(arr1 == arr2);
}

ostream& operator<<(ostream& out, const Vector& arr) {		// перевантаження << (для сіауту)
	if (arr.Getlength() == 0) {
		out << "Масив порожній";
	}
	else {
		for (unsigned int i = 0; i < arr.Getlength(); i++) {
			out << arr[i] << " ";
		}
	}
	return out;
}

static istream& operator>>(istream& in, Vector& arr) {		// перевантаження >> (для сііну)
	int value;
	in >> value;
	arr.AddToBack(value);
	return in;

}

int main() {

	SetConsoleOutputCP(1251);
	srand(time(0));

	Vector a;

	for (int i = 0; i < 11; i++) {
		a.AddToFront(i);
	}
	cout << "Початковий масив\n\n";
	a.Print();

	cout << "\nМетод RemoveFromBack()\n\n";
	a.RemoveFromBack();
	a.Print();

	cout << "\nМетод AddToFront(0)\n\n";
	a.AddToFront(0);
	a.Print();

	cout << "\nМетод RemoveFromFront()\n\n";
	a.RemoveFromFront();
	a.Print();

	cout << "\nМетод Insert(111, 5)\n\n";
	a.Insert(111, 5);
	a.Print();

	cout << "\nМетод RemoveByIndex(0)\n\n";
	a.RemoveByIndex(0);
	a.Print();

	cout << "\nМетод RemoveByValue(111)\n\n";
	a.RemoveByValue(111);
	a.Print();

	cout << "\nМетод RemoveByValue(1)\n\n";
	a.AddToBack(1);
	a.AddToBack(1);
	a.AddToBack(1);
	a.AddToBack(1);
	a.AddToBack(1);	
	a.Print();
	a.RemoveByValue(1);
	a.Print();

	cout << "\nМетод Sort()\n\n";
	a.Sort();
	a.Print();

	cout << "\nМетод Reverse()\n\n";
	a.Reverse();
	a.Print();

	cout << "\nМетод Shuffle()\n\n";
	a.Shuffle();
	a.Print();

	cout << "\nПеревантаження операторів:\n\n";

	cout <<"Масив а "<< a << "\n";

	cout << "Елемент масиву а за індексом 3" << a[3] << "\n";

	cout << "\nВведення елементу в масив:\n\n";
	cout << "\nвведіть число: ";
	cin >> a;
	cout << "Масив а " << a << "\n\n";

	Vector b, c;

	for (int i = 0; i < 11; i++) {
		b.AddToFront(i);
		c.AddToFront(i);
	}
	cout << "Масив b " << b << "\n";
	cout << "Масив c " << c << "\n";

	cout << "\nПеревірка операторів ==, !=:\n\n";

	cout << "Умова: b == c - ";

	if (b == c) {
		cout << "Масиви - рівні\n";
	}
	cout << "Умова: a != b - ";
	if (a != b) {
		cout << "Масиви - не рівні\n";
	}
}
