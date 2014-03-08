#include "stdafx.h"
#include <iostream>
#include <time.h> 
#include <math.h> 
#include <vector>

void NumberAsBinary(
    char *       _result, // ������ � �����������
    unsigned int _number  // ������������ �����
  );

void GenerateRandomArray(
    int *        _result,  // ������������ ������
    unsigned int _maxValue // ������������ ����� � ������������������
  );

void Sort(
    int *        _values, // ����������� ������
    unsigned int _count   // ���������� ��������� � �������
  );

int GetMissingValue(
    const int *  _values, // ��������������� ������ ����� ����� �� 1 �� _count
    unsigned int _count   // ���������� ��������� � �������
  );


int _tmain(int argc, _TCHAR* argv[])
{
  srand (time(NULL));

  //���� ������� �������
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

  //���� ������� ������� � �������� ������� � ���������� ����	
  printf("GenerateRandomArray,Sort Test and GetMissingValue Test \n");	
  for(int i=0;i<4;i++)
  {
    int maximumValue=rand()%15+5;//�������� ������������� ��������
    int* integerArray=new int [maximumValue];//������ ��� �������� ����������� GenerateRandomArray()

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
    int* integerSortArray=new int [maximumValue];//������ ��� �������� ����������� Sort()
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
    char *       _result, // ������ � �����������
    unsigned int _number  // ������������ �����
  )
{
static bool flag = true;//����, ������������ ������ �������������� ������ ����� 
  static int i;//������� �������� ��������

  if (flag)//���� ����� �����, �������� ������� �������� ��������
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
    int *        _result,  // ������������ ������
    unsigned int _maxValue // ������������ ����� � ������������������
  )
{
  std::vector<int> val (_maxValue); 

  for (unsigned i=0; i<_maxValue; i++)
    val.at(i)=i+1;

  while(val.size()>0)//����������� �� ������� ����� �� ���������� ������� ���� ��� �� ����������
  {
    int i = rand() % val.size();
    *(_result++)=val.at(i);
    val.erase(val.begin()+i);
  }
}

//�������� ���������� - "������� ���������"
void Sort(
    int *        _values, // ����������� ������
    unsigned int _count   // ���������� ��������� � �������
  )
{
  int i = 0, j = _count-1;
  int p = _values[_count>>1];//������� ������� ���������� �������

  do {
  while ( _values[i] < p ) 
    i++;
  while ( _values[j] > p )
    j--;

  if (i <= j) 
    {
      if(i!=j)//���� �������� �������� ������ ������� �� ��������
        { 
          _values[i]-=_values[j]; 
          _values[j]=_values[i]+2*_values[j];	
          _values[i]=(_values[j]-_values[i])/2;	
          _values[j]-=_values[i];
        }
        i++; j--;
    }
  } while ( i<=j );

  // ����������� ������, ���� ����, ��� ����������� 
  if ( j > 0 ) Sort(_values, j+1);
  if ( _count > i ) Sort(_values+i, _count-i);
}


int GetMissingValue(
    const int *  _values, // ��������������� ������ ����� ����� �� 1 �� _count
    unsigned int _count   // ���������� ��������� � �������
	)
{
  int sum=0;
  for(unsigned int i=0;i<_count-1;i++)
  {
    sum+=_values[i];
  }

  return (1+_count)*_count/2 -sum;//����� �������������� ��������� ����� ��� �������� ������� ����� ����������
}


