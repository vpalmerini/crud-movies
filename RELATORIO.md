# Projeto 1 - MC833 - Programação em Redes de Computadores

### Nome

Victor Palmerini

### RA

178061

### Data

21/05/2020

## Conteúdo

[Introdução](#introdução)

[Descrição Geral](#descrição-geral)

[Estrutura do Projeto](#estrutura-do-projeto)

[Casos de Uso](#casos-de-uso)

[Rodando Localmente](#rodando-localmente)

[Armazenamento](#armazenamento)

[Estruturas de Dados](#estruturas-de-dados)

[Detalhes da Implementação](#detalhes-da-implementação)

[Limitações](#limitações)

[Conclusão](#conclusão)

[Referências](#referências)

## Introdução

Este é o Trabalho 1 da disciplina _**MC833** - Programação em Redes de Computadores_ da **Unicamp** - Universidade Estadual de Campinas.

O principal objetivo deste trabalho é desenvolver uma boa noção sobre alguns dos conceitos básicos da área de redes de computadores, como comunicação entre nós usando o protocolo TCP, serialização e deserialização de buffers, escrita e leitura em sockets, entre outros que serão descritos ao longo do relatório.

O trabalho requer por parte do aluno um conhecimento básico da linguagem de programação `C` e algumas funções nativas da linguagem para auxiliar na transmissão e recebimento de dados entre 2 nós/computadores. A implementação dessas funções será mais detalhada em breve.

## Descrição Geral

O projeto se baseia numa interação simples entre operadores de um **cinema** que precisam gerenciar de alguma forma os filmes que o cinema oferece, como _adicionar novos filmes, remover filmes antigos, listar filmes_, etc. Essa interação acontece diretamente com uma aplicação _cliente_ que se comunica com um _servidor_, que por sua vez se comunica com a base de dados.

Como já foi dito, tanto _cliente_ quanto _servidor_ foram desenvolvidos utilizando a linguagem `C` e a base de dados, por simplicidade do projeto, utiliza um arquivo binário para persistir os dados. O _servidor_, neste caso, é concorrente. Isto significa que ele pode aceitar diversas conexões ao mesmo tempo, caso se tenha vários operadores dentro do cinema utilizando a aplicação simultaneamente, por exemplo.

A ideia geral do projeto é que se consiga simular uma aplicação de um cinema real, que provavelmente utilizaria comunicação `http` dentro da `web` pela praticidade, com a comunicação levada para uma camada abaixo, a de `transporte`. Dessa forma, utilizou-se o protocolo `TCP` para realizar tal comunicação entre _cliente_ e _servidor_, bem como funcionalidades da linguagem `C` para leitura e escrita nos sockets, entre outros recursos, disponibilizados por sua API.

Em geral, num sistema de tal porte, existiria funcionalidades como autenticação, permissões de usuários e interface gráfica, por exemplo. Mas por questões de simplicidade, o projeto é focado na aplicação dos conceitos de redes de computadores e deixa esses outros aspectos implementados de forma mais simples ou até não implementados.

## Estrutura do Projeto

O projeto é dividido em 2 grandes pastas: `client` e `server`. Além destas, há também algumas pastas que contém funções e estruturas auxiliares utilizadas por `client` e `server`.

Descrevendo melhor a estrutura do projeto:

- `/bin` - pasta de saída com os binários de `client.c` e `server.c` após a compilação destes

- `/wrappers` - pasta com implementação de funções utilizadas na comunicação entre `client` e `server`

- `/serializers` - pasta com implementação das estruturas e funções de serialização e deserialização destas para facilitar a manipulação de dados, tanto do cliente quanto do servidor

- `/server` - pasta com a implementação do servidor (`server.c`) e algumas funções auxiliares para modularização de código

- `/client` - assim como no `/server`, possui a implementação do cliente (`client.c`) e algumas funções auxiliares

- `build-client.sh` e `build-server.sh` - scripts para auxiliar a compilação de todos os arquivos necessários para a compilação de `client.c` e `server.c` respectivamente

- `run-client.sh` e `run-server.sh` - scripts para executar respectivamente **cliente** e **servidor** e que usam os scripts de compilação

## Casos de Uso

Antes de descever as possíveis operações e exemplificar um fluxo possível, é interessante saber os dados que um filme pode ter na aplicação. Segue então um esqueleto da estrutura de um objeto _filme_ dentro da aplicação:

```
- id // identificador único do filme - inteiro positivo
- título // título do filme - sequência de caracteres
- gênero // gênero do filme - sequência de caracteres
- sinopse // sinopse do filme - sequência de caracteres
- salas // salas que oferecem o filme - sequência de caracteres (mais sobre isso na seção de limitações)
```

Do ponto de vista de um operador de cinema, a aplicação possui **7 operações**:

1. _Listar Filmes_

Lista todos os filmes, com seus respectivos detalhes, que estão disponíveis na base de dados.

2. _Adicionar Filme_

Adiciona um filme com os seus respectivos dados: `id`, `título`, `gênero`, `sinopse` e `salas`. Retorna o `id` do filme adicionado.

3. _Remover Filme_

Dado um identificador `id` como entrada, remove o respectivo filme.

4. _Retornar detalhes de um filme_

Dado um identificador `id` como entrada, retorna todos os detalhes do filme.

5. _Retornar o título de um filme_

Dado um identificador `id` como entrada, retorna apenas o título do respectivo filme.

6. _Listar filmes de um determinado gênero_

Dado um gênero como entrada, lista todos os filmes deste gênero com seus respectivos detalhes, que estão disponíveis na base de dados.

7. _Listar Filmes (apenas Título e Salas)_

Lista todos os filmes, porém apenas título e salas, que estão disponíveis na base de dados.

Em todas as operações que retornam algum dado (todas menos a `3`), se não houver nenhum filme na base de dados para a operação escolhida, então o cliente recebe a mensagem `Nenhum filme encontrado`.

## Rodando Localmente

A execução do projeto consiste na execução de 2 programas: `client` e `server`. Portanto, deve-se executar cada um separadamente em uma `shell` (caso esteja num sistema operacional baseado em Unix) ou no [Git Bash](https://gitforwindows.org/) por exemplo se estiver usando Windows.

> Obs1: Pode ser necessária a instalação do pacote _readline-devel_ (Red Hat) / _libreadline-dev_ (Debian) para a execução correta do _cliente_. Verifique se a máquina onde o cliente será executado possui este pacote. Caso contrário, execute:

```
// Red Hat
sudo yum install readline-devel

// Debian
sudo yum install libreadline-dev
```

> Obs2: Não necessariamente os 2 programas devem ser executados na mesma máquina.

É necessário que o `server` seja executado antes do `client`, pois este depende do _servidor_ já estar executando, já que o cliente precisa do endereço e porta do _servidor_ para conseguir realizar essa comunicação.

Para executar o `server`, entre na pasta raiz do projeto e entre com o comando:

```
./run-server.sh {porta}
```

`{porta}` é qualquer porta que se deseja executar o `server`. Em geral, qualquer porta acima de _1024_ deve funcionar (a não ser que outro processo já esteja sendo executado na mesma porta).

Um exemplo seria:

```
./run-server.sh 8000
```

Se tudo ocorrer bem, o `server` estará sendo executado como um processo e ficará esperando por um contato de 1 ou mais clientes.

Com o `server` rodando, está na hora de executar o `client`. Mas antes, é necessário saber o **endereço IP** do _servidor_. Para isso, supondo que você tenha acesso direto ao _servidor_, entre com o comando numa `shell`:

```
// Unix
ifconfig

// Windows - Git Bash
ipconfig
```

O comando deve retornar 1 ou mais endereços IPs. Em geral, se estiver em uma `LAN`, o endereço IP deve seguir um padrão mais ou menos desse tipo: `192.168.0.XX`, em que `XX` é algum inteiro.

Sabendo o endereço IP do _servidor_, temos tudo que é necessário para executar o _cliente_. Para isso, abra uma nova janela da `shell` (caso esteja na mesma máquina física do _servidor_). Na pasta raiz do projeto, entre com o comando:

```
./run-client.sh {IP} {porta}
```

`{porta}` é a porta na qual o `server` está executando e `{IP}` é o endereço IP do _servidor_. No meu caso por exemplo, seria:

```
./run-client 192.168.0.100 8000
```

Se tudo ocorrer bem, o `client` deve estar executando e já terá se comunicado com sucesso com o `server`. Em seguida, a lista de todas as operações deve aparecer na `shell` em que o `client` está sendo executado e, assim que o _cliente_ escolhe uma sequência de operações, o `server` mostra o log dessas operações selecionadas. Segue abaixo um exemplo de fluxo que pode ser seguido a fim de testar algumas funcionalidades da aplicação.

Fluxo sugerido:

1. Popule a base de dados:

```
- Selecione Operação 2.Adicionar Filme
Título: Parasita
Gênero: Drama
Sinopse: Filme que ganhou 4 Oscars
Salas: 1 2 3

// Servidor retorna
ID do filme adicionado: 1
```

```
- Selecione Operação 2.Adicionar Filme
Título: Coringa
Gênero: Drama
Sinopse: Filme que ganhou 2 Oscars
Salas: 3 4 5

// Servidor retorna
ID do filme adicionado: 2
```

```
- Selecione Operação 2.Adicionar Filme
Título: Star Wars
Gênero: Ficção Científica
Sinopse: A Ascensão SkyWalker
Salas: 9 10

// Servidor retorna
ID do filme adicionado: 3
```

2. Liste os filmes adicionados

```
- Selecione Operação 1.Listar Filmes

// Servidor retorna lista de filmes com todos os detalhes
```

3. Liste os filmes de um determinado gênero

```
- Selecione Operação 6.Listar Filmes de um gênero
Gênero: Drama

// Servidor retorna lista de filmes com gênero "Drama" e seus detalhes
```

4. Remova um filme que não está mais em cartaz

```
- Selecione Operação 3.Remover Filme
ID: 1

// Servidor não retorna nada
```

5. Liste todos os filmes (apenas título e salas)

```
- Selecione Operação 7.Listar Filmes (apenas Título e Salas)

// Servidor retorna todos os filmes (ativos) com apenas Título e Salas
```

## Armazenamento

Como já foi dito anteriomente, os dados dos filmes serão armazenados num **arquivo binário**. Quem faz a comunicação com esse arquivo (escrita e leitura de dados) é o _servidor_. Escolheu-se usar esse tipo de armazenamento devido à simplicidade e praticidade de manipulação considerando a estrutura dos dados (mais sobre isso na próxima seção).

Os filmes sempre são adicionados no modo `append` de escrita em arquivo binário, isto é, sempre adicionados ao final da "lista" de filmes.
Cada filme ocupa exatamente `4 kB (4096 bytes)` no arquivo. Então se um cinema tiver 12 filmes cadastrados, o arquivo terá tamanho `12 * 4kB = 49152 bytes`.

O arquivo não existe inicialmente, mas é criado após a 1ª operação ser escolhida, mesmo que seja uma operação de leitura. O nome do arquivo será `db.bin` e será criado no mesmo nível da pasta raiz do projeto.

## Estruturas de Dados

Neste projeto, foram utilizadas 2 estruturas principais para manipular os dados trocados entre _cliente_ e _servidor_. Estas são:

```
// packet (4kB)
int op; // operação escolhida
int movie_id;
char movie_title[256];
char movie_sinopsis[256];
char movie_genre[256];
char rooms[256];
int deleted; // 0 - filme ativo / 1 - filme removido

// response (40kB)
int n_movies; // nº de filmes
packet packets[10]; // lista de filmes
```

A definição de `packet` pode ser encontrada em `/serializers/packet.h`, a de `response` pode ser encontrada em `/serializers/response.h`.

**packet** é sempre a estrutura de dados que o _cliente_ envia para o _servidor_, e o _cliente_ sempre envia exatamente **1 packet**. Na prática, antes dos dados serem enviados, acontece uma _serialização_ da estrutura para um _buffer_. Este _buffer_ é basicamente um ponteiro de caracteres que será escrito no _socket_, no caso de envio de dados, e lido do _socket_ no caso de leitura de dados. Assim como na escrita, na leitura deve ocorrer uma _deserialização_ do _buffer_ para a estrutura adequada.

**response** é sempre a estrutura de dados que o _servidor_ envia para o _cliente_, e o _servidor_ sempre envia exatamente **1 response** como resposta à requisição. Assim como no _cliente_, no _servidor_ ocorre a deserialização do **packet** enviado pelo _cliente_ e a serialização do **response** na hora de enviar a resposta para o _cliente_.

As funções de _serialização_ e _deserialização_ foram implementadas em `/serializers`.

## Detalhes da Implementação

O foco desta seção é detalhar a implementação de `server` e `client`, isto é, explicar o fluxo de funções de cada um até o encerramento da conexão por alguma das 2 partes.

A implementação dos 2 programas pode ser encontrada em `/server/server.c` e `/client/client.c`. Ambos os programas possuem o esqueleto a seguir:

```
1. Importação de bibliotecas

2. Função main() {
    // implementação de funções específicas
}
```

#### Servidor

A primeira coisa a fazer no `server`, assim que é executado, é ler os parâmetros de entrada. No caso, temos apenas um, que é a `porta` em que o _servidor_ será executado. Este parâmetro é lido pela `shell` e convertido para inteiro. Desta maneira, mantém-se o programa genérico em relação à porta de execução do processo.

Após a leitura das entradas, o `server` cria um socket TCP usando o _wrapper_ `Socket()`, que por sua vez executa a função `socket()`. Esta cria um socket para o programa e retorna um inteiro chamado de _socket descriptor_.

Criado o _socket_, agora o `server` popula a estrutura `server_address` do tipo `sockaddr_in`. Esta estrutura terá o tipo de endereço IP utilizado (no caso IPv4), o endereço IP do _servidor_ e a porta (entrada do usuário).

Após a criação do _socket_ e preenchimento da estrutura `server_address`, o `server` faz o _bind_ do socket, isto é, dá ao socket criado o endereço definido em `server_address`.

Feito isso, agora o `server` deve começar a escutar por requisições de _clientes_. Para tal, executa a função `Listen()`, que possibilita agora que o `server` receba novos pedidos de conexões.

Até agora, todos os passos foram executados de forma síncrona e direta. Porém, a partir do próximo passo, todas as operações podem ser executadas em _loop_, de acordo com a comunicação estabelecida com os _clientes_. Assim que o `server` recebe uma nova requisição, executa a função `Accept()`, que por sua vez abre um novo _socket_ e retorna um _socket descriptor_, assim como `Socket()`.

O _servidor_ então clona o processo atual pela execução da função `fork()` e "passa" a conexão agora pra um outro _socket_ (criado por `fork()`). Dessa forma, o _servidor_ consegue lidar com múltiplas conexões simultaneamente. Com a conexão agora estabelecida por outro _socket_, o _servidor_ processa a requisição do _cliente_ e formula a resposta com os dados necessários. Esta parte é feita a partir da função `receive_data()`.

A função `receive_data()` lê o os dados do socket e armazena esses dados num _buffer_ a partir da função `read()`. Feito isso, o _servidor_ deserializa o buffer e estrutura os dados em um `packet`. A partir deste `packet`, o _servidor_ consegue identificar a operação selecionada pelo _cliente_ e os dados relacionados à esta, se necessários.

Toda a lógica de negócio então está implementada na função `receive_data()`, que depois formula a resposta pra ser enviada para o _cliente_. Esta, por sua vez, também é serializada para um _buffer_ antes de ser escrito no socket.

#### Cliente

Assim como no `server`, o `client` lê parâmetros de entrada. Neste caso, o `endereço IP` do servidor e a `porta` na qual o servidor está executando seu processo.

O passo a seguir é bem similar ao seguido pelo `server`. O `client` abre um `socket` a partir da função `Socket()` e recebe um descritor do socket aberto. Além disso, o `client` também possui uma estrutura `sockaddr_in server_address`, a qual é prenchida com o _endereço IP_ do servidor (1º parâmetro de entrada), _porta_ do servidor (2º parâmetro de entrada) e versão do protocolo IP utilizada (_IPv4_ neste caso). E por fim, ocorre a tradução do _endereço IP_ para um formato padrão de endereço IP utilizado na estrutura `sockaddr_in`, utilizando a função `Inet_pton()`.

O `client` não precisa fazer o `Bind()` do socket pois o seu endereço não é relevante para o estabelecimento da conexão. Neste caso, o SO lida com isso de forma automática.

Com todas as informações necessárias para iniciar a comunicação com o `server`, o `client` então inicia a conexão a partir da função `Connect()`. Esta função abre uma conexão a partir do socket estabelecido e informações fornecidas sobre o `server`.

Estabelecida a conexão com o `server`, o `client` agora lista todas as operações possíveis que um operador pode realizar, a partir da função `list_operations()`. O operador então deve entrar com algum número inteiro que corresponda à operação desejada. Caso se queira sair da aplicação, basta entrar com o número 0. Qualquer outro número que não corresponda a uma operação válida, o `client` retornará uma mensagem de operação inválida.

Escolhida uma operação válida, o `client` agora pode perguntar (ou não) um ou mais parâmetros relacionados à operação. Dependendo da operação (operação 1, por exemplo), não há necessidade desse passo. Caso a operação necessite de parâmetros, o `client` então pergunta parâmetro por parâmetro até que tenha todas as informações necessárias para enviar a operação para o `server`. A função `ask_params()` é a responsável por mapear a operação escolhida com as respectivas funções implementadas. São nessas funções que as regras de negócio do _cliente_ são implementadas.

Feito o fluxo de escolha da operação e entrada dos parâmetros, agora o `client` serializa os dados da estrutura `packet` e envia os dados escrevendo o _buffer_ no socket aberto para a aplicação. Este passo é implementado na função `send_data()`. Se tudo ocorrer bem, o `server` deve responder com uma estrutura `response` (que primeiro vem do socket para um buffer). O buffer então é deserializado nessa estrutura e dessa forma o `client` consegue extrair os dados necessários para processar a informação enviada pelo `server`.

O primeiro passo é verificar o número de filmes enviados. Se for 0, então o _cliente_ imprime uma mensagem de que nenhum filme foi encontrado para a operação escolhida. Se houver 1 ou mais filmes, o _cliente_ então imprime esses filmes para o operador. As informações que serão impressas dependem da operação escolhida. O `server` sempre envia todas as informações de todos os filmes que satisfazem àquela operação. Cabe ao `client` filtrar a informação que deve ser mostrada para o operador (só título ou só título e salas, por exemplo).

O `client` fica então nesse loop entre escolher uma operação, enviar as informações para o `server` e ler a resposta enviada. O mesmo ocorre com o `server`, com a diferença que este mantém um processo pra cada conexão enquanto que, se o `client` encerrar a conexão, deve estabelecê-la de novo, se quiser.

## Limitações

Por ser apenas um projeto de disciplina e validação de conceitos, a aplicação como um todo possui algumas limitações que a impede de ser usada num cenário real. Aqui são listadas algumas limitações principais e algumas das melhorias que poderiam ser feitas para melhorar ou até sanar essas limitações.

#### Nº de Filmes

Com a implementação atual, o tamanho de uma estrutura `response` é de `40kB`. Este espaço é suficiente para no máximo 10 filmes. Dependendo do tamanho do cinema, este número pode não ser suficiente. Uma melhoria seria aumentar o tamanho da estrutura `response` para que mais filmes possam ser transmitidos entre _cliente_ e _servidor_. Isto é fácil de atingir já que o protocolo TCP nos garante a entrega dos pacotes e na mesma ordem.

#### Relação Filme - Salas

Como a aplicação possui um arquivo binário como base de dados, não é possível criar relações entre entidades. Suponha o caso, por exemplo, em que se queira listar os filmes de uma determinada sala. É necessário ter um banco de dados relacional para tal operação. Neste caso consegue-se estabelecer relações entre as entidades da aplicação, o que não é possível com a implementaçao atual. Isso sem falar nas vantagens de se usar um gerenciador de banco de dados, o que nos garante atomicidade de transações, segurança, etc.

Outra limitação relacionada é a remoção de filmes. No cenário atual, a remoção de um filme se dá por uma flag `deleted`, que indica se um filme está ativo (`deleted = 0`) ou removido (`deleted = 1`). Isso também ocorre pela limitação de se usar arquivos binários como base de dados.

E por fim, uma observação importante é que o contador de IDs de filmes implementado no _servidor_ persiste apenas na memória. O que significa que se o _servidor_ cair e voltar, filmes com mesmo ID podem existir na base de dados. Isso é uma limitação da aplicação também.

## Conclusão

Como conclusão, podemos afirmar que a aplicação cumpre todos os requisitos estabelecidos pelo trabalho e que tenta, de alguma forma, ser o mais organizada e estruturada possível para simular o projeto de uma aplicação real. Esta estrutura possibilita que novas operações sejam adicionadas facilmente, tanto no _cliente_ quanto no _servidor_.

Além disso, os conceitos principais relacionados à área de redes de computadores foram colocados em prática, o que ajudou a fixá-los e a entender melhor seu funcionamento. Desta forma, qualquer novo projeto em que seja necessário implementar uma comunicação (que não seja na `web`) entre 2 ou mais computadores, pode tomar como base a implementação deste projeto.

## Referências

- _UNIX Network Programming, Volume 1, Third Edition, The Sockets Networking API_
- [Linux Programmer's Manual ](http://man7.org/linux/man-pages/index.html)
