# Generated by Django 2.2.6 on 2019-12-25 10:13

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('subjects', '0019_auto_20190320_1911'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='task',
            name='first',
        ),
        migrations.RemoveField(
            model_name='task',
            name='forth',
        ),
        migrations.RemoveField(
            model_name='task',
            name='second',
        ),
        migrations.RemoveField(
            model_name='task',
            name='third',
        ),
        migrations.AlterField(
            model_name='task',
            name='nameLevel',
            field=models.ForeignKey(on_delete=django.db.models.deletion.PROTECT, to='subjects.Level', verbose_name='Какой предмет'),
        ),
        migrations.AlterField(
            model_name='task',
            name='nameSubjects',
            field=models.ForeignKey(on_delete=django.db.models.deletion.PROTECT, to='subjects.Subject', verbose_name='Какая работа'),
        ),
    ]