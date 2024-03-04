﻿#include<iostream>
#include<array> // Статический массив
#include<vector> // Дин.массив 
#include<deque> // Спец.контейнер - связный список статических массивов с произвольным доступом. Список помнит адреса каждого куска (стат.массива), \
из которого состоит список в оператиной памяти. Внешняя манера использования не отличается от vector. Особенности:\
1. работа с памятью: в случае необходимости приращения выделяется целый блок (один статич.массив), приращение происходит на размер блока (статич.массива).\
С выделением памяти работает лучше, чем vector \
2. лоялен для удаления и добалением элементов в центр коллекции. За короткий промежуток времени располает новый элемент в любую точку списка. vector хорошо \
работает с размещением элементов в конец коллекции, deque - в любое место коллекции. \
3. deque значительно выйгрывает в скорости работы с данными по сравнению с vector.\
Минус deque в том, что непосредственно доступ к данным в коллекции в произвольном доступе на два порядка дольше, чем у vector.\
В С++ коллекция "по умолчанию" - vector \
deque подключаем только тогда, когда есть ограничения по памяти или в произвольные места коллекции надо часто удалять/добавлять данные

// Коллекции языка с++. Требования к вложенным типам и особенности работы

class DemoGood{ // Класс для демонстрации коллекций (в публичной зоне класса ОБЯЗАТЕЛЬНО должны быть все конструкторы, которыми \
	мы будем пользоваться, иначе стандартные коллекции с++ работать не будут!!!)
public:
	DemoGood() { // Конструктор по умочланию
		std::cout << this << " create by defaul constructor\n";
	}
	DemoGood(int a, bool b) { // Коструктор с параметрами
		std::cout << this << " create by parametric\n";
	}
	DemoGood(const DemoGood& other) { // Конструктор копирования 
		std::cout << this << " create by copy constructor\n";
		std::cout << "from " << &other << " object\n";
	}
	~DemoGood() { // Дэструктор
		std::cout << this << " destroyed\n";
	}
};

class DemoBad { // Класс для плохой демонстрации коллекций (конструктор по умолчанию удалим)
public:
	DemoBad() = delete; // Конструктор по умолчанию отсутствует, мы это даже "прибили гвоздями"
	DemoBad(int a, bool b) { // Коструктор с параметрами
		std::cout << this << " create by parametric\n";
	}
	DemoBad(const DemoGood& other) { // Конструктор копирования 
		std::cout << this << " create by copy constructor\n";
		std::cout << "from " << &other << " object\n";
	}
	~DemoBad() { // Дэструктор
		std::cout << this << " destroyed\n";
	}
};

int main() {
	std::array<DemoGood, 10> arrST; // Создаём объект arrST класса DemoGood, который является статическим массивом размером 10 элементов \
	размер указывать обязательно
	// std::vector<DemoGood> arrDin(10); // Создаём объект arrDin класса DemoGood, который является динамическим массивом из 10 элементов \
	Можно и не говорить, на какой размер создаться, а сказать, какой объём памяти захватить: 	
	std::vector<DemoGood>arrDin; // vector не выделяет памяти, если ему не сказать, но может отдельной командой зарезервировать место, не создавая объекты
	arrDin.reserve(10);
	// deque, как и vector'у можно при создании сказать, на какое кол-во элементов она создана. При этом будет создано необходжимое кол-во болванок\
	с помощью конструктора по умолчанию
	std::deque<DemoGood> arrDeque(10); // Создаём объект arrDeque класса DemoGood, который является спец.контейнером из 10 элементов
	
	// При запуске программы 30 раз отработает конструктор и дэструктор

	std::array<DemoBad, 10> arrST2{ // Поскольку нет конструктора по умолчанию (который нужен для стандартных коллекций!!!), создаём массив с помощью \
		"костылей" (вручную делаем список инициализации через конструктор копирования и конструктор с параметрами, которые есть в DemoBad)
				DemoBad{1, true},
				DemoBad{2, true},
				DemoBad{3, true},
				DemoBad{4, true},
				DemoBad{5, true},
				DemoBad{6, true},
				DemoBad{7, true},
				DemoBad{8, true},
				DemoBad{9, true},
				DemoBad{0, true},
	};
	
	// Далее идут два казалось бы одинаковых метода, но есть разница
	arrDin.push_back(DemoGood(0, true)); // Метод принимает в себя готовый объект, работает за счёт конструктора копирования
	arrDin.emplace_back(); // Метод прнимает набор данных, с помощью которых он может что-то сделать, работает за счёт конструктора с параметрами
	// Если закоментить конструктор с параметрами DemoBad или перенести его в приватную область, то методы категории emplace будут вызывать ошибки сборки \
	// с указанием на невозможность обращения к данному конcтруктору 
	
	// Заполняем vector элементами
	std::cout << "==========================================================\n";
	std::vector<DemoGood> example;
	for (int i = 0; i < 17; ++i) {
		example.emplace_back(i, bool(i % 2));
	}

	return 0;
}