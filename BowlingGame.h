#pragma once

/*
Przepraszam za oczy, malo tutaj c++'a, 
ale najwazniejsze ze spelnia testy, prawda? :D
*/

class BowlingGame
{
public:
	void roll(int pins) 
	{
		if(throwsCounter < 20)
		{
			if(spare)
			{
				pkt += pins;
				spare = false;
			}
			if(strike2)
			{
				pkt += pins;
				strike2 = false;
			}
			if(strike1)
			{
				pkt += pins;
				strike2 = strike1;
				strike1 = false;
			}

			pkt += pins;

			++throwsCounter;


			if((throwsCounter % 2) == 0)
			{
				if((pins + lastThrowPins) == 10)
					spare = true;
			}
			else
			{
				if(pins == 10)
				{
					strike1 = true;
					++throwsCounter;
				}
			}


			lastThrowPins = pins;
		}
		else
		{
			if(spare)
			{
				pkt += pins;
				spare = false;
				++throwsCounter;
			}
			if(strike2)
			{
				strike2 = false;
				pkt += pins;
				++throwsCounter;
			}
			if(strike1)
			{
				strike1 = false;
				strike2 = true;
				pkt += pins;
				++throwsCounter;
			}
		}
	}

	int getScore()
	{
		return pkt;
	}
private:
	int pkt = 0;
	int lastThrowPins = 0;
	int throwsCounter = 0;
	bool spare = false;
	bool strike1 = false;
	bool strike2 = false;
};

