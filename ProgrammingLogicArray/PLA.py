import QM

def getsets(noOfFunction, checker, binaries):
	sets = []

	for i in range(len(checker)):
		temp = []
		for j in range(noOfFunction):
			if checker[i][j] == '0':
				temp += binaries[2*j + 1]
			else:
				temp += binaries[2*j]
		sets.append(list(set(temp)))

	return sets

def getBinary(noOfVariable, mintermf, mintermfNot):

	binaryFunc = []

	for i in range(len(mintermf)):
		binaryFunc.append(QM.decimal_to_binary(noOfVariable, mintermf[i]))
		binaryFunc.append(QM.decimal_to_binary(noOfVariable, mintermfNot[i]))

	return binaryFunc  

def main():
	noOfFunction = int(input("Enter the no. of function: "))
	noOfVariable = int(input("Enter the no. of variable: "))
	mintermf = []
	for i in range(noOfFunction):
		mintermf.append([int(x) for x in input("Enter the minterms of Funtion %d \n"%(i+1)).split()])
	mintermfNot = []
	for i in range(noOfFunction):
		temp = []
		for j in range(2 ** noOfVariable):
			if j not in mintermf[i]:
				temp.append(j)
		mintermfNot.append(temp)

	binaries = getBinary(noOfVariable, mintermf, mintermfNot)

	minimizedFunction = []

	for i in range(2 * noOfFunction):
		prime_implicants = QM.check(binaries[i])
		chart = QM.prime_implicant_chart(prime_implicants, binaries[i])
		essential_prime_implicants = QM.selection(chart, prime_implicants)

		minimizedFunction.append(essential_prime_implicants)

	checker = QM.decimal_to_binary(noOfFunction, list(range(2 ** noOfFunction)))

	setsOfFuntion = getsets(noOfFunction, checker, minimizedFunction)

	setSize = [len(x) for x in setsOfFuntion]

	minimum = QM.bindec(setSize.index(min(setSize)), noOfFunction)

	print("Function which have to be realised")

	for i in range(len(minimum)):
		if minimum[i] == '0':
			print("F%d'"%(i+1), end = ' ')
		else:
			print("F%d"%(i+1), end = ' ')

	print()
if __name__ == '__main__':
	main()