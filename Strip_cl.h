class Strip_cl
{
private:



public:

	int StripNbr;
	int StripBus, StripBusSeg;
	int StripNbrAv[2], StripNbrAr[2]; //0=droite, 1=gauche
	int LedCount=24;
	bool RevertRenderingOrder;
	Led_cl Led[25] = {
	Led_cl(0),
	Led_cl(0.5),Led_cl(1.5),Led_cl(2.5),Led_cl(3.5),Led_cl(4.5),
	Led_cl(5.5),Led_cl(6.5),Led_cl(7.5),Led_cl(8.5),Led_cl(9.5),
	Led_cl(10.5),Led_cl(11.5),Led_cl(12.5),Led_cl(13.5),Led_cl(14.5),
	Led_cl(15.5),Led_cl(16.5),Led_cl(17.5),Led_cl(18.5),Led_cl(19.5),
	Led_cl(20.5),Led_cl(21.5),Led_cl(22.5),Led_cl(23.5)
	};


	//Constructeur
	Strip_cl() {};

	Strip_cl(int a_StripNbr, int a_StripBus, int a_StripBusSeg, bool a_RevertRendering,
		int a_StripNbrAr0, int a_StripNbrAr1, int a_StripNbrAv0, int a_StripNbrAv1)
	{
		StripNbr = a_StripNbr; StripBus = a_StripBus; StripBusSeg = a_StripBusSeg;
		RevertRenderingOrder = a_RevertRendering;
		StripNbrAv[0] = a_StripNbrAv0; StripNbrAr[0] = a_StripNbrAr0;
		StripNbrAv[1] = a_StripNbrAv1; StripNbrAr[1] = a_StripNbrAr1;
	}

	void SetLedsColor(uint32_t a_Color)
	{for (int i = 1; i <= LedCount; i++) {Led[i].SetColor(a_Color);} };
	
	void SetLedColor(int a_LedNbr, uint32_t a_Color)
	{ Led[a_LedNbr].SetColor(a_Color);};

};

