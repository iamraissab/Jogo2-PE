#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

// Inclui bibliotecas específicas para controlar o tempo de exibição de texto
#include <unistd.h> // Para usar usleep no Linux/macOS
#include <windows.h> // Sleep no Windows

void digitar(const char *texto, int velocidade) {

    for (int i = 0; texto[i] != '\0'; i++) {
        printf("%c", texto[i]);
        fflush(stdout); // serve para forçar a exibição imediata do que está no buffer de saída, ela garante que o que você mandou imprimir com printf() apareça na tela na hora.
        #ifdef _WIN32
            Sleep(velocidade); // Windows: milissegundos
        #else
            usleep(velocidade * 1000); // Linux/macOS: microssegundos
        #endif
    }

}


void inicio() {

    printf("\n=== Exterminando Ex ===\n");
    printf("1. Novo Jogo\n");
    printf("2. Continuar\n");
    printf("3. Ranking\n");
    printf("4. Creditos\n");
    printf("0. Sair\n");

}

void mostrarStatus(Personagem *p) {

    printf("\n=== STATUS DO JOGADOR ===\n");
    printf("Nome: %s\n", p->nome);
    printf("Vida: %d\n", p->vida);
    printf("Energia: %d\n", p->energia);
    printf("Pontuacao: %d\n", p->pontuacao);
    printf("Alinhamento: %s\n", p->alinhamento);

    printf("\nItens coletados:\n");

    int temItem = 0;
    if (p->itens[0]) { printf("- Guitarra\n"); temItem = 1; }
    if (p->itens[1]) { printf("- Skate\n"); temItem = 1; }
    if (p->itens[2]) { printf("- Notebook\n"); temItem = 1; }
    if (!temItem) printf("- Nenhum item coletado ainda.\n");

    printf("\nQuests concluidas:\n");

    if (p->quests[0]) {
        printf("- Enfrentou Maria na pista de skate\n");
    } 
    else {
        printf("- Nenhuma quest concluida ainda.\n");
    }

}


void criar(Personagem *p) {

    printf("\n=== Criacao de Personagem ===\n");

    printf("Digite o nome do seu personagem: ");
    fgets(p->nome, 50, stdin);
    p->nome[strcspn(p->nome, "\n")] = '\0';

    printf("Digite o nome da sua amada: ");
    fgets(p->amada, 50, stdin);
    p->amada[strcspn(p->amada, "\n")] = '\0';

    int pontos = 10;
    printf("Distribua 10 pontos entre os atributos:\n");
    printf("Forca: "); scanf("%d", &p->forca); pontos -= p->forca;
    printf("Inteligencia: "); scanf("%d", &p->inteligencia); pontos -= p->inteligencia;
    printf("Sabedoria: "); scanf("%d", &p->sabedoria); pontos -= p->sabedoria;
    printf("Carisma: "); scanf("%d", &p->carisma); pontos -= p->carisma;

    if (pontos < 0) {
        printf("Voce gastou mais do que podia! Atributos serao aleatorios.\n");
        int pontos = 10;
        p->forca = rand() % (pontos + 1); // de 0 a 10
        pontos -= p->forca;

        p->inteligencia = rand() % (pontos + 1); // de 0 ao que sobrou
        pontos -= p->inteligencia;

        p->sabedoria = rand() % (pontos + 1);
        pontos -= p->sabedoria;

        p->carisma = pontos; // o que sobrou vai pra carisma
    }


    p->vida = 100;
    p->energia = 100;
    p->magia = 50;
    p->pontuacao = 0;
    p->alinhamento_cont = 0;
    strcpy(p->alinhamento, "neutro");
    strcpy(p->local, "Escola");

    for (int i = 0; i < 10; i++) {
        p->itens[i] = 0;
        p->quests[i] = 0;
    }

    printf("Personagem criado com sucesso!\n");

}


void grava(Personagem p) {

    FILE *f = fopen("save.dat", "wb"); // Abre arquivo binário para escrita
    if (f) {
        fwrite(&p, sizeof(Personagem), 1, f); // Escreve os dados do personagem
        fclose(f);
    }

}


void le(Personagem *p) {

    FILE *f = fopen("save.dat", "rb"); // Abre arquivo binário para leitura
    if (f) {
        fread(p, sizeof(Personagem), 1, f); // // Lê os dados do personagem
        fclose(f);
    }

}


#define MAX_RANKING 100 // Define o número máximo de registros que o ranking pode armazenar

typedef struct {
    char nome[50]; // Nome do jogador
    int pontuacao; // Pontuação obtida
} RegistroRanking;


void mostrarRankingOrdenado() {

    FILE *f = fopen("ranking.txt", "r"); // Abre o arquivo de ranking para leitura
    if (!f) {
        printf("Nenhum ranking encontrado.\n");
        return;

    }


    RegistroRanking ranking[MAX_RANKING]; // vetor para armazenar os registros
    int total = 0;

    // Leitura dos dados e armazena do vetor
    while (fscanf(f, "%s %d", ranking[total].nome, &ranking[total].pontuacao) == 2 && total < MAX_RANKING) {
        total++;
    }

    fclose(f);

    // Ordena do maior para o menor
    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (ranking[j].pontuacao > ranking[i].pontuacao) {
                RegistroRanking temp = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = temp;
            }
        }
    }

    // Exibe o ranking
    printf("\n=== RANKING DE PONTUACAO ===\n");

    for (int i = 0; i < total; i++) {
        printf("%d - %s: %d pontos\n", i + 1, ranking[i].nome, ranking[i].pontuacao);
    }

}


void listarIntegrantes() {

    printf("\n=== Integrantes do Grupo ===\n");
    printf("Eric Jesus\nLucas Aquino\nRaissa Barros\n");

}


void lerCapitulo(const char *nomeArquivo) {

    FILE *f = fopen(nomeArquivo, "r"); // abre o arquivo de texto
    if (!f) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    char linha[256];

    while (fgets(linha, sizeof(linha), f)) {
        digitar(linha, 25); // imprime com efeito de digitação
    }

    fclose(f);

}


void combate(Personagem *jogador, Personagem *inimigo) {

    int escolha;
    printf("\n=== COMBATE: %s vs %s ===\n", jogador->nome, inimigo->nome);

    // loop de combate até que um dos dois fique sem vida
    while (jogador->vida > 0 && inimigo->vida > 0) {
        // exibe os status
        printf("\n%s: Vida %d | Energia %d\n", jogador->nome, jogador->vida, jogador->energia);
        printf("%s: Vida %d\n", inimigo->nome, inimigo->vida);

        //menu de ações
        printf("\n1. Atacar\n2. Fugir\n3. Conversar\nEscolha: ");
        scanf("%d", &escolha);

        //executa a ação escolhida

        switch (escolha) {

            case 1:
                printf("Voce ataca %s!\n", inimigo->nome);
                inimigo->vida -= 10 + jogador->forca; //dano baseado na força
                jogador->alinhamento_cont -= 1; //bater resulta em um alinhamento maldoso
                atualizarAlinhamento(jogador); 
                break;

            case 2:
                printf("Voce tenta fugir, mas %s bloqueia sua saida!\n", inimigo->nome);
                jogador->alinhamento_cont += 1; //tentar fugir resulta em alinhamento bondoso
                atualizarAlinhamento(jogador);
                break;

            case 3:
                printf("Voce tenta conversar, mas %s nao quer papo!\n", inimigo->nome);
                jogador->alinhamento_cont += 3; //tentar conversar resulta em alinhamento bondoso
                jogador->pontuacao += 10; //você ganha pontuação por tentar conversar
                atualizarAlinhamento(jogador);
                break;

            default:
                printf("Acao invalida!\n");
        }

        // inimigo contra ataca se ainda estiver vivo
        if (inimigo->vida > 0) {
            printf("%s contra-ataca!\n", inimigo->nome);
            jogador->vida -= 10;
        }
    }

    // DERROTA DO JOGADOR
    if (jogador->vida <= 0) {

        //diálogos refente ao inimigo que te derrotou

        if (strcmp(inimigo->nome, "Axel") == 0) {
            digitar("\nVoce foi derrotado por Axel...\n", 30);
            digitar("Voce volta para casa, entra no banho e chora ouvindo 'November Rain' do Sweet Child o' Mine...\n", 30);
        } 
        else if (strcmp(inimigo->nome, "Maria") == 0) {
            digitar("\nVoce foi derrotado por Maria...\n", 30);
            digitar("Voce vai ate um mercadinho, compra um sorvete e assiste ao por do sol sozinho.\n", 30);
        } 
        else if (strcmp(inimigo->nome, "Daniel") == 0) {
            digitar("\nVocê foi derrotado por Daniel...\n", 30);
            digitar("Voce volta pra casa e passa a noite jogando no computador, tentando esquecer...\n", 30);
        }
        final();
    }

    // DERROTA DO INIMIGO
   if (inimigo->vida <= 0) {

    // diálogo referente ao inimigo derrotado

        if (strcmp(inimigo->nome, "Axel") == 0) {
            digitar("\nAxel: 'Droga... voce realmente lutou por ela...'\n", 30);
            digitar("Axel: 'Talvez ela precise de alguem assim. Va em frente...'\n", 30);
            strcpy(jogador->local, "Pista de Skate");
        } else if (strcmp(inimigo->nome, "Maria") == 0) {
            digitar("\nMaria: 'Ugh... voce eh mais forte do que parece.'\n", 30);
            digitar("Maria: 'Se ela te escolheu, espero que saiba andar com ela... mesmo sem skate.'\n", 30);
            strcpy(jogador->local, "Ponto de Onibus");
        } else if (strcmp(inimigo->nome, "Daniel") == 0) {
            digitar("\nDaniel: 'Erro fatal... coracao nao eh algoritmo.'\n", 30);
            digitar("Daniel: 'Boa sorte. Ela merece alguem que entenda isso.'\n", 30);
            strcpy(jogador->local, "Final");
        }


        digitar("\nVoce venceu a batalha!\n", 30);
        jogador->vida = 100; //recupera vida ao vencer
        jogador->pontuacao += 100; //ganha ponuação ao vencer


        // Drop de item baseado no inimigo derrotado
        if (strcmp(inimigo->nome, "Axel") == 0) {
            jogador->itens[0] = 1; // Guitarra
            digitar("Voce obteve uma guitarra!\n", 30);
        } 
        else if (strcmp(inimigo->nome, "Maria") == 0) {
            jogador->itens[1] = 1; // Skate
            jogador->quests[0] = 1;
            digitar("Voce obteve um skate!\n", 30);
        } 
        else if (strcmp(inimigo->nome, "Daniel") == 0) {
            jogador->itens[2] = 1; // Notebook
            digitar("Voce obteve um notebook!\n", 30);
        }

        grava(*jogador);  // salva o progresso


        // avança para o próximo capítulo

        if (strcmp(inimigo->nome, "Axel") == 0) {
            capitulo2(jogador);
        } 
        else if (strcmp(inimigo->nome, "Maria") == 0) {
            capitulo3(jogador);
        } 
        else if (strcmp(inimigo->nome, "Daniel") == 0) {
            capituloFinal(jogador);
        }
    }

}

void atualizarAlinhamento(Personagem *p) {

    if (p->alinhamento_cont >= 3) {  // jogador é considerado bondoso se o cont for 3 ou mais
        strcpy(p->alinhamento, "bondoso");
    } 
    else if (p->alinhamento_cont <= -10) { //jogador é maldoso se o cont for menor ou igual a -10
        strcpy(p->alinhamento, "maldoso");
    } 
    else {
        strcpy(p->alinhamento, "neutro"); // jogador é neutro se estiver entre os intervalos
    }

}


void capitulo1(Personagem *p) {

    Personagem axel;
    strcpy(axel.nome, "Axel");
    axel.vida = 80;
    axel.forca = 5;

    lerCapitulo("capitulo1.txt");

    digitar("\nAxel: 'Ela e eu... tinhamos algo especial. Eu escrevia musicas pra ela!'\n", 30);
    digitar("Axel: 'Mas ela dizia que eu era obcecado demais... que eu precisava amadurecer.'\n", 30);
    digitar("Axel: 'Ela terminou comigo no meio de um show. Eu toquei ate a ultima nota com lagrimas nos olhos.'\n", 30);
    digitar("Axel: 'E agora voce aparece? Nao vai ser tao facil assim!'\n", 30);

    combate(p, &axel); //inicia o combate

    atualizarAlinhamento(p); // atualiza o alinhamento


}


void capitulo2(Personagem *p) {

    Personagem maria;
    int escolha;
    strcpy(maria.nome, "Maria");
    maria.vida = 90;
    maria.forca = 6;

    printf("A briga entre voces demorou muito e %s ja foi embora para pista de skate, lugar onde ela sempre vai depois da aula\n", p->amada);

    lerCapitulo("capitulo2.txt");

    printf("\nVoce procura por %s...\n", p->amada);
    digitar("Ela esta la, sentada no meio-fio, olhando o ceu.\n", 30);
    digitar("Voce tenta se aproxima, mas antes de voce se quer chegar perto...\n", 30);
    digitar("Uma garota salta de uma pista de skate e aterrissa bem na sua frente. Eh a Maria.\n", 30);
    digitar("\nMaria: 'Ela e eu... eramos inseparaveis. Ela me ensinou a andar de skate.'\n", 30);
    digitar("Maria: 'Mas eu era competitiva demais. Queria vencer campeonatos, ser a melhor.'\n", 30);
    digitar("Maria: 'Ela dizia que eu esquecia dela quando subia no skate. E talvez fosse verdade.'\n", 30);
    digitar("Maria: 'Ela terminou comigo depois de uma queda feia. Disse que eu precisava cair pra aprender.'\n", 30);
    digitar("Maria: 'E agora voce quer o coracao dela? Vai ter que me enfrentar primeiro.'\n", 30);
    digitar("Sua amada estava entediada e ja saiu da pista de skate\n", 30);
    digitar("Voce quer lutar contra Maria mesmo assim?\n1. Sim\n2. Nao\n", 30);
    scanf("%d", &escolha);

    // jogador escolhe lutar ou não contra Maria, essa é uma quest opcional do jogo

    if(escolha == 1){
        combate(p, &maria); //inicia o combate
        p->quests[0] = 1; // marca a quest como concluída
    }

    else{
        digitar("\nVoce decide nao lutar com Maria. Talvez isso tenha um preco...\n", 30);
        grava(*p);
        capitulo3(p);

    }

    atualizarAlinhamento(p); // atualiza o alinhamento ao final do capítulo


}


void capitulo3(Personagem *p) {

    Personagem daniel;
    strcpy(daniel.nome, "Daniel");
    daniel.vida = 100;
    daniel.forca = 7;

    printf("%s nao esta mais na pista\n", p->amada);
    digitar("Alguem diz que viu ela indo para o ponto de onibus e voce vai atras\n", 30);

    lerCapitulo("capitulo3.txt");

    printf("Voce encontra %s, esperando o proximo onibus.\n", p->amada);

    digitar("Mas antes que voce consiga se aproximar, alguem te puxa pela mochila. Eh Daniel, o programador. O ultimo ex namorado.\n", 30);
    digitar("\nDaniel: 'Ela e eu... eramos como codigo limpo e bem indentado. Perfeitos.'\n", 30);
    digitar("Daniel: 'Mas eu era obcecado por logica. Tentava resolver tudo como se fosse um bug.'\n", 30);
    digitar("Daniel: 'Ela dizia que eu nao sabia lidar com sentimentos reais. Que eu tratava o amor como algoritmo.'\n", 30);
    digitar("Daniel: 'Ela me deixou com um bilhete... em pseudocodigo.'\n", 30);
    digitar("Daniel: 'Se voce quer chegar ate ela, vai ter que compilar comigo primeiro.'\n", 30);

    combate(p, &daniel); // inicia o combate
    atualizarAlinhamento(p); // atualiza o alinhamento ao final do capítulo

}


void capituloFinal(Personagem *p) {

    int escolha;

    printf("\nVoce finalmente alcanca %s no ponto de onibus.\n", p->amada);
    digitar("Ela olha para voce, surpresa, mas com um leve sorriso.\n", 30);

    int temFinalSecreto = (p->itens[0] && p->itens[1] && p->itens[2]); // verifica se o jogador tem os 3 itens para desbloquear o final secreto

    printf("\nVoce quer se declarar?\n");
    printf("1. Sim\n");
    printf("2. Nao\n");

    if (temFinalSecreto) { // se ele tiver os 3 itens, aparece a opção de final secreto
        printf("3. Usar os itens e desbloquear o final secreto\n");
    }

    printf("Escolha: ");
    scanf("%d", &escolha);

    if (escolha == 1) { // final com declaração amorosa

        digitar("\nVoce se declara com o coracao aberto.\n", 30);

        if (strcmp(p->alinhamento, "maldoso") == 0){ // se o alinhamento for maldoso, resulta em um mau final
            digitar("Voce se aproxima. Mas...\n", 30);
            digitar("Ela se afasta e diz: 'Voce venceu todos... mas nao e mais a mesma pessoa que um dia eu gostei.'\n", 30);
            digitar("Ela continua: 'Voce foi cruel demais com todos... Estou com medo de voce.'\n", 30);
            printf("%s entra no onibus e sai, sem se despedir.\n", p->amada);
            digitar("Voce se sente desolado e decide voltar para casa... Fim de Jogo\n", 30);
        } 
        
        else { // se o alinhamento for bondoso ou neutro, resulta em um bom final
            digitar("Voce se aproxima\n", 30);
            printf("%s sorri, se aproxima e te beija.\n", p->amada);
            digitar("Voces embarcam juntos no onibus. Fim de Jogo\n", 30);
        }
    } 
    
    else if (escolha == 2) { // final em que o jogador decide não se declarar
        digitar("\nVoce respira fundo, mas decide nao se declarar.\n", 30);
        digitar("Voce apenas diz: 'Foi bom te ver de novo.'\n", 30);
        digitar("Ela sorri, entra no onibus e vai embora.\n", 30);
        digitar("Meses depois, voce conta essa historia para o Daniel.\n", 30);
        digitar("Ele decide criar um jogo com sua historia.\n", 30);
        digitar("Voce nao conseguiu o seu amor dessa vez. Mas la no fundo, voce sabe que viveu algo unico. Fim de jogo.\n", 30);
    } 
    
    else if (escolha == 3 && temFinalSecreto) {
        lerCapitulo("final_secreto.txt"); //lê o final secreto do arquivo
    } 
    
    else {
        printf("Opcao invalida.\n");
    }

    recorde(*p); //salva a pontuação
    final(); // vai para o menu de fim

}


void final() {

    Personagem p;
    le(&p); // Carrega o personagem salvo
    p.vida = 100; // Restaura vida para recomeçar

    int op;

    do {

        printf("\n=== FIM DE JOGO ===\n");
        printf("1. Ver status\n2. Recomecar do ultimo ponto\n3. Sair\nEscolha: ");
        scanf("%d", &op);

        if (op == 1) {
            mostrarStatus(&p); // exibe os atributos
        } 
        
        else if (op == 2) { // retoma o jogo do ultimo salvamento

            if (strcmp(p.local, "Escola") == 0) {
                capitulo1(&p);
            } 
            
            else if (strcmp(p.local, "Pista de Skate") == 0) {
                capitulo2(&p);
            } 
            
            else if (strcmp(p.local, "Ponto de Onibus") == 0) {
                capitulo3(&p);
            } 
            
            else if (strcmp(p.local, "Final") == 0) {
                capituloFinal(&p);
            } 
            
            else {
                capitulo1(&p); // recomeço se o local estiver inválido
            }

            return; // Sai da função final() e volta para o jogo
        } 
        
        else if (op == 3) {

            printf("Obrigado por jogar!\n");
            exit(0); // encerra o jogo

        } 
        
        else {
            printf("Opcao invalida. Tente novamente.\n");
        }

    } while (op != 3);

}



void recorde(Personagem p) {

    FILE *f = fopen("ranking.txt", "a"); // abre o arquivo de ranking
    if (f) {
        fprintf(f, "%s %d\n", p.nome, p.pontuacao); // salva o nome e a pontuação
        fclose(f);
    }
    
}
