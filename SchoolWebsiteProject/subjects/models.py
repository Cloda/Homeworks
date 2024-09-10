from django.db import models


class Level(models.Model):
	'''модель для предметов'''
	level = models.CharField(max_length = 100, verbose_name = 'Предметы')


	def __str__(self):
		#  название для столбца
		return self.level


	class Meta:
		verbose_name = 'Предмет'
		verbose_name_plural = 'Предметы'


class Math(models.Model):
	"""модель для математики"""
	numberVariant = models.CharField(max_length = 100, verbose_name='Название варианта')
	task1 = models.TextField(verbose_name='Задание 1', default="", blank=True)
	answ1 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task2 = models.TextField(verbose_name='Задание 2', default="", blank=True)
	answ2 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task3 = models.TextField(verbose_name='Задание 3', default="", blank=True)
	answ3 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task4 = models.TextField(verbose_name='Задание 4', default="", blank=True)
	answ4 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task5 = models.TextField(verbose_name='Задание 5', default="", blank=True)
	answ5 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task6 = models.TextField(verbose_name='Задание 6', default="", blank=True)
	answ6 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task7 = models.TextField(verbose_name='Задание 7', default="", blank=True)
	answ7 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task8 = models.TextField(verbose_name='Задание 8', default="", blank=True)
	answ8 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task9 = models.TextField(verbose_name='Задание 9', default="", blank=True)
	answ9 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task10 = models.TextField(verbose_name='Задание 10', default="", blank=True)
	answ10 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task11 = models.TextField(verbose_name='Задание 11', default="", blank=True)
	answ11 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task12 = models.TextField(verbose_name='Задание 12', default="", blank=True)
	answ12 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task13 = models.TextField(verbose_name='Задание 13', default="", blank=True)
	answ13 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task14 = models.TextField(verbose_name='Задание 14', default="", blank=True)
	answ14 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task15 = models.TextField(verbose_name='Задание 15', default="", blank=True)
	answ15 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task16 = models.TextField(verbose_name='Задание 16', default="", blank=True)
	answ16 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task17 = models.TextField(verbose_name='Задание 17', default="", blank=True)
	answ17 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task18 = models.TextField(verbose_name='Задание 18', default="", blank=True)
	answ18 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task19 = models.TextField(verbose_name='Задание 19', default="", blank=True)
	answ19 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)

	def __str__(self):
		#  название для столбца
		return self.numberVariant


	class Meta:
		verbose_name = 'Математика'
		verbose_name_plural = 'Математика'


class Russia(models.Model):
	"""модель для русский язык"""
	numberVariant = models.CharField(max_length = 100, verbose_name='Название варианта')
	task1 = models.TextField(verbose_name='Задание', default="", blank=True)
	answ1 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task2 = models.TextField(verbose_name='Задание 2', default="", blank=True)
	answ2 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task3 = models.TextField(verbose_name='Задание 3', default="", blank=True)
	answ3 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task4 = models.TextField(verbose_name='Задание 4', default="", blank=True)
	answ4 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task5 = models.TextField(verbose_name='Задание 5', default="", blank=True)
	answ5 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task6 = models.TextField(verbose_name='Задание 6', default="", blank=True)
	answ6 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task7 = models.TextField(verbose_name='Задание 7', default="", blank=True)
	answ7 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task8 = models.TextField(verbose_name='Задание 8', default="", blank=True)
	answ8 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task9 = models.TextField(verbose_name='Задание 9', default="", blank=True)
	answ9 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task10 = models.TextField(verbose_name='Задание 10', default="", blank=True)
	answ10 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task11 = models.TextField(verbose_name='Задание 11', default="", blank=True)
	answ11 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task12 = models.TextField(verbose_name='Задание 12', default="", blank=True)
	answ12 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task13 = models.TextField(verbose_name='Задание 13', default="", blank=True)
	answ13 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task14 = models.TextField(verbose_name='Задание 14', default="", blank=True)
	answ14 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task15 = models.TextField(verbose_name='Задание 15', default="", blank=True)
	answ15 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task16 = models.TextField(verbose_name='Задание 16', default="", blank=True)
	answ16 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task17 = models.TextField(verbose_name='Задание 17', default="", blank=True)
	answ17 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task18 = models.TextField(verbose_name='Задание 18', default="", blank=True)
	answ18 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task19 = models.TextField(verbose_name='Задание 19', default="", blank=True)
	answ19 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task20 = models.TextField(verbose_name='Задание 20', default="", blank=True)
	answ20 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task21 = models.TextField(verbose_name='Задание 21', default="", blank=True)
	answ21 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task22 = models.TextField(verbose_name='Задание 22', default="", blank=True)
	answ22 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task23 = models.TextField(verbose_name='Задание 23', default="", blank=True)
	answ23 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task24 = models.TextField(verbose_name='Задание 24', default="", blank=True)
	answ24 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task25 = models.TextField(verbose_name='Задание 25', default="", blank=True)
	answ25 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task26 = models.TextField(verbose_name='Задание 26', default="", blank=True)
	answ26 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task27 = models.TextField(verbose_name='Задание 27', default="", blank=True)
	answ27 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	
	
	def __str__(self):
		#  название для столбца
		return self.numberVariant
	

	class Meta:
		verbose_name = 'Русский язык'
		verbose_name_plural = 'Русский язык'


class Social(models.Model):
	"""модель для обществознание"""
	numberVariant = models.CharField(max_length = 100, verbose_name='Название варианта', default="")
	task1 = models.TextField(verbose_name='Задание', default="", blank=True)
	answ1 = models.TextField(verbose_name='Ответ', default="", blank=True)
	task2 = models.TextField(verbose_name='Задание 2', default="", blank=True)
	answ2 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task3 = models.TextField(verbose_name='Задание 3', default="", blank=True)
	answ3 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task4 = models.TextField(verbose_name='Задание 4', default="", blank=True)
	answ4 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task5 = models.TextField(verbose_name='Задание 5', default="", blank=True)
	answ5 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task6 = models.TextField(verbose_name='Задание 6', default="", blank=True)
	answ6 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task7 = models.TextField(verbose_name='Задание 7', default="", blank=True)
	answ7 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task8 = models.TextField(verbose_name='Задание 8', default="", blank=True)
	answ8 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task9 = models.TextField(verbose_name='Задание 9', default="", blank=True)
	answ9 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task10 = models.TextField(verbose_name='Задание 10', default="", blank=True)
	answ10 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task11 = models.TextField(verbose_name='Задание 11', default="", blank=True)
	answ11 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task12 = models.TextField(verbose_name='Задание 12', default="", blank=True)
	answ12 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task13 = models.TextField(verbose_name='Задание 13', default="", blank=True)
	answ13 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task14 = models.TextField(verbose_name='Задание 14', default="", blank=True)
	answ14 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task15 = models.TextField(verbose_name='Задание 15', default="", blank=True)
	answ15 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task16 = models.TextField(verbose_name='Задание 16', default="", blank=True)
	answ16 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task17 = models.TextField(verbose_name='Задание 17', default="", blank=True)
	answ17 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task18 = models.TextField(verbose_name='Задание 18', default="", blank=True)
	answ18 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task19 = models.TextField(verbose_name='Задание 19', default="", blank=True)
	answ19 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task20 = models.TextField(verbose_name='Задание 20', default="", blank=True)
	answ20 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task21 = models.TextField(verbose_name='Задание 21', default="", blank=True)
	answ21 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task22 = models.TextField(verbose_name='Задание 22', default="", blank=True)
	answ22 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task23 = models.TextField(verbose_name='Задание 23', default="", blank=True)
	answ23 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task24 = models.TextField(verbose_name='Задание 24', default="", blank=True)
	answ24 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task25 = models.TextField(verbose_name='Задание 25', default="", blank=True)
	answ25 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task26 = models.TextField(verbose_name='Задание 26', default="", blank=True)
	answ26 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task27 = models.TextField(verbose_name='Задание 27', default="", blank=True)
	answ27 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task28 = models.TextField(verbose_name='Задание 28', default="", blank=True)
	answ28 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)
	task29 = models.TextField(verbose_name='Задание 29', default="", blank=True)
	answ29 = models.CharField(max_length = 100, verbose_name='Ответ', default="", blank=True)

	
	
	def __str__(self):
		#  название для столбца
		return self.numberVariant

	
	class Meta:
		verbose_name = 'Обществознание'
		verbose_name_plural = 'Обществознание'










