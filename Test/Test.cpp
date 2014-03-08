#include "stdafx.h"
#include <iostream>
#include <time.h> 
#include <math.h> 
#include <vector>

void NumberAsBinary(
    char *       _result, // строка с результатом
    unsigned int _number  // произвольное число
  );

void GenerateRandomArray(
    int *        _result,  // возвращаемый массив
    unsigned int _maxValue // максимальное число в последовательности
  );

void Sort(
    int *        _values, // сортируемый массив
    unsigned int _count   // количество элементов в массиве
  );

int GetMissingValue(
    const int *  _values, // неупорядоченный массив целых чисел от 1 до _count
    unsigned int _count   // количество элементов в массиве
  );


int _tmain(int argc, _TCHAR* argv[])
{
  srand (time(NULL));

  //Тест первого задания
  printf("NumberAsBinary Test \n");
  for(int i=0;i<11;i++)
  {
    std::cout<<"////////////////////////////////////////////////"<<std::endl;
    char string[10] = {""};
    unsigned int number = rand()%512;

    printf("In Dec: ");
    std::cout<<(int)number<<std::endl;

    printf("In Bin: ");
    NumberAsBinary(string,number);
    printf(string);
    std::cout<<std::endl;
  }
  std::cout<<"Press key"<<std::endl;
  getchar();

  //Тест второго задания и третьего задания и четвертого тоже	
  printf("GenerateRandomArray,Sort Test and GetMissingValue Test \n");	
  for(int i=0;i<4;i++)
  {
    int maximumValue=rand()%15+5;//значение максимального элемента
    int* integerArray=new int [maximumValue];//массив для хранения результатов GenerateRandomArray()

    GenerateRandomArray(integerArray,maximumValue);////////////////////////////////////////

    std::cout<<"////////////////////////////////////////////////"<<std::endl;
    printf ("Random Array \n ");
    std::cout<<"With "<<maximumValue<<" digits"<<std::endl;
    std::cout<<'{';
    for(int i=0;i<maximumValue;i++)
    {
      std::cout<<integerArray[i]<<',';
    }
    std::cout<<'}'<<std::endl;

    std::cout<<"/////////"<<std::endl;
    printf ("MissingValue \n ");

    std::cout<<GetMissingValue(integerArray,maximumValue)<<std::endl;////////////////////////////////

    std::cout<<"/////////"<<std::endl;
    printf ("Sort Array \n ");
    int* integerSortArray=new int [maximumValue];//массив для хранения результатов Sort()
    memcpy(integerSortArray, integerArray, sizeof(int) * maximumValue);

    Sort(integerSortArray,maximumValue);//////////////////////////////////////

    std::cout<<'{';
    for(int i=0;i<maximumValue;i++)
    {
      std::cout<<integerSortArray[i]<<',';
    }
    std::cout<<'}'<<std::endl;

    delete [] integerSortArray;
    delete [] integerArray;
  }
  std::cout<<"Press key to exit"<<std::endl;		
  getchar();
return 0;
}

void NumberAsBinary(
	char *       _result, // строка с результатом
	unsigned int _number  // произвольное число
	)
{
	static bool flag = true;//флаг, обозначающий начало преобразования нового числа 
	static int i;//счетчик значащих символов

	if (flag)//если новое число, обнуляем счетчик значащих символов
	{
		i=0;
		flag = false;
	}

	if(_number>1)
	{
		NumberAsBinary(_result,_number/2);
	}

	flag=true;
	_result[i]=_number%2 + '0';
	i++;
}

void GenerateRandomArray(
	int *        _result,  // возвращаемый массив
	unsigned int _maxValue // максимальное число в последовательности
	)
{
	std::vector<int> val (_maxValue); 

	for (unsigned i=0; i<_maxValue; i++)
		val.at(i)=i+1;

	while(val.size()>0)//выдергиваем из вектора числа по рандомному индексу пока они не закончатся
	{
		int i = rand() % val.size();
		*(_result++)=val.at(i);
		val.erase(val.begin()+i);
	}
}

//алгоритм сортировки - "Быстрая сортировк"
void Sort(
	int *        _values, // сортируемый массив
	unsigned int _count   // количество элементов в массиве
	)
{
	int i = 0, j = _count-1;
	int p = _values[_count>>1];//опорный элемент посередине массива

	do {
		while ( _values[i] < p ) 
			i++;
		while ( _values[j] > p )
			j--;

		if (i <= j) 
		{
			if(i!=j)//если элементы разлицны меняем местами их значения
			{ 
				_values[i]-=_values[j]; 
				_values[j]=_values[i]+2*_values[j];	
				_values[i]=(_values[j]-_values[i])/2;	
				_values[j]-=_values[i];
			}
			i++; j--;
		}
	} while ( i<=j );

	// рекурсивные вызовы, если есть, что сортировать 
	if ( j > 0 ) Sort(_values, j+1);
	if ( _count > i ) Sort(_values+i, _count-i);
}


int GetMissingValue(
	const int *  _values, // неупорядоченный массив целых чисел от 1 до _count
	unsigned int _count   // количество элементов в массиве
	)
{
	int sum=0;
	for(unsigned int i=0;i<_count-1;i++)
	{
		sum+=_values[i];
	}

	return (1+_count)*_count/2 -sum;//сумма арифметической прогресии минус все элементы массива кроме последнего
}


