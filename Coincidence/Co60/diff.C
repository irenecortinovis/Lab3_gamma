void diff() {
	std::ifstream infile("Co60_correlation.txt", std::ios::in);
	int a,b;
	infile >> a >> b;
	std::cout << "N(0°) = " << a << std::endl;
	std::cout << "N(90°) = " << b << std::endl;
	std::cout << "( N(90°) - N(0°) ) / N(90°) = " << (float)(a-b)/(float)b << std::endl;
}
