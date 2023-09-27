### Project Setup

1. Install LLVM
2. Add to your .zshrc or .bashrc: \

```bash
export BOOM_C_COMPILER=/opt/homebrew/Cellar/llvm/16.0.6/bin/clang
export BOOM_CXX_COMPILER=/opt/homebrew/Cellar/llvm/16.0.6/bin/clang++
export BOOM_CLANGD_PATH=/opt/homebrew/Cellar/llvm/16.0.6/bin/clangd
export BOOM_LLVM_DIR=/opt/homebrew/Cellar/llvm/16.0.6
```

3. Open VSCode and run ```all: Build [debug]``` task