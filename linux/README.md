## 자주 사용하는 리눅스 명령어
### 그래픽 카드 확인
>	```
>	lshw -C display
>   lspci -vnn | grep VGA -A 12
>	```