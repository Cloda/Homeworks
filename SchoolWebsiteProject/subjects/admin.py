from django.contrib import admin
from subjects.models import Level, Math, Russia, Social
	

#  регистрация модели предметов								
admin.site.register(Level)									
#  регистрация модели математики
admin.site.register(Math)
#  регистрация модели обществознания	
admin.site.register(Social)	
#  регистрация модели русский язык
admin.site.register(Russia)	