
double RandDouble(double min, double max)
{
	if (min == max)
	{
		return min;
	}
	const double EPSINON = 0.00000001;

	double d_div = (max-min);
	int i_div = (int)d_div;
	int div_dec = GetDec(d_div);

	double result = 0.0f;
	int rInteger = 0;
	if (i_div > 0)
	{
		rInteger = rand() % i_div;
	}
	double rDec = 0;
	if (div_dec == 0)
	{
		div_dec = 100;
	}
	
	rDec = (double)(rand() % div_dec) / 100.0f;
	result = (double)(rInteger + rDec);
	if (EPSINON >= result && result>-EPSINON)
	{
		result = min;
	}
	return result;
}


void RedPacket(double total, int quantity)
{
	int i = 0;
	double tmp = 0;
	srand((unsigned int)time(NULL));
	double min = 0.01;
	for (i = 0; i < quantity; ++i)
	{
		double packet = RandDouble(min, total);
		if (i == quantity - 1)
		{
			packet = total;
		}
		printf("第%d个: %.2f\n", i + 1, packet);
		tmp += packet;
		total -= packet;
	}
	std::cout << "Total:" << tmp << std::endl;
}
