/******************************************************************************

age of cities

*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <stdbool.h>


struct mapa {
	int madeira ;
    int pedra ;
    int alimento;
    int ocupadoJogador; // mapa ocupado por 
	
};
struct posicoes {
	int posicaox; // 0 a 19
	int posicaoy; // de 0 a 24
};
struct recursos_jogadores
  {
    int casas;
    int construindoCasa; //turnos falta terminar
    int construindoQuartel; //turnos falat terminar
    int construindoMuralha; 
    int construindoTemplo;
    int habitantes;
	int posicaoxIni; //posicao inicial até 20
	int posicaoyIni; //posicao inicial até 25
    int madeira;
    int pedra;
    int alimento ; 
    
	int cidades; //tem 10 posicoes
	int posicoesConquistada ; // quantidade posicao consquistada no mapa ou numero de posicoes da cidade
	
    struct posicoes posicoes [499] ; // pode ter ate 500 posicoes de 0 a 499
	
    int templo;
    int muralha;
    int quartel;
	
    int soldadoCidade; //quantidade
    int soldadoGuerra;


    int foraJogo;		//1 - ainda jogando ; 0 fora do jogo
	int numeroJogador; // numero do jogador
  };

 int numeroJogadores = 0;  

  struct recursos_jogadores recursos[99]; //máximo numero de jogadores 100
  struct mapa mapa [20] [25]; // criação do matrix do mapa
  
  // baixa os recursos se houver disponibilidade
  //baixo tudo solicitado ou somente o que tem na area
int baixarRecursosMadeira(struct mapa *mapa,int saldoBaixar)//passando por referencia
{
  int saldoRestante = 0 ;

  if ((*mapa).madeira >= saldoBaixar )
  {
	(*mapa).madeira = (*mapa).madeira - saldoBaixar;  
    return 0;
  }
  else 
  {
	saldoRestante = (*mapa).madeira;    
	(*mapa).madeira = 0; // coletou tudo que o mapa ainda tinha
    return saldoRestante;
  }
	
}  
int baixarRecursosPedra(struct mapa *mapa,int saldoBaixar)
{
  int saldoRestante = 0 ;	 
  if ((*mapa).pedra >= saldoBaixar )
  {
	(*mapa).pedra = (*mapa).pedra - saldoBaixar;  
    return 0;
  }
  else 
  {
	saldoRestante = (*mapa).pedra;    
	(*mapa).pedra = 0; // coletou tudo que o mapa ainda tinha
    return saldoRestante; // mas ainda faltou
  }
	
}  
void preencherMapa( struct mapa *mapa)
// preenchimento do mapa com recursos aleatório de 
{
	(*mapa).madeira = 400 + (rand () % 1600); //randomizando de 400 a 2000
	(*mapa).pedra = 400 + (rand () % 1600);
	//(*mapa).alimento = rand() %100;
	(*mapa).ocupadoJogador = -1;
	
}
void mostrarRecursos (struct recursos_jogadores recursos)
{
  int i = 0;
  printf("\n tem %i casas e contruindo %i \t ",recursos.casas,  recursos.construindoCasa);
  if (recursos.construindoQuartel>0) {
   printf(" contruindo quartel faltando %i turnos. ",recursos.construindoQuartel);
  }
  if ( recursos.quartel == 1) {
	printf("possui quartel. ");}
  if (recursos.construindoTemplo>0 ) {
	printf("construindo um templo faltando %i turnos. ",recursos.construindoTemplo);}
  if (recursos.construindoMuralha>0){
  printf(" construindo muralha faltando %i turnos para terminar. ",recursos.construindoMuralha);}
  if (recursos.muralha == 1) {
  printf(" possui muralha.");}
  if (recursos.templo == 1){
  printf(" possui templo. ");}
  if (recursos.madeira>0) {
   printf(" em estoque %i em madeiras. ",recursos.madeira);}
  if (recursos.pedra>0) {
  printf(" em posse %i pedras. ",recursos.pedra);}
  if (recursos.alimento>0){
   printf(" possui %i alimentos em estoque. ",recursos.alimento);}
  printf("possui %i habitantes. ",recursos.habitantes);
  if (recursos.soldadoCidade >0)
  {printf(" Tem %i soldados na cidade e %i na guerra.", recursos.soldadoCidade,recursos.soldadoGuerra); }
  if (recursos.cidades == 1 ){
  	printf("possui uma cidade com %i posicoes. sao elas : ",recursos.posicoesConquistada);
  	for (i=0;i<recursos.posicoesConquistada;++i)
  	{ printf("(%i,%i) ; ",recursos.posicoes[i].posicaox,recursos.posicoes[i].posicaoy);
 	  }
  }
  else
  {
  	 printf("posicao x e y  (%i,%i)", recursos.posicaoxIni, recursos.posicaoyIni);
  }
  
  
}
void inicializandoRecursos(struct recursos_jogadores *recursos, int jogadores)
{
    (*recursos).foraJogo = 1;
    (*recursos).habitantes = 10 ;
    (*recursos).posicaoxIni =   (rand () % 19); //0 até 19
	(*recursos).posicaoyIni =   (rand () % 24); //0 até 24
    (*recursos).posicoes[0].posicaox =  (*recursos).posicaoxIni;
    (*recursos).posicoes[0].posicaoy =  (*recursos).posicaoyIni;
    
     (*recursos).madeira = 0;
     (*recursos).pedra = 0;
     // PARA NÃO MORRER NA PRIMEIRA JOGADA, para todo mundo ficar vivo até o fim da primeira rodada
     (*recursos).alimento = jogadores*10; 
	 (*recursos).cidades = 0;
	 (*recursos).posicoesConquistada = 1; // sem cidade mais ganha ganha uma posição inicial posicaoxini, posicaoyini
	 
     (*recursos).casas = 0;
     (*recursos).quartel = 0 ;
     (*recursos).muralha = 0;
      (*recursos).templo =0;
     (*recursos).construindoQuartel = 0;
     (*recursos).construindoCasa =0;
     (*recursos).construindoMuralha = 0;
     (*recursos).construindoTemplo = 0;
     (*recursos).soldadoCidade = 0;
     (*recursos).soldadoGuerra = 0;
}
// batalha na posicao da cidade o retorno é o ganhador
int batalhaPosicao(struct recursos_jogadores ataque , struct recursos_jogadores defesa)
{ 
  int fatorAtaque = 0, fatorDefesa = 0; ;
  if  (ataque.soldadoGuerra == 0)
    {
	 return defesa.numeroJogador; 
     
	}
  if ((defesa.soldadoCidade + defesa.soldadoGuerra ) == 0 )	
  { 
    return ataque.numeroJogador;
    
  }
  fatorAtaque = ataque.soldadoGuerra * 15; 
  fatorDefesa = (defesa.soldadoCidade + defesa.soldadoGuerra) * 10;
  
  // se tem templo a defesa aumenta 10%
  if (defesa.templo == 1)
  {
  	fatorDefesa = fatorDefesa * (1.10);
  }
  //se a defesa possui muralha aumenta 25%
  if (defesa.muralha == 1)
  {
  	fatorDefesa = fatorDefesa * (1.25);
  }
  //conseguiu para o ataque
  if (fatorDefesa >=  fatorAtaque) 
  { 
   return defesa.numeroJogador;
  }
  else
  { 
    return ataque.numeroJogador;
  }
  
}
//verifica se a posicao escolhida para mover e posicao adjacente a cidade ou posicao inicial
//para ser uma posicao adjacente basta ser o x ou y igual e o outro eixo diferente é -1 ou mais 1
bool posicaoAdjacente(struct recursos_jogadores recursos, int x, int y)
{
	int i = 0 ;
	
  for (i=0; i<=(recursos).posicoesConquistada; ++i)	
  {
  	if ( (recursos.posicoes[i].posicaox == x && recursos.posicoes[i].posicaoy-1 == y ) ||
	   (recursos.posicoes[i].posicaoy == y && recursos.posicoes[i].posicaox-1 == x  ) ||
	   
       (recursos.posicoes[i].posicaox == x && recursos.posicoes[i].posicaoy+1 == y ) ||
	   (recursos.posicoes[i].posicaoy == y && recursos.posicoes[i].posicaox+1 == x  )		   
	   
	   )
  	{ // e adjacente
  	 return true;
  	 break;
	  }
  }	
  return false;
}

// true se já esta conquistado, procurar outra posicao
bool posicaoJaConquistada(struct recursos_jogadores *recursos, int x, int y)
{
 int i= 0 ;

  for (i=0; i<=(*recursos).posicoesConquistada; ++i)	
  {
  	if ( (*recursos).posicoes[i].posicaox == x && (*recursos).posicoes[i].posicaoy == y  )
  	{ // ja conquistou 
  	 return 1;
  	 break;
	  }
  }
   return 0;
}
// posicao existe no mapa
bool pontoExiste(int x, int y )
{
   /// x vai de 0 a 19 e  y vai de 0 a 24
  return (x>=0 && x<20) &&  (y>=0 && y<25);	
}
// ocupa x posicoes ao redor do ponto
void ocuparPosicao (struct recursos_jogadores *recursos, int x,int y,int posicoes)
{  int i = 0 , j =0, voltas;
   int xtemp = 0 , ytemp = 0;
   int vencedorBatalha =0; //vencedor quando entre na posicao de uma cidade
   voltas = 1; //numero de voltas que deu para pegar os pontos ao redor

  // vai ocupando posicoes ao redor do ponto em sentido horario
  // se nao existe vai para proximo ponto
  for(i=1; i<=posicoes; ++voltas)
  {
  	for(j=1;j!=4 && i<=posicoes ;++j)
  	{
  	  switch (j)	
	 {
  	  	case 1:  // j == 1 diminui x, igual y
 	
	 		xtemp = x-voltas;
	 		ytemp = y;
	 	   	  		
  	  		break;
  	  	case 2:  //igual x, aumenta y
  	  		
  	  		xtemp = x;
  	  		ytemp = y+voltas;
  	  		break;
  	  		
  	  	case 3:  // aumenta x, igual y
  	  		xtemp = x + voltas;
  	  		ytemp = y ;
  	  		break;
  	  	
  	  	case 4: // igual x e diminui y
  	  		xtemp = x;
  	  		ytemp = y- voltas;
  	  		break;
		
      }
     
	 
	 // se verifica se a posicao existe no mapa e ja nao foi conquistada pelo jogador
	  if (pontoExiste(xtemp,ytemp)  && !(posicaoJaConquistada(&(*recursos),xtemp,ytemp))) {
	  	++i; // encontrou uma coordenada que existe
	  	//porem a posicao nao esta sendo ocupado por outro jogador
		    if (mapa[xtemp][ytemp].ocupadoJogador == -1) { // nao ocupado
			  	(*recursos).posicoes[(*recursos).posicoesConquistada].posicaox = xtemp; // adicionando a posicao lista de posicoes conquistadas
			  	(*recursos).posicoes[(*recursos).posicoesConquistada].posicaoy = ytemp; //
				//printf( " (%i,%i)\t ", (*recursos).posicoes[(*recursos).posicoesConquistada].posicaox,(*recursos).posicoes[(*recursos).posicoesConquistada].posicaoy);	
			  	++(*recursos).posicoesConquistada;  //posicoes conquistada
			  	mapa[xtemp][ytemp].ocupadoJogador = (*recursos).numeroJogador -1;
		    }
		    // entrou em confronto por ter a mesma posicao de outro jogador
		    else
			{
				vencedorBatalha = batalhaPosicao((*recursos),recursos[mapa[xtemp][ytemp].ocupadoJogador]);
				mapa[xtemp][ytemp].ocupadoJogador = vencedorBatalha-1;
				printf(" posicao (%i, %i) vencida na batalha pelo jogador %i",xtemp,ytemp,vencedorBatalha);
			 } 
	    
	  //	printf( " (%i,%i)\t ", xtemp,ytemp);
	  }	
	  
	 
	}
  }
	
}
 //passando os turnos e verificando se contruio algo 
void contruindo(struct recursos_jogadores *recursos)
{  	int x = 0 ,y = 0 ;
   //se tiver contruindo casa
   if ((*recursos).construindoCasa >0)
   {
     --(*recursos).construindoCasa;
     //casa pronta -- minha casa minha vida para 10 hab
     if ((*recursos).construindoCasa == 0)
     {
       ++(*recursos).casas;   
       printf("Parabens 1 casa terminada\n");
       if ((*recursos).casas == 1 )
       {
       	(*recursos).cidades = 1; // inicio da cidade e 1 casa
       
       	x = (*recursos).posicaoxIni;
       	y = (*recursos).posicaoyIni;
       	ocuparPosicao(&(*recursos),x,y,9);
		
       	//ocupara mais 9 posicoes no mapa além da posicao inical
       	
	   }
       (*recursos).habitantes=(*recursos).habitantes+10;   
	   //cada 3 casas a cidade aumenta uma posicao    
       if ( (*recursos).casas % 3 )// divisivel por 3  -- modulo
       {
       	x = (*recursos).posicoes[(*recursos).posicoesConquistada-1].posicaox; //ultima posicao do array
       	y = (*recursos).posicoes[(*recursos).posicoesConquistada-1].posicaoy;
       	ocuparPosicao(&(*recursos),x,y,1);
	   }
     }
   }
   
  if ((*recursos).construindoQuartel >0) 
  {
     --(*recursos).construindoQuartel;
     //quartel pronto ?
     if ((*recursos).construindoQuartel ==0)
     {
       ++(*recursos).quartel;
     } 
  }
  if ((*recursos).construindoMuralha >0) 
  {
     --(*recursos).construindoMuralha;
     //quartel pronto ?
     if ((*recursos).construindoMuralha ==0)
     {
       ++(*recursos).muralha;
     } 
  }

   if ((*recursos).construindoTemplo >0) 
  {
     --(*recursos).construindoTemplo;
     //quartel pronto ?
     if ((*recursos).construindoTemplo ==0)
     {
       ++(*recursos).templo;
     } 
  }
}
void construirCasa (struct recursos_jogadores * recursos)
{
	(*recursos).madeira = (*recursos).madeira -25;
	(*recursos).pedra  = (*recursos).pedra -25;
	(*recursos).construindoCasa = 5; //turno para construir
}
bool podeConstruirCasa (struct recursos_jogadores recursos)  
{  // 25 madeira, 25 pedra e 5 turnos
 //tem recurso suficiente
  return (recursos.madeira >=25 && recursos.pedra >= 25 && recursos.habitantes>=5);
  
}
void construirQuartel(struct recursos_jogadores * recursos)
{
 (*recursos).madeira = (*recursos).madeira -60;	
 (*recursos).pedra = (*recursos).pedra -50;
 (*recursos).construindoQuartel = 15;
}
bool podeConstruirQuartel(struct recursos_jogadores recursos)
{//60 madeira 15 turnos 50 pedras

 return (recursos.madeira>=60 && recursos.pedra>=50 && recursos.habitantes>=5);

}
void contruirMuralha(struct recursos_jogadores * recursos)
{
 (*recursos).madeira = (*recursos).madeira -120;	
 (*recursos).pedra = (*recursos).pedra -120;
 (*recursos).construindoMuralha = 35;	
}
bool podeConstruirMuralha(struct recursos_jogadores recursos)
{//120 madeira 120 pedras 35 turnos
  return (recursos.madeira >= 120 && recursos.pedra >=120  && recursos.habitantes>=5);

}
void construirTemplo(struct recursos_jogadores * recursos)
{
  (*recursos).madeira = (*recursos).madeira -50;	
  (*recursos).pedra = (*recursos).pedra -50;
  (*recursos).construindoTemplo = 15 ;	
}
bool podeConstruirTemplo(struct recursos_jogadores recursos)
{//50 madeiras e pedras e  15 turnos
  return (recursos.madeira>=50 && recursos.pedra >= 50  && recursos.habitantes>=5);
}
int calculoTempoGasto (clock_t inicio)
{
  clock_t atual;
  atual = clock ();
  double segundos;
  segundos = (double) (atual - inicio) / (double) CLOCKS_PER_SEC;
  return segundos / 60;
}
bool numeroParticipantescorreto(int numeroJogadores)
{
	if (numeroJogadores <= 1)
	{
	printf( "Deve jogar mais de um jogador.\n");
	} else
	if (numeroJogadores > 100)
	{
	 printf("Numero nao pode ultrapassar de 100\n");
	}
 return (numeroJogadores >1 && numeroJogadores <100);	
}

 int main2 (void)
{
  int jogadoresRestantes = 0 ;
  int tempoJogo = 0 , tempoGasto = 0 ;
  int jogador = 0, jogadorTurno = 0;			// jogador atual
  int posicaox = 0 , posicaoy = 0;
  clock_t tempoInicial, tempoAtual;
  tempoInicial = clock ();
  int extrair =0; //quando vai extrair de recursos
  srand((unsigned)time(NULL)); //inicializar o rand para mudar conforme o tempo
  int habitantesMadeira =0 ; // quanto habitantes extraindo madeira
  int habitantesPedra  = 0 ; // quantos habitantes destinados a extrair pedra
  int habitantesAlimentos = 0 ; // quantos habitantes destinados a extrair alimentos 
  int vencedorBatalha = 0;
  int alistarSoldados = 0;
  
  
  
  do
    { 
      printf ("Digite numero jogadores:\t");
      scanf ("%i", &numeroJogadores);
    if (numeroParticipantescorreto(numeroJogadores) )
	{  system("cls"); }
    }
  while (numeroJogadores <= 1);

  
  printf ("Digite o tempo em minutos de jogo:\t");
  scanf ("%i", &tempoJogo);
  printf ("%i jogadores\n", numeroJogadores);


  //prencher o mapa com recursos
  for(posicaox=0;posicaox<20;++posicaox)
  {
	  for(posicaoy=0;posicaoy<25;++posicaoy)
	  {  // preenche as posicoes do mapa com recursos aleatorios
		  preencherMapa(&mapa[posicaox][posicaoy]);
	  }	  
  }	
  
  jogadoresRestantes = numeroJogadores;
  
  //iniciando as variaveis
  for(jogador=0;jogador<numeroJogadores;++jogador)
  {  
    inicializandoRecursos(&recursos[jogador], numeroJogadores);
    mapa [recursos[jogador].posicaoxIni] [recursos[jogador].posicaoyIni].ocupadoJogador = jogador;
    recursos[jogador].numeroJogador = jogador + 1 ; // o vetor começa em zero, mas numero do jogador em 1 a 100
  }
  
  /*/ para teste
  do {
  	int pos = 9;
  	printf("digite x: ");
  	scanf("%i", &posicaox);
  	printf("\n digite y: ");
  	scanf("%i", &posicaoy);  
	  printf(" %i %i ", posicaox,posicaoy);	
   ocuparPosicao(&recursos[0],posicaox,posicaoy,pos);
  }
   while ( 1==1);
   */
  
 
  
  while ((jogadoresRestantes > 1) && (tempoJogo > tempoGasto))
    { 	 printf ("\nResta %i jogador \n",jogadoresRestantes);
      //loop da vez dos jogadores 
      // jogador = jogador da vez
      for (jogador = 0; jogador < numeroJogadores; ++jogador)
	    { 
        if (recursos[jogador].foraJogo == 0 ) {continue;} // jogador fora -passa a vez para proximo jogador
            printf ("\n Jogador %i: \t",jogador+1);
	    	mostrarRecursos(recursos[jogador]);
		
		  int opcao;
		  do{
		   
			
			printf ("\n Digite a opcao de jogo: \n");
			printf ("1 - Coletar\n");
			printf ("2 - Construir\n");
			printf ("3 - Alistar habitante ( soldados) \n");
			printf ("4 - Mover para posicao\n");
			printf ("5 - Convocar soldado para Guerra\t");
			scanf ("%i", &opcao);
			system("cls"); }
			while (opcao <1 || opcao >5);
		  switch (opcao)
		  {
			case 1: //coletar 
			  do{
			  system("cls"); 
			  printf ("Jogador %i . O que Coletar :\n",jogador+1);
			  printf ("1 - Madeira\n");
			  printf ("2 - Pedra\n");
			  printf ("3 - Alimento\n");
			  printf ("4 - Multiplas\t");
			  scanf ("%i", &opcao);}
			  while (opcao <1 || opcao >4);
			   
			   //recursos serao extraido 1 para cada 10 habitantes
			   
			  if (opcao == 4)
			  {
			  	do {
			  		system("cls"); 
				  	printf("\n Voce tem %i habitantes. como voce vai dividir as tarefas \n",recursos[jogador].habitantes);
				  	printf("Quantos hab extrair madeira:");
				  	scanf("%i",&habitantesMadeira);
				  	printf("\nQuantos hab extrair pedra:");
				  	scanf("%i",&habitantesPedra);
				  	printf("\nQuantos hab extrair alimentos:");
				  	scanf("%i",&habitantesAlimentos);
					
					}  // verificar se o numero de habitantes total que vao coletar está correto
				while (habitantesMadeira+habitantesPedra+habitantesAlimentos != recursos[jogador].habitantes);	
								  			  	
			  }
			  else
			  {
			  	 habitantesMadeira = recursos[jogador].habitantes;
			  	 habitantesPedra = recursos[jogador].habitantes;
			  	 habitantesAlimentos = recursos[jogador].habitantes;
			  }
			  //extrair madeira ou multiplas coletas
 			  if (opcao ==1 || opcao == 4 )
 			  { extrair = (10*habitantesMadeira); // quanto vai coletar 1/10 habitantes
				 
				 	 // verificacao se no mapa tem os recursos senao passa para proximas posicoes ate completar ou 
				 	 // varrer todo as posicoes do jogador
					 for(posicaox=0;posicaox<20 && extrair > 0;++posicaox)
					  {   
						  for(posicaoy=0;posicaoy<25 && extrair > 0;++posicaoy)
						  { 
							  if ( mapa[posicaox][posicaoy].ocupadoJogador == jogador) //COLETAR SOMENTE recursos/POSICAO EM SUA POSSE
								{
									extrair = baixarRecursosMadeira(&mapa[posicaox][posicaoy],extrair);
								}
						  }	  
					  }	
				 //vai receber tudo que puder extrair de suas terras desconsiderando o que não conseguiu extrair
				 // pois varreu todas suas posicoes, mas nao completou tudo que poderia extrair	  
				 recursos[jogador].madeira=recursos[jogador].madeira+ (10*habitantesMadeira)- extrair;
			   }
			   //extraindo pedra ou multipla extracao
			  if (opcao == 2 || opcao == 4)
			  {
			  	extrair = (10*habitantesPedra); // quanto vai coletar 1/10 habitantes
					 for(posicaox=0;posicaox<=20 && extrair > 0;++posicaox)
					  {
						  for(posicaoy=0;posicaoy<=25 && extrair > 0;++posicaoy)
						  { 
							  if ( mapa[posicaox][posicaoy].ocupadoJogador == jogador) //COLETAR SOMENTE recursos/POSICAO EM SUA POSSE
								{
									extrair = baixarRecursosPedra(&mapa[posicaox][posicaoy],extrair);
								}
						  }	  
					  }				
					 recursos[jogador].pedra = recursos[jogador].pedra +(10*habitantesPedra)-extrair;
			   } 
			   // extraindo recursos alimentos
			    //recursos ilimitados
			    if (opcao == 3 || opcao == 4 )
			    {
			    	recursos[jogador].alimento = recursos[jogador].alimento + (10*habitantesAlimentos);
				}
					
			 
			 	break; // fim switch-coletar-opcoes
			 	
			// contruir o que 
			case 2:
			   do{
			  system("cls"); 
			  printf ("Jogador %i . O que construir :\n",jogador+1);
			  printf ("1 - Casa\n");
			  printf ("2 - Quartel\n");
			  printf ("3 - Muralha\n");
			  printf( "4 - Templo\n");
			  scanf ("%i", &opcao);}
			  while (opcao <1 || opcao >4);
			  switch (opcao) 
			  {
				case 1:
				 if (podeConstruirCasa(recursos[jogador]))
				 {
				   construirCasa(&recursos[jogador]);
				   
				 }
				 else
				 {printf("Nao pode contruir casa\n");
				 } 
				break;

				case 2:
				if (recursos[jogador].quartel==1)
				{ 
				  printf("Já possui quartel");
				}
				else
				if (podeConstruirQuartel(recursos[jogador]))
				{ construirQuartel(&recursos[jogador]);}
				else
				{printf("Nao pode contruir quartel\n");}
				break;

				case 3:
				  if (podeConstruirMuralha(recursos[jogador]))
				  {
					construirTemplo(&recursos[jogador]);
				  }
				  else
				{printf("Nao pode contruir muralha\n");}
				break;

				case 4:
				  //verifica se tem recursos disponivel para construir o templo
				  if (podeConstruirTemplo(recursos[jogador]))
				  {
					construirTemplo(&recursos[jogador]);
				  }
				break;
			  }


			break;
			
			// converter para soldado na cidade (alistar)
			case 3: 
			 
			  do {
			  	printf("Numero de habitantes para alistar: ");
			  	scanf("%i",&alistarSoldados);
 				//  para ter soldado precisa ter o quartel construido
			    // e 50% total pode ser soldado
			    if ((recursos[jogador].soldadoCidade/recursos[jogador].habitantes*100 ) > 50 )
			    { 
			      printf("Nao pode alistar mais de 50 percento da populacao ");
			      opcao = 0;
				}
			    if (recursos[jogador].quartel == 1 )  
			    {
			    	recursos[jogador].soldadoCidade = recursos[jogador].soldadoCidade+ alistarSoldados;
				}
				else
				{
				  printf("sem quartel nao pode ter soldado") ;
				  break; 
				}			  	
			  }
			  while (alistarSoldados ==0);
			   
			  break;
			  
			 // mover para posicao 
			case 4: 
			  do
			  {
			  	printf("posicao x para avancar:\t");
			  	scanf("%i",&posicaox);
			  	printf("posicao y para avancar:\t");
			  	scanf("%i",&posicaoy);
			  }
			  // repetir enquanto ponto NAO EXISTE ou
			  // posicao ja foi conquistada pelo jogador ou 
			  //posicao digitada NAO E adjacente dos que o jogador possue
			  while ( ! pontoExiste(posicaox,posicaoy) || (posicaoJaConquistada(&recursos[jogador],posicaox,posicaoy)) ||  ! (posicaoAdjacente(recursos[jogador],posicaox,posicaoy)) ); 
			  
			  // ocupar posicao se nao tiver ocupado 
			  if (mapa[posicaox][posicaoy].ocupadoJogador == -1) { // nao ocupado
			  		//colocando na fila de arrays, na ultima posicao
					recursos[jogador].posicoes[recursos[jogador].posicoesConquistada].posicaox = posicaox; // adicionando a posicao lista de posicoes conquistadas
				  	recursos[jogador].posicoes[recursos[jogador].posicoesConquistada].posicaoy = posicaoy; //
			  		++recursos[jogador].posicoesConquistada;  //posicoes conquistada
		  			mapa[posicaox][posicaoy].ocupadoJogador = jogador;
	    		}
	    		else
				{	//batalha de quem moveu para posição - ataque contra que tem a posse da posição na cidade
					vencedorBatalha = batalhaPosicao(recursos[jogador],recursos[mapa[posicaox][posicaoy].ocupadoJogador ]);
					mapa[posicaox][posicaoy].ocupadoJogador  = vencedorBatalha-1; //no vetor começa com zero numero jogador começa com 1
					printf(" posicao (%i, %i) vencida na batalha pelo jogador %i",posicaox,posicaoy,vencedorBatalha);
					}	
			break; //fim do mover-posicao
			case 5 :
				do{
					printf("Numero de soldados guerra:");
					scanf("%i",&alistarSoldados);
					// somente pode ir para guerra soldados ja alistados (soldados na cidade)
					if (recursos[jogador].soldadoCidade == 0  || recursos[jogador].soldadoCidade >= alistarSoldados)
					{
						printf("Soldados alistados insuficientes");
						alistarSoldados = 0;
					}
					else
					{
						recursos[jogador].soldadoGuerra = recursos[jogador].soldadoGuerra + alistarSoldados;
					}
				}
				while (alistarSoldados == 0);	
			 break; //fim convocar para guerra
		  }
		   
 			//processar no final de cada turno e verifica se terminou de construir algo de algum jogador
        for(jogadorTurno=0;jogadorTurno<numeroJogadores;++jogadorTurno)
        { //se tiver fora do jogo , nem checa 
          if (recursos[jogadorTurno].foraJogo == 0 ) {continue;} 
           contruindo(&recursos[jogadorTurno] );//verifica se tem tem algo construindo
		  //verifica se tem alimento no estoque de cada jogador, se não houver diminui um habitante
          // caso tenha nasce mais um		  
          if (recursos[jogadorTurno].alimento <= 0 )
		   {
		    --recursos[jogadorTurno].habitantes;
		  } 
		  else // há alimentos
		  {  int habitantesCidade ;
		     habitantesCidade = recursos[jogadorTurno].habitantes - recursos[jogadorTurno].soldadoGuerra;
		    //perde 1 alimento para cada habitante na cidade
		  	 recursos[jogadorTurno].alimento = recursos[jogadorTurno].alimento - habitantesCidade;
		  	 //perde 2 alimentos para cada soldado em guerra
		  	 recursos[jogadorTurno].alimento = recursos[jogadorTurno].alimento - 2*recursos[jogadorTurno].soldadoGuerra; 
		  	 // só vai aumentar os habitanes se tiver alimento e casa, bolsa familia nao conta
		  	 if (recursos[jogadorTurno].casas >0 ){
		  	 	++recursos[jogadorTurno].habitantes;
			   }
		  	 
		  }
		   //perdeu habitante e ficou sem, sai do jogo
           if (recursos[jogadorTurno].habitantes == 0 ){
           	recursos[jogadorTurno].foraJogo = 0 ; //fora de jogo
           	--jogadoresRestantes;  //menos um no jogo
           	 printf ("\nResta %i jogador :",jogadoresRestantes);
		   }
         }
       
       
	    }	//fim-for

    }	//fim-while  


    // saiu do jogo teve um ganhador
    if (jogadoresRestantes == 1 )
	{
		for(jogador=0;jogador<numeroJogadores;++jogador)
	    {
			if (recursos[jogador].foraJogo == 1 ) // o unico que ficou dentro do jogo
			{
				printf("\n vencedor jogador %i \n ",jogador+1);
				break;
			}	
		}
    }
    else 
	if  (jogadoresRestantes == 0 )
	{ printf("Todo mundo morreu de fome");
	}
    else
    { //ve quem tem maior quantidade de habitantes
        int ganhador ;
        int maiorHabitantes;
         maiorHabitantes =0;
    	for(jogador=0;jogador<numeroJogadores;++jogador)
    	{ 
		 if (recursos[jogador].habitantes > maiorHabitantes ) 
		 { maiorHabitantes = recursos[jogador].habitantes;
		 }
		}
		printf("Ganhador(es) :");
		for(jogador=0;jogador<numeroJogadores;++jogador)
    	{
    	 if (recursos[jogador].habitantes == maiorHabitantes)
    	 { 
    	   	printf("jogador %i .",jogador);
		  }
		}
		
	}
	
   return 0;
}
