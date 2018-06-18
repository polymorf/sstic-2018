#!/usr/bin/python2
from sage.doctest.util import Timer
from struct import pack, unpack
from polytools import *
import itertools

ttry = Timer()
t = Timer()

primes = [
      2,   3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97,
    101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
    233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379,
    383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
    547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691,
    701
]

K_MIN = 0x189AD793E6A9CE
K_MAX = 0x189AD793E6A9CE + 0x7FFFFFFFFFFFF

G=0x0f389b455d0e5c3008aaf2d3305ed5bc5aad78aa5de8b6d1bb87edf11e2655b6a8ec19b89c3a3004e48e955d4ef05be4defd119a49124877e6ffa3a9d4d1
#G=65537

def prime_factors(n, limit=None):
    num = []

    # add 2, 3 to list or prime factors and remove all even numbers(like sieve of ertosthenes)
    while n % 2 == 0:
        num.append(2)
        n = n // 2

    while n % 3 == 0:
        num.append(3)
        n = n // 3

    max_divisor = int(math.ceil(n ** 0.5)) if limit is None else limit
    d, i = 5, 2
    while d <= max_divisor:
        while n % d == 0:
            num.append(d)
            n = n // d

        d += i
        i = 6 - i  # this modifies 2 into 4 and vice versa

    if n > 2:
        num.append(n)

    return num

def factor_list_to_map(factors):
    ret = {}
    for k, g in itertools.groupby(factors):
        ret[k] = len(list(g))
    return ret

def small_factors(x, max_prime):
    factors = prime_factors(x, limit=max_prime)
    return factor_list_to_map(factors)

def element_order(element, modulus, phi_m, phi_m_decomposition):
    if element == 1:
        return 1  # by definition

    if pow(element, phi_m, modulus) != 1:
        return None  # not an element of the group

    order = phi_m
    for factor, power in list(phi_m_decomposition.items()):
        for p in range(1, power + 1):
            next_order = order // factor
            if pow(element, next_order, modulus) == 1:
                order = next_order
            else:
                break
    return order


def mul_inv(a, b):
    b0 = b
    x0, x1 = 0, 1
    if b == 1:
        return 1
    while a > 1:
        q = a // b
        a, b = b, a % b
        x0, x1 = x1 - q * x0, x0
    if x1 < 0:
        x1 += b0
    return x1

def chinese_remainder(n, a):
    sum = 0
    prod = reduce(lambda a, b: a * b, n)

    for n_i, a_i in zip(n, a):
        p = prod // n_i
        sum += a_i * mul_inv(p, n_i) * p
    return sum % prod

def discrete_log(element, generator, generator_order, generator_order_decomposition, modulus):
    if pow(element, generator_order, modulus) != 1:
        return None

    moduli = []
    remainders = []
    for prime, power in list(generator_order_decomposition.items()):
        prime_to_power = prime ** power
        order_div_prime_power = generator_order // prime_to_power  # g.div(generator_order, prime_to_power)
        g_dash = pow(generator, order_div_prime_power, modulus)
        h_dash = pow(element, order_div_prime_power, modulus)
        found = False
        for i in range(0, prime_to_power):
            if pow(g_dash, i, modulus) == h_dash:
                remainders.append(i)
                moduli.append(prime_to_power)
                found = True
                break
        if not found:
            return None

    ccrt = chinese_remainder(moduli, remainders)
    return ccrt


def gen_prime():
    prime=0
    while True:
        a = randrange(1<<0x79)
        k = randrange(K_MIN,K_MAX)
        prime = k*M + power_mod(G,a,M)
        if prime.is_prime():
            print "-"*40
            print "RAND a = ",a
            print "RAND k = ",k
            print "PRIME  = ",prime
            print "-"*40
            return prime


M = 1
phi_m = 1
for p in primes:
    M*=p
    phi_m*=(p-1)

phi_m_decomposition = small_factors(phi_m, 701)
generator_order = element_order(G, M, phi_m, phi_m_decomposition)
generator_order_decomposition = small_factors(generator_order, 701)
print generator_order_decomposition

#sys.exit(0)

p_max = K_MAX * M + M
p_min = K_MIN * M + 1

print "p_min = ",p_min
print "p_max = ",p_max
print "G     = ",G
print "M     = ",M

g = Mod(G,M)
print "g     = ",g

p=gen_prime()
q=gen_prime()
n = p * q
print "p     = ",p
print "q     = ",q
print "n     = ",n

print "generator_order = ",generator_order
c = discrete_log(n, G, generator_order, generator_order_decomposition, M)

print "dlog = ",c
