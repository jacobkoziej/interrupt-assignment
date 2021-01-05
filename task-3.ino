/*
 * Jacob Koziej
 * Interrupt Assignment (Task 3)
 * 2020-01-05
 */


struct {
	// we only ever have 4 states
	volatile unsigned int val : 2;

	uint8_t color[4][2] = {
		// r,   g
		{  0,   0},  // off
		{  0, 255},  // green
		{255, 165},  // orange
		{255,   0}   // red
	};
} state;


void setup()
{
	state.val = 0;

	pinMode(2,  INPUT);
	pinMode(5, OUTPUT);  // green
	pinMode(6, OUTPUT);  // red
	attachInterrupt(digitalPinToInterrupt(2), toggle, RISING);
}

void loop()
{
}

void toggle()
{
	++state.val;
	analogWrite(5, state.color[state.val][1]);
	analogWrite(6, state.color[state.val][0]);
}
