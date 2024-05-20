#! /usr/bin/python3


# Erasthosthanes algo
def SieveOfEratosthenes(num):
	prime = [1 for i in range(num+1)]
    # boolean array
	p = 2
	while (p * p <= num) :
		# If prime[p] is not changed, then it is a prime
		if (prime[p] == 1):

			# Updating all multiples of p
			for i in range(p * p, num+1, p):
				prime[i] = 0
		p += 1

	for p in range(2, num+1):
		if prime[p]:
			print(p)


if __name__ == '__main__':
	num = 10000
	print("Following are the prime numbers smaller"),
	print("than or equal to", num)
	SieveOfEratosthenes(num)