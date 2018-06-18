#!/usr/bin/python2
from struct import pack, unpack
import itertools
from random import randrange, choice
import threading
from sage.doctest.util import Timer
from polytools import *

def size_in_bit(val):
    return len(bin(val).replace("0b","").replace("L",""))


primes = [
      2,   3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97,
    101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
    233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379,
    383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
    547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691,
    701
]

G=0x0f389b455d0e5c3008aaf2d3305ed5bc5aad78aa5de8b6d1bb87edf11e2655b6a8ec19b89c3a3004e48e955d4ef05be4defd119a49124877e6ffa3a9d4d1

def gen_prime():
    prime=0
    while True:
        a = randrange(1<<(0x79 * 8))
        k = randrange(K_MIN,K_MAX)
        prime = k*M + power_mod(G,a,M)
        if prime.is_prime():
            print "-"*40
            print "RAND a = ",a
            print "RAND k = ",k
            print "PRIME  = ",prime
            print "-"*40
            return prime

def get_prime_factors(X):
    factors=[]
    for p in primes:
        if X % p == 0:
            factors.append(p)
    return factors

def get_prime_factors_level2(M):
    level2_primes=[]
    for i in get_prime_factors(M):
        for j in get_prime_factors(M):
            if i == j:
                continue
            val = i*j
            if val not in level2_primes:
                level2_primes.append(val)
    return level2_primes

def get_prime_factors_level3(M):
    level2_primes=get_prime_factors_level2(M)
    level3_primes=[]
    for i in get_prime_factors(M):
        for j in level2_primes:
            if j % i == 0:
                continue
            val = i * j
            if val not in level3_primes:
                level3_primes.append(val)
    return level3_primes



M = 1
for p in primes:
    M*=p

generator_order = Mod(G,M).multiplicative_order()


t = Timer()

min_size = size_in_bit(M)
next_M = M
ord_at_min = generator_order

primes_level_generators = [
    get_prime_factors,
    get_prime_factors_level2,
    get_prime_factors_level3,
]



for level in range(3):
    print "="*40 + " level %d " % (level) + "="*40
    while True:
        t.start()
        M = next_M
        best=None
        factor_list = primes_level_generators[level](M)
        print "LEVEL%d reduction start : %d candidate" % (level,len(factor_list))
        for l in factor_list:
            M_prime = M / (l)
            ord_prime = Mod(G,M_prime).multiplicative_order()

            if ord_at_min > ord_prime:
                next_M = M_prime
                best=l
                ord_at_min = ord_prime
                if level == 2:
                    print "reduction level %d found candidate : size = %d bits" % (level, size_in_bit(next_M))
                    print "          order   = ",ord_at_min
                    print "          m_prime = ",next_M

        if best == None:
            print "reduction level %d finished : size = %d bits" % (level, size_in_bit(next_M))
            print "          order   = ",ord_at_min
            print "          m_prime = ",next_M
            break
        print "END loop best divisor is %d, size = %d bits, found in %s" % (best, size_in_bit(next_M), t.stop().cputime)


# best divisor are (149,421,661), size = 532 bits, found in 0.029507
#           order   =  924
#           m_prime =  9401609904398470577377671865950185420845551196526604360647948191834660218163860515949335907339066922354988390904229503570160603744663859776532492190133339145370

