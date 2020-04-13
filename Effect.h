

class FadeEffect_cl
{
private:

	float CurrVal; // valeur actuelle
	int32_t TargetColor; // valeur cible
	int32_t int8CurrVal;
	int StripNbr, LedNbr; //identifiant strip/led
	int Mode; //0: setcolor / 1: addcolor
	int AttackTime = 1; // en ms
	int MaintainTime; //en ms
	int ReleaseTime = 1; // en ms
	int Step; //0: inactif 1:attack 2: maintain 3:release
	int StepTime; // en ms

public:

	//Constructeurs
	FadeEffect_cl() {}
	FadeEffect_cl(int a_StripNbr, int a_LedNbr, int32_t a_TargetColor, int a_AttackTime, int a_MaintainTime, int a_ReleaseTime,int a_Mode) {
		Mode = a_Mode;
		StripNbr = a_StripNbr;
		LedNbr = a_LedNbr;
		TargetColor = a_TargetColor;
		AttackTime = a_AttackTime * 1000;
		MaintainTime = a_MaintainTime * 1000;
		ReleaseTime = a_ReleaseTime * 1000;
		Step = 1;
		StepTime = 1;
	}

	void test1() {};

	bool RunEffect(Strip_cl* s, unsigned long a_TimeElapsed) {
		//Serial.print(" step: "); Serial.println(Step);
		switch (Step) {
		case 1: //attack
			s[StripNbr].Led[LedNbr].AddColor(GetPercRGB(TargetColor, (uint32_t)((float)StepTime / (float)AttackTime * 100)));
			StepTime = StepTime + a_TimeElapsed;
			if (StepTime > AttackTime) {
				StepTime = 0; Step = 2;
			}
			break;
		case 2: //maintain
			s[StripNbr].Led[LedNbr].AddColor(TargetColor);
			StepTime = StepTime + a_TimeElapsed;
			if (StepTime > MaintainTime) {
				StepTime = ReleaseTime; Step = 3;
			}
			break;
		case 3: //release
			s[StripNbr].Led[LedNbr].AddColor(GetPercRGB(TargetColor, (uint32_t)((float)StepTime / (float)ReleaseTime * 100)));
			StepTime = StepTime - a_TimeElapsed;
			if (StepTime < 0) {
				StepTime = 0; Step = 0;
				return true;
			}
			break;
		default:
			break;
		}
		return false;
	}
};


class Cursor_cl
{

private:

	struct Point_Str {
		float Pos;
		float OldPos;
		int StripNbr;
		int Dir; //-1: arriere, 1: avant
		uint32_t Color;
	};

	// variable de travail

	unsigned long MemTime;
	unsigned long ElapsedTime;
	float PosDiff;
	bool Switch_OldAv, Switch_OldAr, Switch_NewAv, Switch_NewAr;
	int Switch_OldStripNbr, Switch_NewStripNbr, RandInt;

public:

	Point_Str FrPoint;
	Point_Str RePoint;
	int Speed; // led/s
	bool Halt;


	//Constructeurs
	Cursor_cl() {}
	Cursor_cl(int a_StripTarget, float a_FrPointPos, float a_RePointPos, int a_Speed, uint32_t a_Color)
	{
		FrPoint.Pos = a_FrPointPos;
		FrPoint.StripNbr = a_StripTarget;
		FrPoint.Dir = 1;
		FrPoint.Color = a_Color;
		RePoint.Pos = a_RePointPos;
		RePoint.StripNbr = a_StripTarget;
		RePoint.Dir = 1;

		Speed = a_Speed;
		Halt = false;
		MemTime = micros();
	}

	void Refresh(Strip_cl* s)
	{
		//temps écoulé
		ElapsedTime = micros() - MemTime;
		MemTime = micros();
		//Calcul avance parcouru
		PosDiff = (float)Speed * (float)ElapsedTime / 1000000;
		//Calcul nouvelles position
		FrPoint.OldPos = FrPoint.Pos;
		FrPoint.Pos = FrPoint.Pos + FrPoint.Dir * PosDiff;
		RePoint.OldPos = RePoint.Pos;
		RePoint.Pos = RePoint.Pos + RePoint.Dir * PosDiff;

		//********* changement Strip 
		Switch_OldAv = false; Switch_OldAr = false; Switch_NewAv = false; Switch_NewAr = false;
		RandInt = random(0, 2);

		//On test le changement de strip
		if (FrPoint.Pos > s[FrPoint.StripNbr].LedCount) {
			Switch_OldAv = true;
			Switch_OldStripNbr = FrPoint.StripNbr;
			Switch_NewStripNbr = s[Switch_OldStripNbr].StripNbrAv[RandInt];

		};
		if (FrPoint.Pos < 0) {
			Switch_OldAr = true;
			Switch_OldStripNbr = FrPoint.StripNbr;
			Switch_NewStripNbr = s[Switch_OldStripNbr].StripNbrAr[RandInt];
		};
		// Si un changement de strip à faire
		if (Switch_OldAv || Switch_OldAr) {
			//On regarde si le nouveau strip commence à l'avant ou l'arrière
			if ((Switch_OldStripNbr == s[Switch_NewStripNbr].StripNbrAr[0])
				|| (Switch_OldStripNbr == s[Switch_NewStripNbr].StripNbrAr[1])) {
				Switch_NewAr = true;
			}
			else {
				Switch_NewAv = true;
			}


			//Serial.print(" old strip: "); Serial.print(Switch_OldStripNbr);
			//Serial.print(" new strip: "); Serial.print(Switch_NewStripNbr);
			//Serial.print(" choix: "); Serial.print(s[Switch_NewStripNbr].StripNbrAr[0]);
			//Serial.print(" / "); Serial.println(s[Switch_NewStripNbr].StripNbrAr[1]);
			//delay(2000);


			//Affectation nouveau StripNbr
			FrPoint.StripNbr = Switch_NewStripNbr;

			//Affectation position et direction en fonction des combinaison av/av av/ar ar/av ar/ar
			if (Switch_OldAv && Switch_NewAv) {
				FrPoint.Pos = s[Switch_NewStripNbr].LedCount - (FrPoint.Pos - s[Switch_OldStripNbr].LedCount);
				FrPoint.Dir = -1;
			}
			if (Switch_OldAv && Switch_NewAr) {
				FrPoint.Pos = -s[Switch_OldStripNbr].LedCount + FrPoint.Pos;
				FrPoint.Dir = 1;
			}
			if (Switch_OldAr && Switch_NewAv) {
				FrPoint.Pos = s[Switch_NewStripNbr].LedCount + FrPoint.Pos;
				FrPoint.Dir = -1;
			}
			if (Switch_OldAr && Switch_NewAr) {
				FrPoint.Pos = -FrPoint.Pos;
				FrPoint.Dir = 1;
			}
		}


		/*
		Serial.print("Strip: "); Serial.print(FrPoint.StripNbr);
		Serial.print(" Pos: "); Serial.print(FrPoint.Pos);
		Serial.print(" Dir: "); Serial.print(FrPoint.Dir);
		Serial.print(" Rand: "); Serial.println(RandInt);
		*/
	}

	void AddEffect(Strip_cl* s, vector<FadeEffect_cl*>* v, int a_EffcetType)
	{
		switch (a_EffcetType)
		{
			/*
			case 1: //
				for (int i = 1; i <= 30; i++) {
					if (c->FrPoint.StripNbr == i)
					{
						for (int i2 = 1; i2 <= 24; i2++) {
							if (abs(s[i].Led[i2].LedPos - c->FrPoint.Pos) < 6)
							{
								s[i].SetLedColor(i2, c->FrPoint.Color);
							}
						}
					}

				}
				break;
			*/
			case 2: //fade effcet
				for (int i = 1; i <= 30; i++) {
					if (FrPoint.StripNbr == i)
					{
						for (int i2 = 1; i2 <= 24; i2++) {
							if (abs(s[i].Led[i2].LedPos - FrPoint.Pos) < 0.25)
							{
								FadeEffect_cl* p = new FadeEffect_cl(i, i2, FrPoint.Color, 2000, 0, 2000, 0);
								//Serial.println((int)p);
								v->push_back(p);
								//Serial.print("add: "); Serial.print(i); Serial.print("/"); Serial.println(i2);
							}
						}
					}

				}
				break;
			default:
				break;

		}



	}

};

