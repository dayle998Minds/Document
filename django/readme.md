
# django 설치
### 환경 구성
```
$ sudo apt-get install python3
$ sudo pip install virtualenv
```
### virtualenv 활성화
django를 위한 가상 환경 추가
```
$ virtualenv ENV
```
가상 환경 활성화
```
$ source ENV/bin/activate
```
### virtualenv 에서 django rpm 설치
```
(ENV) david@david-ubuntu:~/work/django/helloapp$ pip install django
```
### 프로젝트 생성
django-admin startproject 프로젝트이름
```
(ENV) david@david-ubuntu:~/work/django$ django-admin startproject simpleProject
(ENV) david@david-ubuntu:~/work/django$ cd simpleProject/
(ENV) david@david-ubuntu:~/work/django/simpleProject$ tree
.
├── manage.py
└── simpleProject
    ├── __init__.py
    ├── settings.py
    ├── urls.py
    └── wsgi.py

1 directory, 5 files

```

### 프로젝트 기본 설정 변경
$ vi helloapp/settings.py
```
(ENV) david@david-ubuntu:~/work/django/simpleProject$ vi simpleProject/settings.py 
...
TIME_ZONE = 'Asia/Seoul'


```

### App 생성
$ python manage.py startapp appMain
```
$ python manage.py startapp appMain
(ENV) david@david-ubuntu:~/work/django/simpleProject$ tree
.
├── appMain
│   ├── admin.py
│   ├── apps.py
│   ├── __init__.py
│   ├── migrations
│   │   └── __init__.py
│   ├── models.py
│   ├── tests.py
│   └── views.py
├── manage.py
└── simpleProject
    ├── __init__.py
    ├── __pycache__
    │   ├── __init__.cpython-35.pyc
    │   └── settings.cpython-35.pyc
    ├── settings.py
    ├── urls.py
    └── wsgi.py

4 directories, 14 files

```
### 생성된 App을 프로젝트에 추가
```
$ vi simpleProject/settings.py 
INSTALLED_APPS = [
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    'appMain',
]
```
### Migrations
```
$ python manage.py migrate
```

### homepage를 App으로 변경
```
# vi simpleProject/urls.py 
from django.contrib import admin
from django.urls import path
from django.conf.urls import url, include

urlpatterns = [
    path('admin/', admin.site.urls),
    url(r'^', include('appMain.urls')),
]

```
## App의 View 생성
```
$ vi appMain/views.p
from django.shortcuts import render
from django.views.generic import TemplateView

class HomePageView(TemplateView):
    def get(self, request, **kwargs):
        return render(request, 'index.html', context=None)
```
### App의 index.html 생성
```
$ mkdir -p appMain/templates
$ vi appMain/templates/index.html

<!-- appMain/templates/index.html -->
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Howdy!</title>
    </head>
    <body>
        <h1>Hello Django!</h1>
    </body>
</html>
```
### App의 urls 생성
```
$vi appMain/urls.py
from django.conf.urls import url
from appMain import views

urlpatterns = [
    url(r'^$', views.HomePageView.as_view()),
]
```
### 실행
```
$ python manage.py runserver
```

## about.html 추가
### index.html에 about href추가
```
$ vi appMain/templates/index.html
<!-- appMain/templates/index.html -->
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Howdy!</title>
    </head>
    <body>
        <h1>Hello Django!</h1>
        <a href="/about/">About Me</a>
    </body>
</html>

```
### App의 views에 about view 추가
```
$ vi appMain/views.py
from django.shortcuts import render
from django.views.generic import TemplateView

class HomePageView(TemplateView):
    def get(self, request, **kwargs):
        return render(request, 'index.html', context=None)

# Add this view
class AboutPageView(TemplateView):
    template_name = "about.html"

```
### App의 urls에 about 추가
```
$ vi appMain/urls.py 
from django.conf.urls import url
from appMain import views

urlpatterns = [
    url(r'^$', views.HomePageView.as_view()),
    url(r'^about/$', views.AboutPageView.as_view()), # Add this /about/ route
]

```

### about.html 추가
```
$ vi appMain/templates/about.html
<!-- appMain/templates/about.html -->
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Howdy!</title>
    </head>
    <body>
        <h1>Welcome to the about page</h1>
    <p>
        this page is about page
    </p>
    <a href="/">Go back home</a>
    </body>
</html>

```
### 실행
```
$ python manage.py runserver
```
## db 연동
### 사용할 DB선택
```
$ vi simpleProject/settings.py 

DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.sqlite3',
        'NAME': os.path.join(BASE_DIR, 'db.sqlite3'),
    }
}
```
### db 생성
```
$ python manage.py migrate
Operations to perform:
  Apply all migrations: admin, auth, contenttypes, sessions
Running migrations:
  Applying contenttypes.0001_initial... OK
  Applying auth.0001_initial... OK
  Applying admin.0001_initial... OK
  Applying admin.0002_logentry_remove_auto_add... OK
  Applying contenttypes.0002_remove_content_type_name... OK
  Applying auth.0002_alter_permission_name_max_length... OK
  Applying auth.0003_alter_user_email_max_length... OK
  Applying auth.0004_alter_user_username_opts... OK
  Applying auth.0005_alter_user_last_login_null... OK
  Applying auth.0006_require_contenttypes_0002... OK
  Applying auth.0007_alter_validators_add_error_messages... OK
  Applying auth.0008_alter_user_username_max_length... OK
  Applying auth.0009_alter_user_last_name_max_length... OK
  Applying sessions.0001_initial... OK
(ENV) david@david-ubuntu:~/work/django/simpleProject$ ll
total 60
drwxrwxr-x 4 david david  4096  7월 19 16:04 ./
drwxrwxr-x 7 david david  4096  7월 18 17:44 ../
drwxrwxr-x 5 david david  4096  7월 19 15:48 appMain/
-rw-r--r-- 1 david david 38912  7월 19 16:04 db.sqlite3
-rwxrwxr-x 1 david david   545  7월 18 17:44 manage.py*
drwxrwxr-x 3 david david  4096  7월 19 16:02 simpleProject/

```
### super user 생성
```
$ python manage.py createsuperuser
Username (leave blank to use 'david'): admin
Email address:         
Password: admin1234 
Password (again):admin1234 
Superuser created successfully.
```
아래와 같이 접속 하면 admin화면으로 접근이 됩니다.\
http://127.0.0.1:8000/admin/
## refs
<https://scotch.io/tutorials/build-your-first-python-and-django-application>
<https://tutorial.djangogirls.org/ko/django_models>
<https://javafa.gitbooks.io/python-django/content/chapter3.html>