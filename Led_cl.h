class Led_cl
{

public:

	uint32_t Color;
	float LedPos;




	//Lecture attributs
	float r_LedPos() { return LedPos; };

	//Constructeur
	Led_cl() {}
	Led_cl(float a_LedPos) {
		LedPos = a_LedPos;
		Color = 0;
	}

	void SetColor(uint32_t a_Color) { Color = a_Color; };

	void AddColor(uint32_t a_Color) { 
	
	Color =
	  ( (Color & 0x0000FF) + (a_Color & 0x0000FF) )
	| ( ( ((Color & 0x00FF00) >> 8) + ((a_Color & 0x00FF00) >> 8) ) << 8 )
	| ( ( ((Color & 0xFF0000) >> 16) + ((a_Color & 0xFF0000) >> 16)) << 16) ;
	
	
	};


	/*
	void RefreshEffects(unsigned long a_TimeElapsed){
		RefreshFadeEffect(a_TimeElapsed);
	}
	*/





};
