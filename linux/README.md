### google Chrome 설치

```
wget -q -O - https://dl.google.com/linux/linux_signing_key.pub | sudo apt-key add -
echo "deb [arch=amd64] http://dl.google.com/linux/chrome/deb/ stable main" | sudo tee /etc/apt/sources.list.d/google-chrome.list
sudo apt-get update
sudo apt-get -y install google-chrome-stable
sudo apt-get -y install google-chrome-beta
```

### git 설치
```
sudo apt-get install git
git config --global user.name exampleID
git config --global user.email example@email.com
git config --list
```
### git prompt 설치
```
cd ~
git clone https://github.com/magicmonty/bash-git-prompt.git .bash-git-prompt --depth=1
vi .bashrc
```
마지막줄에 추가
```
GIT_PROMPT_ONLY_IN_REPO=1
source ~/.bash-git-prompt/gitprompt.sh
```
