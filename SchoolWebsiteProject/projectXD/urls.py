from django.contrib import admin
from django.urls import path, include

urlpatterns = [
    path('admin/', admin.site.urls, name='admin'),									#  ссылка на админку
    path('', include('subjects.urls')),									#  ссылки на приложение
]
