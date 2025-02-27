n1 = float(input("digite o nota 1: "))
n2 = float(input("digite o nota 2: "))
n3 = float(input("digite o nota 3: "))
n4 = float(input("digite o nota 4: "))
media = (n1 + n2 + n3 + n4) / 4
print("media: ", media)
###########################################################
metros = float(input("digite o valor em metros: "))
centimetros = metros * 100
print("centimetros: ", centimetros)
############################################################
raio = float(input("digite o raio: "))
area = 3.14 * (raio ** 2)
print("area: ", area)
############################################################
lado = float(input("digite o tamanho do lado do quadrado: "))
area = lado ** 2
dobroArea = area * 2
print("dobro da area:", dobroArea)
############################################################
salario = float(input("Qual o seu salario mensal? "))
diasTrabalhados = float(input("Quantos dias trabalhados? "))
horasDia = float(input("Quantas horas voce trabalha por dia? "))
salarioHora = salario / (diasTrabalhados * horasDia)
print("Voce recebe", salarioHora, " por hora")
###########################################################
f = float("temperatura em Fahrenheit: ")
c = 5*((f - 32)/5)
k = c + 273
print("a temperatura em Celcius: ",c)
print("a temperatura em Kelvin: ",k)
##########################################################
n1 = int(input("digite o primeiro numero inteiro:" ))
n2 = int(input("digite o segundo numero inteiro: "))
n3 = float(input("digite o terceiro numero real"))
a = (2*n1)*(n2/2)
b = (3*n1)+n3
c = n3**3
print(a)
print(b)
print(c)
###########################################################
altura = float(input("digite a altura: "))
pesoIdeal = (72.7 * altura) - 58
print("peso ideal ", pesoIdeal)
###########################################################
sexo = input("Qual o seu sexo? (m/f) ")
altura = float(input("digite a altura: "))
if sexo == 'f':
    pesoIdeal = (72.7 * altura) - 58
elif sexo == "m":
    pesoIdeal = (72.7 * altura) - 58

print("peso ideal ", pesoIdeal)
############################################################