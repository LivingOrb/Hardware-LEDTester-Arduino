#include <Adafruit_NeoPixel.h>

static const uint16_t LedCount = 1;
static const uint8_t LedDataPinNumber = 6;
static const neoPixelType LedType = NEO_KHZ800 | NEO_GRB;

static Adafruit_NeoPixel leds(LedCount, LedDataPinNumber, LedType);

static float wrap(float value, float max)
{
	return value - max * floor(value / max);
}

static void HSV2RGB(float h, float s, float v, uint8_t &r, uint8_t &g, uint8_t &b)
{
	h *= 6.f;
	int sector = (int)h;
	float f = h - sector;
	uint8_t V = (uint8_t)(v * 255.f);
	uint8_t p = (uint8_t)(V * (1.f - s));
	uint8_t q = (uint8_t)(V * (1.f - s * f));
	uint8_t t = (uint8_t)(V * (1.f - s * (1.f - f)));

	switch (sector % 6)
	{
	case 0:
		r = V;
		g = t;
		b = p;
		break;
	case 1:
		r = q;
		g = V;
		b = p;
		break;
	case 2:
		r = p;
		g = V;
		b = t;
		break;
	case 3:
		r = p;
		g = q;
		b = V;
		break;
	case 4:
		r = t;
		g = p;
		b = V;
		break;
	case 5:
		r = V;
		g = p;
		b = q;
		break;
	}
}

void setup()
{
	leds.begin();
	leds.setBrightness(255);
}

static float h = 0.f;
static float s = 1.f;
static float v = 1.f;
static const float hIncrement = 0.0001f;

void loop()
{
	h = wrap(h + hIncrement, 1.f);
	uint8_t r, g, b;
	HSV2RGB(h, s, v, r, g, b);
	leds.setPixelColor(0, r, g, b);
	leds.show();
}
