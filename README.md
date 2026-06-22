# 🎨 Paint Computação Gráfica

Projeto acadêmico desenvolvido em C utilizando OpenGL para a disciplina de Computação Gráfica.

O objetivo do projeto é criar um mini Paint com funcionalidades básicas de desenho, como:

- Pontos
- Linhas
- Quadrados
- Polígonos
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
│   ├── globals.h
│   ├── paint.h
│   ├── selection.h
│   ├── structs.h
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

---

# 🎮 Controles Iniciais

| Tecla | Função |
|---|---|
| P | ferramenta ponto |
| L | ferramenta linha |
| Q | ferramenta quadrado |
| G | ferramenta polígono (clique para adicionar vértices, ENTER para fechar) |
| C | carregar desenho salvo (e entra em modo seleção) |
| X | Entra no modo seleção |
| S | salvar desenho |
| Delete / Backspace | apagar shape selecionado (no modo seleção) |
| ESC | salvar e sair |

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
- Arrastar objetos
- Interface gráfica
- Salvar desenho
- Carregar desenho
- Zoom
- Múltiplos polígonos

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
```

---

# 📄 Licença

Projeto acadêmico para fins educacionais.