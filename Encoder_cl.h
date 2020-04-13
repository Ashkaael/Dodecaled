

class Encoder_cl
{

private:
//Attributs de travail
bool DT, CLK, SW;
bool DT_Mem, CLK_Mem, SW_Mem;
int ActPos_Mem;
//Pin affectée à l'encoder
int PinDT, PinCLK, PinSW;
//Paramètres
int MinVal, MaxVal, StepVal;
bool Loop;
std::string EncName;
//Valeurs actuelles
int ActPos;
bool ActPosChanged;

public:

// Constructueur
Encoder_cl(std::string a_EncName, int a_PinSW, int a_PinCLK, int a_PinDT, 
int a_MinVal, int a_MaxVal, int a_StepVal, int a_Loop):
// initialisation attributs
EncName(a_EncName),PinSW(a_PinSW),PinCLK(a_PinCLK),PinDT(a_PinDT),
MinVal(a_MinVal),MaxVal(a_MaxVal),StepVal(a_StepVal),Loop(a_Loop),
DT(false),CLK(false),SW(false),DT_Mem(false),CLK_Mem(false),SW_Mem(false),ActPosChanged(false)
{
  ActPos = MinVal; ActPos_Mem = MinVal;
  // link des IO
  pinMode (PinCLK,INPUT);  pinMode (PinDT,INPUT);  
  if  (PinSW!=0){ pinMode (PinSW,INPUT); }
  // On mémorise la clock actuel
  CLK_Mem = digitalRead(PinCLK);
}

int GetEncPos() { return ActPos; }
int GetSW_Val() { return SW; }
bool IsActPosChanged() { return ActPosChanged; }

void RefreshEncVal()
{  

  // acquisition valeurs actuelles
  DT = digitalRead(PinDT);
  CLK = digitalRead(PinCLK);
  if (PinSW!=0){SW = digitalRead(PinSW);}

  if ( CLK != CLK_Mem ) { // si changement d'état de la clock
    // si data = clock: sens antihoraire
    if (DT == CLK) {ActPos-=StepVal;}
    else           {ActPos+=StepVal;}
  }

  if (Loop){  if (ActPos<MinVal) {ActPos=MaxVal;}
              if (ActPos>MaxVal) {ActPos=MinVal;}
  }else{      if (ActPos<MinVal) {ActPos=MinVal;}
              if (ActPos>MaxVal) {ActPos=MaxVal;}
  }

  ActPosChanged= (ActPos != ActPos_Mem);

  if(ActPos!=ActPos_Mem) { Serial.print(EncName.data()); Serial.print(": "); Serial.println(ActPos);}
  
  // mémorisation des etats
  DT_Mem = DT;
  CLK_Mem = CLK;
  SW_Mem = SW;
  ActPos_Mem = ActPos;

}

  
};
