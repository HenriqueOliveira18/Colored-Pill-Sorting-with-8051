 #include <c8051f340.h>
#include <string.h>
#include <stdio.h>

//	Definir os Pinos.
#define RW P3_4
#define RS P3_1
#define E P3_3
#define LCD P1
#define posicao P2_4

// Inicialização das funções.
void configLCD(void);
void writeLCD(unsigned char valor, unsigned char TipoDados);
void espera(unsigned int ms);
void configTimer20(void);
void autores(void);
void valoresLCD(void);
void MinMaxLCD(void);
void menuInicial(void);
void digitos(void);
void Apresentacao(void);
void divisoes(void);
void menuCalibrar(void);
void configTimer1(void);
void verificarPasse(void);
void MenuCalibrarCor(void);
void minimosCor(void);
void divisoesAmarelo(void);
void divisoesAzul(void);
void divisoesVerde(void);
void divisoesVermelho(void);
void divisoesLaranja(void);
void divisoesMaximo(void);
void divisoesMinimo(void);
void ValoresLidos(void);
void writeMenu5(void);
unsigned char passeVerificacao=0,controlo=0;

// Variáveis Globais.
unsigned int maximoLaranja=0,maximoAmarelo=0,maximoVerde=0,maximoVermelho=0;
unsigned int minimoLaranja=0,minimoAzul=0,minimoVerde=0,minimoVermelho=0;
unsigned char escreveAzul=0,escreveAmarelo=0,escreveVerde=0,escreveLaranja=0,escreveVermelho=0;
unsigned char contadorAzulU=0,contadorAmareloU=0,contadorLaranjaU=0,contadorVermelhoU=0,contadorVerdeU=0;
unsigned char passo = 0b00000001, contadorS=0, valor=0,minTL2=255,preto=1,contadorAmarelo=0,p=0;
unsigned char valorRecebido=0x37, contadorAzul=0, k=0, digi[5],contador=1,start=0,clean=0,palavra[12];
unsigned char contadorVermelho=0,contadorVerde=0,contadorLaranja=0,contadorServo=0,opcao=0,menu=0,opcaoCor=0;
unsigned char azul[]="B ", amarelo[]="Y ",vermelho[]="R ",laranja[]="O ",verde[]="G ",div[6],contadorDiv=0,auxPassos=0;
unsigned char DivisoesMaximo[6],DivisoesMinimo[6],numeroPassos0=0,numeroPassos1=0,menu1Contador=0,escrevePassos=0;
unsigned int periodoCor=0, velocidade=3500, contadorOnda=0,min=4000,tempo=0,contadorPassos=0;
unsigned char Azul[]="Azul",Amarelo[]="Amarelo",Vermelho[]="Vermelho",Laranja[]="Laranja",Verde[]="Verde";
unsigned char Insira[]="Insira a cor: ";
unsigned int minAzul=1500,maxAmarelo=388,minVermelho=527,maxVermelho=527;
unsigned int minLaranja=494,maxLaranja=494,minVerde=672,maxVerde=672;
unsigned char numAzul[2],numAmarelo[2],numVermelho[2],numLaranja[2],numVerde[2];

__code unsigned char apresentacao1[]="Projeto 2022/2023";
__code unsigned char apresentacao2[]="MICROPROCESSADORES";
__code unsigned char insiraPasse1[]="Insira a "; 
__code unsigned char insiraPasse2[]="Palavra Passe: "; 
__code unsigned char menu1_1[]="1: Iniciar";
__code unsigned char menu1_2[]="2: Ajustar";
__code unsigned char menu1_3[]="3: Passos";
__code unsigned char menu2_1[]="Escolha a cor:";
__code unsigned char menu2_2[]="1B 2Y 3R 4O 5G";
__code unsigned char menu5[]="Contagem motor:";
__code unsigned char password[]="projRH";
__code unsigned char Frase1[]="Realizado por:"; 
__code unsigned char Autores[]="Rafael Seco e Henrique Oliveira.";
__code unsigned char LCDMaximo[]="Maximo: ";
__code unsigned char LCDMinimo[]="Minimo: ";
__code unsigned char valores1[]=" Valores lidos ";
__code unsigned char valores2[]=" com sucesso! ";

void main(void){

	// Valores a alterar para periodos reais.
	unsigned char i=0;
	unsigned char P4=0;	// Desliga o Motor.
	posicao=0;
	P2MDOUT = 0x10;
	P4MDOUT = 0x0F;	// Coloca os 4 pinos onde se liga o motor de passo em modo Push-pull.
	XBR1 = 0x40; // allows the crossbar, i.e. the connection between the PC and the I / O ports
	XBR0 = 0x01;	// connects the UART to P0_4 and P0_5 pin
	OSCICN = 0x83;	/* Set up oscillator (internal) to 12MHz; internal clock signal is 1/12 of this
	amount, ie 1uS. */
	PCA0MD &=~0x40; // allows disable the watchdog
	PCA0MD = 0x00;// do the disable watchdog
	
	configLCD();
	configTimer1();
	
	//	Configuração das Interrupções.
	IE = 0b10110111;
	IT0=1;	// Falling Edge
	// Configuração do Canal Série.
	SCON = 0b01010000;
	// Configuração das Prioridades.
	//IP = 0b00010000;	// Prioridade Alta para o Canal Série.

	Apresentacao();
	espera(500);
	autores();	// Escreve o nome dos autores no LCD.
	while(start==0);	// Testa o botão de iniciar.
	verificarPasse(); //Deveria verificar a password e continuar -> menu0
	menu=1;

	while(1){
		while(menu==1){	// Menu Inicial.
			menuInicial();
			while(opcao==0){
				if(clean==1){
					menu1Contador++;
					if(menu1Contador==3)
						menu1Contador=0;
					menuInicial();
					clean=0;
				}
			}
			
			if(opcao==0x31){
				menu=2;
				opcao=0;
			}
			if(opcao==0x32) {
				opcao=0;
				menu=3;
			}	
			if(opcao==0x33) {
				opcao=0;
				menu=5;
			}	
		}
		while(menu==2){	// Menu "iniciar"/Contador.
			if(i==0){
				configTimer20();
				valoresLCD();
				i++;
			}

			if(start==1 && clean==1){	// Limpa as variáveis/LCD.
				contadorVermelho=0;
				contadorVerde=0;
				contadorAmarelo=0;
				contadorLaranja=0;
				contadorAzul=0;
				contadorVermelhoU=0;
				contadorVerdeU=0;
				contadorAmareloU=0;
				contadorLaranjaU=0;
				contadorAzulU=0;
				valoresLCD();
				clean=0;
			}

		// Código que conta as cores.
			if(contadorOnda!=0){
				if(contadorOnda<3000){	// Se não for Preto
					preto=0;
					if(contadorOnda<min )
						min = contadorOnda;
				}
				else{	// Se for Preto
					if(preto==0 && min<(maxAmarelo+12)){
						contadorAmarelo++;
						valoresLCD();
						divisoes();
						SBUF = div[contadorDiv];
						EX0=0;
						ET2=1;
						tempo=1900;
						posicao=1;
						TL2=65536-tempo;
						TH2=(65536-tempo)>>8;
					}
					if(preto==0 && min>(minAzul-41)){
						contadorAzul++;
						valoresLCD();
						divisoes();
						SBUF = div[contadorDiv];
						EX0=0;
						ET2=1;
						tempo=1900;
						posicao=1;
						TL2=65536-tempo;
						TH2=(65536-tempo)>>8;
					}
					if(preto==0 && min>=(minLaranja-12) && min<(maxLaranja+12)){
						contadorLaranja++;
						valoresLCD();
						divisoes();
						SBUF = div[contadorDiv];
						EX0=0;
						ET2=1;
						tempo=1500;
						posicao=1;
						TL2=65536-tempo;
						TH2=(65536-tempo)>>8;
					}
					if(preto==0 && min>=(minVermelho-15) && min<(maxVermelho+15)){
						contadorVermelho++;
						valoresLCD();
						divisoes();
						SBUF = div[contadorDiv];
						EX0=0;
						ET2=1;
						tempo=1100;
						posicao=1;
						TL2=65536-tempo;
						TH2=(65536-tempo)>>8;
					}
					if(preto==0 && min>=(minVerde-15) && min<(maxVerde+15)){
						contadorVerde++;
						valoresLCD();
						divisoes();
						SBUF = div[contadorDiv];
						EX0=0;
						ET2=1;
						tempo=1200;
						posicao=1;
						TL2=65536-tempo;
						TH2=(65536-tempo)>>8;
					}
					preto=1;
					min=4000;
					contadorOnda=0;
				}	//Else    
				
				
			} 	// if(contadorOnda!=0).
			if(opcao==0x76){	// Código para voltar no Menu.
				opcao=0;
				menu=1;
				TR2=0;
				TR0=0;
			}
		} // while(menu==2)
		i=0;

		while(menu==3){
			
			if(i==0){
				menuCalibrar();
				i++;
			}
			if(opcaoCor!=0)
				menu=4;
			if(opcao==0x76){ // Código para voltar no Menu.
				opcao=0;
				menu=1;
				TR2=0;
				TR0=0;
			}
		}
		i=0;

		if(menu==4){
			configTimer20();
			MenuCalibrarCor();
			minimosCor();
			espera(3000);	// Espera que a peça caia.
			TR2=0;
			TR0=0;
			ValoresLidos();
			espera(1000);
			MinMaxLCD();
			espera(3000); // Espera que o leitor veja os valores lidos no LCD
			opcaoCor=0;
			DivisoesMaximo[0]='\0';
			DivisoesMinimo[0]='\0';
			menu=3;
		}
		i=0;

		while(menu==5){	// Contador de Passos.
			if(i==0){
				configTimer20();
				writeMenu5();
				i=1;
			}

			if(auxPassos==1){
				writeMenu5();
				auxPassos=0;
			}
			
			if(opcao==0x76){ // Código para voltar no Menu.
				opcao=0;
				menu=1;
				TR2=0;
				TR0=0;
				contadorPassos=0;
				numeroPassos0=0;
				numeroPassos1=0;
			}

			if(start==1 && clean==1){
				numeroPassos0=0;
				numeroPassos1=0;
				contadorPassos=0;
				clean=0;
				writeMenu5();
			}
		}
		i=0;
	} // While(1).
} // Main


void configLCD(void) {
	RW = 0;
	writeLCD(0b00111000,0);	// Linhas/Caracteres: 00111(2 linhas)0(Caracteres 5x7)00.
	writeLCD(0b00001100,0);	// Display/Cursor/Piscar: 000011(Display ON)1(Cursor ON)1(Piscar On).
	writeLCD(0b00000001,0);	// Limpar o LCD.
	writeLCD(0b00000110,0);	// Em Incremento ON, Shift Total OFF.
	writeLCD(0b10000000,0);	// Linha de cima 1ª, Valor da coluna a Escrever 1ª(0).
}

void writeLCD(unsigned char valor, unsigned char TipoDados) {
	if(TipoDados == 1)
		RS = 1;
	else
		RS = 0;
	LCD = valor;
	E = 1;
	espera(2);
	E = 0;
	espera(2);
}

void Apresentacao(void){
	unsigned char i=0,j=0,k=0,l=0;
	writeLCD(1,0);	// Limpa o LCD.

	//	Primeiro Nome.
	for(j=0;j<(strlen(apresentacao1)-15);j++){
			writeLCD(0b10000000,0); //escreve na segunda linha e primeira coluna
			for(l=j;l<strlen(apresentacao1);l++)
				writeLCD(apresentacao1[l],1);
			espera(200);
		}
		espera(500);
	for(k=0;k<(strlen(apresentacao2)-15);k++){
		writeLCD(0b11000000,0); //escreve na segunda linha e primeira coluna
		for(i=k;i<strlen(apresentacao2);i++)
			writeLCD(apresentacao2[i],1);
		espera(200);
	}
}

void autores(void) { 
	unsigned char i=0,j=0,k=0;
	
	writeLCD(1,0);	// Limpa o LCD.

	//	Primeiro Nome.
	writeLCD(0b10000000,0);	// Linha de cima 1ª, Valor da coluna a Escrever 1ª(0).
	for(j=0;j<strlen(Frase1);j++)
		writeLCD(Frase1[j],1);

	//	Segundo Nome.
	//while(1) {
		for(k=0;k<(strlen(Autores)-15);k++){
			writeLCD(0b11000000,0); //escreve na segunda linha e primeira coluna
			for(i=k;i<strlen(Autores);i++)
				writeLCD(Autores[i],1);
			espera(200);
		}
	//} Colocar um Break quando o botão do P0.0 for acionado.
}

void valoresLCD(void) {
	unsigned char i=0, j=0, k=0, y=0, z=0;
	writeLCD(1,0);	// Limpa o LCD.
	
	// Escreve "B {VALOR}".
	writeLCD(0b10000000,0);
	while(azul[i]!='\0'){
		writeLCD(azul[i],1);
		i++;
	}
	if(contadorAzul>9){
		contadorAzul=0;
		contadorAzulU++;
	}

	writeLCD(contadorAzulU+48,1);
	writeLCD(contadorAzul+48,1);


	
	// Escreve "Y {VALOR}".
	writeLCD(0b10000110,0);		//Muda de linha
	while(amarelo[j]!='\0'){
		writeLCD(amarelo[j],1);
		j++;
	}
	if(contadorAmarelo>9){
		contadorAmarelo=0;
		contadorAmareloU++;
	}

	writeLCD(contadorAmareloU+48,1);
	writeLCD(contadorAmarelo+48,1);


	// Escreve "G {VALOR}".
	writeLCD(0b10001011,0);		//Muda de linha
	while(verde[k]!='\0'){
		writeLCD(verde[k],1);
		k++;
	}
	if(contadorVerde>9){
		contadorVerde=0;
		contadorVerdeU++;
	}

	writeLCD(contadorVerdeU+48,1);
	writeLCD(contadorVerde+48,1);


	// Escreve "R {VALOR}".
	writeLCD(0b11000000,0);		//Muda de linha
	while(vermelho[z]!='\0'){
		writeLCD(vermelho[z],1);
		z++;
	}
	if(contadorVermelho>9){
		contadorVermelho=0;
		contadorVermelhoU++;
	}

	writeLCD(contadorVermelhoU+48,1);
	writeLCD(contadorVermelho+48,1);
	
	// Escreve "O {VALOR}".
	writeLCD(0b11000110,0);		//Muda de linha
	while(laranja[y]!='\0'){
		writeLCD(laranja[y],1);
		y++;
	}
	if(contadorLaranja>9){
		contadorLaranja=0;
		contadorLaranjaU++;
	}

	writeLCD(contadorLaranjaU+48,1);
	writeLCD(contadorLaranja+48,1);
}

void menuInicial(void){
	unsigned char i=0,j=0;
//SBUF=52;
	writeLCD(1,0);

	if(menu1Contador==0){
		//	Primeira Opção.
		writeLCD(0b10000000,0);	// Linha de cima 1ª, Valor da coluna a Escrever 1ª(0).
		for(i=0;i<strlen(menu1_1);i++)
			writeLCD(menu1_1[i],1);
	
		//	Segunda Opção.
		writeLCD(0b11000000,0);	// Linha de cima 1ª, Valor da coluna a Escrever 1ª(0).
		for(j=0;j<strlen(menu1_2);j++)
			writeLCD(menu1_2[j],1);
	}
	if(menu1Contador==1){
		//	Segunda Opção.
		writeLCD(0b10000000,0);	// Linha de cima 1ª, Valor da coluna a Escrever 1ª(0).
		for(j=0;j<strlen(menu1_2);j++)
			writeLCD(menu1_2[j],1);
		//	Terceira Opção.
		writeLCD(0b11000000,0);	// Linha de cima 1ª, Valor da coluna a Escrever 1ª(0).
		for(i=0;i<strlen(menu1_3);i++)
			writeLCD(menu1_3[i],1);
	}
	if(menu1Contador==2){
		//	Terceira Opção.
		writeLCD(0b10000000,0);	// Linha de cima 1ª, Valor da coluna a Escrever 1ª(0).
		for(i=0;i<strlen(menu1_3);i++)
			writeLCD(menu1_3[i],1);
		//	Primeira Opção.
		writeLCD(0b11000000,0);	// Linha de cima 1ª, Valor da coluna a Escrever 1ª(0).
		for(j=0;j<strlen(menu1_1);j++)
			writeLCD(menu1_1[j],1);
	}
}

void menuCalibrar(void) {	// Menu 3.
	unsigned char i=0, j=0;
	writeLCD(1,0);

	//	Primeira Opção.
	writeLCD(0b10000000,0);	// Linha de cima 1ª, Valor da coluna a Escrever 1ª(0).
	for(i=0;i<strlen(menu2_1);i++)
		writeLCD(menu2_1[i],1);

	//	Segunda Opção.
	writeLCD(0b11000000,0);	// Linha de cima 1ª, Valor da coluna a Escrever 1ª(0).
	for(j=0;j<strlen(menu2_2);j++)
		writeLCD(menu2_2[j],1);
}

void MenuCalibrarCor(void){	// Menu 4.
	unsigned char i=0,j=0;
//SBUF=52;
	writeLCD(1,0);

	writeLCD(0b10000001,0);	// Linha de cima 1ª, Valor da coluna a Escrever 1ª(0).
	for(i=0;i<strlen(Insira);i++)
		writeLCD(Insira[i],1);

	//	Segunda Opção.
	//writeLCD(0b11000000,0);	// Linha de cima 1ª, Valor da coluna a Escrever 1ª(0).

	if(opcaoCor == 0x31){
		writeLCD(0b11000101,0);	// Linha de baixo, Valor da coluna a Escrever 6ª(5).
		for(j=0;j<strlen(Azul);j++)
			writeLCD(Azul[j],1);
	}
	if(opcaoCor == 0x32){
		writeLCD(0b11000100,0);	// Linha de baixo, Valor da coluna a Escrever 4ª(3).
		for(j=0;j<strlen(Amarelo);j++)
			writeLCD(Amarelo[j],1);
	}
	if(opcaoCor == 0x33){
		writeLCD(0b11000100,0);	// Linha de baixo, Valor da coluna a Escrever 4ª(3).
		for(j=0;j<strlen(Vermelho);j++)
			writeLCD(Vermelho[j],1);
	}
	if(opcaoCor == 0x34){
		writeLCD(0b11000100,0);	// Linha de baixo, Valor da coluna a Escrever 4ª(3).
		for(j=0;j<strlen(Laranja);j++)
			writeLCD(Laranja[j],1);
	}
	if(opcaoCor == 0x35){
		writeLCD(0b11000101,0);	// Linha de baixo, Valor da coluna a Escrever 6ª(5).
		for(j=0;j<strlen(Verde);j++)
			writeLCD(Verde[j],1);
	}
}


void espera(unsigned int ms) {
	unsigned int i = 0, j = 0;
	for (i = 0; i < ms; i++)
		for(j=0; j < 668; j++);
}

void configTimer20(void) {
//	[T0]0(gate->Software)0(C/T->Relogio Interno)01(Modo 1: 65536 bits).

	//	Configuração do Temporizador 0.
	TL0 = (65536-5000);
	TH0 = (65536-5000)>>8;
	TF0 = 0;	// Flag do Temporizador 0.
	TR0 = 1;	// ON/OFF do Temporizador 0.


	//	Configuração do Temporizador 2.
	TL2 = 0;
	TH2 = 0;
	RCAP2L = 0;
	RCAP2H = 0;
	TF2 = 0;
	TR2 = 0;
}

void configTimer1(void){
	//	[T1]0(Gate->Software)0(C/T->Relogio Interno)10(Modo 2: 256 bits).
	TMOD = 0b00100001;

	//	Configuração do Temporizador 1.
	TL1 = 204;
	TH1 = 204;
	TF1 = 0;	// Flag do Temporizador 1.
	TR1 = 1;	// ON/OFF do Temporizador 1.
}

void avancoDoMotorPasso(void) __interrupt(1) {	// Interrupção Temporizador 0.
	TL0=(65536-velocidade);
	TH0=(65536-velocidade)>>8;
	TF0 = 0;	//	Renicialização da Flag do Temporizador 0.
	
	passo = passo<<1;
	if(passo>8)
		passo = 1;
	P4 = passo;

	contadorPassos++;
	if(contadorPassos==2048){
		numeroPassos0++;
		auxPassos=1;
		contadorPassos=0;
	}
		
}

void sensorDeCor(void) __interrupt(0){	// Interrupção Externa 0.
	contadorS++;
	TR2=1;
	if(contadorS==50){
		contadorOnda=TH2;
		contadorOnda=(contadorOnda<<8);
		contadorOnda=contadorOnda+TL2;
		contadorS=0;
	}
	TL2=0;	// Renicialização do Temporizador 2 (Low Value).
	TH2=0;	// Renicialização do Temporizador 2 (High Value).
	IE0=0;
}


void canalSerie(void) __interrupt(4) {	// Interrupção do Canal Série
// Flags de Interrupção: TI e RI.
	if(RI==1) {
		RI=0;
		valorRecebido=SBUF;
	// Controlo do Motor:
		if(menu==0){
			// Palavra Passe do Menu 0:
			if(valorRecebido!=0x0B){
				palavra[p]=SBUF;
				p++;
			}
		}

		if(menu==1)
		 	if(valorRecebido==0x31 || valorRecebido==0x32 || valorRecebido==0x33) //Seleção do Menu Inicial
		 			opcao=valorRecebido;

	 	if(menu==3){
	 		if(valorRecebido==0x31 || valorRecebido==0x32 || valorRecebido==0x33 || valorRecebido==0x34 || valorRecebido==0x35)
						opcaoCor = valorRecebido; 
			if(valorRecebido==0x76)
				opcao=valorRecebido;
		}

		if(menu==2 || menu==5 || menu==4){
			if(valorRecebido==0x2B && velocidade>2500){	// Aumenta a velocidade (Diminui o valor).
				TR0 = 1;
				velocidade = velocidade - 1000;
			}
			if(valorRecebido==0x2D && velocidade<10500){	// Diminui a velocidade (Aumenta o valor).
				TR0 = 1;
				velocidade = velocidade + 1000;
			}
			if(valorRecebido==0x30)
				TR0 = 0;
			if(valorRecebido==0x50 || valorRecebido==0x70)
				TR0 = 1;
			if(valorRecebido==0x76)
				opcao=valorRecebido;
		}
	}
	if(TI==1) {
		TI=0;
		if(contadorDiv!=0){
			contadorDiv--;
			SBUF = div[contadorDiv];
		}
	}
}

void divisoes(void) {
	contadorDiv=0;
	while(min!=0){
		div[contadorDiv]=(min%10)+48;
		min=min/10;
		contadorDiv++;
	}
	div[contadorDiv]='\n';

}

void MotorServo(void) __interrupt(5){	// Interrupção Timer 2.
	if(posicao==0){
		posicao=1;
		TL2=65536-tempo;
		TH2=(65536-tempo)>>8;
		TF2=0;
	}
	else{
		posicao=0;
		TL2=65536-(20000-tempo);
		TH2=(65536-(20000-tempo))>>8;
		TF2=0;
	}
	contadorServo++;
	if(contadorServo>21){
		ET2=0;
		EX0=1;
		contadorServo=0;
	}
	
}

void botaIniciar(void) __interrupt(2){
	unsigned int aux = 0;

	for(aux=0;aux<5000;aux++)
		if(P2_0==0)
			aux=0;
	IE1=0;
	if(start==1)
		clean=1;
	start=1;
	
}

void verificarPasse(void){
	unsigned char i=0,j=0;
	//unsigned int z = strcmp(palavra,password);
	writeLCD(1,0);	// Limpa o LCD.

	//"Insira a "
	writeLCD(0b10000000,0);	// Linha de cima 1ª, Valor da coluna a Escrever 1ª(0).
	for(i=0;i<strlen(insiraPasse1);i++)
		writeLCD(insiraPasse1[i],1);

	//"Palavra Passe: "
	writeLCD(0b11000000,0);	// Linha de cima 2ª, Valor da coluna a Escrever 1ª(0).
	for(j=0;j<strlen(insiraPasse2);j++)
		writeLCD(insiraPasse2[j],1);


	while(passeVerificacao==0){
		if(p==7){
			palavra[p]='\0';
			p=0;
			while(controlo==0){
				if(palavra[p]==password[p]){
					p++;
					//SBUF=0x62;
					if(p==6){
						passeVerificacao = 1;
						controlo=1;
					}
				}
				else{
					controlo=1;
					SBUF=0x63;
				}
			}
			controlo=0;
			p=0;
		}
	}
}

void minimosCor(void){
	unsigned char i=0,j=0,k=0,valorAtual=0;

	while(i<3){
		if(contadorOnda!=0){
			if(contadorOnda<3000){	// Se não for Preto
				preto=0;
				if(contadorOnda<min)
					min = contadorOnda;
			}
			else{	// Se for Preto
				if(preto==0 && min<2500){
					if(opcaoCor==0x31){
						if(k==0){
						minAzul=min;
						k++;
						}
						else {
							if(minAzul>min)
								minAzul=min;
						}
						EX0=0;
						ET2=1;
						tempo=1900;
						posicao=1;
						TL2=65536-tempo;
						TH2=(65536-tempo)>>8;
					}
					if(opcaoCor==0x32){
						if(k==0){
						maxAmarelo=min;
						k++;
						}
						else {
							if(maxAmarelo<min)
								maxAmarelo=min;
						}
						EX0=0;
						ET2=1;
						tempo=1900;
						posicao=1;
						TL2=65536-tempo;
						TH2=(65536-tempo)>>8;
					}
					if(opcaoCor==0x33){
						if(k==0){
							minVermelho=min;
							maxVermelho=min;
							k++;
							}
							else {
								if(minVermelho>min)
									minVermelho=min;
								if(maxVermelho<min)
									maxVermelho=min;
							}
							EX0=0;
							ET2=1;
							tempo=1100;
							posicao=1;
							TL2=65536-tempo;
							TH2=(65536-tempo)>>8;
						}
					if(opcaoCor==0x34){
						if(k==0){
							minLaranja=min;
							maxLaranja=min;
							k++;
							}
							else {
								if(minLaranja>min){
									minLaranja=min;
								}
								if(maxLaranja<min)
									maxLaranja=min;
							}
							EX0=0;
							ET2=1;
							tempo=1500;
							posicao=1;
							TL2=65536-tempo;
							TH2=(65536-tempo)>>8;
						}
					if(opcaoCor==0x35){
						if(k==0){
							minVerde=min;
							maxVerde=min;
							k++;
							}
							else {
								if(minVerde>min)
									minVerde=min;
								if(maxVerde<min)
									maxVerde=min;
							}
							EX0=0;
							ET2=1;
							tempo=1100;
							posicao=1;
							TL2=65536-tempo;
							TH2=(65536-tempo)>>8;
						}
					i++;
					min=4000;
					preto=1;
				}// if(min<2500)
			}	//else
		contadorOnda=0;
		}	// if(contador!=0)
	}	//while(i<3)
	
	divisoesMaximo();
	divisoesMinimo();

	
	//espera(4000);
	//menu=3;	
	/* min=maxAzul;
	divisoes();
	SBUF = div[contadorDiv]; */
}	//void

void divisoesMaximo(void){

	contadorDiv=0;
	maximoVermelho = maxVermelho;
	maximoAmarelo = maxAmarelo;
	maximoLaranja = maxLaranja;
	maximoVerde = maxVerde;
	
	if(opcaoCor==0x32){
		while(maximoAmarelo!=0){
			DivisoesMaximo[contadorDiv]=(maximoAmarelo%10)+48;
			maximoAmarelo=maximoAmarelo/10;
			contadorDiv++;
		}
	}
	if(opcaoCor==0x33){
		while(maximoVermelho!=0){
			DivisoesMaximo[contadorDiv]=(maximoVermelho%10)+48;
			maximoVermelho=maximoVermelho/10;
			contadorDiv++;
		}
	}
	if(opcaoCor==0x34){
		while(maximoLaranja!=0){
			DivisoesMaximo[contadorDiv]=(maximoLaranja%10)+48;
			maximoLaranja=maximoLaranja/10;
			contadorDiv++;
		}
	}
	if(opcaoCor==0x35){
		while(maxVerde!=0){
			DivisoesMaximo[contadorDiv]=(maxVerde%10)+48;
			maxVerde=maxVerde/10;
			contadorDiv++;
		}
	}
}

void divisoesMinimo(void){

	contadorDiv=0;
	minimoAzul = minAzul;
	minimoVermelho = minVermelho;
	minimoLaranja = minLaranja;
    minimoVerde = minVerde;
	if(opcaoCor==0x31){
		while(minimoAzul!=0){
			DivisoesMinimo[contadorDiv]=(minimoAzul%10)+48;
			minimoAzul=minimoAzul/10;
			contadorDiv++;
		}
	}
	
	if(opcaoCor==0x33){
		while(minimoVermelho!=0){
			DivisoesMinimo[contadorDiv]=(minimoVermelho%10)+48;
			minimoVermelho=minimoVermelho/10;
			contadorDiv++;
		}
	}
	if(opcaoCor==0x34){
		while(minimoLaranja!=0){
			DivisoesMinimo[contadorDiv]=(minimoLaranja%10)+48;
			minimoLaranja=minimoLaranja/10;
			contadorDiv++;
		}
	}
	if(opcaoCor==0x35){
		while(minimoVerde!=0){
			DivisoesMinimo[contadorDiv]=(minimoVerde%10)+48;
			minimoVerde=minimoVerde/10;
			contadorDiv++;
		}
	}
}

void MinMaxLCD(void){

	unsigned char i=0,j=0;
	writeLCD(1,0);

	if(opcaoCor==0x33||opcaoCor==0x34||opcaoCor==0x35){
		writeLCD(0b10000000,0);
		while(LCDMinimo[i]!='\0'){
			writeLCD(LCDMinimo[i],1);
			i++;
		}
	
		i=3;
		while(i!=0){
			writeLCD(DivisoesMinimo[i-1],1);
			i--;
		}
	
		writeLCD(0b11000000,0);
		while(LCDMaximo[j]!='\0'){
			writeLCD(LCDMaximo[j],1);
			j++;
		}
	
		j=3;
		while(j!=0){
			writeLCD(DivisoesMaximo[j-1],1);
			j--;
		}
	}

	if(opcaoCor==0x31){
		writeLCD(0b10000000,0);
		while(LCDMinimo[i]!='\0'){
			writeLCD(LCDMinimo[i],1);
			i++;
		}
	
		i=4;
		while(i!=0){
			writeLCD(DivisoesMinimo[i-1],1);
			i--;
		}
	}

	if(opcaoCor==0x32){
		writeLCD(0b10000000,0);
		while(LCDMaximo[i]!='\0'){
			writeLCD(LCDMaximo[i],1);
			i++;
		}
	
		i=3;
		while(i!=0){
			writeLCD(DivisoesMaximo[i-1],1);
			i--;
		}
	}
}

void ValoresLidos(void){
	unsigned char i=0,j=0;

	writeLCD(1,0);

	writeLCD(0b10000000,0);
	while(valores1[i]!='\0'){
		writeLCD(valores1[i],1);
		i++;
	}

	writeLCD(0b11000000,0);
	while(valores2[j]!='\0'){
		writeLCD(valores2[j],1);
		j++;
	}
}

void writeMenu5(void) {
	unsigned char i=0,j=0;

	writeLCD(1,0);

	writeLCD(0b10000000,0);
	for(i=0;i<strlen(menu5);i++)
		writeLCD(menu5[i],1);

	writeLCD(0b11000000,0);

	if(numeroPassos0>9){
		numeroPassos0=0;
		numeroPassos1++;
	}

	writeLCD(numeroPassos1+48,1);
	writeLCD(numeroPassos0+48,1);
}

