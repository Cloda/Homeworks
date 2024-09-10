from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),										#  ссылка на домашнюю
    path('subjects/', views.subjects, name='subjects'),							#  ссылка на предметы
    path('subjects/<int:subject>/<int:variant>/', views.task, name='task'),     #  ссылка на вариант
    path('create/', views.chooseSub, name='chooseSub'),                         #  выбор предмета варианта
    path('create/<int:sub>/', views.create, name='create'),                     #  создание варианта
    path('result/', views.result, name='result'),
    path('result/send/', views.send, name='send'),                              #  отправка результатов
]

