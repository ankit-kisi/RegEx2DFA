# RegEx2DFA

**RegEx2DFA** is a C++ project for converting regular expressions into Deterministic Finite Automata (DFA) using various algorithms and the Graphviz library for visualizing the DFA.

## Installation

To get started, follow the instructions below to install the necessary dependencies and set up the project.

### 1. Install Graphviz

#### macOS

You can install Graphviz using Homebrew:

```bash
brew install graphviz
```

#### Linux

On Debian-based systems (like Ubuntu), you can use:

```bash
sudo apt-get update
sudo apt-get install graphviz libgraphviz-dev

```

On Red Hat-based systems (like Fedora), you can use:

```bash
sudo dnf install graphviz graphviz-devel
```

On Arch Linux, you can use:

```bash
sudo pacman -S graphviz
```

#### Windows

Download the Graphviz installer from [Graphviz's official website](https://graphviz.org/download/).
Run the installer and follow the installation instructions.

**Make sure you select:**

```bash
🔘 Add Graphviz to the system PATH for current user
```

![Alt text](https://global.discourse-cdn.com/graphviz/original/1X/754680b6a7f66af5318b6deed62a3e8f5c0d34f2.png)

### 2. Verify Installation

#### macOS/Linux/Windows

To verify that Graphviz was installed correctly, you can check the version of the dot tool (which is part of Graphviz):

```bash
dot -V
```

### 3. Find the Path of Graphviz

#### macOS

The installation path is usually `/opt/homebrew/opt/graphviz`. You can confirm it by running:

```bash
brew --prefix graphviz
```

#### Linux

The installation path is usually `/usr` or `/usr/local`. You can confirm it by running:

```bash
cd /usr/include
find graphviz
```

and

```bash
cd /usr/local/include
find graphviz
```

#### Windows

The default installation path for Graphviz is usually: `"C:\Program Files\Graphviz"`.

If you selected a different path during installation, use that path instead.

![Alt text](https://global.discourse-cdn.com/graphviz/original/1X/ac7f10c21d821a1aa78b4eaf4ac253cda2b775bc.png)

### 4. Add the Path to the Makefile

Open the `Makefile` in your project directory and set the GRAPHVIZ_PATH variable to the path where Graphviz is installed.

#### macOs

```makefile
GRAPHVIZ_PATH = /opt/homebrew/opt/graphviz
```

#### Linux

```makefile
GRAPHVIZ_PATH = /usr
```

#### Windows

You should enclose the path in double quotes.

```makefile
GRAPHVIZ_PATH = "C:\Program Files\Graphviz"
```

### 4. Build the Project

#### macOS/Linux

In your terminal, navigate to the project directory and run:

```bash
make
```

#### Windows

```bash
mingw32-make
```

### 5. Run the Project

```bash
./main
```
