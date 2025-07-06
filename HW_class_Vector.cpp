

#include <iostream>
#include <windows.h>
#include <algorithm>

using namespace std;

class Vector {

	unsigned int capacity = 10; // при створенні масиву, він одразу для себе робить запас пам'яті на 10 елементів
	int* data = new int[capacity];
	unsigned int length = 0; // фактична (реальна) кількість елементів, присутніх у масиві

public:
	Vector() {}

	Vector(const Vector& original) {
		cout << "COPY C-TOR\n";

		this->length = original.length;
		this->capacity = original.capacity;
		this->data = new int[capacity];

		for (int i = 0; i < length; i++) this->data[i] = original.data[i];
	}

	void AddToBack(int value) {
		if (length < capacity) // якщо виділенної зарання пам'яті ВИСТАЧАЄ для додавання чергового елемента
			data[length] = value;
		else { // АЛЕ ЯКЩО МІСЦЯ ВЖЕ НЕ ВИСТАЧАЄ, ТО
			// треба перевиділити пам'ять
			capacity *= 2; // збільшуємо запас пам'яті у 2 рази (можна і в 1.5, можна і в 1.2)
			// якщо був запас 10 елементів, то стане 20
			// якщо запас був 20 елементів, то стане 40, і тд
			int* temp = new int[capacity]; // новий масив буде в 2 рази більше по пам'яті
			// але в старому масиві все ще усього 10 елементів, тому цикл треба написати так, щоб зачепити лише старі елементі зі старого масиву
			for (int i = 0; i < length; i++) {
				temp[i] = data[i];
			}
			// в новий масив в кінець (по індексу 10) пишеться ОДИНАДЦЯТИЙ елемент
			temp[length] = value;
			delete[] data; // в цілях запобігання витокам пам'яті, чистимо пам'ять від старого масиву
			data = temp; // переставляємо покажчик на новий масив
		}
		length++;
	}

	void AddToFront(int value) {
		if (length < capacity) { // ще є вільна пам'ять під черговий елмент
			// перевиділяти пам'ять на 1 елемент кожен раз - погана ідея
			// (якщо елементів буде більше ніж 300000+ то все буде відбуватися максимально повільно)
			// при тому що пам'ять вже виділена (є кепесіті), 
			// то доведеться зробити зсув для всіх існуючих елементів на 1 вправо
			for (int i = length - 1; i >= 0; i--) { // зсув іде справа наліво (тому що якщо робити його зліва направо, з початку масива в кінець) то можна втратити існуючі елементи
				data[i + 1] = data[i];
			}
			data[0] = value;
		}
		else { // АЛЕ ЯКЩО МІСЦЯ ВЖЕ НЕ ВИСТАЧАЄ, ТО
			// треба перевиділити пам'ять
			capacity *= 2; // збільшуємо запас пам'яті у 2 рази (можна і в 1.5, можна і в 1.2)
			// якщо був запас 10 елементів, то стане 20
			// якщо запас був 20 елементів, то стане 40, і тд
			int* temp = new int[capacity]; // новий масив буде в 2 рази більше по пам'яті
			// але в старому масиві все ще усього 10 елементів, тому цикл треба написати так, щоб зачепити лише старі елементі зі старого масиву
			for (int i = 0; i < length; i++) {
				temp[i + 1] = data[i];
			}
			// в новий масив в початок (по індексу 0) пишеться ОДИНАДЦЯТИЙ елемент
			temp[0] = value;
			delete[] data; // в цілях запобігання витокам пам'яті, чистимо пам'ять від старого масиву
			data = temp; // переставляємо покажчик на новий масив
		}
		length++;
	}

	void RemoveFromBack() {
		if (length == 0) {
			cout << "масив пустий, видаляти НЕМА ЧОГО!\n";
			return;
		}
		length--;
	}

	// написати:
	void RemoveFromFront() {		//- метод видаляє значення по індексу 0
		if (length == 0) {
			cout << "масив пустий, видаляти НЕМА ЧОГО!\n";
			return;
		}
		for (int i = 0; i < length - 1; i++) {
			data[i] = data[i + 1];
		}
		length--;
	
	} 
	
	void Insert(int value, unsigned int index) {		// - метод який вставляє значення по індексу без втрати елемента по індексу
		
		if (length > capacity) { // якщо пам'яті не вистачає
			capacity *= 2; 
			int* temp = new int[capacity]; 
			for (int i = 0; i < length; i++) {
				temp[i] = data[i];
			}
			temp[length] = value;
			delete[] data; 
			data = temp; 
		}

		if (index > length) { //якщо індекс поза межами масиву - додаємо в кінець
			AddToBack(value); 
			return;
		} 
		
		for (int i = length; i > index; i--) {
			data[i] = data[i - 1];
		}
		data[index] = value;
		length++;
	}  
	
	void RemoveByIndex(unsigned int index) {		//- метод видаляє елемент по індесу
		if (length == 0) {
			cout << "масив пустий, видаляти НЕМА ЧОГО!\n";
			return;
		}
		if (index > length) { //якщо індекс поза межами масиву - видаляємо останній
			RemoveFromBack();
			return;
		}
		for (int i = index; i < length - 1; i++) {
			data[i] = data[i + 1];
		}
		length--;
	}	
	
	void RemoveByValue(int value) {		//- метод видаляє всі вказані значення з масиву
		if (length == 0) {
			cout << "масив пустий, видаляти НЕМА ЧОГО!\n";
			return;
		}
		for(int i = 0; i < length; i++){
			if (data[i] == value) {
				for (int j = i; j < length; j++) {
					data[j] = data[j + 1];
					
				}
				length--;
				
			}
			
		}

	}
	
	void Sort() {		//- метод сортує масив за зростанням
	
	} 
	
	void Reverse() {		//- метод змінює порядок слідуанн елементів на протилежний


	}
	
	void Shuffle() {	//- метод випадковим чином перемішує елементи в масиві


	}

	// перевантажити:
	// cout <<
	// cin >> 
	// []

	void Print() const {
		if (length == 0) {
			cout << "масив пустий!\n";
		}
		else {
			cout << "ємність масиву: " << capacity << "\n";
			cout << "елементи масиву: ";
			for (int i = 0; i < length; i++)
			{
				cout << data[i] << " ";
			}
			cout << "\n";
		}
	}

	~Vector() {
		cout << "D-TOR\n";
		if (data != nullptr) {
			delete[] data;
		}
	}

	
};

int main() {
	SetConsoleOutputCP(1251);
	srand(time(0));

	Vector a;

	for (int i = 0; i < 11; i++) {
		a.AddToFront(i);

	}
	a.Print();

	a.RemoveFromBack();
	a.AddToFront(0);
	a.Print();
	a.RemoveFromFront();
	a.Print();
	a.Insert(111, 5);
	a.Print();
	a.RemoveByIndex(0);
	a.Print();
	a.RemoveByValue(111);
	a.Print();
	a.AddToBack(2);
	a.AddToBack(1);
	a.AddToBack(2);
	a.AddToBack(1);
	a.AddToBack(2);	
	a.Print();
	a.RemoveByValue(1);
	a.Print();

}