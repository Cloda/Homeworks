# Generated by Django 2.2.6 on 2020-01-08 20:12

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('subjects', '0032_auto_20200108_2147'),
    ]

    operations = [
        migrations.AddField(
            model_name='russia',
            name='answ2',
            field=models.CharField(blank=True, default='', max_length=100, verbose_name='Ответ'),
        ),
        migrations.AddField(
            model_name='russia',
            name='answ3',
            field=models.CharField(blank=True, default='', max_length=100, verbose_name='Ответ'),
        ),
        migrations.AddField(
            model_name='russia',
            name='answ4',
            field=models.CharField(blank=True, default='', max_length=100, verbose_name='Ответ'),
        ),
        migrations.AddField(
            model_name='russia',
            name='answ5',
            field=models.CharField(blank=True, default='', max_length=100, verbose_name='Ответ'),
        ),
        migrations.AddField(
            model_name='russia',
            name='answ6',
            field=models.CharField(blank=True, default='', max_length=100, verbose_name='Ответ'),
        ),
        migrations.AddField(
            model_name='russia',
            name='task2',
            field=models.TextField(blank=True, default='', verbose_name='Задание 2'),
        ),
        migrations.AddField(
            model_name='russia',
            name='task3',
            field=models.TextField(blank=True, default='', verbose_name='Задание 3'),
        ),
        migrations.AddField(
            model_name='russia',
            name='task4',
            field=models.TextField(blank=True, default='', verbose_name='Задание 4'),
        ),
        migrations.AddField(
            model_name='russia',
            name='task5',
            field=models.TextField(blank=True, default='', verbose_name='Задание 5'),
        ),
        migrations.AddField(
            model_name='russia',
            name='task6',
            field=models.TextField(blank=True, default='', verbose_name='Задание 6'),
        ),
        migrations.AddField(
            model_name='social',
            name='answ2',
            field=models.CharField(blank=True, default='', max_length=100, verbose_name='Ответ'),
        ),
        migrations.AddField(
            model_name='social',
            name='answ3',
            field=models.CharField(blank=True, default='', max_length=100, verbose_name='Ответ'),
        ),
        migrations.AddField(
            model_name='social',
            name='answ4',
            field=models.CharField(blank=True, default='', max_length=100, verbose_name='Ответ'),
        ),
        migrations.AddField(
            model_name='social',
            name='answ5',
            field=models.CharField(blank=True, default='', max_length=100, verbose_name='Ответ'),
        ),
        migrations.AddField(
            model_name='social',
            name='answ6',
            field=models.CharField(blank=True, default='', max_length=100, verbose_name='Ответ'),
        ),
        migrations.AddField(
            model_name='social',
            name='task2',
            field=models.TextField(blank=True, default='', verbose_name='Задание 2'),
        ),
        migrations.AddField(
            model_name='social',
            name='task3',
            field=models.TextField(blank=True, default='', verbose_name='Задание 3'),
        ),
        migrations.AddField(
            model_name='social',
            name='task4',
            field=models.TextField(blank=True, default='', verbose_name='Задание 4'),
        ),
        migrations.AddField(
            model_name='social',
            name='task5',
            field=models.TextField(blank=True, default='', verbose_name='Задание 5'),
        ),
        migrations.AddField(
            model_name='social',
            name='task6',
            field=models.TextField(blank=True, default='', verbose_name='Задание 6'),
        ),
    ]