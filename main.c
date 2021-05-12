#include <stdio.h>  
#include <stdlib.h>  


#include "age.h"

 #define mu_assert(message, test) do { if (!(test)) return message; } while (0)
 #define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
  int tests_run;
 

int tests_run = 0;
 //todas as funções envolvidas retornam o tipo (static char *), e retornam o valor 0 caso todos os mu_assert e agregadores mu_run_test passem.
static char *teste_baixasMadeira (void ) {
	puts("=> testando baixa de recursos madeira") ; // saida de informa
   struct mapa mapa;
   mapa.madeira = 10;
   int saldo = 10;
   mu_assert("Erro Baixa estoque 10 de madeira, com 10 recursos no mapa ", baixarRecursosMadeira(&mapa, saldo) ==0	);
   
    mapa.madeira = 0;
    saldo = 10;
    mu_assert("Erro Baixa estoque 10 de madeira, sem recursos no mapa ", baixarRecursosMadeira(&mapa, saldo) ==0	);
    
    mapa.madeira = 20;
    saldo = 10;
    mu_assert("Erro Baixa estoque 10 de madeira, , com 20 recursos no mapa ", baixarRecursosMadeira(&mapa, saldo) ==0	);
    
    mapa.madeira = 10;
    mapa.pedra = 100;
    saldo = 20;
    mu_assert("Erro Baixa estoque 20 de madeira, , com 10 recursos no mapa ", baixarRecursosMadeira(&mapa, saldo) ==10	);
    mu_assert("Erro extracao madeira mapa tinha 10=> ficaria 0 ", mapa.madeira == 0 	);
     mu_assert("Erro extracao madeira, mas nao de pedra ", mapa.pedra == 100 	);

	    
   return 0;
}
static char *teste_baixasPedra (void ) {
	puts("=> testando baixa de recursos pedra") ; // saida de informa
   struct mapa mapa;
   mapa.pedra = 10;
   int saldo = 10;
  // 
    mu_assert("Erro Baixa estoque 10 de pedra, com 10 recursos no mapa ", baixarRecursosPedra(&mapa, saldo) ==0	);
    
    mapa.pedra = 0;
    saldo = 10;
    mu_assert("Erro Baixa estoque 10 de pedra, sem recursos no mapa ", baixarRecursosPedra(&mapa, saldo) ==0	);
    
	mapa.pedra = 20;
    saldo = 10;
    mu_assert("Erro Baixa estoque 10 de pedra, , com 20 recursos no mapa ", baixarRecursosPedra(&mapa, saldo) ==0	);
    
    mapa.pedra = 10;
    saldo = 20;
    mu_assert("Erro Baixa estoque 20 de pedra, , com 10 recursos no mapa ", baixarRecursosPedra(&mapa, saldo) ==10	);
    mu_assert("Erro extracao mapa tinha 10=> ficaria 0 ", mapa.pedra == 0 	);
	
	    
   return 0;
}
static char *teste_mapa (void )
{ puts("Testando preencher mapa");

	struct mapa mapas[1000];

	int i = 0;
	
	for (i=0;i<1000;i++)
	{
	  preencherMapa(&mapas[i]);
	  mu_assert("Erro no preenchimento do mapa", (mapas[i].madeira  >= 400 && mapas[i].madeira <= 2000));
	  mu_assert("Erro no preenchimento do mapa-pedra", (mapas[i].pedra >= 400 && mapas[i].pedra <= 2000));
	  mu_assert("Erro no preenchimento do mapa-ocupado", (mapas[i].ocupadoJogador == -1 ));
	}
  return 0;	
}
static char *teste_batalha (void)
{   puts("Testando batalhas ");

    struct recursos_jogadores ataque;
	struct recursos_jogadores defesa;
	inicializandoRecursos(&ataque,2);
	inicializandoRecursos(&defesa, 2);
	
	ataque.numeroJogador = 1;
	ataque.quartel = 0;
	ataque.soldadoCidade = 0;
	ataque.soldadoGuerra = 0 ;
	
	defesa.numeroJogador = 2;
	defesa.quartel = 0;
	defesa.soldadoCidade = 0;
	defesa.soldadoGuerra = 0;
	mu_assert("Erro batalha - vencedor defesa " , batalhaPosicao(ataque, defesa) == 2 );

	inicializandoRecursos(&ataque,2);
	inicializandoRecursos(&defesa, 2);
	
	ataque.numeroJogador = 1;
	ataque.quartel = 1;
	ataque.soldadoCidade = 0;
	ataque.soldadoGuerra = 0 ;
	
	defesa.numeroJogador = 2;
	defesa.quartel = 0;
	defesa.soldadoCidade = 0;
	defesa.soldadoGuerra = 0;
	mu_assert("Erro batalha - vencedor defesa 2 " , batalhaPosicao(ataque, defesa) == 2 );
	
	inicializandoRecursos(&ataque,2);
	inicializandoRecursos(&defesa, 2);
	
	ataque.numeroJogador = 1;
	ataque.quartel = 1;
	ataque.soldadoCidade = 0;
	ataque.soldadoGuerra = 1 ;
	
	defesa.numeroJogador = 2;
	defesa.quartel = 0;
	defesa.soldadoCidade = 0;
	defesa.soldadoGuerra = 0;
	mu_assert("Erro batalha - vencedor ataque 1 " , batalhaPosicao(ataque, defesa) == 1 );
	
	inicializandoRecursos(&ataque,2);
	inicializandoRecursos(&defesa, 2);
	
	ataque.numeroJogador = 1;
	ataque.quartel = 1;
	ataque.soldadoCidade = 0;
	ataque.soldadoGuerra = 1 ;
	
	defesa.numeroJogador = 2;
	defesa.quartel = 1;
	defesa.soldadoCidade = 1;
	defesa.soldadoGuerra = 0;
	mu_assert("Erro batalha - vencedor ataque 2" , batalhaPosicao(ataque, defesa) == 1 );
	
	inicializandoRecursos(&ataque,2);
	inicializandoRecursos(&defesa, 2);
	
	ataque.numeroJogador = 1;
	ataque.quartel = 1;
	ataque.soldadoCidade = 100;
	ataque.soldadoGuerra = 1 ;
	
	defesa.numeroJogador = 2;
	defesa.quartel = 1;
	defesa.soldadoCidade = 100;
	defesa.soldadoGuerra = 0;
	mu_assert("Erro batalha - vencedor  defesa 3" , batalhaPosicao(ataque, defesa) == 2 );		
	
	inicializandoRecursos(&ataque,2);
	inicializandoRecursos(&defesa, 2);
	
	ataque.numeroJogador = 1;
	ataque.quartel = 1;
	ataque.soldadoCidade = 100;
	ataque.soldadoGuerra = 100 ;
	
	defesa.numeroJogador = 2;
	defesa.quartel = 1;
	defesa.soldadoCidade = 100;
	defesa.soldadoGuerra = 0;
	mu_assert("Erro batalha - vencedor ataque 3 " , batalhaPosicao(ataque, defesa) == 1 );	

	inicializandoRecursos(&ataque,2);
	inicializandoRecursos(&defesa, 2);
	
	ataque.numeroJogador = 1;
	ataque.quartel = 1;
	ataque.soldadoCidade = 100;
	ataque.soldadoGuerra = 20 ;
	
	defesa.numeroJogador = 2;
	defesa.quartel = 1;
	defesa.soldadoCidade = 15;
	defesa.soldadoGuerra = 15;
	defesa.templo = 1;
	mu_assert("Erro batalha - vencedor defesa 4 " , batalhaPosicao(ataque, defesa) == 2 );	

	inicializandoRecursos(&ataque,2);
	inicializandoRecursos(&defesa, 2);
	
	ataque.numeroJogador = 1;
	ataque.quartel = 1;
	ataque.soldadoCidade = 100;
	ataque.soldadoGuerra = 22 ;
	
	defesa.numeroJogador = 2;
	defesa.quartel = 1;
	defesa.soldadoCidade = 15;
	defesa.soldadoGuerra = 15;
	defesa.templo = 1;
	mu_assert("Erro batalha - vencedor defesa 5 " , batalhaPosicao(ataque, defesa) == 2 );	
	
	inicializandoRecursos(&ataque,2);
	inicializandoRecursos(&defesa, 2);
	
	ataque.numeroJogador = 1;
	ataque.quartel = 1;
	ataque.soldadoCidade = 100;
	ataque.soldadoGuerra = 22 ;
	
	defesa.numeroJogador = 2;
	defesa.quartel = 1;
	defesa.soldadoCidade = 15;
	defesa.soldadoGuerra = 15;
	defesa.muralha = 1;
	mu_assert("Erro batalha - vencedor defesa 6 " , batalhaPosicao(ataque, defesa) == 2 );	
				
	return 0;
}
static char *teste_posicaoAdjacente (void) 
{
	puts("Testando adjacente ");
	struct recursos_jogadores recursos;
	//posicaoAdjacente(struct recursos_jogadores recursos, int x, int y)
	
	recursos.posicoesConquistada = 1;
	recursos.posicoes[0].posicaox = 6;
	recursos.posicoes[0].posicaoy = 2;
	
	mu_assert(" erro na posicao adjacente 1", posicaoAdjacente(recursos,6,1)); // e adjacente
	
	recursos.posicoesConquistada = 1;
	recursos.posicoes[0].posicaox = 9;
	recursos.posicoes[0].posicaoy = 2;
	
	mu_assert(" erro na posicao adjacente 2", !posicaoAdjacente(recursos,6,1)); // nao e adjacente

	recursos.posicoesConquistada = 3;
	recursos.posicoes[0].posicaox = 9;
	recursos.posicoes[0].posicaoy = 2;

	recursos.posicoes[1].posicaox = 5;
	recursos.posicoes[1].posicaoy = 2;
	
	recursos.posicoes[2].posicaox = 6;
	recursos.posicoes[2].posicaoy = 2;	
	
	mu_assert(" erro na posicao adjacente 3", posicaoAdjacente(recursos,6,1)); //e adjacente

	recursos.posicoesConquistada = 3;
	recursos.posicoes[0].posicaox = 9;
	recursos.posicoes[0].posicaoy = 2;

	recursos.posicoes[1].posicaox = 5;
	recursos.posicoes[1].posicaoy = 2;
	
	recursos.posicoes[2].posicaox = 6;
	recursos.posicoes[2].posicaoy = 2;	
	
	mu_assert(" erro na posicao adjacente 4", !posicaoAdjacente(recursos,3,2));	//  nao e adjacente		
	

	recursos.posicoesConquistada = 3;
	recursos.posicoes[0].posicaox = 9;
	recursos.posicoes[0].posicaoy = 12;

	recursos.posicoes[1].posicaox = 3;
	recursos.posicoes[1].posicaoy = 2;
	
	recursos.posicoes[2].posicaox = 6;
	recursos.posicoes[2].posicaoy = 2;	
	
	mu_assert(" erro na posicao adjacente 5", posicaoAdjacente(recursos,6,3));	// e adjacente		

	recursos.posicoesConquistada = 3;
	recursos.posicoes[0].posicaox = 9;
	recursos.posicoes[0].posicaoy = 12;

	recursos.posicoes[1].posicaox = 3;
	recursos.posicoes[1].posicaoy = 2;
	
	recursos.posicoes[2].posicaox = 6;
	recursos.posicoes[2].posicaoy = 2;	
	
	mu_assert(" erro na posicao adjacente 5", !posicaoAdjacente(recursos,6,4));	//nao e adjacente
			
	return 0;	
}
static char *teste_posicaoJaConquistada (void)
{
	puts("testando posicao ja conquistada ");
	struct recursos_jogadores recursos;

	recursos.posicoesConquistada = 1;
	recursos.posicoes[0].posicaox = 6;
	recursos.posicoes[0].posicaoy = 2;
	//nao conquistou 
	mu_assert(" erro na posicao conquista 1", ! posicaoJaConquistada(&recursos,6,1));

	recursos.posicoesConquistada = 1;
	recursos.posicoes[0].posicaox = 6;
	recursos.posicoes[0].posicaoy = 1;
	// conquistou 
	mu_assert(" erro na posicao conquista 2",  posicaoJaConquistada(&recursos,6,1));

	inicializandoRecursos(&recursos,2);
	recursos.posicoesConquistada = 3;
	recursos.posicoes[0].posicaox = 9;
	recursos.posicoes[0].posicaoy = 2;

	recursos.posicoes[0].posicaox = 5;
	recursos.posicoes[0].posicaoy = 2;
	
	recursos.posicoes[0].posicaox = 6;
	recursos.posicoes[0].posicaoy = 2;		
	
	mu_assert(" erro na posicao conquista 3",  posicaoJaConquistada(&recursos,6,2));

	recursos.posicoesConquistada = 3;
	recursos.posicoes[0].posicaox = 9;
	recursos.posicoes[0].posicaoy = 2;

	recursos.posicoes[0].posicaox = 5;
	recursos.posicoes[0].posicaoy = 2;
	
	recursos.posicoes[0].posicaox = 6;
	recursos.posicoes[0].posicaoy = 2;		
	
	mu_assert(" erro na posicao conquista 6",  !posicaoJaConquistada(&recursos,2,6));		
	return 0;
	
}
static char *teste_posicaoMapaExiste(void)
{ puts ("testando posicao existe no mapa");
  	mu_assert("Erro funcao pontoExiste 1",	pontoExiste(0,0));
	mu_assert("Erro funcao pontoExiste 2",	! pontoExiste(20,25));
  return 0;
}
static char *teste_ocuparPosicao (void)
{
	puts("testando ocupar posicao");
	struct recursos_jogadores recursos;
	//ocuparPosicao (struct recursos_jogadores *recursos, int x,int y,int posicoes)
	
	recursos.numeroJogador = 1;
	recursos.posicoesConquistada = 1;
	recursos.posicoes[0].posicaox = 6;
	recursos.posicoes[0].posicaoy = 2;	
	
}
static char *testes(void) {
	//geste agrupados
    mu_run_test(teste_baixasMadeira);
    mu_run_test(teste_baixasPedra);
    mu_run_test(teste_mapa);
    mu_run_test(teste_batalha);
    mu_run_test(teste_posicaoAdjacente);
    mu_run_test(teste_posicaoJaConquistada);
    mu_run_test(teste_posicaoMapaExiste);
    
    return 0;
}

int main(int argc, char *argv[])  {
    char *saida;
   
   // fflush(stdin);
    saida = testes();

    if(0!=saida) {
        puts(saida);
        return EXIT_FAILURE;
    }

    puts("TESTES EXECUTADOS COM SUCESSO");
    printf("Testes executados: %d\n", tests_run);

    return EXIT_SUCCESS;
}


