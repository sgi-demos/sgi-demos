Ghidra setup on Mac

1. Install Ghidra:
bash
brew install --cask ghidra

2. Install required dependencies:
bash
brew install gradle
# Xcode Command Line Tools (if not already installed)
xcode-select --install
# necessary so macos doesn’t think it’s malware:
xattr -r -d com.apple.quarantine /opt/homebrew/Caskroom/ghidra*

3. Launch Ghidra:
bash
/opt/homebrew/Caskroom/ghidra/12.0.2-20260129/ghidra_12.0.2_PUBLIC/ghidraRun

4. For easier access, you might want to add an alias to your shell config:
bash
echo 'alias ghidra="/opt/homebrew/Caskroom/ghidra/11.2.1-20241105/ghidra_11.2.1_PUBLIC/ghidraRun"' >> ~/.zshrc
source ~/.zshrc
Then you can just type ghidra to launch it.
