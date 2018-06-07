# NLTK Natural Language Toolkit
NLTK는 자연어 처리 패키지로 교육용으로 개발된 자연어 처리 및 문서 분석용 파이썬 패키지
아래와 같은 기능 제공 
- corpus (말뭉치)
- 토큰 생성
- 형태소 분석
- 품사 태깅

## corpus (말뭉치)
말뭉치(corpus)는 자연어 분석 작업을 위해 만든 샘플 문서 집합을 말한다. 단순히 소설, 신문 등의 문서를 모아놓은 것도 있지만 품사. 형태소, 등의 보조적 의미를 추가하고 쉬운 분석을 위해 구조적인 형태로 정리해 놓은 것을 포함한다. NLTK 패키지의 corpus 서브패키지에서는 다양한 연구용 말뭉치를 제공한다. 이 목록은 전체 corpus의 일부일 뿐이다. 말뭉치 자료는 설치시에 제공되지 않고 download 명령으로 사용자가 다운로드 받아야 한다.
```
import nltk

nltk.download('averaged_perceptron_tagger')
nltk.download("gutenberg")
nltk.download('punkt')
nltk.download('reuters')
nltk.download("stopwords")
nltk.download("webtext")
nltk.download("wordnet")
```
## 토큰 생성
자연어 문서를 분석하기 위해서는 우선 긴 문자열을 분석을 위한 작은 단위로 나누어야 한다. 이 문자열 단위를 토큰(token)이라고 하고 이렇게 문자열을 토큰으로 나누는 작업을 토큰 생성(tokenizing)이라고 한다. 영문의 경우에는 문장, 단어 등을 토큰으로 사용하거나 정규 표현식을 쓸 수 있다.
문자열을 토큰으로 분리하는 함수를 토큰 생성 함수(tokenizer)라고 한다. 토큰 생성 함수는 문자열을 입력받아 토큰 문자열의 리스트를 출력한다.

### word_tokenize를 이용한 토큰 생성
```
from nltk.tokenize import sent_tokenize
print(sent_tokenize(emma_raw[:1000])[3])
```
```
Sixteen years had Miss Taylor been in Mr. Woodhouse's family,
less as a governess than a friend, very fond of both daughters,
but particularly of Emma.
```
sent_tokenize 함수는 nltk.tokenize.punkt 모듈의 PunktSentenceTokenizer 인스턴스를 사용해서 문장의 시작과 끝을 구분한다. 이미 다수의 유럽 언어에서 검증이 되었다.\
sent_tokenize() 에 사용된 인스턴스는 사실 pickle 파일의 요청에 의해 로딩된다. 그러므로 다수의 문장을 분해할려면 PunktSentenceTokenizer 클래스를 한 번 로딩해서 tokenzie() 메소드를 호출하는게 더 효율적이다. 
```
para = "Hello World. It's good to see you. Thanks for buying this book."
import nltk.data
tokenizer = nltk.data.load('tokenizers/punkt/PY3/english.pickle')
tokenizer.tokenize(para)
```
```
['Hello World.', "It's good to see you.", 'Thanks for buying this book.']
```
### word_tokenize를 이용한 토큰 생성
word_tokenize는 space 단위와 구두점(punctuation)을 기준으로 토큰화(Tokenize)한다.
python
```
from nltk.tokenize import word_tokenize
word_tokenize(emma_raw[50:100])
```
```
["Emma", "Woodhouse", ",", "handsome", ",", "clever", ",", "and", "rich", ",", "with", "a"]
```

### RegexpTokenizer를 이용한 토큰 생성
python
```
from nltk.tokenize import RegexpTokenizer
t = RegexpTokenizer("[\w]+")
result = t.tokenize(emma_raw[50:100])
print(json.dumps(result))
```
```
["Emma", "Woodhouse", "handsome", "clever", "and", "rich", "with", "a"]
```
## 형태소 분석
형태소(morpheme)는 언어학에서 일정한 의미가 있는 가장 작은 말의 단위를 뜻한다. 보통 자연어 처리에서는 토큰으로 형태소를 이용한다. 형태소 분석(morphological analysis)이란 단어로부터 어근, 접두사, 접미사, 품사 등 다양한 언어적 속성을 파악하고 이를 이용하여 형태소를 찾아내거나 처리하는 작업이다. 형태소 분석은 아래와 같은 기능이 있다.

- 어간 추출(stemming)
- 원형 복원(lemmatizing)
- 품사 부착(Part-Of-Speech tagging)

### 어간 추출(stemming)
어간 추출(stemming)은 여러가지 이유로 변화된 단어의 접미사나 어미를 제거하여 같은 의미를 가지는 형태소의 실제 형태를 동일하게 만드는 방법이다. NLTK는 PorterStemmer LancasterStemmer 등을 제공한다. 자세한 어간 추출 알고리즘은 다음 웹사이트를 참고한다.\
http://snowball.tartarus.org/algorithms/porter/stemmer.html
#### PorterStemmer
```
words = ['lives', 'dies', 'flies', 'died']
from nltk.stem import PorterStemmer
st = PorterStemmer()
print [st.stem(w) for w in words]
```
```
[u'live', u'die', u'fli', u'die']
```
#### LancasterStemmer
```
words = ['lives', 'dies', 'flies', 'died']
from nltk.stem import LancasterStemmer
st = LancasterStemmer()
print [st.stem(w) for w in words]
```
```
['liv', 'die', 'fli', 'died']
```
### 원형복원(lemmatizing)
```
print("##원형 복원 lemmatizing")
from nltk.stem import WordNetLemmatizer
lm = WordNetLemmatizer()
print [lm.lemmatize(w) for w in words]
print("##원형 복원 lemmatizing, pos 입력")
print lm.lemmatize("lives", pos="v")
print lm.lemmatize("died", pos="v")
```
```
##원형 복원 lemmatizing
[u'life', u'dy', u'fly', 'died']
##원형 복원 lemmatizing, pos 입력
live
die
```
## POS tagging
품사(POS, part-of-speech)는 낱말을 문법적인 기능이나 형태, 뜻에 따라 구분한 것이다. 품사의 구분은 언어마다 그리고 학자마다 다르다. 예를 들어 NLTK에서는 펜 트리뱅크 태그세트(Penn Treebank Tagset)라는 것을 이용한다. 다음은 펜 트리뱅크 태그세트에서 사용하는 품사의 예이다.
- NN 명사(단수형 혹은 집합형)
- PRP 인칭대명사
- CD 서수
- DT 관형사
- VBP 동사 현재형
국내 태그세트로는 "21세기 세종계획 품사 태그세트"를 비롯하여 다양한 품사 태그세트가 있다. 세종계획 품사 태그세트의 자세한 내용은 "(21세기 세종계획)국어 기초자료 구축" 보고서의 "어절 분석 표지 표준안"을 참조한다.
```
from nltk.tag import pos_tag
tagged_list = pos_tag(words)
print tagged_list
```
```
[('lives', 'NNS'), ('dies', 'VBZ'), ('flies', 'NNS'), ('died', 'VBD')]
```
tag를 없애기
```
from nltk.tag import untag
untag(tagged_list)
```
tag에 /추가
```
def tokenizer(doc):
	return ["/".join(p) for p in pos_tag(doc)]
print tokenizer(words)
```
```
['lives/NNS', 'dies/VBZ', 'flies/NNS', 'died/VBD']
```
