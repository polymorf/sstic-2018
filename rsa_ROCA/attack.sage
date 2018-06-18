from sage.doctest.util import Timer
t = Timer()

L = 561914277705127653802070334008637178173253994314586711802612545624757659941226333370288234149988801024187383535530106733166193463367006453312899727108854355747645
order = 168
G = 0x0f389b455d0e5c3008aaf2d3305ed5bc5aad78aa5de8b6d1bb87edf11e2655b6a8ec19b89c3a3004e48e955d4ef05be4defd119a49124877e6ffa3a9d4d1

n = 0xa0e1cdfcc3141ec0a071247edf251a4a118dc8789e1c44f5ba63e4b6b3f34210796446575b12bddc0d73ecc3a5b398fcbdc0dcc71b2dfacf01be12500ac6a572f2829d2bfa9af28bf873dc4a299ad8d03345c5ffc9c07a86bdd01c30bbeac413bddd3e928ae86e8c2a2ada44e4f0353e8d2e992446569d96769e405417e821082a196fb5c895d98b6d269214984393617b860b255d1d0c62a5e1f1717bc7772614d87e56732959caea30000d1b5957294e7a5cab70e5988bc1e206e7e6d0ca095f68e3414ece1ddb0e88ce7667cca91b7c988829976e1455f9843a5e7da1a2b36a2a238765e8d5d421876a52eb4e077d862266f7b6b0dda7a1f2d02d430e311d
#n = 0xdf3bc349ea89004a1b5f79028c0a4a63e83b6262cb1c301d77da0d68292bde3f1a38662011d8e3e244912c6eda9e1712d2e694e08d28cf148cacc756150cd0073d67e34ad9e4b8124fdd5527b325be2626a8d468a742d16e7dea738dea66576b92b31eb08b6aa74c8653e597612463059059789abea4ee09010aba67c6d271d68bd0b1255c2eeb5baa92009b6cd4ad6ece8c3fdd60c0c30eacf1c7dd72b0d7ddeef13b33ca65dc6249f725f67d01d3fc9dbf53250e04f294b5fe3074bf28829479983af786b1dd487dd2fbf83056f033f51190a900b03db4741fdafa0512645a4146b0d3cdabfd3b16868a7931e0d2893e5f90c5e614c11ac9012cdbf4025845
# print 'public key',n


for power in range(order):
  v = L
  g = G
  u = power_mod(g,power,L)

  t.start()

  H = 10 + 2**1021 // v
  u += floor((7*2**1021) // v) * v

  w = lift(1/Mod(v,n))

  R.<x> = QQ[]
  f = (w*u+H*x)/n
  g = H*x

  k = 3
  m = 7
  # print 'multiplicity',k
  # print 'lattice rank',m

  basis = [f^j for j in range(0,k)] + [f^k*g^j for j in range(m-k)]
  basis = [b*n^k for b in basis]
  basis = [b.change_ring(ZZ) for b in basis]

  M = matrix(m)
  for i in range(m):
    M[i] = basis[i].coefficients(sparse=False) + [0]*(m-1-i)
  # print 'time for creating matrix',t.stop().cputime

  t.start()
  M = M.LLL()
  # print 'time for basis reduction',t.stop().cputime

  Q = sum(z*(x/H)^i for i,z in enumerate(M[0]))

  for r,multiplicity in Q.roots():
    # print 'root is',r
    if u+v*r > 0:
      print "r",r
      print "u",u
      print "v",v
      g = gcd(n,u+v*r)
      if g > 1:
        print 'successful factorization'
        print '\tpower',power
        print '\tprime1',g
        print '\tprime2',n/g
        sys.exit()