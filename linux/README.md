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
