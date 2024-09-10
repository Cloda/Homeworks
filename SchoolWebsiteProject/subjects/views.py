from django.shortcuts import render
from .models import Level, Math, Russia, Social
from django.http import HttpResponseRedirect
from django.urls import reverse
from .forms import MathForm, RussiaForm, SocialForm
from django.shortcuts import redirect
from django.db.models import Q
from django.conf import settings
from django.core.mail import send_mail

def index(request):
	#  выводит главную страницу
    return render(request, 'index.html', {})


#  выводит все предметы и уровни
def subjects(request):
	#  все уровни									
	lev = Level.objects.all()				
	math = Math.objects.all().order_by('-id')[0:5]	
	rus = Russia.objects.all().order_by('-id')[0:5]	
	social = Social.objects.all().order_by('-id')[0:5]				
	return render(request, 'subjects.html', {'lev':lev, 'math':math, 'rus':rus, 'social':social})


#  выводит задания
def task(request, subject, variant):
	# функция проверки пустых значений
	def checkValue(mas):
		result = {}
		for i in range(0,len(mas)):
			if mas[i] != "":
				result[i+1] = mas[i]
		return result


	def checkValueList(mas):
		result = []
		for i in range(0,len(mas)):
			if mas[i] != "":
				result.append(mas[i])
		return result
	
	#  название предмета							
	nameSub = Level.objects.get(id=subject)    							
	# выбор заданий
	if subject == 1:
		sub = Math.objects.get(id=variant)
		Answ = [sub.task1, sub.task2, sub.task3, sub.task4,
				sub.task5, sub.task6, sub.task7, sub.task8,
				sub.task9, sub.task10, sub.task11, sub.task12,
				sub.task13, sub.task14, sub.task15, sub.task16, sub.task17,
				sub.task18, sub.task19]
		masAnsw = checkValue(Answ)
	elif subject == 2:
		sub = Russia.objects.get(id=variant)
		Answ = [sub.task1, sub.task2, sub.task3, sub.task4,
				sub.task5, sub.task6, sub.task7, sub.task8,
				sub.task9, sub.task10, sub.task11, sub.task12,
				sub.task13, sub.task14, sub.task15, sub.task16, sub.task17,
				sub.task18, sub.task19, sub.task20, sub.task21, sub.task22,
				sub.task23, sub.task24, sub.task25, sub.task26, sub.task27]
		masAnsw = checkValue(Answ)
	elif subject == 3:
		sub = Social.objects.get(id=variant)
		Answ = [sub.task1, sub.task2, sub.task3, sub.task4,
				sub.task5, sub.task6, sub.task7, sub.task8,
				sub.task9, sub.task10, sub.task11, sub.task12,
				sub.task13, sub.task14, sub.task15, sub.task16, sub.task17,
				sub.task18, sub.task19, sub.task20, sub.task21, sub.task22,
				sub.task23, sub.task24, sub.task25, sub.task26, sub.task27,
				sub.task28, sub.task29]
		masAnsw = checkValue(Answ)
	return render(request, 'task.html', {'variant':masAnsw, 'sub':nameSub, 'num':subject, 'var':variant})


def result(request):
	# функция проверки пустых значений для ответов
	def checkValueList(mas):
		result = []
		for i in range(0,len(mas)):
			if mas[i] != "":
				result.append(mas[i])
		return result

	subject = int(request.POST.get('subject'))
	variant = int(request.POST.get('variant'))

	if request.method == 'POST':
		# предметы
		if subject == 1:
			sub = Math.objects.get(id=variant)
			Answ = [sub.answ1, sub.answ2,  sub.answ3, sub.answ4,
					sub.answ5, sub.answ6, sub.answ7, sub.answ8,
					sub.answ9, sub.answ10, sub.answ11, sub.answ12,
					sub.answ13, sub.answ14, sub.answ15, sub.answ16, sub.answ17,
					sub.answ18, sub.answ19]
			masAnsw = checkValueList(Answ)
		elif subject == 2:
			sub = Russia.objects.get(id=variant)
			Answ = [sub.answ1, sub.answ2,  sub.answ3, sub.answ4,
					sub.answ5, sub.answ6, sub.answ7, sub.answ8,
					sub.answ9, sub.answ10, sub.answ11, sub.answ12,
					sub.answ13, sub.answ14, sub.answ15, sub.answ16, sub.answ17,
					sub.answ18, sub.answ19, sub.answ20, sub.answ21, sub.answ22,
					sub.answ23, sub.answ24, sub.answ25, sub.answ26, sub.answ27]
			masAnsw = checkValueList(Answ)
		elif subject == 3:
			sub = Social.objects.get(id=variant)
			Answ = [sub.answ1, sub.answ2,  sub.answ3, sub.answ4,
					sub.answ5, sub.answ6, sub.answ7, sub.answ8,
					sub.answ9, sub.answ10, sub.answ11, sub.answ12,
					sub.answ13, sub.answ14, sub.answ15, sub.answ16, sub.answ17,
					sub.answ18, sub.answ19, sub.answ20, sub.answ21, sub.answ22,
					sub.answ23, sub.answ24, sub.answ25, sub.answ26, sub.answ27,
					sub.answ28, sub.answ29]
			masAnsw = checkValueList(Answ)
		# проверка
		temp = 0
		childTemp = 0
		lol = []
		for item in request.POST:
			if item == "csrfmiddlewaretoken" or item == "variant" or item == "subject":
				continue
			k = request.POST.get(item)
			lol.append(k)
			if k == masAnsw[childTemp]:
				temp += 1
			childTemp+=1
		return render(request, 'result.html', {'res':temp, 'answ':masAnsw, 'user':lol})
	
	


def chooseSub(request):
	lev = Level.objects.all()
	temp = request.GET.get('temp')
	linkOne = request.GET.get('linkOne')
	linkTwo = request.GET.get('linkTwo')
	return render(request, 'chooseSubject.html', {'lev':lev, 'temp':temp, 'linkOne':linkOne, 'linkTwo':linkTwo})


def create(request, sub):
	if request.method == "POST":
		if sub == 1:
			form = MathForm(request.POST)
			key = Math.objects
			object_list = Math.objects.filter(numberVariant=request.POST.get('numberVariant'))
		elif sub == 2:
			form = RussiaForm(request.POST)
			key = Russia.objects
			object_list = Russia.objects.filter(numberVariant=request.POST.get('numberVariant'))
		elif sub == 3:
			form = SocialForm(request.POST)
			key = Social.objects
			object_list = Social.objects.filter(numberVariant=request.POST.get('numberVariant'))
		if form.is_valid() and len(object_list)==0:
			post = form.save(commit=False)
			post.save()
			_q = key.values('id').filter(numberVariant=request.POST.get('numberVariant')).all()[0]['id']
			return redirect('http://127.0.0.1:8000/create/?temp=True&linkOne='+str(sub)+'&linkTwo='+str(_q))

		else:
			return redirect('index')
	else:
		if sub == 1:
			form = MathForm()
		elif sub == 2:
			form = RussiaForm()
		elif sub == 3:
			form = SocialForm()

	return render(request, 'createVariant.html', {'form':form, 'title':Level.objects.get(id=sub)})


def send(request):
	if request.method == "POST":
		email = request.POST.get('email')
		name = request.POST.get('name')
		female = request.POST.get('female')
		result = request.POST.get('result')
		data = "Ученик - "+ str(name) + " " + str(female) + "Результат - " + str(result) 
		send_mail('Работа ученика', data, settings.EMAIL_HOST_USER, [email])
		return redirect("index")


