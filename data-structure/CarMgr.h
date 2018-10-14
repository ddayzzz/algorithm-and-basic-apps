#pragma once
#include "stdafx.h"
#include <string>
#include "StackList.hpp"
#include <iostream>
#include <fstream>
class Car
{
public:
	Car():number(std::string()),movetimes(0){}
	Car(std::string s):number(s),movetimes(0){}
	virtual ~Car(){}
	void Move() { ++movetimes; }
	std::string getNumber()
	{
		return number;
	}
private:
	std::string number;
	int movetimes;
};
class CarManage
{
public:
	bool isEmpty() { return cars_curr.isEmpty(); }
	void getOut(std::string num)
	{
		if (currcars > 0)
		{
			Car ca = cars_curr.TopAndPop();

		}
		else
		{
			std::cout << "No carr!" << std::endl;
		}
	}
	void showMovetimes(){
		
	}
	void addCar(Car &ca){}
	CarManage(int m, std::ifstream &of) :max(m), currcars(0) {
		while (of.eof() ==false)
		{
			std::string num, action;
			of >> num >> action;
			if (action == "ARRIVE")
			{
				if (currcars == max)
				{
					std::cout << "No place for new car!\n";
				}
				else
				{

					Car ca(num);
					cars_curr.Push(ca);
					++currcars;
					std::cout << "Car :" << num << " arrives\n";
				}
			}
			else if (action == "DEPART")
			{
				while (!cars_curr.isEmpty() && num != cars_curr.Top().getNumber())
				{
					cars_remove.Push(cars_curr.TopAndPop());
					cars_remove.Top().Move();
					--currcars;
				}
				if (cars_curr.isEmpty())
				{
					//fail to find
				}
				else
				{
					cars_curr.Pop();
					--currcars;
					std::cout << "Car :" << num << " departs\n";
				}
				while (!cars_remove.isEmpty() && cars_remove.Top().getNumber() !=num)
				{
					cars_curr.Push(cars_remove.TopAndPop());
					cars_curr.Top().Move();
					++currcars;
				}

			}
		}
	}
private:
	StackList<Car> cars_curr;
	StackList<Car> cars_remove;
	int max;
	int currcars;
};