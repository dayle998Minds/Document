# PyTorch
## PyTorch 이란
딥러닝을 구현하는 라이브러리 중 가장 적합한 것은 텐서플로우(Tensorflow)이다. 그 이유는 오픈 소스인데다가 머신러닝, 딥러닝 알고리즘을 충족시켜주기 때문이다. 텐서플로우의 데이터 플로우 그래프 방식은 수학 계산과 데이터의 흐름을 노드(Node)와 엣지(Edge)를 사용한 방향 그래프로 표현한다. 최근 딥러닝을 구현할 수 있는 라이브러리로 주목받고 있는 것이 있는데, 그것은 바로 파이토치다. 파이토치(Pytorch)는 파이썬(Python) 기반의 오픈 소스 머신러닝 라이브러리로, 페이스북 인공지능 연구집단에 의해 개발되었다. 간결하고 구현이 빨리 되며, 텐서플로우보다 사용자가 익히기 훨씬 쉽다는 특징이 있다. 또한 코드를 직접 다른 사람들에게 설명해 주기에도 효과적이다. 텐서플로우와 파이토치의 가장 큰 차이점은 딥러닝을 구현하는 패러다임이 다르다는 것이다. 텐서플로우는 Define-and-Run 프레임워크인 반면에, 파이토치는 Define-by-Run이다. 이 패러다임의 차이로 텐서플로우의 경우 먼저 모델을 만들고 값을 다 따로 넣어주어야 해서 직관적이지 않지만, 파이토치의 경우 간단하고 직관적이다. 게다가 상대적으로 텐서플로우보다 파이토치가 학습을 따라가기가 더 쉽다.
  

### PyTorch & Tensorflow 비교
구분 | Tensorflow | Pytorch
---------|-----------|------------
패러다임 | Define and Run |Define by Run
그래프 형태 | Static graph | Dynamic graph

### Pytorch가 주목받는 이유
- 설치가 간편하다
- 이해와 디버깅이 쉬운 직관적이고 간결한 코드로 구성되었다
-  Define-by-Run 방식을 기반으로 한 실시간 결과값을 시각화한다
- 파이썬 라이브러리(Numpy, Scipy, Cython)와 높은 호환성을 가진다
- Winograd Convolution Alogithm 기본 적용을 통한 빠른 모델 훈련이 가능하다
- 모델 그래프를 만들 때 고정상태가 아니기 때문에 언제든지 데이터에 따라 조절이 가능하다(유연성 지님)
- Numpy 스러운 Tensor 연산이 GPU로도 가능하다
- Autograd System을 이용해 쉽게 DDN을 짤 수 있다
- 학습 및 추론 속도가 빠르고 다루기 쉽다
### Pytorch 내에 있는 패키지
패키지 | 기술
------|-----
torch | 강력한 GPU 지원 기능을 갖춘 Numpy와 같은 Tensor 라이브러리
torch.autograd | Torch에서 모든 차별화된 Tensor 작업을 지원하는 테이프 기반 자동 차별화 라이브러리
torch.nn | 최고의 유연성을 위해 설계된 자동 그래프와 깊이 통합된 신경 네트워크 라이브러리
torch.optim | SGD, RMSProp, LBFGS, Adam 등과 같은 표준 최적화 방법으로 torch.nn과 함께 사용되는 최적화 패키지
torch.multiprocessing | 파이썬 멀티 프로세싱을 지원하지만, 프로세스 전반에 걸쳐 Torch Tensors의 마법같은 메모리 공유 기능을 제공. 데이터 로딩 및 호그 워트 훈련에 유용.
torch.utils | 편의를 위해 DataLoader, Trainer 및 기타 유틸리티 기능
torch.legacy(.nn/optim) | 이전 버전과의 호환성을 위해 Torch에서 이식된 레거시 코드
## 설치
1. 아나콘다 설치 
https://www.anaconda.com/download/
2. PyTorch 설치
https://pytorch.org/ 접속\
운영체제와 python 버전 선택\
anaconda shell에서 실행 \
```
$ conda install pytorch-cpu -c pytorch

$ pip install msgpack

$ pip install torchvision
```
