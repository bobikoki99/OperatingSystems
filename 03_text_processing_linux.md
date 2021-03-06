-- 03-a-0200

Сортирайте /etc/passwd лексикографски по поле UserID.

cat /etc/passwd | sort -t: -k3

-- 03-a-0201

Сортирайте /etc/passwd числово по поле UserID.
(Открийте разликите с лексикографската сортировка)

cat etc/passwd | sort -n -t: -k3

-- 03-a-0210

Изведете само 1-ва и 5-та колона на файла /etc/passwd спрямо разделител ":".

cut -d: -f1,5

-- 03-a-0211

Изведете съдържанието на файла /etc/passwd от 2-ри до 6-ти символ.

cut -c 2-6 /etc/passwd
head -c 6 /etc/passwd | tail -c 5 

-- 03-a-1500

Намерете броя на символите в /etc/passwd. А колко реда има в /etc/passwd?

wc -c /etc/passwd
wc -l /etc/passwd

-- 03-a-2000

Извадете от файл /etc/passwd:
- първите 12 реда
head -n 12 /etc/passwd

- първите 26 символа
head -c 26 /etc/passwd

- всички редове, освен последните 4
head -n -4 /etc/passwd

- последните 17 реда
tail -n 17 /etc/passwd

- 151-я ред (или друг произволен, ако нямате достатъчно редове)
head -n 151 etc/passwd | tail -n 1

- последните 4 символа от 13-ти ред
cat my_pass | head -n 13 | tail -n 1 | rev | cut -c 1-4 | rev


-- 03-a-2100

Отпечатайте потребителските имена и техните home директории от /etc/passwd.

cat /etc/passwd | cut -d: -f1,6

-- 03-a-2110

Отпечатайте втората колона на /etc/passwd, разделена спрямо символ '/'.

cat /etc/passwd | cut -d/ -f2

-- 03-a-3000

Запаметете във файл в своята home директория резултатът от командата ls -l изпълнена за вашата home директорията.
Сортирайте създадения файла по второ поле (numeric, alphabetically).

touch 3a3000
ls -l > 3a3000
cat 3a3000 | sort -k2
cat 3a3000 | sort -nk2

-- 03-a-5000

Отпечатайте 2 реда над вашия ред в /etc/passwd и 3 реда под него // може да стане и без пайпове

grep -B2 -A3 s62348 /etc/passwd

-- 03-a-5001

Колко хора не се казват Ivan според /etc/passwd

grep -cv :Ivan /etc/passwd

-- 03-a-5002

Изведете имената на хората с второ име по-дълго от 7 (>7) символа според /etc/passwd

cat my_pass | cut -d: -f5 | cut -d, -f1 | egrep " [A-Za-z]{8,}"

-- 03-a-5003

Изведете имената на хората с второ име по-късо от 8 (<=7) символа според /etc/passwd // !(>7) = ?

cat my_pass | cut -d: -f5 | cut -d, -f1 | egrep " [A-Za-z]{,7}"
или
cat my_pass | cut -d: -f5 | cut -d, -f1 | egrep -v " [A-Za-z]{8,}"

-- 03-a-5004

Изведете целите редове от /etc/passwd за хората от 03-a-5003

cat my_pass | grep -v "$(cat my_pass | cut -d: -f5 | cut -d, -f1 | egrep " [A-Za-z]{8,}")" | wc -l


-- 03-b-0300

Намерете факултетния си номер във файлa /etc/passwd.

cat /etc/passwd | grep "Vasil Vasilev" | cut -d: -f1 | tr -d "s"

-- 03-b-3000

Запазете само потребителските имена от /etc/passwd във файл users във вашата home директория.

cat /etc/passwd | cut -d: -f5 | cut -d, -f1 > users.txt

-- 03-b-3400

Колко коментара има във файла /etc/services ? Коментарите се маркират със символа #, след който всеки символ на реда се счита за коментар.

cat /etc/services | grep -c "#"

-- 03-b-3450

Вижте man 5 services. Напишете команда, която ви дава името на протокол с порт естествено число N. Командата да не отпечатва нищо, ако търсения порт не съществува (например при порт 1337). Примерно, ако номера на порта N е 69, командата трябва да отпечати tftp.

cat /etc/services | grep -w 69 | tr "\t" " " | tr -s " " | cut -d " " -f1

-- 03-b-3500

Колко файлове в /bin са shell script? (Колко файлове в дадена директория са ASCII text?)

find /bin -type f | egrep "*.sh$"

-- 03-b-3600

Направете списък с директориите на вашата файлова система, до които нямате достъп. Понеже файловата система може да е много голяма, търсете до 3 нива на дълбочина. А до кои директории имате достъп? Колко на брой са директориите, до които нямате достъп?

find / -maxdepth 3 -type d -printf "%f %m\n" 2>/dev/null | grep -c " [3210]..$" 

-- 03-b-4000

Създайте следната файлова йерархия.
/home/s...../dir1/file1
/home/s...../dir1/file2
/home/s...../dir1/file3

Посредством vi въведете следното съдържание:
file1:
1
2
3

file2:
s
a
d
f

file3:
3
2
1
45
42
14
1
52

Изведете на екрана:
	* статистика за броя редове, думи и символи за всеки един файл
	cat file1 | wc -l 
	cat file1 | wc -w
	cat file1 | wc -m

	* статистика за броя редове и символи за всички файлове
	wc -lc file1 file2 file3

	* общия брой редове на трите файла
	wc -l file1 file2 file3 | tail -n 1 | cut -d ' ' -f1


-- 03-b-4001

Във file2 подменете всички малки букви с главни.
cat file2 | tr "a-z" "A-Z" > helper | cat helper > file2

-- 03-b-4002

Във file3 изтрийте всички "1"-ци.

sed -i "s/1//g" file3

-- 03-b-4003

Изведете статистика за най-често срещаните символи в трите файла.

cat file1 file2 file3 | grep -o . | sort | uniq -c

-- 03-b-4004

Направете нов файл с име по ваш избор, който е конкатенация от file{1,2,3}.
Забележка: съществува решение с едно извикване на определена програма - опитайте да решите задачата чрез него.

touch file4
cat file1 file2 file3 > file4

-- 03-b-4005

Прочетете текстов файл file1 и направете всички главни букви малки като запишете резултата във file2.

cat file1 | tr "A-Z" "a-z" > file2
tr "A-Z" "a-z" < file1 > file2

-- 03-b-5200

Изтрийте всички срещания на буквата 'a' (lower case) в /etc/passwd и намерете броят на оставащите символи.

cat /etc/passwd | tr -d 'a' | wc -c

-- 03-b-5300

Намерете броя на уникалните символи, използвани в имената на потребителите от /etc/passwd.

cat my_pass | cut -d: -f5 | cut -d, -f1 | grep -o . | sort | uniq -c | wc -l

-- 03-b-5400

Отпечатайте всички редове на файла /etc/passwd, които не съдържат символния низ 'ov'.

grep -v "ov" my_pass

-- 03-b-6100

Отпечатайте последната цифра на UID на всички редове между 28-ми и 46-ред в /etc/passwd.

cat my_pass | head -n 46 | tail -n 19 | cut -d: -f3 | rev | sed -r "s/(.)/\1 /g" | cut -d " " -f1

-- 03-b-6700

Отпечатайте правата (permissions) и имената на всички файлове, до които имате read достъп, намиращи се в директорията /tmp.

find /tmp -type f -perm -200 2>/dev/null -printf "%p %m\n" 

-- 03-b-6900

Намерете имената на 10-те файла във вашата home директория, чието съдържание е редактирано най-скоро. На първо място трябва да бъде най-скоро редактираният файл. Намерете 10-те най-скоро достъпени файлове. (hint: Unix time)

find /home/grade -type f -printf "%p %T@ \n" 2>/dev/null | sort -n -t " " -k2 -r | head -n 10

-- 03-b-7000

Файловете, които съдържат C код, завършват на `.c`.
Колко на брой са те във файловата система (или в избрана директория)?

find /home/grade/ -type f -printf "%p\n" | grep "\.c$"

Колко реда C код има в тези файлове?

find /home/grade/ -type f -name "*.c" -exec wc -l {} \; 


-- 03-b-7500

Даден ви е ASCII текстов файл (например /etc/services). Отпечатайте хистограма на N-те (например 10) най-често срещани думи.

cat /etc/services | sed "s/ /\n/g" | sed "s/\t/\n/g" | tr -d "\t" | sort | uniq -c | sort -nr | head -n 11 | tail -n 10

-- 03-b-8000

Вземете факултетните номера на студентите от СИ и ги запишете във файл si.txt сортирани.

cat my_pass | grep /home/SI/ | cut -d: -f1 | tr -d s | head -n -1


-- 03-b-8500

За всеки логнат потребител изпишете "Hello, потребител", като ако това е вашият потребител, напишете "Hello, потребител - this is me!".

Пример:

hello, human - this is me!
Hello, s63465
Hello, s64898

who | tr -s " " | awk -v curr=$(whoami) '{if ($1==curr) { printf ("Hello, %s - this is me\n", $1) } else { printf ("Hello, %s", $1) } }'

-- 03-b-8520

Изпишете имената на студентите от /etc/passwd с главни букви.

cat my_pass | cut -d: -f5 | cut -d, -f1 | tr "a-z" "A-Z"

-- 03-b-8600

Shell Script-овете са файлове, които по конвенция имат разширение .sh. Всеки такъв файл започва с "#!<interpreter>" , където <interpreter> указва на операционната система какъв интерпретатор да пусне (пр: "#!/bin/bash", "#!/usr/bin/python3 -u"). 

Намерете всички .sh файлове и проверете кой е най-често използваният интерпретатор.

find /home/grade -type f -name "*.sh" -exec egrep -e "^#\!" {} \; | sort | uniq -c

-- 03-b-8700

Намерете 5-те най-големи групи подредени по броя на потребителите в тях.



-- 03-b-9000

Направете файл eternity. Намерете всички файлове, които са били модифицирани в последните 15мин (по възможност изключете .).  Запишете във eternity името на файла и часa на последната промяна.

find /home/grade -type f -mmin -15 -printf "%f %Tr\n" > eternity.txt


-- 03-b-9050

Копирайте файл /home/tony/population.csv във вашата home директория.

cp /home/tony/population.csv /home/grade

-- 03-b-9051

Използвайки файл population.csv, намерете колко е общото население на света през 2008 година. А през 2016?

cat population.csv | grep ,2008, | awk -F ',' 'BEGIN {count = 0} {count += $4} END {print count}'
cat population.csv | grep ,2016, | awk -F ',' 'BEGIN {count = 0} {count += $4} END {print count}'


-- 03-b-9052

Използвайки файл population.csv, намерете през коя година в България има най-много население.

cat population.csv | grep ^Bulgaria | awk -F, 'BEGIN {max = 0; year = -1} {if ($4 > max) {max = $4; year = $3}} END {print year}'
или
cat population.csv | grep ^Bulgaria | sort -n -t, -k4 -r | head -n 1 | cut -d, -f3


-- 03-b-9053

Използвайки файл population.csv, намерете коя държава има най-много население през 2016. А коя е с най-малко население?
(Hint: Погледнете имената на държавите)

cat population.csv | grep ,2016, | grep $(cat population.csv | grep ,2016, | rev | cut -d, -f 1 | rev | sort -nr | head -n 1) | cut -d, -f1

cat population.csv | grep ,2016, | grep $(cat population.csv | grep ,2016, | rev | cut -d, -f 1 | rev | sort -r | head -n 1) | cut -d, -f1


-- 03-b-9054

Използвайки файл population.csv, намерете коя държава е на 42-ро място по население през 1969. Колко е населението й през тази година?

cat population.csv | grep ,1969, | grep $(cat population.csv | grep ,1969, | rev | cut -d, -f 1 | rev | sort -nr | head -n 42 | tail -n 1) | cut -d, -f1

-- 03-b-9100

В home директорията си изпълнете командата `curl -o songs.tar.gz "http://fangorn.uni-sofia.bg/misc/songs.tar.gz"`

-- 03-b-9101

Да се разархивира архивът songs.tar.gz в папка songs във вашата home директорията.
mkdir songs
cd /home/grade/songs
tar -xvf songs.tar.gz

-- 03-b-9102

Да се изведат само имената на песните.

find . -type f | cut -d - -f2 | sed "s/ //" | grep ".ogg"| cut -d '(' -f1

-- 03-b-9103

Имената на песните да се направят с малки букви, да се заменят спейсовете с долни черти и да се сортират.

find . -type f | cut -d - -f2 | sed "s/ //" | grep ".ogg"| cut -d '(' -f1 | tr "A-Z" "a-z" | sed "s/ /_/g" | sort | rev | sed "s/_//" | rev

-- 03-b-9104

Да се изведат всички албуми, сортирани по година.

find . -type f | cut -d - -f2 | sed "s/ //" | grep ".ogg"| cut -d '(' -f 2 | cut -d ')' -f1 | sort | uniq | sort -n -t, -k2

-- 03-b-9105

Да се преброят/изведат само песните на Beatles и Pink.

find . -type f -printf "%f\n" | egrep "^(Pink|Beatles) -"

-- 03-b-9106

Да се направят директории с имената на уникалните групи. За улеснение, имената от две думи да се напишат слято:
Beatles, PinkFloyd, Madness

find . -type f -printf "%f\n" | cut -d- -f1 | sort | uniq| tr -d " " | head -n -1 | xargs -I{} mkdir {}

-- 03-b-9200

Напишете серия от команди, които извеждат детайли за файловете и директориите в текущата директория, които имат същите права за достъп както най-големият файл в /etc директорията.

find . -printf "%f %m\n" 2>/dev/null | grep $(find /etc -printf "%f %s %m\n" 2>/dev/null | sort -n -t ' ' -k2 | tail -n 1 | cut -d ' ' -f3)


-- 03-b-9300

Дадени са ви 2 списъка с email адреси - първият има 12 валидни адреса, а вторията има само невалидни. Филтрирайте всички адреси, така че да останат само валидните. Колко кратък регулярен израз можете да направите за целта?

Валидни email адреси (12 на брой):
email@example.com
firstname.lastname@example.com
email@subdomain.example.com
email@123.123.123.123
1234567890@example.com
email@example-one.com
_______@example.com
email@example.name
email@example.museum
email@example.co.jp
firstname-lastname@example.com
unusually.long.long.name@example.com

Невалидни email адреси:
#@%^%#$@#$@#.com
@example.com
myemail
Joe Smith <email@example.com>
email.example.com
email@example@example.com
.email@example.com
email.@example.com
email..email@example.com
email@-example.com
email@example..com
Abc..123@example.com
(),:;<>[\]@example.com
just"not"right@example.com
this\ is"really"not\allowed@example.com

egrep "^[a-zA-Z0-9_-]+([.-]?[a-zA-Z0-9_]+)*@{1}[A-Za-z0-9]+[.-]{1}[A-Za-z0-9]+" emails.txt

-- 03-b-9500

Запишете във файл next потребителското име на човека, който е след вас в изхода на who. Намерете в /etc/passwd допълнителната ифнромация (име, специалност...) и също го запишете във файла next. Използвайки файла, изпратете му съобщение "I know who you are, информацията за студента"

Hint: можете да използвате командата expr, за да смятате аритметични изрази. Например, ще получим 13, ако изпълним: expr 10 + 3

Бонус: "I know who you are, само името му"
