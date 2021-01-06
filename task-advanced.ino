/*
 * Jacob Koziej
 * Interrupt Assignment (Advanced Task)
 * 2020-01-06
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
} state_rgb;


void setup()
{
	state_rgb.val = 0;

	pinMode(2, INPUT);
	pinMode(3, INPUT);
	pinMode(4, INPUT);

	pinMode(7,  OUTPUT);  // red
	pinMode(8,  OUTPUT);  // two white
	pinMode(10, OUTPUT);  // rgb green
	pinMode(11, OUTPUT);  // rgb red

	attachInterrupt(digitalPinToInterrupt(2), toggle_white, RISING);
	attachInterrupt(digitalPinToInterrupt(3), toggle_red,   CHANGE);
	PCICR  |= _BV(PCIE2);    // enable pin change interrupt 2
	PCMSK2 |= _BV(PCINT20);  // pin change interrupt on pin 4
}

void loop()
{
}

void toggle_white()
{
	static uint8_t state = 0;
	state= !state;

	digitalWrite(8, state);
}

void toggle_red()
{
	static uint8_t state = 0;
	state= !state;

	digitalWrite(7, state);
}

ISR(PCINT2_vect)
{
	static uint8_t change = 0;
	change = !change;

	if (change) ++state_rgb.val;

	analogWrite(10, state_rgb.color[state_rgb.val][1]);
	analogWrite(11, state_rgb.color[state_rgb.val][0]);
}
