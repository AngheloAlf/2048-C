def quitarUltimo(frase, punto = "."):
	return punto.join(frase.split(punto)[:-1])

def agregarO(frase):
	return frase+".o"

def agregarh(frase):
	return frase+".h"

def escribirMakefile(iterable, makefile = "Makefile", saltoLinea = False):
	Makefile = open(makefile,"w")
	for i in iterable:
		Makefile.write(i)
		if saltoLinea:
			Makefile.write("\n")
	Makefile.write("\n")
	Makefile.close()
	return

def make_makefile(mainName, names = [], compilador = "g++", flags = ["-o","-c"], nombreFinal = "", errorsFlags = "-Wall", bat = False, rmBat = False, rmExe = False, noEscribir = False):
	#Se definen lineas predeterminadas
	comando = compilador + " {0} "+flags[0]+" {1} "+errorsFlags
	comando2 = compilador + " {0} "+flags[1]+" "+errorsFlags
	Linea = "{0}: {1}"

	#Se crea la variable que contendra los datos para posteriormente ser escritos
	#Se escribe la primera linea
	listaDatos = list()
	if nombreFinal == "":
		nombreFinal = quitarUltimo(mainName)
	escribir = "all: "+ nombreFinal+"\n\n"
	listaDatos.append(escribir)

	#Se genera una lista que contiene solo los comandos que se ejecutan por consola
	listaBat = list()

	#Se genera una variable con los requerimientos para la compilacion del archivo
	sinExtension = quitarUltimo(mainName)
	requerimientos = [sinExtension] + map(quitarUltimo, names)
	requerimientos = map(agregarO,requerimientos)

	#main: main.o a.o b.o c.o\n
	escribir = Linea.format(nombreFinal," ".join(requerimientos))+"\n"
	listaDatos.append(escribir)

	#\tg++ main.o a.o b.o c.o -o main -Wall\n\n
	archivos = " ".join(requerimientos)
	escribir = comando.format(archivos,nombreFinal)
	listaDatos.append("\t"+escribir+"\n\n")
	listaBat.append(escribir)

	#Se quita el elemento sobrante, el cual es el nombre del archivoFinal
	requerimientos = requerimientos[1:]

	#Se genera una lista con los archivos .h
	namesH = map(agregarh,map(quitarUltimo,names))
	listaDatos.append(Linea.format(agregarO(quitarUltimo(mainName)),mainName+" "+" ".join(namesH))+"\n")
	escribir = comando2.format(mainName)
	listaDatos.append("\t"+escribir+"\n\n")
	listaBat.append(escribir)

	#Se iteran y generan los requisitos
	for i in names:
		precompilado = agregarO(quitarUltimo(i))
		requisitos = [i]
		if type(names) == dict and names[i] != None:
			requisitos += names[i]
		listaDatos.append(Linea.format(precompilado," ".join(requisitos))+"\n")
		escribir = comando2.format(i)
		listaDatos.append("\t"+escribir+"\n\n")
		listaBat.append(escribir)

	#Se agrega la linea de limpiado
	listaDatos.append("clean:\n\t")
	escribir = "rm "+agregarO(sinExtension)+" "+" ".join(requerimientos)
	#Se agrega el comando para eliminar los precompilados al .bat
	if rmBat:
		listaBat.insert(0,escribir)
	if rmExe:
		escribir += " "+nombreFinal+" "+nombreFinal+".exe"
	listaDatos.append(escribir)

	#Se invierte el orden de los comandos
	listaBat = listaBat[::-1]

	#Se finaliza la funcion en caso de que no se quiera escribir a disco
	if noEscribir:
		return listaBat

	#Se escribe el archivo
	escribirMakefile(listaDatos)

	#Se escribe un "Makefile" que contiene solo los comandos de compilacion en formato ".bat"
	#De esta forma, se puede ejecutar desde Windows si se tiene los compiladores adecuados
	if bat:
		escribirMakefile(listaBat, "Makefile.bat", True)

	return listaBat

##2 ejemplos de llamada a la funcion
#make_makefile("main.cpp", names = {"a.cpp":("b.h","d.h"), "b.cpp":None, "c.cpp":None})
#make_makefile("main.cpp", names = ["a.cpp","l.cpp","f.cpp"], bat = True)

def menu():
	print "\t\t--Bienvenido al asistente de creacion de Makefile--"
	mainName = raw_input("Ingrese el nombre de su codigo principal (debe incluir la extension del archivo)\nNombre del codigo: ")
	ext = raw_input("\nSu codigo necesita de algun modulo externo? (S/n)")
	names = list()
	if ext.upper() == "S" or ext.lower() == "si":
		print "Ingrese el nombre de los modulos, todos en una linea y separados por un espacio (con extension, no el header)"
		names = raw_input("Modulos: ").split()

	print "\nIngrese un nombre para el ejecutable final (Si se deja en blanco, se generara nombre automaticamente)"
	nombreFinal = raw_input("Nombre ejecutable: ")

	print "\nDesea entrar en las opciones avanzadas?"
	avanzadas = raw_input("(s/N): ")
	if avanzadas.upper() == "S" or avanzadas.lower() == "si":

		print "\nIngrese el compilador que desea utilizar (defecto = g++)"
		compilador = raw_input("Compilador: ")
		if not compilador: 
			compilador = "g++"

		print "\nIngrese flags para los precompilados (defecto = -c)"
		precompilado = raw_input("Flags precompilados: ")
		if not precompilado:
			flags = [None, "-c"]
		else:
			flags = [None, precompilado]

		print "\nIngrese flags para la compilacion final (defecto = -o)"
		compilado = raw_input("Flags compilacion: ")
		if not compilado:
			flags[0] = "-o"
		else:
			flags[0] = compilado

		print "\nIngrese algun flag para errores (defecto = -Wall)"
		errores = raw_input("Flags errores: ")
		if not errores:
			errores = "-Wall"

		print "\nDesea generar un archivo Makefile.bat? (s/N)"
		bat = raw_input("bat file: ")
		if bat.lower() == "s" or bat.lower() == "si":
			bat = True
		else:
			bat = False

		if bat:
			print "\nDesea que el archivo Makefile.bat elimine los precompilados (s/N)"
			rmBat = raw_input("rm precompilados: ")
			if rmBat.lower() == "s" or rmBat.lower() == "si":
				rmBat = True
			else:
				rmBat = False

		print "\nDesea que el comando clean del Makefile elimine los ejecutables? (s/N)"
		rmExe = raw_input("rm ejecutables: ")
		if rmExe.lower() == "s" or rmExe.lower() == "si":
			rmExe = True
		else:
			rmExe = False

		make_makefile(mainName, names = names, compilador = compilador, flags = flags, nombreFinal = nombreFinal, errorsFlags = errores, bat = bat, rmBat = rmBat, rmExe = rmExe)

	else:
		make_makefile(mainName, names = names, nombreFinal = nombreFinal)

if __name__ == "__main__":
	menu()
	