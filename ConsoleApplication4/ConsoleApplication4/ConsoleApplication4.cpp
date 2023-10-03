#include <iostream> // подключение стандартных библиотек: iostream отвечает за потоки ввода и вывода данных (cin cout)
#include <windows.h> // рисование графики, установка координат (COORD), окрашивание (SetConsoleTextAttribute) и многое другое
#include <ctime> // time - получение количества секунд прошедших с 1.01.1970 - нужно для генерации случайных чисел
#include <conio.h> // getch - нажатие на клавиши вроде Y или N, получение аски-кода клавиши
using namespace std; // раскрытие пространства имён, в котором объявлены cin и cout

// глобальная переменная - будет использоваться во многих функциях
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // дескриптор (уникльный номер окна) - нужен для окрашивания и установки координат 

// прототипы функций:
void options(); // настройка размеров и расположения окна, установка заголовка, скрытие мигающего курсора
void window_work();
void cursor_hider();
void intro(); // заставка
void menu(); // три пункта меню
void letter(int x, int y, int forecolor, int backcolor, char symb); // рисование квадрата с буквой для заставки
void text_effect(int x, int y, int forecolor, int backcolor, const char* symb, int len, int pause); // показ "ленты" текста
void exit(); // быстрый выход из приложения
void the_end(); // концовка с пожеланием удачи
void stand(int x, int y, int k, const char* str); // вспомогательная функция по установке курсора в нужную позцию + окрашивание
void help(); // открытие файла справки
void epic_win(); // поздравляшки, если удалось набрать 100 очков (это реально!)
void game(); // основной игровой процесс

// точка входа в приложение
void main()
{
	options();
	intro();
	menu();
}

void letter(int x, int y, int forecolor, int backcolor, char symb) // функция вывода квадратика с буквой (стилизация под клавиатуру)
{
	int sizeX = 9; // размер квадрата по ширине
	int sizeY = 7; // по высоте
	// отрисовка квадрата двойным циклом
	for (int j = 0; j < sizeY; j++)
	{
		for (int i = 0; i < sizeX; i++)
		{
			COORD temp = { x + i, y + j }; // назначение координат
			SetConsoleCursorPosition(h, temp); // установка координат
			SetConsoleTextAttribute(h, backcolor * 16 + forecolor); // окрашивание
			cout << " "; // рисуем пробелы определённого цвета, из которых состоят квадраты
		}
	}

	// пишем букву в центре квадрата
	COORD temp = { x + sizeX / 2, y + sizeY / 2 };
	SetConsoleCursorPosition(h, temp);
	cout << symb;
}

void window_work()
{
	system("title Клавиатурный тренажёр");
	system("mode con cols=130 lines=50");
}
void cursor_hider()
{
	CONSOLE_CURSOR_INFO ci;
	ci.bVisible = false;
	ci.dwSize = 100;
	SetConsoleCursorInfo(h, &ci);
}
void options()
{
	MoveWindow(GetConsoleWindow(), 50, 50, 2000, 2000, true);
}

// побуквенный показ переданного текста:
// x y - начальные координаты показа, фор и бэк калар - цвет текста и фона, текст - указатель на строку текста, лен - длина этого текста, пауз - время в мс перед показом следующей буквы текста
void text_effect(int x, int y, int forecolor, int backcolor, const char* text, int len, int pause)
{
	for (int i = 0; i < len; i++)
	{
		COORD temp = { x + i, y }; // будем ставить курсор в определённые координаты
		SetConsoleCursorPosition(h, temp); // ставим
		SetConsoleTextAttribute(h, backcolor * 16 + forecolor); // применяем цвет
		cout << text[i]; // рисуем букву
		Sleep(pause); // ждём
	}
}

void exit()
{ // делаем цвет текста чёрным - чтобы пользователь не увидел никаких надписей
	SetConsoleTextAttribute(h, 0);
	system("taskkill -im cmd.exe"); // закрываем все процессы по имени cmd - это все консольные окна
}

void the_end()
{
	text_effect(5, 2, 12, 0, "Спасибо за игру!", 16, 15); // красным цветом благодарим за игру
	text_effect(5, 4, 7, 0, "Для выхода нажмите Enter", 24, 15); // белым цветом выводим просьбу нажать на энтер

	while (_getch() != 13); // до тех пор, пока пользователь не нажмёт на энтер - у него код 13
	exit(); // выходим
}

void intro()
{
	setlocale(0, "RUS"); // включаем русскую кодировку
	srand(time(0)); // запускаем генератор случайных чисел
	char message[] = "КЛАВИАТУРНЫЙ";
	for (int i = 0; i < ARRAYSIZE(message) - 1; i++) {
		int fore = 0;
		int back = rand() % 8 + 1;
		letter(5 + i * 10, 4, fore, back, message[i]);
		Sleep(100); // распечатываем первую строку: каждая буква будет в своём квадрате
	}
	char message2[] = "ТРЕНАЖЁР";
	for (int i = 0; i < ARRAYSIZE(message2) - 1; i++)
	{
		int fore = 0;
		int back = rand() % 8 + 1;
		letter(9 + i * 10, 12, fore, back, message2[i]);
		Sleep(100);
	}
	text_effect(56, 22, 15, 0, "Для начала тренировки нажмите 'Y'", 33, 30);
	text_effect(5, 46, 7, 0, "Для выхода из программы нажмите 'N'", 36, 15);

	while (true)
	{
		int n = _getch(); // анализируем код клавиши
		if (n == 'N' || n == 'n') exit(); // выходим
		if (n == 'Y' || n == 'y') break; // продолжаем игровой процесс - возвращаемся в мейн
	}
}

void Stand(int x, int y, int k, const char* str)
{
	COORD c{ x, y };
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, k);
	cout << str << "\n";
}

void help()
{
	setlocale(0, "RUS");

	SetConsoleTextAttribute(h, 9);
	system("type spravka.txt"); // стандартная команда виндовс по распечатке файла (файл лежит в папке с проектом!)

	while (true)
	{
		int n = _getch();
		if (n == 27 || n == 'n') menu();
	}
}

void epic_win()
{
	text_effect(5, 2, 12, 0, "Вы победили!", 16, 15);
	text_effect(5, 4, 7, 0, "Для выхода нажмите Enter", 24, 15);

	while (_getch() != 13);
	exit();
}

void game()
{
	int score = 10; // счёт игры в начале
	char* title = new char[30]; // строка для вывода текста в заголовок
	sprintf_s(title, 29, "title Текущий счёт: %d", score); // формируем строку для вывода текста в заголовок: скор подставляется на место %д
	system(title); // кидаем текст в заголовок

	char current_symb = rand() % 26 + 65; // случайно загадываем английскую букву от А до Z (у них коды от 65 до 65+26)
	int symb_height = 1; // начальная позиция буквы (первая строка)
	int x_pos = rand() % 129; // позиция по иксу - случайная 
	int color = rand() % 15 + 1; // цвет буквы - случайный от 1 до 15 (основные цвета консоли)
	int speed = 150; // начальная пауза при смещении буквы (будет уменьшаться!)
	while (true)
	{ // пока не проиграем
		if (_kbhit()) // если было нажатие на клавиши пользователем
		{
			int n = _getch(); // получаем код нажатой клавиши
			if (n == current_symb + 32)
			{ // если мы нажали именно на ту клавишу, аски-код которой соответствует падающей букве
				score++; // +1 к очкам
				if (score >= 100) epic_win(); // если набрали 100 очок - победа
				sprintf_s(title, 29, "title Текущий счёт: %d", score); // показываем сообщение об этом в заголовок
				system(title);
				COORD c = { x_pos, symb_height - 1 };
				SetConsoleCursorPosition(h, c);
				cout << " "; // стирка "угаданной" буквы, и генерация новой буквы
				current_symb = rand() % 26 + 65;
				symb_height = 1;
				x_pos = rand() % 129;
				color = rand() % 15 + 1;
				speed--; // скорость увеличивается! играть будет сложнее!
				if (speed < 15) speed = 15; // если допустить отрицательные числа для скорости - игра зависнет :)
			}

			else if (n == 27) // при нажатии на Эскейп - выходим в меню
			{
				menu();
				break;
			}
		}
		else
		{ // если нажатия не было - то буква просто падает
			COORD c = { x_pos, symb_height - 1 };
			SetConsoleCursorPosition(h, c);
			SetConsoleTextAttribute(h, color);
			cout << " "; // стираем букву, чтобы потом показать её на строчку ниже
			c.X = x_pos;
			c.Y = symb_height;
			SetConsoleCursorPosition(h, c);
			cout << current_symb;
			symb_height++;

			if (symb_height > 49)
			{ // если буква опустилась слишком низко...
				score--; // - одно очко
				if (score < 2) the_end(); // если меньше двух очок - печаль!
				sprintf_s(title, 29, "title Текущий счёт: %d", score);
				system(title);
				current_symb = rand() % 26 + 65;
				symb_height = 1;
				x_pos = rand() % 129;
				color = rand() % 15 + 1;
			}
			Sleep(speed);
		}
	}
}

void menu()
{
	system("title Клавиатурный тренажёр");
	int start_y = 3;
	system("cls"); // очистка экрана
	setlocale(0, "RUS");
	Stand(5, start_y, 10, "Справка");
	Stand(5, start_y + 2, 2, "Игра");
	Stand(5, start_y + 4, 2, "Выход");

	int k;	// код клавиши
	int cur = 1;	// какой пункт выбран сейчас
	while (true)
	{
		k = _getch();
		if (k == 80) // если нажата курсорная клавиша вниз
		{
			if (cur < 3)
			{
				cur++;
				if (cur == 2)
				{
					Stand(5, start_y, 2, "Справка"); // 2 - это тёмно-зелёный цвет
					Stand(5, start_y + 2, 10, "Игра"); // 10 - ярко-зелёный
				}
				else if (cur == 3) {
					Stand(5, start_y + 2, 2, "Игра");
					Stand(5, start_y + 4, 10, "Выход");
				}
			}
		}
		else if (k == 72) // если нажали вверх
		{
			if (cur > 1)
			{
				cur--;
				if (cur == 2)
				{
					Stand(5, start_y + 2, 10, "Игра");
					Stand(5, start_y + 4, 2, "Выход");
				}
				else if (cur == 1)
				{
					Stand(5, start_y, 10, "Справка");
					Stand(5, start_y + 2, 2, "Игра");
				}
			}
		}
		else if (k == 13) // если нажали на энтер - выбираем пункт меню!
		{
			system("cls");
			SetConsoleTextAttribute(h, 12);
			if (cur == 1)
				help();
			else if (cur == 2)
				game();
			else if (cur == 3)
				the_end();
			_getch();
			exit(0);
		}
	}
}

