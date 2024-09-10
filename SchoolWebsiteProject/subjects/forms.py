from django import forms

from .models import Math, Russia, Social

class MathForm(forms.ModelForm):

    class Meta:
        model = Math
        fields = ('numberVariant', 'task1', 'answ1', 'task2', 'answ2', 
                    'task3', 'answ3', 'task4', 'answ4', 'task5', 'answ5', 
                    'task6', 'answ6', 'task7', 'answ7', 'task7', 'answ7',
                    'task8', 'answ8', 'task9', 'answ9', 'task10', 'answ10', 
                    'task11', 'answ11','task12', 'answ12', 'task13', 'answ13', 
                    'task14', 'answ14', 'task15', 'answ15', 'task16', 'answ16',
                    'task17', 'answ17', 'task18', 'answ18', 'task19', 'answ19')
        widgets={"numberVariant":forms.TextInput(attrs={'class':'create-variant__input'})}


class RussiaForm(forms.ModelForm):

    class Meta:
        model = Russia
        fields = ('numberVariant', 'task1', 'answ1', 'task2', 'answ2', 
                    'task3', 'answ3', 'task4', 'answ4', 'task5', 'answ5', 
                    'task6', 'answ6', 'task7', 'answ7', 'task7', 'answ7',
                    'task8', 'answ8', 'task9', 'answ9', 'task10', 'answ10', 
                    'task11', 'answ11','task12', 'answ12', 'task13', 'answ13', 
                    'task14', 'answ14', 'task15', 'answ15', 'task16', 'answ16',
                    'task17', 'answ17', 'task18', 'answ18', 'task19', 'answ19', 
                    'task20', 'answ20', 'task21', 'answ21', 'task22', 'answ22', 
                    'task23', 'answ23', 'task24', 'answ24', 'task25', 'answ25', 
                    'task26', 'answ26', 'task27', 'answ27')
        widgets={"numberVariant":forms.TextInput(attrs={'class':'create-variant__input'})}


class SocialForm(forms.ModelForm):

    class Meta:
        model = Social
        fields = ('numberVariant', 'task1', 'answ1', 'task2', 'answ2', 
                    'task3', 'answ3', 'task4', 'answ4', 'task5', 'answ5', 
                    'task6', 'answ6', 'task7', 'answ7', 'task7', 'answ7',
                    'task8', 'answ8', 'task9', 'answ9', 'task10', 'answ10', 
                    'task11', 'answ11','task12', 'answ12', 'task13', 'answ13', 
                    'task14', 'answ14', 'task15', 'answ15', 'task16', 'answ16',
                    'task17', 'answ17', 'task18', 'answ18', 'task19', 'answ19', 
                    'task20', 'answ20', 'task21', 'answ21', 'task22', 'answ22', 
                    'task23', 'answ23', 'task24', 'answ24', 'task25', 'answ25', 
                    'task26', 'answ26', 'task27', 'answ27', 'task28', 'answ28', 'task29', 'answ29')
        widgets={"numberVariant":forms.TextInput(attrs={'class':'create-variant__input'})}