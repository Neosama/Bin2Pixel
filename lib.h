
std::string hex_string(std::string hexstr)
{
	std::string str = "";
	str.resize((hexstr.size() + 1) / 2);
	for (size_t i = 0, j = 0; i < str.size(); i++, j++)
	{
		char at = '@';
		str[i] = (hexstr[j] & at ? hexstr[j] + 9 : hexstr[j]) << 4, j++;
		str[i] |= (hexstr[j] & at ? hexstr[j] + 9 : hexstr[j]) & 0xF;
	}
	return str;
}

std::string string_hex(std::string str, const bool capital = false)
{
	std::string hexstr = "";
	hexstr.resize(str.size() * 2);
	static const char a = capital ? 0x40 : 0x60;
	for (size_t i = 0; i < str.size(); i++)
	{
		char c = (str[i] >> 4) & 0xF;
		hexstr[i * 2] = c > 9 ? (c - 9) | a : c | '0';
		hexstr[i * 2 + 1] = (str[i] & 0xF) > 9 ? (str[i] - 9) & 0xF | a : str[i] & 0xF | '0';
	}
	return hexstr;
}

int draw_graph(int x, int y, int last_y, COLORREF COLOR)
{
	// X: Axe Horizontal | Y: Axe Vertical

	HWND Hcon = GetConsoleWindow();
	HDC Hdc = GetDC(Hcon);

	int calibration_verticale = 0;

	SetPixel(Hdc,x,y + calibration_verticale,COLOR); // y

	int j = 0;
	for(j=0;j<last_y;j++) // last_y
		SetPixel(Hdc,x,j + calibration_verticale,COLOR);

	ReleaseDC(Hcon, Hdc);

	return 0;
}

int Hex_to_Pixel(std::string data)
{
	int i,j = 0;

	int max_vertical = 32;
	j = 12; // AXE Y CALIBRATION

	COLORREF COLOR;
	HWND Hcon = GetConsoleWindow();
	HDC Hdc = GetDC(Hcon);

	data = string_hex(data, TRUE); // IN CAPITAL
	int size_data = data.size();

	if(size_data > 255)
	{
		std::cout << "\nError MAX SIZE 255 | Current Size: " << size_data << std::endl;
		return 1;
	}

	for(i=0;i<size_data;i++)
	{
		std::string str_one(1,data[i]);

		if(str_one == "0")
		{
			COLOR = RGB(255,0,0); // RED
			SetPixel(Hdc,i,j,COLOR);
		}

		if(str_one == "1")
		{
			COLOR = RGB(255,128,0); // ORANGE
			SetPixel(Hdc,i,j,COLOR);
		}

		if(str_one == "2")
		{
			COLOR = RGB(255,255,0); // YELLOW
			SetPixel(Hdc,i,j,COLOR);
		}

		if(str_one == "3")
		{
			COLOR = RGB(128,255,0); // GREEN
			SetPixel(Hdc,i,j,COLOR);
		}

		if(str_one == "4")
		{
			COLOR = RGB(0,255,0); // GREEN+
			SetPixel(Hdc,i,j,COLOR);
		}

		if(str_one == "5")
		{
			COLOR = RGB(0,255,128); // GREEN-BLUE
			SetPixel(Hdc,i,j,COLOR);
		}

		if(str_one == "6")
		{
			COLOR = RGB(0,255,255); // BLUE--
			SetPixel(Hdc,i,j,COLOR);
		}

		if(str_one == "7")
		{
			COLOR = RGB(0,128,255); // BLUE-
			SetPixel(Hdc,i,j,COLOR);
		}

		if(str_one == "8")
		{
			COLOR = RGB(0,0,255); // BLUE
			SetPixel(Hdc,i,j,COLOR);
		}

		if(str_one == "9")
		{
			COLOR = RGB(127,0,255); // BLUE-PINK
			SetPixel(Hdc,i,j,COLOR);
		}

		if(str_one == "A")
		{
			COLOR = RGB(255,0,255); // PINK-
			SetPixel(Hdc,i,j,COLOR);
		}

		if(str_one == "B")
		{
			COLOR = RGB(255,0,127); // PINK
			SetPixel(Hdc,i,j,COLOR);
		}

		if(str_one == "C")
		{
			COLOR = RGB(128,128,128); // BLACK/WHITHE
			SetPixel(Hdc,i,j,COLOR);
		}

		if(str_one == "D")
		{
			COLOR = RGB(255,215,0); // GOLD
			SetPixel(Hdc,i,j,COLOR);
		}

		if(str_one == "E")
		{
			COLOR = RGB(255,248,220); // cornsilk
			SetPixel(Hdc,i,j,COLOR);
		}

		if(str_one == "F")
		{
			COLOR = RGB(102,255,0); // GREEN-EXOTIC
			SetPixel(Hdc,i,j,COLOR);
		}

		draw_graph(i, j, 32, COLOR);
	}

	std::cout << "\n\n\n\nInput is \"" << hex_string(data) << "\"" << std::endl;
	ReleaseDC(Hcon, Hdc);
	return 0;
}