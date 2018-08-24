#Keras 케라스

## 용어 정리

### epchos(에포크)
에포크는 모의고사 1회분을 몇 번 풀어볼까 입니다. 즉 100문항의 문제들을 몇 번이나 반복해서 풀어보는 지 정하는 것입니다. 

## 명령어 정리
### 리스트의 슬라이싱
문자열과 마찬가지로 리스트에서도 슬라이싱 기법을 적용할 수 있다. 슬라이싱은 "나눈다"는 뜻이라고 했다.
```
>>> a = [1, 2, 3, 4, 5]
>>> a[0:2]
[1, 2]
>>> a[:2]
[1, 2]
>>> a[2:]
[3, 4, 5]
```
### np.random.seed
난수의 시작점을 설정하는 함수

### MNIST 데이터셋
TensorFlow를 이용해서 머신러닝을 공부하거나, 어떤 머신러닝 알고리즘을 설계했을때 알고리즘을 검증하기 위해서 가장 먼저 적용해보는 데이터셋은 MNIST 데이터셋이다.\
MNIST 데이터셋 다음에는 보통 CIFAR-10 데이터셋을 검증에 사용한다. 
### CIFAR-10 데이터셋
CIFAR-10 데이터셋은 아래와 같이 총 10개의 레이블로 이루어진 이미지 분류를 위한 데이셋으로
`airplane, automobile, bird, cat, deer, dog, frog, horse, ship, and truck.`
각각의 레이블마다 32×32 크기 이미지인 50,000개의 training 데이터셋, 10,000개의 test 데이터셋이 존재하고, 결과적으로 총 60,000개의 32×32 크기의 이미지로 데이터셋이 구성되어 있다.
### load_data()
```
...
from keras.datasets import cifar10
...
# the data, shuffled and split between train and test sets
(X_train, y_train), (X_test, y_test) = cifar10.load_data()
```
keras에서 cifar10을 학습하려면 먼저 cifar10의 database 파일을 다운받아야 합니다. 이를 위해 상기한 바와 같이 db 다운에 필요한 lib를 import 합니다.\
처음 keras를 설치할 때, keras의 설치 위치는 미리 설정된 어떤 디폴트 설치 위치 아래에서의 keras이고 그 아래에 필요한 lib들이 설치 됩니다. 설정된 이 위치는 /usr/local/lib/python2.7/dist-packages입니다. 

여기서 dist-는 배포(distribution) 패키지의 의미로 이 폴더 아래에 들어가 보면
python과 관련하여 그동안 설치한 다양한 패키지(numpy, pandas, Theano, sklearn, ...) 들의 폴더가 있습니다.
따라서 keras의 설치 위치도 여기이며
/usr/local/lib/python2.7/dist-packages/keras 처럼 됩니다.
이 위치를 찾아 keras 폴더에 들어가면 다시 datasets라는 폴더가 있고(즉, 위 코드에서 from keras.datasets 임) 다시 그 밑에 cifar10.py 파일(import cifar10 임)이 있습니다.

### reshape()
텐서의 배열 차원을 변경시켜 주는 함수 있습니다.
reshape 함수를 통해 784 * 1 = 784 즉 1차원 이미지 데이터로 만들어 줍니다.

### to_categorical()
클래스 벡터(정수들)를 바이너리 클래스 매트릭스로 변환한다.
```
keras.utils.np_utils.to_categorical(y, num_classes=None)
y: 매트릭스로 변환될 클래스 백터(정수는 0~num_classes)
num_classes: 총 클래스 수
출력 :입력값에 대한 바이너리 행렬
```

### Sequential
Keras에서 레이어(Layer)들을 구성하는 방법으로 사용되는 핵심적인 자료구조형은 모델(Model)입니다. 그 중에서도 가장 간단한 형태의 모델은 레이어들을 선형으로 쌓는 Sequential Model 입니다.
### model.add() 
입력층 은닉층, 출력층을 생성할 때 사용하는 메소드이다.
### Dense()
Dense는 조밀하게 모여있는 집합 이라는 뜻이다.  각 층이 어떤 특징을 가질지 옵션을 설정하는 역할을 한다.
```
modal.compile(loss ='', optimizer='', metrics =[''])
activation : 다음 층으로 어떻게 값을 넘길지를 결정하는 부분이다. 주로 'relu'와 'sigmoid'가 사용된다.
loss : 한 번 신경망이 실행될 때마다 오차값을 추적하는 함수이다.
optimizer : 오차를 어떻게 줄려 나갈지 정하는 함수이다.
```
### modle.evaluate()
앞서 만든 딥러닝의 모델이 어느 정도 정확하게 예측되는지 를 점검할 수 있게 해주는 함수.
Keras 를 이용한 학습 모델이 테스트셋을 기준으로 얼마만큼 예측성능률을 가지고 잇는지 평가해 보자.
평가는 evaluate() 함수를 이용한다.
결과로 loss와 정확도가 리턴된다.
```
loss_and_metrics = model.evaluate(X_test, Y_test, batch_size=32)

print('')
print('loss : ' + str(loss_and_metrics[0]))
print('accuray : ' + str(loss_and_metrics[1]))
```
### compile() 
모델을 학습 시키기전에, 학습과정을 정의해야 한다. 그 과정은 compile함수를 호출함으로서 완성된다. compile() 함수는 세가지의 인자를 가진다.
```
model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
loss : 현재 가중치 세트를 평가하는 데 사용한 손실 함수 입니다. 다중 클래스 문제이므로 ‘categorical_crossentropy’으로 지정합니다.
optimizer : 최적의 가중치를 검색하는 데 사용되는 최적화 알고리즘으로 효율적인 경사 하강법 알고리즘 중 하나인 ‘adam’을 사용합니다.
metrics : 평가 척도를 나타내며 분류 문제에서는 일반적으로 ‘accuracy’으로 지정합니다.
```
### fit()
모델 설정이 완료되면, .fit()을 통해 모델에 직접 학습데이터(Train Data)를 넣어 학습 시킬 수 있습니다.
### fit_generator()
ImageDataGenerator 객체를 사용하였기 때문에 fit_generator 함수를 통해 fitting한다. steps_per_epoch은 한 번 epoch 돌 때, 데이터를 몇 번 볼 것인가를 정해준다. [트레이닝데이터수/배치사이즈]를 사용하면 되는듯하다. validation_steps는 한 번 epoch 돌 고난 후, validation set을 통해 validation accuracy를 측정할 때 validation set을 몇 번 볼 것인지를 정해준다. 이 때도 마찬가지로 [validation data수/배치사이즈]를 사용하면 된다. 즉 ImageDataGenerator를 쓴 경우, fit_generator를 사용하면 된다고 기억하면 된다. 폴더 구조는 아래와 같이 하면 된다. flow_from_directory에 넣어준 경로(dataset/training_set) 밑에 이런식으로 class(cats, dogs) 별로 폴더를 만들고 폴더 밑에 이미지들을 넣어준다. 그러면 알아서 labeling을 하게 된다. 
```
model.fit_generator(
        train_generator,
        steps_per_epoch=15,
        epochs=50,
        validation_data=test_generator,
        validation_steps=5)
첫번째 인자 : 훈련데이터셋을 제공할 제네레이터를 지정합니다. 본 예제에서는 앞서 생성한 train_generator으로 지정합니다.
steps_per_epoch : 한 epoch에 사용한 스텝 수를 지정합니다. 총 45개의 훈련 샘플이 있고 배치사이즈가 3이므로 15 스텝으로 지정합니다.
epochs : 전체 훈련 데이터셋에 대해 학습 반복 횟수를 지정합니다. 100번을 반복적으로 학습시켜 보겠습니다.
validation_data : 검증데이터셋을 제공할 제네레이터를 지정합니다. 본 예제에서는 앞서 생성한 validation_generator으로 지정합니다.
validation_steps : 한 epoch 종료 시 마다 검증할 때 사용되는 검증 스텝 수를 지정합니다. 홍 15개의 검증 샘플이 있고 배치사이즈가 3이므로 5 스텝으로 지정합니다.
```
### hist
Keras에서는 모델 학습을 위해 fit() 함수를 사용합니다. 이 때, 리턴값으로 학습 이력(History) 정보를 리턴합니다. 여기에는 다음과 같은 항목들이 포함되어 있습니다.

아래 항목들은 매 epoch 마다의 값들이 저장되어 있습니다.
```
loss : 훈련 손실값
acc : 훈련 정확도
val_loss : 검증 손실값
val_acc : 검증 정확도
```
### predict and predict_classes
predict는 nn을 이용한 계산된 값이고 predict_classes는 분류된값(classification)이다.
```
predict 의 경우
[[0.22520512]
 [0.9520419 ]
 [0.9672848 ]
 [0.02690617]]

predict_classes 의 경우
[[0]
 [1]
 [1]
 [0]]
```
### model.save()
학습된 모델 저장하기
```
from keras.models import load_model
model.save('mnist_mlp_model.h5')
```
저장된 파일에는 다음의 정보가 담겨 있습니다.
- 나중에 모델을 재구성하기 위한 모델의 구성 정보
- 모델를 구성하는 각 뉴런들의 가중치
- 손실함수, 최적하기 등의 학습 설정
- 재학습을 할 수 있도록 마지막 학습 상태

### model_to_dot
모델 아키텍처 보기
model_to_dat() 함수를 통해 모델 아키텍처를 가시화 시킬 수 있습니다. model 객체를 생성한 뒤라면 언제든지 아래 코드를 호출하여 모델 아키텍처를 블록 형태로 볼 수 있습니다.

### load_model
학습된 모델 불러오기
‘mnist_mlp_model.h5’에는 모델 아키텍처와 학습된 모델 가중치가 저장되어 있으니, 이를 불러와서 사용해봅니다. 코드 흐름은 다음과 같습니다.

모델 불러오는 함수를 이용하여 앞서 저장한 모델 파일로부터 모델을 재형성합니다.
실제 데이터로 모델을 사용합니다. 이 때 주로 사용되는 함수가 predict() 함수이지만 Sequential 기반의 분류 모델을 사용할 경우 좀 더 편리하게 사용할 수 있도록 predict_classes() 함수를 제공합니다. 이 함수를 이용하면 가장 확률이 높은 클래스 인덱스를 알려줍니다.

## Reference
https://tykimos.github.io/lecture/
