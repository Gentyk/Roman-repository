# Сущности
В коде два класса: **Студент** и **Официальный отчет**.

## Студент
У него есть приватные поля (те, что юзаются только в классе): 
Имя(first_name), фамилия(second_name), имя группы, которой он принадлежит и выводы врачей (строки).

Есть конструктор, деструктор (для удаления динамических вещей (кардио)) и методы фиксирования врачебых решений - public вещи.

## Официальный отчет
Официальный отчет - это строка. Здесь мы демонстрируем перегрузку оператора. В данном случае речь идет об операторе +. Обычно "+" - символ суммы чисел или соединения двух строк. Здесь же мы говорим, что у нас новый метода (соединяем две строки, а между ними засовываем строку с минусами) - типа для красоты.

## Логика работы
 - вводим имя группы и колво-студентов
 - резервируем память
 - заполняем - заключения врачей заполнил "автоматически"
 - составляем отчет с помощью нашего "+"
 - записываем отчет в файл
 - чистим мусор
 
## Изменения с логикой Ильяса
Методы по решениям врачей не фиксировали вынесенные решения, поэтому переделал, чтобы работало. Кардио я также изменил на динамический. По крайней мере тербованиям на бумажке мои методы не противоречат.
