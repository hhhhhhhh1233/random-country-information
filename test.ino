#define SCAN_DELAY 300

const int BUTTON = 13;

int buttonState = 0;

byte LEDS[] = { 6, 7, 8, 9, 10 };
const byte LED_COUNT = sizeof(LEDS);

void setup() 
{
	pinMode(BUTTON, INPUT);
	Serial.begin(9600);
}

void flashLightsSequentially()
{
	for (int i = 0; i < LED_COUNT; i++)
	{
		for (int j = 0; j < LED_COUNT; j++)
		{
			if (i != j)
			{
				pinMode(LEDS[i], OUTPUT);
				pinMode(LEDS[j], OUTPUT);
				digitalWrite(LEDS[i], LOW);
				digitalWrite(LEDS[j], HIGH);
				delay(SCAN_DELAY);
				pinMode(LEDS[i], INPUT);
				pinMode(LEDS[j], INPUT);
			}
		}
	}
}

void lightSpecific(int i[2])
{
	for (int pin = 0; pin < LED_COUNT; pin++)
	{
		pinMode(LEDS[pin], INPUT);
	}

	Serial.println(i[0]);
	Serial.println(i[1]);

	pinMode(LEDS[i[0]], OUTPUT);
	pinMode(LEDS[i[1]], OUTPUT);
	digitalWrite(LEDS[i[0]], LOW);
	digitalWrite(LEDS[i[1]], HIGH);
}

struct country {
	String name;
	String facts[2];
	int ledLocation[2];
};

struct country countries[20] = {
					{"Bangladesh",{"Dhaka is the most densely populated city", "Longest female-led government"},{0, 1}},
					{"China",{"Largest population in the world", "The third largest country to the surface"},{0, 2}},
					{"Russia",{"The only country that is washed as twelve seas", "Russia has a national sex day"},{0, 3}},
					{"New Zealand",{"The first country to allow women to vote", "A national anthem is God save the Queen"},{0, 4}},
					{"Madagascar",{"It is the world's fourth largest island", "Was not discovered before 500 years AD"},{1, 0}},
					{"Tanzania",{"The highest mountain in Africa is here", "Tanganyika is the second largest lake on earth"},{1, 2}},
					{"Egypt",{"Made one of the first peace treatments", "Biggest pyramid weighs 5,8 million tons"},{1, 3}},
					{"Colombia",{"Is not recognized as a country to 1912", "The national sport is called Tejo"},{1, 4}},
					{"Chile",{"The world's largest pool is in Chile", "There are penguins in Chile"},{2, 0}},
					{"Canada",{"Produces most of the worlds syrup", "Has the worlds longest highway"},{2, 1}},
					{"Greenland",{"The name Greenland means Land of People", "The Ice’s between 400-800 thousand years"},{2, 3}},
					{"Cuba",{"Cuba is the largest island in Caribbean", "The coast stretches over 3500 miles"},{2, 4}},
					{"Malta",{"The Maltese love their cars", "The name Malta come from Greece"},{3, 0}},
					{"Finland",{"It is the happiest place on earth", "Free schooling"},{3, 1}},
					{"Greece",{"There are over 120 million olive trees", "Are the most sexually active people"},{3, 2}},
					{"Chad",{"A lake has completely disappeared", "A desert is a big part of the country"},{3, 4}},
					{"Singapore",{"It is a city with 64 islands", "The locals speak Singlish"},{4, 0}},
					{"South Korea",{"Plastic surgery is very popular", "Has different types of robots everywhere"},{4, 1}},
					{"North Korea",{"The calendar is based on Kims birthday", "It has only 3 TV channels"},{4, 2}},
					{"Great Britain",{"You cant be more than 115km from sea", "One dish is called Spotted Dick"},{4, 3}}
};


void loop()
{
	buttonState = digitalRead(BUTTON);
	if (buttonState == HIGH)
	{
		//blink through all the light in some predefined order | TODO: Make it blink through in a random order
		flashLightsSequentially();

		//Generate random number for country index && light the country led
		int randomCountryIndex = random(20);
		lightSpecific(countries[randomCountryIndex].ledLocation);

		//Take the same country and print its name and corresponding fact
		Serial.println(countries[randomCountryIndex].name);
		Serial.println(countries[randomCountryIndex].facts[random(5)]);
	}
}