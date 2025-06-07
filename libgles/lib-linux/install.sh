
# Install VS Code
# set -x
# sudo apt-get install wget gpg
# wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
# sudo install -D -o root -g root -m 644 packages.microsoft.gpg /etc/apt/keyrings/packages.microsoft.gpg
# echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/keyrings/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" |sudo tee /etc/apt/sources.list.d/vscode.list > /dev/null
# rm -f packages.microsoft.gpg
# sudo apt update
# sudo apt install code

# Install Chromium Browser to obtain libEGL.so and libGLESv2.so
sudo apt install chromium-browser
cp /usr/lib/chromium/*.so .

