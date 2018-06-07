# -*- coding: utf-8 -*- 
import json
import nltk
print("## gutenberg ccorpus에 포함된 샘플 출력")

result = nltk.corpus.gutenberg.fileids()
print(result)

print("##제인 오스틴의 엠마 문서 살펴보기")
emma_raw = nltk.corpus.gutenberg.raw("austen-emma.txt")
##print emma_raw

print( "##토큰 생성")
from nltk.tokenize import sent_tokenize
print(sent_tokenize(emma_raw[:1000])[3])

print("##word단위로 token 자르기")
from nltk.tokenize import word_tokenize
result = word_tokenize(emma_raw[50:100])
print(json.dumps(result))

print("## 이쁘게 정리")
from nltk.tokenize import RegexpTokenizer
t = RegexpTokenizer("[\w]+")
result = t.tokenize(emma_raw[50:100])
print(json.dumps(result))

##
## 형태소 분석
##
print("##어간 추출 stemming")
words = ['lives', 'dies', 'flies', 'died']
from nltk.stem import PorterStemmer
st = PorterStemmer()
print [st.stem(w) for w in words]

print("##어간 추출 LancasterStemmer 이용")
words = ['lives', 'dies', 'flies', 'died']
from nltk.stem import LancasterStemmer
st = LancasterStemmer()
print [st.stem(w) for w in words]

print("##원형 복원 lemmatizing")
from nltk.stem import WordNetLemmatizer
lm = WordNetLemmatizer()
print [lm.lemmatize(w) for w in words]
print("##원형 복원 lemmatizing, pos 입력")
print lm.lemmatize("lives", pos="v")
print lm.lemmatize("died", pos="v")
##
## POS tagging
##
print("##postag");
from nltk.tag import pos_tag
words = ['lives', 'dies', 'flies', 'died']
tagged_list = pos_tag(words)
print tagged_list
print("##postag + /");
def tokenizer(doc):
	return ["/".join(p) for p in pos_tag(doc)]
print tokenizer(words)