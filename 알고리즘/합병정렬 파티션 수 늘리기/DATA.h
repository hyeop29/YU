#ifndef DATA_H

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<string.h>
#define SIZE 200000000  //256395 테스트 환경에서 정의 가능한 가장 큰 배열 크기

void Fill(int Array[]);
void Scramble(int Array[]);
void Validate(int Array[], int val);

#endif