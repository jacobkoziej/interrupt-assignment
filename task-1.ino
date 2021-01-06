/*
 * Jacob Koziej
 * Interrupt Assignment (Task 1)
 * 2021-01-05
 */


volatile uint8_t state = 0;


void setup()
{
	pinMode(2,  INPUT);
	pinMode(7, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(2), toggle, CHANGE);
}

void loop()
{
}

void toggle()
{
	state = !state;
	digitalWrite(7, state);
}
