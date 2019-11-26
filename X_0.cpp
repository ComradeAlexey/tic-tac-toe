#include <iostream>
#include <clocale>
using namespace std;
//инициализация поля
void InitField(char field[5][5])
{
	//проходимся по полю в двух циклах и заполняем звёздочками(или другим символом, если укажешь другой символ)
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			field[i][j] = '*';
		}
	}
}
//инициализация пользователя
void InitUser(string nameUsers[2],int numUser)
{
	cout << "Введите имя пользователя № " << numUser << ": ";//выводим предложение ввести имя пользователя
	cin >> nameUsers[numUser];//вводим имя пользователя
	system("pause");//ставим на "паузу"
	system("cls");//очищаем консоль
}
//инициализация юзеров
void InitUsers(string nameUsers[2])
{
	InitUser(nameUsers, 0);//инициализируем первого юзера
	InitUser(nameUsers, 1);//второго
}
//показываем поле
void ShowField(char field[5][5])
{
	//выводим поле с помощью двух циклов
	cout << "  X 0 1 2 3 4" << endl;
	for (size_t i = 0; i < 5; i++)
	{
		cout << "Y " << i << " ";
		for (size_t j = 0; j < 5; j++)
		{
			cout << field[i][j] << ' ';
		}
		cout << endl;
	}
}
//ввод координат пользователем
void EnterUser(int numUser,string nameUser, char field[5][5],int* _x, int* _y)
{
	int x, y;//сюда сохраняем координаты
	bool notCorrectEnter = false;//корректный ли был ввод координат? Если корректный, то false, иначе true
	do
	{
		cout << "Ход пользователя № " << numUser << " под именем: " << nameUser << endl;
		cout << "Введите координаты по X: ";
		cin >> x;
		cout << "Введите координаты по Y: ";
		cin >> y;
		if (field[y][x] != '*')
		{
			cout << "Вы ввели неверные координаты, ячейка занята. Повторите попытку"<<endl;
			system("pause");
			system("cls");
			notCorrectEnter = true;
		}
		else
		{
			if (numUser == 0)
			{
				field[y][x] = 'O';
			}
			else
			{
				field[y][x] = 'X';
			}
			//*_x мы разыменовали указатель, т.е. можем работать не с самим указателем, а с памятью, на которую он указывает, т.е. если мы не будем разыменовывать указатель, то мы заменим указатель на какой-то другой указатель и тогда всё будет слишком плохо :)
			(*_x) = x;
			(*_y) = y;
			system("pause");
			system("cls");
			notCorrectEnter = false;
		}
	} while (notCorrectEnter);
	
}
//следующий пользователь, в этой функции мы изменяем индикатор текущего пользователя на следующего, если был 1 игрок, то теперь ходит 2, и наоборот.
void NextUser(int* numUser)
{
	int nU;
	nU = (*numUser);
	if (nU == 0)
	{
		nU = 1;
	}
	else
	{
		nU = 0;
	}
	(*numUser) = nU;
}
//проверяем клетки по горизонтали
int DirectCheckH(char field[5][5], int x, int y, int xD, int yD, int num)
{
	//xD,yD - x(направление)D(delta - изменение). т.е. эти переменные указывают, куда мы идём в поисках клеток игрока.
	//num - номер игрока
	int index = 0;//кол-во наших клеток, которые мы обнаружили, включая стартовую клетку, т.е. клетку, которую поставил пользователь в последнем ходе.
	bool isY, isX;//логические переменные отвечающие за работу условия выхода из цикла.
	if (xD > 0)//если мы по иксу идём вправо, то выполняем 
	{
		isX = (x + xD) < 5;//складываем стартовую точку с дельтой. и после смотрим, меньше ли 5, или равно или больше 5? т.е. мы проверяем, чтобы следующая дельта точка не вышла за пределы массива.
	}
	else//иначе налево
	{
		isX = (x + xD) >= 0;
	}
	//ничего особенного, обычный цикл
	for (size_t j = x; isX; j += xD)
	{
		if (num == 0)
		{
			if (field[y][j] != 'O')
			{
				return index;
			}
			else
			{
				index++;
			}
		}
		else
		{
			if (field[y][j] != 'X')
			{
				return index;
			}
			else
			{
				index++;
			}
		}

		if (xD > 0)
		{
			isX = (j + xD) < 5;
		}
		else
		{
			isX = (j + xD) >= 0;
		}
	}
	return index;
}
//абсолютно аналогичная функция, но только для вертикали
int DirectCheckV(char field[5][5], int x, int y, int xD, int yD, int num)
{
	int index = 0;
	bool isY, isX;
	if (yD > 0)
	{
		isY = (y + yD) < 5;
	}
	else
	{
		isY = (y + yD) >= 0;
	}
	for (size_t i = y; isY; i += yD)
	{
		if (num == 0)
		{
			if (field[i][x] != 'O')
			{
				return index;
			}
			else
			{
				index++;
			}
		}
		else
		{
			if (field[i][x] != 'X')
			{
				return index;
			}
			else
			{
				index++;
			}
		}
		if (yD > 0)
		{
			isY = (i + yD) < 5;
		}
		else
		{
			isY = (i + yD) >= 0;
		}
	}
	return index;
}
//совмещение тех двух функций даёт нам возможность проверять по диагонали.
int DirectCheckDiagonal(char field[5][5],int x, int y, int xD, int yD, int num)
{
	int index = 0;
	bool isY,isX;
	if (yD > 0)
	{
		isY = (y + yD) < 5;
	}
	else
	{
		isY = (y + yD) >= 0;
	}
	if (xD > 0)
	{
		isX = (x + xD) < 5;
	}
	else
	{
		isX = (x + xD) >= 0;
	}
	for (size_t i = y, j = x; (isY & isX); i += yD, j += xD)
	{
		if (num == 0)
		{
			if (field[i][j] != 'O')
			{
				return index;
			}
			else
			{
				index++;
			}
		}
		else
		{
			if (field[i][j] != 'X')
			{
				return index;
			}
			else
			{
				index++;
			}
		}

		if (xD > 0)
		{
			isX = (j + xD) < 5;
		}
		else
		{
			isX = (j + xD) >= 0;
		}

		if (yD > 0)
		{
			isY = (i + yD) < 5;
		}
		else
		{
			isY = (i + yD) >= 0;
		}
	}
	return index;
}
//проверка на победу
bool CheckWin(char field[5][5],int x, int y, int len,int num)
{
	int sum = 0;//кол-во клеток в ряд, текущего игрока

	sum += DirectCheckV(field, x, y, 0, 1, num);//проход от текущей клетки вправо
	sum += DirectCheckV(field, x, y, 0, -1, num);//влево
	sum--;//т.к. текущую клетку мы считаем два раза, а не один, то мы уменьшаем sum на 1
	if (sum >= len) return false;//если кол-во клеток равно или больше длины необходимой для победы, то мы возвращаем false, чтобы прервать цикл

	sum = 0;
	sum += DirectCheckH(field, x, y, 1, 0, num);//вниз
	sum += DirectCheckH(field, x, y, -1, 0, num);//вверх
	sum--;
	if (sum >= len) return false;
	
	sum = 0;
	sum += DirectCheckDiagonal(field, x, y, 1, -1, num);//диагональ из левого нижнего угла, в правый верхний
	sum += DirectCheckDiagonal(field, x, y, -1, 1, num);
	sum--;
	if (sum >= len) return false;

	sum = 0;
	sum += DirectCheckDiagonal(field, x, y, -1, -1, num);//диагональ из левого верхнего угла, в правый нижний
	sum += DirectCheckDiagonal(field, x, y, 1, 1, num);
	sum--;
	if (sum >= len) return false;

	return true;//если нет таковых, то возвращаем true, и продолжаем цикл
}
//ну тут и так понятно
int main()
{
	setlocale(LC_ALL, "Russian");//устанавливаем русский язык в консоли
	char field[5][5];//поле 5 на 5
	string nameUsers[2];//две строки с именами юзеров
	int curUser = 0;//текущий юзер, первым ходит 1 юзер
	int x, y, len = 3;//x & y - выбранная клетка игроком, len - длина выигрошной строки
	bool checkWin;//проверка на победу
	InitField(field);//инициализация поля
	InitUsers(nameUsers);//инициализация юзеров
	do //начало цикла
	{
		ShowField(field);//показываем поле
		EnterUser(curUser, nameUsers[curUser], field,&x,&y);//ввод пользователем координат клетки
		checkWin = CheckWin(field, x, y, len, curUser);//проверка на победу :)
		if(checkWin==true)//если мы не победили, запускаем следующего юзера
			NextUser(&curUser);
	} while (checkWin);//если мы не победили, то начинаем цикл заново.
	ShowField(field);//если победили, выходим из цикла, выводим поле и надпись ниже.
	cout << "Победил игрок №(" << curUser << ") с именем: " << nameUsers[curUser];
	return 0;
}