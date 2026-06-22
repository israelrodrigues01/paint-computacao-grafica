# 🎨 Paint Computação Gráfica

Projeto acadêmico desenvolvido em C utilizando OpenGL para a disciplina de Computação Gráfica.

O objetivo do projeto é criar um mini Paint com funcionalidades básicas de desenho, como:

- Pontos
- Linhas
- Quadrados
- Polígonos
- Seleção e transformações geométricas
- Animação
- Interação com mouse e teclado

---

# 👥 Equipe

Projeto desenvolvido em grupo.

---

# 📁 Estrutura do Projeto

```text
paint-computacao-grafica/
│
├── src/
│   ├── main.c
│   ├── render.c
│   ├── input.c
│   ├── paint.c
│   ├── selection.c
│   ├── file.c
│   ├── transformacoes.c
│   ├── globals.h
│   ├── paint.h
│   ├── selection.h
│   ├── structs.h
│   ├── transformacoes.h
│   └── file.h
│
├── Makefile
├── drawing.txt
└── README.md
```

---

# 🚀 Clonando o Projeto

## Via HTTPS

```bash
git clone https://github.com/israelrodrigues01/paint-computacao-grafica.git
```

---

## Via SSH

```bash
git clone git@github.com:israelrodrigues01/paint-computacao-grafica.git
```

---

# 📦 Requisitos

Antes de executar o projeto, você precisa instalar:

- GCC
- OpenGL
- GLUT/FreeGLUT
- Make

---

# 🪟 Instalação no Windows (WSL recomendado)

## 1. Instalar WSL

Abra o PowerShell como administrador:

```powershell
wsl --install
```

Reinicie o computador.

---

## 2. Instalar Ubuntu

Abra a Microsoft Store e instale:

- Ubuntu 22.04 LTS

---

## 3. Atualizar o sistema

Abra o Ubuntu e execute:

```bash
sudo apt update && sudo apt upgrade -y
```

---

## 4. Instalar compilador e bibliotecas

```bash
sudo apt install build-essential freeglut3-dev libglew-dev mesa-utils make -y
```

---

## 5. Verificar OpenGL

```bash
glxinfo | grep OpenGL
```

Se aparecer informações da GPU/OpenGL, está funcionando.

---

# 🐧 Instalação no Linux (Ubuntu/Debian)

## Atualizar pacotes

```bash
sudo apt update && sudo apt upgrade -y
```

---

## Instalar dependências

```bash
sudo apt install build-essential freeglut3-dev libglew-dev mesa-utils make -y
```

---

# 🐧 Fedora

```bash
sudo dnf install gcc freeglut-devel glew-devel mesa-demos make
```

---

# 🐧 Arch Linux

```bash
sudo pacman -S gcc freeglut glew mesa-demos make
```

---

# 📥 Entrando no Projeto

```bash
cd paint-computacao-grafica
```

---

# ⚙️ Compilando o Projeto

## Utilizando Makefile

```bash
make
```

---

# ▶️ Executando

```bash
./app
```

ou:

```bash
make run
```

---

# 🧹 Limpando Arquivos Compilados

```bash
make clean
```

---

# 🧠 Conceitos Utilizados

O projeto utiliza:

- OpenGL Legacy
- GLUT
- Computação gráfica 2D
- Eventos de teclado
- Eventos de mouse
- Renderização de primitivas
- Matrizes de transformação (translação, rotação, escala, reflexão, cisalhamento)
- Algoritmos de seleção (ponto, linha e área)

---

# 🎮 Controles

## Ferramentas de desenho

| Tecla | Função |
|---|---|
| P | ferramenta ponto |
| L | ferramenta linha |
| Q | ferramenta quadrado |
| G | ferramenta polígono (clique para adicionar vértices, ENTER para fechar) |
| X | entra no modo seleção |
| C | carregar desenho salvo (e entra em modo seleção) |
| W | salvar desenho |
| Z | apaga o que foi desenhado na tela |
| Delete / Backspace | apagar shape selecionado (no modo seleção) |
| ESC | salvar e sair |

## Seleção e arrasto (modo seleção, tecla X ou C)

| Ação | Função |
|---|---|
| Clique do mouse | seleciona o shape clicado |
| Clique + arrastar | move (translada) o shape selecionado |

## Transformações geométricas (aplicadas no shape selecionado)

| Tecla | Função |
|---|---|
| R | rotaciona +5° |
| E | rotaciona -5° |
| A | aumenta escala |
| D | diminui escala |
| 0 | reflexão no eixo X |
| 1 | reflexão no eixo Y |
| 2 | cisalhamento em X (+) |
| 3 | cisalhamento em X (-) |
| 4 | cisalhamento em Y (+) |
| 5 | cisalhamento em Y (-) |
| 6 | translação para a direita |
| 7 | translação para a esquerda |
| 8 | translação para cima |
| 9 | translação para baixo |

> ⚠️ As teclas de transformação só têm efeito se houver um shape selecionado (modo seleção ativo e algum objeto clicado).

## Animação

| Ação | Função |
|---|---|
| Botão direito do mouse (segurar) | "ímã" — todos os objetos são atraídos para a posição do cursor |
| Soltar botão direito | os objetos retornam à posição original |

---

# 📚 Funções OpenGL Importantes

| Função | Objetivo |
|---|---|
| glClear | limpar tela |
| glBegin | iniciar desenho |
| glEnd | finalizar desenho |
| glVertex2f | criar vértices |
| glColor3f | definir cor |
| glutMouseFunc | capturar mouse |
| glutKeyboardFunc | capturar teclado |
| glutTimerFunc | controlar a animação |

---

# 🛠️ Tecnologias

- Linguagem C
- OpenGL
- GLUT / FreeGLUT
- GCC
- Makefile

---

# 📌 Objetivo do Projeto

Além de criar um Paint simples, o projeto busca praticar:

- Computação gráfica
- Estruturação de projetos
- Trabalho em equipe
- Organização de código
- Eventos gráficos
- Renderização em OpenGL

---

# 🌱 Próximas Funcionalidades

- Seleção de cores
- Ferramenta borracha
- Interface gráfica (toolbar com ícones)
- Zoom

---

# 🔀 Fluxo de Git Recomendado

## Atualizar repositório

```bash
git pull
```

---

## Criar branch

```bash
git checkout -b feature/nome-da-feature
```

---

## Enviar alterações

```bash
git add .
git commit -m "feat: descrição da alteração"
git push
```j