# Exterminando Ex — Jogo de RPG em Texto (C)

Um jogo de RPG narrativo baseado em texto, desenvolvido em linguagem C, onde o jogador precisa enfrentar os ex-namorados da pessoa amada em uma série de combates por turnos, tomando decisões que moldam seu alinhamento (bondoso, neutro ou maldoso) e definem qual final ele vai receber.

## 📖 Sobre o jogo

Você cria um personagem, distribui pontos de atributos e parte em uma jornada por três capítulos, cada um culminando em um combate contra um ex-namorado diferente (Axel, Maria e Daniel). Suas escolhas durante os combates e diálogos afetam seu alinhamento moral, sua pontuação e os itens que você coleta — que juntos podem desbloquear um final secreto.

O jogo combina:
- Narrativa com efeito de digitação (texto exibido caractere por caractere)
- Sistema de combate por turnos (atacar, fugir ou conversar)
- Sistema de alinhamento moral (bondoso / neutro / maldoso), influenciado pelas ações do jogador
- Coleta de itens e quests opcionais
- Sistema de pontuação com ranking persistente
- Múltiplos finais, incluindo um final secreto
- Sistema de salvamento e retomada de progresso

## 🎮 Como jogar

Ao iniciar o jogo, você verá o menu principal:

```
=== Exterminando Ex ===
1. Novo Jogo
2. Continuar
3. Ranking
4. Creditos
0. Sair
```

- **Novo Jogo**: cria um personagem novo (nome, nome da amada, atributos) e começa a história no Capítulo 1.
- **Continuar**: carrega o progresso salvo em `save.dat` e retoma o Capítulo 1 (a partir daí, o jogo direciona automaticamente para o capítulo correspondente ao seu último local salvo, ao escolher "Recomeçar do último ponto" na tela de fim de capítulo).
- **Ranking**: exibe a pontuação de todos os jogadores salvos em `ranking.txt`, ordenada da maior para a menor.
- **Creditos**: mostra os integrantes do grupo responsável pelo desenvolvimento.
- **Sair**: encerra o jogo.

### Criação de personagem

Você distribui 10 pontos entre 4 atributos: **Força**, **Inteligência**, **Sabedoria** e **Carisma**. Se gastar mais pontos do que tem disponível, os atributos são sorteados aleatoriamente no lugar.

### Combate

Cada capítulo termina em um combate contra um ex-namorado. A cada turno você escolhe:
1. **Atacar** — causa dano baseado na sua força, mas piora seu alinhamento.
2. **Fugir** — o inimigo bloqueia a fuga, mas melhora seu alinhamento.
3. **Conversar** — não causa dano, mas melhora bastante o alinhamento e concede pontuação.

Vencer um combate recupera sua vida, concede pontuação, itens exclusivos daquele inimigo e avança para o próximo capítulo.

## 🗂️ Estrutura do projeto

```
.
├── main.c                 # Ponto de entrada do jogo (menu principal e loop)
├── funcoes.h               # Cabeçalho com os protótipos das funções
├── personagem.h             # Cabeçalho com a definição da struct Personagem
├── funcoes.c (ou similar)  # Implementação das funções do jogo
├── capitulo1.txt            # Texto narrativo do Capítulo 1
├── capitulo2.txt            # Texto narrativo do Capítulo 2
├── capitulo3.txt            # Texto narrativo do Capítulo 3
├── final_secreto.txt        # Texto do final secreto (desbloqueado com os 3 itens)
├── save.dat                 # Arquivo binário gerado ao salvar o progresso
└── ranking.txt               # Arquivo de texto com o histórico de pontuações
```

## ⚙️ Requisitos

- Compilador C (GCC/MinGW recomendado)
- O projeto inclui `<windows.h>` (para `Sleep()`) e `<unistd.h>` (para `usleep()`), com compilação condicional via `#ifdef _WIN32` — ou seja, **compila tanto em Windows quanto em Linux/macOS**, adaptando automaticamente o efeito de digitação para cada sistema.

## 🛠️ Como compilar

Se o projeto estiver dividido em múltiplos arquivos `.c`:

```bash
gcc main.c funcoes.c -o exterminando_ex.exe
```

Ou abra o projeto no **Code::Blocks** e use *Build and Run* (F9).

## 🧩 Principais mecânicas implementadas

- **Structs (`typedef struct`)** para representar o personagem (`Personagem`), incluindo atributos, itens, quests e alinhamento.
- **Ponteiros para struct** passados entre funções para manipular os dados do jogador sem duplicar memória.
- **Manipulação de arquivos**:
  - Leitura de arquivos `.txt` para exibir a narrativa de cada capítulo.
  - Leitura e escrita de arquivo binário (`fread`/`fwrite`) para salvar e carregar o progresso (`save.dat`).
  - Leitura e escrita de arquivo de texto (`fscanf`/`fprintf`) para o sistema de ranking (`ranking.txt`).
- **Compilação condicional** (`#ifdef _WIN32`) para portabilidade entre Windows e Linux/macOS.
- **Efeito de digitação** (texto aparecendo caractere por caractere) usando `Sleep()`/`usleep()`.
- **Ordenação (bubble sort)** para exibir o ranking de pontuações em ordem decrescente.
- **Sistema de combate por turnos** com múltiplas ações possíveis e impacto direto no alinhamento moral do personagem.
- **Múltiplos finais**, incluindo um final condicional (bondoso/maldoso) e um final secreto desbloqueado pela coleta de itens.

## 👥 Integrantes

- Eric Jesus
- Lucas Aquino
- Raissa Barros

## 📌 Observações

Este é um projeto acadêmico/de estudo, desenvolvido para praticar conceitos de linguagem C como structs, ponteiros, manipulação de arquivos, compilação condicional e organização de código em múltiplos arquivos-fonte.
