static const uint8_t font[80][5] = {
	{
		0, 0, 0, 0, 0
	},
	{ //0
		0b00000000,
		0b01111110,
		0b10000001,
		0b10000001,
		0b01111110
	},
	{ //1
		0b00000000,
		0b10000010,
		0b11111111,
		0b10000000,
		0b00000000
	},
	{ //2
		0b11000010,
		0b10100001,
		0b10010001,
		0b10001001,
		0b10000110,
	},
	{ //3
		0b01000010,
		0b10001001,
		0b10001001,
		0b10001001,
		0b01110110,
	},
	{ //4
		0b00010000,
		0b00011000,
		0b00010100,
		0b00010010,
		0b11111111
	},
	{ //5
		0b01001111,
		0b10001001,
		0b10001001,
		0b10001001,
		0b01110001,
	},
	{ //6
		0b01111110,
		0b10001001,
		0b10001001,
		0b10001001,
		0b01110000,
	},
	{ //7
		0b00000001,
		0b11000001,
		0b00100001,
		0b00011001,
		0b00000111
	},
	{ //8
		0b01110110,
		0b10001001,
		0b10001001,
		0b10001001,
		0b01110110
	},
	{ //9
		0b01001110,
		0b10010001,
		0b10010001,
		0b10010001,
		0b01111110
	},
	{//:
		0b00000000,
		0b00000000,
		0b00100100,
		0b00000000,
		0b00000000
	},
	{//;
		0b00000000,
		0b00000000,
		0b01100100,
		0b00000000,
		0b00000000
	},
	{//A
		0b11111110,
		0b00010001,
		0b00010001,
		0b00010001,
		0b11111110
	},
	{
		0b11111111,
		0b10001001,
		0b10001001,
		0b10001001,
		0b01110110
	},
	{
		0b01111110,
		0b10000001,
		0b10000001,
		0b10000001,
		0b10000001
	},
	{
		0b11111111,
		0b10000001,
		0b10000001,
		0b10000001,
		0b01111110
	},
	{
		0b11111111,
		0b10001001,
		0b10001001,
		0b10001001,
		0b10001001
	},
	{
		0b11111111,
		0b00010001,
		0b00010001,
		0b00010001,
		0b00000001
	},
	{
		0b01111110,
		0b10000001,
		0b10010001,
		0b10010001,
		0b01100001
	},
	{
		0b11111111,
		0b00010000,
		0b00010000,
		0b00010000,
		0b11111111
	},
	{
		0b10000001,
		0b10000001,
		0b11111111,
		0b10000001,
		0b10000001,
	},
	{
		0b01000000,
		0b10000000,
		0b10000001,
		0b10000001,
		0b01111111
	},
	{
		0b11111111,
		0b00011000,
		0b00100100,
		0b01000010,
		0b10000001
	},
	{
		0b11111111,
		0b10000000,
		0b10000000,
		0b10000000,
		0b10000000
	},
	{
		0b11111111,
		0b00000110,
		0b00011000,
		0b00000110,
		0b11111111
	},
	{
		0b11111111,
		0b00000110,
		0b00011000,
		0b01100000,
		0b11111111
	},
	{
		0b01111110,
		0b10000001,
		0b10000001,
		0b10000001,
		0b01111110
	},
	{
		0b11111111,
		0b00010001,
		0b00010001,
		0b00010001,
		0b00001110
	},
	{
		0b01111110,
		0b10000001,
		0b10100001,
		0b11000001,
		0b11111110
	},
	{
		0b11111111,
		0b00011001,
		0b00101001,
		0b01001001,
		0b10000110
	},
	{
		0b10000110,
		0b10001001,
		0b10001001,
		0b10001001,
		0b01110001
	},
	{
		0b00000001,
		0b00000001,
		0b11111111,
		0b00000001,
		0b00000001
	},
	{
		0b01111111,
		0b10000000,
		0b10000000,
		0b01000000,
		0b11111111
	},
	{
		0b00001111,
		0b00110000,
		0b11000000,
		0b00110000,
		0b00001111
	},
	{
		0b00111111,
		0b11000000,
		0b00111111,
		0b11000000,
		0b00111111
	},
	{
		0b10000001,
		0b01100110,
		0b00011000,
		0b01100110,
		0b10000001
	},
	{
		0b00000011,
		0b00001100,
		0b11110000,
		0b00001100,
		0b00000011
	},
	{
		0b10000011,
		0b10000101,
		0b10011001,
		0b10100001,
		0b11000001
	},
	{
		0b00000000,
		0b00000000,
		0b00100100,
		0b00000000,
		0b00000000
	},
	{
		0b0000000,
		0b0000000,
		0b1100100,
		0b0000000,
		0b0000000
	},

	//lower case
	{
		0b11100000,
		0b10010010,
		0b10010010,
		0b10010010,
		0b01111100
	},
	{
		0b11111111,
		0b10001000,
		0b10001000,
		0b10001000,
		0b01110000
	},
	{
		0b01111100,
		0b10000010,
		0b10000010,
		0b10000010,
		0b10000010
	},
	{
		0b01110000,
		0b10001000,
		0b10001000,
		0b10001000,
		0b11111111
	},
	{//e	
		0b01111000,
		0b10100100,
		0b10100100,
		0b10100100,
		0b00111000
	},
	{//f
		0b00010000,
		0b11111110,
		0b00010001,
		0b00010001,
		0b00000010
	},
	{//g
		0b01001110,
		0b10010001,
		0b10010001,
		0b10010001,
		0b01111111
	},
	{//h
		0b11111111,
		0b00001000,
		0b00001000,
		0b00001000,
		0b11110000
	},
	{//i
		0b00000000,
		0b00000000,
		0b11111010,
		0b00000000,
		0b00000000,
	},
	{//j
		0b01000000,
		0b10000000,
		0b01111010,
		0b00000000,
		0b00000000
	},
	{//k
		0b11111110,
		0b00110000,
		0b01001000,
		0b10000100,
		0b00000000
	},
	{//l
		0b00000000,
		0b00000000,
		0b11111111,
		0b00000000,
		0b00000000
	},
	{//m
		0b11111000,
		0b00001000,
		0b11110000,
		0b00001000,
		0b11110000
	},
	{//n
		0b11111000,
		0b00100000,
		0b00010000,
		0b00010000,
		0b11100000
	},
	{//o
		0b01111000,
		0b10000100,
		0b10000100,
		0b01111000,
		0b00000000
	},
	{//p
		0b00000000,
		0b11111110,
		0b00100100,
		0b00100010,
		0b00011100
	},
	{//q
		0b00011110,
		0b00100001,
		0b00100001,
		0b00100010,
		0b11111111
	},
	{//r
		0b00000000,
		0b00000000,
		0b11111100,
		0b00001000,
		0b00000100
	},
	{//s
		0b10001100,
		0b10010010,
		0b10010010,
		0b01100010,
		0b00000000
	},
	{//t
		0b00000000,
		0b00000100,
		0b01111110,
		0b10000100,
		0b01000000
	},
	{//u
		0b01111100,
		0b10000000,
		0b10000000,
		0b01000000,
		0b11111100
	},
	{//v
		0b00001100,
		0b00110000,
		0b11000000,
		0b00110000,
		0b00001100
	},
	{//w
		0b00111100,
		0b11000000,
		0b00111100,
		0b11000000,
		0b00111100
	},
	{//x
		0b10000100,
		0b01001000,
		0b00110000,
		0b01001000,
		0b10000100
	},
	{//y
		0b00000100,
		0b00011000,
		0b11100000,
		0b00011000,
		0b00000100
	},
	{//z
		0b11000100,
		0b10100100,
		0b10010100,
		0b10001100,
		0b10000100
	},
};

