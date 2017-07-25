import nation
import re

Nation = nation.nation(open('D://programme//pythoncharm//NATION//nationsDict.dat', "r"))
print(Nation.getdic())
Nation.pop_density()
print(Nation.getwords())

country = input("Enter a country: ")
while(True):
    try:
        items = Nation.getwords()[Nation.getdic()[country]]
        print('Continent: '+str(items[1])+'\n')
        print('Population: '+str(int(float(items[2])*1000000))+'\n')
        print('Area: '+str(float(items[3]))+' square miles'+'\n')
    except:
        print('Error\n')
    country = input("Enter a country: ")